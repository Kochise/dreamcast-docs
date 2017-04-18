/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File: directx.cpp
 *
 ***************************************************************************/

// N.B. The use of RM denotes the Direct3D retained mode objects

// The Macros TRY_DD, TRY_DS, TRY_D3D, TRY_D3DRM are defined in DirectX.h and are for
// error checking.

#define INITGUID
// Includes....
#include "directx.h"
#include "mmsystem.h"
#include "winmain.h"
#include "conio.h"

// Globals....
LPDIRECTDRAW            g_lpDD = NULL;          // DirectDraw object
LPDIRECT3D              g_lpD3D = NULL;         // Direct3D object
LPDIRECTSOUND           g_lpDS = NULL;          // DirectSound object
LPDIRECT3DRM            g_lpD3DRM = NULL;       // Direct3D RM object
DWORD                   g_dwGDIMem = 0;         // Memory in available from GDI's surface

D3DDeviceInfo           g_deviceInfo;           // 3D device info
LPGUID                  g_lpD3DDeviceGuid = NULL; // Guid to 3D device

VideoMode               g_vidModes[NUM_VID_MODES];// Array of available video modes
DWORD                   g_dwCurrMode = 0;
DWORD                   g_dwNumModes = 0;

BOOL                    g_bSoundPresent = FALSE; // Do we have sound capabilites?

LPDIRECTDRAWSURFACE     g_lpPrimary = NULL;     // Primary surface
LPDIRECTDRAWSURFACE     g_lpBackBuffer = NULL;  // BackBuffer surface
LPDIRECTDRAWSURFACE     g_lpZBuffer = NULL;     // ZBuffer
LPDIRECTDRAWPALETTE     g_lpPalette = NULL;     // Palette
PALETTEENTRY            g_rPal[768];            // Rockem3D palette

LPDIRECTDRAW            g_lpSplashDD = NULL;        // DirectDraw object used for splash screen
LPDIRECTDRAWSURFACE     g_lpSplashPrimary = NULL;   // Primary surface
LPDIRECTDRAWPALETTE     g_lpSplashPalette = NULL;   // Palette

LPDIRECT3DDEVICE        g_lpD3DDevice = NULL;   // Direct3D device
LPDIRECT3DRMDEVICE      g_lpD3DRMDevice = NULL; // Direct3D RM Device
LPDIRECT3DRMVIEWPORT    g_lpD3DRMViewport = NULL; // Direct3D RM Viewport

DDCAPS                  g_driverCaps;           // Driver capabilities
DDCAPS                  g_HELcaps;              // HEL capabilities

DWORD                   g_dwZBufferBitDepth = 16;// ZBuffer bit depth
DWORD                   g_dwZBufferMemType = DDSCAPS_SYSTEMMEMORY;// Type of ZBuffer

LPDIRECTSOUNDBUFFER     g_lpSounds[NUM_SOUNDS]; // Sound buffers
LPDIRECTSOUND3DLISTENER      g_lpDs3dListener;               // Listener object for Direct 3D Sound
LPDIRECTSOUNDBUFFER             g_3DSoundBuffer;                // Direct Sound buffer for the Listener object
LPDIRECTSOUND3DBUFFER   g_lp3dSounds[NUM_SOUNDS];//3D Sound Buffers


// State booleans
BOOL                    g_bHardware3D = FALSE;  // Do we have hardware?
BOOL			g_bOutOfVideoMemory = FALSE; // Out of video memory, fall back on software

float                   g_xratio = 0.0f;        // X ratio used for computing power bars
float                   g_yratio = 0.0f;        // Y ratio used for computing power bars

// Power bar x,y and width values
DWORD                   g_vidModeX;             // Current X video resolution
DWORD                   g_vidModeY;             // Current Y video resolution
DWORD                   g_vidModeBIT;           // Current video bit depth
DWORD                   g_dwFontHeight = 0;
DWORD                   g_dwAveCharWidth = 0;
DWORD                   g_lbar1 = 0;
DWORD                   g_wbar1 = 0;
DWORD                   g_lbar2 = 0;
DWORD                   g_wbar2 = 0;
DWORD                   g_hbar1 = 0;
DWORD                   g_hbar2 = 0;

// Externals....
extern HWND                     g_hWnd;         // Defined in WINMAIN.CPP
extern BOOL                     g_bSoundPaused; // Defined in WINMAIN.CPP
extern LPDIRECT3DRMFRAME        g_lpCamera;     // Defined in RM.CPP
extern LPDIRECT3DRMFRAME        g_lpScene;      // Defined in RM.CPP
extern LPDIRECT3DRMFRAME        g_lpPlayers;    // Defined in RM.CPP
extern LPDIRECT3DRMLIGHT        g_lpDir;        // Defined in RM.CPP

//----------------------------------------------------------------------
// 
// Function     : TraceErrorDD()
//
// Purpose      : Traces an error (DirectDraw)
//
//----------------------------------------------------------------------

