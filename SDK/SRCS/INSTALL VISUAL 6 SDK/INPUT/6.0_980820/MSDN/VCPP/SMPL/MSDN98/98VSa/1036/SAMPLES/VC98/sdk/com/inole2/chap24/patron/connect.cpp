/*
 * CONNECT.CPP
 * Patron Chapter 24
 *
 * Helper functions for working with connection points on objects
 * and the event sets of those objects.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * InterfaceConnect
 *
 * Purpose:
 *  Connects some sink interface of a given IID to an object.
 *
 * Parameters:
 *  pObj            LPUNKNOWN of the object to which we connect
 *  riid            REFIID of the interface of the sink
 *  pIUnknownSink   LPUNKNOWN of the caller's sink interface that
 *                  is actually of the type matching riid
 *  pdwConn         LPDWORD in which to return the connection key
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL InterfaceConnect(LPUNKNOWN pObj, REFIID riid
    , LPUNKNOWN pIUnknownSink, LPDWORD pdwConn)
    {
    HRESULT                     hr;
    LPCONNECTIONPOINTCONTAINER  pCPC;
    LPCONNECTIONPOINT           pCP;

    if (NULL==pObj || NULL==pIUnknownSink || NULL==pdwConn)
        return FALSE;

    hr=pObj->QueryInterface(IID_IConnectionPointContainer
        , (PPVOID)&pCPC);

    if (FAILED(hr))
        return FALSE;

    hr=pCPC->FindConnectionPoint(riid, &pCP);

    if (SUCCEEDED(hr))
        {
        hr=pCP->Advise(pIUnknownSink, pdwConn);
        pCP->Release();
        }

    pCPC->Release();
    return SUCCEEDED(hr);
    }



/*
 * InterfaceDisconnect
 *
 * Purpose:
 *  Disconnects a prior connection to an object.
 *
 * Parameters:
 *  pObj            LPUNKNOWN of the object from which to disconnect
 *  riid            REFIID of the interface of the sink
 *  pdwConn         LPDWORD containing the key returned by
 *                  InterfaceConnect.  This function will zero the
 *                  key on diconnect.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL InterfaceDisconnect(LPUNKNOWN pObj, REFIID riid
    , LPDWORD pdwConn)
    {
    HRESULT                     hr;
    LPCONNECTIONPOINTCONTAINER  pCPC;
    LPCONNECTIONPOINT           pCP;

    if (NULL==pObj || NULL==pdwConn)
        return FALSE;

    if (0==*pdwConn)
        return FALSE;

    hr=pObj->QueryInterface(IID_IConnectionPointContainer
        , (PPVOID)&pCPC);

    if (FAILED(hr))
        return FALSE;

    hr=pCPC->FindConnectionPoint(riid, &pCP);

    if (SUCCEEDED(hr))
        {
        hr=pCP->Unadvise(*pdwConn);

        if (SUCCEEDED(hr))
            *pdwConn=0L;

        pCP->Release();
        }

    pCPC->Release();
    return SUCCEEDED(hr);
    }






/*
 * ObjectTypeInfo
 *
 * Purpose:
 *  Retrieves the ITypeInfo for the entire object from which
 *  one can learn the IID of the event set and navigate to the
 *  ITypeInfo for events, among other things.
 *
 * Parameters:
 *  pObj            LPUNKNOWN of the object
 *  ppITypeInfo     LPTYPEINFO * in which to return the ITypeInfo
 *                  interface for the object's events.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL ObjectTypeInfo(LPUNKNOWN pObj, LPTYPEINFO *ppITypeInfo)
    {
    HRESULT             hr;
    LPPROVIDECLASSINFO  pIProvideClassInfo;
    
    if (NULL==pObj || NULL==ppITypeInfo)
        return FALSE;

    *ppITypeInfo=NULL;

    /*
     * Get the object's IProvideClassInfo and call the GetClassInfo
     * method therein.  This will give us back the ITypeInfo for
     * the entire object.
     */

    hr=pObj->QueryInterface(IID_IProvideClassInfo
        , (PPVOID)&pIProvideClassInfo);

    if (FAILED(hr))
        return FALSE;

    hr=pIProvideClassInfo->GetClassInfo(ppITypeInfo);
    pIProvideClassInfo->Release();

    return SUCCEEDED(hr);
    }




/*
 * ObjectTypeInfoEvents
 *
 * Purpose:
 *  Retrieves the events type information from an object.  This is
 *  defined to be the "default source" interface in the object's
 *  type library.
 *
 * Parameters:
 *  pObj            LPUNKNOWN of the object
 *  ppITypeInfo     LPTYPEINFO * in which to return the ITypeInfo
 *                  interface for the object's events.
 *
 * Return Value:
 *  BOOL            TRUE if the event type lib exists, FALSE
 *                  if not or on any other error.
 */

BOOL ObjectTypeInfoEvents(LPUNKNOWN pObj, LPTYPEINFO *ppITypeInfo)
    {
    HRESULT             hr;
    LPTYPEINFO          pITypeInfoAll;
    LPTYPEATTR          pTA;

    if (NULL==pObj || NULL==ppITypeInfo)
        return FALSE;

    if (!ObjectTypeInfo(pObj, &pITypeInfoAll))
        return FALSE;

    /*
     * We have the object's overall ITypeInfo in pITypeInfoAll.
     * Now get the type attributes which will tell us the number of
     * individual interfaces in this type library.  We then loop
     * through the "implementation types" for all those interfaces
     * calling GetImplTypeFlags, looking for the default source.
     */

    *ppITypeInfo=NULL;  //Use this to determine success

    if (SUCCEEDED(pITypeInfoAll->GetTypeAttr(&pTA)))
        {
        UINT        i;
        int         iFlags;

        for (i=0; i < pTA->cImplTypes; i++)
            {
            //Get the implementation type for this interface
            hr=pITypeInfoAll->GetImplTypeFlags(i, &iFlags);

            if (FAILED(hr))
                continue;

            if ((iFlags & IMPLTYPEFLAG_FDEFAULT)
                && (iFlags & IMPLTYPEFLAG_FSOURCE))
                {
                HREFTYPE    hRefType=NULL;

                /*
                 * This is the interface we want.  Get a handle to
                 * the type description from which we can then get
                 * the ITypeInfo.
                 */
                pITypeInfoAll->GetRefTypeOfImplType(i, &hRefType);
                hr=pITypeInfoAll->GetRefTypeInfo(hRefType
                    , ppITypeInfo);

                break;
                }
            }

        pITypeInfoAll->ReleaseTypeAttr(pTA);
        }

    pITypeInfoAll->Release();
    return (NULL!=*ppITypeInfo);
    }






/*
 * ObjectEventsIID
 *
 * Purpose:
 *  Determines the IID of the object's events interface so we
 *  can ask for the right IConnectionPoint for events.
 *
 * Parameters:
 *  pObj            LPUNKNOWN of the object
 *  piid            IID * in which to return the IID for events
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL ObjectEventsIID(LPUNKNOWN pObj, IID *piid)
    {
    HRESULT             hr;
    LPTYPEINFO          pITypeInfo;
    LPTYPEATTR          pTA;

    *piid=CLSID_NULL;

    if (!ObjectTypeInfoEvents(pObj, &pITypeInfo))
        return FALSE;

    hr=pITypeInfo->GetTypeAttr(&pTA);

    if (SUCCEEDED(hr))
        {
        *piid=pTA->guid;
        pITypeInfo->ReleaseTypeAttr(pTA);
        }

    pITypeInfo->Release();
    return SUCCEEDED(hr);
    }
