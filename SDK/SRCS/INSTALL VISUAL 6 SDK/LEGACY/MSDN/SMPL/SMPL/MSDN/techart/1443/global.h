/*
    global.h

    Main application header file

*/

#include <windows.h>
#include <shellapi.h>
#include <commdlg.h>
#include "dialogs.h"
#ifndef RC_INVOKED // OLE headers nuke the resource compiler
#include <stdlib.h>
#include <memory.h>
#include <malloc.h>
#include <stdio.h>
#include <ole2.h>
#endif // RC_INVOKED

//
// Menu ids
//

#define IDM_OPEN            0x0100
#define IDM_SAVE            0x0101
#define IDM_SAVEAS          0x0102
#define IDM_PRINT           0x0103
#define IDM_PRINTSETUP      0x0104
#define IDM_EXIT            0x0105
#define IDM_NEW             0x0106

#define IDM_CUT             0x0200
#define IDM_COPY            0x0201
#define IDM_PASTE           0x0203
#define IDM_INSERTOBJECT    0x0204

#define IDM_DEBUG0          0x0800
#define IDM_DEBUG1          (IDM_DEBUG0+1)
#define IDM_DEBUG2          (IDM_DEBUG0+2)
#define IDM_DEBUG3          (IDM_DEBUG0+3)
#define IDM_DEBUG4          (IDM_DEBUG0+4)
#define IDM_DEBUG_DIRTY     (IDM_DEBUG0+5)

#define IDM_HELPCONTENTS    0x0900
#define IDM_ABOUT           0x0901

//
// Clipboard formats
//

#define CF_TEXTBOXOBJECT "Text Box Object"

//
// Names of streams in the OLE2 structured storage model we use
//

#define INFO_STREAM     "INFO"
#define OBJECT_STREAM   "TEXTOBJECTS"


//
// Structure used to describe an object
//

#define DEFAULT_OBJ_WIDTH   100
#define DEFAULT_OBJ_HEIGHT  75

typedef struct _OBJECT {
    struct _OBJECT FAR *pNext;  // pointer to the next one
    LPVOID pInfo;               // pointer to its info
    RECT rc;                    // container rectangle
    UINT uiSize;                // size of the info
    BOOL bSelected;             // is it selected
    UINT uiType;                // CF_TEXT etc
} OBJECT, FAR *POBJECT;

//
// Structure used in the INFO stream
//

#define MAKEFOURCC( ch0, ch1, ch2, ch3 )                                \
                ( (DWORD)(BYTE)(ch0) | ( (DWORD)(BYTE)(ch1) << 8 ) |    \
                ( (DWORD)(BYTE)(ch2) << 16 ) | ( (DWORD)(BYTE)(ch3) << 24 ) )

#define FILEMAGIC MAKEFOURCC('T','B','O','X')
#define FILEEXT "TBS"

typedef struct _FILEHEADER {
    DWORD dwMagic;              // magic number
    int iWidth;                 // width of the window
    int iHeight;                // height of the window
} FILEHEADER, FAR *PFILEHEADER;

//
// global data
//

char *gszAppName;                   // App name
HINSTANCE ghAppInstance;            // app instance
HWND ghwndMain;                     // main window handle
TEXTMETRIC gtmSysFont;              // system font metrics
HANDLE ghAccTable;                  // accelerator table
UINT gcfTextBoxObject;
POBJECT gpObjList;                  // pointer to the object list
POINT gptInsert;                    // coords of insertion point

//
// main.c
//

extern LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern UINT cdecl Message(UINT uiBtns, LPSTR lpFormat, ...) ;

//
// init.c
//

extern BOOL InitFirstInstance(HANDLE hInstance);
extern BOOL InitCurrentInstance(HANDLE hInstance, LPSTR lpszCmdLine, int cmdShow);
extern void Terminate(void);

//
// help.c
//

extern void About(HWND hWnd);
extern void Help(HWND hWnd, WORD wParam);

//
// file.c
//

// <dwFlags> for PromptForFileName()
#define PFFN_OPENFILE        0x0001    // prompt to open a file
#define PFFN_SAVEFILE        0x0002    // prompt to save a file
#define PFFN_SHOWDEFAULT     0x0004    // init. show what's in <achFileName>
#define PFFN_OVERWRITEPROMPT 0x0008    // prompt the user about overwriting
#define PFFN_UPPERCASE       0x0010    // make the name uppercase

