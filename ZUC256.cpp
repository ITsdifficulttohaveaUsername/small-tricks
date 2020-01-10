#include <malloc.h>
#include <stdio.h>


#define MulByPow2(x, k)((((x)<<k) | ((x)>>(31-k))) & 0x7FFFFFFF)
#define ROT(a, k)(((a)<<k) | ((a) >> (32-k)))
#define MAKEU31(a,b,c)(((uint32)(a) << 23)| ((uint32)(b) << 8) | (uint32)(c))
#define MAKEU32(a,b,c,d)(((uint32)(a) << 24)| ((uint32)(b) << 16) | (uint32)(c) << 8 | (uint32)(d))

typedef unsigned char uchar8;   // 保证了一定是 8-bit
typedef unsigned int uint32;    // 保证了一定是 32 -bit

uint32 LFSR_S0;
uint32 LFSR_S1;
uint32 LFSR_S2;
uint32 LFSR_S3;
uint32 LFSR_S4;
uint32 LFSR_S5;
uint32 LFSR_S6;
uint32 LFSR_S7;
uint32 LFSR_S8;
uint32 LFSR_S9;
uint32 LFSR_S10;
uint32 LFSR_S11;
uint32 LFSR_S12;
uint32 LFSR_S13;
uint32 LFSR_S14;
uint32 LFSR_S15;

uint32 F_R1;
uint32 F_R2;

uint32 BRC_X0;
uint32 BRC_X1;
uint32 BRC_X2;
uint32 BRC_X3;

/* the constants D*/
uchar8 d[16]={
    0x22,0x2F,0x24,0x2A,0x6D,0x40,0x40,0x40,
    0x40,0x40,0x40,0x40,0x40,0x52,0x10,0x30
};

/* seed key stream */
uchar8 K[32];

/* initial vector */
uchar8 IV[25];

