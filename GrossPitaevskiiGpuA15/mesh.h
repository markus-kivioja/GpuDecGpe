#define FACE_COUNT 4
#define DUAL_EDGE_LENGTH 0.93322244621236106
#define VALUES_IN_BLOCK 46
#define INDICES_PER_BLOCK 184
const Vector3 BLOCK_WIDTH = Vector3(3.9100000000000001, 3.9100000000000001, 3.9100000000000001); // dimensions of unit block
const ddouble VOLUME = 1.2453431458333333; // volume of body elements
const bool IS_3D = true; // 3-dimensional
void getPositions(Buffer<Vector3> &pos)
{
	pos.resize(VALUES_IN_BLOCK);
	pos[0] = Vector3(3.4212500000000006, 0.12218750000000045, 0.73312500000000058);
	pos[1] = Vector3(2.6881250000000008, 2.0771875000000004, 1.4662500000000005);
	pos[2] = Vector3(3.4212500000000006, 2.8103125000000002, 0.73312500000000047);
	pos[3] = Vector3(2.1993750000000003, 3.4212500000000006, 0.12218750000000045);
	pos[4] = Vector3(0.24437500000000051, 0.85531250000000048, 1.4662500000000007);
	pos[5] = Vector3(0.32583333333333392, 2.6066666666666674, 0.32583333333333375);
	pos[6] = Vector3(1.4662500000000005, 2.6881250000000003, 0.85531250000000036);
	pos[7] = Vector3(2.8103125000000002, 0.73312500000000047, 3.4212500000000006);
	pos[8] = Vector3(0.85531250000000048, 1.4662500000000005, 0.24437500000000034);
	pos[9] = Vector3(3.4212500000000006, 0.12218750000000045, 2.1993750000000003);
	pos[10] = Vector3(1.4662500000000005, 0.24437500000000048, 0.85531250000000036);
	pos[11] = Vector3(3.4212500000000006, 0.48875000000000046, 1.4662500000000005);
	pos[12] = Vector3(1.4662500000000005, 0.24437500000000034, 2.0771875000000004);
	pos[13] = Vector3(0.32583333333333375, 2.6066666666666669, 2.6066666666666674);
	pos[14] = Vector3(0.32583333333333397, 0.32583333333333375, 0.32583333333333386);
	pos[15] = Vector3(0.65166666666666717, 0.65166666666666728, 0.65166666666666706);
	pos[16] = Vector3(3.4212500000000006, 2.4437500000000005, 1.4662500000000005);
	pos[17] = Vector3(2.0771875000000004, 1.4662500000000005, 0.24437500000000034);
	pos[18] = Vector3(2.2808333333333337, 2.2808333333333337, 0.65166666666666695);
	pos[19] = Vector3(2.6066666666666669, 0.32583333333333375, 0.32583333333333386);
	pos[20] = Vector3(2.2808333333333337, 0.65166666666666728, 0.65166666666666706);
	pos[21] = Vector3(2.6881250000000003, 0.85531250000000048, 1.4662500000000007);
	pos[22] = Vector3(0.12218750000000056, 0.73312500000000047, 3.4212500000000006);
	pos[23] = Vector3(0.12218750000000056, 2.1993750000000007, 3.4212500000000006);
	pos[24] = Vector3(1.4662500000000005, 3.4212500000000006, 0.48875000000000046);
	pos[25] = Vector3(0.65166666666666706, 2.2808333333333337, 0.65166666666666695);
	pos[26] = Vector3(0.73312500000000058, 3.4212500000000006, 0.12218750000000045);
	pos[27] = Vector3(0.24437500000000034, 2.0771875000000004, 1.4662500000000005);
	pos[28] = Vector3(2.6066666666666669, 2.6066666666666674, 0.32583333333333375);
	pos[29] = Vector3(3.4212500000000006, 2.8103125000000002, 2.1993750000000007);
	pos[30] = Vector3(2.1993750000000007, 3.4212500000000006, 2.8103125000000002);
	pos[31] = Vector3(2.8103125000000002, 2.1993750000000007, 3.4212500000000006);
	pos[32] = Vector3(2.2808333333333337, 0.65166666666666706, 2.2808333333333337);
	pos[33] = Vector3(2.6066666666666674, 0.32583333333333386, 2.6066666666666669);
	pos[34] = Vector3(0.85531250000000036, 1.4662500000000005, 2.6881250000000003);
	pos[35] = Vector3(0.48875000000000057, 1.4662500000000005, 3.4212500000000006);
	pos[36] = Vector3(2.0771875000000009, 1.4662500000000005, 2.6881250000000003);
	pos[37] = Vector3(1.4662500000000005, 2.6881250000000008, 2.0771875000000004);
	pos[38] = Vector3(0.32583333333333375, 0.32583333333333386, 2.6066666666666669);
	pos[39] = Vector3(0.65166666666666706, 0.65166666666666706, 2.2808333333333337);
	pos[40] = Vector3(0.65166666666666706, 2.2808333333333337, 2.2808333333333337);
	pos[41] = Vector3(2.6066666666666674, 2.6066666666666669, 2.6066666666666674);
	pos[42] = Vector3(2.2808333333333337, 2.2808333333333337, 2.2808333333333337);
	pos[43] = Vector3(1.4662500000000005, 3.4212500000000006, 2.4437500000000005);
	pos[44] = Vector3(2.4437500000000005, 1.4662500000000005, 3.4212500000000006);
	pos[45] = Vector3(0.73312500000000047, 3.4212500000000006, 2.8103125000000002);
}
ddouble getLaplacian(Buffer<int3> &blockDirs, Buffer<int> &valueInds, Buffer<ddouble> &hodges)
{
	blockDirs.resize(INDICES_PER_BLOCK);
	// Dual node idx:  0
	blockDirs[0] = make_int3(1, 0, 0);
	blockDirs[1] = make_int3(0, 0, 0);
	blockDirs[2] = make_int3(0, 0, 0);
	blockDirs[3] = make_int3(0, -1, 0);
	// Dual node idx:  1
	blockDirs[4] = make_int3(0, 0, 0);
	blockDirs[5] = make_int3(0, 0, 0);
	blockDirs[6] = make_int3(0, 0, 0);
	blockDirs[7] = make_int3(0, 0, 0);
	// Dual node idx:  2
	blockDirs[8] = make_int3(0, 1, 0);
	blockDirs[9] = make_int3(0, 0, 0);
	blockDirs[10] = make_int3(1, 0, 0);
	blockDirs[11] = make_int3(0, 0, 0);
	// Dual node idx:  3
	blockDirs[12] = make_int3(0, 1, 0);
	blockDirs[13] = make_int3(0, 0, 0);
	blockDirs[14] = make_int3(0, 0, 0);
	blockDirs[15] = make_int3(0, 0, -1);
	// Dual node idx:  4
	blockDirs[16] = make_int3(0, 0, 0);
	blockDirs[17] = make_int3(-1, 0, 0);
	blockDirs[18] = make_int3(0, 0, 0);
	blockDirs[19] = make_int3(0, 0, 0);
	// Dual node idx:  5
	blockDirs[20] = make_int3(-1, 0, 0);
	blockDirs[21] = make_int3(0, 0, 0);
	blockDirs[22] = make_int3(0, 0, 0);
	blockDirs[23] = make_int3(0, 0, -1);
	// Dual node idx:  6
	blockDirs[24] = make_int3(0, 0, 0);
	blockDirs[25] = make_int3(0, 0, 0);
	blockDirs[26] = make_int3(0, 0, 0);
	blockDirs[27] = make_int3(0, 0, 0);
	// Dual node idx:  7
	blockDirs[28] = make_int3(0, 0, 1);
	blockDirs[29] = make_int3(0, 0, 0);
	blockDirs[30] = make_int3(1, 0, 0);
	blockDirs[31] = make_int3(0, 0, 0);
	// Dual node idx:  8
	blockDirs[32] = make_int3(0, 0, 0);
	blockDirs[33] = make_int3(0, 0, -1);
	blockDirs[34] = make_int3(0, 0, 0);
	blockDirs[35] = make_int3(0, 0, 0);
	// Dual node idx:  9
	blockDirs[36] = make_int3(1, 0, 0);
	blockDirs[37] = make_int3(0, 0, 0);
	blockDirs[38] = make_int3(0, 0, 0);
	blockDirs[39] = make_int3(0, -1, 0);
	// Dual node idx:  10
	blockDirs[40] = make_int3(0, 0, 0);
	blockDirs[41] = make_int3(0, -1, 0);
	blockDirs[42] = make_int3(0, 0, 0);
	blockDirs[43] = make_int3(0, 0, 0);
	// Dual node idx:  11
	blockDirs[44] = make_int3(0, 0, 0);
	blockDirs[45] = make_int3(1, 0, 0);
	blockDirs[46] = make_int3(0, 0, 0);
	blockDirs[47] = make_int3(0, 0, 0);
	// Dual node idx:  12
	blockDirs[48] = make_int3(0, 0, 0);
	blockDirs[49] = make_int3(0, -1, 0);
	blockDirs[50] = make_int3(0, 0, 0);
	blockDirs[51] = make_int3(0, 0, 0);
	// Dual node idx:  13
	blockDirs[52] = make_int3(0, 0, 0);
	blockDirs[53] = make_int3(0, 0, 0);
	blockDirs[54] = make_int3(0, 0, 0);
	blockDirs[55] = make_int3(-1, 0, 0);
	// Dual node idx:  14
	blockDirs[56] = make_int3(-1, 0, 0);
	blockDirs[57] = make_int3(0, 0, 0);
	blockDirs[58] = make_int3(0, 0, -1);
	blockDirs[59] = make_int3(0, -1, 0);
	// Dual node idx:  15
	blockDirs[60] = make_int3(0, 0, 0);
	blockDirs[61] = make_int3(0, 0, 0);
	blockDirs[62] = make_int3(0, 0, 0);
	blockDirs[63] = make_int3(0, 0, 0);
	// Dual node idx:  16
	blockDirs[64] = make_int3(0, 0, 0);
	blockDirs[65] = make_int3(0, 0, 0);
	blockDirs[66] = make_int3(1, 0, 0);
	blockDirs[67] = make_int3(0, 0, 0);
	// Dual node idx:  17
	blockDirs[68] = make_int3(0, 0, 0);
	blockDirs[69] = make_int3(0, 0, -1);
	blockDirs[70] = make_int3(0, 0, 0);
	blockDirs[71] = make_int3(0, 0, 0);
	// Dual node idx:  18
	blockDirs[72] = make_int3(0, 0, 0);
	blockDirs[73] = make_int3(0, 0, 0);
	blockDirs[74] = make_int3(0, 0, 0);
	blockDirs[75] = make_int3(0, 0, 0);
	// Dual node idx:  19
	blockDirs[76] = make_int3(0, 0, 0);
	blockDirs[77] = make_int3(0, 0, 0);
	blockDirs[78] = make_int3(0, 0, -1);
	blockDirs[79] = make_int3(0, -1, 0);
	// Dual node idx:  20
	blockDirs[80] = make_int3(0, 0, 0);
	blockDirs[81] = make_int3(0, 0, 0);
	blockDirs[82] = make_int3(0, 0, 0);
	blockDirs[83] = make_int3(0, 0, 0);
	// Dual node idx:  21
	blockDirs[84] = make_int3(0, 0, 0);
	blockDirs[85] = make_int3(0, 0, 0);
	blockDirs[86] = make_int3(0, 0, 0);
	blockDirs[87] = make_int3(0, 0, 0);
	// Dual node idx:  22
	blockDirs[88] = make_int3(0, 0, 1);
	blockDirs[89] = make_int3(0, 0, 0);
	blockDirs[90] = make_int3(-1, 0, 0);
	blockDirs[91] = make_int3(0, 0, 0);
	// Dual node idx:  23
	blockDirs[92] = make_int3(0, 0, 1);
	blockDirs[93] = make_int3(0, 0, 0);
	blockDirs[94] = make_int3(-1, 0, 0);
	blockDirs[95] = make_int3(0, 0, 0);
	// Dual node idx:  24
	blockDirs[96] = make_int3(0, 0, 0);
	blockDirs[97] = make_int3(0, 1, 0);
	blockDirs[98] = make_int3(0, 0, 0);
	blockDirs[99] = make_int3(0, 0, 0);
	// Dual node idx:  25
	blockDirs[100] = make_int3(0, 0, 0);
	blockDirs[101] = make_int3(0, 0, 0);
	blockDirs[102] = make_int3(0, 0, 0);
	blockDirs[103] = make_int3(0, 0, 0);
	// Dual node idx:  26
	blockDirs[104] = make_int3(0, 1, 0);
	blockDirs[105] = make_int3(0, 0, 0);
	blockDirs[106] = make_int3(0, 0, 0);
	blockDirs[107] = make_int3(0, 0, -1);
	// Dual node idx:  27
	blockDirs[108] = make_int3(0, 0, 0);
	blockDirs[109] = make_int3(-1, 0, 0);
	blockDirs[110] = make_int3(0, 0, 0);
	blockDirs[111] = make_int3(0, 0, 0);
	// Dual node idx:  28
	blockDirs[112] = make_int3(0, 0, 0);
	blockDirs[113] = make_int3(0, 0, 0);
	blockDirs[114] = make_int3(0, 0, 0);
	blockDirs[115] = make_int3(0, 0, -1);
	// Dual node idx:  29
	blockDirs[116] = make_int3(0, 1, 0);
	blockDirs[117] = make_int3(0, 0, 0);
	blockDirs[118] = make_int3(1, 0, 0);
	blockDirs[119] = make_int3(0, 0, 0);
	// Dual node idx:  30
	blockDirs[120] = make_int3(0, 0, 1);
	blockDirs[121] = make_int3(0, 0, 0);
	blockDirs[122] = make_int3(0, 1, 0);
	blockDirs[123] = make_int3(0, 0, 0);
	// Dual node idx:  31
	blockDirs[124] = make_int3(0, 0, 1);
	blockDirs[125] = make_int3(0, 0, 0);
	blockDirs[126] = make_int3(1, 0, 0);
	blockDirs[127] = make_int3(0, 0, 0);
	// Dual node idx:  32
	blockDirs[128] = make_int3(0, 0, 0);
	blockDirs[129] = make_int3(0, 0, 0);
	blockDirs[130] = make_int3(0, 0, 0);
	blockDirs[131] = make_int3(0, 0, 0);
	// Dual node idx:  33
	blockDirs[132] = make_int3(0, 0, 0);
	blockDirs[133] = make_int3(0, 0, 0);
	blockDirs[134] = make_int3(0, -1, 0);
	blockDirs[135] = make_int3(0, 0, 0);
	// Dual node idx:  34
	blockDirs[136] = make_int3(0, 0, 0);
	blockDirs[137] = make_int3(0, 0, 0);
	blockDirs[138] = make_int3(0, 0, 0);
	blockDirs[139] = make_int3(0, 0, 0);
	// Dual node idx:  35
	blockDirs[140] = make_int3(0, 0, 0);
	blockDirs[141] = make_int3(0, 0, 1);
	blockDirs[142] = make_int3(0, 0, 0);
	blockDirs[143] = make_int3(0, 0, 0);
	// Dual node idx:  36
	blockDirs[144] = make_int3(0, 0, 0);
	blockDirs[145] = make_int3(0, 0, 0);
	blockDirs[146] = make_int3(0, 0, 0);
	blockDirs[147] = make_int3(0, 0, 0);
	// Dual node idx:  37
	blockDirs[148] = make_int3(0, 0, 0);
	blockDirs[149] = make_int3(0, 0, 0);
	blockDirs[150] = make_int3(0, 0, 0);
	blockDirs[151] = make_int3(0, 0, 0);
	// Dual node idx:  38
	blockDirs[152] = make_int3(0, 0, 0);
	blockDirs[153] = make_int3(0, 0, 0);
	blockDirs[154] = make_int3(0, -1, 0);
	blockDirs[155] = make_int3(-1, 0, 0);
	// Dual node idx:  39
	blockDirs[156] = make_int3(0, 0, 0);
	blockDirs[157] = make_int3(0, 0, 0);
	blockDirs[158] = make_int3(0, 0, 0);
	blockDirs[159] = make_int3(0, 0, 0);
	// Dual node idx:  40
	blockDirs[160] = make_int3(0, 0, 0);
	blockDirs[161] = make_int3(0, 0, 0);
	blockDirs[162] = make_int3(0, 0, 0);
	blockDirs[163] = make_int3(0, 0, 0);
	// Dual node idx:  41
	blockDirs[164] = make_int3(0, 0, 0);
	blockDirs[165] = make_int3(0, 0, 0);
	blockDirs[166] = make_int3(0, 0, 0);
	blockDirs[167] = make_int3(0, 0, 0);
	// Dual node idx:  42
	blockDirs[168] = make_int3(0, 0, 0);
	blockDirs[169] = make_int3(0, 0, 0);
	blockDirs[170] = make_int3(0, 0, 0);
	blockDirs[171] = make_int3(0, 0, 0);
	// Dual node idx:  43
	blockDirs[172] = make_int3(0, 0, 0);
	blockDirs[173] = make_int3(0, 0, 0);
	blockDirs[174] = make_int3(0, 1, 0);
	blockDirs[175] = make_int3(0, 0, 0);
	// Dual node idx:  44
	blockDirs[176] = make_int3(0, 0, 0);
	blockDirs[177] = make_int3(0, 0, 1);
	blockDirs[178] = make_int3(0, 0, 0);
	blockDirs[179] = make_int3(0, 0, 0);
	// Dual node idx:  45
	blockDirs[180] = make_int3(0, 0, 1);
	blockDirs[181] = make_int3(0, 0, 0);
	blockDirs[182] = make_int3(0, 1, 0);
	blockDirs[183] = make_int3(0, 0, 0);

	valueInds.resize(INDICES_PER_BLOCK);
	// Dual node idx:  0
	valueInds[0] = 14;
	valueInds[1] = 11;
	valueInds[2] = 19;
	valueInds[3] = 2;
	// Dual node idx:  1
	valueInds[4] = 42;
	valueInds[5] = 16;
	valueInds[6] = 18;
	valueInds[7] = 21;
	// Dual node idx:  2
	valueInds[8] = 0;
	valueInds[9] = 16;
	valueInds[10] = 5;
	valueInds[11] = 28;
	// Dual node idx:  3
	valueInds[12] = 19;
	valueInds[13] = 24;
	valueInds[14] = 28;
	valueInds[15] = 30;
	// Dual node idx:  4
	valueInds[16] = 27;
	valueInds[17] = 11;
	valueInds[18] = 39;
	valueInds[19] = 15;
	// Dual node idx:  5
	valueInds[20] = 2;
	valueInds[21] = 25;
	valueInds[22] = 26;
	valueInds[23] = 23;
	// Dual node idx:  6
	valueInds[24] = 37;
	valueInds[25] = 24;
	valueInds[26] = 18;
	valueInds[27] = 25;
	// Dual node idx:  7
	valueInds[28] = 19;
	valueInds[29] = 44;
	valueInds[30] = 22;
	valueInds[31] = 33;
	// Dual node idx:  8
	valueInds[32] = 25;
	valueInds[33] = 35;
	valueInds[34] = 15;
	valueInds[35] = 17;
	// Dual node idx:  9
	valueInds[36] = 38;
	valueInds[37] = 11;
	valueInds[38] = 33;
	valueInds[39] = 29;
	// Dual node idx:  10
	valueInds[40] = 12;
	valueInds[41] = 24;
	valueInds[42] = 20;
	valueInds[43] = 15;
	// Dual node idx:  11
	valueInds[44] = 21;
	valueInds[45] = 4;
	valueInds[46] = 9;
	valueInds[47] = 0;
	// Dual node idx:  12
	valueInds[48] = 32;
	valueInds[49] = 43;
	valueInds[50] = 39;
	valueInds[51] = 10;
	// Dual node idx:  13
	valueInds[52] = 45;
	valueInds[53] = 40;
	valueInds[54] = 23;
	valueInds[55] = 29;
	// Dual node idx:  14
	valueInds[56] = 0;
	valueInds[57] = 15;
	valueInds[58] = 22;
	valueInds[59] = 26;
	// Dual node idx:  15
	valueInds[60] = 4;
	valueInds[61] = 14;
	valueInds[62] = 8;
	valueInds[63] = 10;
	// Dual node idx:  16
	valueInds[64] = 2;
	valueInds[65] = 29;
	valueInds[66] = 27;
	valueInds[67] = 1;
	// Dual node idx:  17
	valueInds[68] = 18;
	valueInds[69] = 44;
	valueInds[70] = 20;
	valueInds[71] = 8;
	// Dual node idx:  18
	valueInds[72] = 1;
	valueInds[73] = 28;
	valueInds[74] = 6;
	valueInds[75] = 17;
	// Dual node idx:  19
	valueInds[76] = 0;
	valueInds[77] = 20;
	valueInds[78] = 7;
	valueInds[79] = 3;
	// Dual node idx:  20
	valueInds[80] = 21;
	valueInds[81] = 19;
	valueInds[82] = 17;
	valueInds[83] = 10;
	// Dual node idx:  21
	valueInds[84] = 1;
	valueInds[85] = 11;
	valueInds[86] = 32;
	valueInds[87] = 20;
	// Dual node idx:  22
	valueInds[88] = 14;
	valueInds[89] = 35;
	valueInds[90] = 7;
	valueInds[91] = 38;
	// Dual node idx:  23
	valueInds[92] = 5;
	valueInds[93] = 35;
	valueInds[94] = 31;
	valueInds[95] = 13;
	// Dual node idx:  24
	valueInds[96] = 6;
	valueInds[97] = 10;
	valueInds[98] = 3;
	valueInds[99] = 26;
	// Dual node idx:  25
	valueInds[100] = 27;
	valueInds[101] = 5;
	valueInds[102] = 6;
	valueInds[103] = 8;
	// Dual node idx:  26
	valueInds[104] = 14;
	valueInds[105] = 24;
	valueInds[106] = 5;
	valueInds[107] = 45;
	// Dual node idx:  27
	valueInds[108] = 40;
	valueInds[109] = 16;
	valueInds[110] = 25;
	valueInds[111] = 4;
	// Dual node idx:  28
	valueInds[112] = 2;
	valueInds[113] = 18;
	valueInds[114] = 3;
	valueInds[115] = 31;
	// Dual node idx:  29
	valueInds[116] = 9;
	valueInds[117] = 16;
	valueInds[118] = 13;
	valueInds[119] = 41;
	// Dual node idx:  30
	valueInds[120] = 3;
	valueInds[121] = 43;
	valueInds[122] = 33;
	valueInds[123] = 41;
	// Dual node idx:  31
	valueInds[124] = 28;
	valueInds[125] = 44;
	valueInds[126] = 23;
	valueInds[127] = 41;
	// Dual node idx:  32
	valueInds[128] = 36;
	valueInds[129] = 33;
	valueInds[130] = 12;
	valueInds[131] = 21;
	// Dual node idx:  33
	valueInds[132] = 7;
	valueInds[133] = 32;
	valueInds[134] = 30;
	valueInds[135] = 9;
	// Dual node idx:  34
	valueInds[136] = 36;
	valueInds[137] = 35;
	valueInds[138] = 40;
	valueInds[139] = 39;
	// Dual node idx:  35
	valueInds[140] = 23;
	valueInds[141] = 8;
	valueInds[142] = 22;
	valueInds[143] = 34;
	// Dual node idx:  36
	valueInds[144] = 34;
	valueInds[145] = 44;
	valueInds[146] = 42;
	valueInds[147] = 32;
	// Dual node idx:  37
	valueInds[148] = 42;
	valueInds[149] = 43;
	valueInds[150] = 40;
	valueInds[151] = 6;
	// Dual node idx:  38
	valueInds[152] = 22;
	valueInds[153] = 39;
	valueInds[154] = 45;
	valueInds[155] = 9;
	// Dual node idx:  39
	valueInds[156] = 34;
	valueInds[157] = 38;
	valueInds[158] = 12;
	valueInds[159] = 4;
	// Dual node idx:  40
	valueInds[160] = 37;
	valueInds[161] = 13;
	valueInds[162] = 34;
	valueInds[163] = 27;
	// Dual node idx:  41
	valueInds[164] = 30;
	valueInds[165] = 42;
	valueInds[166] = 31;
	valueInds[167] = 29;
	// Dual node idx:  42
	valueInds[168] = 37;
	valueInds[169] = 41;
	valueInds[170] = 36;
	valueInds[171] = 1;
	// Dual node idx:  43
	valueInds[172] = 45;
	valueInds[173] = 30;
	valueInds[174] = 12;
	valueInds[175] = 37;
	// Dual node idx:  44
	valueInds[176] = 31;
	valueInds[177] = 17;
	valueInds[178] = 7;
	valueInds[179] = 36;
	// Dual node idx:  45
	valueInds[180] = 26;
	valueInds[181] = 43;
	valueInds[182] = 38;
	valueInds[183] = 13;

	hodges.resize(INDICES_PER_BLOCK);
	hodges[0] = 1.8838181330577379;
	hodges[1] = 2.0931312589530426;
	hodges[2] = 1.8838181330577373;
	hodges[3] = 1.2558787553718254;
	hodges[4] = 1.8838181330577377;
	hodges[5] = 2.0931312589530426;
	hodges[6] = 1.8838181330577373;
	hodges[7] = 1.2558787553718254;
	hodges[8] = 1.2558787553718249;
	hodges[9] = 2.0931312589530426;
	hodges[10] = 1.8838181330577379;
	hodges[11] = 1.8838181330577373;
	hodges[12] = 1.8838181330577377;
	hodges[13] = 2.0931312589530426;
	hodges[14] = 1.8838181330577379;
	hodges[15] = 1.2558787553718254;
	hodges[16] = 1.2558787553718254;
	hodges[17] = 2.0931312589530418;
	hodges[18] = 1.8838181330577384;
	hodges[19] = 1.8838181330577377;
	hodges[20] = 1.6745050071624337;
	hodges[21] = 3.1396968884295626;
	hodges[22] = 1.6745050071624337;
	hodges[23] = 1.6745050071624334;
	hodges[24] = 1.2558787553718254;
	hodges[25] = 2.0931312589530418;
	hodges[26] = 1.8838181330577379;
	hodges[27] = 1.8838181330577377;
	hodges[28] = 1.8838181330577379;
	hodges[29] = 2.0931312589530426;
	hodges[30] = 1.2558787553718249;
	hodges[31] = 1.8838181330577377;
	hodges[32] = 1.8838181330577379;
	hodges[33] = 2.0931312589530426;
	hodges[34] = 1.8838181330577379;
	hodges[35] = 1.2558787553718254;
	hodges[36] = 1.8838181330577377;
	hodges[37] = 2.0931312589530426;
	hodges[38] = 1.8838181330577379;
	hodges[39] = 1.2558787553718254;
	hodges[40] = 1.2558787553718254;
	hodges[41] = 2.0931312589530426;
	hodges[42] = 1.8838181330577379;
	hodges[43] = 1.8838181330577379;
	hodges[44] = 2.0931312589530418;
	hodges[45] = 2.0931312589530418;
	hodges[46] = 2.0931312589530426;
	hodges[47] = 2.0931312589530426;
	hodges[48] = 1.8838181330577379;
	hodges[49] = 2.0931312589530426;
	hodges[50] = 1.8838181330577377;
	hodges[51] = 1.2558787553718254;
	hodges[52] = 1.674505007162433;
	hodges[53] = 3.1396968884295622;
	hodges[54] = 1.6745050071624341;
	hodges[55] = 1.6745050071624337;
	hodges[56] = 1.6745050071624334;
	hodges[57] = 3.1396968884295635;
	hodges[58] = 1.6745050071624334;
	hodges[59] = 1.6745050071624337;
	hodges[60] = 1.6745050071624334;
	hodges[61] = 3.1396968884295635;
	hodges[62] = 1.6745050071624337;
	hodges[63] = 1.6745050071624337;
	hodges[64] = 2.0931312589530426;
	hodges[65] = 2.0931312589530422;
	hodges[66] = 2.0931312589530418;
	hodges[67] = 2.0931312589530426;
	hodges[68] = 1.8838181330577379;
	hodges[69] = 2.0931312589530426;
	hodges[70] = 1.8838181330577379;
	hodges[71] = 1.2558787553718254;
	hodges[72] = 1.674505007162433;
	hodges[73] = 3.1396968884295626;
	hodges[74] = 1.6745050071624337;
	hodges[75] = 1.6745050071624337;
	hodges[76] = 1.674505007162433;
	hodges[77] = 3.1396968884295635;
	hodges[78] = 1.6745050071624334;
	hodges[79] = 1.6745050071624337;
	hodges[80] = 1.6745050071624334;
	hodges[81] = 3.1396968884295635;
	hodges[82] = 1.6745050071624337;
	hodges[83] = 1.6745050071624337;
	hodges[84] = 1.2558787553718254;
	hodges[85] = 2.0931312589530418;
	hodges[86] = 1.8838181330577384;
	hodges[87] = 1.8838181330577377;
	hodges[88] = 1.8838181330577379;
	hodges[89] = 2.0931312589530426;
	hodges[90] = 1.2558787553718254;
	hodges[91] = 1.8838181330577373;
	hodges[92] = 1.8838181330577379;
	hodges[93] = 2.0931312589530418;
	hodges[94] = 1.2558787553718254;
	hodges[95] = 1.8838181330577384;
	hodges[96] = 2.0931312589530418;
	hodges[97] = 2.0931312589530418;
	hodges[98] = 2.0931312589530426;
	hodges[99] = 2.0931312589530426;
	hodges[100] = 1.6745050071624334;
	hodges[101] = 3.1396968884295626;
	hodges[102] = 1.6745050071624334;
	hodges[103] = 1.6745050071624337;
	hodges[104] = 1.8838181330577379;
	hodges[105] = 2.0931312589530426;
	hodges[106] = 1.8838181330577379;
	hodges[107] = 1.2558787553718254;
	hodges[108] = 1.8838181330577379;
	hodges[109] = 2.0931312589530426;
	hodges[110] = 1.8838181330577377;
	hodges[111] = 1.2558787553718254;
	hodges[112] = 1.674505007162433;
	hodges[113] = 3.1396968884295626;
	hodges[114] = 1.6745050071624337;
	hodges[115] = 1.6745050071624334;
	hodges[116] = 1.2558787553718249;
	hodges[117] = 2.0931312589530422;
	hodges[118] = 1.8838181330577379;
	hodges[119] = 1.8838181330577379;
	hodges[120] = 1.2558787553718249;
	hodges[121] = 2.0931312589530422;
	hodges[122] = 1.8838181330577379;
	hodges[123] = 1.8838181330577377;
	hodges[124] = 1.8838181330577379;
	hodges[125] = 2.0931312589530422;
	hodges[126] = 1.2558787553718249;
	hodges[127] = 1.883818133057739;
	hodges[128] = 1.6745050071624337;
	hodges[129] = 3.1396968884295626;
	hodges[130] = 1.6745050071624337;
	hodges[131] = 1.6745050071624341;
	hodges[132] = 1.6745050071624334;
	hodges[133] = 3.1396968884295626;
	hodges[134] = 1.6745050071624337;
	hodges[135] = 1.6745050071624337;
	hodges[136] = 1.2558787553718251;
	hodges[137] = 2.0931312589530418;
	hodges[138] = 1.8838181330577379;
	hodges[139] = 1.8838181330577377;
	hodges[140] = 2.0931312589530418;
	hodges[141] = 2.0931312589530418;
	hodges[142] = 2.0931312589530426;
	hodges[143] = 2.0931312589530418;
	hodges[144] = 1.2558787553718251;
	hodges[145] = 2.0931312589530422;
	hodges[146] = 1.8838181330577384;
	hodges[147] = 1.8838181330577379;
	hodges[148] = 1.8838181330577377;
	hodges[149] = 2.0931312589530426;
	hodges[150] = 1.8838181330577373;
	hodges[151] = 1.2558787553718254;
	hodges[152] = 1.674505007162433;
	hodges[153] = 3.139696888429564;
	hodges[154] = 1.6745050071624337;
	hodges[155] = 1.6745050071624337;
	hodges[156] = 1.6745050071624334;
	hodges[157] = 3.139696888429564;
	hodges[158] = 1.6745050071624334;
	hodges[159] = 1.6745050071624341;
	hodges[160] = 1.674505007162433;
	hodges[161] = 3.1396968884295622;
	hodges[162] = 1.6745050071624337;
	hodges[163] = 1.6745050071624337;
	hodges[164] = 1.6745050071624334;
	hodges[165] = 3.1396968884295617;
	hodges[166] = 1.6745050071624346;
	hodges[167] = 1.6745050071624337;
	hodges[168] = 1.6745050071624334;
	hodges[169] = 3.1396968884295617;
	hodges[170] = 1.6745050071624341;
	hodges[171] = 1.6745050071624334;
	hodges[172] = 2.0931312589530426;
	hodges[173] = 2.0931312589530422;
	hodges[174] = 2.0931312589530418;
	hodges[175] = 2.0931312589530426;
	hodges[176] = 2.0931312589530422;
	hodges[177] = 2.0931312589530418;
	hodges[178] = 2.0931312589530426;
	hodges[179] = 2.0931312589530422;
	hodges[180] = 1.2558787553718249;
	hodges[181] = 2.0931312589530426;
	hodges[182] = 1.8838181330577379;
	hodges[183] = 1.8838181330577373;

	return 3.139696888429564;
}
