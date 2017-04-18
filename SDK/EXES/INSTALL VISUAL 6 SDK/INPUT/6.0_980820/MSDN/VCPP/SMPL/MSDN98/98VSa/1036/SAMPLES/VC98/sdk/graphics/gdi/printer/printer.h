
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/******************************************************************************\
*
*                                PRINTER.H
*
\******************************************************************************/
#include "strings.h"


/******************************************************************************\
*                             SYMBOLIC CONSTANTS
\******************************************************************************/

#define IDM_PRINT                 101  // menu id's
#define IDM_PRINTDLG              102
#define IDM_GETDEVICECAPS         103
#define IDM_ENUMPRINTERS          104
#define IDM_GETPRINTERDRIVER      105
#define IDM_ENUMPRINTERDRIVERS    106
#define IDM_REFRESH               107
#define IDM_ABOUT                 108

#define IDM_HIENGLISH             201
#define IDM_HIMETRIC              202
#define IDM_LOENGLISH             203
#define IDM_LOMETRIC              204
#define IDM_TWIPS                 205
#define IDM_ISOTROPIC             206
#define IDM_ANISOTROPIC           207
#define IDM_TEXT                  208

#define IDM_ARC                   301
#define IDM_ELLIPSE               302
#define IDM_LINETO                303
#define IDM_PIE                   304
#define IDM_PLGBLT                305
#define IDM_POLYBEZIER            306
#define IDM_POLYGON               307
#define IDM_POLYLINE              308
#define IDM_POLYPOLYGON           309
#define IDM_RECTANGLE             310
#define IDM_ROUNDRECT             311
#define IDM_STRETCHBLT            312
#define IDM_ALLGRAPHICS           313
#define IDM_NOGRAPHICS            314
#define IDM_ENUMFONTS             315
#define IDM_DRAWAXIS              316

#define IDM_SETPENCOLOR           401
#define IDM_PENWIDTH_1            402
#define IDM_PENWIDTH_2            403
#define IDM_PENWIDTH_3            404
#define IDM_PENWIDTH_4            405
#define IDM_PENWIDTH_5            406
#define IDM_PENWIDTH_6            407
#define IDM_PENWIDTH_7            408
#define IDM_PENWIDTH_8            409
#define IDM_PENCOLOR_SOLID        410
#define IDM_PENCOLOR_DASH         411
#define IDM_PENCOLOR_DOT          412
#define IDM_PENCOLOR_DASHDOT      413
#define IDM_PENCOLOR_DASHDOTDOT   414
#define IDM_PENCOLOR_NULL         415
#define IDM_PENCOLOR_INSIDEFRAME  416

#define IDM_SETBRUSHCOLOR               501
#define IDM_BRUSHSTYLE_HORIZONTAL       502
#define IDM_BRUSHSTYLE_VERTICAL         503
#define IDM_BRUSHSTYLE_FDIAGONAL        504
#define IDM_BRUSHSTYLE_BDIAGONAL        505
#define IDM_BRUSHSTYLE_CROSS            506
#define IDM_BRUSHSTYLE_DIAGCROSS        507
#define IDM_BRUSHSTYLE_SOLIDCLR         508
#define IDM_BRUSHSTYLE_DITHEREDCLR      509
#define IDM_BRUSHSTYLE_SOLIDTEXTCLR     510
#define IDM_BRUSHSTYLE_DITHEREDTEXTCLR  511
#define IDM_BRUSHSTYLE_SOLIDBKCLR       512
#define IDM_BRUSHSTYLE_DITHEREDBKCLR    513

#define IDM_TEXTCOLOR             601

#define ID_COMBOBOX               701  // toolbar combobox id

#define MAIN_ICON                 1
#define MAIN_MENU_NAME            "MENU"
#define MAIN_CLASS_NAME           "PRINTER"
#define MAIN_WND_TITLE	          IDS_MAINWNDTITLE
#define MAIN_CLASS_STYLE          CS_HREDRAW | CS_VREDRAW
#define MAIN_WND_STYLE            WS_OVERLAPPEDWINDOW

#define MAX_MAP_MODES             8    // # items in gaMMLookup
#define MAX_PENWIDTHS             8    // # items in gaPenWidths
#define MAX_PENSTYLES             7    // # items in gaPenStyles
#define MAX_BRUSHSTYLES           5    // # items in gaBrushStyles

#define ERR_MOD_NAME             IDS_ERR_PRINTER



/******************************************************************************\
*                                 TYPEDEFS
\******************************************************************************/

typedef struct tagMAPMODELOOKUP
{
  WORD   wMenuItem;
  int    iMapMode;

} MAPMODELOOKUP;

typedef struct tagGRAPHICLOOKUP
{
  WORD   wMenuItem;
  DWORD  dwGraphic;

} GRAPHICLOOKUP;

typedef struct tagPENWIDTHLOOKUP
{
  WORD   wMenuItem;
  int    iPenWidth;

} PENWIDTHLOOKUP;

typedef struct tagPENSTYLELOOKUP
{
  WORD   wMenuItem;
  int    iPenStyle;

} PENSTYLELOOKUP;

