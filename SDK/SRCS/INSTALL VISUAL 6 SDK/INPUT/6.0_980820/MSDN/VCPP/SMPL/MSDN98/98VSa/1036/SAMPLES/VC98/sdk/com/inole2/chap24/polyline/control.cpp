/*
 * CONTROL.CPP
 * Polyline Chapter 24
 *
 * Additional interfaces above the Chapter 23 version of Polyline
 * to make it an OLE Control, specifically ISpecifyPropertyPages,
 * IProvideClassInfo, IOleControl, and IDispatch, none of which
 * are terribly complex.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "polyline.h"


//ISpecifyPropertyPages implementation
/*
 * CImpISpecifyPP::CImpISpecifyPP
 * CImpISpecifyPP::~CImpISpecifyPP
 *
 * Parameters (Constructor):
 *  pObj            PCPolyline of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpISpecifyPP::CImpISpecifyPP(PCPolyline pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpISpecifyPP::~CImpISpecifyPP(void)
    {
    return;
    }


/*
 * CImpISpecifyPP::QueryInterface
 * CImpISpecifyPP::AddRef
 * CImpISpecifyPP::Release
 */

STDMETHODIMP CImpISpecifyPP::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpISpecifyPP::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpISpecifyPP::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpISpecifyPP::GetPages
 *
 * Purpose:
 *  Returns an array of GUIDs identifying the indivudual property
 *  pages used for this object.
 *
 * Parameters:
 *  pPages          CAUUID * pointing to a counted array of GUIDs.
 *                  This function allocates the array elements
 *                  and stores them in this structure.
 */

