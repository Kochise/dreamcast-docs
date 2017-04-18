/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    RTerrain.cpp

Abstract:

	Terrain rendering.    

-------------------------------------------------------------------*/

// Appologies to the reader - the terms tangential and radial
// (and related variables containing "t" and "r") have been used incorrectly in this file.

#include "DC.h"
#include "DCWorld.h"
#include "DCGraphics.h"
#include "DCVis.h"
#include "DCRender.h"

// Must be at least 3. Less than 3 will cause the visibility routines to blow up.
#define NUM_RADIAL_TEXTURES 8
// Can be 1 or greater.
#define NUM_TANGENTIAL_TEXTURES 3

#define TANGENTIAL_STRETCH 1.4269f //1.5f

// Max MIP level used in rendering the terrain. (Polys, not texels).
#define MIP_MAX			 2

// The number of strips per texture must be a multiple of 2^(MIP_MAX+2).
// For MIP_MAP=2, this is 16.
#define LD_OBS_STRIPS_PER_TEX 16
#define LD_PL_STRIPS_PER_TEX 32
#define HD_OBS_STRIPS_PER_TEX 32
#define HD_PL_STRIPS_PER_TEX 64
// The strip length should be approximately STRIPS_PER_TEX*2*sqrt(3)/2
// (STRIPS_PER_TEX * 1.73) and rounded to the nearest even number.
#define LD_OBS_STRIP_LENGTH 28
#define LD_PL_STRIP_LENGTH 54
#define HD_OBS_STRIP_LENGTH 54
#define HD_PL_STRIP_LENGTH 110

#define MAX_STRIP_LENGTH HD_PL_STRIP_LENGTH

#define LD_TEXTURE_DIMENSIONS				128
#define HD_TEXTURE_DIMENSIONS				256

#define MAX_FRACTAL_OCTAVES					9

// So we have something to display while textures are being generated.
#define TEXGEN_SCREEN_IMAGE TEXT("IntroTG")

// In Intro.cpp.
void DisplaySplashBitmap(TCHAR *FileName,BOOL Front);

struct RingInfo
{
	BOOL MipBoundary;
	int StripsPerTex;
	int StripLength;
	int HalfStripLength;
	int StripVertexDensity;
	int RenderStripLength;
	WORD EvenStripIndices[MAX_STRIP_LENGTH+1];
	WORD OddStripIndices[MAX_STRIP_LENGTH+1];
};

struct TileInfo
{
	int StartStripDataIndex;
	HANDLE Texture;
	float StartAngle,EndAngle;
	float MinHeight,MaxHeight;
	// Bounding sphere.
	DCVector BoundingSphereCenter;
	float    BoundingSphereRadius;
	// Bounding corners. Made to pass directly into vis routines.
	DCPlane  BoundingCorners[8];
};

// This is the ratio of the outer edge of a tile to the inner edge.
static float TileEdgeRadiusRatio;
// This is dependent on the detail level.
static int TextureDimensions;
// Used by the collision helper code.
static float DeltaAngleForCollision;
// Coefficents for functions used to scale the world height.
static float ia,ib,ic,id;
static float oa,ob,oc;
// Coefficents for functions used to scale the danger height.
static float dia,dib,dic,did;
static float doa,dob,doc;
// Precalulated rotation values for fractal function.
static float FractalSin[MAX_FRACTAL_OCTAVES];
static float FractalCos[MAX_FRACTAL_OCTAVES];
// Texture handles.
static HANDLE TexHandles[NUM_TANGENTIAL_TEXTURES][NUM_RADIAL_TEXTURES];
// Player view variables.
static DCVertex *PlVertexBuffer;
static DCVertex **PlStripData;
static RingInfo PlRings[NUM_TANGENTIAL_TEXTURES];
static TileInfo PlTiles[NUM_TANGENTIAL_TEXTURES][NUM_RADIAL_TEXTURES];
// Observer view variables.
static DCVertex *ObsVertexBuffer;
static DCVertex **ObsStripData;
static RingInfo ObsRings[NUM_TANGENTIAL_TEXTURES];
static TileInfo ObsTiles[NUM_TANGENTIAL_TEXTURES][NUM_RADIAL_TEXTURES];
// Temp buffer used to store vertices.
static DCVertex *V;
// So we know to set the vertex color values.
static BOOL NeedToSetColorValues;

// Evaluates the fractal based on the input parameters.
float EvaluateFractal(float U, float V, float H, float Period, float Spacing)
{
	// Adjust U and V by the period.
	float Inv=1.0f/Period;
	U*=Inv;V*=Inv;

	// Do loop, accumulating noise values.
	// Spacing*3 represents our smallest full weighted period.
	int i;
	float Noise,Scale;
	for (i=0,Spacing*=3,Noise=0,Scale=1.0f;
		 i<MAX_FRACTAL_OCTAVES && Period>=Spacing;
		 i++,Period*=0.5f,Scale*=H,U*=2,V*=2)
	{
		float Sin=FractalSin[i],Cos=FractalCos[i];
		Noise+=Scale*GNoise2(U*Cos + V*Sin, V*Cos - U*Sin);
	}
	// Add in a final weighted noise value.
	if (Period>=Spacing*0.5f && i<MAX_FRACTAL_OCTAVES)
	{
		float Weight=2*Period/Spacing-1;
		float Sin=FractalSin[i],Cos=FractalCos[i];
		Noise+=Weight*Scale*GNoise2(U*Cos + V*Sin, V*Cos - U*Sin);
	}

	return Noise;
}

