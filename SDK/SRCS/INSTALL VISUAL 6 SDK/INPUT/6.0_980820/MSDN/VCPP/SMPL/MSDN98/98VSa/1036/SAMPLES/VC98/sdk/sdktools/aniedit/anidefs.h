/*
 * Common includes
 *
 */
#include "anicur.h"
#include "anidlgs.h"
#include "animsg.h"

/*
 * Constants
 *
 */
#define CMS_WAIT_FOR_PROCESS    (60 * 1000) // one minute

#define AIM_PROCESSTERM         (WM_USER + 0x0FFF)
#define AIM_SETCHILDAPP         (AIM_PROCESSTERM + 1)

#define CCH_TITLE    80
#define CCH_CREATOR  80
#define CCH_JIF      10         /* Numbers are small even in German! */

#define CTRL_C  (TEXT(('C' - 'A') + 1))
#define CTRL_V  (TEXT(('V' - 'A') + 1))
#define CTRL_X  (TEXT(('X' - 'A') + 1))

#define TITL_ERROR  (DWORD)(-1)
#define szPREVIEW   TEXT("AniEditPreviewClass")
#define szBNTBAR    TEXT("AniEditBtnBarClass")


#define PM_NEWCURSOR            (WM_USER + 0x4a50)
#define PM_PAUSEANIMATION       (PM_NEWCURSOR + 1)
#define PM_UNPAUSEANIMATION     (PM_NEWCURSOR + 2)
#define PM_SETSTEP              (PM_NEWCURSOR + 3)

#define ID_PREVIEWTIMER         (0x0050)

#define MULTISEL        1       /* listbox is mutliple selction */

/*
 * Structure defintions
 *
 */
typedef struct _FRAME *PFRAME;

typedef struct _FRAME {
    int         cRef;           /* refrence count */
    int         iFrame;
    PFRAME      pfrmNext;
    DWORD       dwCheckSum;     /* checksum of the icon data.  Used to
                                 * compare new imported icons against existing
                                 * ones to see if we can sequence them.
                                 */
    HICON       hcur;           /* icon representation of raw data below */
    WORD        xHotSpot;
    WORD        yHotSpot;
    RTAG        rtag;           /* icon chunk as it appears in file */
    BYTE        abIcon[1];
} FRAME;


typedef struct _STEP *PSTEP;

typedef struct _STEP {
    JIF     jif;
    PFRAME  pfrmFrame;
} STEP;

typedef struct _THDDATA {
    HWND    hwndCaller;
    HWND    hwndMonitor;
    HANDLE  hprocMonitor;
} THDDATA, *PTHDDATA;

typedef struct _ANICUR {
    ANIHEADER anih;
    BOOL      fDirty;
    CHAR      azTitle[CCH_TITLE];
    CHAR      azCreator[CCH_CREATOR];
    TCHAR     szFile[MAX_PATH];
} ANICUR;


typedef struct _CLPBRDDAT *PCLPBRDDAT;

typedef struct _CLPBRDDAT {
    PCLPBRDDAT pcbdNext;
    STEP    stp;
} CLPBRDDAT;

//
// Structure that contains data used within a preview window.  This
// data is unique for each preview window, and is used to optimize
// the painting.
//
typedef struct
{
    HDC hdcMem;
    HBITMAP hbmMem;
    HBITMAP hbmOld;
    HICON   hcur;
    DWORD   iFrame;
    WORD    xHot;
    WORD    yHot;
} PREVIEWDATA, *PPREVIEWDATA;

typedef struct {
    int id;
    int idSys;
} RADIOCOLOR;

/*
 * Header of the resource file in the new format
 */
#pragma pack(2)
typedef struct tagNEWHEADER {
    WORD reserved;
    WORD rt;
    WORD cResources;
} NEWHEADER, *LPNEWHEADER;

typedef struct tagICONDIR {
    BYTE Width;            /* 16, 32, 64 */
    BYTE Height;           /* 16, 32, 64 */
    BYTE ColorCount;       /* 2, 8, 16 */
    BYTE reserved;
} ICONDIR;

typedef struct tagCURSORDIR {
    WORD Width;
    WORD Height;
} CURSORDIR;

typedef struct tagRESDIR {
    union {
        ICONDIR Icon;
        CURSORDIR Cursor;
    } ResInfo;

    WORD Planes;
    WORD BitCount;
    DWORD BytesInRes;
    WORD idIcon;
} RESDIR;
typedef RESDIR *LPRESDIR;

