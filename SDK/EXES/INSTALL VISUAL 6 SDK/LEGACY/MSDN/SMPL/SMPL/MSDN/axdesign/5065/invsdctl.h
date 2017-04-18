//=--------------------------------------------------------------------------=
// InvisibleDesignerCtl.H
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for the InvisibleDesigner control.
//
#ifndef _INVISIBLEDESIGNERCONTROL_H_

#include "IPServer.H"
#include "CtrlObj.H"
#include "InvsDsgrInterfaces.H"
#include "Dispids.H"

#include <Designer.H>


//=--------------------------------------------------------------------------=
// CInvisibleDesignerControl
//=--------------------------------------------------------------------------=
// our control.
//
class CInvisibleDesignerControl : public COleControl, public IInvisibleDesigner,
                                  public ISupportErrorInfo, public IActiveDesigner {

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

    // IInvisibleDesigner methods
    //
    STDMETHOD(get_MyString)(BSTR * pbstrMyString);
    STDMETHOD(put_MyString)(BSTR bstrMyString);
    STDMETHOD_(void, AboutBox)(THIS);

    // IActiveDesigner methods
    //
    STDMETHOD(GetRuntimeClassID)(CLSID *pclsid);
    STDMETHOD(GetRuntimeMiscStatusFlags)(DWORD *dwMiscFlags);
    STDMETHOD(QueryPersistenceInterface)(REFIID riid);
//[10/8/96, IvoSa]    STDMETHOD(SaveRuntimeState)(REFIID riid, void *pObj);
	STDMETHOD(SaveRuntimeState)(REFIID riidPersist, REFIID riidObjStgMed, void *pMedium);
    STDMETHOD(GetExtensibilityObject)(IDispatch **ppvObjOut);

    // OLE Control stuff follows:
    //
    CInvisibleDesignerControl(IUnknown *pUnkOuter);
    virtual ~CInvisibleDesignerControl();

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
//       ie.  extern VERBINFO m_InvisibleDesignerCustomVerbs [];
//
extern const GUID    *rgInvisibleDesignerPropPages [];
DEFINE_CONTROLOBJECT(InvisibleDesigner,
    &CLSID_InvisibleDesigner,
    "InvisAtRunTest",
    CInvisibleDesignerControl::Create,
    1,
    &IID_IInvisibleDesigner,
    "InvisibleDesigner.HLP",
    &DIID_DInvisibleDesignerEvents,
    OLEMISC_SETCLIENTSITEFIRST|OLEMISC_ACTIVATEWHENVISIBLE|OLEMISC_RECOMPOSEONRESIZE|OLEMISC_CANTLINKINSIDE|OLEMISC_INSIDEOUT|OLEMISC_INVISIBLEATRUNTIME,
    0,                              // no IPointerInactive policy by default
    RESID_TOOLBOX_BITMAP,
    "InvisibleDesignerWndClass",
    1,
    rgInvisibleDesignerPropPages,
    0,
    NULL);



#define _INVISIBLEDESIGNERCONTROL_H_
#endif // _INVISIBLEDESIGNERCONTROL_H_

