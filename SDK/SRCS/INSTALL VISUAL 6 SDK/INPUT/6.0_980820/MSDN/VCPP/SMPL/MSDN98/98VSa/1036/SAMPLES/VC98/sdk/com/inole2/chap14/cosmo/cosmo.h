/*
 * COSMO.H
 * Cosmo Chapter 14
 *
 * Single include file that pulls in everything needed for other
 * source files in the Cosmo application.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _COSMO_H_
#define _COSMO_H_

#define INC_CLASSLIB
//CHAPTER14MOD
#define INC_AUTOMATION
#define GUIDS_FROM_TYPELIB
#define CHAPTER14
#include <memory.h>
//End CHAPTER14MOD
#include <inole.h>
#include "resource.h"

//CHAPTER14MOD
//Get the Automation interfaces
#include "icosmo.h"
//End CHAPTER14MOD


//Get the editor window information.
#include "polyline.h"



//CHAPTER14MOD
/*
 * Forward reference automation object classes for our frame
 * and document classes which then contain them.
 */

class CAutoApp;
typedef CAutoApp *PCAutoApp;
class CClassFactory;
typedef CClassFactory *PCClassFactory;
class CAutoFigures;
typedef CAutoFigures *PCAutoFigures;
class CAutoFigure;
typedef CAutoFigure *PCAutoFigure;
//End CHAPTER14MOD


//COSMO.CPP:  Frame object that creates a main window

class CCosmoFrame : public CFrame
    {
    //CHAPTER14MOD
    friend CClassFactory;
    friend CAutoApp;
    friend CAutoFigures;
    //End CHAPTER14MOD

    private:
        HBITMAP         m_hBmpLines[5];     //Menu item bitmaps
        UINT            m_uIDCurLine;       //Current line selection
        BOOL            m_fInitialized;     //Did OleInitalize work?

        LPCLASSFACTORY  m_pIClassDataTran;  //For locking

        //CHAPTER14MOD
        BOOL            m_fEmbedding;   //-Embedding flag?
        BOOL            m_fAutomation;  //-Automation flag?

        PCAutoApp       m_pAutoApp;     //Implements ICosmoApplication
        DWORD           m_dwActiveApp;  //From RegisterActiveObject

        PCClassFactory  m_pIClassFactoryApp;
        DWORD           m_dwRegCOApp;

        PCClassFactory  m_pIClassFactoryFig;
        DWORD           m_dwRegCOFig;
        //End CHAPTER14MOD

    protected:
        //Overridable for creating a CClient for this frame
        virtual PCClient  CreateCClient(void);

        virtual BOOL      RegisterAllClasses(void);
        virtual BOOL      PreShowInit(void);
        virtual UINT      CreateToolbar(void);

        virtual LRESULT   OnCommand(HWND, WPARAM, LPARAM);
        virtual void      OnDocumentDataChange(PCDocument);
        virtual void      OnDocumentActivate(PCDocument);

        //New for this class
        virtual void      CreateLineMenu(void);

    public:
        CCosmoFrame(HINSTANCE, HINSTANCE, LPSTR, int);
        virtual ~CCosmoFrame(void);

        //Overrides
        virtual BOOL      Init(PFRAMEINIT);
        virtual void      UpdateMenus(HMENU, UINT);
        virtual void      UpdateToolbar(void);

        //New for this class
        virtual void      CheckLineSelection(UINT);

        //CHAPTER14MOD
        PCAutoApp         AutoApp(void);
        //End CHAPTER14MOD
    };


typedef CCosmoFrame *PCCosmoFrame;





//CLIENT.CPP

/*
 * The only reason we have a derived class here is to override
 * CreateCDocument so we can create our own type as well as
 * overriding NewDocument to perform one other piece of work once
 * the document's been created.
 */

class CCosmoClient : public CClient
    {
    //CHAPTER14MOD
    friend class CAutoFigures;
    //End CHAPTER14MOD

    //CHAPTER14MOD
    protected:
        PCAutoFigures   m_pAutoFigures;     //Collection object
    //End CHAPTER14MOD

    protected:
        //Overridable for creating a new CDocument
        virtual PCDocument CreateCDocument(void);

    public:
        CCosmoClient(HINSTANCE, PCFrame);
        virtual ~CCosmoClient(void);

        virtual BOOL       Init(HMENU, LPRECT);

        virtual PCDocument NewDocument(BOOL);

        //CHAPTER14MOD
        PCAutoFigures      AutoFigures(void);
        //End CHAPTER14MOD

    };

typedef CCosmoClient *PCCosmoClient;




//DOCUMENT.CPP