typedef struct _ICONFILERESDIR {    // ird
    BYTE bWidth;
    BYTE bHeight;
    BYTE bColorCount;
    BYTE bReserved;
    WORD xHotspot;
    WORD yHotspot;
    DWORD dwDIBSize;
    DWORD dwDIBOffset;
} ICONFILERESDIR;

typedef struct tagCURSORRESOURCE {
    WORD xHotspot;
    WORD yHotspot;
    BITMAPINFOHEADER bih;
} CURSORRESOURCE, *PCURSORRESOURCE;
#pragma pack()


/*
 * Globals
 *
 */
extern HANDLE hInst;
extern HWND ghwndMain;
extern HWND ghwndLB;
extern int gcyCursor, gcxCursor;
extern HBRUSH ghbrHighlight, ghbrWindow, ghbrPrevBackgnd;
extern COLORREF gcrHighlightText;
extern ANICUR ganiAcon;
extern TCHAR gszTempFile[];
extern BOOL gfEditFrame;
extern TCHAR gszWindowTitle[];
extern TCHAR gszDots[];
extern PFRAME   gpfrmFrames;
extern PCLPBRDDAT gpbdClipBoard;
extern TCHAR gszCursorEditor[MAX_PATH];
extern int giradColor;
RADIOCOLOR garadColor[];

/*
 * String table pointers
 */
extern LPTSTR gpszAniFilter;
extern LPTSTR gpszImagEdit;
extern LPTSTR gpszCUR;
extern LPTSTR gpszANI;
extern LPTSTR gpszUnknownError;
extern LPTSTR gpszCurFilter;
extern LPTSTR gpszUntitled;
extern LPTSTR gpszImport;

/*
 * Macros
 *
 */
#if 0
#   include <stdio.h>
#   define DPRINT(p)   if(1){ printf p; fflush(stdout); } else
#else
#   define DPRINT(p)
#endif


#define WRITEME(hwnd)       \
            MessageBox(hwnd, "This function is not yet implemented",    \
            NULL, MB_OK | MB_ICONSTOP)

#define FALLTHRU(label)

#define COUNTOF(sz)     (sizeof(sz) / sizeof((sz)[0]))

#define FreeMem(pv)     LocalFree((HLOCAL)pv)

#define IsValidPS(ps)   (((ps) != (PSTEP)LB_ERR) && ((ps) != NULL))


#define PADUP(cb)       (((cb) + 1) & ~1)
#define RET_CLOSE_IF_ERR( func, hf )  \
        if( !func ) {CloseHandle(hf); return FALSE;} else

#define GetStep(hwnd, iSel) (PSTEP)SendDlgItemMessage(hwnd, \
        DLG_MAIN_FRAMELIST, LB_GETITEMDATA, iSel, 0)

#define GetStepCount(hwnd) SendDlgItemMessage(hwnd, \
        DLG_MAIN_FRAMELIST, LB_GETCOUNT, 0, 0)

#define GetSelStepCount(hwnd) SendDlgItemMessage(hwnd, \
        DLG_MAIN_FRAMELIST, LB_GETSELCOUNT, 0, 0)

#define ResumePreview(hwnd, id) \
    SendDlgItemMessage(hwnd, id, PM_UNPAUSEANIMATION, 0, 0)

#define PausePreview(hwnd, id) \
    SendDlgItemMessage(hwnd, id, PM_PAUSEANIMATION, 0, 0)

#define SetPreviewStep(hwnd, id, iStep) \
    SendDlgItemMessage(hwnd, id, PM_SETSTEP, iStep, 0)

#define PreviewCursor(hwnd, id) \
    SendDlgItemMessage(hwnd, id, PM_NEWCURSOR, 0, 0)

#define FmtFree( psz ) if((psz) != gszDots) LocalFree(psz); else

#define UpdateStepSel( hWnd )                                    \
    SendMessage(hWnd, WM_COMMAND, MAKEWPARAM( DLG_MAIN_FRAMELIST, \
            LBN_SELCHANGE), (LPARAM)(GetDlgItem(hWnd,             \
            DLG_MAIN_FRAMELIST)))

#define SetStepSel(hWnd, iMin, iMax)    (               \
    SendDlgItemMessage(hWnd, DLG_MAIN_FRAMELIST,        \
            LB_SELITEMRANGE, TRUE, MAKELPARAM((iMin), (iMax))), \
    UpdateStepSel(hWnd)                                 \
)


/*
 * Function Prototypes
 *
 */

