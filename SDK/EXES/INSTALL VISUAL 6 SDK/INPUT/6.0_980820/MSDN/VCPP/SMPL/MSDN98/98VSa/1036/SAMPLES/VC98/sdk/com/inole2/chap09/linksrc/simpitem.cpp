/*
 * SIMPITEM.CPP
 * Simple Item Object for Link Source, Chapter 9
 *
 * Implementation of an item object with nothing more
 * than the shared IDescription in IDESCRIP.CPP.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "linksrc.h"

#ifdef WIN32ANSI
/*
 * This is to turn off the mapping to ANSI wrapper APIs because
 * we're actually using wide char strings under Win32 all the time
 * in parts of this code.
 */
#undef CreateItemMoniker
#define CreateItemMoniker CreateItemMoniker

#endif


/*
 * CSimpleItem::CSimpleItem
 * CSimpleItem::~CSimpleItem
 *
 * Parameters (Constructor):
 *  pUnkParent      LPUNKNOWN to the parent in which this
 *                  item lives
 *  pfnDestroy      PFNDESTROYED to call when an object
 *                  is destroyed.
 */

CSimpleItem::CSimpleItem(LPUNKNOWN pUnkParent
    , PFNDESTROYED pfnDestroy)
    {
    m_cRef=0;

    //This keeps the parent storage open as well
    m_pUnkParent=pUnkParent;
    pUnkParent->AddRef();

    m_pfnDestroy=pfnDestroy;

    m_pIStorage=NULL;
    m_pmk=NULL;
    m_dwRegROT=0;

    m_pImpIDescription=NULL;
    return;
    }

CSimpleItem::~CSimpleItem(void)
    {
    //Remove us from the running object table
    if (0!=m_dwRegROT)
        {
        IRunningObjectTable    *pROT;

        if (SUCCEEDED(GetRunningObjectTable(0, &pROT)))
            {
            pROT->Revoke(m_dwRegROT);
            pROT->Release();
            }
        }

    ReleaseInterface(m_pmk);
    ReleaseInterface(m_pIStorage);
    DeleteInterfaceImp(m_pImpIDescription);

    ReleaseInterface(m_pUnkParent);
    return;
    }



/*
 * CSimpleItem::Init
 *
 * Purpose:
 *  Performs any intiailization of a CSimpleItem that's prone to
 *  failure that we also use internally before exposing the object
 *  outside.
 *
 * Parameters:
 *  pmkLeft         IMoniker * of our containing object.
 *  pbc             IBindCtx * to use to register ourselves
 *                  as running.
 *  pszItem         LPOLESTR naming this object.
 *  pIStorage       IStorage * to our information.
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful,
 *                  FALSE otherwise.
 */

BOOL CSimpleItem::Init(IMoniker *pmkLeft, IBindCtx *pbc
    , LPOLESTR pszItem, IStorage *pIStorage)
    {
    OLECHAR     szDelim[]=OLETEXT("!");
    HRESULT     hr=ResultFromScode(S_FALSE);
    IMoniker   *pmkItem;

    m_pImpIDescription=new CImpIDescription(this);

    if (NULL==m_pImpIDescription)
        return FALSE;

    m_pIStorage=pIStorage;
    m_pImpIDescription->SetStorage(m_pIStorage);


    /*
     * Create an item moniker for ourselves and register as
     * running.  Failure here is not critical.
     */
    if (FAILED(CreateItemMoniker(szDelim, pszItem, &pmkItem)))
        return TRUE;

    //Create a composite for ourselves
    if (SUCCEEDED(pmkLeft->ComposeWith(pmkItem, FALSE, &m_pmk)))
        {
        IRunningObjectTable *pROT;

        if (SUCCEEDED(pbc->GetRunningObjectTable(&pROT)))
            {
            pROT->Register(0, this, m_pmk, &m_dwRegROT);
            pROT->Release();
            }
        }

    pmkItem->Release();
    return TRUE;
    }




/*
 * CSimpleItem::QueryInterface
 * CSimpleItem::AddRef
 * CSimpleItem::Release
 *
 * Purpose:
 *  IUnknown members for CSimpleItem object.
 */

STDMETHODIMP CSimpleItem::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid)
        *ppv=this;

    if (IID_IDescription==riid)
        *ppv=m_pImpIDescription;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CSimpleItem::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CSimpleItem::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    if (NULL!=m_pfnDestroy)
        (*m_pfnDestroy)();

    delete this;
    return 0;
    }