//Constant ID for the window polyline that lives in a document
#define ID_POLYLINE         10


class CCosmoDoc : public CDocument
    {
    friend class CPolylineAdviseSink;
    //CHAPTER14MOD
    friend class CAutoFigure;
    //End CHAPTER14MOD

    protected:
        UINT                    m_uPrevSize;    //Last WM_SIZE wParam
        LONG                    m_lVer;         //Loaded Polyline ver

        PCPolyline              m_pPL;          //Polyline window here
        PCPolylineAdviseSink    m_pPLAdv;       //Advises from Polyline

        //CHAPTER14MOD
        PCAutoFigure            m_pAutoFig;     //ICosmoFigure
        DWORD                   m_dwActiveFig;  //From RegisterActiveObject
        //End CHAPTER14MOD

    protected:
        virtual BOOL     FMessageHook(HWND, UINT, WPARAM, LPARAM
            , LRESULT *);

        virtual BOOL     FQueryPasteFromData(LPDATAOBJECT);
        virtual BOOL     PasteFromData(LPDATAOBJECT);

    public:
        CCosmoDoc(HINSTANCE, PCFrame, PCDocumentAdviseSink);
        virtual ~CCosmoDoc(void);

        virtual BOOL     Init(PDOCUMENTINIT);

        virtual void     Clear(void);

        virtual UINT     Load(BOOL, LPTSTR);
        virtual UINT     Save(UINT, LPTSTR);

        virtual void     Undo(void);
        virtual BOOL     Clip(HWND, BOOL);
        virtual HGLOBAL  RenderFormat(UINT);
        virtual BOOL     FQueryPaste(void);
        virtual BOOL     Paste(HWND);

        virtual COLORREF ColorSet(UINT, COLORREF);
        virtual COLORREF ColorGet(UINT);

        virtual UINT     LineStyleSet(UINT);
        virtual UINT     LineStyleGet(void);

        //CHAPTER14MOD
        PCAutoFigure     AutoFigure(void);
        //End CHAPTER14MOD
    };

typedef CCosmoDoc *PCCosmoDoc;


//These color indices wrap the polyline definitions
#define DOCCOLOR_BACKGROUND             POLYLINECOLOR_BACKGROUND
#define DOCCOLOR_LINE                   POLYLINECOLOR_LINE


//CHAPTER14MOD

//These are global for simplification of object implementation.
extern ULONG g_cObj;
extern ULONG g_cLock;
extern HWND  g_hWnd;

//Function for the object to notify on destruction.
void ObjectDestroyed(void);

//ICLASSF.CPP:  The generic class factory for our automation objects
class CClassFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;
        PCCosmoFrame    m_pFR;
        CLSID           m_clsID;
        BOOL            m_fCreated;     //Created one object yet?

    public:
        CClassFactory(PCCosmoFrame, REFCLSID);
        ~CClassFactory(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP         CreateInstance(LPUNKNOWN, REFIID
                                 , PPVOID);
        STDMETHODIMP         LockServer(BOOL);
    };

typedef CClassFactory *PCClassFactory;


//AUTOBASE.CPP

class CImpIDispatch;
typedef CImpIDispatch *PCImpIDispatch;

class CImpIExtConn;
typedef class CImpIExtConn *PCImpIExtConn;



/*
 * CAutoBase is a base class for the other automation objects
 * in this application.  It centralizes the implementation of
 * IDispatch as well as the loading of type information.  Since
 * it implements an IDispatch that calls ITypeInfo directly, this
 * is structured to handle multiple languages although this
 * sample only uses one.
 *
 * The pure virtual VTableInterface makes this an abstract
 * base class.  That one function must be overridden to supply
 * the right interface pointer to IDispatch::Invoke.
 */

class CAutoBase
    {
    friend CImpIDispatch;

    public:
        ULONG           m_cRef; //Public for debug checks

    protected:
        PFNDESTROYED    m_pfnDestroy;
        HINSTANCE       m_hInst;

        /*
         * This union will have some pointer in it.  The CAutoBase
         * implementation stores m_pObj.  Derived classes may
         * reference that pointer as a frame, client, or
         * document pointer.
         */
        union
            {
            void           *m_pObj;
            PCCosmoFrame    m_pFR;
            PCCosmoClient   m_pCL;
            PCCosmoDoc      m_pDoc;
            };

        IID             m_iid;
        IID             m_diid;

        PCImpIDispatch  m_pImpIDispatch;    //Our IDispatch
        PCImpIExtConn   m_pImpIExtConn;     //For app or doc

    protected:
        virtual void *VTableInterface(void)=0;

    public:
        CAutoBase(void *, HINSTANCE, REFIID, REFIID
            , PFNDESTROYED);
        virtual CAutoBase::~CAutoBase(void);

        virtual BOOL    Init(BOOL);
    };

