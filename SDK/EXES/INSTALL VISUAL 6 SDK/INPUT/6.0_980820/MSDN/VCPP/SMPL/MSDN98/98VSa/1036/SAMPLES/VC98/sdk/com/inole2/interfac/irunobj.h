/*
 * IRUNOBJ.H
 *
 * Definitions of a template IRunnableObject interface
 * implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IRUNOBJ_H_
#define _IRUNOBJ_H_

#include <inole.h>

class CImpIRunnableObject;
typedef class CImpIRunnableObject *PCImpIRunnableObject;

class CImpIRunnableObject : public IRunnableObject
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIRunnableObject(LPVOID, LPUNKNOWN);
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


#endif //_IRUNOBJ_H_
