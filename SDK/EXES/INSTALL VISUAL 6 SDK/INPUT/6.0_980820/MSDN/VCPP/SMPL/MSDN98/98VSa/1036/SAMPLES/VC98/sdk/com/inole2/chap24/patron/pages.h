/*
 * PAGES.H
 * Patron Chapter 24
 *
 * Definitions and function prototypes for the Pages window control
 * as well as the CPage class.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _PAGES_H_
#define _PAGES_H_

#include <stdlib.h>     //For atol

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


#include "tenant.h"

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

class CPage : public IUnknown
    {
    friend class CIOleUILinkContainer;
    friend class CImpIOleItemContainer;

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

        BOOL        m_fDragPending;     //Waiting for drag?
        BOOL        m_fSizePending;     //Waiting for debounce?
        int         m_cxyDist;          //Debounce distance
        UINT        m_cDelay;           //Debounce delay
        POINTS      m_ptDown;           //Point of click to debounce
        UINT        m_uKeysDown;        //Keys when click happens
        DWORD       m_fTimer;           //Timer active?
        BOOL        m_fReopen;          //Did we just close?

        LPMONIKER               m_pmkFile;  //Document name
        ULONG                   m_cRef;
        DWORD                   m_dwRegROTWild;

        class CImpIOleItemContainer *m_pImpIOleItemContainer;

        BOOL                m_fFirstUIActivate;

    protected:
        BOOL         TenantGet(UINT, PCTenant *, BOOL);
        BOOL         TenantGetFromID(DWORD, PCTenant *, BOOL);
        BOOL         TenantAdd(UINT, DWORD, PCTenant *);
        LPDATAOBJECT TransferObjectCreate(PPOINTL);

        //PAGEMOUS.CPP
        BOOL         SelectTenantAtPoint(UINT, UINT);
        UINT         TenantFromPoint(UINT, UINT, PCTenant *);
        BOOL         DragDrop(UINT, UINT, UINT);

    public:
        CPage(DWORD, HWND, class CPages *);
        ~CPage(void);

        //IUnknown for delegation
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

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
        void        ActivateObject(LONG, LPMSG);

        void        ShowObjectTypes(BOOL);
        void        NotifyTenantsOfRename(LPTSTR, LPMONIKER);
        BOOL        FQueryLinksInPage(void);
        BOOL        ConvertObject(HWND, BOOL);
        void        ScrolledWindow(void);
        void        SwitchActiveTenant(PCTenant);
        //CHAPTER24MOD
        void        ToggleDesignMode(BOOL);
        void        ToggleUIDead(BOOL);
        void        ToggleHatchHandles(BOOL);
        BOOL        FQueryEnableEvents(void);
        void        AssignEvents(HWND);
        BOOL        TryMnemonic(LPMSG);
        //End CHAPTER24MOD

        //PAGEMOUSE.CPP
        BOOL        OnRightDown(UINT, UINT, UINT);
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


//CHAPTER24MOD
//EVENTS.CPP
BOOL    APIENTRY EventsDlgProc(HWND, UINT, WPARAM, LPARAM);

//Helpers for EventsDlgProc
void CheckAction(HWND, HWND);
void UpdateAction(HWND, UINT);
void TestSelection(HWND);

#ifdef WIN32
#define PROP_POINTER    TEXT("Pointer")
#else
#define PROP_SELECTOR   "Selector"
#define PROP_OFFSET     "Offset"
#endif

//End CHAPTER24MOD


class CPages : public CWindow
    {
    friend LRESULT APIENTRY PagesWndProc(HWND, UINT, WPARAM, LPARAM);
    friend BOOL    APIENTRY PrintDlgProc(HWND, UINT, WPARAM, LPARAM);

    friend class CPage;
    friend class CTenant;
    friend class CDropTarget;
    friend class CImpIAdviseSink;
    friend class CImpIOleItemContainer;
    friend class CImpIOleInPlaceSite;

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

        BOOL        m_fDragSource;          //Source==target?
        BOOL        m_fMoveInPage;          //Moving in same page
        BOOL        m_fLinkAllowed;         //Linking in drag-drop?
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

        BOOL        m_fShowTypes;           //Show Object active?
        LPMONIKER   m_pmkFile;
        BOOL        m_fAddUI;
        //CHAPTER24MOD
        BOOL        m_fDesignMode;
        BOOL        m_fUIDead;
        BOOL        m_fHatchHandles;
        IFontDisp  *m_pIFont;               //Ambient font
        //End CHAPTER24MOD

    private:
        void        Draw(HDC, BOOL, BOOL);
        void        UpdateScrollRanges(void);
        BOOL        ConfigureForDevice(void);
        BOOL        PageGet(UINT, PCPage *, BOOL);
        BOOL        PageAdd(UINT, DWORD, BOOL);

        void        CalcBoundingRect(LPRECT, BOOL);

        //DRAGDROP.CPP
        UINT        UTestDroppablePoint(PPOINTL);
        void        DrawDropTargetRect(PPOINTL, LPSIZEL);
        void        AdjustPosition(PPOINTL, LPSIZEL);

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
        void        ActivateObject(LONG, LPMSG);
        //CHAPTER24MOD
        void        ToggleDesignMode(BOOL);
        void        ToggleUIDead(BOOL);
        void        ToggleHatchHandles(BOOL);
        BOOL        FQueryEnableEvents(void);
        void        AssignEvents(HWND);
        BOOL        TryMnemonic(LPMSG);
        //End CHAPTER24MOD

        void        ShowObjectTypes(BOOL);
        void        NotifyTenantsOfRename(LPTSTR, LPMONIKER);
        BOOL        FQueryLinksInPage(void);
        BOOL        GetUILinkContainer(class CIOleUILinkContainer **);
        BOOL        ConvertObject(HWND);
        UINT        IPageGetFromID(DWORD, PCPage *, BOOL);
    };

typedef CPages *PCPages;


//Fixed names of streams in the Pages IStorage
#define SZSTREAMPAGELIST        OLETEXT("Page List")
#define SZSTREAMDEVICECONFIG    OLETEXT("Device Configuration")

//Return values for UTestDroppablePoint
#define UDROP_NONE              0x0000      //Exclusive
#define UDROP_CLIENT            0x0001      //Inclusive
#define UDROP_INSETLEFT         0x0002      //L/R are exclusive
#define UDROP_INSETRIGHT        0x0004
#define UDROP_INSETHORZ         (UDROP_INSETLEFT | UDROP_INSETRIGHT)

#define UDROP_INSETTOP          0x0008      //T/B are exclusive
#define UDROP_INSETBOTTOM       0x0010
#define UDROP_INSETVERT         (UDROP_INSETTOP | UDROP_INSETBOTTOM)


//Object used for the Links dialog

class CIOleUILinkContainer : public IOleUILinkContainer
    {
    private:
        ULONG                   m_cRef;
        PCPage                  m_pPage;
        UINT                    m_iTenant;
        LPOLEUILINKCONTAINER    m_pDelIUILinks;

    public:
        BOOL                    m_fDirty;   //No reason to hide it

    protected:
        STDMETHODIMP GetObjectInterface(DWORD, REFIID, PPVOID);

    public:
        CIOleUILinkContainer(PCPage);
        ~CIOleUILinkContainer(void);

        BOOL Init(void);
        BOOL IsDirty(void);

        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP_(DWORD) GetNextLink(DWORD);
        STDMETHODIMP         SetLinkUpdateOptions(DWORD, DWORD);
        STDMETHODIMP         GetLinkUpdateOptions(DWORD, LPDWORD);
        STDMETHODIMP         SetLinkSource(DWORD, LPTSTR, ULONG
                                 , ULONG *, BOOL);
        STDMETHODIMP         GetLinkSource(DWORD, LPTSTR *, ULONG *
                                 , LPTSTR *, LPTSTR *, BOOL *
                                 , BOOL *);
        STDMETHODIMP         OpenLinkSource(DWORD);
        STDMETHODIMP         UpdateLink(DWORD, BOOL, BOOL);
        STDMETHODIMP         CancelLink(DWORD);
    };

typedef CIOleUILinkContainer *PCIOleUILinkContainer;


#endif  //_PAGES_H_
