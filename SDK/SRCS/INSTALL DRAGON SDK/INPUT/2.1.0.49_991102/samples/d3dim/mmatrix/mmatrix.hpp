/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    mmatrix.hpp

Abstract:

   Include file for mmatrix

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++

#define D3D_OVERLOADS

#include <tchar.h>
#include <windows.h>
#include <ddraw.h>
#include <d3d.h>
#include "FloatMathLib.h"
#include "D3DMath.hpp"

// ++++ Enumerated Types ++++++++++++++++++++++++++++++++++++++++++++

// Output types
enum toutputlevel { OUTPUT_ALL = 0, OUTPUT_FAILURESONLY };

// ++++ Types +++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Error type
typedef int terr;

struct LightDirn
{
	float	w;
	float	x;
	float	y;
	float	z;
};


// ++++ Defines +++++++++++++++++++++++++++++++++++++++++++++++++++++

// D3DUtil.cpp defines
#define PI                 3.1415926f
#define MAX_LIGHTS         10

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

// mmatrix.cpp variables
extern HWND                 g_hwndApp;                   // HWND of the application
extern HINSTANCE            g_hinst;                     // HINSTANCE of the application

// Error.cpp variables
extern toutputlevel         g_outputlevel;               // Amount of detail in error messages
extern terr                 g_errLast;                   // Error return code of last function

// DDUtil.cpp variables
extern LPDIRECTDRAW4        g_pdd;                       // The DirectDraw object
extern LPDIRECTDRAWSURFACE4 g_pddsPrimary;               // Primary directdraw surface
extern LPDIRECTDRAWSURFACE4 g_pddsBack;                  // Back buffer directdraw surface

// D3DUtil.cpp variables
extern LPDIRECT3DVIEWPORT3  g_pviewport;                 // Main Direct3D viewport
extern LPDIRECT3DMATERIAL3  g_pmatWhite;                 // Global white material
extern LPDIRECT3DMATERIAL3  g_pmatBkGnd;                 // Global background material
extern D3DMATERIALHANDLE    g_hmatWhite;                 // Global white material handle
extern D3DMATERIALHANDLE    g_hmatBlack;                 // Global black material handle
extern LPDIRECT3DDEVICE3    g_p3ddevice;                 // Main Direct3D Device
extern LPDIRECT3DLIGHT      g_rglight[MAX_LIGHTS];       // Global D3D light.
extern LPDIRECT3D3          g_pd3d;                      // Direct3D object
extern D3DMATRIX            g_matIdent;                  // Global identity matrix.
extern int                  g_cLights;                   // Number of lights

// ++++ Global Functions ++++++++++++++++++++++++++++++++++++++++++++

// Concatenate Matrices
extern "C" void ConcatenateMatrices( float *pmOut, float **ppmIn );

// Transpose Matrix
extern "C" void TransposeMatrix( float *pmOut, float *pmIn );

// Transforms vector
extern "C" void VectorMatrixMultiply( float *pvOut, float *pmIn, float *pvIn );

// Build scale matrix and then scale
extern "C" void ScaleMatrix( float *pmOut, float *pmIn, float *pScale );

// Add ALL components of two matrices
extern "C" void AddMatrices( float *pmOut, float *pmIn1, float *pmIn2 );

// DDUtil.cpp functions
void FlipBuffers();
BOOL InitDirectDraw();
LPDIRECTDRAWSURFACE4 LoadBitmapToDDS(LPTSTR tszBitmap);
HRESULT GetSurfaceDesc(LPDDSURFACEDESC2 pddsurfdesc, LPDIRECTDRAWSURFACE4 pddsurf);

// D3DUtil.cpp functions
BOOL InitDirect3D();
BOOL AddLight(float rRed, float rGreen, float rBlue, float rX, float rY, float rZ);
LPDIRECT3DMATERIAL3 CreateMaterial(float rRed, float rGreen, float rBlue, float rAlpha, float rPower, 
                                   float rSpecR, float rSpecG, float rSpecB, 
                                   float rEmisR, float rEmisG, float rEmisB);
void SetProjectionMatrix(LPD3DMATRIX pM, float rNear, float rFar, float rFov, float rAspect);
void SetViewMatrix(LPD3DMATRIX pmatxDest, LPD3DVECTOR pvectFrom, LPD3DVECTOR pvectAt, LPD3DVECTOR pvectUp);
void NormalizeVector(LPD3DVECTOR pvect);

// TxtrUtil.cpp functions
LPDIRECT3DTEXTURE2 LoadTexture(TCHAR *tszFileName);

// Error.cpp functions
BOOL CheckError(TCHAR *tszErr);
void RetailOutput(TCHAR *tszErr, ...);
#ifdef DEBUG
void DebugOutput(TCHAR *tszErr, ...);
#else
__inline void DebugOutput(TCHAR *tszErr, ...) {};
#endif
