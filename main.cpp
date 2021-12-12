#include <iostream>
#include <chrono>
using namespace std::chrono;

// Utils

/**
 * Elevate number by x value.
 * @param num
 * @param by
 * @return
 */
float elevate_by(float num, int by);
/**
 * Print an array.
 * @param arr
 * @param arr_size
 */
void print_arr(float *arr, int arr_size);
/**
 * Print matrix.
 * @param i
 * @param j
 * @param arr
 */
void print_matrix(int i, int j, int width, float *arr);

/**
 * Gets item from flattened matrix by given `i` and `j`.
 * @param i
 * @param j
 * @param mx
 * @return
 */
float get_from_flattened_matrix(int i, int j, int width, float *mx);

/**
 * Sets item to flattened matrix by given `i` and `j`.
 * @param i
 * @param j
 * @param mx
 * @return
 */
void set_item_flattened_matrix(int i, int j, int width, float *mx, float v);


// Polynomial

/**
 * Use this function to find coefficients for the X -> Y polynomial regression.
 * @param mx Matrix ixj, being i>0 and j=2
 * @param dgr
 * @param buffer Needs to be dgr+1 size
 * @param arr_size
 */
void find_coefficients(int arr_size, float *mx, int dgr, float *buffer);
/**
 * Predict using coefficients and a new x_value
 * Function is something like: F(X) = a0 + a1X + a2*X²
 * @param coefficients [a0, a1, a2, ...]
 * @param x_value
 * @return
 */
float predict(int arr_size, const float *coefficients, float x_value);

/**
 * Specific function to sum and elevate x to inject into augmented matrix.
 * @param x
 * @param s
 * @param dgr
 * @return
 */
float elevate_and_sum_all(const float *x, int s, int dgr);
/**
 * Specific function to sum y values to inject into augmented matrix.
 * @param y
 * @param x
 * @param s
 * @param x_degree
 * @return value of the sum function (E(y*X^n))
 */
float sum_y(const float *y, const float *x, int s, int x_degree);
/**
 * Retrieve x and y from matrix.
 * @param arr_size
 * @param arr
 * @param inject_matrix
 */
void find_x_y(int arr_size, float *arr, float *inject_matrix);
/**
 * Private function that calculate the coefficients from x,y and dgr.
 * @param x
 * @param y
 * @param dgr
 * @param arr_size
 * @param buffer
 */
void calculate_coef(float x[], float y[], int dgr, int arr_size, float *buffer);


// Gauss

/**
 * Calculates the result of the linear system by given a and b, resulting into the augmented matrix.
 * @param arr_size
 * @param a
 * @param b
 * @param buffer where is injected the results of the linear system. With size arr_size+1
 */
void gauss_method(int arr_size, float *a, float *b, float *buffer);
/**
 * Calculates the result of the linear system given an unique matrix.
 * @param n
 * @param mx
 * @param inject
 */
void gauss_method_unique_mx(int n, float *mx, float *inject);

/**
 * Joins a and b into one unique augmented matrix, being always [n][n+1]
 * @param n
 * @param mx_a
 * @param mx_b
 * @param buffer
 */
void join_mx(int n, float *mx_a, float *mx_b, float *buffer);
/**
 * Transforms matrix into Triangle format.
 * @param n
 * @param mx
 */
void convert_triangle(int n, float *mx);
/**
 * Apply back substitution to matrix.
 * @param n
 * @param mx
 * @param buffer where is injected the matrix after back substitution
 */
void back_subs(int n, float *mx, float *buffer);

int size = 250;
int degree = 2;
float to_predict =  5.7;
// length == size
float value[250][2];
// length == size
float global_buffer[250][250];
// length == degree + 1
float x_result[3][3], y_result[1][3];
// length == degree + 1
float coef[3];

