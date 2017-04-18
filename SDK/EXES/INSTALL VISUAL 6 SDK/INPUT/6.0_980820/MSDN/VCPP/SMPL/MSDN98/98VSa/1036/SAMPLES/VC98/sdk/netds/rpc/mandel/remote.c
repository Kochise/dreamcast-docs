/****************************************************************************
                   Microsoft RPC Version 2.0
           Copyright Microsoft Corp. 1992, 1993, 1994- 1996
                        mandel Example

    FILE:      remote.c

    PURPOSE:   Client side of the RPC distributed application Mandel

    COMMENTS:  Code to do the remote calculations for the Windows
               Mandelbrot Set distributed drawing program.

               Information coming into this module (via API calls) is
               based on upper-left being (0,0) (the Windows standard).
               We translate that to lower-left is (0,0) before we ship
               it out onto the net, and we do reverse translations
               accordingly.

               The iteration data is passed back to the main window
               procedure (by means of a WM_PAINTLINE message) which
               draws the picture.

               A word about the shared buffer: multiple buffers could
               be used, but a single one is used. The buffer is requested
               in this code, and then released after the data has been
               drawn (in PaintLine() in mandel.c). So long as the painting
               is done quickly, this is efficient.

****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#ifdef RPC
#include "mdlrpc.h"
#endif
#include "mandel.h"


/*
 * External variables
 */
extern int          fBound;
extern svr_table    SvrTable;    // the server table
extern int          iLines;
extern double       dPrec;
extern int          fContinueZoom;
extern int          fZoomIn;
extern int          iHistMaxI;
extern int          iHistMaxJ;
extern RECT         rcZoom;
extern BOOL         fRectDefined;


/*
 * Picture information
 */
int             cPictureID = 0;    // picture id, in case we reset in the middle
static CPOINT   cptLL;             // upper-left
static double   dPrecision;        // precision of draw
static LONGRECT rclPicture;        // rectangle defining client window
static DWORD    dwCurrentLine;     // next line to be drawn
static DWORD    dwThreshold;       // threshold for iterations

/*
 * Function prototypes for local procs
 */
DWORD CalcThreshold(double);


/*
 *  InitRemote --
 *
 *  This function initializes everything for our remote connections.
 *  It gets the local wksta name (making sure the wksta is started)
 *  and it creates the mailslot with which to collect replies to our poll.
 *
 *  RETURNS
 *      TRUE    - initialization succeeded
 *      FALSE   - initialization failed, can't go on
 */

BOOL InitRemote(HWND hWnd)
{

#ifndef RPC
    UNREFERENCED_PARAMETER(hWnd);
#endif

    // set up our local entry
    strcpy(SvrTable.name, "Local machine");
    SvrTable.iStatus = SS_LOCAL;

    // good, we succeeded
    return(TRUE);
}


/*
 *  CheckDrawStatus --
 *
 *  This function does a check of all buffers being drawn.
 *
 *  If it finds an idle pipe, and there is work to be done, it assigns
 *      a line, and writes out the request.
 *  If it finds a read-pending pipe, it checks if the read has completed.
 *      If it has, it is read and a message is sent so the read data can
 *      be processed.
 *
 *  RETURNS
 *      TRUE    - we did a piece of work
 *      FALSE   - we could not find any work to do.
 */

BOOL CheckDrawStatus(HWND hwnd)
{
    CALCBUF     cb;
    LPVOID      pbBuf;

    while(TRUE) {

        // Check the status
        switch(SvrTable.iStatus) {

        case SS_PAINTING:
            break;

        case SS_IDLE:
            break;

        case SS_LOCAL:
            // Do a chunk of work locally

#ifdef RPC
            if (fBound == FALSE)
                break;
#endif

            if ((long) dwCurrentLine > rclPicture.xRight) {
                if (fContinueZoom == TRUE) {
                    if ((fZoomIn == TRUE) && (dPrec < (double)MINPREC))
                        fZoomIn = FALSE;  // start zooming out
                    if ((fZoomIn == FALSE) && (dPrec > (double)MAXPREC))
                        fZoomIn = TRUE;
                    if (fZoomIn) {
                        CountHistogram();
                        rcZoom.top    = iHistMaxJ * (WIDTH/4);
                        rcZoom.bottom = rcZoom.top + (WIDTH/4) - 1;
                        rcZoom.left   = iHistMaxI * (HEIGHT/4);
                        rcZoom.right  = rcZoom.left + (HEIGHT/4) - 1;
                        fRectDefined = TRUE;
                        PostMessage(hwnd, WM_COMMAND, IDM_ZOOMIN, 0L);
                    }
                    else
                        PostMessage(hwnd, WM_COMMAND, IDM_ZOOMOUT, 0L);
                }
                break;
            }

            if (TakeDrawBuffer() == FALSE)
                break;

            pbBuf = LockDrawBuffer();

            cb.rclDraw.xLeft = dwCurrentLine;
            cb.rclDraw.xRight = dwCurrentLine + iLines - 1;
            cb.rclDraw.yTop = rclPicture.yTop;
            cb.rclDraw.yBottom = rclPicture.yBottom;

            RpcTryExcept {
                MandelCalc(&cptLL,
                           &(cb.rclDraw),
                           dPrecision,
                           dwThreshold,
                           (LINEBUF *) pbBuf);
            }
            RpcExcept(1) {
                char szFail[MSGLEN];

                sprintf (szFail, "%s (0x%x)\n", EXCEPT_MSG, RpcExceptionCode());
                MessageBox(hwnd,
                           szFail,
                           "Remote Procedure Call",
                           MB_ICONINFORMATION);
                        KillTimer(hwnd, 1);  // stop timer for polls
                    EnableMenuItem(GetMenu(hwnd), IDM_GO, MF_ENABLED);  // enable GO
                    UnlockDrawBuffer();

                            ReturnDrawBuffer();
                        return(FALSE);
            }
            RpcEndExcept

            UnlockDrawBuffer();

            SvrTable.cPicture = cPictureID;
            SvrTable.dwLine = dwCurrentLine;
            SvrTable.cLines = iLines;

            PostMessage(hwnd, WM_PAINTLINE, 0, 0L);
            dwCurrentLine += iLines;

            return(TRUE);
        }

        return(FALSE);
    }
}