void TraceErrorDD(HRESULT hErr, char *sFile, int nLine)
{       
    char dderr[256];
    char err[1024];

    switch (hErr)
    {
        case DDERR_ALREADYINITIALIZED : sprintf(dderr, "DDERR_ALREADYINITIALIZED"); break;
        case DDERR_CANNOTATTACHSURFACE : sprintf(dderr, "DDERR_CANNOTATTACHSURFACE"); break;
        case DDERR_CANNOTDETACHSURFACE : sprintf(dderr, "DDERR_CANNOTDETACHSURFACE"); break;
        case DDERR_CURRENTLYNOTAVAIL : sprintf(dderr, "DDERR_CURRENTLYNOTAVAIL"); break;
        case DDERR_EXCEPTION : sprintf(dderr, "DDERR_EXCEPTION"); break;
        case DDERR_GENERIC : sprintf(dderr, "DDERR_GENERIC"); break;
        case DDERR_HEIGHTALIGN : sprintf(dderr, "DDERR_HEIGHTALIGN"); break;
        case DDERR_INCOMPATIBLEPRIMARY : sprintf(dderr, "DDERR_INCOMPATIBLEPRIMARY"); break;
        case DDERR_INVALIDCAPS : sprintf(dderr, "DDERR_INVALIDCAPS"); break;
        case DDERR_INVALIDCLIPLIST : sprintf(dderr, "DDERR_INVALIDCLIPLIST"); break;
        case DDERR_INVALIDMODE : sprintf(dderr, "DDERR_INVALIDMODE"); break;
        case DDERR_INVALIDOBJECT : sprintf(dderr, "DDERR_INVALIDOBJECT"); break;
        case DDERR_INVALIDPARAMS : sprintf(dderr, "DDERR_INVALIDPARAMS"); break;
        case DDERR_INVALIDPIXELFORMAT : sprintf(dderr, "DDERR_INVALIDPIXELFORMAT"); break;
        case DDERR_INVALIDRECT : sprintf(dderr, "DDERR_INVALIDRECT"); break;
        case DDERR_LOCKEDSURFACES : sprintf(dderr, "DDERR_LOCKEDSURFACES"); break;
        case DDERR_NO3D : sprintf(dderr, "DDERR_NO3D"); break;
        case DDERR_NOALPHAHW : sprintf(dderr, "DDERR_NOALPHAHW"); break;
        case DDERR_NOCLIPLIST : sprintf(dderr, "DDERR_NOCLIPLIST"); break;
        case DDERR_NOCOLORCONVHW : sprintf(dderr, "DDERR_NOCOLORCONVHW"); break;
        case DDERR_NOCOOPERATIVELEVELSET : sprintf(dderr, "DDERR_NOCOOPERATIVELEVELSET"); break;
        case DDERR_NOCOLORKEY : sprintf(dderr, "DDERR_NOCOLORKEY"); break;
        case DDERR_NOCOLORKEYHW : sprintf(dderr, "DDERR_NOCOLORKEYHW"); break;
        case DDERR_NODIRECTDRAWSUPPORT : sprintf(dderr, "DDERR_NODIRECTDRAWSUPPORT"); break;
        case DDERR_NOEXCLUSIVEMODE : sprintf(dderr, "DDERR_NOEXCLUSIVEMODE"); break;
        case DDERR_NOFLIPHW : sprintf(dderr, "DDERR_NOFLIPHW"); break;
        case DDERR_NOGDI : sprintf(dderr, "DDERR_NOGDI"); break;
        case DDERR_NOMIRRORHW : sprintf(dderr, "DDERR_NOMIRRORHW"); break;
        case DDERR_NOTFOUND : sprintf(dderr, "DDERR_NOTFOUND"); break;
        case DDERR_NOOVERLAYHW : sprintf(dderr, "DDERR_NOOVERLAYHW"); break;
        case DDERR_NORASTEROPHW : sprintf(dderr, "DDERR_NORASTEROPHW"); break;
        case DDERR_NOROTATIONHW : sprintf(dderr, "DDERR_NOROTATIONHW"); break;
        case DDERR_NOSTRETCHHW : sprintf(dderr, "DDERR_NOSTRETCHHW"); break;
        case DDERR_NOT4BITCOLOR : sprintf(dderr, "DDERR_NOT4BITCOLOR"); break;
        case DDERR_NOT4BITCOLORINDEX : sprintf(dderr, "DDERR_NOT4BITCOLORINDEX"); break;
        case DDERR_NOT8BITCOLOR : sprintf(dderr, "DDERR_NOT8BITCOLOR"); break;
        case DDERR_NOTEXTUREHW : sprintf(dderr, "DDERR_NOTEXTUREHW"); break;
        case DDERR_NOVSYNCHW : sprintf(dderr, "DDERR_NOVSYNCHW"); break;
        case DDERR_NOZBUFFERHW : sprintf(dderr, "DDERR_NOZBUFFERHW"); break;
        case DDERR_NOZOVERLAYHW : sprintf(dderr, "DDERR_NOZOVERLAYHW"); break;
        case DDERR_OUTOFCAPS : sprintf(dderr, "DDERR_OUTOFCAPS"); break;
        case DDERR_OUTOFMEMORY : sprintf(dderr, "DDERR_OUTOFMEMORY"); break;
        case DDERR_OUTOFVIDEOMEMORY : sprintf(dderr, "DDERR_OUTOFVIDEOMEMORY"); break;
        case DDERR_OVERLAYCANTCLIP : sprintf(dderr, "DDERR_OVERLAYCANTCLIP"); break;
        case DDERR_OVERLAYCOLORKEYONLYONEACTIVE : sprintf(dderr, "DDERR_OVERLAYCOLORKEYONLYONEACTIVE"); break;
        case DDERR_PALETTEBUSY : sprintf(dderr, "DDERR_PALETTEBUSY"); break;
        case DDERR_COLORKEYNOTSET : sprintf(dderr, "DDERR_COLORKEYNOTSET"); break;
        case DDERR_SURFACEALREADYATTACHED : sprintf(dderr, "DDERR_SURFACEALREADYATTACHED"); break;
        case DDERR_SURFACEALREADYDEPENDENT : sprintf(dderr, "DDERR_SURFACEALREADYDEPENDENT"); break;
        case DDERR_SURFACEBUSY : sprintf(dderr, "DDERR_SURFACEBUSY"); break;
        case DDERR_CANTLOCKSURFACE : sprintf(dderr, "DDERR_CANTLOCKSURFACE"); break;
        case DDERR_SURFACEISOBSCURED : sprintf(dderr, "DDERR_SURFACEISOBSCURED"); break;
        case DDERR_SURFACELOST : sprintf(dderr, "DDERR_SURFACELOST"); break;
        case DDERR_SURFACENOTATTACHED : sprintf(dderr, "DDERR_SURFACENOTATTACHED"); break;
        case DDERR_TOOBIGHEIGHT : sprintf(dderr, "DDERR_TOOBIGHEIGHT"); break;
        case DDERR_TOOBIGSIZE : sprintf(dderr, "DDERR_TOOBIGSIZE"); break;
        case DDERR_TOOBIGWIDTH : sprintf(dderr, "DDERR_TOOBIGWIDTH"); break;
        case DDERR_UNSUPPORTED : sprintf(dderr, "DDERR_UNSUPPORTED"); break;
        case DDERR_UNSUPPORTEDFORMAT : sprintf(dderr, "DDERR_UNSUPPORTEDFORMAT"); break;
        case DDERR_UNSUPPORTEDMASK : sprintf(dderr, "DDERR_UNSUPPORTEDMASK"); break;
        case DDERR_VERTICALBLANKINPROGRESS : sprintf(dderr, "DDERR_VERTICALBLANKINPROGRESS"); break;
        case DDERR_WASSTILLDRAWING : sprintf(dderr, "DDERR_WASSTILLDRAWING"); break;
        case DDERR_XALIGN : sprintf(dderr, "DDERR_XALIGN"); break;
        case DDERR_INVALIDDIRECTDRAWGUID : sprintf(dderr, "DDERR_INVALIDDIRECTDRAWGUID"); break;
        case DDERR_DIRECTDRAWALREADYCREATED : sprintf(dderr, "DDERR_DIRECTDRAWALREADYCREATED"); break;
        case DDERR_NODIRECTDRAWHW : sprintf(dderr, "DDERR_NODIRECTDRAWHW"); break;
        case DDERR_PRIMARYSURFACEALREADYEXISTS : sprintf(dderr, "DDERR_PRIMARYSURFACEALREADYEXISTS"); break;
        case DDERR_NOEMULATION : sprintf(dderr, "DDERR_NOEMULATION"); break;
        case DDERR_REGIONTOOSMALL : sprintf(dderr, "DDERR_REGIONTOOSMALL"); break;
        case DDERR_CLIPPERISUSINGHWND : sprintf(dderr, "DDERR_CLIPPERISUSINGHWND"); break;
        case DDERR_NOCLIPPERATTACHED : sprintf(dderr, "DDERR_NOCLIPPERATTACHED"); break;
        case DDERR_NOHWND : sprintf(dderr, "DDERR_NOHWND"); break;
        case DDERR_HWNDSUBCLASSED : sprintf(dderr, "DDERR_HWNDSUBCLASSED"); break;
        case DDERR_HWNDALREADYSET : sprintf(dderr, "DDERR_HWNDALREADYSET"); break;
        case DDERR_NOPALETTEATTACHED : sprintf(dderr, "DDERR_NOPALETTEATTACHED"); break;
        case DDERR_NOPALETTEHW : sprintf(dderr, "DDERR_NOPALETTEHW"); break;
        case DDERR_BLTFASTCANTCLIP : sprintf(dderr, "DDERR_BLTFASTCANTCLIP"); break;
        case DDERR_NOBLTHW : sprintf(dderr, "DDERR_NOBLTHW"); break;
        case DDERR_NODDROPSHW : sprintf(dderr, "DDERR_NODDROPSHW"); break;
        case DDERR_OVERLAYNOTVISIBLE : sprintf(dderr, "DDERR_OVERLAYNOTVISIBLE"); break;
        case DDERR_NOOVERLAYDEST : sprintf(dderr, "DDERR_NOOVERLAYDEST"); break;
        case DDERR_INVALIDPOSITION : sprintf(dderr, "DDERR_INVALIDPOSITION"); break;
        case DDERR_NOTAOVERLAYSURFACE : sprintf(dderr, "DDERR_NOTAOVERLAYSURFACE"); break;
        case DDERR_EXCLUSIVEMODEALREADYSET : sprintf(dderr, "DDERR_EXCLUSIVEMODEALREADYSET"); break;
        case DDERR_NOTFLIPPABLE : sprintf(dderr, "DDERR_NOTFLIPPABLE"); break;
        case DDERR_CANTDUPLICATE : sprintf(dderr, "DDERR_CANTDUPLICATE"); break;
        case DDERR_NOTLOCKED : sprintf(dderr, "DDERR_NOTLOCKED"); break;
        case DDERR_CANTCREATEDC : sprintf(dderr, "DDERR_CANTCREATEDC"); break;
        case DDERR_NODC : sprintf(dderr, "DDERR_NODC"); break;
        case DDERR_WRONGMODE : sprintf(dderr, "DDERR_WRONGMODE"); break;
        case DDERR_IMPLICITLYCREATED : sprintf(dderr, "DDERR_IMPLICITLYCREATED"); break;
        case DDERR_NOTPALETTIZED : sprintf(dderr, "DDERR_NOTPALETTIZED"); break;
        case DDERR_UNSUPPORTEDMODE : sprintf(dderr, "DDERR_UNSUPPORTEDMODE"); break;
        case DDERR_NOMIPMAPHW : sprintf(dderr, "DDERR_NOMIPMAPHW"); break;
        case DDERR_INVALIDSURFACETYPE : sprintf(dderr, "DDERR_INVALIDSURFACETYPE"); break;
        case DDERR_DCALREADYCREATED : sprintf(dderr, "DDERR_DCALREADYCREATED"); break;
        case DDERR_CANTPAGELOCK : sprintf(dderr, "DDERR_CANTPAGELOCK"); break;
        case DDERR_CANTPAGEUNLOCK : sprintf(dderr, "DDERR_CANTPAGEUNLOCK"); break;
        case DDERR_NOTPAGELOCKED : sprintf(dderr, "DDERR_NOTPAGELOCKED"); break;
        case DDERR_NOTINITIALIZED : sprintf(dderr, "DDERR_NOTINITIALIZED"); break;

        default : sprintf(dderr, "Unknown Error"); break;
    }
    sprintf(err, "DirectDraw Error %s\nin file %s at line %d", dderr, sFile, nLine);
    RegError(err);
}

//----------------------------------------------------------------------
// 
// Function     : TraceErrorDS()
//
// Purpose      : Traces an error (DirectSound)
//
//----------------------------------------------------------------------

void TraceErrorDS(HRESULT hErr, char *sFile, int nLine)
{       
    char dserr[256];
    char err[1024];

    switch (hErr)
    {
        case DSERR_ALLOCATED : sprintf(dserr, "DSERR_ALLOCATED"); break;
        case DSERR_CONTROLUNAVAIL : sprintf(dserr, "DSERR_CONTROLUNAVAIL"); break;
        case DSERR_INVALIDPARAM : sprintf(dserr, "DSERR_INVALIDPARAM"); break;
        case DSERR_INVALIDCALL : sprintf(dserr, "DSERR_INVALIDCALL"); break;
        case DSERR_GENERIC : sprintf(dserr, "DSERR_GENERIC"); break;
        case DSERR_PRIOLEVELNEEDED : sprintf(dserr, "DSERR_PRIOLEVELNEEDED"); break;
        case DSERR_OUTOFMEMORY : sprintf(dserr, "DSERR_OUTOFMEMORY"); break;
        case DSERR_BADFORMAT : sprintf(dserr, "DSERR_BADFORMAT"); break;
        case DSERR_UNSUPPORTED : sprintf(dserr, "DSERR_UNSUPPORTED"); break;
        case DSERR_NODRIVER : sprintf(dserr, "DSERR_NODRIVER"); break;
        case DSERR_ALREADYINITIALIZED : sprintf(dserr, "DSERR_ALREADYINITIALIZED"); break;
        case DSERR_NOAGGREGATION : sprintf(dserr, "DSERR_NOAGGREGATION"); break;
        case DSERR_BUFFERLOST : sprintf(dserr, "DSERR_BUFFERLOST"); break;
        case DSERR_OTHERAPPHASPRIO : sprintf(dserr, "DSERR_OTHERAPPHASPRIO"); break;
        case DSERR_UNINITIALIZED : sprintf(dserr, "DSERR_UNINITIALIZED"); break;

        default : sprintf(dserr, "Unknown Error"); break;
    }
    sprintf(err, "DirectSound Error %s\nin file %s at line %d", dserr, sFile, nLine);
    RegError(err);
}

//----------------------------------------------------------------------
// 
// Function     : TraceErrorD3D()
//
// Purpose      : Traces an error (Direct3D)
//
//----------------------------------------------------------------------