int main() {
    value[0][0] = 5.771746026235907;
    value[0][1] = 2756.999505988017;
    value[1][0] = 1.4909464996379098;
    value[1][1] = 331.27119264629675;
    value[2][0] = 9.533623819928094;
    value[2][1] = 6946.331166639915;
    value[3][0] = 8.675744376940758;
    value[3][1] = 5821.543204104686;
    value[4][0] = 2.564082791209792;
    value[4][1] = 705.2624401914835;
    value[5][0] = 5.548095794679393;
    value[5][1] = 2568.557212753365;
    value[6][0] = 6.2094208091037775;
    value[6][1] = 3145.4586196049218;
    value[7][0] = 6.2094208091037775;
    value[7][1] = 3145.4586196049218;
    value[8][0] = 7.145620909711442;
    value[8][1] = 4063.859557631181;
    value[9][0] = 9.383340381276938;
    value[9][1] = 6742.058579154288;
    value[10][0] = 8.24023711896795;
    value[10][1] = 5288.846434886358;
    value[11][0] = 8.191250731648477;
    value[11][1] = 5230.542151549525;
    value[12][0] = 2.1194577214984918;
    value[12][1] = 531.304007533727;
    value[13][0] = 9.323856083185056;
    value[13][1] = 6662.053225814113;
    value[14][0] = 5.71614829755184;
    value[14][1] = 2709.518768847371;
    value[15][0] = 2.965562583860496;
    value[15][1] = 885.4426526625473;
    value[16][0] = 1.2472965377877905;
    value[16][1] = 268.17811521888746;
    value[17][0] = 1.8992697077712328;
    value[17][1] = 455.1114300785863;
    value[18][0] = 8.93330978871369;
    value[18][1] = 6148.728322841983;
    value[19][0] = 4.51291774247013;
    value[19][1] = 1784.9644873483137;
    value[20][0] = 4.99793321654179;
    value[20][1] = 2133.956486690935;
    value[21][0] = 6.599810497566239;
    value[21][1] = 3513.934886810751;
    value[22][0] = 9.065286967005235;
    value[22][1] = 6319.8752118050315;
    value[23][0] = 4.800511110564394;
    value[23][1] = 1988.0404021924546;
    value[24][0] = 1.8530552537039868;
    value[24][1] = 439.9569526627225;
    value[25][0] = 2.8341804858058164;
    value[25][1] = 824.0662807456939;
    value[26][0] = 9.990236505657313;
    value[26][1] = 7585.827846093324;
    value[27][0] = 5.702282593262107;
    value[27][1] = 2697.7428918799915;
    value[28][0] = 7.138263795324247;
    value[28][1] = 4056.177570899768;
    value[29][0] = 7.946033914029875;
    value[29][1] = 4943.588080050652;
    value[30][0] = 6.349097710296637;
    value[30][1] = 3274.9135592525768;
    value[31][0] = 5.903449638842832;
    value[31][1] = 2871.1527116534508;
    value[32][0] = 1.7839492286836411;
    value[32][1] = 417.8379407924588;
    value[33][0] = 4.563121002567502;
    value[33][1] = 1819.6035830329101;
    value[34][0] = 3.7119378220903183;
    value[34][1] = 1278.6739912364526;
    value[35][0] = 4.939089946612534;
    value[35][1] = 2089.9104318135496;
    value[36][0] = 4.6148511874178;
    value[36][1] = 1855.654835772052;
    value[37][0] = 1.3973183201623751;
    value[37][1] = 306.07093341793257;
    value[38][0] = 4.630430491366546;
    value[38][1] = 1866.5835159856551;
    value[39][0] = 4.714773161697695;
    value[39][1] = 1926.3219670852168;
    value[40][0] = 8.803930617166179;
    value[40][1] = 5983.250169070664;
    value[41][0] = 7.0053889892944285;
    value[41][1] = 3918.7025673572084;
    value[42][0] = 1.6721498208719785;
    value[42][1] = 383.42939647911794;
    value[43][0] = 4.918645597423286;
    value[43][1] = 2074.717429199502;
    value[44][0] = 5.5666411288697555;
    value[44][1] = 2583.9243756459728;
    value[45][0] = 9.436159795079467;
    value[45][1] = 6813.503195337304;
    value[46][0] = 9.941098851279015;
    value[46][1] = 7515.647717223222;
    value[47][0] = 5.748229616883211;
    value[47][1] = 2736.8650667433685;
    value[48][0] = 5.999265406547654;
    value[48][1] = 2955.682966224525;
    value[49][0] = 9.22975597300344;
    value[49][1] = 6536.473090788756;
    value[50][0] = 5.167591918969274;
    value[50][1] = 2263.5879392099696;
    value[51][0] = 5.53117717308133;
    value[51][1] = 2554.578793186919;
    value[52][0] = 1.9225980565292813;
    value[52][1] = 462.87151055365433;
    value[53][0] = 9.636933776219779;
    value[53][1] = 7088.536853139432;
    value[54][0] = 2.6371909351479284;
    value[54][1] = 736.4399931985793;
    value[55][0] = 2.5281899384936666;
    value[55][1] = 690.2217215202567;
    value[56][0] = 4.475096901702815;
    value[56][1] = 1759.0953883867346;
    value[57][0] = 5.396347480632123;
    value[57][1] = 2444.571950798404;
    value[58][0] = 6.94878196526434;
    value[58][1] = 3860.865242638493;
    value[59][0] = 7.691401723555048;
    value[59][1] = 4654.272116883008;
    value[60][0] = 4.273472130728313;
    value[60][1] = 1624.4692948981894;
    value[61][0] = 7.608270730693701;
    value[61][1] = 4561.727343974442;
    value[62][0] = 1.6720287273741126;
    value[62][1] = 383.3930492051953;
    value[63][0] = 6.1470600618207625;
    value[63][1] = 3088.5184736970727;
    value[64][0] = 2.3187403284871566;
    value[64][1] = 605.9476923164748;
    value[65][0] = 9.285058584116914;
    value[65][1] = 6610.130584212456;
    value[66][0] = 2.9982445561400404;
    value[66][1] = 901.0750008594696;
    value[67][0] = 5.939049725937713;
    value[67][1] = 2902.413907295015;
    value[68][0] = 6.1383069574437865;
    value[68][1] = 3080.568551333319;
    value[69][0] = 4.658326237679177;
    value[69][1] = 1886.2345004568106;
    value[70][0] = 1.437691351501741;
    value[70][1] = 316.79121171865074;
    value[71][0] = 8.809071178882503;
    value[71][1] = 5989.781600261325;
    value[72][0] = 4.147391008929532;
    value[72][1] = 1543.0941232385615;
    value[73][0] = 1.7056429320110036;
    value[73][1] = 393.5592147002573;
    value[74][0] = 6.820778178063464;
    value[74][1] = 3731.686526384169;
    value[75][0] = 7.825316822738247;
    value[75][1] = 4805.328537881245;
    value[76][0] = 2.1512152019891984;
    value[76][1] = 542.8373318048264;
    value[77][0] = 6.692866718874117;
    value[77][1] = 3604.8272267402085;
    value[78][0] = 9.840726898782588;
    value[78][1] = 7373.313541407218;
    value[79][0] = 9.002992728409929;
    value[79][1] = 6238.797353172908;
    value[80][0] = 1.3912445297206075;
    value[80][1] = 304.4773416461424;
    value[81][0] = 3.1717144363987715;
    value[81][1] = 986.4807018042853;
    value[82][0] = 1.5806695748606294;
    value[82][1] = 356.53918886057363;
    value[83][0] = 1.9194302472685167;
    value[83][1] = 461.8134082885672;
    value[84][0] = 5.737488420147972;
    value[84][1] = 2727.6936210205045;
    value[85][0] = 9.81375408576096;
    value[85][1] = 7335.297879970095;
    value[86][0] = 5.201179872720772;
    value[86][1] = 2289.7158250450675;
    value[87][0] = 4.170406327707584;
    value[87][1] = 1557.7873272394488;
    value[88][0] = 2.570190757347825;
    value[88][1] = 707.8393995645932;
    value[89][0] = 9.421493871520426;
    value[89][1] = 6793.6277131961215;
    value[90][0] = 9.446625651996039;
    value[90][1] = 6827.7045715522645;
    value[91][0] = 9.39387060407323;
    value[91][1] = 6756.271687822111;
    value[92][0] = 6.234037853918204;
    value[92][1] = 3168.0814864718345;
    value[93][0] = 5.091516875288564;
    value[93][1] = 2204.976951418642;
    value[94][0] = 7.100223389345451;
    value[94][1] = 4016.574840292887;
    value[95][0] = 1.7173161959802088;
    value[95][1] = 397.1255900228545;
    value[96][0] = 5.5844188277784506;
    value[96][1] = 2598.699371438342;
    value[97][0] = 8.378625575552986;
    value[97][1] = 5455.321820725077;
    value[98][0] = 1.466442307586732;
    value[98][1] = 324.56063235955224;
    value[99][0] = 1.6225033486914997;
    value[99][1] = 368.694790958476;
    value[100][0] = 1.3365527789929983;
    value[100][1] = 290.35378402872794;
    value[101][0] = 6.0837819359636125;
    value[101][1] = 3031.2813756656715;
    value[102][0] = 4.548464700729124;
    value[102][1] = 1809.455639781057;
    value[103][0] = 9.448822694247664;
    value[103][1] = 6830.687683781057;
    value[104][0] = 6.46890575048782;
    value[104][1] = 3388.067989652925;
    value[105][0] = 2.1195473816777057;
    value[105][1] = 531.3363762073816;
    value[106][0] = 5.277100706363948;
    value[106][1] = 2349.339653992753;
    value[107][0] = 4.9201471509332615;
    value[107][1] = 2075.8313584407488;
    value[108][0] = 2.770131695761282;
    value[108][1] = 794.9965680379256;
    value[109][0] = 7.709752285567095;
    value[109][1] = 4674.82735174938;
    value[110][0] = 3.455234425811625;
    value[110][1] = 1134.8798237635044;
    value[111][0] = 1.2766373702105387;
    value[111][1] = 275.34827276730704;
    value[112][0] = 7.085176663988682;
    value[112][1] = 4000.964468649975;
    value[113][0] = 6.480010760197271;
    value[113][1] = 3398.6551470306317;
    value[114][0] = 5.584045566018069;
    value[114][1] = 2598.3887128196675;
    value[115][0] = 6.331557272178415;
    value[115][1] = 3258.5110837812044;
    value[116][0] = 2.2823858558576804;
    value[116][1] = 591.9278608172502;
    value[117][0] = 4.476384640324595;
    value[117][1] = 1759.9729899878394;
    value[118][0] = 1.6666923572200163;
    value[118][1] = 381.79327159761266;
    value[119][0] = 5.335869882835952;
    value[119][1] = 2396.0318977375314;
    value[120][0] = 2.2242269676661177;
    value[120][1] = 569.8731504154579;
    value[121][0] = 6.419788689144322;
    value[121][1] = 3341.4425367111253;
    value[122][0] = 7.1577390660162505;
    value[122][1] = 4076.5288727836387;
    value[123][0] = 5.169155240588828;
    value[123][1] = 2264.8006337036427;
    value[124][0] = 3.652810875733496;
    value[124][1] = 1244.7591390682887;
    value[125][0] = 6.27713716619057;
    value[125][1] = 3207.887895279046;
    value[126][0] = 6.692746326790964;
    value[126][1] = 3604.708873257227;
    value[127][0] = 8.011119514881269;
    value[127][1] = 5018.954274509355;
    value[128][0] = 9.603880486758538;
    value[128][1] = 7042.881218515827;
    value[129][0] = 6.62746783247695;
    value[129][1] = 3540.8260803781786;
    value[130][0] = 1.0463119551548488;
    value[130][1] = 222.21082958766254;
    value[131][0] = 2.8875298552780513;
    value[131][1] = 848.7058146600798;
    value[132][0] = 6.802316565446363;
    value[132][1] = 3713.239352747824;
    value[133][0] = 9.733701722517237;
    value[133][1] = 7223.054224081637;
    value[134][0] = 4.7978803102980825;
    value[134][1] = 1986.1317520814334;
    value[135][0] = 6.019594856573622;
    value[135][1] = 2973.7785239580708;
    value[136][0] = 6.367494396617343;
    value[136][1] = 3292.1616949229674;
    value[137][0] = 4.734419077462285;
    value[137][1] = 1940.3757677278445;
    value[138][0] = 5.304266197444012;
    value[138][1] = 2370.8643103825448;
    value[139][0] = 2.7043144081141146;
    value[139][1] = 765.7054930437109;
    value[140][0] = 7.1492407431949685;
    value[140][1] = 4067.6419365101287;
    value[141][0] = 7.115550481435777;
    value[141][1] = 4032.507742212489;
    value[142][0] = 1.5524584417856255;
    value[142][1] = 348.4762942420801;
    value[143][0] = 2.8071920093402594;
    value[143][1] = 811.7490452416951;
    value[144][0] = 3.4009432644553734;
    value[144][1] = 1105.6165393664965;
    value[145][0] = 1.6302406833279617;
    value[145][1] = 370.96910608140814;
    value[146][0] = 1.921471010363824;
    value[146][1] = 462.49490150908605;
    value[147][0] = 4.681493032087071;
    value[147][1] = 1902.6346559084452;
    value[148][0] = 3.1230388065637635;
    value[148][1] = 962.1027545651152;
    value[149][0] = 9.716376456486774;
    value[149][1] = 7198.876721939589;
    value[150][0] = 7.23599868690594;
    value[150][1] = 4158.828926478787;
    value[151][0] = 6.707200519375052;
    value[151][1] = 3618.93240322476;
    value[152][0] = 9.26936879167134;
    value[152][1] = 6589.191096302202;
    value[153][0] = 5.728801894414537;
    value[153][1] = 2720.2880476223263;
    value[154][0] = 5.1461939773931205;
    value[154][1] = 2247.022615693835;
    value[155][0] = 3.5855368066366644;
    value[155][1] = 1206.7494630103954;
    value[156][0] = 4.320839467751945;
    value[156][1] = 1655.5998297762992;
    value[157][0] = 4.220990452653266;
    value[157][1] = 1590.3339211442014;
    value[158][0] = 2.2425880363910866;
    value[158][1] = 576.7862429090122;
    value[159][0] = 3.4264655771356214;
    value[159][1] = 1119.323294231717;
    value[160][0] = 9.9155124427973;
    value[160][1] = 7479.234335195666;
    value[161][0] = 9.907614828183489;
    value[161][1] = 7468.012803358438;
    value[162][0] = 8.69831564948819;
    value[162][1] = 5849.854744162865;
    value[163][0] = 9.532764072553698;
    value[163][1] = 6945.1538191401905;
    value[164][0] = 7.802827502151773;
    value[164][1] = 4779.790129344111;
    value[165][0] = 7.041281353041563;
    value[165][1] = 3955.600809496601;
    value[166][0] = 3.1727044168883203;
    value[166][1] = 986.9798521400703;
    value[167][0] = 3.4155338626544105;
    value[167][1] = 1113.4415708652004;
    value[168][0] = 5.709089227947185;
    value[168][1] = 2703.5203685610954;
    value[169][0] = 1.7206765386484886;
    value[169][1] = 398.15566600307807;
    value[170][0] = 5.473639229097064;
    value[170][1] = 2507.3314346544407;
    value[171][0] = 7.792139722528622;
    value[171][1] = 4767.677422567721;
    value[172][0] = 2.5212405999010152;
    value[172][1] = 687.329884258884;
    value[173][0] = 3.6984199076703863;
    value[173][1] = 1270.8782685851775;
    value[174][0] = 6.627167239179734;
    value[174][1] = 3540.5332546202812;
    value[175][0] = 4.3965361491687105;
    value[175][1] = 1705.9823816973176;
    value[176][0] = 7.1375379778011725;
    value[176][1] = 4055.420102024485;
    value[177][0] = 8.948868802189232;
    value[177][1] = 6168.781931687146;
    value[178][0] = 3.2696869492890204;
    value[178][1] = 1036.5248539839483;
    value[179][0] = 2.3783377961758263;
    value[179][1] = 629.3199208278203;
    value[180][0] = 7.728588637446682;
    value[180][1] = 4695.9743782400765;
    value[181][0] = 1.7792788594892026;
    value[181][1] = 416.3665124649736;
    value[182][0] = 9.168519518451145;
    value[182][1] = 6455.3976594342175;
    value[183][0] = 9.719605010167081;
    value[183][1] = 7203.379090778325;
    value[184][0] = 6.4914191748991135;
    value[184][1] = 3409.549028531392;
    value[185][0] = 1.342383407382468;
    value[185][1] = 291.84010606587424;
    value[186][0] = 6.698364793086334;
    value[186][1] = 3610.234302864414;
    value[187][0] = 4.309779698861306;
    value[187][1] = 1648.303872066958;
    value[188][0] = 7.474154366241493;
    value[188][1] = 4414.405139886992;
    value[189][0] = 6.389403245240046;
    value[189][1] = 3312.7627751416967;
    value[190][0] = 1.8868902541946768;
    value[190][1] = 451.0235180426018;
    value[191][0] = 9.150007988241937;
    value[191][1] = 6430.989286355809;
    value[192][0] = 7.505030965774917;
    value[192][1] = 4448.105228420825;
    value[193][0] = 4.5065728283914295;
    value[193][1] = 1780.6110436394733;
    value[194][0] = 8.773787603459269;
    value[194][1] = 5945.023763553077;
    value[195][0] = 3.4384885322831247;
    value[195][1] = 1125.8109204268485;
    value[196][0] = 8.346055485093489;
    value[196][1] = 5415.9070028772885;
    value[197][0] = 9.778702505252896;
    value[197][1] = 7286.043805335122;
    value[198][0] = 9.620827602066248;
    value[198][1] = 7066.2712574341385;
    value[199][0] = 1.294161100256126;
    value[199][1] = 279.686481164249;
    value[200][0] = 9.686333373372127;
    value[200][1] = 7157.04822055518;
    value[201][0] = 4.45786552593886;
    value[201][1] = 1747.3738047124166;
    value[202][0] = 2.3200359543968894;
    value[202][1] = 606.4506583057869;
    value[203][0] = 8.283085338507897;
    value[203][1] = 5340.112597177185;
    value[204][0] = 5.943832905255473;
    value[204][1] = 2906.6272557061397;
    value[205][0] = 1.940783727651356;
    value[205][1] = 468.9722443177162;
    value[206][0] = 5.871900864292598;
    value[206][1] = 2843.5931346554253;
    value[207][0] = 2.702172792051348;
    value[207][1] = 764.7622945508899;
    value[208][0] = 3.2639783259743047;
    value[208][1] = 1033.573080937162;
    value[209][0] = 9.829216780176923;
    value[209][1] = 7357.078999886427;
    value[210][0] = 9.509667813021922;
    value[210][1] = 6913.5631766001125;
    value[211][0] = 3.1001782765427084;
    value[211][1] = 950.7648602703232;
    value[212][0] = 1.3522699833605647;
    value[212][1] = 294.37092300925116;
    value[213][0] = 4.427906513703379;
    value[213][1] = 1727.0904400488855;
    value[214][0] = 5.164077487454128;
    value[214][1] = 2260.862950078413;
    value[215][0] = 8.922640398122613;
    value[215][1] = 6134.9958538099645;
    value[216][0] = 6.75605840830992;
    value[216][1] = 3667.2209811139296;
    value[217][0] = 1.3192448761852935;
    value[217][1] = 285.9689542337136;
    value[218][0] = 7.608591737767817;
    value[218][1] = 4562.082894135352;
    value[219][0] = 1.590076324025636;
    value[219][1] = 359.2517545275869;
    value[220][0] = 5.0548796538676015;
    value[220][1] = 2177.0311408903062;
    value[221][0] = 2.3991258039678174;
    value[221][1] = 637.5859620944942;
    value[222][0] = 1.8983115779112545;
    value[222][1] = 454.7942946147278;
    value[223][0] = 5.338666290462211;
    value[223][1] = 2398.2653585296594;
    value[224][0] = 1.7930265299817476;
    value[224][1] = 420.7062869495357;
    value[225][0] = 5.228543003594986;
    value[225][1] = 2311.114881464041;
    value[226][0] = 2.1280664845502217;
    value[226][1] = 534.4168882263565;
    value[227][0] = 6.704014289948784;
    value[227][1] = 3615.794578541583;
    value[228][0] = 1.799894185246011;
    value[228][1] = 422.88385198289404;
    value[229][0] = 4.252416766603272;
    value[229][1] = 1610.729367331445;
    value[230][0] = 6.278293461869235;
    value[230][1] = 3208.959327052333;
    value[231][0] = 3.3412435394149846;
    value[231][1] = 1073.9008211644402;
    value[232][0] = 8.137922409930965;
    value[232][1] = 5167.441112917988;
    value[233][0] = 9.50468710493985;
    value[233][1] = 6906.760165526645;
    value[234][0] = 5.841029444724341;
    value[234][1] = 2816.756317618391;
    value[235][0] = 2.7858936722858587;
    value[235][1] = 802.0986674758541;
    value[236][0] = 5.3929807994821415;
    value[236][1] = 2441.8567353134745;
    value[237][0] = 8.843838831019198;
    value[237][1] = 6034.050616328443;
    value[238][0] = 5.024869866794874;
    value[238][1] = 2154.276567494628;
    value[239][0] = 3.182429295733868;
    value[239][1] = 991.8902439888594;
    value[240][0] = 5.1875870082708335;
    value[240][1] = 2279.123525794424;
    value[241][0] = 6.522851073406161;
    value[241][1] = 3439.6548883984387;
    value[242][0] = 5.0909529650458225;
    value[242][1] = 2204.5454335838863;
    value[243][0] = 7.7790844478450945;
    value[243][1] = 4752.902660020206;
    value[244][0] = 2.2535965419391752;
    value[244][1] = 580.9530236007326;
    value[245][0] = 8.736142480650063;
    value[245][1] = 5897.456975064094;
    value[246][0] = 1.5736303032285353;
    value[246][1] = 354.5171912140133;
    value[247][0] = 3.4214257641860346;
    value[247][1] = 1116.60964287701;
    value[248][0] = 8.82521416978582;
    value[248][1] = 6010.31572811477;
    value[249][0] = 8.692188901061646;
    value[249][1] = 5842.163004952757;

    std::cout << "Running Code\n";
    std::cout << "Value to Predict: ";
    std::cout << to_predict;
    std::cout << "\n";

    auto start = high_resolution_clock::now();

    // Using in global buffer -> float coef[3];
    find_coefficients(size, &value[0][0], degree, coef);
    float prediction = predict(degree+1, &coef[0], to_predict);
    auto stop = high_resolution_clock::now();


    std::cout << "Predicted value are: ";
    std::cout << prediction;

    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << std::endl;
    std::cout << "Duration of methods: ";
    std::cout << duration.count() << " Microseconds" << std::endl;
    return 0;
}


