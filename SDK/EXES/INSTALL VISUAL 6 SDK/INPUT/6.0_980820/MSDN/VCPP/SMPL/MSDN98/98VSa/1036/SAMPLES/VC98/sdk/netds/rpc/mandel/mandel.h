/****************************************************************************

    MANDEL.H -- Constants and function definitions for MANDEL.C

    Copyright (C) 1990 - 1997 Microsoft Corporation

****************************************************************************/

/* Constants */

#ifdef WIN16
#define APIENTRY        PASCAL
#define UNREFERENCED_PARAMETER
#endif

#define IDM_ABOUT        100
#define IDM_ZOOMIN       101
#define IDM_ZOOMOUT      105
#define IDM_TOP          106
#define IDM_REDRAW       107
#define IDM_EXIT         108
#define IDM_CONTINUOUS   109
#define IDM_PROTSEQ      110
#define IDD_PROTSEQNAME  111
#define IDM_SERVER       112
#define IDD_SERVERNAME   113
#define IDM_ENDPOINT     114
#define IDD_ENDPOINTNAME 115
#define IDM_BIND         116
#define IDM_GO           117
#define IDM_1LINE        200
#define IDM_2LINES       201
#define IDM_4LINES       202

#define WIDTH            300
#define HEIGHT           300
#define LINES              4
#define BUFSIZE         1200     // (HEIGHT * LINES)
#define MAX_BUFSIZE     4800     // (BUFSIZE * sizeof(short))

#define POLL_TIME        2000

#define CNLEN             25     // computer name length
#define UNCLEN       CNLEN+2     // \\computername
#define PATHLEN           260    // Path
#define MSGLEN            300    // arbitrary large number for message size
#define MAXPROTSEQ         20    // protocol sequence

#define NCOLORS           11

#define SVR_TABLE_SZ      20

// Status of connection to server
#define SS_DISCONN         0
#define SS_IDLE            1
#define SS_READPENDING     2
#define SS_PAINTING        3
#define SS_LOCAL           4

#define MINPREC       5.0E-9
#define MAXPREC       5.0E-3

#define WM_DOSOMEWORK   (WM_USER+0)
#define WM_PAINTLINE    (WM_USER+1)

#define EXCEPT_MSG      "The remote procedure raised an exception.\n\
Check your connection settings."

/* Data Structures */

typedef struct _svr_table {
    char    name[UNCLEN];       // name of remote server
    int     hfPipe;             // RPC handle
    int     iStatus;            // status of connection
    int     cPicture;           // picture id for this line
    DWORD   dwLine;             // line we're drawing
    int     cLines;             // lines in this chunk
} svr_table;

#ifndef RPC                     // If RPC, the following data would be
                                // defined in the IDL file
typedef struct _cpoint {
    double    real;
    double    imag;
} CPOINT;

typedef CPOINT * PCPOINT;

typedef struct _LONGRECT {
    long    xLeft;
    long    yBottom;
    long    xRight;
    long    yTop;
} LONGRECT;

typedef LONGRECT *PLONGRECT;

typedef unsigned short LINEBUF[BUFSIZE];

#endif

typedef struct _calcbuf {
    LONGRECT  rclDraw;
    double    dblPrecision;
    DWORD     dwThreshold;
    CPOINT    cptLL;
} CALCBUF;


/* Function Prototypes */

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);

LONG APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);
BOOL APIENTRY Protseq(HWND, UINT, UINT, LONG);
BOOL APIENTRY Server(HWND, UINT, UINT, LONG);
BOOL APIENTRY Endpoint(HWND, UINT, UINT, LONG);

#ifdef RPC
RPC_STATUS Bind(HWND);
#endif

void CountHistogram(void);

BOOL InitRemote(HWND);
BOOL CheckDrawStatus(HWND);
void SetNewCalc(CPOINT, double, RECT);
void IncPictureID(void);
void ResetPictureID(void);
BOOL CheckDrawingID(int);
DWORD QueryThreshold(void);

// buffer routines
BOOL TakeDrawBuffer(void);
LPVOID LockDrawBuffer(void);
void UnlockDrawBuffer(void);
void ReturnDrawBuffer(void);
void FreeDrawBuffer(void);


#ifndef RPC                     // If RPC, MandelCalc() would be
                                // defined in the IDL file
void MandelCalc(PCPOINT   pcptLL,
                PLONGRECT prcDraw,
                double    precision,
                DWORD     ulThreshold,
                LINEBUF * pbBuf);
#endif



