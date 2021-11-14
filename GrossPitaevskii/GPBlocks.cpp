#include "VortexState.hpp"
#include "../Output/Picture.hpp"
#include "../Output/Text.hpp"
#include "../Types/Complex.hpp"
#include "../Types/Random.hpp"
#include "../Mesh/DelaunayMesh.hpp"
#include <iostream>
#include <sstream>

ddouble RATIO = 1.0;
ddouble RATIOSQ = 1.0;

enum GridType
{
	CUBIC = 0,
	FCC,
	BCC,
	A15,
	C15,
	Z,
	COUNT
};

constexpr double scales[] = { 1.00, 2.51, 2.27, 3.91, 5.39, 3.70 };
// integration times = 1.9923, 1.9928, 1.9826, 1.9852, 1.9265, 1.9898

ddouble potentialRZ(const ddouble r, const ddouble z)
{
	return 0.5 * (r * r + RATIO * RATIO * z * z);
}

ddouble potentialV3(const Vector3 &p)
{
	return 0.5 * (p.x * p.x + p.y * p.y + RATIO * RATIO * p.z * p.z);
}

void generateCode() // generates code section for different grid structures
{
	/*	// square grid
	mesh.createGrid(Vector4(-1,-1,0,0), Vector4(2,2,1,0), 1.0);
	const Vector3 dim(1,1,1); // maximum block coordinates
*//*
	// triangle grid
	const ddouble SQ3 = sqrt(3.0);
	mesh.createTriangleGrid(Vector2(-SQ3,-3), Vector2(2*SQ3,6), SQ3);
	mesh.stretchLinear(Vector4(0,0,1,0), 1, 0, 0, 0);
	const Vector3 dim(SQ3,3,1); // maximum block coordinates
*/
	for (GridType gridType = CUBIC; gridType < GridType::COUNT; gridType = (GridType)(gridType + 1))
	{
		uint i, j, k;
		DelaunayMesh mesh(3);

		const ddouble scale = scales[gridType];
		Vector3 dim;
		std::string filename;

		switch (gridType)
		{
		case CUBIC:
			mesh.createGrid(scale * Vector4(-1, -1, -1, 0), scale * Vector4(2, 2, 2, 0), scale);
			dim = Vector3(scale, scale, scale); // maximum block coordinates
			filename = "../../GrossPitaevskiiGpuCube/mesh.h";
			break;
		case FCC:
			mesh.createFccGrid(scale * Vector3(-1.125, -1.125, -1.125), scale * Vector3(1.875, 1.875, 1.875), scale);
			dim = Vector3(scale, scale, scale); // maximum block coordinates
			filename = "../../GrossPitaevskiiGpuFcc/mesh.h";
			break;
		case BCC:
			mesh.createBccGrid(scale * Vector3(-1.125, -1.125, -1.125), scale * Vector3(1.875, 1.875, 1.875), scale);
			dim = Vector3(scale, scale, scale); // maximum block coordinates
			filename = "../../GrossPitaevskiiGpuBcc/mesh.h";
			break;
		case A15:
			mesh.createA15Grid(scale * Vector3(-1.125, -1.125, -1.125), scale * Vector3(1.875, 1.875, 1.875), scale);
			dim = Vector3(scale, scale, scale); // maximum block coordinates
			filename = "../../GrossPitaevskiiGpuA15/mesh.h";
			break;
		case C15:
			mesh.createC15Grid(scale * Vector3(-1.125, -1.125, -1.125), scale * Vector3(1.875, 1.875, 1.875), scale);
			dim = Vector3(scale, scale, scale); // maximum block coordinates
			filename = "../../GrossPitaevskiiGpuC15/mesh.h";
			break;
		case Z:
			mesh.createZGrid(scale * Vector3(-1.125, -1.125, -1.125), scale * Vector3(1.875, 1.875 * sqrt(3.0), 1.875), scale);
			dim = Vector3(scale, scale * sqrt(3.0), scale); // maximum block coordinates
			filename = "../../GrossPitaevskiiGpuZ/mesh.h";
			break;
		default:
			break;
		}

		// find circumcenters inside the block
		Buffer<Vector3> p(mesh.getBodySize());
		Buffer<uint> ind;
		uint inds = 0;
		uint totalFaceCount = 0;
		for (i = 0; i < p.size(); i++)
		{
			p[i] = mesh.getBodyPosition(i).toVector3();

			if (p[i].x < 0.0 || p[i].y < 0.0 || p[i].z < 0.0) continue;
			if (p[i].x >= dim.x || p[i].y >= dim.y || p[i].z >= dim.z) continue;
			ind.gather(i, inds);
			totalFaceCount += mesh.getBodyFaces(i).size();
		}

		// compute terms for laplacian
		const ddouble bhodge = mesh.getBodyHodge(ind[0]);
		uint fsize = 0;
		ddouble factor = 0.0;
		ddouble dualEdgeLength = 0;
		const Buffer<uint>& f0 = mesh.getBodyFaces(ind[0]);
		for (i = 0; i < f0.size(); i++)
		{
			auto faceBodies = mesh.getFaceBodies(f0[i]);
			if (faceBodies.size() < 2) continue;
			if (fsize == 0)
			{
				factor = bhodge / mesh.getFaceHodge(f0[i]);
				dualEdgeLength = mesh.getFaceDualVector(f0[i]).len();
				std::cout << "dual edge length = " << dualEdgeLength << std::endl;
			}
			fsize++;
		}

		// print code
		Text text;
		Text hodgesText;
		Text indicesAndFaceCountsText;
		text.precision(17);
		hodgesText.precision(17);
		bool constantFaceCount = totalFaceCount == (f0.size() * inds);
		uint faceCount = totalFaceCount / inds;
		text << "#define FACE_COUNT " << faceCount << std::endl;
		text << "#define DUAL_EDGE_LENGTH " << dualEdgeLength << std::endl;
		text << "#define VALUES_IN_BLOCK " << inds << std::endl;
		text << "#define INDICES_PER_BLOCK " << totalFaceCount << std::endl;
		text << "const Vector3 BLOCK_WIDTH = Vector3(" << dim.x << ", " << dim.y << ", " << dim.z << "); // dimensions of unit block" << std::endl;
		text << "const ddouble VOLUME = " << 1.0 / bhodge << "; // volume of body elements" << std::endl;
		if (fsize == f0.size()) text << "const bool IS_3D = true; // 3-dimensional" << std::endl;
		else text << "const bool IS_3D = false; // 2-dimensional" << std::endl;
		text << "void getPositions(Buffer<Vector3> &pos)" << std::endl;
		text << "{" << std::endl;
		text << "\tpos.resize(VALUES_IN_BLOCK);" << std::endl;
		for (i = 0; i < inds; i++) text << "\tpos[" << i << "] = Vector3(" << p[ind[i]].x << ", " << p[ind[i]].y << ", " << p[ind[i]].z << ");" << std::endl;
		text << "}" << std::endl;
		if (constantFaceCount)
			text << "ddouble getLaplacian(Buffer<int3> &blockDirs, Buffer<int> &valueInds, Buffer<ddouble> &hodges)" << std::endl;
		else
			text << "ddouble getLaplacian(Buffer<int3> &blockDirs, Buffer<int> &valueInds, Buffer<ddouble> &hodges, Buffer<int2> &indicesAndFaceCounts)" << std::endl;
		text << "{" << std::endl;
		text << "\tblockDirs.resize(INDICES_PER_BLOCK);" << std::endl;
		fsize = 0;
		std::vector<uint32_t> valueInds;
		for (i = 0; i < inds; i++)
		{
			ddouble bodyHodge = mesh.getBodyHodge(ind[i]);
			const Buffer<uint>& f = mesh.getBodyFaces(ind[i]);
			indicesAndFaceCountsText << "\tindicesAndFaceCounts[" << i << "] = make_int2(" << fsize << ", " << f.size() << ");" << std::endl;
			for (j = 0; j < f.size(); j++)
			{
				const Buffer<uint>& b = mesh.getFaceBodies(f[j]);
				if (b.size() < 2) continue;
				const uint other = (b[0] == ind[i] ? b[1] : b[0]);
				Vector3 pp = p[other];
				Text link;
				int x = 0, y = 0, z = 0;
				if (pp.x < 0.0)
				{
					pp.x += dim.x; link << "-nx";
					x = -1;
				}
				else if (pp.x >= dim.x)
				{
					pp.x -= dim.x; link << "nx";
					x = 1;
				}
				if (pp.y < 0.0)
				{
					pp.y += dim.y; link << (link.str().empty() ? "-ny" : " - ny");
					y = -1;
				}
				else if (pp.y >= dim.y)
				{
					pp.y -= dim.y; link << (link.str().empty() ? "ny" : " + ny");
					y = 1;
				}
				if (pp.z < 0.0)
				{
					pp.z += dim.z; link << (link.str().empty() ? "-nz" : " - nz");
					z = -1;
				}
				else if (pp.z >= dim.z)
				{
					pp.z -= dim.z; link << (link.str().empty() ? "nz" : " + nz");
					z = 1;
				}
				for (k = 0; k < inds; k++)
				{
					if ((p[ind[k]] - pp).lensq() < 1e-13) break;
				}
				if (k >= inds)
				{
					std::cout << "FAILED" << std::endl;
					return;
				}
				if (link.str().empty()) link << "0";
				if (j == 0)
					text << "\t// Dual node idx:  " << i << std::endl;
				text << "\tblockDirs[" << fsize << "] = make_int3(" << std::to_string(x) << ", " << std::to_string(y) << ", " << std::to_string(z) << ");" << std::endl;
				ddouble hodge = bodyHodge / mesh.getFaceHodge(f[j]);
				factor = max(factor, hodge);
				hodgesText << "\thodges[" << fsize++ << "] = " << hodge << ";" << std::endl;
				valueInds.push_back(k);
			}
		}
		text << std::endl << "\tvalueInds.resize(INDICES_PER_BLOCK);" << std::endl;
		for (size_t i = 0; i < valueInds.size(); ++i)
		{
			if (i % faceCount == 0)
				text << "\t// Dual node idx:  " << i / faceCount << std::endl;
			text << "\tvalueInds[" << i << "] = " << valueInds[i] << ";" << std::endl;
		}
		text << std::endl << "\thodges.resize(INDICES_PER_BLOCK);" << std::endl;
		text << hodgesText.str() << std::endl;
		if (!constantFaceCount)
		{
			text << std::endl << "\tindicesAndFaceCounts.resize(VALUES_IN_BLOCK);" << std::endl;
			text << indicesAndFaceCountsText.str() << std::endl;
		}
		text << "\treturn " << factor << ";" << std::endl;
		text << "}" << std::endl;

		std::cout << text.str() << std::endl;
		text.save(filename);
	}
}
/*
// square grid
const Vector3 BLOCK_WIDTH = Vector3(1, 1, 1); // dimensions of unit block
const ddouble VOLUME = 1; // volume of body elements
const bool IS_3D = false; // 2-dimensional
void getPositions(Buffer<Vector3> &pos)
{
	pos.resize(1);
	pos[0] = Vector3(0.5, 0.5, 0.5);
}
ddouble getLaplacian(Buffer<uint> &ind, const uint nx, const uint ny, const uint nz)
{
	ind.resize(4);
	ind[0] = 0 - nx;
	ind[1] = 0 - ny;
	ind[2] = 0 + nx;
	ind[3] = 0 + ny;
	return 1;
}
*/
/*
// triangle grid
const Vector3 BLOCK_WIDTH = Vector3(sqrt(3.0), 3, 1); // dimensions of unit block
const ddouble VOLUME = sqrt(27.0 / 16.0); // volume of body elements
const bool IS_3D = false; // 2-dimensional
void getPositions(Buffer<Vector3> &pos)
{
	pos.resize(4);
	pos[0] = Vector3(0, 1, 0.5);
	pos[1] = Vector3(sqrt(0.75), 0.5, 0.5);
	pos[2] = Vector3(0, 2, 0.5);
	pos[3] = Vector3(sqrt(0.75), 2.5, 0.5);
}
ddouble getLaplacian(Buffer<uint> &ind, const uint nx, const uint ny, const uint nz)
{
	ind.resize(12);
	ind[0] = 1 - nx;
	ind[1] = 1;
	ind[2] = 2;
	ind[3] = 0 + nx;
	ind[4] = 0;
	ind[5] = 3 - ny;
	ind[6] = 3 - nx;
	ind[7] = 3;
	ind[8] = 0;
	ind[9] = 2 + nx;
	ind[10] = 2;
	ind[11] = 1 + ny;
	return 4.0 / 3.0;
}
*/