void TraceErrorD3D(HRESULT hErr, char *sFile, int nLine)
{       
    char d3derr[256];
    char err[1024];

    switch (hErr)
    {
        case D3DERR_BADMAJORVERSION : sprintf(d3derr, "D3DERR_BADMAJORVERSION"); break;
        case D3DERR_BADMINORVERSION : sprintf(d3derr, "D3DERR_BADMINORVERSION"); break;
        case D3DERR_EXECUTE_CREATE_FAILED : sprintf(d3derr, "D3DERR_EXECUTE_CREATE_FAILED"); break;
        case D3DERR_EXECUTE_DESTROY_FAILED : sprintf(d3derr, "D3DERR_EXECUTE_DESTROY_FAILED"); break;
        case D3DERR_EXECUTE_LOCK_FAILED : sprintf(d3derr, "D3DERR_EXECUTE_LOCK_FAILED"); break;
        case D3DERR_EXECUTE_UNLOCK_FAILED : sprintf(d3derr, "D3DERR_EXECUTE_UNLOCK_FAILED"); break;
        case D3DERR_EXECUTE_LOCKED : sprintf(d3derr, "D3DERR_EXECUTE_LOCKED"); break;
        case D3DERR_EXECUTE_NOT_LOCKED : sprintf(d3derr, "D3DERR_EXECUTE_NOT_LOCKED"); break;
        case D3DERR_EXECUTE_FAILED : sprintf(d3derr, "D3DERR_EXECUTE_FAILED"); break;
        case D3DERR_EXECUTE_CLIPPED_FAILED : sprintf(d3derr, "D3DERR_EXECUTE_CLIPPED_FAILED"); break;
        case D3DERR_TEXTURE_NO_SUPPORT : sprintf(d3derr, "D3DERR_TEXTURE_NO_SUPPORT"); break;
        case D3DERR_TEXTURE_CREATE_FAILED : sprintf(d3derr, "D3DERR_TEXTURE_CREATE_FAILED"); break;
        case D3DERR_TEXTURE_DESTROY_FAILED : sprintf(d3derr, "D3DERR_TEXTURE_DESTROY_FAILED"); break;
        case D3DERR_TEXTURE_LOCK_FAILED : sprintf(d3derr, "D3DERR_TEXTURE_LOCK_FAILED"); break;
        case D3DERR_TEXTURE_UNLOCK_FAILED : sprintf(d3derr, "D3DERR_TEXTURE_UNLOCK_FAILED"); break;
        case D3DERR_TEXTURE_LOAD_FAILED : sprintf(d3derr, "D3DERR_TEXTURE_LOAD_FAILED"); break;
        case D3DERR_TEXTURE_SWAP_FAILED : sprintf(d3derr, "D3DERR_TEXTURE_SWAP_FAILED"); break;
        case D3DERR_TEXTURE_LOCKED : sprintf(d3derr, "D3DERR_TEXTURE_LOCKED"); break;
        case D3DERR_TEXTURE_NOT_LOCKED : sprintf(d3derr, "D3DERR_TEXTURE_NOT_LOCKED"); break;
        case D3DERR_TEXTURE_GETSURF_FAILED : sprintf(d3derr, "D3DERR_TEXTURE_GETSURF_FAILED"); break;
        case D3DERR_MATRIX_CREATE_FAILED : sprintf(d3derr, "D3DERR_MATRIX_CREATE_FAILED"); break;
        case D3DERR_MATRIX_DESTROY_FAILED : sprintf(d3derr, "D3DERR_MATRIX_DESTROY_FAILED"); break;
        case D3DERR_MATRIX_SETDATA_FAILED : sprintf(d3derr, "D3DERR_MATRIX_SETDATA_FAILED"); break;
        case D3DERR_MATRIX_GETDATA_FAILED : sprintf(d3derr, "D3DERR_MATRIX_GETDATA_FAILED"); break;
        case D3DERR_SETVIEWPORTDATA_FAILED : sprintf(d3derr, "D3DERR_SETVIEWPORTDATA_FAILED"); break;
        case D3DERR_MATERIAL_CREATE_FAILED : sprintf(d3derr, "D3DERR_MATERIAL_CREATE_FAILED"); break;
        case D3DERR_MATERIAL_DESTROY_FAILED : sprintf(d3derr, "D3DERR_MATERIAL_DESTROY_FAILED"); break;
        case D3DERR_MATERIAL_SETDATA_FAILED : sprintf(d3derr, "D3DERR_MATERIAL_SETDATA_FAILED"); break;
        case D3DERR_MATERIAL_GETDATA_FAILED : sprintf(d3derr, "D3DERR_MATERIAL_GETDATA_FAILED"); break;
        case D3DERR_LIGHT_SET_FAILED : sprintf(d3derr, "D3DERR_LIGHT_SET_FAILED"); break;
        case D3DERR_SCENE_IN_SCENE : sprintf(d3derr, "D3DERR_SCENE_IN_SCENE"); break;
        case D3DERR_SCENE_NOT_IN_SCENE : sprintf(d3derr, "D3DERR_SCENE_NOT_IN_SCENE"); break;
        case D3DERR_SCENE_BEGIN_FAILED : sprintf(d3derr, "D3DERR_SCENE_BEGIN_FAILED"); break;
        case D3DERR_SCENE_END_FAILED : sprintf(d3derr, "D3DERR_SCENE_END_FAILED"); break;

        default : sprintf(d3derr, "Unknown Error"); break;
    }
    sprintf(err, "Direct3D Error %s\nin file %s at line %d", d3derr, sFile, nLine);
    RegError(err);
}

//----------------------------------------------------------------------
// 
// Function     : TraceErrorD3DRM()
//
// Purpose      : Traces an error (Direct3D retained mode)
//
//----------------------------------------------------------------------

void TraceErrorD3DRM(HRESULT hErr, char *sFile, int nLine)
{       
    char d3drmerr[256];
    char err[1024];

    switch (hErr)
    {
        case D3DRMERR_BADOBJECT : sprintf(d3drmerr, "D3DRMERR_BADOBJECT"); break;
        case D3DRMERR_BADTYPE : sprintf(d3drmerr, "D3DRMERR_BADTYPE"); break;
        case D3DRMERR_BADALLOC : sprintf(d3drmerr, "D3DRMERR_BADALLOC"); break;
        case D3DRMERR_FACEUSED : sprintf(d3drmerr, "D3DRMERR_FACEUSED"); break;
        case D3DRMERR_NOTFOUND : sprintf(d3drmerr, "D3DRMERR_NOTFOUND"); break;
        case D3DRMERR_NOTDONEYET : sprintf(d3drmerr, "D3DRMERR_NOTDONEYET"); break;
        case D3DRMERR_FILENOTFOUND : sprintf(d3drmerr, "D3DRMERR_FILENOTFOUND"); break;
        case D3DRMERR_BADFILE : sprintf(d3drmerr, "D3DRMERR_BADFILE"); break;
        case D3DRMERR_BADDEVICE : sprintf(d3drmerr, "D3DRMERR_BADDEVICE"); break;
        case D3DRMERR_BADVALUE : sprintf(d3drmerr, "D3DRMERR_BADVALUE"); break;
        case D3DRMERR_BADMAJORVERSION : sprintf(d3drmerr, "D3DRMERR_BADMAJORVERSION"); break;
        case D3DRMERR_BADMINORVERSION : sprintf(d3drmerr, "D3DRMERR_BADMINORVERSION"); break;
        case D3DRMERR_UNABLETOEXECUTE : sprintf(d3drmerr, "D3DRMERR_UNABLETOEXECUTE"); break;

        default : sprintf(d3drmerr, "Unknown Error"); break;
    }
    sprintf(err, "Direct3D-RM Error : %s\nin file %s at line %d", d3drmerr, sFile, nLine);
    RegError(err);
}

//----------------------------------------------------------------------
// 
// Function     : SortDisplayModes()
//
// Purpose      : Sorts the list of display modes
//
//----------------------------------------------------------------------

void SortDisplayModes()
{
    // Sort by width * height
    for (DWORD i = 0; i < g_dwNumModes; i ++)
    {
        for (DWORD k = 0; k < g_dwNumModes - 1; k ++)
        {
            int c1 = g_vidModes[k].width * g_vidModes[k].height;
            int c2 = g_vidModes[k + 1].width * g_vidModes[k + 1].height;

            if (c1 > c2)
            {
                VideoMode tmp;
                
                // Swap the two video modes
                tmp                     = g_vidModes[k];
                g_vidModes[k]           = g_vidModes[k + 1];
                g_vidModes[k + 1]       = tmp;

                // Keep g_dwCurrMode up to date
                if (g_dwCurrMode == k)
                {
                    g_dwCurrMode = k + 1;
                }
                else if (g_dwCurrMode == k + 1)
                {
                    g_dwCurrMode = k;
                }
            }
        }
    }
}

//----------------------------------------------------------------------
// 
// Function     : DDEnumCallBack()
//
// Purpose      : Call back to enumerate installed DirectDraw devices
//
//----------------------------------------------------------------------

BOOL FAR PASCAL DDEnumCallback(GUID FAR* lpGUID, LPSTR lpDriverDesc, LPSTR lpDriverName, LPVOID lpContext)
{
    LPDIRECTDRAW lpDD;
    DDCAPS DriverCaps, HELCaps;

        // Make sure the guid is valid
    if (lpGUID) 
    {
        // Try to create a DirectDraw object
        TRY_DD(DirectDrawCreate(lpGUID, &lpDD, NULL))
        
        // Get the DirectDraw capabilities
        memset(&DriverCaps, 0, sizeof(DDCAPS));
        DriverCaps.dwSize = sizeof(DDCAPS);
        
        memset(&HELCaps, 0, sizeof(DDCAPS));
        HELCaps.dwSize = sizeof(DDCAPS);
        
        TRY_DD(lpDD->GetCaps(&DriverCaps, &HELCaps))

        // Does this driver have 3D hardware capabilites?
        if (DriverCaps.dwCaps & DDCAPS_3D) 
        {
            *(LPDIRECTDRAW*)lpContext = lpDD;
            return DDENUMRET_CANCEL;
        }

        *(LPDIRECTDRAW*)lpContext = NULL;
        lpDD->Release();
    }

        // Yahoo!
    return DDENUMRET_OK;
}

