typedef int u32;
typedef char u8;


#define MulByPow2(x, k)((((x)<<k) | ((x)>>(31-k))) & 0x7FFFFFFF)
#define ROT(a, k)(((a)<<k) | ((a) >> (32-k)))
#define MAKEU31(a,b,c)(((u32)(a) << 23)| ((u32)(b) << 8) | (u32)(c))
#define MAKEU32(a,b,c,d)(((u32)(a) << 24)| ((u32)(b) << 16) | (u32)(c) << 8 | (u32)(d))

/*L1, L2*/
u32 L1(u32 X) {
	return (X ^ ROT(X, 2) ^ ROT(X, 10) ^ ROT(X, 18) ^ ROT(X, 24));
}

u32 L2(u32 X) {
	return (X ^ ROT(X, 8) ^ ROT(X, 14) ^ ROT(X, 22) ^ ROT(X, 30));
}

/*s-boxs*/
u8 Sbox0[256] = {
0x3e,0x72,0x5b,0x47,0xca,0xe0,0x00,0x33,0x04,0xd1,0x54,0x98,0x09,0xb9,0x6d,0xcb,
0x7b,0x1b,0xf9,0x32,0xaf,0x9d,0x6a,0xa5,0xb8,0x2d,0xfc,0x1d,0x08,0x53,0x03,0x90,
0x4d,0x4e,0x84,0x99,0xe4,0xce,0xd9,0x91,0xdd,0xb6,0x85,0x48,0x8b,0x29,0x6e,0xac,
0xcd,0xc1,0xf8,0x1e,0x73,0x43,0x69,0xc6,0xb5,0xbd,0xfd,0x39,0x63,0x20,0xd4,0x38,
0x76,0x7d,0xb2,0xa7,0xcf,0xed,0x57,0xc5,0xf3,0x2c,0xbb,0x14,0x21,0x06,0x55,0x9b,
0xe3,0xef,0x5e,0x31,0x4f,0x7f,0x5a,0xa4,0x0d,0x82,0x51,0x49,0x5f,0xba,0x58,0x1c,
0x4a,0x16,0xd5,0x17,0xa8,0x92,0x24,0x1f,0x8c,0xff,0xd8,0xae,0x2e,0x01,0xd3,0xad,
0x3b,0x4b,0xda,0x46,0xeb,0xc9,0xde,0x9a,0x8f,0x87,0xd7,0x3a,0x80,0x6f,0x2f,0xc8,
0xb1,0xb4,0x37,0xf7,0x0a,0x22,0x13,0x28,0x7c,0xcc,0x3c,0x89,0xc7,0xc3,0x96,0x56,
0x07,0xbf,0x7e,0xf0,0x0b,0x2b,0x97,0x52,0x35,0x41,0x79,0x61,0xa6,0x4c,0x10,0xfe,
0xbc,0x26,0x95,0x88,0x8a,0xb0,0xa3,0xfb,0xc0,0x18,0x94,0xf2,0xe1,0xe5,0xe9,0x5d,
0xd0,0xdc,0x11,0x66,0x64,0x5c,0xec,0x59,0x42,0x75,0x12,0xf5,0x74,0x9c,0xaa,0x23,
0x0e,0x86,0xab,0xbe,0x2a,0x02,0xe7,0x67,0xe6,0x44,0xa2,0x6c,0xc2,0x93,0x9f,0xf1,
0xf6,0xfa,0x36,0xd2,0x50,0x68,0x9e,0x62,0x71,0x15,0x3d,0xd6,0x40,0xc4,0xe2,0x0f,
0x8e,0x83,0x77,0x6b,0x25,0x05,0x3f,0x0c,0x30,0xea,0x70,0xb7,0xa1,0xe8,0xa9,0x65,
0x8d,0x27,0x1a,0xdb,0x81,0xb3,0xa0,0xf4,0x45,0x7a,0x19,0xdf,0xee,0x78,0x34,0x60
};

u8 Sbox1[256] = {
0x55,0xc2,0x63,0x71,0x3b,0xc8,0x47,0x86,0x9f,0x3c,0xda,0x5b,0x29,0xaa,0xfd,0x77,
0x8c,0xc5,0x94,0x0c,0xa6,0x1a,0x13,0x00,0xe3,0xa8,0x16,0x72,0x40,0xf9,0xf8,0x42,
0x44,0x26,0x68,0x96,0x81,0xd9,0x45,0x3e,0x10,0x76,0xc6,0xa7,0x8b,0x39,0x43,0xe1,
0x3a,0xb5,0x56,0x2a,0xc0,0x6d,0xb3,0x05,0x22,0x66,0xbf,0xdc,0x0b,0xfa,0x62,0x48,
0xdd,0x20,0x11,0x06,0x36,0xc9,0xc1,0xcf,0xf6,0x27,0x52,0xbb,0x69,0xf5,0xd4,0x87,
0x7f,0x84,0x4c,0xd2,0x9c,0x57,0xa4,0xbc,0x4f,0x9a,0xdf,0xfe,0xd6,0x8d,0x7a,0xeb,
0x2b,0x53,0xd8,0x5c,0xa1,0x14,0x17,0xfb,0x23,0xd5,0x7d,0x30,0x67,0x73,0x08,0x09,
0xee,0xb7,0x70,0x3f,0x61,0xb2,0x19,0x8e,0x4e,0xe5,0x4b,0x93,0x8f,0x5d,0xdb,0xa9,
0xad,0xf1,0xae,0x2e,0xcb,0x0d,0xfc,0xf4,0x2d,0x46,0x6e,0x1d,0x97,0xe8,0xd1,0xe9,
0x4d,0x37,0xa5,0x75,0x5e,0x83,0x9e,0xab,0x82,0x9d,0xb9,0x1c,0xe0,0xcd,0x49,0x89,
0x01,0xb6,0xbd,0x58,0x24,0xa2,0x5f,0x38,0x78,0x99,0x15,0x90,0x50,0xb8,0x95,0xe4,
0xd0,0x91,0xc7,0xce,0xed,0x0f,0xb4,0x6f,0xa0,0xcc,0xf0,0x02,0x4a,0x79,0xc3,0xde,
0xa3,0xef,0xea,0x51,0xe6,0x6b,0x18,0xec,0x1b,0x2c,0x80,0xf7,0x74,0xe7,0xff,0x21,
0x5a,0x6a,0x54,0x1e,0x41,0x31,0x92,0x35,0xc4,0x33,0x07,0x0a,0xba,0x7e,0x0e,0x34,
0x88,0xb1,0x98,0x7c,0xf3,0x3d,0x60,0x6c,0x7b,0xca,0xd3,0x1f,0x32,0x65,0x04,0x28,
0x64,0xbe,0x85,0x9b,0x2f,0x59,0x8a,0xd7,0xb0,0x25,0xac,0xaf,0x12,0x03,0xe2,0xf2
};

/* get the high 16bit of the 31bit section */
u32 GethighBit(u32 u){
    u32 result;
    result = u & 0x7FFF8000;
    result = result >> 15;
    return result;
}

/* get the low 16bit of the 31bit section */
u32 GetLowBit(u32 u){
    u32 result;
    result = u & 0xFFFF;
    return result;
}

/*mod(2^23 - 1) 加法的实现 AddM*/
u32 AddM(u32 a, u32 b) {
	u32 c = a + b;
	return (c & 0x7FFFFFFF) + (c >> 31);
}

/* inverse operation of circular shift */
#define COUNTERCIRCULARSHIFT(a,k) (a >> k) | (a >> (32-k))

/* inverse operation of L1 */
u32 CounterL1(u32 X){
    return ~(X ^ COUNTERCIRCULARSHIFT(X,2) ^ COUNTERCIRCULARSHIFT(X,10) ^ COUNTERCIRCULARSHIFT(X,18) ^ COUNTERCIRCULARSHIFT(X,24));
}

/* inverse operation of L2 */
u32 CounterL2(u32 X){
    return ~(X ^ COUNTERCIRCULARSHIFT(X,8) ^ COUNTERCIRCULARSHIFT(X,14) ^ COUNTERCIRCULARSHIFT(X,22) ^ COUNTERCIRCULARSHIFT(X,30));
}

/* the state registers of LFSR */
u32 S0;
u32 S1;
u32 S2;
u32 S3;
u32 S4;
u32 S5;
u32 S6;
u32 S7;
u32 S8;
u32 S9;
u32 S10;
u32 S11;
u32 S12;
u32 S13;
u32 S14;
u32 S15;
u32 S16;
u32 S17;
u32 S18;
u32 S19;
u32 S20;
u32 S21;
u32 S22;

/* the different condition of registers in F */
u32 R1_0;
u32 R1_1;
u32 R1_2;
u32 R1_3;
u32 R1_4;
u32 R1_5;
u32 R1_6;
u32 R1_7;
u32 R1_8;
u32 R2_0;
u32 R2_1;
u32 R2_2;
u32 R2_3;
u32 R2_4;
u32 R2_5;
u32 R2_6;
u32 R2_7;
u32 R2_8;

/* the carry bit of caculation */
u32 c1_2;
u32 c1_3;
u32 c1_4;
u32 c2_0;
u32 c2_1;
u32 c2_3;
u32 c2_4;
u32 c2_5;
u32 c2_6;
u32 c2_7;
u32 c3_2;
u32 c3_3;
u32 c3_5;
u32 c3_7;

/*intercepted key stream */
u32 Z2;
u32 Z3;
u32 Z4;
u32 Z5;
u32 Z6;
u32 Z7;
u32 Z8;

