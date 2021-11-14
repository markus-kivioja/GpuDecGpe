#define FACE_COUNT 6
#define DUAL_EDGE_LENGTH 1
#define VALUES_IN_BLOCK 1
#define INDICES_PER_BLOCK 6
const Vector3 BLOCK_WIDTH = Vector3(1, 1, 1); // dimensions of unit block
const ddouble VOLUME = 1; // volume of body elements
const bool IS_3D = true; // 3-dimensional
void getPositions(Buffer<Vector3> &pos)
{
	pos.resize(VALUES_IN_BLOCK);
	pos[0] = Vector3(0.5, 0.5, 0.5);
}
ddouble getLaplacian(Buffer<int3> &blockDirs, Buffer<int> &valueInds, Buffer<ddouble> &hodges)
{
	blockDirs.resize(INDICES_PER_BLOCK);
	// Dual node idx:  0
	blockDirs[0] = make_int3(0, 0, -1);
	blockDirs[1] = make_int3(-1, 0, 0);
	blockDirs[2] = make_int3(0, -1, 0);
	blockDirs[3] = make_int3(1, 0, 0);
	blockDirs[4] = make_int3(0, 1, 0);
	blockDirs[5] = make_int3(0, 0, 1);

	valueInds.resize(INDICES_PER_BLOCK);
	// Dual node idx:  0
	valueInds[0] = 0;
	valueInds[1] = 0;
	valueInds[2] = 0;
	valueInds[3] = 0;
	valueInds[4] = 0;
	valueInds[5] = 0;

	hodges.resize(INDICES_PER_BLOCK);
	hodges[0] = 1;
	hodges[1] = 1;
	hodges[2] = 1;
	hodges[3] = 1;
	hodges[4] = 1;
	hodges[5] = 1;

	return 1;
}