//----------------------------------------------------------------------
// 
// Function     : DDEnumDisplayModesCallBack()
//
// Purpose      : Call back function to receive display mode information
//
//----------------------------------------------------------------------

HRESULT CALLBACK DDEnumDisplayModesCallback(LPDDSURFACEDESC pddsd, LPVOID Context)
{       
    // While each mode gets enumerated we have to decide whether 
    // the 3D device and mode are compatible
    if (g_deviceInfo.lpHWGuid)
    {           
        // Make sure there is enough video ram to support this mode
        //if hardware is in use
        DWORD dwBitDepthMultiplier;
        
        switch(pddsd->ddpfPixelFormat.dwRGBBitCount)
        {
            case 8  : dwBitDepthMultiplier = 1; break;
            case 16 : dwBitDepthMultiplier = 2; break;
            case 24 : dwBitDepthMultiplier = 3; break;
            case 32 : dwBitDepthMultiplier = 4; break;
        }

        DWORD dwVidRamNeeded = ((pddsd->dwWidth * pddsd->dwHeight) * dwBitDepthMultiplier) * 3;

        if (dwVidRamNeeded > (g_driverCaps.dwVidMemFree + g_dwGDIMem))
          return DDENUMRET_OK;

        // Make sure the Direct3D device can render at a given bit depth
        switch (pddsd->ddpfPixelFormat.dwRGBBitCount)
        {
            case 8 : 
            {
                if (!(g_deviceInfo.HWDeviceDesc.dwDeviceRenderBitDepth & DDBD_8)) return DDENUMRET_OK;
            }
            break;

            case 16 :
            {
                if (!(g_deviceInfo.HWDeviceDesc.dwDeviceRenderBitDepth & DDBD_16)) return DDENUMRET_OK;
            }
            break;

            case 24 : 
            {
                if (!(g_deviceInfo.HWDeviceDesc.dwDeviceRenderBitDepth & DDBD_24)) return DDENUMRET_OK;
            }
            break;

            case 32 :
            {
                if (!(g_deviceInfo.HWDeviceDesc.dwDeviceRenderBitDepth & DDBD_32)) return DDENUMRET_OK;
            }
            break;
        }

        // If we have hardware, start up in 640x480x16 if possible
        if ((pddsd->dwWidth == 640) && (pddsd->dwHeight == 480) && (pddsd->ddpfPixelFormat.dwRGBBitCount == 16))
        {
            g_dwCurrMode = g_dwNumModes;
        }
    }

    // Record the video mode information
    g_vidModes[g_dwNumModes].width  = pddsd->dwWidth;
    g_vidModes[g_dwNumModes].height = pddsd->dwHeight;
    g_vidModes[g_dwNumModes].bpp    = pddsd->ddpfPixelFormat.dwRGBBitCount;
    
    g_dwNumModes ++;
            
    return DDENUMRET_OK;
}

//------------------------------------------------------------------
// 
// Function     : D3DEnumDriverCallBack()
//
// Purpose      : Enumeration Function
//
//------------------------------------------------------------------

HRESULT WINAPI D3DEnumDeviceCallBack(LPGUID lpGuid,     
                                     LPSTR lpDeviceDescription,
                                     LPSTR lpDeviceName,
                                     LPD3DDEVICEDESC lpHWDesc, 
                                     LPD3DDEVICEDESC lpHELDesc, 
                                     LPVOID lpContext)
{
    static BOOL bFoundHardwareDevice = FALSE;   

    // No need to enumerate if we already found the device that supports
    if (bFoundHardwareDevice) return D3DENUMRET_OK;

    D3DDeviceInfo* pInfo = (D3DDeviceInfo *)lpContext;
    
    // Is this a hardware device?
    if (lpHWDesc->dcmColorModel & pInfo->cm)
    {
        // Driver needs to pass some tests....

        // Make sure the driver has ZBuffering capabilities
        if ((lpHWDesc->dwDeviceZBufferBitDepth & DDBD_16) || 
            (lpHWDesc->dwDeviceZBufferBitDepth & DDBD_24) ||
            (lpHWDesc->dwDeviceZBufferBitDepth & DDBD_32))
        {                                       
            // Record the HAL description for later use
            memcpy(&pInfo->HWDeviceDesc, lpHWDesc, sizeof(D3DDEVICEDESC));

            // Record the guid for later use
            pInfo->lpHWGuid = lpGuid;
            
            // No need to keep looking for any more devices
            bFoundHardwareDevice = TRUE;
        }
        
        // Yahoo!
        return D3DENUMRET_OK;
    }

    // Is this a software device?
    if (lpHELDesc->dcmColorModel & pInfo->cm) 
    {
        // Record the HEL description for later use
        memcpy(&pInfo->SWDeviceDesc, lpHELDesc, sizeof(D3DDEVICEDESC));
            
        // Record the guid for later use
        pInfo->lpSWGuid = lpGuid;
            
        g_lpD3DDeviceGuid = lpGuid;
    }

    return D3DENUMRET_OK;
}

//----------------------------------------------------------------------
// 
// Function     : InitD3DDevice()
//
// Purpose      : Performs initialisation for correct Direct3D device
//                        RGB, MONO, HAL etc
//
//----------------------------------------------------------------------

BOOL InitD3DDevice()
{
    memset(&g_deviceInfo, 0, sizeof(D3DDeviceInfo));

    // Use RGB colour if in hardware, RAMP if in software       

    // Record the colour model that we wish to search for in the structure passed
    // to the enumeration call back
    g_deviceInfo.cm = g_bHardware3D ? D3DCOLOR_RGB : D3DCOLOR_MONO;;
    
    // Enumerate the drivers
    TRY_D3D(g_lpD3D->EnumDevices(D3DEnumDeviceCallBack, &g_deviceInfo)) 

    // Test to see whether we have hardware or software
    if (g_deviceInfo.lpHWGuid)
    {
        // We have a hardware driver!

        // Use a video memory based ZBuffer
        g_dwZBufferMemType = DDSCAPS_VIDEOMEMORY;

        // Use 16 bit ZBuffering if possible, higher if not
        if (g_deviceInfo.HWDeviceDesc.dwDeviceZBufferBitDepth & DDBD_16)
        {
            g_dwZBufferBitDepth = 16;
        }
        else if (g_deviceInfo.HWDeviceDesc.dwDeviceZBufferBitDepth & DDBD_24)
        {
            g_dwZBufferBitDepth = 24;
        }
        else if (g_deviceInfo.HWDeviceDesc.dwDeviceZBufferBitDepth & DDBD_32)
        {
            g_dwZBufferBitDepth = 32;
        }
        else
        {
            g_dwZBufferBitDepth = 0;
        }
        
        // Use Hardware device
        g_lpD3DDeviceGuid = g_deviceInfo.lpHWGuid;
    }
    else
    {
        // We have a software driver!

        // Use a system memory based ZBuffer
        g_dwZBufferMemType = DDSCAPS_SYSTEMMEMORY;

        // And force the bit depth to 16
        g_dwZBufferBitDepth = 16;

        // Default to the software device
        g_lpD3DDeviceGuid = g_deviceInfo.lpSWGuid;
    }

    // Yahoo!
    return TRUE;
}

//----------------------------------------------------------------------
// 
// Function     : InitDirectX()
//
// Purpose      : Initialises DirectX (DirectDraw, Direct3D, Direct3DRM, DirectSound)
//
//----------------------------------------------------------------------

