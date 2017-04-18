/*
 * POLYLINE.H
 * Polyline Component Chapter 21
 *
 * Definitions and function prototypes
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _POLYLINE_H_
#define _POLYLINE_H_

#define INC_CLASSLIB
#define INC_CONTROLS
//CHAPTER21MOD
#define INC_OLEUI
#define CHAPTER21
//CHAPTER21MOD
#include <inole.h>
#include <ipoly10.h>
#include "resource.h"


//Classname
#define SZCLASSPOLYLINE             TEXT("polyline")

//Stream Name that holds the data
#define SZSTREAM                    OLETEXT("CONTENTS")

#define SZPOLYFRAMETITLE            TEXT("Polyline Figure in %s")

//Magic number to add to aspects returned from IViewObject::Freeze
#define FREEZE_KEY_OFFSET           0x0723

#define HIMETRIC_PER_INCH           2540
#define CCHPATHMAX                  256

//Window extra bytes and offsets
#define CBPOLYLINEWNDEXTRA          (sizeof(LONG))
#define PLWL_STRUCTURE              0


//DLLPOLY.CPP
int PASCAL LibMain(HINSTANCE, WORD, WORD, LPSTR);

//This class factory object creates Polyline objects.

class CPolylineClassFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;

    public:
        CPolylineClassFactory(void);
        ~CPolylineClassFactory(void);

        //IUnknown members
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP         CreateInstance(LPUNKNOWN, REFIID
                                 , PPVOID);
        STDMETHODIMP         LockServer(BOOL);
    };

typedef CPolylineClassFactory *PCPolylineClassFactory;



//POLYWIN.CPP
LRESULT APIENTRY PolylineWndProc(HWND, UINT, WPARAM, LPARAM);


#ifdef WIN32
#define PROP_POINTER    TEXT("Pointer")
#else
#define PROP_SELECTOR   "Selector"
#define PROP_OFFSET     "Offset"
#endif

BOOL APIENTRY PolyDlgProc(HWND, UINT, WPARAM, LPARAM);

//Forward class references
class CImpIPolyline;
typedef class CImpIPolyline *PCImpIPolyline;

class CImpIConnPtCont;
typedef CImpIConnPtCont *PCImpIConnPtCont;

class CConnectionPoint;
typedef CConnectionPoint *PCConnectionPoint;

class CImpIPersistStorage;
typedef class CImpIPersistStorage *PCImpIPersistStorage;

class CImpIPersistStreamInit;
typedef class CImpIPersistStreamInit *PCImpIPersistStreamInit;

class CImpIDataObject;
typedef class CImpIDataObject *PCImpIDataObject;

class CImpIOleObject;
typedef class CImpIOleObject *PCImpIOleObject;

class CImpIViewObject;
typedef class CImpIViewObject *PCImpIViewObject;

class CImpIRunnableObject;
typedef class CImpIRunnableObject *PCImpIRunnableObject;

//CHAPTER21MOD
class CImpIExternalConnection;
typedef class CImpIExternalConnection *PCImpIExternalConnection;
//End CHAPTER21MOD


//POLYLINE.CPP
class CPolyline : public IUnknown
    {
    friend LRESULT APIENTRY PolylineWndProc(HWND, UINT, WPARAM
        , LPARAM);

    friend class CImpIPolyline;
    friend class CImpIConnPtCont;
    friend class CConnectionPoint;
    friend class CImpIPersistStorage;
    friend class CImpIPersistStreamInit;
    friend class CImpIDataObject;

    friend BOOL APIENTRY PolyDlgProc(HWND, UINT, WPARAM, LPARAM);
    friend class CImpIOleObject;
    friend class CImpIViewObject;
    friend class CImpIRunnableObject;

    //CHAPTER21MOD
    friend class CImpIExternalConnection;
    //End CHAPTER21MOD

    protected:
        HWND            m_hWnd;
        HINSTANCE       m_hInst;

        ULONG           m_cRef;         //Object reference count
        LPUNKNOWN       m_pUnkOuter;    //Controlling Unknown
        PFNDESTROYED    m_pfnDestroy;   //Function called on closure
        BOOL            m_fDirty;       //Have we changed?
        POLYLINEDATA    m_pl;           //Our actual data

        //Contained interfaces
        PCImpIPolyline          m_pImpIPolyline;
        PCImpIConnPtCont        m_pImpIConnPtCont;
        PCImpIPersistStorage    m_pImpIPersistStorage;
        PCImpIPersistStreamInit m_pImpIPersistStreamInit;
        PCImpIDataObject        m_pImpIDataObject;

        /*
         * Connected sink:  only one per object.  We get this
         * through our connection point.
         */
        IPolylineAdviseSink10  *m_pAdv;
        PCConnectionPoint       m_pConnPt;

        PCStringTable   m_pST;          //Object strings
        UINT            m_cf;           //Object clipboard format
        CLSID           m_clsID;        //Current CLSID

        //We have to hold these for IPersistStorage::Save
        LPSTORAGE       m_pIStorage;
        LPSTREAM        m_pIStream;

        LPDATAADVISEHOLDER  m_pIDataAdviseHolder;

        //These are default handler interfaces we use
        LPUNKNOWN           m_pDefIUnknown;
        LPVIEWOBJECT2       m_pDefIViewObject;
        LPPERSISTSTORAGE    m_pDefIPersistStorage;
        LPDATAOBJECT        m_pDefIDataObject;

        //Implemented and used interfaces
        PCImpIOleObject     m_pImpIOleObject;       //Implemented
        LPOLEADVISEHOLDER   m_pIOleAdviseHolder;    //Used

        LPOLECLIENTSITE     m_pIOleClientSite;      //Used

        PCImpIViewObject    m_pImpIViewObject;      //Implemented
        LPADVISESINK        m_pIAdviseSink;         //Used
        DWORD               m_dwFrozenAspects;      //Freeze
        DWORD               m_dwAdviseAspects;      //SetAdvise
        DWORD               m_dwAdviseFlags;        //SetAdvise

        POLYLINEDATA        m_plContent;            //For freezing
        POLYLINEDATA        m_plThumbnail;          //For freezing

        PCImpIRunnableObject m_pImpIRunnableObject; //Implemented
        HWND                m_hDlg;                 //Editing window

        //CHAPTER21MOD
        PCImpIExternalConnection m_pImpIExternalConnection; //Implemented
        BOOL                     m_fLockContainer;
        DWORD                    m_dwRegROT;
        //End CHAPTER21MOD


    protected:
        void      PointScale(LPRECT, LPPOINTS, BOOL);
        void      Draw(HDC, BOOL, BOOL, LPRECT, PPOLYLINEDATA);
        HINSTANCE Instance(void);
        LPTSTR    String(UINT);
        void      SendAdvise(UINT);
        void      RectConvertMappings(LPRECT, BOOL);

        /*
         * These members pulled from IPolyline now serve as a
         * central store for this functionality to be used from
         * other interfaces like IPersistStorage and IDataObject.
         * Other interfaces later may also use them.
         */
        STDMETHODIMP DataSet(PPOLYLINEDATA, BOOL, BOOL);
        STDMETHODIMP DataGet(PPOLYLINEDATA);

        STDMETHODIMP RenderNative(HGLOBAL *);
        STDMETHODIMP RenderBitmap(HBITMAP *);
        STDMETHODIMP RenderMetafilePict(HGLOBAL *);


    public:
        CPolyline(LPUNKNOWN, PFNDESTROYED, HINSTANCE);
        ~CPolyline(void);

        BOOL      Init(void);

        //Non-delegating object IUnknown
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);
    };