// UTILS

float elevate_by(float num, int by){
    float res = 1;
    for (int i = 0; i < by; ++i) {
        res = res * num;
    }
    return res;
}

void print_arr(float *arr, int arr_size){
    printf("{ ");
    for (int i = 0; i < arr_size; ++i) {
        if (i ==0) printf("%.2f", arr[i]);
        else printf(", %.2f", arr[i]);
    }
    printf(" }");
}

void print_matrix(int i, int j, int width, float *arr){
    printf("{ \n");
    for (int k=0; k < i; k++){
        printf("  ");
        printf("{ ");
        for (int u = 0; u < j; ++u) {
            if (u ==0) printf("%.2f", get_from_flattened_matrix(k, u, width, arr));
            else printf(", %.2f", get_from_flattened_matrix(k,u, width, arr));
        }
        printf(" }");
        if (k < i-1) printf(",\n");
    }
    printf("\n");
    printf("}");
}

float get_from_flattened_matrix(int i, int j, int width, float *mx){
    int res = (i * width) + j;
    return mx[res];
}

void set_item_flattened_matrix(int i, int j, int width, float *mx, float v){
    int res = (i * width) + j;
    mx[res] = v;
}

// Polynomial Prediction

void find_coefficients(int arr_size, float *mx, int dgr, float *buffer) {
    float *x, *y;
    // ! Used global buffer instead of res[2][arr_size];
    find_x_y(arr_size, mx, &global_buffer[0][0]);
    x = global_buffer[0];
    y = global_buffer[1];
    calculate_coef(x, y, dgr, arr_size, buffer);
}

