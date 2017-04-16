//
// Sample 3D Drawing routines
//  
#include "windows.h"
#include "draw3d.h"
#include "memory.h"

#ifdef WIN32
#define _fmemicmp memicmp
#endif

// Windows Versions (Byte order flipped from GetWindowsVersion)
#define ver30 0x0300      

typedef COLORREF CV;
// CoLoR Table
typedef struct
    {
    CV rgcv[ICVMAX];
    } CLRT;



// BRush Table
typedef struct
    {
    HBRUSH mpicvhbr[ICVBRUSHMAX];
    } BRT;

int mpicvSysColor[] =
    {
    COLOR_BTNHIGHLIGHT,
    COLOR_BTNFACE,
    COLOR_BTNSHADOW,
    COLOR_BTNTEXT,
    COLOR_WINDOW,
    COLOR_WINDOWTEXT,
    COLOR_GRAYTEXT,
    COLOR_WINDOWFRAME
    };


static BOOL InternalDraw3dColorChange(BOOL fForce);
static VOID DeleteObjectNull(HANDLE FAR *ph);
static VOID DeleteObjects(VOID);
static VOID PatFill(HDC hdc, RC FAR *lprc);

/*-----------------------------------------------------------------------
|   Draw3d Global ( Static ) Variables
-----------------------------------------------------------------------*/
CLRT clrt;
BRT brt;    
BOOL f3dDialogs;
int cInited;
WORD verWindows;
 
/*-----------------------------------------------------------------------
|   Draw3d Utility routines
-----------------------------------------------------------------------*/
static VOID DeleteObjectNull(HANDLE FAR *ph)
    {
    if (*ph != NULL)
        {
        DeleteObject(*ph);
        *ph = NULL;
        }
    }

static VOID DeleteObjects(VOID)
    {
    int icv;

    for(icv = 0; icv < ICVBRUSHMAX; icv++)
        DeleteObjectNull(&brt.mpicvhbr[icv]);
    }


static VOID PatFill(HDC hdc, RC FAR *lprc)
    {
    PatBlt(hdc, lprc->xLeft, lprc->yTop, lprc->xRight-lprc->xLeft, lprc->yBot-lprc->yTop, PATCOPY);
    }

       
/*-----------------------------------------------------------------------
|   Draw3dRec
|
|   Arguments:
|       HDC hdc:    
|       RC FAR *lprc:   
|       LONG cvUpperLeft:  
|       LONG cvLowerRight:  
|       WORD grbit;
|       
|   Returns:
|       
-----------------------------------------------------------------------*/
VOID Draw3dRec(HDC hdc, RC FAR *lprc, ICV icvUpperLeft, ICV icvLowerRight, DR3 dr3)
    {
    COLORREF cvSav;
    RC rc;

    cvSav = SetBkColor(hdc, clrt.rgcv[icvUpperLeft]);

    // top
    rc = *lprc;
    rc.yBot = rc.yTop+1;
    if (dr3 & DR3TOP)
        ExtTextOut(hdc, 0, 0, ETO_OPAQUE, (LPRECT) &rc, 
            (char far *) NULL, 0, (int far *) NULL);

    // left
    rc.yBot = lprc->yBot;
    rc.xRight = rc.xLeft+1;
    if (dr3 & DR3LEFT)
        ExtTextOut(hdc, 0, 0, ETO_OPAQUE, (LPRECT) &rc, 
            (char far *) NULL, 0, (int far *) NULL);

    if (icvUpperLeft != icvLowerRight)
        SetBkColor(hdc, clrt.rgcv[icvLowerRight]);

    // right
    rc.xRight = lprc->xRight;
    rc.xLeft = rc.xRight-1;
    if (dr3 & DR3RIGHT)
        ExtTextOut(hdc, 0, 0, ETO_OPAQUE, (LPRECT) &rc, 
            (char far *) NULL, 0, (int far *) NULL);

    // bot
    if (dr3 & DR3BOT)
        {
        rc.xLeft = lprc->xLeft;
        rc.yTop = rc.yBot-1;
        if (dr3 & DR3HACKBOTRIGHT)
            rc.xRight -=2;
        ExtTextOut(hdc, 0, 0, ETO_OPAQUE, (LPRECT) &rc, 
            (char far *) NULL, 0, (int far *) NULL);
        }

    SetBkColor(hdc, cvSav);
    }

VOID Draw3dInsetRect(HDC hdc, RC FAR *prc, DR3 dr3)
    {
    RC rc;

    rc = *prc;
    Draw3dRec(hdc, &rc, ICVWINDOWFRAME, ICVBTNFACE, (WORD)(dr3 & DR3ALL));
    rc.xLeft--;
    rc.yTop--;
    rc.xRight++;
    rc.yBot++;
    Draw3dRec(hdc, &rc, ICVBTNSHADOW, ICVBTNHILITE, dr3);
    }


