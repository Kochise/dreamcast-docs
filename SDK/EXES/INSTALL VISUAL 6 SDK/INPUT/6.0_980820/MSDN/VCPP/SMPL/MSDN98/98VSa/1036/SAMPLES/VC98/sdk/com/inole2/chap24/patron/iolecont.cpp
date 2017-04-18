/*
 * IOLECONT.CPP
 * Patron Chapter 24
 *
 * Implementation of the IOleItemContainer interface for Patron's
 * CPage and CPatronDoc alike, using the constructor parameter fDoc
 * to differentiate.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include <stdlib.h>
#include "patron.h"


/*
 * CImpIOleItemContainer::CImpIOleItemContainer
 * CImpIOleItemContainer::~CImpIOleItemContainer
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the page or pages.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 *  fDoc            BOOL indicating if we're in CPatronDoc or CPage
 */

CImpIOleItemContainer::CImpIOleItemContainer(LPVOID pObj
    , LPUNKNOWN pUnkOuter, BOOL fDoc)
    {
    m_cRef=0;
    m_fDoc=fDoc;

    if (fDoc)
        {
        m_pDoc=(PCPatronDoc)pObj;
        m_pPage=NULL;
        }
    else
        {
        m_pDoc=NULL;
        m_pPage=(PCPage)pObj;
        }

    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIOleItemContainer::~CImpIOleItemContainer(void)
    {
    return;
    }




/*
 * CImpIOleItemContainer::QueryInterface
 * CImpIOleItemContainer::AddRef
 * CImpIOleItemContainer::Release
 *
 * Purpose:
 *  IUnknown members for CImpIOleItemContainer object.
 */

STDMETHODIMP CImpIOleItemContainer::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIOleItemContainer::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIOleItemContainer::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIOleItemContainer::ParseDisplayName
 *
 * Purpose:
 *  Inherited member of IParseDisplayName that takes a string name
 *  and turns out a moniker for it.
 *
 * Parameters:
 *  pbc             LPBC to the binding context
 *  pszName         LPOLESTR to the name to parse.
 *  pchEaten        ULONG * into which to store how many
 *                  characters we scanned in the display name.
 *  ppmk            LPMONIKER * in which to return the moniker.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleItemContainer::ParseDisplayName(LPBC pbc
    , LPOLESTR pszName, ULONG *pchEaten, LPMONIKER *ppmk)
    {
    OLECHAR     ch;
    ULONG       chEaten=0;
    TCHAR       szName[256];
    TCHAR       szComp[15];
    LPTSTR      psz;
    UINT        cch;

    *ppmk=NULL;
    *pchEaten=0;

    /*
     * All we have to look for is the string between the !
     * delimeters (or a null terminator).  pszName should be pointing
     * to a !, so skip it and scan the string for a ! or 0,
     * then pass the result to CreateItemMoniker.
     */

    psz=szName;

    ch=*pszName++;
    chEaten++;

    if ((OLECHAR)'!'!=ch)
        return ResultFromScode(MK_E_SYNTAX);

    ch=*pszName++;

    while ((OLECHAR)0!=ch && (OLECHAR)'!' !=ch)
        {
        *psz++=(TCHAR)ch;
        chEaten++;
        ch=*pszName++;
        }

    *psz=(TCHAR)0;

    /*
     * Syntax check.  If we're the DOcument object, check for
     * "Page n" at the beginning of the string.  Otherwise check
     * for "Tenant n".
     */
    lstrcpy(szComp, m_fDoc ? TEXT("Page ") : TEXT("Tenant "));

    //Does szName start with szComp?
    cch=lstrlen(szComp);

    if (0!=_tcsncicmp(szName, szComp, cch))
        {
        *pchEaten=1;    //Parsed ! at least
        return ResultFromScode(MK_E_SYNTAX);
        }

    //Check for a number in szName
    if ((TCHAR)'0' != szName[cch])
        {
        if (0==_ttoi(szName+cch))
            {
            *pchEaten=cch;  //Got past name
            return ResultFromScode(MK_E_SYNTAX);
            }
        }

    *pchEaten=chEaten;
   #ifdef WIN32ANSI
    //Use the ANSI version here since szName is ANSI
    return INOLE_CreateItemMoniker(TEXT("!"), szName, ppmk);
   #else
    return CreateItemMoniker(OLETEXT("!"), szName, ppmk);
   #endif
    }




/*
 * CImpIOleItemContainer::EnumObjects
 *
 * Purpose:
 *  Creates and returns an IEnumUnknown object that allows the
 *  caller to walk through the objects in this continer thing.
 *
 * Parameters:
 *  dwFlags         DWORD specifying what kind of objects to
 *                  enumerate.
 *  ppEnum          LPENUMUNKNOWN * into which to return the
 *                  enumerator
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleItemContainer::EnumObjects(DWORD dwFlags
    , LPENUMUNKNOWN *ppEnum)
    {
    *ppEnum=NULL;
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIOleItemContainer::LockContainer
 *
 * Purpose:
 *  Establishes a lock on the container to prevent it from shutting
 *  down outside of user control.  This is used to control the
 *  lifetime of the container when it's used to update a link to an
 *  embedded object within it.  If we're unlock and the user has not
 *  taken control, we close.
 *
 * Parameters:
 *  fLock           BOOL indicating a lock or unlock.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleItemContainer::LockContainer(BOOL fLock)
    {
    /*
     * This is pretty much the same implementation as
     * IClassFactory::LockServer, and we can use the same lock
     * count to accomplish our goal.
     */

    if (fLock)
        g_cLock++;
    else
        {
        g_cLock--;
        g_cObj++;
        ObjectDestroyed();
        }

    return NOERROR;
    }






