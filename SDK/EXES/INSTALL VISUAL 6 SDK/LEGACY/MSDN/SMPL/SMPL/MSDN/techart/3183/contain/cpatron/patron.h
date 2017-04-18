/*
 * PATRON.H
 * Patron Control Container
 *
 * Single include file that pulls in everything needed for other
 * source files in the application.
 *
 * Copyright (c)1993-1994 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _PATRON_H_
#define _PATRON_H_

#define INC_OLE2
#include <windows.h>
#include <ole2.h>
#include <ole2ver.h>
#include <ole2ui.h>
#include <bookguid.h>

//CONTROLMOD
#ifdef WIN32
#include <oleauto.h>
#else
#include <dispatch.h>
#endif

#include <olectl.h>

#ifndef INITGUIDS
#include <olectlid.h>
#endif

#ifndef WIN32
#include <olenls.h>
#endif
//End CONTROLMOD

extern "C"
    {
    #include <commdlg.h>
   #ifndef WIN32
    #include <print.h>
   #endif
    }

#include <classlib.h>
#include "resource.h"
#include "pages.h"

/*
 * UINT value such that adding one produces zero.  Portable to Win32.
 * This is used to represent a non-existent zero-based UINT value
 */
#define NOVALUE                     ((UINT)-1)


//PATRON.CPP:  Frame object that creates a main window

class CPatronFrame : public CFrame, public IOleInPlaceFrame
    {
    //For access to m_pCL for document creation
    friend class CLinkClassFactory;

    private:
        BOOL            m_fInitialized;     //OleInitialize worked
        LPCLASSFACTORY  m_pIClassDataTran;  //For locking.
        PCDocument      m_pDocCreated;      //What class factory makes
        BOOL            m_fEmbedding;       //-Embedding on command line?
        DWORD           m_dwRegCO;          //From CoRegisterClassObject
        LPCLASSFACTORY  m_pIClassFactory;

        DWORD           m_cRef;
        HMENU           m_hMenuOrg;         //Original menu, not changed
        HMENU           m_hMenuTop;
        HWND            m_hWndObj;          //Object window
        BOOL            m_fOurToolsShowing; //Our tools up?

        int             m_cyTop;            //In-place tool allocations
        int             m_cyBottom;
        int             m_cxLeft;
        int             m_cxRight;

        BOOL            m_fInContextHelp;   //In context help mode?

        LPOLEINPLACEACTIVEOBJECT    m_pIOleIPActiveObject;

    //This is for access from IOleInPlaceSite::GetWindowContext
    public:
        HACCEL          m_hAccelIP;         //Accelerators for in-place

    protected:
        //Overridable for creating a CPatronClient
        virtual PCClient    CreateCClient(void);

        virtual BOOL        FMessageHook(HWND, UINT, WPARAM, LPARAM
                                , LRESULT *);

        virtual BOOL        FPreShowInit(void);
        virtual void        ParseCommandLine(void);
        virtual BOOL        FRegisterAllClasses(void);
        virtual UINT        CreateGizmos(void);
        virtual LRESULT     OnCommand(HWND, WPARAM, LPARAM);

    public:
        CPatronFrame(HINSTANCE, HINSTANCE, LPSTR, int);
        virtual ~CPatronFrame(void);

        //Overrides
        virtual BOOL        FInit(PFRAMEINIT);
        virtual WPARAM      MessageLoop(void);

        virtual void        UpdateMenus(HMENU, UINT);
        virtual void        UpdateGizmos(void);
        void                ShowUIAndTools(BOOL, BOOL);
        void                ReinstateUI(void);

        //IOleInPlaceFrame implementation
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP         GetWindow(HWND *);
        STDMETHODIMP         ContextSensitiveHelp(BOOL);
        STDMETHODIMP         GetBorder(LPRECT);
        STDMETHODIMP         RequestBorderSpace(LPCBORDERWIDTHS);
        STDMETHODIMP         SetBorderSpace(LPCBORDERWIDTHS);
        STDMETHODIMP         SetActiveObject(LPOLEINPLACEACTIVEOBJECT
                                 , LPCTSTR);
        STDMETHODIMP         InsertMenus(HMENU, LPOLEMENUGROUPWIDTHS);
        STDMETHODIMP         SetMenu(HMENU, HOLEMENU, HWND);
        STDMETHODIMP         RemoveMenus(HMENU);
        STDMETHODIMP         SetStatusText(LPCTSTR);
        STDMETHODIMP         EnableModeless(BOOL);
        STDMETHODIMP         TranslateAccelerator(LPMSG, WORD);
    };


