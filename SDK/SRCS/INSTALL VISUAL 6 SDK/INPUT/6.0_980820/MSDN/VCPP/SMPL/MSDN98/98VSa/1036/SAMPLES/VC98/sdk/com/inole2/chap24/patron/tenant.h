/*
 * TENANT.H
 * Patron Chapter 24
 *
 * Definitions and function prototypes for the CTenant class
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _TENANT_H_
#define _TENANT_H_


class CImpIOleClientSite : public IOleClientSite
    {
    protected:
        ULONG               m_cRef;
        class CTenant      *m_pTen;
        LPUNKNOWN           m_pUnkOuter;

    public:
        CImpIOleClientSite(class CTenant *, LPUNKNOWN);
        ~CImpIOleClientSite(void);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP SaveObject(void);
        STDMETHODIMP GetMoniker(DWORD, DWORD, LPMONIKER *);
        STDMETHODIMP GetContainer(LPOLECONTAINER *);
        STDMETHODIMP ShowObject(void);
        STDMETHODIMP OnShowWindow(BOOL);
        STDMETHODIMP RequestNewObjectLayout(void);
    };

typedef CImpIOleClientSite *PCImpIOleClientSite;



class CImpIAdviseSink : public IAdviseSink
    {
    protected:
        ULONG               m_cRef;
        class CTenant      *m_pTen;
        LPUNKNOWN           m_pUnkOuter;

    public:
        CImpIAdviseSink(class CTenant *, LPUNKNOWN);
        ~CImpIAdviseSink(void);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP_(void)  OnDataChange(LPFORMATETC, LPSTGMEDIUM);
        STDMETHODIMP_(void)  OnViewChange(DWORD, LONG);
        STDMETHODIMP_(void)  OnRename(LPMONIKER);
        STDMETHODIMP_(void)  OnSave(void);
        STDMETHODIMP_(void)  OnClose(void);
    };


typedef CImpIAdviseSink *PCImpIAdviseSink;


class CImpIOleInPlaceSite : public IOleInPlaceSite
    {
    protected:
        ULONG               m_cRef;
        class CTenant      *m_pTen;
        LPUNKNOWN           m_pUnkOuter;

    public:
        CImpIOleInPlaceSite(class CTenant *, LPUNKNOWN);
        ~CImpIOleInPlaceSite(void);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetWindow(HWND *);
        STDMETHODIMP ContextSensitiveHelp(BOOL);
        STDMETHODIMP CanInPlaceActivate(void);
        STDMETHODIMP OnInPlaceActivate(void);
        STDMETHODIMP OnUIActivate(void);
        STDMETHODIMP GetWindowContext(LPOLEINPLACEFRAME *
                        , LPOLEINPLACEUIWINDOW *, LPRECT, LPRECT
                        , LPOLEINPLACEFRAMEINFO);
        STDMETHODIMP Scroll(SIZE);
        STDMETHODIMP OnUIDeactivate(BOOL);
        STDMETHODIMP OnInPlaceDeactivate(void);
        STDMETHODIMP DiscardUndoState(void);
        STDMETHODIMP DeactivateAndUndo(void);
        STDMETHODIMP OnPosRectChange(LPCRECT);
    };

typedef CImpIOleInPlaceSite *PCImpIOleInPlaceSite;


//CHAPTER24MOD
class CImpIOleControlSite : public IOleControlSite
    {
    protected:
        ULONG           m_cRef;
        class CTenant  *m_pTen;
        LPUNKNOWN       m_pUnkOuter;

    public:
        CImpIOleControlSite(class CTenant *, LPUNKNOWN);
        ~CImpIOleControlSite(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP OnControlInfoChanged(void);
        STDMETHODIMP LockInPlaceActive(BOOL);
        STDMETHODIMP GetExtendedControl(LPDISPATCH *);
        STDMETHODIMP TransformCoords(POINTL *, POINTF *, DWORD);
        STDMETHODIMP TranslateAccelerator(LPMSG, DWORD);
        STDMETHODIMP OnFocus(BOOL);
        STDMETHODIMP ShowPropertyFrame(void);
    };

typedef class CImpIOleControlSite *PCImpIOleControlSite;


//This IDispatch implements Ambient properties
class CImpIDispatch : public IDispatch
    {
    protected:
        ULONG           m_cRef;
        class CTenant  *m_pTen;
        LPUNKNOWN       m_pUnkOuter;

    public:
        CImpIDispatch(class CTenant *, LPUNKNOWN);
        ~CImpIDispatch(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetTypeInfoCount(UINT *);
        STDMETHODIMP GetTypeInfo(UINT, LCID, ITypeInfo **);
        STDMETHODIMP GetIDsOfNames(REFIID, OLECHAR **, UINT
            , LCID, DISPID *);
        STDMETHODIMP Invoke(DISPID, REFIID, LCID, USHORT
            , DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *);
    };

typedef class CImpIDispatch *PCImpIDispatch;


//Events IDispatch created once for each outgoing event set.
class CDispatchEvents : public IDispatch
    {
    protected:
        ULONG           m_cRef;
        class CTenant  *m_pTen;

    public:
        CDispatchEvents(class CTenant *);
        ~CDispatchEvents(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetTypeInfoCount(UINT *);
        STDMETHODIMP GetTypeInfo(UINT, LCID, ITypeInfo **);
        STDMETHODIMP GetIDsOfNames(REFIID, OLECHAR **, UINT
            , LCID, DISPID *);
        STDMETHODIMP Invoke(DISPID, REFIID, LCID, USHORT
            , DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *);
    };

typedef class CDispatchEvents *PCDispatchEvents;


//End CHAPTER24MOD



/*
 * Tenant class describing an individual piece of data in a page.
 * It knows where it sits, what object is inside of it, and what
 * its idenitifer is such that it can find it's storage within a
 * page.
 */

