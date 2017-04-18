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
#include <mmsystem.h> // for timeGetSystemTime in debugging msgs
#include <stdio.h>
#include <ole2.h>
#include <ole2ui.h>     // **** New for this app
#include <enumfetc.h>     // **** New for this app
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
#define IDM_DELETE          0x0205

#define IDM_DEBUG0          0x0800
#define IDM_DEBUG1          (IDM_DEBUG0+1)
#define IDM_DEBUG2          (IDM_DEBUG0+2)
#define IDM_DEBUG3          (IDM_DEBUG0+3)
#define IDM_DEBUG4          (IDM_DEBUG0+4)
#define IDM_DEBUGCLEAR      (IDM_DEBUG0+5)

#define IDM_HELPCONTENTS    0x0900
#define IDM_ABOUT           0x0901

//
// Names of streams in the OLE2 structured storage model we use
// Note the leading '\3' character which marks them as private
// so they won't be touched by any object handler if we use them
// in a sub-storage used to save an object's data.
//

#define INFO_STREAM     "\3INFO"
#define OBJLIST_STREAM  "\3OBJLIST"

//
// Structure used to describe an object
//

#define DEFAULT_OBJ_WIDTH   100
#define DEFAULT_OBJ_HEIGHT  75
#define OBJECT_MAGIC MAKEFOURCC('N','E','R','D')

typedef struct _OBJECT FAR *POBJECT;

typedef struct _OBJECT {
    DWORD dwMagic;                  // magic number
    POBJECT pNext;                  // pointer to the next one
    LONG lRef;                      // reference count
    LPOLEOBJECT pOleObj;            // pointer to its OLE info
    LPSTORAGE pStorage;             // pointer to its storage object
    char szStorageName[32];         // its storage name (OLE1 etc)
    RECT rc;                        // container rectangle
    BOOL bSelected;                 // is it selected
    BOOL bObjOpenInWindow;          // TRUE if open in server window
    struct _ObjIClientSite {        // IClientSite interface
        IOleClientSiteVtbl FAR * lpVtbl;  // pointer to generic vtbl for IClientSite
        POBJECT pObject;            // pointer to the objects data
    } ObjIClientSite;
    struct _ObjIAdviseSink {        // IAdviseSink interface
        IAdviseSinkVtbl FAR * lpVtbl; // pointer to generic vtbl for IAdviseSink
        POBJECT pObject;            // pointer to the objects data
    } ObjIAdviseSink;
    struct _ObjIDataObject {        // IDataObject interface
        IDataObjectVtbl FAR * lpVtbl; // pointer to generic vtbl for IDataObject
        POBJECT pObject;            // pointer to the objects data
    } ObjIDataObject;
    int iXOffset;                   // drag-drop mouse offset
    int iYOffset;
} OBJECT;

//
// Structure used primarily to implement the interfaces
// for drag and drop which are related to the entire document rather
// than to a single object within the document.  OK, OK, so we could
// view the document as yet another type of object.
//

typedef struct _MYDOCINFO FAR *PMYDOCINFO;

typedef struct _MYDOCINFO {
    LONG lRef;                      // reference count
    POINT ptMouseOffset;            // mouse offset in object in MMTEXT
    int iWidth;                     // width in MMTEXT
    int iHeight;                    // height in MMTEXT
    RECT rcDrag;                    // drag feedback rectangle
    POINTL ptlPrev;                 // prev mouse position
    struct _DocIDropTarget {        // IDropTarget interface
        IDropTargetVtbl FAR * lpVtbl; // pointer to the vtbl
        PMYDOCINFO pDocInfo;          // pointer to the base info
    } DocIDropTarget;
    struct _DocIDropSource {        // IDropSource interface
        IDropSourceVtbl FAR * lpVtbl; // pointer to the vtbl
        PMYDOCINFO pDocInfo;          // pointer to the base info
    } DocIDropSource;
} MYDOCINFO;