/*
 * CImpIOleItemContainer::GetObject
 *
 * Purpose:
 *  Returns the requested interface pointer on an object in this
 *  container.
 *
 * Parameters:
 *  pszItem         LPOLESTR to the item we must locate.
 *  dwSpeed         DWORD identifying how long the caller is willing
 *                  to wait.
 *  pcb             LPBINDCTX providing the binding context.
 *  riid            REFIID of the interface requested.
 *  ppv             PPVOID into which to return the object.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleItemContainer::GetObject(LPOLESTR pszItem
    , DWORD dwSpeed, LPBINDCTX pbc, REFIID riid, PPVOID ppv)
    {
    DWORD       dw;
    char        szTemp[40];     //ANSI for atol
    HRESULT     hr=ResultFromScode(E_FAIL);
    PCPage      pPage;
    PCTenant    pTenant;
    LPUNKNOWN   pObj;
    UINT        i, iCur;

    *ppv=NULL;

    if (m_fDoc)
        {
        /*
         * The item name should be "Page n", so we'll do it the
         * easy way:  call atol on pszItem+5 (we always know that
         * we'll have "Page " there since we put it there (see
         * CPage::GetStorageName).
         */

        UNICODETOANSI((pszItem+5), szTemp, sizeof(szTemp));
        dw=atol(szTemp);

        i=m_pDoc->m_pPG->IPageGetFromID(dw, &pPage, FALSE);

        if (NOVALUE==i)
            return hr;

        /*
         * If we're asked for immediate speed, only do this if the
         * page is already current, i.e. everything is loaded.
         */
        iCur=m_pDoc->m_pPG->CurPageGet();

        if (BINDSPEED_IMMEDIATE==dwSpeed && iCur!=i)
            return ResultFromScode(MK_E_EXCEEDEDDEADLINE);

        m_pDoc->m_pPG->CurPageSet(i);

        //This will have changed to be the current page now.
        if (NULL!=m_pDoc->m_pPG->m_pPageCur)
            hr=m_pDoc->m_pPG->m_pPageCur->QueryInterface(riid, ppv);
        }
    else
        {
        if (TenantFromName(pszItem, &pTenant))
            {
            pTenant->ObjectGet(&pObj);

            /*
             * If we're asked for immediate or moderate, only work
             * if the object is already running.
             */
            hr=IsRunning(pszItem);  //This is the function below

            if ((BINDSPEED_IMMEDIATE==dwSpeed
                || BINDSPEED_MODERATE==dwSpeed) && NOERROR!=hr)
                hr=ResultFromScode(MK_E_EXCEEDEDDEADLINE);
            else
                {
                //IMPORTANT:  Make sure this object is running first
                OleRun(pObj);
                hr=pObj->QueryInterface(riid, ppv);
                }

            pObj->Release();
            }
        else
            hr=ResultFromScode(MK_E_NOOBJECT);
        }

    return hr;
    }






