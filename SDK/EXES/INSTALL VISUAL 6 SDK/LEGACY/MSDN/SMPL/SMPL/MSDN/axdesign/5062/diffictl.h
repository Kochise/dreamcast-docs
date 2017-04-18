//=--------------------------------------------------------------------------=
// DifferentInstanceCtl.H
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for the DifferentInstance control.
//
#ifndef _DIFFERENTINSTANCECONTROL_H_

#include "IPServer.H"
#include "CtrlObj.H"
#include "DiffInstInterfaces.H"
#include "Dispids.H"

//=--------------------------------------------------------------------------=
// CDifferentInstanceControl
//=--------------------------------------------------------------------------=
// our control.
//
class CDifferentInstanceControl : public COleControl, public IDifferentInstance, public ISupportErrorInfo {

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

    // IDifferentInstance methods
    //
    STDMETHOD(get_MyString)(BSTR * pbstrMyString);
    STDMETHOD(put_MyString)(BSTR bstrMyString);
    STDMETHOD_(void, AboutBox)(void);

    // OLE Control stuff follows:
    //
    CDifferentInstanceControl(IUnknown *pUnkOuter);
    virtual ~CDifferentInstanceControl();

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

    // private state information.
    //
    BSTR m_bstrMyString;
};


// TODO: if you have an array of verbs, then add an extern here with the name
//       of it, so that you can include it in the DEFINE_CONTROLOBJECT.
//       ie.  extern VERBINFO m_DifferentInstanceCustomVerbs [];
//
extern const GUID    *rgDifferentInstancePropPages [];
DEFINE_CONTROLOBJECT(DifferentInstance,
    &CLSID_DifferentInstance,
    "DifferentInstanceCtl",
    CDifferentInstanceControl::Create,
    1,
    &IID_IDifferentInstance,
    "DifferentInstance.HLP",
    &DIID_DDifferentInstanceEvents,
    OLEMISC_SETCLIENTSITEFIRST|OLEMISC_ACTIVATEWHENVISIBLE|OLEMISC_RECOMPOSEONRESIZE|OLEMISC_CANTLINKINSIDE|OLEMISC_INSIDEOUT,
    0,                              // no IPointerInactive policy by default
    RESID_TOOLBOX_BITMAP,
    "DifferentInstanceWndClass",
    1,
    rgDifferentInstancePropPages,
    0,
    NULL);



#define _DIFFERENTINSTANCECONTROL_H_
#endif // _DIFFERENTINSTANCECONTROL_H_