/* W of the F*/
u32 W1_3;
u32 W2_3;

/* this function is using to itreation states */
void IterateStates(){
    if(S4 != 0xFFFFFFFF){
        S4 += 1;
    }
    else{
        S4 = 0;
        if(S5 != 0xFFFFFFFF){
            S5 += 1;
        }
        else{
            S5 = 0;
            if(S6 != 0xFFFFFFFF){
                S6 += 1;
            }
            else{
                S6 = 0;
                if(S8 != 0x0000FFFF){
                    S8 += 1;
                }
                else{
                    S8 = 0;
                    if(S9 != 0xFFFFFFFF){
                        S9 += 1;
                    }
                    else{
                        S9 = 0;
                        if(S14 != 0x0000FFFF){
                            S14 += 1;
                        }
                        else{
                            S14 = 0;
                            if(S15 != 0xFFFFFFFF){
                                S15 += 1;
                            }
                            else{
                                S15 = 0;
                                if(S17 != 0x0000FFFF){
                                    S17 += 1;
                                }
                                else{
                                    S17 = 0;
                                    if(S18 != 0xFFFFFFFF){
                                        S18 += 1;
                                    }
                                    else{
                                        S18 = 0;
                                        if(S19 != 0xFFFFFFFF){
                                            S19 += 1;
                                        }
                                        else{
                                            S19 = 0;
                                            if(S20 != 0x7FFF8000){
                                                S20 = S20 >> 15;
                                                S20 += 1;
                                                S20 = S20 << 15;
                                            }
                                            else{
                                                S20 = 0;
                                                if(S22 != 0x7FFF8000){
                                                    S22 = S22 >> 15;
                                                    S22 += 1;
                                                    S22 = S22 << 15;
                                                }
                                                else{
                                                    S22 = 0;
                                                    if(R1_4 != 0xFFFFFFFF){
                                                        R1_4 += 1;
                                                    }
                                                    else{
                                                        R1_4 = 0;
                                                        if(R1_6 != 0xFFFFFFFF){
                                                            R1_6 += 1;
                                                        }
                                                        else{
                                                            R1_6 = 0;
                                                            if(c1_3 == 0){
                                                                c1_3 = 1;
                                                            }
                                                            else{
                                                                c1_3 = 0;
                                                                if(c2_3 == 0){
                                                                    c2_3 = 1;
                                                                }
                                                                else{
                                                                    c2_3 = 0;
                                                                    if(c2_4 == 0){
                                                                        c2_4 = 1;
                                                                    }
                                                                    else{
                                                                        c2_4 = 0;
                                                                        if(c2_6 == 0){
                                                                            c2_6 = 1;
                                                                        }
                                                                        else{
                                                                            c2_6 = 0;
                                                                            if(c2_7 == 0){
                                                                                c2_7 = 1;
                                                                            }
                                                                            else{
                                                                                c2_7 = 0;
                                                                                if(c3_3 == 0){
                                                                                    c3_3 = 1;
                                                                                }
                                                                                else{
                                                                                    c3_3 = 0;
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/* the progress of Attack */
int main(){
        S4 = 0;
        S5 = 0;
        S6 = 0;
        S8 = 0;
        S9 = 0;
        S14 = 0;
        S15 = 0;
        S17 = 0;
        S18 = 0;
        S19 = 0;
        S20 = 0;
        S22 = 0;
        R1_4 = 0;
        R1_6 = 0;
        c1_3 = 0;
        c2_3 = 0;
        c2_4 = 0;
        c2_6 = 0;
        c2_7 = 0;
        c3_3 = 0;
        int i;
        u32 result, container1, container2;
        printf("This is the program that embody the algorithm of conjecture and determine attack.\n");
        printf("Please input the cipher.\n");
        printf("Cipher block 1:");
        scanf("%X",&Z2);
        printf("Cipher block 2:");
        scanf("%X",&Z3);
        printf("Cipher block 3:");
        scanf("%X",&Z4);
        printf("Cipher block 4:");
        scanf("%X",&Z5);
        printf("Cipher block 5:");
        scanf("%X",&Z6);
        printf("Cipher block 6:");
        scanf("%X",&Z7);
        printf("Cipher block 7:");
        scanf("%X",&Z8);
        /* step 1 */
        label:
        printf("Working on step 1...\n");
        container1 = GetLowBit(S4);
        container1 = AddM(container1, MulByPow2(GetLowBit(S4), 8));
        container1 = AddM(container1, MulByPow2(GetLowBit(S8), 20));
        container1 = AddM(container1, MulByPow2(GetLowBit(S14), 21));
        container1 = AddM(container1, MulByPow2(GetLowBit(S17), 17));
        result = AddM(container1, MulByPow2(GetLowBit(S19), 15));
        if (result <= 0xFFFF) {
            c1_4 = 0;
        } else {
            c1_4 = 1;
        }
        S20 = GetLowBit(result);
        printf("Step 1 finished.Get result:the lower 16 bit of S20 is %#X ",S20);
        printf("and c1_4 is %#X.\n",c1_4);


        /* step 2 */
        printf("\nWorking on step 2...\n");
        container1 = S5;
        container1 = AddM(container1, MulByPow2(S5, 8));
        container1 = AddM(container1, MulByPow2(S9, 20));
        container1 = AddM(container1, MulByPow2(S15, 21));
        container1 = AddM(container1, MulByPow2(S18, 17));
        result = AddM(container1, MulByPow2(S20, 15));
        S21 = result;
        printf("Step 2 finished.Get result:the S21 is %#X.\n,",S21);

        /* step 3 */
        printf("\nWorking on step 3...\n");
        container1 = Z4 ^ (GetLowBit(S6) + GethighBit(S4));
        container2 = R1_4 ^ (GethighBit(S19) | (GetLowBit(S18)));
        R2_4 = container1 - container2;
        container1 = GetLowBit(S2);
        container1 = AddM(container1, MulByPow2(GetLowBit(S2), 8));
        container1 = AddM(container1, MulByPow2(GetLowBit(S6), 20));
        container1 = AddM(container1, MulByPow2(GetLowBit(S12), 21));
        container1 = AddM(container1, MulByPow2(GetLowBit(S15), 17));
        result = AddM(container1, MulByPow2(GetLowBit(S17), 15));
        if (result <= 0xFFFF) {
            c1_2 = 0;
        } else {
            c1_2 = 1;
        }
        printf("Step 3 finished.Get result:the R2_4 is %#X ",R2_4);
        printf("and c1_2 is %#X.\n",c1_2);


        /* step 4 */
        printf("\nWorking on step 4...\n");
        int rown;
        int coln;

        /* first,calulate low 16 bit of W1_3 and high 16bit of W2_3 */
        /* get first 8bit */
        for (i = 0; i <= 255; i++) {
                if (Sbox0[i] = R1_4 & 0xFF000000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }

        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        rown -= 1;
        if (coln >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        coln -= 8;
        if (coln >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        coln -= 4;
        if (coln >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        coln -= 2;
        if (coln >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        coln -= 1;

        /* get second 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_4 & 0x00FF0000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00800000;
        } else {
            container1 = container1 & 0xFF7FFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00400000;
        } else {
            container1 = container1 & 0xFFBFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00200000;
        } else {
            container1 = container1 & 0xFFDFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00100000;
        } else {
            container1 = container1 & 0xFFEFFFFF;
        }
        rown -= 1;
        if (coln >= 8) {
            container1 = container1 | 0x00080000;
        } else {
            container1 = container1 & 0xFFF7FFFF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00040000;
        } else {
            container1 = container1 & 0xFFFBFFFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00020000;
        } else {
            container1 = container1 & 0xFFFDFFFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00010000;
        } else {
            container1 = container1 & 0xFFFEFFFF;
        }
        coln -= 1;

        /* get third 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_4 & 0x0000FF00) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00008000;
        } else {
            container1 = container1 & 0xFFFF7FFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00004000;
        } else {
            container1 = container1 & 0xFFFFBFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00002000;
        } else {
            container1 = container1 & 0xFFFFDFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00001000;
        } else {
            container1 = container1 & 0xFFFFEFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00000800;
        } else {
            container1 = container1 & 0xFFFFF7FF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000400;
        } else {
            container1 = container1 & 0xFFFFFBFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000200;
        } else {
            container1 = container1 & 0xFFFFFDFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000100;
        } else {
            container1 = container1 & 0xFFFFFEFF;
        }
        coln -= 1;

        /* get last 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_4 & 0x000000FF) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00000080;
        } else {
            container1 = container1 & 0xFFFFFF7F;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00000040;
        } else {
            container1 = container1 & 0xFFFFFFBF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00000020;
        } else {
            container1 = container1 & 0xFFFFFFDF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00000010;
        } else {
            container1 = container1 & 0xFFFFFFEF;
        }
        rown -= 1;
        if (coln >= 8) {
            container1 = container1 | 0x00000008;
        } else {
            container1 = container1 & 0xFFFFFFF7;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000004;
        } else {
            container1 = container1 & 0xFFFFFFFB;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000002;
        } else {
            container1 = container1 & 0xFFFFFFFD;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000001;
        } else {
            container1 = container1 & 0xFFFFFFFE;
        }
        coln -= 1;

        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL1(container1);

        /* now, put the bits to where they should be */
        container1 = container2;
        W1_3 = ((container1 & 0xFFFF0000) >> 16);
        container1 = ((container1 & 0x0000FFFF) << 16);

        /* so,it's time to calulate low 16 bit of container1container1container1container1 and high 16bit of W1_3 */
        /* get first 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_4 & 0xFF000000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }

        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        coln -= 8;
        if (coln >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        coln -= 4;
        if (coln >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        coln -= 2;
        if (coln >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        coln -= 1;

        /* get second 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_4 & 0x00FF0000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00800000;
        } else {
            container1 = container1 & 0xFF7FFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00400000;
        } else {
            container1 = container1 & 0xFFBFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00200000;
        } else {
            container1 = container1 & 0xFFDFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00100000;
        } else {
            container1 = container1 & 0xFFEFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00080000;
        } else {
            container1 = container1 & 0xFFF7FFFF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00040000;
        } else {
            container1 = container1 & 0xFFFBFFFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00020000;
        } else {
            container1 = container1 & 0xFFFDFFFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00010000;
        } else {
            container1 = container1 & 0xFFFEFFFF;
        }
        coln -= 1;
        /* get third 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_4 & 0x0000FF00) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00008000;
        } else {
            container1 = container1 & 0xFFFF7FFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00004000;
        } else {
            container1 = container1 & 0xFFFFBFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00002000;
        } else {
            container1 = container1 & 0xFFFFDFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00001000;
        } else {
            container1 = container1 & 0xFFFFEFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00000800;
        } else {
            container1 = container1 & 0xFFFFF7FF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000400;
        } else {
            container1 = container1 & 0xFFFFFBFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000200;
        } else {
            container1 = container1 & 0xFFFFFDFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000100;
        } else {
            container1 = container1 & 0xFFFFFEFF;
        }
        coln -= 1;

        /* get last 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_4 & 0x000000FF) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00000080;
        } else {
            container1 = container1 & 0xFFFFFF7F;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00000040;
        } else {
            container1 = container1 & 0xFFFFFFBF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00000020;
        } else {
            container1 = container1 & 0xFFFFFFDF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00000010;
        } else {
            container1 = container1 & 0xFFFFFFEF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00000008;
        } else {
            container1 = container1 & 0xFFFFFFF7;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000004;
        } else {
            container1 = container1 & 0xFFFFFFFB;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000002;
        } else {
            container1 = container1 & 0xFFFFFFFD;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000001;
        } else {
            container1 = container1 & 0xFFFFFFFE;
        }
        coln -= 1;

        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL2(container1);

        /* now, put the bits to where they should be */
        container1 = container2;
        W2_3 = W2_3 | ((container1 & 0xFFFF0000) >> 16);
        W1_3 = W1_3 | ((container1 & 0x0000FFFF) << 16);
        printf("Step 4 finished.Get result:the W1_3 is %#X ",W1_3);
        printf("and W2_3 is %#X.\n",W2_3);

        /* step 5  */
        printf("\nWorking on step 5...\n");
        container1 = GetLowBit(R1_3) + GethighBit(S12);
        if(container1 <= 0xFFFF){
            c2_3 = 0;
        }
        else{
            c2_3 = 1;
        }
        R1_3 = (((W1_3 & 0xFFFF0000) >> 16) - GetLowBit(S14) - c2_3) << 16;
        printf("Step 5 finished.Get result:the higher 16 bit of R1_3 is %#X.\n",R1_3);

        /* step 6 */
        printf("\nWorking on step 6...\n");
        container1 = GetLowBit(R1_4) + GethighBit(S13);
        if(container1 <= 0xFFFF){
            c2_4 = 0;
        }
        else {
            c2_4 = 1;
        }
        container1 = L2(((GetLowBit(R2_4)+ GethighBit(S9)) << 16) | ((R1_4 & 0xFFFF0000) >> 16) + GetLowBit(S15) + c2_4);
        R2_5 = MAKEU32(Sbox0[container1 >> 24], Sbox1[(container1 >> 16 ) & 0xFF], Sbox0[(container1 >> 8) & 0xFF], Sbox1[container1 & 0xFF]);
        printf("Step 6 finished.Get result:the R2_5 is %#X.\n",R2_5);


        /* step 7 */
        printf("\nWorking on step 7...\n");
        container1 = GetLowBit(Z5) ^ GethighBit(S5) - GetLowBit(R2_5);
        R1_5 = container1 ^ GetLowBit(S19);
        printf("Step 7 finished.Get result:the lower 16 bit of R1_5 is %#X ",R1_5);
        printf("and c3_5 is %#X.\n",c3_5);

        /* step 8 */
        /* get third 8bit */
        printf("\nWorking on step 8...\n");
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_5 & 0x0000FF00) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00008000;
        } else {
            container1 = container1 & 0xFFFF7FFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00004000;
        } else {
            container1 = container1 & 0xFFFFBFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00002000;
        } else {
            container1 = container1 & 0xFFFFDFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00001000;
        } else {
            container1 = container1 & 0xFFFFEFFF;
        }
        rown -= 1;
        if (!rown) {
            printf("step4 error!");
        }

        if (coln >= 8) {
            container1 = container1 | 0x00000800;
        } else {
            container1 = container1 & 0xFFFFF7FF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000400;
        } else {
            container1 = container1 & 0xFFFFFBFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000200;
        } else {
            container1 = container1 & 0xFFFFFDFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000100;
        } else {
            container1 = container1 & 0xFFFFFEFF;
        }
        coln -= 1;

        /* get last 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_5 & 0x000000FF) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00000080;
        } else {
            container1 = container1 & 0xFFFFFF7F;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00000040;
        } else {
            container1 = container1 & 0xFFFFFFBF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00000020;
        } else {
            container1 = container1 & 0xFFFFFFDF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00000010;
        } else {
            container1 = container1 & 0xFFFFFFEF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00000008;
        } else {
            container1 = container1 & 0xFFFFFFF7;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000004;
        } else {
            container1 = container1 & 0xFFFFFFFB;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000002;
        } else {
            container1 = container1 & 0xFFFFFFFD;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000001;
        } else {
            container1 = container1 & 0xFFFFFFFE;
        }
        coln -= 1;

        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL1(container1);

        /* now, put the bits to where they should be */
        S11 = 0x0000FFFF & container2 - R2_4 >> 16;
        printf("Step 8 finished.Get result:the lower 16 bit of S11 is %#X.\n",S11);

        /* step 9 */
        printf("\nWorking on step 9...\n");
        container1 = GetLowBit(S17) ^ GetLowBit(R1_3);
        container2 = container1 + GetLowBit(R2_3);
        if(container2 <= 0xFFFF){
            c3_3 = 0;
        }
        else{
            c3_3 = 1;
        }
        container1 = (Z3 >> 16) ^ GetLowBit(S5);
        container2 = GethighBit(S18) ^ (R1_3 >> 16);
        R2_3 = (container1 - c3_3 - container2) << 16;
        printf("Step 9 finished.Get result:the higher 16 bit of R1_5 is %#X.\n",R2_3);

        /* step 10 */
        printf("\nWorking on step 10...\n");
        /* get third 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_4 & 0x0000FF00) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00008000;
        } else {
            container1 = container1 & 0xFFFF7FFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00004000;
        } else {
            container1 = container1 & 0xFFFFBFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00002000;
        } else {
            container1 = container1 & 0xFFFFDFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00001000;
        } else {
            container1 = container1 & 0xFFFFEFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00000800;
        } else {
            container1 = container1 & 0xFFFFF7FF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000400;
        } else {
            container1 = container1 & 0xFFFFFBFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000200;
        } else {
            container1 = container1 & 0xFFFFFDFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000100;
        } else {
            container1 = container1 & 0xFFFFFEFF;
        }
        coln -= 1;
        /* get last 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_4 & 0x000000FF) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00000080;
        } else {
            container1 = container1 & 0xFFFFFF7F;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00000040;
        } else {
            container1 = container1 & 0xFFFFFFBF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00000020;
        } else {
            container1 = container1 & 0xFFFFFFDF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00000010;
        } else {
            container1 = container1 & 0xFFFFFFEF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00000008;
        } else {
            container1 = container1 & 0xFFFFFFF7;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000004;
        } else {
            container1 = container1 & 0xFFFFFFFB;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000002;
        } else {
            container1 = container1 & 0xFFFFFFFD;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000001;
        } else {
            container1 = container1 & 0xFFFFFFFE;
        }
        coln -= 1;

        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL1(container1);

        /* now, put the bits to where they should be */
        S10 = 0x0000FFFF & container2 - R2_3 >> 16;
        printf("Step 10 finished.Get result:the lower 16 bit of S10 is %#X.\n",S10);

        /* step 11 */
        printf("\nWorking on step 11...\n");
        /* get first 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_6 & 0xFF000000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }

        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        coln -= 8;
        if (coln >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        coln -= 4;
        if (coln >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        coln -= 2;
        if (coln >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        coln -= 1;

        /* get second 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_6 & 0x00FF0000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00800000;
        } else {
            container1 = container1 & 0xFF7FFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00400000;
        } else {
            container1 = container1 & 0xFFBFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00200000;
        } else {
            container1 = container1 & 0xFFDFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00100000;
        } else {
            container1 = container1 & 0xFFEFFFFF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x00080000;
        } else {
            container1 = container1 & 0xFFF7FFFF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00040000;
        } else {
            container1 = container1 & 0xFFFBFFFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00020000;
        } else {
            container1 = container1 & 0xFFFDFFFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00010000;
        } else {
            container1 = container1 & 0xFFFEFFFF;
        }
        coln -= 1;


        /* get third 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_6 & 0x0000FF00) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00008000;
        } else {
            container1 = container1 & 0xFFFF7FFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00004000;
        } else {
            container1 = container1 & 0xFFFFBFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00002000;
        } else {
            container1 = container1 & 0xFFFFDFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00001000;
        } else {
            container1 = container1 & 0xFFFFEFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00000800;
        } else {
            container1 = container1 & 0xFFFFF7FF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000400;
        } else {
            container1 = container1 & 0xFFFFFBFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000200;
        } else {
            container1 = container1 & 0xFFFFFDFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000100;
        } else {
            container1 = container1 & 0xFFFFFEFF;
        }
        coln -= 1;


        /* get last 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_6 & 0x000000FF) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00000080;
        } else {
            container1 = container1 & 0xFFFFFF7F;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00000040;
        } else {
            container1 = container1 & 0xFFFFFFBF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00000020;
        } else {
            container1 = container1 & 0xFFFFFFDF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00000010;
        } else {
            container1 = container1 & 0xFFFFFFEF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00000008;
        } else {
            container1 = container1 & 0xFFFFFFF7;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000004;
        } else {
            container1 = container1 & 0xFFFFFFFB;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000002;
        } else {
            container1 = container1 & 0xFFFFFFFD;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000001;
        } else {
            container1 = container1 & 0xFFFFFFFE;
        }
        coln -= 1;


        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL1(container1);

        /* get the high 16bit of S14 */
        container1 = (container2 & 0xFFFF0000) >> 16;
        S14 = (container1 - GetLowBit(R1_5)) << 15;

        /* get the low 16 bit of S12 */
        container1 = (container2 & 0x0000FFFF);
        S12 = container1 - (R2_5 >> 16);
        printf("Step 11 finished.Get result:the lower 16 bit of S12 is %#X ",S12);
        printf("and the higher 16 bit of S14 is %#X.\n",S14);

        /* step 12 */
        printf("\nWorking on step 12...\n");
        container1 = Z6 ^((GetLowBit(S8)) << 16 | GethighBit(S6)) ^ ((GethighBit(S21)) << 16 | GetLowBit(S20));
        container2 = container1 - R1_6;
        R2_6 = container2;
        printf("Step 12 finished.Get result:the R2_6 is %#X.\n",R2_6);

        /* step 13 */
        printf("\nWorking on step 13...\n");
        /* get first 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_6 & 0xFF000000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }

        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        coln -= 8;
        if (coln >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        coln -= 4;
        if (coln >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        coln -= 2;
        if (coln >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        coln -= 1;


        /* get second 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_6 & 0x00FF0000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00800000;
        } else {
            container1 = container1 & 0xFF7FFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00400000;
        } else {
            container1 = container1 & 0xFFBFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00200000;
        } else {
            container1 = container1 & 0xFFDFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00100000;
        } else {
            container1 = container1 & 0xFFEFFFFF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x00080000;
        } else {
            container1 = container1 & 0xFFF7FFFF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00040000;
        } else {
            container1 = container1 & 0xFFFBFFFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00020000;
        } else {
            container1 = container1 & 0xFFFDFFFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00010000;
        } else {
            container1 = container1 & 0xFFFEFFFF;
        }
        coln -= 1;

        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL2(container1);
        result = ((((0xFFFF0000 & container2) - GetLowBit(R2_5))) & 0x00008000);
        if(result == S10 & 0x00008000){
            /* now, put the bits to where they should be */
            S10 = (((0xFFFF0000 & container2) - GetLowBit(R2_5))) && 0x7FFF0000 | S10;
            printf("Step 13 finished.Get result:the higher 16 bit of S10.\n");
            printf("We have got the lower 16 bit of S10 in step 10.\n");
            printf("So combine the two results and get S10 is %#X.\n",S10);
        }
        else{
            printf("In step 13,we get the higher 16 bit of S10.\n");
            printf("But the last bit of this doesn't equals the first bit of the result in step 10.\n");
            printf("This means the conjecture process is not right.We have to conjecture again.\n\n");
            IterateStates();
            goto label;
        }


        /* step 14 */
        printf("\nWorking on step 14...\n");
        /* get high 16 bit of R1_7*/
        container1 = GetLowBit(R1_6) + GethighBit(S15);
        container2 = L1(container1);
        R1_7 = ((Sbox0[container2 >> 24]) << 24) | ((Sbox1[(container2 >> 16) & 0xFF]) << 16);

        /* get c2_6 */
        container1 = GetLowBit(R1_6) + GethighBit(S15);
        if(container1 <= 0xFFFF){
            c2_6 = 0;
        }
        else{
            c2_6 = 1;
        }

        /* get low 16 bit of R2_7 */
        container1 = c2_6 + GetLowBit(S17) + R1_6 >> 16;
        container2 = L2(container1);
        R2_7 = ((Sbox0[(container2 >> 8) & 0x0000FF00]) | (Sbox1[container2 & 0x000000FF]));
        printf("Step 14 finished.Get result:the lower 16 bit of R2_7 is %#X ",R2_7);
        printf("and the higher 16 bit of R1_7 is %#X.\n",R1_7);


        /* step 15 */
        printf("\nWorking on step 15...\n");
        /* get third 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_6 & 0x0000FF00) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00008000;
        } else {
            container1 = container1 & 0xFFFF7FFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00004000;
        } else {
            container1 = container1 & 0xFFFFBFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00002000;
        } else {
            container1 = container1 & 0xFFFFDFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00001000;
        } else {
            container1 = container1 & 0xFFFFEFFF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x00000800;
        } else {
            container1 = container1 & 0xFFFFF7FF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000400;
        } else {
            container1 = container1 & 0xFFFFFBFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000200;
        } else {
            container1 = container1 & 0xFFFFFDFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000100;
        } else {
            container1 = container1 & 0xFFFFFEFF;
        }
        coln -= 1;


        /* get last 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_6 & 0x000000FF) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00000080;
        } else {
            container1 = container1 & 0xFFFFFF7F;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00000040;
        } else {
            container1 = container1 & 0xFFFFFFBF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00000020;
        } else {
            container1 = container1 & 0xFFFFFFDF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00000010;
        } else {
            container1 = container1 & 0xFFFFFFEF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x00000008;
        } else {
            container1 = container1 & 0xFFFFFFF7;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000004;
        } else {
            container1 = container1 & 0xFFFFFFFB;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000002;
        } else {
            container1 = container1 & 0xFFFFFFFD;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000001;
        } else {
            container1 = container1 & 0xFFFFFFFE;
        }
        coln -= 1;


        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL1(container1);
        /* now, put the bits to where they should be */
        S16 = (0x0000FFFF & container2 - GethighBit(R2_5)) >> 16;
        printf("Step 15 finished.Get result:the lower 16 bit of S16 is %#X.\n",S16);

        /* step 16 */
        printf("\nWorking on step 16...\n");
        container1 = GetLowBit(S6);
        container1 = AddM(container1, MulByPow2(GetLowBit(S6), 8));
        container1 = AddM(container1, MulByPow2(GetLowBit(S10), 20));
        container1 = AddM(container1, MulByPow2(GetLowBit(S16), 21));
        container1 = AddM(container1, MulByPow2(GetLowBit(S19), 17));
        result = AddM(container1, MulByPow2(GetLowBit(S21), 15));
        if (result <= 0xFFFF) {
            c1_4 = 0;
        } else {
            c1_4 = 1;
        }
        S22 = GetLowBit(result);
        container1 = GetLowBit(S21) ^ GetLowBit(R1_7);
        container2 = container1 + GetLowBit(R2_7);
        if(container2 <= 0xFFFF){
            c3_7 = 0;
        }
        else{
            c3_7 = 1;
        }
        printf("Step 16 finished.Get result:the lower 16 bit of S22 is %#X ",S22);
        printf("and the c3_7 is %#X\n.\n",c3_7);


        /* step 17 */
        printf("\nWorking on step 17...\n");
        container1 = GetLowBit(R1_5) + GethighBit(S14);
        if(container1 <= 0xFFFF){
            c2_4 = 0;
        }
        else {
            c2_4 = 1;
        }

       /* get third 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_6 & 0x0000FF00) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00008000;
        } else {
            container1 = container1 & 0xFFFF7FFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00004000;
        } else {
            container1 = container1 & 0xFFFFBFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00002000;
        } else {
            container1 = container1 & 0xFFFFDFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00001000;
        } else {
            container1 = container1 & 0xFFFFEFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00000800;
        } else {
            container1 = container1 & 0xFFFFF7FF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000400;
        } else {
            container1 = container1 & 0xFFFFFBFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000200;
        } else {
            container1 = container1 & 0xFFFFFDFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000100;
        } else {
            container1 = container1 & 0xFFFFFEFF;
        }
        coln -= 1;


        /* get last 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_6 & 0x000000FF) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00000080;
        } else {
            container1 = container1 & 0xFFFFFF7F;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00000040;
        } else {
            container1 = container1 & 0xFFFFFFBF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00000020;
        } else {
            container1 = container1 & 0xFFFFFFDF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00000010;
        } else {
            container1 = container1 & 0xFFFFFFEF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x00000008;
        } else {
            container1 = container1 & 0xFFFFFFF7;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000004;
        } else {
            container1 = container1 & 0xFFFFFFFB;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000002;
        } else {
            container1 = container1 & 0xFFFFFFFD;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000001;
        } else {
            container1 = container1 & 0xFFFFFFFE;
        }
        coln -= 1;

        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL2(container1);
        result = GethighBit(S14) + GetLowBit(R1_5);
        if(result < 0x00010000){
            c2_5 = 0;
        }
        else{
            c2_5 = 1;
        }
        /* now, put the bits to where they should be */
        R1_5 = (0x0000FFFF & container2 - R1_5 >> 16 - c2_5) << 16;
        printf("Step 17 finished.Get result:the higher 16 bit of R1_5 is %#X.\n",R1_5);

        /* step 18 */
        printf("\nWorking on step 18...\n");
        /* get first 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_5 & 0xFF000000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }

        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        coln -= 8;
        if (coln >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        coln -= 4;
        if (coln >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        coln -= 2;
        if (coln >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        coln -= 1;

        /* get second 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_5 & 0x00FF0000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00800000;
        } else {
            container1 = container1 & 0xFF7FFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00400000;
        } else {
            container1 = container1 & 0xFFBFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00200000;
        } else {
            container1 = container1 & 0xFFDFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00100000;
        } else {
            container1 = container1 & 0xFFEFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00080000;
        } else {
            container1 = container1 & 0xFFF7FFFF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00040000;
        } else {
            container1 = container1 & 0xFFFBFFFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00020000;
        } else {
            container1 = container1 & 0xFFFDFFFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00010000;
        } else {
            container1 = container1 & 0xFFFEFFFF;
        }
        coln -= 1;


        container2 = CounterL1(container1);
        S13 = ((container2 >> 16) - GetLowBit(R1_4)) << 15;
        printf("Step 18 finished.Get result:the higher 16 bit of S13 is %#X.\n",S13);


        /* step 19 */
        printf("\nWorking on step 19...\n");
        container1 = GetLowBit(S21) ^ GetLowBit(R1_7);
        container2 = container1 + GetLowBit(R2_7);
        if(container2 <= 0xFFFF){
            c3_7 = 0;
        }
        else{
            c3_7 = 1;
        }
        container1 = (Z7 >> 16) ^ GetLowBit(S9);
        container2 = GethighBit(S22) ^ (R1_7 >> 16);
        R2_7 = (container1 - c3_7 - container2) << 16 | R2_7;
        printf("Step 19 finished.Get result:the higher 16 bit of R2_7.\n");
        printf("We have got the lower 16 bit of R2_7 in step 14.\n");
        printf("So combine the two results and get R2_7 is %#X.\n",R2_7);

        /* step 20 */
        printf("\nWorking on step 20...\n");
        /* get c2_7 */
        container1 = GetLowBit(R1_7) + GethighBit(S16);
        if(container1 <= 0xFFFF){
            c2_7 = 0;
        }
        else{
            c2_7 = 1;
        }

        container1 = (R1_7 >> 16) + GetLowBit(S18) + c2_7;
        container2 = L2(container1);
        R2_8 = (Sbox0[(container2 >> 8) & 0xFF]) << 8 | Sbox1[container2 & 0xFF] ;

        container1 = R2_7 >> 16 + GetLowBit(S14);
        container2 = L1(container1);
        R1_8 = (Sbox0[(container2 >> 8) & 0xFF]) << 8 | Sbox1[container2 & 0xFF];
        printf("Step 20 finished.Get result:the lower 16 bit of R1_8 is %#X ",R1_8);
        printf("and the lowerer 16 bit of R2_8 is %#X.\n",R2_8);

        /* step 21 */
        printf("\nWorking on step 21...\n");
        container1 = GetLowBit(S22) + GetLowBit(R1_8) + GetLowBit(R2_8);
        container2 = GetLowBit(Z8);
        S8 = (container2 ^ container1) << 15;
        printf("Step 21 finished.Get result:the higher 16 bit of S8 is %#X.\n",S8);

        /* step 22 */
        printf("\nWorking on step 22...\n");
        container1 = AddM(MulByPow2(S13, 17), MulByPow2(S15, 15));
        container1 = AddM(container1, MulByPow2(S10, 21));
        container1 = AddM(container1, MulByPow2(S4, 20));
        container2 = S16 - container1;
        while(container2 < 0){
            container2 += 0x7FFFFFFF;
        }
        container2 = container2 / 0x10002;
        S0 = container2;
        printf("Step 22 finished.Get result:the S0 is %#X.\n",S0);

        /* step 23 */
        printf("\nWorking on step 23...\n");
        container1 = GetLowBit(S4);
        container1 = AddM(container1, MulByPow2(GetLowBit(S2), 8));
        container1 = AddM(container1, MulByPow2(GetLowBit(S6), 20));
        container1 = AddM(container1, MulByPow2(GetLowBit(S12), 21));
        container1 = AddM(container1, MulByPow2(GetLowBit(S15), 17));
        result = AddM(container1, MulByPow2(GetLowBit(S17), 15));
        if (result <= 0xFFFF) {
            c1_2 = 0;
        } else {
            c1_2 = 1;
        }

        container1 = AddM(MulByPow2(GetLowBit(S15), 17), MulByPow2(GetLowBit(S17), 15));
        container1 = AddM(container1, MulByPow2(GetLowBit(S12), 21));
        container1 = AddM(container1, MulByPow2(GetLowBit(S6), 20));
        container2 = GetLowBit(S18) - container1;
        while(container2 < 0){
            container2 += 0xFFFF;
        }
        container2 = container2 / 0x10002;
        S2 = (container2) & 0x0000FFFF;
        printf("Step 23 finished.Get result:the lower 16 bit of S2 is %#X ",S2);
        printf("and the c1_2 is %#X.\n",c1_2);

        /* step 24 */
        printf("\nWorking on step 24...\n");
        /* get first 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_7 & 0xFF000000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }

        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        coln -= 8;
        if (coln >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        coln -= 4;
        if (coln >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        coln -= 2;
        if (coln >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        coln -= 1;
        /* get second 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_7 & 0x00FF0000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00800000;
        } else {
            container1 = container1 & 0xFF7FFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00400000;
        } else {
            container1 = container1 & 0xFFBFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00200000;
        } else {
            container1 = container1 & 0xFFDFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00100000;
        } else {
            container1 = container1 & 0xFFEFFFFF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x00080000;
        } else {
            container1 = container1 & 0xFFF7FFFF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00040000;
        } else {
            container1 = container1 & 0xFFFBFFFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00020000;
        } else {
            container1 = container1 & 0xFFFDFFFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00010000;
        } else {
            container1 = container1 & 0xFFFEFFFF;
        }
        coln -= 1;

        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL2(container1);

        result = (((0xFFFF0000 & container2) - GetLowBit(R2_6))) & 0x00008000;
        /* now, put the bits to where they should be */
        if(result == S11 & 0x00008000){
            /* now, put the bits to where they should be */
            S11 = (((0xFFFF0000 & container2) - GetLowBit(R2_6))) & 0x7FFF0000 | S11;
            printf("Step 24 finished.Get result:the higher 16 bit of S11.\n");
            printf("We have got the lower 16 bit of S11 in step 8.\n");
            printf("So combine the two results and get S11 is %#X.\n",S11);
        }
        else{
            printf("In step 24,we get the higher 16 bit of S11.\n");
            printf("But the last bit of this doesn't equals the first bit of the result in step 8.\n");
            printf("This means the conjecture process is not right.We have to conjecture again.\n");
            IterateStates();
            goto label;


        /* step 25 */
        printf("\nWorking on step 25...\n");
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_3 & 0xFF000000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }

        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        coln -= 8;
        if (coln >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        coln -= 4;
        if (coln >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        coln -= 2;
        if (coln >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        coln -= 1;

        /* get second 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_3 & 0x00FF0000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00800000;
        } else {
            container1 = container1 & 0xFF7FFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00400000;
        } else {
            container1 = container1 & 0xFFBFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00200000;
        } else {
            container1 = container1 & 0xFFDFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00100000;
        } else {
            container1 = container1 & 0xFFEFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00080000;
        } else {
            container1 = container1 & 0xFFF7FFFF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00040000;
        } else {
            container1 = container1 & 0xFFFBFFFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00020000;
        } else {
            container1 = container1 & 0xFFFDFFFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00010000;
        } else {
            container1 = container1 & 0xFFFEFFFF;
        }
        coln -= 1;

        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL1(container1);

        /* now, put the bits to where they should be */
        R1_2 = ((0xFFFF0000 & container2) >> 16  - GethighBit(S11)) & 0x0000FFFF;
        printf("Step 25 finished.Get result:the lower 16 bit of R1_2 is %#X.\n",R1_2);

        /* step 26 */
        printf("\nWorking on step 26...\n");
        container1 = Z7 ^ ((GethighBit(S22)) << 16 | (GetLowBit(21))) ^ (R1_7 + R2_7);
        container2 = container1 & 0x0000FFFF;
        S7 = container2 << 15;
        printf("Step 26 finished.Get result:the higher 16 bit of S7 is %#X.\n",S7);

        /* step 27 */
        printf("\nWorking on step 27...\n");
        /* get first 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_3 & 0xFF000000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }

        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        coln -= 8;
        if (coln >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        coln -= 4;
        if (coln >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        coln -= 2;
        if (coln >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        coln -= 1;


        /* get second 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_3 & 0x00FF0000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00800000;
        } else {
            container1 = container1 & 0xFF7FFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00400000;
        } else {
            container1 = container1 & 0xFFBFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00200000;
        } else {
            container1 = container1 & 0xFFDFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00100000;
        } else {
            container1 = container1 & 0xFFEFFFFF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x00080000;
        } else {
            container1 = container1 & 0xFFF7FFFF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00040000;
        } else {
            container1 = container1 & 0xFFFBFFFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00020000;
        } else {
            container1 = container1 & 0xFFFDFFFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00010000;
        } else {
            container1 = container1 & 0xFFFEFFFF;
        }
        coln -= 1;

        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL2(container1);

        /* now, put the bits to where they should be */
        R2_2 = ((0xFFFF0000 & container2) >> 16  - GethighBit(S7)) & 0x0000FFFF;
        printf("Step 27 finished.Get result:the lower 16 bit of R2_2 is %#X.\n",R2_2);

        /* step 28 */
        printf("\nWorking on step 28...\n");
        container1 = GetLowBit(S16) ^ GetLowBit(R1_2) + GetLowBit(R2_2);
        container2 = GetLowBit(Z2) ^ container1;

        result = (container2 << 15) & 0x00008000;
        if(result == S2 & 0x00008000){
            /* now, put the bits to where they should be */
            S2 = container2 << 15 | S2;
            printf("Step 28 finished.Get result:the higher 16 bit of S2.\n");
            printf("We have got the lower 16 bit of S2 in step 23.\n");
            printf("So combine the two results and get S2 is %#X.\n",S2);
        }
        else{
            printf("In step 28,we get the higher 16 bit of S2.\n");
            printf("But the last bit of this doesn't equals the first bit of the result in step 23.\n");
            printf("This means the conjecture process is not right.We have to conjecture again.\n");
            IterateStates();
            goto label;
        }

        /* step 29 */
        printf("\nWorking on step 29...\n");
        container1 = AddM(MulByPow2(GethighBit(S15), 17), MulByPow2(GethighBit(S17), 15));
        container1 = AddM(container1, MulByPow2(GethighBit(S6), 20));
        container1 = AddM(container1, MulByPow2(GethighBit(S2),8));
        container1 = AddM(container1,GethighBit(S2));
        container2 = GethighBit(S18) - container1 - c1_2;
        while(container2 < 0){
            container2 += 0xFFFF0000;
        }
        container2 = container2 / 0x20001;
        result = (container2) & 0x00008000;
        if(result == S12 & 0x00008000){
            /* now, put the bits to where they should be */
            S12 = (container2) & 0x7FFF0000 | S12;
            printf("Step 29 finished.Get result:the higher 16 bit of S12.\n");
            printf("We have got the lower 16 bit of S12 in step 11.\n");
            printf("So combine the two results and get S12 is %#X.\n",S12);
        }
        else{
            printf("In step 29,we get the higher 16 bit of S12.\n");
            printf("But the last bit of this doesn't equals the first bit of the result in step 11.\n");
            printf("This means the conjecture process is not right.We have to conjecture again.\n");
            IterateStates();
            goto label;
        }

        /* step 30 */
        printf("\nWorking on step 30...\n");
        container1 = Z5 ^ ((GethighBit(S20)) << 16 | (GetLowBit(19))) ^ (R1_5 + R2_5);
        container2 = container1 & 0xFFFF0000;
        result = (container2) & 0x00008000;
        if(result == S7 & 0x00008000){
            /* now, put the bits to where they should be */
            S7 = container2 >> 16 | S7;
            printf("Step 30 finished.Get result:the lowerer 16 bit of S7.\n");
            printf("We have got the higher 16 bit of S7 in step 26.\n");
            printf("So combine the two results and get S7 is %#X.\n",S7);
        }
        else{
            printf("In step 30,we get the higher 16 bit of S7.\n");
            printf("But the last bit of this doesn't equals the first bit of the result in step 26.\n");
            printf("This means the conjecture process is not right.We have to conjecture again.\n");
            IterateStates();
            goto label;
        }

        /* step 31 */
        printf("\nWorking on step 31...\n");
        /* get first 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_4 & 0xFF000000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }

        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        coln -= 8;
        if (coln >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        coln -= 4;
        if (coln >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        coln -= 2;
        if (coln >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        coln -= 1;

        /* get second 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_4 & 0x00FF0000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00800000;
        } else {
            container1 = container1 & 0xFF7FFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00400000;
        } else {
            container1 = container1 & 0xFFBFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00200000;
        } else {
            container1 = container1 & 0xFFDFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00100000;
        } else {
            container1 = container1 & 0xFFEFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00080000;
        } else {
            container1 = container1 & 0xFFF7FFFF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00040000;
        } else {
            container1 = container1 & 0xFFFBFFFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00020000;
        } else {
            container1 = container1 & 0xFFFDFFFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00010000;
        } else {
            container1 = container1 & 0xFFFEFFFF;
        }
        coln -= 1;

        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL2(container1);

        /* now, put the bits to where they should be */

        R1_3 = ((0xFFFF0000 & container2) >> 16  - GethighBit(S12)) & 0x0000FFFF | R1_3;

        /* get the first 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_4 & 0xFF000000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }

        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        coln -= 8;
        if (coln >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        coln -= 4;
        if (coln >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        coln -= 2;
        if (coln >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        coln -= 1;


        /* get second 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_4 & 0x00FF0000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00800000;
        } else {
            container1 = container1 & 0xFF7FFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00400000;
        } else {
            container1 = container1 & 0xFFBFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00200000;
        } else {
            container1 = container1 & 0xFFDFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00100000;
        } else {
            container1 = container1 & 0xFFEFFFFF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x00080000;
        } else {
            container1 = container1 & 0xFFF7FFFF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00040000;
        } else {
            container1 = container1 & 0xFFFBFFFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00020000;
        } else {
            container1 = container1 & 0xFFFDFFFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00010000;
        } else {
            container1 = container1 & 0xFFFEFFFF;
        }
        coln -= 1;

        /* get the 32bit stream by reserse L opreation */

        container2 = CounterL2(container1);

        /* now, put the bits to where they should be */
        R2_3 = ((0xFFFF0000 & container2) >> 16  - GethighBit(S8)) & 0x0000FFFF | R2_3;
        printf("Step 31 finished.Get result:the lower 16 bit of R1_3.\n");
        printf("We have got the higher 16 bit of R1_3 in step 5.\n");
        printf("So combine the two results and get R1_3 is %#X.\n",R1_3);
        printf("Step 31 finished.Get result:the lower 16 bit of R2_3.\n");
        printf("We have got the higher 16 bit of R2_3 in step 9.\n");
        printf("So combine the two results and get R2_3 is %#X.\n",R1_3);

        /* step 32 */
        printf("\nWorking on step 32...\n");
        /* get third 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_3 & 0x0000FF00) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00008000;
        } else {
            container1 = container1 & 0xFFFF7FFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00004000;
        } else {
            container1 = container1 & 0xFFFFBFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00002000;
        } else {
            container1 = container1 & 0xFFFFDFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00001000;
        } else {
            container1 = container1 & 0xFFFFEFFF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x00000800;
        } else {
            container1 = container1 & 0xFFFFF7FF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000400;
        } else {
            container1 = container1 & 0xFFFFFBFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000200;
        } else {
            container1 = container1 & 0xFFFFFDFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000100;
        } else {
            container1 = container1 & 0xFFFFFEFF;
        }
        coln -= 1;


        /* get last 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_3 & 0x000000FF) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00000080;
        } else {
            container1 = container1 & 0xFFFFFF7F;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00000040;
        } else {
            container1 = container1 & 0xFFFFFFBF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00000020;
        } else {
            container1 = container1 & 0xFFFFFFDF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00000010;
        } else {
            container1 = container1 & 0xFFFFFFEF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x00000008;
        } else {
            container1 = container1 & 0xFFFFFFF7;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000004;
        } else {
            container1 = container1 & 0xFFFFFFFB;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000002;
        } else {
            container1 = container1 & 0xFFFFFFFD;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000001;
        } else {
            container1 = container1 & 0xFFFFFFFE;
        }
        coln -= 1;


        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL1(container1);
        /* now, put the bits to where they should be */
        R2_2 = (0x0000FFFF & container2 - GetLowBit(S9)) << 16 | R2_2;
        printf("Step 32 finished.Get result:the higher 16 bit of R2_2.\n");
        printf("We have got the lower 16 bit of R2_2 in step 27.\n");
        printf("So combine the two results and get R2_2 is %#X.\n",R2_2);

        /* step 33 */
        printf("\nWorking on step 33...\n");
        container1 = GetLowBit(S17) ^ GetLowBit(R1_3) + GetLowBit(R2_3);
        container2 = GetLowBit(Z3) ^ container1;
        S3 = container2 << 15;
        printf("Step 33 finished.Get result:the higher 16 bit of S3 is %#X.\n",S3);

        /* step 34 */
        printf("\nWorking on step 34...\n");
        container1 = GetLowBit(S3);
        container1 = AddM(container1, MulByPow2(GetLowBit(S3), 8));
        container1 = AddM(container1, MulByPow2(GetLowBit(S7), 20));
        container1 = AddM(container1, MulByPow2(GetLowBit(S13), 21));
        container1 = AddM(container1, MulByPow2(GetLowBit(S16), 17));
        result = AddM(container1, MulByPow2(GetLowBit(S18), 15));
        if (result <= 0x00010000) {
            c1_3 = 0;
        } else {
            c1_3 = 1;
        }
        container1 = AddM(MulByPow2(GethighBit(S13), 21), MulByPow2(GethighBit(S18), 15));
        container1 = AddM(container1, MulByPow2(GethighBit(S7), 20));
        container1 = AddM(container1, MulByPow2(GethighBit(S3),8));
        container1 = AddM(container1,GethighBit(S3));
        container2 = GethighBit(S19) - container1 - c1_3;
        while(container2 < 0){
            container2 += 0xFFFF0000;
        }
        container2 = container2 / 0x20001;
        result = container2 & 0x00008000;
        if(result == S16 & 0x00008000){
            /* now, put the bits to where they should be */
            S16 = container2 & 0x7FFF0000 | S16;
            printf("Step 34 finished.Get result:the higher 16 bit of S16.\n");
            printf("We have got the lower 16 bit of S16 in step 15.\n");
            printf("So combine the two results and get S16 is %#X.\n",S16);
        }
        else{
            printf("In step 34,we get the higher 16 bit of S16.\n");
            printf("But the last bit of this doesn't equals the first bit of the result in step 16.\n");
            printf("This means the conjecture process is not right.We have to conjecture again.\n");
            IterateStates();
            goto label;
        }


        /* step 35 */
        printf("\nWorking on step 35...\n");
        result = GetLowBit(S16) ^ GetLowBit(R1_2)+R1_2 >> 16;
        if(result < 0x00010000){
            c3_2 = 0;
        }
        else{
            c3_2 = 1;
        }
        container1 = Z2 >> 16 ^ GetLowBit(S4) ^ GethighBit(S17);
        container2 = (container1 - c3_2 - R2_2) >> 16;
        R1_2 = container2 << 16 | R1_2;
        printf("Step 35 finished.Get result:the higher 16 bit of R1_2.\n");
        printf("We have got the higher 16 bit of R1_2 in step 25.\n");
        printf("So combine the two results and get R1_2 is %#X.\n",R1_2);

        /* step 36 */
        printf("\nWorking on step 36...\n");
        container1 = GetLowBit(Z7) ^ GethighBit(S7) - GetLowBit(R2_7);
        R1_7 = (container1 ^ GetLowBit(S21)) & 0x0000FFFF | R1_7;
        printf("Step 36 finished.Get result:the lower 16 bit of R1_7.\n");
        printf("We have got the higher 16 bit of R1_7 in step 14.\n");
        printf("So combine the two results and get R1_7 is %#X.\n",R1_7);

        /* step 37 */
        printf("\nWorking on step 37...\n");
        /* get third 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_7 & 0x0000FF00) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00008000;
        } else {
            container1 = container1 & 0xFFFF7FFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00004000;
        } else {
            container1 = container1 & 0xFFFFBFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00002000;
        } else {
            container1 = container1 & 0xFFFFDFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00001000;
        } else {
            container1 = container1 & 0xFFFFEFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00000800;
        } else {
            container1 = container1 & 0xFFFFF7FF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000400;
        } else {
            container1 = container1 & 0xFFFFFBFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000200;
        } else {
            container1 = container1 & 0xFFFFFDFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000100;
        } else {
            container1 = container1 & 0xFFFFFEFF;
        }
        coln -= 1;

        /* get last 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_7 & 0x000000FF) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00000080;
        } else {
            container1 = container1 & 0xFFFFFF7F;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00000040;
        } else {
            container1 = container1 & 0xFFFFFFBF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00000020;
        } else {
            container1 = container1 & 0xFFFFFFDF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00000010;
        } else {
            container1 = container1 & 0xFFFFFFEF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00000008;
        } else {
            container1 = container1 & 0xFFFFFFF7;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000004;
        } else {
            container1 = container1 & 0xFFFFFFFB;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000002;
        } else {
            container1 = container1 & 0xFFFFFFFD;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000001;
        } else {
            container1 = container1 & 0xFFFFFFFE;
        }
        coln -= 1;

        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL1(container1);

        /* now, put the bits to where they should be */
        result = (0x0000FFFF & container2 - R2_6 >> 16) & 0x00008000;
        if(result == S13 & 0x00008000){
            /* now, put the bits to where they should be */
            S13 = 0x0000FFFF & container2 - R2_6 >> 16 | S13;
            printf("Step 37 finished.Get result:the lower 16 bit of S13.\n");
            printf("We have got the lower 16 bit of S13 in step 18.\n");
            printf("So combine the two results and get S13 is %#X.\n",S13);
        }
        else{
            printf("In step 37,we get the lower 16 bit of S13.\n");
            printf("But the last bit of this doesn't equals the first bit of the result in step 18.\n");
            printf("This means the conjecture process is not right.We have to conjecture again.\n");
            IterateStates();
            goto label;
        }


        /* step 38 */
        printf("\nWorking on step 38...\n");
        container1 = AddM(MulByPow2(GetLowBit(S16), 17), MulByPow2(GetLowBit(S18), 15));
        container1 = AddM(container1, MulByPow2(GetLowBit(S13), 21));
        container1 = AddM(container1, MulByPow2(GetLowBit(S7), 20));
        container2 = GetLowBit(S19) - container1;
        while(container2 < 0){
            container2 += 0xFFFF;
        }
        container2 = container2 / 0x10002;
        result = container2 & 0x00008000;
        if(result == S3 & 0x00008000){
            /* now, put the bits to where they should be */
            S3 = container2 & 0x0000FFFF | S3;
            printf("Step 38 finished.Get result:the lower 16 bit of S3.\n");
            printf("We have got the lower 16 bit of S3 in step 33.\n");
            printf("So combine the two results and get S3 is %#X.\n",S3);
        }
        else{
            printf("In step 38,we get the lower 16 bit of S3.\n");
            printf("But the last bit of this doesn't equals the first bit of the result in step 33.\n");
            printf("This means the conjecture process is not right.We have to conjecture again.\n");
            IterateStates();
            goto label;
        }

        /* step 39 */
        printf("\nWorking on step 39...\n");
        /* get first 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_2 & 0xFF000000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }

        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        coln -= 8;
        if (coln >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        coln -= 4;
        if (coln >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        coln -= 2;
        if (coln >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        coln -= 1;


        /* get second 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_2 & 0x00FF0000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00800000;
        } else {
            container1 = container1 & 0xFF7FFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00400000;
        } else {
            container1 = container1 & 0xFFBFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00200000;
        } else {
            container1 = container1 & 0xFFDFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00100000;
        } else {
            container1 = container1 & 0xFFEFFFFF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x00080000;
        } else {
            container1 = container1 & 0xFFF7FFFF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00040000;
        } else {
            container1 = container1 & 0xFFFBFFFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00020000;
        } else {
            container1 = container1 & 0xFFFDFFFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00010000;
        } else {
            container1 = container1 & 0xFFFEFFFF;
        }
        coln -= 1;


        /* get third 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_2 & 0x0000FF00) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00008000;
        } else {
            container1 = container1 & 0xFFFF7FFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00004000;
        } else {
            container1 = container1 & 0xFFFFBFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00002000;
        } else {
            container1 = container1 & 0xFFFFDFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00001000;
        } else {
            container1 = container1 & 0xFFFFEFFF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x00000800;
        } else {
            container1 = container1 & 0xFFFFF7FF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000400;
        } else {
            container1 = container1 & 0xFFFFFBFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000200;
        } else {
            container1 = container1 & 0xFFFFFDFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000100;
        } else {
            container1 = container1 & 0xFFFFFEFF;
        }
        coln -= 1;


        /* get last 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_2 & 0x000000FF) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00000080;
        } else {
            container1 = container1 & 0xFFFFFF7F;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00000040;
        } else {
            container1 = container1 & 0xFFFFFFBF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00000020;
        } else {
            container1 = container1 & 0xFFFFFFDF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00000010;
        } else {
            container1 = container1 & 0xFFFFFFEF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x00000008;
        } else {
            container1 = container1 & 0xFFFFFFF7;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000004;
        } else {
            container1 = container1 & 0xFFFFFFFB;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000002;
        } else {
            container1 = container1 & 0xFFFFFFFD;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000001;
        } else {
            container1 = container1 & 0xFFFFFFFE;
        }
        coln -= 1;


        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL1(container1);

        /* now, put the bits to where they should be */
        container1 = container2;
        container1 = ((container1 & 0xFFFF0000) >> 16);
        R1_1 = container1 - GethighBit(S10);

        container2 = (container2 & 0x0000FFFF);
        R2_1 = (container2 - GetLowBit(S8)) << 16;

        container1 = GetLowBit(R1_1) + GethighBit(S10);
        if(container1 <= 0xFFFF){
            c2_1 = 0;
        }
        else{
            c2_1 = 1;
        }

        /* get first 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_2 & 0xFF000000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }

        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        coln -= 8;
        if (coln >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        coln -= 4;
        if (coln >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        coln -= 2;
        if (coln >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        coln -= 1;

        /* get second 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_2 & 0x00FF0000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00800000;
        } else {
            container1 = container1 & 0xFF7FFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00400000;
        } else {
            container1 = container1 & 0xFFBFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00200000;
        } else {
            container1 = container1 & 0xFFDFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00100000;
        } else {
            container1 = container1 & 0xFFEFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00080000;
        } else {
            container1 = container1 & 0xFFF7FFFF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00040000;
        } else {
            container1 = container1 & 0xFFFBFFFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00020000;
        } else {
            container1 = container1 & 0xFFFDFFFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00010000;
        } else {
            container1 = container1 & 0xFFFEFFFF;
        }
        coln -= 1;


        /* get third 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_2 & 0x0000FF00) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00008000;
        } else {
            container1 = container1 & 0xFFFF7FFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00004000;
        } else {
            container1 = container1 & 0xFFFFBFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00002000;
        } else {
            container1 = container1 & 0xFFFFDFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00001000;
        } else {
            container1 = container1 & 0xFFFFEFFF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x00000800;
        } else {
            container1 = container1 & 0xFFFFF7FF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000400;
        } else {
            container1 = container1 & 0xFFFFFBFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000200;
        } else {
            container1 = container1 & 0xFFFFFDFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000100;
        } else {
            container1 = container1 & 0xFFFFFEFF;
        }
        coln -= 1;


        /* get last 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_2 & 0x000000FF) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00000080;
        } else {
            container1 = container1 & 0xFFFFFF7F;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00000040;
        } else {
            container1 = container1 & 0xFFFFFFBF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00000020;
        } else {
            container1 = container1 & 0xFFFFFFDF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00000010;
        } else {
            container1 = container1 & 0xFFFFFFEF;
        }
        rown -= 1;


        if (coln >= 8) {
            container1 = container1 | 0x00000008;
        } else {
            container1 = container1 & 0xFFFFFFF7;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000004;
        } else {
            container1 = container1 & 0xFFFFFFFB;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000002;
        } else {
            container1 = container1 & 0xFFFFFFFD;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000001;
        } else {
            container1 = container1 & 0xFFFFFFFE;
        }
        coln -= 1;


        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL2(container1);

        /* now, put the bits to where they should be */
        container1 = container2;
        R2_1 = (container1 >> 16 - GethighBit(S6)) & 0x0000FFFF | R2_1;
        R1_1 = ((container1 & 0x0000FFFF) - GetLowBit(S12) - c2_1) << 16 | R1_1;
        printf("Step 39 finished.Get result:the R1_1 is %#X ",R1_1);
        printf("and the R2_1 is %#X.\n",R2_1);

        /* step 40 */
        printf("\nWorking on step 40...\n");
        /* get first 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_1 & 0xFF000000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }

        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        coln -= 8;
        if (coln >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        coln -= 4;
        if (coln >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        coln -= 2;
        if (coln >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        coln -= 1;

        /* get second 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_1 & 0x00FF0000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00800000;
        } else {
            container1 = container1 & 0xFF7FFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00400000;
        } else {
            container1 = container1 & 0xFFBFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00200000;
        } else {
            container1 = container1 & 0xFFDFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00100000;
        } else {
            container1 = container1 & 0xFFEFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00080000;
        } else {
            container1 = container1 & 0xFFF7FFFF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00040000;
        } else {
            container1 = container1 & 0xFFFBFFFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00020000;
        } else {
            container1 = container1 & 0xFFFDFFFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00010000;
        } else {
            container1 = container1 & 0xFFFEFFFF;
        }
        coln -= 1;

        /* get third 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_1 & 0x0000FF00) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00008000;
        } else {
            container1 = container1 & 0xFFFF7FFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00004000;
        } else {
            container1 = container1 & 0xFFFFBFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00002000;
        } else {
            container1 = container1 & 0xFFFFDFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00001000;
        } else {
            container1 = container1 & 0xFFFFEFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00000800;
        } else {
            container1 = container1 & 0xFFFFF7FF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000400;
        } else {
            container1 = container1 & 0xFFFFFBFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000200;
        } else {
            container1 = container1 & 0xFFFFFDFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000100;
        } else {
            container1 = container1 & 0xFFFFFEFF;
        }
        coln -= 1;

        /* get last 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R1_1 & 0x000000FF) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00000080;
        } else {
            container1 = container1 & 0xFFFFFF7F;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00000040;
        } else {
            container1 = container1 & 0xFFFFFFBF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00000020;
        } else {
            container1 = container1 & 0xFFFFFFDF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00000010;
        } else {
            container1 = container1 & 0xFFFFFFEF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00000008;
        } else {
            container1 = container1 & 0xFFFFFFF7;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000004;
        } else {
            container1 = container1 & 0xFFFFFFFB;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000002;
        } else {
            container1 = container1 & 0xFFFFFFFD;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000001;
        } else {
            container1 = container1 & 0xFFFFFFFE;
        }
        coln -= 1;

        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL1(container1);

        /* now, put the bits to where they should be */
        container1 = container2;
        container1 = ((container1 & 0xFFFF0000) >> 16);
        R1_0 = container1 - GethighBit(S9);

        container2 = (container2 & 0x0000FFFF);
        R2_0 = (container2 - GetLowBit(S7)) << 16;

        container1 = GetLowBit(R1_0) + GethighBit(S9);
        if(container1 <= 0xFFFF){
            c2_0 = 0;
        }
        else{
            c2_0 = 1;
        }

        /* get first 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_1 & 0xFF000000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }

        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x80000000;
        } else {
            container1 = container1 & 0x7FFFFFFF;
        }
        coln -= 8;
        if (coln >= 4) {
            container1 = container1 | 0x40000000;
        } else {
            container1 = container1 & 0xBFFFFFFF;
        }
        coln -= 4;
        if (coln >= 2) {
            container1 = container1 | 0x20000000;
        } else {
            container1 = container1 & 0xDFFFFFFF;
        }
        coln -= 2;
        if (coln >= 1) {
            container1 = container1 | 0x10000000;
        } else {
            container1 = container1 & 0xEFFFFFFF;
        }
        coln -= 1;

        /* get second 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_1 & 0x00FF0000) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00800000;
        } else {
            container1 = container1 & 0xFF7FFFFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00400000;
        } else {
            container1 = container1 & 0xFFBFFFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00200000;
        } else {
            container1 = container1 & 0xFFDFFFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00100000;
        } else {
            container1 = container1 & 0xFFEFFFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00080000;
        } else {
            container1 = container1 & 0xFFF7FFFF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00040000;
        } else {
            container1 = container1 & 0xFFFBFFFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00020000;
        } else {
            container1 = container1 & 0xFFFDFFFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00010000;
        } else {
            container1 = container1 & 0xFFFEFFFF;
        }
        coln -= 1;

        /* get third 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_1 & 0x0000FF00) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00008000;
        } else {
            container1 = container1 & 0xFFFF7FFF;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00004000;
        } else {
            container1 = container1 & 0xFFFFBFFF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00002000;
        } else {
            container1 = container1 & 0xFFFFDFFF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00001000;
        } else {
            container1 = container1 & 0xFFFFEFFF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00000800;
        } else {
            container1 = container1 & 0xFFFFF7FF;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000400;
        } else {
            container1 = container1 & 0xFFFFFBFF;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000200;
        } else {
            container1 = container1 & 0xFFFFFDFF;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000100;
        } else {
            container1 = container1 & 0xFFFFFEFF;
        }
        coln -= 1;

        /* get last 8bit */
        for (i = 0; i <= 255; i++) {
            if (Sbox0[i] = R2_1 & 0x000000FF) {
                rown = i / 16;
                coln = i % 16;
            } else {
                //no-do op
            }
        }
        /* convert rown,coln from decimalism to hexadecimal */
        if (rown >= 8) {
            container1 = container1 | 0x00000080;
        } else {
            container1 = container1 & 0xFFFFFF7F;
        }
        rown -= 8;
        if (rown >= 4) {
            container1 = container1 | 0x00000040;
        } else {
            container1 = container1 & 0xFFFFFFBF;
        }
        rown -= 4;
        if (rown >= 2) {
            container1 = container1 | 0x00000020;
        } else {
            container1 = container1 & 0xFFFFFFDF;
        }
        rown -= 2;
        if (rown >= 1) {
            container1 = container1 | 0x00000010;
        } else {
            container1 = container1 & 0xFFFFFFEF;
        }
        rown -= 1;

        if (coln >= 8) {
            container1 = container1 | 0x00000008;
        } else {
            container1 = container1 & 0xFFFFFFF7;
        }
        coln -= 8;

        if (coln >= 4) {
            container1 = container1 | 0x00000004;
        } else {
            container1 = container1 & 0xFFFFFFFB;
        }
        coln -= 4;

        if (coln >= 2) {
            container1 = container1 | 0x00000002;
        } else {
            container1 = container1 & 0xFFFFFFFD;
        }
        coln -= 2;

        if (coln >= 1) {
            container1 = container1 | 0x00000001;
        } else {
            container1 = container1 & 0xFFFFFFFE;
        }
        coln -= 1;


        /* get the 32bit stream by reserse L opreation */
        container2 = CounterL2(container1);

        /* now, put the bits to where they should be */
        container1 = container2;
        R2_0 = (container1 >> 16 - GethighBit(S5)) & 0x0000FFFF | R2_0;
        R1_0 = ((container1 & 0x0000FFFF) - GetLowBit(S11) - c2_0) << 16 | R1_0;
        printf("Step 40 finished.Get result:the R1_1 is %#X ",R1_0);
        printf("and the R2_1 is %#X.\n",R2_0);

        /* step 41 */
        printf("\nWorking on step 41...\n");
        container1 = S17 - MulByPow2(S16,15);
        container1 = container1 - MulByPow2(S14,17);
        container1 = container1 - MulByPow2(S11,21);
        container1 = container1 - MulByPow2(S5,20);
        while(container1 < 0){
            container1 += 0xFFFFFFFF;
        }
        container1 = container1 / 0x10002;
        S1 = container1;
        printf("Step 41 finished.Get result:the S1 is %#X.\n",S1);

        /* step 42 */
        printf("\nWorking on step 42...\n");
        container1 = S16 - MulByPow2(S15,15);
        container1 = container1 - MulByPow2(S13,17);
        container1 = container1 - MulByPow2(S10,21);
        container1 = container1 - MulByPow2(S4,20);
        while(container1 < 0){
            container1 += 0xFFFFFFFF;
        }
        container1 = container1 / 0x10002;
        S0 = container1;
        printf("Step 42 finished.Get result:the S0 is %#X.\n",S0);
        }
        printf("The process of attack is finished.");
}
