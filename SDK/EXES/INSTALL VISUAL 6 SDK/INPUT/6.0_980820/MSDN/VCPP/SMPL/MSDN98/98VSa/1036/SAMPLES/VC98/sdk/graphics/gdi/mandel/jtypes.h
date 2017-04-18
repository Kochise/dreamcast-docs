/******************************Module*Header*******************************\
* Module Name: jtypes.h
*
* Contains the INFO structure and handy macros
*
* Created: 10-Jan-1992 13:21:01
* Author: Petrus Wong
*
* Copyright (C) 1993-1997 Microsoft Corporation
*
* The INFO structure is allocated dynmamically when the MDI child is
* created and freed when the window is about to be destroyed.  The pointer
* to this data structure is stored in the LONG user data window structure.
* This data structure stores the per-window's info.
*
* Dependencies:
*
*   #include windows.h
*
\**************************************************************************/
//
// Handy macros for the transformations used in fractal generations
//
#define Xform(Pt, SrcFrom, SrcTo, DestFrom, DestTo) \
         (((Pt-SrcFrom)/(SrcTo-SrcFrom)*(DestTo-DestFrom))+DestFrom)
#define Xform2(Pt, SrcFrom, SrcTo, DestFrom, DestTo) \
         ((int) ((Pt-SrcFrom)/(SrcTo-SrcFrom)*(DestTo-DestFrom)+DestFrom))
#define XformFix(Pt, SrcFrom, SrcTo, DestFrom, DestTo) \
         (lMul(lDiv(Pt-SrcFrom,SrcTo-SrcFrom), DestTo-DestFrom)+DestFrom)

#define SIZEOFCAPTIONTEXT	20
#define MAX_FRAME           800
#define MAX_FILE            800

typedef struct _FileInfo{
    HANDLE      hFile;
    HANDLE      hMapFile;
    LPVOID      lpvMapView;
} FILEINFO, *PFILEINFO;

typedef struct _RLEDATA{
    ULONG           ulFiles;
    ULONG           ulFrames;
    HPALETTE        hPal;
    LPBITMAPINFO    pbmi;
    FILEINFO        rgFileInfo[MAX_FILE];
    PBYTE           rgpjFrame[MAX_FRAME];
    ULONG           ulSize[MAX_FRAME];
    PBITMAPINFO     rgpbmi[MAX_FRAME];
} RLEDATA, *PRLEDATA;

typedef struct _PerWndInfo {
    char    CaptionBarText[SIZEOFCAPTIONTEXT];
    HWND    hwnd;               // hJulia or hView, the drawing surface
    HWND    hParent;            // ghwndClient, the client area of main frame
    HWND    hTextWnd;           // hTextWnd, the status window
    RECT    rcClient;           // hJulia & hTextWnd's parent rc
    HDC     hdcClient;          // DC handle of client area of main frame
    HRGN    hRgnPath;           // Region handle for the drawing surface
    HANDLE  hThrd;              // handle to drawing thread or play thread
    HANDLE  hThrd0;
    BOOL    bDrawing;           // curently drawing?
    DWORD   dwThreadId;         // drawing thread or play thread ID
    DWORD   dwElapsed;          // elapsed time for the drawing operation
    double  xFrom;              // drawing range in floating points
    double  xTo;                //
    double  yFrom;              //         Floating Points
    double  yTo;                //
    double  c1;                 // C = c1 + i c2 where c1, c2 are reals
    double  c2;                 // the C value corresponding to the Julia set
    LONG    lxFrom;             // drawing range in fix points
    LONG    lxTo;               //
    LONG    lyFrom;             //         Fix Points
    LONG    lyTo;               //
    LONG    lc1;                // C = c1 + i c2 where c1, c2 are reals
    LONG    lc2;                // the C value corresponding to the Julia set
    HBITMAP hBmpSaved;          // saved bitmap for the drawing
    BOOL    bSizeChng;          //        not used
    BOOL    bMandel;            // Drawing is a Mandelbrot or Julia set?
    int     iIteration;         // number of computations done on each pixel
    int     iStep;              // drawn on every one, two or three line(s)?
    BOOL    bStretch;           // stretching bitmaps
    int     iStretchMode;       // stretching mode to use
    BOOL    bSetDIBsToDevice;   // SetDIBsToDevice reather than BitBlt?
    BOOL    bFill;              // FloodFill mode presently?
    HBRUSH  hBrush;             // handle to brush
    HANDLE  hQuitEvent;         // Event for quiting color cycling thread
    HANDLE  hCycleThrd;         // Color cycling thread
    DWORD   dwCycleThrdID;      // Color cycling thread ID
    BOOL    bClrCycle;          // For suspending and resuming color cycle thrd
    BOOL    bFirstTime;         // Creating color cycling thrd only once
    DWORD   dwSuspend;          // Store return result of suspend/resume cycle thrd
    HBITMAP hBmpMono;           // Monochrome bitmap
    BOOL    bUseMono;           // Display monochrome bitmap instead
    HANDLE  hPrtThrd;           // Print thread
    DWORD   dwPrtThrdID;        // Print thread ID
    HPALETTE    hPal;           // The palette used for the drawing
    HPALETTE    hHTPal;         // The halftone palette used for the drawing
    HPALETTE    hCyclePal;
    RLEDATA RleData;            // RLE data for RLE viewer
    BOOL    bPlayRleCont;       // Playing RLE continuously
    PVOID   *prghPen;           // Pointer to array of hPen
    INT     iPen;               // number of Pens
    INT     iPriority;          // thread priority
    BOOL    bUseDIB;            // Should we use the DIB for stretch?
    BOOL    bCoreHdr;           // used in bDrawDIB
} INFO, *PINFO;

typedef struct _PrtData{
    INFO        info;
    int         index;
    BOOL        bUseDefault;
    DEVMODE     DevMode;
} PRTDATA, *PPRTDATA;

typedef struct _FileHdr{
    DWORD       bfSize;
    WORD        bfReserved1;
    WORD        bfReserved2;
    DWORD       bfOffbits;
} FILEHDR;
