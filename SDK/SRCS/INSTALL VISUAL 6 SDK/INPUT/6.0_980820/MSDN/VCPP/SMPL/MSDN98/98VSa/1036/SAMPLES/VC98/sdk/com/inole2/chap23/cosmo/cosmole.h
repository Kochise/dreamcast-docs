/*
 * COSMOLE.H
 * Cosmo Chapter 23
 *
 * Include file containing all compound document related
 * definitions.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _COSMOLE_H_
#define _COSMOLE_H_


//These are global for simplification of object implementation.
extern ULONG g_cObj;
extern ULONG g_cLock;
extern HWND  g_hWnd;

//CHAPTER23MOD
//This is for simplification of CCosmoFrame::CheckLineSelection
extern PCToolBar    g_pInPlaceTB;

#define ID_HATCHWINDOW  2000
//End CHAPTER23MOD

//Function for the object to notify on destruction.
void ObjectDestroyed(void);


//ICLASSF.CPP
class CFigureClassFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;
        PCCosmoFrame    m_pFR;
        BOOL            m_fCreated;     //Created one object yet?

    public:
        CFigureClassFactory(PCCosmoFrame);
        ~CFigureClassFactory(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP         CreateInstance(LPUNKNOWN, REFIID
                                 , PPVOID);
        STDMETHODIMP         LockServer(BOOL);
    };

typedef CFigureClassFactory *PCFigureClassFactory;


//FIGURE.CPP
//This is what the class factory creates

#define CFORMATETCGET   5

class CImpIPersistStorage;
typedef class CImpIPersistStorage *PCImpIPersistStorage;
class CImpIDataObject;
typedef class CImpIDataObject *PCImpIDataObject;
class CImpIOleObject;
typedef class CImpIOleObject *PCImpIOleObject;
class CImpIPersistFile;
typedef class CImpIPersistFile *PCImpIPersistFile;
//CHAPTER23MOD
class CImpIOleInPlaceObject;
typedef class CImpIOleInPlaceObject *PCImpIOleInPlaceObject;
class CImpIOleInPlaceActiveObject;
typedef class CImpIOleInPlaceActiveObject *PCImpIOleInPlaceActiveObject;
//End CHAPTER23MOD

class CFigure : public IUnknown
    {
    friend class CImpIPersistStorage;
    friend class CImpIDataObject;
    friend class CImpIOleObject;
    friend class CImpIPersistFile;
    //CHAPTER23MOD
    friend class CImpIOleInPlaceObject;
    friend class CImpIOleInPlaceActiveObject;
    //End CHAPTER23MOD

    protected:
        ULONG               m_cRef;
        PCCosmoFrame        m_pFR;      //Frame (for UI changes)
        PCCosmoDoc          m_pDoc;     //What holds real polyline
        PCPolyline          m_pPL;      //Copy of m_pDoc->m_pPL

        BOOL                m_fEmbedded;
        PFNDESTROYED        m_pfnDestroy;

        PCStringTable       m_pST;      //Object strings

        //Things for IPersistStorage
        PCImpIPersistStorage m_pImpIPersistStorage;
        LPSTORAGE           m_pIStorage;
        LPSTREAM            m_pIStream;
        CLSID               m_clsID;

        //Things for IDataObject
        PCImpIDataObject    m_pImpIDataObject;      //Implemented
        LPDATAADVISEHOLDER  m_pIDataAdviseHolder;   //Used

        UINT                m_cf;                   //pDoc->m_cf
        ULONG               m_cfeGet;
        FORMATETC           m_rgfeGet[CFORMATETCGET];

        //Things for IOleObject
        PCImpIOleObject     m_pImpIOleObject;       //Implemented
        LPOLEADVISEHOLDER   m_pIOleAdviseHolder;    //Used
        LPOLECLIENTSITE     m_pIOleClientSite;      //Used

        LPMONIKER           m_pMoniker;
        DWORD               m_dwRegROT;
        PCImpIPersistFile   m_pImpIPersistFile;     //Implemented

        //CHAPTER23MOD
        LPOLEINPLACESITE            m_pIOleIPSite;
        LPOLEINPLACEFRAME           m_pIOleIPFrame;
        LPOLEINPLACEUIWINDOW        m_pIOleIPUIWindow;

        PCImpIOleInPlaceObject       m_pImpIOleIPObject;
        PCImpIOleInPlaceActiveObject m_pImpIOleIPActiveObject;

        HMENU                       m_hMenuShared;
        HOLEMENU                    m_hOLEMenu;
        HACCEL                      m_hAccel;

        PCHatchWin                  m_pHW;      //Hatch window
        PCToolBar                   m_pTB;      //In-place toolbar
        UINT                        m_cyBar;    //Copy of m_pFR->m_cyBar
        BOOL                        m_fUndoDeactivates;
        BOOL                        m_fAllowInPlace;
        BOOL                        m_fForceSave;
        //End CHAPTER23MOD

    public:
        CFigure(PFNDESTROYED, PCCosmoDoc);
        ~CFigure(void);

        //Non-delegating IUnknown:  we don't support aggregation
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        BOOL Init(void);
        void FrameSet(PCCosmoFrame);
        BOOL FIsDirty(void);
        BOOL FIsEmbedded(void);
        void SendAdvise(UINT);

        //CHAPTER23MOD
        HRESULT  InPlaceActivate(LPOLECLIENTSITE, BOOL);
        void     InPlaceDeactivate(void);
        HRESULT  UIActivate(void);
        void     UIDeactivate(void);
        BOOL     InPlaceMenuCreate(void);
        BOOL     InPlaceMenuDestroy(void);
        BOOL     InPlaceToolsCreate(void);
        BOOL     InPlaceToolsDestroy(void);
        BOOL     InPlaceToolsRenegotiate(void);

        void     OpenIntoWindow(void);
        BOOL     Undo(void);
        //End CHAPTER23MOD
    };

typedef CFigure *PCFigure;

//Codes for CFigure::SendAdvise
//......Code......................Method called in CFigureSendAdvise...
#define OBJECTCODE_SAVED       0  //IOleAdviseHolder::SendOnSave
#define OBJECTCODE_CLOSED      1  //IOleAdviseHolder::SendOnClose
#define OBJECTCODE_RENAMED     2  //IOleAdviseHolder::SendOnRename
#define OBJECTCODE_SAVEOBJECT  3  //IOleClientSite::SaveObject
#define OBJECTCODE_DATACHANGED 4  //IDataAdviseHolder::SendOnDataChange
#define OBJECTCODE_SHOWWINDOW  5  //IOleClientSite::OnShowWindow(TRUE)
#define OBJECTCODE_HIDEWINDOW  6  //IOleClientSite::OnShowWindow(FALSE)
#define OBJECTCODE_SHOWOBJECT  7  //IOleClientSite::ShowObject


//IPERSTOR.CPP

class CImpIPersistStorage : public IPersistStorage
    {
    protected:
        ULONG               m_cRef;
        PCFigure            m_pObj;
        LPUNKNOWN           m_pUnkOuter;
        PSSTATE             m_psState;      //Storage state
        BOOL                m_fConvert;     //Are we Converting?

    public:
        CImpIPersistStorage(PCFigure, LPUNKNOWN);
        ~CImpIPersistStorage(void);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetClassID(LPCLSID);

        STDMETHODIMP IsDirty(void);
        STDMETHODIMP InitNew(LPSTORAGE);
        STDMETHODIMP Load(LPSTORAGE);
        STDMETHODIMP Save(LPSTORAGE, BOOL);
        STDMETHODIMP SaveCompleted(LPSTORAGE);
        STDMETHODIMP HandsOffStorage(void);
    };



//IDATAOBJ.CPP
class CImpIDataObject : public IDataObject
    {
    private:
        ULONG           m_cRef;
        PCFigure        m_pObj;
        LPUNKNOWN       m_pUnkOuter;

    public:
        CImpIDataObject(PCFigure, LPUNKNOWN);
        ~CImpIDataObject(void);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IDataObject members
        STDMETHODIMP GetData(LPFORMATETC, LPSTGMEDIUM);
        STDMETHODIMP GetDataHere(LPFORMATETC, LPSTGMEDIUM);
        STDMETHODIMP QueryGetData(LPFORMATETC);
        STDMETHODIMP GetCanonicalFormatEtc(LPFORMATETC, LPFORMATETC);
        STDMETHODIMP SetData(LPFORMATETC, LPSTGMEDIUM, BOOL);
        STDMETHODIMP EnumFormatEtc(DWORD, LPENUMFORMATETC *);
        STDMETHODIMP DAdvise(LPFORMATETC, DWORD,  LPADVISESINK
                         , DWORD *);
        STDMETHODIMP DUnadvise(DWORD);
        STDMETHODIMP EnumDAdvise(LPENUMSTATDATA *);
    };


//IOLEOBJ.CPP
class CImpIOleObject : public IOleObject
    {
    private:
        ULONG           m_cRef;
        PCFigure        m_pObj;
        LPUNKNOWN       m_pUnkOuter;

    public:
        CImpIOleObject(PCFigure, LPUNKNOWN);
        ~CImpIOleObject(void);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IOleObject members
        STDMETHODIMP SetClientSite(LPOLECLIENTSITE);
        STDMETHODIMP GetClientSite(LPOLECLIENTSITE *);
        STDMETHODIMP SetHostNames(LPCOLESTR, LPCOLESTR);
        STDMETHODIMP Close(DWORD);
        STDMETHODIMP SetMoniker(DWORD, LPMONIKER);
        STDMETHODIMP GetMoniker(DWORD, DWORD, LPMONIKER *);
        STDMETHODIMP InitFromData(LPDATAOBJECT, BOOL, DWORD);
        STDMETHODIMP GetClipboardData(DWORD, LPDATAOBJECT *);
        STDMETHODIMP DoVerb(LONG, LPMSG, LPOLECLIENTSITE, LONG, HWND
                         , LPCRECT);
        STDMETHODIMP EnumVerbs(LPENUMOLEVERB *);
        STDMETHODIMP Update(void);
        STDMETHODIMP IsUpToDate(void);
        STDMETHODIMP GetUserClassID(CLSID *);
        STDMETHODIMP GetUserType(DWORD, LPOLESTR *);
        STDMETHODIMP SetExtent(DWORD, LPSIZEL);
        STDMETHODIMP GetExtent(DWORD, LPSIZEL);
        STDMETHODIMP Advise(LPADVISESINK, DWORD *);
        STDMETHODIMP Unadvise(DWORD);
        STDMETHODIMP EnumAdvise(LPENUMSTATDATA *);
        STDMETHODIMP GetMiscStatus(DWORD, DWORD *);
        STDMETHODIMP SetColorScheme(LPLOGPALETTE);
    };



class CImpIPersistFile : public IPersistFile
    {
    protected:
        ULONG               m_cRef;
        PCFigure            m_pObj;
        LPUNKNOWN           m_pUnkOuter;

    public:
        CImpIPersistFile(PCFigure, LPUNKNOWN);
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



//CHAPTER23MOD
//IIPOBJ.CPP
class CImpIOleInPlaceObject : public IOleInPlaceObject
    {
    protected:
        ULONG               m_cRef;
        PCFigure            m_pObj;
        LPUNKNOWN           m_pUnkOuter;

    public:
        CImpIOleInPlaceObject(PCFigure, LPUNKNOWN);
        ~CImpIOleInPlaceObject(void);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetWindow(HWND *);
        STDMETHODIMP ContextSensitiveHelp(BOOL);
        STDMETHODIMP InPlaceDeactivate(void);
        STDMETHODIMP UIDeactivate(void);
        STDMETHODIMP SetObjectRects(LPCRECT, LPCRECT);
        STDMETHODIMP ReactivateAndUndo(void);
    };



//IIPAOBJ.CPP
class CImpIOleInPlaceActiveObject
    : public IOleInPlaceActiveObject
    {
    protected:
        ULONG               m_cRef;
        PCFigure            m_pObj;
        LPUNKNOWN           m_pUnkOuter;

    public:
        CImpIOleInPlaceActiveObject(PCFigure, LPUNKNOWN);
        ~CImpIOleInPlaceActiveObject(void);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetWindow(HWND *);
        STDMETHODIMP ContextSensitiveHelp(BOOL);
        STDMETHODIMP TranslateAccelerator(LPMSG);
        STDMETHODIMP OnFrameWindowActivate(BOOL);
        STDMETHODIMP OnDocWindowActivate(BOOL);
        STDMETHODIMP ResizeBorder(LPCRECT, LPOLEINPLACEUIWINDOW
                         , BOOL);
        STDMETHODIMP EnableModeless(BOOL);
    };

//End CHAPTER23MOD

#endif _COSMOLE_H_