// cubic grid
/*const Vector3 BLOCK_WIDTH = Vector3(1, 1, 1); // dimensions of unit block
const ddouble VOLUME = 1; // volume of body elements
const bool IS_3D = true; // 3-dimensional
void getPositions(Buffer<Vector3> &pos)
{
	pos.resize(1);
	pos[0] = Vector3(0.5, 0.5, 0.5);
}
ddouble getLaplacian(Buffer<uint> &ind, const uint nx, const uint ny, const uint nz)
{
	ind.resize(6);
	ind[0] = 0 - nz;
	ind[1] = 0 - nx;
	ind[2] = 0 - ny;
	ind[3] = 0 + nx;
	ind[4] = 0 + ny;
	ind[5] = 0 + nz;
	return 1;
}
*/

// bcc grid
const Vector3 BLOCK_WIDTH = sqrt(8.0) * Vector3(1, 1, 1); // dimensions of unit block
const ddouble VOLUME = sqrt(32.0 / 9.0); // volume of body elements
const bool IS_3D = true; // 3-dimensional
void getPositions(Buffer<Vector3> &pos)
{
	pos.resize(12);
	const ddouble SQ1_8 = 1.0 / sqrt(8.0);
	pos[0] = SQ1_8 * Vector3(1, 3, 7);
	pos[1] = SQ1_8 * Vector3(7, 1, 3);
	pos[2] = SQ1_8 * Vector3(7, 3, 1);
	pos[3] = SQ1_8 * Vector3(7, 3, 5);
	pos[4] = SQ1_8 * Vector3(7, 5, 3);
	pos[5] = SQ1_8 * Vector3(1, 7, 3);
	pos[6] = SQ1_8 * Vector3(3, 7, 1);
	pos[7] = SQ1_8 * Vector3(3, 7, 5);
	pos[8] = SQ1_8 * Vector3(5, 7, 3);
	pos[9] = SQ1_8 * Vector3(3, 1, 7);
	pos[10] = SQ1_8 * Vector3(3, 5, 7);
	pos[11] = SQ1_8 * Vector3(5, 3, 7);
}
ddouble getLaplacian(Buffer<uint> &ind, const uint nx, const uint ny, const uint nz)
{
	ind.resize(48);
	ind[0] = 9;
	ind[1] = 10;
	ind[2] = 2 - nx + nz;
	ind[3] = 3 - nx;
	ind[4] = 2;
	ind[5] = 3;
	ind[6] = 5 + nx - ny;
	ind[7] = 8 - ny;
	ind[8] = 1;
	ind[9] = 4;
	ind[10] = 0 + nx - nz;
	ind[11] = 11 - nz;
	ind[12] = 1;
	ind[13] = 4;
	ind[14] = 0 + nx;
	ind[15] = 11;
	ind[16] = 2;
	ind[17] = 3;
	ind[18] = 5 + nx;
	ind[19] = 8;
	ind[20] = 6;
	ind[21] = 7;
	ind[22] = 1 - nx + ny;
	ind[23] = 4 - nx;
	ind[24] = 5;
	ind[25] = 8;
	ind[26] = 9 + ny - nz;
	ind[27] = 10 - nz;
	ind[28] = 5;
	ind[29] = 8;
	ind[30] = 9 + ny;
	ind[31] = 10;
	ind[32] = 6;
	ind[33] = 7;
	ind[34] = 1 + ny;
	ind[35] = 4;
	ind[36] = 0;
	ind[37] = 11;
	ind[38] = 6 - ny + nz;
	ind[39] = 7 - ny;
	ind[40] = 0;
	ind[41] = 11;
	ind[42] = 6 + nz;
	ind[43] = 7;
	ind[44] = 9;
	ind[45] = 10;
	ind[46] = 2 + nz;
	ind[47] = 3;
	return 1.5;
}