typedef CPolyline *PCPolyline;


//Codes for CPolyline::SendAdvise
//......Code.....................Method called in CPolyline::SendAdvise
#define OBJECTCODE_SAVED       0 //IOleAdviseHolder::SendOnSave
#define OBJECTCODE_CLOSED      1 //IOleAdviseHolder::SendOnClose
#define OBJECTCODE_RENAMED     2 //IOleAdviseHolder::SendOnRename
#define OBJECTCODE_SAVEOBJECT  3 //IOleClientSite::SaveObject
#define OBJECTCODE_DATACHANGED 4 //IDataAdviseHolder::SendOnDataChange
#define OBJECTCODE_SHOWWINDOW  5 //IOleClientSite::OnShowWindow(TRUE)
#define OBJECTCODE_HIDEWINDOW  6 //IOleClientSite::OnShowWindow(FALSE)
#define OBJECTCODE_SHOWOBJECT  7 //IOleClientSite::ShowObject



//Interface implementation contained in the Polyline.

class CImpIPolyline : public IPolyline10
    {
    protected:
        ULONG               m_cRef;      //Interface reference count
        PCPolyline          m_pObj;      //Back pointer to object
        LPUNKNOWN           m_pUnkOuter; //Controlling unknown

    public:
        CImpIPolyline(PCPolyline, LPUNKNOWN);
        ~CImpIPolyline(void);

        //IUnknown members.
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //Manipulation members:
        STDMETHODIMP Init(HWND, LPRECT, DWORD, UINT);
        STDMETHODIMP New(void);
        STDMETHODIMP Undo(void);
        STDMETHODIMP Window(HWND *);

        STDMETHODIMP RectGet(LPRECT);
        STDMETHODIMP SizeGet(LPRECT);
        STDMETHODIMP RectSet(LPRECT, BOOL);
        STDMETHODIMP SizeSet(LPRECT, BOOL);

        STDMETHODIMP ColorSet(UINT, COLORREF, COLORREF *);
        STDMETHODIMP ColorGet(UINT, COLORREF *);

        STDMETHODIMP LineStyleSet(UINT, UINT *);
        STDMETHODIMP LineStyleGet(UINT *);
    };


