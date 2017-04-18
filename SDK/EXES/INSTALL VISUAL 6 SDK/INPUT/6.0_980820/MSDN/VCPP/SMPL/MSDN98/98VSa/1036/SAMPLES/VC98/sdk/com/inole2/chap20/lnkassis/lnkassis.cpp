/*
 * LNKASSIS.CPP
 * Links Assistant Chapter 20
 *
 * Implementation of the CLinks object with the IOleUILinkContainer
 * interface to assist handling the Links dialog for linking
 * containers.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "lnkassis.h"


/*
 * CLinks::CLinks
 * CLinks::~CLinks
 *
 * Parameters (Constructor):
 *  pfnDestroy      PFNDESTROYED to call when object is destroyed.
 */

CLinks::CLinks(PFNDESTROYED pfnDestroy)
    {
    m_cRef=0;
    m_pfnDestroy=pfnDestroy;
    return;
    }


CLinks::~CLinks(void)
    {
    return;
    }




/*
 * CLinks::QueryInterface
 * CLinks::AddRef
 * CLinks::Release
 *
 * Purpose:
 *  IUnknown members for CLinks object.
 */

STDMETHODIMP CLinks::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IOleUILinkContainer==riid)
        {
        *ppv=this;
        AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CLinks::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CLinks::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    if (NULL!=m_pfnDestroy)
        (*m_pfnDestroy)();

    delete this;
    return 0;
    }





/*
 * CLinks::GetNextLink
 *
 * Purpose:
 *  Function to fill out the IOleUILinkContainer interface.
 *  Does nothing.
 *
 * Parameters:
 *  dwLink          DWORD ignored.
 *
 * Return Value:
 *  DWORD           Alwaus 0L
 *
 */

STDMETHODIMP_(DWORD) CLinks::GetNextLink(DWORD dwLink)
    {
    return 0L;
    }





/*
 * CLinks::SetLinkUpdateOptions
 *
 * Purpose:
 *  Calls IOleLink::SetUpdateOptions for the object identified by
 *  dwLink.
 *
 * Parameters:
 *  dwLink          DWORD, an IOleLink pointer to the object
 *                  affected.
 *  dwOptions       DWORD containing the new options.
 *
 * Return Value:
 *  HRESULT         Return value of IOleLink::SetUpdateOptions.
 */

STDMETHODIMP CLinks::SetLinkUpdateOptions(DWORD dwLink
    , DWORD dwOptions)
    {
    LPOLELINK       pIOleLink=(LPOLELINK)dwLink;

    if (NULL==pIOleLink)
        return ResultFromScode(E_FAIL);

    return pIOleLink->SetUpdateOptions(dwOptions);
    }





/*
 * CLinks::GetLinkUpdateOptions
 *
 * Purpose:
 *  Call IOleLink::GetUpdateOptions for the object identified by
 *  dwLink.
 *
 * Parameters:
 *  dwLink          DWORD, an IOleLink pointer to the object
 *                  affected.
 *  pdwOptions      LPDWORD in which to store the options.
 *
 * Return Value:
 *  HRESULT         Return value of IOleLink::GetUpdateOptions
 */

STDMETHODIMP CLinks::GetLinkUpdateOptions(DWORD dwLink
    , LPDWORD pdwOptions)
    {
    LPOLELINK       pIOleLink=(LPOLELINK)dwLink;

    if (NULL==pIOleLink)
        return ResultFromScode(E_FAIL);

    return pIOleLink->GetUpdateOptions(pdwOptions);
    }





/*
 * CLinks::SetLinkSource
 *
 * Purpose:
 *  Changes the moniker to which an object is linked.
 *
 * Parameters:
 *  dwLink          DWORD, an IOleLink pointer to the object
 *                  affected.
 *  pszName         LPTSTR to the displayable name of the source.
 *  cchName         ULONG length of the file portaion of pszName
 *  pchEaten        ULONG * in which to return the number of
 *                  characters used in parsing pszDisplayName.
 *  fValidate       BOOL indicating if we're to validate that the
 *                  source exists first.
 *
 * Return Value:
 *  HRESULT         If successful, NOERROR indicates that the link
 *                  is available, S_FALSE to indicate it's not.
 *                  This information is later required in
 *                  GetLinkSource.  E_FAIL on failure.
 */