typedef CAutoBase *PCAutoBase;


/*
 * CImpIDispatch is the contained object inside CAutoBase that
 * provides the entry points for IDispatch.  We could use
 * CreateStdDispatch for this, but this sample is structured
 * for multilingual support so we use our own IDispatch.
 */

class CImpIDispatch : public IDispatch
    {
    public:
        ULONG           m_cRef;             //For debugging
        ITypeInfo      *m_pITypeInfo;       //Loaded

    private:
        PCAutoBase      m_pObj;
        LPUNKNOWN       m_pUnkOuter;

    public:
        CImpIDispatch(PCAutoBase, LPUNKNOWN);
        ~CImpIDispatch(void);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IDispatch members
        STDMETHODIMP GetTypeInfoCount(UINT *);
        STDMETHODIMP GetTypeInfo(UINT, LCID, ITypeInfo **);
        STDMETHODIMP GetIDsOfNames(REFIID, OLECHAR **, UINT, LCID
            , DISPID *);
        STDMETHODIMP Invoke(DISPID, REFIID, LCID, WORD
            , DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *);
    };



/*
 * Implementation of generic IExternalConnection for both the
 * application and document objects which will call the app or
 * document object's Release when the last external connection
 * disappears.
 */

class CImpIExtConn : public IExternalConnection
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPUNKNOWN       m_pUnkOuter; //For delegation, closure

        ULONG           m_cStrong;   //Strong ref count.

    public:
        CImpIExtConn(LPUNKNOWN);
        ~CImpIExtConn(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP_(DWORD) AddConnection(DWORD, DWORD);
        STDMETHODIMP_(DWORD) ReleaseConnection(DWORD, DWORD, BOOL);
    };



/*
 * AUTOAPP.CPP:  Implementation of ICosmoApplication.
 */

//Actions for CAutoApp::MoveSize and CAutoFigure::MoveSize helpers
typedef enum
    {
    MOVESIZEACTION_LEFT=0,
    MOVESIZEACTION_TOP,
    MOVESIZEACTION_WIDTH,
    MOVESIZEACTION_HEIGHT,
    MOVESIZEACTION_GETLEFT,
    MOVESIZEACTION_GETTOP,
    MOVESIZEACTION_GETWIDTH,
    MOVESIZEACTION_GETHEIGHT
    } MOVESIZEACTION;


//"Application" object for OLE Automation
class CAutoApp : public CAutoBase, public ICosmoApplication
    {
    protected:
        BOOL            m_fQuitCalled;

    protected:
        long    MoveSize(MOVESIZEACTION, long, long, long, long);

        virtual void *VTableInterface(void);

    public:
        CAutoApp(PCCosmoFrame);

        //IUnknown methods
        STDMETHODIMP QueryInterface(REFIID riid, PPVOID ppv);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //ICosmoApplication methods
        STDMETHODIMP_(IDispatch *)  get_Application(void);
        STDMETHODIMP_(IDispatch *)  get_ActiveFigure(void);
        STDMETHODIMP_(BSTR)         get_Caption(void);
        STDMETHODIMP_(IDispatch *)  get_Figures(void);
        STDMETHODIMP_(BSTR)         get_FullName(void);
        STDMETHODIMP_(BSTR)         get_Name(void);
        STDMETHODIMP_(BSTR)         get_Path(void);
        STDMETHODIMP_(long)         get_Left(void);
        STDMETHODIMP_(void)         put_Left(long x);
        STDMETHODIMP_(long)         get_Top(void);
        STDMETHODIMP_(void)         put_Top(long y);
        STDMETHODIMP_(long)         get_Width(void);
        STDMETHODIMP_(void)         put_Width(long cx);
        STDMETHODIMP_(long)         get_Height(void);
        STDMETHODIMP_(void)         put_Height(long cy);
        STDMETHODIMP_(VARIANT_BOOL) get_Visible(void);
        STDMETHODIMP_(void)         put_Visible(VARIANT_BOOL);
        STDMETHODIMP_(BSTR)         get_StatusBar(void);
        STDMETHODIMP_(void)         put_StatusBar(BSTR);
        STDMETHODIMP_(void)         Quit(void);
    };




//AUTOFIGS.CPP:  Implementation of ICosmoFigures collection
class CEnumFigures;
typedef CEnumFigures *PCEnumFigures;