/*
 * In aniedit.c
 */
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
INT  APIENTRY GetHeightFromPoints( int pts);
BOOL APIENTRY MainWndProc(HWND hWnd, UINT message, UINT wParam, LONG lParam);
void DrawCursorListItem( DRAWITEMSTRUCT *pdis );
int FmtMessageBox( HWND hwnd, DWORD dwTitleID, LPTSTR pszTitleStr,
    UINT fuStyle, BOOL fSound, DWORD dwTextID, ... );
LPTSTR FmtSprintf( DWORD id, ... );
PVOID AllocMem( DWORD cb );
LRESULT CALLBACK PreviewWndProc( HWND hwnd, UINT msg, WPARAM wParam,
        LPARAM lParam );
VOID NextFrame( HWND hwnd, BOOL fRun );
VOID SetWindowFileTitle(HWND hWnd, LPTSTR szFileTitle);
void AniAddFontModule(HINSTANCE hInst);
VOID ReadRegistry( VOID );
VOID WriteRegistry( VOID );
LRESULT CALLBACK BtnBarWndProc( HWND hwnd, UINT msg, WPARAM wParam,
        LPARAM lParam);
#ifdef DBCS
BOOL LoadResourceStr( VOID );
#endif


/*
 * In anicmd.c
 */
void LoadAniFile(HWND hWnd, HANDLE hfCursor, LPTSTR szFileTitle, LPTSTR szFile);
BOOL DoCommand( HWND hWnd, UINT wParam, LONG lParam );
VOID ExitCommand(HWND hWnd);
BOOL CheckDirty(HWND hWnd);
void NewAniCursor( HWND hwnd );
BOOL ExecProgram( HWND hwndCaller, LPTSTR pszCmdLine );
BOOL GetCurrentSel( HWND hwnd, int id, int *paiSel, int ciSel, int *pcSel );
VOID SetCurrentSel( HWND hwnd, int id, BOOL fExtend, int iSel);
VOID EditFrame(HWND hWnd, BOOL fEditFrame);
PSTEP NewStep( void );
VOID DestroyStep( PSTEP ps );
VOID CopyStep( PSTEP psDst, PSTEP psSrc );
VOID LinkStepFrame(PSTEP ps, PFRAME pf );
VOID DestroyFrame( PFRAME pf );
PCLPBRDDAT NewClpBrdDat( void );
VOID DestroyClpBrdDat(PCLPBRDDAT pcbd);
int __cdecl RevCompInts(const void *elm1, const void *elm2);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);
BOOL APIENTRY OptionsProc( HWND hDlg, UINT message, UINT wParam, LONG lParam);
void ClearStepSel( HWND hWnd );



/*
 * In anifile.c
 */
BOOL CreateFrameFromCursorFile(HWND hwnd,  LPTSTR pszFile, BOOL fEdit);
HANDLE PromptAndOpenFile( HWND hwnd, DWORD  cchFileTitle, LPTSTR pszFileTitle,
    DWORD cchFileName, LPTSTR pszFileName, LPTSTR pszFilter);
BOOL PromptForFile( HWND hwnd, DWORD  cchFileTitle, LPTSTR pszFileTitle,
    DWORD  cchFileName, LPTSTR pszFile, LPTSTR pszFilter, LPTSTR pszDlgTitle,
    BOOL fSave );
BOOL ReadAniFile( HWND hwnd, HANDLE hf );
PFRAME ReadIconFromFile(HWND hwnd, HANDLE hf, DWORD ckSize);
BOOL ReadTag( HANDLE hf, PRTAG ptag);
BOOL ReadChunk( HANDLE hf, PRTAG ptag, PVOID pv);
BOOL ReadChunkN( HANDLE hf, PRTAG ptag, PVOID pv, DWORD cbMax);
BOOL SkipChunk( HANDLE hf, PRTAG ptag);
DWORD CalcCheckSum( PBYTE pb, DWORD cb );
HICON ConvertDataToIcon( PFRAME pf, WORD *pxHotSave, WORD *pyHotSave );
BOOL GetTempCursorFileName( LPTSTR pszName );
BOOL SaveAniFile( HWND hwnd, HANDLE hf );
BOOL WriteTag(HANDLE hf, PRTAG prtag);
BOOL WriteType(HANDLE hf, FOURCC ckID );
BOOL WriteTagData(HANDLE hf, PRTAG prtag, VOID *pvData );
VOID SaveFile(HWND hwnd, BOOL fPrompt);
