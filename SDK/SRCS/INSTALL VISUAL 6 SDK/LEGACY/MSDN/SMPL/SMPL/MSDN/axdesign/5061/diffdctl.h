//=--------------------------------------------------------------------------=
// DifferentDesignerCtl.H
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for the DifferentDesigner control.
//
#ifndef _DIFFERENTDESIGNERCONTROL_H_

#include "IPServer.H"
#include "CtrlObj.H"
#include "DiffDsgrInterfaces.H"
#include "Dispids.H"

#include <designer.H>

//=--------------------------------------------------------------------------=
// CDifferentDesignerControl
//=--------------------------------------------------------------------------=
// our control.
//
class CDifferentDesignerControl : public COleControl, public IDifferentDesigner,
                                  public ISupportErrorInfo,
                                  public IActiveDesigner  {

  public:
    // IUnknown methods
    //
    DECLARE_STANDARD_UNKNOWN();

    // IDispatch methods
    //
    DECLARE_STANDARD_DISPATCH();

    // ISupportErrorInfo methods
    //
    DECLARE_STANDARD_SUPPORTERRORINFO();

    // IActiveDesigner methods
    //
    STDMETHOD(GetRuntimeClassID)(CLSID *pclsid);
    STDMETHOD(GetRuntimeMiscStatusFlags)(DWORD *dwMiscFlags);
    STDMETHOD(QueryPersistenceInterface)(REFIID riid);
//[10/8/96, IvoSa]    STDMETHOD(SaveRuntimeState)(REFIID riid, void *pObj);
	STDMETHOD(SaveRuntimeState)(REFIID riidPersist, REFIID riidObjStgMed, void *pObjStgMed);
    STDMETHOD(GetExtensibilityObject)(IDispatch **ppvObjOut);

    // IDifferentDesigner methods
    //
    STDMETHOD(get_MyString)(BSTR * pbstrMyString);
    STDMETHOD(put_MyString)(BSTR bstrMyString);
    STDMETHOD_(void, AboutBox)(THIS);

    // OLE Control stuff follows:
    //
    CDifferentDesignerControl(IUnknown *pUnkOuter);
    virtual ~CDifferentDesignerControl();

    // static creation function.  all controls must have one of these!
    //
    static IUnknown *Create(IUnknown *);

  private:
    // overridables that the control must implement.
    //
    STDMETHOD(LoadBinaryState)(IStream *pStream);
    STDMETHOD(SaveBinaryState)(IStream *pStream);
    STDMETHOD(LoadTextState)(IPropertyBag *pPropertyBag, IErrorLog *pErrorLog);
    STDMETHOD(SaveTextState)(IPropertyBag *pPropertyBag, BOOL fWriteDefault);
    STDMETHOD(OnDraw)(DWORD dvAspect, HDC hdcDraw, LPCRECTL prcBounds, LPCRECTL prcWBounds, HDC hicTargetDev, BOOL fOptimize);
    virtual LRESULT WindowProc(UINT msg, WPARAM wParam, LPARAM lParam);
    virtual BOOL    RegisterClassData(void);

    virtual HRESULT InternalQueryInterface(REFIID, void **);
    virtual BOOL    BeforeCreateWindow(DWORD *pdwWindowStyle, DWORD *pdwExWindowStyle, LPSTR pszWindowTitle);
    HRESULT SaveStandardState(IStream *pStream);

    // private state information.
    //
    BSTR m_bstrMyString;
};


// TODO: if you have an array of verbs, then add an extern here with the name
//       of it, so that you can include it in the DEFINE_CONTROLOBJECT.
//       ie.  extern VERBINFO m_DifferentDesignerCustomVerbs [];
//
extern const GUID    *rgDifferentDesignerPropPages [];
DEFINE_CONTROLOBJECT(DifferentDesigner,
    &CLSID_DifferentDesigner,
    "DifferentDesignerCtl",
    CDifferentDesignerControl::Create,
    1,
    &IID_IDifferentDesigner,
    "DifferentDesigner.HLP",
    &DIID_DDifferentDesignerEvents,
    OLEMISC_SETCLIENTSITEFIRST|OLEMISC_ACTIVATEWHENVISIBLE|OLEMISC_RECOMPOSEONRESIZE|OLEMISC_CANTLINKINSIDE|OLEMISC_INSIDEOUT,
    0,                              // no IPointerInactive policy by default
    RESID_TOOLBOX_BITMAP,
    "DifferentDesignerWndClass",
    1,
    rgDifferentDesignerPropPages,
    0,
    NULL);



#define _DIFFERENTDESIGNERCONTROL_H_
#endif // _DIFFERENTDESIGNERCONTROL_H_
