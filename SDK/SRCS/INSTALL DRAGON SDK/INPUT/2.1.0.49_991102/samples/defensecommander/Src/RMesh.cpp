/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    RMesh.cpp

Abstract:

    Mesh rendering.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"
#include "DCMesh.h"
#include "DCVis.h"
#include "DCRender.h"
#include "DCWorld.h"
#include "DCGame.h"

#define VERTEX_BUFFER_SIZE 112
#if VERTEX_BUFFER_SIZE < TSM_MAX_STRIP_VERTICES
#error "RMesh.cpp: VERTEX_BUFFER_SIZE must be >=TSM_MAX_STRIP_VERTICES
#endif

// Buffer to hold indices for rendering.
static WORD *I;
// Buffer to hold vertices before rendering.
static DCVertex *V;

// Init/shutdown.
BOOL InitRMesh(void)
{
	I=(WORD *)DCMalloc32(sizeof(WORD)*VERTEX_BUFFER_SIZE*3);
	if (!I)
		return FALSE;

	V=(DCVertex *)DCMalloc32(sizeof(DCVertex)*VERTEX_BUFFER_SIZE);
	if (!V)
	{
		DCSafeFree32(I);
		return FALSE;
	}
	
	return TRUE;
}

void ShutdownRMesh(void)
{
	DCSafeFree32(V);
	DCSafeFree32(I);
}


