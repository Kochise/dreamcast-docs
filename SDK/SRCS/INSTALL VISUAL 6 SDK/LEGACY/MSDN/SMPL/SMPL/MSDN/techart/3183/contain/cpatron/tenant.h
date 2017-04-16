/*
 * TENANT.H
 * Patron Control Container
 *
 * Definitions and function prototypes for the CTenant class
 *
 * Copyright (c)1993-1994 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
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

typedef CImpIOleClientSite *PIMPIOLECLIENTSITE;



class CImpIAdviseSink : public IAdviseSink2
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
        STDMETHODIMP_(void)  OnLinkSrcChange(LPMONIKER);
    };


typedef CImpIAdviseSink *PIMPIADVISESINK;


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

typedef CImpIOleInPlaceSite *PIMPIOLEINPLACESITE;


//CONTROLMOD
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

typedef class CImpIOleControlSite *PIMPIOLECONTROLSITE;


//For property changes
class CImpIPropertyNotifySink : public IPropertyNotifySink
    {
    protected:
        ULONG           m_cRef;
        class CTenant  *m_pTen;
        LPUNKNOWN       m_pUnkOuter;

    public:
        CImpIPropertyNotifySink(class CTenant *, LPUNKNOWN);
        ~CImpIPropertyNotifySink(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP OnChanged(DISPID);
        STDMETHODIMP OnRequestEdit(DISPID);
    };

typedef class CImpIPropertyNotifySink *PIMPIPROPERTYNOTIFYSINK;


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
        STDMETHODIMP GetIDsOfNames(REFIID, TCHAR **, UINT
            , LCID, DISPID *);
        STDMETHODIMP Invoke(DISPID, REFIID, LCID, USHORT
            , DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *);
    };

typedef class CImpIDispatch *PIMPIDISPATCH;


//This IDispatch implements Events specific to the control
class CImpIDispatchEvents : public IDispatch
    {
    protected:
        ULONG           m_cRef;
        class CTenant  *m_pTen;
        LPUNKNOWN       m_pUnkOuter;

    public:
        CImpIDispatchEvents(class CTenant *, LPUNKNOWN);
        ~CImpIDispatchEvents(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetTypeInfoCount(UINT *);
        STDMETHODIMP GetTypeInfo(UINT, LCID, ITypeInfo **);
        STDMETHODIMP GetIDsOfNames(REFIID, TCHAR **, UINT
            , LCID, DISPID *);
        STDMETHODIMP Invoke(DISPID, REFIID, LCID, USHORT
            , DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *);
    };

typedef class CImpIDispatchEvents *PIMPIDISPATCHEVENTS;


//End CONTROLMOD



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
#define TENANTSTATE_DEFAULT      0x00000000
#define TENANTSTATE_SELECTED     0x00000001
#define TENANTSTATE_OPEN         0x00000002
#define TENANTSTATE_SHOWTYPE     0x00000004

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


//CONTROLMOD
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
#define SZEVENTSSTREAM  TEXT("\003Event Mappings")

//End CONTROLMOD



class CTenant : public IUnknown
    {
    friend CImpIOleClientSite;
    friend CImpIAdviseSink;
    friend CImpIOleInPlaceSite;

    //CONTROLMOD
    friend CImpIOleControlSite;
    friend CImpIPropertyNotifySink;
    friend CImpIDispatch;
    friend CImpIDispatchEvents;
    //End CONTROLMOD

    private:
        HWND            m_hWnd;         //Pages window
        DWORD           m_dwID;         //Persistent DWORD ID
        DWORD           m_cOpens;       //Count calls to FOpen

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

        //Our interfaces
        PIMPIOLECLIENTSITE  m_pIOleClientSite;
        PIMPIADVISESINK     m_pIAdviseSink;

        LPMONIKER       m_pmk;          //Relative moniker
        LPMONIKER       m_pmkFile;      //Container document moniker
        BOOL            m_fRepaintEnabled;  //No redundant paints

        PIMPIOLEINPLACESITE m_pIOleIPSite;   //Our interface
        LPOLEINPLACEOBJECT  m_pIOleIPObject; //The object
        RECT                m_rcPos;         //Last object rect
        BOOL                m_fInRectSet;    //Prevent reentrancy

        //CONTROLMOD
        PIMPIOLECONTROLSITE     m_pIOleControlSite; //Implemented
        PIMPIDISPATCH           m_pIDispatch;       //Implemented

        PIMPIDISPATCHEVENTS     m_pIDispatchEvents; //Implemented
        DWORD                   m_dwConnEvents;
        IID                     m_iidEvents;
        PCEventMap              m_pEventMap;

        PIMPIPROPERTYNOTIFYSINK m_pIPropNoteSink;   //Implemented
        DWORD                   m_dwConnProp;

        //Control interfaces
        LPOLECONTROL        m_pIOleControl;      //Used
        LPDISPATCH          m_pIDispatchControl; //Used

        //Ambient properties
        OLE_COLOR           m_clrBack;
        OLE_COLOR           m_clrFore;
        HFONT               m_hFont;
        LCID                m_lcid;
        BOOL                m_fDesignMode;

        //Other state information
        BOOL                m_fHaveControlInfo;
        CONTROLINFO         m_ctrlInfo;
        ULONG               m_cLockInPlace;
        BOOL                m_fPendingDeactivate;
        //End CONTROLMOD


    /*
     * This flag is used exculsively by the implementation of
     * IOleUILinkContainer on the page we're in for the Links
     * Dialog. Since we never use it ourselves, public here
     * is no big deal.
     */
    public:
        BOOL            m_fLinkAvail;

    protected:
        BOOL    FObjectInitialize(LPUNKNOWN, LPFORMATETC, DWORD);
        void    ReleaseInterface(LPUNKNOWN *);
        HRESULT CreateStatic(LPDATAOBJECT, LPFORMATETC
            , LPUNKNOWN *);

        //CONTROLMOD
        BOOL    FControlInitialize(void);
        //End CONTROLMOD

    public:
        CTenant(DWORD, HWND, CPages *);
        ~CTenant(void);

        //Gotta have an IUnknown for delegation.
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        DWORD       GetID(void);
        UINT        GetStorageName(LPTSTR);
        UINT        UCreate(TENANTTYPE, LPVOID, LPFORMATETC, LPPOINTL
                        , LPSIZEL, LPSTORAGE, PPATRONOBJECT, DWORD);
        BOOL        FLoad(LPSTORAGE, PTENANTINFO);
        void        GetInfo(PTENANTINFO);
        BOOL        FOpen(LPSTORAGE);
        void        Close(BOOL);
        BOOL        Update(void);
        void        Destroy(LPSTORAGE);

        void        Select(BOOL, BOOL);
        void        ShowAsOpen(BOOL);
        void        ShowYourself(void);
        void        AddVerbMenu(HMENU, UINT);
        void        CopyEmbeddedObject(LPDATAOBJECT, LPFORMATETC
                        , LPPOINTL);
        void        CopyLinkedObject(LPDATAOBJECT, LPFORMATETC
                        , LPPOINTL);
        void        NotifyOfRename(LPTSTR, LPMONIKER, LPMONIKER);
        void        StorageGet(LPSTORAGE *);
        void        ShowObjectType(BOOL);
        BOOL        Activate(LONG, LPMSG);

        void        Draw(HDC, DVTARGETDEVICE *, HDC, int, int
                        , BOOL, BOOL);
        void        Repaint(void);
        void        Invalidate(void);

        TENANTTYPE  TypeGet(void);
        BOOL        FIsSelected(void);
        BOOL        FConvertToStatic(void);

        void        ObjectClassFormatAndIcon(LPCLSID, LPWORD
                        , LPTSTR *, HGLOBAL *);
        BOOL        FSwitchOrUpdateAspect(HGLOBAL, BOOL);
        void        EnableRepaint(BOOL);

        void        ObjectGet(LPUNKNOWN *);
        void        FormatEtcGet(LPFORMATETC, BOOL);
        void        SizeGet(LPSIZEL, BOOL);
        void        SizeSet(LPSIZEL, BOOL, BOOL);
        void        RectGet(LPRECTL, BOOL);
        void        RectSet(LPRECTL, BOOL, BOOL);

        void        DeactivateInPlaceObject(BOOL);
        void        UpdateInPlaceObjectRects(LPCRECT, BOOL);
        HWND        ObjectWindow(void);

        //CONTROLMOD
        void        ToggleDesignMode(BOOL);
        PCEventMap  EventMap(void);
        BOOL        HasControl(void);
        BOOL        HasEvents(void);
        void        AmbientChange(DISPID);
        //End CONTROLMOD
    };


typedef CTenant *PCTenant;

//Return codes for UCreate
#define UCREATE_FAILED              0
#define UCREATE_GRAPHICONLY         1
#define UCREATE_PLACEDOBJECT        2


//CONTROLMOD
//Helper functions in CONNECT.CPP

BOOL InterfaceConnect(LPUNKNOWN, REFIID, LPUNKNOWN, LPDWORD);
BOOL InterfaceDisconnect(LPUNKNOWN, REFIID, LPDWORD);
BOOL ObjectTypeInfo(LPUNKNOWN, LPTYPEINFO *);
BOOL ObjectTypeInfoEvents(LPUNKNOWN, LPTYPEINFO *);
BOOL ObjectEventsIID(LPUNKNOWN, IID *);

//End CONTROLMOD

#endif //_TENANT_H_
