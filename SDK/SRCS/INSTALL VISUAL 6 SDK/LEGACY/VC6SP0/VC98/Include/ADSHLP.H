//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1996
//
//  File:       oleds.h
//
//  Contents:   Public header file for all oleds client code
//
//----------------------------------------------------------------------------

#ifndef _ADSHLP_
#define _ADSHLP_



#ifdef __cplusplus
extern "C" {
#endif

HRESULT WINAPI
ADsGetObject(
    LPWSTR lpszPathName,
    REFIID riid,
    VOID * * ppObject
    );


HRESULT WINAPI
ADsBuildEnumerator(
    IADsContainer *pADsContainer,
    IEnumVARIANT   **ppEnumVariant
    );

HRESULT WINAPI
ADsFreeEnumerator(
    IEnumVARIANT *pEnumVariant
    );

HRESULT WINAPI
ADsEnumerateNext(
    IEnumVARIANT *pEnumVariant,
    ULONG         cElements,
    VARIANT FAR  *pvar,
    ULONG FAR    *pcElementsFetched
    );

HRESULT WINAPI
ADsBuildVarArrayStr(
    LPWSTR *lppPathNames,
    DWORD  dwPathNames,
    VARIANT * pVar
    );

HRESULT WINAPI
ADsBuildVarArrayInt(
    LPDWORD    lpdwObjectTypes,
    DWORD      dwObjectTypes,
    VARIANT * pVar
    );


HRESULT WINAPI
ADsOpenObject(
    LPWSTR lpszPathName,
    LPWSTR lpszUserName,
    LPWSTR lpszPassword,
    DWORD  dwReserved,
    REFIID riid,
    void FAR * FAR * ppObject
    );

//
// Helper functions for extended error support
//

HRESULT WINAPI
ADsGetLastError(
    OUT     LPDWORD lpError,
    OUT     LPWSTR  lpErrorBuf,
    IN      DWORD   dwErrorBufLen,
    OUT     LPWSTR  lpNameBuf,
    IN      DWORD   dwNameBufLen
    );

VOID WINAPI
ADsSetLastError(
    IN  DWORD   dwErr,
    IN  LPWSTR  pszError,
    IN  LPWSTR  pszProvider
    );


VOID WINAPI
ADsFreeAllErrorRecords(
    VOID);

LPVOID WINAPI
AllocADsMem(
    DWORD cb
);

BOOL WINAPI
FreeADsMem(
   LPVOID pMem
);

LPVOID WINAPI
ReallocADsMem(
   LPVOID pOldMem,
   DWORD cbOld,
   DWORD cbNew
);

LPWSTR WINAPI
AllocADsStr(
    LPWSTR pStr
);

BOOL WINAPI
FreeADsStr(
   LPWSTR pStr
);


BOOL WINAPI
ReallocADsStr(
   LPWSTR *ppStr,
   LPWSTR pStr
);


HRESULT WINAPI
ADsEncodeBinaryData (
   PBYTE   pbSrcData,
   DWORD   dwSrcLen,
   LPWSTR  * ppszDestData
   );


HRESULT WINAPI
PropVariantToAdsType(
    VARIANT * pVariant,
    DWORD dwNumVariant,
    PADSVALUE *ppAdsValues,
    PDWORD pdwNumValues
    );

HRESULT WINAPI
AdsTypeToPropVariant(
    PADSVALUE pAdsValues,
    DWORD dwNumValues,
    VARIANT * pVariant
    );

void WINAPI
AdsFreeAdsValues(
    PADSVALUE pAdsValues,
    DWORD dwNumValues
    );

#if DBG

extern LIST_ENTRY ADsMemList ;

extern CRITICAL_SECTION ADsMemCritSect ;

VOID WINAPI InitADsMem(
    VOID
    ) ;

VOID WINAPI AssertADsMemLeaks(
    VOID
    ) ;


VOID WINAPI
DumpMemoryTracker();


#else

#define InitADsMem()
#define AssertADsMemLeaks()

#define DumpMemoryTracker()



#endif


#ifdef __cplusplus
}
#endif

#endif // _ADSHLP_





