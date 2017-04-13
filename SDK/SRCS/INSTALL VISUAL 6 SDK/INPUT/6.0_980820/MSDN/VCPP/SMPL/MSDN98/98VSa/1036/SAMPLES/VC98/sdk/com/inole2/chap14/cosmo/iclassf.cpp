/*
 * ICLASSF.CPP
 * Cosmo Chapter 14
 *
 * Implementation of a class factory for Cosmo's OLE Automation
 * support.  This same implementation handles CLSID_CosmoFigure
 * as well as CLSID_Cosmo2Application.  The CLSID is given to the
 * constructor.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "cosmo.h"


/*
 * CClassFactory::CClassFactory
 * CClassFactory::~CClassFactory
 *
 * Constructor Parameters:
 *  pFR             PCCosmoFrame that can create documents.
 *  rclsID          REFCLSID of the object this factory should
 *                  create.
 */

CClassFactory::CClassFactory(PCCosmoFrame pFR, REFCLSID rclsID)
    {
    m_cRef=0L;
    m_pFR=pFR;
    m_clsID=rclsID;
    m_fCreated=FALSE;
    return;
    }


CClassFactory::~CClassFactory(void)
    {
    return;
    }




/*
 * CClassFactory::QueryInterface
 * CClassFactory::AddRef
 * CClassFactory::Release
 */

STDMETHODIMP CClassFactory::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IClassFactory==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CClassFactory::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CClassFactory::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }




/*
 * CClassFactory::CreateInstance
 *
 * Purpose:
 *  Instantiates a Figure object that supports embedding.
 *
 * Parameters:
 *  pUnkOuter       LPUNKNOWN to the controlling IUnknown if we are
 *                  being used in an aggregation.
 *  riid            REFIID identifying the interface the caller
 *                  desires to have for the new object.
 *  ppvObj          PPVOID in which to store the desired
 *                  interface pointer for the new object.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise contains
 *                  E_NOINTERFACE if we cannot support the requested
 *                  interface.
 */

STDMETHODIMP CClassFactory::CreateInstance(LPUNKNOWN pUnkOuter
    , REFIID riid, PPVOID ppvObj)
    {
    HRESULT             hr;

    *ppvObj=NULL;

    /*
     * We can only create one instance of the application object
     * from this factory, but we can create multiple figure
     * objects.  Creation of a figure never sets this flag.
     */
    if (m_fCreated)
        return ResultFromScode(E_UNEXPECTED);

    hr=ResultFromScode(E_OUTOFMEMORY);

    //We don't support aggregation
    if (NULL!=pUnkOuter)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    //Check which class we're supposed to create
    if (CLSID_Cosmo2Application==m_clsID)
        {
        /*
         * By virtue of this application running, the frame
         * object has already created the 'application' object
         * we want to return.  So we just grab the right interface
         * pointer from it.
         */
        hr=m_pFR->AutoApp()->QueryInterface(riid, ppvObj);

        //Assume we created an object.
        g_cObj++;
        }


    if (CLSID_CosmoFigure==m_clsID)
        {
        /*
         * We can actually use the Figures collection object
         * that the client object maintains since it has
         * creation code in it already.
         */
        IDispatch      *pIDispatch;
        ICosmoFigures  *pICosmoFigs;

        pIDispatch=m_pFR->AutoApp()->get_Figures();

        if (NULL!=pIDispatch)
            {
            /*
             * We have the collection IDispatch, we want to
             * call the Add method which we can do through
             * ICosmoFigures.
             */
            if (SUCCEEDED(pIDispatch->QueryInterface
                (IID_ICosmoFigures, (PPVOID)&pICosmoFigs)))
                {
                pIDispatch->Release();

                /*
                 * Get the pointer for the new figure.  This will
                 * increment g_cObj when successful.
                 */
                pIDispatch=pICosmoFigs->Add();

                if (NULL!=pIDispatch)
                    {
                    //Get the originally requested pointer.
                    hr=pIDispatch->QueryInterface(riid, ppvObj);
                    pIDispatch->Release();

                    /*
                     * Also force an AddRef on the application object
                     * to prevent shutdown when we access it through
                     * Figure::Application.  Such an access would
                     * AddRef it and Release it, then cause shutdown.
                     * The application object isn't any good any more.
                     *
                     * Note that since we didn't put the /Automation
                     * flag on the LocalServer[32] entry for the
                     * figure CLSID (we did for the app CLSID) then
                     * the app class factory was never registered
                     * and there's no danger of the app object being
                     * created later.
                     */
                    m_pFR->AutoApp()->AddRef();
                    }
                else
                    g_cObj++;   //To fake shutdown
                }
            }
        }

    /*
     * By assuming we created an object (with g_cObj++) allows us
     * to just call ObjectDestroyed to do shutdown as necessary.
     * If this CreateInstance was for the application object,
     * then this app was launched for the purpose of getting
     * at the object, so shutdown will occur (the class factory
     * is only registered if /Automation is present).
     *
     * For the Figure object, that class factory is always
     * registered, so there might be other object and there
     * might be user control, so ObjectDestroyed will not necessarily
     * cause shutdown.
     */

    if (FAILED(hr))
        ObjectDestroyed();
    else
        {
        //Prevent second 'instantiations' of the application object.
        m_fCreated=(CLSID_Cosmo2Application==m_clsID);
        }

    return hr;
    }






/*
 * CClassFactory::LockServer
 *
 * Purpose:
 *  Increments or decrements the lock count of the serving
 *  IClassFactory object.  When the number of locks goes to
 *  zero and the number of objects is zero, we shut down the
 *  application.
 *
 * Parameters:
 *  fLock           BOOL specifying whether to increment or
 *                  decrement the lock count.
 *
 * Return Value:
 *  HRESULT         NOERROR always.
 */

STDMETHODIMP CClassFactory::LockServer(BOOL fLock)
    {
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