BOOL InitDirectX()
{
    FILE        *fp;
    BYTE        pal[768];
    HRESULT     rval;
    DDSURFACEDESC ddsd;

    // Enumerate DirectDraw drivers to see what is installed, preferring one with
    // Hardware 3D capabilities
    TRY_DD(DirectDrawEnumerate(DDEnumCallback, &g_lpDD))

    // If g_lpDD is NULL, there isn't a DirectDraw device with hardware 3D capabilities,
    // so create a device using the HEL 
    if (!g_lpDD)
    {
            TRY_DD(DirectDrawCreate(NULL, &g_lpDD, NULL))
    }

    // NOTE : Exclusive mode would normally be set here but because of the splash
    // screen being displayed it isn't. The reason is that the splash screen uses
    // 640x480x8 and that mode may not be available if we are using a hardware 3D
    // DirectDraw device.

    // Zero out caps structures
    memset(&g_driverCaps, 0, sizeof(DDCAPS));
    g_driverCaps.dwSize = sizeof(DDCAPS);

    memset(&g_HELcaps, 0, sizeof(DDCAPS));
    g_HELcaps.dwSize = sizeof(DDCAPS);

    // Get the current display mode as we can use that memory when full
    // screen exclusive
    memset(&ddsd, 0, sizeof ddsd);
    ddsd.dwSize = sizeof ddsd;
    TRY_DD(g_lpDD->GetDisplayMode(&ddsd));
    g_dwGDIMem = ddsd.lPitch * ddsd.dwHeight *
      (ddsd.ddpfPixelFormat.dwRGBBitCount / 8);

    // Get hardware capabilities
    TRY_DD(g_lpDD->GetCaps(&g_driverCaps, &g_HELcaps));

    // Global to determine whether we have hardware 3D capabilities or not
    g_bHardware3D = g_driverCaps.dwCaps & DDCAPS_3D;

    // Create Direct3D object
    TRY_D3D(g_lpDD->QueryInterface(IID_IDirect3D, (LPVOID *)&g_lpD3D));

    // Enumerate Direct3D devices, preferring hardware rendering over software
    if (!InitD3DDevice())
    {
            RegError("Error locating suitable Direct3D driver!");
            return FALSE;
    }

    // Enumerate all the display modes, this is done after locating the 3D device so
    // that any mode that is not compatible with the 3D device does not get added to
    // the list of valid modes.
    TRY_DD(g_lpDD->EnumDisplayModes(0, NULL, NULL, DDEnumDisplayModesCallback))

    // Sort display modes into lowest width * height first
    SortDisplayModes();

    // Create Direct3D RM object
    TRY_D3DRM(Direct3DRMCreate(&g_lpD3DRM))

    // Set default amount of texture colours
    g_lpD3DRM->SetDefaultTextureColors(16);
    
    // Set default amount of texture shades
    g_lpD3DRM->SetDefaultTextureShades(16);

    // Create DirectSound object
    rval = DirectSoundCreate(NULL, &g_lpDS, NULL);
    
    // Determine whether sound is present
    g_bSoundPresent = rval == DS_OK ? TRUE : FALSE;

    if (g_bSoundPresent)
    {
        // Set the DirectSound cooperative level
        TRY_DS(g_lpDS->SetCooperativeLevel(g_hWnd, DSSCL_NORMAL))

                // Create the Direct 3D Sound Buffer
                g_3DSoundBuffer = CreateSoundBuffer3D();
                if(g_3DSoundBuffer == NULL)
                {
                        RegError("Not able to create Direct 3D Sound Buffer");
            return FALSE;
                }
                // Query interface for Direct 3D Sound Listener object
                if(DS_OK != g_3DSoundBuffer->QueryInterface(IID_IDirectSound3DListener, (void**)&g_lpDs3dListener))
                {
                        RegError("Not able to create Direct 3D Sound Listener object");
            return FALSE;
                }
                // Set the Direct 3D Sound Rolloff Factor
                g_lpDs3dListener->SetRolloffFactor((FLOAT).01,DS3D_DEFERRED);
                // Change listener's orientation
                g_lpDs3dListener->SetOrientation(-D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(0),DS3D_DEFERRED);
                // Commit the changes to Rolloff Factor and orientation
                g_lpDs3dListener->CommitDeferredSettings();

        // Null out all the sound pointers
        for (int i = 0; i < NUM_SOUNDS; i ++)
        {
            g_lpSounds[i] = NULL;
        }

        // Load the sounds      
        if (!CreateBufferFromWaveFile("INTRO.WAV", INTRO))
        {
            RegError("Couldn't load INTRO.WAV!");
            return FALSE;
        }
        
        if (!CreateBufferFromWaveFile("PUNCH1.WAV", PLAYER1_PUNCH1))
        {
            RegError("Couldn't load PUNCH1.WAV!");
            return FALSE;
        }
        
        if (!CreateBufferFromWaveFile("PUNCH3.WAV", PLAYER1_PUNCH2))
        {
            RegError("Couldn't load PUNCH3.WAV!");
            return FALSE;
        }
        
        if (!CreateBufferFromWaveFile("PUNCH2.WAV", PLAYER2_PUNCH1))
        {
            RegError("Couldn't load PUNCH2.WAV!");
            return FALSE;
        }

        if (!CreateBufferFromWaveFile("PUNCH4.WAV", PLAYER2_PUNCH2))    
        {
            RegError("Couldn't load PUNCH4.WAV!");
            return FALSE;
        }
        
        if (!CreateBufferFromWaveFile("WALK0.WAV", PLAYER1_WALK))
        {
            RegError("Couldn't load WALK0.WAV!");
            return FALSE;
        }

        if (!CreateBufferFromWaveFile("WALK1.WAV", PLAYER2_WALK))
        {
            RegError("Couldn't load WALK1.WAV!");
            return FALSE;
        }

        if (!CreateBufferFromWaveFile("WHOOSH1.WAV", WHOOSH1))  
        {
            RegError("Couldn't load WHOOSH1.WAV!");
            return FALSE;
        }
        
        if (!CreateBufferFromWaveFile("WHOOSH2.WAV", WHOOSH2))
        {
            RegError("Couldn't load WHOOSH2.WAV!");
            return FALSE;
        }

        if (!CreateBufferFromWaveFile("DEFEND1.WAV", PLAYER1_OUCH))
        {
            RegError("Couldn't load DEFEND1.WAV!");
            return FALSE;
        }

        if (!CreateBufferFromWaveFile("DEFEND2.WAV", PLAYER2_OUCH))
        {
            RegError("Couldn't load DEFEND2.WAV!");
            return FALSE;
        }
        
        if (!CreateBufferFromWaveFile("HEAD.WAV", HEAD_SPRING))
        {
            RegError("Couldn't load HEAD.WAV!");
            return FALSE;
        }

        if (!CreateBufferFromWaveFile("BLOCK1.WAV", BLOCK1))
        {
            RegError("Couldn't load BLOCK1.WAV!");
            return FALSE;
        }

        if (!CreateBufferFromWaveFile("BLOCK2.WAV", BLOCK2))
        {
            RegError("Couldn't load BLOCK2.WAV!");
            return FALSE;
        }
        
        if (!CreateBufferFromWaveFile("BLOCK3.WAV", BLOCK3))
        {
            RegError("Couldn't load BLOCK3.WAV!");
            return FALSE;
        }
        
        if (!CreateBufferFromWaveFile("CLOOP.WAV", CROWD_LOOP))
        {
            RegError("Couldn't load CLOOP.WAV!");
            return FALSE;
        }
        
        if (!CreateBufferFromWaveFile("CBOO.WAV", VICTORY_BOO))
        {
            RegError("Couldn't load CBOO.WAV!");
            return FALSE;
        }
        
        if (!CreateBufferFromWaveFile("CYEAH.WAV", VICTORY_YEAH))
        {
            RegError("Couldn't load CYEAH.WAV!");
            return FALSE;
        }

        if (!CreateBufferFromWaveFile("REVUP1.WAV", SERVO_UP_1))
        {
            RegError("Couldn't load REVUP1.WAV!");
            return FALSE;
        }
        
        if (!CreateBufferFromWaveFile("REVUP2.WAV", SERVO_UP_2))
        {
            RegError("Couldn't load REVUP2.WAV!");
            return FALSE;
        }
        
        if (!CreateBufferFromWaveFile("REVUP3.WAV", SERVO_UP_3))
        {
            RegError("Couldn't load REVUP3.WAV!");
            return FALSE;
        }
        
        if (!CreateBufferFromWaveFile("REVDN1.WAV", SERVO_DOWN_1))
        {
            RegError("Couldn't load REVDOWN1.WAV!");
            return FALSE;
        }
        
        if (!CreateBufferFromWaveFile("REVDN2.WAV", SERVO_DOWN_2))
        {
            RegError("Couldn't load REVDOWN2.WAV!");
            return FALSE;
        }
        
        if (!CreateBufferFromWaveFile("REVDN3.WAV", SERVO_DOWN_3))
        {
            RegError("Couldn't load REVDOWN3.WAV!");
            return FALSE;
        }
                if (!CreateBufferFromWaveFile("RANDOM1.WAV", RANDOM1))
        {
            RegError("Couldn't load RANDOM1.WAV!");
            return FALSE;
        }
                if (!CreateBufferFromWaveFile("RANDOM2.WAV", RANDOM2))
        {
            RegError("Couldn't load RANDOM2.WAV!");
            return FALSE;
        }
                if (!CreateBufferFromWaveFile("RANDOM3.WAV", RANDOM3))
        {
            RegError("Couldn't load RANDOM3.WAV!");
            return FALSE;
        }
                if (!CreateBufferFromWaveFile("RANDOM4.WAV", RANDOM4))
        {
            RegError("Couldn't load RANDOM4.WAV!");
            return FALSE;
        }
                if (!CreateBufferFromWaveFile("RANDOM5.WAV", RANDOM5))
        {
            RegError("Couldn't load RANDOM5.WAV!");
            return FALSE;
        }
                if (!CreateBufferFromWaveFile("RANDOM6.WAV", RANDOM6))
        {
            RegError("Couldn't load RANDOM6.WAV!");
            return FALSE;
        }
    }
                            
    // Load Rockem3D's palette
    fp = fopen("ROCKEM3D.PAL", "rb");
    if (!fp)
    {
        RegError("Couldn't load ROCKEM3D.PAL!");
        return FALSE;
    }

    // Read in the raw rgb's
    fread(pal, 768, 1, fp);
    
    // Close the file
    fclose(fp); 
            
    // Set up palette 
    g_rPal[0].peFlags   = D3DPAL_READONLY;
    g_rPal[253].peFlags = D3DPAL_READONLY;
    g_rPal[254].peFlags = D3DPAL_READONLY;
    g_rPal[255].peFlags = D3DPAL_READONLY;
    
    for (int i = 1; i < 253; i++)
    {
        g_rPal[i].peRed   = pal[i * 3];
        g_rPal[i].peGreen = pal[(i * 3) + 1];
        g_rPal[i].peBlue  = pal[(i * 3) + 2];                   
        g_rPal[i].peFlags = D3DPAL_READONLY;
    }
    
    // Set the entries 253 and 254 to a colour for the power bars
    g_rPal[253].peRed   = 0;
    g_rPal[253].peGreen = 0;
    g_rPal[253].peBlue  = 255;

    g_rPal[254].peRed   = 255;
    g_rPal[254].peGreen = 0;
    g_rPal[254].peBlue  = 0;

    // Yahoo!
    return TRUE;
}

//----------------------------------------------------------------------
// 
// Function     : SetDirectDrawExclusiveMode()
//
// Purpose      : Sets exclusive mode for DirectDraw
//
//----------------------------------------------------------------------

BOOL SetDirectDrawExclusiveMode()
{
    TRY_DD(g_lpDD->SetCooperativeLevel(g_hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX))

    // Yahoo!
    return TRUE;
}


//----------------------------------------------------------------------
// 
// Function     : TermDirectX()
//
// Purpose      : Destroys all the DirectX objects
//
//----------------------------------------------------------------------

