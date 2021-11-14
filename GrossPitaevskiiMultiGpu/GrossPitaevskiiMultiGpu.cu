#include <cuda_runtime.h>
#include "helper_cuda.h"

#include "VortexState.hpp"
#include "Output/Picture.hpp"
#include "Output/Text.hpp"
#include "Types/Complex.hpp"
#include "Types/Random.hpp"
#include "Mesh/DelaunayMesh.hpp"

#include <iostream>
#include <sstream>
#include <chrono>

#include <mesh.h>

ddouble RATIO = 0.1;
ddouble KAPPA = 20;
ddouble G = 5000;

#define LOAD_STATE_FROM_DISK 1
#define SAVE_PICTURE 0
#define SAVE_VOLUME 0

#define THREAD_BLOCK_X 16
#define THREAD_BLOCK_Y 1
#define THREAD_BLOCK_Z 1

#define WARP_SIZE 32

ddouble potentialRZ(const ddouble r, const ddouble z)
{
	return 0.5 * (r * r + RATIO * RATIO * z * z);
}

ddouble potentialV3(const Vector3& p)
{
	return 0.5 * (p.x * p.x + p.y * p.y + RATIO * RATIO * p.z * p.z);
}

bool saveVolumeMap(const std::string& path, const Buffer<ushort>& vol, const uint xsize, const uint ysize, const uint zsize, const Vector3& h)
{
	Text rawpath;
	rawpath << path << ".raw";

	// save raw
	std::ofstream fs(rawpath.str().c_str(), std::ios_base::binary | std::ios::trunc);
	if (fs.fail()) return false;
	fs.write((char*)&vol[0], 2 * xsize * ysize * zsize);
	fs.close();

	// save header
	Text text;

	text << "ObjectType              = Image" << std::endl;
	text << "NDims                   = 3" << std::endl;
	text << "BinaryData              = True" << std::endl;
	text << "CompressedData          = False" << std::endl;
	text << "BinaryDataByteOrderMSB  = False" << std::endl;
	text << "TransformMatrix         = 1 0 0 0 1 0 0 0 1" << std::endl;
	text << "Offset                  = " << -0.5 * xsize * h.x << " " << -0.5 * ysize * h.y << " " << -0.5 * zsize * h.z << std::endl;
	text << "CenterOfRotation        = 0 0 0" << std::endl;
	text << "DimSize                 = " << xsize << " " << ysize << " " << zsize << std::endl;
	text << "ElementSpacing          = " << h.x << " " << h.y << " " << h.z << std::endl;
	text << "ElementNumberOfChannels = 1" << std::endl;
	text << "ElementType             = MET_USHORT" << std::endl;
	text << "ElementDataFile         = " << rawpath.str() << std::endl;
	text.save(path);
	return true;
}

struct BlockPsis
{
	double2 values[VALUES_IN_BLOCK];
};

struct LdsBlockPsis
{
	double3 values[VALUES_IN_BLOCK];
};

struct BlockPots
{
	double values[VALUES_IN_BLOCK];
};

struct PitchedPtr
{
	char* ptr;
	size_t pitch;
	size_t slicePitch;
};

// Arithmetic operators for cuda vector types
inline __host__ __device__ double2 operator+(double2 a, double2 b)
{
	return make_double2(a.x + b.x, a.y + b.y);
}
inline __host__ __device__ double2 operator-(double2 a, double2 b)
{
	return make_double2(a.x - b.x, a.y - b.y);
}
inline __host__ __device__ void operator+=(double2& a, double2 b)
{
	a.x += b.x;
	a.y += b.y;
}
inline __host__ __device__ double2 operator*(double b, double2 a)
{
	return make_double2(b * a.x, b * a.y);
}

__device__ const uint perms[VALUES_IN_BLOCK][FACE_COUNT] = {
		{3, 2, 0, 1}, // 0
		{2, 0, 1, 3}, // 1
		{1, 0, 2, 3}, // 2
		{1, 0, 2, 3}, // 3 
		{2, 0, 1, 3}, // 4
		{3, 1, 0, 2}, // 5
		{0, 1, 2, 3}, // 6
		{0, 1, 2, 3}, // 7
		{3, 1, 0, 2}, // 8
		{2, 3, 0, 1}, // 9
		{2, 3, 0, 1}, // 10
		{3, 2, 0, 1}  // 11
};

