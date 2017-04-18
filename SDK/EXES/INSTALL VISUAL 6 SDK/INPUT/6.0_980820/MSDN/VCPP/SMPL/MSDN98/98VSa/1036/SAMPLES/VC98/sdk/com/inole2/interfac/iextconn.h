/*
 * IEXTCONN.H
 *
 * Definitions of a template IExternalConnection interface
 * implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IEXTCONN_H_
#define _IEXTCONN_H_

#include <inole.h>

class CImpIExternalConnection;
typedef class CImpIExternalConnection *PCImpIExternalConnection;

class CImpIExternalConnection : public IExternalConnection
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIExternalConnection(LPVOID, LPUNKNOWN);
        ~CImpIExternalConnection(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP_(DWORD) AddConnection(DWORD, DWORD);
        STDMETHODIMP_(DWORD) ReleaseConnection(DWORD, DWORD, BOOL);
    };


#endif //_IEXTCONN_H_
