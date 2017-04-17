/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCNoise.h

Abstract:

    Noise / random number related functions.

-------------------------------------------------------------------*/


// Init/shutdown.
BOOL InitNoise(void);
void ShutdownNoise(void);

// Random functions.
extern DWORD gFastRandSeed;
static inline void SeedFastRand(DWORD Seed) { gFastRandSeed=Seed; }
static inline DWORD FastRand(void) { return (gFastRandSeed=1664525*gFastRandSeed + 1013904223)>>16; }
#define FAST_RAND_MAX 0xFFFF

// Not actually a good random number generator but the current terrain looks good.
#define SeedGoodRand srand
#define GoodRand rand
#define GOOD_RAND_MAX RAND_MAX

// Gradient noise functions.
float GNoise1(float A);
float GNoise2(float A, float B);
float GNoise3(float A, float B, float C);

// "Shaping" functions.
float Bias(float In, float Bias);
float Gain(float In, float Gain);