/*
 * CImpIOleItemContainer::GetObjectStorage
 *
 * Purpose:
 *  Similar to get Object in that we have to locate the object
 *  described by a given name, but instead of returning any old
 *  interface we return a storage element.
 *
 * Parameters:
 *  pszItem         LPOLESTR to the item we must locate.
 *  pcb             LPBINDCTX providing the binding context.
 *  riid            REFIID of the interface requested.  Usually
 *                  IStorage or IStream.
 *  ppv             PPVOID into which to return the object.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleItemContainer::GetObjectStorage(LPOLESTR pszItem
    , LPBINDCTX pbc, REFIID riid, PPVOID ppv)
    {
    PCTenant    pTenant;

    *ppv=NULL;

    if (m_fDoc)
        return ResultFromScode(E_NOTIMPL);

    //Can only handle IStorage.
    if (IID_IStorage!=riid)
        return ResultFromScode(E_NOINTERFACE);

    if (TenantFromName(pszItem, &pTenant))
        pTenant->StorageGet((LPSTORAGE *)ppv);

    return (NULL!=*ppv) ? NOERROR : ResultFromScode(E_FAIL);
    }






/*
 * CImpIOleItemContainer::IsRunning
 *
 * Purpose:
 *  Answers if the object under the given name is currently running.
 *
 * Parameters:
 *  pszItem         LPOLESTR of the item to check
 *
 * Return Value:
 *  HRESULT         NOERROR if the object is running, S_FALSE
 *                  otherwise.  Possibly MK_E_NOOBJECT if the name
 *                  is bogus.
 */

STDMETHODIMP CImpIOleItemContainer::IsRunning(LPOLESTR pszItem)
    {
    HRESULT     hr;
    PCTenant    pTenant;
    LPUNKNOWN   pObj;
    LPOLEOBJECT pIOleObject;

    /*
     * If this is the document's container interface, the object
     * is a page and the page is always running.
     */
    if (m_fDoc)
        return NOERROR;
    else
        {
        if (TenantFromName(pszItem, &pTenant))
            {
            //Ask the actual object if its running.
            pTenant->ObjectGet(&pObj);
            hr=pObj->QueryInterface(IID_IOleObject
                , (PPVOID)&pIOleObject);
            pObj->Release();

            if (SUCCEEDED(hr))
                {
                hr=(OleIsRunning(pIOleObject))
                    ? NOERROR : ResultFromScode(S_FALSE);
                pIOleObject->Release();
                }
            }
        else
            hr=ResultFromScode(MK_E_NOOBJECT);
        }

    return hr;
    }




/*
 * CImpIOleItemContainer::TenantFromName
 * (Private)
 *
 * Purpose:
 *  This function which is NOT part of the interface retrieves
 *  a tenant pointer from a tenant name.
 *
 * Parameters:
 *  pszItem         LPOLESTR of the tenant to locate.
 *  ppTenant        PCTenant * in which to return the pointer.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CImpIOleItemContainer::TenantFromName(LPOLESTR pszItem
    , PCTenant *ppTenant)
    {
    DWORD       dw;
    char        szTemp[40];     //ANSI for atol

    if (m_fDoc)
        return FALSE;

    //The item name should be "Tenant xxxx", so use pszItem+7.
    UNICODETOANSI((pszItem+7), szTemp, sizeof(szTemp));
    dw=atol(szTemp);

    *ppTenant=NULL;

    return m_pPage->TenantGetFromID(dw, ppTenant, FALSE);
    }
