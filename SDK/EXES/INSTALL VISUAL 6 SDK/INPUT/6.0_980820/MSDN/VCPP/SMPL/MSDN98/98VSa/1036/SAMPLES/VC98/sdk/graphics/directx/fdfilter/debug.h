/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:		debug.h
 *  Content:	debug header
 *
 ***************************************************************************/
#ifndef __DEBUG_INCLUDED__
#define __DEBUG_INCLUDED__
#ifdef __cplusplus
extern "C"
{
#endif

LPSTR TranslateDSError( HRESULT );

//
//
//
//
#if defined(DEBUG) || defined(_DEBUG)
    #define DEBUG_SECTION       "Debug"     // section name for 
    #define DEBUG_MODULE_NAME   "FDFILTER"    // key name and prefix for output
    #define DEBUG_MAX_LINE_LEN  255         // max line length (bytes!)
#endif


//
//  based code makes since only in win 16 (to try and keep stuff out of
//  [fixed] data segments, etc)...
//
#ifndef BCODE
#ifdef _WIN32
    #define BCODE
#else
    #define BCODE           _based(_segname("_CODE"))
#endif
#endif




//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

#if defined(DEBUG) || defined(_DEBUG)
    BOOL WINAPI DbgEnable(BOOL fEnable);
    UINT WINAPI DbgGetLevel(void);
    UINT WINAPI DbgSetLevel(UINT uLevel);
    UINT WINAPI DbgInitialize(BOOL fEnable);
    void WINAPI _Assert( char * szFile, int iLine );
    void WINAPI DbgDumpWFX( int, PWAVEFORMATEX );

    void FAR CDECL dprintf(UINT uDbgLevel, LPSTR szFmt, ...);

    #define D(x)        {x;}
    #define DPF         dprintf
    #define DPI(sz)     {static char BCODE ach[] = sz; OutputDebugStr(ach);}
    #define DPWFX	DbgDumpWFX
    #define ASSERT(x)   if( !(x) )  _Assert( __FILE__, __LINE__)
#else
    #define DbgEnable(x)        FALSE
    #define DbgGetLevel()       0
    #define DbgSetLevel(x)      0
    #define DbgInitialize(x)    0
    #define DbgDumpWFX(x,y)	0

    #ifdef _MSC_VER
    #pragma warning(disable:4002)
    #endif

    #define D(x)
    #define DPF()
    #define DPI(sz)
    #define DPWFX()
    #define ASSERT(x)
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define ASSERT_HWND( h )    ASSERT( IsWindow((h)) )
#else
#define ASSERT_HWND( h )    ASSERT( NULL != (h) )
#endif

#ifdef __cplusplus
}
#endif
#endif  // __DEBUG_INCLUDED__

