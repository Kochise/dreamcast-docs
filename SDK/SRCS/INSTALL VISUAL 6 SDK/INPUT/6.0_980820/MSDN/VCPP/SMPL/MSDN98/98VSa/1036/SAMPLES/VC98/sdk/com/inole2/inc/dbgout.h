/*
 * DBGOUT.H
 *
 * Useful debugging output macros that compile to nothing and
 * eliminate ugly #ifdef DEBUGs from source code.  Note that
 * string literals do not need TEXT() around them as this file
 * includes them.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  INTERNET>kraigb@microsoft.com
 */

#ifndef _DBGOUT_H
#define _DBGOUT_H

#ifdef DEBUG

//Basic debug macros
#define D(x)        {x;}

#define ODS(x)  \
    {\
    TCHAR        szDebug[128];\
    OutputDebugString(TEXT(x));\
    wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
    OutputDebugString(szDebug);\
    }

#define ODSsz(f, s) \
    {\
    TCHAR       szDebug[128];\
    wsprintf(szDebug, TEXT(f), (LPTSTR)s);\
    OutputDebugString(szDebug);\
    wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
    OutputDebugString(szDebug);\
    }


#define ODSu(f, u)  \
    {\
    TCHAR       szDebug[128];\
    wsprintf(szDebug, TEXT(f), (UINT)u);\
    OutputDebugString(szDebug);\
    wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
    OutputDebugString(szDebug);\
    }


#define ODSlu(f, lu) \
    {\
    TCHAR       szDebug[128];\
    wsprintf(szDebug, TEXT(f), (DWORD)lu);\
    OutputDebugString(szDebug);\
    wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
    OutputDebugString(szDebug);\
    }

#define ODSlulu(f, lu1, lu2) \
    {\
    TCHAR       szDebug[128];\
    wsprintf(szDebug, TEXT(f), (DWORD)lu1, (DWORD)lu1);\
    OutputDebugString(szDebug);\
    wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
    OutputDebugString(szDebug);\
    }

#define ODSszu(f, s, u)     \
    {\
    TCHAR       szDebug[128];\
    wsprintf(szDebug, TEXT(f), (LPTSTR)s, (UINT)u);\
    OutputDebugString(szDebug);\
    wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
    OutputDebugString(szDebug);\
    }


#define ODSszlu(f, s, lu)   \
    {\
    TCHAR       szDebug[128];\
    wsprintf(szDebug, TEXT(f), (LPTSTR)s, (DWORD)lu);\
    OutputDebugString(szDebug);\
    wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
    OutputDebugString(szDebug);\
    }


#define ASSERT(condition) \
    {\
    if (!(condition))\
        ODS("Assertion Failure");\
    }

#else   //NO DEBUG

#define D(x)
#define ODS(x)

#define ODSsz(f, s)
#define ODSu(f, u)
#define ODSlu(f, lu)
#define ODSszu(f, s, u)
#define ODSszlu(f, s, lu)
#define ASSERT(c)

#endif //DEBUG

#endif //_DBGOUT_H
