/*
 * ICLASSF2.H
 *
 * Definitions for a template Class Factory object with the
 * IClassFactory2 interface.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _ICLASSF2_H_
#define _ICLASSF2_H_

#define INC_CONTROLS
#include <inole.h>

class CClassFactory2;
typedef class CClassFactory2 *PCClassFactory2;

class CClassFactory2 : public IClassFactory2
    {
    protected:
        ULONG           m_cRef;         //Reference count on object

    public:
        CClassFactory2(void);
        ~CClassFactory2(void);

        //IUnknown interface members
        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP CreateInstance(LPUNKNOWN, REFIID, LPVOID *);
        STDMETHODIMP LockServer(BOOL);

        //IClassFactory2 members
        STDMETHODIMP GetLicInfo(LPLICINFO);
	    STDMETHODIMP RequestLicKey(DWORD, BSTR *);
	    STDMETHODIMP CreateInstanceLic(LPUNKNOWN, LPUNKNOWN, REFIID
	    	, BSTR, LPVOID *);
    };


#endif //_ICLASSF2_H_
