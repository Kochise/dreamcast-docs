/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    BasicD3DIM.hpp

Abstract:

   Include file for BasicD3DIM

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++

#define D3D_OVERLOADS

#include <tchar.h>
#include <windows.h>
#include <ddraw.h>
#include <d3d.h>
#ifdef UNDER_CE
#include "FloatMathLib.h"
#endif // UNDER_CE

// ++++ Enumerated Types ++++++++++++++++++++++++++++++++++++++++++++

// Output types
enum toutputlevel { OUTPUT_ALL = 0, OUTPUT_FAILURESONLY };

// ++++ Types +++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Error type
typedef int terr;

// ++++ Defines +++++++++++++++++++++++++++++++++++++++++++++++++++++

// D3DUtil.cpp defines
#define PI                 3.1415926f
#define TWOPI              6.2831853f
#define MAX_LIGHTS         10

// Flexible vertex format for a lit vertex with 2 texture coordinates
#define FVF_MLVERTEX       (D3DFVF_XYZ | D3DFVF_TEX2)

// ++++ Structures ++++++++++++++++++++++++++++++++++++++++++++++++++

// Camera definition
typedef struct _CAMERA {
	D3DVECTOR vectPosition;
	D3DVECTOR vectInterest;
	D3DVALUE  rRoll;
	D3DVALUE  rFieldOfView;
	D3DVALUE  rNearPlane;
	D3DVALUE  rFarPlane;
} CAMERA, *PCAMERA;

// Lit vertex format with two texture coordinates (for multistage texturing)
typedef struct _MLVERTEX {
    D3DVECTOR vectPosition;
    D3DVALUE  u0, v0;
    D3DVALUE  u1, v1;
} MLVERTEX, *PMLVERTEX;

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

// RearViewMirro.cpp variables
extern HWND                 g_hwndApp;                   // HWND of the application
extern HINSTANCE            g_hinst;                     // HINSTANCE of the application

// Error.cpp variables
extern toutputlevel g_outputlevel;                      // Amount of detail in error messages
extern terr g_errLast;                                  // Error return code of last function

// DDUtil.cpp variables
extern LPDIRECTDRAW4        g_pdd;                       // The DirectDraw object
extern LPDIRECTDRAWSURFACE4 g_pddsPrimary;               // Primary directdraw surface
extern LPDIRECTDRAWSURFACE4 g_pddsBack;                  // Back buffer directdraw surface

// D3DUtil.cpp variables
extern LPDIRECT3DVIEWPORT3  g_pviewport;                 // Main Direct3D viewport
extern LPDIRECT3DMATERIAL3  g_pmatWhite;                 // Global white material
extern LPDIRECT3DMATERIAL3  g_pmatBlack;                 // Global black material
extern D3DMATERIALHANDLE    g_hmatWhite;                 // Global white material handle
extern D3DMATERIALHANDLE    g_hmatBlack;                 // Global black material handle
extern LPDIRECT3DDEVICE3    g_p3ddevice;                 // Main Direct3D Device
extern LPDIRECT3DLIGHT      g_rglight[MAX_LIGHTS];       // Global D3D light.
extern LPDIRECT3D3          g_pd3d;                      // Direct3D object
extern D3DMATRIX            g_matIdent;                  // Global identity matrix.
extern CAMERA               g_cam;                       // Camera data
extern BOOL                 g_fIsHardwareAccelerated;    // True if we're hardware accelerated.
extern int                  g_cLights;                   // Number of lights

// ++++ Global Functions ++++++++++++++++++++++++++++++++++++++++++++

// BasicD3DIM.cpp functions
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

// DDUtil.cpp functions
void FlipBuffers();
BOOL InitDirectDraw();
LPDIRECTDRAWSURFACE4 LoadBitmapToDDS(LPTSTR tszBitmap);
HRESULT GetSurfaceDesc(LPDDSURFACEDESC pddsurfdesc, LPDIRECTDRAWSURFACE pddsurf);
HRESULT GetSurfaceDesc(LPDDSURFACEDESC2 pddsurfdesc, LPDIRECTDRAWSURFACE4 pddsurf);

// D3DUtil.cpp functions
BOOL InitDirect3D();
BOOL AddLight(float rRed, float rGreen, float rBlue, float rX, float rY, float rZ);
LPDIRECT3DMATERIAL3 CreateMaterial(float rRed, float rGreen, float rBlue, float rAlpha, float rPower, 
                                   float rSpecR, float rSpecG, float rSpecB, 
                                   float rEmisR, float rEmisG, float rEmisB);
void SetProjectionMatrix(LPD3DMATRIX pM, float rNear, float rFar, float rFov, float rAspect);
void SetViewMatrix(LPD3DMATRIX pmatxDest, LPD3DVECTOR pvectFrom, LPD3DVECTOR pvectAt, LPD3DVECTOR pvectUp);

BOOL SetView(PCAMERA pcam);

void MultiplyVectorMatrix(LPD3DVECTOR pvectDest, LPD3DVECTOR pvectSrc, LPD3DMATRIX pmatxSrc);
void MultiplyMatrices(LPD3DMATRIX r, LPD3DMATRIX x, LPD3DMATRIX y);

// MirrorUtil.cpp functions
BOOL ReplaceRenderTarget(LPDIRECTDRAWSURFACE4 pdds, LPDIRECTDRAWSURFACE4* ppddsOld, LPD3DRECT pd3drect);
BOOL SetReflectedView(PCAMERA pcam, PMLVERTEX pvert, LPD3DMATRIX pmatWorld);
HRESULT SetReflectionTextureCoords(PMLVERTEX pvert, DWORD dwVertexCount);

// TxtrUtil.cpp functions
LPDIRECT3DTEXTURE2 LoadTexture(TCHAR *tszFileName);
LPDIRECT3DTEXTURE2 LoadAlphaTexture(TCHAR *tstrFileName);
LPDIRECT3DTEXTURE2 CreateTargetTexture(DWORD dwWidth, DWORD dwHeight);
HRESULT SetColorStage(DWORD dwStage, DWORD dwArg1, DWORD dwArg2, D3DTEXTUREOP d3dtop);
HRESULT SetAlphaStage(DWORD dwStage, DWORD dwArg1, DWORD dwArg2, D3DTEXTUREOP d3dtop);

// Error.cpp functions
BOOL CheckError(TCHAR *tszErr);
void RetailOutput(TCHAR *tszErr, ...);
#ifdef DEBUG
void DebugOutput(TCHAR *tszErr, ...);
#else
__inline void DebugOutput(TCHAR *tszErr, ...) {};
#endif
