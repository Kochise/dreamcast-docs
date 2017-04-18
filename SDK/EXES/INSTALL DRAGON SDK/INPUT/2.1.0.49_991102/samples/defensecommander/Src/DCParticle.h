/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCParticle.h

Abstract:

   Particle system funcitons. 

-------------------------------------------------------------------*/

enum ParticleType
{
	LIFETIME,			// User1 is lifetime.
	EXPAND_THEN_FADE,	// User1 is expansion rate, User2 is radius to start fading, User3 is fade rate.
	EXPAND_AND_FADE,	// User1 is expand rate, User2 is fade rate.
	EXPAND_FADE_DECELERATE // User1 is expand rate, User2 is fade rate, User3 is start speed.
};

enum ParticleTexture
{
	SMOKE1=0,
	SMOKE2,
	SMOKE3,
	SMOKE4,
	SMOKE5,
	SMOKE6,
	SMOKE7,
	SMOKE8,
	SMOKE9,
	SMOKE10,
	MAX_PARTICLE_TEXTURES
};

void SpawnParticle(ParticleType Type, ParticleTexture Texture, 
				   DCVector *Loc, float Radius, DCVector *Vel,
				   float InitialTime, float Intensity, DWORD Color,
				   float User1, float User2, float User3);

void KillAllParticles(void);

// Complex particle generation functions.
float ParticleSmokeTrail(DCVector *StartPos, DCVector *EndPos, float StartRadius, float EndRatio, 
						 float TimeLeftFromLast, float DeltaTime, float SpawnRate,
						 float Intensity, DWORD Color, int *LastCount);

void ParticleExplosion(DCVector *Center, float StartRadius, int NumParticles, 
					   float LowFadeRateValue, float HighFadeRateValue, // These are 1/fade time.
					   float Intensity, DWORD Color);
