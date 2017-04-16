//=--------------------------------------------------------------------------=
// CirclCtl.H
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for the CircleCo control.
//
#ifndef _CIRCLECOCONTROL_H_
#define _CIRCLECOCONTROL_H_

#include "IPServer.H"
#include "CtrlObj.H"
#include "CircleCoInterfaces.H"
#include "Dispids.H"
#include "Designer.H"

//UNDONE: remove this
//[10/8/96, IvoSa] #include "ObjExt.H"


// Global Object Name:
//
extern char g_pszWhatAmI [];    

// Global TypeInfo pointer:
//
extern ITypeInfo * g_pTypeInfo;



// The structure which will hold the information about each circle we are
// adding.

typedef struct tagCIRCLEINFO {
    // ambient position of the circle in our view
    long lLeft;
    long lTop;
    long lRight;
    long lBottom;
    long lCX;
    long lCY;
    IUnknown* pCircle;
    // whether we actually have the circle: all other parameters are invalid if this
    // is false
    BOOL bHaveIt;   
    BSTR bstrName; 
    COLOR_TYPE CV;
    // Necessary to be notified of changes in the circle's properties
    IConnectionPoint *pCP;
    IPropertyNotifySink *pPNS;
    DWORD dwCookie;
    
} CIRCLEINFO;

#define MAXCIRCLES 10
#define AREASIZE   1000
#define CIRCLERADIUS 100


typedef struct tagCIRCLECOCTLSTATE {

    // base class type information

    IServiceProvider *pServiceProvider;
    // our host's service provider

    // our dynamic co class
    ICreateTypeInfo2 *pctiCoClass;

    // our dynamic interface
    ICreateTypeInfo2 *pRuntimeDispinterface;

    // the typeinfo of a circle, cached for efficiency
    ITypeInfo        *pCircleTI;

    BOOL              bUserMode;

    // dynamic typeinfo information

    GUID guidTypeLib;
    GUID guidTypeInfo;
    DWORD dwTICookie;
    
    // Current number of circles
    DWORD dwCircleNum;   
    
    // Monotonically increasing count of circles to be used in deriving their
    // default names
    DWORD dwCircleCount;

    // The actual array of circles
    CIRCLEINFO rgCircles[MAXCIRCLES];

    // The currently selected circle or -1 for none
    int iSelectedCircle;

    // The last valid view rectangle of our window
    RECTL rcLastView;

    // The type of brush we will use to draw our circles with
    HATCH_TYPE hv;
    
} CIRCLECOCTLSTATE;



//=--------------------------------------------------------------------------=
// CCircleCoControl
//=--------------------------------------------------------------------------=
// our control.
//
class CCircleCoControl : 
    public COleControl, 
    public IDispatch, 
    public IProvideDynamicClassInfo,
    public ISelectionContainer,
    public HCircleCo
{

public:
    // IUnknown methods
    //
    DECLARE_STANDARD_UNKNOWN();

    // IDispatch methods
    // we have to implement our own since we're not dual interface based
    //
    STDMETHOD(GetTypeInfoCount)(UINT *);
    STDMETHOD(GetTypeInfo)(UINT, LCID, ITypeInfo **);
    STDMETHOD(GetIDsOfNames)(REFIID, OLECHAR **, UINT, LCID, DISPID *);
    STDMETHOD(Invoke)(DISPID, REFIID, LCID, WORD, DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *);



    // ISelectionContainer
    STDMETHOD(CountObjects)(THIS_ DWORD dwFlags, ULONG * pc);
    STDMETHOD(GetObjects)(THIS_ DWORD dwFlags, ULONG cObjects, IUnknown **apUnkObjects);
    STDMETHOD(SelectObjects)(THIS_ ULONG cSelect,IUnknown **apUnkSelect, DWORD dwFlags);



    // IProvideClassInfo methods
    //
    STDMETHOD(GetClassInfo)(LPTYPEINFO * ppTI);

    // IProvideDynamicClassInfo methods
    //
    STDMETHOD(GetDynamicClassInfo)(ITypeInfo ** ppTI, DWORD * pdwCookie);
    STDMETHOD(FreezeShape)(void);

    /* HCircleCo methods */
    // We implement these so that we get to use OA to do our standard
    // dispatch work for us
    STDMETHOD(put_BrushType)(THIS_ HATCH_TYPE hv);
    STDMETHOD(get_BrushType)(THIS_ HATCH_TYPE FAR* hv);

    // OLE Control stuff follows:
    //
    BOOL InitializeNewState(void);
    CCircleCoControl(IUnknown *pUnkOuter);
    virtual ~CCircleCoControl();

    // static creation function.  all controls must have one of these!
    //
    static IUnknown *Create(IUnknown *);

protected:

    //          circlctl.cpp
    void AddDeleteCircle(DWORD, DWORD);
    void DeleteCircle(int);
    int GetIndexFromName(LPSTR);
    int GetIndexFromCoords(DWORD,DWORD);
    void TryToFireEvent(DWORD, DWORD);
    void SelectCircle(DWORD, DWORD);
    void TryToViewCode(DWORD, DWORD);
    void MaybeSelectionChanged(int, BOOL);
    HRESULT CreateObject(int);
    void BeforeDestroyWindow(void);
    BOOL AfterCreateWindow(void);

    //          circti.cpp
    HRESULT CreateRuntimeTypeInfo();
    HRESULT CreateInterfaces(ICreateTypeLib *, ICreateTypeInfo **, ITypeInfo **);
    HRESULT AddToTypeInfo(int);
    void DeleteFromTypeInfo(int);

    //          circsel.cpp
    HRESULT AttachSink(int);
    void DetachSink(int);
    HRESULT CallOnSelectChange(ISelectionContainer *);

public:

    // Public so that the selection prop update mechanism can get at them
    BOOL InUserMode(void);
    void OnChangedColor(int);
    void OnChangedName(int);

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
    virtual void    AmbientPropertyChanged(DISPID);

    // private state information.
    //
    CIRCLECOCTLSTATE m_state;
};


DEFINE_CONTROLOBJECT(CircleCo,
    &CLSID_CircleCo,
    "CircleCoCtl",
    CCircleCoControl::Create,
    1,
    &DIID_DCircleCo,
    "",
    &DIID_DCircleCoEvents,
    OLEMISC_SETCLIENTSITEFIRST|OLEMISC_ACTIVATEWHENVISIBLE|OLEMISC_RECOMPOSEONRESIZE|OLEMISC_CANTLINKINSIDE|OLEMISC_INSIDEOUT,
    0,                              // no IPointerInactive policy by default
    RESID_TOOLBOX_BITMAP,
    "CircleCoWndClass",
    0,
    NULL,
    0,
    NULL);



#endif // _CIRCLECOCONTROL_H_
