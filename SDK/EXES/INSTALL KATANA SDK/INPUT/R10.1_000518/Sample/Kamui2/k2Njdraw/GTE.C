/*********************************************************
 *	FILE NAME: kmtrfrm.c
 *
 *
 *
 *
 *
 *********************************************************/

/* $Revision:$ */

#include <math.h>
#include <machine.h>

#include "kamui2.h"
/*
 * for Use Faster Macro
 */
#define _KM_USE_VERTEX_MACRO_L4_
#define _KM_USE_CHANGESTRIP_MACRO_
#include "kamuix.h"

#include "gte.h"
#include "model.h"

/* Temporary External */
extern KMSURFACEDESC			FaceTexture;

/* Assembler Externs */
extern KGMATRIX MatrixBuffer;
extern KGMATRIX ViewMatrix;
extern float kgScreenCenterX;				/* Screen Center X */
extern float kgScreenCenterY;				/* Screen Center Y */
extern float kgScreenDistance;				/*　画角      */
extern float kgScreenScaleX;				/* Scale X */
extern float kgScreenScaleY;				/* Scale Y */
extern KMDWORD CurrentGlobal[5][4];			/* Globalのデータ */
extern float kgAmbientColor[4];				/* アンビエント */
extern float kgPallalelLightDir[12];		/* 平行光源 */
extern float kgPallalelLightColor[12];		/* 平行光源の色 */

/* Prototypes */
void kgFinalizeView(void* pMatrix);
static KMVOID DrawModel( PKMVERTEXBUFFDESC pVBufDesc, PKG_MODEL mod );
static KMVOID DrawMesh( PKMVERTEXBUFFDESC pVBufDesc, PKG_MESH pMesh, PKG_MATERIAL pMate, PKG_MODEL mod );

/* Definitions */
#define USE_TEXTURE		(0x00200000)
#define USE_ALPHA		(0x00100000)
#define USE_ENV			(0x00400000)