void calculate_coef(float x[], float y[], int dgr, int arr_size, float *buffer) {
    int quantity = dgr + 1, i, ii, elevate_by;
    float v;
    // Removed from here to put on global scope -> float x_result[quantity][quantity], y_result[1][quantity];
    for (i=0; i<quantity; i++){
        for (ii=0; ii < quantity; ii++){
            elevate_by= i + ii;
            v = elevate_and_sum_all(x, arr_size, elevate_by);
            x_result[i][ii] = v;
        }
        elevate_by = i;
        y_result[0][i] = sum_y(y, x, arr_size, elevate_by);
    }
    x_result[0][0] = (float) arr_size;
    gauss_method(quantity, &x_result[0][0], &y_result[0][0], buffer);
}

float predict(int arr_size, const float *coefficients, float x_value) {
    int i;
    float a, res = 0;
    for (i = 0; i < arr_size; ++i) {
        a = coefficients[i];
        res += a * elevate_by(x_value, i);
    }
    return res;
}

/*
 * Example:
 * [ [1,6], [2, 7] ] -> x = [1, 2]; y = [6, 7]
 */
void find_x_y(int arr_size, float *arr, float *inject_matrix){
    int i;
    // ! Using buffer instead of float x[arr_size], y[arr_size];
    for (i = 0; i < arr_size; i++){
        float get1 = get_from_flattened_matrix(i, 0, 2, arr);
        set_item_flattened_matrix(0, i, arr_size, inject_matrix, get1);
        float get2 = get_from_flattened_matrix(i, 1, 2, arr);
        set_item_flattened_matrix(1, i, arr_size, inject_matrix, get2);
    }
    // Called before, making faster
//    for (int j = 0; j < arr_size; ++j) {
//        set_item_flattened_matrix(0, j, arr_size, inject_matrix, x[j]);
//        set_item_flattened_matrix(1, j, arr_size, inject_matrix, y[j]);
//    }
}