// flags for File functions
#define FILE_PROMPT_FOR_SAVE        0x0001
#define FILE_DONT_PROMPT_FOR_SAVE   0x0000
#define FILE_UPDATE_CAPTION         0x0002
#define FILE_DONT_UPDATE_CAPTION    0x0000
#define FILE_SAVE                   0x0000
#define FILE_SAVE_AS                0x0004

// global file data
BOOL gfDirty;
char gachFileName[_MAX_PATH];
BOOL gfUntitled;

// functions
extern BOOL FileNew(WORD wFlags);
extern BOOL FileOpen(LPSTR szFileName);
extern BOOL FileSave(WORD wFlags);
extern BOOL PromptToSave(void);
BOOL PromptForFileName(HWND hwndOwner,   // window that will own dialog box
                       HANDLE hInst,     // module that contains the resources
                       LPSTR achFileName,// where to put file name
                       WORD cchFileName, // size of <achFileName>
                       LPSTR szCaption,  // caption string
                       LPSTR szFilter,   // file filter
                       LPSTR szDefExt,   // default extension
                       DWORD dwFlags);   // random flags

//
// clip.c
//

extern void ClipCommand(HWND hWnd, WPARAM aParam);
extern void InitClipMenu(HMENU hmenuPopup);

//
// print.c
//

extern void Print(HDC hDC);

//
// Debug support
//

extern LRESULT CALLBACK DebugWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#ifdef DEBUG

    DWORD   __dwEval;
    int __iDebugLevel;

    extern void SetDebugLevel(int i);
    extern void __AssertMsg(LPSTR exp ,LPSTR file, int line);
    extern void cdecl DbgOut(LPSTR lpFormat, ...);

    #define ASSERT(exp) \
        ((exp) ? (void)0 : __AssertMsg((LPSTR)(#exp), (LPSTR)__FILE__, __LINE__))
    #define EVAL(exp) \
        (__dwEval=(DWORD)(exp), (__dwEval) ? (void)0 : __AssertMsg((LPSTR)(#exp), (LPSTR)__FILE__, __LINE__), __dwEval)

    #define dprintf                          DbgOut
    #define dprintf1 if (__iDebugLevel >= 1) DbgOut
    #define dprintf2 if (__iDebugLevel >= 2) DbgOut
    #define dprintf3 if (__iDebugLevel >= 3) DbgOut
    #define dprintf4 if (__iDebugLevel >= 4) DbgOut

#else // not DEBUG

    #define ASSERT(exp) 0
    #define EVAL(exp) (exp)

    #define dprintf  if (0) ((int (*)(char *, ...)) 0)
    #define dprintf1 if (0) ((int (*)(char *, ...)) 0)
    #define dprintf2 if (0) ((int (*)(char *, ...)) 0)
    #define dprintf3 if (0) ((int (*)(char *, ...)) 0)
    #define dprintf4 if (0) ((int (*)(char *, ...)) 0)

#endif // DEBUG

//
// object.c
//

#define SB_WIDTH            5       // width of size border

#define SB_HIT_NONE         0
#define SB_HIT_TOP          1
#define SB_HIT_LEFT         2
#define SB_HIT_BOTTOM       3
#define SB_HIT_RIGHT        4

extern POBJECT CreateObj(int x, int y, int w, int h, 
                         UINT uiType, UINT uiSize, LPVOID pData);
extern void DeleteObj(POBJECT pObj);
extern void RenderObj(HDC hDC, POBJECT pObj);
extern void InsertObjCmd(HWND hWnd);
extern POBJECT HitTestObj(int x, int y);
extern UINT SizeBorderHitTestObj(int x, int y);
extern void SelectObj(POBJECT pObj, BOOL bDesel);
extern void BringObjToTop(POBJECT pObj);
extern void AppendObj(POBJECT pObj);
extern void UnlinkObj(POBJECT pObj);

//
// memory allocation macros
//

#define ALLOCATE(s) (_fcalloc((s),1))
#define FREE(p)     (_ffree(p))
