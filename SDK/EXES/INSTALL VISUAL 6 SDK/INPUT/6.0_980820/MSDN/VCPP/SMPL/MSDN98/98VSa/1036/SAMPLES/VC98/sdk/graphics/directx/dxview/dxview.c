/****************************************************************************

    Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.

    PROGRAM: dxview.c

    PURPOSE: DirectX Device Viewer

    FUNCTIONS:

    COMMENTS:

****************************************************************************/

#include "dxview.h"

#pragma comment(lib, "dxguid")
#pragma comment(lib, "ddraw")
#pragma comment(lib, "dsound")
#pragma comment(lib, "dplayx")
#pragma comment(lib, "dinput")
#pragma comment(lib, "comctl32")

/****************************************************************************
 ***************************************************************************/

HINSTANCE   g_hInstance;
char        g_szAppName[]   = "DXView";
char        g_szClassName[] = "DXView";
char        g_szTitle[]     = "DirectX Device Viewer";
HWND        g_hwndMain;

HWND        g_hwndLV;        // List view
HWND        g_hwndTV;        // Tree view
HIMAGELIST  g_hImageList;
HFONT       g_hFont;
int         g_xPaneSplit;
int         g_xHalfSplitWidth;
BOOL        g_bSplitMove;
DWORD       g_dwViewState;
DWORD       g_tmAveCharWidth;
extern BOOL g_PrintToFile;
UINT		g_idTimer;
LPLOCALAPP	g_lpLocalApp;

HINSTANCE g_hDSoundLib = NULL;

typedef HRESULT (WINAPI * PFN_DSCREATE)(LPGUID lpguid, LPDIRECTSOUND * ppDS, IUnknown FAR * pUnkOuter);
typedef BOOL (WINAPI * PFN_DSENUMERATE)(LPDSENUMCALLBACK lpDSEnumCallback, LPVOID lpContext);
typedef HRESULT (WINAPI * PFN_DSCCREATE)(LPGUID lpGUID,	LPDIRECTSOUNDCAPTURE *lplpDSC,LPUNKNOWN pUnkOuter);
typedef BOOL (WINAPI * PFN_DSCENUMERATE)(LPDSENUMCALLBACK lpDSEnumCallback,LPVOID lpContext);

/****************************************************************************
 ***************************************************************************/

IDirectDraw *lpDD;                  // DirectDraw object
IDirectDraw2 *lpDD2;                // DirectDraw object
IDirect3D2  *lp3D;                  // Direct3D object
GUID *       ddid;

IDirectSound *lpDS;                 // DirectSound object
GUID *       dsid;

IDirectSoundCapture *lpDSC;         // DirectSoundCapture object
GUID *       dscid;

IDirectPlay3A  *lpDP3A;             // DirectPlay object
GUID *       dpid;

/****************************************************************************
 ***************************************************************************/

#define DDCAPDEF(name,val,flag) {name, FIELD_OFFSET(DDCAPS,val), flag}
#define DDVALDEF(name,val)      {name, FIELD_OFFSET(DDCAPS,val), 0}
#define DDHEXDEF(name,val)      {name, FIELD_OFFSET(DDCAPS,val), 0xFFFFFFFF}
#define ROPDEF(name,dwRops,rop) DDCAPDEF(name,dwRops[((rop>>16)&0xFF)/32],(1<<((rop>>16)&0xFF)%32))

#define DSCAPDEF(name,val,flag) {name, FIELD_OFFSET(DSCAPS,val), flag}
#define DSVALDEF(name,val)      {name, FIELD_OFFSET(DSCAPS,val), 0}

#define DSCCAPDEF(name,val,flag) {name, FIELD_OFFSET(DSCCAPS,val), flag}
#define DSCVALDEF(name,val)      {name, FIELD_OFFSET(DSCCAPS,val), 0}

#define DPCAPDEF(name,val,flag) {name, FIELD_OFFSET(DPCAPS,val), flag}
#define DPHEXDEF(name,val)      {name, FIELD_OFFSET(DPCAPS,val), 0xFFFFFFFF}
#define DPVALDEF(name,val)      {name, FIELD_OFFSET(DPCAPS,val), 0}

#define D3CAPDEF(name,val,flag) {name, FIELD_OFFSET(D3DDEVICEDESC,val), flag}
#define D3HEXDEF(name,val)      {name, FIELD_OFFSET(D3DDEVICEDESC,val), 0xFFFFFFFF}
#define D3VALDEF(name,val)      {name, FIELD_OFFSET(D3DDEVICEDESC,val), 0}

#define SURFCAPDEF(name,val,flag) {name, FIELD_OFFSET(DDSURFACEDESC,val), flag}
#define SURFVALDEF(name,val)      {name, FIELD_OFFSET(DDSURFACEDESC,val), 0}

#define MAKEMODE(xres,yres,bpp) (((DWORD)xres << 20) | ((DWORD)yres << 8) | bpp)
#define GETXRES(mode)           (int)((mode >> 20) & 0x0FFF)
#define GETYRES(mode)           (int)((mode >> 8)  & 0x0FFF)
#define GETCRES(mode)           (int)((mode >> 0)  & 0x00FF)

IDirectDraw * DDCreate(GUID *pid);

BOOL PrintValueLine(char * szText, DWORD dwValue, PRINTCBINFO *lpInfo)
{
    char    szBuff[80];
    DWORD cchLen;
    int xName, xVal, yLine;

    // Calculate Name and Value column x offsets
    xName   = (lpInfo->dwCurrIndent * DEF_TAB_SIZE * lpInfo->dwCharWidth);
    xVal    = xName + (32 * lpInfo->dwCharWidth);
    yLine   = (lpInfo->dwCurrLine * lpInfo->dwLineHeight);

    // Print name
    wsprintf (szBuff, szText);
    cchLen = _tcslen (szText);
    if (! PrintLine (xName, yLine, szBuff, cchLen, lpInfo))
        return FALSE;

    // Print value
    wsprintf (szBuff, "%d", dwValue);
    cchLen = _tcslen (szBuff);
    if (! PrintLine (xVal, yLine, szBuff, cchLen, lpInfo))
        return FALSE;

    // Advance to next line on page
    if (! PrintNextLine (lpInfo))
        return FALSE;

   return TRUE;
}

VOID VidMem(long lParam1, long foo2)
{
    HRESULT ddrval;
    DWORD dwTotalMem;
    DWORD dwFreeMem;
    DDSCAPS DDSCaps;

    LVAddColumn(g_hwndLV, 0, "Type", 24);
    LVAddColumn(g_hwndLV, 1, "Total", 10);
    LVAddColumn(g_hwndLV, 2, "Free", 10);

    if (DDCreate((GUID*)lParam1))
    {
        IDirectDraw_QueryInterface(lpDD,&IID_IDirectDraw2,&lpDD2);

        DDSCaps.dwCaps = DDSCAPS_VIDEOMEMORY;
        ddrval = IDirectDraw2_GetAvailableVidMem(lpDD2, &DDSCaps, &dwTotalMem, &dwFreeMem );
        if(ddrval != DD_OK)
        {
            dwTotalMem = 0;
            dwFreeMem = 0;
        };
        LVAddText(g_hwndLV, 0, "Video");
        LVAddText(g_hwndLV, 1, "%d", dwTotalMem);
        LVAddText(g_hwndLV, 2, "%d", dwFreeMem);

        DDSCaps.dwCaps = DDSCAPS_LOCALVIDMEM;
        ddrval = IDirectDraw2_GetAvailableVidMem(lpDD2, &DDSCaps, &dwTotalMem, &dwFreeMem );
        if(ddrval != DD_OK)
        {
            dwTotalMem = 0;
            dwFreeMem = 0;
        };
        LVAddText(g_hwndLV, 0, "Video (local)");
        LVAddText(g_hwndLV, 1, "%d", dwTotalMem);
        LVAddText(g_hwndLV, 2, "%d", dwFreeMem);

        DDSCaps.dwCaps = DDSCAPS_NONLOCALVIDMEM;
        ddrval = IDirectDraw2_GetAvailableVidMem(lpDD2, &DDSCaps, &dwTotalMem, &dwFreeMem );
        if(ddrval != DD_OK)
        {
            dwTotalMem = 0;
            dwFreeMem = 0;
        };
        LVAddText(g_hwndLV, 0, "Video (non-local)");
        LVAddText(g_hwndLV, 1, "%d", dwTotalMem);
        LVAddText(g_hwndLV, 2, "%d", dwFreeMem);

        DDSCaps.dwCaps = DDSCAPS_TEXTURE;
        ddrval = IDirectDraw2_GetAvailableVidMem(lpDD2, &DDSCaps, &dwTotalMem, &dwFreeMem );
        if(ddrval != DD_OK)
        {
            dwTotalMem = 0;
            dwFreeMem = 0;
        };
        LVAddText(g_hwndLV, 0, "Texture");
        LVAddText(g_hwndLV, 1, "%d", dwTotalMem);
        LVAddText(g_hwndLV, 2, "%d", dwFreeMem);
    }
}

BOOL VidMemPrint(long lParam1, long lParam2, PRINTCBINFO *lpInfo)
{
    HRESULT ddrval;
    DWORD dwTotalMem;
    DWORD dwFreeMem;
    DDSCAPS DDSCaps;

    if (DDCreate((GUID*)lParam1))
    {
        IDirectDraw_QueryInterface(lpDD,&IID_IDirectDraw2,&lpDD2);

        DDSCaps.dwCaps = DDSCAPS_VIDEOMEMORY;
        ddrval = IDirectDraw2_GetAvailableVidMem(lpDD2, &DDSCaps, &dwTotalMem, &dwFreeMem );
        if(ddrval != DD_OK)
        {
            dwTotalMem = 0;
            dwFreeMem = 0;
        };
        PrintValueLine("TotalMem",dwTotalMem,lpInfo);
        PrintValueLine("FreeMem",dwFreeMem,lpInfo);

        DDSCaps.dwCaps = DDSCAPS_LOCALVIDMEM;
        ddrval = IDirectDraw2_GetAvailableVidMem(lpDD2, &DDSCaps, &dwTotalMem, &dwFreeMem );
        if(ddrval != DD_OK)
        {
            dwTotalMem = 0;
            dwFreeMem = 0;
        };
        PrintValueLine("TotalVideoMem",dwTotalMem,lpInfo);
        PrintValueLine("FreeVideoMem",dwFreeMem,lpInfo);

        DDSCaps.dwCaps = DDSCAPS_NONLOCALVIDMEM;
        ddrval = IDirectDraw2_GetAvailableVidMem(lpDD2, &DDSCaps, &dwTotalMem, &dwFreeMem );
        if(ddrval != DD_OK)
        {
            dwTotalMem = 0;
            dwFreeMem = 0;
        };
        PrintValueLine("TotalAGPMem",dwTotalMem,lpInfo);
        PrintValueLine("FreeAGPMem",dwFreeMem,lpInfo);

        DDSCaps.dwCaps = DDSCAPS_TEXTURE;
        ddrval = IDirectDraw2_GetAvailableVidMem(lpDD2, &DDSCaps, &dwTotalMem, &dwFreeMem );
        if(ddrval != DD_OK)
        {
            dwTotalMem = 0;
            dwFreeMem = 0;
        };
        PrintValueLine("TotalTextureMem",dwTotalMem,lpInfo);
        PrintValueLine("FreeTextureMem",dwFreeMem,lpInfo);
    }
    return TRUE; 
};

/****************************************************************************
 ***************************************************************************/
CAPDEF OtherInfoDefs[] =
{
    DDVALDEF("VidMemTotal",                   dwVidMemTotal),
    DDVALDEF("VidMemFree",                    dwVidMemFree),
    DDHEXDEF("AlphaBltConstBitDepths",        dwAlphaBltConstBitDepths),
    DDCAPDEF("  8",                           dwAlphaBltConstBitDepths, DDBD_8),
    DDCAPDEF("  16",                          dwAlphaBltConstBitDepths, DDBD_16),
    DDCAPDEF("  24",                          dwAlphaBltConstBitDepths, DDBD_24),
    DDCAPDEF("  32",                          dwAlphaBltConstBitDepths, DDBD_32),
    DDHEXDEF("AlphaBltPixelBitDepths",        dwAlphaBltPixelBitDepths),
    DDCAPDEF("  8",                           dwAlphaBltPixelBitDepths, DDBD_8),
    DDCAPDEF("  16",                          dwAlphaBltPixelBitDepths, DDBD_16),
    DDCAPDEF("  24",                          dwAlphaBltPixelBitDepths, DDBD_24),
    DDCAPDEF("  32",                          dwAlphaBltPixelBitDepths, DDBD_32),
    DDHEXDEF("AlphaBltSurfaceBitDepths",      dwAlphaBltSurfaceBitDepths),
    DDCAPDEF("  8",                           dwAlphaBltSurfaceBitDepths, DDBD_8),
    DDCAPDEF("  16",                          dwAlphaBltSurfaceBitDepths, DDBD_16),
    DDCAPDEF("  24",                          dwAlphaBltSurfaceBitDepths, DDBD_24),
    DDCAPDEF("  32",                          dwAlphaBltSurfaceBitDepths, DDBD_32),
    DDHEXDEF("AlphaOverlayConstBitDepths",    dwAlphaOverlayConstBitDepths),
    DDCAPDEF("  8",                           dwAlphaOverlayConstBitDepths, DDBD_8),
    DDCAPDEF("  16",                          dwAlphaOverlayConstBitDepths, DDBD_16),
    DDCAPDEF("  24",                          dwAlphaOverlayConstBitDepths, DDBD_24),
    DDCAPDEF("  32",                          dwAlphaOverlayConstBitDepths, DDBD_32),
    DDHEXDEF("AlphaOverlayPixelBitDepths",    dwAlphaOverlayPixelBitDepths),
    DDCAPDEF("  8",                           dwAlphaOverlayPixelBitDepths, DDBD_8),
    DDCAPDEF("  16",                          dwAlphaOverlayPixelBitDepths, DDBD_16),
    DDCAPDEF("  24",                          dwAlphaOverlayPixelBitDepths, DDBD_24),
    DDCAPDEF("  32",                          dwAlphaOverlayPixelBitDepths, DDBD_32),
    DDHEXDEF("AlphaOverlaySurfaceBitDepths",  dwAlphaOverlaySurfaceBitDepths),
    DDCAPDEF("  8",                           dwAlphaOverlaySurfaceBitDepths, DDBD_8),
    DDCAPDEF("  16",                          dwAlphaOverlaySurfaceBitDepths, DDBD_16),
    DDCAPDEF("  24",                          dwAlphaOverlaySurfaceBitDepths, DDBD_24),
    DDCAPDEF("  32",                          dwAlphaOverlaySurfaceBitDepths, DDBD_32),
    DDHEXDEF("ZBufferBitDepths",              dwZBufferBitDepths),
    DDCAPDEF("  8",                           dwZBufferBitDepths, DDBD_8),
    DDCAPDEF("  16",                          dwZBufferBitDepths, DDBD_16),
    DDCAPDEF("  24",                          dwZBufferBitDepths, DDBD_24),
    DDCAPDEF("  32",                          dwZBufferBitDepths, DDBD_32),
    DDVALDEF("MaxVisibleOverlays",            dwMaxVisibleOverlays),
    DDVALDEF("CurrVisibleOverlays",           dwCurrVisibleOverlays),
    DDVALDEF("NumFourCCCodes",                dwNumFourCCCodes),
    DDVALDEF("AlignBoundarySrc",              dwAlignBoundarySrc),
    DDVALDEF("AlignSizeSrc",                  dwAlignSizeSrc),
    DDVALDEF("AlignBoundaryDest",             dwAlignBoundaryDest),
    DDVALDEF("AlignSizeDest",                 dwAlignSizeDest),
    DDVALDEF("AlignStrideAlign",              dwAlignStrideAlign),
    DDVALDEF("MinOverlayStretch",             dwMinOverlayStretch),
    DDVALDEF("MaxOverlayStretch",             dwMaxOverlayStretch),
    DDVALDEF("MinLiveVideoStretch",           dwMinLiveVideoStretch),
    DDVALDEF("MaxLiveVideoStretch",           dwMaxLiveVideoStretch),
    DDVALDEF("MinHwCodecStretch",             dwMinHwCodecStretch),
    DDVALDEF("MaxHwCodecStretch",             dwMaxHwCodecStretch),
    DDVALDEF("dwReserved1",                   dwReserved1),
    DDVALDEF("dwReserved2",                   dwReserved2),
    DDVALDEF("dwReserved3",                   dwReserved3),

    //DDHEXDEF("dwCaps",                      dwCaps),
    DDVALDEF("dwMaxVideoPorts",               dwMaxVideoPorts),
    DDVALDEF("dwCurrVideoPorts",               dwCurrVideoPorts),
    //DDVALDEF("dwSVBCaps2",                   dwSVBCaps2),
    { "", 0, 0 }
};

/****************************************************************************
 ***************************************************************************/

#define GEN_CAPS(dwCaps)                                                     \
\
    DDCAPDEF("3D",                        dwCaps, DDCAPS_3D),                   \
    DDCAPDEF("ALIGNBOUNDARYDEST",         dwCaps, DDCAPS_ALIGNBOUNDARYDEST),    \
    DDCAPDEF("ALIGNSIZEDEST",             dwCaps, DDCAPS_ALIGNSIZEDEST),        \
    DDCAPDEF("ALIGNBOUNDARYSRC",          dwCaps, DDCAPS_ALIGNBOUNDARYSRC),     \
    DDCAPDEF("ALIGNSIZESRC",              dwCaps, DDCAPS_ALIGNSIZESRC),         \
    DDCAPDEF("ALIGNSTRIDE",               dwCaps, DDCAPS_ALIGNSTRIDE),          \
    DDCAPDEF("GDI",                       dwCaps, DDCAPS_GDI),                  \
    DDCAPDEF("OVERLAY",                   dwCaps, DDCAPS_OVERLAY),              \
    DDCAPDEF("OVERLAYCANTCLIP",           dwCaps, DDCAPS_OVERLAYCANTCLIP),      \
    DDCAPDEF("OVERLAYFOURCC",             dwCaps, DDCAPS_OVERLAYFOURCC),        \
    DDCAPDEF("OVERLAYSTRETCH",            dwCaps, DDCAPS_OVERLAYSTRETCH),       \
    DDCAPDEF("PALETTE",                   dwCaps, DDCAPS_PALETTE),              \
    DDCAPDEF("PALETTEVSYNC",              dwCaps, DDCAPS_PALETTEVSYNC),         \
    DDCAPDEF("READSCANLINE",              dwCaps, DDCAPS_READSCANLINE),         \
    DDCAPDEF("STEREOVIEW",                dwCaps, DDCAPS_STEREOVIEW),           \
    DDCAPDEF("VBI",                       dwCaps, DDCAPS_VBI),                  \
    DDCAPDEF("ZOVERLAYS",                 dwCaps, DDCAPS_ZOVERLAYS),            \
    DDCAPDEF("NOHARDWARE",                dwCaps, DDCAPS_NOHARDWARE),           \
    DDCAPDEF("BANKSWITCHED",              dwCaps, DDCAPS_BANKSWITCHED),


#define GEN_CAPS2(dwCaps2)                                                      \
    DDCAPDEF("CERTIFIED",                 dwCaps2,DDCAPS2_CERTIFIED),           \
    DDCAPDEF("NO2DDURING3DSCENE",         dwCaps2,DDCAPS2_NO2DDURING3DSCENE),   \
    DDCAPDEF("VIDEOPORT",                 dwCaps2,DDCAPS2_VIDEOPORT),           \
    DDCAPDEF("AUTOFLIPOVERLAY",           dwCaps2,DDCAPS2_AUTOFLIPOVERLAY),     \
    DDCAPDEF("CANBOBINTERLEAVED",         dwCaps2,DDCAPS2_CANBOBINTERLEAVED),   \
    DDCAPDEF("CANBOBNONINTERLEAVED",      dwCaps2,DDCAPS2_CANBOBNONINTERLEAVED),\
    DDCAPDEF("COLORCONTROLOVERLAY",       dwCaps2,DDCAPS2_COLORCONTROLOVERLAY), \
    DDCAPDEF("COLORCONTROLPRIMARY",       dwCaps2,DDCAPS2_COLORCONTROLPRIMARY), \
    DDCAPDEF("NONLOCALVIDMEM",            dwCaps2,DDCAPS2_NONLOCALVIDMEM),      \
    DDCAPDEF("NONLOCALVIDMEMCAPS",        dwCaps2,DDCAPS2_NONLOCALVIDMEMCAPS),  \
    DDCAPDEF("WIDESURFACES",              dwCaps2,DDCAPS2_WIDESURFACES),        \
    DDCAPDEF("NOPAGELOCKREQUIRED",        dwCaps2,DDCAPS2_NOPAGELOCKREQUIRED),  


