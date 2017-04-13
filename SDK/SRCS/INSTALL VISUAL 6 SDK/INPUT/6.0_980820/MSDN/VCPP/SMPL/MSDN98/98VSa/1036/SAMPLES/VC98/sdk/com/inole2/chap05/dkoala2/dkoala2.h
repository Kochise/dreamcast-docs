/*
 * DKOALA2.H
 * Koala Object DLL Self-Registering Server Chapter 5
 *
 * Definitions, classes, and prototypes for a DLL that
 * provides Koala objects to any other object user.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _DKOALA2_H_
#define _DKOALA2_H_


//Get the object definitions
#include "koala.h"


STDAPI DllRegisterServer(void);
STDAPI DllUnregisterServer(void);
BOOL   SetKeyAndValue(LPTSTR, LPTSTR, LPTSTR);

void   ObjectDestroyed(void);


//DKOALA.CPP
//This class factory object creates Koala objects.

class CKoalaClassFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;

    public:
        CKoalaClassFactory(void);
        ~CKoalaClassFactory(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP         CreateInstance(LPUNKNOWN, REFIID
                                 , PPVOID);
        STDMETHODIMP         LockServer(BOOL);
    };

typedef CKoalaClassFactory *PCKoalaClassFactory;

#endif //_DKOALA2_H_