// Evaluates the terrain height at a point in the world.
// Spacing is the approximate point spacing between calls the this
// function. It is use to remove high frequency data that would
// otherwise cause aliasing.
float EvaluateTerrainHeight(float X, float Z, float Spacing)
{
	// Calculate height scale.
	float R=(float)sqrt(X*X + Z*Z);
	float Height;

	// Calculate maximum height level based on R.
	if (R < DCW_TERRAIN_LOW_OUTER_RADIUS)
		// Low.
		Height=DCW_TERRAIN_LOW_HEIGHT;
	else if (R < DCW_TERRAIN_HIGH_INNER_RADIUS)
		// Transition from low to high.
		Height=ia*R*R*R + ib*R*R + ic*R + id;
	else if (R < DCW_TERRAIN_HIGH_OUTER_RADIUS)
		// High region of terrain.
		Height=DCW_TERRAIN_HIGH_HEIGHT;
	else
		// Transition from high to edge of world (which has zero height).
		Height=oa*R*R + ob*R + oc;

	// Modulate maxumim height by fractal noise.
	// We add a big offset to X and Z so different pieces of of the noise lattice
	// are used in each octave.
	float Fractal=0.5f + 0.5f*EvaluateFractal(X+4327.0f,Z-(4327.0f*2),
											  0.33333f,DCW_TERRAIN_PERIOD,Spacing);

	return Height*Fractal;
}

// Evaluates the terrain height exactly.
float GetTerrainHeight(float X, float Z)
{
	// Evaluate height via fractal.
	return EvaluateTerrainHeight(X,Z,(float)sqrt(X*X + Z*Z)*DeltaAngleForCollision);
}

// Evaluates danger height.
float GetDangerHeight(float X, float Z)
{
	float R=(float)sqrt(X*X + Z*Z);

	// Calculate height level based on R.
	if (R < DCW_DANGER_LOW_OUTER_RADIUS)
		// Low
		return DCW_DANGER_LOW_HEIGHT;
	else if (R < DCW_DANGER_HIGH_INNER_RADIUS)
		// Transition from low to high.
		return dia*R*R*R + dib*R*R + dic*R + did;
	else if (R < DCW_DANGER_HIGH_OUTER_RADIUS)
		// High region of DANGER.
		return DCW_DANGER_HIGH_HEIGHT;
	else
		// Transition from high to edge of world (which has zero height).
		return doa*R*R + dob*R + doc;
}

// Evaluates danger angle (angle necessary to clear terrain).
float GetDangerAngle(float X, float Z, float DirX, float DirZ)
{
	float R=FastSqrt(X*X + Z*Z);
	float Slope;

	// Calculate based on R.
	if (R < DCW_DANGER_LOW_OUTER_RADIUS)
		// Low.
		return 0;
	else if (R < DCW_DANGER_HIGH_INNER_RADIUS)
		// Transition from low to high.
		Slope=3*dia*R*R + 2*dib*R + dic;
	else if (R < DCW_DANGER_HIGH_OUTER_RADIUS)
		// High region of DANGER.
		return 0;
	else
		// Transition from high to edge of world (which has zero height).
		Slope=2*doa*R + dob;

	// Adjust slope based on direction.
	float Tmp1=1.0f/R;
	X*=Tmp1; Z*=Tmp1;
	float Tmp2=1.0f/FastSqrt(DirX*DirX + DirZ*DirZ);
	DirX*=Tmp2; DirZ*=Tmp2;
	Slope*=X*DirX + Z*DirZ; // Dot product, gives scaling value in rangle 1 to -1.

	// Convert slope to angle.
	return (float)atan(Slope);
}