void TermDirectX()
{
    // Destroy everything in the reverse order in which they were created
        int i;

    // Destroy rendering device
    if (g_lpD3DDevice)
    {
        g_lpD3DDevice->Release();
        g_lpD3DDevice = NULL;
    }

    // Destroy all surfaces
    if (g_lpZBuffer)
    {
        g_lpZBuffer->Release();
        g_lpZBuffer = NULL;
    }

    if (g_lpBackBuffer)
    {
        g_lpBackBuffer->Release();
        g_lpBackBuffer = NULL;
    }

    if (g_lpPrimary)
    {
        g_lpPrimary->Release();
        g_lpPrimary = NULL;
    }

    // Restore the original video mode  
    if(g_lpDD)
        g_lpDD->RestoreDisplayMode();

    // Destroy sounds
    for (i = 0; i < NUM_SOUNDS; i ++)
    {
        if (g_lpSounds[i])
        {       
            g_lpSounds[i]->Release();
            g_lpSounds[i] = NULL;
        }
    }

        // Destroy DirectSound3D buffers
    for (i = 0; i < NUM_SOUNDS; i ++)
    {
        if (g_lp3dSounds[i])
        {       
            g_lp3dSounds[i]->Release();
            g_lp3dSounds[i] = NULL;
        }
    }
        
        // Destroy DirectSound3D Listener object
    if (g_lpDs3dListener)
    {
        g_lpDs3dListener->Release();
        g_lpDs3dListener = NULL;
    }
        // Destroy DirectSound3D Primary buffer
    if (g_3DSoundBuffer)
    {
        g_3DSoundBuffer->Release();
        g_3DSoundBuffer = NULL;
    } 

    // Destroy DirectSound object
    if (g_lpDS)
    {
        g_lpDS->Release();
        g_lpDS = NULL;
    }
    
    // Destroy Direct3D RM object
    if (g_lpD3DRM)
    {
        g_lpD3DRM->Release();
        g_lpD3DRM = NULL;
    }

    // Destroy Direct3D object
    if (g_lpD3D)
    {
        g_lpD3D->Release();
        g_lpD3D = NULL;
    }

    // Destroy DirectDraw object
    if (g_lpDD)
    {
        g_lpDD->Release();
        g_lpDD = NULL;
    }
}

//----------------------------------------------------------------------
// 
// Function     : SoftwareGUID();
//
// Purpose      : Returns a pointer to a software driver GUID
//
//----------------------------------------------------------------------
HRESULT SoftwareGUID(LPGUID* ret_guid)
{
    static D3DFINDDEVICERESULT result;
    D3DFINDDEVICESEARCH search;
    HRESULT err;
    
    memset(&search, 0, sizeof search);
    search.dwSize = sizeof search;
    search.dwFlags = D3DFDS_HARDWARE | D3DFDS_COLORMODEL;
    search.bHardware = FALSE;
    search.dcmColorModel = D3DCOLOR_RGB;
    result.dwSize = sizeof(D3DFINDDEVICERESULT);

    if (err = g_lpD3D->FindDevice(&search, &result))
	return err;
    *ret_guid = &result.guid;
    return D3D_OK;
}


//----------------------------------------------------------------------
// 
// Function     : EnterVideoMode()
//
// Purpose      : Calls EnterVideoModeWHBD with mode information
//
//----------------------------------------------------------------------

BOOL EnterVideoMode(int mode)
{
    int width    = g_vidModes[mode].width;
    int height   = g_vidModes[mode].height;
    int bitdepth = g_vidModes[mode].bpp;
    g_dwCurrMode = mode;

    // Try to enter video mode described by width, height and bitdepth
    return EnterVideoModeWHBD(width, height, bitdepth);
}

//----------------------------------------------------------------------
// 
// Function     : EnterVideoModeWHBD()
//
// Purpose      : Switches video mode and creates all neccessary structures
//                        required for rendering
//
//----------------------------------------------------------------------

BOOL EnterVideoModeWHBD(int width, int height, int bitdepth)
{
    DDSURFACEDESC ddsd;
    DDSCAPS ddscaps;

    // Destroy all existing viewports, devices and surfaces     
    
    // Destroy Direct3D RM viewport
    if (g_lpD3DRMViewport)
    {   
        g_lpD3DRMViewport->Release();
        g_lpD3DRMViewport = NULL;
    }

    // Destroy Direct3D RM device
    if (g_lpD3DRMDevice)
    {
        g_lpD3DRMDevice->Release();
        g_lpD3DRMDevice = NULL;
    }

    // Destroy Direct3D device
    if (g_lpD3DDevice)
    {
        g_lpD3DDevice->Release();
        g_lpD3DDevice = NULL;
    }

    // Destroy ZBuffer
    if (g_lpZBuffer)
    {
        g_lpZBuffer->Release();
        g_lpZBuffer = NULL;
    }

    // Destroy Primary surface
    if (g_lpPrimary)
    {
        g_lpPrimary->Release();
        g_lpPrimary = NULL;
    }

    // Switch video mode
    TRY_DD(g_lpDD->SetDisplayMode(width, height, bitdepth))

    // First, create complex flipping primary surface
    
    // Fill out surface description
    memset(&ddsd, sizeof(DDSURFACEDESC), 0);
    ddsd.dwSize                 = sizeof(DDSURFACEDESC);
    ddsd.dwFlags                = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps         = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_3DDEVICE;
    ddsd.dwBackBufferCount      = 1;

    // Create the primary surface with 1 back buffer
    TRY_DD(g_lpDD->CreateSurface(&ddsd, &g_lpPrimary, NULL))

    // Get pointer to back buffer
    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    TRY_DD(g_lpPrimary->GetAttachedSurface(&ddscaps, &g_lpBackBuffer))

    // Only create a ZBuffer if g_dwZBufferBitDepth > 0
    if (g_dwZBufferBitDepth)
    {
	HRESULT err;

        // Then, create Z-Buffer. The g_dwZBufferMemType and g_dwZBufferBitDepth variables
        // are set up when the Direct3D device enumeration is done at runtime
        memset(&ddsd, sizeof(DDSURFACEDESC), 0);
        ddsd.dwSize             = sizeof(DDSURFACEDESC);
        ddsd.dwFlags            = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_ZBUFFERBITDEPTH;;
        ddsd.dwWidth            = width;
        ddsd.dwHeight           = height;
        ddsd.ddsCaps.dwCaps     = DDSCAPS_ZBUFFER | g_dwZBufferMemType;
        ddsd.dwZBufferBitDepth  = g_dwZBufferBitDepth;

        // Create the ZBuffer
	if (err = g_lpDD->CreateSurface(&ddsd, &g_lpZBuffer, NULL))
	{
	    if (err == DDERR_OUTOFVIDEOMEMORY)
	    {
		// Out of video memory - create system memory zbuffer for software renderer
		memset(&ddsd, sizeof(DDSURFACEDESC), 0);
		ddsd.dwSize             = sizeof(DDSURFACEDESC);
		ddsd.dwFlags            = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_ZBUFFERBITDEPTH;;
		ddsd.dwWidth            = width;
		ddsd.dwHeight           = height;
		ddsd.ddsCaps.dwCaps     = DDSCAPS_ZBUFFER | DDSCAPS_SYSTEMMEMORY;
		ddsd.dwZBufferBitDepth  = 16;
		if (err = g_lpDD->CreateSurface(&ddsd, &g_lpZBuffer, NULL))
		{
		    TRY_DD(err);
		}
		else
		{
		    g_bOutOfVideoMemory = TRUE;
		}
	    }
	    else
	    {
		TRY_DD(err);
	    }
	}
	else
	{
	    g_bOutOfVideoMemory = FALSE;
	}

        // Attach ZBuffer to the back buffer
        TRY_DD(g_lpBackBuffer->AddAttachedSurface(g_lpZBuffer))
    }

    // Retrieve the caps of the primary surface
    TRY_DD(g_lpPrimary->GetCaps(&ddscaps))

    // Create and attach palette (only if we in 8-bit palettized colour modes)
    if ((bitdepth == 8) && (ddscaps.dwCaps & DDCAPS_PALETTE))
    {
        // Create the palette
        TRY_DD(g_lpDD->CreatePalette(DDPCAPS_8BIT | DDPCAPS_INITIALIZE, g_rPal, &g_lpPalette, NULL))
        
        // Set the back buffer's palette
        TRY_DD(g_lpBackBuffer->SetPalette(g_lpPalette))

        // Set the primary surface's palette
        TRY_DD(g_lpPrimary->SetPalette(g_lpPalette))
    }

    // Create Direct3D device
    if (!g_bOutOfVideoMemory)
    {
	TRY_D3D(g_lpBackBuffer->QueryInterface(*g_lpD3DDeviceGuid, (LPVOID *)&g_lpD3DDevice))
    }
    else 
    {
	LPGUID guidSoftware;
	TRY_D3D(SoftwareGUID(&guidSoftware))
	TRY_D3D(g_lpBackBuffer->QueryInterface(*guidSoftware, (LPVOID*)&g_lpD3DDevice))
    }

    // Create Direct3D RM Device from Direct3D Device
    TRY_D3DRM(g_lpD3DRM->CreateDeviceFromD3D(g_lpD3D, g_lpD3DDevice, &g_lpD3DRMDevice))

    // Set the buffer count to 2 so D3DRM can keep track of extents for fullscreen flipping surface
    TRY_D3DRM(g_lpD3DRMDevice->SetBufferCount(2))

    // Render using gouraud shading
    g_lpD3DRMDevice->SetQuality(D3DRMRENDER_GOURAUD);

    // And no dithering please (NOTE : dithering is for looks not speed!)
    g_lpD3DRMDevice->SetDither(FALSE);

    // Set texture quality
    g_lpD3DRMDevice->SetTextureQuality(D3DRMTEXTURE_NEAREST);

    // Set the number of shades for lighting
    g_lpD3DRMDevice->SetShades(8);
    
    // Create RM viewport from device and camera (camera has already been initialised
    // by InitScene() in RM.CPP)
    TRY_D3DRM(g_lpD3DRM->CreateViewport(g_lpD3DRMDevice, 
                                        g_lpCamera,
                                        0,
                                        0,
                                        width,
                                        height,
                                        &g_lpD3DRMViewport))

    // Set the back clipping plane to be something fairly large
    g_lpD3DRMViewport->SetBack(D3DVAL(30000.0f));

    // Diddle with the lights depending on what driver we are using
    switch (g_deviceInfo.cm)
    {
        case D3DCOLOR_MONO : 
        {
            // Enable the directional light only to hit the players, not the arena
            g_lpDir->SetEnableFrame(g_lpPlayers);
        }
        break;

        case D3DCOLOR_RGB :
        {
            // Enable the directional light to hit all objects
            g_lpDir->SetEnableFrame(g_lpScene);
        }
        break;
    }   

    // Record video mode information
    g_vidModeX = width;
    g_vidModeY = height;
    g_vidModeBIT = bitdepth;
    
    // And calculate values for the power bars
    g_xratio = (float)width / 1000.0f;
    g_yratio = (float)height / 1000.0f;

    g_lbar1 = (DWORD)(float)(50.0f * g_xratio);
    g_wbar1 = (DWORD)(float)(400.0f * g_xratio);
    g_lbar2 = (DWORD)(float)(550.0f * g_xratio);
    g_wbar2 = g_wbar1;
    g_hbar1 = (DWORD)(float)(30.0f * g_yratio);
    g_hbar2 = (DWORD)(float)(20.0f * g_yratio);

    // Finally, calculate the height of the current font
    HDC hDC;
    hDC = ::GetDC(g_hWnd);
    
    TEXTMETRIC txtMetric;
    GetTextMetrics(hDC, &txtMetric);
    
    ::ReleaseDC(g_hWnd, hDC);

    g_dwFontHeight   = txtMetric.tmHeight;
    g_dwAveCharWidth = txtMetric.tmAveCharWidth;

    // Yahoo!
    return TRUE;        
}