uint integrateInTime(const VortexState &state, const ddouble block_scale, const Vector3 &minp, const Vector3 &maxp, const uint iteration_period, const uint number_of_iterations)
{
	uint i, j, k, l;

	// find dimensions
	const Vector3 dom = maxp - minp;
	const uint xsize = uint(dom.x / (block_scale * BLOCK_WIDTH.x)) + 1;
	const uint ysize = uint(dom.y / (block_scale * BLOCK_WIDTH.y)) + 1;
	const uint zsize = uint(dom.z / (block_scale * BLOCK_WIDTH.z)) + 1;
	const Vector3 p0 = 0.5 * (minp + maxp - block_scale * Vector3(BLOCK_WIDTH.x * xsize, BLOCK_WIDTH.y * ysize, BLOCK_WIDTH.z * zsize));

	// find relative circumcenters for each body element
	Buffer<Vector3> bpos;
	getPositions(bpos);

	// compute discrete dimensions
	const uint bsize = bpos.size(); // number of values inside a block
	const uint bxsize = (xsize + 1) * bsize; // number of values on x-row
	const uint bxysize = (ysize + 1) * bxsize; // number of values on xy-plane
	const uint ii0 = (IS_3D ? bxysize : 0) + bxsize + bsize; // reserved zeros in the beginning of value table
	const uint vsize = ii0 + (IS_3D ? zsize + 1 : zsize) * bxysize; // total number of values

	// initialize stationary state
	Buffer<Complex> Psi0(vsize, Complex(0,0)); // initial discrete wave function
	Buffer<ddouble> pot(vsize, 0.0); // discrete potential multiplied by time step size
	ddouble g = state.getG(); // effective interaction strength
	ddouble maxpot = 0.0; // maximal value of potential
	for(k=0; k<zsize; k++)
	{
		for(j=0; j<ysize; j++)
		{
			for(i=0; i<xsize; i++)
			{
				for(l=0; l<bsize; l++)
				{
					const uint ii = ii0 + k * bxysize + j * bxsize + i * bsize + l;
					const Vector3 p(p0.x + block_scale * (i * BLOCK_WIDTH.x + bpos[l].x), p0.y + block_scale * (j * BLOCK_WIDTH.y + bpos[l].y), p0.z + block_scale * (k * BLOCK_WIDTH.z + bpos[l].z)); // position
					Psi0[ii] = state.getPsi(p);
					pot[ii] = potentialV3(p);
					const ddouble poti = pot[ii] + g * Psi0[ii].normsq();
					if(poti > maxpot) maxpot = poti;
				}
			}
		}
	}

	// find terms for laplacian
	Buffer<uint> lapind;
	ddouble lapfac = -0.5 * getLaplacian(lapind, bsize, bxsize, bxysize) / (block_scale * block_scale);
	const uint lapsize = lapind.size() / bsize;
	ddouble lapfac0 = lapsize * (-lapfac);

	// compute time step size
	const uint steps_per_iteration = uint(iteration_period * (maxpot + lapfac0)) + 1; // number of time steps per iteration period
	const ddouble time_step_size = iteration_period / ddouble(steps_per_iteration); // time step in time units

	// multiply terms with time_step_size
	g *= time_step_size;
	lapfac *= time_step_size;
	lapfac0 *= time_step_size;
	for(i=0; i<vsize; i++) pot[i] *= time_step_size;

	// initialize discrete field
	Buffer<Complex> evenPsi(vsize); // wave function at even time steps
	Buffer<Complex> oddPsi(vsize); // wave function at odd time steps
	const Complex oddPhase = state.getPhase(-0.5 * time_step_size);
	Random rnd(54363);
	for(i=0; i<vsize; i++)
	{
		const Vector2 c = 0.0 * rnd.getUniformCircle();
		evenPsi[i] = Psi0[i] * Complex(1.0 + c.x, c.y);
		oddPsi[i] = oddPhase * evenPsi[i];
	}

	// integrate in time
	const ddouble volume = (IS_3D ? block_scale : 1.0) * block_scale * block_scale * VOLUME;
	uint iter = 0;
	while(true)
	{
		// print squared norm and error
		ddouble normsq = 0.0;
		Complex error(0.0, 0.0);
		for(i=ii0; i<vsize; i++)
		{
			normsq += evenPsi[i].normsq() * volume;
			error += (Psi0[i].con() * evenPsi[i]) * volume;
		}
		std::cout << "normsq=" << normsq << " error=" << normsq - error.norm() << std::endl;

		// draw picture
		Picture pic(xsize, ysize);
		k = zsize / 2;
		l = 0;
		for(j=0; j<ysize; j++)
		{
			for(i=0; i<xsize; i++)
			{
				const uint ii = ii0 + k * bxysize + j * bxsize + i * bsize + l;
				pic.setColor(i, j, 5.0 * Vector4(evenPsi[ii].r, evenPsi[ii].norm(), evenPsi[ii].i, 1.0));
			}
		}
		std::ostringstream picpath;
		picpath << "kuva" << iter << ".bmp";
		pic.save(picpath.str(), false);

		// finish iteration
		if(++iter > number_of_iterations) break;

		// integrate one iteration
		for(uint step=0; step<steps_per_iteration; step++)
		{
			// update odd values
			for(k=0; k<zsize; k++)
			{
				for(j=0; j<ysize; j++)
				{
					for(i=0; i<xsize; i++)
					{
						const uint ii = ii0 + k * bxysize + j * bxsize + i * bsize;
						uint lapi = 0;
						uint lapimax = 0;
						for(l=0; l<bsize; l++)
						{
							const uint jj = ii + l;
							lapimax += lapsize;
							Complex sum = evenPsi[ii + lapind[lapi++]];
							while(lapi < lapimax) sum += evenPsi[ii + lapind[lapi++]];
							sum = lapfac * sum + (lapfac0 + pot[jj] + g * evenPsi[jj].normsq()) * evenPsi[jj];
							oddPsi[jj] += Complex(sum.i, -sum.r);
						}
					}
				}
			}
			// update even values
			for(k=0; k<zsize; k++)
			{
				for(j=0; j<ysize; j++)
				{
					for(i=0; i<xsize; i++)
					{
						const uint ii = ii0 + k * bxysize + j * bxsize + i * bsize;
						uint lapi = 0;
						uint lapimax = 0;
						for(l=0; l<bsize; l++)
						{
							const uint jj = ii + l;
							lapimax += lapsize;
							Complex sum = oddPsi[ii + lapind[lapi++]];
							while(lapi < lapimax) sum += oddPsi[ii + lapind[lapi++]];
							sum = lapfac * sum + (lapfac0 + pot[jj] + g * oddPsi[jj].normsq()) * oddPsi[jj];
							evenPsi[jj] += Complex(sum.i, -sum.r);
						}
					}
				}
			}
		}
	}
	return 0;
}