STDMETHODIMP CImpISpecifyPP::GetPages(CAUUID *pPages)
    {
    IMalloc *pIMalloc;
    GUID    *pGUID;

    pPages->cElems=0;
    pPages->pElems=NULL;

    if (FAILED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
        return ResultFromScode(E_OUTOFMEMORY);

    pGUID=(GUID *)pIMalloc->Alloc(CPROPPAGES * sizeof(GUID));

    if (NULL!=pGUID)
        {
        //We use our own page plus the standard color page.
        pGUID[0]=CLSID_PolylinePropPage;

        //Fill the structure and return.
        pPages->cElems=CPROPPAGES;
        pPages->pElems=pGUID;
        }

    pIMalloc->Release();
    return (NULL!=pGUID) ? NOERROR
        : ResultFromScode(E_OUTOFMEMORY);
    }




//IProvideClassInfo interface implementation
/*
 * CImpIProvideClassInfo::CImpIProvideClassInfo
 * CImpIProvideClassInfo::~CImpIProvideClassInfo
 *
 * Parameters (Constructor):
 *  pObj            PCPolyline of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIProvideClassInfo::CImpIProvideClassInfo(PCPolyline pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIProvideClassInfo::~CImpIProvideClassInfo(void)
    {
    return;
    }



/*
 * CImpIProvideClassInfo::QueryInterface
 * CImpIProvideClassInfo::AddRef
 * CImpIProvideClassInfo::Release
 */

STDMETHODIMP CImpIProvideClassInfo::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIProvideClassInfo::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIProvideClassInfo::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIProvideClassInfo::GetClassInfo
 *
 * Purpose:
 *  Returns the ITypeInfo through which the caller can retrieve
 *  information about the entire object.
 *
 * Parameters:
 *  ppTI            LPTYPEINFO * in which to store the ITypeInfo
 *                  pointer.
 */

STDMETHODIMP CImpIProvideClassInfo::GetClassInfo(LPTYPEINFO *ppTI)
    {
    if (NULL==ppTI)
        return ResultFromScode(E_POINTER);

    *ppTI=NULL;

    return m_pObj->m_pITypeLib->GetTypeInfoOfGuid(CLSID_Polyline19
        , ppTI);
    }




//IDispatch interface implementation

/*
 * CImpIDispatch::CImpIDispatch
 * CImpIDispatch::~CImpIDispatch
 *
 * Parameters (Constructor):
 *  pObj            PCPolyline of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIDispatch::CImpIDispatch(PCPolyline pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIDispatch::~CImpIDispatch(void)
    {
    return;
    }



/*
 * CImpIDispatch::QueryInterface
 * CImpIDispatch::AddRef
 * CImpIDispatch::Release
 */

STDMETHODIMP CImpIDispatch::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIDispatch::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIDispatch::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIDispatch::GetTypeInfoCount
 * CImpIDispatch::GetTypeInfo
 * CImpIDispatch::GetIDsOfNames
 *
 * The usual
 */

STDMETHODIMP CImpIDispatch::GetTypeInfoCount(UINT *pctInfo)
    {
    //We implement GetTypeInfo so return 1
    *pctInfo=1;
    return NOERROR;
    }


STDMETHODIMP CImpIDispatch::GetTypeInfo(UINT itInfo, LCID lcid
    , ITypeInfo **ppITypeInfo)
    {
    if (0!=itInfo)
        return ResultFromScode(TYPE_E_ELEMENTNOTFOUND);

    if (NULL==ppITypeInfo)
        return ResultFromScode(E_POINTER);

    *ppITypeInfo=NULL;

    //We ignore the LCID
    return m_pObj->m_pITypeLib->GetTypeInfoOfGuid
        (DIID_DIPolylineControl, ppITypeInfo);
    }


STDMETHODIMP CImpIDispatch::GetIDsOfNames(REFIID riid
    , OLECHAR **rgszNames, UINT cNames, LCID lcid, DISPID *rgDispID)
    {
    HRESULT     hr;
    ITypeInfo  *pTI;

    if (IID_NULL!=riid)
        return ResultFromScode(DISP_E_UNKNOWNINTERFACE);

    hr=GetTypeInfo(0, lcid, &pTI);

    if (SUCCEEDED(hr))
        {
        hr=DispGetIDsOfNames(pTI, rgszNames, cNames, rgDispID);
        pTI->Release();
        }

    return hr;
    }



/*
 * CImpIDispatch::Invoke
 *
 * Purpose:
 *  Calls a method in the dispatch interface or manipulates a
 *  property.
 *
 * Parameters:
 *  dispID          DISPID of the method or property of interest.
 *  riid            REFIID reserved, must be IID_NULL.
 *  lcid            LCID of the locale.
 *  wFlags          USHORT describing the context of the invocation.
 *  pDispParams     DISPPARAMS * to the array of arguments.
 *  pVarResult      VARIANT * in which to store the result.  Is
 *                  NULL if the caller is not interested.
 *  pExcepInfo      EXCEPINFO * to exception information.
 *  puArgErr        UINT * in which to store the index of an
 *                  invalid parameter if DISP_E_TYPEMISMATCH
 *                  is returned.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error code.
 */

STDMETHODIMP CImpIDispatch::Invoke(DISPID dispID, REFIID riid
    , LCID lcid, unsigned short wFlags, DISPPARAMS *pDispParams
    , VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
    {
    HRESULT     hr;
    ITypeInfo  *pTI;

    //riid is supposed to be IID_NULL always
    if (IID_NULL!=riid)
        return ResultFromScode(DISP_E_UNKNOWNINTERFACE);

    //Get the ITypeInfo for lcid
    hr=GetTypeInfo(0, lcid, &pTI);

    if (FAILED(hr))
        return hr;

    hr=pTI->Invoke(m_pObj->m_pImpIPolylineControl, dispID, wFlags
        , pDispParams, pVarResult, pExcepInfo, puArgErr);

    pTI->Release();
    return hr;
    }



//IPolylineControl interface implementation

/*
 * CImpIPolylineControl::CImpIPolylineControl
 * CImpIPolylineControl::~CImpIPolylineControl
 *
 * Parameters (Constructor):
 *  pObj            PCPolyline of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIPolylineControl::CImpIPolylineControl(PCPolyline pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIPolylineControl::~CImpIPolylineControl(void)
    {
    return;
    }



/*
 * CImpIPolylineControl::QueryInterface
 * CImpIPolylineControl::AddRef
 * CImpIPolylineControl::Release
 */

STDMETHODIMP CImpIPolylineControl::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIPolylineControl::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIPolylineControl::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIPolylineControl::BackColor
 * CImpIPolylineControl::LineColor
 * CImpIPolylineControl::LineStyle
 * CImpIPolylineControl::Clear
 * CImpIPolylineControl::RemoveLastPoint
 *
 * Purpose:
 *  Dispatch interface entry points that map to IPolyline
 *  members.
 */

STDMETHODIMP_(void) CImpIPolylineControl::put_BackColor
    (OLE_COLOR cr)
    {
    COLORREF        crOld;

    m_pObj->m_pImpIPolyline->ColorSet(POLYLINECOLOR_BACKGROUND
        , cr, &crOld);
    return;
    }

STDMETHODIMP_(OLE_COLOR) CImpIPolylineControl::get_BackColor(void)
    {
    COLORREF        cr;

    m_pObj->m_pImpIPolyline->ColorGet(POLYLINECOLOR_BACKGROUND
        , &cr);

    return cr;
    }

STDMETHODIMP_(void) CImpIPolylineControl::put_LineColor
    (OLE_COLOR cr)
    {
    COLORREF        crOld;

    m_pObj->m_pImpIPolyline->ColorSet(POLYLINECOLOR_LINE
        , cr, &crOld);

    return;
    }

STDMETHODIMP_(OLE_COLOR) CImpIPolylineControl::get_LineColor(void)
    {
    COLORREF        cr;

    m_pObj->m_pImpIPolyline->ColorGet(POLYLINECOLOR_LINE, &cr);
    return cr;
    }

STDMETHODIMP_(void) CImpIPolylineControl::put_LineStyle
    (short iStyle)
    {
    UINT    i;

    m_pObj->m_pImpIPolyline->LineStyleSet(iStyle, &i);
    return;
    }

STDMETHODIMP_(short) CImpIPolylineControl::get_LineStyle(void)
    {
    UINT    iStyle;

    m_pObj->m_pImpIPolyline->LineStyleGet(&iStyle);
    return (short)iStyle;
    }

STDMETHODIMP CImpIPolylineControl::Clear(void)
    {
    return m_pObj->m_pImpIPolyline->New();
    }

STDMETHODIMP CImpIPolylineControl::RemoveLastPoint(void)
    {
    return m_pObj->m_pImpIPolyline->Undo();
    }






//IOleControl interface implementation

/*
 * CImpIOleControl::CImpIOleControl
 * CImpIOleControl::~CImpIOleControl
 *
 * Parameters (Constructor):
 *  pObj            PCPolyline of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleControl::CImpIOleControl(PCPolyline pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIOleControl::~CImpIOleControl(void)
    {
    return;
    }



/*
 * CImpIOleControl::QueryInterface
 * CImpIOleControl::AddRef
 * CImpIOleControl::Release
 */

STDMETHODIMP CImpIOleControl::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIOleControl::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIOleControl::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIOleControl::GetControlInfo
 *
 * Purpose:
 *  Fills a CONTROLINFO structure containing information about
 *  the controls mnemonics and other behavioral aspects.
 *
 * Parameters:
 *  pCI             LPCONTROLINFO to the structure to fill
 */

STDMETHODIMP CImpIOleControl::GetControlInfo(LPCONTROLINFO pCI)
    {
    if (NULL==pCI)
        return ResultFromScode(E_INVALIDARG);

    *pCI=m_pObj->m_ctrlInfo;
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIOleControl::OnMnemonic
 *
 * Purpose:
 *  Notifies the control that a mnemonic was activated.
 *
 * Parameters:
 *  pMsg            LPMSG containing the message that matches one of
 *                  the control's mnemonics.  The control uses this
 *                  to distinguish which mnemonic was pressed.
 */

STDMETHODIMP CImpIOleControl::OnMnemonic(LPMSG pMsg)
    {
    //No mnemonics
    return NOERROR;
    }





/*
 * CImpIOleControl::OnAmbientPropertyChange
 *
 * Purpose:
 *  Notifies the control that one or more of the container's ambient
 *  properties changed.
 *
 * Parameters:
 *  dispID          DISPID identifying the property, which can
 *                  be DISPID_UNKNOWN indicating that more than
 *                  one changed.
 */

STDMETHODIMP CImpIOleControl::OnAmbientPropertyChange(DISPID dispID)
    {
    /*
     * We detect any change in UIDead or ShowHatching.  Changes
     * in container colors do not affect us as we only use those
     * for initial values.
     */

    switch (dispID)
        {
        case DISPID_UNKNOWN:
            m_pObj->AmbientsInitialize(INITAMBIENT_SHOWHATCHING
                | INITAMBIENT_UIDEAD);
            break;

        case DISPID_AMBIENT_SHOWHATCHING:
            m_pObj->AmbientsInitialize(INITAMBIENT_SHOWHATCHING);
            break;

        case DISPID_AMBIENT_UIDEAD:
            m_pObj->AmbientsInitialize(INITAMBIENT_UIDEAD);
            break;
        }

    return NOERROR;
    }




/*
 * CImpIOleControl::FreezeEvents
 *
 * Purpose:
 *  Instructs the control to stop firing events or to continue
 *  firing them.
 *
 * Parameters:
 *  fFreeze         BOOL indicating to freeze (TRUE) or thaw (FALSE)
 *                  events from this control.
 */

STDMETHODIMP CImpIOleControl::FreezeEvents(BOOL fFreeze)
    {
    m_pObj->m_fFreezeEvents=fFreeze;
    return NOERROR;
    }






//CAdviseRouter class implementation
/*
 * CAdviseRouter::CAdviseRouter
 * CAdviseRouter::~CAdviseRouter
 *
 * Constructor Parameters:
 *  pIDispatch      IDispatch * to which we route notifications.
 *  pObj            PCPolyline to the control itself.
 */

CAdviseRouter::CAdviseRouter(IDispatch *pIDispatch
    , PCPolyline pObj)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pIDispatch=pIDispatch;
    return;
    }


CAdviseRouter::~CAdviseRouter(void)
    {
    ReleaseInterface(m_pIDispatch);
    return;
    }




/*
 * CAdviseRouter::QueryInterface
 * CAdviseRouter::AddRef
 * CAdviseRouter::Release
 *
 * Purpose:
 *  IUnknown members for this IPolylineAdviseSink implementations.
 */

STDMETHODIMP CAdviseRouter::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IPolylineAdviseSink10==riid)
        {
        *ppv=this;
        AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CAdviseRouter::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CAdviseRouter::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }




/*
 * CAdviseRouter::OnPointChange
 * CAdviseRouter::OnSizeChange
 * CAdviseRouter::OnColorChange
 * CAdviseRouter::OnLineStyleChange
 *
 * Purpose:
 *  Invokes the same member in the IDispatch pointer we hold.
 */

STDMETHODIMP_(void) CAdviseRouter::OnPointChange(void)
    {
    Invoke(EVENT_ONPOINTCHANGE);
    return;
    }

STDMETHODIMP_(void) CAdviseRouter::OnSizeChange(void)
    {
    Invoke(EVENT_ONSIZECHANGE);
    return;
    }


STDMETHODIMP_(void) CAdviseRouter::OnColorChange(void)
    {
    Invoke(EVENT_ONCOLORCHANGE);
    return;
    }


STDMETHODIMP_(void) CAdviseRouter::OnLineStyleChange(void)
    {
    Invoke(EVENT_ONLINESTYLECHANGE);
    return;
    }




/*
 * CAdviseRouter::Invoke
 *
 * Purpose:
 *  Calls IDispatch::Invoke for any of the events we handle.
 *  None of these have any arguments.
 *
 * Parameters:
 *  dispID          DISPID of the event to fire.
 *
 * Return Value:
 *  None
 */

void CAdviseRouter::Invoke(DISPID dispID)
    {
    DISPPARAMS  dp;
    VARIANT     va;

    if (m_pObj->m_fFreezeEvents)
        return;

    m_pIDispatch->Invoke(dispID, IID_NULL
        , LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp
        , &va, NULL, NULL);

    return;
    }
