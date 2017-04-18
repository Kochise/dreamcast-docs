/*
 * COSMOLE.H
 * Cosmo Chapter 18
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


class CFigure : public IUnknown
    {
    friend class CImpIPersistStorage;
    friend class CImpIDataObject;
    friend class CImpIOleObject;

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


#endif _COSMOLE_H_
