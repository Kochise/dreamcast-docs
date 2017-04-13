/*
 * ANSI.CPP
 *
 * Utility functions for dealing with OLE APIs that need
 * Unicode strings.  These are only defined when UNICODE
 * is not defined, otherwise INOLE.H simply redefines them
 * as macro pass-throughs to the original OLE functions.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define NOMACROREDIRECT
#include "inoledll.h"


#ifdef WIN32ANSI

/*
 * ConvertStringAlloc
 *
 * Purpose:
 *  Allocates memory using the task allocator.  Used internally
 *  in this file.
 */

HRESULT ConvertStringAlloc(ULONG ulSize, void **ppv)
    {
    HRESULT     hr;
    IMalloc    *pIMalloc;

    if (NULL==ppv)
        return ResultFromScode(E_INVALIDARG);

    hr=CoGetMalloc(MEMCTX_TASK, &pIMalloc);

    if (FAILED(hr))
        return hr;

    *ppv=pIMalloc->Alloc(ulSize);
    pIMalloc->Release();

    return (NULL==*ppv) ? ResultFromScode(E_OUTOFMEMORY) : NOERROR;
    }



/*
 * INOLE_ConvertStringToANSI
 *
 * Purpose:
 *  Converts the string in pszW to ANSI, allocating the
 *  output buffer pointed to by *ppszA on output.  The
 *  string is allocated with COM's task allocator.
 *
 */

STDAPI INOLE_ConvertStringToANSI(LPCWSTR pszW, LPSTR *ppszA)
    {
    ULONG   cch;
    HRESULT hr;

    //If input is NULL then just return the same
    if (NULL==pszW)
        {
        *ppszA=NULL;
        return NOERROR;
        }

    //This calculates the number of MBCS characters we'll need
    cch=1+WideCharToMultiByte(CP_ACP, 0, pszW, -1, NULL, 0, NULL, NULL);

    hr=ConvertStringAlloc(cch, (void **)ppszA);

    if (FAILED(hr))
        return hr;

    WideCharToMultiByte(CP_ACP, 0, pszW, -1, *ppszA, cch, NULL, NULL);
    return NOERROR;
    }




/*
 * INOLE_StringFromCLSID
 */

STDAPI INOLE_StringFromCLSID(REFCLSID clsID, LPSTR *ppszCLSID)
    {
    LPWSTR  psz;
    HRESULT hr;

    if (NULL==ppszCLSID)
        return ResultFromScode(E_INVALIDARG);

    hr=StringFromCLSID(clsID, &psz);

    if (FAILED(hr))
        return hr;

    hr=INOLE_ConvertStringToANSI(psz, ppszCLSID);
    CoTaskMemFree((void *)psz);
    return hr;
    }



/*
 * INOLE_StringFromGUID2
 */

STDAPI INOLE_StringFromGUID2(REFGUID guid, LPSTR pszGUID, int cch)
    {
    LPSTR   psz;
    HRESULT hr;

    if (NULL==pszGUID)
        return ResultFromScode(E_INVALIDARG);

    hr=INOLE_StringFromCLSID(guid, &psz);

    if (FAILED(hr))
        return hr;

    lstrcpyn(pszGUID, psz, cch);
    CoTaskMemFree((void *)psz);
    return hr;
    }





/*
 * INOLE_ProgIDFromCLSID
 */

STDAPI INOLE_ProgIDFromCLSID(REFCLSID clsID, LPSTR *ppszProgID)
    {
    LPWSTR  psz;
    HRESULT hr;

    if (NULL==ppszProgID)
		return ResultFromScode(E_INVALIDARG);

    hr=ProgIDFromCLSID(clsID, &psz);

    if (FAILED(hr))
        return hr;

    hr=INOLE_ConvertStringToANSI(psz, ppszProgID);
    CoTaskMemFree(psz);
    return hr;
    }




/*
 * INOLE_ReadFmtUserTypeStg
 * INOLE_WriteFmtUserTypeStg
 */