//Patron Objects clipboard format
typedef struct tagPATRONOBJECT
    {
    POINTL      ptl;        //Location of object
    POINTL      ptlPick;    //Pick point from drag-drop operation
    SIZEL       szl;        //Extents of object (absolute)
    FORMATETC   fe;         //Actual object format
    } PATRONOBJECT, *PPATRONOBJECT;



//Values for hit-testing, drawing, and resize-tracking tenants
#define CXYHANDLE       5

//Tenant types (not persistent, but determined at load time)
typedef enum
    {
    TENANTTYPE_NULL=0,
    TENANTTYPE_STATIC,
    TENANTTYPE_EMBEDDEDOBJECT,
    TENANTTYPE_EMBEDDEDFILE,
    TENANTTYPE_EMBEDDEDOBJECTFROMDATA,
    TENANTTYPE_LINKEDOBJECT,
    TENANTTYPE_LINKEDFILE,
    TENANTTYPE_LINKEDOBJECTFROMDATA
    } TENANTTYPE, *PTENANTTYPE;


//State flags
//CHAPTER24MOD
//Switched #defines to an enum
enum
    {
    TENANTSTATE_DEFAULT =0x00000000,
    TENANTSTATE_SELECTED=0x00000001,
    TENANTSTATE_OPEN    =0x00000002,
    TENANTSTATE_SHOWTYPE=0x00000004,

    //New ones for controls.
    TENANTSTATE_CONTROL     =0x00000100,
    TENANTSTATE_EVENTS      =0x00000200,
    TENANTSTATE_BUTTON      =0x00000400,
    TENANTSTATE_LABEL       =0x00000800,
    TENANTSTATE_DEFBUTTON   =0x00001000,
    TENANTSTATE_CANCELBUTTON=0x00002000
    };

//To mask off non-control flags
#define STATEMASK_CONTROLS 0xFFFFFF00

//End CHAPTER24MOD

/*
 * Persistent information we need to save for each tenant, which is
 * done in the tenant list instead of with each tenant.  Since this
 * is a small structure it's best not to blow another stream for it
 * (overhead).
 */
typedef struct tagTENANTINFO
    {
    DWORD       dwID;
    RECTL       rcl;
    FORMATETC   fe;             //Excludes ptd
    short       fSetExtent;     //Call IOleObject::SetExtent on Run
    } TENANTINFO, *PTENANTINFO;


//CHAPTER24MOD
/*
 * Event handling constructs:  EVENTACTION is the type of
 * action to execute on an event.  EVENTMAP is an element of
 * an array to hold event mappings.
 */