STDMETHODIMP CLinks::SetLinkSource(DWORD dwLink, LPTSTR pszName
    , ULONG cchName, ULONG *pchEaten, BOOL fValidate)
    {
    LPOLELINK       pIOleLink=(LPOLELINK)dwLink;
    HRESULT         hr;
    CLSID           clsID=CLSID_NULL;
    LPMONIKER       pmk=NULL;
    BOOL            fAvail=FALSE;

    if (fValidate)
        {
        //Check things out and get a moniker and CLSID.
        if (!ValidateLinkSource(pszName, pchEaten, &pmk, &clsID))
            return ResultFromScode(E_FAIL);

        //If we got a CLSID, then we found the source.
        if (CLSID_NULL!=clsID)
            fAvail=TRUE;
        }
    else
        {
        if (!CreateNewSourceMoniker(pszName, cchName, &pmk))
            return ResultFromScode(E_FAIL);
        }

    if (NULL==pIOleLink)
        {
        pmk->Release();
        return ResultFromScode(E_FAIL);
        }

    if (NULL!=pmk)
        {
        hr=pIOleLink->SetSourceMoniker(pmk, clsID);
        pmk->Release();
        }
    else
       #ifdef WIN32ANSI
        {
        OLECHAR     szTemp[512];

        MultiByteToWideChar(CP_ACP, 0, pszName, -1, szTemp, 512);
        hr=pIOleLink->SetSourceDisplayName(szTemp);
        }
       #else
        hr=pIOleLink->SetSourceDisplayName(pszName);
       #endif

    if (FAILED(hr))
        return hr;

    return fAvail ? NOERROR : ResultFromScode(S_FALSE);
    }






/*
 * CLinks::GetLinkSource
 *
 * Purpose:
 *  Retrieves various strings and values for this link source.
 *
 * Parameters:
 *  dwLink          DWORD, an IOleLink pointer to the object
 *                  affected.
 *  ppszName        LPTSTR * in which to return the new source
 *                  name
 *  pcchName        ULONG * in which to return the length of
 *                  pszName
 *  ppszFullLink    LPTSTR * in which to return the full name of
 *                  the class of linked object.
 *  ppszShortLink   LPTSTR * in which to return the short name of
 *                  the class of linked object.
 *  pfSourceAvail   BOOL * ignored.
 *  pfSelected      BOOL * ignored.
 *
 * Return Value:
 *  HRESULT         NOERROR on success, error code otherwise.
 */

STDMETHODIMP CLinks::GetLinkSource(DWORD dwLink
    , LPTSTR *ppszName, ULONG *pcchName
    , LPTSTR *ppszFullLink, LPTSTR *ppszShortLink
    , BOOL *pfSourceAvail, BOOL *pfSelected)
    {
    LPOLELINK       pIOleLink=(LPOLELINK)dwLink;
    HRESULT         hr;
    LPOLEOBJECT     pIOleObject=NULL;
    LPMONIKER       pmk=NULL;
    LPMONIKER       pmkFirst=NULL;
    LPBC            pbc=NULL;
   #ifdef WIN32ANSI
    OLECHAR        *pszOut;
    TCHAR          *pszTemp;
   #endif

    if (NULL==pIOleLink)
        return ResultFromScode(E_FAIL);

    *ppszName=NULL;
    *pcchName=0;
    *ppszFullLink=NULL;
    *ppszShortLink=NULL;

    hr=pIOleLink->GetSourceMoniker(&pmk);

    if (SUCCEEDED(hr))
        {
        hr=pIOleLink->QueryInterface(IID_IOleObject
            , (PPVOID)&pIOleObject);

        if (SUCCEEDED(hr))
            {
           #ifdef WIN32ANSI
            pszTemp=(TCHAR *)CoTaskMemAlloc(80);
            pIOleObject->GetUserType(USERCLASSTYPE_FULL
                , &pszOut);
            WideCharToMultiByte(CP_ACP, 0, pszOut, -1
                , pszTemp, 80, NULL, NULL);
            CoTaskMemFree((void *)pszOut);
            *ppszFullLink=pszTemp;

            pszTemp=(TCHAR *)CoTaskMemAlloc(80);
            pIOleObject->GetUserType(USERCLASSTYPE_SHORT
                , &pszOut);
            WideCharToMultiByte(CP_ACP, 0, pszOut, -1
                , pszTemp, 80, NULL, NULL);
            CoTaskMemFree((void *)pszOut);
            *ppszShortLink=pszTemp;
           #else
            pIOleObject->GetUserType(USERCLASSTYPE_FULL
                , ppszFullLink);
            pIOleObject->GetUserType(USERCLASSTYPE_SHORT
                , ppszShortLink);
           #endif
            pIOleObject->Release();
            }

        *pcchName=CchFilePrefix(pmk);
        pmk->Release();
        }

   #ifdef WIN32ANSI
    pszTemp=(TCHAR *)CoTaskMemAlloc(80);
    hr=pIOleLink->GetSourceDisplayName(&pszOut);
    WideCharToMultiByte(CP_ACP, 0, pszOut, -1
        , pszTemp, 80, NULL, NULL);
    CoTaskMemFree((void *)pszOut);
    *ppszName=pszTemp;
    return hr;
   #else
    return pIOleLink->GetSourceDisplayName(ppszName);
   #endif
    }