//
// Structure used in the INFO stream
//

#define MAKEFOURCC( ch0, ch1, ch2, ch3 )                                \
                ( (DWORD)(BYTE)(ch0) | ( (DWORD)(BYTE)(ch1) << 8 ) |    \
                ( (DWORD)(BYTE)(ch2) << 16 ) | ( (DWORD)(BYTE)(ch3) << 24 ) )

#define FILEMAGIC MAKEFOURCC('B','U','K','T')
#define FILEEXT "BKT"

typedef struct _FILEHEADER {
    DWORD dwMagic;              // magic number
    int iWidth;                 // width of the window
    int iHeight;                // height of the window
    DWORD dwNextObject;         // next object number
} FILEHEADER, FAR *PFILEHEADER;

//
// global data
//

char *gszAppName;                   // App name
HINSTANCE ghAppInstance;            // app instance
HWND ghwndMain;                     // main window handle
TEXTMETRIC gtmSysFont;              // system font metrics
HANDLE ghAccTable;                  // accelerator table
POBJECT gpObjList;                  // pointer to the object list
POINT gptInsert;                    // coords of insertion point
LPSTORAGE gpStorage;                // pointer to the current storage object
BOOL gfDirty;                       // TRUE if modified
char gachFileName[_MAX_PATH];       // current file name
DWORD gdwNextObject;                // next free object number
MYDOCINFO gDocInfo;                 // document info
int iLogPixelsX;
int iLogPixelsY;

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
// store.c
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
    extern void ClearDebugHistory(void);

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

// Create Obj flags

#define AS_TEMPORARY        0x00000001
#define FROM_STORAGE        0x00000002
#define FROM_DATA           0x00000004
#define FROM_CLASSID        0x00000008

extern POBJECT CreateObj(int x, int y, int w, int h,
                  LPSTORAGE pStorage, LPDATAOBJECT pDataObj,
                  REFCLSID pClsid,
                  DWORD dwFlags);
extern void DeleteObj(POBJECT pObj);
extern POBJECT CopyObj(POBJECT pObj);
extern void RenderObj(HDC hDC, POBJECT pObj);
extern void InsertObjCmd(HWND hWnd);
extern POBJECT HitTestObj(int x, int y);
extern UINT SizeBorderHitTestObj(int x, int y);
extern void SelectObj(POBJECT pObj, BOOL bDesel);
extern void BringObjToTop(POBJECT pObj);
extern void AppendObj(POBJECT pObj);
extern void UnlinkObj(POBJECT pObj);
extern BOOL ActivateObj(POBJECT pObj);
extern BOOL GetObjData(POBJECT pObj, LPFORMATETC pFmt, 
                       LPSTGMEDIUM pMed, BOOL bHere);

//
// memory allocation macros
//

#define ALLOCATE(s) (_fcalloc((s),1))
#define FREE(p)     (_ffree(p))

//
// iface.c
//

extern BOOL InitInterfaces(void);
extern IOleClientSiteVtbl MyClientSiteVtbl;
extern IAdviseSinkVtbl MyAdviseSinkVtbl;
extern IDataObjectVtbl MyDataObjectVtbl;
extern IDropTargetVtbl MyDropTargetVtbl;

//
// error.c
//

extern BOOL MyTestOleResult(HRESULT hResult);

//
// dataform.c
//

extern UINT gcfEmbeddedObject;
extern UINT gcfObjectDescriptor;
extern FORMATETC gSingleObjGetFmts[];
extern int giSingleObjGetFmts;

extern void InitDataFormats(void);
extern BOOL IsValidDataFormat(POBJECT pObj, LPFORMATETC pFmt);

//
// util.c
//

extern void GetObjectDescriptorPointAndSize(LPDATAOBJECT pData, 
            POINT FAR *ppt, int FAR *lpw, int FAR *lph);
extern void DrawBand(HWND hWnd, LPRECT prc);
