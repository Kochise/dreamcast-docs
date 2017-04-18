/*
 * PAGES.H
 * Patron Chapter 13
 *
 * Definitions and function prototypes for the Pages window control
 * as well as the CPage and CTenant classes.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _PAGES_H_
#define _PAGES_H_

//Versioning.
#define VERSIONMAJOR                2
#define VERSIONMINOR                0
#define VERSIONCURRENT              0x00020000

//Classname
#define SZCLASSPAGES                TEXT("pages")

#define HIMETRIC_PER_INCH           2540
#define LOMETRIC_PER_INCH           254
#define LOMETRIC_BORDER             60          //Border around page


//Window extra bytes and offsets
#define CBPAGESWNDEXTRA             (sizeof(LONG))
#define PAGEWL_STRUCTURE            0



/*
 * Tenant class describing an individual piece of data in a page.
 * It knows where it sits, what object is inside of it, and what
 * its identifer is such that it can find it's storage within a
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

//Tenant creation types (not persistent)
typedef enum
    {
    TENANTTYPE_NULL=0,
    TENANTTYPE_STATIC,
    } TENANTTYPE, *PTENANTTYPE;


//State flags
#define TENANTSTATE_DEFAULT      0x00000000
#define TENANTSTATE_SELECTED     0x00000001


/*
 * Persistent information we need to save for each tenant, which is
 * done in the tenant list instead of with each tenant.  Since this
 * is a small structure it's best not to blow another stream for it
 * (overhead).  (fSetExtent used in compound documents later on.)
 */
typedef struct tagTENANTINFO
    {
    DWORD       dwID;
    RECTL       rcl;
    FORMATETC   fe;             //Excludes ptd
    short       fSetExtent;     //Call IOleObject::SetExtent on Run
    } TENANTINFO, *PTENANTINFO;


class CTenant
    {
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

    protected:
        HRESULT CreateStatic(LPDATAOBJECT, LPFORMATETC
            , LPUNKNOWN *);

    public:
        CTenant(DWORD, HWND, CPages *);
        ~CTenant(void);

        DWORD       GetID(void);
        UINT        GetStorageName(LPOLESTR);
        UINT        Create(TENANTTYPE, LPVOID, LPFORMATETC, PPOINTL
                        , LPSIZEL, LPSTORAGE, PPATRONOBJECT, DWORD);
        BOOL        Load(LPSTORAGE, PTENANTINFO);
        void        GetInfo(PTENANTINFO);
        BOOL        Open(LPSTORAGE);
        void        Close(BOOL);
        BOOL        Update(void);
        void        Destroy(LPSTORAGE);

        void        Select(BOOL);
        BOOL        Activate(LONG);
        void        Draw(HDC, DVTARGETDEVICE *, HDC, int, int
                        , BOOL, BOOL);
        void        Repaint(void);
        void        Invalidate(void);

        void        ObjectGet(LPUNKNOWN *);
        void        FormatEtcGet(LPFORMATETC, BOOL);
        void        SizeGet(LPSIZEL, BOOL);
        void        SizeSet(LPSIZEL, BOOL);
        void        RectGet(LPRECTL, BOOL);
        void        RectSet(LPRECTL, BOOL);
    };


typedef CTenant *PCTenant;

//Return codes for Create
#define CREATE_FAILED               0
#define CREATE_GRAPHICONLY          1
#define CREATE_PLACEDOBJECT         2



typedef struct tagTENANTLIST
    {
    DWORD       cTenants;
    DWORD       dwIDNext;
    } TENANTLIST, *PTENANTLIST;

#define SZSTREAMTENANTLIST        OLETEXT("Tenant List")

//Delay timer used in mouse debouncing
#define IDTIMER_DEBOUNCE          120



/*
 * Page class describing an individual page and what things it
 * contains, managing an IStorage for us.
 *
 * A DWORD is used to identify this page as the name of the storage
 * is the string form of this ID.  If we added a page every second,
 * it would take 136 years to overrun this counter, so we can
 * get away with saving it persistently.  I hope this software is
 * obsolete by then.
 */