int main ( int argc, char** argv )
{
	// for code generation
	generateCode();
	return 0;

	// preliminary vortex state to find vortex size
	VortexState state0;
	state0.setKappa(10);
	state0.setG(40);
	if(IS_3D) state0.setRange(0.0, 15.0, 10.0, 0.2, 0.2); // use this for 3d
	else state0.setRange(0.0, 15.0, 1.0, 0.2, 1.0); // use this for 2d
	state0.iterateSolution(potentialRZ, 10000, 1e-29);
	const ddouble eps = 1e-5 * state0.searchFunctionMax();
	const ddouble minr = state0.searchMinR(eps);
	const ddouble maxr = state0.searchMaxR(eps);
	const ddouble maxz = state0.searchMaxZ(eps);
	std::cout << "maxf=" << 1e6*eps << " minr=" << minr << " maxr=" << maxr << " maxz=" << maxz << std::endl;

	// more accurate vortex state
	VortexState state;
	state.setKappa(10);
	state.setG(40);
	if(IS_3D) state.setRange(minr, maxr, maxz, 0.03, 0.03); // use this for 3d
	else state.setRange(minr, maxr, 1.0, 0.03, 1.0); // use this for 2d
	state.initialize(state0);
	state.iterateSolution(potentialRZ, 10000, 1e-29);
	std::cout << "maxf=" << state.searchFunctionMax() << std::endl;

	// integrate in time using DEC
	if(IS_3D) integrateInTime(state, 0.1, Vector3(-maxr, -maxr, -maxz), Vector3(maxr, maxr, maxz), 1.0, 10); // use this for 3d
	else integrateInTime(state, 0.1, Vector3(-maxr, -maxr, 0.0), Vector3(maxr, maxr, 0.0), 1.0, 10); // use this for 2d

	return 0;
}
