#define FACE_COUNT 4
#define DUAL_EDGE_LENGTH 0.99180528385789291
#define VALUES_IN_BLOCK 80
#define INDICES_PER_BLOCK 320
const Vector3 BLOCK_WIDTH = Vector3(3.7000000000000002, 6.4085879880048457, 3.7000000000000002); // dimensions of unit block
const ddouble VOLUME = 0.91389134953944084; // volume of body elements
const bool IS_3D = true; // 3-dimensional
void getPositions(Buffer<Vector3> &pos)
{
	pos.resize(VALUES_IN_BLOCK);
	pos[0] = Vector3(0.23124999999999907, 0.32197049550181706, 2.3124999999999991);
	pos[1] = Vector3(0.53958333333333208, 0.72250724475212036, 0.46249999999999891);
	pos[2] = Vector3(1.8885416666666659, 3.0589716153788871, 0.46249999999999902);
	pos[3] = Vector3(0.6607142857142847, 1.3709953149668963, 3.1714285714285699);
	pos[4] = Vector3(1.3874999999999988, 6.0629972347561578, 1.6958333333333322);
	pos[5] = Vector3(2.1142857142857134, 0.074019174537344315, 3.1714285714285704);
	pos[6] = Vector3(2.0812499999999989, 4.3273379880048459, 2.3124999999999991);
	pos[7] = Vector3(3.2374999999999989, 1.523580743252726, 2.3124999999999991);
	pos[8] = Vector3(1.3874999999999988, 2.6298250983249907, 1.4535714285714276);
	pos[9] = Vector3(0.66071428571428492, 1.3709953149668965, 1.4535714285714274);
	pos[10] = Vector3(0.73229166666666534, 2.7919471158786853, 1.0791666666666655);
	pos[11] = Vector3(1.3874999999999988, 3.1257277402539372, 2.3124999999999991);
	pos[12] = Vector3(0.26428571428571324, 3.2783131685397673, 3.1714285714285708);
	pos[13] = Vector3(1.3874999999999988, 4.7278747372551484, 2.3124999999999991);
	pos[14] = Vector3(2.5822916666666655, 1.8573613676279781, 1.0791666666666655);
	pos[15] = Vector3(0.69374999999999887, 4.327337988004845, 2.3124999999999991);
	pos[16] = Vector3(3.2374999999999989, 6.3300217342563601, 2.3124999999999991);
	pos[17] = Vector3(1.3874999999999988, 1.7906052427529278, 2.9291666666666654);
	pos[18] = Vector3(1.3874999999999988, 1.7906052427529278, 1.695833333333332);
	pos[19] = Vector3(3.2374999999999989, 2.8587032407537358, 1.695833333333332);
	pos[20] = Vector3(2.1142857142857134, 1.3709953149668961, 1.4535714285714274);
	pos[21] = Vector3(0.69374999999999865, 3.5262644895042405, 2.3124999999999991);
	pos[22] = Vector3(0.66071428571428481, 0.074019174537343746, 1.4535714285714276);
	pos[23] = Vector3(0.88645833333333202, 3.0589716153788871, 0.46249999999999913);
	pos[24] = Vector3(1.3874999999999988, 5.2237773791840949, 1.4535714285714274);
	pos[25] = Vector3(0.26428571428571307, 3.2783131685397673, 1.4535714285714274);
	pos[26] = Vector3(3.2374999999999989, 2.0194833851816725, 1.4535714285714274);
	pos[27] = Vector3(0.19270833333333204, 1.8573613676279783, 1.0791666666666655);
	pos[28] = Vector3(0.84791666666666576, 0.72250724475212036, 1.0791666666666657);
	pos[29] = Vector3(2.2354166666666662, 0.72250724475212036, 0.46249999999999891);
	pos[30] = Vector3(2.1142857142857134, 0.074019174537344079, 1.4535714285714274);
	pos[31] = Vector3(2.0427083333333327, 2.7919471158786848, 1.0791666666666655);
	pos[32] = Vector3(2.0812499999999994, 3.5262644895042401, 2.3124999999999991);
	pos[33] = Vector3(0.23124999999999907, 1.1230439940024233, 2.3124999999999991);
	pos[34] = Vector3(1.9270833333333326, 0.72250724475212036, 1.0791666666666657);
	pos[35] = Vector3(0.26428571428571324, 4.5752893089693183, 1.453571428571427);
	pos[36] = Vector3(0.038541666666665253, 1.5903368681277763, 0.46249999999999897);
	pos[37] = Vector3(0.19270833333333226, 5.9962411098811081, 1.0791666666666657);
	pos[38] = Vector3(0.73229166666666556, 5.0616553616304003, 1.0791666666666653);
	pos[39] = Vector3(0.077083333333332504, 3.926801238754543, 1.0791666666666655);
	pos[40] = Vector3(0.3854166666666658, 3.926801238754543, 0.46249999999999897);
	pos[41] = Vector3(0.88645833333333202, 4.794630862130199, 0.46249999999999897);
	pos[42] = Vector3(0.038541666666665475, 6.2632656093813104, 0.46249999999999908);
	pos[43] = Vector3(0.66071428571428459, 0.074019174537343913, 3.1714285714285704);
	pos[44] = Vector3(2.5437499999999988, 1.1230439940024228, 2.3124999999999991);
	pos[45] = Vector3(2.5437499999999988, 0.32197049550181739, 2.3124999999999991);
	pos[46] = Vector3(2.5107142857142852, 3.2783131685397668, 1.4535714285714274);
	pos[47] = Vector3(3.2374999999999989, 4.9948992367553506, 1.695833333333332);
	pos[48] = Vector3(2.0427083333333327, 5.0616553616304012, 1.0791666666666653);
	pos[49] = Vector3(2.7364583333333323, 1.5903368681277761, 0.46249999999999902);
	pos[50] = Vector3(2.6979166666666661, 3.926801238754543, 1.0791666666666655);
	pos[51] = Vector3(3.2374999999999989, 5.8341190923274135, 1.4535714285714274);
	pos[52] = Vector3(2.5107142857142848, 4.5752893089693192, 1.4535714285714274);
	pos[53] = Vector3(2.5822916666666655, 5.9962411098811081, 1.0791666666666655);
	pos[54] = Vector3(2.3895833333333325, 3.926801238754543, 0.46249999999999897);
	pos[55] = Vector3(1.8885416666666659, 4.794630862130199, 0.46249999999999897);
	pos[56] = Vector3(2.7364583333333323, 6.2632656093813104, 0.46249999999999891);
	pos[57] = Vector3(2.0427083333333327, 2.7919471158786848, 3.5458333333333325);
	pos[58] = Vector3(2.1142857142857134, 1.3709953149668961, 3.1714285714285708);
	pos[59] = Vector3(1.9270833333333328, 0.72250724475212036, 3.5458333333333321);
	pos[60] = Vector3(0.84791666666666554, 0.72250724475212047, 3.5458333333333321);
	pos[61] = Vector3(1.3874999999999988, 6.0629972347561578, 2.9291666666666654);
	pos[62] = Vector3(1.3874999999999988, 2.6298250983249907, 3.1714285714285704);
	pos[63] = Vector3(1.3874999999999988, 5.2237773791840949, 3.1714285714285704);
	pos[64] = Vector3(2.5822916666666655, 1.8573613676279781, 3.5458333333333325);
	pos[65] = Vector3(3.2374999999999989, 2.019483385181672, 3.1714285714285708);
	pos[66] = Vector3(0.19270833333333193, 1.8573613676279783, 3.5458333333333325);
	pos[67] = Vector3(0.73229166666666534, 2.7919471158786853, 3.5458333333333325);
	pos[68] = Vector3(3.2374999999999989, 2.8587032407537358, 2.9291666666666654);
	pos[69] = Vector3(0.19270833333333215, 5.9962411098811081, 3.5458333333333321);
	pos[70] = Vector3(0.73229166666666556, 5.0616553616304003, 3.5458333333333325);
	pos[71] = Vector3(0.077083333333332449, 3.926801238754543, 3.5458333333333325);
	pos[72] = Vector3(0.26428571428571335, 4.5752893089693183, 3.1714285714285708);
	pos[73] = Vector3(2.5107142857142848, 3.2783131685397668, 3.1714285714285704);
	pos[74] = Vector3(3.2374999999999989, 4.9948992367553506, 2.9291666666666658);
	pos[75] = Vector3(2.0427083333333322, 5.0616553616304012, 3.5458333333333325);
	pos[76] = Vector3(2.6979166666666656, 3.926801238754543, 3.5458333333333325);
	pos[77] = Vector3(2.5107142857142848, 4.5752893089693192, 3.1714285714285708);
	pos[78] = Vector3(2.582291666666666, 5.9962411098811081, 3.5458333333333325);
	pos[79] = Vector3(3.2374999999999989, 5.8341190923274144, 3.1714285714285708);
}
ddouble getLaplacian(Buffer<int3> &blockDirs, Buffer<int> &valueInds, Buffer<ddouble> &hodges)
{
	blockDirs.resize(INDICES_PER_BLOCK);
	// Dual node idx:  0
	blockDirs[0] = make_int3(0, 0, 0);
	blockDirs[1] = make_int3(0, 0, 0);
	blockDirs[2] = make_int3(0, 0, 0);
	blockDirs[3] = make_int3(-1, -1, 0);
	// Dual node idx:  1
	blockDirs[4] = make_int3(0, 0, -1);
	blockDirs[5] = make_int3(0, 0, 0);
	blockDirs[6] = make_int3(0, 0, 0);
	blockDirs[7] = make_int3(0, -1, 0);
	// Dual node idx:  2
	blockDirs[8] = make_int3(0, 0, -1);
	blockDirs[9] = make_int3(0, 0, 0);
	blockDirs[10] = make_int3(0, 0, 0);
	blockDirs[11] = make_int3(0, 0, 0);
	// Dual node idx:  3
	blockDirs[12] = make_int3(0, 0, 0);
	blockDirs[13] = make_int3(0, 0, 0);
	blockDirs[14] = make_int3(0, 0, 0);
	blockDirs[15] = make_int3(0, 0, 0);
	// Dual node idx:  4
	blockDirs[16] = make_int3(0, 1, 0);
	blockDirs[17] = make_int3(0, 1, 0);
	blockDirs[18] = make_int3(0, 0, 0);
	blockDirs[19] = make_int3(0, 0, 0);
	// Dual node idx:  5
	blockDirs[20] = make_int3(0, 0, 0);
	blockDirs[21] = make_int3(0, -1, 0);
	blockDirs[22] = make_int3(0, -1, 0);
	blockDirs[23] = make_int3(0, 0, 0);
	// Dual node idx:  6
	blockDirs[24] = make_int3(0, 0, 0);
	blockDirs[25] = make_int3(0, 0, 0);
	blockDirs[26] = make_int3(0, 0, 0);
	blockDirs[27] = make_int3(0, 0, 0);
	// Dual node idx:  7
	blockDirs[28] = make_int3(0, 0, 0);
	blockDirs[29] = make_int3(0, 0, 0);
	blockDirs[30] = make_int3(1, 0, 0);
	blockDirs[31] = make_int3(0, 0, 0);
	// Dual node idx:  8
	blockDirs[32] = make_int3(0, 0, 0);
	blockDirs[33] = make_int3(0, 0, 0);
	blockDirs[34] = make_int3(0, 0, 0);
	blockDirs[35] = make_int3(0, 0, 0);
	// Dual node idx:  9
	blockDirs[36] = make_int3(0, 0, 0);
	blockDirs[37] = make_int3(0, 0, 0);
	blockDirs[38] = make_int3(0, 0, 0);
	blockDirs[39] = make_int3(0, 0, 0);
	// Dual node idx:  10
	blockDirs[40] = make_int3(0, 0, 0);
	blockDirs[41] = make_int3(0, 0, 0);
	blockDirs[42] = make_int3(0, 0, 0);
	blockDirs[43] = make_int3(0, 0, 0);
	// Dual node idx:  11
	blockDirs[44] = make_int3(0, 0, 0);
	blockDirs[45] = make_int3(0, 0, 0);
	blockDirs[46] = make_int3(0, 0, 0);
	blockDirs[47] = make_int3(0, 0, 0);
	// Dual node idx:  12
	blockDirs[48] = make_int3(0, 0, 0);
	blockDirs[49] = make_int3(-1, 0, 0);
	blockDirs[50] = make_int3(0, 0, 0);
	blockDirs[51] = make_int3(0, 0, 0);
	// Dual node idx:  13
	blockDirs[52] = make_int3(0, 0, 0);
	blockDirs[53] = make_int3(0, 0, 0);
	blockDirs[54] = make_int3(0, 0, 0);
	blockDirs[55] = make_int3(0, 0, 0);
	// Dual node idx:  14
	blockDirs[56] = make_int3(0, 0, 0);
	blockDirs[57] = make_int3(0, 0, 0);
	blockDirs[58] = make_int3(0, 0, 0);
	blockDirs[59] = make_int3(0, 0, 0);
	// Dual node idx:  15
	blockDirs[60] = make_int3(0, 0, 0);
	blockDirs[61] = make_int3(0, 0, 0);
	blockDirs[62] = make_int3(0, 0, 0);
	blockDirs[63] = make_int3(0, 0, 0);
	// Dual node idx:  16
	blockDirs[64] = make_int3(0, 0, 0);
	blockDirs[65] = make_int3(0, 0, 0);
	blockDirs[66] = make_int3(1, 1, 0);
	blockDirs[67] = make_int3(0, 1, 0);
	// Dual node idx:  17
	blockDirs[68] = make_int3(0, 0, 0);
	blockDirs[69] = make_int3(0, 0, 0);
	blockDirs[70] = make_int3(0, 0, 0);
	blockDirs[71] = make_int3(0, 0, 0);
	// Dual node idx:  18
	blockDirs[72] = make_int3(0, 0, 0);
	blockDirs[73] = make_int3(0, 0, 0);
	blockDirs[74] = make_int3(0, 0, 0);
	blockDirs[75] = make_int3(0, 0, 0);
	// Dual node idx:  19
	blockDirs[76] = make_int3(0, 0, 0);
	blockDirs[77] = make_int3(1, 0, 0);
	blockDirs[78] = make_int3(0, 0, 0);
	blockDirs[79] = make_int3(0, 0, 0);
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
	blockDirs[88] = make_int3(0, 0, 0);
	blockDirs[89] = make_int3(0, -1, 0);
	blockDirs[90] = make_int3(0, 0, 0);
	blockDirs[91] = make_int3(0, -1, 0);
	// Dual node idx:  23
	blockDirs[92] = make_int3(0, 0, -1);
	blockDirs[93] = make_int3(0, 0, 0);
	blockDirs[94] = make_int3(0, 0, 0);
	blockDirs[95] = make_int3(0, 0, 0);
	// Dual node idx:  24
	blockDirs[96] = make_int3(0, 0, 0);
	blockDirs[97] = make_int3(0, 0, 0);
	blockDirs[98] = make_int3(0, 0, 0);
	blockDirs[99] = make_int3(0, 0, 0);
	// Dual node idx:  25
	blockDirs[100] = make_int3(0, 0, 0);
	blockDirs[101] = make_int3(-1, 0, 0);
	blockDirs[102] = make_int3(0, 0, 0);
	blockDirs[103] = make_int3(0, 0, 0);
	// Dual node idx:  26
	blockDirs[104] = make_int3(1, 0, 0);
	blockDirs[105] = make_int3(0, 0, 0);
	blockDirs[106] = make_int3(0, 0, 0);
	blockDirs[107] = make_int3(0, 0, 0);
	// Dual node idx:  27
	blockDirs[108] = make_int3(0, 0, 0);
	blockDirs[109] = make_int3(0, 0, 0);
	blockDirs[110] = make_int3(-1, 0, 0);
	blockDirs[111] = make_int3(0, 0, 0);
	// Dual node idx:  28
	blockDirs[112] = make_int3(0, 0, 0);
	blockDirs[113] = make_int3(0, 0, 0);
	blockDirs[114] = make_int3(0, 0, 0);
	blockDirs[115] = make_int3(0, 0, 0);
	// Dual node idx:  29
	blockDirs[116] = make_int3(0, 0, -1);
	blockDirs[117] = make_int3(0, 0, 0);
	blockDirs[118] = make_int3(0, 0, 0);
	blockDirs[119] = make_int3(0, -1, 0);
	// Dual node idx:  30
	blockDirs[120] = make_int3(0, 0, 0);
	blockDirs[121] = make_int3(0, -1, 0);
	blockDirs[122] = make_int3(0, 0, 0);
	blockDirs[123] = make_int3(0, -1, 0);
	// Dual node idx:  31
	blockDirs[124] = make_int3(0, 0, 0);
	blockDirs[125] = make_int3(0, 0, 0);
	blockDirs[126] = make_int3(0, 0, 0);
	blockDirs[127] = make_int3(0, 0, 0);
	// Dual node idx:  32
	blockDirs[128] = make_int3(0, 0, 0);
	blockDirs[129] = make_int3(0, 0, 0);
	blockDirs[130] = make_int3(0, 0, 0);
	blockDirs[131] = make_int3(0, 0, 0);
	// Dual node idx:  33
	blockDirs[132] = make_int3(0, 0, 0);
	blockDirs[133] = make_int3(0, 0, 0);
	blockDirs[134] = make_int3(0, 0, 0);
	blockDirs[135] = make_int3(-1, 0, 0);
	// Dual node idx:  34
	blockDirs[136] = make_int3(0, 0, 0);
	blockDirs[137] = make_int3(0, 0, 0);
	blockDirs[138] = make_int3(0, 0, 0);
	blockDirs[139] = make_int3(0, 0, 0);
	// Dual node idx:  35
	blockDirs[140] = make_int3(0, 0, 0);
	blockDirs[141] = make_int3(-1, 0, 0);
	blockDirs[142] = make_int3(0, 0, 0);
	blockDirs[143] = make_int3(0, 0, 0);
	// Dual node idx:  36
	blockDirs[144] = make_int3(0, 0, -1);
	blockDirs[145] = make_int3(0, 0, 0);
	blockDirs[146] = make_int3(-1, 0, 0);
	blockDirs[147] = make_int3(0, 0, 0);
	// Dual node idx:  37
	blockDirs[148] = make_int3(0, 0, 0);
	blockDirs[149] = make_int3(0, 0, 0);
	blockDirs[150] = make_int3(-1, 0, 0);
	blockDirs[151] = make_int3(0, 1, 0);
	// Dual node idx:  38
	blockDirs[152] = make_int3(0, 0, 0);
	blockDirs[153] = make_int3(0, 0, 0);
	blockDirs[154] = make_int3(0, 0, 0);
	blockDirs[155] = make_int3(0, 0, 0);
	// Dual node idx:  39
	blockDirs[156] = make_int3(0, 0, 0);
	blockDirs[157] = make_int3(-1, 0, 0);
	blockDirs[158] = make_int3(0, 0, 0);
	blockDirs[159] = make_int3(0, 0, 0);
	// Dual node idx:  40
	blockDirs[160] = make_int3(0, 0, -1);
	blockDirs[161] = make_int3(0, 0, 0);
	blockDirs[162] = make_int3(0, 0, 0);
	blockDirs[163] = make_int3(0, 0, 0);
	// Dual node idx:  41
	blockDirs[164] = make_int3(0, 0, -1);
	blockDirs[165] = make_int3(0, 0, 0);
	blockDirs[166] = make_int3(0, 0, 0);
	blockDirs[167] = make_int3(0, 0, 0);
	// Dual node idx:  42
	blockDirs[168] = make_int3(0, 0, -1);
	blockDirs[169] = make_int3(0, 0, 0);
	blockDirs[170] = make_int3(-1, 0, 0);
	blockDirs[171] = make_int3(0, 1, 0);
	// Dual node idx:  43
	blockDirs[172] = make_int3(0, 0, 0);
	blockDirs[173] = make_int3(0, -1, 0);
	blockDirs[174] = make_int3(0, -1, 0);
	blockDirs[175] = make_int3(0, 0, 0);
	// Dual node idx:  44
	blockDirs[176] = make_int3(0, 0, 0);
	blockDirs[177] = make_int3(0, 0, 0);
	blockDirs[178] = make_int3(0, 0, 0);
	blockDirs[179] = make_int3(0, 0, 0);
	// Dual node idx:  45
	blockDirs[180] = make_int3(0, 0, 0);
	blockDirs[181] = make_int3(0, 0, 0);
	blockDirs[182] = make_int3(0, 0, 0);
	blockDirs[183] = make_int3(0, -1, 0);
	// Dual node idx:  46
	blockDirs[184] = make_int3(0, 0, 0);
	blockDirs[185] = make_int3(0, 0, 0);
	blockDirs[186] = make_int3(0, 0, 0);
	blockDirs[187] = make_int3(0, 0, 0);
	// Dual node idx:  47
	blockDirs[188] = make_int3(0, 0, 0);
	blockDirs[189] = make_int3(1, 0, 0);
	blockDirs[190] = make_int3(0, 0, 0);
	blockDirs[191] = make_int3(0, 0, 0);
	// Dual node idx:  48
	blockDirs[192] = make_int3(0, 0, 0);
	blockDirs[193] = make_int3(0, 0, 0);
	blockDirs[194] = make_int3(0, 0, 0);
	blockDirs[195] = make_int3(0, 0, 0);
	// Dual node idx:  49
	blockDirs[196] = make_int3(0, 0, -1);
	blockDirs[197] = make_int3(0, 0, 0);
	blockDirs[198] = make_int3(1, 0, 0);
	blockDirs[199] = make_int3(0, 0, 0);
	// Dual node idx:  50
	blockDirs[200] = make_int3(0, 0, 0);
	blockDirs[201] = make_int3(1, 0, 0);
	blockDirs[202] = make_int3(0, 0, 0);
	blockDirs[203] = make_int3(0, 0, 0);
	// Dual node idx:  51
	blockDirs[204] = make_int3(1, 0, 0);
	blockDirs[205] = make_int3(0, 0, 0);
	blockDirs[206] = make_int3(0, 0, 0);
	blockDirs[207] = make_int3(0, 0, 0);
	// Dual node idx:  52
	blockDirs[208] = make_int3(0, 0, 0);
	blockDirs[209] = make_int3(0, 0, 0);
	blockDirs[210] = make_int3(0, 0, 0);
	blockDirs[211] = make_int3(0, 0, 0);
	// Dual node idx:  53
	blockDirs[212] = make_int3(0, 0, 0);
	blockDirs[213] = make_int3(0, 0, 0);
	blockDirs[214] = make_int3(0, 0, 0);
	blockDirs[215] = make_int3(0, 1, 0);
	// Dual node idx:  54
	blockDirs[216] = make_int3(0, 0, -1);
	blockDirs[217] = make_int3(0, 0, 0);
	blockDirs[218] = make_int3(0, 0, 0);
	blockDirs[219] = make_int3(0, 0, 0);
	// Dual node idx:  55
	blockDirs[220] = make_int3(0, 0, -1);
	blockDirs[221] = make_int3(0, 0, 0);
	blockDirs[222] = make_int3(0, 0, 0);
	blockDirs[223] = make_int3(0, 0, 0);
	// Dual node idx:  56
	blockDirs[224] = make_int3(0, 0, -1);
	blockDirs[225] = make_int3(0, 0, 0);
	blockDirs[226] = make_int3(1, 0, 0);
	blockDirs[227] = make_int3(0, 1, 0);
	// Dual node idx:  57
	blockDirs[228] = make_int3(0, 0, 1);
	blockDirs[229] = make_int3(0, 0, 0);
	blockDirs[230] = make_int3(0, 0, 0);
	blockDirs[231] = make_int3(0, 0, 0);
	// Dual node idx:  58
	blockDirs[232] = make_int3(0, 0, 0);
	blockDirs[233] = make_int3(0, 0, 0);
	blockDirs[234] = make_int3(0, 0, 0);
	blockDirs[235] = make_int3(0, 0, 0);
	// Dual node idx:  59
	blockDirs[236] = make_int3(0, 0, 1);
	blockDirs[237] = make_int3(0, 0, 0);
	blockDirs[238] = make_int3(0, 0, 0);
	blockDirs[239] = make_int3(0, 0, 0);
	// Dual node idx:  60
	blockDirs[240] = make_int3(0, 0, 1);
	blockDirs[241] = make_int3(0, 0, 0);
	blockDirs[242] = make_int3(0, 0, 0);
	blockDirs[243] = make_int3(0, 0, 0);
	// Dual node idx:  61
	blockDirs[244] = make_int3(0, 1, 0);
	blockDirs[245] = make_int3(0, 1, 0);
	blockDirs[246] = make_int3(0, 0, 0);
	blockDirs[247] = make_int3(0, 0, 0);
	// Dual node idx:  62
	blockDirs[248] = make_int3(0, 0, 0);
	blockDirs[249] = make_int3(0, 0, 0);
	blockDirs[250] = make_int3(0, 0, 0);
	blockDirs[251] = make_int3(0, 0, 0);
	// Dual node idx:  63
	blockDirs[252] = make_int3(0, 0, 0);
	blockDirs[253] = make_int3(0, 0, 0);
	blockDirs[254] = make_int3(0, 0, 0);
	blockDirs[255] = make_int3(0, 0, 0);
	// Dual node idx:  64
	blockDirs[256] = make_int3(0, 0, 1);
	blockDirs[257] = make_int3(0, 0, 0);
	blockDirs[258] = make_int3(0, 0, 0);
	blockDirs[259] = make_int3(0, 0, 0);
	// Dual node idx:  65
	blockDirs[260] = make_int3(1, 0, 0);
	blockDirs[261] = make_int3(0, 0, 0);
	blockDirs[262] = make_int3(0, 0, 0);
	blockDirs[263] = make_int3(0, 0, 0);
	// Dual node idx:  66
	blockDirs[264] = make_int3(0, 0, 1);
	blockDirs[265] = make_int3(0, 0, 0);
	blockDirs[266] = make_int3(-1, 0, 0);
	blockDirs[267] = make_int3(0, 0, 0);
	// Dual node idx:  67
	blockDirs[268] = make_int3(0, 0, 1);
	blockDirs[269] = make_int3(0, 0, 0);
	blockDirs[270] = make_int3(0, 0, 0);
	blockDirs[271] = make_int3(0, 0, 0);
	// Dual node idx:  68
	blockDirs[272] = make_int3(0, 0, 0);
	blockDirs[273] = make_int3(1, 0, 0);
	blockDirs[274] = make_int3(0, 0, 0);
	blockDirs[275] = make_int3(0, 0, 0);
	// Dual node idx:  69
	blockDirs[276] = make_int3(0, 0, 1);
	blockDirs[277] = make_int3(0, 0, 0);
	blockDirs[278] = make_int3(-1, 0, 0);
	blockDirs[279] = make_int3(0, 1, 0);
	// Dual node idx:  70
	blockDirs[280] = make_int3(0, 0, 1);
	blockDirs[281] = make_int3(0, 0, 0);
	blockDirs[282] = make_int3(0, 0, 0);
	blockDirs[283] = make_int3(0, 0, 0);
	// Dual node idx:  71
	blockDirs[284] = make_int3(0, 0, 1);
	blockDirs[285] = make_int3(-1, 0, 0);
	blockDirs[286] = make_int3(0, 0, 0);
	blockDirs[287] = make_int3(0, 0, 0);
	// Dual node idx:  72
	blockDirs[288] = make_int3(0, 0, 0);
	blockDirs[289] = make_int3(-1, 0, 0);
	blockDirs[290] = make_int3(0, 0, 0);
	blockDirs[291] = make_int3(0, 0, 0);
	// Dual node idx:  73
	blockDirs[292] = make_int3(0, 0, 0);
	blockDirs[293] = make_int3(0, 0, 0);
	blockDirs[294] = make_int3(0, 0, 0);
	blockDirs[295] = make_int3(0, 0, 0);
	// Dual node idx:  74
	blockDirs[296] = make_int3(0, 0, 0);
	blockDirs[297] = make_int3(1, 0, 0);
	blockDirs[298] = make_int3(0, 0, 0);
	blockDirs[299] = make_int3(0, 0, 0);
	// Dual node idx:  75
	blockDirs[300] = make_int3(0, 0, 1);
	blockDirs[301] = make_int3(0, 0, 0);
	blockDirs[302] = make_int3(0, 0, 0);
	blockDirs[303] = make_int3(0, 0, 0);
	// Dual node idx:  76
	blockDirs[304] = make_int3(0, 0, 1);
	blockDirs[305] = make_int3(1, 0, 0);
	blockDirs[306] = make_int3(0, 0, 0);
	blockDirs[307] = make_int3(0, 0, 0);
	// Dual node idx:  77
	blockDirs[308] = make_int3(0, 0, 0);
	blockDirs[309] = make_int3(0, 0, 0);
	blockDirs[310] = make_int3(0, 0, 0);
	blockDirs[311] = make_int3(0, 0, 0);
	// Dual node idx:  78
	blockDirs[312] = make_int3(0, 0, 1);
	blockDirs[313] = make_int3(0, 0, 0);
	blockDirs[314] = make_int3(0, 0, 0);
	blockDirs[315] = make_int3(0, 1, 0);
	// Dual node idx:  79
	blockDirs[316] = make_int3(1, 0, 0);
	blockDirs[317] = make_int3(0, 0, 0);
	blockDirs[318] = make_int3(0, 0, 0);
	blockDirs[319] = make_int3(0, 0, 0);

	valueInds.resize(INDICES_PER_BLOCK);
	// Dual node idx:  0
	valueInds[0] = 22;
	valueInds[1] = 43;
	valueInds[2] = 33;
	valueInds[3] = 16;
	// Dual node idx:  1
	valueInds[4] = 60;
	valueInds[5] = 28;
	valueInds[6] = 36;
	valueInds[7] = 42;
	// Dual node idx:  2
	valueInds[8] = 57;
	valueInds[9] = 31;
	valueInds[10] = 54;
	valueInds[11] = 23;
	// Dual node idx:  3
	valueInds[12] = 60;
	valueInds[13] = 17;
	valueInds[14] = 66;
	valueInds[15] = 33;
	// Dual node idx:  4
	valueInds[16] = 22;
	valueInds[17] = 30;
	valueInds[18] = 61;
	valueInds[19] = 24;
	// Dual node idx:  5
	valueInds[20] = 59;
	valueInds[21] = 61;
	valueInds[22] = 78;
	valueInds[23] = 45;
	// Dual node idx:  6
	valueInds[24] = 52;
	valueInds[25] = 77;
	valueInds[26] = 32;
	valueInds[27] = 13;
	// Dual node idx:  7
	valueInds[28] = 26;
	valueInds[29] = 65;
	valueInds[30] = 33;
	valueInds[31] = 44;
	// Dual node idx:  8
	valueInds[32] = 31;
	valueInds[33] = 18;
	valueInds[34] = 10;
	valueInds[35] = 11;
	// Dual node idx:  9
	valueInds[36] = 28;
	valueInds[37] = 18;
	valueInds[38] = 33;
	valueInds[39] = 27;
	// Dual node idx:  10
	valueInds[40] = 23;
	valueInds[41] = 27;
	valueInds[42] = 25;
	valueInds[43] = 8;
	// Dual node idx:  11
	valueInds[44] = 8;
	valueInds[45] = 62;
	valueInds[46] = 32;
	valueInds[47] = 21;
	// Dual node idx:  12
	valueInds[48] = 71;
	valueInds[49] = 68;
	valueInds[50] = 67;
	valueInds[51] = 21;
	// Dual node idx:  13
	valueInds[52] = 24;
	valueInds[53] = 63;
	valueInds[54] = 6;
	valueInds[55] = 15;
	// Dual node idx:  14
	valueInds[56] = 49;
	valueInds[57] = 31;
	valueInds[58] = 26;
	valueInds[59] = 20;
	// Dual node idx:  15
	valueInds[60] = 35;
	valueInds[61] = 72;
	valueInds[62] = 21;
	valueInds[63] = 13;
	// Dual node idx:  16
	valueInds[64] = 51;
	valueInds[65] = 79;
	valueInds[66] = 0;
	valueInds[67] = 45;
	// Dual node idx:  17
	valueInds[68] = 3;
	valueInds[69] = 58;
	valueInds[70] = 62;
	valueInds[71] = 18;
	// Dual node idx:  18
	valueInds[72] = 9;
	valueInds[73] = 20;
	valueInds[74] = 17;
	valueInds[75] = 8;
	// Dual node idx:  19
	valueInds[76] = 46;
	valueInds[77] = 25;
	valueInds[78] = 26;
	valueInds[79] = 68;
	// Dual node idx:  20
	valueInds[80] = 34;
	valueInds[81] = 18;
	valueInds[82] = 44;
	valueInds[83] = 14;
	// Dual node idx:  21
	valueInds[84] = 25;
	valueInds[85] = 12;
	valueInds[86] = 15;
	valueInds[87] = 11;
	// Dual node idx:  22
	valueInds[88] = 28;
	valueInds[89] = 4;
	valueInds[90] = 0;
	valueInds[91] = 37;
	// Dual node idx:  23
	valueInds[92] = 67;
	valueInds[93] = 10;
	valueInds[94] = 40;
	valueInds[95] = 2;
	// Dual node idx:  24
	valueInds[96] = 48;
	valueInds[97] = 4;
	valueInds[98] = 38;
	valueInds[99] = 13;
	// Dual node idx:  25
	valueInds[100] = 39;
	valueInds[101] = 19;
	valueInds[102] = 10;
	valueInds[103] = 21;
	// Dual node idx:  26
	valueInds[104] = 27;
	valueInds[105] = 19;
	valueInds[106] = 14;
	valueInds[107] = 7;
	// Dual node idx:  27
	valueInds[108] = 36;
	valueInds[109] = 10;
	valueInds[110] = 26;
	valueInds[111] = 9;
	// Dual node idx:  28
	valueInds[112] = 9;
	valueInds[113] = 34;
	valueInds[114] = 22;
	valueInds[115] = 1;
	// Dual node idx:  29
	valueInds[116] = 59;
	valueInds[117] = 34;
	valueInds[118] = 49;
	valueInds[119] = 56;
	// Dual node idx:  30
	valueInds[120] = 34;
	valueInds[121] = 4;
	valueInds[122] = 45;
	valueInds[123] = 53;
	// Dual node idx:  31
	valueInds[124] = 2;
	valueInds[125] = 14;
	valueInds[126] = 46;
	valueInds[127] = 8;
	// Dual node idx:  32
	valueInds[128] = 46;
	valueInds[129] = 73;
	valueInds[130] = 6;
	valueInds[131] = 11;
	// Dual node idx:  33
	valueInds[132] = 9;
	valueInds[133] = 3;
	valueInds[134] = 0;
	valueInds[135] = 7;
	// Dual node idx:  34
	valueInds[136] = 20;
	valueInds[137] = 28;
	valueInds[138] = 30;
	valueInds[139] = 29;
	// Dual node idx:  35
	valueInds[140] = 39;
	valueInds[141] = 47;
	valueInds[142] = 38;
	valueInds[143] = 15;
	// Dual node idx:  36
	valueInds[144] = 66;
	valueInds[145] = 27;
	valueInds[146] = 49;
	valueInds[147] = 1;
	// Dual node idx:  37
	valueInds[148] = 42;
	valueInds[149] = 38;
	valueInds[150] = 51;
	valueInds[151] = 22;
	// Dual node idx:  38
	valueInds[152] = 41;
	valueInds[153] = 37;
	valueInds[154] = 35;
	valueInds[155] = 24;
	// Dual node idx:  39
	valueInds[156] = 40;
	valueInds[157] = 50;
	valueInds[158] = 35;
	valueInds[159] = 25;
	// Dual node idx:  40
	valueInds[160] = 71;
	valueInds[161] = 39;
	valueInds[162] = 41;
	valueInds[163] = 23;
	// Dual node idx:  41
	valueInds[164] = 70;
	valueInds[165] = 38;
	valueInds[166] = 40;
	valueInds[167] = 55;
	// Dual node idx:  42
	valueInds[168] = 69;
	valueInds[169] = 37;
	valueInds[170] = 56;
	valueInds[171] = 1;
	// Dual node idx:  43
	valueInds[172] = 60;
	valueInds[173] = 61;
	valueInds[174] = 69;
	valueInds[175] = 0;
	// Dual node idx:  44
	valueInds[176] = 20;
	valueInds[177] = 58;
	valueInds[178] = 45;
	valueInds[179] = 7;
	// Dual node idx:  45
	valueInds[180] = 30;
	valueInds[181] = 5;
	valueInds[182] = 44;
	valueInds[183] = 16;
	// Dual node idx:  46
	valueInds[184] = 50;
	valueInds[185] = 19;
	valueInds[186] = 31;
	valueInds[187] = 32;
	// Dual node idx:  47
	valueInds[188] = 52;
	valueInds[189] = 35;
	valueInds[190] = 51;
	valueInds[191] = 74;
	// Dual node idx:  48
	valueInds[192] = 55;
	valueInds[193] = 53;
	valueInds[194] = 52;
	valueInds[195] = 24;
	// Dual node idx:  49
	valueInds[196] = 64;
	valueInds[197] = 14;
	valueInds[198] = 36;
	valueInds[199] = 29;
	// Dual node idx:  50
	valueInds[200] = 54;
	valueInds[201] = 39;
	valueInds[202] = 52;
	valueInds[203] = 46;
	// Dual node idx:  51
	valueInds[204] = 37;
	valueInds[205] = 47;
	valueInds[206] = 53;
	valueInds[207] = 16;
	// Dual node idx:  52
	valueInds[208] = 50;
	valueInds[209] = 47;
	valueInds[210] = 48;
	valueInds[211] = 6;
	// Dual node idx:  53
	valueInds[212] = 56;
	valueInds[213] = 48;
	valueInds[214] = 51;
	valueInds[215] = 30;
	// Dual node idx:  54
	valueInds[216] = 76;
	valueInds[217] = 50;
	valueInds[218] = 55;
	valueInds[219] = 2;
	// Dual node idx:  55
	valueInds[220] = 75;
	valueInds[221] = 48;
	valueInds[222] = 54;
	valueInds[223] = 41;
	// Dual node idx:  56
	valueInds[224] = 78;
	valueInds[225] = 53;
	valueInds[226] = 42;
	valueInds[227] = 29;
	// Dual node idx:  57
	valueInds[228] = 2;
	valueInds[229] = 64;
	valueInds[230] = 73;
	valueInds[231] = 62;
	// Dual node idx:  58
	valueInds[232] = 59;
	valueInds[233] = 17;
	valueInds[234] = 64;
	valueInds[235] = 44;
	// Dual node idx:  59
	valueInds[236] = 29;
	valueInds[237] = 60;
	valueInds[238] = 58;
	valueInds[239] = 5;
	// Dual node idx:  60
	valueInds[240] = 1;
	valueInds[241] = 59;
	valueInds[242] = 3;
	valueInds[243] = 43;
	// Dual node idx:  61
	valueInds[244] = 43;
	valueInds[245] = 5;
	valueInds[246] = 63;
	valueInds[247] = 4;
	// Dual node idx:  62
	valueInds[248] = 57;
	valueInds[249] = 17;
	valueInds[250] = 67;
	valueInds[251] = 11;
	// Dual node idx:  63
	valueInds[252] = 75;
	valueInds[253] = 61;
	valueInds[254] = 70;
	valueInds[255] = 13;
	// Dual node idx:  64
	valueInds[256] = 49;
	valueInds[257] = 57;
	valueInds[258] = 65;
	valueInds[259] = 58;
	// Dual node idx:  65
	valueInds[260] = 66;
	valueInds[261] = 68;
	valueInds[262] = 64;
	valueInds[263] = 7;
	// Dual node idx:  66
	valueInds[264] = 36;
	valueInds[265] = 67;
	valueInds[266] = 65;
	valueInds[267] = 3;
	// Dual node idx:  67
	valueInds[268] = 23;
	valueInds[269] = 66;
	valueInds[270] = 12;
	valueInds[271] = 62;
	// Dual node idx:  68
	valueInds[272] = 73;
	valueInds[273] = 12;
	valueInds[274] = 65;
	valueInds[275] = 19;
	// Dual node idx:  69
	valueInds[276] = 42;
	valueInds[277] = 70;
	valueInds[278] = 79;
	valueInds[279] = 43;
	// Dual node idx:  70
	valueInds[280] = 41;
	valueInds[281] = 69;
	valueInds[282] = 72;
	valueInds[283] = 63;
	// Dual node idx:  71
	valueInds[284] = 40;
	valueInds[285] = 76;
	valueInds[286] = 72;
	valueInds[287] = 12;
	// Dual node idx:  72
	valueInds[288] = 71;
	valueInds[289] = 74;
	valueInds[290] = 70;
	valueInds[291] = 15;
	// Dual node idx:  73
	valueInds[292] = 76;
	valueInds[293] = 68;
	valueInds[294] = 57;
	valueInds[295] = 32;
	// Dual node idx:  74
	valueInds[296] = 77;
	valueInds[297] = 72;
	valueInds[298] = 79;
	valueInds[299] = 47;
	// Dual node idx:  75
	valueInds[300] = 55;
	valueInds[301] = 78;
	valueInds[302] = 77;
	valueInds[303] = 63;
	// Dual node idx:  76
	valueInds[304] = 54;
	valueInds[305] = 71;
	valueInds[306] = 77;
	valueInds[307] = 73;
	// Dual node idx:  77
	valueInds[308] = 76;
	valueInds[309] = 74;
	valueInds[310] = 75;
	valueInds[311] = 6;
	// Dual node idx:  78
	valueInds[312] = 56;
	valueInds[313] = 75;
	valueInds[314] = 79;
	valueInds[315] = 5;
	// Dual node idx:  79
	valueInds[316] = 69;
	valueInds[317] = 74;
	valueInds[318] = 78;
	valueInds[319] = 16;

	hodges.resize(INDICES_PER_BLOCK);
	hodges[0] = 1.8879586447154018;
	hodges[1] = 1.8879586447154024;
	hodges[2] = 2.3374726077428769;
	hodges[3] = 2.3374726077428774;
	hodges[4] = 2.6296566837107358;
	hodges[5] = 2.6296566837107362;
	hodges[6] = 1.6182502668989163;
	hodges[7] = 1.6182502668989156;
	hodges[8] = 2.6296566837107362;
	hodges[9] = 2.6296566837107385;
	hodges[10] = 1.6182502668989163;
	hodges[11] = 1.6182502668989152;
	hodges[12] = 2.4749709964336359;
	hodges[13] = 1.912477588153265;
	hodges[14] = 2.4749709964336346;
	hodges[15] = 1.6182502668989172;
	hodges[16] = 2.2312238528454751;
	hodges[17] = 2.2312238528454729;
	hodges[18] = 1.314828341855369;
	hodges[19] = 2.2312238528454755;
	hodges[20] = 2.4749709964336359;
	hodges[21] = 1.9124775881532621;
	hodges[22] = 2.4749709964336351;
	hodges[23] = 1.618250266898916;
	hodges[24] = 1.8879586447154018;
	hodges[25] = 1.8879586447154018;
	hodges[26] = 2.3374726077428778;
	hodges[27] = 2.3374726077428791;
	hodges[28] = 1.8879586447154018;
	hodges[29] = 1.8879586447154018;
	hodges[30] = 2.3374726077428778;
	hodges[31] = 2.3374726077428791;
	hodges[32] = 2.4749709964336337;
	hodges[33] = 1.9124775881532656;
	hodges[34] = 2.4749709964336346;
	hodges[35] = 1.6182502668989154;
	hodges[36] = 2.4749709964336359;
	hodges[37] = 1.9124775881532656;
	hodges[38] = 1.6182502668989152;
	hodges[39] = 2.4749709964336359;
	hodges[40] = 2.6296566837107398;
	hodges[41] = 1.5026609621204214;
	hodges[42] = 2.1655996218794313;
	hodges[43] = 2.16559962187943;
	hodges[44] = 1.887958644715402;
	hodges[45] = 1.8879586447154024;
	hodges[46] = 2.337472607742876;
	hodges[47] = 2.3374726077428778;
	hodges[48] = 2.4749709964336373;
	hodges[49] = 1.9124775881532636;
	hodges[50] = 2.4749709964336364;
	hodges[51] = 1.6182502668989156;
	hodges[52] = 1.8879586447154015;
	hodges[53] = 1.8879586447154024;
	hodges[54] = 2.3374726077428782;
	hodges[55] = 2.3374726077428778;
	hodges[56] = 2.629656683710738;
	hodges[57] = 1.5026609621204219;
	hodges[58] = 2.16559962187943;
	hodges[59] = 2.1655996218794322;
	hodges[60] = 1.8879586447154009;
	hodges[61] = 1.8879586447154015;
	hodges[62] = 2.3374726077428818;
	hodges[63] = 2.3374726077428778;
	hodges[64] = 1.8879586447154018;
	hodges[65] = 1.8879586447154024;
	hodges[66] = 2.3374726077428778;
	hodges[67] = 2.3374726077428787;
	hodges[68] = 2.2312238528454751;
	hodges[69] = 2.2312238528454733;
	hodges[70] = 2.2312238528454751;
	hodges[71] = 1.3148283418553692;
	hodges[72] = 2.2312238528454755;
	hodges[73] = 2.2312238528454738;
	hodges[74] = 1.3148283418553686;
	hodges[75] = 2.2312238528454755;
	hodges[76] = 2.2312238528454773;
	hodges[77] = 2.2312238528454746;
	hodges[78] = 2.2312238528454751;
	hodges[79] = 1.3148283418553688;
	hodges[80] = 2.4749709964336368;
	hodges[81] = 1.9124775881532625;
	hodges[82] = 1.6182502668989147;
	hodges[83] = 2.4749709964336359;
	hodges[84] = 1.8879586447154018;
	hodges[85] = 1.8879586447154018;
	hodges[86] = 2.3374726077428822;
	hodges[87] = 2.3374726077428769;
	hodges[88] = 2.4749709964336346;
	hodges[89] = 1.9124775881532654;
	hodges[90] = 1.6182502668989156;
	hodges[91] = 2.4749709964336368;
	hodges[92] = 2.6296566837107367;
	hodges[93] = 2.6296566837107389;
	hodges[94] = 1.6182502668989167;
	hodges[95] = 1.6182502668989145;
	hodges[96] = 2.4749709964336337;
	hodges[97] = 1.9124775881532645;
	hodges[98] = 2.4749709964336346;
	hodges[99] = 1.6182502668989149;
	hodges[100] = 2.4749709964336382;
	hodges[101] = 1.9124775881532645;
	hodges[102] = 2.4749709964336359;
	hodges[103] = 1.6182502668989154;
	hodges[104] = 2.4749709964336364;
	hodges[105] = 1.9124775881532641;
	hodges[106] = 2.4749709964336359;
	hodges[107] = 1.6182502668989152;
	hodges[108] = 2.629656683710738;
	hodges[109] = 1.5026609621204214;
	hodges[110] = 2.1655996218794313;
	hodges[111] = 2.1655996218794313;
	hodges[112] = 2.1655996218794322;
	hodges[113] = 1.5026609621204221;
	hodges[114] = 2.1655996218794304;
	hodges[115] = 2.6296566837107371;
	hodges[116] = 2.6296566837107354;
	hodges[117] = 2.6296566837107358;
	hodges[118] = 1.6182502668989169;
	hodges[119] = 1.6182502668989163;
	hodges[120] = 2.4749709964336346;
	hodges[121] = 1.9124775881532625;
	hodges[122] = 1.6182502668989147;
	hodges[123] = 2.4749709964336359;
	hodges[124] = 2.6296566837107385;
	hodges[125] = 1.5026609621204225;
	hodges[126] = 2.1655996218794304;
	hodges[127] = 2.1655996218794296;
	hodges[128] = 1.887958644715402;
	hodges[129] = 1.8879586447154031;
	hodges[130] = 2.3374726077428787;
	hodges[131] = 2.3374726077428774;
	hodges[132] = 1.8879586447154013;
	hodges[133] = 1.8879586447154031;
	hodges[134] = 2.3374726077428769;
	hodges[135] = 2.3374726077428778;
	hodges[136] = 2.1655996218794331;
	hodges[137] = 1.5026609621204208;
	hodges[138] = 2.1655996218794309;
	hodges[139] = 2.6296566837107362;
	hodges[140] = 2.4749709964336395;
	hodges[141] = 1.9124775881532621;
	hodges[142] = 2.4749709964336364;
	hodges[143] = 1.6182502668989147;
	hodges[144] = 2.6296566837107362;
	hodges[145] = 2.6296566837107376;
	hodges[146] = 1.6182502668989163;
	hodges[147] = 1.6182502668989156;
	hodges[148] = 2.629656683710738;
	hodges[149] = 1.5026609621204208;
	hodges[150] = 2.1655996218794309;
	hodges[151] = 2.1655996218794336;
	hodges[152] = 2.6296566837107407;
	hodges[153] = 1.5026609621204197;
	hodges[154] = 2.1655996218794313;
	hodges[155] = 2.16559962187943;
	hodges[156] = 2.629656683710738;
	hodges[157] = 1.5026609621204208;
	hodges[158] = 2.165599621879434;
	hodges[159] = 2.1655996218794322;
	hodges[160] = 2.6296566837107367;
	hodges[161] = 2.6296566837107376;
	hodges[162] = 1.6182502668989165;
	hodges[163] = 1.6182502668989163;
	hodges[164] = 2.6296566837107398;
	hodges[165] = 2.6296566837107398;
	hodges[166] = 1.6182502668989163;
	hodges[167] = 1.6182502668989147;
	hodges[168] = 2.6296566837107358;
	hodges[169] = 2.6296566837107371;
	hodges[170] = 1.6182502668989156;
	hodges[171] = 1.6182502668989163;
	hodges[172] = 2.4749709964336342;
	hodges[173] = 1.9124775881532645;
	hodges[174] = 2.4749709964336368;
	hodges[175] = 1.6182502668989165;
	hodges[176] = 1.8879586447154013;
	hodges[177] = 1.8879586447154013;
	hodges[178] = 2.3374726077428791;
	hodges[179] = 2.3374726077428769;
	hodges[180] = 1.8879586447154013;
	hodges[181] = 1.8879586447154022;
	hodges[182] = 2.3374726077428791;
	hodges[183] = 2.3374726077428769;
	hodges[184] = 2.4749709964336364;
	hodges[185] = 1.9124775881532667;
	hodges[186] = 2.4749709964336355;
	hodges[187] = 1.6182502668989154;
	hodges[188] = 2.2312238528454755;
	hodges[189] = 2.2312238528454729;
	hodges[190] = 2.2312238528454755;
	hodges[191] = 1.3148283418553683;
	hodges[192] = 2.6296566837107389;
	hodges[193] = 1.5026609621204217;
	hodges[194] = 2.1655996218794313;
	hodges[195] = 2.16559962187943;
	hodges[196] = 2.6296566837107362;
	hodges[197] = 2.6296566837107376;
	hodges[198] = 1.6182502668989152;
	hodges[199] = 1.6182502668989169;
	hodges[200] = 2.629656683710738;
	hodges[201] = 1.5026609621204214;
	hodges[202] = 2.1655996218794309;
	hodges[203] = 2.1655996218794313;
	hodges[204] = 2.4749709964336364;
	hodges[205] = 1.9124775881532647;
	hodges[206] = 2.4749709964336355;
	hodges[207] = 1.6182502668989152;
	hodges[208] = 2.4749709964336351;
	hodges[209] = 1.9124775881532647;
	hodges[210] = 2.4749709964336368;
	hodges[211] = 1.6182502668989152;
	hodges[212] = 2.6296566837107376;
	hodges[213] = 1.5026609621204214;
	hodges[214] = 2.16559962187943;
	hodges[215] = 2.1655996218794322;
	hodges[216] = 2.6296566837107371;
	hodges[217] = 2.629656683710738;
	hodges[218] = 1.6182502668989167;
	hodges[219] = 1.6182502668989163;
	hodges[220] = 2.6296566837107376;
	hodges[221] = 2.629656683710738;
	hodges[222] = 1.6182502668989156;
	hodges[223] = 1.6182502668989152;
	hodges[224] = 2.6296566837107362;
	hodges[225] = 2.6296566837107371;
	hodges[226] = 1.6182502668989152;
	hodges[227] = 1.6182502668989169;
	hodges[228] = 2.6296566837107398;
	hodges[229] = 1.5026609621204228;
	hodges[230] = 2.1655996218794318;
	hodges[231] = 2.1655996218794304;
	hodges[232] = 2.4749709964336377;
	hodges[233] = 1.9124775881532621;
	hodges[234] = 2.4749709964336368;
	hodges[235] = 1.6182502668989152;
	hodges[236] = 2.629656683710738;
	hodges[237] = 1.5026609621204199;
	hodges[238] = 2.165599621879434;
	hodges[239] = 2.1655996218794322;
	hodges[240] = 2.6296566837107385;
	hodges[241] = 1.502660962120421;
	hodges[242] = 2.1655996218794318;
	hodges[243] = 2.1655996218794304;
	hodges[244] = 2.2312238528454746;
	hodges[245] = 2.2312238528454729;
	hodges[246] = 2.2312238528454751;
	hodges[247] = 1.3148283418553695;
	hodges[248] = 2.4749709964336342;
	hodges[249] = 1.9124775881532652;
	hodges[250] = 2.4749709964336351;
	hodges[251] = 1.6182502668989163;
	hodges[252] = 2.4749709964336355;
	hodges[253] = 1.9124775881532645;
	hodges[254] = 2.4749709964336355;
	hodges[255] = 1.6182502668989163;
	hodges[256] = 2.6296566837107398;
	hodges[257] = 1.5026609621204219;
	hodges[258] = 2.1655996218794309;
	hodges[259] = 2.1655996218794331;
	hodges[260] = 2.4749709964336368;
	hodges[261] = 1.9124775881532619;
	hodges[262] = 2.4749709964336364;
	hodges[263] = 1.6182502668989156;
	hodges[264] = 2.6296566837107402;
	hodges[265] = 1.5026609621204217;
	hodges[266] = 2.1655996218794318;
	hodges[267] = 2.1655996218794304;
	hodges[268] = 2.6296566837107402;
	hodges[269] = 1.5026609621204217;
	hodges[270] = 2.1655996218794322;
	hodges[271] = 2.1655996218794304;
	hodges[272] = 2.231223852845476;
	hodges[273] = 2.2312238528454729;
	hodges[274] = 2.2312238528454729;
	hodges[275] = 1.3148283418553692;
	hodges[276] = 2.6296566837107402;
	hodges[277] = 1.502660962120421;
	hodges[278] = 2.1655996218794322;
	hodges[279] = 2.1655996218794336;
	hodges[280] = 2.629656683710742;
	hodges[281] = 1.5026609621204199;
	hodges[282] = 2.1655996218794318;
	hodges[283] = 2.1655996218794304;
	hodges[284] = 2.6296566837107402;
	hodges[285] = 1.5026609621204208;
	hodges[286] = 2.1655996218794336;
	hodges[287] = 2.1655996218794322;
	hodges[288] = 2.4749709964336386;
	hodges[289] = 1.9124775881532623;
	hodges[290] = 2.4749709964336373;
	hodges[291] = 1.6182502668989156;
	hodges[292] = 2.4749709964336355;
	hodges[293] = 1.9124775881532652;
	hodges[294] = 2.4749709964336364;
	hodges[295] = 1.6182502668989167;
	hodges[296] = 2.2312238528454755;
	hodges[297] = 2.2312238528454724;
	hodges[298] = 2.2312238528454733;
	hodges[299] = 1.3148283418553688;
	hodges[300] = 2.6296566837107398;
	hodges[301] = 1.502660962120421;
	hodges[302] = 2.1655996218794309;
	hodges[303] = 2.1655996218794313;
	hodges[304] = 2.6296566837107402;
	hodges[305] = 1.5026609621204201;
	hodges[306] = 2.1655996218794313;
	hodges[307] = 2.1655996218794309;
	hodges[308] = 2.4749709964336355;
	hodges[309] = 1.9124775881532641;
	hodges[310] = 2.4749709964336359;
	hodges[311] = 1.6182502668989156;
	hodges[312] = 2.6296566837107398;
	hodges[313] = 1.5026609621204208;
	hodges[314] = 2.1655996218794322;
	hodges[315] = 2.1655996218794309;
	hodges[316] = 2.4749709964336377;
	hodges[317] = 1.9124775881532623;
	hodges[318] = 2.4749709964336382;
	hodges[319] = 1.6182502668989163;

	return 2.629656683710742;
}