class CPage
    {
    private:
        DWORD       m_dwID;             //Persistent identifier
        LPSTORAGE   m_pIStorage;        //Substorage for this page
        HWND        m_hWnd;             //Pages window
        DWORD       m_cOpens;           //Calls to Open

        class CPages *m_pPG;            //Pages window

        DWORD       m_dwIDNext;
        DWORD       m_cTenants;
        HWND        m_hWndTenantList;   //Listbox; our tenant list

        UINT        m_iTenantCur;
        PCTenant    m_pTenantCur;

        UINT        m_uHTCode;          //Last hit-test/mouse move
        UINT        m_uSizingFlags;     //Restrictions on sizing
        BOOL        m_fTracking;        //Tracking resize?
        RECTL       m_rclOrg;           //Original before tracking
        RECTL       m_rcl;              //Tracking rectangle
        RECTL       m_rclBounds;        //Boundaries f/size tracking
        HDC         m_hDC;              //Tracking hDC

        //CHAPTER13MOD
        BOOL        m_fDragPending;     //Waiting for drag?
        //End CHAPTER13MOD
        BOOL        m_fSizePending;     //Waiting for debounce?
        int         m_cxyDist;          //Debounce distance
        UINT        m_cDelay;           //Debounce delay
        POINTS      m_ptDown;           //Point of click to debounce
        //CHAPTER13MOD
        UINT        m_uKeysDown;        //Keys when click happens
        //End CHAPTER13MOD
        DWORD       m_fTimer;           //Timer active?

    protected:
        BOOL         TenantGet(UINT, PCTenant *, BOOL);
        BOOL         TenantAdd(UINT, DWORD, PCTenant *);
        LPDATAOBJECT TransferObjectCreate(PPOINTL);

        //PAGEMOUS.CPP
        UINT         TenantFromPoint(UINT, UINT, PCTenant *);
        //CHAPTER13MOD
        BOOL         DragDrop(UINT, UINT, UINT);
        //End CHAPTER13MOD

    public:
        CPage(DWORD, HWND, class CPages *);
        ~CPage(void);

        DWORD       GetID(void);
        BOOL        Open(LPSTORAGE);
        void        Close(BOOL);
        BOOL        Update(void);
        void        Destroy(LPSTORAGE);
        UINT        GetStorageName(LPOLESTR);

        void        Draw(HDC, int, int, BOOL, BOOL);

        BOOL        TenantCreate(TENANTTYPE, LPVOID, LPFORMATETC
                        , PPATRONOBJECT, DWORD);
        BOOL        TenantDestroy(void);
        BOOL        TenantClip(BOOL);
        BOOL        FQueryObjectSelected(HMENU);

        //PAGEMOUSE.CPP
        BOOL        OnLeftDown(UINT, UINT, UINT);
        BOOL        OnLeftDoubleClick(UINT, UINT, UINT);
        BOOL        OnLeftUp(UINT, UINT, UINT);
        void        OnMouseMove(UINT, int, int);
        void        OnTimer(UINT);
        void        StartSizeTracking(void);
        void        OnNCHitTest(UINT, UINT);
        BOOL        OnSetCursor(UINT);
    };

typedef CPage *PCPage;



/*
 * Structures to save with the document describing the device
 * configuration and pages that we have.  This is followed by
 * a list of DWORD IDs for the individual pages.
 */

typedef struct tagDEVICECONFIG
    {
    DWORD       cb;                         //Size of structure
    TCHAR       szDriver[CCHDEVICENAME];
    TCHAR       szDevice[CCHDEVICENAME];
    TCHAR       szPort[CCHDEVICENAME];
    DWORD       cbDevMode;                  //Size of actual DEVMODE
    DEVMODE     dm;                         //Variable
    } DEVICECONFIG, *PDEVICECONFIG;

//Offset to cbDevMode
#define CBSEEKOFFSETCBDEVMODE  (sizeof(DWORD)   \
                               +(3*CCHDEVICENAME*sizeof(TCHAR)))

//Combined OLE and Patron device structures.
typedef struct tagCOMBINEDEVICE
    {
    DVTARGETDEVICE  td;
    DEVICECONFIG    dc;
    } COMBINEBDEVICE, *PCOMBINEDEVICE;


typedef struct tagPAGELIST
    {
    DWORD       cPages;
    DWORD       iPageCur;
    DWORD       dwIDNext;
    } PAGELIST, *PPAGELIST;


//PRINT.CPP
BOOL    APIENTRY PrintDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL    APIENTRY AbortProc(HDC, int);


//PAGEWIN.CPP
LRESULT APIENTRY PagesWndProc(HWND, UINT, WPARAM, LPARAM);
void             RectConvertMappings(LPRECT, HDC, BOOL);