typedef CPatronFrame *PCPatronFrame;


//These are global for simplification of object implementation.
extern ULONG g_cObj;
extern ULONG g_cLock;
extern HWND  g_hWnd;
extern PCPatronFrame  g_pFR;

//Type for an object-destroyed callback
typedef void (PASCAL *PFNDESTROYED)(void);

//Function for the object to notify on destruction.
void PASCAL ObjectDestroyed(void);


//ICLASSF.CPP

class CLinkClassFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;
        PCPatronFrame   m_pFR;          //For document creation.

    public:
        CLinkClassFactory(PCPatronFrame);
        ~CLinkClassFactory(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP         CreateInstance(LPUNKNOWN, REFIID
                                 , PPVOID);
        STDMETHODIMP         LockServer(BOOL);
    };

typedef CLinkClassFactory *PCLinkClassFactory;




//CLIENT.CPP

/*
 * The only reason we have a derived class here is to override
 * CreateCDocument so we can create our own type as well as
 * overriding NewDocument to perform one other piece of work once
 * the document's been created.
 */

class CPatronClient : public CClient
    {
    protected:
        //Overridable for creating a new CDocument
        virtual PCDocument CreateCDocument(void);

    public:
        CPatronClient(HINSTANCE);
        virtual ~CPatronClient(void);

        //This is added to handle IOleInPlaceFrame::SetMenu
        void         SetMenu(HWND, HMENU, HMENU);
        void         MoveWithoutFamily(LPRECT, int, int);
        void         CallContextHelpOnDocuments(BOOL);
    };


typedef CPatronClient *PCPatronClient;




//DOCUMENT.CPP

//Constant ID for the pages window that lives in a document window
#define ID_PAGES            723


class CImpIPersistFile;
typedef class CImpIPersistFile *PIMPIPERSISTFILE;
class CImpIOleItemContainer;
typedef class CImpIOleItemContainer *PIMPIOLEITEMCONTAINER;
class CImpIOleInPlaceUIWindow;
typedef class CImpIOleInPlaceUIWindow *PIMPIOLEINPLACEUIWINDOW;

/*
 * To support linking to embeddings, the document needs to have
 * IPersistFile and IOleItemContainer interfaces, so we multiply
 * inherit from IUnknown and provide two interface implementations.
 */

