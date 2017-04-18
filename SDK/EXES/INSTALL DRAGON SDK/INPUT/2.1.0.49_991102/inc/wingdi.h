/*++

Copyright (c) 1995-1998  Microsoft Corporation

Module Name: wingdi.h

--*/
#ifndef _WINGDI_H_
#define _WINGDI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <windef.h>


typedef struct tagPALETTEENTRY {
    BYTE        peRed;
    BYTE        peGreen;
    BYTE        peBlue;
    BYTE        peFlags;
} PALETTEENTRY, *PPALETTEENTRY, FAR *LPPALETTEENTRY;

/* Logical Palette */
typedef struct tagLOGPALETTE {
    WORD        palVersion;
    WORD        palNumEntries;
    PALETTEENTRY        palPalEntry[1];
} LOGPALETTE, *PLOGPALETTE, NEAR *NPLOGPALETTE, FAR *LPLOGPALETTE;


#define TRUETYPE_FONTTYPE       0x0004  
#define LF_FACESIZE				32

typedef struct tagLOGFONTA
{
    LONG      lfHeight;
    LONG      lfWidth;
    LONG      lfEscapement;
    LONG      lfOrientation;
    LONG      lfWeight;
    BYTE      lfItalic;
    BYTE      lfUnderline;
    BYTE      lfStrikeOut;
    BYTE      lfCharSet;
    BYTE      lfOutPrecision;
    BYTE      lfClipPrecision;
    BYTE      lfQuality;
    BYTE      lfPitchAndFamily;
    CHAR      lfFaceName[LF_FACESIZE];
} LOGFONTA, *PLOGFONTA, NEAR *NPLOGFONTA, FAR *LPLOGFONTA;

typedef struct tagLOGFONTW
{
    LONG      lfHeight;
    LONG      lfWidth;
    LONG      lfEscapement;
    LONG      lfOrientation;
    LONG      lfWeight;
    BYTE      lfItalic;
    BYTE      lfUnderline;
    BYTE      lfStrikeOut;
    BYTE      lfCharSet;
    BYTE      lfOutPrecision;
    BYTE      lfClipPrecision;
    BYTE      lfQuality;
    BYTE      lfPitchAndFamily;
    WCHAR     lfFaceName[LF_FACESIZE];
} LOGFONTW, *PLOGFONTW, NEAR *NPLOGFONTW, FAR *LPLOGFONTW;


#define WINUSERAPI


// @CESYSGEN IF GWES_PGDI || GWES_MGBASE
#define WINGDIAPI

#define GDI_ERROR			(0xFFFFFFFFL)
#define ERROR               0

#define OBJ_PEN             1
#define OBJ_BRUSH           2
#define OBJ_DC              3
#define OBJ_PAL             5
#define OBJ_FONT            6
#define OBJ_BITMAP          7
#define OBJ_REGION          8
#define OBJ_MEMDC           10
#define OBJ_ENHMETADC       12
#define OBJ_ENHMETAFILE     13

#define MIN_OBJ_TYPE        OBJ_PEN
#define MAX_OBJ_TYPE        OBJ_ENHMETAFILE

#define CLR_INVALID			0xFFFFFFFF
#define BI_RGB				0

/* Parameters for GetStockObject */
#define WHITE_BRUSH         0
#define LTGRAY_BRUSH        1
#define GRAY_BRUSH          2
#define DKGRAY_BRUSH        3
#define BLACK_BRUSH         4
#define NULL_BRUSH          5
#define HOLLOW_BRUSH        NULL_BRUSH
#define WHITE_PEN           6
#define BLACK_PEN           7
#define NULL_PEN            8
#define SYSTEM_FONT         13
#define DEFAULT_PALETTE     15

/* Device Parameters for GetDeviceCaps() */
#define DRIVERVERSION 0     /* Device driver version                    */
#define TECHNOLOGY    2     /* Device classification                    */
#define HORZSIZE      4     /* Horizontal size in millimeters           */
#define VERTSIZE      6     /* Vertical size in millimeters             */
#define HORZRES       8     /* Horizontal width in pixels               */
#define VERTRES       10    /* Vertical height in pixels                */
#define BITSPIXEL     12    /* Number of bits per pixel                 */
#define PLANES        14    /* Number of planes                         */
#define NUMBRUSHES    16    /* Number of brushes the device has         */
#define NUMPENS       18    /* Number of pens the device has            */
#define NUMMARKERS    20    /* Number of markers the device has         */
#define NUMFONTS      22    /* Number of fonts the device has           */
#define NUMCOLORS     24    /* Number of colors the device supports     */
#define PDEVICESIZE   26    /* Size required for device descriptor      */
#define CURVECAPS     28    /* Curve capabilities                       */
#define LINECAPS      30    /* Line capabilities                        */
#define POLYGONALCAPS 32    /* Polygonal capabilities                   */
#define TEXTCAPS      34    /* Text capabilities                        */
#define CLIPCAPS      36    /* Clipping capabilities                    */
#define RASTERCAPS    38    /* Bitblt capabilities                      */
#define ASPECTX       40    /* Length of the X leg                      */
#define ASPECTY       42    /* Length of the Y leg                      */
#define ASPECTXY      44    /* Length of the hypotenuse                 */

// Printing related DeviceCaps.

#define PHYSICALWIDTH   110 /* Physical Width in device units           */
#define PHYSICALHEIGHT  111 /* Physical Height in device units          */
#define PHYSICALOFFSETX 112 /* Physical Printable Area x margin         */
#define PHYSICALOFFSETY 113 /* Physical Printable Area y margin         */


#ifndef NOGDICAPMASKS

/* Device Capability Masks: */

/* Device Technologies */
#define DT_PLOTTER          0   /* Vector plotter                   */
#define DT_RASDISPLAY       1   /* Raster display                   */
#define DT_RASPRINTER       2   /* Raster printer                   */
#define DT_RASCAMERA        3   /* Raster camera                    */
#define DT_CHARSTREAM       4   /* Character-stream, PLP            */
#define DT_DISPFILE         6   /* Display-file                     */

/* Curve Capabilities */
#define CC_NONE             0   /* Curves not supported             */
#define CC_CIRCLES          1   /* Can do circles                   */
#define CC_PIE              2   /* Can do pie wedges                */
#define CC_CHORD            4   /* Can do chord arcs                */
#define CC_ELLIPSES         8   /* Can do ellipese                  */
#define CC_WIDE             16  /* Can do wide lines                */
#define CC_STYLED           32  /* Can do styled lines              */
#define CC_WIDESTYLED       64  /* Can do wide styled lines         */
#define CC_INTERIORS        128 /* Can do interiors                 */
#define CC_ROUNDRECT        256 /*                                  */