KMSURFACEDESC NullTexture;
KMDWORD WhiteTex[32] = {
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

LPKGMATRIX pCurrentPtr;
/* Strip Head */
KMSTRIPHEAD 			StripHeadOpaque;
KMSTRIPHEAD				StripHeadTrans;

/*
*			Texture
*/
PKMSURFACEDESC pTextureList;

KMVOID kgSetTexList(PKMSURFACEDESC pTexList)
{
	pTextureList = pTexList;
}

void kgChangeScreenCenter(float CenterX, float CenterY)
{
	kgScreenCenterX 	= CenterX;
	kgScreenCenterY 	= CenterY;
}

void kgChangeScreenScale(float ScaleX, float ScaleY)
{
	kgScreenScaleX		= ScaleX;
	kgScreenScaleY		= ScaleY;
}

void kgInitGeometry(float CenterX, float CenterY, float Pers)
{
	KMDWORD nLoop;
	KMSTRIPCONTEXT StripContext;

	for(nLoop = 0; nLoop < 12; nLoop++)
	{
		kgPallalelLightDir[nLoop] = 0.0f;
		kgPallalelLightColor[nLoop] = 0.0f;
	}

	kgScreenCenterX 	= CenterX;
	kgScreenCenterY 	= CenterY;
	kgScreenDistance 	= Pers;
	kgScreenScaleX		= 640.0f;
	kgScreenScaleY		= 640.0f;
	pCurrentPtr			= &MatrixBuffer;

	/* Create / Load Null Texture */
	kmCreateTextureSurface(		&NullTexture, 	/* Null texture Surafce Desc */
								8, 8,			/* U, V Size */
								KM_TEXTURE_TWIDDLED | KM_TEXTURE_RGB565
							);
	kmLoadTexture( &NullTexture, WhiteTex );

	memset(&StripContext, 0, sizeof(KMSTRIPCONTEXT));
	StripContext.nSize						 					= sizeof(KMSTRIPCONTEXT);
	StripContext.StripControl.nListType							= KM_OPAQUE_POLYGON;
	StripContext.StripControl.nUserClipMode						= KM_USERCLIP_DISABLE;
	StripContext.StripControl.nShadowMode						= KM_NORMAL_POLYGON;
	StripContext.StripControl.bOffset							= KM_TRUE;
	StripContext.StripControl.bGouraud							= KM_TRUE;
	StripContext.ObjectControl.nDepthCompare					= KM_GREATEREQUAL;
	StripContext.ObjectControl.nCullingMode						= KM_CULLSMALL;
	StripContext.ObjectControl.bZWriteDisable					= KM_FALSE;
	StripContext.ObjectControl.bDCalcControl					= KM_FALSE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].nSRCBlendingMode	= KM_ONE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].nDSTBlendingMode	= KM_ZERO;
	StripContext.ImageControl[KM_IMAGE_PARAM1].bSRCSelect		= KM_FALSE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].bDSTSelect		= KM_FALSE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].nFogMode			= KM_NOFOG;
	StripContext.ImageControl[KM_IMAGE_PARAM1].bColorClamp		= KM_FALSE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].bUseAlpha		= KM_FALSE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].bIgnoreTextureAlpha= KM_FALSE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].nFlipUV			= KM_NOFLIP;
	StripContext.ImageControl[KM_IMAGE_PARAM1].nClampUV			= KM_NOCLAMP;
	StripContext.ImageControl[KM_IMAGE_PARAM1].nFilterMode		= KM_BILINEAR;
	StripContext.ImageControl[KM_IMAGE_PARAM1].bSuperSampleMode	= KM_FALSE;
	StripContext.ImageControl[KM_IMAGE_PARAM1].dwMipmapAdjust	= KM_MIPMAP_D_ADJUST_1_00;
	StripContext.ImageControl[KM_IMAGE_PARAM1].nTextureShadingMode= KM_MODULATE_ALPHA;
	kmGenerateStripHead05( &StripHeadOpaque, &StripContext);

	memcpy(&StripHeadTrans, &StripHeadOpaque, sizeof(KMSTRIPHEAD));
	kmChangeStripListType(&StripHeadTrans, KM_TRANS_POLYGON);		/* Change To Translucent */
	kmChangeStripBlendingMode(&StripHeadTrans, KM_IMAGE_PARAM1,
							  KM_SRCALPHA, 				/* Source Blending A */
							  KM_INVSRCALPHA			/* Dest Blending (1-A) */
							  );
	kmChangeStripUseAlpha(&StripHeadTrans, KM_IMAGE_PARAM1, KM_TRUE);	/* Use Alpha */
}

KMBOOLEAN kgPushMatrix(void)
{
	kgGetMatrix(pCurrentPtr);
	pCurrentPtr++;
	return TRUE;
}

KMBOOLEAN kgPopMatrix(void)
{
	pCurrentPtr--;
	kgSetMatrix(pCurrentPtr);
	return TRUE;
}
/*
*			Set Global
*/
void kgSetOpaqueGlobal(KMDWORD dwPARAMCONT, KMDWORD dwISPTSP, KMDWORD dwTSP, KMDWORD dwTex)
{
	CurrentGlobal[0][0] = dwPARAMCONT;
	CurrentGlobal[0][1] = dwISPTSP;
	CurrentGlobal[0][2] = dwTSP;
	CurrentGlobal[0][3] = dwTex;
}
void kgSetTransGlobal(KMDWORD dwPARAMCONT, KMDWORD dwISPTSP, KMDWORD dwTSP, KMDWORD dwTex)
{
	CurrentGlobal[2][0] = dwPARAMCONT;
	CurrentGlobal[2][1] = dwISPTSP;
	CurrentGlobal[2][2] = dwTSP;
	CurrentGlobal[2][3] = dwTex;
}
void kgSetPunchGlobal(KMDWORD dwPARAMCONT, KMDWORD dwISPTSP, KMDWORD dwTSP, KMDWORD dwTex)
{
	CurrentGlobal[4][0] = dwPARAMCONT;
	CurrentGlobal[4][1] = dwISPTSP;
	CurrentGlobal[4][2] = dwTSP;
	CurrentGlobal[4][3] = dwTex;
}

