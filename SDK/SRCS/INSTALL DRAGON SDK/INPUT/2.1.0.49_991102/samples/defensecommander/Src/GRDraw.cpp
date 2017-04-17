/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    GRDraw.cpp

Abstract:

    Code to draw triangle outlines for when "show triangles" is
	enabled.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"

void GraphicsClass::DrawTriangles(DCVertex Verts[],int Count)
{
	int NumLines=Count;
	LPDIRECT3DTEXTURE2 OrgTexture;
	DWORD OrgDepthBias;
	DWORD OrgBlend;
	DWORD OrgSpecular;
	D3DCMPFUNC OrgZEnable;
	DCVertex *LV;
	WORD *Indices;

	// Save existing state.
	D3DDevice->GetTexture(0,&OrgTexture);
	D3DDevice->GetRenderState(D3DRENDERSTATE_ZBIAS,&OrgDepthBias);
	D3DDevice->GetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,&OrgBlend);
	D3DDevice->GetRenderState(D3DRENDERSTATE_SPECULARENABLE,&OrgSpecular);
	D3DDevice->GetRenderState(D3DRENDERSTATE_ZFUNC,(DWORD *)&OrgZEnable);

	// Set new state.
	D3DDevice->SetTexture(0,NULL);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ZBIAS,OrgDepthBias+1);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,FALSE);
	D3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE);
	if (OrgZEnable==D3DCMP_EQUAL || OrgZEnable==D3DCMP_LESS)
		D3DDevice->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_LESSEQUAL);

	// Make local copy of vertices with new color.
	LV=(DCVertex *)DCMalloc(sizeof(DCVertex)*Count);
	if (!LV)
		return;
	DCCopyMemory(LV,Verts,Count*sizeof(DCVertex));
	for (int i=0;i<Count;i++)
		LV[i].Color=0xFFFF00FF;

	// Create line indices.
	Indices=(WORD *)DCMalloc(sizeof(WORD)*NumLines*2);
	if (!Indices)
	{
		DCFree(LV);
		return;
	}
	for (i=0;i<Count;i+=3)
	{
		Indices[(i*2) + 0]=i+0;
		Indices[(i*2) + 1]=i+1;
		Indices[(i*2) + 2]=i+1;
		Indices[(i*2) + 3]=i+2;
		Indices[(i*2) + 4]=i+2;
		Indices[(i*2) + 5]=i+0;
	}

	// Draw lines.
	D3DDevice->DrawIndexedPrimitive(D3DPT_LINELIST,
									VertexType,
									LV,
									Count,
									Indices,
									NumLines*2,
									VertexFlags & ~D3DDP_DONOTCLIP);

	// Free memory.
	DCFree(Indices);
	DCFree(LV);
	
	// Restore state.
	D3DDevice->SetTexture(0,OrgTexture);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ZBIAS,OrgDepthBias);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,OrgBlend);
	D3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,OrgSpecular);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ZFUNC,OrgZEnable);
}

void GraphicsClass::DrawTrianglesIndexed(DCVertex Verts[],int Count,WORD *IndicesIn,int IndexCount)
{
	int NumLines=IndexCount;
	LPDIRECT3DTEXTURE2 OrgTexture;
	DWORD OrgDepthBias;
	DWORD OrgBlend;
	DWORD OrgSpecular;
	D3DCMPFUNC OrgZEnable;
	DCVertex *LV;

	// Save existing state.
	D3DDevice->GetTexture(0,&OrgTexture);
	D3DDevice->GetRenderState(D3DRENDERSTATE_ZBIAS,&OrgDepthBias);
	D3DDevice->GetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,&OrgBlend);
	D3DDevice->GetRenderState(D3DRENDERSTATE_SPECULARENABLE,&OrgSpecular);
	D3DDevice->GetRenderState(D3DRENDERSTATE_ZFUNC,(DWORD *)&OrgZEnable);

	// Set new state.
	D3DDevice->SetTexture(0,NULL);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ZBIAS,OrgDepthBias+1);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,FALSE);
	D3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE);
	if (OrgZEnable==D3DCMP_EQUAL || OrgZEnable==D3DCMP_LESS)
		D3DDevice->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_LESSEQUAL);

	// Make local copy of vertices with new color.
	LV=(DCVertex *)DCMalloc(sizeof(DCVertex)*IndexCount);
	if (!LV)
		return;
	for (int i=0;i<IndexCount;i++)
	{
		DCCopyMemory(LV + i,Verts + IndicesIn[i],sizeof(DCVertex));
		LV[i].Color=0xFFFFFFFF;
	}

	// Create line indices.
	WORD *Indices=(WORD *)DCMalloc(sizeof(WORD)*NumLines*2);
	if (!Indices)
	{
		DCFree(LV);
		return;
	}
	for (i=0;i<IndexCount;i+=3)
	{
		Indices[(i*2) + 0]=i+0;
		Indices[(i*2) + 1]=i+1;
		Indices[(i*2) + 2]=i+1;
		Indices[(i*2) + 3]=i+2;
		Indices[(i*2) + 4]=i+2;
		Indices[(i*2) + 5]=i+0;
	}

	// Draw lines.
	D3DDevice->DrawIndexedPrimitive(D3DPT_LINELIST,
									VertexType,
									LV,
									IndexCount,
									Indices,
									NumLines*2,
									VertexFlags & ~D3DDP_DONOTCLIP);

	// Free memory.
	DCFree(Indices);
	DCFree(LV);
	
	// Restore state.
	D3DDevice->SetTexture(0,OrgTexture);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ZBIAS,OrgDepthBias);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,OrgBlend);
	D3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,OrgSpecular);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ZFUNC,OrgZEnable);
}