#define GEN_BLTCAPS(dwCaps)                                                     \
    DDCAPDEF("BLT",                       dwCaps, DDCAPS_BLT),                  \
    DDCAPDEF("BLTCOLORFILL",              dwCaps, DDCAPS_BLTCOLORFILL),         \
    DDCAPDEF("BLTDEPTHFILL",              dwCaps, DDCAPS_BLTDEPTHFILL),         \
    DDCAPDEF("BLTFOURCC",                 dwCaps, DDCAPS_BLTFOURCC),            \
    DDCAPDEF("BLTSTRETCH",                dwCaps, DDCAPS_BLTSTRETCH),           \
    DDCAPDEF("BLTQUEUE",                  dwCaps, DDCAPS_BLTQUEUE),             \
    DDCAPDEF("COLORKEY",                  dwCaps, DDCAPS_COLORKEY),             \
    DDCAPDEF("ALPHA",                     dwCaps, DDCAPS_ALPHA),                \
    DDCAPDEF("CKEYHWASSIST",              dwCaps, DDCAPS_COLORKEYHWASSIST),     \
    DDCAPDEF("CANCLIP",                   dwCaps, DDCAPS_CANCLIP),              \
    DDCAPDEF("CANCLIPSTRETCHED",          dwCaps, DDCAPS_CANCLIPSTRETCHED),     \
    DDCAPDEF("CANBLTSYSMEM",              dwCaps, DDCAPS_CANBLTSYSMEM),         \
    DDCAPDEF("ZBLTS",                     dwCaps, DDCAPS_ZBLTS),                


#define GEN_BLTCAPS2(dwCaps2)                                                   \
    DDCAPDEF("CANDROPZ16BIT",             dwCaps2,DDCAPS2_CANDROPZ16BIT),       \
    DDCAPDEF("NOPAGELOCKREQUIRED",        dwCaps2,DDCAPS2_NOPAGELOCKREQUIRED),  


/****************************************************************************
 ***************************************************************************/
CAPDEF GenCaps[] =
{
    GEN_CAPS(dwCaps)
    GEN_CAPS2(dwCaps2)
    { "", 0, 0 }
};

//
// NOTE GenCaps and CapsDefs are the same
// because some are blt caps that apply to VRAM->VRAM blts and
// some are "general" caps...
//
CAPDEF CapsDefs[] =
{
    GEN_BLTCAPS(dwCaps)
    GEN_BLTCAPS2(dwCaps2)
    { "", 0, 0 }
};
CAPDEF SVBCapsDefs[] =
{
    GEN_BLTCAPS(dwSVBCaps)
    GEN_BLTCAPS2(dwSVBCaps2)
    { "", 0, 0 }
};
CAPDEF VSBCapsDefs[] =
{
    GEN_BLTCAPS(dwVSBCaps)
//  GEN_BLTCAPS2(dwVSBCaps2)
    { "", 0, 0 }
};
CAPDEF SSBCapsDefs[] =
{
    GEN_BLTCAPS(dwSSBCaps)
//  GEN_BLTCAPS2(dwSSBCaps2)
    { "", 0, 0 }
};
CAPDEF NLVBCapsDefs[] =
{
    GEN_BLTCAPS(dwNLVBCaps)
    GEN_BLTCAPS2(dwNLVBCaps2)
    { "", 0, 0 }
};

/****************************************************************************
 ***************************************************************************/
#define GEN_CKCAPS(dwCKeyCaps)                                                              \
    DDCAPDEF("DESTBLT",                 dwCKeyCaps, DDCKEYCAPS_DESTBLT),                  \
    DDCAPDEF("DESTBLTCLRSPACE",         dwCKeyCaps, DDCKEYCAPS_DESTBLTCLRSPACE),          \
    DDCAPDEF("DESTBLTCLRSPACEYUV",      dwCKeyCaps, DDCKEYCAPS_DESTBLTCLRSPACEYUV),       \
    DDCAPDEF("DESTBLTYUV",              dwCKeyCaps, DDCKEYCAPS_DESTBLTYUV),               \
    DDCAPDEF("DESTOVERLAY",             dwCKeyCaps, DDCKEYCAPS_DESTOVERLAY),              \
    DDCAPDEF("DESTOVERLAYCLRSPACE",     dwCKeyCaps, DDCKEYCAPS_DESTOVERLAYCLRSPACE),      \
    DDCAPDEF("DESTOVERLAYCLRSPACEYUV",  dwCKeyCaps, DDCKEYCAPS_DESTOVERLAYCLRSPACEYUV),   \
    DDCAPDEF("DESTOVERLAYONEACTIVE",    dwCKeyCaps, DDCKEYCAPS_DESTOVERLAYONEACTIVE),     \
    DDCAPDEF("DESTOVERLAYYUV",          dwCKeyCaps, DDCKEYCAPS_DESTOVERLAYYUV),           \
    DDCAPDEF("SRCBLT",                  dwCKeyCaps, DDCKEYCAPS_SRCBLT),                   \
    DDCAPDEF("SRCBLTCLRSPACE",          dwCKeyCaps, DDCKEYCAPS_SRCBLTCLRSPACE),           \
    DDCAPDEF("SRCBLTCLRSPACEYUV",       dwCKeyCaps, DDCKEYCAPS_SRCBLTCLRSPACEYUV),        \
    DDCAPDEF("SRCBLTYUV",               dwCKeyCaps, DDCKEYCAPS_SRCBLTYUV),                \
    DDCAPDEF("SRCOVERLAY",              dwCKeyCaps, DDCKEYCAPS_SRCOVERLAY),               \
    DDCAPDEF("SRCOVERLAYCLRSPACE",      dwCKeyCaps, DDCKEYCAPS_SRCOVERLAYCLRSPACE),       \
    DDCAPDEF("SRCOVERLAYCLRSPACEYUV",   dwCKeyCaps, DDCKEYCAPS_SRCOVERLAYCLRSPACEYUV),    \
    DDCAPDEF("SRCOVERLAYONEACTIVE",     dwCKeyCaps, DDCKEYCAPS_SRCOVERLAYONEACTIVE),      \
    DDCAPDEF("SRCOVERLAYYUV",           dwCKeyCaps, DDCKEYCAPS_SRCOVERLAYYUV),

CAPDEF CKeyCapsDefs[] =
{
    GEN_CKCAPS(dwCKeyCaps)
    { "", 0, 0}
};
CAPDEF VSBCKeyCapsDefs[] =
{
    GEN_CKCAPS(dwVSBCKeyCaps)
    { "", 0, 0}
};
CAPDEF SVBCKeyCapsDefs[] =
{
    GEN_CKCAPS(dwSVBCKeyCaps)
    { "", 0, 0}
};
CAPDEF SSBCKeyCapsDefs[] =
{
    GEN_CKCAPS(dwSSBCKeyCaps)
    { "", 0, 0}
};
CAPDEF NLVBCKeyCapsDefs[] =
{
    GEN_CKCAPS(dwNLVBCKeyCaps)
    { "", 0, 0}
};


/****************************************************************************
 ***************************************************************************/
#define GEN_FXCAPS(dwFXCaps)                                                            \
    DDCAPDEF("BLTARITHSTRETCHY",          dwFXCaps, DDFXCAPS_BLTARITHSTRETCHY),         \
    DDCAPDEF("BLTARITHSTRETCHYN",         dwFXCaps, DDFXCAPS_BLTARITHSTRETCHYN),        \
    DDCAPDEF("BLTMIRRORLEFTRIGHT",        dwFXCaps, DDFXCAPS_BLTMIRRORLEFTRIGHT),       \
    DDCAPDEF("BLTMIRRORUPDOWN",           dwFXCaps, DDFXCAPS_BLTMIRRORUPDOWN),          \
    DDCAPDEF("BLTROTATION",               dwFXCaps, DDFXCAPS_BLTROTATION),              \
    DDCAPDEF("BLTROTATION90",             dwFXCaps, DDFXCAPS_BLTROTATION90),            \
    DDCAPDEF("BLTSHRINKX",                dwFXCaps, DDFXCAPS_BLTSHRINKX),               \
    DDCAPDEF("BLTSHRINKXN",               dwFXCaps, DDFXCAPS_BLTSHRINKXN),              \
    DDCAPDEF("BLTSHRINKY",                dwFXCaps, DDFXCAPS_BLTSHRINKY),               \
    DDCAPDEF("BLTSHRINKYN",               dwFXCaps, DDFXCAPS_BLTSHRINKYN),              \
    DDCAPDEF("BLTSTRETCHX",               dwFXCaps, DDFXCAPS_BLTSTRETCHX),              \
    DDCAPDEF("BLTSTRETCHXN",              dwFXCaps, DDFXCAPS_BLTSTRETCHXN),             \
    DDCAPDEF("BLTSTRETCHY",               dwFXCaps, DDFXCAPS_BLTSTRETCHY),              \
    DDCAPDEF("BLTSTRETCHYN",              dwFXCaps, DDFXCAPS_BLTSTRETCHYN),             \
    DDCAPDEF("OVERLAYARITHSTRETCHY",      dwFXCaps, DDFXCAPS_OVERLAYARITHSTRETCHY),     \
    DDCAPDEF("OVERLAYARITHSTRETCHYN",     dwFXCaps, DDFXCAPS_OVERLAYARITHSTRETCHYN),    \
    DDCAPDEF("OVERLAYSHRINKX",            dwFXCaps, DDFXCAPS_OVERLAYSHRINKX),           \
    DDCAPDEF("OVERLAYSHRINKXN",           dwFXCaps, DDFXCAPS_OVERLAYSHRINKXN),          \
    DDCAPDEF("OVERLAYSHRINKY",            dwFXCaps, DDFXCAPS_OVERLAYSHRINKY),           \
    DDCAPDEF("OVERLAYSHRINKYN",           dwFXCaps, DDFXCAPS_OVERLAYSHRINKYN),          \
    DDCAPDEF("OVERLAYSTRETCHX",           dwFXCaps, DDFXCAPS_OVERLAYSTRETCHX),          \
    DDCAPDEF("OVERLAYSTRETCHXN",          dwFXCaps, DDFXCAPS_OVERLAYSTRETCHXN),         \
    DDCAPDEF("OVERLAYSTRETCHY",           dwFXCaps, DDFXCAPS_OVERLAYSTRETCHY),          \
    DDCAPDEF("OVERLAYSTRETCHYN",          dwFXCaps, DDFXCAPS_OVERLAYSTRETCHYN),         \
    DDCAPDEF("OVERLAYMIRRORLEFTRIGHT",    dwFXCaps, DDFXCAPS_OVERLAYMIRRORLEFTRIGHT),   \
    DDCAPDEF("OVERLAYMIRRORUPDOWN",       dwFXCaps, DDFXCAPS_OVERLAYMIRRORUPDOWN),