// Evaluates the terrain color at a point in the world.
DWORD EvaluateTerrainColor(float X, float Z, float Spacing)
{
	// Calculate lighting.
	// Evalulate 5 terrain height values;
	DCVector V(X,EvaluateTerrainHeight(X,Z,Spacing),Z);
	DCVector V1(X,EvaluateTerrainHeight(X,Z+Spacing,Spacing),Z+Spacing);
	DCVector V2(X+Spacing,EvaluateTerrainHeight(X+Spacing,Z,Spacing),Z);
	DCVector V3(X,EvaluateTerrainHeight(X,Z-Spacing,Spacing),Z-Spacing);
	DCVector V4(X-Spacing,EvaluateTerrainHeight(X-Spacing,Z,Spacing),Z);
	// Calculate surface vectors in 4 different directions.
	V1-=V; V2-=V; V3-=V; V4-=V;
	// Calculate normal by taking cross product and accumulating results.
	DCVector TmpV;
	V=V1^V2;
	V.Normalize();
	TmpV=V2^V3;
	TmpV.Normalize();
	V+=TmpV;
	TmpV=V3^V4;
	TmpV.Normalize();
	V+=TmpV;
	TmpV=V4^V1;
	TmpV.Normalize();
	V+=TmpV;
	// Normalize final result.
	V.Normalize();
	// Get sun vector and normalize.
	DCVector Sun=DCW_SUN_DIR;
	Sun.Normalize();
	// Calculate light intensity by taking dot product.
	float I=V|Sun;
	// Light level must be positive.
	if (I < 0)
		I=0;
	// Scale intensity so full itensity plus ambient=1.
	I*=(1.0f-DCW_AMBIENT_INTENSITY);
	// Add ambient light intensity.
	I+=DCW_AMBIENT_INTENSITY;
	// Generate a vector from this intensity.
	DCVector LightColor(I,I,I);

	// Calculate terrain color.

	// Figure out terrain type(s).
	float DirtScale=0.0f,GrassScale=0.0f,MountainScale=0.0f;

	// We do 5x5 supersample to get smooth transitions between terrain types.
#if 1
	float AddAmount=1.0f/25.0f;
	for (float U=-Spacing;U<=Spacing;U+=Spacing/2)
	{
		for (float V=-Spacing;V<=Spacing;V+=Spacing/2)
		{
#else
	float AddAmount=1.0f;	
	float U=0;
	{
		float V=0;
		{
#endif
			float TerrainHeight=EvaluateTerrainHeight(X+U,Z+V,Spacing);
			
			if (TerrainHeight<=DCW_COLOR_DIRT_HIGH_LEVEL)
			{
				// Dirt.
				DirtScale+=AddAmount;
			}
			else if (TerrainHeight<DCW_COLOR_GRASS_LOW_LEVEL)
			{
				// Transition from dirt to grass.
				float Noise=EvaluateFractal(X+U,Z+V,0.5f,DCW_COLOR_DIRT_GRASS_TRANSITION_PERIOD,Spacing)*0.5f+0.5f;
				float Threshold=(TerrainHeight-DCW_COLOR_DIRT_HIGH_LEVEL)/(DCW_COLOR_GRASS_LOW_LEVEL-DCW_COLOR_DIRT_HIGH_LEVEL);
				if (Noise<Threshold)
					GrassScale+=AddAmount;
				else
					DirtScale+=AddAmount;
			}
			else if (TerrainHeight<=DCW_COLOR_GRASS_HIGH_LEVEL)
			{
				// Grass.
				GrassScale+=AddAmount;
			}
			else if (TerrainHeight<DCW_COLOR_MOUNTAIN_LOW_LEVEL)
			{
				// Transition from grass to mountain.
				float Noise=EvaluateFractal(X+U,Z+V,0.5f,DCW_COLOR_GRASS_MOUNTAIN_TRANSITION_PERIOD,Spacing)*0.5f+0.5f;
				float Threshold=(TerrainHeight-DCW_COLOR_GRASS_HIGH_LEVEL)/(DCW_COLOR_MOUNTAIN_LOW_LEVEL-DCW_COLOR_GRASS_HIGH_LEVEL);
				if (Noise<Threshold)
					MountainScale+=AddAmount;
				else
					GrassScale+=AddAmount;
			}
			else
			{
				// Mountain.
				MountainScale+=AddAmount;
			}
		}
	}

	// Generate color based on terrain type.
	DCVector TerrainColor=DCVector(0,0,0);

	// Add in dirt portion.
	if (DirtScale)
	{
		float Alpha=EvaluateFractal(X,Z,0.5f,DCW_COLOR_DIRT_PERIOD,Spacing)*0.5f+0.5f;
		Alpha=__max(__min(Alpha,1.0f),0.0f);
		TerrainColor+=((DCW_COLOR_DIRT_A*Alpha) + (DCW_COLOR_DIRT_B*(1-Alpha)))*DirtScale;
	}
	
	// Add in grass portion
	if (GrassScale)
	{
		float Alpha=EvaluateFractal(X,Z,0.5f,DCW_COLOR_GRASS_PERIOD,Spacing)*0.5f+0.5f;
		Alpha=__max(__min(Alpha,1.0f),0.0f);
		TerrainColor+=((DCW_COLOR_GRASS_A*Alpha) + (DCW_COLOR_GRASS_B*(1-Alpha)))*GrassScale;
	}

	// Add in mountain proportions.
	if (MountainScale)
	{
		float Alpha=EvaluateFractal(X,Z,0.5f,DCW_COLOR_MOUNTAIN_PERIOD,Spacing)*0.5f+0.5f;
		Alpha=Gain(Alpha,0.9f);
		Alpha=__max(__min(Alpha,1.0f),0.0f);
		TerrainColor+=((DCW_COLOR_MOUNTAIN_A*Alpha) + (DCW_COLOR_MOUNTAIN_B*(1-Alpha)))*MountainScale;
	}

	// Modulate terrain color with light color.
	TerrainColor*=LightColor;
	
	// Clamp color.
	TerrainColor.ClampMin(0.0f);
	TerrainColor.ClampMax(1.0f);

	// Create packed integer return value.
	int R=(int)(TerrainColor.X*255);
	int G=(int)(TerrainColor.Y*255);
	int B=(int)(TerrainColor.Z*255);
	return 0xFF000000 | (R << 16) | (G << 8) | B;
}

// Loads a terrain texture off disk. If it doesn't exist, this function will generate it.
static BOOL CreateTexture(HANDLE TextureID, int *X, int *Y, DWORD *Flags, DWORD **Data)
{
	// A new texture will mean the vertex color values will need to updated
	// Because we're using MaxColor.
	NeedToSetColorValues=TRUE;
	
	// Figure out which tile we have.
	int r=((int)TextureID)&0xFFFF;
	int t=((int)TextureID)>>16;
	TileInfo *PlTile=&PlTiles[t][r];
	TileInfo *ObsTile=&ObsTiles[t][r];

	// Figure out texture name.
	TCHAR Name[0x100];
	wsprintf(Name,TEXT("Terrain\\Ter%c%02i%02i"),(gHighTextureDetail) ? (TCHAR)'H' : (TCHAR)'L',t,r);
	
	// Attempt to load image from disk.
	if (!ReadImageFileMipmapped(Name,X,Y,Flags,Data))
	{
		// No image so we have to create one.
		// Change splash screen if we haven't already done so
		// so user doesn't think system has crashed.
		static BOOL ChangedSplash=FALSE;
		if (!ChangedSplash)
		{
			DisplaySplashBitmap(TEXGEN_SCREEN_IMAGE,TRUE);
			ChangedSplash=TRUE;
		}

		// Allocate space.
		DWORD *D=(DWORD *)DCMalloc(TextureDimensions*TextureDimensions*sizeof(DWORD));
		if (!D)
			return FALSE;

		// Generate radius values for the texture.
		float TexelRadiusValues[HD_TEXTURE_DIMENSIONS];
		float TexelRadiusRatio=(float)exp(log(TileEdgeRadiusRatio)/(float)(TextureDimensions-1));
		for (int i=0;i<TextureDimensions;i++)
			TexelRadiusValues[i]=
				(float)pow(TexelRadiusRatio,(float)(i+((TextureDimensions-1)*t))) * DCW_TERRAIN_INNER_RADIUS;

		// Loop through each texel in the texture.
		float AngleStep=(PlTile->EndAngle - PlTile->StartAngle)/(float)(TextureDimensions-1);
		float Angle=PlTile->StartAngle;
		for (int u=0;u<TextureDimensions;u++,Angle+=AngleStep)
		{
			// Figure out 2D vector to scale radius values by.
			float VX=(float)sin(Angle);
			float VZ=(float)cos(Angle);

			for (int v=0;v<TextureDimensions;v++)
			{
				float R=TexelRadiusValues[v];
				D[v*TextureDimensions + u]=EvaluateTerrainColor(R*VX,R*VZ,AngleStep*R);
			}
		}
		
		// Save newly created file so we don't have to create it again.
		WriteImageFile(Name,TextureDimensions,TextureDimensions,FALSE,D);

		// Set return data.
		*X=*Y=TextureDimensions;
		*Flags=TFLAG_MIPMAPPED;
		*Data=D;
	}
	return TRUE;
}

void FitLine(float h1, float r1, float h2, float r2,
			 float &a, float &b)
{
	a=(h2-h1)/(r2-r1);
	b=h1-a*r1;
}

// Fits a quadratic function to the points specified.
// The slope at the first points is zero.
void FitQuadraticFunction(float h1, float r1, float h2, float r2,
						  float &a, float &b, float &c)
{
	a=(h2-h1)/(r2*r2 - 2*r1*r2 + r1*r1);
	b=-2*r1*a;
	c=h1+r1*r1*a;
}


// Fits a cubic function to the points specified.
// The slope at the two points is zero.
void FitCubicFunction(float h1, float r1, float h2, float r2,
					  float &a, float &b, float &c, float &d)
{
	float f=3*(r2*r2-r1*r1)/(2*(r1-r2));
	float g=-(3*r1*r1 + 2*f*r1);
	a=(h2-h1)/(r2*r2*r2 + f*r2*r2 + g*r2 - r1*r1*r1 - f*r1*r1 - g*r1);
	b=f*a;
	c=g*a;
	d=h1 - a*r1*r1*r1 - b*r1*r1 - c*r1;
}


static BOOL CalculateTerrain(int BaseStripsPerTex, int BaseStripLength,
							 DCVertex* &VertexBuffer,
							 DCVertex** &StripData,
							 RingInfo *Rings,
							 TileInfo Tiles[][NUM_RADIAL_TEXTURES])
{
	// Init ring data and figure out size of data structures that we need to allocate.
	int i,MipLevel;
	int VertexBufferSize=0;
	int StripDataBufferSize=0;
	for (i=0,MipLevel=MIP_MAX;i<NUM_TANGENTIAL_TEXTURES;i++)
	{
		Rings[i].MipBoundary=(MipLevel!=0);
		int ExtraVerts=(Rings[i].MipBoundary) ? 4 : 2;
		Rings[i].StripsPerTex=BaseStripsPerTex >> MipLevel;
		Rings[i].StripLength=((((BaseStripLength-ExtraVerts) >> MipLevel) + 0x01) & ~0x01) + ExtraVerts;
		Rings[i].HalfStripLength=Rings[i].StripLength/2;
		Rings[i].StripVertexDensity=Rings[i].StripLength-((Rings[i].MipBoundary) ? 5 : 3);
		Rings[i].RenderStripLength=(Rings[i].MipBoundary) ? Rings[i].StripLength-1 : Rings[i].StripLength+1;
		
		if (MipLevel)
		{
			MipLevel--;
		}

		// Generate strip indices.
		if (Rings[i].MipBoundary)
		{
			// Bit different for mip boundary since we have to deal with matchup vertices.
			for (int j=0;j<Rings[i].HalfStripLength-1;j++)
			{
				Rings[i].EvenStripIndices[j*2]=j;
				Rings[i].EvenStripIndices[j*2+1]=j+Rings[i].HalfStripLength;
				Rings[i].OddStripIndices[j*2]=j+Rings[i].HalfStripLength;
				Rings[i].OddStripIndices[j*2+1]=j;
			}
			// Set vertex to matchup with next ring.
			Rings[i].EvenStripIndices[Rings[i].StripLength-2]=
			Rings[i].OddStripIndices[Rings[i].StripLength-2]=
				Rings[i].StripLength-1;
		}
		else
		{
			for (int j=0;j<Rings[i].HalfStripLength;j++)
			{
				Rings[i].EvenStripIndices[j*2]=j;
				Rings[i].EvenStripIndices[j*2+1]=j+Rings[i].HalfStripLength;
				Rings[i].OddStripIndices[j*2]=j+Rings[i].HalfStripLength;
				Rings[i].OddStripIndices[j*2+1]=j;
			}
			// We need to pad the strip out by one more triangle so it is of an odd number of tris. 
			// Otherwise reversing it has no effect on winding order.
			Rings[i].EvenStripIndices[Rings[i].StripLength]=Rings[i].EvenStripIndices[Rings[i].StripLength-2];
			Rings[i].OddStripIndices[Rings[i].StripLength]=Rings[i].OddStripIndices[Rings[i].StripLength-2];
		}
		// Reverse odd strip direction so back face culling will work correctly.
		for (int j=0;j<Rings[i].RenderStripLength/2;j++)
		{
			WORD Tmp=Rings[i].OddStripIndices[j];
			Rings[i].OddStripIndices[j]=Rings[i].OddStripIndices[Rings[i].RenderStripLength-1-j];
			Rings[i].OddStripIndices[Rings[i].RenderStripLength-1-j]=Tmp;
		}

		// Add space necessary to buffer sizes.
		VertexBufferSize+=Rings[i].HalfStripLength*(Rings[i].StripsPerTex+1)*NUM_RADIAL_TEXTURES;
		StripDataBufferSize+=(Rings[i].StripsPerTex+1)*NUM_RADIAL_TEXTURES;
	}

	// Allocate space.
	VertexBuffer=(DCVertex *)DCMalloc(sizeof(DCVertex)*VertexBufferSize);
	StripData=(DCVertex **)DCMalloc(sizeof(DCVertex *)*StripDataBufferSize);
	if (!VertexBuffer || !StripData)
	{
		SetErrorMessage(IDS_ERROR_OUTOFMEMORY);
		return FALSE;
	}

	// Generate data for each tile.
	int CurrentVertexIndex=0;
	int CurrentStripDataIndex=0;
	for (int t=NUM_TANGENTIAL_TEXTURES-1;t>=0;t--)
	{
		// Ratio of the radius of a strip vertex to the previous.
		float StripVertexRadiusRatio=(float)exp(log(TileEdgeRadiusRatio)/(float)Rings[t].StripVertexDensity);
		// Delta-angle between each strip edge.
		float AngleStep=DC_PI*2/(float)(Rings[t].StripsPerTex*NUM_RADIAL_TEXTURES);
		float TexUStep=(float)(TextureDimensions-1)/(float)(Rings[t].StripsPerTex*TextureDimensions);
		float TexVStep=(float)(TextureDimensions-1)/(float)(Rings[t].StripVertexDensity*TextureDimensions);

		// Generate radius and V values for strip vertices.
		float StripRadiusValues[MAX_STRIP_LENGTH];
		float VValues[MAX_STRIP_LENGTH];
		float TexV=0.5f/(float)TextureDimensions;
		for (int i=0;i<Rings[t].StripLength-2;i++,TexV+=TexVStep)
		{
			StripRadiusValues[i+1]=
				(float)pow(StripVertexRadiusRatio,(float)(i+(Rings[t].StripVertexDensity*t))) * DCW_TERRAIN_INNER_RADIUS;
			VValues[i+1]=TexV;
		}
		// The first and last vertices get duplicated so the strip 
		// starts and ends cleanly.
		StripRadiusValues[0]=StripRadiusValues[1];
		StripRadiusValues[Rings[t].StripLength-1]=StripRadiusValues[Rings[t].StripLength-2];
		VValues[0]=VValues[1];
		VValues[Rings[t].StripLength-1]=VValues[Rings[t].StripLength-2];

		// Need to keep this index for the end of the ring.
		int FirstStripDataIndex=CurrentStripDataIndex;

		// Init angle to 0.
		float Angle=0;
		
		for (int r=0;r<NUM_RADIAL_TEXTURES;r++)
		{
			// Init min/max heights to really large/small values.
			float MinHeight=DCW_TERRAIN_HIGH_HEIGHT*DCW_TERRAIN_HIGH_HEIGHT;
			float MaxHeight=-DCW_TERRAIN_HIGH_HEIGHT*DCW_TERRAIN_HIGH_HEIGHT;

			// Set texture.		
			Tiles[t][r].Texture=TexHandles[t][r];
			
			// Set start strip data index.
			Tiles[t][r].StartStripDataIndex=CurrentStripDataIndex;

			// Set start angle.
			Tiles[t][r].StartAngle=Angle;

			float TexU=0.5f/TextureDimensions;
			for (int sr=0;sr<=Rings[t].StripsPerTex;sr++,TexU+=TexUStep)
			{
				// Set pointer to vertex data for this strip
				StripData[CurrentStripDataIndex++]=VertexBuffer+CurrentVertexIndex;
				DC_ASSERT(CurrentStripDataIndex<=StripDataBufferSize);

				// Figure out 2D vector to scale radius values by.
				float VX=(float)sin(Angle);
				float VZ=(float)cos(Angle);

				// Handle wraparound case. If we don't do this we get an imperfect join
				// at angles 0 and 360.
				if (fabs(Angle-DC_PI*2)<AngleStep*0.1f)
				{
					VX=(float)sin(0.0f);
					VZ=(float)cos(0.0f);
				}
				
				// Generate vertex values and V texture coordinates.
				for (int tr=0;tr<Rings[t].HalfStripLength;tr++)
				{
					DCVertex *V=VertexBuffer+CurrentVertexIndex;
					int Index=tr*2+(sr&0x01);
					float R=StripRadiusValues[Index];
					V->X=VX*R;
					V->Z=VZ*R;
					V->Y= EvaluateTerrainHeight(V->X,
												V->Z,
												R*AngleStep);
					V->U=TexU;
					V->V=VValues[Index];
		
					// Update min/max height.
					if (V->Y < MinHeight)
						MinHeight=V->Y;
					if (V->Y > MaxHeight)
						MaxHeight=V->Y;

					// Move to next vertex.
					CurrentVertexIndex++;
					DC_ASSERT(CurrentVertexIndex<=VertexBufferSize);
				}
				// If this isn't the outer ring, copy the start vertex value(s) from
				// the outer ring to the end vertex value(s) of this ring to ensure
				// we'll have no cracks.
				if (t<NUM_TANGENTIAL_TEXTURES-1)
				{
					if (Rings[t].MipBoundary)
					{
						float TmpV=	VValues[Rings[t].StripLength-4];

						// Bit different at mip boundary since we use
						// an extra vertex to get a proper matchup.
						// Copy end vertex.
						DCVertex *SV=StripData[Tiles[t+1][r].StartStripDataIndex+sr*2];
						DCVertex *DV=StripData[Tiles[t][r].StartStripDataIndex+sr]+Rings[t].HalfStripLength-2;
						DV->X=SV->X; DV->Y=SV->Y; DV->Z=SV->Z;
						DV->V=TmpV;
						// Copy matchup vertex.
						if (sr)
						{
							DCVertex *SV=StripData[Tiles[t+1][r].StartStripDataIndex+sr*2-1];
							DCVertex *DV=StripData[Tiles[t][r].StartStripDataIndex+sr]+Rings[t].HalfStripLength-1;
							DV->X=SV->X; DV->Y=SV->Y; DV->Z=SV->Z;
							DV->U=SV->U;
							DV->V=TmpV;
						}
					}
					else
					{
						DCVertex *SV=StripData[Tiles[t+1][r].StartStripDataIndex+sr];
						DCVertex *DV=StripData[Tiles[t][r].StartStripDataIndex+sr]+Rings[t].HalfStripLength-1;
						DV->X=SV->X; DV->Y=SV->Y; DV->Z=SV->Z;
					}
				}
#if 1
				// For the inner ring, bring first vertex in the strip to the center of the world.
				if (t==0 && (sr&0x01)==0)
				{
					DCVertex *V=StripData[CurrentStripDataIndex-1];
					
					// Set coordinates to center of world.
					V->X=V->Z=0;
					V->Y=DCW_TERRAIN_LOW_HEIGHT*0.5f;

					// Fixup the V value.
					float Scale=StripRadiusValues[2]/(StripRadiusValues[2]-StripRadiusValues[0]);
					V->V=VValues[2] - Scale*(VValues[2]-VValues[0]);
				}
#endif
				// Don't increment the angle on the last piece of strip data since the
				// same angle needs to be used for the next tile.
				if (sr!=Rings[t].StripsPerTex)
					Angle+=AngleStep;
			}
			
			// Set end angle.
			Tiles[t][r].EndAngle=Angle;
			
			// Save min/max height.
			Tiles[t][r].MinHeight=MinHeight;
			Tiles[t][r].MaxHeight=MaxHeight;

			// Figure out bounding sphere.
			Tiles[t][r].BoundingSphereCenter.Y=
				(Tiles[t][r].MinHeight + Tiles[t][r].MaxHeight)/2;
			// To get X and Z values, first figure out the bounding circle center for a tile
			// centered on the Z axis (so X coordinate of center is 0).
			float SinA=(float)sin(DC_PI/(float)NUM_RADIAL_TEXTURES);
			float CosA=(float)cos(DC_PI/(float)NUM_RADIAL_TEXTURES);
			float R1=(float)pow(TileEdgeRadiusRatio,(float)t)*DCW_TERRAIN_INNER_RADIUS;
			float R2=(float)pow(TileEdgeRadiusRatio,(float)(t+1))*DCW_TERRAIN_INNER_RADIUS;
			float Z1=R1*CosA, X1=R1*SinA, Z2=R2*CosA, X2=R2*SinA;
			float ZC=0.5f*(X2*X2 - X1*X1 + Z2*Z2 - Z1*Z1)/(Z2-Z1);
			// Rotate Z coordinate so we get X and Z coordinate for our tile.
			float TileAngle=0.5f*(Tiles[t][r].EndAngle + Tiles[t][r].StartAngle);
			Tiles[t][r].BoundingSphereCenter.X=ZC*(float)sin(TileAngle);
			Tiles[t][r].BoundingSphereCenter.Z=ZC*(float)cos(TileAngle);
			// Now figure out radius of sphere.
			float RX=X1;
			float RY=(Tiles[t][r].MaxHeight - Tiles[t][r].MaxHeight)/2;
			float RZ=Z1-ZC;
			Tiles[t][r].BoundingSphereRadius=(float)sqrt(RX*RX + RY*RY + RZ*RZ);

			// Figure out bounding corners.
			// Extend R2 to enclose curvature of tile.
			R2=R2/CosA;
			// Figure out X/Z coordinates for top corners.
			// They go in the order near-left, near-right, far-left, far-right.
			Tiles[t][r].BoundingCorners[0].X=R1*(float)sin(Tiles[t][r].StartAngle);
			Tiles[t][r].BoundingCorners[0].Z=R1*(float)cos(Tiles[t][r].StartAngle);
			Tiles[t][r].BoundingCorners[1].X=R1*(float)sin(Tiles[t][r].EndAngle);
			Tiles[t][r].BoundingCorners[1].Z=R1*(float)cos(Tiles[t][r].EndAngle);
			Tiles[t][r].BoundingCorners[2].X=R2*(float)sin(Tiles[t][r].StartAngle);
			Tiles[t][r].BoundingCorners[2].Z=R2*(float)cos(Tiles[t][r].StartAngle);
			Tiles[t][r].BoundingCorners[3].X=R2*(float)sin(Tiles[t][r].EndAngle);
			Tiles[t][r].BoundingCorners[3].Z=R2*(float)cos(Tiles[t][r].EndAngle);
			// Copy values to bottom corners.
			Tiles[t][r].BoundingCorners[4].X=Tiles[t][r].BoundingCorners[0].X;
			Tiles[t][r].BoundingCorners[4].Z=Tiles[t][r].BoundingCorners[0].Z;
			Tiles[t][r].BoundingCorners[5].X=Tiles[t][r].BoundingCorners[1].X;
			Tiles[t][r].BoundingCorners[5].Z=Tiles[t][r].BoundingCorners[1].Z;
			Tiles[t][r].BoundingCorners[6].X=Tiles[t][r].BoundingCorners[2].X;
			Tiles[t][r].BoundingCorners[6].Z=Tiles[t][r].BoundingCorners[2].Z;
			Tiles[t][r].BoundingCorners[7].X=Tiles[t][r].BoundingCorners[3].X;
			Tiles[t][r].BoundingCorners[7].Z=Tiles[t][r].BoundingCorners[3].Z;
			// Set y values.
			Tiles[t][r].BoundingCorners[0].Y=Tiles[t][r].BoundingCorners[1].Y=
				Tiles[t][r].BoundingCorners[2].Y=Tiles[t][r].BoundingCorners[3].Y=
				Tiles[t][r].MinHeight;
			Tiles[t][r].BoundingCorners[4].Y=Tiles[t][r].BoundingCorners[5].Y=
				Tiles[t][r].BoundingCorners[6].Y=Tiles[t][r].BoundingCorners[7].Y=
				Tiles[t][r].MaxHeight;
			// Set w values.
			Tiles[t][r].BoundingCorners[0].W=Tiles[t][r].BoundingCorners[1].W=
				Tiles[t][r].BoundingCorners[2].W=Tiles[t][r].BoundingCorners[3].W=
				Tiles[t][r].BoundingCorners[4].W=Tiles[t][r].BoundingCorners[5].W=
				Tiles[t][r].BoundingCorners[6].W=Tiles[t][r].BoundingCorners[7].W=1.0f;
		}
	}
	
	return TRUE;
}

// Initializes the terrain.
BOOL InitTerrain(void)
{
	int PlStripsPerTex,ObsStripsPerTex;
	int PlStripLength,ObsStripLength;

	// Init variables dependent on detail level.
	if (gHighDetail)
	{
#ifdef DREAMCAST // On Dreamcast high detail player but low detail observer works best
				 // since mesh rendering performance isn't so good.
		ObsStripsPerTex=LD_OBS_STRIPS_PER_TEX;
		ObsStripLength=LD_OBS_STRIP_LENGTH;
#else
		ObsStripsPerTex=HD_OBS_STRIPS_PER_TEX;
		ObsStripLength=HD_OBS_STRIP_LENGTH;
#endif
		PlStripsPerTex=HD_PL_STRIPS_PER_TEX;
		PlStripLength=HD_PL_STRIP_LENGTH;
	}
	else
	{
		ObsStripsPerTex=LD_OBS_STRIPS_PER_TEX;
		ObsStripLength=LD_OBS_STRIP_LENGTH;
		PlStripsPerTex=LD_PL_STRIPS_PER_TEX;
		PlStripLength=LD_PL_STRIP_LENGTH;
	}
	if (gHighTextureDetail)
		TextureDimensions=HD_TEXTURE_DIMENSIONS;
	else
		TextureDimensions=LD_TEXTURE_DIMENSIONS;

	DeltaAngleForCollision=DC_PI*2/(float)(ObsStripsPerTex*NUM_RADIAL_TEXTURES);

	// Init ratio of outer tile radius to inner tile radius.
	float LargeConst=1000; // Ideally we would like this value to be infinity.
	TileEdgeRadiusRatio=(float)pow(1+(2*DC_PI)/(NUM_RADIAL_TEXTURES*LargeConst),LargeConst*TANGENTIAL_STRETCH);

	// Init coefficients for the polynomial functions we use to scale
	// the world height.
	// This one is a cubic function for the transition from low to
	// high ground.
	FitCubicFunction(DCW_TERRAIN_LOW_HEIGHT,DCW_TERRAIN_LOW_OUTER_RADIUS,
					 DCW_TERRAIN_HIGH_HEIGHT,DCW_TERRAIN_HIGH_INNER_RADIUS,
					 ia,ib,ic,id);
	// This one is a squared function for the transition from high
	// to zero height at the outer edge of the world.
	FitQuadraticFunction(DCW_TERRAIN_HIGH_HEIGHT,DCW_TERRAIN_HIGH_OUTER_RADIUS,
						 0,DCW_TERRAIN_OUTER_RADIUS,
						 oa,ob,oc);

	// Also have polynomial functions to scale danger height.
	FitCubicFunction(DCW_DANGER_LOW_HEIGHT,DCW_DANGER_LOW_OUTER_RADIUS,
					 DCW_DANGER_HIGH_HEIGHT,DCW_DANGER_HIGH_INNER_RADIUS,
					 dia,dib,dic,did);
	FitQuadraticFunction(DCW_DANGER_HIGH_HEIGHT,DCW_DANGER_HIGH_OUTER_RADIUS,
						 0,DCW_DANGER_OUTER_RADIUS,
						 doa,dob,doc);

	// Create rotation values for fractal function.
	SeedGoodRand(0x00000001);
	for (int i=0;i<MAX_FRACTAL_OCTAVES;i++)
	{
		float Angle=(float)GoodRand()*DC_PI/(float)GOOD_RAND_MAX;
		FractalSin[i]=(float)sin(Angle);
		FractalCos[i]=(float)cos(Angle);
	}

	// Add textures.
	for (int t=0;t<NUM_TANGENTIAL_TEXTURES;t++)
		for (int r=0;r<NUM_RADIAL_TEXTURES;r++)
			TexHandles[t][r]=gGraphics.AddTexture(CreateTexture,(HANDLE)(r | (t<<16)),FALSE,TRUE);

	// Calculate player view terrain.
	if (!CalculateTerrain(PlStripsPerTex,PlStripLength,
						  PlVertexBuffer,PlStripData,PlRings,PlTiles))
		return FALSE;

	// Calculate observer view terrain.
	if (!CalculateTerrain(ObsStripsPerTex,ObsStripLength,
						  ObsVertexBuffer,ObsStripData,ObsRings,ObsTiles))
		return FALSE;

	V=(DCVertex *)DCMalloc32(sizeof(DCVertex)*MAX_STRIP_LENGTH);
	if (!V)
		return FALSE;

	NeedToSetColorValues=TRUE;

	return TRUE;
}

// Shuts down the terrain.
void ShutdownTerrain(void)
{
	// Free any memory we allocated.
	DCSafeFree32(V);
	DCSafeFree(ObsStripData);
	DCSafeFree(ObsVertexBuffer);
	DCSafeFree(PlStripData);
	DCSafeFree(PlVertexBuffer);
}

// Puts the texture maxcolor value into the relevant vertices.
void SetVertexColorValues(RingInfo *Rings,TileInfo (*Tiles)[NUM_RADIAL_TEXTURES],DCVertex **StripData)
{
	RingInfo Ring;
	TileInfo *Tile;
	DCVertex **StripDataPtrs;

	for (int t=0;t<NUM_TANGENTIAL_TEXTURES;t++)
	{
		Ring=Rings[t];

		for (int r=0;r<NUM_RADIAL_TEXTURES;r++)
		{
			// Get tile.
			Tile=&Tiles[t][r];
			DWORD MaxColor=gGraphics.GetTextureMaxColor(Tile->Texture);

			StripDataPtrs=StripData + Tile->StartStripDataIndex;

			for (int tr=0;tr<=Ring.StripsPerTex;tr++)
			{
				for (int sr=0;sr<Ring.HalfStripLength;sr++)
				{
					(*StripDataPtrs)[sr].Color=MaxColor;

				}
				StripDataPtrs++;
			}
		}
	}
}

// Sets a single vertex in a strip.
static inline void SetVertex(DCVertex *DV, DCVertex *SV)
{
	DV->X=SV->X;		
	DV->Y=SV->Y;		
	DV->Z=SV->Z;
	DV->U=SV->U;
	DV->V=SV->V;
}

// Sets every second vertex in a strip.
static inline void SetVertices(DCVertex *DV, DCVertex *SV,int Count)
{
	for (;Count;Count--,SV++,DV+=2)
	{
		DV->X=SV->X;		
		DV->Y=SV->Y;		
		DV->Z=SV->Z;
		DV->U=SV->U;
		DV->V=SV->V;
	}
}

// Renders the terrain.
void RenderTerrain()
{
	RingInfo *Rings;
	TileInfo (*Tiles)[NUM_RADIAL_TEXTURES];
	DCVertex **StripData;

	RingInfo Ring;
	TileInfo *Tile;
	DCVertex **StripDataPtrs;
	int StartStrip,EndStrip;

	// Set vertex color values if necessary.
	if (NeedToSetColorValues)
	{
		SetVertexColorValues(ObsRings,ObsTiles,ObsStripData);
		SetVertexColorValues(PlRings,PlTiles,PlStripData);
		NeedToSetColorValues=FALSE;
	}
	
	gGraphics.ShadeModeFlat();
	gGraphics.DisableBlend();
	gGraphics.EnableDepthTest();
	gGraphics.DepthFunc(DFUNC_LESS);
	gGraphics.EnableDepthWrite();
	gGraphics.CullCW();
	gGraphics.TexAddressModeClamp();

	// Select which terrain to use.
	if (gRender.Frame.IsObserverMode)
	{
		Rings=ObsRings;
		Tiles=ObsTiles;
		StripData=ObsStripData;
	}
	else
	{
		Rings=PlRings;
		Tiles=PlTiles;
		StripData=PlStripData;
	}

	// Loop through each tile.
	for (int t=0;t<NUM_TANGENTIAL_TEXTURES;t++)
	{
		Ring=Rings[t];

		for (int r=0;r<NUM_RADIAL_TEXTURES;r++)
		{
			// Get tile.
			Tile=&Tiles[t][r];

			// Do visibility test.
			if (gVis.IsInWorldCenter() && !gRender.Frame.IsObserverMode)
			{
				// If we're in the center of the world we can use special routines.
				// Do a quick bounding sphere test since this rejects 40-60% of the tiles.
				if (gVis.SphereNotVisible(Tile->BoundingSphereCenter,
										Tile->BoundingSphereRadius))
					continue;
				// Bounding sphere isn't so good so do corner tests as well.
				if (gVis.EightPointsNotVisible(Tile->BoundingCorners))
					continue;
				// Walk through the strips from each side, figuring out the start and end strip we need to draw.
				// This could be a bit quicker if a binary search was used instead of a linear one but not
				// worth the effort really.
				if (gVis.IsLookingUp())
				{
					// See if top, far points are in.
					// Start strip.
					for (StartStrip=1;StartStrip<=Ring.StripsPerTex;StartStrip++)
					{
						DCVertex *V=StripData[Tile->StartStripDataIndex+StartStrip] + Ring.HalfStripLength-1;
						if (!gVis.PointOutsideLeft(V->X, Tile->MaxHeight, V->Z))
							break;
					}
					if (StartStrip > Ring.StripsPerTex)
						continue;
					StartStrip--;
					// End strip.
					for (EndStrip=Ring.StripsPerTex-1;EndStrip>=StartStrip;EndStrip--)
					{
						DCVertex *V=StripData[Tile->StartStripDataIndex+EndStrip] + Ring.HalfStripLength-1;
						if (!gVis.PointOutsideRight(V->X, Tile->MaxHeight, V->Z))
							break;
					}
					if (EndStrip < StartStrip)
						continue;
					EndStrip++;
				}
				else
				{
					// See if bottom, near points are in.
					// Start strip.
					for (StartStrip=1;StartStrip<=Ring.StripsPerTex;StartStrip++)
					{
						DCVertex *V=StripData[Tile->StartStripDataIndex+StartStrip];
						if (!gVis.PointOutsideLeft(V->X, Tile->MinHeight, V->Z))
							break;
					}
					if (StartStrip > Ring.StripsPerTex)
						continue;
					StartStrip--;
					// End strip.
					for (EndStrip=Ring.StripsPerTex-1;EndStrip>=StartStrip;EndStrip--)
					{
						DCVertex *V=StripData[Tile->StartStripDataIndex+EndStrip];
						if (!gVis.PointOutsideRight(V->X, Tile->MinHeight, V->Z))
							break;
					}
					if (EndStrip < StartStrip)
						continue;
					EndStrip++;
				}
			}
			else
			{
				// Don't bother with a sphere test, its pretty useless once we get away
				// from the center of the world. Instead just do full bounding corner test.
				if (gVis.EightPointsNotVisible(Tile->BoundingCorners))
					continue;
				// There isn't much else we can do (easily) so draw the full tile.
				StartStrip=0;
				EndStrip=Ring.StripsPerTex;
			}

			// Set texture.
			gGraphics.SetTexture(Tile->Texture);

			// Get pointer to strip data pointers.
			StripDataPtrs=StripData + (Tile->StartStripDataIndex+StartStrip);

			// Init strip data.
			DWORD MaxColor=gGraphics.GetTextureMaxColor(Tile->Texture);
			for (int i=0;i<Ring.StripLength;i++)
				V[i].Color=MaxColor;

			for (int tr=StartStrip;tr<EndStrip;tr++)
			{
				gGraphics.StripIndexed(*(StripDataPtrs++),
									   Ring.StripLength,
									   (tr&0x01) ? Ring.OddStripIndices : Ring.EvenStripIndices,
									   Ring.RenderStripLength);
			}
		}
	}
}
