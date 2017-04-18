//=--------------------------------------------------------------------------=
// ToDoCtl.H
//=--------------------------------------------------------------------------=
// Copyright 1995-1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for the ToDo control.
//
#ifndef _TODOCTL_H_

#include "IPServer.H"

// DOCOBJ: include CDocObj.H for DocObjects instead of CCtrlObj.
#include "CDocObj.H"                

#include "ToDoSvrIfc.H"
#include "Dispids.H"

typedef struct tagTODOCTLSTATE {

    // TODO: put state variables here, and probably get rid of fGarbage, unless
    // you have a real need for it
    //
    VARIANT_BOOL fGarbage;

} TODOCTLSTATE;

//=--------------------------------------------------------------------------=
// CToDoControl
//=--------------------------------------------------------------------------=
// our control.
//
// DOCOBJ: use CDocumentObject as the base class instead of COleControl or 
//         CInternetControl
//
class CToDoControl : public CDocumentObject, public IToDo, public ISupportErrorInfo {

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

    // IToDo methods
    //
    // TODO: copy over the method declarations from ToDoInterfaces.H
    //       don't forget to remove the PURE from them.
    //
    STDMETHOD_(void, AboutBox)(THIS);

    // OLE Control stuff follows:
    //
    CToDoControl(IUnknown *pUnkOuter);
    virtual ~CToDoControl();

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
    TODOCTLSTATE m_state;
};


// TODO: if you have an array of verbs, then add an extern here with the name
//       of it, so that you can include it in the DEFINE_DOCOBJECT.
//       ie.  extern VERBINFO m_ToDoCustomVerbs [];
//
extern const GUID    *rgToDoPropPages [];

// DOCOBJ: Use DEFINE_DOCOBJECT macro instead of DEFIND_CONTROL macro to 
//         set up information about the DocObject. The last 4 items are 
//         specific to DocObjects.
//
DEFINE_DOCOBJECT(ToDo,
    &CLSID_ToDo,
    "ToDoCtl",
    CToDoControl::Create,
    1,
    &IID_IToDo,
    "ToDo.HLP",
    &DIID_DToDoEvents,
    OLEMISC_SETCLIENTSITEFIRST|OLEMISC_ACTIVATEWHENVISIBLE|OLEMISC_RECOMPOSEONRESIZE|OLEMISC_CANTLINKINSIDE|OLEMISC_INSIDEOUT,
    0,
    RESID_TOOLBOX_BITMAP,
    "ToDoWndClass",
    1,
    rgToDoPropPages,
    0,
    NULL,
    DOCMISC_CANTOPENEDIT|DOCMISC_NOFILESUPPORT,     // dwDocMiscStatus
    FALSE,                                          // no IPrint support
    IDS_DEFAULTEXT,                                 // resource ID of default file extension
    IDS_FILEDESCRIPTION,                            // resource ID of file description
    );

#define _TODOCTL_H_
#endif // _TODOCTL_H_
