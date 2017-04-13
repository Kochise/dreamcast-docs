/*
 * IUNKNOWN.H
 *
 * Definitions and function prototypes for a template IUnknown
 * interface implementation that delegates all IUnknown calls
 * to some object controller, ignorant of aggregation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IUNKNOWN_H_
#define _IUNKNOWN_H_

#include <inole.h>

class CImpIUnknown;
typedef class CImpIUnknown *PCImpIUnknown;

class CImpIUnknown : public IUnknown
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIUnknown(LPVOID, LPUNKNOWN);
        ~CImpIUnknown(void);

        //IUnknown interface members
        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);
    };


#endif //_IUNKNOWN_H_