__global__ void update(PitchedPtr nextStep, PitchedPtr prevStep, PitchedPtr potentials, int3* blockDirs, int* valueInds, double* hodges, double g, uint3 dimensions)
{
	size_t xid = blockIdx.x * blockDim.x + threadIdx.x;
	size_t yid = blockIdx.y * blockDim.y + threadIdx.y;
	size_t zid = blockIdx.z * blockDim.z + threadIdx.z;
	size_t dataXid = xid / VALUES_IN_BLOCK; // One thread per every dual node so VALUES_IN_BLOCK threads per mesh block (on z-axis)

	// Kill the leftover threads but leave threads for the additional zero buffer at the edges
	if (dataXid > dimensions.x || yid > dimensions.y || zid > dimensions.z)
	{
		return;
	}

	__shared__ LdsBlockPsis ldsPrevPsis[THREAD_BLOCK_Z * THREAD_BLOCK_Y * THREAD_BLOCK_X];
	size_t threadIdxInBlock = threadIdx.z * THREAD_BLOCK_Y * THREAD_BLOCK_X + threadIdx.y * THREAD_BLOCK_X + threadIdx.x / VALUES_IN_BLOCK;

	size_t dualNodeId = xid % VALUES_IN_BLOCK; // Dual node id. One thread per every dual node so VALUES_IN_BLOCK threads per mesh block (on z-axis)

	char* prevPsi = prevStep.ptr + prevStep.slicePitch * zid + prevStep.pitch * yid + sizeof(BlockPsis) * dataXid;
	BlockPots* pot = (BlockPots*)(potentials.ptr + potentials.slicePitch * zid + potentials.pitch * yid) + dataXid;
	BlockPsis* nextPsi = (BlockPsis*)(nextStep.ptr + nextStep.slicePitch * zid + nextStep.pitch * yid) + dataXid;
	double2 prev = ((BlockPsis*)prevPsi)->values[dualNodeId];
	ldsPrevPsis[threadIdxInBlock].values[dualNodeId] = make_double3(prev.x, prev.y, 0);
	double normsq = prev.x * prev.x + prev.y * prev.y;

	// Kill also the leftover edge threads
	if (dataXid == dimensions.x || yid == dimensions.y || zid == dimensions.z)
	{
		return;
	}

	uint idxInWarp = threadIdxInBlock % WARP_SIZE;

	uint primaryFaceStart = dualNodeId * FACE_COUNT;
	double2 sum = make_double2(0, 0);

	__syncthreads();
#pragma unroll
	for (int i = 0; i < FACE_COUNT; ++i)
	{
		uint primaryFace = primaryFaceStart + perms[dualNodeId][i];

		int neighbourX = threadIdx.x / VALUES_IN_BLOCK + blockDirs[primaryFace].x;
		int neighbourY = threadIdx.y + blockDirs[primaryFace].y;
		int neighbourZ = threadIdx.z + blockDirs[primaryFace].z;

		double2 neighbourPsi;

		// Read from the local shared memory
		if ((0 <= neighbourX) && (neighbourX < THREAD_BLOCK_X) &&
			(0 <= neighbourY) && (neighbourY < THREAD_BLOCK_Y) &&
			(0 <= neighbourZ) && (neighbourZ < THREAD_BLOCK_Z))
		{
			int neighbourIdx = neighbourZ * THREAD_BLOCK_Y * THREAD_BLOCK_X + neighbourY * THREAD_BLOCK_X + neighbourX;
			double3 temp = ldsPrevPsis[neighbourIdx].values[valueInds[primaryFace]];
			neighbourPsi = make_double2(temp.x, temp.y);
		}
		else // Read from the global memory
		{
			int offset = blockDirs[primaryFace].z * prevStep.slicePitch + blockDirs[primaryFace].y * prevStep.pitch + blockDirs[primaryFace].x * sizeof(BlockPsis);
			neighbourPsi = ((BlockPsis*)(prevPsi + offset))->values[valueInds[primaryFace]];
		}
		sum += hodges[primaryFace] * (neighbourPsi - prev);
	}

	sum += (pot->values[dualNodeId] + g * normsq) * prev;

	nextPsi->values[dualNodeId] += make_double2(sum.y, -sum.x);
};

