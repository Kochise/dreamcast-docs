/*
 * BEEPER.H
 * Beeper Object #6 with Property Pages Chapter 16
 *
 * Classes that implement the Beeper object for supporting
 * property pages.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _BEEPER_H_
#define _BEEPER_H_

/*
 * This #define tells <bookguid.h> to not define GUIDs that will
 * be defined in MKTYPLIB-generated header files, like ibeeper.h.
 */
#define GUIDS_FROM_TYPELIB
#define INC_AUTOMATION
//CHAPTER16MOD
#define INC_CONTROLS
#define CHAPTER16
//End CHAPTER16MOD
#include <inole.h>
#include <malloc.h>

//This file is generated from MKTYPLIB
#include "ibeeper.h"

//Help context ID for exceptions
#define HID_SOUND_PROPERTY_LIMITATIONS  0x1E100

//English exception strings
#define IDS_0_MIN                   16
#define IDS_0_EXCEPTIONSOURCE       (IDS_0_MIN)
#define IDS_0_EXCEPTIONINVALIDSOUND (IDS_0_MIN+1)

//German exception strings
#define IDS_7_MIN                   32
#define IDS_7_EXCEPTIONSOURCE       (IDS_7_MIN)
#define IDS_7_EXCEPTIONINVALIDSOUND (IDS_7_MIN+1)


//Forward class declarations for friend statements
class CImpIDispatch;
typedef CImpIDispatch *PCImpIDispatch;

//CHAPTER16MOD
class CImpISpecifyPP;
typedef CImpISpecifyPP *PCImpISpecifyPP;

class CImpIConnPtCont;
typedef CImpIConnPtCont *PCImpIConnPtCont;

class CConnectionPoint;
typedef CConnectionPoint *PCConnectionPoint;

//Number of property pages we support
#define CPROPPAGES      1
//End CHAPTER16MOD

class CBeeper : public IBeeper
    {
    friend CImpIDispatch;
    //CHAPTER16MOD
    friend CImpISpecifyPP;
    friend CImpIConnPtCont;
    friend CConnectionPoint;
    //End CHAPTER16MOD

    protected:
        ULONG           m_cRef;             //Object reference count
        LPUNKNOWN       m_pUnkOuter;        //Controlling unknown
        PFNDESTROYED    m_pfnDestroy;       //To call on closure

        long            m_lSound;
        PCImpIDispatch  m_pImpIDispatch;    //Our IDispatch

        //CHAPTER16MOD
        PCImpISpecifyPP  m_pImpISpecifyPP;   //Our ISpecifyPropertyPages
        PCImpIConnPtCont m_pImpIConnPtCont;  //Our IConnectionPointContainer

        IPropertyNotifySink *m_pIPropNotifySink;    //Client's
        PCConnectionPoint    m_pConnPt;             //Ours
        //End CHAPTER16MOD

    public:
        CBeeper(LPUNKNOWN, PFNDESTROYED);
        ~CBeeper(void);

        BOOL         Init(void);

        //Non-delegating object IUnknown
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IBeeper functions
        STDMETHODIMP_(long)  get_Sound(void);
        STDMETHODIMP_(void)  put_Sound(long);
        STDMETHODIMP_(long)  Beep(void);
    };

typedef CBeeper *PCBeeper;


//DISPIDs for our dispinterface
enum
    {
    PROPERTY_SOUND=0,
    METHOD_BEEP
    };

/*
 * IDispatch interface implementations for the Beeper.
 */

class CImpIDispatch : public IDispatch
    {
    public:
        ULONG           m_cRef;     //For debugging

    private:
        PCBeeper        m_pObj;
        LPUNKNOWN       m_pUnkOuter;
        WORD            m_wException;

        ITypeInfo      *m_pITINeutral;      //Type information
        ITypeInfo      *m_pITIGerman;

    public:
        CImpIDispatch(PCBeeper, LPUNKNOWN);
        ~CImpIDispatch(void);

        /*
         * This function is called from CBeeper functions that
         * are called from within DispInvoke to set an exception.
         * This is because the CBeeper functions have no way to
         * tell DispInvoke of such exceptions, so we have to
         * tell our IDispatch::Invoke implementation directly.
         */
        void Exception(WORD);

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


//Exceptions we can throw from IDispatch::Invoke
enum
    {
    EXCEPTION_NONE=0,
    EXCEPTION_INVALIDSOUND=1000
    };


//Exception filling function for the EXCEPINFO structure.
HRESULT STDAPICALLTYPE FillException(EXCEPINFO *);

//CHAPTER16MOD

class CImpISpecifyPP : public ISpecifyPropertyPages
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        PCBeeper        m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpISpecifyPP(PCBeeper, LPUNKNOWN);
        ~CImpISpecifyPP(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetPages(CAUUID *);
    };



//CONNPT.CPP

class CImpIConnPtCont : public IConnectionPointContainer
    {
    private:
        ULONG               m_cRef;      //Interface ref count
        PCBeeper            m_pObj;      //Backpointer to object
        LPUNKNOWN           m_pUnkOuter; //Controlling unknown

    public:
        CImpIConnPtCont(PCBeeper, LPUNKNOWN);
        ~CImpIConnPtCont(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);

        //IConnectionPointContainer members
        STDMETHODIMP EnumConnectionPoints(IEnumConnectionPoints **);
	    STDMETHODIMP FindConnectionPoint(REFIID, IConnectionPoint **);
    };


//This object only supports one connection per point
#define CCONNMAX    1
#define ADVISEKEY   72388       //Arbitrary

class CConnectionPoint : public IConnectionPoint
    {
    private:
        ULONG           m_cRef;     //Object reference count
        PCBeeper        m_pObj;     //Containing object.

    public:
        CConnectionPoint(PCBeeper);
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


//End CHAPTER16MOD

#endif //_BEEPER_H_