/* Line Capabilities */
#define LC_NONE             0   /* Lines not supported              */
#define LC_POLYLINE         2   /* Can do polylines                 */
#define LC_MARKER           4   /* Can do markers                   */
#define LC_POLYMARKER       8   /* Can do polymarkers               */
#define LC_WIDE             16  /* Can do wide lines                */
#define LC_STYLED           32  /* Can do styled lines              */
#define LC_WIDESTYLED       64  /* Can do wide styled lines         */
#define LC_INTERIORS        128 /* Can do interiors                 */

/* Polygonal Capabilities */
#define PC_NONE             0   /* Polygonals not supported         */
#define PC_POLYGON          1   /* Can do polygons                  */
#define PC_RECTANGLE        2   /* Can do rectangles                */
#define PC_WINDPOLYGON      4   /* Can do winding polygons          */
#define PC_TRAPEZOID        4   /* Can do trapezoids                */
#define PC_SCANLINE         8   /* Can do scanlines                 */
#define PC_WIDE             16  /* Can do wide borders              */
#define PC_STYLED           32  /* Can do styled borders            */
#define PC_WIDESTYLED       64  /* Can do wide styled borders       */
#define PC_INTERIORS        128 /* Can do interiors                 */

/* Clipping Capabilities */
#define CP_NONE             0   /* No clipping of output            */
#define CP_RECTANGLE        1   /* Output clipped to rects          */
#define CP_REGION           2   /* obsolete                         */

/* Text Capabilities */
#define TC_OP_CHARACTER     0x00000001  /* Can do OutputPrecision   CHARACTER      */
#define TC_OP_STROKE        0x00000002  /* Can do OutputPrecision   STROKE         */
#define TC_CP_STROKE        0x00000004  /* Can do ClipPrecision     STROKE         */
#define TC_CR_90            0x00000008  /* Can do CharRotAbility    90             */
#define TC_CR_ANY           0x00000010  /* Can do CharRotAbility    ANY            */
#define TC_SF_X_YINDEP      0x00000020  /* Can do ScaleFreedom      X_YINDEPENDENT */
#define TC_SA_DOUBLE        0x00000040  /* Can do ScaleAbility      DOUBLE         */
#define TC_SA_INTEGER       0x00000080  /* Can do ScaleAbility      INTEGER        */
#define TC_SA_CONTIN        0x00000100  /* Can do ScaleAbility      CONTINUOUS     */
#define TC_EA_DOUBLE        0x00000200  /* Can do EmboldenAbility   DOUBLE         */
#define TC_IA_ABLE          0x00000400  /* Can do ItalisizeAbility  ABLE           */
#define TC_UA_ABLE          0x00000800  /* Can do UnderlineAbility  ABLE           */
#define TC_SO_ABLE          0x00001000  /* Can do StrikeOutAbility  ABLE           */
#define TC_RA_ABLE          0x00002000  /* Can do RasterFontAble    ABLE           */
#define TC_VA_ABLE          0x00004000  /* Can do VectorFontAble    ABLE           */
#define TC_RESERVED         0x00008000
#define TC_SCROLLBLT        0x00010000  /* Don't do text scroll with blt           */

#endif /* NOGDICAPMASKS */

/* Raster Capabilities */
#define RC_NONE
#define RC_BITBLT           1       /* Can do standard BLT.             */
#define RC_BANDING          2       /* Device requires banding support  */
#define RC_SCALING          4       /* Device requires scaling support  */
#define RC_BITMAP64         8       /* Device can support >64K bitmap   */
#define RC_GDI20_OUTPUT     0x0010      /* has 2.0 output calls         */
#define RC_GDI20_STATE      0x0020
#define RC_SAVEBITMAP       0x0040
#define RC_DI_BITMAP        0x0080      /* supports DIB to memory       */
#define RC_PALETTE          0x0100      /* supports a palette           */
#define RC_DIBTODEV         0x0200      /* supports DIBitsToDevice      */
#define RC_BIGFONT          0x0400      /* supports >64K fonts          */
#define RC_STRETCHBLT       0x0800      /* supports StretchBlt          */
#define RC_STRETCHDIB       0x2000      /* supports StretchDIBits       */
#define RC_OP_DX_OUTPUT     0x4000
#define RC_DEVBITS          0x8000

#define LOGPIXELSX    88    /* Logical pixels/inch in X                 */
#define LOGPIXELSY    90    /* Logical pixels/inch in Y                 */

#define SIZEPALETTE  104    /* Number of entries in physical palette    */
#define NUMRESERVED  106    /* Number of reserved entries in palette    */
#define COLORRES     108    /* Actual color resolution                  */

/* Device Capability Masks: */

/* Device Technologies */
#define DT_RASDISPLAY       1   /* Raster display                   */

#define RDH_RECTANGLES		1

#define TRANSPARENT         1
#define OPAQUE              2

#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define PALETTERGB(r,g,b)   (0x02000000 | RGB(r,g,b))
/* The PALETTEINDEX macro has been removed.  Use RGB or PALETTEINDEX2BPP instead. */
#define PALETTEINDEX2BPP(i)  (((i)==0)?0x00000000:(((i)==1)?0x00808080:(((i)==2)?0x00C0C0C0:0x00FFFFFF)))
#define RGBA(r,g,b,a)        ((COLORREF)( (((DWORD)(BYTE)(a))<<24) | RGB(r,g,b) ))

#define GetRValue(rgb)  ((BYTE)(rgb))
#define GetGValue(rgb)  ((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue(rgb)  ((BYTE)((rgb) >> 16))

typedef DWORD COLORREF;

typedef struct tagRGBQUAD {
        BYTE    rgbBlue;
        BYTE    rgbGreen;
        BYTE    rgbRed;
        BYTE    rgbReserved;
} RGBQUAD, FAR *LPRGBQUAD;

typedef struct tagBITMAP {
    LONG        bmType;
    LONG        bmWidth;
    LONG        bmHeight;
    LONG        bmWidthBytes;
    WORD        bmPlanes;
    WORD        bmBitsPixel;
    LPVOID      bmBits;
} BITMAP, *PBITMAP, FAR *LPBITMAP;

typedef struct tagBITMAPINFOHEADER {
        DWORD      biSize;
        LONG       biWidth;
        LONG       biHeight;
        WORD       biPlanes;
        WORD       biBitCount;
        DWORD      biCompression;
        DWORD      biSizeImage;
        LONG       biXPelsPerMeter;
        LONG       biYPelsPerMeter;
        DWORD      biClrUsed;
        DWORD      biClrImportant;
} BITMAPINFOHEADER, FAR *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagBITMAPINFO {
    BITMAPINFOHEADER    bmiHeader;
    RGBQUAD             bmiColors[1];
} BITMAPINFO, FAR *LPBITMAPINFO, *PBITMAPINFO;