CAPDEF FXCapsDefs[] =
{
    GEN_FXCAPS(dwFXCaps)
    { "", 0, 0}
};
CAPDEF VSBFXCapsDefs[] =
{
    GEN_FXCAPS(dwVSBFXCaps)
    { "", 0, 0}
};
CAPDEF SVBFXCapsDefs[] =
{
    GEN_FXCAPS(dwSVBFXCaps)
    { "", 0, 0}
};
CAPDEF SSBFXCapsDefs[] =
{
    GEN_FXCAPS(dwSSBFXCaps)
    { "", 0, 0}
};
CAPDEF NLVBFXCapsDefs[] =
{
    GEN_FXCAPS(dwNLVBFXCaps)
    { "", 0, 0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF PalCapsDefs[] =
{
    DDCAPDEF("4BIT",              dwPalCaps, DDPCAPS_4BIT),
    DDCAPDEF("8BITENTRIES",       dwPalCaps, DDPCAPS_8BITENTRIES),
    DDCAPDEF("8BIT",              dwPalCaps, DDPCAPS_8BIT),
    DDCAPDEF("INITIALIZE",        dwPalCaps, DDPCAPS_INITIALIZE),
    DDCAPDEF("PRIMARYSURFACE",    dwPalCaps, DDPCAPS_PRIMARYSURFACE),
    DDCAPDEF("PRIMARYSURFACELEFT",dwPalCaps, DDPCAPS_PRIMARYSURFACELEFT),
    DDCAPDEF("VSYNC",             dwPalCaps, DDPCAPS_VSYNC),
    { "", 0, 0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF SurfCapsDefs[] =
{
    DDCAPDEF( "3DDEVICE",             ddsCaps.dwCaps, DDSCAPS_3DDEVICE),
    DDCAPDEF( "ALPHA",                ddsCaps.dwCaps, DDSCAPS_ALPHA),
    DDCAPDEF( "BACKBUFFER",           ddsCaps.dwCaps, DDSCAPS_BACKBUFFER),
    DDCAPDEF( "COMPLEX",              ddsCaps.dwCaps, DDSCAPS_COMPLEX),
    DDCAPDEF( "FLIP",                 ddsCaps.dwCaps, DDSCAPS_FLIP),
    DDCAPDEF( "FRONTBUFFER",          ddsCaps.dwCaps, DDSCAPS_FRONTBUFFER),
    DDCAPDEF( "MIPMAP",               ddsCaps.dwCaps, DDSCAPS_MIPMAP),
    DDCAPDEF( "OFFSCREENPLAIN",       ddsCaps.dwCaps, DDSCAPS_OFFSCREENPLAIN),
    DDCAPDEF( "OVERLAY",              ddsCaps.dwCaps, DDSCAPS_OVERLAY),
    DDCAPDEF( "PALETTE",              ddsCaps.dwCaps, DDSCAPS_PALETTE),
    DDCAPDEF( "PRIMARYSURFACE",       ddsCaps.dwCaps, DDSCAPS_PRIMARYSURFACE),
    DDCAPDEF( "PRIMARYSURFACELEFT",   ddsCaps.dwCaps, DDSCAPS_PRIMARYSURFACELEFT),
    DDCAPDEF( "SYSTEMMEMORY",         ddsCaps.dwCaps, DDSCAPS_SYSTEMMEMORY),
    DDCAPDEF( "TEXTURE",              ddsCaps.dwCaps, DDSCAPS_TEXTURE),
    DDCAPDEF( "VIDEOMEMORY",          ddsCaps.dwCaps, DDSCAPS_VIDEOMEMORY),
    DDCAPDEF( "VISIBLE",              ddsCaps.dwCaps, DDSCAPS_VISIBLE),
    DDCAPDEF( "WRITEONLY",            ddsCaps.dwCaps, DDSCAPS_WRITEONLY),
    DDCAPDEF( "ZBUFFER",              ddsCaps.dwCaps, DDSCAPS_ZBUFFER),
    DDCAPDEF( "OWNDC",                ddsCaps.dwCaps, DDSCAPS_OWNDC),
    DDCAPDEF( "LIVEVIDEO",            ddsCaps.dwCaps, DDSCAPS_LIVEVIDEO),
    DDCAPDEF( "HWCODEC",              ddsCaps.dwCaps, DDSCAPS_HWCODEC),
    DDCAPDEF( "MODEX",                ddsCaps.dwCaps, DDSCAPS_MODEX),
    { "", 0, 0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF SVisionCapsDefs[] =
{
    DDCAPDEF( "ENIGMA",  dwSVCaps, DDSVCAPS_ENIGMA),
    DDCAPDEF( "FLICKER", dwSVCaps, DDSVCAPS_FLICKER),
    DDCAPDEF( "REDBLUE", dwSVCaps, DDSVCAPS_REDBLUE),
    DDCAPDEF( "SPLIT",   dwSVCaps, DDSVCAPS_SPLIT),
    { "", 0, 0}
};

/****************************************************************************
 ***************************************************************************/
#define GEN_ROPS(dwRops)						\
    ROPDEF("SRCCOPY",    dwRops, SRCCOPY),      \
    ROPDEF("SRCPAINT",   dwRops, SRCPAINT),     \
    ROPDEF("SRCAND",     dwRops, SRCAND),       \
    ROPDEF("SRCINVERT",  dwRops, SRCINVERT),    \
    ROPDEF("SRCERASE",   dwRops, SRCERASE),     \
    ROPDEF("NOTSRCCOPY", dwRops, NOTSRCCOPY),   \
    ROPDEF("NOTSRCERASE",dwRops, NOTSRCERASE),  \
    ROPDEF("MERGECOPY",  dwRops, MERGECOPY),    \
    ROPDEF("MERGEPAINT", dwRops, MERGEPAINT),   \
    ROPDEF("PATCOPY",    dwRops, PATCOPY),      \
    ROPDEF("PATPAINT",   dwRops, PATPAINT),     \
    ROPDEF("PATINVERT",  dwRops, PATINVERT),    \
    ROPDEF("DSTINVERT",  dwRops, DSTINVERT),    \
    ROPDEF("BLACKNESS",  dwRops, BLACKNESS),    \
    ROPDEF("WHITENESS",  dwRops, WHITENESS),

CAPDEF ROPCapsDefs[] =
{
    GEN_ROPS(dwRops)
    {"", 0, 0}
};
CAPDEF VSBROPCapsDefs[] =
{
    GEN_ROPS(dwVSBRops)
    {"", 0, 0}
};
CAPDEF SVBROPCapsDefs[] =
{
    GEN_ROPS(dwSVBRops)
    {"", 0, 0}
};
CAPDEF SSBROPCapsDefs[] =
{
    GEN_ROPS(dwSSBRops)
    {"", 0, 0}
};
CAPDEF NLVBROPCapsDefs[] =
{
    GEN_ROPS(dwNLVBRops)
    {"", 0, 0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEFS DDCapDefs[] =
{
    {"",                    NULL,               (LPARAM)0,                  NULL},
    {"Memory",              VidMem,             (LPARAM)0,                  VidMemPrint},

    {"+Caps",               NULL,               (LPARAM)0,                  NULL},
    {"General",             DDAddCaps,          (LPARAM)GenCaps,           DDPrintCaps},
    {"Palette Caps",        DDAddCaps,          (LPARAM)PalCapsDefs,        DDPrintCaps},
    {"Surface Caps",        DDAddCaps,          (LPARAM)SurfCapsDefs,       DDPrintCaps},
    {"Stereo Vision Caps",  DDAddCaps,          (LPARAM)SVisionCapsDefs,    DDPrintCaps},

    {"+Video - Video",      NULL,               (LPARAM)0,                  NULL},
    {"General",             DDAddCaps,          (LPARAM)CapsDefs,           DDPrintCaps},
    {"Color Key",           DDAddCaps,          (LPARAM)CKeyCapsDefs,       DDPrintCaps},
    {"FX",                  DDAddCaps,          (LPARAM)FXCapsDefs,         DDPrintCaps},
    {"ROPS",                DDAddCaps,          (LPARAM)ROPCapsDefs,        DDPrintCaps},
    {"-",                   NULL,               (LPARAM)0,                  NULL},

    {"+System - Video",     NULL,               (LPARAM)0,                  NULL},
    {"General",             DDAddCaps,          (LPARAM)SVBCapsDefs,        DDPrintCaps},
    {"Color Key",           DDAddCaps,          (LPARAM)SVBCKeyCapsDefs,    DDPrintCaps},
    {"FX",                  DDAddCaps,          (LPARAM)SVBFXCapsDefs,      DDPrintCaps},
    {"ROPS",                DDAddCaps,          (LPARAM)SVBROPCapsDefs,     DDPrintCaps},
    {"-",                   NULL,               (LPARAM)0,                  NULL},

    {"+Video - System",     NULL,               (LPARAM)0,                  NULL},
    {"General",             DDAddCaps,          (LPARAM)VSBCapsDefs,        DDPrintCaps},
    {"Color Key",           DDAddCaps,          (LPARAM)SSBCKeyCapsDefs,    DDPrintCaps},
    {"FX",                  DDAddCaps,          (LPARAM)SSBFXCapsDefs,      DDPrintCaps},
    {"ROPS",                DDAddCaps,          (LPARAM)VSBROPCapsDefs,     DDPrintCaps},
    {"-",                   NULL,               (LPARAM)0,                  NULL},

    {"+System - System",    NULL,               (LPARAM)0,                  NULL},
    {"General",             DDAddCaps,          (LPARAM)SSBCapsDefs,        DDPrintCaps},
    {"Color Key",           DDAddCaps,          (LPARAM)SSBCKeyCapsDefs,    DDPrintCaps},
    {"FX",                  DDAddCaps,          (LPARAM)SSBFXCapsDefs,      DDPrintCaps},
    {"ROPS",                DDAddCaps,          (LPARAM)SSBROPCapsDefs,     DDPrintCaps},
    {"-",                   NULL,               (LPARAM)0,                  NULL},

    {"+NonLocal - Video",   NULL,               (LPARAM)0,                  NULL},
    {"General",             DDAddCaps,          (LPARAM)NLVBCapsDefs,       DDPrintCaps},
    {"Color Key",           DDAddCaps,          (LPARAM)NLVBCKeyCapsDefs,   DDPrintCaps},
    {"FX",                  DDAddCaps,          (LPARAM)NLVBFXCapsDefs,     DDPrintCaps},
    {"ROPS",                DDAddCaps,          (LPARAM)NLVBROPCapsDefs,    DDPrintCaps},
    {"-",                   NULL,               (LPARAM)0,                  NULL},

    {"-",                   NULL,               (LPARAM)0,                  NULL},

    {"Video Modes",         DDAddVideoModes,    (LPARAM)0,                  DDPrintVideoModes},
    {"FourCC Formats",      DDFourCCFormat,     (LPARAM)0,                  DDPrintFourCCFormat},
    {"Other",               DDAddCaps,          (LPARAM)OtherInfoDefs,      DDPrintCaps},

    { NULL, 0, 0, NULL}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF ValidFlags[] =
{
    D3CAPDEF("COLORMODEL",            dwFlags, D3DDD_COLORMODEL),           
    D3CAPDEF("DEVCAPS",               dwFlags, D3DDD_DEVCAPS),              
    D3CAPDEF("TRANSFORMCAPS",         dwFlags, D3DDD_TRANSFORMCAPS),        
    D3CAPDEF("LIGHTINGCAPS",          dwFlags, D3DDD_LIGHTINGCAPS),         
    D3CAPDEF("BCLIPPING",             dwFlags, D3DDD_BCLIPPING),            
    D3CAPDEF("LINECAPS",              dwFlags, D3DDD_LINECAPS),             
    D3CAPDEF("TRICAPS",               dwFlags, D3DDD_TRICAPS),              
    D3CAPDEF("DEVICERENDERBITDEPTH",  dwFlags, D3DDD_DEVICERENDERBITDEPTH), 
    D3CAPDEF("DEVICEZBUFFERBITDEPTH", dwFlags, D3DDD_DEVICEZBUFFERBITDEPTH),
    D3CAPDEF("MAXBUFFERSIZE",         dwFlags, D3DDD_MAXBUFFERSIZE),        
    D3CAPDEF("MAXVERTEXCOUNT",        dwFlags, D3DDD_MAXVERTEXCOUNT),       
    {"",0,0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF ColorModel[] =
{
    D3CAPDEF("D3DCOLOR_MONO",           dcmColorModel, D3DCOLOR_MONO),
    D3CAPDEF("D3DCOLOR_RGB",            dcmColorModel, D3DCOLOR_RGB),
    {"",0,0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF DevCaps[] =
{
    D3CAPDEF("SORTINCREASINGZ",             dwDevCaps, D3DDEVCAPS_SORTINCREASINGZ),
    D3CAPDEF("SORTDECREASINGZ",             dwDevCaps, D3DDEVCAPS_SORTDECREASINGZ),
    D3CAPDEF("SORTEXACT",                   dwDevCaps, D3DDEVCAPS_SORTEXACT),
    D3CAPDEF("EXECUTESYSTEMMEMORY",         dwDevCaps, D3DDEVCAPS_EXECUTESYSTEMMEMORY),
    D3CAPDEF("EXECUTEVIDEOMEMORY",          dwDevCaps, D3DDEVCAPS_EXECUTEVIDEOMEMORY),
    D3CAPDEF("TLVERTEXSYSTEMEMORY",         dwDevCaps, D3DDEVCAPS_TLVERTEXSYSTEMMEMORY),
    D3CAPDEF("TLVERTEXVIDEOMEMORY",         dwDevCaps, D3DDEVCAPS_TLVERTEXVIDEOMEMORY),
    D3CAPDEF("TEXTURESYSTEMMEMORY",         dwDevCaps, D3DDEVCAPS_TEXTURESYSTEMMEMORY),
    D3CAPDEF("TEXTUREVIDEOMEMORY",          dwDevCaps, D3DDEVCAPS_TEXTUREVIDEOMEMORY),
    D3CAPDEF("FLOATTLVERTEX"              , dwDevCaps, D3DDEVCAPS_FLOATTLVERTEX),
    D3CAPDEF("DRAWPRIMTLVERTEX"           , dwDevCaps, D3DDEVCAPS_DRAWPRIMTLVERTEX),
    D3CAPDEF("CANRENDERAFTERFLIP"         , dwDevCaps, D3DDEVCAPS_CANRENDERAFTERFLIP),
    D3CAPDEF("TEXTURENONLOCALVIDMEM" , dwDevCaps, D3DDEVCAPS_TEXTURENONLOCALVIDMEM),

    {"",0,0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF TransformCaps[] =
{
    D3CAPDEF("CLIP",  dtcTransformCaps.dwCaps, D3DTRANSFORMCAPS_CLIP),  
    {"",0,0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF LightingCaps[] =
{
    D3CAPDEF("D3DLIGHTINGMODEL_RGB",       dlcLightingCaps.dwLightingModel, D3DLIGHTINGMODEL_RGB),      
    D3CAPDEF("D3DLIGHTINGMODEL_MONO",      dlcLightingCaps.dwLightingModel, D3DLIGHTINGMODEL_MONO),     

    D3CAPDEF("D3DLIGHTCAPS_POINT",         dlcLightingCaps.dwCaps,          D3DLIGHTCAPS_POINT),        
    D3CAPDEF("D3DLIGHTCAPS_SPOT",          dlcLightingCaps.dwCaps,          D3DLIGHTCAPS_SPOT),         
    D3CAPDEF("D3DLIGHTCAPS_DIRECTIONAL",   dlcLightingCaps.dwCaps,          D3DLIGHTCAPS_DIRECTIONAL),  
    D3CAPDEF("D3DLIGHTCAPS_PARALLELPOINT", dlcLightingCaps.dwCaps,          D3DLIGHTCAPS_PARALLELPOINT),
    D3VALDEF("dwNumLights",                dlcLightingCaps.dwNumLights),   
    {"",0,0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF BClipping[] =
{
    D3CAPDEF("bClipping", bClipping, TRUE),
    {"",0,0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF TriMisc[] =
{
    D3CAPDEF("MASKPLANES",            dpcTriCaps.dwMiscCaps,           D3DPMISCCAPS_MASKPLANES),
    D3CAPDEF("MASKZ",                 dpcTriCaps.dwMiscCaps,           D3DPMISCCAPS_MASKZ),
    D3CAPDEF("LINEPATTERNREP",        dpcTriCaps.dwMiscCaps,           D3DPMISCCAPS_LINEPATTERNREP),
    D3CAPDEF("CONFORMANT",            dpcTriCaps.dwMiscCaps,           D3DPMISCCAPS_CONFORMANT),
    D3CAPDEF("CULLNONE",              dpcTriCaps.dwMiscCaps,           D3DPMISCCAPS_CULLNONE),
    D3CAPDEF("CULLCW",                dpcTriCaps.dwMiscCaps,           D3DPMISCCAPS_CULLCW),
    D3CAPDEF("CULLCCW",               dpcTriCaps.dwMiscCaps,           D3DPMISCCAPS_CULLCCW),

    D3CAPDEF("DITHER",              dpcTriCaps.dwRasterCaps,         D3DPRASTERCAPS_DITHER),
    D3CAPDEF("ROP2",                dpcTriCaps.dwRasterCaps,         D3DPRASTERCAPS_ROP2),
    D3CAPDEF("XOR",                 dpcTriCaps.dwRasterCaps,         D3DPRASTERCAPS_XOR),
    D3CAPDEF("PAT",                 dpcTriCaps.dwRasterCaps,         D3DPRASTERCAPS_PAT),
    D3CAPDEF("ZTEST",               dpcTriCaps.dwRasterCaps,         D3DPRASTERCAPS_ZTEST),
    D3CAPDEF("SUBPIXEL",            dpcTriCaps.dwRasterCaps,         D3DPRASTERCAPS_SUBPIXEL),
    D3CAPDEF("SUBPIXELX",           dpcTriCaps.dwRasterCaps,         D3DPRASTERCAPS_SUBPIXELX),
    D3CAPDEF("FOGVERTEX",           dpcTriCaps.dwRasterCaps,         D3DPRASTERCAPS_FOGVERTEX),
    D3CAPDEF("FOGTABLE",            dpcTriCaps.dwRasterCaps,         D3DPRASTERCAPS_FOGTABLE),

    {"",0,0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF TriFog[] =
{
    D3CAPDEF("FOGVERTEX",       dpcTriCaps.dwRasterCaps,         D3DPRASTERCAPS_FOGVERTEX),
    D3CAPDEF("FOGTABLE",        dpcTriCaps.dwRasterCaps,         D3DPRASTERCAPS_FOGTABLE),

    D3CAPDEF("FOG FLAT",        dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_FOGFLAT             ),
    D3CAPDEF("FOG GOURAUD",     dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_FOGGOURAUD          ),
    D3CAPDEF("FOG PHONG",       dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_FOGPHONG            ),

    {"",0,0}
};


/****************************************************************************
 ***************************************************************************/
CAPDEF TriCull[] =
{
    D3CAPDEF("CULL NONE",           dpcTriCaps.dwMiscCaps,           D3DPMISCCAPS_CULLNONE),
    D3CAPDEF("CULL CW",             dpcTriCaps.dwMiscCaps,           D3DPMISCCAPS_CULLCW),
    D3CAPDEF("CULL CCW",            dpcTriCaps.dwMiscCaps,           D3DPMISCCAPS_CULLCCW),

    {"",0,0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF TriTextureBlend[] =
{
    D3CAPDEF("DECAL",           dpcTriCaps.dwTextureBlendCaps,   D3DPTBLENDCAPS_DECAL              ),
    D3CAPDEF("MODULATE",        dpcTriCaps.dwTextureBlendCaps,   D3DPTBLENDCAPS_MODULATE           ),
    D3CAPDEF("DECALALPHA",      dpcTriCaps.dwTextureBlendCaps,   D3DPTBLENDCAPS_DECALALPHA         ),
    D3CAPDEF("MODULATEALPHA",   dpcTriCaps.dwTextureBlendCaps,   D3DPTBLENDCAPS_MODULATEALPHA      ),
    D3CAPDEF("DECALMASK",       dpcTriCaps.dwTextureBlendCaps,   D3DPTBLENDCAPS_DECALMASK          ),
    D3CAPDEF("MODULATEMASK",    dpcTriCaps.dwTextureBlendCaps,   D3DPTBLENDCAPS_MODULATEMASK       ),
    D3CAPDEF("COPY",            dpcTriCaps.dwTextureBlendCaps,   D3DPTBLENDCAPS_COPY               ),

    {"",0,0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF TriTextureFilter[] =
{
    D3CAPDEF("NEAREST",         dpcTriCaps.dwTextureFilterCaps,  D3DPTFILTERCAPS_NEAREST           ),
    D3CAPDEF("LINEAR",          dpcTriCaps.dwTextureFilterCaps,  D3DPTFILTERCAPS_LINEAR            ),
    D3CAPDEF("MIPNEAREST",      dpcTriCaps.dwTextureFilterCaps,  D3DPTFILTERCAPS_MIPNEAREST        ),
    D3CAPDEF("MIPLINEAR",       dpcTriCaps.dwTextureFilterCaps,  D3DPTFILTERCAPS_MIPLINEAR         ),
    D3CAPDEF("LINEARMIPNEAREST",dpcTriCaps.dwTextureFilterCaps,  D3DPTFILTERCAPS_LINEARMIPNEAREST  ),
    D3CAPDEF("LINEARMIPLINEAR", dpcTriCaps.dwTextureFilterCaps,  D3DPTFILTERCAPS_LINEARMIPLINEAR   ),

    {"",0,0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF TriTextureCaps[] =
{
    D3CAPDEF("PERSPECTIVE",     dpcTriCaps.dwTextureCaps,        D3DPTEXTURECAPS_PERSPECTIVE       ),
    D3CAPDEF("POW2",            dpcTriCaps.dwTextureCaps,        D3DPTEXTURECAPS_POW2              ),
    D3CAPDEF("ALPHA",           dpcTriCaps.dwTextureCaps,        D3DPTEXTURECAPS_ALPHA             ),
    D3CAPDEF("TRANSPARENCY",    dpcTriCaps.dwTextureCaps,        D3DPTEXTURECAPS_TRANSPARENCY      ),
    D3CAPDEF("BORDER",          dpcTriCaps.dwTextureCaps,        D3DPTEXTURECAPS_BORDER            ),
    D3CAPDEF("SQUAREONLY",      dpcTriCaps.dwTextureCaps,        D3DPTEXTURECAPS_SQUAREONLY        ),
    
    D3CAPDEF("WRAP",            dpcTriCaps.dwTextureAddressCaps, D3DPTADDRESSCAPS_WRAP             ),
    D3CAPDEF("MIRROR",          dpcTriCaps.dwTextureAddressCaps, D3DPTADDRESSCAPS_MIRROR           ),
    D3CAPDEF("CLAMP",           dpcTriCaps.dwTextureAddressCaps, D3DPTADDRESSCAPS_CLAMP            ),
    D3CAPDEF("BORDER",          dpcTriCaps.dwTextureAddressCaps, D3DPTADDRESSCAPS_BORDER           ),
    D3CAPDEF("INDEPENDENTUV",   dpcTriCaps.dwTextureAddressCaps, D3DPTADDRESSCAPS_INDEPENDENTUV    ),

    {"",0,0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF TriZCmpCaps[] =
{
    D3CAPDEF("NEVER",               dpcTriCaps.dwZCmpCaps,           D3DPCMPCAPS_NEVER                 ),
    D3CAPDEF("LESS",                dpcTriCaps.dwZCmpCaps,           D3DPCMPCAPS_LESS                  ),
    D3CAPDEF("EQUAL",               dpcTriCaps.dwZCmpCaps,           D3DPCMPCAPS_EQUAL                 ),
    D3CAPDEF("LESSEQUAL",           dpcTriCaps.dwZCmpCaps,           D3DPCMPCAPS_LESSEQUAL             ),
    D3CAPDEF("GREATER",             dpcTriCaps.dwZCmpCaps,           D3DPCMPCAPS_GREATER               ),
    D3CAPDEF("NOTEQUAL",            dpcTriCaps.dwZCmpCaps,           D3DPCMPCAPS_NOTEQUAL              ),
    D3CAPDEF("GREATEREQUAL",        dpcTriCaps.dwZCmpCaps,           D3DPCMPCAPS_GREATEREQUAL          ),
    D3CAPDEF("ALWAYS",              dpcTriCaps.dwZCmpCaps,           D3DPCMPCAPS_ALWAYS                ),

    {"",0,0}
};


/****************************************************************************
 ***************************************************************************/
CAPDEF TriACmpCaps[] =
{
    D3CAPDEF("NEVER",                  dpcTriCaps.dwAlphaCmpCaps,       D3DPCMPCAPS_NEVER                 ),
    D3CAPDEF("LESS",                   dpcTriCaps.dwAlphaCmpCaps,       D3DPCMPCAPS_LESS                  ),
    D3CAPDEF("EQUAL",                  dpcTriCaps.dwAlphaCmpCaps,       D3DPCMPCAPS_EQUAL                 ),
    D3CAPDEF("LESSEQUAL",              dpcTriCaps.dwAlphaCmpCaps,       D3DPCMPCAPS_LESSEQUAL             ),
    D3CAPDEF("GREATER",                dpcTriCaps.dwAlphaCmpCaps,       D3DPCMPCAPS_GREATER               ),
    D3CAPDEF("NOTEQUAL",               dpcTriCaps.dwAlphaCmpCaps,       D3DPCMPCAPS_NOTEQUAL              ),
    D3CAPDEF("GREATEREQUAL",           dpcTriCaps.dwAlphaCmpCaps,       D3DPCMPCAPS_GREATEREQUAL          ),
    D3CAPDEF("ALWAYS",                 dpcTriCaps.dwAlphaCmpCaps,       D3DPCMPCAPS_ALWAYS                ),

    {"",0,0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF TriSrcBlendCaps[] =
{
    D3CAPDEF("ZERO",                 dpcTriCaps.dwSrcBlendCaps,       D3DPBLENDCAPS_ZERO                ),
    D3CAPDEF("ONE",                  dpcTriCaps.dwSrcBlendCaps,       D3DPBLENDCAPS_ONE                 ),
    D3CAPDEF("SRCCOLOR",             dpcTriCaps.dwSrcBlendCaps,       D3DPBLENDCAPS_SRCCOLOR            ),
    D3CAPDEF("INVSRCCOLOR",          dpcTriCaps.dwSrcBlendCaps,       D3DPBLENDCAPS_INVSRCCOLOR         ),
    D3CAPDEF("SRCALPHA",             dpcTriCaps.dwSrcBlendCaps,       D3DPBLENDCAPS_SRCALPHA            ),
    D3CAPDEF("INVSRCALPHA",          dpcTriCaps.dwSrcBlendCaps,       D3DPBLENDCAPS_INVSRCALPHA         ),
    D3CAPDEF("DESTALPHA",            dpcTriCaps.dwSrcBlendCaps,       D3DPBLENDCAPS_DESTALPHA           ),
    D3CAPDEF("INVDESTALPHA",         dpcTriCaps.dwSrcBlendCaps,       D3DPBLENDCAPS_INVDESTALPHA        ),
    D3CAPDEF("DESTCOLOR",            dpcTriCaps.dwSrcBlendCaps,       D3DPBLENDCAPS_DESTCOLOR           ),
    D3CAPDEF("INVDESTCOLOR",         dpcTriCaps.dwSrcBlendCaps,       D3DPBLENDCAPS_INVDESTCOLOR        ),
    D3CAPDEF("SRCALPHASAT",          dpcTriCaps.dwSrcBlendCaps,       D3DPBLENDCAPS_SRCALPHASAT         ),
    D3CAPDEF("BOTHSRCALPHA",         dpcTriCaps.dwSrcBlendCaps,       D3DPBLENDCAPS_BOTHSRCALPHA        ),
    D3CAPDEF("BOTHINVSRCALPHA",      dpcTriCaps.dwSrcBlendCaps,       D3DPBLENDCAPS_BOTHINVSRCALPHA     ),

    {"",0,0}
};
    
/****************************************************************************
 ***************************************************************************/
CAPDEF TriDestBlendCaps[] =
{
    D3CAPDEF("ZERO",                 dpcTriCaps.dwDestBlendCaps,      D3DPBLENDCAPS_ZERO                ),
    D3CAPDEF("ONE",                  dpcTriCaps.dwDestBlendCaps,      D3DPBLENDCAPS_ONE                 ),
    D3CAPDEF("SRCCOLOR",             dpcTriCaps.dwDestBlendCaps,      D3DPBLENDCAPS_SRCCOLOR            ),
    D3CAPDEF("INVSRCCOLOR",          dpcTriCaps.dwDestBlendCaps,      D3DPBLENDCAPS_INVSRCCOLOR         ),
    D3CAPDEF("SRCALPHA",             dpcTriCaps.dwDestBlendCaps,      D3DPBLENDCAPS_SRCALPHA            ),
    D3CAPDEF("INVSRCALPHA",          dpcTriCaps.dwDestBlendCaps,      D3DPBLENDCAPS_INVSRCALPHA         ),
    D3CAPDEF("DESTALPHA",            dpcTriCaps.dwDestBlendCaps,      D3DPBLENDCAPS_DESTALPHA           ),
    D3CAPDEF("INVDESTALPHA",         dpcTriCaps.dwDestBlendCaps,      D3DPBLENDCAPS_INVDESTALPHA        ),
    D3CAPDEF("DESTCOLOR",            dpcTriCaps.dwDestBlendCaps,      D3DPBLENDCAPS_DESTCOLOR           ),
    D3CAPDEF("INVDESTCOLOR",         dpcTriCaps.dwDestBlendCaps,      D3DPBLENDCAPS_INVDESTCOLOR        ),
    D3CAPDEF("SRCALPHASAT",          dpcTriCaps.dwDestBlendCaps,      D3DPBLENDCAPS_SRCALPHASAT         ),
    D3CAPDEF("BOTHSRCALPHA",         dpcTriCaps.dwDestBlendCaps,      D3DPBLENDCAPS_BOTHSRCALPHA        ),
    D3CAPDEF("BOTHINVSRCALPHA",      dpcTriCaps.dwDestBlendCaps,      D3DPBLENDCAPS_BOTHINVSRCALPHA     ),

    {"",0,0}
};
    
/****************************************************************************
 ***************************************************************************/
CAPDEF TriShadeCaps[] =
{
    D3CAPDEF("COLOR FLAT MONO",        dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_COLORFLATMONO       ),
    D3CAPDEF("COLOR FLAT RGB",         dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_COLORFLATRGB        ),
    D3CAPDEF("COLOR GOURAUD MONO",     dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_COLORGOURAUDMONO    ),
    D3CAPDEF("COLOR GOURAUD RGB",      dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_COLORGOURAUDRGB     ),
    D3CAPDEF("COLOR PHONG MONO",       dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_COLORPHONGMONO      ),
    D3CAPDEF("COLOR PHONG RGB",        dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_COLORPHONGRGB       ),
    
    D3CAPDEF("SPECULAR FLAT MONO",     dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_SPECULARFLATMONO    ),
    D3CAPDEF("SPECULAR FLAT RGB",      dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_SPECULARFLATRGB     ),
    D3CAPDEF("SPECULAR GOURAUD MONO",  dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_SPECULARGOURAUDMONO ),
    D3CAPDEF("SPECULAR GOURAUD RGB",   dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_SPECULARGOURAUDRGB  ),
    D3CAPDEF("SPECULAR PHONG MONO",    dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_SPECULARPHONGMONO   ),
    D3CAPDEF("SPECULAR PHONG RGB",     dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_SPECULARPHONGRGB    ),
    
    D3CAPDEF("ALPHA FLAT BLEND",       dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_ALPHAFLATBLEND      ),
    D3CAPDEF("ALPHA FLAT STIPPLED",    dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_ALPHAFLATSTIPPLED   ),
    D3CAPDEF("ALPHA GOURAUD BLEND",    dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_ALPHAGOURAUDBLEND   ),
    D3CAPDEF("ALPHA GOURAUD STIPPLED", dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_ALPHAGOURAUDSTIPPLED),
    D3CAPDEF("ALPHA PHONG BLEND",      dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_ALPHAPHONGBLEND     ),
    D3CAPDEF("ALPHA PHONG STIPPLED",   dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_ALPHAPHONGSTIPPLED  ),
    
    D3CAPDEF("FOG FLAT",               dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_FOGFLAT             ),
    D3CAPDEF("FOG GOURAUD",            dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_FOGGOURAUD          ),
    D3CAPDEF("FOG PHONG",              dpcTriCaps.dwShadeCaps,          D3DPSHADECAPS_FOGPHONG            ),
    
    {"",0,0}
};


/****************************************************************************
 ***************************************************************************/
CAPDEF D3dMisc[] =
{
    D3CAPDEF("D3DCOLOR_MONO",         dcmColorModel, D3DCOLOR_MONO),
    D3CAPDEF("D3DCOLOR_RGB",          dcmColorModel, D3DCOLOR_RGB),

    D3CAPDEF("bClipping", bClipping, TRUE),
    D3CAPDEF("CLIP",  dtcTransformCaps.dwCaps, D3DTRANSFORMCAPS_CLIP),  


    D3VALDEF("MaxBufferSize",         dwMaxBufferSize),        
    D3VALDEF("MaxVertexCount",        dwMaxVertexCount),       
    D3HEXDEF("DeviceRenderBitDepth",  dwDeviceRenderBitDepth),
    D3CAPDEF("  8",                   dwDeviceRenderBitDepth, DDBD_8),
    D3CAPDEF("  16",                  dwDeviceRenderBitDepth, DDBD_16),
    D3CAPDEF("  24",                  dwDeviceRenderBitDepth, DDBD_24),
    D3CAPDEF("  32",                  dwDeviceRenderBitDepth, DDBD_32),
    D3HEXDEF("DeviceZBufferBitDepth", dwDeviceZBufferBitDepth),
    D3CAPDEF("  8",                   dwDeviceZBufferBitDepth, DDBD_8),
    D3CAPDEF("  16",                  dwDeviceZBufferBitDepth, DDBD_16),
    D3CAPDEF("  24",                  dwDeviceZBufferBitDepth, DDBD_24),
    D3CAPDEF("  32",                  dwDeviceZBufferBitDepth, DDBD_32),
    D3VALDEF("MinTextureWidth",       dwMinTextureWidth),
    D3VALDEF("MinTextureHeight",      dwMinTextureHeight),
    D3VALDEF("MaxTextureWidth",       dwMaxTextureWidth),
    D3VALDEF("MaxTextureHeight",      dwMaxTextureHeight),
    D3VALDEF("MinStippleWidth",       dwMinStippleWidth),
    D3VALDEF("MaxStippleWidth",       dwMaxStippleWidth),
    D3VALDEF("MinStippleHeight",      dwMinStippleHeight),
    D3VALDEF("MaxStippleHeight",      dwMaxStippleHeight),

    {"",0,0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEFS D3CapDefs[] =
{
    {"",                D3AddCaps, (LPARAM)ValidFlags,       D3PrintCaps},
    {"DevCaps",         D3AddCaps, (LPARAM)DevCaps,          D3PrintCaps},
    {"Misc",            D3AddCaps, (LPARAM)D3dMisc,          D3PrintCaps},
//  {"ColorModel",      D3AddCaps, (LPARAM)ColorModel,       D3PrintCaps},
//  {"TransformCaps",   D3AddCaps, (LPARAM)TransformCaps,    D3PrintCaps},
//  {"BClipping",       D3AddCaps, (LPARAM)BClipping,        D3PrintCaps},
    {"LightingCaps",    D3AddCaps, (LPARAM)LightingCaps,     D3PrintCaps},

    {"+Triangle Caps",      NULL,      (LPARAM)0,                NULL},
    {"Z Compare",           D3AddCaps, (LPARAM)TriZCmpCaps,      D3PrintCaps},
    {"Alpha Compare",       D3AddCaps, (LPARAM)TriACmpCaps,      D3PrintCaps},
    {"Misc",                D3AddCaps, (LPARAM)TriMisc,          D3PrintCaps},
    {"Cull",                D3AddCaps, (LPARAM)TriCull,          D3PrintCaps},
    {"Fog",                 D3AddCaps, (LPARAM)TriFog,           D3PrintCaps},
    {"Texture Caps",        D3AddCaps, (LPARAM)TriTextureCaps,   D3PrintCaps},
    {"Texture Filter",      D3AddCaps, (LPARAM)TriTextureFilter, D3PrintCaps},
    {"Texture Blend",       D3AddCaps, (LPARAM)TriTextureBlend,  D3PrintCaps},
    {"Texture Source Blend",D3AddCaps, (LPARAM)TriSrcBlendCaps,  D3PrintCaps},
    {"Texture Dest Blend",  D3AddCaps, (LPARAM)TriDestBlendCaps, D3PrintCaps},
    {"-",                   NULL,      (LPARAM)0,                NULL},

    {"+Line Caps",          NULL,          (LPARAM)0,                NULL},
    {"Z Compare",           D3AddLineCaps, (LPARAM)TriZCmpCaps,      D3PrintCaps},
    {"Alpha Compare",       D3AddLineCaps, (LPARAM)TriACmpCaps,      D3PrintCaps},
    {"Misc",                D3AddLineCaps, (LPARAM)TriMisc,          D3PrintCaps},
    {"Cull",                D3AddLineCaps, (LPARAM)TriCull,          D3PrintCaps},
    {"Fog",                 D3AddLineCaps, (LPARAM)TriFog,           D3PrintCaps},
    {"Texture Caps",        D3AddLineCaps, (LPARAM)TriTextureCaps,   D3PrintCaps},
    {"Texture Filter",      D3AddLineCaps, (LPARAM)TriTextureFilter, D3PrintCaps},
    {"Texture Blend",       D3AddLineCaps, (LPARAM)TriTextureBlend,  D3PrintCaps},
    {"Texture Source Blend",D3AddLineCaps, (LPARAM)TriSrcBlendCaps,  D3PrintCaps},
    {"Texture Dest Blend",  D3AddLineCaps, (LPARAM)TriDestBlendCaps, D3PrintCaps},
    {"-",                   NULL,          (LPARAM)0,                NULL},

    {"Texture Formats",     D3AddTexF, (LPARAM)0,                0},
    {NULL, 0, 0, NULL}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF DSInfo[] =
{
    DSVALDEF("MinSecondarySampleRate",          dwMinSecondarySampleRate),
    DSVALDEF("MaxSecondarySampleRate",          dwMaxSecondarySampleRate),
    DSVALDEF("PrimaryBuffers",                  dwPrimaryBuffers),
    DSVALDEF("MaxHwMixingAllBuffers",           dwMaxHwMixingAllBuffers),
    DSVALDEF("MaxHwMixingStaticBuffers",        dwMaxHwMixingStaticBuffers),
    DSVALDEF("MaxHwMixingStreamingBuffers",     dwMaxHwMixingStreamingBuffers),
    DSVALDEF("FreeHwMixingAllBuffers",          dwFreeHwMixingAllBuffers),
    DSVALDEF("FreeHwMixingStaticBuffers",       dwFreeHwMixingStaticBuffers),
    DSVALDEF("FreeHwMixingStreamingBuffers",    dwFreeHwMixingStreamingBuffers),
    DSVALDEF("MaxHw3DAllBuffers",               dwMaxHw3DAllBuffers),
    DSVALDEF("MaxHw3DStaticBuffers",            dwMaxHw3DStaticBuffers),
    DSVALDEF("MaxHw3DStreamingBuffers",         dwMaxHw3DStreamingBuffers),
    DSVALDEF("FreeHw3DAllBuffers",              dwFreeHw3DAllBuffers),
    DSVALDEF("FreeHw3DStaticBuffers",           dwFreeHw3DStaticBuffers),
    DSVALDEF("FreeHw3DStreamingBuffers",        dwFreeHw3DStreamingBuffers),
    DSVALDEF("TotalHwMemBytes",                 dwTotalHwMemBytes),
    DSVALDEF("FreeHwMemBytes",                  dwFreeHwMemBytes),
    DSVALDEF("MaxContigFreeHwMemBytes",         dwMaxContigFreeHwMemBytes),
    DSVALDEF("UnlockTransferRateHwBuffers",     dwUnlockTransferRateHwBuffers),
    DSVALDEF("PlayCpuOverheadSwBuffers",        dwPlayCpuOverheadSwBuffers),
    {"", 0, 0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF DSGeneralCaps[] =
{
    DSCAPDEF("PRIMARYMONO",       dwFlags,    DSCAPS_PRIMARYMONO),
    DSCAPDEF("PRIMARYSTEREO",     dwFlags,    DSCAPS_PRIMARYSTEREO),
    DSCAPDEF("PRIMARY8BIT",       dwFlags,    DSCAPS_PRIMARY8BIT),
    DSCAPDEF("PRIMARY16BIT",      dwFlags,    DSCAPS_PRIMARY16BIT),
    DSCAPDEF("CONTINUOUSRATE",    dwFlags,    DSCAPS_CONTINUOUSRATE),
    DSCAPDEF("EMULDRIVER",        dwFlags,    DSCAPS_EMULDRIVER),
    DSCAPDEF("SECONDARYMONO",     dwFlags,    DSCAPS_SECONDARYMONO),
    DSCAPDEF("SECONDARYSTEREO",   dwFlags,    DSCAPS_SECONDARYSTEREO),
    DSCAPDEF("SECONDARY8BIT",     dwFlags,    DSCAPS_SECONDARY8BIT),
    DSCAPDEF("SECONDARY16BIT",    dwFlags,    DSCAPS_SECONDARY16BIT),
    {"", 0, 0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEFS DSCapDefs[] =
{
    {"",                    DSAddCaps,          (LPARAM)DSInfo,         DSPrintCaps},
    {"General",             DSAddCaps,          (LPARAM)DSInfo,         DSPrintCaps},
    {"General Caps",        DSAddCaps,          (LPARAM)DSGeneralCaps,  DSPrintCaps},
    {NULL, 0, 0, NULL}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF DSCInfo[] =
{
    DSCVALDEF("Channels",          dwChannels),
    {"", 0, 0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF DSCGeneralCaps[] =
{
    DSCCAPDEF("EMULDRIVER",        dwFlags,    DSCCAPS_EMULDRIVER),
    DSCCAPDEF("WAVE_FORMAT_1M08",  dwFormats,  WAVE_FORMAT_1M08),
    DSCCAPDEF("WAVE_FORMAT_1S08",  dwFormats,  WAVE_FORMAT_1S08),
    DSCCAPDEF("WAVE_FORMAT_1M16",  dwFormats,  WAVE_FORMAT_1M16),
    DSCCAPDEF("WAVE_FORMAT_1S16",  dwFormats,  WAVE_FORMAT_1S16),
    DSCCAPDEF("WAVE_FORMAT_2M08",  dwFormats,  WAVE_FORMAT_2M08),
    DSCCAPDEF("WAVE_FORMAT_2S08",  dwFormats,  WAVE_FORMAT_2S08),
    DSCCAPDEF("WAVE_FORMAT_2M16",  dwFormats,  WAVE_FORMAT_2M16),
    DSCCAPDEF("WAVE_FORMAT_2S16",  dwFormats,  WAVE_FORMAT_2S16),
    DSCCAPDEF("WAVE_FORMAT_4M08",  dwFormats,  WAVE_FORMAT_4M08),
    DSCCAPDEF("WAVE_FORMAT_4S08",  dwFormats,  WAVE_FORMAT_4S08),
    DSCCAPDEF("WAVE_FORMAT_4M16",  dwFormats,  WAVE_FORMAT_4M16),
    DSCCAPDEF("WAVE_FORMAT_4S16",  dwFormats,  WAVE_FORMAT_4S16),
    {"", 0, 0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEFS DSCCapDefs[] =
{
    {"",                    DSCAddCaps,          (LPARAM)DSCInfo,         DSCPrintCaps},
    {"General",             DSCAddCaps,          (LPARAM)DSCInfo,         DSCPrintCaps},
    {"General Caps",        DSCAddCaps,          (LPARAM)DSCGeneralCaps,  DSCPrintCaps},
    {NULL, 0, 0, NULL}
};

/****************************************************************************
 ***************************************************************************/
CAPDEF DPInfo[] =
{
    DPVALDEF("Size",                dwSize),
    DPHEXDEF("Flags",               dwFlags),
    DPVALDEF("MaxBufferSize",       dwMaxBufferSize),
    DPVALDEF("MaxQueueSize",        dwMaxQueueSize),
    DPVALDEF("MaxPlayers",          dwMaxPlayers),
    DPVALDEF("HundredBaud",         dwHundredBaud),
    DPVALDEF("Latency",             dwLatency),
    DPVALDEF("MaxLocalPlayers",     dwMaxLocalPlayers),
    DPVALDEF("HeaderLength",        dwHeaderLength),
    DPVALDEF("Timeout",             dwTimeout),
    {"", 0, 0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEFS DPCapDefs[] =
{
    {"",                    DPAddCaps,			(LPARAM)DPInfo,			  DPPrintCaps},
    {"Sessions",            DPAddSessions,      (LPARAM)0,            DPPrintSessions},
    {NULL, 0, 0}
};

/****************************************************************************
 ***************************************************************************/
CAPDEFS DPLocalAppsDef[] =
{
    {"LocalApplications",	DPAddLocalApps,	(LPARAM)0,	DPPrintLocalApps},
    {NULL, 0, 0}
};

//================================================================
//  WinMain - entry point
//================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    CoInitialize( NULL );
    g_hInstance = hInstance; // Store instance handle in our global variable
    g_idTimer = 0;                  //Used by DPlay
    g_lpLocalApp = NULL;    //Used by DPLay

    // Try to load the dsound.dll
    g_hDSoundLib = LoadLibrary("DSOUND.DLL");
    if (g_hDSoundLib == NULL)
    {       // couldn't load the library so put up a message and quit.
        MessageBox(g_hwndMain, "Could not load DSOUND.DLL", g_szAppName, MB_OK);
        CoUninitialize();
        return 0;       // terminate after showing the message.
    }

    //Create the initial local app list.
    DPAddLocalApps(0L, 0);

    if (InitInstance(hInstance, lpCmdLine, nCmdShow, DXView_WIDTH, DXView_HEIGHT))
    {
        while(GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    if (g_lpLocalApp)
        FreeLocalAppList();

    // Unload dsound.dll
    FreeLibrary(g_hDSoundLib);

    CoUninitialize();
    return(msg.wParam);
}

//================================================================
//  InitInstance - create main window
//================================================================
BOOL InitInstance(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow, int iWidth, int iHeight)
{
    WNDCLASS  wc;

    wc.style         = CS_HREDRAW | CS_VREDRAW; // Class style(s).
    wc.lpfnWndProc   = (WNDPROC)WndProc;        // Window Procedure
    wc.cbClsExtra    = 0;                       // No per-class extra data.
    wc.cbWndExtra    = 0;                       // No per-window extra data.
    wc.hInstance     = hInstance;               // Owner of this class
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIRECTX)); // Icon name from .RC
    wc.hCursor       = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_SPLIT));// Cursor
    wc.hbrBackground = (HBRUSH)(COLOR_3DFACE+1); // Default color
    wc.lpszMenuName  = "Menu";                   // Menu name from .RC
    wc.lpszClassName = g_szClassName;            // Name to register as

    if(!RegisterClass(&wc))
    {
        return FALSE;
    }

    // Create a main window for this application instance.
    g_hwndMain = CreateWindowEx(
        0,
        g_szClassName,   // See RegisterClass() call.
        g_szTitle,       // Text for window title bar.
        WS_OVERLAPPEDWINDOW,// Window style.
        CW_USEDEFAULT, CW_USEDEFAULT, iWidth, iHeight, // Use default positioning
        NULL,            // Overlapped windows have no parent.
        NULL,            // Use the window class menu.
        hInstance,       // This instance owns this window.
        NULL);

    // If window could not be created, return "failure"
    if (! g_hwndMain)
    {
        return(FALSE);
    }

    // Make the window visible; update its client area; and return "success"
    ShowWindow (g_hwndMain, nCmdShow); // Show the window

    return(TRUE);              // We succeeded...
}

//================================================================
//  WndProc - main window proc
//================================================================
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_CREATE:
            return DXView_OnCreate(hwnd);

        case WM_SIZE:
            DXView_OnSize(hwnd);
            break;

        case WM_LBUTTONDOWN:
            g_bSplitMove = TRUE;
            SetCapture(hwnd);
            break;

        case WM_LBUTTONUP:
            g_bSplitMove = FALSE;
            ReleaseCapture();
            break;

        case WM_MOUSEMOVE:
            if(g_bSplitMove)
            {
                RECT    rect;
                // change the value from unsigned to signed
                int     x = (int)(short)LOWORD(lParam);

                GetClientRect(hwnd, &rect);
                if (rect.left > x)
                {
                    x = rect.left;
                }
                else if (rect.right < x)
                {
                    x = rect.right;
                }
                g_xPaneSplit = (x - g_xHalfSplitWidth);
                DXView_OnSize(hwnd);
            }
            break;

        case WM_NOTIFY:
            if (((NMHDR*)lParam)->hwndFrom == g_hwndTV)
            {
                if (((NMHDR*)lParam)->code == TVN_SELCHANGED)
                    DXView_OnTreeSelect(g_hwndTV, (NM_TREEVIEW*)lParam);
            }

            if (((NMHDR*)lParam)->hwndFrom == g_hwndLV)
            {
                if (((NMHDR*)lParam)->code == NM_RDBLCLK)
                    DXView_OnListViewDblClick(g_hwndLV, (NM_LISTVIEW*)lParam);
            }

            break;

       case WM_TIMER:
			// refresh the session list
			EnumSessions( lpDP3A );
			break;

       case WM_COMMAND:  // message: command from application menu
            DXView_OnCommand(hwnd, wParam);
            break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;

        case WM_DESTROY:  // message: window being destroyed
            DXView_Cleanup();  // Free per item struct for all items
            PostQuitMessage(0);
            break;
    }

    return(DefWindowProc(hwnd, message, wParam, lParam));
}

//================================================================
//================================================================
BOOL DXView_OnCreate(HWND hwnd)
{
    HDC hDC;
    int PixelsPerInch;
    TEXTMETRIC tm;
    static TCHAR szBuf[MAX_PATH];

    hDC = GetDC(hwnd);
    PixelsPerInch = GetDeviceCaps(hDC, LOGPIXELSX);
    g_hFont = GetStockObject(ANSI_FIXED_FONT);
    SelectObject(hDC, g_hFont);
    GetTextMetrics(hDC, &tm);
    g_tmAveCharWidth = tm.tmAveCharWidth;
    ReleaseDC(hwnd, hDC);

    // Initialize global data
    g_dwViewState = IDM_VIEWAVAIL;
    g_xPaneSplit = PixelsPerInch * 12 / 4;
    g_xHalfSplitWidth = GetSystemMetrics(SM_CXSIZEFRAME) / 2;

    // Make sure that the common control library read to rock
    InitCommonControls();

    CheckMenuItem(GetMenu(hwnd), g_dwViewState, MF_BYCOMMAND | MF_CHECKED);

    // Create the list view window.
    g_hwndLV = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, "",
        WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT,
        0, 0, 0, 0, hwnd, (HMENU)IDC_LV, g_hInstance, NULL);

    // create the tree view window.
    g_hwndTV = CreateWindowEx(WS_EX_CLIENTEDGE, WC_TREEVIEW, "",
        WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES |
        TVS_HASBUTTONS | TVS_LINESATROOT,
        0, 0, 0, 0, hwnd, (HMENU)IDC_TV, g_hInstance, NULL);

    // create our image list.
    DXView_InitImageList();

    // Initialize the tree view
    DXView_FillTree(g_hwndTV);

    return(TRUE);
}

//================================================================
//================================================================
IDirectDraw * DDCreate(GUID *pid)
{
    if (lpDD && pid == ddid)
        return lpDD;

    if (lp3D)
    {
        IDirect3D2_Release(lp3D);
        lp3D = NULL;
    }

    if (lpDD)
    {
        IDirectDraw_Release(lpDD);
        lpDD = NULL;
    }

    // There is no need to create DirectDraw emulation-only just to get
    // the HEL caps.  In fact, this will fail if there is another DirectDraw
    // app running and using the hardware.
    if( pid == (GUID *)DDCREATE_EMULATIONONLY )
    {
        pid = NULL;
    }
    if (DirectDrawCreate(pid, &lpDD, NULL) == DD_OK)
    {
        IDirectDraw_QueryInterface(lpDD,&IID_IDirect3D2,&lp3D);
        ddid = pid;
        return lpDD;
    }
    if(!g_PrintToFile)
        MessageBox(g_hwndMain, "DirectDrawCreate failed.", g_szAppName, MB_OK);
    return NULL;
}

//================================================================
//================================================================
IDirectSound * DSCreate(GUID *pid)
{
	PFN_DSCREATE pfn_DSCreate;

    if (lpDS && pid == dsid)
        return lpDS;

    if (lpDS)
    {
        IDirectSound_Release(lpDS);
        lpDS = NULL;
    }

	// Call DirectSoundCreate.
	pfn_DSCreate = (PFN_DSCREATE)GetProcAddress(g_hDSoundLib, "DirectSoundCreate");
	if (pfn_DSCreate == NULL)
	{
        MessageBox(g_hwndMain, "DSOUND.DLL does not implement DirectSoundCreate()", g_szAppName, MB_OK);		
		return NULL;
	}

	if ((*pfn_DSCreate)(pid, &lpDS, NULL) == DD_OK)
	{
		dsid = pid;
		return lpDS;
	}

    if(!g_PrintToFile)
        MessageBox(g_hwndMain, "DirectSoundCreate failed.", g_szAppName, MB_OK);
    return NULL;
}

//================================================================
//================================================================
IDirectSoundCapture * DSCCreate(GUID *pid)
{
	PFN_DSCCREATE pfn_DSCCreate;

    if (lpDSC && pid == dsid)
        return lpDSC;

    if (lpDSC)
    {
        IDirectSoundCapture_Release(lpDSC);
        lpDSC = NULL;
    }

	pfn_DSCCreate = (PFN_DSCCREATE)GetProcAddress(g_hDSoundLib, "DirectSoundCaptureCreate");
	if (pfn_DSCCreate == NULL)
	{
        MessageBox(g_hwndMain, "DSOUND.DLL does not implement DirectSoundCaptureCreate()", g_szAppName, MB_OK);		
		return NULL;
	}
	
	if ((*pfn_DSCCreate)(pid, &lpDSC, NULL) == DD_OK)
	{
        dscid = pid;
        return lpDSC;
	}

    if(!g_PrintToFile)
        MessageBox(g_hwndMain, "DirectSoundCaptureCreate failed.", g_szAppName, MB_OK);
    return NULL;
}

//================================================================
//================================================================
IDirectPlay3 * DPCreate(GUID *pid)
{
	LPDIRECTPLAY	lpDP = NULL;
	HRESULT	hr;

    if (lpDP3A && pid == dpid)
        return lpDP3A;

    if (lpDP3A)
	{
        lpDP3A->lpVtbl->Release(lpDP3A);
		lpDP3A = NULL;
	}

    if (DirectPlayCreate(pid, &lpDP, NULL) == DD_OK)
    {
        hr = lpDP->lpVtbl->QueryInterface( lpDP, &IID_IDirectPlay3A, (LPVOID *) &lpDP3A );
		lpDP->lpVtbl->Release(lpDP);
		dpid = pid;
        return lpDP3A;
    }
    if(!g_PrintToFile)
        MessageBox(g_hwndMain, "DirectPlayCreate failed.", g_szAppName, MB_OK);
    return NULL;
}

//================================================================
//================================================================
void AddCapsToTV(HTREEITEM hRoot, CAPDEFS *pcds, LPARAM lParam1)
{
    HTREEITEM hTree;
    HTREEITEM hParent[20];
    char *name;
    int level=0;
    BOOL fRoot = TRUE; // the first one is always a root

    hParent[0] = hRoot;

    while (name = pcds->szName)
    {
        if (*name == '-')
        {
            level--;
            name++;
        }

        if (*name == '+')
        {
            fRoot = TRUE;
            name++;
        }

        if (*name)
        {
            hTree = TVAddNode(hParent[level], name, fRoot, IDI_CAPS,
                              pcds->Callback, lParam1,
                              pcds->lParam2, pcds->printCallback);

            if (fRoot)
            {
                level++;
                hParent[level] = hTree;
                fRoot = FALSE;
            }
        }

        pcds++;  // Get next Cap bit definition
    }
}

//================================================================
//================================================================
char c_szYes[] = "Yes";
char c_szNo[] = "No";
char c_szCurrentMode[] = "Current Mode";

//================================================================
// AddMoreCapsToLV is like AddCapsToLV, except it doesn't add the
// column headers like AddCapsToLV does.
//================================================================
void AddMoreCapsToLV(CAPDEF *pcd, LPVOID pv)
{
    DWORD dwValue;

    while(pcd->szName && *pcd->szName)
    {
        dwValue = *(DWORD *)(((BYTE *)pv) + pcd->dwOffset);

        if (pcd->dwFlag == 0)
        {
            LVAddText(g_hwndLV, 0, "%s", pcd->szName);
            LVAddText(g_hwndLV, 1, "%d", dwValue);
        }
        else if (pcd->dwFlag == 0xFFFFFFFF)     // hex
        {
            LVAddText(g_hwndLV, 0, "%s", pcd->szName);
            LVAddText(g_hwndLV, 1, "0x%08X", dwValue);
        }
        else
        {
            if (pcd->dwFlag & dwValue)
            {
                LVAddText(g_hwndLV, 0, pcd->szName);
                LVAddText(g_hwndLV, 1, c_szYes);
            }
            else if (g_dwViewState == IDM_VIEWALL)
            {
                LVAddText(g_hwndLV, 0, pcd->szName);
                LVAddText(g_hwndLV, 1, c_szNo);
            }
        }

        pcd++;  // Get next Cap bit definition
    }
}


//================================================================
// AddColsToLV adds the column headers but no data.
//================================================================
void AddColsToLV(void)
{
    LVAddColumn(g_hwndLV, 0, "Name", 24);
    LVAddColumn(g_hwndLV, 1, "Value", 10);
}

//================================================================
//================================================================
void AddCapsToLV(CAPDEF *pcd, LPVOID pv)
{
    AddColsToLV();
    AddMoreCapsToLV(pcd, pv);
}

//================================================================
//================================================================
BOOL PrintCapsToDC(CAPDEF *pcd, LPVOID pv, PRINTCBINFO * lpInfo)
{
    DWORD dwValue;
    DWORD cchLen;
    int   xName, xVal, yLine;

    // Check Parameters
    if ((! pcd) || (!lpInfo))
        return FALSE;

    // Calculate Name and Value column x offsets
    xName   = (lpInfo->dwCurrIndent * DEF_TAB_SIZE * lpInfo->dwCharWidth);
    xVal    = xName + (32 * lpInfo->dwCharWidth);

    while (pcd->szName && *pcd->szName)
    {
        dwValue = *(DWORD *)(((BYTE *)pv) + pcd->dwOffset);
        yLine = lpInfo->dwCurrLine * lpInfo->dwLineHeight;

        if (pcd->dwFlag)
        {
            if (pcd->dwFlag & dwValue)
            {
                // Print Name
                cchLen = _tcslen (pcd->szName);
                if (! PrintLine (xName, yLine, pcd->szName, cchLen, lpInfo))
                    return FALSE;

                // Print Yes in value column
                cchLen = _tcslen (c_szYes);
                if (! PrintLine (xVal, yLine, c_szYes, cchLen, lpInfo))
                    return FALSE;
        
                // Advance to next line on page
                if (! PrintNextLine (lpInfo))
                    return FALSE;
            }
            else if (g_dwViewState == IDM_VIEWALL)
            {
                // Print name
                cchLen = _tcslen (pcd->szName);
                if (! PrintLine (xName, yLine, pcd->szName, cchLen, lpInfo))
                    return FALSE;

                // Print No in value column
                cchLen = _tcslen (c_szNo);
                if (! PrintLine (xVal, yLine, c_szNo, cchLen, lpInfo))
                    return FALSE;

                // Advance to next line on page
                if (! PrintNextLine (lpInfo))
                    return FALSE;
            }
        }
        else
        {
            char    szBuff[80];

            // Print name
            wsprintf (szBuff, pcd->szName, "test");
            cchLen = _tcslen (pcd->szName);
            if (! PrintLine (xName, yLine, szBuff, cchLen, lpInfo))
                return FALSE;

            // Print value
            wsprintf (szBuff, "%d", dwValue);
            cchLen = _tcslen (szBuff);
            if (! PrintLine (xVal, yLine, szBuff, cchLen, lpInfo))
                return FALSE;

            // Advance to next line on page
            if (! PrintNextLine (lpInfo))
                return FALSE;
        }

        pcd++;  // Get next Cap bit definition
    }

    // Success
    return TRUE;
} // End PrintCapsToDC


//================================================================
//================================================================
void DDAddCaps(LPARAM lParam1, LPARAM lParam2)
{
    // lParam1 is the GUID for the driver we should open
    // lParam2 is the CAPDEF table we should use

    if (DDCreate((GUID*)lParam1))
    {
        DDCAPS ddcaps;

        ddcaps.dwSize = sizeof(ddcaps);

        if (lParam1 == DDCREATE_EMULATIONONLY)
            IDirectDraw_GetCaps(lpDD, NULL, &ddcaps);
        else
            IDirectDraw_GetCaps(lpDD, &ddcaps, NULL);

        AddCapsToLV((CAPDEF *)lParam2, (LPVOID)&ddcaps);
    }
}


//================================================================
//================================================================
BOOL DDPrintCaps(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo)
{
    // lParam1 is the GUID for the driver we should open
    // lParam2 is the CAPDEF table we should use

    if (DDCreate((GUID*)lParam1))
    {
        DDCAPS ddcaps;

        ddcaps.dwSize = sizeof(ddcaps);

        if (lParam1 == DDCREATE_EMULATIONONLY)
            IDirectDraw_GetCaps(lpDD, NULL, &ddcaps);
        else
            IDirectDraw_GetCaps(lpDD, &ddcaps, NULL);

        // Print DirectDraw caps
        return PrintCapsToDC((CAPDEF *)lParam2, (LPVOID)&ddcaps, lpInfo);
    }

    // DDCreate failed but keep printing
    return TRUE;
}

//================================================================
//================================================================
void DSAddCaps(LPARAM lParam1, LPARAM lParam2)
{
    // lParam1 is the GUID for the driver we should open
    // lParam2 is the CAPDEF table we should use

    if (DSCreate((GUID*)lParam1))
    {
        DSCAPS dscaps;

        dscaps.dwSize = sizeof(dscaps);

        IDirectSound_GetCaps(lpDS, &dscaps);

        AddCapsToLV((CAPDEF *)lParam2, (LPVOID)&dscaps);
    }
}


//================================================================
//================================================================
BOOL DSPrintCaps(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo)
{
    // lParam1 is the GUID for the driver we should open
    // lParam2 is the CAPDEF table we should use

    if (DSCreate((GUID*)lParam1))
    {
        DSCAPS dscaps;

        dscaps.dwSize = sizeof(dscaps);

        IDirectSound_GetCaps(lpDS, &dscaps);

        // Print DirectSound Caps
        return PrintCapsToDC((CAPDEF *)lParam2, (LPVOID)&dscaps, lpInfo);
    }

    // DSCreate failed but keep printing
    return TRUE;
}


//================================================================
//================================================================
void DSCAddCaps(LPARAM lParam1, LPARAM lParam2)
{
    // lParam1 is the GUID for the driver we should open
    // lParam2 is the CAPDEF table we should use

    if (DSCCreate((GUID*)lParam1))
    {
        DSCCAPS dsccaps;

        dsccaps.dwSize = sizeof(dsccaps);

        IDirectSoundCapture_GetCaps(lpDSC, &dsccaps);

        AddCapsToLV((CAPDEF *)lParam2, (LPVOID)&dsccaps);
    }
}


//================================================================
//================================================================
BOOL DSCPrintCaps(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo)
{
    // lParam1 is the GUID for the driver we should open
    // lParam2 is the CAPDEF table we should use

    if (DSCCreate((GUID*)lParam1))
    {
        DSCCAPS dsccaps;

        dsccaps.dwSize = sizeof(dsccaps);

        IDirectSoundCapture_GetCaps(lpDSC, &dsccaps);

        // Print DirectSound Caps
        return PrintCapsToDC((CAPDEF *)lParam2, (LPVOID)&dsccaps, lpInfo);
    }

    // DSCCreate failed but keep printing
    return TRUE;
}


//================================================================
//================================================================
void DPAddCaps(LPARAM lParam1, LPARAM lParam2)
{
    // lParam1 is the GUID for the driver we should open
    // lParam2 is the CAPDEF table we should use
	HRESULT hr = DPERR_GENERIC;

	CAPDEF * pcd = (CAPDEF *) lParam2;

    if ( DPCreate( (GUID*) lParam1) )
    {
        DPCAPS	dpcaps,
				dpcapsGuar;
		DWORD	dwValue,
				dwValueGuar;

		memset(&dpcaps, 0, sizeof(DPCAPS));
		memset(&dpcapsGuar, 0, sizeof(DPCAPS));

        dpcaps.dwSize = sizeof(DPCAPS);
        dpcapsGuar.dwSize = sizeof(DPCAPS);

        hr = lpDP3A->lpVtbl->GetCaps(lpDP3A, &dpcapsGuar, DPGETCAPS_GUARANTEED);

		if (FAILED(hr))
		{
			return;
		}

        lpDP3A->lpVtbl->GetCaps(lpDP3A, &dpcaps, 0);

		if (FAILED(hr))
		{
			return;
		}

		LVAddColumn(g_hwndLV, 0, "Name", 24);
		LVAddColumn(g_hwndLV, 1, "Non-guaranteed", 16);
		LVAddColumn(g_hwndLV, 2, "Guaranteed", 16);

		while(pcd->szName && *pcd->szName)
		{
			dwValue = *((DWORD *)((BYTE *)&dpcaps + pcd->dwOffset));
			dwValueGuar = *((DWORD *)((BYTE *)&dpcapsGuar + pcd->dwOffset));

			LVAddText(g_hwndLV, 0, pcd->szName, "test");
			LVAddText(g_hwndLV, 1, "%d", dwValue);
			LVAddText(g_hwndLV, 2, "%d", dwValueGuar);
			pcd++;  // Get next Cap bit definition
		}

		LVAddText( g_hwndLV, 0, "Group Optimized" );
		LVAddText( g_hwndLV, 1, ( dpcaps.dwFlags & DPCAPS_GROUPOPTIMIZED ? c_szYes : c_szNo ) );
		LVAddText( g_hwndLV, 2, ( dpcapsGuar.dwFlags & DPCAPS_GROUPOPTIMIZED ? c_szYes : c_szNo ) );

		LVAddText( g_hwndLV, 0, "Guaranteed Optimized" );
		LVAddText( g_hwndLV, 1, ( dpcaps.dwFlags & DPCAPS_GUARANTEEDOPTIMIZED ? c_szYes : c_szNo ) );
		LVAddText( g_hwndLV, 2, ( dpcapsGuar.dwFlags & DPCAPS_GUARANTEEDOPTIMIZED ? c_szYes : c_szNo ) );

		LVAddText( g_hwndLV, 0, "Guaranteed Supported" );
		LVAddText( g_hwndLV, 1, ( dpcaps.dwFlags & DPCAPS_GUARANTEEDSUPPORTED ? c_szYes : c_szNo ) );
		LVAddText( g_hwndLV, 2, ( dpcapsGuar.dwFlags & DPCAPS_GUARANTEEDSUPPORTED ? c_szYes : c_szNo) );

		LVAddText( g_hwndLV, 0, "Keep Alive Optimized" );
		LVAddText( g_hwndLV, 1, ( dpcaps.dwFlags & DPCAPS_KEEPALIVEOPTIMIZED ? c_szYes : c_szNo ) );
		LVAddText( g_hwndLV, 2, ( dpcapsGuar.dwFlags & DPCAPS_KEEPALIVEOPTIMIZED ? c_szYes : c_szNo ) );

		lpDP3A->lpVtbl->Release(lpDP3A);
		lpDP3A = NULL;

    }
}

//================================================================
//================================================================
BOOL FAR PASCAL DPEnumLocalAppsCallback( LPCDPLAPPINFO lpAppInfo, LPVOID lpContext, DWORD dwFlags)
{
	LPLOCALAPP * lp = (LPLOCALAPP *) lpContext;
	LPLOCALAPP lpTemp = NULL;
	WCHAR wszBuffer[128];


	if (StringFromGUID2( &(lpAppInfo->guidApplication), wszBuffer, 128 ))
	{
		char szBuffer[128];

	    wcstombs(szBuffer, wszBuffer, wcslen(wszBuffer)+1);
		if (g_hwndLV)
		{
			//when we are called the first time, 
			//the listview hasn't been created yet.
			LVAddText(g_hwndLV, 0, lpAppInfo->lpszAppNameA);
			LVAddText(g_hwndLV, 1, szBuffer);
		}
	}

	//Add to our local linked list of app names.
	//This list is used to provide the app names when we
	//enumerate sessions later.
	lpTemp = *lp;
	*lp = (LPLOCALAPP) LocalAlloc( LPTR, sizeof( LOCALAPP )+strlen(lpAppInfo->lpszAppNameA)+1 );

	if (*lp)
	{
		(*lp)->guidApplication = lpAppInfo->guidApplication;
		strcpy( (*lp)->szAppNameA, lpAppInfo->lpszAppNameA );
		(*lp)->lpNext = lpTemp;
	}

	return TRUE;
}


//================================================================
//================================================================
void DPAddLocalApps(LPARAM lParam1, LPARAM lParam2)
{
    // lParam1 is the GUID for the driver we should open
    // lParam2 is the CAPDEF table we should use

	LPDIRECTPLAYLOBBYA	lpDPLA	= NULL;
	HRESULT				hr		= DPERR_GENERIC;
    if (g_lpLocalApp)
	{
		FreeLocalAppList();
		g_lpLocalApp = NULL;
	}

	if ( g_hwndLV)
	{
		//When we are called the first time,
		//the list view has not been created yet.
		LVAddColumn(g_hwndLV, 0, "Name", 16);
		LVAddColumn(g_hwndLV, 1, "guidApplication", 48);
	}

    hr = DirectPlayLobbyCreateA(NULL, &lpDPLA, NULL, NULL, 0 );

	if (SUCCEEDED(hr))
	{
		lpDPLA->lpVtbl->EnumLocalApplications(lpDPLA, DPEnumLocalAppsCallback, &g_lpLocalApp, 0 );
		lpDPLA->lpVtbl->Release(lpDPLA);
	}

}


//================================================================
//================================================================
BOOL FAR PASCAL DPEnumLocalAppsPrintCallback( LPCDPLAPPINFO lpAppInfo, LPVOID lpContext, DWORD dwFlags)
{
    int		xName, 
			xGuid,
			yLine;
    PRINTCBINFO * lpInfo = (PRINTCBINFO *) lpContext;
    DWORD cchLen;
	WCHAR wszBuffer[128];
	char szBuffer[128];

    
    if (! lpInfo)
        return FALSE;

    if (dwFlags & DPESC_TIMEDOUT)
    {
        // We could reset lpdwTimeOut and return true to continue waiting
        // NOTE: This does not tell DirectPlay to query again for hosts.
        //       This just gives potentially slow hosts more time to respond
        //       to our initial query.
        return FALSE;  // Stop waiting for hosts
    }

    xName   = (lpInfo->dwCurrIndent * DEF_TAB_SIZE * lpInfo->dwCharWidth);
    xGuid   = xName + (24 * lpInfo->dwCharWidth);
    yLine   = (lpInfo->dwCurrLine * lpInfo->dwLineHeight);

    // Print AppInfo information

	cchLen = strlen (lpAppInfo->lpszAppNameA);
	if (! PrintLine (xName, yLine, lpAppInfo->lpszAppNameA, cchLen, lpInfo))
		return FALSE;

	if (StringFromGUID2( &(lpAppInfo->guidApplication), wszBuffer, 128 ))
	{
	    wcstombs(szBuffer, wszBuffer, wcslen(wszBuffer)+1);
 
		if (! PrintLine (xGuid, yLine, szBuffer, strlen(szBuffer), lpInfo))
			return FALSE;

		// Advance printer one line
		if (! PrintNextLine (lpInfo))
			return FALSE;

	}

	return TRUE;
}


//================================================================
//================================================================
BOOL DPPrintLocalApps(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo)
{
    // lParam1 is the GUID for the driver we should open
    // lParam2 is the CAPDEF table we should use

	LPDIRECTPLAYLOBBYA	lpDPLA = NULL;


    DirectPlayLobbyCreateA(NULL, &lpDPLA, NULL, NULL, 0 );

	if (lpDPLA)
	{
		lpDPLA->lpVtbl->EnumLocalApplications(	lpDPLA, 
												DPEnumLocalAppsPrintCallback, 
												(LPVOID)lpInfo, 
												0 );
		lpDPLA->lpVtbl->Release(lpDPLA);
    }

    // DPLobbyCreate failed but keep printing
    return TRUE;
}


//================================================================
//================================================================
BOOL DPPrintCaps(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo)
{
    // lParam1 is the GUID for the driver we should open
    // lParam2 is the CAPDEF table we should use

    if (DPCreate((GUID*)lParam1))
    {
        DPCAPS dpcaps;
		BOOL	bKeepPrinting;
		HRESULT	hr = DPERR_GENERIC;
		int xName,
			xGuid,
			yLine;

        dpcaps.dwSize = sizeof(dpcaps);
        hr = lpDP3A->lpVtbl->GetCaps(lpDP3A, &dpcaps, 0);

		if (FAILED(hr))
		{
			// GetCaps failed but keep printing
			return TRUE;
		}

		// Advance printer one line
		if (! PrintNextLine (lpInfo))
			return FALSE;

		xName   = (lpInfo->dwCurrIndent * DEF_TAB_SIZE * lpInfo->dwCharWidth);
		xGuid   = xName + (24 * lpInfo->dwCharWidth);
		yLine   = (lpInfo->dwCurrLine * lpInfo->dwLineHeight);

		if (! PrintLine (xName, yLine, "Non-guaranteed", 14, lpInfo))
			return FALSE;

		// Advance printer one line
		if (! PrintNextLine (lpInfo))
			return FALSE;

		// Advance printer one line
		if (! PrintNextLine (lpInfo))
			return FALSE;

        bKeepPrinting = PrintCapsToDC ((CAPDEF *)lParam2, (LPVOID)&dpcaps, lpInfo);

		// Advance printer one line
		if (! PrintNextLine (lpInfo))
			return FALSE;
		// Advance printer one line
		if (! PrintNextLine (lpInfo))
			return FALSE;

		if (bKeepPrinting)
		{
	        hr = lpDP3A->lpVtbl->GetCaps(lpDP3A, &dpcaps, DPGETCAPS_GUARANTEED );
			if (FAILED(hr))
			{
				// GetCaps failed but keep printing
				return TRUE;
			}

			xName   = (lpInfo->dwCurrIndent * DEF_TAB_SIZE * lpInfo->dwCharWidth);
			xGuid   = xName + (24 * lpInfo->dwCharWidth);
			yLine   = (lpInfo->dwCurrLine * lpInfo->dwLineHeight);

			if (! PrintLine (xName, yLine, "Guaranteed", 10, lpInfo))
				return FALSE;

			// Advance printer one line
			if (! PrintNextLine (lpInfo))
				return FALSE;

			// Advance printer one line
			if (! PrintNextLine (lpInfo))
				return FALSE;

			// Print DirectPlay caps
			bKeepPrinting = PrintCapsToDC ((CAPDEF *)lParam2, (LPVOID)&dpcaps, lpInfo);

			// Advance printer one line
			if (! PrintNextLine (lpInfo))
				return FALSE;
		}
		
		return bKeepPrinting;
    }

    // DPCreate failed but keep printing
    return TRUE;
}

//================================================================
//================================================================
void D3AddCaps(LPARAM lParam1, LPARAM lParam2)
{
    // lParam1 is the CAP3DDEVICEDESC Struct
    // lParam2 is the CAPDEF table we should use

    // Unlike other AddCaps function this info has been prethought for us
    // so just print it out.
    AddCapsToLV((CAPDEF *)lParam2, (LPVOID)lParam1);
}

//================================================================
//================================================================
void D3AddLineCaps(LPARAM lParam1, LPARAM lParam2)
{
    // lParam1 is the CAP3DDEVICEDESC Struct
    // lParam2 is the CAPDEF table we should use

    CAP3DDEVICEDESC *p = (CAP3DDEVICEDESC*)lParam1;
    D3DPRIMCAPS     save;

    // slam the line caps over the triangle caps so we can use the
    // same tables
    save = p->d3dDeviceDesc.dpcTriCaps;
    p->d3dDeviceDesc.dpcTriCaps = p->d3dDeviceDesc.dpcLineCaps;
    AddCapsToLV((CAPDEF *)lParam2, (LPVOID)lParam1);
    p->d3dDeviceDesc.dpcTriCaps = save;
}

//================================================================
//================================================================

int BitCount(DWORD dw)
{
    int i;

    for (i=0; dw; dw=dw>>1)
        i += (dw & 1);

    return i;
}

//================================================================
//================================================================
HRESULT CALLBACK EnumTextureCallback(DDSURFACEDESC *pddsd, LPVOID lParam)
{
    DDPIXELFORMAT ddpf = pddsd->ddpfPixelFormat;
    TCHAR ach[80];

    if (ddpf.dwRBitMask == 0 && ddpf.dwGBitMask == 0 && ddpf.dwBBitMask == 0)
        wsprintf(ach, "%d bit", ddpf.dwRGBBitCount);
    else if (BitCount(ddpf.dwRGBAlphaBitMask) == 0)
        wsprintf(ach, "%d bit %d%d%d",
            ddpf.dwRGBBitCount,
            BitCount(ddpf.dwRBitMask),
            BitCount(ddpf.dwGBitMask),
            BitCount(ddpf.dwBBitMask));
    else
        wsprintf(ach, "%d bit %d%d%d%d",
            ddpf.dwRGBBitCount,
            BitCount(ddpf.dwRBitMask),
            BitCount(ddpf.dwGBitMask),
            BitCount(ddpf.dwBBitMask),
            BitCount(ddpf.dwRGBAlphaBitMask));

    LVAddText(g_hwndLV, 0, ach);

    ach[0] = 0;

    if (ddpf.dwFlags & DDPF_RGB)
        lstrcat(ach,"RGB ");
    if (ddpf.dwFlags & DDPF_YUV)
        lstrcat(ach,"YUV ");
    if (ddpf.dwFlags & DDPF_PALETTEINDEXED8)
        lstrcat(ach,"PAL8 ");
    if (ddpf.dwFlags & DDPF_PALETTEINDEXED4)
        lstrcat(ach,"PAL4 ");
    if (ddpf.dwFlags & DDPF_ALPHA)
        lstrcat(ach,"ALPHA ");
    if (ddpf.dwFlags & DDPF_ALPHAPIXELS)
        lstrcat(ach,"ALPHAPIXELS ");

    LVAddText(g_hwndLV, 1, ach);

    return DDENUMRET_OK;
}

//================================================================
//================================================================

void D3AddTexF(LPARAM lParam1, LPARAM lParam2)
{
    // lParam1 is the CAP3DDEVICEDESC Struct
    // lParam2 is 0

    CAP3DDEVICEDESC *p = (CAP3DDEVICEDESC*)lParam1;

    //
    // this is going to be tricky
    // to enum the texture formats we are going to need
    // a Direct3DDevice, to get a device we need a surface
    // to get a surface we might need to chage the video mode!
    // also to create a device we will need a palette in 8 bpp modes!
    // mabey we should just use the primary surface?
    //
    if (DDCreate(p->device) && lp3D)
    {
        IDirectDrawSurface *Surface=NULL;
        IDirectDrawPalette *Palette=NULL;
        IDirect3DDevice2   *Device=NULL;

        DDSURFACEDESC ddsd;
        ZeroMemory(&ddsd, sizeof(ddsd));

        ddsd.dwSize = sizeof(ddsd);
        ddsd.dwFlags = DDSD_CAPS;
        ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE; // | DDSCAPS_VIDEOMEMORY;

        IDirectDraw_SetCooperativeLevel(lpDD, g_hwndMain, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE | DDSCL_NOWINDOWCHANGES);
        IDirectDraw_CreateSurface(lpDD, &ddsd, &Surface, NULL);
        IDirectDraw_SetCooperativeLevel(lpDD, g_hwndMain, DDSCL_NORMAL);

        if (Surface)
        {
            //
            // before we can create a 3D device, we need to
            // attach a palette (8 bpp modes only)
            //
            IDirectDrawSurface_GetSurfaceDesc(Surface, &ddsd);

            if (ddsd.ddpfPixelFormat.dwRGBBitCount == 8)
            {
                HDC hdc;
                PALETTEENTRY ape[256];

                hdc = GetDC(NULL);
                GetSystemPaletteEntries(hdc, 0, 256, ape);
                ReleaseDC(NULL, hdc);

                IDirectDraw_CreatePalette(lpDD, DDPCAPS_8BIT, ape, &Palette, NULL);

                if (Palette)
                {
                    IDirectDrawSurface_SetPalette(Surface, Palette);
                }
            }
        }

        if (Surface)
        {
            IDirect3D2_CreateDevice(lp3D, &p->driver, Surface, &Device);

            if (Device == NULL)
            {
                IDirectDrawSurface_Release(Surface);
                Surface = NULL;

                //
                // we cant create a 3d device for the primary, create a
                // 555 offscreen surface and try that
                //
                ddsd.dwSize = sizeof(ddsd);
                ddsd.dwFlags = DDSD_CAPS | DDSD_PIXELFORMAT | DDSD_HEIGHT | DDSD_WIDTH;
                ddsd.dwWidth = 100;
                ddsd.dwHeight = 100;
                ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE | DDSCAPS_VIDEOMEMORY;
                ddsd.ddpfPixelFormat.dwSize            = sizeof(DDPIXELFORMAT);
                ddsd.ddpfPixelFormat.dwFlags           = DDPF_RGB;
                ddsd.ddpfPixelFormat.dwFourCC          = 0;
                ddsd.ddpfPixelFormat.dwRGBBitCount     = 16;
                ddsd.ddpfPixelFormat.dwRBitMask        = 0x7C00; // 0xF800;
                ddsd.ddpfPixelFormat.dwGBitMask        = 0x03E0; // 0x07E0;
                ddsd.ddpfPixelFormat.dwBBitMask        = 0x001F; // 0x001F;
                ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 0x0000;

                IDirectDraw_CreateSurface(lpDD, &ddsd, &Surface, NULL);

                if (Surface != NULL)
                {
                    IDirect3D2_CreateDevice(lp3D, &p->driver, Surface, &Device);
                }
            }

            if (Device)
            {
                LVAddColumn(g_hwndLV, 0, "Format", 24);
                LVAddColumn(g_hwndLV, 1, "Flags", 24);

                IDirect3DDevice2_EnumTextureFormats(Device, EnumTextureCallback, NULL);
                IDirect3DDevice2_Release(Device);
            }
            else
            {
                LVAddColumn(g_hwndLV, 0, "Message", 50);
                LVAddText(g_hwndLV, 0, "Cant create D3D Device, change display mode.");
            }

            if (Surface)
            {
                IDirectDrawSurface_Release(Surface);
            }

            if (Palette)
            {
                IDirectDrawPalette_Release(Palette);
            }
        }
        else
        {
            LVAddColumn(g_hwndLV, 0, "Message", 50);
            LVAddText(g_hwndLV, 0, "Cant create surface.");
        }
    }
}

//================================================================
//================================================================
BOOL D3PrintCaps(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo)
{
    // lParam1 is the CAP3DDEVICEDESC Struct
    // lParam2 is the CAPDEF table we should use

    // Unlike other PrintCaps function this info has been prethought for us
    // so just print it out.
    return PrintCapsToDC ((CAPDEF *)lParam2, (LPVOID)lParam1, lpInfo);
}

//================================================================
// EnumSessionsCallback
//================================================================
BOOL PASCAL EnumSessionsCallback
(
LPCDPSESSIONDESC2 lpDesc,         // Pointer to Session Description Struct
LPDWORD lpdwTimeOut,          // Used to extend the timeout if hosts aren't responding quickly enough.
DWORD dwFlags,                 // Flags (used to notify us when we've timed out).
LPVOID	lpContext
)
{
	BOOL					bDataAvailable;
	char					szBuffer[128];
	DWORD					dwSize			= 128;
	LPLV_INSTANCEGUIDSTRUCT	lpInstGuidStruct = NULL;
	LV_ITEM					lvi;

	int						i, count;
	BOOL					bGuidNotFound;

	memset( &lvi, 0, sizeof( LV_ITEM ));

    if (dwFlags & DPESC_TIMEDOUT)
    {
        // We could reset lpdwTimeOut and return true to continue waiting
        // NOTE: This does not tell DirectPlay to query again for hosts.
        //       This just gives potentially slow hosts more time to respond
        //       to our initial query.
        return FALSE;  // Stop waiting for hosts
    }

	i = 0;
	count = ListView_GetItemCount( g_hwndLV );
	bGuidNotFound = TRUE;

	while ((bGuidNotFound) && ( i < count))
	{
		lvi.iItem = i;
		lvi.mask = LVIF_PARAM;
		lvi.lParam = 0;

		bDataAvailable =ListView_GetItem( g_hwndLV, &lvi );
		
		if (bDataAvailable)
		{
			lpInstGuidStruct = (LPLV_INSTANCEGUIDSTRUCT) lvi.lParam;
			
			if (lpInstGuidStruct)
			{
				if ( IsEqualGUID(	&(lpDesc->guidInstance),
									&(lpInstGuidStruct->guidInstance) ) )
				{
					//This session is already in our list. Mark that it is active,
					//so it doesn't get deleted when the next timer fires.
					lpInstGuidStruct->dwRefresh = TRUE;
					bGuidNotFound = FALSE;
				}
			}
			else
			{
				//This item has no pointer to a guidInstance, it must be invalid.
				ListView_DeleteItem( g_hwndLV, i);
			}
		}
		else
		{
			//This item has no data, so it must be invalid.
			ListView_DeleteItem( g_hwndLV, i);
		}

		i++;
	}

    if (bGuidNotFound)
	{
		// This session was in our list view. 
		// Add new session information to table
		i = LVAddText(g_hwndLV, 0, ( lpDesc->lpszSessionNameA ? lpDesc->lpszSessionNameA : "<NO SESSION NAME>" ) );

		GetAppName(szBuffer, &(lpDesc->guidApplication), dwSize);
		LVAddText(g_hwndLV, 1, szBuffer);

		LVAddText(g_hwndLV, 2, "%d", lpDesc->dwMaxPlayers);
		LVAddText(g_hwndLV, 3, "%d", lpDesc->dwCurrentPlayers);
		LVAddText(g_hwndLV, 4, (lpDesc->dwFlags&DPSESSION_SECURESERVER ? c_szYes : c_szNo ) );
		LVAddText(g_hwndLV, 5, (lpDesc->dwFlags&DPSESSION_PASSWORDREQUIRED ? c_szYes : c_szNo ));

		//Keep track of our guidInstance so we'll recognize this session
		//when we enumerate later
		lpInstGuidStruct = (LPLV_INSTANCEGUIDSTRUCT) LocalAlloc( LPTR, sizeof(LV_INSTANCEGUIDSTRUCT));

		if (lpInstGuidStruct)
		{
			LV_ITEM	lvi;
			memset( &lvi, 0, sizeof( LV_ITEM));
			lpInstGuidStruct->guidInstance = lpDesc->guidInstance;
			lpInstGuidStruct->dwRefresh = TRUE;

			lvi.iItem = i;
			lvi.mask = LVIF_PARAM;
			lvi.lParam = (long) lpInstGuidStruct;
  
			ListView_SetItem( g_hwndLV, (LPARAM)&lvi, ); 
		}
	}

    //Keep enumerating until it times out on its own.
	return TRUE;
}


//================================================================
// EnumPrintSessionsCallback
//================================================================
BOOL PASCAL EnumPrintSessionsCallback 
(
    LPCDPSESSIONDESC2 lpDesc,         // Pointer to Session Description Struct
    LPDWORD         lpdwTimeOut,    // Used to extend the timeout if hosts aren't responding quickly enough.
    DWORD           dwFlags,         // Flags (used to notify us when we've timed out).
    LPVOID          lpContext         // User definable data passed in from EnumSessions() call.
)
{
    int xName,  yLine;
    PRINTCBINFO * lpInfo = (PRINTCBINFO *) lpContext;
    CHAR szBuff[256],
		 szAppName[128];
    DWORD cchLen;
    
    if (! lpInfo)
        return FALSE;

    if (dwFlags & DPESC_TIMEDOUT)
    {
        // We could reset lpdwTimeOut and return true to continue waiting
        // NOTE: This does not tell DirectPlay to query again for hosts.
        //       This just gives potentially slow hosts more time to respond
        //       to our initial query.
        return FALSE;  // Stop waiting for hosts
    }

    xName   = (lpInfo->dwCurrIndent * DEF_TAB_SIZE * lpInfo->dwCharWidth);
    yLine   = (lpInfo->dwCurrLine * lpInfo->dwLineHeight);

    // Print session information
    wsprintf (szBuff, "Session Name   : %s", lpDesc->lpszSessionNameA);
    cchLen = strlen (szBuff);
    if (! PrintLine (xName, yLine, szBuff, cchLen, lpInfo))
        return FALSE;
    if (! PrintNextLine (lpInfo))
        return FALSE;

    yLine   = (lpInfo->dwCurrLine * lpInfo->dwLineHeight);
	GetAppName( szAppName, &(lpDesc->guidApplication), 128 );
    wsprintf (szBuff, "App Name/GUID  : %s", szAppName);
	cchLen = strlen (szBuff);
    if (! PrintLine (xName, yLine, szBuff, cchLen, lpInfo))
        return FALSE;
    if (! PrintNextLine (lpInfo))
        return FALSE;

    yLine   = (lpInfo->dwCurrLine * lpInfo->dwLineHeight);
    wsprintf (szBuff, "Max Players    : %d", lpDesc->dwMaxPlayers);
    cchLen = strlen (szBuff);
    if (! PrintLine (xName, yLine, szBuff, cchLen, lpInfo))
        return FALSE;
    if (! PrintNextLine (lpInfo))
        return FALSE;

    yLine   = (lpInfo->dwCurrLine * lpInfo->dwLineHeight);
    wsprintf (szBuff, "Cur Players    : %d", lpDesc->dwCurrentPlayers);
    cchLen = strlen (szBuff);
	if (! PrintLine (xName, yLine, szBuff, cchLen, lpInfo))
        return FALSE;
    if (! PrintNextLine (lpInfo))
        return FALSE;

    yLine   = (lpInfo->dwCurrLine * lpInfo->dwLineHeight);
 	wsprintf (szBuff, "Secure Session : %s",(lpDesc->dwFlags&DPSESSION_SECURESERVER ? c_szYes : c_szNo ) ); 
    cchLen = strlen (szBuff);
	if (! PrintLine (xName, yLine, szBuff, cchLen, lpInfo))
        return FALSE;
    if (! PrintNextLine (lpInfo))
        return FALSE;

  
    yLine   = (lpInfo->dwCurrLine * lpInfo->dwLineHeight);
 	wsprintf (szBuff, "Password Req'd : %s",(lpDesc->dwFlags&DPSESSION_PASSWORDREQUIRED  ? c_szYes : c_szNo ) ); 
    cchLen = strlen (szBuff);
	if (! PrintLine (xName, yLine, szBuff, cchLen, lpInfo))
        return FALSE;
    if (! PrintNextLine (lpInfo))
        return FALSE;

	// Advance printer one line
    if (! PrintNextLine (lpInfo))
        return FALSE;

    // Success
    return TRUE;
}

//================================================================
//================================================================
void DPAddSessions(LPARAM lParam1, LPARAM lParam2)
{
    // lParam1 is the GUID for the driver we should open
    // lParam2 is the CAPDEF table we should use
	HRESULT	hr = DPERR_GENERIC;

    if (DPCreate((GUID*)lParam1))
    {
        LVAddColumn(g_hwndLV, 0, "Session Name", 16);
        LVAddColumn(g_hwndLV, 1, "Application Name/GUID", 24);
        LVAddColumn(g_hwndLV, 2, "Max", 4);
        LVAddColumn(g_hwndLV, 3, "Cur", 4);
        LVAddColumn(g_hwndLV, 4, "Sec", 4);
        LVAddColumn(g_hwndLV, 5, "Pwd", 5);

        hr = EnumSessions(	lpDP3A );
		if (SUCCEEDED(hr))
		{
			g_idTimer = SetTimer(g_hwndMain, 1, TIMER_PERIOD, NULL);
		}
    }
}


//================================================================
//================================================================
BOOL DPPrintSessions(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo)
{
    // lParam1 is the GUID for the driver we should open
    // lParam2 is the CAPDEF table we should use

    DPSESSIONDESC2   dps;
    HCURSOR         hCur=NULL;
	HRESULT			hr = DPERR_GENERIC;

    memset(&dps, 0, sizeof(DPSESSIONDESC2));
    dps.dwSize = sizeof(DPSESSIONDESC2);

    hCur=SetCursor(LoadCursor(NULL, IDC_WAIT));

    if (DPCreate((GUID*)lParam1))
    {
        hr = lpDP3A->lpVtbl->EnumSessions (	lpDP3A, &dps, 0, EnumPrintSessionsCallback, 
										(LPVOID)lpInfo, 			
										DPENUMSESSIONS_ALL|
										DPENUMSESSIONS_PASSWORDREQUIRED );

    }

    if (hCur)
        SetCursor(hCur);

    return TRUE;
}

//================================================================
//================================================================
typedef struct LLMode
{
    DWORD x,y,bpp;	
        BOOL IsModeX;
        struct LLMode *Next;
}LinkMode;	

static LinkMode *pModesHead = NULL; 

void DDFourCCFormat(LPARAM lParam1, LPARAM lParam2)
{
    HRESULT ddrval;
    int iNumOfCodes,iCount;
    DWORD *FourCC;
    char szText[5]={0,0,0,0,0};

    if(lpDD != NULL)
    {
        ddrval = IDirectDraw_GetFourCCCodes(lpDD,&iNumOfCodes, NULL);
        LVAddColumn(g_hwndLV, 0, "Codes", 24);
        LVAddColumn(g_hwndLV, 1, "", 24);
        if( ddrval == DD_OK)
        {
            FourCC = GlobalAlloc(GPTR,(sizeof(DWORD)*iNumOfCodes));
            if(FourCC)
            {
                ddrval = IDirectDraw_GetFourCCCodes(lpDD,&iNumOfCodes, FourCC);
                // Assume all FourCC values are ascii strings
                for(iCount = 0;iCount < iNumOfCodes; iCount++)
                {
                    memcpy(szText,&FourCC[iCount],4);
                    LVAddText(g_hwndLV, 0, "%s", szText);
                }
            }
        }
    }
}


//================================================================
//================================================================
BOOL DDPrintFourCCFormat(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo)
{
    HRESULT ddrval;
    int iNumOfCodes,iCount;
    DWORD *FourCC;
    char szText[5]={0,0,0,0,0};
    int  xCode, yLine;


    if(lpDD != NULL)
    {
        ddrval = IDirectDraw_GetFourCCCodes(lpDD,&iNumOfCodes, NULL);
        if( ddrval == DD_OK)
        {
            FourCC = GlobalAlloc(GPTR,(sizeof(DWORD)*iNumOfCodes));
            if(FourCC)
            {
                xCode  = (lpInfo->dwCurrIndent * DEF_TAB_SIZE * lpInfo->dwCharWidth);
                ddrval = IDirectDraw_GetFourCCCodes(lpDD,&iNumOfCodes, FourCC);
                if (ddrval == DD_OK)
                {
                    // Assume all FourCC values are ascii strings
                    for(iCount = 0;iCount < iNumOfCodes; iCount++)
                    {
                        yLine  = (lpInfo->dwCurrLine * lpInfo->dwLineHeight);
    
                        memcpy(szText,&FourCC[iCount],4);
         
                        // Print Code
                        if (! PrintLine (xCode, yLine, szText, 4, lpInfo))
                            return FALSE;

                        if (! PrintNextLine (lpInfo))
                            return FALSE;
                    }
                }
            }
        }
    }

    // Success
    return TRUE;
}


//================================================================
//================================================================

//================================================================
// DisplayEnumModes
//================================================================
HRESULT CALLBACK EnumDisplayModesCallback(LPDDSURFACEDESC pddsd, LPVOID Context)
{
    if(pddsd->ddsCaps.dwCaps & DDSCAPS_STANDARDVGAMODE)
    {
        LVAddText(g_hwndLV, 0, "%dx%dx%d (StandardVGA)", pddsd->dwWidth, pddsd->dwHeight, pddsd->ddpfPixelFormat.dwRGBBitCount);
    }else if(pddsd->ddsCaps.dwCaps & DDSCAPS_MODEX)
    {
        LVAddText(g_hwndLV, 0, "%dx%dx%d (ModeX)", pddsd->dwWidth, pddsd->dwHeight, pddsd->ddpfPixelFormat.dwRGBBitCount);
    }else
    {
        LVAddText(g_hwndLV, 0, "%dx%dx%d ", pddsd->dwWidth, pddsd->dwHeight, pddsd->ddpfPixelFormat.dwRGBBitCount);
    }
    return DDENUMRET_OK;
} /* EnumModesCallback */

HRESULT CALLBACK EnumDisplayModesCallbackPrint(LPDDSURFACEDESC pddsd, LPVOID Context)
{
    TCHAR szBuff[80];
    DWORD cchLen;
    PRINTCBINFO * lpInfo = Context;
    int xMode, yLine;

    if (! lpInfo)
        return FALSE;

    xMode = (lpInfo->dwCurrIndent * DEF_TAB_SIZE * lpInfo->dwCharWidth);
    yLine = (lpInfo->dwCurrLine * lpInfo->dwLineHeight);

    if(pddsd->ddsCaps.dwCaps & DDSCAPS_STANDARDVGAMODE)
    {
        wsprintf(szBuff, TEXT("%dx%dx%d (StandardVGA)"), pddsd->dwWidth, pddsd->dwHeight, pddsd->ddpfPixelFormat.dwRGBBitCount);
    }else if(pddsd->ddsCaps.dwCaps & DDSCAPS_MODEX)
    {
        wsprintf(szBuff, TEXT("%dx%dx%d (ModeX)"), pddsd->dwWidth, pddsd->dwHeight, pddsd->ddpfPixelFormat.dwRGBBitCount);
    }else
    {
        wsprintf(szBuff, TEXT("%dx%dx%d "), pddsd->dwWidth, pddsd->dwHeight, pddsd->ddpfPixelFormat.dwRGBBitCount);
    }
    // Print Mode Info
    cchLen = _tcslen (szBuff);
    if (! PrintLine (xMode, yLine, szBuff, cchLen, lpInfo))
        return DDENUMRET_CANCEL;
    // Advance to next line
    if (! PrintNextLine (lpInfo))
        return DDENUMRET_CANCEL;

	return DDENUMRET_OK;
} /* EnumModesCallback */

//================================================================
// PrintEnumModes
//================================================================
/*BOOL PrintEnumModes ()
{
    LinkMode *tmp= NULL;


    tmp = pModesHead;
    while (tmp != NULL) //cycle though all modes since unique modes don't always happen
    {

        if (tmp->IsModeX)
            wsprintf (szBuff, TEXT("%dx%dx%d (ModeX)"), tmp->x, tmp->y, tmp->bpp);
        else
            wsprintf (szBuff, TEXT("%dx%dx%d "), tmp->x, tmp->y, tmp->bpp);


        tmp = tmp->Next;
    }

    // Success
    return TRUE;
}*/ /* EnumModesCallback */

//================================================================
// Should we hourglass the cursor? this takes a while
//================================================================
void DDAddVideoModes(LPARAM lParam1, LPARAM lParam2)
{
    DWORD mode;
    DDSURFACEDESC ddsd;

    LVAddColumn(g_hwndLV, 0, "Mode", 24);
    LVAddColumn(g_hwndLV, 1, "", 24);

    // lParam1 is the GUID for the driver we should open
    // lParam2 is not used

    if (DDCreate((GUID*)lParam1))
    {
        // Get the current mode mode for this driver
        ddsd.dwSize = sizeof(DDSURFACEDESC);
        IDirectDraw_GetDisplayMode(lpDD, &ddsd);

        mode = MAKEMODE(ddsd.dwWidth, ddsd.dwHeight, ddsd.ddpfPixelFormat.dwRGBBitCount);

        // Find all mode for this driver and add them to the listview
        //Erase previous list
        {
            LinkMode *tmp, *tmp1;	

            tmp = pModesHead;
            while(tmp != NULL)
            {
                tmp1 = tmp;
                tmp = tmp->Next;
                GlobalFree(tmp1);  //Note We will exit with a list in place
            }
            pModesHead = NULL;
        }
        //Get Modes
        IDirectDraw_SetCooperativeLevel(lpDD, g_hwndMain, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE | DDSCL_ALLOWMODEX | DDSCL_NOWINDOWCHANGES);
        IDirectDraw_EnumDisplayModes(lpDD, DDEDM_STANDARDVGAMODES, NULL, (LPVOID)mode, EnumDisplayModesCallback);
        IDirectDraw_SetCooperativeLevel(lpDD, g_hwndMain, DDSCL_NORMAL);
    }
}


//================================================================
// Should we hourglass the cursor? this takes a while
//================================================================
BOOL DDPrintVideoModes(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo)
{
    BOOL  fResult = TRUE;   // Even if we can't enum modes, let's keep on printing other stuff
    DWORD mode;
    DDSURFACEDESC ddsd;

    LVAddColumn(g_hwndLV, 0, "Mode", 24);
    LVAddColumn(g_hwndLV, 1, "", 24);

    // lParam1 is the GUID for the driver we should open
    // lParam2 is not used

    if (DDCreate((GUID*)lParam1))
    {
        // Get the current mode mode for this driver
        ddsd.dwSize = sizeof(DDSURFACEDESC);
        IDirectDraw_GetDisplayMode(lpDD, &ddsd);

        mode = MAKEMODE(ddsd.dwWidth, ddsd.dwHeight, ddsd.ddpfPixelFormat.dwRGBBitCount);

        // Find all mode for this driver and add them to the listview
        //Erase previous list
        {
            LinkMode *tmp, *tmp1;	

            tmp = pModesHead;
            while(tmp != NULL)
            {
                tmp1 = tmp;
                tmp = tmp->Next;
                GlobalFree(tmp1);  //Note We will exit with a list in place
            }
            pModesHead = NULL;
        }

        //Get Mode with ModeX
        IDirectDraw_SetCooperativeLevel(lpDD, g_hwndMain, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE | DDSCL_ALLOWMODEX | DDSCL_NOWINDOWCHANGES);
        IDirectDraw_EnumDisplayModes(lpDD, DDEDM_STANDARDVGAMODES, NULL, (LPVOID)lpInfo, EnumDisplayModesCallbackPrint);
        IDirectDraw_SetCooperativeLevel(lpDD, g_hwndMain, DDSCL_NORMAL);
    }

    // Success
    return fResult;
} // End DDPrintVideoModes


//================================================================
//================================================================
void DXView_OnTreeSelect(HWND hwndTV, NM_TREEVIEW *ptv)
{
    NODEINFO *pni;

    SendMessage(g_hwndLV, WM_SETREDRAW, FALSE, 0);
    LVDeleteAllItems(g_hwndLV);
    LVAddColumn(g_hwndLV, 0, "", 0);

    if (ptv == NULL)
    {
        TV_ITEM tvi;
        // get lParam of current tree node
        tvi.hItem  = TreeView_GetSelection(g_hwndTV);
        tvi.mask   = TVIF_PARAM;
        tvi.lParam = 0;
        TreeView_GetItem(g_hwndTV, &tvi);
        pni = (NODEINFO*)tvi.lParam;
    }
    else
    {
        pni = (NODEINFO*)ptv->itemNew.lParam;
    }

    if (pni && pni->Callback)
    {
        pni->Callback(pni->lParam1, pni->lParam2);
    }

    SendMessage(g_hwndLV, WM_SETREDRAW, TRUE, 0);
    InvalidateRect(g_hwndLV, NULL, TRUE);
}

//================================================================
//================================================================
void DXView_OnListViewDblClick(HWND hwndLV, NM_LISTVIEW *plv)
{
    LV_ITEM lvi;

    lvi.mask   = LVIF_PARAM;
    lvi.lParam = 0;
    lvi.iItem  = plv->iItem;
    ListView_GetItem(hwndLV, &lvi);
}


//================================================================
//================================================================
void DXView_OnCommand(HWND hwnd, WPARAM wParam)
{
    HMENU hMenu;
    BOOL  fPrintAll;

    switch(LOWORD(wParam))
    {
        case IDM_VIEWAVAIL:
        case IDM_VIEWALL:
            hMenu = GetMenu(hwnd);
            CheckMenuItem(hMenu, g_dwViewState, MF_BYCOMMAND | MF_UNCHECKED);
            g_dwViewState = LOWORD(wParam);
            CheckMenuItem(hMenu, g_dwViewState, MF_BYCOMMAND | MF_CHECKED);
            DXView_OnTreeSelect(g_hwndTV, NULL);
            break;

        case IDM_PRINT:
        case IDM_PRINTALL:
            // Print all statistics or just current selection
            if (LOWORD(wParam) == IDM_PRINTALL)
                fPrintAll = TRUE;
            else
                fPrintAll = FALSE;
            // Print out statistics
            DXView_OnPrint (hwnd, g_hwndTV, fPrintAll);
            break;

        case IDM_PRINTTOFILE:
                fPrintAll = TRUE;
                g_PrintToFile = TRUE;
            // Print out statistics
            DXView_OnFile (hwnd, g_hwndTV, fPrintAll);
            break;

        case IDM_ABOUT:
            DialogBox(g_hInstance, "About", hwnd, (DLGPROC)About);
            break;

        case IDM_EXIT:
            PostMessage(hwnd, WM_CLOSE, 0, 0);
            break;
    }
}

//================================================================
//================================================================
void DXView_Cleanup()
{
    if (lp3D)
        IDirect3D2_Release(lp3D);

    if (lpDD)
        IDirectDraw_Release(lpDD);

    if (lpDS)
        IDirectSound_Release(lpDS);

    if (lpDSC)
        IDirectSoundCapture_Release(lpDSC);

    if (lpDP3A)
	{
        lpDP3A->lpVtbl->Release(lpDP3A);
		lpDP3A = NULL;
	}

    if(g_hImageList)
        ImageList_Destroy(g_hImageList);
}

//================================================================
//================================================================
BOOL DXView_InitImageList()
{
    int cxSmIcon;
    int cySmIcon;
    UINT Index;
    HICON hIcon;

    if (g_hImageList)
        return TRUE;

    cxSmIcon = GetSystemMetrics(SM_CXSMICON);
    cySmIcon = GetSystemMetrics(SM_CYSMICON);

    //  First, create the image list that is needed.
    if((g_hImageList = ImageList_Create(cxSmIcon, cySmIcon, TRUE, IDI_LASTIMAGE - IDI_FIRSTIMAGE, 10)) == NULL)
        return(FALSE);

    //
    //  Initialize the image list with all of the icons that we'll be using
    //  Once set, send its handle to all interested child windows.
    //
    for (Index = IDI_FIRSTIMAGE; Index <= IDI_LASTIMAGE; Index++)
    {
        hIcon = LoadImage(g_hInstance, MAKEINTRESOURCE(Index), IMAGE_ICON, cxSmIcon, cySmIcon, 0);
        ImageList_AddIcon(g_hImageList, hIcon);
        DestroyIcon(hIcon);
    }

    TreeView_SetImageList(g_hwndTV, g_hImageList, TVSIL_NORMAL);

    return(TRUE);
}

//================================================================
//================================================================
HRESULT CALLBACK DDEnumCallBack(GUID *pid, LPSTR lpDriverDesc, LPSTR lpDriverName, LPVOID lpContext)
{
    HTREEITEM hParent = (HTREEITEM)lpContext;
    TCHAR szText[256];

    if (HIWORD(pid) != 0)
    {
        GUID temp = *pid;
        pid = (GUID *)LocalAlloc(LPTR, sizeof(GUID));
        *pid = temp;
    }

    // Add subnode to treeview
    if (lpDriverName && *lpDriverName)
        wsprintf(szText, "%s (%s)", lpDriverDesc, lpDriverName);
    else
        lstrcpy(szText, lpDriverDesc);

    DDCapDefs[0].szName = szText;
    AddCapsToTV(hParent, DDCapDefs, (LPARAM)pid);

    return(DDENUMRET_OK);
}

//================================================================
//================================================================
HRESULT CALLBACK DSEnumCallBack(const GUID *lpGUID, LPCSTR lpDriverDesc, LPCSTR lpDriverName, LPVOID lpContext)
{
    HTREEITEM hParent = (HTREEITEM)lpContext;
    TCHAR     szText[256];
    LPGUID    lpTemp = NULL;

    if( lpGUID != NULL )
        {
        if(( lpTemp = LocalAlloc( LPTR, sizeof(GUID))) == NULL )
        return( TRUE );

        memcpy( lpTemp, lpGUID, sizeof(GUID));
    }

    // Add subnode to treeview
    if (lpDriverName && *lpDriverName)
        wsprintf(szText, "%s (%s)", lpDriverDesc, lpDriverName);
    else
        lstrcpy(szText, lpDriverDesc);

    DSCapDefs[0].szName = szText;
    AddCapsToTV(hParent, DSCapDefs, (LPARAM)lpTemp);

    return(DDENUMRET_OK);
}

//================================================================
//================================================================
HRESULT CALLBACK DSCEnumCallBack(const GUID *lpGUID, LPCSTR lpDriverDesc, LPCSTR lpDriverName, LPVOID lpContext)
{
    HTREEITEM hParent = (HTREEITEM)lpContext;
    TCHAR     szText[256];
    LPGUID    lpTemp = NULL;

    if( lpGUID != NULL )
    {
        if(( lpTemp = LocalAlloc( LPTR, sizeof(GUID))) == NULL )
        return( TRUE );

        memcpy( lpTemp, lpGUID, sizeof(GUID));
    }

    // Add subnode to treeview
    if (lpDriverName && *lpDriverName)
        wsprintf(szText, "%s (%s)", lpDriverDesc, lpDriverName);
    else
        lstrcpy(szText, lpDriverDesc);

    DSCCapDefs[0].szName = szText;
    AddCapsToTV(hParent, DSCCapDefs, (LPARAM)lpTemp);

    return(DDENUMRET_OK);
}

//================================================================
//================================================================
BOOL CALLBACK DPEnumCallback(GUID *pid, LPSTR szName, DWORD major_ver, DWORD minor_ver, LPVOID lpContext)
{
    HTREEITEM hParent = (HTREEITEM)lpContext;
    TCHAR szText[256];

    if (HIWORD(pid) != 0)
    {
        GUID temp = *pid;
        pid = (GUID *)LocalAlloc(LPTR, sizeof(GUID));
        *pid = temp;
    }

    wsprintf(szText, "%s %d.%d", szName, major_ver, minor_ver);

    DPCapDefs[0].szName = szText;
    AddCapsToTV(hParent, DPCapDefs, (LPARAM)pid);

    return TRUE;
}

//================================================================
//================================================================
HRESULT CALLBACK D3EnumCallback(
            LPGUID pid,
            LPSTR lpDriverDesc,
            LPSTR lpDriverName, 
            LPD3DDEVICEDESC lpD3DDeviceDesc1, 
            LPD3DDEVICEDESC lpD3DDeviceDesc2, 
            LPVOID lpContext)
{
    HTREEITEM hParent = (HTREEITEM)lpContext;
    TCHAR szText[256];

    //Store this info now is much easier than recreating it later.
    CAP3DDEVICEDESC *temp;
    if(lpD3DDeviceDesc1->dwFlags != 0)
    {
        temp = LocalAlloc(LPTR, sizeof(CAP3DDEVICEDESC));
        memcpy(temp,lpD3DDeviceDesc1,sizeof(CAP3DDEVICEDESC));
    }else
    {
        temp = LocalAlloc(LPTR, sizeof(CAP3DDEVICEDESC));
        memcpy(temp,lpD3DDeviceDesc2,sizeof(CAP3DDEVICEDESC));
    }
    temp->device = ddid;
    memcpy(&temp->driver,pid,sizeof(GUID));

    // Add subnode to treeview
    if (lpDriverName && *lpDriverName)
        wsprintf(szText, "%s (%s)", lpDriverDesc, lpDriverName);
    else
        lstrcpy(szText, lpDriverDesc);

    D3CapDefs[0].szName = szText;
    AddCapsToTV(hParent, D3CapDefs, (LPARAM)temp);

    return(DDENUMRET_OK);
}

HRESULT CALLBACK DDEnumCallBack3D(GUID *pid, LPSTR lpDriverDesc, LPSTR lpDriverName, LPVOID lpContext)
{
    HTREEITEM hParent = (HTREEITEM)lpContext;
    HTREEITEM hTree;
    TCHAR szText[256];

    if (HIWORD(pid) != 0)
    {
        GUID temp = *pid;
        pid = (GUID *)LocalAlloc(LPTR, sizeof(GUID));
        *pid = temp;
    }

    // Add subnode to treeview
    if (lpDriverName && *lpDriverName)
        wsprintf(szText, "%s (%s)", lpDriverDesc, lpDriverName);
    else
        lstrcpy(szText, lpDriverDesc);

    hTree = TVAddNode(hParent,szText,TRUE,IDI_CAPS, NULL, 0, 0, NULL);
    
    if (DDCreate(pid) && lp3D)
    {
        IDirect3D2_EnumDevices(lp3D, D3EnumCallback, hTree);
    }

    return(DDENUMRET_OK);
}

//================================================================
//================================================================
void DXView_FillTree(HWND hwndTV)
{
    HTREEITEM   hTree, hTreeSubNode;

    PFN_DSENUMERATE pfn_DSEnumerate;
    PFN_DSCENUMERATE pfn_DSCEnumerate;

    // Add direct draw devices

    hTree = TVAddNode(TVI_ROOT, "DirectDraw Devices", TRUE,
                      IDI_DIRECTX, NULL, 0, 0, NULL);

    // Add Display Driver node(s) and capability nodes to treeview
    DirectDrawEnumerate(DDEnumCallBack, hTree);

    // Add Hardware Emulation Layer node to treeview
    DDEnumCallBack((GUID *)DDCREATE_EMULATIONONLY, "Hardware Emulation Layer", NULL, (LPVOID)hTree);

    TreeView_Expand(g_hwndTV, hTree, TVE_EXPAND);
    TreeView_SelectItem(g_hwndTV, hTree);

    // Add direct 3D devices
    hTree = TVAddNode(TVI_ROOT, "Direct3D Devices", TRUE,
                      IDI_DIRECTX, NULL, 0, 0, NULL);
    DirectDrawEnumerate(DDEnumCallBack3D, hTree);

    TreeView_Expand(g_hwndTV, hTree, TVE_EXPAND);

    pfn_DSEnumerate = (PFN_DSENUMERATE)GetProcAddress(g_hDSoundLib, "DirectSoundEnumerateA");
    if (pfn_DSEnumerate == NULL)
    {
        MessageBox(g_hwndMain, "DSOUND.DLL does not implement DirectSoundEnumerate()", g_szAppName, MB_OK);
    }
    else
    {
        // Add direct sound devices
        hTree = TVAddNode(TVI_ROOT, "DirectSound Devices", TRUE,
                                          IDI_DIRECTX, NULL, 0, 0, NULL);

        (*pfn_DSEnumerate)(DSEnumCallBack, hTree);

        TreeView_Expand(g_hwndTV, hTree, TVE_EXPAND);
    }


    // Get a pointer to the DirectSoundCaptureEnumerate
    pfn_DSCEnumerate = (PFN_DSCENUMERATE)GetProcAddress(g_hDSoundLib, "DirectSoundCaptureEnumerateA");
    if (pfn_DSCEnumerate == NULL)
    {
        MessageBox(g_hwndMain, "DSOUND.DLL does not implement DirectSoundCaptureEnumerate(). The system may not have DirectX 5.0 installed.", g_szAppName, MB_OK);
    }
    else
    {
        // Add direct sound capture devices
        hTree = TVAddNode(TVI_ROOT, "DirectSoundCapture Devices", TRUE,
                                                    IDI_DIRECTX, NULL, 0, 0, NULL);
        (*pfn_DSCEnumerate)(DSCEnumCallBack, hTree);
        TreeView_Expand(g_hwndTV, hTree, TVE_EXPAND);
    }

    // Add direct play devices

    hTree = TVAddNode(TVI_ROOT, "DirectPlay Devices", TRUE,
                      IDI_DIRECTX, NULL, 0, 0, NULL);

    hTreeSubNode = TVAddNode(hTree, "Connections", TRUE,
                      IDI_CAPS, NULL, 0, 0, NULL);
    TreeView_Expand(g_hwndTV, hTree, TVE_EXPAND);

    DirectPlayEnumerate(DPEnumCallback, hTreeSubNode);
    TreeView_Expand(g_hwndTV, hTree, TVE_EXPAND);

    AddCapsToTV(hTree, DPLocalAppsDef, 0);
    TreeView_Expand(g_hwndTV, hTree, TVE_EXPAND);

    //
    //  DirectInput goo is in dinput.c
    //
    DI_FillTree();
}

//================================================================
//  About - process about box
//================================================================
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_INITDIALOG:
            return(TRUE);

        case WM_COMMAND:                      // message: received a command
            if(LOWORD(wParam) == IDOK        // "OK" box selected?
            || LOWORD(wParam) == IDCANCEL) {  // System menu close command?
                EndDialog(hDlg, TRUE);        // Exit the dialog
                return(TRUE);
            }
            break;
    }
    return(FALSE); // Didn't process the message
}

//================================================================
//================================================================
//  DXView_OnSize
//
//  DESCRIPTION:
//     Called whenever the size of the app window has changed or the size
//     of its child controls should be adjusted.
//
//  PARAMETERS:
//     hWnd, handle of app window.
//
//================================================================
//================================================================
void DXView_OnSize(HWND hWnd)
{
    HDWP hDWP;
    RECT ClientRect;
    int Height;
    HWND hKeyTreeWnd;
    HWND hValueListWnd;
    int x;
    int dx;

    if (IsIconic(hWnd))
        return;

    if ((hDWP = BeginDeferWindowPos(2)) != NULL)
    {
        //  Data structure used when calling GetEffectiveClientRect (which takes into
        //  account space taken up by the toolbars/status bars).  First half of the
        //  pair is zero when at the end of the list, second half is the control id.
        int s_EffectiveClientRectData[] = {
            1, 0,                               //  For the menu bar, but is unused
            0, 0                                //  First zero marks end of data
        };

        GetEffectiveClientRect(hWnd, &ClientRect, s_EffectiveClientRectData);
        Height = ClientRect.bottom - ClientRect.top;

        hKeyTreeWnd = g_hwndTV;

        DeferWindowPos(hDWP, hKeyTreeWnd, NULL, 0, ClientRect.top, g_xPaneSplit,
            Height, SWP_NOZORDER | SWP_NOACTIVATE);

        x = g_xPaneSplit + GetSystemMetrics(SM_CXSIZEFRAME);
        dx = ClientRect.right - ClientRect.left - x;

        hValueListWnd = g_hwndLV;

        DeferWindowPos(hDWP, hValueListWnd, NULL, x, ClientRect.top, dx, Height,
            SWP_NOZORDER | SWP_NOACTIVATE);

        EndDeferWindowPos(hDWP);
    }
}
#ifdef _X86_
#pragma optimize("", off)
#endif
/*----------------------------------------------------------------------------*\
\*----------------------------------------------------------------------------*/

void LVAddColumn(HWND hwndLV, int i, char *name, int width)
{
    LV_COLUMN col;

    if (i == 0)
    {
        while(ListView_DeleteColumn(hwndLV, 0))
            ;
    }

    col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
    col.fmt  = LVCFMT_LEFT;
    col.pszText = name;
    col.cchTextMax = 0;
    col.cx = width * g_tmAveCharWidth;
    col.iSubItem = 0;
    ListView_InsertColumn(hwndLV, i, &col);
}

/*----------------------------------------------------------------------------*\
\*----------------------------------------------------------------------------*/
int LVAddText(HWND hwndLV, int col, const char *sz, ...)
{
    LV_ITEM lvi;
    char    ach[80];
    va_list vl;

    va_start(vl, sz );
    wvsprintf(ach,sz, vl);

    lvi.mask        = LVIF_TEXT;
    lvi.iSubItem    = 0;
    lvi.state       = 0;
    lvi.stateMask   = 0;
    lvi.pszText     = ach;
    lvi.cchTextMax  = 0;
    lvi.iImage      = 0;
    lvi.lParam      = 0;

    if (col == 0)
    {
            lvi.iItem    = 0x7FFF;
            lvi.iSubItem = 0;
        return ListView_InsertItem(hwndLV, &lvi);
    }
    else
    {
        lvi.iItem    = ListView_GetItemCount(hwndLV)-1;
        lvi.iSubItem = col;
        return ListView_SetItem(hwndLV, &lvi);
    }
    va_end(vl);
}

/*----------------------------------------------------------------------------*\
\*----------------------------------------------------------------------------*/
void LVDeleteAllItems( HWND hwndLV )
{

	//Used by DPLay asynchronous enum sessions
	if (g_idTimer)
	{

		BOOL	bDataAvailable;
		LPLV_INSTANCEGUIDSTRUCT	lpInstGuidStruct = NULL;
		LV_ITEM	lvi;
		int		i, count;

		KillTimer(g_hwndMain, g_idTimer ); 
		g_idTimer = 0;

		memset( &lvi, 0, sizeof( LV_ITEM ));

		count	= ListView_GetItemCount( g_hwndLV );

		for ( i = 0; i < count; i++ )
		{
			lvi.iItem = i;
			lvi.mask = LVIF_PARAM;
			lvi.lParam = 0;

			bDataAvailable =ListView_GetItem( g_hwndLV, &lvi );
			
			if ((bDataAvailable) && (lvi.lParam))
				LocalFree( (LPVOID) lvi.lParam );

		}

	}

	ListView_DeleteAllItems( hwndLV );
}

/*----------------------------------------------------------------------------*\
\*----------------------------------------------------------------------------*/
HTREEITEM TVAddNode(
    HTREEITEM       hParent, 
    LPSTR           szText, 
    BOOL            fKids, 
    int             iImage, 
    SELCALLBACK     Callback, 
    LPARAM          lParam1, 
    LPARAM          lParam2,
    PRINTCALLBACK   printCallback)
{
    TV_INSERTSTRUCT tvi;
    NODEINFO *pni;

    pni = (NODEINFO *)LocalAlloc(LPTR, sizeof(NODEINFO));

    if (pni == NULL)
        return NULL;

    pni->lParam1        = lParam1;
    pni->lParam2        = lParam2;
    pni->Callback       = Callback;
    pni->printCallback  = printCallback;

    // Add Node to treeview
    tvi.hParent             = hParent;
    tvi.hInsertAfter        = TVI_LAST;
    tvi.item.mask           = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_CHILDREN;
    tvi.item.iImage         = iImage - IDI_FIRSTIMAGE;
    tvi.item.iSelectedImage = iImage - IDI_FIRSTIMAGE;
    tvi.item.lParam         = (LPARAM)pni;
    tvi.item.cChildren      = fKids;
    tvi.item.pszText        = szText;

    return TreeView_InsertItem(g_hwndTV, &tvi);
}


/*----------------------------------------------------------------------------*\
\*----------------------------------------------------------------------------*/
HRESULT EnumSessions( LPDIRECTPLAY3A lpDP3A )
{

    DPSESSIONDESC2   dps;
	HRESULT			hr = DPERR_GENERIC;


	if (lpDP3A)
	{
		memset(&dps, 0, sizeof(dps));
		dps.dwSize = sizeof(dps);

		ResetListViewRefresh( g_hwndLV );

		hr = lpDP3A->lpVtbl->EnumSessions(	lpDP3A, &dps, 0, EnumSessionsCallback, 
											NULL, 
											DPENUMSESSIONS_ALL|
											DPENUMSESSIONS_PASSWORDREQUIRED|
											DPENUMSESSIONS_ASYNC);
		RemoveStaleSessions();
	}

	return hr;
}


/*----------------------------------------------------------------------------*\
\*----------------------------------------------------------------------------*/
void FreeLocalAppList()
{
	LOCALAPP * lpTemp;

	while( g_lpLocalApp )
	{
		lpTemp = (LPLOCALAPP) g_lpLocalApp->lpNext;
		LocalFree( g_lpLocalApp );
		g_lpLocalApp = lpTemp;
	}
}

/*----------------------------------------------------------------------------*\
\*----------------------------------------------------------------------------*/
void GetAppName(LPSTR szNameBuffer, LPCGUID lpguidApplication, DWORD dwBufferSize)
{
	LPLOCALAPP	lpTemp = g_lpLocalApp;
	WCHAR		wszBuffer[128];

	while (lpTemp)
	{
		if (IsEqualGUID( &(lpTemp->guidApplication), lpguidApplication ))
		{
			strncpy( szNameBuffer, lpTemp->szAppNameA, dwBufferSize ); 
			return;
		}
		else
		{
			lpTemp = (LPLOCALAPP)lpTemp->lpNext;
		}
	}

	//If we ended up here, the GUID doesn't match anything we have installed locally.
	if (StringFromGUID2( lpguidApplication, wszBuffer, 128 ))
	{
	    wcstombs(szNameBuffer, wszBuffer, wcslen(wszBuffer)+1);
	}

}

/*----------------------------------------------------------------------------*\
\*----------------------------------------------------------------------------*/
void RemoveStaleSessions()
{
	BOOL bDataAvailable;
	int i		= 0,
		count	= ListView_GetItemCount( g_hwndLV );

	LPLV_INSTANCEGUIDSTRUCT	lpInstGuidStruct = NULL;
	LV_ITEM	lvi;

	memset( &lvi, 0, sizeof(LV_ITEM) );

	while( i < count)
	{
		lvi.iItem = i;
		lvi.mask = LVIF_PARAM;
		lvi.lParam = 0;

		bDataAvailable =ListView_GetItem( g_hwndLV, &lvi );
		
		if (bDataAvailable)
		{
			lpInstGuidStruct = (LPLV_INSTANCEGUIDSTRUCT) lvi.lParam;
			if (lpInstGuidStruct)
			{
				if (FALSE == lpInstGuidStruct->dwRefresh)
				{
					LocalFree( lpInstGuidStruct );
					ListView_DeleteItem( g_hwndLV, i);
				}
			}
		}
		else
		{
			//This item has no data, so it must be invalid.
			ListView_DeleteItem( g_hwndLV, i);
		}

		i++;
	}

}

/*----------------------------------------------------------------------------*\
\*----------------------------------------------------------------------------*/
void ResetListViewRefresh( HWND hwndLV )
{
	BOOL bDataAvailable;
	int i		= 0,
		count	= ListView_GetItemCount( hwndLV );

	LPLV_INSTANCEGUIDSTRUCT	lpInstGuidStruct = NULL;
	LV_ITEM	lvi;

	memset( &lvi, 0, sizeof(LV_ITEM) );

	while( i < count)
	{
		lvi.iItem = i;
		lvi.mask = LVIF_PARAM;
		lvi.lParam = 0;

		bDataAvailable =ListView_GetItem( hwndLV, &lvi );
		
		if (bDataAvailable)
		{
			lpInstGuidStruct = (LPLV_INSTANCEGUIDSTRUCT) lvi.lParam;
			
			if (lpInstGuidStruct)
			{
					//Mark this session to be deleted next time if it does not
					//respond to this enum request.
					lpInstGuidStruct->dwRefresh = FALSE;
			}
		}
		else
		{
			//This item has no data, so it must be invalid.
			ListView_DeleteItem( hwndLV, i);
		}

		i++;
	}

}


#ifdef _X86_
#pragma optimize("", on)
#endif
