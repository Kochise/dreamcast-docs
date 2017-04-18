/*
 * COSMO.H
 *
 * Definitions and function prototypes for the OLE Cosmo Server.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */

#include "polyline.h"

//Resource identifiers.
#define IDR_MENU            1
#define IDR_ACCELERATORS    1
#define IDD_ABOUT           1

//POLYLINE Window ID
#define ID_POLYLINE         10


//Menu command identifiers.
#define IDM_FILENEW         100
#define IDM_FILEOPEN        101
#define IDM_FILESAVE        102
#define IDM_FILESAVEAS      103
#define IDM_FILEIMPORT      104
#define IDM_FILEEXIT        110

#define IDM_EDITUNDO        200
#define IDM_EDITCUT         201
#define IDM_EDITCOPY        202
#define IDM_EDITPASTE       203

#define IDM_HELPABOUT       300


//File-related string lengths.
#define CCHPATHMAX          256
#define CCHFILENAMEMAX      15



/*
 * CSTRINGS is number of strings to load from the stringtable.
 * CCHSTRINGMAX is the maximum length that any string is allowed.
 *
 * What will happen is that CSTRINGS*CCHSTRINGMAX is allocated to begin
 * with and the stringtable is loaded into that space, Only using what's
 * required for each string.  After that, the space is reallocated to
 * be as small as possible.
 */

#define CSTRINGS            30
#define CCHSTRINGMAX        80



//String ID values.  Keep in SEQUENTIAL order and use 0-n
#define IDS_CAPTION         0
#define IDS_CLASSCOSMO      1
#define IDS_CLASSPOLYLINE   2
#define IDS_FILEDIRTY       3
#define IDS_DEFEXT          4
#define IDS_FILEOPENFILTER  5
#define IDS_FILEOPEN        6
#define IDS_FILESAVEAS      7
#define IDS_FILEIMPORT      8
#define IDS_FULLNAME        9
#define IDS_FIGURE          10
#define IDS_DOTEXT          11
#define IDS_MODULE          12
#define IDS_UNTITLED        13
#define IDS_EMPTY           14

#define IDS_VERBEDIT        15
#define IDS_UPDATE          16
#define IDS_SAVE            17
#define IDS_SAVEAS          18
#define IDS_SAVECOPYAS      19
#define IDS_EXIT            20
#define IDS_EXITANDRETURN   21
#define IDS_EMBEDDING       22
#define IDS_NATIVE          23
#define IDS_DATAFORMATS     24
#define IDS_STDFILEEDITING  25
#define IDS_OWNERLINK       26
#define IDS_OBJECTLINK      27

#define IDS_CLOSEALERT1     28
#define IDS_CLOSEALERT2     29




/*
 * Structure holding the "global" variables.  Creating a structure with
 * has several advantages over separately declaring each field as a
 * global:
 *  1.  Keep source files clean.
 *  2.  Eliminates need for many "extern" declarations.
 *  3.  A single pointer to this structure can be passed throughout
 *      the application, hiding the fact that it's global.
 *  4.  Allows the variables to be allocated dynamically or from
 *      different memory than the application's DS.
 *  5.  Any reference to these variables will have a pointer or
 *      structure dereference, which points to where the variable
 *      actually is defined.  Separate globals are not distinguishable
 *      from locals, making code harder to read.
 *
 * Note that fNoDirty is used from OLEOBJ.C in the ObjShow method
 * to prevent setting fDirty when the window is sized from ObjShow.
 */

typedef struct
    {
    HWND        hWnd;               //Top-level application window.
    HWND        hWndPolyline;       //Editor window.
    HINSTANCE   hInst;              //Application instance handle.
    LPSTR       pszCmdLine;         //Command line passed to WinMain.
    UINT        nCmdShow;           //Initial ShowWindow command.
    HLOCAL      hStringMem;         //Stringtable memory.
    UINT        cfCosmo;            //Private clipboard format.
    BOOL        fDirty;             //Is file dirty?
    BOOL        fNoDirty;           //If TRUE, don't touch dirty flag.
    BOOL        fOpenFile;          //FALSE if File/New used until saved.
    char        szFile[CCHPATHMAX]; //Filename for Save command.

    BOOL        fOLE;               //Indicates if we are linked/embedded.
    } GLOBALS;

typedef GLOBALS FAR * LPGLOBALS;

//External:
extern char NEAR *rgpsz[CSTRINGS];
extern LPGLOBALS pGlob;


//Versioning.
#define VERSIONMAJOR        1
#define VERSIONMINOR        0







/*
 * Function prototypes, organized by source file.  Any small definition
 * required by only one source file is also included here under the
 * same heading.
 */

//CLIP.C
BOOL      WINAPI FEditCut(LPGLOBALS);
BOOL      WINAPI FEditCopy(LPGLOBALS, BOOL);
BOOL      WINAPI FEditPaste(LPGLOBALS);
HGLOBAL   WINAPI HGetPolyline(HWND);
HGLOBAL   WINAPI HGetMetafilePict(HWND);
HGLOBAL   WINAPI HGetBitmap(HWND);


//COMMDLG.C
BOOL     WINAPI FSaveOpenDialog(HWND, HINSTANCE, LPSTR, LPSTR, LPSTR, LPSTR, BOOL);

//EXIT.C
BOOL     WINAPI FApplicationExit(LPGLOBALS);

//FILE.C
BOOL     WINAPI FDirtySet(BOOL);
BOOL     WINAPI FCleanVerify(LPGLOBALS);
BOOL     WINAPI FFileNew(LPGLOBALS);
BOOL     WINAPI FFileOpen(LPGLOBALS, BOOL);
BOOL     WINAPI FFileSave(LPGLOBALS);
BOOL     WINAPI FFileSaveAs(LPGLOBALS);
BOOL     WINAPI FFileExit(LPGLOBALS);

//FILEIO.C
BOOL     WINAPI FCosFileRead(LPGLOBALS, LPSTR, LPPOLYLINE);
BOOL     WINAPI FCosFileWrite(LPGLOBALS, LPSTR, LPPOLYLINE);


//INIT.C
BOOL     WINAPI FApplicationInit(LPGLOBALS, HINSTANCE);
BOOL     WINAPI FClassRegister(LPGLOBALS, HINSTANCE);
BOOL     WINAPI FFileInit(LPGLOBALS);
HLOCAL   WINAPI HLoadAppStrings(LPGLOBALS);
HLOCAL   WINAPI HListParse(LPSTR);
LPSTR    PASCAL PszWhiteSpaceScan(LPSTR, BOOL);

//MISC.C
void     WINAPI WindowTitleSet(HWND, LPSTR);
void     WINAPI RectConvertToHiMetric(HWND, LPRECT);
void     WINAPI RectConvertToDevice(HWND, LPRECT);

//COSMO.C
LRESULT  WINAPI CosmoWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL     WINAPI AboutProc(HWND, UINT, WPARAM, LPARAM);