ddouble integrateInTime(const VortexState& state, const ddouble block_scale, const Vector3& minp, const Vector3& maxp, const ddouble iteration_period, const uint number_of_iterations, uint gpuCount, bool enablePeerAccess = true)
{
	uint i, j, k, l;

	// find dimensions
	const Vector3 domain = maxp - minp;
	const uint xsize = uint(domain.x / (block_scale * BLOCK_WIDTH.x)) + 1;
	const uint ysize = uint(domain.y / (block_scale * BLOCK_WIDTH.y)) + 1;
	const uint zsize = uint(domain.z / (block_scale * BLOCK_WIDTH.z)) + 1;
	const Vector3 p0 = 0.5 * (minp + maxp - block_scale * Vector3(BLOCK_WIDTH.x * xsize, BLOCK_WIDTH.y * ysize, BLOCK_WIDTH.z * zsize));

	std::vector<uint> zSizes(gpuCount);
	uint zRemainder = zsize % gpuCount;
	for (uint gpuIdx = 0; gpuIdx < gpuCount; ++gpuIdx)
	{
		zSizes[gpuIdx] = zsize / gpuCount;
		if (zRemainder)
		{
			zSizes[gpuIdx]++;
			zRemainder--;
		}
		//std::cout << "GPU " << gpuIdx << " z-size: " << zSizes[gpuIdx] << ", ";
	}
	//std::cout << std::endl;

	std::cout << "Problem size: " << xsize << ", " << ysize << ", " << zsize << std::endl;
	//std::cout << "z-slice size: " << xsize << ", " << ysize << std::endl;

	// find relative circumcenters for each body element
	Buffer<Vector3> bpos;
	getPositions(bpos);

	// compute discrete dimensions
	const uint bsize = bpos.size(); // number of values inside a block
	const uint bxsize = (xsize + 1) * bsize; // number of values on x-row
	const uint bxysize = (ysize + 1) * bxsize; // number of values on xy-plane
	const uint ii0 = (IS_3D ? bxysize : 0) + bxsize + bsize; // reserved zeros in the beginning of value table
	const uint vsize = ii0 + (IS_3D ? zsize + 1 : zsize) * bxysize; // total number of values

	//std::cout << "bodies = " << xsize * ysize * zsize * bsize << std::endl;

	// initialize stationary state
	Buffer<Complex> Psi0(vsize, Complex(0, 0)); // initial discrete wave function
	Buffer<ddouble> pot(vsize, 0.0); // discrete potential multiplied by time step size
	ddouble g = state.getG(); // effective interaction strength
	ddouble maxpot = 0.0; // maximal value of potential
	for (k = 0; k < zsize; k++)
	{
		for (j = 0; j < ysize; j++)
		{
			for (i = 0; i < xsize; i++)
			{
				for (l = 0; l < bsize; l++)
				{
					const uint ii = ii0 + k * bxysize + j * bxsize + i * bsize + l;
					const Vector3 p(p0.x + block_scale * (i * BLOCK_WIDTH.x + bpos[l].x), p0.y + block_scale * (j * BLOCK_WIDTH.y + bpos[l].y), p0.z + block_scale * (k * BLOCK_WIDTH.z + bpos[l].z)); // position
					Psi0[ii] = state.getPsi(p);
					pot[ii] = potentialV3(p);
					const ddouble poti = pot[ii] + g * Psi0[ii].normsq();
					if (poti > maxpot) maxpot = poti;
				}
			}
		}
	}

	// find terms for laplacian
	Buffer<int3> blockDirs;
	Buffer<int> valueInds;
	Buffer<ddouble> hodges;
	ddouble lapfac = -0.5 * getLaplacian(blockDirs, valueInds, hodges) / (block_scale * block_scale);
	const uint lapsize = blockDirs.size() / bsize;
	ddouble lapfac0 = lapsize * (-lapfac);

	// compute time step size
	const uint steps_per_iteration = 691; // uint(iteration_period * (maxpot + lapfac0)) + 1; // number of time steps per iteration period
	const ddouble time_step_size = iteration_period / ddouble(steps_per_iteration); // time step in time units

	std::cout << "steps_per_iteration = " << steps_per_iteration << std::endl;

	// multiply terms with time_step_size
	g *= time_step_size;
	lapfac *= time_step_size;
	lapfac0 *= time_step_size;
	for (i = 0; i < vsize; i++) pot[i] *= time_step_size;
	for (int i = 0; i < hodges.size(); ++i) hodges[i] = -0.5 * hodges[i] / (block_scale * block_scale) * time_step_size;

	// Initialize host memory
	size_t dxsize = xsize + 2; // One element buffer to both ends
	size_t dysize = ysize + 2;
	size_t hostSize = dxsize * dysize * (zsize + 2);
	BlockPsis* h_evenPsi;// = new BlockPsis[dxsize * dysize * (zsize + 2)];
	BlockPsis* h_oddPsi;// = new BlockPsis[dxsize * dysize * (zsize + 2)];
	BlockPots* h_pot;// = new BlockPots[dxsize * dysize * (zsize + 2)];
	checkCudaErrors(cudaMallocHost(&h_evenPsi, hostSize * sizeof(BlockPsis)));
	checkCudaErrors(cudaMallocHost(&h_oddPsi, hostSize * sizeof(BlockPsis)));
	checkCudaErrors(cudaMallocHost(&h_pot, hostSize * sizeof(BlockPots)));
	memset(h_evenPsi, 0, hostSize * sizeof(BlockPsis));
	memset(h_oddPsi, 0, hostSize * sizeof(BlockPsis));
	memset(h_pot, 0, hostSize * sizeof(BlockPots));

	// initialize discrete field
	const Complex oddPhase = state.getPhase(-0.5 * time_step_size);
	Random rnd(54363);
	for (k = 0; k < zsize; k++)
	{
		for (j = 0; j < ysize; j++)
		{
			for (i = 0; i < xsize; i++)
			{
				for (l = 0; l < bsize; l++)
				{
					const uint srcI = ii0 + k * bxysize + j * bxsize + i * bsize + l;
					const uint dstI = (k + 1) * dxsize * dysize + (j + 1) * dxsize + (i + 1);
					const Vector2 c = 0.01 * rnd.getUniformCircle();
					const Complex noise(c.x + 1.0, c.y);
					const Complex noisedPsi = Psi0[srcI] * noise;
					double2 even = make_double2(noisedPsi.r, noisedPsi.i);
					h_evenPsi[dstI].values[l] = even;
					h_oddPsi[dstI].values[l] = make_double2(oddPhase.r * even.x - oddPhase.i * even.y,
						oddPhase.i * even.x + oddPhase.r * even.y);
					h_pot[dstI].values[l] = pot[srcI];
				}
			}
		}
	}

	// Initialize device memory
	std::vector<cudaPitchedPtr> d_cudaEvenPsis(gpuCount);
	std::vector<cudaPitchedPtr> d_cudaOddPsis(gpuCount);
	std::vector<cudaPitchedPtr> d_cudaPots(gpuCount);
	std::vector<PitchedPtr> d_evenPsis(gpuCount);
	std::vector<PitchedPtr> d_oddPsis(gpuCount);
	std::vector<PitchedPtr> d_pots(gpuCount);
	std::vector<int3*> d_blockDirs(gpuCount);
	std::vector<int*> d_valueInds(gpuCount);
	std::vector<ddouble*> d_hodges(gpuCount);
	std::vector<cudaPitchedPtr> h_cudaEvenPsis(gpuCount);
	std::vector<cudaPitchedPtr> h_cudaOddPsis(gpuCount);
	std::vector<cudaPitchedPtr> h_cudaPots(gpuCount);
	std::vector<cudaExtent> psiExtents(gpuCount);

	std::vector<size_t> dzSizes(gpuCount);
	for (uint gpuIdx = 0; gpuIdx < gpuCount; ++gpuIdx)
	{
		dzSizes[gpuIdx] = zSizes[gpuIdx] + 2;

		psiExtents[gpuIdx] = make_cudaExtent(dxsize * sizeof(BlockPsis), dysize, dzSizes[gpuIdx]);
		cudaExtent potExtent = make_cudaExtent(dxsize * sizeof(BlockPots), dysize, dzSizes[gpuIdx]);

		cudaSetDevice(gpuIdx);

		if (enablePeerAccess)
		{
			for (uint peerGpu = 0; peerGpu < gpuCount; ++peerGpu)
			{
				if (peerGpu != gpuIdx)
				{
					int canAccessPeer;
					cudaDeviceCanAccessPeer(&canAccessPeer, gpuIdx, peerGpu);
					if ((canAccessPeer == 1) && cudaDeviceEnablePeerAccess(peerGpu, 0) == cudaSuccess)
					{
						//std::cout << "GPU " << gpuIdx << " can access GPU " << peerGpu << std::endl;
					}
					else
					{
						//std::cout << "GPU " << gpuIdx << " can NOT access GPU " << peerGpu << std::endl;
					}
				}
			}
		}

		checkCudaErrors(cudaMalloc3D(&d_cudaEvenPsis[gpuIdx], psiExtents[gpuIdx]));
		checkCudaErrors(cudaMalloc3D(&d_cudaOddPsis[gpuIdx], psiExtents[gpuIdx]));
		checkCudaErrors(cudaMalloc3D(&d_cudaPots[gpuIdx], potExtent));

		// Offsets are for the zero valued padding on the edges, offset = z + y + x in bytes
		size_t offset = d_cudaEvenPsis[gpuIdx].pitch * dysize + d_cudaEvenPsis[gpuIdx].pitch + sizeof(BlockPsis);
		size_t potOffset = d_cudaPots[gpuIdx].pitch * dysize + d_cudaPots[gpuIdx].pitch + sizeof(BlockPots);
		PitchedPtr d_evenPsi = { (char*)d_cudaEvenPsis[gpuIdx].ptr + offset, d_cudaEvenPsis[gpuIdx].pitch, d_cudaEvenPsis[gpuIdx].pitch * dysize };
		PitchedPtr d_oddPsi = { (char*)d_cudaOddPsis[gpuIdx].ptr + offset, d_cudaOddPsis[gpuIdx].pitch, d_cudaOddPsis[gpuIdx].pitch * dysize };
		PitchedPtr d_pot = { (char*)d_cudaPots[gpuIdx].ptr + potOffset, d_cudaPots[gpuIdx].pitch, d_cudaPots[gpuIdx].pitch * dysize };
		d_evenPsis[gpuIdx] = d_evenPsi;
		d_oddPsis[gpuIdx] = d_oddPsi;
		d_pots[gpuIdx] = d_pot;

		checkCudaErrors(cudaMalloc(&d_blockDirs[gpuIdx], blockDirs.size() * sizeof(int3)));
		checkCudaErrors(cudaMalloc(&d_valueInds[gpuIdx], valueInds.size() * sizeof(int)));
		checkCudaErrors(cudaMalloc(&d_hodges[gpuIdx], hodges.size() * sizeof(ddouble)));

		bool first = (gpuIdx == 0);

		h_cudaEvenPsis[gpuIdx].ptr = first ? h_evenPsi : ((BlockPsis*)h_cudaEvenPsis[gpuIdx - 1].ptr) + dxsize * dysize * (dzSizes[gpuIdx - 1] - 2);
		h_cudaEvenPsis[gpuIdx].pitch = dxsize * sizeof(BlockPsis);
		h_cudaEvenPsis[gpuIdx].xsize = d_cudaEvenPsis[gpuIdx].xsize;
		h_cudaEvenPsis[gpuIdx].ysize = d_cudaEvenPsis[gpuIdx].ysize;

		h_cudaOddPsis[gpuIdx].ptr = first ? h_oddPsi : ((BlockPsis*)h_cudaOddPsis[gpuIdx - 1].ptr) + dxsize * dysize * (dzSizes[gpuIdx - 1] - 2);
		h_cudaOddPsis[gpuIdx].pitch = dxsize * sizeof(BlockPsis);
		h_cudaOddPsis[gpuIdx].xsize = d_cudaOddPsis[gpuIdx].xsize;
		h_cudaOddPsis[gpuIdx].ysize = d_cudaOddPsis[gpuIdx].ysize;

		h_cudaPots[gpuIdx].ptr = first ? h_pot : ((BlockPots*)h_cudaPots[gpuIdx - 1].ptr) + dxsize * dysize * (dzSizes[gpuIdx - 1] - 2);
		h_cudaPots[gpuIdx].pitch = dxsize * sizeof(BlockPots);
		h_cudaPots[gpuIdx].xsize = d_cudaPots[gpuIdx].xsize;
		h_cudaPots[gpuIdx].ysize = d_cudaPots[gpuIdx].ysize;

		// Copy from host memory to device memory
		cudaMemcpy3DParms evenPsiParams = { 0 };
		cudaMemcpy3DParms oddPsiParams = { 0 };
		cudaMemcpy3DParms potParams = { 0 };

		evenPsiParams.srcPtr = h_cudaEvenPsis[gpuIdx];
		evenPsiParams.dstPtr = d_cudaEvenPsis[gpuIdx];
		evenPsiParams.extent = psiExtents[gpuIdx];
		evenPsiParams.kind = cudaMemcpyHostToDevice;

		oddPsiParams.srcPtr = h_cudaOddPsis[gpuIdx];
		oddPsiParams.dstPtr = d_cudaOddPsis[gpuIdx];
		oddPsiParams.extent = psiExtents[gpuIdx];
		oddPsiParams.kind = cudaMemcpyHostToDevice;

		potParams.srcPtr = h_cudaPots[gpuIdx];
		potParams.dstPtr = d_cudaPots[gpuIdx];
		potParams.extent = potExtent;
		potParams.kind = cudaMemcpyHostToDevice;

		checkCudaErrors(cudaMemcpy3DAsync(&evenPsiParams));
		checkCudaErrors(cudaMemcpy3DAsync(&oddPsiParams));
		checkCudaErrors(cudaMemcpy3DAsync(&potParams));
		checkCudaErrors(cudaMemcpy(d_blockDirs[gpuIdx], &blockDirs[0], blockDirs.size() * sizeof(int3), cudaMemcpyHostToDevice));
		checkCudaErrors(cudaMemcpy(d_valueInds[gpuIdx], &valueInds[0], valueInds.size() * sizeof(int), cudaMemcpyHostToDevice));
		checkCudaErrors(cudaMemcpy(d_hodges[gpuIdx], &hodges[0], hodges.size() * sizeof(ddouble), cudaMemcpyHostToDevice));

		cudaDeviceSynchronize();
	}

	// Clear host memory after data has been copied to devices
	Psi0.clear();
	pot.clear();
	bpos.clear();
	blockDirs.clear();
	valueInds.clear();
	hodges.clear();
	cudaFreeHost(h_oddPsi);
	cudaFreeHost(h_pot);
#if !(SAVE_PICTURE || SAVE_VOLUME)
	cudaFreeHost(h_evenPsi);
#endif

	// Integrate in time
	dim3 dimBlock(THREAD_BLOCK_X * VALUES_IN_BLOCK, THREAD_BLOCK_Y, THREAD_BLOCK_Z);
	std::vector<dim3> dimGrids(gpuCount);
	std::vector<uint3> dimensions(gpuCount);
	for (uint gpuIdx = 0; gpuIdx < gpuCount; ++gpuIdx)
	{
		dimensions[gpuIdx] = make_uint3(xsize, ysize, zSizes[gpuIdx]);
		dimGrids[gpuIdx] = dim3((xsize + THREAD_BLOCK_X - 1) / THREAD_BLOCK_X,
			(ysize + THREAD_BLOCK_Y - 1) / THREAD_BLOCK_Y,
			(zSizes[gpuIdx] + THREAD_BLOCK_Z - 1) / THREAD_BLOCK_Z);
	}

	std::vector<cudaMemcpy3DParms> evenMemcpiesFrom(gpuCount - 1, { 0 });
	std::vector<cudaMemcpy3DParms> evenMemcpiesTo(gpuCount - 1, { 0 });
	std::vector<cudaMemcpy3DParms> oddMemcpiesFrom(gpuCount - 1, { 0 });
	std::vector<cudaMemcpy3DParms> oddMemcpiesTo(gpuCount - 1, { 0 });
	
	cudaExtent oneSliceExtent = make_cudaExtent(dxsize * sizeof(BlockPsis), dysize, 1);
	for (uint gpuIdx = 0; gpuIdx < gpuCount - 1; ++gpuIdx)
	{
		cudaPitchedPtr evenFromSrc = d_cudaEvenPsis[gpuIdx];
		cudaPitchedPtr evenFromDst = d_cudaEvenPsis[gpuIdx + 1];
		cudaPitchedPtr evenToSrc = d_cudaEvenPsis[gpuIdx + 1];
		cudaPitchedPtr evenToDst = d_cudaEvenPsis[gpuIdx];
	
		cudaPitchedPtr oddFromSrc = d_cudaOddPsis[gpuIdx];
		cudaPitchedPtr oddFromDst = d_cudaOddPsis[gpuIdx + 1];
		cudaPitchedPtr oddToSrc = d_cudaOddPsis[gpuIdx + 1];
		cudaPitchedPtr oddToDst = d_cudaOddPsis[gpuIdx];
	
		evenFromSrc.ptr = ((char*)evenFromSrc.ptr) + d_evenPsis[gpuIdx].slicePitch * (dzSizes[gpuIdx] - 2);
		evenToDst.ptr = ((char*)evenToDst.ptr) + d_evenPsis[gpuIdx].slicePitch * (dzSizes[gpuIdx] - 1);
		evenToSrc.ptr = ((char*)evenToSrc.ptr) + d_evenPsis[gpuIdx + 1].slicePitch * 1;
		evenFromDst.ptr = ((char*)evenFromDst.ptr) + d_evenPsis[gpuIdx + 1].slicePitch * 0;
	
		oddFromSrc.ptr = ((char*)oddFromSrc.ptr) + d_oddPsis[gpuIdx].slicePitch * (dzSizes[gpuIdx] - 2);
		oddToDst.ptr = ((char*)oddToDst.ptr) + d_oddPsis[gpuIdx].slicePitch * (dzSizes[gpuIdx] - 1);
		oddToSrc.ptr = ((char*)oddToSrc.ptr) + d_oddPsis[gpuIdx + 1].slicePitch * 1;
		oddFromDst.ptr = ((char*)oddFromDst.ptr) + d_oddPsis[gpuIdx + 1].slicePitch * 0;

		evenMemcpiesFrom[gpuIdx].srcPtr = evenFromSrc;
		evenMemcpiesFrom[gpuIdx].dstPtr = evenFromDst;
		evenMemcpiesFrom[gpuIdx].extent = oneSliceExtent;
		evenMemcpiesFrom[gpuIdx].kind = cudaMemcpyDefault;

		evenMemcpiesTo[gpuIdx].srcPtr = evenToSrc;
		evenMemcpiesTo[gpuIdx].dstPtr = evenToDst;
		evenMemcpiesTo[gpuIdx].extent = oneSliceExtent;
		evenMemcpiesTo[gpuIdx].kind = cudaMemcpyDefault;

		oddMemcpiesFrom[gpuIdx].srcPtr = oddFromSrc;
		oddMemcpiesFrom[gpuIdx].dstPtr = oddFromDst;
		oddMemcpiesFrom[gpuIdx].extent = oneSliceExtent;
		oddMemcpiesFrom[gpuIdx].kind = cudaMemcpyDefault;

		oddMemcpiesTo[gpuIdx].srcPtr = oddToSrc;
		oddMemcpiesTo[gpuIdx].dstPtr = oddToDst;
		oddMemcpiesTo[gpuIdx].extent = oneSliceExtent;
		oddMemcpiesTo[gpuIdx].kind = cudaMemcpyDefault;
	}

	struct StreamsAndEvents
	{
		cudaStream_t backwardsStream;
		cudaStream_t forwardsStream;
		cudaStream_t kernelStream;

		cudaEvent_t backwardsEvent;
		cudaEvent_t forwardsEvent;
		cudaEvent_t kernelEvent;
	};
	std::vector<StreamsAndEvents> streamAndEvents(gpuCount);
	for (uint gpuIdx = 0; gpuIdx < gpuCount; ++gpuIdx)
	{
		cudaSetDevice(gpuIdx);
		cudaStreamCreate(&streamAndEvents[gpuIdx].backwardsStream);
		cudaStreamCreate(&streamAndEvents[gpuIdx].forwardsStream);
		cudaStreamCreate(&streamAndEvents[gpuIdx].kernelStream);

		cudaEventCreate(&streamAndEvents[gpuIdx].backwardsEvent);
		cudaEventCreate(&streamAndEvents[gpuIdx].forwardsEvent);
		cudaEventCreate(&streamAndEvents[gpuIdx].kernelEvent);

		if (gpuIdx < gpuCount - 1)
		{
			cudaEventRecord(streamAndEvents[gpuIdx].forwardsEvent, streamAndEvents[gpuIdx].forwardsStream);
		}
		if (0 < gpuIdx)
		{
			cudaEventRecord(streamAndEvents[gpuIdx].backwardsEvent, streamAndEvents[gpuIdx].backwardsStream);
		}
	}

#if SAVE_PICTURE || SAVE_VOLUME
	std::vector<cudaMemcpy3DParms> evenPsiBackParams(gpuCount, { 0 });
	for (uint gpuIdx = 0; gpuIdx < gpuCount; ++gpuIdx)
	{
		d_cudaEvenPsis[gpuIdx].ptr = ((char*)d_cudaEvenPsis[gpuIdx].ptr) + d_evenPsis[gpuIdx].slicePitch;
		h_cudaEvenPsis[gpuIdx].ptr = ((BlockPsis*)h_cudaEvenPsis[gpuIdx].ptr) + dxsize * dysize;
		psiExtents[gpuIdx].depth -= 2;

		evenPsiBackParams[gpuIdx].srcPtr = d_cudaEvenPsis[gpuIdx];
		evenPsiBackParams[gpuIdx].dstPtr = h_cudaEvenPsis[gpuIdx];
		evenPsiBackParams[gpuIdx].extent = psiExtents[gpuIdx];
		evenPsiBackParams[gpuIdx].kind = cudaMemcpyDeviceToHost;
	}
#endif
	double2 lapfacs = make_double2(lapfac, lapfac0);

	uint iter = 0;
	auto startTime = std::chrono::system_clock::now();
	while (true)
	{
#if SAVE_PICTURE || SAVE_VOLUME
		//cudaDeviceSynchronize();
#endif

#if SAVE_PICTURE
		// draw picture
		Picture pic(dxsize, dysize);
		k = zsize / 2 + 1;
		for (j = 0; j < dysize; j++)
		{
			for (i = 0; i < dxsize; i++)
			{
				const uint idx = k * dxsize * dysize + j * dxsize + i;
				double norm = sqrt(h_evenPsi[idx].values[0].x * h_evenPsi[idx].values[0].x + h_evenPsi[idx].values[0].y * h_evenPsi[idx].values[0].y);

				pic.setColor(i, j, 5.0 * Vector4(h_evenPsi[idx].values[0].x, norm, h_evenPsi[idx].values[0].y, 1.0));
			}
		}
		std::ostringstream picpath;
		picpath << "tulokset/kuva" << iter << ".bmp";
		pic.save(picpath.str(), false);
#endif

#if SAVE_VOLUME
		// save volume map
		const ddouble fmax = state.searchFunctionMax();
		const ddouble unit = 60000.0 / (bsize * fmax * fmax);
		Buffer<ushort> vol(dxsize * dysize * (zsize + 2));
		for (k = 0; k < (zsize + 2); k++)
		{
			for (j = 0; j < dysize; j++)
			{
				for (i = 0; i < dxsize; i++)
				{
					const uint idx = k * dxsize * dysize + j * dxsize + i;
					ddouble sum = 0.0;
					for (l = 0; l < bsize; l++)
					{
						sum += h_evenPsi[idx].values[0].x * h_evenPsi[idx].values[0].x + h_evenPsi[idx].values[0].y * h_evenPsi[idx].values[0].y;
					}
					sum *= unit;
					vol[idx] = (sum > 65535.0 ? 65535 : ushort(sum));
				}
			}
		}
		Text volpath;
		volpath << "volume" << iter << ".mhd";
		saveVolumeMap(volpath.str(), vol, dxsize, dysize, (zsize + 2), block_scale * BLOCK_WIDTH);
#endif

		// finish iteration
		if (++iter > number_of_iterations) break;

		// integrate one iteration
		//std::cout << "Iteration " << iter << std::endl;
		for (uint step = 0; step < steps_per_iteration; step++)
		{
			// update odd values
			for (uint gpuIdx = 0; gpuIdx < gpuCount; ++gpuIdx)
			{
				cudaSetDevice(gpuIdx);
				if (gpuIdx < gpuCount - 1)
					cudaStreamWaitEvent(streamAndEvents[gpuIdx].kernelStream, streamAndEvents[gpuIdx + 1].backwardsEvent, 0);
				if (gpuIdx > 0)
					cudaStreamWaitEvent(streamAndEvents[gpuIdx].kernelStream, streamAndEvents[gpuIdx - 1].forwardsEvent, 0);

				// Launch the CUDA kernel, even -> odd
				update << <dimGrids[gpuIdx], dimBlock, 0, streamAndEvents[gpuIdx].kernelStream >> > (d_oddPsis[gpuIdx], d_evenPsis[gpuIdx], d_pots[gpuIdx], d_blockDirs[gpuIdx], d_valueInds[gpuIdx], d_hodges[gpuIdx], g, dimensions[gpuIdx]);

				cudaEventRecord(streamAndEvents[gpuIdx].kernelEvent, streamAndEvents[gpuIdx].kernelStream);
			}

			for (uint gpuIdx = 0; gpuIdx < gpuCount; ++gpuIdx)
			{
				cudaSetDevice(gpuIdx);
				if (gpuIdx < gpuCount - 1)
				{
					cudaStreamWaitEvent(streamAndEvents[gpuIdx].forwardsStream, streamAndEvents[gpuIdx].kernelEvent, 0);
					cudaMemcpy3DAsync(&oddMemcpiesFrom[gpuIdx], streamAndEvents[gpuIdx].forwardsStream);
					cudaEventRecord(streamAndEvents[gpuIdx].forwardsEvent, streamAndEvents[gpuIdx].forwardsStream);
				}
				if (gpuIdx > 0)
				{
					cudaStreamWaitEvent(streamAndEvents[gpuIdx].backwardsStream, streamAndEvents[gpuIdx].kernelEvent, 0);
					cudaMemcpy3DAsync(&oddMemcpiesTo[gpuIdx - 1], streamAndEvents[gpuIdx].backwardsStream);
					cudaEventRecord(streamAndEvents[gpuIdx].backwardsEvent, streamAndEvents[gpuIdx].backwardsStream);
				}
			}

			// update even values
			for (uint gpuIdx = 0; gpuIdx < gpuCount; ++gpuIdx)
			{
				cudaSetDevice(gpuIdx);
				if (gpuIdx < gpuCount - 1)
					cudaStreamWaitEvent(streamAndEvents[gpuIdx].kernelStream, streamAndEvents[gpuIdx + 1].backwardsEvent, 0);
				if (gpuIdx > 0)
					cudaStreamWaitEvent(streamAndEvents[gpuIdx].kernelStream, streamAndEvents[gpuIdx - 1].forwardsEvent, 0);

				// Launch the CUDA kernel, odd -> even
				update << <dimGrids[gpuIdx], dimBlock, 0, streamAndEvents[gpuIdx].kernelStream >> > (d_evenPsis[gpuIdx], d_oddPsis[gpuIdx], d_pots[gpuIdx], d_blockDirs[gpuIdx], d_valueInds[gpuIdx], d_hodges[gpuIdx], g, dimensions[gpuIdx]);

				cudaEventRecord(streamAndEvents[gpuIdx].kernelEvent, streamAndEvents[gpuIdx].kernelStream);
			}

			for (uint gpuIdx = 0; gpuIdx < gpuCount; ++gpuIdx)
			{
				cudaSetDevice(gpuIdx);
				if (gpuIdx < gpuCount - 1)
				{
					cudaStreamWaitEvent(streamAndEvents[gpuIdx].forwardsStream, streamAndEvents[gpuIdx].kernelEvent, 0);
					cudaMemcpy3DAsync(&evenMemcpiesFrom[gpuIdx], streamAndEvents[gpuIdx].forwardsStream);
					cudaEventRecord(streamAndEvents[gpuIdx].forwardsEvent, streamAndEvents[gpuIdx].forwardsStream);
				}
				if (gpuIdx > 0)
				{
					cudaStreamWaitEvent(streamAndEvents[gpuIdx].backwardsStream, streamAndEvents[gpuIdx].kernelEvent, 0);
					cudaMemcpy3DAsync(&evenMemcpiesTo[gpuIdx - 1], streamAndEvents[gpuIdx].backwardsStream);
					cudaEventRecord(streamAndEvents[gpuIdx].backwardsEvent, streamAndEvents[gpuIdx].backwardsStream);
				}
			}
		}
#if SAVE_PICTURE || SAVE_VOLUME
		// Copy back from device memory to host memory
		for (uint gpuIdx = 0; gpuIdx < gpuCount; ++gpuIdx)
		{
			cudaSetDevice(gpuIdx);
			checkCudaErrors(cudaMemcpy3DAsync(&evenPsiBackParams[gpuIdx]));
		}
#endif
	}
	for (uint gpuIdx = 0; gpuIdx < gpuCount; ++gpuIdx)
	{
		cudaSetDevice(gpuIdx);
		cudaDeviceSynchronize();
	}
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - startTime).count() * 1e-6;
	std::cout << "Duration for of the integration of one time unit: " << duration / number_of_iterations << std::endl;
	std::cout << "Total duration: " << duration << std::endl;

	cudaError_t err = cudaGetLastError();
	if (err != cudaSuccess)
	{
		fprintf(stderr, "Failed to launch kernels (error code %s)!\n", cudaGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	for (uint gpuIdx = 0; gpuIdx < gpuCount; ++gpuIdx)
	{
		checkCudaErrors(cudaFree(d_cudaEvenPsis[gpuIdx].ptr));
		checkCudaErrors(cudaFree(d_cudaOddPsis[gpuIdx].ptr));
		checkCudaErrors(cudaFree(d_cudaPots[gpuIdx].ptr));
		checkCudaErrors(cudaFree(d_blockDirs[gpuIdx]));
		checkCudaErrors(cudaFree(d_valueInds[gpuIdx]));
		checkCudaErrors(cudaFree(d_hodges[gpuIdx]));
	}
	return duration;
}

int main(int argc, char** argv)
{
#if LOAD_STATE_FROM_DISK
	VortexState state;
	state.load("state.dat");
	const ddouble eps = 1e-5 * state.searchFunctionMax();
	const ddouble maxr = state.searchMaxR(eps);
	const ddouble maxz = state.searchMaxZ(eps);
#else
	// preliminary vortex state to find vortex size
	VortexState state0;
	state0.setKappa(KAPPA);
	state0.setG(G);
	if (IS_3D) state0.setRange(0.0, 15.0, 35.0, 0.2, 0.2); // use this for 3d
	else state0.setRange(0.0, 15.0, 1.0, 0.2, 1.0); // use this for 2d
	state0.iterateSolution(potentialRZ, 10000, 1e-29);
	const ddouble eps = 1e-5 * state0.searchFunctionMax();
	const ddouble minr = state0.searchMinR(eps);
	ddouble maxr = state0.searchMaxR(eps);
	ddouble maxz = state0.searchMaxZ(eps);
	//std::cout << "maxf=" << 1e6*eps << " minr=" << minr << " maxr=" << maxr << " maxz=" << maxz << std::endl;

	// more accurate vortex state
	VortexState state;
	state.setKappa(KAPPA);
	state.setG(G);
	if (IS_3D) state.setRange(minr, maxr, maxz, 0.03, 0.03); // use this for 3d
	else state.setRange(minr, maxr, 1.0, 0.03, 1.0); // use this for 2d
	state.initialize(state0);
	state.iterateSolution(potentialRZ, 10000, 1e-29);
	state.save("state.dat");
	maxr = state.searchMaxR(eps);
	maxz = state.searchMaxZ(eps);
	//std::cout << "maxf=" << state.searchFunctionMax() << std::endl;
#endif
	uint gpuCount = (argc > 1) ? std::stoi(argv[1]) : 4;

	const int number_of_iterations = 1;
	const ddouble iteration_period = 1.0;
	ddouble blockScale = (argc > 2) ? std::stod(argv[2]) : 0.0391; // PIx2 / (20.0 * sqrt(state.integrateCurvature()));

	std::cout << gpuCount << " GPUs" << std::endl;
	std::cout << "kappa = " << KAPPA << ", " << state.getKappa() << std::endl;
	std::cout << "g = " << G << ", " << state.getG() << std::endl;
	std::cout << "iteration_period = " << iteration_period << std::endl;
	std::cout << "maxr = " << maxr << std::endl;
	std::cout << "maxz = " << maxz << std::endl;

	const ddouble EPSILON = 0.02;
	const ddouble TARGET = 7.1725;
	bool firstIter = true;
	while (true)
	{
		std::cout << "Block scale: " << blockScale << std::endl;

		auto time = integrateInTime(state, blockScale, Vector3(-maxr, -maxr, -maxz), Vector3(maxr, maxr, maxz), iteration_period, number_of_iterations, gpuCount, firstIter);

		auto timeDelta = time - TARGET;
		if (abs(timeDelta) < EPSILON)
		{
			break;
		}
		blockScale += std::pow(0.4 * timeDelta, 3);

		if (blockScale < 0)
		{
			std::cout << "SCALE BECAME NEGATIVE!" << std::endl;
			return 0;
		}
		std::cout << std::endl;
		firstIter = false;
	}

	return 0;
}