/*
 *  SetNewCalc --
 *
 *  This sets up new information for a drawing and
 *  updates the drawing ID so any calculations in progress will not
 *  be mixed in.
 */

void SetNewCalc(CPOINT cptUL, double dPrec, RECT rc)
{
    // First, translate from upper left to lower left
    cptLL.real = cptUL.real;
    cptLL.imag = cptUL.imag - (dPrec * (rc.bottom - rc.top));

    // Now the precision
    dPrecision = dPrec;

    // The rectangle. Once again, translate.
    rclPicture.xLeft = (long) rc.left;
    rclPicture.xRight = (long) rc.right;
    rclPicture.yBottom = (long) rc.top;
    rclPicture.yTop = (long) rc.bottom;

    // Current line, start of drawing
    dwCurrentLine = rclPicture.xLeft;

    dwThreshold = CalcThreshold(dPrecision);
}


void IncPictureID(void)
{
    cPictureID++;
}


void ResetPictureID(void)
{
    cPictureID = 0;
}


/*
 *  CheckDrawing --
 *
 *  Just a sanity check here -- a function to check to make sure that we're
 *  on the right drawing
 */

BOOL CheckDrawingID(int id)
{
    return((id == cPictureID) ? TRUE : FALSE);
}


/*
 *  TakeDrawBuffer ensures only one pipe read at a time.
 *  LockDrawBuffer locks the handle and returns a pointer.
 *  UnlockDrawBuffer unlocks the handle.
 *  ReturnDrawBuffer lets another pipe read go.
 *  FreeDrawBuffer ensures the allocated buffer is freed upon exit.
 */

static BOOL fBufferTaken = FALSE;
static HANDLE hSharedBuf = (HANDLE) NULL;


BOOL TakeDrawBuffer(void)
{
    if (fBufferTaken) {
        return(FALSE);
    }

    if (hSharedBuf == (HANDLE) NULL) {
        hSharedBuf = LocalAlloc(LMEM_MOVEABLE, MAX_BUFSIZE);
        if (hSharedBuf == (HANDLE) NULL)
            return(FALSE);
    }

    fBufferTaken = TRUE;
    return(TRUE);
}


LPVOID LockDrawBuffer(void)
{
    if (hSharedBuf == (HANDLE) NULL)
        return(NULL);

    return(LocalLock(hSharedBuf));
}


void UnlockDrawBuffer(void)
{
    LocalUnlock(hSharedBuf);
}


void ReturnDrawBuffer(void)
{
    fBufferTaken = FALSE;
}


void FreeDrawBuffer(void)
{
    if (hSharedBuf != (HANDLE) NULL)
        LocalFree(hSharedBuf);
}


/*
 *  CalcThreshold --
 *
 *  We need an iteration threshold beyond which we give up. We want it to
 *  increase the farther we zoom in. This code generates a threshold value
 *  based on the precision of drawing.
 *
 *  RETURNS
 *      threshold calculated based on precision
 */

DWORD CalcThreshold(double precision)
{
    DWORD   thres = 25;
    double  multiplier = (double) 100.0;

    /* for every 100, multiply by 2 */
    while ((precision *= multiplier) < (double)1.0)
        thres *= 2;

    return(thres);
}


/*
 *  QueryThreshold --
 *
 *  Callback for finding out what the current drawing's threshold is.
 */

DWORD QueryThreshold(void)
{
    return(dwThreshold);
}