class CPages : public CWindow
    {
    friend LRESULT APIENTRY PagesWndProc(HWND, UINT, WPARAM, LPARAM);
    friend BOOL    APIENTRY PrintDlgProc(HWND, UINT, WPARAM, LPARAM);

    friend class CPage;
    friend class CTenant;
    //CHAPTER13MOD
    friend class CDropTarget;
    //End CHAPTER13MOD

    protected:
        PCPage      m_pPageCur;             //Current page
        UINT        m_iPageCur;             //Current page
        UINT        m_cPages;               //Number of pages

        HWND        m_hWndPageList;         //Listbox with page list
        HFONT       m_hFont;                //Page font
        BOOL        m_fSystemFont;          //m_hFont system object?

        UINT        m_cx;                   //Page size in LOMETRIC
        UINT        m_cy;

        UINT        m_xMarginLeft;          //Unusable margins,
        UINT        m_xMarginRight;         //in LOMETRIC
        UINT        m_yMarginTop;
        UINT        m_yMarginBottom;

        UINT        m_xPos;                 //Viewport scroll pos,
        UINT        m_yPos;                 //both in *PIXELS*

        DWORD       m_dwIDNext;             //Next ID for a page.
        LPSTORAGE   m_pIStorage;            //Root storage

        UINT        m_cf;                   //Clipboard format
        BOOL        m_fDirty;

        //CHAPTER13MOD
        BOOL        m_fDragSource;          //Source==target?
        BOOL        m_fMoveInPage;          //Moving in same page
        POINTL      m_ptDrop;               //Where to move object

        BOOL        m_fDragRectShown;       //Is rect on the screen?
        UINT        m_uScrollInset;         //Hit-test for drag-drop
        UINT        m_uScrollDelay;         //Delay before repeat
        DWORD       m_dwTimeLast;           //Ticks on last DragOver
        UINT        m_uHScrollCode;         //L/R on scroll repeat?
        UINT        m_uVScrollCode;         //U/D on scroll repeat?
        UINT        m_uLastTest;            //Last test result
        POINTL      m_ptlRect;              //Last feedback rectangle
        SIZEL       m_szlRect;
        //End CHAPTER13MOD

    protected:
        void        Draw(HDC, BOOL, BOOL);
        void        UpdateScrollRanges(void);
        BOOL        ConfigureForDevice(void);
        BOOL        PageGet(UINT, PCPage *, BOOL);
        BOOL        PageAdd(UINT, DWORD, BOOL);

        void        CalcBoundingRect(LPRECT, BOOL);

        //CHAPTER13MOD
        //DRAGDROP.CPP
        UINT        UTestDroppablePoint(PPOINTL);
        void        DrawDropTargetRect(PPOINTL, LPSIZEL);
        void        AdjustPosition(PPOINTL, LPSIZEL);
        //End CHAPTER13MOD


    public:
        CPages(HINSTANCE, UINT);
        ~CPages(void);

        BOOL        Init(HWND, LPRECT, DWORD, UINT, LPVOID);

        BOOL        StorageSet(LPSTORAGE, BOOL, BOOL);
        BOOL        StorageUpdate(BOOL);

        BOOL        Print(HDC, LPTSTR, DWORD, UINT, UINT, UINT);

        void        RectGet(LPRECT);
        void        RectSet(LPRECT, BOOL);
        void        SizeGet(LPRECT);
        void        SizeSet(LPRECT, BOOL);

        PCPage      ActivePage(void);
        UINT        PageInsert(UINT);
        UINT        PageDelete(UINT);
        UINT        CurPageGet(void);
        UINT        CurPageSet(UINT);
        UINT        NumPagesGet(void);

        BOOL        DevModeSet(HGLOBAL, HGLOBAL);
        HGLOBAL     DevModeGet(void);

        BOOL        FIsDirty(void);
        BOOL        DevReadConfig(PCOMBINEDEVICE *, HDC *);
        BOOL        TenantCreate(TENANTTYPE, LPVOID, LPFORMATETC
                        , PPATRONOBJECT, DWORD);
        BOOL        TenantDestroy(void);
        BOOL        TenantClip(BOOL);
        BOOL        FQueryObjectSelected(HMENU);
    };

typedef CPages *PCPages;


//Fixed names of streams in the Pages IStorage
#define SZSTREAMPAGELIST        OLETEXT("Page List")
#define SZSTREAMDEVICECONFIG    OLETEXT("Device Configuration")

//CHAPTER13MOD
//Return values for UTestDroppablePoint
#define UDROP_NONE              0x0000      //Exclusive
#define UDROP_CLIENT            0x0001      //Inclusive
#define UDROP_INSETLEFT         0x0002      //L/R are exclusive
#define UDROP_INSETRIGHT        0x0004
#define UDROP_INSETHORZ         (UDROP_INSETLEFT | UDROP_INSETRIGHT)

#define UDROP_INSETTOP          0x0008      //T/B are exclusive
#define UDROP_INSETBOTTOM       0x0010
#define UDROP_INSETVERT         (UDROP_INSETTOP | UDROP_INSETBOTTOM)
//End CHAPTER13MOD

#endif  //_PAGES_H_
