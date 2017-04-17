/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    RParticle.cpp

Abstract:

	Particle system. 

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"
#include "DCParticle.h"
#include "DCRender.h"

BOOL CreateProceduralSmoke(HANDLE TextureID, int *X, int *Y, DWORD *Flags, DWORD **Data);

#define MAX_PARTICLES 2500

// Particle structure is 64 bytes (2 cache lines). 
// This is important since the array is not accessed sequentially.
struct Particle
{
	Particle *Next;
	BOOL New;
	ParticleType Type;
	DCVector Loc;
	float Radius;
	DCVector Vel;
	float Intensity;
	DWORD Color;
	float User1, User2, User3;
	QWORD AllocNum;
};

struct ParticleList
{
	HANDLE Texture;
	Particle *First,*Last;
	TEXTURE_LOAD_FUNCTION LoadFunc;
	HANDLE LoadFuncTextureID;
	BOOL IdIsText;
};

// Variables.
static BOOL Initialized=FALSE;
static float HScale,VScale;
static Particle *ParticleBuffer;
static Particle *FirstFree;
static ParticleList Lists[MAX_PARTICLE_TEXTURES]=
{
	{NULL,NULL,NULL,CreateProceduralSmoke,(HANDLE)1,FALSE},
	{NULL,NULL,NULL,CreateProceduralSmoke,(HANDLE)2,FALSE},
	{NULL,NULL,NULL,CreateProceduralSmoke,(HANDLE)3,FALSE},
	{NULL,NULL,NULL,CreateProceduralSmoke,(HANDLE)4,FALSE},
	{NULL,NULL,NULL,CreateProceduralSmoke,(HANDLE)5,FALSE},
	{NULL,NULL,NULL,CreateProceduralSmoke,(HANDLE)6,FALSE},
	{NULL,NULL,NULL,CreateProceduralSmoke,(HANDLE)7,FALSE},
	{NULL,NULL,NULL,CreateProceduralSmoke,(HANDLE)8,FALSE},
	{NULL,NULL,NULL,CreateProceduralSmoke,(HANDLE)9,FALSE},
	{NULL,NULL,NULL,CreateProceduralSmoke,(HANDLE)10,FALSE}
};
static QWORD CurrentAllocNum;

#define VBUFF_SIZE (3*256)
static DCVertex *VBuff;

// Initializes the particle system.
BOOL InitParticles(void)
{
	// Allocate memory for particles.
	ParticleBuffer=(Particle *)DCMalloc(sizeof(Particle)*MAX_PARTICLES);
	if (!ParticleBuffer)
		return FALSE;

	// Allocate 32 byte aligned vertex buffer.
	VBuff=(DCVertex *)DCMalloc32(sizeof(DCVertex)*VBUFF_SIZE);
	if (!VBuff)
	{
		DCFree(ParticleBuffer);
		return FALSE;
	}

	// Figure out horizontal and vertical scale for an equilateral triangle
	// to enclose a particle.
	HScale=1.0f/(float)tan(DC_TO_RADIANS(30));
	VScale=2.0f;

	// Init U's and V's in vertex buffer.
	int i;
	for (i=0;i<VBUFF_SIZE;i+=3)
	{
		float Base=0.5f-1.0f/64.0f;

		VBuff[i+0].U=0.5f;
		VBuff[i+0].V=0.5f-VScale*Base;
		VBuff[i+1].U=0.5f+HScale*Base;
		VBuff[i+1].V=0.5f+Base;
		VBuff[i+2].U=0.5f-HScale*Base;
		VBuff[i+2].V=0.5f+Base;
	}

	// Init free linked list.
	Particle *P;
	for (i=0,P=ParticleBuffer;i<MAX_PARTICLES;i++,P++)
	{
		P->Next=FirstFree;
		FirstFree=P;
	}

	// Init texture specific lists.
	for (i=0;i<MAX_PARTICLE_TEXTURES;i++)
	{
		Lists[i].Texture=gGraphics.AddTexture(Lists[i].LoadFunc,
											  Lists[i].LoadFuncTextureID,
											  Lists[i].IdIsText,FALSE);
		Lists[i].First=NULL;
		Lists[i].Last=NULL;
	}

	// Init current alloc num.
	CurrentAllocNum=1;

	Initialized=TRUE;
	return TRUE;
}

// Shuts down the particle system.
void ShutdownParticles(void)
{
	if (Initialized)
	{
		// Free memory for particles.
		DCSafeFree32(VBuff);
		DCSafeFree(ParticleBuffer);

		Initialized=FALSE;
	}
}