class CPatronDoc : public CDocument, public IUnknown
    {
    //These need access to FQueryPasteFromData, FPasteFromData
    friend class CDropTarget;
    friend class CDropSource;
    friend class CImpIPersistFile;
    friend class CImpIOleItemContainer;
    friend class CImpIOleInPlaceUIWindow;

    protected:
        LONG            m_lVer;         //Loaded data version
        PCPages         m_pPG;          //Pages window in us
        LPSTORAGE       m_pIStorage;    //Root storage for document
        BOOL            m_fPrintSetup;

        class CDropTarget *m_pDropTarget;   //Registered target

        UINT            m_cfEmbeddedObject; //Clipboard formats
        UINT            m_cfObjectDescriptor;
        UINT            m_cfLinkSource;
        UINT            m_cfLinkSrcDescriptor;
        BOOL            m_fShowTypes;       //Show Objects active?

        ULONG               m_cRef;
        BOOL                m_fRename;          //Rename on USave?
        DWORD               m_dwRegROT;

        PIMPIPERSISTFILE         m_pIPersistFile;
        PIMPIOLEITEMCONTAINER    m_pIOleItemContainer;
        PIMPIOLEINPLACEUIWINDOW  m_pIOleIPUIWindow;     //Ours
        LPOLEINPLACEACTIVEOBJECT m_pIOleIPActiveObject; //Object's
        BOOL                     m_fNoObjectFrameTools;

        //CONTROLMOD
        BOOL                     m_fDesignMode;
        //End CONTROLMOD

    protected:
        virtual BOOL    FMessageHook(HWND, UINT, WPARAM, LPARAM
            , LRESULT *);

        BOOL            FQueryPasteFromData(LPDATAOBJECT
                            , LPFORMATETC, PTENANTTYPE);
        BOOL            FQueryPasteLinkFromData(LPDATAOBJECT
                            , LPFORMATETC, PTENANTTYPE);
        BOOL            FPasteFromData(LPDATAOBJECT, LPFORMATETC
                            , TENANTTYPE, PPATRONOBJECT, DWORD
                            , BOOL);

    public:
        CPatronDoc(HINSTANCE, PCFrame);
        virtual ~CPatronDoc(void);

        //We now need our ubiquitous set of IUnknown members.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        virtual BOOL    FInit(PDOCUMENTINIT);
        virtual void    Clear(void);

        virtual BOOL    FDirtyGet(void);
        virtual void    Delete(void);
        virtual BOOL    FQueryPrinterSetup(void);
        virtual BOOL    FQueryObjectSelected(HMENU);

        virtual UINT    ULoad(BOOL, LPTSTR);
        virtual UINT    USave(UINT, LPTSTR);

        virtual BOOL    Print(HWND);
        virtual UINT    PrinterSetup(HWND, BOOL);

        virtual BOOL    FClip(HWND, BOOL);
        virtual BOOL    FQueryPaste(void);
        virtual BOOL    FPaste(HWND);
        virtual BOOL    FPasteSpecial(HWND);
        virtual BOOL    FQueryEnableEditLinks(void);
        virtual BOOL    FEditLinks(HWND);
        virtual BOOL    FShowOrQueryObjectTypes(BOOL, BOOL);
        virtual BOOL    FConvertObject(HWND);

        virtual UINT    NewPage(void);
        virtual UINT    DeletePage(void);
        virtual UINT    NextPage(void);
        virtual UINT    PreviousPage(void);
        virtual UINT    FirstPage(void);
        virtual UINT    LastPage(void);

        virtual void    Rename(LPTSTR);
        virtual BOOL    FInsertObject(HWND);
        virtual void    ActivateObject(LONG, LPMSG);
        virtual BOOL    NoObjectFrameTools(BOOL, BOOL);
        //CONTROLMOD
        virtual BOOL    FToggleOrQueryDesignMode(BOOL, BOOL);
        virtual BOOL    FQueryEnableEvents(void);
        virtual void    AssignEvents(HWND);
        //End CONTROLMOD
    };

typedef CPatronDoc *PCPatronDoc;

//Hook for Print Dialog to hide Setup... button
UINT CALLBACK PrintDlgHook(HWND, UINT, WPARAM, LPARAM);


//IPersistFile implementation for CPatronDoc

class CImpIPersistFile : public IPersistFile
    {
    protected:
        ULONG               m_cRef;      //Interface reference count
        PCPatronDoc         m_pDoc;      //Back pointer to the object
        LPUNKNOWN           m_pUnkOuter; //Controlling unknown

    public:
        CImpIPersistFile(PCPatronDoc, LPUNKNOWN);
        ~CImpIPersistFile(void);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetClassID(LPCLSID);

        STDMETHODIMP IsDirty(void);
        STDMETHODIMP Load(LPCTSTR, DWORD);
        STDMETHODIMP Save(LPCTSTR, BOOL);
        STDMETHODIMP SaveCompleted(LPCTSTR);
        STDMETHODIMP GetCurFile(LPTSTR *);
    };



