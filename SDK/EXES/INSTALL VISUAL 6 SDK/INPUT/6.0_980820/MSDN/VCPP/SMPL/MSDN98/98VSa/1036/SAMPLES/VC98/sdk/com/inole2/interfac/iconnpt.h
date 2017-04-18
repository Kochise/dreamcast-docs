/*
 * ICONNPT.H
 *
 * Header for template IConnectionPoint implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _ICONNPT_H_
#define _ICONNPT_H_

#define INC_CONTROLS
#include <inole.h>

class CConnectionPoint;
typedef class CConnectionPoint *PCConnectionPoint;

class CConnectionPoint : public IConnectionPoint
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object

    public:
        CConnectionPoint(LPVOID);
        ~CConnectionPoint(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetConnectionInterface(IID *);
        STDMETHODIMP GetConnectionPointContainer
            (IConnectionPointContainer **);
        STDMETHODIMP Advise(LPUNKNOWN, DWORD *);
        STDMETHODIMP Unadvise(DWORD);
        STDMETHODIMP EnumConnections(LPENUMCONNECTIONS *);
    };


#endif //_ICONNPT_H_