void GraphicsClass::DrawStripTriangles(DCVertex Verts[],int Count)
{
	int NumLines=Count*2-3;
	LPDIRECT3DTEXTURE2 OrgTexture;
	DWORD OrgDepthBias;
	DWORD OrgBlend;
	DWORD OrgSpecular;
	D3DCMPFUNC OrgZEnable;
	DCVertex *LV;
	WORD *Indices;

	// Save existing state.
	D3DDevice->GetTexture(0,&OrgTexture);
	D3DDevice->GetRenderState(D3DRENDERSTATE_ZBIAS,&OrgDepthBias);
	D3DDevice->GetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,&OrgBlend);
	D3DDevice->GetRenderState(D3DRENDERSTATE_SPECULARENABLE,&OrgSpecular);
	D3DDevice->GetRenderState(D3DRENDERSTATE_ZFUNC,(DWORD *)&OrgZEnable);

	// Set new state.
	D3DDevice->SetTexture(0,NULL);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ZBIAS,OrgDepthBias+1);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,FALSE);
	D3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE);
	if (OrgZEnable==D3DCMP_EQUAL || OrgZEnable==D3DCMP_LESS)
		D3DDevice->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_LESSEQUAL);

	// Make local copy of vertices with new color.
	LV=(DCVertex *)DCMalloc(sizeof(DCVertex)*Count);
	if (!LV)
		return;
	DCCopyMemory(LV,Verts,Count*sizeof(DCVertex));
	for (int i=0;i<Count;i++)
		LV[i].Color=0xFFFFFFFF;

	// Create line indices.
	Indices=(WORD *)DCMalloc(sizeof(WORD)*NumLines*2);
	if (!Indices)
	{
		DCFree(LV);
		return;
	}
	Indices[0]=0;
	Indices[1]=1;
	for (i=2;i<Count;i++)
	{
		Indices[(i-2)*4 + 2]=i;
		Indices[(i-2)*4 + 3]=i-1;
		Indices[(i-2)*4 + 4]=i;
		Indices[(i-2)*4 + 5]=i-2;
	}

	// Draw lines.
	D3DDevice->DrawIndexedPrimitive(D3DPT_LINELIST,
									VertexType,
									LV,
									Count,
									Indices,
									NumLines*2,
									VertexFlags & ~D3DDP_DONOTCLIP);

	// Free memory.
	DCFree(Indices);
	DCFree(LV);
	
	// Restore state.
	D3DDevice->SetTexture(0,OrgTexture);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ZBIAS,OrgDepthBias);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,OrgBlend);
	D3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,OrgSpecular);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ZFUNC,OrgZEnable);
}

void GraphicsClass::DrawStripTrianglesIndexed(DCVertex Verts[],int VertexCount,WORD *IndicesIn,int IndexCount)
{
	int NumLines=IndexCount*2-3;
	LPDIRECT3DTEXTURE2 OrgTexture;
	DWORD OrgDepthBias;
	DWORD OrgBlend;
	DWORD OrgSpecular;
	D3DCMPFUNC OrgZEnable;
	DCVertex *LV;

	// Save existing state.
	D3DDevice->GetTexture(0,&OrgTexture);
	D3DDevice->GetRenderState(D3DRENDERSTATE_ZBIAS,&OrgDepthBias);
	D3DDevice->GetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,&OrgBlend);
	D3DDevice->GetRenderState(D3DRENDERSTATE_SPECULARENABLE,&OrgSpecular);
	D3DDevice->GetRenderState(D3DRENDERSTATE_ZFUNC,(DWORD *)&OrgZEnable);

	// Set new state.
	D3DDevice->SetTexture(0,NULL);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ZBIAS,OrgDepthBias+1);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,FALSE);
	D3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,FALSE);
	if (OrgZEnable==D3DCMP_EQUAL || OrgZEnable==D3DCMP_LESS)
		D3DDevice->SetRenderState(D3DRENDERSTATE_ZFUNC,D3DCMP_LESSEQUAL);

	// Make local copy of vertices with new color.
	LV=(DCVertex *)DCMalloc(sizeof(DCVertex)*IndexCount);
	if (!LV)
		return;
	for (int i=0;i<IndexCount;i++)
	{
		DCCopyMemory(LV + i,Verts + IndicesIn[i],sizeof(DCVertex));
		LV[i].Color=0xFFFFFFFF;
	}

	// Create line indices.
	WORD *Indices=(WORD *)DCMalloc(sizeof(WORD)*NumLines*2);
	if (!Indices)
	{
		DCFree(LV);
		return;
	}
	Indices[0]=0;
	Indices[1]=1;
	for (i=2;i<IndexCount;i++)
	{
		Indices[(i-2)*4 + 2]=i;
		Indices[(i-2)*4 + 3]=i-1;
		Indices[(i-2)*4 + 4]=i;
		Indices[(i-2)*4 + 5]=i-2;
	}

	// Draw lines.
	D3DDevice->DrawIndexedPrimitive(D3DPT_LINELIST,
									VertexType,
									LV,
									IndexCount,
									Indices,
									NumLines*2,
									VertexFlags & ~D3DDP_DONOTCLIP);

	// Free memory.
	DCFree(Indices);
	DCFree(LV);
	
	// Restore state.
	D3DDevice->SetTexture(0,OrgTexture);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ZBIAS,OrgDepthBias);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE,OrgBlend);
	D3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE,OrgSpecular);
	D3DDevice->SetRenderState(D3DRENDERSTATE_ZFUNC,OrgZEnable);
}
