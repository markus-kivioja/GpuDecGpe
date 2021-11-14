#define FACE_COUNT 5
#define DUAL_EDGE_LENGTH 1.0868618817494704
#define VALUES_IN_BLOCK 12
#define INDICES_PER_BLOCK 64
const Vector3 BLOCK_WIDTH = Vector3(2.5099999999999998, 2.5099999999999998, 2.5099999999999998); // dimensions of unit block
const ddouble VOLUME = 0.65888545833333312; // volume of body elements
const bool IS_3D = true; // 3-dimensional
void getPositions(Buffer<Vector3> &pos)
{
	pos.resize(VALUES_IN_BLOCK);
	pos[0] = Vector3(1.5687500000000001, 1.5687500000000001, 1.5687500000000001);
	pos[1] = Vector3(1.5687500000000001, 0.3137500000000002, 0.3137500000000002);
	pos[2] = Vector3(0.3137500000000002, 0.3137500000000002, 0.3137500000000002);
	pos[3] = Vector3(0.94125000000000014, 0.94125000000000014, 0.94125000000000014);
	pos[4] = Vector3(0.3137500000000002, 1.5687500000000001, 0.3137500000000002);
	pos[5] = Vector3(1.5687500000000001, 1.5687500000000001, 0.3137500000000002);
	pos[6] = Vector3(2.19625, 2.19625, 0.94125000000000014);
	pos[7] = Vector3(0.3137500000000002, 1.5687500000000001, 1.5687500000000001);
	pos[8] = Vector3(1.5687500000000001, 0.3137500000000002, 1.5687500000000001);
	pos[9] = Vector3(0.3137500000000002, 0.3137500000000002, 1.5687500000000001);
	pos[10] = Vector3(2.19625, 0.94125000000000014, 2.19625);
	pos[11] = Vector3(0.94125000000000014, 2.19625, 2.19625);
}
ddouble getLaplacian(Buffer<int3> &blockDirs, Buffer<int> &valueInds, Buffer<ddouble> &hodges, Buffer<int2> &indicesAndFaceCounts)
{
	blockDirs.resize(INDICES_PER_BLOCK);
	// Dual node idx:  0
	blockDirs[0] = make_int3(0, 0, 0);
	blockDirs[1] = make_int3(0, 0, 0);
	blockDirs[2] = make_int3(0, 0, 0);
	blockDirs[3] = make_int3(0, 0, 0);
	// Dual node idx:  1
	blockDirs[4] = make_int3(0, -1, 0);
	blockDirs[5] = make_int3(0, 0, 0);
	blockDirs[6] = make_int3(0, 0, -1);
	blockDirs[7] = make_int3(0, -1, -1);
	// Dual node idx:  2
	blockDirs[8] = make_int3(-1, -1, 0);
	blockDirs[9] = make_int3(0, 0, 0);
	blockDirs[10] = make_int3(-1, 0, -1);
	blockDirs[11] = make_int3(0, -1, -1);
	// Dual node idx:  3
	blockDirs[12] = make_int3(0, 0, 0);
	blockDirs[13] = make_int3(0, 0, 0);
	blockDirs[14] = make_int3(0, 0, 0);
	blockDirs[15] = make_int3(0, 0, 0);
	blockDirs[16] = make_int3(0, 0, 0);
	blockDirs[17] = make_int3(0, 0, 0);
	blockDirs[18] = make_int3(0, 0, 0);
	blockDirs[19] = make_int3(0, 0, 0);
	// Dual node idx:  4
	blockDirs[20] = make_int3(-1, 0, 0);
	blockDirs[21] = make_int3(0, 0, 0);
	blockDirs[22] = make_int3(0, 0, -1);
	blockDirs[23] = make_int3(-1, 0, -1);
	// Dual node idx:  5
	blockDirs[24] = make_int3(0, 0, 0);
	blockDirs[25] = make_int3(0, 0, 0);
	blockDirs[26] = make_int3(0, 0, -1);
	blockDirs[27] = make_int3(0, 0, -1);
	// Dual node idx:  6
	blockDirs[28] = make_int3(1, 1, 0);
	blockDirs[29] = make_int3(1, 0, 0);
	blockDirs[30] = make_int3(1, 1, 0);
	blockDirs[31] = make_int3(0, 1, 0);
	blockDirs[32] = make_int3(0, 0, 0);
	blockDirs[33] = make_int3(0, 1, 0);
	blockDirs[34] = make_int3(1, 0, 0);
	blockDirs[35] = make_int3(0, 0, 0);
	// Dual node idx:  7
	blockDirs[36] = make_int3(0, 0, 0);
	blockDirs[37] = make_int3(0, 0, 0);
	blockDirs[38] = make_int3(-1, 0, 0);
	blockDirs[39] = make_int3(-1, 0, 0);
	// Dual node idx:  8
	blockDirs[40] = make_int3(0, 0, 0);
	blockDirs[41] = make_int3(0, 0, 0);
	blockDirs[42] = make_int3(0, -1, 0);
	blockDirs[43] = make_int3(0, -1, 0);
	// Dual node idx:  9
	blockDirs[44] = make_int3(-1, 0, 0);
	blockDirs[45] = make_int3(0, 0, 0);
	blockDirs[46] = make_int3(0, -1, 0);
	blockDirs[47] = make_int3(-1, -1, 0);
	// Dual node idx:  10
	blockDirs[48] = make_int3(1, 0, 1);
	blockDirs[49] = make_int3(1, 0, 0);
	blockDirs[50] = make_int3(1, 0, 1);
	blockDirs[51] = make_int3(0, 0, 1);
	blockDirs[52] = make_int3(0, 0, 0);
	blockDirs[53] = make_int3(0, 0, 1);
	blockDirs[54] = make_int3(1, 0, 0);
	blockDirs[55] = make_int3(0, 0, 0);
	// Dual node idx:  11
	blockDirs[56] = make_int3(0, 1, 1);
	blockDirs[57] = make_int3(0, 1, 0);
	blockDirs[58] = make_int3(0, 1, 1);
	blockDirs[59] = make_int3(0, 0, 1);
	blockDirs[60] = make_int3(0, 0, 0);
	blockDirs[61] = make_int3(0, 0, 1);
	blockDirs[62] = make_int3(0, 1, 0);
	blockDirs[63] = make_int3(0, 0, 0);

	valueInds.resize(INDICES_PER_BLOCK);
	// Dual node idx:  0
	valueInds[0] = 11;
	valueInds[1] = 3;
	valueInds[2] = 10;
	valueInds[3] = 6;
	valueInds[4] = 6;
	// Dual node idx:  1
	valueInds[5] = 3;
	valueInds[6] = 10;
	valueInds[7] = 11;
	valueInds[8] = 6;
	valueInds[9] = 3;
	// Dual node idx:  2
	valueInds[10] = 10;
	valueInds[11] = 11;
	valueInds[12] = 0;
	valueInds[13] = 5;
	valueInds[14] = 7;
	// Dual node idx:  3
	valueInds[15] = 8;
	valueInds[16] = 1;
	valueInds[17] = 9;
	valueInds[18] = 4;
	valueInds[19] = 2;
	// Dual node idx:  4
	valueInds[20] = 6;
	valueInds[21] = 3;
	valueInds[22] = 11;
	valueInds[23] = 10;
	valueInds[24] = 6;
	// Dual node idx:  5
	valueInds[25] = 3;
	valueInds[26] = 11;
	valueInds[27] = 10;
	valueInds[28] = 2;
	valueInds[29] = 4;
	// Dual node idx:  6
	valueInds[30] = 9;
	valueInds[31] = 1;
	valueInds[32] = 5;
	valueInds[33] = 8;
	valueInds[34] = 7;
	// Dual node idx:  7
	valueInds[35] = 0;
	valueInds[36] = 11;
	valueInds[37] = 3;
	valueInds[38] = 10;
	valueInds[39] = 6;
	// Dual node idx:  8
	valueInds[40] = 10;
	valueInds[41] = 3;
	valueInds[42] = 11;
	valueInds[43] = 6;
	valueInds[44] = 10;
	// Dual node idx:  9
	valueInds[45] = 3;
	valueInds[46] = 11;
	valueInds[47] = 6;
	valueInds[48] = 2;
	valueInds[49] = 9;
	// Dual node idx:  10
	valueInds[50] = 4;
	valueInds[51] = 1;
	valueInds[52] = 8;
	valueInds[53] = 5;
	valueInds[54] = 7;
	// Dual node idx:  11
	valueInds[55] = 0;
	valueInds[56] = 2;
	valueInds[57] = 9;
	valueInds[58] = 1;
	valueInds[59] = 4;
	// Dual node idx:  12
	valueInds[60] = 7;
	valueInds[61] = 5;
	valueInds[62] = 8;
	valueInds[63] = 0;

	hodges.resize(INDICES_PER_BLOCK);
	hodges[0] = 1.9047316709258588;
	hodges[1] = 1.9047316709258588;
	hodges[2] = 1.9047316709258588;
	hodges[3] = 1.9047316709258588;
	hodges[4] = 1.9047316709258588;
	hodges[5] = 1.9047316709258588;
	hodges[6] = 1.9047316709258588;
	hodges[7] = 1.9047316709258588;
	hodges[8] = 1.9047316709258588;
	hodges[9] = 1.9047316709258588;
	hodges[10] = 1.9047316709258588;
	hodges[11] = 1.9047316709258588;
	hodges[12] = 0.47618291773146471;
	hodges[13] = 0.47618291773146471;
	hodges[14] = 0.47618291773146471;
	hodges[15] = 0.47618291773146471;
	hodges[16] = 0.47618291773146471;
	hodges[17] = 0.47618291773146471;
	hodges[18] = 0.47618291773146471;
	hodges[19] = 0.47618291773146471;
	hodges[20] = 1.9047316709258588;
	hodges[21] = 1.9047316709258588;
	hodges[22] = 1.9047316709258588;
	hodges[23] = 1.9047316709258588;
	hodges[24] = 1.9047316709258588;
	hodges[25] = 1.9047316709258588;
	hodges[26] = 1.9047316709258588;
	hodges[27] = 1.9047316709258588;
	hodges[28] = 0.47618291773146471;
	hodges[29] = 0.47618291773146471;
	hodges[30] = 0.47618291773146471;
	hodges[31] = 0.47618291773146471;
	hodges[32] = 0.47618291773146471;
	hodges[33] = 0.47618291773146471;
	hodges[34] = 0.47618291773146471;
	hodges[35] = 0.47618291773146471;
	hodges[36] = 1.9047316709258588;
	hodges[37] = 1.9047316709258588;
	hodges[38] = 1.9047316709258588;
	hodges[39] = 1.9047316709258588;
	hodges[40] = 1.9047316709258588;
	hodges[41] = 1.9047316709258588;
	hodges[42] = 1.9047316709258588;
	hodges[43] = 1.9047316709258588;
	hodges[44] = 1.9047316709258588;
	hodges[45] = 1.9047316709258588;
	hodges[46] = 1.9047316709258588;
	hodges[47] = 1.9047316709258588;
	hodges[48] = 0.47618291773146471;
	hodges[49] = 0.47618291773146471;
	hodges[50] = 0.47618291773146471;
	hodges[51] = 0.47618291773146471;
	hodges[52] = 0.47618291773146471;
	hodges[53] = 0.47618291773146471;
	hodges[54] = 0.47618291773146471;
	hodges[55] = 0.47618291773146471;
	hodges[56] = 0.47618291773146471;
	hodges[57] = 0.47618291773146471;
	hodges[58] = 0.47618291773146471;
	hodges[59] = 0.47618291773146471;
	hodges[60] = 0.47618291773146471;
	hodges[61] = 0.47618291773146471;
	hodges[62] = 0.47618291773146471;
	hodges[63] = 0.47618291773146471;


	indicesAndFaceCounts.resize(VALUES_IN_BLOCK);
	indicesAndFaceCounts[0] = make_int2(0, 4);
	indicesAndFaceCounts[1] = make_int2(4, 4);
	indicesAndFaceCounts[2] = make_int2(8, 4);
	indicesAndFaceCounts[3] = make_int2(12, 8);
	indicesAndFaceCounts[4] = make_int2(20, 4);
	indicesAndFaceCounts[5] = make_int2(24, 4);
	indicesAndFaceCounts[6] = make_int2(28, 8);
	indicesAndFaceCounts[7] = make_int2(36, 4);
	indicesAndFaceCounts[8] = make_int2(40, 4);
	indicesAndFaceCounts[9] = make_int2(44, 4);
	indicesAndFaceCounts[10] = make_int2(48, 8);
	indicesAndFaceCounts[11] = make_int2(56, 8);

	return 1.9047316709258588;
}