// Renders the opaque meshes.
static void RenderOpaqueMeshCallback(HANDLE Mesh, DCVector *Loc, DCVector *Rot, void *User)
{
	// Make sure there is something opaque to render.
	if (!( ((TSMHeader *)Mesh)->Flags & TSM_FLAG_HAVE_OPAQUE ))
		return;

	// If first person mesh, save it and return.
	if (((TSMHeader *)Mesh)->Flags & TSM_FLAG_FIRST_PERSON && !((RMeshCurrentState *)User)->RenderFirstPerson)
	{
		gRender.Frame.FirstPerson.Mesh=Mesh;
		gRender.Frame.FirstPerson.Loc=*Loc;
		gRender.Frame.FirstPerson.Rot=*Rot;
		return;
	}

	// If user render mesh, call user function.
	if (((TSMHeader *)Mesh)->Flags & TSM_FLAG_USER_RENDER)
	{
		// Call user render function.
		((UserRenderMeshHeader *)Mesh)->RenderCallback(
			((UserRenderMeshHeader *)Mesh)->CallbackUserData,
			Loc,Rot,(RMeshCurrentState *)User);
		return;
	}

	// See if visible.
	if (gVis.SphereNotVisible(*Loc,((TSMHeader *)Mesh)->BoundingRadiusView))
		return;

	TSMVertex *Verts=((TSMHeader *)Mesh)->Verts;
	TSMVector *Normals=((TSMHeader *)Mesh)->Normals;
	
	// Calculate scaled sun normal.
	DCVector Sun=DCW_SUN_DIR;
	Sun.Normalize();
	Sun*=(1.0f-DCW_AMBIENT_INTENSITY)*255.0f;
	Sun.RotateY(-Rot->Y);
	Sun.RotateX(-Rot->X);
	Sun.RotateZ(-Rot->Z);

	// Set world matrix.
	gGraphics.MatrixIdentity();
	gGraphics.MatrixRotateZ(Rot->Z);
	gGraphics.MatrixRotateX(Rot->X);
	gGraphics.MatrixRotateY(Rot->Y);
	gGraphics.MatrixTranslate(Loc->X,Loc->Y,Loc->Z);
	gGraphics.SetWorldMatrix();

	// Walk the material list.
	for (int mi=0;mi<TSM_NUM_MATERIALS;mi++)
	{
		TSMMaterial *Mat=((TSMHeader *)Mesh)->Materials+mi;
		
		// If this material isn't used we are done.
		if (!(Mat->Flags & TSM_MFLAG_USED))
			return;

		// If this material isn't opaque/translucent as we wan't, move onto the next
		// We don't currently support opaque coronas (could be useful for billboards?)
		if (Mat->Flags & (TSM_MFLAG_TRANSLUCENT | TSM_MFLAG_CORONA))
			continue;

		// Set state as necessary.
		if (((RMeshCurrentState *)User)->LastTexture!=Mat->TextureHandle)
		{
			((RMeshCurrentState *)User)->LastTexture=Mat->TextureHandle;
			gGraphics.SetTexture(Mat->TextureHandle);
		}
		DWORD TmpFlags=Mat->Flags & (TSM_MFLAG_SMOOTH | TSM_MFLAG_TEXCLAMP);
		if (((RMeshCurrentState *)User)->LastFlags!=TmpFlags)
		{
			((RMeshCurrentState *)User)->LastFlags=TmpFlags;
			if (TmpFlags & TSM_MFLAG_SMOOTH)
				gGraphics.ShadeModeGouraud();
			else
				gGraphics.ShadeModeFlat();
			if (TmpFlags & TSM_MFLAG_TEXCLAMP)
				gGraphics.TexAddressModeClamp();
			else
				gGraphics.TexAddressModeRepeat();
		}

		// Render the strips.
		DCVertex *DV=V;
		WORD *DI=I;
		int VertexCount=0,IndexCount=0;
		for (signed short *ind=Mat->Indices;;)
		{
			int Count=*(ind++);
			if (!Count)
				break;

			// See if buffer can hold this strip.
			if (VertexCount+Count>TSM_MAX_STRIP_VERTICES)
			{
				gGraphics.TrianglesIndexed(V,VertexCount,I,((int)DI - (int)I)>>1);
				DV=V;
				DI=I;
				VertexCount=0;
			}

			// Put vertex data and indices in buffers.
			for (int i=0;i<Count;i++,DV++,VertexCount++)
			{
				TSMVertex *SV=Verts + *(ind++);
				TSMVector *SN=Normals + *(ind++);

				float I=SN->X*Sun.X + SN->Y*Sun.Y + SN->Z*Sun.Z;
				if (I<0)
					I=0;
				I+=(DCW_AMBIENT_INTENSITY*255.0f);
				int TmpI=(int)I;

				DV->X=SV->X;
				DV->Y=SV->Y;
				DV->Z=SV->Z;
				DV->Color=0xFF000000 | (TmpI<<16) | (TmpI<<8) | TmpI;
				DV->U=SV->U;
				DV->V=SV->V;

				if (i & 0x01)
				{
					*(DI++)=VertexCount;
					*(DI++)=VertexCount+2;
					*(DI++)=VertexCount+1;
				}
				else
				{
					*(DI++)=VertexCount;
					*(DI++)=VertexCount+1;
					*(DI++)=VertexCount+2;
				}
			}
			
			// Above loop will place 2 too many triangles in index buffer
			// so they must be removed.
			DI-=6;
		}
		
		// If there is something in the buffers, we must render it.
		if (VertexCount)
		{
			gGraphics.TrianglesIndexed(V,VertexCount,I,((int)DI - (int)I)>>1);
		}
	}
}

void RenderOpaqueMeshes(void)
{
	// Setup basic state.
	gGraphics.DisableBlend();
	gGraphics.EnableDepthTest();
	gGraphics.DepthFunc(DFUNC_LESSEQUAL);
	gGraphics.EnableDepthWrite();
	gGraphics.CullCW();
	gGraphics.TexAddressModeRepeat();
	gGraphics.ShadeModeFlat();
	gGraphics.SetTexture(NULL);

	// Setup callback struct. "last" matches the state we just set.
	RMeshCurrentState CurrentState;
	CurrentState.LastFlags=0;
	CurrentState.LastTexture=NULL;
	CurrentState.Translucent=FALSE;
	CurrentState.RenderFirstPerson=FALSE;

	// Have callback routine called with all the meshes.
	gGame.GetAllEntityMeshes(RenderOpaqueMeshCallback,&CurrentState,TRUE);
}