#include "pshpack2.h"
typedef struct _tagBITMAPFILEHEADER {
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;
#include "poppack.h"

typedef struct tagHANDLETABLE {
    HGDIOBJ     objectHandle[1];
} HANDLETABLE, *PHANDLETABLE, FAR *LPHANDLETABLE;

WINGDIAPI  HDC       WINAPI CreateCompatibleDC(HDC);
WINGDIAPI  BOOL      WINAPI DeleteDC(HDC);
WINGDIAPI  BOOL      WINAPI DeleteObject(HGDIOBJ);
WINGDIAPI  COLORREF  WINAPI GetBkColor(HDC);
WINGDIAPI  int       WINAPI GetBkMode(HDC);
WINGDIAPI  HGDIOBJ   WINAPI GetCurrentObject(HDC,UINT);
WINGDIAPI  int       WINAPI GetDeviceCaps(HDC,int);
WINGDIAPI  int       WINAPI GetObjectA(HGDIOBJ, int, LPVOID);
WINGDIAPI  int       WINAPI GetObjectW(HGDIOBJ, int, LPVOID);
WINGDIAPI  DWORD     WINAPI GetObjectType(HGDIOBJ h);
WINGDIAPI  HGDIOBJ   WINAPI GetStockObject(int);
WINGDIAPI  COLORREF  WINAPI GetTextColor(HDC);
WINGDIAPI  HGDIOBJ   WINAPI SelectObject(HDC,HGDIOBJ);
WINGDIAPI  COLORREF  WINAPI SetBkColor(HDC,COLORREF);
WINGDIAPI  int       WINAPI SetBkMode(HDC,int);
WINGDIAPI  COLORREF  WINAPI SetTextColor(HDC,COLORREF);

#ifdef UNICODE
#define GetObject   GetObjectW
#else
#define GetObject   GetObjectA
#endif //UNICODE
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGBASE
/* palette entry flags */
#define PC_RESERVED     0x01    /* palette index used for animation */
#define PC_EXPLICIT     0x02    /* palette index is explicit to device */

/* constants for the biCompression field */
#define BI_BITFIELDS  3L
#define BI_ALPHABITFIELDS  6L

#include <pshpack1.h>
typedef struct tagRGBTRIPLE {
        BYTE    rgbtBlue;
        BYTE    rgbtGreen;
        BYTE    rgbtRed;
} RGBTRIPLE;
#include <poppack.h>

typedef struct  tagCOLORADJUSTMENT {
    WORD   caSize;
    WORD   caFlags;
    WORD   caIlluminantIndex;
    WORD   caRedGamma;
    WORD   caGreenGamma;
    WORD   caBlueGamma;
    WORD   caReferenceBlack;
    WORD   caReferenceWhite;
    SHORT  caContrast;
    SHORT  caBrightness;
    SHORT  caColorfulness;
    SHORT  caRedGreenTint;
} COLORADJUSTMENT, *PCOLORADJUSTMENT, FAR *LPCOLORADJUSTMENT;

/* size of a device name string */
#define CCHDEVICENAME 32

/* size of a form name string */
#define CCHFORMNAME 32

typedef struct _devicemodeA {
    BYTE   dmDeviceName[CCHDEVICENAME];
    WORD dmSpecVersion;
    WORD dmDriverVersion;
    WORD dmSize;
    WORD dmDriverExtra;
    DWORD dmFields;
    short dmOrientation;
    short dmPaperSize;
    short dmPaperLength;
    short dmPaperWidth;
    short dmScale;
    short dmCopies;
    short dmDefaultSource;
    short dmPrintQuality;
    short dmColor;
    short dmDuplex;
    short dmYResolution;
    short dmTTOption;
    short dmCollate;
    BYTE   dmFormName[CCHFORMNAME];
    WORD   dmLogPixels;
    DWORD  dmBitsPerPel;
    DWORD  dmPelsWidth;
    DWORD  dmPelsHeight;
    DWORD  dmDisplayFlags;
    DWORD  dmDisplayFrequency;
    DWORD  dmICMMethod;
    DWORD  dmICMIntent;
    DWORD  dmMediaType;
    DWORD  dmDitherType;
    DWORD  dmICCManufacturer;
    DWORD  dmICCModel;
    DWORD  dmPanningWidth;
    DWORD  dmPanningHeight;
} DEVMODEA, *PDEVMODEA, *NPDEVMODEA, *LPDEVMODEA;

typedef struct _devicemodeW {
    WCHAR  dmDeviceName[CCHDEVICENAME];
    WORD dmSpecVersion;
    WORD dmDriverVersion;
    WORD dmSize;
    WORD dmDriverExtra;
    DWORD dmFields;
    short dmOrientation;
    short dmPaperSize;
    short dmPaperLength;
    short dmPaperWidth;
    short dmScale;
    short dmCopies;
    short dmDefaultSource;
    short dmPrintQuality;
    short dmColor;
    short dmDuplex;
    short dmYResolution;
    short dmTTOption;
    short dmCollate;
    WCHAR  dmFormName[CCHFORMNAME];
    WORD   dmLogPixels;
    DWORD  dmBitsPerPel;
    DWORD  dmPelsWidth;
    DWORD  dmPelsHeight;
    DWORD  dmDisplayFlags;
    DWORD  dmDisplayFrequency;
// #if (WINVER >= 0x0400)
//     DWORD  dmICMMethod;
//     DWORD  dmICMIntent;
//     DWORD  dmMediaType;
//     DWORD  dmDitherType;
//     DWORD  dmReserved1;
//     DWORD  dmReserved2;
// #endif /* WINVER */
} DEVMODEW, *PDEVMODEW, *NPDEVMODEW, *LPDEVMODEW;

#ifdef UNICODE
typedef DEVMODEW DEVMODE;
typedef PDEVMODEW PDEVMODE;
typedef NPDEVMODEW NPDEVMODE;
typedef LPDEVMODEW LPDEVMODE;
#else
typedef DEVMODEA DEVMODE;
typedef PDEVMODEA PDEVMODE;
typedef NPDEVMODEA NPDEVMODE;
typedef LPDEVMODEA LPDEVMODE;
#endif

/* field selection bits */
#define DM_ORIENTATION      0x00000001L
#define DM_PAPERSIZE        0x00000002L
#define DM_PAPERLENGTH      0x00000004L
#define DM_PAPERWIDTH       0x00000008L
#define DM_SCALE            0x00000010L
#define DM_COPIES           0x00000100L
#define DM_DEFAULTSOURCE    0x00000200L
#define DM_PRINTQUALITY     0x00000400L
#define DM_COLOR            0x00000800L
#define DM_DUPLEX           0x00001000L
#define DM_YRESOLUTION      0x00002000L
#define DM_TTOPTION         0x00004000L
#define DM_COLLATE          0x00008000L
#define DM_FORMNAME         0x00010000L
#define DM_LOGPIXELS        0x00020000L
#define DM_BITSPERPEL       0x00040000L
#define DM_PELSWIDTH        0x00080000L
#define DM_PELSHEIGHT       0x00100000L
#define DM_DISPLAYFLAGS     0x00200000L
#define DM_DISPLAYFREQUENCY 0x00400000L

/* orientation selections */
#define DMORIENT_PORTRAIT   1
#define DMORIENT_LANDSCAPE  2

/* paper selections */
#define DMPAPER_LETTER               1  /* Letter 8 1/2 x 11 in               */
#define DMPAPER_LEGAL                5  /* Legal 8 1/2 x 14 in                */
#define DMPAPER_A4                   9  /* A4 210 x 297 mm                    */
#define DMPAPER_B4                  12  /* B4 (JIS) 250 x 354                 */
#define DMPAPER_B5                  13  /* B5 (JIS) 182 x 257 mm              */

/* print qualities */
#define DMRES_DRAFT         (-1)
#define DMRES_HIGH          (-4)

/* color enable/disable for color printers */
#define DMCOLOR_MONOCHROME  1
#define DMCOLOR_COLOR       2

WINGDIAPI BOOL     WINAPI SetViewportOrgEx(HDC,int,int,LPPOINT);

// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGDRAW
/* Binary raster ops */
#define R2_BLACK            1   /*  0       */
#define R2_NOTMERGEPEN      2   /* DPon     */
#define R2_MASKNOTPEN       3   /* DPna     */
#define R2_NOTCOPYPEN       4   /* PN       */
#define R2_MASKPENNOT       5   /* PDna     */
#define R2_NOT              6   /* Dn       */
#define R2_XORPEN           7   /* DPx      */
#define R2_NOTMASKPEN       8   /* DPan     */
#define R2_MASKPEN          9   /* DPa      */
#define R2_NOTXORPEN        10  /* DPxn     */
#define R2_NOP              11  /* D        */
#define R2_MERGENOTPEN      12  /* DPno     */
#define R2_COPYPEN          13  /* P        */
#define R2_MERGEPENNOT      14  /* PDno     */
#define R2_MERGEPEN         15  /* DPo      */
#define R2_WHITE            16  /*  1       */
#define R2_LAST             16

/* Brush Styles */
#define BS_PATTERN          3
#define BS_INDEXED          4
#define BS_DIBPATTERN       5
#define BS_PATTERN8X8       7
#define BS_DIBPATTERN8X8    8
#define BS_MONOPATTERN      9

WINGDIAPI HBRUSH WINAPI CreatePatternBrush(HBITMAP);
WINGDIAPI HPEN   WINAPI CreatePen(int, int, COLORREF);
WINGDIAPI BOOL   WINAPI FillRgn(HDC, HRGN, HBRUSH);
WINGDIAPI int    WINAPI SetROP2(HDC, int);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGDRAW
#define BS_SOLID            0
#define BS_NULL             1
#define BS_HOLLOW           BS_NULL
#define BS_DIBPATTERNPT     6

#define PS_SOLID            0
#define PS_DASH             1
#define PS_NULL             5

typedef struct tagLOGBRUSH {
    UINT        lbStyle;
    COLORREF    lbColor;
    LONG        lbHatch;
} LOGBRUSH, *PLOGBRUSH, NEAR *NPLOGBRUSH, FAR *LPLOGBRUSH;

typedef struct tagLOGPEN {
    UINT        lopnStyle;
    POINT       lopnWidth;
    COLORREF    lopnColor;
} LOGPEN, *PLOGPEN, NEAR *NPLOGPEN, FAR *LPLOGPEN;

WINGDIAPI HBRUSH   WINAPI CreateDIBPatternBrushPt(CONST VOID *,UINT);
WINGDIAPI HPEN     WINAPI CreatePenIndirect(CONST LOGPEN *);
WINGDIAPI HBRUSH   WINAPI CreateSolidBrush(COLORREF);
WINGDIAPI BOOL     WINAPI DrawEdge(HDC,RECT *,UINT,UINT);
WINGDIAPI BOOL     WINAPI DrawFocusRect(HDC,CONST RECT *);
WINGDIAPI BOOL     WINAPI Ellipse(HDC,int,int,int,int);
WINGDIAPI int      WINAPI FillRect(HDC,CONST RECT *,HBRUSH);
WINGDIAPI COLORREF WINAPI GetPixel(HDC,int,int);
WINGDIAPI HBRUSH   WINAPI GetSysColorBrush(int);
WINGDIAPI BOOL     WINAPI Polygon(HDC,CONST POINT *,int);
WINGDIAPI BOOL     WINAPI Polyline(HDC,CONST POINT *,int);
WINGDIAPI BOOL     WINAPI Rectangle(HDC,int,int,int,int);
WINGDIAPI BOOL     WINAPI RoundRect(HDC,int,int,int,int,int,int);
WINGDIAPI BOOL     WINAPI SetBrushOrgEx(HDC,int,int,LPPOINT);
WINGDIAPI COLORREF WINAPI SetPixel(HDC,int,int,COLORREF);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGBITMAP
WINGDIAPI  HBITMAP   WINAPI CreateBitmap(int,int,UINT,UINT,CONST VOID *);
WINGDIAPI  HBITMAP   WINAPI CreateCompatibleBitmap(HDC,int,int);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGBITMAP || GWES_MGDX
/* structures for defining DIBs */
typedef struct tagBITMAPCOREHEADER {
        DWORD   bcSize;                 /* used to get to color table */
        WORD    bcWidth;
        WORD    bcHeight;
        WORD    bcPlanes;
        WORD    bcBitCount;
} BITMAPCOREHEADER, FAR *LPBITMAPCOREHEADER, *PBITMAPCOREHEADER;

typedef struct tagBITMAPCOREINFO {
    BITMAPCOREHEADER    bmciHeader;
    RGBTRIPLE           bmciColors[1];
} BITMAPCOREINFO, FAR *LPBITMAPCOREINFO, *PBITMAPCOREINFO;
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGRGN
typedef struct _RGNDATAHEADER {
    DWORD   dwSize;
    DWORD   iType;
    DWORD   nCount;
    DWORD   nRgnSize;
    RECT    rcBound;
} RGNDATAHEADER, *PRGNDATAHEADER;

typedef struct _RGNDATA {
    RGNDATAHEADER   rdh;
    char            Buffer[1];
} RGNDATA, *PRGNDATA, NEAR *NPRGNDATA, FAR *LPRGNDATA;
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGRGN
#define NULLREGION          1
#define SIMPLEREGION        2
#define COMPLEXREGION       3
#define RGN_ERROR			ERROR

#define RGN_AND             1
#define RGN_OR              2
#define RGN_XOR             3
#define RGN_DIFF            4
#define RGN_COPY            5
#define RGN_MIN             RGN_AND
#define RGN_MAX             RGN_COPY

WINGDIAPI  int       WINAPI CombineRgn(HRGN,HRGN,HRGN,int);
WINGDIAPI  HRGN      WINAPI CreateRectRgnIndirect(CONST RECT *);
WINGDIAPI  BOOL      WINAPI EqualRgn(HRGN,HRGN);
WINGDIAPI  int       WINAPI ExcludeClipRect(HDC,int,int,int,int);
WINGDIAPI  int       WINAPI GetClipBox(HDC,LPRECT);
WINGDIAPI  int       WINAPI GetClipRgn(HDC,HRGN);
WINGDIAPI  DWORD     WINAPI GetRegionData(HRGN,DWORD,LPRGNDATA);
WINGDIAPI  int       WINAPI GetRgnBox(HRGN,RECT *);
WINGDIAPI  int       WINAPI IntersectClipRect(HDC,int,int,int,int);
WINGDIAPI  int       WINAPI OffsetRgn(HRGN,int,int);
WINGDIAPI  BOOL      WINAPI PtInRegion(HRGN,int,int);
WINGDIAPI  BOOL      WINAPI RectInRegion(HRGN,CONST RECT *);
WINGDIAPI  int       WINAPI SelectClipRgn(HDC,HRGN);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGRGN
WINGDIAPI HRGN  WINAPI  CreateRectRgn(int, int, int, int); 
WINGDIAPI BOOL  WINAPI  RectVisible(HDC, CONST RECT *);
WINGDIAPI BOOL  WINAPI  SetRectRgn(HRGN, int, int, int, int);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGBLT
/* Ternary raster operations */
#define SRCCOPY             (DWORD)0x00CC0020 /* dest = source                   */
#define SRCPAINT            (DWORD)0x00EE0086 /* dest = source OR dest           */
#define SRCAND              (DWORD)0x008800C6 /* dest = source AND dest          */
#define SRCINVERT           (DWORD)0x00660046 /* dest = source XOR dest          */
#define SRCERASE            (DWORD)0x00440328 /* dest = source AND (NOT dest )   */
#define NOTSRCCOPY          (DWORD)0x00330008 /* dest = (NOT source)             */
#define NOTSRCERASE         (DWORD)0x001100A6 /* dest = (NOT src) AND (NOT dest) */
#define MERGECOPY           (DWORD)0x00C000CA /* dest = (source AND pattern)     */
#define MERGEPAINT          (DWORD)0x00BB0226 /* dest = (NOT source) OR dest     */
#define PATCOPY             (DWORD)0x00F00021 /* dest = pattern                  */
#define PATPAINT            (DWORD)0x00FB0A09 /* dest = DPSnoo                   */
#define PATINVERT           (DWORD)0x005A0049 /* dest = pattern XOR dest         */
#define DSTINVERT           (DWORD)0x00550009 /* dest = (NOT dest)               */
#define BLACKNESS           (DWORD)0x00000042 /* dest = BLACK                    */
#define WHITENESS           (DWORD)0x00FF0062 /* dest = WHITE                    */

WINGDIAPI  BOOL      WINAPI BitBlt(HDC,int,int,int,int,HDC,int,int,DWORD);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGBLT2
/* Quaternary raster codes */
#define MAKEROP4(fore,back) (DWORD)((((back) << 8) & 0xFF000000) | (fore))

WINGDIAPI  BOOL      WINAPI MaskBlt(HDC,int,int,int,int,HDC,int,int,HBITMAP,int,int,DWORD);
WINGDIAPI  BOOL		 WINAPI PatBlt(HDC,int,int,int,int,DWORD);
WINGDIAPI  BOOL      WINAPI StretchBlt(HDC,int,int,int,int,HDC,int,int,int,int,DWORD);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGBLT2
WINGDIAPI  BOOL      WINAPI TransparentImage(HDC,int,int,int,int,HANDLE,int,int,int,int,COLORREF);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGTT || GWES_MGRAST
#define ETO_OPAQUE                   0x0002
#define ETO_CLIPPED                  0x0004

#define OUT_DEFAULT_PRECIS      0
#define OUT_STRING_PRECIS       1
#define OUT_RASTER_PRECIS       6
#define CLIP_DEFAULT_PRECIS     0
#define CLIP_CHARACTER_PRECIS   1
#define CLIP_STROKE_PRECIS      2

#define DEFAULT_QUALITY			0
#define DRAFT_QUALITY			1
#define RASTER_FONTTYPE			0x0001
#define NONANTIALIASED_QUALITY  3
#define ANTIALIASED_QUALITY     4

#ifdef UNICODE
#define LOGFONT					LOGFONTW
#define PLOGFONT				PLOGFONTW
#define NPLOGFONT				NPLOGFONTW
#define LPLOGFONT				LPLOGFONTW
#else
#define LOGFONT					LOGFONTA
#define PLOGFONT				PLOGFONTA
#define NPLOGFONT				NPLOGFONTA
#define LPLOGFONT				LPLOGFONTA
#endif //!UNICODE

#define DEFAULT_PITCH           0
#define FIXED_PITCH             1
#define VARIABLE_PITCH          2

#define ANSI_CHARSET            0
#define DEFAULT_CHARSET         1
#define SYMBOL_CHARSET          2
#define SHIFTJIS_CHARSET        128
#define HANGEUL_CHARSET         129
#define GB2312_CHARSET          134
#define CHINESEBIG5_CHARSET     136
#define OEM_CHARSET             255

#define JOHAB_CHARSET           130
#define HEBREW_CHARSET          177
#define ARABIC_CHARSET          178
#define GREEK_CHARSET           161
#define TURKISH_CHARSET         162
#define VIETNAMESE_CHARSET      163
#define THAI_CHARSET            222
#define EASTEUROPE_CHARSET      238
#define RUSSIAN_CHARSET         204
#define MAC_CHARSET             77
#define BALTIC_CHARSET          186

#define FS_LATIN1               0x00000001L
#define FS_LATIN2               0x00000002L
#define FS_CYRILLIC             0x00000004L
#define FS_GREEK                0x00000008L
#define FS_TURKISH              0x00000010L
#define FS_HEBREW               0x00000020L
#define FS_ARABIC               0x00000040L
#define FS_BALTIC               0x00000080L
#define FS_VIETNAMESE           0x00000100L
#define FS_THAI                 0x00010000L
#define FS_JISJAPAN             0x00020000L
#define FS_CHINESESIMP          0x00040000L
#define FS_WANSUNG              0x00080000L
#define FS_CHINESETRAD          0x00100000L
#define FS_JOHAB                0x00200000L
#define FS_SYMBOL               0x80000000L

/* Font Families */
#define FF_DONTCARE         (0<<4)  /* Don't care or don't know. */
#define FF_ROMAN            (1<<4)  /* Variable stroke width, serifed. */
                                    /* Times Roman, Century Schoolbook, etc. */
#define FF_SWISS            (2<<4)  /* Variable stroke width, sans-serifed. */
                                    /* Helvetica, Swiss, etc. */
#define FF_MODERN           (3<<4)  /* Constant stroke width, serifed or sans-serifed. */
                                    /* Pica, Elite, Courier, etc. */
#define FF_SCRIPT           (4<<4)  /* Cursive, etc. */
#define FF_DECORATIVE       (5<<4)  /* Old English, etc. */

/* Font Weights */
#define FW_DONTCARE         0
#define FW_THIN             100
#define FW_EXTRALIGHT       200
#define FW_LIGHT            300
#define FW_NORMAL           400
#define FW_MEDIUM           500
#define FW_SEMIBOLD         600
#define FW_BOLD             700
#define FW_EXTRABOLD        800
#define FW_HEAVY            900

/* tmPitchAndFamily flags */
#define TMPF_FIXED_PITCH    0x01
#define TMPF_VECTOR         0x02
#define TMPF_DEVICE         0x08
#define TMPF_TRUETYPE       0x04

typedef struct tagTEXTMETRICA
{
    LONG        tmHeight;
    LONG        tmAscent;
    LONG        tmDescent;
    LONG        tmInternalLeading;
    LONG        tmExternalLeading;
    LONG        tmAveCharWidth;
    LONG        tmMaxCharWidth;
    LONG        tmWeight;
    LONG        tmOverhang;
    LONG        tmDigitizedAspectX;
    LONG        tmDigitizedAspectY;
    char        tmFirstChar;
    char        tmLastChar;
    char        tmDefaultChar;
    char        tmBreakChar;
    BYTE        tmItalic;
    BYTE        tmUnderlined;
    BYTE        tmStruckOut;
    BYTE        tmPitchAndFamily;
    BYTE        tmCharSet;
} TEXTMETRICA, *PTEXTMETRICA, NEAR *NPTEXTMETRICA, FAR *LPTEXTMETRICA;

typedef struct tagTEXTMETRICW
{
    LONG        tmHeight;
    LONG        tmAscent;
    LONG        tmDescent;
    LONG        tmInternalLeading;
    LONG        tmExternalLeading;
    LONG        tmAveCharWidth;
    LONG        tmMaxCharWidth;
    LONG        tmWeight;
    LONG        tmOverhang;
    LONG        tmDigitizedAspectX;
    LONG        tmDigitizedAspectY;
    WCHAR       tmFirstChar;
    WCHAR       tmLastChar;
    WCHAR       tmDefaultChar;
    WCHAR       tmBreakChar;
    BYTE        tmItalic;
    BYTE        tmUnderlined;
    BYTE        tmStruckOut;
    BYTE        tmPitchAndFamily;
    BYTE        tmCharSet;
} TEXTMETRICW, *PTEXTMETRICW, NEAR *NPTEXTMETRICW, FAR *LPTEXTMETRICW;

#ifdef UNICODE
typedef TEXTMETRICW TEXTMETRIC;
typedef PTEXTMETRICW PTEXTMETRIC;
typedef NPTEXTMETRICW NPTEXTMETRIC;
typedef LPTEXTMETRICW LPTEXTMETRIC;
#else
typedef TEXTMETRICA TEXTMETRIC;
typedef PTEXTMETRICA PTEXTMETRIC;
typedef NPTEXTMETRICA NPTEXTMETRIC;
typedef LPTEXTMETRICA LPTEXTMETRIC;
#endif // UNICODE

/* ntmFlags field flags */
#define NTM_REGULAR     0x00000040L
#define NTM_BOLD        0x00000020L
#define NTM_ITALIC      0x00000001L

typedef struct tagNEWTEXTMETRICA
{
    LONG        tmHeight;
    LONG        tmAscent;
    LONG        tmDescent;
    LONG        tmInternalLeading;
    LONG        tmExternalLeading;
    LONG        tmAveCharWidth;
    LONG        tmMaxCharWidth;
    LONG        tmWeight;
    LONG        tmOverhang;
    LONG        tmDigitizedAspectX;
    LONG        tmDigitizedAspectY;
    BYTE        tmFirstChar;
    BYTE        tmLastChar;
    BYTE        tmDefaultChar;
    BYTE        tmBreakChar;
    BYTE        tmItalic;
    BYTE        tmUnderlined;
    BYTE        tmStruckOut;
    BYTE        tmPitchAndFamily;
    BYTE        tmCharSet;
    DWORD       ntmFlags;
    UINT        ntmSizeEM;
    UINT        ntmCellHeight;
    UINT        ntmAvgWidth;
} NEWTEXTMETRICA, *PNEWTEXTMETRICA, NEAR *NPNEWTEXTMETRICA, FAR *LPNEWTEXTMETRICA;

typedef struct tagNEWTEXTMETRICW
{
    LONG        tmHeight;
    LONG        tmAscent;
    LONG        tmDescent;
    LONG        tmInternalLeading;
    LONG        tmExternalLeading;
    LONG        tmAveCharWidth;
    LONG        tmMaxCharWidth;
    LONG        tmWeight;
    LONG        tmOverhang;
    LONG        tmDigitizedAspectX;
    LONG        tmDigitizedAspectY;
    WCHAR       tmFirstChar;
    WCHAR       tmLastChar;
    WCHAR       tmDefaultChar;
    WCHAR       tmBreakChar;
    BYTE        tmItalic;
    BYTE        tmUnderlined;
    BYTE        tmStruckOut;
    BYTE        tmPitchAndFamily;
    BYTE        tmCharSet;
    DWORD       ntmFlags;
    UINT        ntmSizeEM;
    UINT        ntmCellHeight;
    UINT        ntmAvgWidth;
} NEWTEXTMETRICW, *PNEWTEXTMETRICW, NEAR *NPNEWTEXTMETRICW, FAR *LPNEWTEXTMETRICW;

#ifdef UNICODE
typedef NEWTEXTMETRICW NEWTEXTMETRIC;
typedef PNEWTEXTMETRICW PNEWTEXTMETRIC;
typedef NPNEWTEXTMETRICW NPNEWTEXTMETRIC;
typedef LPNEWTEXTMETRICW LPNEWTEXTMETRIC;
#else
typedef NEWTEXTMETRICA NEWTEXTMETRIC;
typedef PNEWTEXTMETRICA PNEWTEXTMETRIC;
typedef NPNEWTEXTMETRICA NPNEWTEXTMETRIC;
typedef LPNEWTEXTMETRICA LPNEWTEXTMETRIC;
#endif // UNICODE

WINGDIAPI  int       WINAPI AddFontResourceA(LPWSTR);
WINGDIAPI  int       WINAPI AddFontResourceW(LPCWSTR);
WINGDIAPI  HFONT     WINAPI CreateFontIndirectA(CONST LOGFONTA *);
WINGDIAPI  HFONT     WINAPI CreateFontIndirectW(CONST LOGFONTW *);
WINGDIAPI  BOOL      WINAPI ExtTextOutA(HDC,int,int,UINT,CONST RECT *,LPCSTR,UINT,CONST INT *);
WINGDIAPI  BOOL      WINAPI ExtTextOutW(HDC,int,int,UINT,CONST RECT *,LPCWSTR,UINT,CONST INT *);
WINGDIAPI  BOOL      WINAPI GetTextExtentExPointA(HDC,LPCSTR,int,int,LPINT,LPINT,LPSIZE);
WINGDIAPI  BOOL      WINAPI GetTextExtentExPointW(HDC,LPCWSTR,int,int,LPINT,LPINT,LPSIZE);
WINGDIAPI  BOOL      WINAPI GetTextMetricsA(HDC,LPTEXTMETRICA);
WINGDIAPI  BOOL      WINAPI GetTextMetricsW(HDC,LPTEXTMETRICW);
WINGDIAPI  BOOL      WINAPI RemoveFontResourceA(LPCSTR);
WINGDIAPI  BOOL      WINAPI RemoveFontResourceW(LPCWSTR);


/* GetTextExtentPoint variants */
#define GetTextExtentPointW(hdc, lpString, cbString, lpSize) \
        GetTextExtentExPointW(hdc, lpString, cbString, 0, NULL, NULL, lpSize)

#define GetTextExtentPointA(hdc, lpString, cbString, lpSize) \
        GetTextExtentExPointA(hdc, lpString, cbString, 0, NULL, NULL, lpSize)

#ifdef UNICODE
#define GetTextExtentPoint(hdc, lpString, cbString, lpSize) \
        GetTextExtentPointW(hdc, lpString, cbString, lpSize)
#else
#define GetTextExtentPoint(hdc, lpString, cbString, lpSize) \
        GetTextExtentPointA(hdc, lpString, cbString, lpSize)
#endif


/* GetTextExtentPoint32 variants */
#define GetTextExtentPoint32W(hdc, lpString, cbString, lpSize) \
        GetTextExtentPointW(hdc, lpString, cbString, lpSize)

#define GetTextExtentPoint32A(hdc, lpString, cbString, lpSize) \
        GetTextExtentPointA(hdc, lpString, cbString, lpSize)

#define GetTextExtentPoint32(hdc, lpString, cbString, lpSize) \
        GetTextExtentPoint(hdc, lpString, cbString, lpSize)


#ifdef UNICODE
#define AddFontResource         AddFontResourceW
#define CreateFontIndirect      CreateFontIndirectW
#define ExtTextOut              ExtTextOutW
#define GetTextExtentExPoint    GetTextExtentExPointW
#define GetTextMetrics          GetTextMetricsW
#define RemoveFontResource      RemoveFontResourceW
#else
#define AddFontResource         AddFontResourceA
#define CreateFontIndirect      CreateFontIndirectA
#define ExtTextOut              ExtTextOutA
#define GetTextExtentExPoint    GetTextExtentExPointA
#define GetTextMetrics          GetTextMetricsA
#define RemoveFontResource      RemoveFontResourceA
#endif //UNICODE
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGDRWTXT
/* DrawText() Format Flags */
#define DT_TOP              0x00000000
#define DT_LEFT             0x00000000
#define DT_CENTER           0x00000001
#define DT_RIGHT            0x00000002
#define DT_VCENTER          0x00000004
#define DT_BOTTOM           0x00000008
#define DT_WORDBREAK        0x00000010
#define DT_SINGLELINE       0x00000020
#define DT_EXPANDTABS       0x00000040
#define DT_TABSTOP          0x00000080
#define DT_NOCLIP           0x00000100
#define DT_EXTERNALLEADING  0x00000200
#define DT_CALCRECT         0x00000400
#define DT_NOPREFIX         0x00000800
#define DT_INTERNAL         0x00001000

WINUSERAPI int WINAPI DrawTextA(HDC,LPCSTR,int,RECT *,UINT);
WINUSERAPI int WINAPI WINAPI DrawTextW(HDC,LPCWSTR,int,RECT *,UINT);

#ifdef UNICODE
#define DrawText                DrawTextW
#else
#define DrawText                DrawTextA
#endif
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGTT || GWES_MGRAST2
#define LF_FULLFACESIZE     64
typedef struct tagENUMLOGFONT
{
    LOGFONT   elfLogFont;
    TCHAR     elfFullName[LF_FULLFACESIZE];
    TCHAR     elfStyle[LF_FACESIZE];
} ENUMLOGFONT, FAR* LPENUMLOGFONT;

typedef int (CALLBACK* FONTENUMPROC)(CONST LOGFONT *, CONST TEXTMETRIC *, DWORD, LPARAM);

WINGDIAPI  int       WINAPI EnumFontFamiliesA(HDC,LPCSTR,FONTENUMPROC,LPARAM);
WINGDIAPI  int       WINAPI EnumFontFamiliesW(HDC,LPCWSTR,FONTENUMPROC,LPARAM);
WINGDIAPI  int       WINAPI EnumFontsA(HDC,LPCSTR,FONTENUMPROC,LPARAM);
WINGDIAPI  int       WINAPI EnumFontsW(HDC,LPCWSTR,FONTENUMPROC,LPARAM);
WINGDIAPI  int       WINAPI GetTextFaceA(HDC,int,LPSTR);
WINGDIAPI  int       WINAPI GetTextFaceW(HDC,int,LPWSTR);

#ifdef UNICODE
#define EnumFontFamilies        EnumFontFamiliesW
#define EnumFonts               EnumFontsW
#define GetTextFace             GetTextFaceW
#else
#define EnumFontFamilies        EnumFontFamiliesA
#define EnumFonts               EnumFontsA
#define GetTextFace             GetTextFaceA
#endif //UNICODE
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGTT
WINGDIAPI  BOOL      WINAPI EnableEUDC(BOOL);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGTCI
typedef struct tagFONTSIGNATURE
{
    DWORD fsUsb[4];
    DWORD fsCsb[2];
} FONTSIGNATURE, *PFONTSIGNATURE,FAR *LPFONTSIGNATURE;

typedef struct tagCHARSETINFO
{
    UINT ciCharset;
    UINT ciACP;
    FONTSIGNATURE fs;
} CHARSETINFO, *PCHARSETINFO, NEAR *NPCHARSETINFO, FAR *LPCHARSETINFO;

#define TCI_SRCCHARSET  1
#define TCI_SRCCODEPAGE 2
#define TCI_SRCFONTSIG  3

WINGDIAPI   BOOL    WINAPI TranslateCharsetInfo(DWORD *, LPCHARSETINFO, DWORD dwFlags);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGDIBSEC
#define DIB_RGB_COLORS      0 /* color table in RGBs */
#define DIB_PAL_COLORS      1 /* color table in palette indices */

typedef struct tagDIBSECTION {
    BITMAP              dsBm;
    BITMAPINFOHEADER    dsBmih;
    DWORD               dsBitfields[3];
    HANDLE              dshSection;
    DWORD               dsOffset;
} DIBSECTION, FAR *LPDIBSECTION, *PDIBSECTION;

typedef struct tagDIBSECTION2 {
    BITMAP              dsBm;
    BITMAPINFOHEADER    dsBmih;
    DWORD               dsBitfields[3];
    HANDLE              dshSection;
    DWORD               dsOffset;
    DWORD               dsAlphaBitfield;
} DIBSECTION2, FAR *LPDIBSECTION2, *PDIBSECTION2;

WINGDIAPI  HBITMAP   WINAPI CreateDIBSection(HDC,CONST BITMAPINFO *,UINT,VOID **,HANDLE,DWORD);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGDC
WINGDIAPI BOOL WINAPI RestoreDC(HDC,int);
WINGDIAPI int  WINAPI SaveDC(HDC);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGDC
WINGDIAPI HDC  WINAPI CreateDCA(LPCSTR, LPCSTR , LPCSTR , CONST DEVMODEA *);
WINGDIAPI HDC  WINAPI CreateDCW(LPCWSTR, LPCWSTR , LPCWSTR , CONST DEVMODEW *);
WINGDIAPI int  WINAPI ExtEscape(HDC, int, int, LPCSTR, int, LPSTR);

#ifdef UNICODE
#define CreateDC  CreateDCW
#else
#define CreateDC  CreateDCA
#endif // !UNICODE
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGPAL
WINGDIAPI HPALETTE WINAPI CreatePalette(CONST LOGPALETTE *);
WINGDIAPI UINT     WINAPI GetNearestPaletteIndex(HPALETTE, COLORREF);
WINGDIAPI UINT     WINAPI GetPaletteEntries(HPALETTE, UINT, UINT, LPPALETTEENTRY);
WINGDIAPI UINT     WINAPI GetSystemPaletteEntries(HDC, UINT, UINT, LPPALETTEENTRY);
WINGDIAPI UINT     WINAPI RealizePalette(HDC);
WINGDIAPI HPALETTE WINAPI SelectPalette(HDC, HPALETTE, BOOL);
WINGDIAPI UINT     WINAPI SetPaletteEntries(HPALETTE, UINT, UINT, CONST PALETTEENTRY *);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGPAL
WINGDIAPI COLORREF WINAPI GetNearestColor(HDC, COLORREF);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGPRINT
/* Spooler Error Codes */
#define SP_ERROR                     (-1)

#ifdef STRICT
typedef BOOL (CALLBACK* ABORTPROC)(HDC, int);
#else
typedef FARPROC ABORTPROC;
#endif

typedef struct _DOCINFOA {
    int     cbSize;
    LPCSTR   lpszDocName;
    LPCSTR   lpszOutput;
    LPCSTR   lpszDatatype;
    DWORD    fwType;
} DOCINFOA, *LPDOCINFOA;

typedef struct _DOCINFOW {
    int     cbSize;
    LPCWSTR  lpszDocName;
    LPCWSTR  lpszOutput;
    LPCWSTR  lpszDatatype;
    DWORD    fwType;
} DOCINFOW, *LPDOCINFOW;

#ifdef UNICODE
typedef DOCINFOW DOCINFO;
typedef LPDOCINFOW LPDOCINFO;
#else
typedef DOCINFOA DOCINFO;
typedef LPDOCINFOA LPDOCINFO;
#endif // UNICODE

WINGDIAPI int WINAPI AbortDoc(HDC);
WINGDIAPI int WINAPI EndDoc(HDC);
WINGDIAPI int WINAPI EndPage(HDC);
WINGDIAPI int WINAPI SetAbortProc(HDC, ABORTPROC);
WINGDIAPI int WINAPI StartDocA(HDC, CONST DOCINFOA *);
WINGDIAPI int WINAPI StartDocW(HDC, CONST DOCINFOW *);
WINGDIAPI int WINAPI StartPage(HDC);

#ifdef UNICODE
#define StartDoc  StartDocW
#else
#define StartDoc  StartDocA
#endif // !UNICODE
// @CESYSGEN ENDIF

#ifdef UNDER_NT
            int         WINAPI MulDiv(int,int,int);
WINGDIAPI	int			WINAPI SetMapMode(HDC, int);
WINGDIAPI	BOOL		WINAPI SetViewportExtEx(HDC, int, int, LPSIZE);
WINGDIAPI	BOOL		WINAPI SetViewportOrgEx(HDC, int, int, LPPOINT);
WINGDIAPI	int			WINAPI GetDIBits(HDC, HBITMAP, UINT, UINT, LPVOID, LPBITMAPINFO, UINT);
WINGDIAPI	LONG		WINAPI GetBitmapBits(HBITMAP, LONG, LPVOID);
WINGDIAPI	UINT		WINAPI GetDIBColorTable(HDC, UINT, UINT, RGBQUAD *);
WINGDIAPI	int			WINAPI StretchDIBits(HDC, int, int, int, int, int, int, int, 
								int, CONST VOID *, CONST BITMAPINFO *, UINT, DWORD);
WINGDIAPI	BOOL		WINAPI SetWindowExtEx(HDC, int, int, LPSIZE);
WINGDIAPI	BOOL		WINAPI SetWindowOrgEx(HDC, int, int, LPPOINT);
WINGDIAPI	int			WINAPI SetStretchBltMode(HDC, int);

#define COLORONCOLOR   3
#define MM_ANISOTROPIC 8
#endif // UNDER_NT


#ifdef __cplusplus
}
#endif


#ifdef WINCEOEM
#include <pwingdi.h>	// internal defines 
#ifndef GDI_SERVER
#ifdef WINCEMACRO
#include <mwingdi.h> 	// macro defines
#endif
#endif
#endif


#endif /* _WINGDI_H_ */