class CAutoFigures : public CAutoBase, public ICosmoFigures
    {
    friend CEnumFigures;

    protected:
        IDispatch    *NewFigure(LPTSTR);
        virtual void *VTableInterface(void);

    public:
        CAutoFigures(PCCosmoClient);
        ~CAutoFigures(void);

        //IUnknown methods
        STDMETHODIMP QueryInterface(REFIID riid, PPVOID ppv);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //ICosmoFigures methods
        STDMETHODIMP_(IDispatch *) get_Application(void);
        STDMETHODIMP_(IDispatch *) get_Parent(void);
        STDMETHODIMP_(long)        get_Count(void);
        STDMETHODIMP_(IDispatch *) Item(VARIANT);
        STDMETHODIMP_(IDispatch *) Add(void);
        STDMETHODIMP_(IDispatch *) Open(BSTR);
        STDMETHODIMP_(void)        Close(void);
        STDMETHODIMP_(IUnknown *)  _NewEnum(void);
    };

typedef CAutoFigures *PCAutoFigures;

//Enumerator of whatever is held in the collection
class CEnumFigures : public IEnumVARIANT
    {
    protected:
        ULONG       m_cRef;
        HWND        m_hList;
        HINSTANCE   m_hInst;
        ULONG       m_iCur;
        ULONG       m_cItems;

    public:
        CEnumFigures(HINSTANCE);
        ~CEnumFigures(void);

        BOOL    Init(HWND, BOOL);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IEnumFORMATETC members
        STDMETHODIMP Next(ULONG, VARIANT *, ULONG *);
        STDMETHODIMP Skip(ULONG);
        STDMETHODIMP Reset(void);
        STDMETHODIMP Clone(IEnumVARIANT **);
    };


/*
 * AUTOFIG.CPP: Implementation of ICosmoFigure object.  This
 * class has no specific data members and only one private
 * function, MoveSize, which is just a helper.  It should be
 * obvious that this class is little more than another route
 * to get at the same functionality we have elsewhere in Cosmo,
 * which is what Automation is really all about when added to
 * an application with a lot of user interface.
 */

class CAutoFigure : public CAutoBase, public ICosmoFigure
    {
    protected:
        long    MoveSize(MOVESIZEACTION, long, long, long, long);

        virtual void *VTableInterface(void);

    public:
        CAutoFigure(PCCosmoDoc);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //ICosmoFigure members
        STDMETHODIMP_(IDispatch *)  get_Application(void);
        STDMETHODIMP_(IDispatch *)  get_Parent(void);
        STDMETHODIMP_(BSTR)         get_FullName(void);
        STDMETHODIMP_(BSTR)         get_Name(void);
        STDMETHODIMP_(BSTR)         get_Path(void);
        STDMETHODIMP_(VARIANT_BOOL) get_Saved(void);
        STDMETHODIMP_(short)        get_NumberOfPoints(void);
        STDMETHODIMP_(long)         get_BackColor(void);
        STDMETHODIMP_(void)         put_BackColor(long);
        STDMETHODIMP_(long)         get_LineColor(void);
        STDMETHODIMP_(void)         put_LineColor(long);
        STDMETHODIMP_(short)        get_LineStyle(void);
        STDMETHODIMP_(void)         put_LineStyle(short);
        STDMETHODIMP_(long)         get_Left(void);
        STDMETHODIMP_(void)         put_Left(long);
        STDMETHODIMP_(long)         get_Top(void);
        STDMETHODIMP_(void)         put_Top(long);
        STDMETHODIMP_(long)         get_Width(void);
        STDMETHODIMP_(void)         put_Width(long);
        STDMETHODIMP_(long)         get_Height(void);
        STDMETHODIMP_(void)         put_Height(long);
        STDMETHODIMP_(VARIANT_BOOL) get_Visible(void);
        STDMETHODIMP_(void)         put_Visible(VARIANT_BOOL);

        STDMETHODIMP_(void)         Activate(void);
        STDMETHODIMP_(void)         Close(VARIANT, VARIANT);
        STDMETHODIMP_(void)         RevertToSaved(void);
        STDMETHODIMP_(void)         Save(void);
        STDMETHODIMP_(void)         SaveAs(BSTR);
        STDMETHODIMP_(void)         Import(BSTR);
        STDMETHODIMP_(void)         Copy(void);
        STDMETHODIMP_(void)         Cut(void);
        STDMETHODIMP_(void)         Paste(void);
        STDMETHODIMP_(VARIANT_BOOL) AddPoint(short, short);
        STDMETHODIMP_(void)         RemovePoint(void);
    };



//End CHAPTER14MOD



#endif //_COSMO_H_