// Ticks a particle. Returns false if the particle dies during this tick.
static inline BOOL TickParticle(Particle *P, float FrameTime)
{
	switch (P->Type)
	{
		case LIFETIME:
			P->Loc+=P->Vel*FrameTime;
			P->User1-=FrameTime;
			if (P->User1<0)
				return FALSE;
			break;
		case EXPAND_THEN_FADE:
			if (P->Radius >= P->User2)
			{
				// Fading.
				P->Intensity-=P->User3*FrameTime;
				if (P->Intensity<=0)
					return FALSE;
				P->Radius+=P->User1*FrameTime*0.0625f;
			}
			else
			{
				// Expanding.
				P->Radius+=P->User1*FrameTime;
			}
			break;
		case EXPAND_AND_FADE:
			P->Intensity-=P->User2*FrameTime;
			if (P->Intensity<=0)
				return FALSE;
			P->Radius+=P->User1*FrameTime;
			break;
		case EXPAND_FADE_DECELERATE:
		{
			// Fade.
			P->Intensity-=P->User2*FrameTime;
			if (P->Intensity < 0)
				return FALSE;
			// Expand.
			P->Radius+=P->User1*FrameTime;
			// Must keep time step reasonably small for deceleration.
			for (;FrameTime>0;FrameTime-=(1.0f/160.0f))
			{
				float DeltaTime=__min(FrameTime,(1.0f/160.0f));
				
				P->User3-=0.1f*P->User3*P->User3*DeltaTime;
				if (P->User3<0)
					P->User3=0;
				P->Loc+=P->Vel*(DeltaTime*P->User3);
			}
			break;
		}
		default:
			return FALSE;
	}
	return TRUE;
}

// Tick and render the particles.
void RenderParticles()
{
	gGraphics.MatrixIdentity();
	gGraphics.SetWorldMatrix();

	// Init state.
	gGraphics.DisableTransforms();
	gGraphics.ShadeModeFlat();
	gGraphics.EnableBlend();
	gGraphics.BlendMode(BLEND_ONE,BLEND_INVOTHERCOLOR);
	gGraphics.EnableDepthTest();
	gGraphics.DepthFunc(DFUNC_LESSEQUAL);
	gGraphics.DisableDepthWrite();
	gGraphics.CullDisable();
	gGraphics.TexAddressModeClamp();
	
	// Calculate projection matrix * view matrix.
	DCMatrix16 M;
	float *pM=(float *)&M;
	float *PM=(float *)&gRender.Frame.ProjectionMatrix;
	float *VM=(float *)&gRender.Frame.ViewMatrix;
	int i;
	for (i=0;i<4;i++)
		for (int j=0;j<16;j+=4)
			pM[i+j]=VM[j+0] * PM[i+0] +
					VM[j+1] * PM[i+4] +
					VM[j+2] * PM[i+8] +
					VM[j+3] * PM[i+12];

	// Loop through the lists.
	for (i=0;i<MAX_PARTICLE_TEXTURES;i++)
	{
		ParticleList *List=Lists+i;

		if (List->First)
		{
			// Something in the list so set texture and render particle(s).
			gGraphics.SetTexture(List->Texture);

			// Init to start of vertex buffer.
			int VBIndex=0;

			// Walk the particles.
			for (Particle *P=List->First,*Prev=NULL;P;)
			{
				// Tick this particle.
				BOOL Status;
				if (P->New)
				{
					P->New=FALSE;
					Status=TRUE;
				}
				else
				{
					Status=TickParticle(P,gRender.Frame.FrameTime);
				}

				// See if particle dead.
				if (!Status)
				{
					// Remove particle from list because it is dead.
					// Get this now because we are going to lose it.
					Particle *Next=P->Next;
					// Unlink.
					if (Prev==NULL)
						List->First=P->Next;
					else
						Prev->Next=P->Next;
					// Fixup last if necessary.
					if (List->Last==P)
						List->Last=Prev;
					// Add particle back to free list.
					P->Next=FirstFree;
					FirstFree=P;
					// Move to next.
					P=Next;

					continue;
				}

				// Flush vertex buffer if full.
				if (VBIndex >= VBUFF_SIZE)
				{
					gGraphics.Triangles(VBuff,VBIndex);
					VBIndex=0;
				}

				// Add triangle for this particle to vertex buffer..
				DCPlane Center;
				Center.X=M.m11*P->Loc.X + M.m21*P->Loc.Y + M.m31*P->Loc.Z + M.m41;
				Center.Y=M.m12*P->Loc.X + M.m22*P->Loc.Y + M.m32*P->Loc.Z + M.m42;
				Center.Z=M.m13*P->Loc.X + M.m23*P->Loc.Y + M.m33*P->Loc.Z + M.m43;
				Center.W=M.m14*P->Loc.X + M.m24*P->Loc.Y + M.m34*P->Loc.Z + M.m44;
				// Clip test against front clip plane.
				if (Center.Z > -Center.W)
				{
					// Caclulate InvW.
					Center.W=1.0f/Center.W;

					// Calculate radius.
					float Radius=gRender.Frame.ProjectionMatrix.m22*P->Radius*gGraphics.ScaleY3D*Center.W;

					// Adjust X and Y into screen coordinates and scale Z.
					Center.X=Center.X*Center.W*gGraphics.ScaleX3D + gGraphics.TransX3D;
					Center.Y=Center.Y*Center.W*gGraphics.ScaleY3D + gGraphics.TransY3D;
					Center.Z=Center.Z*Center.W;

					// Calculate color (based on color and intensity).
					int Intensity=(int)(P->Intensity*256.0f);
					DWORD Color=((((P->Color & 0x00FF0000)*Intensity)>>8)&0x00FF0000) |
								((((P->Color & 0x0000FF00)*Intensity)>>8)&0x0000FF00) |
								((((P->Color & 0x000000FF)*Intensity)>>8)&0x000000FF);

					VBuff[VBIndex].X=Center.X;
					VBuff[VBIndex].Y=Center.Y+VScale*Radius;
					VBuff[VBIndex].Z=Center.Z;
					VBuff[VBIndex].InvW=Center.W;
					VBuff[VBIndex].Color=Color;

					VBuff[VBIndex+1].X=Center.X+HScale*Radius;
					VBuff[VBIndex+1].Y=Center.Y-Radius;
					VBuff[VBIndex+1].Z=Center.Z;
					VBuff[VBIndex+1].InvW=Center.W;
					VBuff[VBIndex+1].Color=Color;

					VBuff[VBIndex+2].X=Center.X-HScale*Radius;
					VBuff[VBIndex+2].Y=Center.Y-Radius;
					VBuff[VBIndex+2].Z=Center.Z;
					VBuff[VBIndex+2].InvW=Center.W;
					VBuff[VBIndex+2].Color=Color;

					VBIndex+=3;
				}

				// Move to next particle.
				Prev=P;
				P=P->Next;
			}

			// Flush vertex buffer.
			if (VBIndex)
			{
				gGraphics.Triangles(VBuff,VBIndex);
				VBIndex=0;
			}
		}
	}

	// Restore state.
	gGraphics.EnableTransforms();
}

