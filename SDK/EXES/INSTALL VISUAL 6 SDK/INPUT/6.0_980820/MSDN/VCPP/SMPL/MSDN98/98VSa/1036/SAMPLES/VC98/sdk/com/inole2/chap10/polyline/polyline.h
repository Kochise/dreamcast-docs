/*
 * POLYLINE.H
 * Polyline Component Chapter 10
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
//CHAPTER10MOD
#define CHAPTER10
#include <inole.h>
#include <ipoly10.h>
#include "resource.h"
//End CHAPTER10MOD


//Classname
#define SZCLASSPOLYLINE             TEXT("polyline")

//Stream Name that holds the data
#define SZSTREAM                    OLETEXT("CONTENTS")


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


//CHAPTER10MOD
class CImpIDataObject;
typedef class CImpIDataObject *PCImpIDataObject;

#define CFORMATETCGET       3
#define CFORMATETCSET       1
//End CHAPTER10MOD


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

    //CHAPTER10MOD
    friend class CImpIDataObject;
    //End CHAPTER10MOD

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
        //CHAPTER10MOD
        PCImpIDataObject        m_pImpIDataObject;
        //End CHAPTER10MOD

        /*
         * Connected sink:  only one per object.  We get this
         * through our connection point.
         */
        //CHAPTER10MOD
        IPolylineAdviseSink10  *m_pAdv;
        //End CHAPTER10MOD
        PCConnectionPoint       m_pConnPt;

        PCStringTable   m_pST;          //Object strings
        UINT            m_cf;           //Object clipboard format
        CLSID           m_clsID;        //Current CLSID

        //We have to hold these for IPersistStorage::Save
        LPSTORAGE       m_pIStorage;
        LPSTREAM        m_pIStream;

        //CHAPTER10MOD
        LPDATAADVISEHOLDER  m_pIDataAdviseHolder;
        //End CHAPTER10MOD


    protected:
        void      PointScale(LPRECT, LPPOINTS, BOOL);
        void      Draw(HDC, BOOL, BOOL);
        void      RectConvertMappings(LPRECT, BOOL);

        //CHAPTER10MOD
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
        //End CHAPTER10MOD


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




//Interface implementations contained in the Polyline.

//CHPATER10MOD
class CImpIPolyline : public IPolyline10
//End CHAPTER10MOD
    {
    protected:
        ULONG               m_cRef;      //Interface ref count
        PCPolyline          m_pObj;      //Backpointer to object
        LPUNKNOWN           m_pUnkOuter; //Controlling unknown

    public:
        CImpIPolyline(PCPolyline, LPUNKNOWN);
        ~CImpIPolyline(void);

        //IUnknown members.
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //CHAPTER10MOD
        //Data* and Render* replaced with IDataObject
        //End CHAPTER10MOD

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


//CHAPTER10MOD
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

//End CHAPTER10MOD

#endif  //_POLYLINE_H_