//----------------------------------------------------------------------
// 
// Function     : EnterPrevVideoMode()
//
// Purpose      : Enters previous mode in vidModes[]
//
//----------------------------------------------------------------------

BOOL EnterPrevVideoMode()
{
    if (g_dwCurrMode > 0)
    {
        return EnterVideoMode(-- g_dwCurrMode);
    }
    
    return TRUE;
}

//----------------------------------------------------------------------
// 
// Function     : EnterNextVideoMode()
//
// Purpose      : Enters nextmode in vidModes[]
//
//----------------------------------------------------------------------

BOOL EnterNextVideoMode()
{
    if (g_dwCurrMode < g_dwNumModes - 1)
    {
        return EnterVideoMode(++ g_dwCurrMode);
    }
    
    return TRUE;
}

//----------------------------------------------------------------------
// 
// Function     : EnterLowestVideoMode()
//
// Purpose      : Enters lowest mode in vidModes[]
//
//----------------------------------------------------------------------

BOOL EnterLowestVideoMode()
{
    return EnterVideoMode(0);   
}

//----------------------------------------------------------------------
// 
// Function     : EnterHighestVideoMode()
//
// Purpose      : Enters highest mode in vidModes[]
//
//----------------------------------------------------------------------

BOOL EnterHighestVideoMode()
{
    return EnterVideoMode(g_dwNumModes - 1);    
}

//----------------------------------------------------------------------
// 
// Function     : ReenterVideoMode()
//
// Purpose      : Re-enters current video mode
//
//----------------------------------------------------------------------

BOOL ReenterCurrentVideoMode()
{
    return EnterVideoMode(g_dwCurrMode);
}

//----------------------------------------------------------------------
// 
// Function     : CleanUp()
//
// Purpose      : Destroys all surfaces and rendering devices 
//
//----------------------------------------------------------------------

void CleanUp()
{
    // Destroy everything in the reverse order that they were created
            
    // Destroy viewport
    if (g_lpD3DRMViewport)
    {
        g_lpD3DRMViewport->Release();
        g_lpD3DRMViewport = NULL;
    }

    // Destroy rendering devices
    if (g_lpD3DRMDevice)
    {
        g_lpD3DRMDevice->Release();
        g_lpD3DRMDevice = NULL;
    }

    if (g_lpD3DDevice)
    {
        g_lpD3DDevice->Release();
        g_lpD3DDevice = NULL;
    }

    // Destroy all surfaces
    if (g_lpZBuffer)
    {
        g_lpZBuffer->Release();
        g_lpZBuffer = NULL;
    }

    if (g_lpBackBuffer)
    {
        g_lpBackBuffer->Release();
        g_lpBackBuffer = NULL;
    }

    if (g_lpPrimary)
    {
        g_lpPrimary->Release();
        g_lpPrimary = NULL;
    }   

    // Destroy palette
    if (g_lpPalette)
    {
        g_lpPalette->Release();
        g_lpPalette = NULL;
    }
    
    // Restore the original video mode
    g_lpDD->RestoreDisplayMode();
}

//----------------------------------------------------------------------
// 
// Function     : DoSplashScreen()
//
// Purpose      : Draws splash screen (if possible)
//
//----------------------------------------------------------------------

BOOL DoSplashScreen(DWORD delay)
{
    LPDIRECTDRAWSURFACE backbuffer = NULL;
    DDSURFACEDESC       ddsd;
    DDSCAPS             ddscaps;
    HRESULT             rval;
    DWORD               dwStart;
    int                 i;
    FILE                *fp;
    BYTE                rgbs[768], scanbuf[640];
    void                *lpSurf;
    BYTE                *pSurf;
    DWORD               dummy;

    delay;
    
    // Create a DirectDraw device
    rval = DirectDrawCreate(NULL, &g_lpSplashDD, NULL);
    if (rval != DD_OK) goto fail;

    // Set cooperative level
    rval = g_lpSplashDD->SetCooperativeLevel(g_hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
    if (rval != DD_OK) goto fail;

    // Attempt to enter 640x480x8
    // Switch video mode        
    rval = g_lpSplashDD->SetDisplayMode(640, 480, 8);
    if (rval != DD_OK) goto fail;

    // Create complex flipping primary surface

    // Clear surface caps structure
    memset(&ddscaps, 0, sizeof(DDSCAPS));
    
    // Fill out surface description
    memset(&ddsd, sizeof(DDSURFACEDESC), 0);
    ddsd.dwSize                 = sizeof(DDSURFACEDESC);
    ddsd.dwFlags                = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps         = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
    ddsd.dwBackBufferCount      = 1;

    // Create the primary surface with 1 back buffer
    rval = g_lpSplashDD->CreateSurface(&ddsd, &g_lpSplashPrimary, NULL);
    if (rval != DD_OK) goto fail;

    // Get pointer to back buffer
    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    rval = g_lpSplashPrimary->GetAttachedSurface(&ddscaps, &backbuffer);
    if (rval != DD_OK) goto fail;

    // Open the splash screen file
    fp = fopen("ROCKEM3D.BIN", "rb");
    if (!fp) goto fail;
    
    memset(&ddsd, 0, sizeof(DDSURFACEDESC));
    ddsd.dwSize = sizeof(DDSURFACEDESC);

    // Lock the backbuffer to get a pointer to it
    rval = backbuffer->Lock(NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR, NULL);
    if (rval != DD_OK) goto fail;

    // Read the image into the backbuffer
    lpSurf = ddsd.lpSurface;

    // Read in lines of image, accounting for pitch
    pSurf = (BYTE *)lpSurf;

    // Read first dword from .BIN file, that corresponds to WIDTH and HEIGHT (two words)
    fread(&dummy, 4, 1, fp);

    for (i = 0; i < 480; i ++)
    {
        fread(scanbuf, 640, 1, fp);
        memcpy(pSurf, scanbuf, 640);
        pSurf += ddsd.lPitch;
    }

    // Close the file
    fclose(fp);

    // Unlock the surface
    rval = backbuffer->Unlock(lpSurf);
    if (rval != DD_OK) goto fail;

    // Set up the palette               
    fp = fopen("SPLASH.PAL", "rb");
    if (!fp) goto fail;

    fread(rgbs, 768, 1, fp);
    fclose(fp);
    
    // Set up the PALETTEENTRY's from the 768 byte RGB array
    PALETTEENTRY ppe[256];
    for (i = 0; i < 256; i ++)
    {
        ppe[i].peRed   = rgbs[i * 3];
        ppe[i].peGreen = rgbs[(i * 3) + 1];
        ppe[i].peBlue  = rgbs[(i * 3) + 2];
        ppe[i].peFlags = PC_NOCOLLAPSE;
    }
    
    // Create the palette
    //rval = g_lpDD->CreatePalette(DDPCAPS_8BIT | DDPCAPS_INITIALIZE, ppe, &g_lpPalette, NULL);
    rval = g_lpSplashDD->CreatePalette(DDPCAPS_8BIT | DDPCAPS_INITIALIZE, ppe, &g_lpSplashPalette, NULL);
    if (rval != DD_OK) goto fail;

    // Set the backbuffer's palette
    rval = g_lpSplashPrimary->SetPalette(g_lpSplashPalette);
    if (rval != DD_OK) goto fail;

    // And flip the splash screen into view
    rval = g_lpSplashPrimary->Flip(NULL, DDFLIP_WAIT);
    if (rval != DD_OK) goto fail;

    // Wait for delay milliseconds or a specific keypress
    dwStart = timeGetTime();
    
    while (timeGetTime() - dwStart < delay)
    {
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) break;
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) break;
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) break;
        if ((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_F4) & 0x8000)) break;
    }   

    backbuffer->Release();

    // Yahoo!
    return TRUE;

    fail:

    // Close file
    if (fp)
    {
        fclose(fp);
    }
    
    // Release palette
    if (g_lpSplashPalette)
    {
        g_lpSplashPalette->Release();
        g_lpSplashPalette = NULL;
    }

    // Release primary surface
    if (g_lpSplashPrimary)
    {
        g_lpSplashPrimary->Release();
        g_lpSplashPrimary = NULL;
    }

    if (g_lpSplashDD)
    {
        g_lpSplashDD->Release();
        g_lpSplashDD = NULL;
    }

    // Yahoo!
    return FALSE;
}


//----------------------------------------------------------------------
// 
// Function     : ReleaseSplashScreen()
//
// Purpose      : Releases the splash screen
//
//----------------------------------------------------------------------

void ReleaseSplashScreen()
{
    // Release palette
    if (g_lpSplashPalette)
    {
        g_lpSplashPalette->Release();
        g_lpSplashPalette = NULL;
    }

    // Release primary surface
    if (g_lpSplashPrimary)
    {
        g_lpSplashPrimary->Release();
        g_lpSplashPrimary = NULL;
    }

    if (g_lpSplashDD)
    {
        g_lpSplashDD->Release();
        g_lpSplashDD = NULL;
    }
}