typedef enum
    {
    ACTION_NONE=-1,
    ACTION_BEEPDEFAULT=MB_OK,
    ACTION_BEEPASTERISK=MB_ICONASTERISK,
    ACTION_BEEPEXCLAMATION=MB_ICONEXCLAMATION,
    ACTION_BEEPHAND=MB_ICONHAND,
    ACTION_BEEPQUESTION=MB_ICONQUESTION,
    ACTION_TAILING=-2
    } EVENTACTION;


typedef struct tagEVENTMAP
    {
    DISPID      id;             //Event ID
    EVENTACTION iAction;        //Action to take
    BSTR        bstrName;       //Event name (function only)
    } EVENTMAP, *PEVENTMAP;


class CEventMap
    {
    public:
        UINT            m_cEvents;
        LPTYPEINFO      m_pITypeInfo;
        PEVENTMAP       m_pEventMap;

    public:
        CEventMap(LPTYPEINFO);
        ~CEventMap(void);

        BOOL            Init(void);
        BOOL            Set(DISPID, EVENTACTION);
        EVENTACTION     Get(DISPID);
        void            Serialize(LPSTREAM);
        void            Deserialize(LPSTREAM);
    };

typedef CEventMap *PCEventMap;

//Events stream in the object storage
#define SZEVENTSSTREAM  OLETEXT("\003Event Mappings")

//End CHAPTER24MOD