/*
*					Light
*
*/
void kgSetAmbientColor(float Red, float Green, float Blue)
{
	kgAmbientColor[0] = Red;
	kgAmbientColor[1] = Green;
	kgAmbientColor[2] = Blue;
}

void kgSetParallelLightDir(int LightNo, float x, float y, float z)
{
	kgPallalelLightDir[LightNo * 4 + 0] = -x;
	kgPallalelLightDir[LightNo * 4 + 1] = y;
	kgPallalelLightDir[LightNo * 4 + 2] = z;
	kgVector(&kgPallalelLightDir[LightNo * 4], &kgPallalelLightDir[LightNo * 4]);
}

void kgSetParallelLightColor(int LightNo, float Red, float Green, float Blue)
{
	kgPallalelLightColor[LightNo * 4 + 0] = Red;
	kgPallalelLightColor[LightNo * 4 + 1] = Green;
	kgPallalelLightColor[LightNo * 4 + 2] = Blue;
}
/*
*					Geometry
*
*/
void kgInitMatrix(void* pViewMatrix)
{
	kgSetMatrix(pViewMatrix);
}

void kgSetView(		LPKGMATRIX pViewMatrix, 
					float px, float py, float pz,
					float vx, float vy, float vz)
{
	KGMATRIX Th, Ttemp, Tra, Tro;
	float cosa, sina, cosb, sinb, div, diffx, diffy, diffz;

	diffx = px - vx; diffy = py - vy; diffz = pz - vz;
	/* 
	 * 		Calculate Rotate Angle from View point 
	*/

	div = 1.0f / (float)sqrt(diffx * diffx + diffz * diffz);
	cosa = diffz * div;
	sina = diffx * div;
	div = 1.0f / (float)sqrt(diffx * diffx + diffy * diffy + diffz * diffz);
	cosb = (float)sqrt(diffx * diffx + diffz * diffz) * div;
	sinb = diffy * div;

	/* 
	 * 		Generate View Matrix
	*/
	kgSetIdentity();				/* CurrentMatrix =　Unit Matrix */
	kgSetAngleRotateX(cosb, -sinb);	/* FR result FR<->XMATRIX (frchg) */
	kgSetAngleRotateY(cosa, -sina);	/* FR result FR<->XMATRIX (frchg) */
	kgTranslate(-px, -py, -pz);		/* XMATRIX *= Translate */
	kgFinalizeView(pViewMatrix);
}

void kgSetViewAngle(LPKGMATRIX pViewMatrix,
					float px, float py, float pz,
					float head, float pitch, float bank)
{
	float div;
	KMDWORD head_t, pitch_t, bank_t;

	div = (1.0f /(2 * 3.141592653) * 65536.0f);

	head_t =(KMDWORD)( head * div );
	pitch_t =(KMDWORD)( pitch * div );
	bank_t =(KMDWORD)( bank * div );

	kgSetIdentity();
	kgRotateZ(bank_t);
	kgRotateY(head_t);
	kgRotateX(pitch_t);
	kgTranslate(-px, -py, -pz);
	kgFinalizeView(pViewMatrix);
}

KMVOID kgBasicDrawObject( PKMVERTEXBUFFDESC pVBufDesc, PKG_OBJECT obj )
{
	do
	{
		kgPushMatrix();

		if (!(obj->Eval & 1))
		{
			kgTranslate( obj->Position.x, obj->Position.y, obj->Position.z );
		}
		if (!(obj->Eval & 4))
		{
			kgScale( obj->Scale.x   , obj->Scale.y   , obj->Scale.z    );
		}
		if (!(obj->Eval & 2))
		{
			kgRotateZ( obj->Angle.z );
			kgRotateY( obj->Angle.y );
			kgRotateX( obj->Angle.x );
		}

		if (obj->Model) DrawModel( pVBufDesc, obj->Model );
		if (obj->Child) kgBasicDrawObject( pVBufDesc, obj->Child );

		kgPopMatrix();
		obj = obj->Sibling ;
	} while (obj != NULL);
}
/*

*/
KMBOOLEAN ClipModel( PKG_MODEL mod )
{
	return FALSE;
}