//----------------------------------------------------------------------
// 
// Function     : RestoreSurfaces()
//
// Purpose      : Restores all surfaces if they somehow got lost (Alt-Tab)
//
//----------------------------------------------------------------------

BOOL RestoreSurfaces()
{
    // Attempt to restore primary surface
    if (g_lpPrimary)
    {
        if (g_lpPrimary->IsLost()) TRY_DD(g_lpPrimary->Restore())
    }

    // Attempt to restore zbuffer
    if (g_lpZBuffer)
    {
        if (g_lpZBuffer->IsLost()) TRY_DD(g_lpZBuffer->Restore())
    }

    // Yahoo!
    return TRUE;
}

//----------------------------------------------------------------------
// 
// Function     : CreateSoundBuffer()
//
// Purpose      : Creates a DirectSound buffer
//
//----------------------------------------------------------------------

BOOL CreateSoundBuffer(DWORD dwBuf, DWORD dwBufSize, DWORD dwFreq, DWORD dwBitsPerSample, DWORD dwBlkAlign, BOOL bStereo)
{
    PCMWAVEFORMAT pcmwf;
    DSBUFFERDESC dsbdesc;
    
    // Set up wave format structure.
    memset( &pcmwf, 0, sizeof(PCMWAVEFORMAT) );
    pcmwf.wf.wFormatTag         = WAVE_FORMAT_PCM;      
    pcmwf.wf.nChannels          = bStereo ? 2 : 1;
    pcmwf.wf.nSamplesPerSec     = dwFreq;
    pcmwf.wf.nBlockAlign        = (WORD)dwBlkAlign;
    pcmwf.wf.nAvgBytesPerSec    = pcmwf.wf.nSamplesPerSec * pcmwf.wf.nBlockAlign;
    pcmwf.wBitsPerSample        = (WORD)dwBitsPerSample;

    // Set up DSBUFFERDESC structure.
    memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));  // Zero it out. 
    dsbdesc.dwSize              = sizeof(DSBUFFERDESC);
    dsbdesc.dwFlags             = DSBCAPS_CTRL3D;               // Needed creation flag for Direct 3D Sound
        dsbdesc.dwBufferBytes       = dwBufSize; 
    dsbdesc.lpwfxFormat         = (LPWAVEFORMATEX)&pcmwf;

    TRY_DS(g_lpDS->CreateSoundBuffer(&dsbdesc, &g_lpSounds[dwBuf], NULL))
    
        // Query for the 3D Sound Buffer interface.
    TRY_DS(g_lpSounds[dwBuf]->QueryInterface(IID_IDirectSound3DBuffer, (void**) &g_lp3dSounds[dwBuf]));

    // Yahoo!
    return TRUE;
}

//----------------------------------------------------------------------
// 
// Function     : ReadData()
//
// Purpose      : Reads in data from a wave file
//
//----------------------------------------------------------------------

BOOL ReadData(LPDIRECTSOUNDBUFFER lpDSB, FILE* pFile, DWORD dwSize, DWORD dwPos) 
{
    // Seek to correct position in file (if necessary)
    if (dwPos != 0xffffffff) 
    {
        if (fseek(pFile, dwPos, SEEK_SET) != 0) 
        {
            return FALSE;
        }
    }

    // Lock data in buffer for writing
    LPVOID pData1;
    DWORD  dwData1Size;
    LPVOID pData2;
    DWORD  dwData2Size;
    HRESULT rval;

    rval = lpDSB->Lock(0, dwSize, &pData1, &dwData1Size, &pData2, &dwData2Size, DSBLOCK_FROMWRITECURSOR);
    if (rval != DS_OK)
    {
        return FALSE;
    }

    // Read in first chunk of data
    if (dwData1Size > 0) 
    {
        if (fread(pData1, dwData1Size, 1, pFile) != 1) 
        {          
                        char holder[256];
                        wsprintf(holder,"Data1 : %d, dwdata: %d, pFile: %d",pData1,dwData1Size,pFile);
                        OutputDebugString(holder);
            return FALSE;
        }
    }

    // read in second chunk if necessary
    if (dwData2Size > 0) 
    {
        if (fread(pData2, dwData2Size, 1, pFile) != 1) 
        {
            return FALSE;
        }
    }

    // Unlock data in buffer
    rval = lpDSB->Unlock(pData1, dwData1Size, pData2, dwData2Size);
    if (rval != DS_OK)
    {
        return FALSE;
    }

    // Yahoo!
    return TRUE;
}

//----------------------------------------------------------------------
// 
// Function     : CreateSoundBufferFromWaveFile()
//
// Purpose      : Creates a DirectSound buffer from a wave file
//
//----------------------------------------------------------------------

BOOL CreateBufferFromWaveFile(char* FileName, DWORD dwBuf)
{
    // Open the wave file       
    FILE* pFile = fopen(FileName,"rb");
    if (pFile == NULL) return FALSE;

    // Read in the wave header          
    WaveHeader wavHdr;
    if (fread(&wavHdr, sizeof(wavHdr), 1, pFile) != 1) 
    {
        fclose(pFile);
        return NULL;
    }

    // Figure out the size of the data region
    DWORD dwSize = wavHdr.dwDSize;

    // Is this a stereo or mono file?
    BOOL bStereo = wavHdr.wChnls > 1 ? TRUE : FALSE;

    // Create the sound buffer for the wave file
    if (!CreateSoundBuffer(dwBuf, dwSize, wavHdr.dwSRate, wavHdr.BitsPerSample, wavHdr.wBlkAlign, bStereo))
    {
        // Close the file
        fclose(pFile);
        
        return FALSE;
    }

    // Read the data for the wave file into the sound buffer
    if (!ReadData(g_lpSounds[dwBuf], pFile, dwSize, sizeof(wavHdr))) 
    {
        fclose(pFile);
        return FALSE;
    }

    // Close out the wave file
    fclose(pFile);

    // Yahoo!
    return TRUE;
}

//----------------------------------------------------------------------
// 
// Function     : StopAllSounds()
//
// Purpose      : Stops all sounds
//
//----------------------------------------------------------------------

BOOL StopAllSounds()
{
    // Make sure we have a valid sound buffer
    for (int i = 0; i < NUM_SOUNDS; i ++)
    {
        if (g_lpSounds[i])
        {
            DWORD dwStatus;
            TRY_DS(g_lpSounds[i]->GetStatus(&dwStatus));

            if ((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
            {
                // Play the sound
                TRY_DS(g_lpSounds[i]->Stop())
            }
        }
    }

    // Yahoo!
    return TRUE;
}

//----------------------------------------------------------------------
// 
// Function     : PlaySoundDS()
//
// Purpose      : Plays a sound using direct sound
// 
//                      D3DVECTOR
//----------------------------------------------------------------------

BOOL PlaySoundDS(DWORD dwSound,D3DVECTOR d3dvPos, DWORD dwFlags)
{

    if (g_bSoundPaused) return TRUE;

    if (!g_bSoundPresent) return TRUE;

    // Make sure the sound is valid
    if (dwSound >= NUM_SOUNDS) return FALSE;    

    // Make sure we have a valid sound buffer
    if (g_lpSounds[dwSound])
    {
        DWORD dwStatus;
        TRY_DS(g_lpSounds[dwSound]->GetStatus(&dwStatus));

        if ((dwStatus & DSBSTATUS_PLAYING) != DSBSTATUS_PLAYING)
        {
           // Set the 3D position of the sound, using supplied position vector.
           TRY_DS(g_lp3dSounds[dwSound]->SetPosition(d3dvPos.x, d3dvPos.y, d3dvPos.z, DS3D_IMMEDIATE));
            // Play the sound
           TRY_DS(g_lpSounds[dwSound]->Play(0, 0, dwFlags));
        }
    }

    // Yahoo!
    return TRUE;
}

//----------------------------------------------------------------------
// 
// Function     : RecalcPowerBars()
//
// Purpose      : Calculates width of power bars based upon current 
//                        screen resolution
//
//----------------------------------------------------------------------

void RecalcPowerBars(DWORD player1health, DWORD player2health)
{
    g_wbar1 = (DWORD)(float)((400.0f * ((float)player1health / 100.0f)) * g_xratio);
    g_wbar2 = (DWORD)(float)((400.0f * ((float)player2health / 100.0f)) * g_xratio);
}



//----------------------------------------------------------------------
// 
// Function     : CreateSoundBuffer3D()
//
// Purpose      : Creates a 3D sound buffer and returns the sound buffer
//
//----------------------------------------------------------------------

IDirectSoundBuffer *CreateSoundBuffer3D()
{
    IDirectSoundBuffer *pDSB = NULL;
    DSBUFFERDESC dsBD = {0};

        ZeroMemory( &dsBD, sizeof(DSBUFFERDESC));
        dsBD.dwSize = sizeof(dsBD);
    dsBD.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
        dsBD.dwBufferBytes = 0;  //must be zero for primary buffer..

        if (g_lpDS->CreateSoundBuffer(&dsBD, &pDSB, NULL) != DS_OK)
                pDSB = NULL;

    return pDSB;
}

//----------------------------------------------------------------------
// 
// Function     : PlayRandomWave()
//
// Purpose      : Creates a random wave at a random spot
//
//----------------------------------------------------------------------

VOID CALLBACK PlayRandomWave( HWND hwnd, UINT uMsg,	UINT idEvent, DWORD dwTime )
{
        D3DVECTOR       d3dPosition;    // DSVECTOR used for the positon of the wave...
 
        int RandomWave[]={RANDOM1,RANDOM2,RANDOM3,RANDOM4,RANDOM5,RANDOM6};

        g_lpCamera->GetPosition(g_lpScene, &d3dPosition);
        // fill in the position generated for the wave file.
        d3dPosition.x += (rand() % 2 == 0 ? (rand() % 250) : -(rand() % 250));
        d3dPosition.z += (rand() % 2 == 0 ? (rand() % 250) : -(rand() % 250));

        PlaySoundDS(RandomWave[rand() % (sizeof(RandomWave) / sizeof(RandomWave[0]))],d3dPosition);
        return;
}