float sum_y(const float *y, const float *x, int s, int x_degree){
    float res = 0, temp_x, temp_y;
    for (int i = 0; i < s; ++i) {
        temp_x = x[i];
        temp_y = y[i];
        temp_x = elevate_by(temp_x, x_degree);
        res += temp_x * temp_y;
    }
    return res;
}

float elevate_and_sum_all(const float *x, int s, int dgr){
    float res = 0, temp;
    for (int i = 0; i < s; ++i) {
        temp = x[i];
        res += elevate_by(temp, dgr);
    }
    return res;
}


// Gauss

void gauss_method(int arr_size, float *a, float *b, float *buffer){
//    Using Global buffer instead of float mx[arr_size][arr_size+1];
    join_mx(arr_size, a, b, &global_buffer[0][0]);
    gauss_method_unique_mx(arr_size, &global_buffer[0][0], buffer);
}

void join_mx(int n, float *mx_a, float *mx_b, float *buffer){
    for (int i = 0; i < n; i++) {
        for (int ii = 0; ii < n+1; ii++) {
            if (ii == n)
                set_item_flattened_matrix(i, ii, n+1, buffer, get_from_flattened_matrix(i, 0, 1, mx_b));
            else
                set_item_flattened_matrix(i, ii, n+1, buffer, get_from_flattened_matrix(i, ii, n, mx_a));
        }
    }
}

