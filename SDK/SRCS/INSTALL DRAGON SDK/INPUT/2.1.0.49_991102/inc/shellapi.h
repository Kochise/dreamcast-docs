/*****************************************************************************\
*                                                                             *
* shellapi.h -  SHELL.DLL functions, types, and definitions                   *
*                                                                             *
* Copyright (c) 1992-1998, Microsoft Corp.  All rights reserved               *
*                                                                             *
\*****************************************************************************/

#ifndef _INC_SHELLAPI
#define _INC_SHELLAPI


//
// Define API decoration for direct importing of DLL references.
//
#ifndef WINSHELLAPI
#if !defined(_SHELL32_)
#define WINSHELLAPI DECLSPEC_IMPORT
#else
#define WINSHELLAPI
#endif
#endif // WINSHELLAPI


#include <pshpack1.h>

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */


// @CESYSGEN IF GWES_ICONCMN

#define EIRESID(x) (-1 * (int)(x))

#ifndef ExtractIconExA
HICON WINAPI ExtractIconExA(LPCSTR lpszFile, int nIconIndex, HICON FAR *phiconLarge, HICON FAR *phiconSmall, UINT nIcons);
#endif

#ifndef ExtractIconExW
HICON WINAPI ExtractIconExW(LPCWSTR lpszFile, int nIconIndex, HICON FAR *phiconLarge, HICON FAR *phiconSmall, UINT nIcons);
#endif

#ifdef UNICODE
#define ExtractIconEx  ExtractIconExW
#else
#define ExtractIconEx  ExtractIconExA
#endif // !UNICODE

// @CESYSGEN ENDIF


////
//// Shell File Operations
////

#ifndef FO_MOVE //these need to be kept in sync with the ones in shlobj.h

#define FO_MOVE           0x0001
#define FO_COPY           0x0002
#define FO_DELETE         0x0003
#define FO_RENAME         0x0004

#define FOF_MULTIDESTFILES         0x0001
#define FOF_CONFIRMMOUSE           0x0002
#define FOF_SILENT                 0x0004  // don't create progress/report
#define FOF_RENAMEONCOLLISION      0x0008
#define FOF_NOCONFIRMATION         0x0010  // Don't prompt the user.
#define FOF_WANTMAPPINGHANDLE      0x0020  // Fill in SHFILEOPSTRUCT.hNameMappings
                                      // Must be freed using SHFreeNameMappings
#define FOF_ALLOWUNDO              0x0040
#define FOF_FILESONLY              0x0080  // on *.*, do only files
#define FOF_SIMPLEPROGRESS         0x0100  // means don't show names of files
#define FOF_NOCONFIRMMKDIR         0x0200  // don't confirm making any needed dirs

typedef WORD FILEOP_FLAGS;

#define PO_DELETE       0x0013  // printer is being deleted
#define PO_RENAME       0x0014  // printer is being renamed
#define PO_PORTCHANGE   0x0020  // port this printer connected to is being changed
                                // if this id is set, the strings received by
                                // the copyhook are a doubly-null terminated
                                // list of strings.  The first is the printer
                                // name and the second is the printer port.
#define PO_REN_PORT     0x0034  // PO_RENAME and PO_PORTCHANGE at same time.

// no POF_ flags currently defined

typedef WORD PRINTEROP_FLAGS;

#endif // FO_MOVE

// implicit parameters are:
//      if pFrom or pTo are unqualified names the current directories are
//      taken from the global current drive/directory settings managed
//      by Get/SetCurrentDrive/Directory
//
//      the global confirmation settings

#ifndef UNICODE_ONLY
typedef struct _SHFILEOPSTRUCTA
{
        HWND            hwnd;
        UINT            wFunc;
        LPCSTR          pFrom;
        LPCSTR          pTo;
        FILEOP_FLAGS    fFlags;
        BOOL            fAnyOperationsAborted;
        LPVOID          hNameMappings;
        LPCSTR           lpszProgressTitle; // only used if FOF_SIMPLEPROGRESS
} SHFILEOPSTRUCTA, FAR *LPSHFILEOPSTRUCTA;
#endif //!UNICODE_ONLY
#ifndef ANSI_ONLY
typedef struct _SHFILEOPSTRUCTW
{
        HWND            hwnd;
        UINT            wFunc;
        LPCWSTR         pFrom;
        LPCWSTR         pTo;
        FILEOP_FLAGS    fFlags;
        BOOL            fAnyOperationsAborted;
        LPVOID          hNameMappings;
        LPCWSTR          lpszProgressTitle; // only used if FOF_SIMPLEPROGRESS
} SHFILEOPSTRUCTW, FAR *LPSHFILEOPSTRUCTW;
#endif //!ANSI_ONLY
#ifdef UNICODE
typedef SHFILEOPSTRUCTW SHFILEOPSTRUCT;
typedef LPSHFILEOPSTRUCTW LPSHFILEOPSTRUCT;
#else
typedef SHFILEOPSTRUCTA SHFILEOPSTRUCT;
typedef LPSHFILEOPSTRUCTA LPSHFILEOPSTRUCT;
#endif // UNICODE

#ifndef UNICODE_ONLY
WINSHELLAPI int WINAPI SHFileOperationA(LPSHFILEOPSTRUCTA lpFileOp);
#endif //!UNICODE_ONLY
#ifndef ANSI_ONLY
WINSHELLAPI int WINAPI SHFileOperationW(LPSHFILEOPSTRUCTW lpFileOp);
#endif //!ANSI_ONLY
#ifdef UNICODE
#define SHFileOperation  SHFileOperationW
#else
#define SHFileOperation  SHFileOperationA
#endif // !UNICODE


////
////  Begin ShellExecuteEx and family
////
// @CESYSGEN IF COREDLL_SHEXEC
// @CESYSGEN ENDIF
////
////  End ShellExecuteEx and family
////


// These APIs are sysgened out if the system is to run Shell-less
// @CESYSGEN IF COREDLL_SHELLAPIS
// @CESYSGEN ENDIF


////
//// Begin SHGetFileInfo
////
// @CESYSGEN IF COREDLL_FILEINFO
// @CESYSGEN ENDIF
////
//// End SHGetFileInfo
////


//
// SHAddToRecentDocs
//
// @CESYSGEN IF COREDLL_SHELLAPIS
// @CESYSGEN ENDIF

// @CESYSGEN IF COREDLL_SHORTCUT
// @CESYSGEN ENDIF

// @CESYSGEN IF COREDLL_SHMISC
// @CESYSGEN ENDIF

#ifndef UNDER_NT
#ifdef WINCEOEM
#ifdef WINCEMACRO
#include <mshellap.h>
#endif
#endif
#endif


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#include <poppack.h>

#endif  /* _INC_SHELLAPI */