/*
 * CLinks::OpenLinkSource
 *
 * Purpose:
 *  Does nothing.  The container using this object is the only
 *  one that knows how to activate an object properly.
 *
 * Parameters:
 *  dwLink          DWORD ignored.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CLinks::OpenLinkSource(DWORD dwLink)
    {
    return NOERROR;
    }






/*
 * CLinks::UpdateLink
 *
 * Purpose:
 *  Updates the link for this object.
 *
 * Parameters:
 *  dwLink          DWORD, an IOleLink pointer to the object
 *                  affected.
 *  fErrorMessage   BOOL indicating if we can show errors.
 *  fErrorAction    BOOL making no sense whatsoever.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, error code otherwise. If
 *                  there is an error, the caller should set the
 *                  link availability flag to FALSE.  Otherwise set
 *                  to TRUE.
 */

STDMETHODIMP CLinks::UpdateLink(DWORD dwLink
    , BOOL fErrorMessage, BOOL fErrorAction)
    {
    LPOLELINK       pIOleLink=(LPOLELINK)dwLink;
    HRESULT         hr;
    LPOLEOBJECT     pIOleObject;

    if (NULL==pIOleLink)
        return ResultFromScode(E_FAIL);

    hr=pIOleLink->QueryInterface(IID_IOleObject
        , (PPVOID)&pIOleObject);

    if (FAILED(hr))
        return hr;

    hr=pIOleObject->IsUpToDate();
	
    if (NOERROR!=hr)
        {
        hr=pIOleObject->Update();

        if (FAILED(hr))
            return hr;
        }

    return NOERROR;
    }






/*
 * CLinks::CancelLink
 *
 * Purpose:
 *  Sets the source moniker in the link to NULL but does nothing
 *  else.  How the container decides to convert this to static
 *  is its choice.
 *
 * Parameters:
 *  dwLink          DWORD, an IOleLink pointer to the object
 *                  affected.
 *
 * Return Value:
 *  HRESULT         Standard.
 */

STDMETHODIMP CLinks::CancelLink(DWORD dwLink)
    {
    LPOLELINK       pIOleLink=(LPOLELINK)dwLink;

    if (NULL!=pIOleLink)
        return pIOleLink->SetSourceMoniker(NULL, CLSID_NULL);

    return NOERROR;
    }





//PROTECTED FUNCTIONS INTERNAL TO CLinks

/*
 * CLinks::ValidateLinkSource
 * (Protected)
 *
 * Purpose:
 *  Given a name of a link source retrieve a moniker for it and
 *  a CLSID if we can bind.
 *
 * Parameters:
 *  pszName         LPTSTR of the source
 *  pchEaten        ULONG * into which to return how many
 *                  characters we parse.
 *  ppmk            LPMONIKER * into which to store the moniker
 *  pclsID          LPCLSID into which to store the clsID.
 *
 * Return Value:
 *  BOOL            TRUE if *ppmk has a valid moniker,
 *                  FALSE otherwise.
 */