// Spawns a single particle.
void SpawnParticle(ParticleType Type, ParticleTexture Texture, 
				   DCVector *Loc, float Radius, DCVector *Vel,
				   float InitialTime, float Intensity, DWORD Color,
				   float User1, float User2, float User3)
{
	Particle *P;

	// Get the first particle on the free list.
	if (FirstFree)
	{
		P=FirstFree;
		FirstFree=P->Next;
	}
	else
	{
		// Hunt for oldest particle so we can steal it.
		QWORD LowestAllocNum=0;
		ParticleList *BestList;
		for (int i=0;i<MAX_PARTICLE_TEXTURES;i++)
		{
			if (Lists[i].First)
			{
				if (Lists[i].First->AllocNum < LowestAllocNum || LowestAllocNum==0)
				{
					BestList=Lists+i;
					LowestAllocNum=Lists[i].First->AllocNum;
				}
			}
		}

		DC_ASSERT(LowestAllocNum!=0);

		// Steal the particle.
		P=BestList->First;
		
		// Remove particle from the list we're stealing from.
		if (BestList->Last==P)
			BestList->Last=NULL;
		BestList->First=P->Next;
	}

	// Init the particle
	P->New=TRUE;
	P->Type=Type;
	P->Loc=*Loc;
	P->Radius=Radius;
	P->Vel=*Vel;
	P->Intensity=Intensity;
	P->Color=Color & 0x00FFFFFF;
	P->User1=User1;
	P->User2=User2;
	P->User3=User3;

	// Tick it for the initial amount of time.
	BOOL Status=TickParticle(P,InitialTime);

	// Make sure particle still alive.
	if (Status)
	{
		// Add it to the list for the texture.
		ParticleList *List=Lists + Texture;
		if (List->Last)
			List->Last->Next=P;
		if (!List->First)
			List->First=P;
		List->Last=P;
		P->Next=NULL;

		// Set alloc num.
		P->AllocNum=CurrentAllocNum;
		CurrentAllocNum++;
	}
	else
	{
		// Particle died straight away so put back on free list.
		P->Next=FirstFree;
		FirstFree=P;
	}
}