void gauss_method_unique_mx(int n, float *mx, float *inject){
    // Apply triangle to matrix.
    convert_triangle(n, mx);
    // Apply back substitution.
    back_subs(n, mx, inject);
}

void convert_triangle(int n, float *mx){
    int i, ii, iii;
    float ratio, temp;
    for( i=0;i<n;i++)
    {
        for(ii=0; ii < n; ii++)
        {
            if(ii > i)
            {
                ratio = get_from_flattened_matrix(ii, i,n+1, mx) / get_from_flattened_matrix(i, i, n+1, mx);
                for(iii=0; iii < n + 1; iii++){
                    float get1 = get_from_flattened_matrix(ii, iii, n+1, mx);
                    float get2 = get_from_flattened_matrix(i, iii, n+1, mx);
                    temp = get1 - ratio * get2;
                    set_item_flattened_matrix(ii, iii, n+1, mx, temp);
                }
            }
        }
    }
}

void back_subs(int n, float *mx, float *buffer){
    int i, ii;
    float sum;
    buffer[n - 1]= get_from_flattened_matrix(n-1, n, n+1, mx) / get_from_flattened_matrix(n-1, n-1, n+1, mx);

    for(i=n-2;i>=0;i--)
    {
        sum=0;
        for(ii= i + 1; ii < n; ii++)
            sum = sum + get_from_flattened_matrix(i, ii, n+1, mx) * buffer[ii];
        buffer[i] = (get_from_flattened_matrix(i, n,n+1, mx) - sum) / get_from_flattened_matrix(i, i, n+1, mx);
    }
}
