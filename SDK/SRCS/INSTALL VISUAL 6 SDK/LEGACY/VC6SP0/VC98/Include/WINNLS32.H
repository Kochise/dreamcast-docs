/*++ BUILD Version: 0003    // Increment this if a change has global effects

Copyright (c) 1985-97, Microsoft Corporation

Module Name:

    winnls32.h

Abstract:

    Procedure declarations, constant definitions and macros for the
    Windows NT 3.x compatible FarEast IMM component.

--*/

#ifndef _WINNLS32_
#define _WINNLS32_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _tagDATETIME {
    WORD    year;
    WORD    month;
    WORD    day;
    WORD    hour;
    WORD    min;
    WORD    sec;
} DATETIME;

typedef struct _tagIMEPROA {
    HWND        hWnd;
    DATETIME    InstDate;
    UINT        wVersion;
    BYTE        szDescription[50];
    BYTE        szName[80];
    BYTE        szOptions[30];
} IMEPROA,*PIMEPROA,NEAR *NPIMEPROA,FAR *LPIMEPROA;
typedef struct _tagIMEPROW {
    HWND        hWnd;
    DATETIME    InstDate;
    UINT        wVersion;
    WCHAR       szDescription[50];
    WCHAR       szName[80];
    WCHAR       szOptions[30];
} IMEPROW,*PIMEPROW,NEAR *NPIMEPROW,FAR *LPIMEPROW;
#ifdef UNICODE
typedef IMEPROW IMEPRO;
typedef PIMEPROW PIMEPRO;
typedef NPIMEPROW NPIMEPRO;
typedef LPIMEPROW LPIMEPRO;
#else
typedef IMEPROA IMEPRO;
typedef PIMEPROA PIMEPRO;
typedef NPIMEPROA NPIMEPRO;
typedef LPIMEPROA LPIMEPRO;
#endif // UNICODE

BOOL  WINAPI IMPGetIMEA(HWND, LPIMEPROA);
BOOL  WINAPI IMPGetIMEW(HWND, LPIMEPROW);
#ifdef UNICODE
#define IMPGetIME  IMPGetIMEW
#else
#define IMPGetIME  IMPGetIMEA
#endif // !UNICODE
BOOL  WINAPI IMPQueryIMEA(LPIMEPROA);
BOOL  WINAPI IMPQueryIMEW(LPIMEPROW);
#ifdef UNICODE
#define IMPQueryIME  IMPQueryIMEW
#else
#define IMPQueryIME  IMPQueryIMEA
#endif // !UNICODE
BOOL  WINAPI IMPSetIMEA(HWND, LPIMEPROA);
BOOL  WINAPI IMPSetIMEW(HWND, LPIMEPROW);
#ifdef UNICODE
#define IMPSetIME  IMPSetIMEW
#else
#define IMPSetIME  IMPSetIMEA
#endif // !UNICODE

UINT  WINAPI WINNLSGetIMEHotkey(HWND);
BOOL  WINAPI WINNLSEnableIME(HWND, BOOL);
BOOL  WINAPI WINNLSGetEnableStatus(HWND);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif // _WINNLS32_

