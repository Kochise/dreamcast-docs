/*
 *
 *
 *
 */
#if !defined(__gte_h)
#define __gte_h

#include "model.h"

typedef float KG2DVECTOR[2];
typedef float KG3DVECTOR[4];
typedef float KGCOLOR[4];

typedef struct _tagKGMATRIX
{
	/* for Vertex Data */
	float		_11, _21, _31, _41;
	float		_12, _22, _32, _42;
	float		_13, _23, _33, _43;
	float		_14, _24, _34, _44;

} KGMATRIX, *LPKGMATRIX;

#define KG_COLOR_A 0
#define KG_COLOR_R 1
#define KG_COLOR_G 2
#define KG_COLOR_B 3

#define KG_X 0
#define KG_Y 1
#define KG_Z 2

#define KG_CONTROL_ENDOFMODEL 0x00000001


typedef struct _tagKGTLVERTEX
{
	KMDWORD	Control;			/* Control Bit */
								/* Bit 0... End Of This Model Data */
								/* Bit 1-3  ListType */
	KMDWORD	ParamWord;

	float	fX;					/* ç¿ïW */
	float	fY;
	float	fZ;

	float	fU;					/* Texture Vector */
	float	fV;
	KMDWORD	Reserved0;

	float	NormX;
	float	NormY;
	float	NormZ;

	KMDWORD	Reserved1[5];
}KGVERTEX, *PKGVERTEX;

#define PI	3.1415926535f
/* Function Prototypes */

void kgInitGeometry(float CenterX, float CenterY, float Pers);

/* 
 * Assembler 
 */
void kgInitMatrix(void* pViewMatrix);
void kgSetIdentity(void);
void kgSetUnitMatrix(void* pMatrix);
void kgSetMatrix(void* pMatrix);
void kgGetMatrix(void* pMatrix);
void kgScale(float x, float y, float z);
void kgTranslate(float x, float y, float z);
void kgRotateX(KMDWORD angle);
void kgRotateY(KMDWORD angle);
void kgRotateZ(KMDWORD angle);
void kgSetAngleRotateX(float cosa, float sina);
void kgSetAngleRotateY(float cosb, float sinb);
KMBOOLEAN kgProjection(float *pOutput, float *pInput);
void kgPoint(float *pOutput, float *pInput);
void kgVector(float *pOutput, float *pInput);
void kgEnvMap(float *pOutput, float *pInput);
float kgInnerProduct(float *Vector1, float *Vector2);
float kgOuterProduct(float *Vector1, float *Vector2);
void kgPreprocessLight(void);
void kgCalcLambertLight(KG3DVECTOR *Color, KG3DVECTOR *Data, void * Diffuse);

KMBOOLEAN kgPushMatrix(void);
KMBOOLEAN kgPopMatrix(void);

/* View */
void kgSetView(LPKGMATRIX pViewMatrix, float px, float py, float pz, float vx, float vy, float vz);
void kgSetViewAngle(LPKGMATRIX pViewMatrix, float px, float py, float pz, float head, float pitch, float bank);

void kgSetOpaqueGlobal(KMDWORD dwPARAMCONT, KMDWORD dwISPTSP, KMDWORD dwTSP, KMDWORD dwTex);
void kgSetTransGlobal(KMDWORD dwPARAMCONT, KMDWORD dwISPTSP, KMDWORD dwTSP, KMDWORD dwTex);
void kgSetPunchGlobal(KMDWORD dwPARAMCONT, KMDWORD dwISPTSP, KMDWORD dwTSP, KMDWORD dwTex);
void kgSetAmbientColor(float Red, float Green, float Blue);
void kgSetParallelLightDir(int LightNo, float x, float y, float z);
void kgSetParallelLightColor(int LightNo, float Red, float Green, float Blue);
void kgChangeScreenCenter(float CenterX, float CenterY);
void kgChangeScreenScale(float ScaleX, float ScaleY);

KMVOID kgBasicDrawObject(PKMVERTEXBUFFDESC pVBufDesc, PKG_OBJECT obj );
KMVOID kgSetTexList(PKMSURFACEDESC pTexList);


extern KGMATRIX ViewMatrix;

#endif /* __kmtrfrm_h */
