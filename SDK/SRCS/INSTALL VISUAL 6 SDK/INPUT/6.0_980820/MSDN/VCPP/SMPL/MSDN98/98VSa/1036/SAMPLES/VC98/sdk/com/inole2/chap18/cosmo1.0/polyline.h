/*
 * POLYLINE.H
 *
 * Definitions and function prototypes for the PolyLine window class.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */


//Need some extra types for Windows 3.1
#ifndef WIN32
#ifndef POINTS
typedef POINT POINTS;
#endif  //POINTS

#ifndef LPPOINTS
typedef POINTS FAR *LPPOINTS;
#endif  //LPPOINTS
#endif

typedef struct
    {
    short   left;
    short   top;
    short   right;
    short   bottom;
    } RECTS, FAR *LPRECTS;

#define RECTSTORECT(rs, r) {(r).left=(rs).left;(r).top=(rs).top; \
    (r).right=(rs).right;(r).bottom=(rs).bottom;};

#define RECTTORECTS(r, rs) {(rs).left=(short)(r).left;(rs).top=(short)(r).top; \
    (rs).right=(short)(r).right;(rs).bottom=(short)(r).bottom;};

//Messages
#define PLM_RECTSET         WM_USER
#define PLM_POLYLINESET     WM_USER+1
#define PLM_POLYLINEGET     WM_USER+2
#define PLM_POLYLINENEW     WM_USER+3
#define PLM_BITMAPGET       WM_USER+4
#define PLM_METAFILEGET     WM_USER+5
#define PLM_METAFILEPICTGET WM_USER+6
#define PLM_BACKUPUNDO      WM_USER+7

//Notifications
#define PLN_POINTCHANGE     1
#define PLN_SIZECHANGE      2

//Definitions and structures.
#define CPOLYLINEPOINTS     20
#define CBPOLYLINEWNDEXTRA  sizeof(HLOCAL)

typedef struct
    {
    WORD        wVerMaj;                //Major version number.
    WORD        wVerMin;                //Minor version number.
    WORD        cPoints;                //Number of points.
    WORD        fDrawEntire;            //Flag to draw entire figure.
    RECTS       rc;
    POINTS      rgpt[CPOLYLINEPOINTS];  //Array of points.
    } POLYLINE;

typedef POLYLINE FAR *LPPOLYLINE;
#define CBPOLYLINE sizeof(POLYLINE)


//Function prototypes.
HWND     WINAPI HPolylineWindowCreate(HWND, HINSTANCE);
LONG     WINAPI PolylineWndProc(HWND, UINT, WPARAM, LPARAM);
DWORD    PASCAL LPolylineUserMessage(HWND, UINT, WPARAM, LPARAM, LPPOLYLINE);
void     PASCAL PolylineDraw(HWND, HDC, LPPOLYLINE);
