/*
 * PATRON.H
 * Patron Chapter 22
 *
 * Single include file that pulls in everything needed for other
 * source files in the application.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _PATRON_H_
#define _PATRON_H_

#define INC_CLASSLIB
#define INC_OLEUI
//CHAPTER22MOD
#define CHAPTER22
//End CHAPTER22MOD
#include <inole.h>
#include "resource.h"

//Get editor window information
#include "pages.h"


/*
 * UINT value such that adding one produces zero.  Portable to Win32.
 * This is used to represent a non-existent zero-based UINT value
 */
#define NOVALUE                     ((UINT)-1)


//PATRON.CPP:  Frame object that creates a main window

//CHAPTER22MOD
class CPatronFrame : public CFrame, public IOleInPlaceFrame
//End CHAPTER22MOD
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

        //CHAPTER22MOD
        DWORD           m_cRef;
        HMENU           m_hMenuOrg;         //Original menu
        HMENU           m_hMenuTop;
        HWND            m_hWndObj;          //Object window
        BOOL            m_fOurToolsShowing; //Our tools up?

        int             m_cyTop;            //In-place tool allocations
        int             m_cyBottom;
        int             m_cxLeft;
        int             m_cxRight;

        BOOL            m_fInContextHelp;   //In context help mode?

        LPOLEINPLACEACTIVEOBJECT    m_pIOleIPActiveObject;
        //End CHAPTER22MOD

    //CHAPTER22MOD
    //This is for access from IOleInPlaceSite::GetWindowContext
    public:
        HACCEL          m_hAccelIP;         //Accelerators for in-place
    //End CHAPTER22MOD

    protected:
        //Overridable for creating a CPatronClient
        virtual PCClient    CreateCClient(void);

        virtual BOOL        FMessageHook(HWND, UINT, WPARAM, LPARAM
                                , LRESULT *);

        virtual BOOL        PreShowInit(void);
        virtual BOOL        RegisterAllClasses(void);
        virtual UINT        CreateToolbar(void);
        virtual LRESULT     OnCommand(HWND, WPARAM, LPARAM);

    public:
        CPatronFrame(HINSTANCE, HINSTANCE, LPSTR, int);
        virtual ~CPatronFrame(void);

        //Overrides
        virtual BOOL        Init(PFRAMEINIT);

        //CHAPTER22MOD
        virtual WPARAM      MessageLoop(void);
        //End CHAPTER22MOD

        virtual void        UpdateMenus(HMENU, UINT);
        virtual void        UpdateToolbar(void);

        //CHAPTER22MOD
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
                                 , LPCOLESTR);
        STDMETHODIMP         InsertMenus(HMENU, LPOLEMENUGROUPWIDTHS);
        STDMETHODIMP         SetMenu(HMENU, HOLEMENU, HWND);
        STDMETHODIMP         RemoveMenus(HMENU);
        STDMETHODIMP         SetStatusText(LPCOLESTR);
        STDMETHODIMP         EnableModeless(BOOL);
        STDMETHODIMP         TranslateAccelerator(LPMSG, WORD);
        //End CHAPTER22MOD
    };


typedef CPatronFrame *PCPatronFrame;


//These are global for simplification of object implementation.
extern ULONG g_cObj;
extern ULONG g_cLock;
extern HWND  g_hWnd;

//CHAPTER22MOD
extern PCPatronFrame  g_pFR;
//End CHAPTER22MOD

//Function for the object to notify on destruction.
void ObjectDestroyed(void);


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
        CPatronClient(HINSTANCE, PCFrame);
        virtual ~CPatronClient(void);

        //CHAPTER22MOD
        //This is added to handle IOleInPlaceFrame::SetMenu
        void         SetMenu(HWND, HMENU, HMENU);
        void         MoveWithoutFamily(LPRECT, int, int);
        void         CallContextHelpOnDocuments(BOOL);
        //End CHAPTER22MOD
    };


typedef CPatronClient *PCPatronClient;




//DOCUMENT.CPP

//Constant ID for the pages window that lives in a document window
#define ID_PAGES            723


class CImpIPersistFile;
typedef class CImpIPersistFile *PCImpIPersistFile;
class CImpIOleItemContainer;
typedef class CImpIOleItemContainer *PCImpIOleItemContainer;
//CHAPTER22MOD
class CImpIOleInPlaceUIWindow;
typedef class CImpIOleInPlaceUIWindow *PCImpIOleInPlaceUIWindow;
//End CHAPTER22MOD

/*
 * To support linking to embeddings, the document needs to have
 * IPersistFile and IOleItemContainer interfaces, so we multiply
 * inherit from IUnknown and provide two interface implementations.
 */