uchar8 S0[256] = {
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

uchar8 S1[256] = {
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

uint32 AddM(uint32 a, uint32 b) {
	uint32 c = a + b;
    return (c & 0x7FFFFFFF) + (c >> 31);
}


void LFSRWithInitialisationMode(uint32 u) {
	uint32 f, v;
	f = LFSR_S0;
	v = MulByPow2(LFSR_S0, 8);
	f = AddM(f, v);

	v = MulByPow2(LFSR_S4, 20);
	f = AddM(f, v);

	v = MulByPow2(LFSR_S10, 21);
	f = AddM(f, v);

	v = MulByPow2(LFSR_S13, 17);
	f = AddM(f, v);

	v = MulByPow2(LFSR_S15, 15);
	f = AddM(f, v);

	f = AddM(f, u);

    /*update the state*/

	LFSR_S0 = LFSR_S1;
	LFSR_S1 = LFSR_S2;
	LFSR_S2 = LFSR_S3;
	LFSR_S3 = LFSR_S4;
	LFSR_S4 = LFSR_S5;
	LFSR_S5 = LFSR_S6;
	LFSR_S6 = LFSR_S7;
	LFSR_S7 = LFSR_S8;
	LFSR_S8 = LFSR_S9;
	LFSR_S9 = LFSR_S10;
	LFSR_S10 = LFSR_S11;
	LFSR_S11 = LFSR_S12;
	LFSR_S12 = LFSR_S13;
	LFSR_S13 = LFSR_S14;
	LFSR_S14 = LFSR_S15;
	LFSR_S15 = f;

}


void LFSRWithWorkMode() {
	uint32 f, v; f = LFSR_S0;
	v = MulByPow2(LFSR_S0, 8);
	f = AddM(f, v);

	v = MulByPow2(LFSR_S4, 20);
	f = AddM(f, v);

	v = MulByPow2(LFSR_S10, 21);
	f = AddM(f, v);

	v = MulByPow2(LFSR_S13, 17);
	f = AddM(f, v);

	v = MulByPow2(LFSR_S15, 15);
	f = AddM(f, v);

	/* update the state */
	LFSR_S0 = LFSR_S1;
	LFSR_S1 = LFSR_S2;
	LFSR_S2 = LFSR_S3;
	LFSR_S3 = LFSR_S4;
	LFSR_S4 = LFSR_S5;
	LFSR_S5 = LFSR_S6;
	LFSR_S6 = LFSR_S7;
	LFSR_S7 = LFSR_S8;
	LFSR_S8 = LFSR_S9;
	LFSR_S9 = LFSR_S10;
	LFSR_S10 = LFSR_S11;
	LFSR_S11 = LFSR_S12;
	LFSR_S12 = LFSR_S13;
	LFSR_S13 = LFSR_S14;
	LFSR_S14 = LFSR_S15;
	LFSR_S15 = f;
}

/*BitReconstruction*/
void BitReconstruction() {
	BRC_X0 = ((LFSR_S15 & 0x7FFF8000) << 1) | (LFSR_S14 & 0xFFFF);
	BRC_X1 = ((LFSR_S11 & 0xFFFF) << 16) | (LFSR_S9 >> 15);
	BRC_X2 = ((LFSR_S7 & 0xFFFF) << 16) | (LFSR_S5 >> 15);
	BRC_X3 = ((LFSR_S2 & 0xFFFF) << 16) | (LFSR_S0 >> 15);
}

/*L1, L2*/
uint32 L1(uint32 X) {
	return (X ^ ROT(X, 2) ^ ROT(X, 10) ^ ROT(X, 18) ^ ROT(X, 24));
}

uint32 L2(uint32 X) {
	return (X ^ ROT(X, 8) ^ ROT(X, 14) ^ ROT(X, 22) ^ ROT(X, 30));
}

uint32 F() {
	uint32 W, W1, W2, u, v;
	W = (BRC_X0 ^ F_R1) + F_R2;
	W1 = F_R1 + BRC_X1;
	W2 = F_R2 + BRC_X2;
	u = L1((W1 << 16) | (W2 >> 16));
	v = L2((W2 << 16) | (W1 >> 16));
	F_R1 = MAKEU32(S0[u >> 24], S1[(u >> 16) & 0xFF],
		S0[(u >> 8) & 0xFF], S1[u & 0xFF]);
	F_R2 = MAKEU32(S0[v >> 24], S1[(v >> 16) & 0xFF],
		S0[(v >> 8) & 0xFF], S1[v & 0xFF]);
	return W;
}

void Initialization() {
	uint32 W;
	int nCount = 32;
    /* expand key */
    LFSR_S0 = ((uint32)K[0] << 23)| ((uint32)d[0] << 16) | ((uint32)K[21] << 8) | ((uint32)K[16]);
    LFSR_S1 = ((uint32)K[1] << 23)| ((uint32)d[1] << 16) | ((uint32)K[22] << 8) | ((uint32)K[17]);
    LFSR_S2 = ((uint32)K[2] << 23)| ((uint32)d[2] << 16) | ((uint32)K[23] << 8) | ((uint32)K[18]);
    LFSR_S3 = ((uint32)K[3] << 23)| ((uint32)d[3] << 16) | ((uint32)K[24] << 8) | ((uint32)K[19]);
    LFSR_S4 = ((uint32)K[4] << 23)| ((uint32)d[4] << 16) | ((uint32)K[25] << 8) | ((uint32)K[20]);
    LFSR_S5 = ((uint32)IV[0] << 23)| ((((uint32)d[5]) | ((uint32)IV[17])) << 16) | ((uint32)K[5] << 8) | ((uint32)K[26]);
    LFSR_S6 = ((uint32)IV[1] << 23)| ((((uint32)d[6]) | ((uint32)IV[18])) << 16) | ((uint32)K[6] << 8) | ((uint32)K[27]);
    LFSR_S7 = ((uint32)IV[10] << 23)| ((((uint32)d[7]) | ((uint32)IV[19])) << 16) | ((uint32)K[7] << 8) | ((uint32)IV[2]);
    LFSR_S8 = ((uint32)K[8] << 23)| ((((uint32)d[8]) | ((uint32)IV[20])) << 16) | ((uint32)IV[3] << 8) | ((uint32)IV[11]);
    LFSR_S9 = ((uint32)K[9] << 23)| ((((uint32)d[9]) | ((uint32)IV[21])) << 16) | ((uint32)IV[12] << 8) | ((uint32)IV[4]);
    LFSR_S10 = ((uint32)IV[5] << 23)| ((((uint32)d[10]) | ((uint32)IV[22])) << 16) | ((uint32)K[10] << 8) | ((uint32)K[28]);
    LFSR_S11 = ((uint32)K[11] << 23)| ((((uint32)d[11]) | ((uint32)IV[23])) << 16) | ((uint32)IV[6] << 8) | ((uint32)IV[13]);
    LFSR_S12 = ((uint32)K[12] << 23)| ((((uint32)d[12]) | ((uint32)IV[24])) << 16) | ((uint32)IV[7] << 8) | ((uint32)IV[14]);
    LFSR_S13 = ((uint32)K[13] << 23)| ((uint32)d[13] << 16) | ((uint32)IV[15] << 8) | ((uint32)IV[8]);
    LFSR_S14 = ((uint32)K[14] << 23)| ((((uint32)d[14]) | ((uint32)K[31]) & 0xF0) << 16) | ((uint32)IV[16] << 8) | ((uint32)IV[9]);
    LFSR_S15 = ((uint32)K[15] << 23)| ((((uint32)d[15]) | ((uint32)K[31]) & 0x0F) << 16) | ((uint32)K[30] << 8) | ((uint32)K[29]);


	/*set R1, R2 = 0*/
	F_R1 = 0;
	F_R2 = 0;
	while (nCount > 0) {
		BitReconstruction();
		W = F();
		LFSRWithInitialisationMode(W >> 1);
		nCount--;
	}
}

void GenerateKeystream(int KeystreamLen) {
	int i;
	BitReconstruction();
	F();
	LFSRWithWorkMode();
    uint32 Z;
	for (i = 0; i < KeystreamLen; i++) {
		BitReconstruction();
		Z = F() ^ BRC_X3;
		printf("%x, ",Z);
		LFSRWithWorkMode();
	}
}

int main(){
/* get initial vector */
    printf("Please input the initial vector:\n");
    int count = 0;
    for(count;count <= 16;count++){
        printf("Now you have input IV%d,a 8bit initial vector.\n",count);
        scanf("%x",&IV[count]);
    }
    count = 17;
    for(count;count <= 24;count++){
        printf("Now you have input IV%d,a 6bit initial vector.\n",count);
        scanf("%x",&IV[count]);
    }

    /* get key stream */
    printf("Please input the key stream:\n");
    count = 0;
    for(count;count <= 31;count++){
        printf("Now you have input K%d,a 8bit key.\n",count);
        scanf("%x",&K[count]);
    }

    /* initialization*/
    Initialization();

    /* generate key stream */
    GenerateKeystream(20);

    return 0;
}

