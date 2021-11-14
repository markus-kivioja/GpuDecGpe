#define FACE_COUNT 4
#define DUAL_EDGE_LENGTH 0.6876432142500688
#define VALUES_IN_BLOCK 136
#define INDICES_PER_BLOCK 544
const Vector3 BLOCK_WIDTH = Vector3(5.3899999999999997, 5.3899999999999997, 5.3899999999999997); // dimensions of unit block
const ddouble VOLUME = 1.2233657734374999; // volume of body elements
const bool IS_3D = true; // 3-dimensional
void getPositions(Buffer<Vector3> &pos)
{
	pos.resize(VALUES_IN_BLOCK);
	pos[0] = Vector3(4.8285416666666672, 2.975729166666667, 2.975729166666667);
	pos[1] = Vector3(1.6282291666666673, 5.1092708333333334, 0.7860416666666673);
	pos[2] = Vector3(1.908958333333334, 2.975729166666667, 3.7617708333333337);
	pos[3] = Vector3(5.1092708333333334, 2.414270833333334, 3.2564583333333337);
	pos[4] = Vector3(2.4142708333333336, 0.56145833333333406, 2.4142708333333336);
	pos[5] = Vector3(2.0212500000000007, 4.7162500000000005, 4.7162500000000005);
	pos[6] = Vector3(2.975729166666667, 3.7617708333333337, 1.908958333333334);
	pos[7] = Vector3(2.4142708333333336, 2.4142708333333336, 0.56145833333333406);
	pos[8] = Vector3(2.975729166666667, 4.8285416666666672, 2.975729166666667);
	pos[9] = Vector3(4.8285416666666672, 3.7617708333333324, 3.7617708333333324);
	pos[10] = Vector3(0.067375000000000629, 0.067375000000000629, 3.9751250000000002);
	pos[11] = Vector3(3.3687500000000004, 3.3687500000000004, 3.3687500000000004);
	pos[12] = Vector3(1.2801250000000006, 2.7623750000000005, 0.067375000000000684);
	pos[13] = Vector3(2.0212500000000007, 2.0212500000000007, 2.0212500000000007);
	pos[14] = Vector3(4.6039583333333338, 3.7617708333333333, 0.28072916666666775);
	pos[15] = Vector3(3.9751250000000002, 2.762375, 2.7623750000000005);
	pos[16] = Vector3(1.6282291666666675, 0.56145833333333417, 1.6282291666666673);
	pos[17] = Vector3(1.6282291666666675, 1.6282291666666673, 0.56145833333333417);
	pos[18] = Vector3(1.2801250000000004, 3.9751250000000007, 1.2801250000000008);
	pos[19] = Vector3(0.06737500000000074, 3.9751250000000002, 0.067375000000000684);
	pos[20] = Vector3(1.0667708333333339, 1.908958333333334, 0.28072916666666742);
	pos[21] = Vector3(1.6282291666666675, 2.4142708333333336, 3.481041666666667);
	pos[22] = Vector3(3.2564583333333337, 5.1092708333333334, 2.414270833333334);
	pos[23] = Vector3(0.067375000000000684, 2.7623750000000005, 1.2801250000000006);
	pos[24] = Vector3(1.908958333333334, 0.28072916666666736, 1.0667708333333339);
	pos[25] = Vector3(0.067375000000000795, 1.2801250000000006, 2.7623750000000005);
	pos[26] = Vector3(2.7623750000000005, 1.2801250000000006, 0.067375000000000795);
	pos[27] = Vector3(1.4148750000000012, 2.6276250000000005, 2.6276250000000005);
	pos[28] = Vector3(3.9751250000000002, 0.067375000000000795, 0.067375000000000573);
	pos[29] = Vector3(2.414270833333334, 3.2564583333333337, 5.1092708333333334);
	pos[30] = Vector3(0.67375000000000063, 0.67375000000000074, 3.3687500000000004);
	pos[31] = Vector3(0.28072916666666736, 2.1335416666666669, 2.9757291666666665);
	pos[32] = Vector3(3.9751249999999994, 3.9751249999999994, 3.9751249999999994);
	pos[33] = Vector3(0.28072916666666742, 1.0667708333333339, 1.908958333333334);
	pos[34] = Vector3(0.56145833333333417, 4.3232291666666667, 4.3232291666666667);
	pos[35] = Vector3(4.3232291666666676, 3.2564583333333337, 1.6282291666666673);
	pos[36] = Vector3(2.7623750000000005, 2.7623750000000005, 3.9751250000000002);
	pos[37] = Vector3(1.2801250000000006, 0.067375000000000795, 2.762375);
	pos[38] = Vector3(1.0667708333333339, 0.28072916666666742, 1.908958333333334);
	pos[39] = Vector3(2.1335416666666669, 0.28072916666666736, 2.9757291666666665);
	pos[40] = Vector3(0.67375000000000063, 3.3687500000000004, 0.67375000000000074);
	pos[41] = Vector3(0.56145833333333406, 2.4142708333333336, 2.4142708333333336);
	pos[42] = Vector3(2.1335416666666669, 2.9757291666666665, 0.28072916666666736);
	pos[43] = Vector3(0.28072916666666736, 2.9757291666666665, 2.1335416666666669);
	pos[44] = Vector3(5.1092708333333334, 3.2564583333333337, 2.414270833333334);
	pos[45] = Vector3(4.6039583333333338, 1.0667708333333341, 2.975729166666667);
	pos[46] = Vector3(0.56145833333333417, 1.6282291666666675, 1.6282291666666673);
	pos[47] = Vector3(0.28072916666666742, 1.908958333333334, 1.0667708333333339);
	pos[48] = Vector3(2.7623750000000005, 0.067375000000000518, 1.2801250000000006);
	pos[49] = Vector3(1.4148750000000008, 1.4148750000000008, 1.4148750000000008);
	pos[50] = Vector3(3.9751250000000002, 1.2801250000000008, 1.2801250000000006);
	pos[51] = Vector3(2.975729166666667, 0.2807291666666672, 2.1335416666666669);
	pos[52] = Vector3(2.4142708333333336, 1.6282291666666675, 3.481041666666667);
	pos[53] = Vector3(1.0667708333333341, 3.7617708333333337, 2.1335416666666669);
	pos[54] = Vector3(1.908958333333334, 1.0667708333333339, 0.28072916666666736);
	pos[55] = Vector3(3.3687500000000004, 0.67375000000000063, 0.67375000000000063);
	pos[56] = Vector3(4.3232291666666676, 0.78604166666666719, 2.414270833333334);
	pos[57] = Vector3(2.9757291666666665, 2.1335416666666669, 0.28072916666666736);
	pos[58] = Vector3(2.6276250000000005, 2.6276250000000001, 1.4148750000000012);
	pos[59] = Vector3(2.6276250000000005, 1.4148750000000012, 2.6276250000000005);
	pos[60] = Vector3(0.78604166666666719, 4.3232291666666676, 2.414270833333334);
	pos[61] = Vector3(1.908958333333334, 3.7617708333333337, 2.975729166666667);
	pos[62] = Vector3(3.7617708333333337, 2.975729166666667, 1.908958333333334);
	pos[63] = Vector3(3.481041666666667, 2.4142708333333336, 1.6282291666666675);
	pos[64] = Vector3(3.7617708333333337, 2.1335416666666669, 1.0667708333333341);
	pos[65] = Vector3(3.7617708333333337, 1.908958333333334, 2.975729166666667);
	pos[66] = Vector3(3.481041666666667, 1.6282291666666677, 2.414270833333334);
	pos[67] = Vector3(3.7617708333333337, 1.0667708333333341, 2.1335416666666669);
	pos[68] = Vector3(1.4148750000000008, 5.3226250000000004, 5.3226250000000004);
	pos[69] = Vector3(4.3232291666666676, 1.6282291666666673, 3.2564583333333337);
	pos[70] = Vector3(4.8285416666666672, 1.0667708333333339, 1.0667708333333341);
	pos[71] = Vector3(4.8285416666666672, 0.28072916666666681, 0.2807291666666667);
	pos[72] = Vector3(5.1092708333333334, 0.78604166666666719, 1.6282291666666673);
	pos[73] = Vector3(4.6039583333333338, 0.28072916666666775, 3.7617708333333333);
	pos[74] = Vector3(2.7623750000000005, 3.9751250000000002, 2.7623750000000005);
	pos[75] = Vector3(2.414270833333334, 4.3232291666666676, 0.78604166666666719);
	pos[76] = Vector3(2.6276250000000005, 5.3226250000000004, 4.1098750000000006);
	pos[77] = Vector3(5.1092708333333334, 1.6282291666666673, 0.7860416666666673);
	pos[78] = Vector3(4.6039583333333338, 2.975729166666667, 1.0667708333333341);
	pos[79] = Vector3(4.3232291666666676, 2.414270833333334, 0.78604166666666719);
	pos[80] = Vector3(4.1098750000000006, 4.1098750000000006, 1.4148750000000005);
	pos[81] = Vector3(3.7617708333333333, 4.6039583333333338, 0.28072916666666775);
	pos[82] = Vector3(1.6282291666666677, 3.481041666666667, 2.414270833333334);
	pos[83] = Vector3(2.1335416666666669, 3.7617708333333337, 1.0667708333333341);
	pos[84] = Vector3(2.4142708333333336, 3.481041666666667, 1.6282291666666675);
	pos[85] = Vector3(3.7617708333333324, 4.8285416666666672, 3.7617708333333324);
	pos[86] = Vector3(4.3232291666666667, 4.3232291666666667, 0.56145833333333417);
	pos[87] = Vector3(1.6282291666666673, 4.3232291666666676, 3.2564583333333337);
	pos[88] = Vector3(1.0667708333333341, 4.8285416666666672, 1.0667708333333339);
	pos[89] = Vector3(0.28072916666666675, 4.8285416666666672, 0.28072916666666675);
	pos[90] = Vector3(5.3226250000000004, 4.1098750000000006, 2.6276250000000005);
	pos[91] = Vector3(2.414270833333334, 5.1092708333333334, 3.2564583333333337);
	pos[92] = Vector3(1.0667708333333339, 4.6039583333333338, 2.975729166666667);
	pos[93] = Vector3(0.78604166666666719, 5.1092708333333334, 1.6282291666666673);
	pos[94] = Vector3(0.28072916666666781, 4.6039583333333338, 3.7617708333333333);
	pos[95] = Vector3(1.0667708333333339, 1.0667708333333339, 4.8285416666666672);
	pos[96] = Vector3(3.4810416666666661, 5.1092708333333343, 4.3232291666666667);
	pos[97] = Vector3(2.975729166666667, 4.6039583333333338, 1.0667708333333339);
	pos[98] = Vector3(3.2564583333333337, 4.3232291666666676, 1.6282291666666673);
	pos[99] = Vector3(5.1092708333333334, 5.1092708333333334, 0.56145833333333273);
	pos[100] = Vector3(4.7162500000000005, 4.7162500000000005, 2.0212500000000007);
	pos[101] = Vector3(5.3226250000000004, 5.3226250000000004, 1.4148750000000008);
	pos[102] = Vector3(4.1098750000000006, 5.3226250000000004, 2.6276250000000005);
	pos[103] = Vector3(4.3232291666666667, 5.1092708333333343, 3.4810416666666661);
	pos[104] = Vector3(5.1092708333333343, 4.3232291666666667, 3.4810416666666661);
	pos[105] = Vector3(2.414270833333334, 0.78604166666666742, 4.3232291666666676);
	pos[106] = Vector3(0.28072916666666775, 3.7617708333333333, 4.6039583333333338);
	pos[107] = Vector3(2.975729166666667, 1.908958333333334, 3.7617708333333337);
	pos[108] = Vector3(2.1335416666666669, 1.0667708333333341, 3.7617708333333337);
	pos[109] = Vector3(1.0667708333333341, 2.1335416666666669, 3.7617708333333337);
	pos[110] = Vector3(2.9757291666666674, 2.975729166666667, 4.8285416666666672);
	pos[111] = Vector3(3.7617708333333324, 3.7617708333333324, 4.8285416666666672);
	pos[112] = Vector3(1.2801250000000006, 1.2801250000000006, 3.9751250000000002);
	pos[113] = Vector3(1.4148750000000005, 4.1098750000000006, 4.1098750000000006);
	pos[114] = Vector3(0.28072916666666675, 0.28072916666666675, 4.8285416666666672);
	pos[115] = Vector3(1.6282291666666673, 0.7860416666666673, 5.1092708333333334);
	pos[116] = Vector3(1.6282291666666671, 3.2564583333333337, 4.3232291666666676);
	pos[117] = Vector3(0.7860416666666673, 1.6282291666666673, 5.1092708333333334);
	pos[118] = Vector3(1.0667708333333341, 2.975729166666667, 4.6039583333333338);
	pos[119] = Vector3(0.78604166666666742, 2.414270833333334, 4.3232291666666676);
	pos[120] = Vector3(3.7617708333333333, 0.28072916666666775, 4.6039583333333338);
	pos[121] = Vector3(4.3232291666666667, 0.56145833333333417, 4.3232291666666667);
	pos[122] = Vector3(4.1098750000000006, 1.4148750000000005, 4.1098750000000006);
	pos[123] = Vector3(2.975729166666667, 1.0667708333333339, 4.6039583333333338);
	pos[124] = Vector3(3.2564583333333337, 1.6282291666666671, 4.3232291666666676);
	pos[125] = Vector3(3.2564583333333337, 2.414270833333334, 5.1092708333333334);
	pos[126] = Vector3(5.1092708333333343, 3.4810416666666661, 4.3232291666666667);
	pos[127] = Vector3(5.3226250000000004, 1.4148750000000008, 5.3226250000000004);
	pos[128] = Vector3(4.1098750000000006, 2.6276250000000005, 5.3226250000000004);
	pos[129] = Vector3(5.1092708333333334, 0.56145833333333295, 5.1092708333333334);
	pos[130] = Vector3(5.3226250000000004, 2.6276250000000005, 4.1098750000000006);
	pos[131] = Vector3(4.7162500000000005, 2.0212500000000007, 4.7162500000000005);
	pos[132] = Vector3(4.3232291666666667, 3.4810416666666661, 5.1092708333333343);
	pos[133] = Vector3(2.6276250000000005, 4.1098750000000006, 5.3226250000000004);
	pos[134] = Vector3(0.56145833333333295, 5.1092708333333334, 5.1092708333333334);
	pos[135] = Vector3(3.4810416666666661, 4.3232291666666667, 5.1092708333333343);
}
ddouble getLaplacian(Buffer<int3> &blockDirs, Buffer<int> &valueInds, Buffer<ddouble> &hodges)
{
	blockDirs.resize(INDICES_PER_BLOCK);
	// Dual node idx:  0
	blockDirs[0] = make_int3(0, 0, 0);
	blockDirs[1] = make_int3(0, 0, 0);
	blockDirs[2] = make_int3(0, 0, 0);
	blockDirs[3] = make_int3(0, 0, 0);
	// Dual node idx:  1
	blockDirs[4] = make_int3(0, 0, -1);
	blockDirs[5] = make_int3(0, 1, 0);
	blockDirs[6] = make_int3(0, 0, 0);
	blockDirs[7] = make_int3(0, 0, 0);
	// Dual node idx:  2
	blockDirs[8] = make_int3(0, 0, 0);
	blockDirs[9] = make_int3(0, 0, 0);
	blockDirs[10] = make_int3(0, 0, 0);
	blockDirs[11] = make_int3(0, 0, 0);
	// Dual node idx:  3
	blockDirs[12] = make_int3(0, 0, 0);
	blockDirs[13] = make_int3(1, 0, 0);
	blockDirs[14] = make_int3(0, 0, 0);
	blockDirs[15] = make_int3(0, 0, 0);
	// Dual node idx:  4
	blockDirs[16] = make_int3(0, 0, 0);
	blockDirs[17] = make_int3(0, 0, 0);
	blockDirs[18] = make_int3(0, 0, 0);
	blockDirs[19] = make_int3(0, 0, 0);
	// Dual node idx:  5
	blockDirs[20] = make_int3(0, 0, 0);
	blockDirs[21] = make_int3(0, 0, 0);
	blockDirs[22] = make_int3(0, 0, 0);
	blockDirs[23] = make_int3(0, 0, 0);
	// Dual node idx:  6
	blockDirs[24] = make_int3(0, 0, 0);
	blockDirs[25] = make_int3(0, 0, 0);
	blockDirs[26] = make_int3(0, 0, 0);
	blockDirs[27] = make_int3(0, 0, 0);
	// Dual node idx:  7
	blockDirs[28] = make_int3(0, 0, 0);
	blockDirs[29] = make_int3(0, 0, 0);
	blockDirs[30] = make_int3(0, 0, 0);
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
	blockDirs[40] = make_int3(0, -1, 0);
	blockDirs[41] = make_int3(0, 0, 0);
	blockDirs[42] = make_int3(0, 0, 0);
	blockDirs[43] = make_int3(-1, 0, 0);
	// Dual node idx:  11
	blockDirs[44] = make_int3(0, 0, 0);
	blockDirs[45] = make_int3(0, 0, 0);
	blockDirs[46] = make_int3(0, 0, 0);
	blockDirs[47] = make_int3(0, 0, 0);
	// Dual node idx:  12
	blockDirs[48] = make_int3(0, 0, 0);
	blockDirs[49] = make_int3(0, 0, 0);
	blockDirs[50] = make_int3(0, 0, -1);
	blockDirs[51] = make_int3(0, 0, 0);
	// Dual node idx:  13
	blockDirs[52] = make_int3(0, 0, 0);
	blockDirs[53] = make_int3(0, 0, 0);
	blockDirs[54] = make_int3(0, 0, 0);
	blockDirs[55] = make_int3(0, 0, 0);
	// Dual node idx:  14
	blockDirs[56] = make_int3(1, 0, 0);
	blockDirs[57] = make_int3(0, 0, 0);
	blockDirs[58] = make_int3(0, 0, -1);
	blockDirs[59] = make_int3(0, 0, 0);
	// Dual node idx:  15
	blockDirs[60] = make_int3(0, 0, 0);
	blockDirs[61] = make_int3(0, 0, 0);
	blockDirs[62] = make_int3(0, 0, 0);
	blockDirs[63] = make_int3(0, 0, 0);
	// Dual node idx:  16
	blockDirs[64] = make_int3(0, 0, 0);
	blockDirs[65] = make_int3(0, 0, 0);
	blockDirs[66] = make_int3(0, 0, 0);
	blockDirs[67] = make_int3(0, 0, 0);
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
	blockDirs[76] = make_int3(0, 0, -1);
	blockDirs[77] = make_int3(0, 0, 0);
	blockDirs[78] = make_int3(-1, 0, 0);
	blockDirs[79] = make_int3(0, 0, 0);
	// Dual node idx:  20
	blockDirs[80] = make_int3(0, 0, 0);
	blockDirs[81] = make_int3(0, 0, 0);
	blockDirs[82] = make_int3(0, 0, -1);
	blockDirs[83] = make_int3(0, 0, 0);
	// Dual node idx:  21
	blockDirs[84] = make_int3(0, 0, 0);
	blockDirs[85] = make_int3(0, 0, 0);
	blockDirs[86] = make_int3(0, 0, 0);
	blockDirs[87] = make_int3(0, 0, 0);
	// Dual node idx:  22
	blockDirs[88] = make_int3(0, 0, 0);
	blockDirs[89] = make_int3(0, 1, 0);
	blockDirs[90] = make_int3(0, 0, 0);
	blockDirs[91] = make_int3(0, 0, 0);
	// Dual node idx:  23
	blockDirs[92] = make_int3(0, 0, 0);
	blockDirs[93] = make_int3(0, 0, 0);
	blockDirs[94] = make_int3(-1, 0, 0);
	blockDirs[95] = make_int3(0, 0, 0);
	// Dual node idx:  24
	blockDirs[96] = make_int3(0, 0, 0);
	blockDirs[97] = make_int3(0, 0, 0);
	blockDirs[98] = make_int3(0, 0, 0);
	blockDirs[99] = make_int3(0, -1, 0);
	// Dual node idx:  25
	blockDirs[100] = make_int3(0, 0, 0);
	blockDirs[101] = make_int3(0, 0, 0);
	blockDirs[102] = make_int3(0, 0, 0);
	blockDirs[103] = make_int3(-1, 0, 0);
	// Dual node idx:  26
	blockDirs[104] = make_int3(0, 0, 0);
	blockDirs[105] = make_int3(0, 0, 0);
	blockDirs[106] = make_int3(0, 0, 0);
	blockDirs[107] = make_int3(0, 0, -1);
	// Dual node idx:  27
	blockDirs[108] = make_int3(0, 0, 0);
	blockDirs[109] = make_int3(0, 0, 0);
	blockDirs[110] = make_int3(0, 0, 0);
	blockDirs[111] = make_int3(0, 0, 0);
	// Dual node idx:  28
	blockDirs[112] = make_int3(0, 0, 0);
	blockDirs[113] = make_int3(0, 0, 0);
	blockDirs[114] = make_int3(0, -1, 0);
	blockDirs[115] = make_int3(0, 0, -1);
	// Dual node idx:  29
	blockDirs[116] = make_int3(0, 0, 0);
	blockDirs[117] = make_int3(0, 0, 1);
	blockDirs[118] = make_int3(0, 0, 0);
	blockDirs[119] = make_int3(0, 0, 0);
	// Dual node idx:  30
	blockDirs[120] = make_int3(0, 0, 0);
	blockDirs[121] = make_int3(0, 0, 0);
	blockDirs[122] = make_int3(0, 0, 0);
	blockDirs[123] = make_int3(0, 0, 0);
	// Dual node idx:  31
	blockDirs[124] = make_int3(0, 0, 0);
	blockDirs[125] = make_int3(0, 0, 0);
	blockDirs[126] = make_int3(0, 0, 0);
	blockDirs[127] = make_int3(-1, 0, 0);
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
	blockDirs[141] = make_int3(0, 0, 0);
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
	blockDirs[151] = make_int3(0, -1, 0);
	// Dual node idx:  38
	blockDirs[152] = make_int3(0, 0, 0);
	blockDirs[153] = make_int3(0, 0, 0);
	blockDirs[154] = make_int3(0, 0, 0);
	blockDirs[155] = make_int3(0, -1, 0);
	// Dual node idx:  39
	blockDirs[156] = make_int3(0, 0, 0);
	blockDirs[157] = make_int3(0, 0, 0);
	blockDirs[158] = make_int3(0, 0, 0);
	blockDirs[159] = make_int3(0, -1, 0);
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
	blockDirs[171] = make_int3(0, 0, -1);
	// Dual node idx:  43
	blockDirs[172] = make_int3(0, 0, 0);
	blockDirs[173] = make_int3(0, 0, 0);
	blockDirs[174] = make_int3(0, 0, 0);
	blockDirs[175] = make_int3(-1, 0, 0);
	// Dual node idx:  44
	blockDirs[176] = make_int3(0, 0, 0);
	blockDirs[177] = make_int3(1, 0, 0);
	blockDirs[178] = make_int3(0, 0, 0);
	blockDirs[179] = make_int3(0, 0, 0);
	// Dual node idx:  45
	blockDirs[180] = make_int3(0, 0, 0);
	blockDirs[181] = make_int3(1, 0, 0);
	blockDirs[182] = make_int3(0, 0, 0);
	blockDirs[183] = make_int3(0, 0, 0);
	// Dual node idx:  46
	blockDirs[184] = make_int3(0, 0, 0);
	blockDirs[185] = make_int3(0, 0, 0);
	blockDirs[186] = make_int3(0, 0, 0);
	blockDirs[187] = make_int3(0, 0, 0);
	// Dual node idx:  47
	blockDirs[188] = make_int3(0, 0, 0);
	blockDirs[189] = make_int3(0, 0, 0);
	blockDirs[190] = make_int3(-1, 0, 0);
	blockDirs[191] = make_int3(0, 0, 0);
	// Dual node idx:  48
	blockDirs[192] = make_int3(0, 0, 0);
	blockDirs[193] = make_int3(0, 0, 0);
	blockDirs[194] = make_int3(0, -1, 0);
	blockDirs[195] = make_int3(0, 0, 0);
	// Dual node idx:  49
	blockDirs[196] = make_int3(0, 0, 0);
	blockDirs[197] = make_int3(0, 0, 0);
	blockDirs[198] = make_int3(0, 0, 0);
	blockDirs[199] = make_int3(0, 0, 0);
	// Dual node idx:  50
	blockDirs[200] = make_int3(0, 0, 0);
	blockDirs[201] = make_int3(0, 0, 0);
	blockDirs[202] = make_int3(0, 0, 0);
	blockDirs[203] = make_int3(0, 0, 0);
	// Dual node idx:  51
	blockDirs[204] = make_int3(0, 0, 0);
	blockDirs[205] = make_int3(0, 0, 0);
	blockDirs[206] = make_int3(0, -1, 0);
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
	blockDirs[215] = make_int3(0, 0, 0);
	// Dual node idx:  54
	blockDirs[216] = make_int3(0, 0, 0);
	blockDirs[217] = make_int3(0, 0, 0);
	blockDirs[218] = make_int3(0, 0, 0);
	blockDirs[219] = make_int3(0, 0, -1);
	// Dual node idx:  55
	blockDirs[220] = make_int3(0, 0, 0);
	blockDirs[221] = make_int3(0, 0, 0);
	blockDirs[222] = make_int3(0, 0, 0);
	blockDirs[223] = make_int3(0, 0, 0);
	// Dual node idx:  56
	blockDirs[224] = make_int3(0, 0, 0);
	blockDirs[225] = make_int3(0, 0, 0);
	blockDirs[226] = make_int3(0, -1, 0);
	blockDirs[227] = make_int3(0, 0, 0);
	// Dual node idx:  57
	blockDirs[228] = make_int3(0, 0, 0);
	blockDirs[229] = make_int3(0, 0, 0);
	blockDirs[230] = make_int3(0, 0, 0);
	blockDirs[231] = make_int3(0, 0, -1);
	// Dual node idx:  58
	blockDirs[232] = make_int3(0, 0, 0);
	blockDirs[233] = make_int3(0, 0, 0);
	blockDirs[234] = make_int3(0, 0, 0);
	blockDirs[235] = make_int3(0, 0, 0);
	// Dual node idx:  59
	blockDirs[236] = make_int3(0, 0, 0);
	blockDirs[237] = make_int3(0, 0, 0);
	blockDirs[238] = make_int3(0, 0, 0);
	blockDirs[239] = make_int3(0, 0, 0);
	// Dual node idx:  60
	blockDirs[240] = make_int3(0, 0, 0);
	blockDirs[241] = make_int3(0, 0, 0);
	blockDirs[242] = make_int3(-1, 0, 0);
	blockDirs[243] = make_int3(0, 0, 0);
	// Dual node idx:  61
	blockDirs[244] = make_int3(0, 0, 0);
	blockDirs[245] = make_int3(0, 0, 0);
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
	blockDirs[256] = make_int3(0, 0, 0);
	blockDirs[257] = make_int3(0, 0, 0);
	blockDirs[258] = make_int3(0, 0, 0);
	blockDirs[259] = make_int3(0, 0, 0);
	// Dual node idx:  65
	blockDirs[260] = make_int3(0, 0, 0);
	blockDirs[261] = make_int3(0, 0, 0);
	blockDirs[262] = make_int3(0, 0, 0);
	blockDirs[263] = make_int3(0, 0, 0);
	// Dual node idx:  66
	blockDirs[264] = make_int3(0, 0, 0);
	blockDirs[265] = make_int3(0, 0, 0);
	blockDirs[266] = make_int3(0, 0, 0);
	blockDirs[267] = make_int3(0, 0, 0);
	// Dual node idx:  67
	blockDirs[268] = make_int3(0, 0, 0);
	blockDirs[269] = make_int3(0, 0, 0);
	blockDirs[270] = make_int3(0, 0, 0);
	blockDirs[271] = make_int3(0, 0, 0);
	// Dual node idx:  68
	blockDirs[272] = make_int3(0, 1, 0);
	blockDirs[273] = make_int3(0, 0, 1);
	blockDirs[274] = make_int3(0, 0, 0);
	blockDirs[275] = make_int3(0, 0, 0);
	// Dual node idx:  69
	blockDirs[276] = make_int3(0, 0, 0);
	blockDirs[277] = make_int3(0, 0, 0);
	blockDirs[278] = make_int3(0, 0, 0);
	blockDirs[279] = make_int3(0, 0, 0);
	// Dual node idx:  70
	blockDirs[280] = make_int3(0, 0, 0);
	blockDirs[281] = make_int3(0, 0, 0);
	blockDirs[282] = make_int3(0, 0, 0);
	blockDirs[283] = make_int3(0, 0, 0);
	// Dual node idx:  71
	blockDirs[284] = make_int3(0, -1, 0);
	blockDirs[285] = make_int3(0, 0, 0);
	blockDirs[286] = make_int3(0, 0, -1);
	blockDirs[287] = make_int3(0, 0, 0);
	// Dual node idx:  72
	blockDirs[288] = make_int3(0, -1, 0);
	blockDirs[289] = make_int3(1, 0, 0);
	blockDirs[290] = make_int3(0, 0, 0);
	blockDirs[291] = make_int3(0, 0, 0);
	// Dual node idx:  73
	blockDirs[292] = make_int3(1, 0, 0);
	blockDirs[293] = make_int3(0, 0, 0);
	blockDirs[294] = make_int3(0, -1, 0);
	blockDirs[295] = make_int3(0, 0, 0);
	// Dual node idx:  74
	blockDirs[296] = make_int3(0, 0, 0);
	blockDirs[297] = make_int3(0, 0, 0);
	blockDirs[298] = make_int3(0, 0, 0);
	blockDirs[299] = make_int3(0, 0, 0);
	// Dual node idx:  75
	blockDirs[300] = make_int3(0, 0, 0);
	blockDirs[301] = make_int3(0, 0, 0);
	blockDirs[302] = make_int3(0, 0, -1);
	blockDirs[303] = make_int3(0, 0, 0);
	// Dual node idx:  76
	blockDirs[304] = make_int3(0, 0, 0);
	blockDirs[305] = make_int3(0, 1, 0);
	blockDirs[306] = make_int3(0, 0, 0);
	blockDirs[307] = make_int3(0, 0, 0);
	// Dual node idx:  77
	blockDirs[308] = make_int3(0, 0, -1);
	blockDirs[309] = make_int3(1, 0, 0);
	blockDirs[310] = make_int3(0, 0, 0);
	blockDirs[311] = make_int3(0, 0, 0);
	// Dual node idx:  78
	blockDirs[312] = make_int3(0, 0, 0);
	blockDirs[313] = make_int3(1, 0, 0);
	blockDirs[314] = make_int3(0, 0, 0);
	blockDirs[315] = make_int3(0, 0, 0);
	// Dual node idx:  79
	blockDirs[316] = make_int3(0, 0, 0);
	blockDirs[317] = make_int3(0, 0, 0);
	blockDirs[318] = make_int3(0, 0, -1);
	blockDirs[319] = make_int3(0, 0, 0);
	// Dual node idx:  80
	blockDirs[320] = make_int3(0, 0, 0);
	blockDirs[321] = make_int3(0, 0, 0);
	blockDirs[322] = make_int3(0, 0, 0);
	blockDirs[323] = make_int3(0, 0, 0);
	// Dual node idx:  81
	blockDirs[324] = make_int3(0, 1, 0);
	blockDirs[325] = make_int3(0, 0, 0);
	blockDirs[326] = make_int3(0, 0, 0);
	blockDirs[327] = make_int3(0, 0, -1);
	// Dual node idx:  82
	blockDirs[328] = make_int3(0, 0, 0);
	blockDirs[329] = make_int3(0, 0, 0);
	blockDirs[330] = make_int3(0, 0, 0);
	blockDirs[331] = make_int3(0, 0, 0);
	// Dual node idx:  83
	blockDirs[332] = make_int3(0, 0, 0);
	blockDirs[333] = make_int3(0, 0, 0);
	blockDirs[334] = make_int3(0, 0, 0);
	blockDirs[335] = make_int3(0, 0, 0);
	// Dual node idx:  84
	blockDirs[336] = make_int3(0, 0, 0);
	blockDirs[337] = make_int3(0, 0, 0);
	blockDirs[338] = make_int3(0, 0, 0);
	blockDirs[339] = make_int3(0, 0, 0);
	// Dual node idx:  85
	blockDirs[340] = make_int3(0, 0, 0);
	blockDirs[341] = make_int3(0, 0, 0);
	blockDirs[342] = make_int3(0, 0, 0);
	blockDirs[343] = make_int3(0, 0, 0);
	// Dual node idx:  86
	blockDirs[344] = make_int3(0, 0, 0);
	blockDirs[345] = make_int3(0, 0, 0);
	blockDirs[346] = make_int3(0, 0, 0);
	blockDirs[347] = make_int3(0, 0, 0);
	// Dual node idx:  87
	blockDirs[348] = make_int3(0, 0, 0);
	blockDirs[349] = make_int3(0, 0, 0);
	blockDirs[350] = make_int3(0, 0, 0);
	blockDirs[351] = make_int3(0, 0, 0);
	// Dual node idx:  88
	blockDirs[352] = make_int3(0, 0, 0);
	blockDirs[353] = make_int3(0, 0, 0);
	blockDirs[354] = make_int3(0, 0, 0);
	blockDirs[355] = make_int3(0, 0, 0);
	// Dual node idx:  89
	blockDirs[356] = make_int3(0, 0, -1);
	blockDirs[357] = make_int3(0, 0, 0);
	blockDirs[358] = make_int3(-1, 0, 0);
	blockDirs[359] = make_int3(0, 0, 0);
	// Dual node idx:  90
	blockDirs[360] = make_int3(0, 0, 0);
	blockDirs[361] = make_int3(1, 0, 0);
	blockDirs[362] = make_int3(0, 0, 0);
	blockDirs[363] = make_int3(0, 0, 0);
	// Dual node idx:  91
	blockDirs[364] = make_int3(0, 0, 0);
	blockDirs[365] = make_int3(0, 1, 0);
	blockDirs[366] = make_int3(0, 0, 0);
	blockDirs[367] = make_int3(0, 0, 0);
	// Dual node idx:  92
	blockDirs[368] = make_int3(0, 0, 0);
	blockDirs[369] = make_int3(0, 1, 0);
	blockDirs[370] = make_int3(0, 0, 0);
	blockDirs[371] = make_int3(0, 0, 0);
	// Dual node idx:  93
	blockDirs[372] = make_int3(-1, 0, 0);
	blockDirs[373] = make_int3(0, 1, 0);
	blockDirs[374] = make_int3(0, 0, 0);
	blockDirs[375] = make_int3(0, 0, 0);
	// Dual node idx:  94
	blockDirs[376] = make_int3(0, 1, 0);
	blockDirs[377] = make_int3(0, 0, 0);
	blockDirs[378] = make_int3(0, 0, 0);
	blockDirs[379] = make_int3(-1, 0, 0);
	// Dual node idx:  95
	blockDirs[380] = make_int3(0, 0, 0);
	blockDirs[381] = make_int3(0, 0, 0);
	blockDirs[382] = make_int3(0, 0, 0);
	blockDirs[383] = make_int3(0, 0, 0);
	// Dual node idx:  96
	blockDirs[384] = make_int3(0, 1, 0);
	blockDirs[385] = make_int3(0, 0, 0);
	blockDirs[386] = make_int3(0, 0, 0);
	blockDirs[387] = make_int3(0, 0, 0);
	// Dual node idx:  97
	blockDirs[388] = make_int3(0, 0, 0);
	blockDirs[389] = make_int3(0, 1, 0);
	blockDirs[390] = make_int3(0, 0, 0);
	blockDirs[391] = make_int3(0, 0, 0);
	// Dual node idx:  98
	blockDirs[392] = make_int3(0, 0, 0);
	blockDirs[393] = make_int3(0, 0, 0);
	blockDirs[394] = make_int3(0, 0, 0);
	blockDirs[395] = make_int3(0, 0, 0);
	// Dual node idx:  99
	blockDirs[396] = make_int3(0, 1, 0);
	blockDirs[397] = make_int3(0, 0, 0);
	blockDirs[398] = make_int3(1, 0, 0);
	blockDirs[399] = make_int3(0, 0, 0);
	// Dual node idx:  100
	blockDirs[400] = make_int3(0, 0, 0);
	blockDirs[401] = make_int3(0, 0, 0);
	blockDirs[402] = make_int3(0, 0, 0);
	blockDirs[403] = make_int3(0, 0, 0);
	// Dual node idx:  101
	blockDirs[404] = make_int3(1, 0, 0);
	blockDirs[405] = make_int3(0, 1, 0);
	blockDirs[406] = make_int3(0, 0, 0);
	blockDirs[407] = make_int3(0, 0, 0);
	// Dual node idx:  102
	blockDirs[408] = make_int3(0, 0, 0);
	blockDirs[409] = make_int3(0, 1, 0);
	blockDirs[410] = make_int3(0, 0, 0);
	blockDirs[411] = make_int3(0, 0, 0);
	// Dual node idx:  103
	blockDirs[412] = make_int3(0, 1, 0);
	blockDirs[413] = make_int3(0, 0, 0);
	blockDirs[414] = make_int3(0, 0, 0);
	blockDirs[415] = make_int3(0, 0, 0);
	// Dual node idx:  104
	blockDirs[416] = make_int3(1, 0, 0);
	blockDirs[417] = make_int3(0, 0, 0);
	blockDirs[418] = make_int3(0, 0, 0);
	blockDirs[419] = make_int3(0, 0, 0);
	// Dual node idx:  105
	blockDirs[420] = make_int3(0, 0, 0);
	blockDirs[421] = make_int3(0, 0, 0);
	blockDirs[422] = make_int3(0, -1, 0);
	blockDirs[423] = make_int3(0, 0, 0);
	// Dual node idx:  106
	blockDirs[424] = make_int3(0, 0, 1);
	blockDirs[425] = make_int3(0, 0, 0);
	blockDirs[426] = make_int3(-1, 0, 0);
	blockDirs[427] = make_int3(0, 0, 0);
	// Dual node idx:  107
	blockDirs[428] = make_int3(0, 0, 0);
	blockDirs[429] = make_int3(0, 0, 0);
	blockDirs[430] = make_int3(0, 0, 0);
	blockDirs[431] = make_int3(0, 0, 0);
	// Dual node idx:  108
	blockDirs[432] = make_int3(0, 0, 0);
	blockDirs[433] = make_int3(0, 0, 0);
	blockDirs[434] = make_int3(0, 0, 0);
	blockDirs[435] = make_int3(0, 0, 0);
	// Dual node idx:  109
	blockDirs[436] = make_int3(0, 0, 0);
	blockDirs[437] = make_int3(0, 0, 0);
	blockDirs[438] = make_int3(0, 0, 0);
	blockDirs[439] = make_int3(0, 0, 0);
	// Dual node idx:  110
	blockDirs[440] = make_int3(0, 0, 0);
	blockDirs[441] = make_int3(0, 0, 0);
	blockDirs[442] = make_int3(0, 0, 0);
	blockDirs[443] = make_int3(0, 0, 0);
	// Dual node idx:  111
	blockDirs[444] = make_int3(0, 0, 0);
	blockDirs[445] = make_int3(0, 0, 0);
	blockDirs[446] = make_int3(0, 0, 0);
	blockDirs[447] = make_int3(0, 0, 0);
	// Dual node idx:  112
	blockDirs[448] = make_int3(0, 0, 0);
	blockDirs[449] = make_int3(0, 0, 0);
	blockDirs[450] = make_int3(0, 0, 0);
	blockDirs[451] = make_int3(0, 0, 0);
	// Dual node idx:  113
	blockDirs[452] = make_int3(0, 0, 0);
	blockDirs[453] = make_int3(0, 0, 0);
	blockDirs[454] = make_int3(0, 0, 0);
	blockDirs[455] = make_int3(0, 0, 0);
	// Dual node idx:  114
	blockDirs[456] = make_int3(0, -1, 0);
	blockDirs[457] = make_int3(0, 0, 0);
	blockDirs[458] = make_int3(-1, 0, 0);
	blockDirs[459] = make_int3(0, 0, 0);
	// Dual node idx:  115
	blockDirs[460] = make_int3(0, -1, 0);
	blockDirs[461] = make_int3(0, 0, 1);
	blockDirs[462] = make_int3(0, 0, 0);
	blockDirs[463] = make_int3(0, 0, 0);
	// Dual node idx:  116
	blockDirs[464] = make_int3(0, 0, 0);
	blockDirs[465] = make_int3(0, 0, 0);
	blockDirs[466] = make_int3(0, 0, 0);
	blockDirs[467] = make_int3(0, 0, 0);
	// Dual node idx:  117
	blockDirs[468] = make_int3(-1, 0, 0);
	blockDirs[469] = make_int3(0, 0, 1);
	blockDirs[470] = make_int3(0, 0, 0);
	blockDirs[471] = make_int3(0, 0, 0);
	// Dual node idx:  118
	blockDirs[472] = make_int3(0, 0, 0);
	blockDirs[473] = make_int3(0, 0, 1);
	blockDirs[474] = make_int3(0, 0, 0);
	blockDirs[475] = make_int3(0, 0, 0);
	// Dual node idx:  119
	blockDirs[476] = make_int3(0, 0, 0);
	blockDirs[477] = make_int3(0, 0, 0);
	blockDirs[478] = make_int3(-1, 0, 0);
	blockDirs[479] = make_int3(0, 0, 0);
	// Dual node idx:  120
	blockDirs[480] = make_int3(0, 0, 1);
	blockDirs[481] = make_int3(0, 0, 0);
	blockDirs[482] = make_int3(0, 0, 0);
	blockDirs[483] = make_int3(0, -1, 0);
	// Dual node idx:  121
	blockDirs[484] = make_int3(0, 0, 0);
	blockDirs[485] = make_int3(0, 0, 0);
	blockDirs[486] = make_int3(0, 0, 0);
	blockDirs[487] = make_int3(0, 0, 0);
	// Dual node idx:  122
	blockDirs[488] = make_int3(0, 0, 0);
	blockDirs[489] = make_int3(0, 0, 0);
	blockDirs[490] = make_int3(0, 0, 0);
	blockDirs[491] = make_int3(0, 0, 0);
	// Dual node idx:  123
	blockDirs[492] = make_int3(0, 0, 0);
	blockDirs[493] = make_int3(0, 0, 1);
	blockDirs[494] = make_int3(0, 0, 0);
	blockDirs[495] = make_int3(0, 0, 0);
	// Dual node idx:  124
	blockDirs[496] = make_int3(0, 0, 0);
	blockDirs[497] = make_int3(0, 0, 0);
	blockDirs[498] = make_int3(0, 0, 0);
	blockDirs[499] = make_int3(0, 0, 0);
	// Dual node idx:  125
	blockDirs[500] = make_int3(0, 0, 0);
	blockDirs[501] = make_int3(0, 0, 1);
	blockDirs[502] = make_int3(0, 0, 0);
	blockDirs[503] = make_int3(0, 0, 0);
	// Dual node idx:  126
	blockDirs[504] = make_int3(1, 0, 0);
	blockDirs[505] = make_int3(0, 0, 0);
	blockDirs[506] = make_int3(0, 0, 0);
	blockDirs[507] = make_int3(0, 0, 0);
	// Dual node idx:  127
	blockDirs[508] = make_int3(1, 0, 0);
	blockDirs[509] = make_int3(0, 0, 1);
	blockDirs[510] = make_int3(0, 0, 0);
	blockDirs[511] = make_int3(0, 0, 0);
	// Dual node idx:  128
	blockDirs[512] = make_int3(0, 0, 0);
	blockDirs[513] = make_int3(0, 0, 1);
	blockDirs[514] = make_int3(0, 0, 0);
	blockDirs[515] = make_int3(0, 0, 0);
	// Dual node idx:  129
	blockDirs[516] = make_int3(0, 0, 1);
	blockDirs[517] = make_int3(0, 0, 0);
	blockDirs[518] = make_int3(1, 0, 0);
	blockDirs[519] = make_int3(0, 0, 0);
	// Dual node idx:  130
	blockDirs[520] = make_int3(0, 0, 0);
	blockDirs[521] = make_int3(1, 0, 0);
	blockDirs[522] = make_int3(0, 0, 0);
	blockDirs[523] = make_int3(0, 0, 0);
	// Dual node idx:  131
	blockDirs[524] = make_int3(0, 0, 0);
	blockDirs[525] = make_int3(0, 0, 0);
	blockDirs[526] = make_int3(0, 0, 0);
	blockDirs[527] = make_int3(0, 0, 0);
	// Dual node idx:  132
	blockDirs[528] = make_int3(0, 0, 1);
	blockDirs[529] = make_int3(0, 0, 0);
	blockDirs[530] = make_int3(0, 0, 0);
	blockDirs[531] = make_int3(0, 0, 0);
	// Dual node idx:  133
	blockDirs[532] = make_int3(0, 0, 0);
	blockDirs[533] = make_int3(0, 0, 1);
	blockDirs[534] = make_int3(0, 0, 0);
	blockDirs[535] = make_int3(0, 0, 0);
	// Dual node idx:  134
	blockDirs[536] = make_int3(0, 0, 1);
	blockDirs[537] = make_int3(0, 0, 0);
	blockDirs[538] = make_int3(0, 1, 0);
	blockDirs[539] = make_int3(0, 0, 0);
	// Dual node idx:  135
	blockDirs[540] = make_int3(0, 0, 1);
	blockDirs[541] = make_int3(0, 0, 0);
	blockDirs[542] = make_int3(0, 0, 0);
	blockDirs[543] = make_int3(0, 0, 0);

	valueInds.resize(INDICES_PER_BLOCK);
	// Dual node idx:  0
	valueInds[0] = 3;
	valueInds[1] = 44;
	valueInds[2] = 9;
	valueInds[3] = 15;
	// Dual node idx:  1
	valueInds[4] = 68;
	valueInds[5] = 24;
	valueInds[6] = 75;
	valueInds[7] = 88;
	// Dual node idx:  2
	valueInds[8] = 116;
	valueInds[9] = 36;
	valueInds[10] = 21;
	valueInds[11] = 61;
	// Dual node idx:  3
	valueInds[12] = 130;
	valueInds[13] = 31;
	valueInds[14] = 69;
	valueInds[15] = 0;
	// Dual node idx:  4
	valueInds[16] = 16;
	valueInds[17] = 59;
	valueInds[18] = 51;
	valueInds[19] = 39;
	// Dual node idx:  5
	valueInds[20] = 133;
	valueInds[21] = 68;
	valueInds[22] = 76;
	valueInds[23] = 113;
	// Dual node idx:  6
	valueInds[24] = 98;
	valueInds[25] = 74;
	valueInds[26] = 84;
	valueInds[27] = 62;
	// Dual node idx:  7
	valueInds[28] = 17;
	valueInds[29] = 58;
	valueInds[30] = 57;
	valueInds[31] = 42;
	// Dual node idx:  8
	valueInds[32] = 22;
	valueInds[33] = 91;
	valueInds[34] = 85;
	valueInds[35] = 74;
	// Dual node idx:  9
	valueInds[36] = 104;
	valueInds[37] = 0;
	valueInds[38] = 126;
	valueInds[39] = 32;
	// Dual node idx:  10
	valueInds[40] = 94;
	valueInds[41] = 30;
	valueInds[42] = 114;
	valueInds[43] = 73;
	// Dual node idx:  11
	valueInds[44] = 74;
	valueInds[45] = 32;
	valueInds[46] = 36;
	valueInds[47] = 15;
	// Dual node idx:  12
	valueInds[48] = 20;
	valueInds[49] = 40;
	valueInds[50] = 118;
	valueInds[51] = 42;
	// Dual node idx:  13
	valueInds[52] = 59;
	valueInds[53] = 58;
	valueInds[54] = 27;
	valueInds[55] = 49;
	// Dual node idx:  14
	valueInds[56] = 19;
	valueInds[57] = 78;
	valueInds[58] = 132;
	valueInds[59] = 86;
	// Dual node idx:  15
	valueInds[60] = 62;
	valueInds[61] = 0;
	valueInds[62] = 65;
	valueInds[63] = 11;
	// Dual node idx:  16
	valueInds[64] = 4;
	valueInds[65] = 49;
	valueInds[66] = 24;
	valueInds[67] = 38;
	// Dual node idx:  17
	valueInds[68] = 7;
	valueInds[69] = 49;
	valueInds[70] = 54;
	valueInds[71] = 20;
	// Dual node idx:  18
	valueInds[72] = 53;
	valueInds[73] = 83;
	valueInds[74] = 88;
	valueInds[75] = 40;
	// Dual node idx:  19
	valueInds[76] = 106;
	valueInds[77] = 40;
	valueInds[78] = 14;
	valueInds[79] = 89;
	// Dual node idx:  20
	valueInds[80] = 12;
	valueInds[81] = 47;
	valueInds[82] = 117;
	valueInds[83] = 17;
	// Dual node idx:  21
	valueInds[84] = 2;
	valueInds[85] = 52;
	valueInds[86] = 109;
	valueInds[87] = 27;
	// Dual node idx:  22
	valueInds[88] = 102;
	valueInds[89] = 51;
	valueInds[90] = 98;
	valueInds[91] = 8;
	// Dual node idx:  23
	valueInds[92] = 47;
	valueInds[93] = 40;
	valueInds[94] = 78;
	valueInds[95] = 43;
	// Dual node idx:  24
	valueInds[96] = 48;
	valueInds[97] = 54;
	valueInds[98] = 16;
	valueInds[99] = 1;
	// Dual node idx:  25
	valueInds[100] = 33;
	valueInds[101] = 30;
	valueInds[102] = 31;
	valueInds[103] = 45;
	// Dual node idx:  26
	valueInds[104] = 57;
	valueInds[105] = 55;
	valueInds[106] = 54;
	valueInds[107] = 123;
	// Dual node idx:  27
	valueInds[108] = 82;
	valueInds[109] = 13;
	valueInds[110] = 21;
	valueInds[111] = 41;
	// Dual node idx:  28
	valueInds[112] = 71;
	valueInds[113] = 55;
	valueInds[114] = 81;
	valueInds[115] = 120;
	// Dual node idx:  29
	valueInds[116] = 133;
	valueInds[117] = 42;
	valueInds[118] = 116;
	valueInds[119] = 110;
	// Dual node idx:  30
	valueInds[120] = 112;
	valueInds[121] = 37;
	valueInds[122] = 25;
	valueInds[123] = 10;
	// Dual node idx:  31
	valueInds[124] = 25;
	valueInds[125] = 109;
	valueInds[126] = 41;
	valueInds[127] = 3;
	// Dual node idx:  32
	valueInds[128] = 85;
	valueInds[129] = 11;
	valueInds[130] = 111;
	valueInds[131] = 9;
	// Dual node idx:  33
	valueInds[132] = 25;
	valueInds[133] = 38;
	valueInds[134] = 46;
	valueInds[135] = 72;
	// Dual node idx:  34
	valueInds[136] = 134;
	valueInds[137] = 113;
	valueInds[138] = 106;
	valueInds[139] = 94;
	// Dual node idx:  35
	valueInds[140] = 78;
	valueInds[141] = 44;
	valueInds[142] = 80;
	valueInds[143] = 62;
	// Dual node idx:  36
	valueInds[144] = 2;
	valueInds[145] = 110;
	valueInds[146] = 107;
	valueInds[147] = 11;
	// Dual node idx:  37
	valueInds[148] = 39;
	valueInds[149] = 30;
	valueInds[150] = 38;
	valueInds[151] = 92;
	// Dual node idx:  38
	valueInds[152] = 37;
	valueInds[153] = 33;
	valueInds[154] = 16;
	valueInds[155] = 93;
	// Dual node idx:  39
	valueInds[156] = 37;
	valueInds[157] = 108;
	valueInds[158] = 4;
	valueInds[159] = 91;
	// Dual node idx:  40
	valueInds[160] = 23;
	valueInds[161] = 12;
	valueInds[162] = 19;
	valueInds[163] = 18;
	// Dual node idx:  41
	valueInds[164] = 46;
	valueInds[165] = 27;
	valueInds[166] = 43;
	valueInds[167] = 31;
	// Dual node idx:  42
	valueInds[168] = 12;
	valueInds[169] = 83;
	valueInds[170] = 7;
	valueInds[171] = 29;
	// Dual node idx:  43
	valueInds[172] = 23;
	valueInds[173] = 53;
	valueInds[174] = 41;
	valueInds[175] = 44;
	// Dual node idx:  44
	valueInds[176] = 90;
	valueInds[177] = 43;
	valueInds[178] = 35;
	valueInds[179] = 0;
	// Dual node idx:  45
	valueInds[180] = 73;
	valueInds[181] = 25;
	valueInds[182] = 56;
	valueInds[183] = 69;
	// Dual node idx:  46
	valueInds[184] = 41;
	valueInds[185] = 49;
	valueInds[186] = 47;
	valueInds[187] = 33;
	// Dual node idx:  47
	valueInds[188] = 23;
	valueInds[189] = 20;
	valueInds[190] = 77;
	valueInds[191] = 46;
	// Dual node idx:  48
	valueInds[192] = 51;
	valueInds[193] = 55;
	valueInds[194] = 97;
	valueInds[195] = 24;
	// Dual node idx:  49
	valueInds[196] = 17;
	valueInds[197] = 13;
	valueInds[198] = 16;
	valueInds[199] = 46;
	// Dual node idx:  50
	valueInds[200] = 70;
	valueInds[201] = 67;
	valueInds[202] = 64;
	valueInds[203] = 55;
	// Dual node idx:  51
	valueInds[204] = 48;
	valueInds[205] = 67;
	valueInds[206] = 22;
	valueInds[207] = 4;
	// Dual node idx:  52
	valueInds[208] = 107;
	valueInds[209] = 21;
	valueInds[210] = 108;
	valueInds[211] = 59;
	// Dual node idx:  53
	valueInds[212] = 82;
	valueInds[213] = 18;
	valueInds[214] = 60;
	valueInds[215] = 43;
	// Dual node idx:  54
	valueInds[216] = 26;
	valueInds[217] = 24;
	valueInds[218] = 17;
	valueInds[219] = 115;
	// Dual node idx:  55
	valueInds[220] = 48;
	valueInds[221] = 50;
	valueInds[222] = 28;
	valueInds[223] = 26;
	// Dual node idx:  56
	valueInds[224] = 45;
	valueInds[225] = 72;
	valueInds[226] = 102;
	valueInds[227] = 67;
	// Dual node idx:  57
	valueInds[228] = 26;
	valueInds[229] = 64;
	valueInds[230] = 7;
	valueInds[231] = 125;
	// Dual node idx:  58
	valueInds[232] = 63;
	valueInds[233] = 13;
	valueInds[234] = 84;
	valueInds[235] = 7;
	// Dual node idx:  59
	valueInds[236] = 66;
	valueInds[237] = 13;
	valueInds[238] = 52;
	valueInds[239] = 4;
	// Dual node idx:  60
	valueInds[240] = 92;
	valueInds[241] = 93;
	valueInds[242] = 90;
	valueInds[243] = 53;
	// Dual node idx:  61
	valueInds[244] = 87;
	valueInds[245] = 74;
	valueInds[246] = 82;
	valueInds[247] = 2;
	// Dual node idx:  62
	valueInds[248] = 35;
	valueInds[249] = 15;
	valueInds[250] = 63;
	valueInds[251] = 6;
	// Dual node idx:  63
	valueInds[252] = 62;
	valueInds[253] = 66;
	valueInds[254] = 64;
	valueInds[255] = 58;
	// Dual node idx:  64
	valueInds[256] = 63;
	valueInds[257] = 50;
	valueInds[258] = 79;
	valueInds[259] = 57;
	// Dual node idx:  65
	valueInds[260] = 69;
	valueInds[261] = 15;
	valueInds[262] = 66;
	valueInds[263] = 107;
	// Dual node idx:  66
	valueInds[264] = 65;
	valueInds[265] = 63;
	valueInds[266] = 67;
	valueInds[267] = 59;
	// Dual node idx:  67
	valueInds[268] = 56;
	valueInds[269] = 50;
	valueInds[270] = 66;
	valueInds[271] = 51;
	// Dual node idx:  68
	valueInds[272] = 115;
	valueInds[273] = 1;
	valueInds[274] = 5;
	valueInds[275] = 134;
	// Dual node idx:  69
	valueInds[276] = 45;
	valueInds[277] = 3;
	valueInds[278] = 122;
	valueInds[279] = 65;
	// Dual node idx:  70
	valueInds[280] = 77;
	valueInds[281] = 72;
	valueInds[282] = 71;
	valueInds[283] = 50;
	// Dual node idx:  71
	valueInds[284] = 99;
	valueInds[285] = 70;
	valueInds[286] = 129;
	valueInds[287] = 28;
	// Dual node idx:  72
	valueInds[288] = 101;
	valueInds[289] = 33;
	valueInds[290] = 56;
	valueInds[291] = 70;
	// Dual node idx:  73
	valueInds[292] = 10;
	valueInds[293] = 45;
	valueInds[294] = 103;
	valueInds[295] = 121;
	// Dual node idx:  74
	valueInds[296] = 61;
	valueInds[297] = 8;
	valueInds[298] = 6;
	valueInds[299] = 11;
	// Dual node idx:  75
	valueInds[300] = 97;
	valueInds[301] = 1;
	valueInds[302] = 133;
	valueInds[303] = 83;
	// Dual node idx:  76
	valueInds[304] = 5;
	valueInds[305] = 105;
	valueInds[306] = 96;
	valueInds[307] = 91;
	// Dual node idx:  77
	valueInds[308] = 127;
	valueInds[309] = 47;
	valueInds[310] = 79;
	valueInds[311] = 70;
	// Dual node idx:  78
	valueInds[312] = 14;
	valueInds[313] = 23;
	valueInds[314] = 79;
	valueInds[315] = 35;
	// Dual node idx:  79
	valueInds[316] = 78;
	valueInds[317] = 77;
	valueInds[318] = 128;
	valueInds[319] = 64;
	// Dual node idx:  80
	valueInds[320] = 86;
	valueInds[321] = 100;
	valueInds[322] = 98;
	valueInds[323] = 35;
	// Dual node idx:  81
	valueInds[324] = 28;
	valueInds[325] = 97;
	valueInds[326] = 86;
	valueInds[327] = 135;
	// Dual node idx:  82
	valueInds[328] = 61;
	valueInds[329] = 84;
	valueInds[330] = 53;
	valueInds[331] = 27;
	// Dual node idx:  83
	valueInds[332] = 84;
	valueInds[333] = 18;
	valueInds[334] = 75;
	valueInds[335] = 42;
	// Dual node idx:  84
	valueInds[336] = 6;
	valueInds[337] = 82;
	valueInds[338] = 83;
	valueInds[339] = 58;
	// Dual node idx:  85
	valueInds[340] = 96;
	valueInds[341] = 8;
	valueInds[342] = 103;
	valueInds[343] = 32;
	// Dual node idx:  86
	valueInds[344] = 99;
	valueInds[345] = 80;
	valueInds[346] = 81;
	valueInds[347] = 14;
	// Dual node idx:  87
	valueInds[348] = 92;
	valueInds[349] = 91;
	valueInds[350] = 113;
	valueInds[351] = 61;
	// Dual node idx:  88
	valueInds[352] = 93;
	valueInds[353] = 1;
	valueInds[354] = 89;
	valueInds[355] = 18;
	// Dual node idx:  89
	valueInds[356] = 134;
	valueInds[357] = 88;
	valueInds[358] = 99;
	valueInds[359] = 19;
	// Dual node idx:  90
	valueInds[360] = 100;
	valueInds[361] = 60;
	valueInds[362] = 104;
	valueInds[363] = 44;
	// Dual node idx:  91
	valueInds[364] = 76;
	valueInds[365] = 39;
	valueInds[366] = 87;
	valueInds[367] = 8;
	// Dual node idx:  92
	valueInds[368] = 94;
	valueInds[369] = 37;
	valueInds[370] = 87;
	valueInds[371] = 60;
	// Dual node idx:  93
	valueInds[372] = 101;
	valueInds[373] = 38;
	valueInds[374] = 60;
	valueInds[375] = 88;
	// Dual node idx:  94
	valueInds[376] = 10;
	valueInds[377] = 92;
	valueInds[378] = 34;
	valueInds[379] = 104;
	// Dual node idx:  95
	valueInds[380] = 117;
	valueInds[381] = 115;
	valueInds[382] = 114;
	valueInds[383] = 112;
	// Dual node idx:  96
	valueInds[384] = 120;
	valueInds[385] = 76;
	valueInds[386] = 135;
	valueInds[387] = 85;
	// Dual node idx:  97
	valueInds[388] = 81;
	valueInds[389] = 48;
	valueInds[390] = 98;
	valueInds[391] = 75;
	// Dual node idx:  98
	valueInds[392] = 97;
	valueInds[393] = 22;
	valueInds[394] = 80;
	valueInds[395] = 6;
	// Dual node idx:  99
	valueInds[396] = 71;
	valueInds[397] = 101;
	valueInds[398] = 89;
	valueInds[399] = 86;
	// Dual node idx:  100
	valueInds[400] = 102;
	valueInds[401] = 101;
	valueInds[402] = 90;
	valueInds[403] = 80;
	// Dual node idx:  101
	valueInds[404] = 93;
	valueInds[405] = 72;
	valueInds[406] = 100;
	valueInds[407] = 99;
	// Dual node idx:  102
	valueInds[408] = 100;
	valueInds[409] = 56;
	valueInds[410] = 103;
	valueInds[411] = 22;
	// Dual node idx:  103
	valueInds[412] = 73;
	valueInds[413] = 102;
	valueInds[414] = 104;
	valueInds[415] = 85;
	// Dual node idx:  104
	valueInds[416] = 94;
	valueInds[417] = 90;
	valueInds[418] = 103;
	valueInds[419] = 9;
	// Dual node idx:  105
	valueInds[420] = 123;
	valueInds[421] = 115;
	valueInds[422] = 76;
	valueInds[423] = 108;
	// Dual node idx:  106
	valueInds[424] = 19;
	valueInds[425] = 118;
	valueInds[426] = 126;
	valueInds[427] = 34;
	// Dual node idx:  107
	valueInds[428] = 124;
	valueInds[429] = 36;
	valueInds[430] = 52;
	valueInds[431] = 65;
	// Dual node idx:  108
	valueInds[432] = 52;
	valueInds[433] = 112;
	valueInds[434] = 105;
	valueInds[435] = 39;
	// Dual node idx:  109
	valueInds[436] = 21;
	valueInds[437] = 112;
	valueInds[438] = 119;
	valueInds[439] = 31;
	// Dual node idx:  110
	valueInds[440] = 125;
	valueInds[441] = 29;
	valueInds[442] = 111;
	valueInds[443] = 36;
	// Dual node idx:  111
	valueInds[444] = 135;
	valueInds[445] = 110;
	valueInds[446] = 132;
	valueInds[447] = 32;
	// Dual node idx:  112
	valueInds[448] = 109;
	valueInds[449] = 108;
	valueInds[450] = 95;
	valueInds[451] = 30;
	// Dual node idx:  113
	valueInds[452] = 34;
	valueInds[453] = 5;
	valueInds[454] = 116;
	valueInds[455] = 87;
	// Dual node idx:  114
	valueInds[456] = 134;
	valueInds[457] = 95;
	valueInds[458] = 129;
	valueInds[459] = 10;
	// Dual node idx:  115
	valueInds[460] = 68;
	valueInds[461] = 54;
	valueInds[462] = 105;
	valueInds[463] = 95;
	// Dual node idx:  116
	valueInds[464] = 118;
	valueInds[465] = 29;
	valueInds[466] = 113;
	valueInds[467] = 2;
	// Dual node idx:  117
	valueInds[468] = 127;
	valueInds[469] = 20;
	valueInds[470] = 119;
	valueInds[471] = 95;
	// Dual node idx:  118
	valueInds[472] = 106;
	valueInds[473] = 12;
	valueInds[474] = 119;
	valueInds[475] = 116;
	// Dual node idx:  119
	valueInds[476] = 118;
	valueInds[477] = 117;
	valueInds[478] = 130;
	valueInds[479] = 109;
	// Dual node idx:  120
	valueInds[480] = 28;
	valueInds[481] = 123;
	valueInds[482] = 121;
	valueInds[483] = 96;
	// Dual node idx:  121
	valueInds[484] = 129;
	valueInds[485] = 122;
	valueInds[486] = 120;
	valueInds[487] = 73;
	// Dual node idx:  122
	valueInds[488] = 121;
	valueInds[489] = 131;
	valueInds[490] = 124;
	valueInds[491] = 69;
	// Dual node idx:  123
	valueInds[492] = 120;
	valueInds[493] = 26;
	valueInds[494] = 124;
	valueInds[495] = 105;
	// Dual node idx:  124
	valueInds[496] = 123;
	valueInds[497] = 125;
	valueInds[498] = 122;
	valueInds[499] = 107;
	// Dual node idx:  125
	valueInds[500] = 128;
	valueInds[501] = 57;
	valueInds[502] = 124;
	valueInds[503] = 110;
	// Dual node idx:  126
	valueInds[504] = 106;
	valueInds[505] = 130;
	valueInds[506] = 132;
	valueInds[507] = 9;
	// Dual node idx:  127
	valueInds[508] = 117;
	valueInds[509] = 77;
	valueInds[510] = 131;
	valueInds[511] = 129;
	// Dual node idx:  128
	valueInds[512] = 131;
	valueInds[513] = 79;
	valueInds[514] = 132;
	valueInds[515] = 125;
	// Dual node idx:  129
	valueInds[516] = 71;
	valueInds[517] = 127;
	valueInds[518] = 114;
	valueInds[519] = 121;
	// Dual node idx:  130
	valueInds[520] = 131;
	valueInds[521] = 119;
	valueInds[522] = 126;
	valueInds[523] = 3;
	// Dual node idx:  131
	valueInds[524] = 128;
	valueInds[525] = 127;
	valueInds[526] = 130;
	valueInds[527] = 122;
	// Dual node idx:  132
	valueInds[528] = 14;
	valueInds[529] = 128;
	valueInds[530] = 126;
	valueInds[531] = 111;
	// Dual node idx:  133
	valueInds[532] = 5;
	valueInds[533] = 75;
	valueInds[534] = 135;
	valueInds[535] = 29;
	// Dual node idx:  134
	valueInds[536] = 89;
	valueInds[537] = 68;
	valueInds[538] = 114;
	valueInds[539] = 34;
	// Dual node idx:  135
	valueInds[540] = 81;
	valueInds[541] = 133;
	valueInds[542] = 96;
	valueInds[543] = 111;

	hodges.resize(INDICES_PER_BLOCK);
	hodges[0] = 2.6435266297444953;
	hodges[1] = 2.6435266297444953;
	hodges[2] = 1.4161749802202666;
	hodges[3] = 1.73916225641085;
	hodges[4] = 1.7391622564108518;
	hodges[5] = 2.6435266297444895;
	hodges[6] = 1.416174980220265;
	hodges[7] = 2.6435266297444953;
	hodges[8] = 2.6435266297444908;
	hodges[9] = 1.7391622564108513;
	hodges[10] = 2.6435266297444935;
	hodges[11] = 1.4161749802202643;
	hodges[12] = 1.7391622564108506;
	hodges[13] = 2.6435266297444886;
	hodges[14] = 1.416174980220265;
	hodges[15] = 2.6435266297444948;
	hodges[16] = 1.4161749802202657;
	hodges[17] = 1.7391622564108502;
	hodges[18] = 2.643526629744493;
	hodges[19] = 2.6435266297444948;
	hodges[20] = 1.8357823817670096;
	hodges[21] = 1.8357823817670096;
	hodges[22] = 1.8357823817670096;
	hodges[23] = 1.8357823817670096;
	hodges[24] = 2.6435266297444917;
	hodges[25] = 1.7391622564108513;
	hodges[26] = 2.6435266297444935;
	hodges[27] = 1.4161749802202643;
	hodges[28] = 1.4161749802202657;
	hodges[29] = 1.7391622564108502;
	hodges[30] = 2.6435266297444948;
	hodges[31] = 2.6435266297444948;
	hodges[32] = 2.6435266297444953;
	hodges[33] = 2.6435266297444953;
	hodges[34] = 1.4161749802202666;
	hodges[35] = 1.7391622564108504;
	hodges[36] = 2.6435266297444908;
	hodges[37] = 1.4161749802202683;
	hodges[38] = 2.6435266297444908;
	hodges[39] = 1.739162256410848;
	hodges[40] = 2.0869947076930218;
	hodges[41] = 1.4686259054136079;
	hodges[42] = 2.0869947076930226;
	hodges[43] = 2.0869947076930213;
	hodges[44] = 1.8357823817670105;
	hodges[45] = 1.8357823817670131;
	hodges[46] = 1.8357823817670105;
	hodges[47] = 1.8357823817670098;
	hodges[48] = 2.0869947076930218;
	hodges[49] = 1.4686259054136079;
	hodges[50] = 2.0869947076930222;
	hodges[51] = 2.0869947076930231;
	hodges[52] = 1.83578238176701;
	hodges[53] = 1.8357823817670105;
	hodges[54] = 1.83578238176701;
	hodges[55] = 1.8357823817670096;
	hodges[56] = 1.7391622564108506;
	hodges[57] = 1.4161749802202657;
	hodges[58] = 2.6435266297444908;
	hodges[59] = 2.6435266297444944;
	hodges[60] = 2.0869947076930222;
	hodges[61] = 2.0869947076930209;
	hodges[62] = 2.0869947076930235;
	hodges[63] = 1.4686259054136077;
	hodges[64] = 1.4161749802202652;
	hodges[65] = 1.7391622564108522;
	hodges[66] = 2.6435266297444935;
	hodges[67] = 2.6435266297444922;
	hodges[68] = 1.4161749802202652;
	hodges[69] = 1.7391622564108522;
	hodges[70] = 2.6435266297444935;
	hodges[71] = 2.6435266297444922;
	hodges[72] = 2.0869947076930231;
	hodges[73] = 2.0869947076930222;
	hodges[74] = 2.0869947076930222;
	hodges[75] = 1.4686259054136077;
	hodges[76] = 2.0869947076930213;
	hodges[77] = 1.4686259054136079;
	hodges[78] = 2.0869947076930213;
	hodges[79] = 2.0869947076930226;
	hodges[80] = 1.7391622564108511;
	hodges[81] = 1.4161749802202648;
	hodges[82] = 2.6435266297444953;
	hodges[83] = 2.6435266297444926;
	hodges[84] = 2.6435266297444935;
	hodges[85] = 1.4161749802202659;
	hodges[86] = 2.643526629744493;
	hodges[87] = 1.7391622564108522;
	hodges[88] = 1.7391622564108506;
	hodges[89] = 2.6435266297444922;
	hodges[90] = 1.416174980220265;
	hodges[91] = 2.6435266297444948;
	hodges[92] = 2.0869947076930222;
	hodges[93] = 1.4686259054136082;
	hodges[94] = 2.0869947076930226;
	hodges[95] = 2.0869947076930231;
	hodges[96] = 1.7391622564108513;
	hodges[97] = 1.4161749802202648;
	hodges[98] = 2.6435266297444944;
	hodges[99] = 2.6435266297444953;
	hodges[100] = 2.0869947076930222;
	hodges[101] = 1.4686259054136082;
	hodges[102] = 2.0869947076930231;
	hodges[103] = 2.0869947076930218;
	hodges[104] = 2.0869947076930231;
	hodges[105] = 1.4686259054136082;
	hodges[106] = 2.0869947076930226;
	hodges[107] = 2.0869947076930218;
	hodges[108] = 2.0869947076930226;
	hodges[109] = 1.4686259054136086;
	hodges[110] = 2.0869947076930222;
	hodges[111] = 2.08699470769302;
	hodges[112] = 2.0869947076930226;
	hodges[113] = 1.4686259054136079;
	hodges[114] = 2.0869947076930213;
	hodges[115] = 2.0869947076930218;
	hodges[116] = 1.7391622564108509;
	hodges[117] = 2.6435266297444886;
	hodges[118] = 1.4161749802202652;
	hodges[119] = 2.6435266297444944;
	hodges[120] = 1.83578238176701;
	hodges[121] = 1.8357823817670098;
	hodges[122] = 1.8357823817670105;
	hodges[123] = 1.83578238176701;
	hodges[124] = 1.7391622564108526;
	hodges[125] = 1.4161749802202643;
	hodges[126] = 2.6435266297444953;
	hodges[127] = 2.6435266297444935;
	hodges[128] = 2.0869947076930191;
	hodges[129] = 1.4686259054136124;
	hodges[130] = 2.0869947076930191;
	hodges[131] = 2.0869947076930191;
	hodges[132] = 1.7391622564108513;
	hodges[133] = 1.4161749802202648;
	hodges[134] = 2.643526629744493;
	hodges[135] = 2.6435266297444948;
	hodges[136] = 1.4161749802202648;
	hodges[137] = 1.7391622564108526;
	hodges[138] = 2.6435266297444926;
	hodges[139] = 2.6435266297444926;
	hodges[140] = 2.6435266297444944;
	hodges[141] = 1.416174980220265;
	hodges[142] = 1.7391622564108511;
	hodges[143] = 2.6435266297444917;
	hodges[144] = 2.0869947076930226;
	hodges[145] = 2.0869947076930213;
	hodges[146] = 2.0869947076930226;
	hodges[147] = 1.4686259054136082;
	hodges[148] = 2.0869947076930231;
	hodges[149] = 1.4686259054136077;
	hodges[150] = 2.0869947076930231;
	hodges[151] = 2.0869947076930213;
	hodges[152] = 1.739162256410852;
	hodges[153] = 1.4161749802202648;
	hodges[154] = 2.6435266297444926;
	hodges[155] = 2.6435266297444953;
	hodges[156] = 1.7391622564108524;
	hodges[157] = 1.4161749802202643;
	hodges[158] = 2.6435266297444953;
	hodges[159] = 2.6435266297444935;
	hodges[160] = 1.8357823817670105;
	hodges[161] = 1.83578238176701;
	hodges[162] = 1.83578238176701;
	hodges[163] = 1.8357823817670098;
	hodges[164] = 1.4161749802202657;
	hodges[165] = 1.7391622564108502;
	hodges[166] = 2.6435266297444948;
	hodges[167] = 2.6435266297444948;
	hodges[168] = 1.7391622564108526;
	hodges[169] = 1.4161749802202643;
	hodges[170] = 2.6435266297444953;
	hodges[171] = 2.643526629744493;
	hodges[172] = 1.7391622564108524;
	hodges[173] = 1.4161749802202643;
	hodges[174] = 2.6435266297444953;
	hodges[175] = 2.6435266297444939;
	hodges[176] = 1.7391622564108506;
	hodges[177] = 2.6435266297444886;
	hodges[178] = 1.416174980220265;
	hodges[179] = 2.6435266297444948;
	hodges[180] = 1.416174980220265;
	hodges[181] = 1.7391622564108504;
	hodges[182] = 2.6435266297444953;
	hodges[183] = 2.6435266297444948;
	hodges[184] = 1.4161749802202652;
	hodges[185] = 1.739162256410852;
	hodges[186] = 2.643526629744493;
	hodges[187] = 2.6435266297444926;
	hodges[188] = 1.7391622564108513;
	hodges[189] = 1.4161749802202648;
	hodges[190] = 2.6435266297444944;
	hodges[191] = 2.6435266297444935;
	hodges[192] = 2.0869947076930226;
	hodges[193] = 1.4686259054136077;
	hodges[194] = 2.0869947076930222;
	hodges[195] = 2.0869947076930222;
	hodges[196] = 2.0869947076930222;
	hodges[197] = 1.4686259054136082;
	hodges[198] = 2.0869947076930222;
	hodges[199] = 2.0869947076930222;
	hodges[200] = 2.0869947076930209;
	hodges[201] = 2.0869947076930226;
	hodges[202] = 2.0869947076930235;
	hodges[203] = 1.4686259054136077;
	hodges[204] = 1.7391622564108522;
	hodges[205] = 1.4161749802202643;
	hodges[206] = 2.6435266297444953;
	hodges[207] = 2.6435266297444939;
	hodges[208] = 2.6435266297444935;
	hodges[209] = 1.4161749802202659;
	hodges[210] = 2.643526629744493;
	hodges[211] = 1.7391622564108522;
	hodges[212] = 2.6435266297444926;
	hodges[213] = 1.7391622564108526;
	hodges[214] = 2.6435266297444917;
	hodges[215] = 1.4161749802202643;
	hodges[216] = 1.7391622564108515;
	hodges[217] = 1.4161749802202648;
	hodges[218] = 2.6435266297444944;
	hodges[219] = 2.6435266297444953;
	hodges[220] = 1.8357823817670098;
	hodges[221] = 1.8357823817670098;
	hodges[222] = 1.83578238176701;
	hodges[223] = 1.8357823817670105;
	hodges[224] = 2.6435266297444953;
	hodges[225] = 1.4161749802202652;
	hodges[226] = 1.739162256410852;
	hodges[227] = 2.6435266297444908;
	hodges[228] = 1.7391622564108526;
	hodges[229] = 1.4161749802202643;
	hodges[230] = 2.6435266297444953;
	hodges[231] = 2.643526629744493;
	hodges[232] = 2.0869947076930226;
	hodges[233] = 1.4686259054136093;
	hodges[234] = 2.0869947076930209;
	hodges[235] = 2.08699470769302;
	hodges[236] = 2.0869947076930226;
	hodges[237] = 1.4686259054136086;
	hodges[238] = 2.0869947076930222;
	hodges[239] = 2.08699470769302;
	hodges[240] = 2.6435266297444953;
	hodges[241] = 1.4161749802202652;
	hodges[242] = 1.7391622564108515;
	hodges[243] = 2.6435266297444904;
	hodges[244] = 2.6435266297444913;
	hodges[245] = 1.7391622564108513;
	hodges[246] = 2.6435266297444953;
	hodges[247] = 1.4161749802202643;
	hodges[248] = 2.6435266297444917;
	hodges[249] = 1.7391622564108511;
	hodges[250] = 2.6435266297444935;
	hodges[251] = 1.4161749802202643;
	hodges[252] = 2.6435266297444935;
	hodges[253] = 1.4161749802202657;
	hodges[254] = 2.643526629744493;
	hodges[255] = 1.7391622564108524;
	hodges[256] = 2.643526629744493;
	hodges[257] = 1.7391622564108524;
	hodges[258] = 2.6435266297444913;
	hodges[259] = 1.4161749802202641;
	hodges[260] = 2.6435266297444917;
	hodges[261] = 1.7391622564108522;
	hodges[262] = 2.6435266297444953;
	hodges[263] = 1.4161749802202643;
	hodges[264] = 2.6435266297444957;
	hodges[265] = 1.4161749802202657;
	hodges[266] = 2.6435266297444917;
	hodges[267] = 1.7391622564108524;
	hodges[268] = 2.6435266297444922;
	hodges[269] = 1.7391622564108522;
	hodges[270] = 2.6435266297444926;
	hodges[271] = 1.4161749802202643;
	hodges[272] = 2.08699470769302;
	hodges[273] = 2.08699470769302;
	hodges[274] = 1.4686259054136077;
	hodges[275] = 2.0869947076930182;
	hodges[276] = 2.6435266297444944;
	hodges[277] = 1.416174980220265;
	hodges[278] = 1.7391622564108511;
	hodges[279] = 2.6435266297444917;
	hodges[280] = 2.6435266297444944;
	hodges[281] = 2.6435266297444953;
	hodges[282] = 1.416174980220263;
	hodges[283] = 1.73916225641085;
	hodges[284] = 2.6435266297444966;
	hodges[285] = 1.4161749802202623;
	hodges[286] = 2.6435266297444975;
	hodges[287] = 1.7391622564108504;
	hodges[288] = 1.739162256410852;
	hodges[289] = 2.6435266297444899;
	hodges[290] = 1.4161749802202652;
	hodges[291] = 2.6435266297444953;
	hodges[292] = 1.7391622564108509;
	hodges[293] = 1.4161749802202657;
	hodges[294] = 2.6435266297444908;
	hodges[295] = 2.6435266297444944;
	hodges[296] = 2.0869947076930226;
	hodges[297] = 2.0869947076930213;
	hodges[298] = 2.0869947076930226;
	hodges[299] = 1.4686259054136082;
	hodges[300] = 2.6435266297444953;
	hodges[301] = 1.4161749802202652;
	hodges[302] = 1.739162256410852;
	hodges[303] = 2.6435266297444904;
	hodges[304] = 1.4686259054136077;
	hodges[305] = 2.08699470769302;
	hodges[306] = 2.0869947076930235;
	hodges[307] = 2.08699470769302;
	hodges[308] = 1.7391622564108518;
	hodges[309] = 2.6435266297444895;
	hodges[310] = 1.416174980220265;
	hodges[311] = 2.6435266297444939;
	hodges[312] = 1.416174980220265;
	hodges[313] = 1.7391622564108504;
	hodges[314] = 2.6435266297444953;
	hodges[315] = 2.6435266297444948;
	hodges[316] = 2.6435266297444953;
	hodges[317] = 1.4161749802202652;
	hodges[318] = 1.739162256410852;
	hodges[319] = 2.6435266297444908;
	hodges[320] = 2.0869947076930226;
	hodges[321] = 1.4686259054136077;
	hodges[322] = 2.0869947076930204;
	hodges[323] = 2.0869947076930204;
	hodges[324] = 1.7391622564108509;
	hodges[325] = 1.4161749802202659;
	hodges[326] = 2.6435266297444944;
	hodges[327] = 2.6435266297444908;
	hodges[328] = 2.6435266297444957;
	hodges[329] = 1.4161749802202657;
	hodges[330] = 2.6435266297444917;
	hodges[331] = 1.7391622564108524;
	hodges[332] = 2.643526629744493;
	hodges[333] = 1.7391622564108513;
	hodges[334] = 2.6435266297444908;
	hodges[335] = 1.4161749802202641;
	hodges[336] = 2.6435266297444935;
	hodges[337] = 1.4161749802202657;
	hodges[338] = 2.643526629744493;
	hodges[339] = 1.7391622564108511;
	hodges[340] = 2.6435266297444926;
	hodges[341] = 1.4161749802202688;
	hodges[342] = 2.6435266297444926;
	hodges[343] = 1.7391622564108487;
	hodges[344] = 1.4161749802202648;
	hodges[345] = 1.7391622564108526;
	hodges[346] = 2.6435266297444926;
	hodges[347] = 2.6435266297444926;
	hodges[348] = 2.6435266297444939;
	hodges[349] = 1.416174980220265;
	hodges[350] = 1.7391622564108511;
	hodges[351] = 2.6435266297444913;
	hodges[352] = 2.6435266297444939;
	hodges[353] = 2.6435266297444957;
	hodges[354] = 1.416174980220263;
	hodges[355] = 1.7391622564108511;
	hodges[356] = 2.6435266297444979;
	hodges[357] = 1.4161749802202623;
	hodges[358] = 2.6435266297444975;
	hodges[359] = 1.7391622564108506;
	hodges[360] = 1.4686259054136077;
	hodges[361] = 2.0869947076930195;
	hodges[362] = 2.086994707693024;
	hodges[363] = 2.08699470769302;
	hodges[364] = 1.7391622564108506;
	hodges[365] = 2.6435266297444882;
	hodges[366] = 1.416174980220265;
	hodges[367] = 2.6435266297444948;
	hodges[368] = 1.4161749802202652;
	hodges[369] = 1.73916225641085;
	hodges[370] = 2.6435266297444944;
	hodges[371] = 2.6435266297444953;
	hodges[372] = 1.7391622564108515;
	hodges[373] = 2.6435266297444895;
	hodges[374] = 1.4161749802202652;
	hodges[375] = 2.6435266297444939;
	hodges[376] = 1.7391622564108509;
	hodges[377] = 1.4161749802202659;
	hodges[378] = 2.6435266297444944;
	hodges[379] = 2.6435266297444908;
	hodges[380] = 2.6435266297444948;
	hodges[381] = 2.6435266297444948;
	hodges[382] = 1.4161749802202632;
	hodges[383] = 1.7391622564108498;
	hodges[384] = 2.6435266297444913;
	hodges[385] = 1.7391622564108549;
	hodges[386] = 1.4161749802202626;
	hodges[387] = 2.6435266297444904;
	hodges[388] = 1.4161749802202652;
	hodges[389] = 1.7391622564108504;
	hodges[390] = 2.6435266297444939;
	hodges[391] = 2.6435266297444953;
	hodges[392] = 2.6435266297444935;
	hodges[393] = 1.416174980220265;
	hodges[394] = 1.7391622564108511;
	hodges[395] = 2.6435266297444917;
	hodges[396] = 2.6435266297444939;
	hodges[397] = 1.7391622564108471;
	hodges[398] = 2.6435266297444948;
	hodges[399] = 1.4161749802202637;
	hodges[400] = 1.8357823817670096;
	hodges[401] = 1.8357823817670096;
	hodges[402] = 1.8357823817670096;
	hodges[403] = 1.8357823817670096;
	hodges[404] = 2.08699470769302;
	hodges[405] = 2.08699470769302;
	hodges[406] = 1.4686259054136077;
	hodges[407] = 2.0869947076930178;
	hodges[408] = 1.4686259054136077;
	hodges[409] = 2.08699470769302;
	hodges[410] = 2.086994707693024;
	hodges[411] = 2.08699470769302;
	hodges[412] = 2.6435266297444922;
	hodges[413] = 1.7391622564108553;
	hodges[414] = 1.4161749802202626;
	hodges[415] = 2.6435266297444904;
	hodges[416] = 2.6435266297444917;
	hodges[417] = 1.7391622564108553;
	hodges[418] = 1.4161749802202626;
	hodges[419] = 2.6435266297444895;
	hodges[420] = 2.6435266297444957;
	hodges[421] = 1.4161749802202652;
	hodges[422] = 1.7391622564108518;
	hodges[423] = 2.6435266297444904;
	hodges[424] = 1.7391622564108506;
	hodges[425] = 1.4161749802202654;
	hodges[426] = 2.6435266297444913;
	hodges[427] = 2.6435266297444939;
	hodges[428] = 2.6435266297444913;
	hodges[429] = 1.7391622564108513;
	hodges[430] = 2.6435266297444935;
	hodges[431] = 1.4161749802202643;
	hodges[432] = 2.6435266297444939;
	hodges[433] = 1.7391622564108524;
	hodges[434] = 2.6435266297444917;
	hodges[435] = 1.4161749802202643;
	hodges[436] = 2.6435266297444939;
	hodges[437] = 1.7391622564108524;
	hodges[438] = 2.6435266297444917;
	hodges[439] = 1.4161749802202643;
	hodges[440] = 2.6435266297444961;
	hodges[441] = 2.6435266297444944;
	hodges[442] = 1.4161749802202668;
	hodges[443] = 1.7391622564108502;
	hodges[444] = 2.6435266297444926;
	hodges[445] = 1.416174980220269;
	hodges[446] = 2.6435266297444926;
	hodges[447] = 1.7391622564108487;
	hodges[448] = 2.0869947076930231;
	hodges[449] = 2.0869947076930231;
	hodges[450] = 2.0869947076930209;
	hodges[451] = 1.4686259054136079;
	hodges[452] = 2.0869947076930226;
	hodges[453] = 1.4686259054136077;
	hodges[454] = 2.0869947076930209;
	hodges[455] = 2.0869947076930204;
	hodges[456] = 2.643526629744497;
	hodges[457] = 1.4161749802202626;
	hodges[458] = 2.6435266297444966;
	hodges[459] = 1.7391622564108506;
	hodges[460] = 1.7391622564108518;
	hodges[461] = 2.6435266297444899;
	hodges[462] = 1.416174980220265;
	hodges[463] = 2.6435266297444944;
	hodges[464] = 2.6435266297444953;
	hodges[465] = 1.416174980220265;
	hodges[466] = 1.7391622564108513;
	hodges[467] = 2.6435266297444908;
	hodges[468] = 1.7391622564108513;
	hodges[469] = 2.6435266297444899;
	hodges[470] = 1.416174980220265;
	hodges[471] = 2.6435266297444944;
	hodges[472] = 1.416174980220265;
	hodges[473] = 1.7391622564108504;
	hodges[474] = 2.6435266297444953;
	hodges[475] = 2.6435266297444957;
	hodges[476] = 2.6435266297444953;
	hodges[477] = 1.4161749802202652;
	hodges[478] = 1.7391622564108513;
	hodges[479] = 2.6435266297444904;
	hodges[480] = 1.7391622564108506;
	hodges[481] = 1.4161749802202659;
	hodges[482] = 2.6435266297444939;
	hodges[483] = 2.6435266297444908;
	hodges[484] = 1.4161749802202648;
	hodges[485] = 1.7391622564108526;
	hodges[486] = 2.6435266297444926;
	hodges[487] = 2.6435266297444926;
	hodges[488] = 2.0869947076930226;
	hodges[489] = 1.4686259054136077;
	hodges[490] = 2.0869947076930204;
	hodges[491] = 2.0869947076930204;
	hodges[492] = 1.4161749802202652;
	hodges[493] = 1.73916225641085;
	hodges[494] = 2.6435266297444948;
	hodges[495] = 2.6435266297444957;
	hodges[496] = 2.6435266297444944;
	hodges[497] = 1.416174980220265;
	hodges[498] = 1.7391622564108511;
	hodges[499] = 2.6435266297444913;
	hodges[500] = 1.7391622564108509;
	hodges[501] = 2.6435266297444886;
	hodges[502] = 1.4161749802202652;
	hodges[503] = 2.6435266297444961;
	hodges[504] = 2.6435266297444917;
	hodges[505] = 1.7391622564108553;
	hodges[506] = 1.4161749802202626;
	hodges[507] = 2.6435266297444895;
	hodges[508] = 2.08699470769302;
	hodges[509] = 2.08699470769302;
	hodges[510] = 1.4686259054136077;
	hodges[511] = 2.0869947076930182;
	hodges[512] = 1.4686259054136077;
	hodges[513] = 2.0869947076930204;
	hodges[514] = 2.086994707693024;
	hodges[515] = 2.08699470769302;
	hodges[516] = 2.6435266297444935;
	hodges[517] = 1.7391622564108473;
	hodges[518] = 2.6435266297444939;
	hodges[519] = 1.4161749802202634;
	hodges[520] = 1.4686259054136077;
	hodges[521] = 2.0869947076930195;
	hodges[522] = 2.086994707693024;
	hodges[523] = 2.08699470769302;
	hodges[524] = 1.8357823817670096;
	hodges[525] = 1.8357823817670096;
	hodges[526] = 1.8357823817670096;
	hodges[527] = 1.8357823817670096;
	hodges[528] = 2.6435266297444922;
	hodges[529] = 1.7391622564108553;
	hodges[530] = 1.4161749802202626;
	hodges[531] = 2.6435266297444904;
	hodges[532] = 1.4686259054136077;
	hodges[533] = 2.0869947076930204;
	hodges[534] = 2.0869947076930235;
	hodges[535] = 2.08699470769302;
	hodges[536] = 2.6435266297444939;
	hodges[537] = 1.7391622564108475;
	hodges[538] = 2.6435266297444944;
	hodges[539] = 1.4161749802202634;
	hodges[540] = 2.6435266297444913;
	hodges[541] = 1.7391622564108549;
	hodges[542] = 1.4161749802202626;
	hodges[543] = 2.6435266297444904;

	return 2.6435266297444979;
}
