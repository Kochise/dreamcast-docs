/*
 * HCOSMO.H
 * Cosmo Handler Chapter 19
 *
 * Definitions and function prototypes for the Cosmo Handler.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _HCOSMO_H_
#define _HCOSMO_H_

#define CHAPTER19
#include <inole.h>
#include <ipoly10.h>      //For POLYLINEDATA definitions


#define HIMETRIC_PER_INCH           2540

//Stream name in the object storage
#define SZSTREAM                    OLETEXT("CONTENTS")


//HCOSMO.CPP

class CFigureClassFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;         //Reference count on object

    public:
        CFigureClassFactory(void);
        ~CFigureClassFactory(void);

        //IUnknown members
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP    CreateInstance(LPUNKNOWN, REFIID, PPVOID);
        STDMETHODIMP    LockServer(BOOL);
    };

typedef CFigureClassFactory *PCFigureClassFactory;


//Magic number to add to aspects returned from IViewObject::Freeze
#define FREEZE_KEY_OFFSET       0x0723



//Forward class references
class CImpIOleObject;
typedef class CImpIOleObject *PCImpIOleObject;
class CImpIViewObject2;
typedef class CImpIViewObject2 *PCImpIViewObject2;
class CImpIPersistStorage;
typedef class CImpIPersistStorage *PCImpIPersistStorage;
class CImpIAdviseSink;
typedef class CImpIAdviseSink *PCImpIAdviseSink;


//HCOSMO.CPP

class CFigure : public IUnknown
    {
    friend class CImpIOleObject;
    friend class CImpIViewObject2;
    friend class CImpIPersistStorage;
    friend class CImpIAdviseSink;

    protected:
        ULONG                m_cRef;
        LPUNKNOWN            m_pUnkOuter;
        PFNDESTROYED         m_pfnDestroy;

        POLYLINEDATA         m_pl;          //Our actual data.
        UINT                 m_cf;          //Obj clipboard format.
        CLSID                m_clsID;       //Current CLSID

        //These are default handler interfaces we use
        LPUNKNOWN            m_pDefIUnknown;
        LPOLEOBJECT          m_pDefIOleObject;
        LPVIEWOBJECT2        m_pDefIViewObject2;
        LPPERSISTSTORAGE     m_pDefIPersistStorage;
        LPDATAOBJECT         m_pDefIDataObject;

        //Implemented interfaces
        PCImpIOleObject      m_pImpIOleObject;
        PCImpIViewObject2    m_pImpIViewObject2;
        PCImpIPersistStorage m_pImpIPersistStorage;
        PCImpIAdviseSink     m_pImpIAdviseSink;

        //Advise sink we get in IViewObject
        LPADVISESINK         m_pIAdvSinkView;
        DWORD                m_dwAdviseFlags;
        DWORD                m_dwAdviseAspects;
        DWORD                m_dwFrozenAspects;

        //Copies of frozen aspects
        POLYLINEDATA         m_plContent;
        POLYLINEDATA         m_plThumbnail;


    protected:
        void      Draw(HDC, LPRECT, DWORD, DVTARGETDEVICE *
                      , HDC, PPOLYLINEDATA);
        void      PointScale(LPRECT, LPPOINTS, BOOL);

    public:
        CFigure(LPUNKNOWN, PFNDESTROYED, HINSTANCE);
        ~CFigure(void);

        BOOL      Init(void);

        //Non-delegating object IUnknown
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);
    };

typedef CFigure *PCFigure;



class CImpIPersistStorage : public IPersistStorage
    {
    protected:
        ULONG               m_cRef;
        PCFigure            m_pObj;
        LPUNKNOWN           m_pUnkOuter;
        PSSTATE             m_psState;   //Storage state
        BOOL                m_fConvert;  //Are we Converting?

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


class CImpIViewObject2 : public IViewObject2
    {
    private:
        ULONG           m_cRef;
        PCFigure        m_pObj;
        LPUNKNOWN       m_pUnkOuter;

    public:
        CImpIViewObject2(PCFigure, LPUNKNOWN);
        ~CImpIViewObject2(void);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IViewObject2 members
        STDMETHODIMP Draw(DWORD, LONG, LPVOID, DVTARGETDEVICE *
            , HDC, HDC, LPCRECTL, LPCRECTL
            , BOOL (CALLBACK *)(DWORD), DWORD);
        STDMETHODIMP GetColorSet(DWORD, LONG, LPVOID
            , DVTARGETDEVICE *, HDC, LPLOGPALETTE *);
        STDMETHODIMP Freeze(DWORD, LONG, LPVOID, LPDWORD);
        STDMETHODIMP Unfreeze(DWORD);
        STDMETHODIMP SetAdvise(DWORD, DWORD, LPADVISESINK);
        STDMETHODIMP GetAdvise(LPDWORD, LPDWORD, LPADVISESINK *);
        STDMETHODIMP GetExtent(DWORD, LONG, DVTARGETDEVICE *
            , LPSIZEL);
    };


class CImpIAdviseSink : public IAdviseSink
    {
    protected:
        ULONG           m_cRef;
        PCFigure        m_pObj;
        LPUNKNOWN       m_pUnkOuter;

    public:
        CImpIAdviseSink(PCFigure, LPUNKNOWN);
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


#endif  //_HCOSMO_H_
