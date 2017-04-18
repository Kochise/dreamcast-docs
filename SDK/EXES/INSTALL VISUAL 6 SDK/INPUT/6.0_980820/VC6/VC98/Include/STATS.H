// --stats.h--------------------------------------------------------------------
//
//  This header file defines the C version of the stats
//  library.
// 
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef __stats_h
#define __stats_h

#ifdef __cplusplus
extern "C" {
#endif 

#include <windows.h>
#include <mapix.h>
#include <stattype.h>

typedef HANDLE HFLDMTRC;
typedef HANDLE HJSWINDOW;

// Folder Metrics API
// ------------------------
HRESULT HrOpenFolderMetrics(
    IN LPMAPIFOLDER lpFolder,
    OUT HFLDMTRC *phFolderMetric);

HRESULT HrGetFolderMetrics(
    IN HFLDMTRC hFolderMetric,
    IN FILETIME *pftNow,
    IN DWORD fMetric,
    OUT DWORD *pcMessages,
    OUT FILETIME *pftLongestWait,
    OUT FILETIME *pftTotalWait);

VOID CloseFolderMetrics(
    IN HFLDMTRC hFolderMetric);


// Jump Slide Window API
// ---------------------

HRESULT HrJSOpen(
    IN JSWINDOWTYPE enType,
    IN FILETIME *pftNow,
    IN FILETIME *pftResolution,
    IN DWORD dwWindowDuration,
    OUT HJSWINDOW *phJSWindow);

HRESULT HrJSCollectDataPoint(
    IN HJSWINDOW hJSWindow,
    IN FILETIME *pftNow,
    IN DWORD dwValue);

HRESULT HrJSGetValue(
    IN HJSWINDOW hJSWindow,
    IN FILETIME *pftNow,
    OUT DWORD *pdwWindowValue,
    OUT DWORD *pdwFractionCompleteNum,
    OUT DWORD *pdwFractionCompleteDen);

VOID JSClose(
    IN HJSWINDOW hJSWindow);

HRESULT HrFileTimeToSeconds(
    IN FILETIME *pft,
    OUT DWORD *pdwSec);


// Convert between __int64 and FILETIME
// ------------------------------------

#define INT64_FROM_FILETIME(li) (*((__int64 *)&(li)))
#define FILETIME_FROM_INT64(li) (*((FILETIME *)&(li)))


#ifdef __cplusplus
}
#endif 

#endif


