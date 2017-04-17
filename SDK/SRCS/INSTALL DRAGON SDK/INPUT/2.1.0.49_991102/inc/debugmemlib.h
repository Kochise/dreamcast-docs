/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    DebugMemLib.h

Abstract:

    Header file for the Memory Tracking library

-------------------------------------------------------------------*/

// ++++ Defines +++++++++++++++++++++++++++++++++++++++++++++++

// Comment the following line out if you want to disable memory tracking.
// You may want to move this define into your project settings.
//#define DEBUGMEM

#ifdef DEBUGMEM

#ifndef UNDER_CE
#pragma warning(disable:4291)
#endif

// These defines remap the standard allocation/deallocation functions
// to the special ones in the Memory Tracking library
#define malloc(a)                DebugMalloc(a, __FILE__, __LINE__)
#define realloc(a, b)            DebugRealloc(a, b, __FILE__, __LINE__)
#define free(a)                  DebugFree(a, __FILE__, __LINE__)
#define LocalAlloc(a, b)         DebugLocalAlloc(a, b, __FILE__, __LINE__)
#define LocalReAlloc(a, b,c )    DebugLocalReAlloc(a, b, c, __FILE__, __LINE__)
#define LocalFree(a)             DebugLocalFree(a, __FILE__, __LINE__)
#define LocalSize(a)             DebugLocalSize(a, __FILE__, __LINE__)
#define HeapAlloc(a, b, c)       DebugHeapAlloc(a, b, c, __FILE__, __LINE__)
#define HeapReAlloc(a, b, c, d)  DebugHeapReAlloc(a, b, c, d, __FILE__, __LINE__)
#define HeapFree(a, b, c)        DebugHeapFree(a, b, c, __FILE__, __LINE__)
#define HeapSize(a, b, c)        DebugHeapSize(a, b, c, __FILE__, __LINE__)
#define VirtualAlloc(a, b, c, d) DebugVirtualAlloc(a, b, c, d, __FILE__, __LINE__)
#define VirtualFree(a, b, c)     DebugVirtualFree(a, b, c, __FILE__, __LINE__)

// ++++ Functions +++++++++++++++++++++++++++++++++++++++++++++

// This function only has to be called if the app wants non-standard behaviour
#ifdef __cplusplus
extern "C" {
#endif

void SetDebugMemFlags(BOOL fOutputWarnings, BOOL fBreakOnWarning, 
                                 BOOL fBreakOnError, BOOL fExtensiveChecking);

void DebugExit();

// ++++ Internal Functions ++++++++++++++++++++++++++++++++++++

// The following functions are internal to the Memory Tracking Library, and 
// should not be called by the application using the library.  They are included
// here since the compiler needs their declarations for the macro remapping to work.
void  *DebugMalloc(int nSize, char *pszFile, int nLine, BOOL bBracket = FALSE);
void  *DebugRealloc(void *pvMem, int nSize, char *szFile, int nLine);
void  DebugFree(void *pvMem, char *szFile, int nLine, BOOL bBracket = FALSE);

void  *DebugLocalAlloc(DWORD dwFlags, int nSize, char *pszFile, int nLine);
void  *DebugLocalReAlloc(HLOCAL hMem, UINT uBytes, UINT uFlags, char *szFile, int nLine);
void  DebugLocalFree(LPVOID lpMem, char *szFile, int nLine);
DWORD DebugLocalSize(LPVOID lpMem, char *szFile, int nLine);

void  *DebugHeapAlloc(HANDLE hHeap, DWORD dwFlags, DWORD dwBytes, char *szFile, int nLine);
void  *DebugHeapReAlloc(HANDLE hHeap, DWORD dwFlags, LPVOID pvMem, DWORD dwBytes, char *szFile, int nLine);
BOOL  DebugHeapFree(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, char *szFile, int nLine);
DWORD DebugHeapSize(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, char *szFile, int nLine);

void  *DebugVirtualAlloc(LPVOID pvAddress, DWORD dwBytes, DWORD dwAllocationType, DWORD dwProtect, char *szFile, int nLine);
BOOL  DebugVirtualFree(LPVOID pvAddress, DWORD dwBytes, DWORD dwFreeType, char *szFile, int nLine);

#ifdef __cplusplus
}
#endif // __cplusplus

void __cdecl operator delete[](void *pUserData);
void* __cdecl operator new[](size_t nSize, char * lpszFileName, int nLine);
void* __cdecl operator new(size_t nSize, char * lpszFileName, int nLine);
#define DEBUG_NEW new(__FILE__, __LINE__)
#define new DEBUG_NEW

#endif //DEBUGMEM