//=--------------------------------------------------------------------------=
// Misc.H
//=--------------------------------------------------------------------------=
// various utility routines our base class will find useful.
//
// marcwan, 1.96
//
#ifndef _MISC_H_

#include "CirclCtl.H"


//=--------------------------------------------------------------------------=
//  various macros
//=--------------------------------------------------------------------------=
#define RELNULL(ptr) \
if (NULL != (ptr)) { (ptr)->Release(); (ptr) = NULL; }


#define FREENULL(ptr) \
if (NULL != (ptr)) { HeapFree(g_hHeap,0,(ptr)); (ptr) = NULL; }

#define FAILGO(val) \
if (FAILED(val)) goto OnError;

//=--------------------------------------------------------------------------=
// function prototypes
//=--------------------------------------------------------------------------=

// string helpers
//
BOOL  MiscCopyHeapStr(LPSTR *, LPSTR);
BOOL  MiscGetWideHeapStr(LPWSTR *, LPSTR);
BOOL  MiscGetAnsiHeapStr(LPSTR *, LPWSTR);
BOOL  MiscReplaceHeapString(LPSTR *, LPSTR, int);

// persistence helpers
//
HRESULT MiscLoadProperty(IStream *, LPBYTE, int iSize, VARTYPE);
HRESULT MiscSaveProperty(IStream *, LPBYTE, int iSize, VARTYPE);

// error helpers
//
void    Error(HWND, WORD, WORD, DWORD);
void    ErrorReplace(HWND, WORD, WORD, LPSTR, DWORD);
WORD    ErrorFromHresult(HRESULT, WORD);

// really miscellaneous thingies!
//
int   ResourceMessageBox(HWND, WORD, WORD, UINT);
int   ResourceMessageBoxReplace(HWND, WORD, WORD, LPSTR, UINT);

#define _MISC_H_
#endif // _MISC_H_

