/*
 * BEEPER.H
 * Beeper Automation Object #3 Chapter 14
 *
 * Classes that implement the Beeper object.
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
#define CHAPTER14
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
class CImpISupportErrorInfo;
typedef CImpISupportErrorInfo *PCImpISupportErrorInfo;


class CBeeper : public IBeeper
    {
    friend CImpIDispatch;

    protected:
        ULONG           m_cRef;             //Object reference count
        LPUNKNOWN       m_pUnkOuter;        //Controlling unknown
        PFNDESTROYED    m_pfnDestroy;       //To call on closure

        long            m_lSound;

        //Our interfaces
        PCImpIDispatch         m_pImpIDispatch;
        PCImpISupportErrorInfo m_pImpISuppErr;

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

        ITypeInfo      *m_pITINeutral;      //Type information
        ITypeInfo      *m_pITIGerman;

    public:
        CImpIDispatch(PCBeeper, LPUNKNOWN);
        ~CImpIDispatch(void);

        //For raising exceptions
        void                 Exception(WORD);


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


/*
 * ISupportErrorInfo interface implementations for the Beeper.
 */

class CImpISupportErrorInfo : public ISupportErrorInfo
    {
    public:
        ULONG           m_cRef;     //For debugging

    private:
        PCBeeper        m_pObj;
        LPUNKNOWN       m_pUnkOuter;

    public:
        CImpISupportErrorInfo(PCBeeper, LPUNKNOWN);
        ~CImpISupportErrorInfo(void);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //ISupportErrorInfo members
        STDMETHODIMP InterfaceSupportsErrorInfo(REFIID);
    };



#endif //_BEEPER_H_