class CImpIConnPtCont : public IConnectionPointContainer
    {
    private:
        ULONG               m_cRef;      //Interface ref count
        PCPolyline          m_pObj;      //Back pointer to object
        LPUNKNOWN           m_pUnkOuter; //Controlling unknown

    public:
        CImpIConnPtCont(PCPolyline, LPUNKNOWN);
        ~CImpIConnPtCont(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);

        //IConnectionPointContainer members
        STDMETHODIMP EnumConnectionPoints(IEnumConnectionPoints **);
	    STDMETHODIMP FindConnectionPoint(REFIID, IConnectionPoint **);
    };


/*
 * This connection point will only allow one connection,
 * so it always returns the same connection key.  It also
 * doesn't bother to implement enumerations.
 */

#define CCONNMAX    1
#define ADVISEKEY   72388       //Arbitrary

class CConnectionPoint : public IConnectionPoint
    {
    private:
        ULONG           m_cRef;     //Object reference count
        PCPolyline      m_pObj;     //Containing object.

    public:
        CConnectionPoint(PCPolyline);
        ~CConnectionPoint(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IConnectionPoint members
        STDMETHODIMP GetConnectionInterface(IID *);
        STDMETHODIMP GetConnectionPointContainer
            (IConnectionPointContainer **);
        STDMETHODIMP Advise(LPUNKNOWN, DWORD *);
        STDMETHODIMP Unadvise(DWORD);
        STDMETHODIMP EnumConnections(IEnumConnections **);
    };



class CImpIPersistStorage : public IPersistStorage
    {
    protected:
        ULONG               m_cRef;      //Interface reference count
        PCPolyline          m_pObj;      //Back pointer to object
        LPUNKNOWN           m_pUnkOuter; //Controlling unknown
        PSSTATE             m_psState;   //Storage state

    public:
        CImpIPersistStorage(PCPolyline, LPUNKNOWN);
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


class CImpIPersistStreamInit : public IPersistStreamInit
    {
    protected:
        ULONG               m_cRef;      //Interface reference count
        PCPolyline          m_pObj;      //Back pointer to object
        LPUNKNOWN           m_pUnkOuter; //Controlling unknown

    public:
        CImpIPersistStreamInit(PCPolyline, LPUNKNOWN);
        ~CImpIPersistStreamInit(void);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetClassID(LPCLSID);

        STDMETHODIMP IsDirty(void);
        STDMETHODIMP Load(LPSTREAM);
        STDMETHODIMP Save(LPSTREAM, BOOL);
        STDMETHODIMP GetSizeMax(ULARGE_INTEGER *);
        STDMETHODIMP InitNew(void);
    };


//IDATAOBJ.CPP
class CImpIDataObject : public IDataObject
    {
    private:
        ULONG               m_cRef;      //Interface reference count
        PCPolyline          m_pObj;      //Back pointer to object
        LPUNKNOWN           m_pUnkOuter; //Controlling unknown

    public:
        CImpIDataObject(PCPolyline, LPUNKNOWN);
        ~CImpIDataObject(void);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IDataObject members
        STDMETHODIMP GetData(LPFORMATETC, LPSTGMEDIUM);
        STDMETHODIMP GetDataHere(LPFORMATETC, LPSTGMEDIUM);
        STDMETHODIMP QueryGetData(LPFORMATETC);
        STDMETHODIMP GetCanonicalFormatEtc(LPFORMATETC,LPFORMATETC);
        STDMETHODIMP SetData(LPFORMATETC, LPSTGMEDIUM, BOOL);
        STDMETHODIMP EnumFormatEtc(DWORD, LPENUMFORMATETC *);
        STDMETHODIMP DAdvise(LPFORMATETC, DWORD, LPADVISESINK
            , DWORD *);
        STDMETHODIMP DUnadvise(DWORD);
        STDMETHODIMP EnumDAdvise(LPENUMSTATDATA *);
    };



//IENUMFE.CPP
class CEnumFormatEtc : public IEnumFORMATETC
    {
    private:
        ULONG           m_cRef;
        LPUNKNOWN       m_pUnkRef;
        ULONG           m_iCur;
        ULONG           m_cfe;
        LPFORMATETC     m_prgfe;

    public:
        CEnumFormatEtc(LPUNKNOWN, ULONG, LPFORMATETC);
        ~CEnumFormatEtc(void);

        //IUnknown members that delegate to m_pUnkRef.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IEnumFORMATETC members
        STDMETHODIMP Next(ULONG, LPFORMATETC, ULONG *);
        STDMETHODIMP Skip(ULONG);
        STDMETHODIMP Reset(void);
        STDMETHODIMP Clone(IEnumFORMATETC **);
    };


typedef CEnumFormatEtc *PCEnumFormatEtc;



class CImpIOleObject : public IOleObject
    {
    private:
        ULONG           m_cRef;
        PCPolyline      m_pObj;
        LPUNKNOWN       m_pUnkOuter;

    public:
        CImpIOleObject(PCPolyline, LPUNKNOWN);
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
        STDMETHODIMP DoVerb(LONG, LPMSG, LPOLECLIENTSITE, LONG
                         , HWND, LPCRECT);
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


//IVIEWOBJ.CPP
class CImpIViewObject : public IViewObject2
    {
    private:
        ULONG           m_cRef;
        PCPolyline      m_pObj;
        LPUNKNOWN       m_pUnkOuter;

    public:
        CImpIViewObject(PCPolyline, LPUNKNOWN);
        ~CImpIViewObject(void);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IViewObject members
        STDMETHODIMP Draw(DWORD, LONG, LPVOID
            , DVTARGETDEVICE *, HDC, HDC, LPCRECTL
            , LPCRECTL, BOOL (CALLBACK *)(DWORD), DWORD);
        STDMETHODIMP GetColorSet(DWORD, LONG, LPVOID
            , DVTARGETDEVICE *, HDC, LPLOGPALETTE *);
        STDMETHODIMP Freeze(DWORD, LONG, LPVOID, LPDWORD);
        STDMETHODIMP Unfreeze(DWORD);
        STDMETHODIMP SetAdvise(DWORD, DWORD, LPADVISESINK);
        STDMETHODIMP GetAdvise(LPDWORD, LPDWORD, LPADVISESINK *);
        STDMETHODIMP GetExtent(DWORD, LONG, DVTARGETDEVICE *
            , LPSIZEL);
    };


class CImpIRunnableObject : public IRunnableObject
    {
    protected:
        ULONG           m_cRef;
        PCPolyline      m_pObj;
        LPUNKNOWN       m_pUnkOuter;

    public:
        CImpIRunnableObject(PCPolyline, LPUNKNOWN);
        ~CImpIRunnableObject(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetRunningClass(LPCLSID);
        STDMETHODIMP Run(LPBINDCTX);
        STDMETHODIMP_(BOOL) IsRunning(void);
        STDMETHODIMP LockRunning(BOOL, BOOL);
        STDMETHODIMP SetContainedObject(BOOL);
    };


//CHAPTER21MOD
class CImpIExternalConnection : public IExternalConnection
    {
    protected:
        ULONG           m_cRef;
        PCPolyline      m_pObj;
        LPUNKNOWN       m_pUnkOuter;
        DWORD           m_cLockStrong;

    public:
        CImpIExternalConnection(PCPolyline, LPUNKNOWN);
        ~CImpIExternalConnection(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP_(DWORD) AddConnection(DWORD, DWORD);
        STDMETHODIMP_(DWORD) ReleaseConnection(DWORD, DWORD, BOOL);
    };
//End CHAPTER21MOD


#endif  //_POLYLINE_H_