class CPatronDoc : public CDocument, public IUnknown
    {
    //These need access to FQueryPasteFromData, PasteFromData
    friend class CDropTarget;
    friend class CDropSource;
    friend class CImpIPersistFile;
    friend class CImpIOleItemContainer;
    //CHAPTER22MOD
    friend class CImpIOleInPlaceUIWindow;
    //End CHAPTER22MOD

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
        BOOL                m_fRename;          //Rename on Save?
        DWORD               m_dwRegROT;
        DWORD               m_dwRegROTWild;

        PCImpIPersistFile       m_pImpIPersistFile;
        PCImpIOleItemContainer  m_pImpIOleItemContainer;

        //CHAPTER22MOD
        PCImpIOleInPlaceUIWindow m_pImpIOleIPUIWindow;  //Ours
        LPOLEINPLACEACTIVEOBJECT m_pIOleIPActiveObject; //Object's
        BOOL                     m_fNoObjectFrameTools;
        //End CHAPTER22MOD

    protected:
        virtual BOOL    FMessageHook(HWND, UINT, WPARAM, LPARAM
            , LRESULT *);

        BOOL            FQueryPasteFromData(LPDATAOBJECT
                            , LPFORMATETC, PTENANTTYPE);
        BOOL            FQueryPasteLinkFromData(LPDATAOBJECT
                            , LPFORMATETC, PTENANTTYPE);
        BOOL            PasteFromData(LPDATAOBJECT, LPFORMATETC
                            , TENANTTYPE, PPATRONOBJECT, DWORD
                            , BOOL);

    public:
        CPatronDoc(HINSTANCE, PCFrame, PCDocumentAdviseSink);
        virtual ~CPatronDoc(void);

        //We now need our ubiquitous set of IUnknown members.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        virtual BOOL    Init(PDOCUMENTINIT);
        virtual void    Clear(void);

        virtual BOOL    FDirtySet(BOOL);
        virtual BOOL    FDirtyGet(void);
        virtual void    Delete(void);
        virtual BOOL    FQueryPrinterSetup(void);
        virtual BOOL    FQueryObjectSelected(HMENU);

        virtual UINT    Load(BOOL, LPTSTR);
        virtual UINT    Save(UINT, LPTSTR);

        virtual BOOL    Print(HWND);
        virtual UINT    PrinterSetup(HWND, BOOL);

        virtual BOOL    Clip(HWND, BOOL);
        virtual BOOL    FQueryPaste(void);
        virtual BOOL    Paste(HWND);
        virtual BOOL    PasteSpecial(HWND);
        virtual BOOL    FQueryEnableEditLinks(void);
        virtual BOOL    EditLinks(HWND);
        virtual BOOL    ShowOrQueryObjectTypes(BOOL, BOOL);

        virtual UINT    NewPage(void);
        virtual UINT    DeletePage(void);
        virtual UINT    NextPage(void);
        virtual UINT    PreviousPage(void);
        virtual UINT    FirstPage(void);
        virtual UINT    LastPage(void);

        virtual void    Rename(LPTSTR);
        virtual BOOL    InsertObject(HWND);
        //CHAPTER22MOD
        virtual void    ActivateObject(LONG, LPMSG);
        virtual BOOL    NoObjectFrameTools(BOOL, BOOL);
        //End CHAPTER22MOD
        virtual BOOL    ConvertObject(HWND);

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
        STDMETHODIMP Load(LPCOLESTR, DWORD);
        STDMETHODIMP Save(LPCOLESTR, BOOL);
        STDMETHODIMP SaveCompleted(LPCOLESTR);
        STDMETHODIMP GetCurFile(LPOLESTR *);
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
        BOOL         TenantFromName(LPOLESTR, PCTenant *);

    public:
        CImpIOleItemContainer(LPVOID, LPUNKNOWN, BOOL);
        ~CImpIOleItemContainer(void);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP ParseDisplayName(LPBC, LPOLESTR, ULONG *
            , LPMONIKER *);
        STDMETHODIMP EnumObjects(DWORD, LPENUMUNKNOWN *);
        STDMETHODIMP LockContainer(BOOL);
        STDMETHODIMP GetObject(LPOLESTR, DWORD, LPBINDCTX, REFIID
            , PPVOID);
        STDMETHODIMP GetObjectStorage(LPOLESTR, LPBINDCTX, REFIID
            , PPVOID);
        STDMETHODIMP IsRunning(LPOLESTR);
    };



//CHAPTER22MOD
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
                         , LPCOLESTR);
    };
//End CHAPTER22MOD






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
