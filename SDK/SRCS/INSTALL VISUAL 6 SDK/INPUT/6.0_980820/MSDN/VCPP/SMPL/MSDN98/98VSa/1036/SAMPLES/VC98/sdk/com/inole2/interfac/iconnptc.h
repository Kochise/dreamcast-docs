/*
 * ICONNPTC.H
 *
 * Header for template IConnectionPointContainer interface
 * implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _ICONNPTC_H_
#define _ICONNPTC_H_

#define INC_CONTROLS
#include <inole.h>

class CImpIConnectionPointContainer;
typedef class CImpIConnectionPointContainer
    *PCImpIConnectionPointContainer;

class CImpIConnectionPointContainer : public IConnectionPointContainer
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIConnectionPointContainer(LPVOID, LPUNKNOWN);
        ~CImpIConnectionPointContainer(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

    	STDMETHODIMP EnumConnectionPoints(LPENUMCONNECTIONPOINTS *);
	    STDMETHODIMP FindConnectionPoint(REFIID, LPCONNECTIONPOINT *);
    };


#endif //_ICONNPTC_H_
