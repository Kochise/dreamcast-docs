/*
 * TENANT.H
 * Patron Chapter 22
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


//CHAPTER22MOD
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
//End CHAPTER22MOD


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


class CTenant : public IUnknown
    {
    friend CImpIOleClientSite;
    friend CImpIAdviseSink;
    //CHAPTER22MOD
    friend CImpIOleInPlaceSite;
    //End CHAPTER22MOD

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

        //CHAPTER22MOD
        PCImpIOleInPlaceSite m_pImpIOleIPSite; //Our interface
        LPOLEINPLACEOBJECT   m_pIOleIPObject;  //The object
        RECT                 m_rcPos;          //Last object rect
        BOOL                 m_fInRectSet;     //Prevent reentrancy
        //End CHAPTER22MOD

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

        //CHAPTER22MOD
        void        Select(BOOL, BOOL);
        //End CHAPTER22MOD
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

        //CHAPTER22MOD
        BOOL        Activate(LONG, LPMSG);
        //End CHAPTER22MOD

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

        //CHAPTER22MOD
        void        DeactivateInPlaceObject(BOOL);
        void        UpdateInPlaceObjectRects(LPCRECT, BOOL);
        HWND        ObjectWindow(void);
        //End CHAPTER22MOD
    };


typedef CTenant *PCTenant;

//Return codes for Create
#define CREATE_FAILED               0
#define CREATE_GRAPHICONLY          1
#define CREATE_PLACEDOBJECT         2



#endif //_TENANT_H_
