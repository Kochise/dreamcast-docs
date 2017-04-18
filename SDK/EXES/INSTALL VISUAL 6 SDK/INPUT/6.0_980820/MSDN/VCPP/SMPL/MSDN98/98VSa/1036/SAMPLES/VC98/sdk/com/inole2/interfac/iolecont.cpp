/*
 * IOLECONT.CPP
 *
 * Templace implementation of the IOleItemContainer interface.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iolecont.h"


/*
 * CImpIOleItemContainer::CImpIOleItemContainer
 * CImpIOleItemContainer::~CImpIOleItemContainer
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object controlling this interface.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleItemContainer::CImpIOleItemContainer(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
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
    , LPVOID *ppv)
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
 */

STDMETHODIMP CImpIOleItemContainer::ParseDisplayName(LPBC pbc
    , LPOLESTR pszName, ULONG *pchEaten, LPMONIKER *ppmk)
    {
    *ppmk=NULL;
    return ResultFromScode(E_NOTIMPL);
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
 */

STDMETHODIMP CImpIOleItemContainer::LockContainer(BOOL fLock)
    {
    /*
     * This is pretty much the same implementation as
     * IClassFactory::LockServer, and we can use the same lock
     * count to accomplish our goal.
     */

    return ResultFromScode(E_NOTIMPL);
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
 *  ppv             LPVOID * into which to return the object.
 */

STDMETHODIMP CImpIOleItemContainer::GetObject(LPOLESTR pszItem
    , DWORD dwSpeed, LPBINDCTX pbc, REFIID riid, LPVOID *ppv)
    {
    *ppv=NULL;
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIOleItemContainer::GetObjectStorage
 *
 * Purpose:
 *  Similar to GetObject in that we have to locate the object
 *  described by a given name, but instead of returning any old
 *  interface we return a storage element.
 *
 * Parameters:
 *  pszItem         LPOLESTR to the item we must locate.
 *  pcb             LPBINDCTX providing the binding context.
 *  riid            REFIID of the interface requested.  Usually
 *                  IStorage or IStream.
 *  ppv             LPVOID into which to return the object.
 */

STDMETHODIMP CImpIOleItemContainer::GetObjectStorage(LPOLESTR pszItem
    , LPBINDCTX pbc, REFIID riid, LPVOID *ppv)
    {
    *ppv=NULL;
    return ResultFromScode(E_NOTIMPL);
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
    return ResultFromScode(E_NOTIMPL);
    }