// Renders the translucent meshes.
static void RenderTranslucentMeshCallback(HANDLE Mesh, DCVector *Loc, DCVector *Rot, void *User)
{
	// Make sure there is something opaque to render.
	if (!( ((TSMHeader *)Mesh)->Flags & TSM_FLAG_HAVE_TRANS ))
		return;

	// Don't render first person mesh just yet.
	if (((TSMHeader *)Mesh)->Flags & TSM_FLAG_FIRST_PERSON && !((RMeshCurrentState *)User)->RenderFirstPerson)
		return;

	// If user render mesh, call user function.
	if (((TSMHeader *)Mesh)->Flags & TSM_FLAG_USER_RENDER)
	{
		// Call user render function.
		((UserRenderMeshHeader *)Mesh)->RenderCallback(
			((UserRenderMeshHeader *)Mesh)->CallbackUserData,
			Loc,Rot,(RMeshCurrentState *)User);
		return;
	}

	// See if visible.
	if (gVis.SphereNotVisible(*Loc,((TSMHeader *)Mesh)->BoundingRadiusView))
		return;

	TSMVertex *Verts=((TSMHeader *)Mesh)->Verts;
	DWORD MaxColor=0xFFFFFFFF;
	int MatrixState=0; // Keeps track of how the matrix is set.
	DCMatrix16 Matrix;

	// Walk the material list.
	for (int mi=0;mi<TSM_NUM_MATERIALS;mi++)
	{
		TSMMaterial *Mat=((TSMHeader *)Mesh)->Materials+mi;
		
		// If this material isn't used we are done.
		if (!(Mat->Flags & TSM_MFLAG_USED))
			return;

		// If this material isn't opaque/translucent as we wan't, move onto the next
		if (!(Mat->Flags & TSM_MFLAG_TRANSLUCENT))
			continue;

		// Get max color.
		MaxColor=gGraphics.GetTextureMaxColor(Mat->TextureHandle);

		// Set state as necessary.
		if (((RMeshCurrentState *)User)->LastTexture!=Mat->TextureHandle)
		{
			((RMeshCurrentState *)User)->LastTexture=Mat->TextureHandle;
			gGraphics.SetTexture(Mat->TextureHandle);
		}
		DWORD TmpFlags=Mat->Flags & TSM_MFLAG_TEXCLAMP;
		if (((RMeshCurrentState *)User)->LastFlags!=TmpFlags)
		{
			((RMeshCurrentState *)User)->LastFlags=TmpFlags;
			if (TmpFlags & TSM_MFLAG_TEXCLAMP)
				gGraphics.TexAddressModeClamp();
			else
				gGraphics.TexAddressModeRepeat();
		}

		// See if coronas or not.
		if (Mat->Flags & TSM_MFLAG_CORONA)
		{
			if (MatrixState!=1)
			{
				// Set world matrix.
				gGraphics.MatrixIdentity();
				gGraphics.SetWorldMatrix();
				
				gGraphics.MatrixRotateZ(Rot->Z);
				gGraphics.MatrixRotateX(Rot->X);
				gGraphics.MatrixRotateY(Rot->Y);
				gGraphics.MatrixTranslate(Loc->X,Loc->Y,Loc->Z);

				gGraphics.MatrixGet(&Matrix);
			
				MatrixState=1;
			}
			
			// Set constant values in vertex structures.
			V[0].Color=V[1].Color=V[2].Color=V[3].Color=MaxColor;
			V[0].U=0; V[0].V=0;
			V[1].U=1; V[1].V=0;
			V[2].U=0; V[2].V=1;
			V[3].U=1; V[3].V=1;

			
			int Count=((DWORD *)Mat->Indices)[0];
			TSMCorona *Corona=(TSMCorona *)(Mat->Indices+2);
			for (;Count;Count--,Corona++)
			{
				// Calculate center point of corona.
				DCVector Center=DCVector(
					Matrix.m11*Corona->CX + Matrix.m21*Corona->CY + Matrix.m31*Corona->CZ + Matrix.m41,
					Matrix.m12*Corona->CX + Matrix.m22*Corona->CY + Matrix.m32*Corona->CZ + Matrix.m42,
					Matrix.m13*Corona->CX + Matrix.m23*Corona->CY + Matrix.m33*Corona->CZ + Matrix.m43);
				float Radius=Corona->Radius;

				// If directional, adjust intensity.
				if (Mat->Flags & TSM_MFLAG_CORONA_DIRECTIONAL)
				{
					// Flare center to viewer.
					DCVector Vec1=gRender.Frame.ViewLoc - Center;
					Vec1.FastNormalize();

					// Normal.
					DCVector Vec2=DCVector(
					Matrix.m11*Corona->NX + Matrix.m21*Corona->NY + Matrix.m31*Corona->NZ + Matrix.m41,
					Matrix.m12*Corona->NX + Matrix.m22*Corona->NY + Matrix.m32*Corona->NZ + Matrix.m42,
					Matrix.m13*Corona->NX + Matrix.m23*Corona->NY + Matrix.m33*Corona->NZ + Matrix.m43);
					Vec2-=*Loc;

					float Dot=Vec1|Vec2;
					if (Dot <= 0)
						continue;
					int I=(int)(Dot*255.0f);
					if (I > 255)
						I=255;
					DWORD Color=0xFF000000 | (I << 16) | (I << 8) | I;
					V[0].Color=V[1].Color=V[2].Color=V[3].Color=Color;
				}

				// Project towards viewer if we're supposed to.
				if (Mat->Flags & TSM_MFLAG_CORONA_PROJECT)
				{
					float Dist=gRender.Frame.ViewLoc.FastDist(*Loc) - 
							   ((TSMHeader *)Mesh)->BoundingRadiusCollision;
					DCVector Vec=Center - gRender.Frame.ViewLoc;
					float Scale=Dist/Vec.FastLength();
					Center=gRender.Frame.ViewLoc+(Vec*Scale);
					Radius*=Scale;
				}
				
				// Calculate scaled view vectors.
				DCVector VecX=gRender.Frame.ViewVecX*Radius;
				DCVector VecY=gRender.Frame.ViewVecY*Radius;

				// Fill in vertex structures.
				V[0].X = Center.X - VecX.X - VecY.X;
				V[0].Y = Center.Y - VecX.Y - VecY.Y;
				V[0].Z = Center.Z - VecX.Z - VecY.Z;
				V[1].X = Center.X + VecX.X - VecY.X;
				V[1].Y = Center.Y + VecX.Y - VecY.Y;
				V[1].Z = Center.Z + VecX.Z - VecY.Z;
				V[2].X = Center.X - VecX.X + VecY.X;
				V[2].Y = Center.Y - VecX.Y + VecY.Y;
				V[2].Z = Center.Z - VecX.Z + VecY.Z;
				V[3].X = Center.X + VecX.X + VecY.X;
				V[3].Y = Center.Y + VecX.Y + VecY.Y;
				V[3].Z = Center.Z + VecX.Z + VecY.Z;

				// Render short strip.
				gGraphics.Strip(V,4);
			}
		}
		else
		{
			if (MatrixState!=2)
			{
				// Set world matrix.
				gGraphics.MatrixIdentity();
				gGraphics.MatrixRotateZ(Rot->Z);
				gGraphics.MatrixRotateX(Rot->X);
				gGraphics.MatrixRotateY(Rot->Y);
				gGraphics.MatrixTranslate(Loc->X,Loc->Y,Loc->Z);
				gGraphics.SetWorldMatrix();
			
				MatrixState=2;
			}
			
			// Render the strips.
			for (signed short *ind=Mat->Indices;;)
			{
				int Count=*(ind++);
				if (!Count)
					break;

				int i;
				DCVertex *DV;
				for (i=0,DV=V;i<Count;i++,DV++)
				{
					TSMVertex *SV=Verts + *(ind);
					ind+=2;

					DV->X=SV->X;
					DV->Y=SV->Y;
					DV->Z=SV->Z;
					DV->Color=MaxColor;
					DV->U=SV->U;
					DV->V=SV->V;
				}
				gGraphics.Strip(V,Count);
			}
		}
	}
}

