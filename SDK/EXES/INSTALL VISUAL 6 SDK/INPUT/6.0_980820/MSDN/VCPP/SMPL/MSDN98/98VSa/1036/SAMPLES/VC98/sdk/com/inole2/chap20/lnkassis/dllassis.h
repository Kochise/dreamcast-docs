/*
 * DLLASSIST.H
 * Links Assistant Chapter 20
 *
 * Definitions, classes, and prototypes for a DLL that provides
 * CLSID_LinksAssistant objects to a linking container applications.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _DLLASSIS_H_
#define _DLLASSIS_H_

#include "lnkassis.h"

void ObjectDestroyed(void);


//DLLASSIS.CPP
//This class factory object creates Links Assistant objects.

class CLinksClassFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;

    public:
        CLinksClassFactory(void);
        ~CLinksClassFactory(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP         CreateInstance(LPUNKNOWN, REFIID
                                 , PPVOID);
        STDMETHODIMP         LockServer(BOOL);
    };

typedef CLinksClassFactory *PCLinksClassFactory;


#endif //_DLLASSIS_H_