STDAPI INOLE_ReadFmtUserTypeStg(IStorage *pIStorage
    , CLIPFORMAT *pcf, LPSTR *ppszUserType)
    {
    HRESULT     hr;
    LPOLESTR    pszUserType;

    if (NULL==ppszUserType)
        return ResultFromScode(E_INVALIDARG);

    hr=ReadFmtUserTypeStg(pIStorage, pcf, &pszUserType);

    if (FAILED(hr))
        return hr;

    if (ppszUserType)
        {
        hr=INOLE_ConvertStringToANSI(pszUserType, ppszUserType);
        CoTaskMemFree(pszUserType);
        }

    return hr;
    }


STDAPI INOLE_WriteFmtUserTypeStg(IStorage *pIStorage, CLIPFORMAT cf
    , LPSTR pszUserType)
    {
    OLECHAR     szType[512];
    HRESULT     hr;

    if (NULL==pszUserType)
        return ResultFromScode(E_INVALIDARG);

    MultiByteToWideChar(CP_ACP, 0, pszUserType, -1, szType, 512);
    hr=WriteFmtUserTypeStg(pIStorage, cf, szType);

    return hr;
    }



/*
 * INOLE_StgIsStorageFile
 * INOLE_StgCreateDocfile
 * INOLE_StgOpenStorage
 */

STDAPI INOLE_StgIsStorageFile(LPCSTR pszName)
    {
    OLECHAR     szTemp[MAX_PATH];

    MultiByteToWideChar(CP_ACP, 0, pszName, -1
        , szTemp, MAX_PATH);
    return StgIsStorageFile(szTemp);
    }



STDAPI INOLE_StgCreateDocfile(LPCSTR pszNameA, DWORD grfMode
    , DWORD reserved, IStorage **ppIStorage)
    {
    OLECHAR     szTemp[MAX_PATH];
    LPOLESTR    pszName;

    *ppIStorage=NULL;

    if (NULL!=pszNameA)
        {
        MultiByteToWideChar(CP_ACP, 0, pszNameA, -1
            , szTemp, MAX_PATH);
        pszName=szTemp;
        }
	else
        pszName=NULL;

    return StgCreateDocfile(pszName, grfMode, reserved
        , ppIStorage);
    }



STDAPI INOLE_StgOpenStorage(LPCSTR pszNameA, IStorage *pStgPri
    , DWORD grfMode, SNB snbEx, DWORD reserved
    , IStorage * *ppIStorage)
    {
    OLECHAR   szTemp[MAX_PATH];
    LPOLESTR  pszName;

    *ppIStorage=NULL;

    if (NULL!=pszNameA)
        {
        MultiByteToWideChar(CP_ACP, 0, pszNameA, -1
            , szTemp, MAX_PATH);
        pszName= szTemp;
        }
	else
        pszName=NULL;

    return StgOpenStorage(pszName, pStgPri, grfMode, snbEx
        , reserved, ppIStorage);
    }




/*
 * INOLE_CreateFileMoniker
 * INOLE_CreateItemMoniker
 * INOLE_MkParseDisplayName
 */

STDAPI INOLE_CreateFileMoniker(LPCSTR pszPathNameA, LPMONIKER *ppmk)
    {
    OLECHAR     szTemp[MAX_PATH];

    if (NULL==ppmk)
        return ResultFromScode(E_INVALIDARG);

    *ppmk=NULL;

    MultiByteToWideChar(CP_ACP, 0, pszPathNameA, -1
        , szTemp, MAX_PATH);

    return CreateFileMoniker(szTemp, ppmk);
    }


STDAPI INOLE_CreateItemMoniker(LPCSTR pszDelimA, LPCSTR pszItemA
    , LPMONIKER *ppmk)
    {
    OLECHAR     szItem[MAX_PATH];   //Some assumptions about string length
    OLECHAR     szDelim[20];

    if (NULL==ppmk)
        return ResultFromScode(E_INVALIDARG);

    *ppmk=NULL;

    MultiByteToWideChar(CP_ACP, 0, pszItemA, -1
        , szItem, MAX_PATH);
    MultiByteToWideChar(CP_ACP, 0, pszDelimA, -1
        , szDelim, 20);

    return CreateItemMoniker(szDelim, szItem, ppmk);
    }


