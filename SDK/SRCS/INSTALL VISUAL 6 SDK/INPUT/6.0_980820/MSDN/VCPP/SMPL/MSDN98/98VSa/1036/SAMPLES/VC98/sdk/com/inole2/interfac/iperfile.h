/*
 * IPERFILE.H
 *
 * Definitions of a template IPersistFile interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IPERFILE_H_
#define _IPERFILE_H_

#include <inole.h>

class CImpIPersistFile;
typedef class CImpIPersistFile *PCImpIPersistFile;

class CImpIPersistFile : public IPersistFile
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIPersistFile(LPVOID, LPUNKNOWN);
        ~CImpIPersistFile(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetClassID(LPCLSID);

        STDMETHODIMP IsDirty(void);
        STDMETHODIMP Load(LPCOLESTR, DWORD);
        STDMETHODIMP Save(LPCOLESTR, BOOL);
        STDMETHODIMP SaveCompleted(LPCOLESTR);
        STDMETHODIMP GetCurFile(LPOLESTR *);
    };


#endif  //_IPERFILE_H_