KMVOID DrawModel( PKMVERTEXBUFFDESC pVBufDesc, PKG_MODEL mod )
{
	KMDWORD i;
	PKG_MESH     pMesh;
	PKG_MATERIAL pMate;

	if (ClipModel( mod )) return;					/* モデル単位クリップ			*/

	kgPreprocessLight();

	pMesh = mod->Mesh;								/* メッシュポインタ				*/
	for(i=0; i<mod->MeshNum; i++) 
	{
		pMate = mod->Material;						/* マテリアルポインタ			*/
		pMate+= pMesh->MaterialID & 0xff;			/* マテリアルＩＤ				*/
		DrawMesh( pVBufDesc, pMesh, pMate, mod );	/* メッシュ描画					*/
		pMesh++;									/* 次のメッシュ					*/
	}
}

/*
	Mesh Draw

*/
static PKMDWORD PutMeshTX(PKMDWORD pkmCurrentPtr, PKG_MESH pMesh, PKG_MATERIAL pMate, PKG_MODEL mod )
{
	KMDWORD   			i,j;
	KMDWORD   			Num;
	register PKMWORD	pUV;
	register PKMWORD   	pIdx;

	pIdx = pMesh->Mesh;								/* Index List				*/
	pUV	 = (PKMWORD)pMesh->vertuv;
	for(i=0; i < pMesh->MeshNum; i++)
	{
		Num = *pIdx++;								/* Strip And Direction		*/
		Num = (Num & 0x7fff);
		for(j = 0; j < Num; j++)
		{
			/* 
			 * SetVertex Using Assembler as kmxxSetVertex_5
			 */
			pkmCurrentPtr++;
			kgProjection((float *)pkmCurrentPtr, (float *)(&(mod->PList[*pIdx])));
			if (j == (Num - 1))
				*--pkmCurrentPtr = KM_VERTEXPARAM_ENDOFSTRIP;
			else
				*--pkmCurrentPtr = KM_VERTEXPARAM_NORMAL;
			pUV++;
			pkmCurrentPtr += 6;
			*(float *)--pkmCurrentPtr = ((float)*pUV--) * (1.0f/256.0f);
			*(float *)--pkmCurrentPtr = ((float)*pUV++) * (1.0f/256.0f);
			pUV++;
			prefetch(pkmCurrentPtr);
			pkmCurrentPtr += 4;
			kgCalcLambert(pkmCurrentPtr, (float *)(&(mod->PNormal[*pIdx])), (void *)&pMate->Diff);
			prefetch(pkmCurrentPtr);
			pkmCurrentPtr += 8;
			pIdx++;
		}
	}
	return pkmCurrentPtr;
}

static PKMDWORD PutMeshTXENV(PKMDWORD pkmCurrentPtr, PKG_MESH pMesh, PKG_MATERIAL pMate, PKG_MODEL mod )
{
	KMDWORD   			i,j;
	KMDWORD   			Num;
	register PKMWORD   	pIdx;

	pIdx = pMesh->Mesh;								/* Index List				*/
	for(i=0; i < pMesh->MeshNum; i++)
	{
		Num = *pIdx++;								/* Strip And Direction		*/
		Num = (Num & 0x7fff);
		for(j = 0; j < Num; j++)
		{
			/* 
			 * SetVertex Using Assembler as kmxxSetVertex_5
			 */
			pkmCurrentPtr++;
			kgProjection((float *)pkmCurrentPtr, (float *)(&(mod->PList[*pIdx])));
			if (j == (Num - 1))
				*--pkmCurrentPtr = KM_VERTEXPARAM_ENDOFSTRIP;
			else
				*--pkmCurrentPtr = KM_VERTEXPARAM_NORMAL;
			pkmCurrentPtr += 4;
			kgEnvMap((float *)pkmCurrentPtr ,(float *)(&(mod->PNormal[*pIdx])));
			prefetch(pkmCurrentPtr);
			pkmCurrentPtr += 4;
			kgCalcLambert(pkmCurrentPtr, (float *)(&(mod->PNormal[*pIdx])), (void *)&pMate->Diff);
			prefetch(pkmCurrentPtr);
			pkmCurrentPtr += 8;
			pIdx++;
		}
	}
	return pkmCurrentPtr;
}