BOOL CLinks::ValidateLinkSource(LPTSTR pszName
    , ULONG *pchEaten, LPMONIKER *ppmk, LPCLSID pclsID)
    {
    HRESULT     hr;
    LPBC        pbc=NULL;
    LPOLEOBJECT pIOleObject;

    *ppmk=NULL;
    *pclsID=CLSID_NULL;

    if (FAILED(CreateBindCtx(0, &pbc)))
        return FALSE;

    hr=MkParseDisplayName(pbc, pszName, pchEaten, ppmk);

    if (SUCCEEDED(hr))
        {
        /*
         * Now that we have a moniker for this new source, so try
         * binding to that source and get its CLSID.
         */
        hr=(*ppmk)->BindToObject(pbc, NULL, IID_IOleObject
            , (PPVOID)&pIOleObject);

        if (SUCCEEDED(hr))
            {
            pIOleObject->GetUserClassID(pclsID);
            pIOleObject->Release();
            }

        return TRUE;
        }

    pbc->Release();
    return FALSE;
    }




/*
 * CLinks::CreateNewSourceMoniker
 * (Protected)
 *
 * Purpose:
 *  Given a name of a link source create a moniker for it.
 *
 * Parameters:
 *  pszName         LPTSTR of the source
 *  cchName         ULONG length of the filename in pszName.
 *  ppmk            LPMONIKER * into which to store the moniker
 *
 * Return Value:
 *  BOOL            TRUE if *ppmk has a valid moniker,
 *                  FALSE otherwise.
 */

BOOL CLinks::CreateNewSourceMoniker(LPTSTR pszName
    , ULONG cchName, LPMONIKER *ppmk)
    {
    TCHAR       szName[CCHPATHMAX];
    LPMONIKER   pmkFile=NULL;
    LPMONIKER   pmkItem=NULL;

    *ppmk=NULL;
    lstrcpyn(szName, pszName, (int)cchName+1);
    CreateFileMoniker(szName, &pmkFile);

    if (NULL==pmkFile)
        return FALSE;

    if (lstrlen(pszName) > (int)cchName)
        {
        lstrcpy(szName, pszName+cchName+1);
        CreateItemMoniker(TEXT("!"), szName, &pmkItem);

        if (NULL!=pmkItem)
            {
            CreateGenericComposite(pmkFile, pmkItem, ppmk);
            pmkItem->Release();
            }

        pmkFile->Release();

        if (NULL==*ppmk)
            return FALSE;
        }
    else
        *ppmk=pmkFile;

    return TRUE;
    }




/*
 * CLinks::CchFilePrefix
 * (Protected)
 *
 * Purpose:
 *  Returns the length of a file moniker given that pmk is either
 *  a file moniker or a composite containing a file moniker
 *  as the first item.
 *
 * Parameters:
 *  pmk             IMoniker * to check.
 *
 * Return Value:
 *  UINT            Length of the file moniker text.
 */

UINT CLinks::CchFilePrefix(LPMONIKER pmk)
    {
    LPMONIKER       pmkFirst=NULL;
    LPENUMMONIKER   pEnum;
    DWORD           dwMk;
    LPOLESTR        psz=NULL;
    LPBC            pbc=NULL;
    ULONG           cch=0;
    HRESULT         hr;

    if (NULL==pmk)
       return 0;

    hr=pmk->IsSystemMoniker(&dwMk);

    if (FAILED(hr) || MKSYS_GENERICCOMPOSITE!=dwMk)
        {
        //Already a single moniker
        pmkFirst=pmk;
        pmk->AddRef();
        }
    else
        {
        //Pull off the first moniker in a composite
        hr=pmk->Enum(TRUE, &pEnum);

        if (FAILED(hr))
            return NULL;

        hr=pEnum->Next(1, &pmkFirst, NULL);
        pEnum->Release();
        }

    if (NULL==pmkFirst)
        return 0;

    hr=pmkFirst->IsSystemMoniker(&dwMk);

    if (SUCCEEDED(hr) && MKSYS_FILEMONIKER==dwMk);
        {
        if (SUCCEEDED(CreateBindCtx(0, &pbc)))
            {
            if (SUCCEEDED(pmkFirst->GetDisplayName(pbc, NULL
                , &psz)))
                {
               #ifdef WIN32ANSI
                cch=wcslen(psz);
               #else
                cch=lstrlen(psz);
               #endif
                CoTaskMemFree((void *)psz);
                }

            pbc->Release();
            }
        }

    pmkFirst->Release();
    return cch;
    }
