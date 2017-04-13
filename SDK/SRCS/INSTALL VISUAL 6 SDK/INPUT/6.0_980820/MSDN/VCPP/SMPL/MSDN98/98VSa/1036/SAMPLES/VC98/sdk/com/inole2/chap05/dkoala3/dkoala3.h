/*
 * DKOALA3.H
 * Koala Object DLL Licensed Server Chapter 5
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


#ifndef _DKOALA3_H_
#define _DKOALA3_H_


//Get the object definitions
#define INC_CONTROLS
#include "koala.h"

BOOL CheckForLicenseFile(HINSTANCE, LPTSTR, LPBYTE, UINT);


void   ObjectDestroyed(void);


//DKOALA.CPP
//This class factory object creates Koala objects.

class CKoalaClassFactory : public IClassFactory2
    {
    protected:
        ULONG           m_cRef;

    private:
        HRESULT CreateAnObject(LPUNKNOWN, REFIID, PPVOID);


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

        //IClassFactory2 members
        STDMETHODIMP         GetLicInfo(LPLICINFO);
	    STDMETHODIMP         RequestLicKey(DWORD, BSTR *);
	    STDMETHODIMP         CreateInstanceLic(LPUNKNOWN
                                , LPUNKNOWN, REFIID, BSTR, PPVOID);
    };

typedef CKoalaClassFactory *PCKoalaClassFactory;

#endif //_DKOALA3_H_