STDAPI INOLE_MkParseDisplayName(LPBC pbc, LPCSTR pszUserNameA
    , ULONG *pchEaten, LPMONIKER *ppmk)
    {
    OLECHAR     szTemp[512];    //Assumption on string length

    if (NULL==ppmk)
        return ResultFromScode(E_INVALIDARG);

    *ppmk=NULL;

    MultiByteToWideChar(CP_ACP, 0, pszUserNameA, -1
        , szTemp, 512);

    return MkParseDisplayName(pbc, szTemp, pchEaten, ppmk);
    }



/*
 * INOLE_OleCreateLinkToFile
 * INOLE_OleCreateFromFile
 */

STDAPI INOLE_OleCreateLinkToFile(LPCSTR lpszFileName, REFIID riid
    , DWORD renderopt, LPFORMATETC lpFormatEtc
    , LPOLECLIENTSITE pClientSite, LPSTORAGE pStg, LPVOID *ppvObj)
    {
    OLECHAR     szFile[512];    //Assumption on string length

    MultiByteToWideChar(CP_ACP, 0, lpszFileName, -1, szFile, 512);
    return OleCreateLinkToFile(szFile, riid, renderopt, lpFormatEtc
        , pClientSite, pStg, ppvObj);
    }



STDAPI INOLE_OleCreateFromFile(REFCLSID rclsid, LPCSTR lpszFileName
    , REFIID riid, DWORD renderopt, LPFORMATETC lpFormatEtc
    , LPOLECLIENTSITE pClientSite, LPSTORAGE pStg, LPVOID *ppvObj)
    {
    OLECHAR     szFile[512];    //Assumption on string length

    MultiByteToWideChar(CP_ACP, 0, lpszFileName, -1, szFile, 512);
    return OleCreateFromFile(rclsid, szFile, riid, renderopt, lpFormatEtc
        , pClientSite, pStg, ppvObj);
    }

#else

//Do-nothing functions so we can at least export them.

#ifndef WIN32
STDAPI INOLE_ConvertStringToANSI(LPCSTR a, LPSTR *b) {return NOERROR;}
#else
STDAPI INOLE_ConvertStringToANSI(LPCWSTR a, LPSTR *b) {return NOERROR;}
#endif
STDAPI INOLE_StringFromCLSID(REFCLSID a, LPSTR *b) {return NOERROR;}
STDAPI INOLE_StringFromGUID2(REFGUID a, LPSTR b, int c) {return NOERROR;}
STDAPI INOLE_ProgIDFromCLSID(REFCLSID a, LPSTR *b) {return NOERROR;}

STDAPI INOLE_ReadFmtUserTypeStg(IStorage *a, CLIPFORMAT *b, LPSTR *c) {return NOERROR;}
STDAPI INOLE_WriteFmtUserTypeStg(IStorage *a, CLIPFORMAT b, LPSTR c) {return NOERROR;}

STDAPI INOLE_StgIsStorageFile(LPCSTR a) {return NOERROR;}
STDAPI INOLE_StgCreateDocfile(LPCSTR a, DWORD b, DWORD c, IStorage ** d) {return NOERROR;}
STDAPI INOLE_StgOpenStorage(LPCSTR a, IStorage *b, DWORD c, SNB d
           , DWORD e, IStorage **f) {return NOERROR;}

STDAPI INOLE_CreateFileMoniker(LPCSTR, LPMONIKER *) {return NOERROR;}
STDAPI INOLE_CreateItemMoniker(LPCSTR, LPCSTR, LPMONIKER *) {return NOERROR;}
STDAPI INOLE_MkParseDisplayName(LPBC, LPCSTR, ULONG *, LPMONIKER *) {return NOERROR;}

STDAPI INOLE_OleCreateLinkToFile(LPCOLESTR, REFIID, DWORD, LPFORMATETC
    , LPOLECLIENTSITE, LPSTORAGE, LPVOID *) {return NOERROR;}

STDAPI INOLE_OleCreateFromFile(REFCLSID, LPCOLESTR, REFIID
    , DWORD, LPFORMATETC, LPOLECLIENTSITE, LPSTORAGE, LPVOID *) {return NOERROR;}


#endif
