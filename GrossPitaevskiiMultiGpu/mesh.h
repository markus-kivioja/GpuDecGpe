#define FACE_COUNT 4
#define DUAL_EDGE_LENGTH 0.80256619664673123
#define VALUES_IN_BLOCK 12
#define INDICES_PER_BLOCK 48
const Vector3 BLOCK_WIDTH = Vector3(2.27, 2.27, 2.27); // dimensions of unit block
const ddouble VOLUME = 0.97475691666666664; // volume of body elements
const bool IS_3D = true; // 3-dimensional
void getPositions(Buffer<Vector3> &pos)
{
	pos.resize(VALUES_IN_BLOCK);
	pos[0] = Vector3(0.28374999999999967, 0.85124999999999962, 1.9862500000000001);
	pos[1] = Vector3(1.9862500000000001, 0.28374999999999967, 0.85124999999999962);
	pos[2] = Vector3(1.9862500000000001, 0.85124999999999962, 0.28374999999999967);
	pos[3] = Vector3(1.9862500000000001, 0.85124999999999962, 1.4187499999999997);
	pos[4] = Vector3(1.9862500000000001, 1.4187499999999997, 0.85124999999999962);
	pos[5] = Vector3(0.28374999999999967, 1.9862500000000001, 0.85124999999999962);
	pos[6] = Vector3(0.85124999999999962, 1.9862500000000001, 0.28374999999999967);
	pos[7] = Vector3(0.85124999999999962, 1.9862500000000001, 1.4187499999999997);
	pos[8] = Vector3(1.4187499999999997, 1.9862500000000001, 0.85124999999999962);
	pos[9] = Vector3(0.85124999999999962, 0.28374999999999967, 1.9862500000000001);
	pos[10] = Vector3(0.85124999999999962, 1.4187499999999997, 1.9862500000000001);
	pos[11] = Vector3(1.4187499999999997, 0.85124999999999962, 1.9862500000000001);
}
ddouble getLaplacian(Buffer<int3> &blockDirs, Buffer<int> &valueInds, Buffer<ddouble> &hodges)
{
	blockDirs.resize(INDICES_PER_BLOCK);
	// Dual node idx:  0
	blockDirs[0] = make_int3(0, 0, 0);
	blockDirs[1] = make_int3(0, 0, 0);
	blockDirs[2] = make_int3(-1, 0, 1);
	blockDirs[3] = make_int3(-1, 0, 0);
	// Dual node idx:  1
	blockDirs[4] = make_int3(0, 0, 0);
	blockDirs[5] = make_int3(0, 0, 0);
	blockDirs[6] = make_int3(1, -1, 0);
	blockDirs[7] = make_int3(0, -1, 0);
	// Dual node idx:  2
	blockDirs[8] = make_int3(0, 0, 0);
	blockDirs[9] = make_int3(0, 0, 0);
	blockDirs[10] = make_int3(1, 0, -1);
	blockDirs[11] = make_int3(0, 0, -1);
	// Dual node idx:  3
	blockDirs[12] = make_int3(0, 0, 0);
	blockDirs[13] = make_int3(0, 0, 0);
	blockDirs[14] = make_int3(1, 0, 0);
	blockDirs[15] = make_int3(0, 0, 0);
	// Dual node idx:  4
	blockDirs[16] = make_int3(0, 0, 0);
	blockDirs[17] = make_int3(0, 0, 0);
	blockDirs[18] = make_int3(1, 0, 0);
	blockDirs[19] = make_int3(0, 0, 0);
	// Dual node idx:  5
	blockDirs[20] = make_int3(0, 0, 0);
	blockDirs[21] = make_int3(0, 0, 0);
	blockDirs[22] = make_int3(-1, 1, 0);
	blockDirs[23] = make_int3(-1, 0, 0);
	// Dual node idx:  6
	blockDirs[24] = make_int3(0, 0, 0);
	blockDirs[25] = make_int3(0, 0, 0);
	blockDirs[26] = make_int3(0, 1, -1);
	blockDirs[27] = make_int3(0, 0, -1);
	// Dual node idx:  7
	blockDirs[28] = make_int3(0, 0, 0);
	blockDirs[29] = make_int3(0, 0, 0);
	blockDirs[30] = make_int3(0, 1, 0);
	blockDirs[31] = make_int3(0, 0, 0);
	// Dual node idx:  8
	blockDirs[32] = make_int3(0, 0, 0);
	blockDirs[33] = make_int3(0, 0, 0);
	blockDirs[34] = make_int3(0, 1, 0);
	blockDirs[35] = make_int3(0, 0, 0);
	// Dual node idx:  9
	blockDirs[36] = make_int3(0, 0, 0);
	blockDirs[37] = make_int3(0, 0, 0);
	blockDirs[38] = make_int3(0, -1, 1);
	blockDirs[39] = make_int3(0, -1, 0);
	// Dual node idx:  10
	blockDirs[40] = make_int3(0, 0, 0);
	blockDirs[41] = make_int3(0, 0, 0);
	blockDirs[42] = make_int3(0, 0, 1);
	blockDirs[43] = make_int3(0, 0, 0);
	// Dual node idx:  11
	blockDirs[44] = make_int3(0, 0, 0);
	blockDirs[45] = make_int3(0, 0, 0);
	blockDirs[46] = make_int3(0, 0, 1);
	blockDirs[47] = make_int3(0, 0, 0);

	valueInds.resize(INDICES_PER_BLOCK);
	// Dual node idx:  0
	valueInds[0] = 9;
	valueInds[1] = 10;
	valueInds[2] = 2;
	valueInds[3] = 3;
	// Dual node idx:  1
	valueInds[4] = 2;
	valueInds[5] = 3;
	valueInds[6] = 5;
	valueInds[7] = 8;
	// Dual node idx:  2
	valueInds[8] = 1;
	valueInds[9] = 4;
	valueInds[10] = 0;
	valueInds[11] = 11;
	// Dual node idx:  3
	valueInds[12] = 1;
	valueInds[13] = 4;
	valueInds[14] = 0;
	valueInds[15] = 11;
	// Dual node idx:  4
	valueInds[16] = 2;
	valueInds[17] = 3;
	valueInds[18] = 5;
	valueInds[19] = 8;
	// Dual node idx:  5
	valueInds[20] = 6;
	valueInds[21] = 7;
	valueInds[22] = 1;
	valueInds[23] = 4;
	// Dual node idx:  6
	valueInds[24] = 5;
	valueInds[25] = 8;
	valueInds[26] = 9;
	valueInds[27] = 10;
	// Dual node idx:  7
	valueInds[28] = 5;
	valueInds[29] = 8;
	valueInds[30] = 9;
	valueInds[31] = 10;
	// Dual node idx:  8
	valueInds[32] = 6;
	valueInds[33] = 7;
	valueInds[34] = 1;
	valueInds[35] = 4;
	// Dual node idx:  9
	valueInds[36] = 0;
	valueInds[37] = 11;
	valueInds[38] = 6;
	valueInds[39] = 7;
	// Dual node idx:  10
	valueInds[40] = 0;
	valueInds[41] = 11;
	valueInds[42] = 6;
	valueInds[43] = 7;
	// Dual node idx:  11
	valueInds[44] = 9;
	valueInds[45] = 10;
	valueInds[46] = 2;
	valueInds[47] = 3;

	hodges.resize(INDICES_PER_BLOCK);
	hodges[0] = 2.328785732306081;
	hodges[1] = 2.3287857323060801;
	hodges[2] = 2.3287857323060801;
	hodges[3] = 2.3287857323060797;
	hodges[4] = 2.328785732306081;
	hodges[5] = 2.3287857323060801;
	hodges[6] = 2.3287857323060801;
	hodges[7] = 2.3287857323060797;
	hodges[8] = 2.328785732306081;
	hodges[9] = 2.3287857323060801;
	hodges[10] = 2.3287857323060801;
	hodges[11] = 2.3287857323060797;
	hodges[12] = 2.3287857323060801;
	hodges[13] = 2.3287857323060801;
	hodges[14] = 2.3287857323060801;
	hodges[15] = 2.3287857323060788;
	hodges[16] = 2.3287857323060801;
	hodges[17] = 2.3287857323060801;
	hodges[18] = 2.3287857323060801;
	hodges[19] = 2.3287857323060788;
	hodges[20] = 2.328785732306081;
	hodges[21] = 2.3287857323060801;
	hodges[22] = 2.3287857323060801;
	hodges[23] = 2.3287857323060797;
	hodges[24] = 2.328785732306081;
	hodges[25] = 2.3287857323060801;
	hodges[26] = 2.3287857323060801;
	hodges[27] = 2.3287857323060797;
	hodges[28] = 2.3287857323060801;
	hodges[29] = 2.3287857323060801;
	hodges[30] = 2.3287857323060801;
	hodges[31] = 2.3287857323060788;
	hodges[32] = 2.3287857323060801;
	hodges[33] = 2.3287857323060801;
	hodges[34] = 2.3287857323060801;
	hodges[35] = 2.3287857323060788;
	hodges[36] = 2.328785732306081;
	hodges[37] = 2.3287857323060801;
	hodges[38] = 2.3287857323060801;
	hodges[39] = 2.3287857323060797;
	hodges[40] = 2.3287857323060801;
	hodges[41] = 2.3287857323060801;
	hodges[42] = 2.3287857323060801;
	hodges[43] = 2.3287857323060788;
	hodges[44] = 2.3287857323060801;
	hodges[45] = 2.3287857323060801;
	hodges[46] = 2.3287857323060801;
	hodges[47] = 2.3287857323060788;

	return 2.328785732306081;
}