class CTenant : public IUnknown
    {
    friend CImpIOleClientSite;
    friend CImpIAdviseSink;
    friend CImpIOleInPlaceSite;

    //CHAPTER24MOD
    friend CImpIOleControlSite;
    friend CImpIDispatch;

    friend CDispatchEvents;
    //End CHAPTER24MOD

    private:
        HWND            m_hWnd;         //Pages window
        DWORD           m_dwID;         //Persistent DWORD ID
        DWORD           m_cOpens;       //Count calls to Open

        BOOL            m_fInitialized; //Something here?
        LPUNKNOWN       m_pObj;         //The object here
        LPSTORAGE       m_pIStorage;    //Sub-storage for tenant

        FORMATETC       m_fe;           //Used to create the object
        DWORD           m_dwState;      //State flags
        RECTL           m_rcl;          //Space of this object
        CLSID           m_clsID;        //Object class (for statics)
        BOOL            m_fSetExtent;   //Call SetExtent on next run

        class CPages   *m_pPG;          //Pages window

        TENANTTYPE      m_tType;            //Type identifier
        ULONG           m_cRef;             //We're an object now
        LPOLEOBJECT     m_pIOleObject;      //IOleObject on m_pObj
        LPVIEWOBJECT2   m_pIViewObject2;    //IViewObject2 on m_pObj
        ULONG           m_grfMisc;          //OLEMISC flags
        BOOL            m_fRepaintEnabled;  //No redundant paints

        //Our interfaces
        PCImpIOleClientSite m_pImpIOleClientSite;
        PCImpIAdviseSink    m_pImpIAdviseSink;

        LPMONIKER       m_pmk;          //Relative moniker
        LPMONIKER       m_pmkFile;      //Container document moniker

        PCImpIOleInPlaceSite m_pImpIOleIPSite; //Our interface
        LPOLEINPLACEOBJECT   m_pIOleIPObject;  //The object
        RECT                 m_rcPos;          //Last object rect
        BOOL                 m_fInRectSet;     //Prevent reentrancy

        //CHAPTER24MOD
        PCImpIOleControlSite    m_pImpIOleControlSite; //Implemented
        PCImpIDispatch          m_pImpIDispatch;       //Implemented

        PCDispatchEvents        m_pDispEvents;      //Event Sink
        DWORD                   m_dwConnEvents;
        IID                     m_iidEvents;
        PCEventMap              m_pEventMap;

        //Control interfaces
        LPOLECONTROL        m_pIOleControl;      //Used
        LPDISPATCH          m_pIDispatchControl; //Used

        //Ambient properties
        OLE_COLOR           m_clrBack;
        OLE_COLOR           m_clrFore;
        IFontDisp          *m_pIFont;       //Copy from CPages
        LCID                m_lcid;
        BOOL                m_fDesignMode;
        BOOL                m_fUIDead;
        BOOL                m_fHatchHandles;

        //Other state information
        BOOL                m_fHaveControlInfo;
        CONTROLINFO         m_ctrlInfo;
        ULONG               m_cLockInPlace;
        BOOL                m_fPendingDeactivate;
        //End CHAPTER24MOD


    /*
     * This flag is used exculsively by the implementation of
     * IOleUILinkContainer on the page we're in for the Links
     * Dialog. Since we never use it ourselves, public here
     * is no big deal.
     */
    public:
        BOOL            m_fLinkAvail;

    protected:
        BOOL    ObjectInitialize(LPUNKNOWN, LPFORMATETC, DWORD);
        HRESULT CreateStatic(LPDATAOBJECT, LPFORMATETC
            , LPUNKNOWN *);

        //CHAPTER24MOD
        BOOL    ControlInitialize(void);
        //End CHAPTER24MOD

    public:
        CTenant(DWORD, HWND, CPages *);
        ~CTenant(void);

        //Gotta have an IUnknown for delegation
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        DWORD       GetID(void);
        UINT        GetStorageName(LPOLESTR);
        void        StorageGet(LPSTORAGE *);
        UINT        Create(TENANTTYPE, LPVOID, LPFORMATETC, PPOINTL
                        , LPSIZEL, LPSTORAGE, PPATRONOBJECT, DWORD);
        BOOL        Load(LPSTORAGE, PTENANTINFO);
        void        GetInfo(PTENANTINFO);
        BOOL        Open(LPSTORAGE);
        void        Close(BOOL);
        BOOL        Update(void);
        void        Destroy(LPSTORAGE);

        void        Select(BOOL, BOOL);
        void        ShowAsOpen(BOOL);
        void        ShowYourself(void);
        void        AddVerbMenu(HMENU, UINT);
        TENANTTYPE  TypeGet(void);
        void        CopyEmbeddedObject(LPDATAOBJECT, LPFORMATETC
                        , PPOINTL);
        void        ShowObjectType(BOOL);
        void        CopyLinkedObject(LPDATAOBJECT, LPFORMATETC
                        , PPOINTL);
        void        NotifyOfRename(LPTSTR, LPMONIKER, LPMONIKER);
        BOOL        Activate(LONG, LPMSG);

        void        Draw(HDC, DVTARGETDEVICE *, HDC, int, int
                        , BOOL, BOOL);
        void        Repaint(void);
        void        Invalidate(void);

        void        ObjectClassFormatAndIcon(LPCLSID, LPWORD
                        , LPTSTR *, HGLOBAL *, LPTSTR *);
        BOOL        SwitchOrUpdateAspect(HGLOBAL, BOOL);
        void        EnableRepaint(BOOL);

        BOOL        FIsSelected(void);
        BOOL        ConvertToStatic(void);

        void        ObjectGet(LPUNKNOWN *);
        void        FormatEtcGet(LPFORMATETC, BOOL);
        void        SizeGet(LPSIZEL, BOOL);
        void        SizeSet(LPSIZEL, BOOL, BOOL);
        void        RectGet(LPRECTL, BOOL);
        void        RectSet(LPRECTL, BOOL, BOOL);

        void        DeactivateInPlaceObject(BOOL);
        void        UpdateInPlaceObjectRects(LPCRECT, BOOL);
        HWND        ObjectWindow(void);

        //CHAPTER24MOD
        void        ToggleDesignMode(BOOL);
        void        ToggleUIDead(BOOL);
        void        ToggleHatchHandles(BOOL);
        PCEventMap  EventMap(void);
        DWORD       GetControlFlags();
        BOOL        TryMnemonic(LPMSG);
        void        AmbientChange(DISPID);
        //End CHAPTER24MOD
    };


typedef CTenant *PCTenant;

//Return codes for Create
#define CREATE_FAILED               0
#define CREATE_GRAPHICONLY          1
#define CREATE_PLACEDOBJECT         2


//CHAPTER24MOD
//Helper functions in CONNECT.CPP

BOOL InterfaceConnect(LPUNKNOWN, REFIID, LPUNKNOWN, LPDWORD);
BOOL InterfaceDisconnect(LPUNKNOWN, REFIID, LPDWORD);
BOOL ObjectTypeInfo(LPUNKNOWN, LPTYPEINFO *);
BOOL ObjectTypeInfoEvents(LPUNKNOWN, LPTYPEINFO *);
BOOL ObjectEventsIID(LPUNKNOWN, IID *);

//End CHAPTER24MOD

#endif //_TENANT_H_