typedef struct tagBRUSHSTYLELOOKUP
{
  WORD   wMenuItem;
  int    iBrushStyle;

} BRUSHSTYLELOOKUP;

typedef struct tagSTATUSBARLOOKUP
{
  WORD   wMenuItem;
  LPCSTR szText;

} STATUSBARLOOKUP;



/******************************************************************************\
*                                GLOBAL VARS
\******************************************************************************/

HANDLE  ghInst;                        // app instance handle
HWND    ghwndMain;                     // main app window handle
HWND    ghwndAbort;                    // Abort dialog handle
LONG    glcyMenu;                      // menu height
DWORD   gdwGraphicsOptions = DRAWAXIS; // current graphic options (to display)
int     giMapMode = MM_TEXT;           // current map mode
HDC     ghdc;                          // device context to print on
BOOL    gbAbort;                       // AbortProc return code

char    gszDeviceName[BUFSIZE];        // current device name
char    gszPort      [BUFSIZE];        // current port
char    gszDriverName[BUFSIZE];        // current driver name

DWORD   gdwPenColor   = 0x00ff00;      // current pen color
DWORD   gdwBrushColor = 0x0000ff;      // current brush color
DWORD   gdwTextColor =  0xff0000;      // current text color

int     giPenStyle   = PS_SOLID;       // current pen style
int     giPenWidth   = 1;              // current pen width
int     giBrushStyle = HS_HORIZONTAL;    // current brush style

MAPMODELOOKUP gaMMLookup[] =

    { { IDM_HIENGLISH  , MM_HIENGLISH   },
      { IDM_HIMETRIC   , MM_HIMETRIC    },
      { IDM_LOENGLISH  , MM_LOENGLISH   },
      { IDM_LOMETRIC   , MM_LOMETRIC    },
      { IDM_TWIPS      , MM_TWIPS       },
      { IDM_ISOTROPIC  , MM_ISOTROPIC   },
      { IDM_ANISOTROPIC, MM_ANISOTROPIC },
      { IDM_TEXT       , MM_TEXT        } };

GRAPHICLOOKUP gaGraphicLookup[] =

    { { IDM_ARC        , ARC         },
      { IDM_ELLIPSE    , ELLIPSE     },
      { IDM_LINETO     , LINETO      },
      { IDM_PIE        , PIE         },
      { IDM_PLGBLT     , PLG_BLT     },
      { IDM_POLYBEZIER , POLYBEZIER  },
      { IDM_POLYGON    , POLYGON     },
      { IDM_POLYLINE   , POLYLINE    },
      { IDM_POLYPOLYGON, POLYPOLYGON },
      { IDM_RECTANGLE  , RECTANGLE   },
      { IDM_ROUNDRECT  , ROUNDRECT   },
      { IDM_STRETCHBLT , STRETCH_BLT } };

PENWIDTHLOOKUP gaPenWidths[] =

    { { IDM_PENWIDTH_1, 1 },
      { IDM_PENWIDTH_2, 2 },
      { IDM_PENWIDTH_3, 3 },
      { IDM_PENWIDTH_4, 4 },
      { IDM_PENWIDTH_5, 5 },
      { IDM_PENWIDTH_6, 6 },
      { IDM_PENWIDTH_7, 7 },
      { IDM_PENWIDTH_8, 8 } };

PENSTYLELOOKUP gaPenStyles[] =

    { { IDM_PENCOLOR_SOLID      , PS_SOLID      },
      { IDM_PENCOLOR_DASH       , PS_DASH       },
      { IDM_PENCOLOR_DOT        , PS_DOT        },
      { IDM_PENCOLOR_DASHDOT    , PS_DASHDOT    },
      { IDM_PENCOLOR_DASHDOTDOT , PS_DASHDOTDOT },
      { IDM_PENCOLOR_NULL       , PS_NULL       },
      { IDM_PENCOLOR_INSIDEFRAME, PS_INSIDEFRAME} };

BRUSHSTYLELOOKUP gaBrushStyles[] =

    { { IDM_BRUSHSTYLE_HORIZONTAL     , HS_HORIZONTAL     },
      { IDM_BRUSHSTYLE_VERTICAL       , HS_VERTICAL       },
      { IDM_BRUSHSTYLE_FDIAGONAL      , HS_FDIAGONAL      },
      { IDM_BRUSHSTYLE_BDIAGONAL      , HS_BDIAGONAL      },
      { IDM_BRUSHSTYLE_CROSS          , HS_CROSS          },
      { IDM_BRUSHSTYLE_DIAGCROSS      , HS_DIAGCROSS      } };




/******************************************************************************\
*                            FUNCTION PROTOTYPES
\******************************************************************************/

LRESULT CALLBACK MainWndProc   (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK AboutDlgProc  (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK AbortDlgProc  (HWND, UINT, WPARAM, LPARAM);

BOOL    CALLBACK AbortProc     (HDC, int);

void    InvalidateClient       (void);
void    RefreshPrinterCombobox (HWND);
void    PrintThread            (LPVOID);
