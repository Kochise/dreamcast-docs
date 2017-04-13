/*
 * BEEPER.H
 * Beeper Automation Object #5 Chapter 14
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
#define INC_CONTROLS
#define CHAPTER14
#include <inole.h>

//This file is generated from MKTYPLIB
#include "ibeeper.h"

class CImpIProvideClassInfo;
typedef class CImpIProvideClassInfo *PCImpIProvideClassInfo;



class CBeeper : public IBeeper
    {
    protected:
        ULONG           m_cRef;         //Object reference count
        LPUNKNOWN       m_pUnkOuter;    //Controlling unknown
        PFNDESTROYED    m_pfnDestroy;   //To call on closure

        long            m_lSound;       //Type of sound

        ITypeInfo      *m_pITINeutral;  //Type information
        IUnknown       *m_pIUnkStdDisp; //StdDispatch object

        PCImpIProvideClassInfo  m_pImpIProvideCI;

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


class CImpIProvideClassInfo : public IProvideClassInfo
    {
    public:
        ULONG           m_cRef;     //For debugging

    private:
        LPUNKNOWN       m_pUnkOuter;
        ITypeInfo      *m_pITI;     //To return from GetClassInfo

    public:
        CImpIProvideClassInfo(LPUNKNOWN, ITypeLib *);
        ~CImpIProvideClassInfo(void);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IProvideClassInfo members
        STDMETHODIMP GetClassInfo(ITypeInfo **);

    };



#endif //_BEEPER_H_