static PKMDWORD PutMeshNTX(PKMDWORD pkmCurrentPtr, PKG_MESH pMesh, PKG_MATERIAL pMate, PKG_MODEL mod )
{
	KMDWORD   			i,j;
	KMDWORD   			Num;
	register PKMWORD   	pIdx;

	pIdx = pMesh->Mesh;								/* Index List				*/
	for(i=0; i < pMesh->MeshNum; i++)
	{
		Num = *pIdx++;								/* Strip And Direction		*/
		Num = (Num & 0x7fff);
		for(j = 0; j < Num; j++)
		{
			/* 
			 * SetVertex Using Assembler as kmxxSetVertex_5
			 */
			pkmCurrentPtr++;
			kgProjection((float *)pkmCurrentPtr, (float *)(&(mod->PList[*pIdx])));
			if (j == (Num - 1))
				*--pkmCurrentPtr = KM_VERTEXPARAM_ENDOFSTRIP;
			else
				*--pkmCurrentPtr = KM_VERTEXPARAM_NORMAL;
			pkmCurrentPtr += 6;
			*(float *)--pkmCurrentPtr = 0.0f;
			*(float *)--pkmCurrentPtr = 0.0f;
			prefetch(pkmCurrentPtr);
			pkmCurrentPtr += 4;
			kgCalcLambert(pkmCurrentPtr, (float *)(&(mod->PNormal[*pIdx])), (void *)&pMate->Diff);
			prefetch(pkmCurrentPtr);
			pkmCurrentPtr += 8;
			pIdx++;
		}
	}
	return pkmCurrentPtr;
}

/*----------------------------------------------------------------------------------*/
KMVOID DrawMesh( PKMVERTEXBUFFDESC pVBufDesc, PKG_MESH pMesh, PKG_MATERIAL pMate, PKG_MODEL mod )
{
	PKMSTRIPHEAD		pStripHead;

	/* 
	 * Select Opaque/ Translucent From Attribute 
	 */
	if (pMate->Attr & USE_ALPHA) 
		pStripHead = &StripHeadTrans;
	else 
		pStripHead = &StripHeadOpaque;

	if (pMate->Attr & USE_TEXTURE)
	{												/* Generate StripHead	*/
		kmxxGetCurrentPtr(pVBufDesc);
		kmChangeStripTextureSurface( 	pStripHead, 
										KM_IMAGE_PARAM1, 
										&pTextureList[pMate->TexID]
									);

		kmxxStartStrip(pVBufDesc, pStripHead);
		if (pMate->Attr & USE_ENV)
		{
			pkmCurrentPtr = PutMeshTXENV(pkmCurrentPtr, pMesh, pMate, mod );
		}
		else
		{
			pkmCurrentPtr = PutMeshTX(pkmCurrentPtr, pMesh, pMate, mod );
		}
		kmxxReleaseCurrentPtr(pVBufDesc);
		return;
	}
	else
	{
		kmxxGetCurrentPtr(pVBufDesc);
		kmChangeStripTextureSurface( 	pStripHead, 
										KM_IMAGE_PARAM1, 
										&NullTexture
									);
		kmxxStartStrip(pVBufDesc, pStripHead);
		pkmCurrentPtr = PutMeshNTX(pkmCurrentPtr, pMesh, pMate, mod );
		kmxxReleaseCurrentPtr(pVBufDesc);
	}
}