/*-----------------------------------------------------------------------
|   Draw3dCtlColor
|
|       Common CTL_COLOR processor for 3d UITF dialogs & alerts.
|
|   Arguments:
|
|   Returns:
|       appropriate brush if f3dDialogs.  Returns FALSE otherwise
|
-----------------------------------------------------------------------*/
HBRUSH FAR PASCAL Draw3dCtlColor(UINT wm, WPARAM wParam, LPARAM lParam)
{
    if(f3dDialogs) {
            SetTextColor((HDC) wParam, clrt.rgcv[ICVBTNTEXT]);
            SetBkColor((HDC) wParam, clrt.rgcv[ICVBTNFACE]);
            return brt.mpicvhbr[ICVBTNFACE];
    }
    return (HBRUSH) FALSE;
}


/*-----------------------------------------------------------------------
|   Draw3dColorChange
|   
|       App calls this when it gets a WM_SYSCOLORCHANGE message
|       
|   Returns:
|       TRUE if successful.
|       
-----------------------------------------------------------------------*/
BOOL FAR PASCAL Draw3dColorChange(VOID)
    {
    return InternalDraw3dColorChange(FALSE);
    }


static BOOL InternalDraw3dColorChange(BOOL fForce)
    {
    ICV icv;
    static CLRT clrtNew;
    static BRT brtNew;

    if (!f3dDialogs)
        return FALSE;

    for (icv = 0; icv < ICVMAX; icv++)
        clrtNew.rgcv[icv] = GetSysColor(mpicvSysColor[icv]);

    if (verWindows == ver30)
        clrtNew.rgcv[ICVBTNHILITE] = RGB(0xff, 0xff, 0xff);

    if (clrtNew.rgcv[ICVGRAYTEXT] == 0L || clrtNew.rgcv[ICVGRAYTEXT] == clrtNew.rgcv[ICVBTNFACE])
        clrtNew.rgcv[ICVGRAYTEXT] = RGB(0x80, 0x80, 0x80);
    if (clrtNew.rgcv[ICVGRAYTEXT] == clrtNew.rgcv[ICVBTNFACE])
        clrtNew.rgcv[ICVGRAYTEXT] = 0L;

    if (fForce || _fmemicmp(&clrt, &clrtNew, sizeof(CLRT))) {
        for (icv = 0; icv < ICVBRUSHMAX; icv++)
            brtNew.mpicvhbr[icv] = CreateSolidBrush(clrtNew.rgcv[icv]);

        for (icv = 0; icv < ICVBRUSHMAX; icv++) {
            if (brtNew.mpicvhbr[icv] == NULL) {
               for (icv = 0; icv < ICVBRUSHMAX; icv++)
                  DeleteObjectNull(&brtNew.mpicvhbr[icv]);
               return FALSE;
            }
        }

        DeleteObjects();
        brt = brtNew;
        clrt = clrtNew;
        return TRUE;
    }
        
    return TRUE;
}




#ifdef IN_A_DLL
/*-----------------------------------------------------------------------
|   LibMain
-----------------------------------------------------------------------*/
#ifdef WIN32
BOOL LibMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
#else
int FAR PASCAL LibMain(hModule, wDataSeg, cbHeapSize, lpszCmdLine)
HANDLE  hModule;
WORD    wDataSeg;
WORD    cbHeapSize;
LPSTR   lpszCmdLine;
#endif
{
   return 1;
}

#endif
  

BOOL FInit3dDialogs(VOID)
{
    HDC hdc;
    extern HANDLE hinstLib;
    WORD wT;

    wT = (WORD) GetVersion();
    verWindows = (LOBYTE(wT) << 8) | HIBYTE(wT); 
    
    hdc = GetDC(NULL);
    f3dDialogs = GetDeviceCaps(hdc,BITSPIXEL)*GetDeviceCaps(hdc,PLANES) >= 4;
    
    // Win 3.1 EGA lies to us...
    if(GetSystemMetrics(SM_CYSCREEN) == 350 && GetSystemMetrics(SM_CXSCREEN) == 640)
        f3dDialogs = FALSE;
        
    ReleaseDC(NULL, hdc);
    
    if (f3dDialogs) {
        if ( !InternalDraw3dColorChange(TRUE)) {
            f3dDialogs = FALSE;
        }            
    }
    return f3dDialogs;
}



VOID End3dDialogs(VOID)
    {
    DeleteObjects();
    f3dDialogs = FALSE;
    }
               
               
BOOL FAR PASCAL Draw3dRegister(void)
{
    cInited++;
    
    if (cInited == 1) {
        return FInit3dDialogs();
    }
    return f3dDialogs;
}


BOOL FAR PASCAL Draw3dUnregister(void)
{
    cInited--;
        
    if (cInited == 0) {
       End3dDialogs();
    }
    return TRUE;
}




               




  