/*
 * IOleItemContainer implementation for both CPatronDoc and CPage,
 * therefore have two back pointers.
 */

class CImpIOleItemContainer : public IOleItemContainer
    {
    protected:
        ULONG               m_cRef;
        class CPage        *m_pPage;
        PCPatronDoc         m_pDoc;      //Convenient naming & types
        LPUNKNOWN           m_pUnkOuter;
        BOOL                m_fDoc;      //Document or page?

    private:
        BOOL         FTenantFromName(LPTSTR, PCTenant *);

    public:
        CImpIOleItemContainer(LPVOID, LPUNKNOWN, BOOL);
        ~CImpIOleItemContainer(void);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP ParseDisplayName(LPBC, LPTSTR, ULONG *
            , LPMONIKER *);
        STDMETHODIMP EnumObjects(DWORD, LPENUMUNKNOWN *);
        STDMETHODIMP LockContainer(BOOL);
        STDMETHODIMP GetObject(LPTSTR, DWORD, LPBINDCTX, REFIID
            , PPVOID);
        STDMETHODIMP GetObjectStorage(LPTSTR, LPBINDCTX, REFIID
            , PPVOID);
        STDMETHODIMP IsRunning(LPTSTR);
    };



//This goes on the document.

class CImpIOleInPlaceUIWindow : public IOleInPlaceUIWindow
    {
    protected:
        ULONG               m_cRef;
        PCPatronDoc         m_pDoc;
        LPUNKNOWN           m_pUnkOuter;

    public:
        CImpIOleInPlaceUIWindow(PCPatronDoc, LPUNKNOWN);
        ~CImpIOleInPlaceUIWindow(void);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetWindow(HWND *);
        STDMETHODIMP ContextSensitiveHelp(BOOL);
        STDMETHODIMP GetBorder(LPRECT);
        STDMETHODIMP RequestBorderSpace(LPCBORDERWIDTHS);
        STDMETHODIMP SetBorderSpace(LPCBORDERWIDTHS);
        STDMETHODIMP SetActiveObject(LPOLEINPLACEACTIVEOBJECT
                         , LPCTSTR);
    };





//Drag-drop objects we need in the document

class CDropTarget : public IDropTarget
    {
    protected:
        ULONG               m_cRef;
        PCPatronDoc         m_pDoc;

        LPDATAOBJECT        m_pIDataObject;  //From DragEnter
        BOOL                m_fPendingRepaint;
        POINTL              m_ptPick;        //Pick-up offsets
        POINTL              m_ptLast;        //Last drag point
        SIZEL               m_szl;           //Object size
        BOOL                m_fFeedback;     //Draw feedback?
        FORMATETC           m_fe;            //Real dropping format

    public:
        CDropTarget(PCPatronDoc);
        ~CDropTarget(void);

        //IDropTarget interface members
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP DragEnter(LPDATAOBJECT, DWORD, POINTL,LPDWORD);
        STDMETHODIMP DragOver(DWORD, POINTL, LPDWORD);
        STDMETHODIMP DragLeave(void);
        STDMETHODIMP Drop(LPDATAOBJECT, DWORD, POINTL, LPDWORD);
    };


typedef CDropTarget *PCDropTarget;


class CDropSource : public IDropSource
    {
    protected:
        ULONG               m_cRef;

    public:
        CDropSource(void);
        ~CDropSource(void);

        //IDropSource interface members
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP QueryContinueDrag(BOOL, DWORD);
        STDMETHODIMP GiveFeedback(DWORD);
    };

typedef CDropSource *PCDropSource;


#endif //_PATRON_H_