// Renders the translucent meshes.
void RenderTranslucentMeshes(void)
{
	// Setup basic state.
	gGraphics.EnableBlend();
	gGraphics.BlendMode(BLEND_ONE,BLEND_INVOTHERCOLOR);
	gGraphics.EnableDepthTest();
	gGraphics.DepthFunc(DFUNC_LESSEQUAL);
	gGraphics.DisableDepthWrite();
	gGraphics.CullDisable();
	gGraphics.TexAddressModeRepeat();
	gGraphics.ShadeModeGouraud();
	gGraphics.SetTexture(NULL);

	// Setup callback struct. "last" matches the state we just set.
	RMeshCurrentState CurrentState;
	CurrentState.LastFlags=0;
	CurrentState.LastTexture=NULL;
	CurrentState.Translucent=TRUE;
	CurrentState.RenderFirstPerson=FALSE;

	// Have callback routine called with all the meshes.
	gGame.GetAllEntityMeshes(RenderTranslucentMeshCallback,&CurrentState,TRUE);
}

// Render first person mesh, right over the top of everything else.
void RenderFirstPersonMesh(void)
{
	if (gRender.Frame.FirstPerson.Mesh)
	{
#ifdef DREAMCAST
		// Scale InvW's so mesh is rendered in front of things.
		float m[16];
		gGraphics.GetProjectionMatrix((DCMatrix16 *)m);
		for (int i=0;i<16;i++)
			m[i]*=1.0f/8.0f;
		gGraphics.SetProjectionMatrix((DCMatrix16 *)m);
#endif
		// Setup state for opaque.
//		gGraphics.DisableDepthTest();
		gGraphics.EnableDepthTest();
		gGraphics.DepthFunc(DFUNC_LESSEQUAL);
		gGraphics.EnableDepthWrite();

		gGraphics.DisableBlend();
		gGraphics.CullCW();
		gGraphics.TexAddressModeRepeat();
		gGraphics.ShadeModeFlat();
		gGraphics.SetTexture(NULL);

		// Setup callback struct. "last" matches the state we just set.
		RMeshCurrentState CurrentState;
		CurrentState.LastFlags=0;
		CurrentState.LastTexture=NULL;
		CurrentState.Translucent=FALSE;
		CurrentState.RenderFirstPerson=TRUE;

		// Render mesh.
		RenderOpaqueMeshCallback(gRender.Frame.FirstPerson.Mesh,
								 &gRender.Frame.FirstPerson.Loc,
								 &gRender.Frame.FirstPerson.Rot,
								 &CurrentState);

		// Setup state for translucent.
		gGraphics.EnableBlend();
		gGraphics.BlendMode(BLEND_ONE,BLEND_INVOTHERCOLOR);
		gGraphics.CullDisable();
		gGraphics.TexAddressModeRepeat();
		gGraphics.ShadeModeGouraud();
		gGraphics.SetTexture(NULL);

		// Setup callback struct. "last" matches the state we just set.
		CurrentState.LastFlags=0;
		CurrentState.LastTexture=NULL;
		CurrentState.Translucent=TRUE;
		CurrentState.RenderFirstPerson=TRUE;

		// Render mesh.
		RenderTranslucentMeshCallback(gRender.Frame.FirstPerson.Mesh,
									  &gRender.Frame.FirstPerson.Loc,
									  &gRender.Frame.FirstPerson.Rot,
									  &CurrentState);
#ifdef DREAMCAST
		// Restore projection matrix.
		gGraphics.SetProjectionMatrix(&gRender.Frame.ProjectionMatrix);
#endif
	}
}