// Kills off all the particles.
void KillAllParticles(void)
{
	// Do this the easy way. Just add everything to the free list
	// and NULL the headers for the other lists.
	FirstFree=NULL;

	int i;
	Particle *P;
	for (i=0,P=ParticleBuffer;i<MAX_PARTICLES;i++,P++)
	{
		P->Next=FirstFree;
		FirstFree=P;
	}

	for (i=0;i<MAX_PARTICLE_TEXTURES;i++)
	{
		Lists[i].First=NULL;
		Lists[i].Last=NULL;
	}
}

float ParticleSmokeTrail(DCVector *StartPos, DCVector *EndPos, float StartRadius, float EndRatio,
						 float TimeLeftFromLast, float DeltaTime, float SpawnRate,
						 float Intensity, DWORD Color, int *LastCount)
{
	DCVector ZeroVel(0,0,0);
	DCVector DirVec=*EndPos-*StartPos;
	float InvDT=1.0f/DeltaTime;

#define TIME_RATE_RATIO 0.1f	

	// Figure out start time rate.
	float StartTimeRate=0.25f;
	for (int Tmp=0x01;Tmp<=EndRatio;Tmp=Tmp<<1)
		StartTimeRate*=1.0f/TIME_RATE_RATIO;

	float Time;
	for (Time=-TimeLeftFromLast+SpawnRate;Time<=DeltaTime;Time+=SpawnRate)
	{
		DCVector Loc=*StartPos+(DirVec*(Time*InvDT));

		// As clouds double in size, we only need half as many.
		float EndRadius=StartRadius;
		float TimeRate=StartTimeRate;
		for (int Ander=0x01;Ander<=EndRatio;Ander=Ander<<1)
		{
			if ((*LastCount & Ander))
				break;
			EndRadius*=2;
			TimeRate*=TIME_RATE_RATIO;
		}
		
		(*LastCount)++;

		// Add some randomness just like a real smoke trail.
		if (EndRadius>StartRadius)
			EndRadius*=0.75f + (float)FastRand()*(0.25f/(float)FAST_RAND_MAX);

		// Spawn the particle.
		SpawnParticle(EXPAND_THEN_FADE, (ParticleTexture)(SMOKE1 + FastRand()%10),
					  &Loc, StartRadius, &ZeroVel, DeltaTime-Time, Intensity, Color, 
					  StartRadius*(16/0.25f),EndRadius,TimeRate);
	}
	
	return __max(0,SpawnRate-(Time-DeltaTime));
}

void ParticleExplosion(DCVector *Center, float StartRadius, int NumParticles, 
					   float LowFadeRateValue, float HighFadeRateValue,
					   float Intensity, DWORD Color)
{
	// Figure out radius of particles.
	float ParticleRadius=(float)FastSqrt((2*4*DC_PI)*StartRadius*StartRadius/NumParticles);
	
	// Generate paticles over the surface of a sphere.
	for (int i=0;i<NumParticles;)
	{
		// Vector with random coordinates of unit length or less.
		DCVector V;
		V.X=FastRand()*(2.0f/(float)FAST_RAND_MAX)-1.0f;
		V.Y=FastRand()*(2.0f/(float)FAST_RAND_MAX)-1.0f;
		V.Z=FastRand()*(2.0f/(float)FAST_RAND_MAX)-1.0f;
		
		float Length=V.FastLength();
		// Reject anything outside the unit sphere which gives us an
		// even distribution.
		if (Length>1.0f)
			continue;

		DCVector SpawnPoint=*Center + (V*(StartRadius/*/Length*/));
		DCVector BaseVel=V*(1.0f/Length);

		// Spawn the particle.
		SpawnParticle(EXPAND_FADE_DECELERATE, (ParticleTexture)(SMOKE1 + FastRand()%10),
					  &SpawnPoint, ParticleRadius, &BaseVel, 0.0f, Intensity, Color,
					  // Expand rate. At most, particle will expand by 100%.
					  ParticleRadius*FastRand()*LowFadeRateValue*(1.0f/(float)FAST_RAND_MAX),
					  // Fade rate.
					  LowFadeRateValue+(HighFadeRateValue-LowFadeRateValue)*FastRand()*(1.0f/(float)FAST_RAND_MAX),
					  // Speed.
					  StartRadius*Length*10.0f);
//					  FastRand()*StartRadius*(10.0f/(float)FAST_RAND_MAX));

		// Move on to next particle.
		i++;
	}
}
