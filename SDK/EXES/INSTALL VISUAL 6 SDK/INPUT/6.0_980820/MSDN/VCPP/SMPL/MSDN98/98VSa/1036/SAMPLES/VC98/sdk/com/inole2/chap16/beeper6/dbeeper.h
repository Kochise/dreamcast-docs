/*
 * DBEEPER.H
 * Beeper Object #6 with Property Pages Chapter 16
 *
 * Definitions, classes, and prototypes for the server of Beeper
 * objects.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _DBEEPER_H_
#define _DBEEPER_H_


//Get the object definitions
#include "beeper.h"


//DBEEPER.CPP
void ObjectDestroyed(void);

//This class factory object creates other objects

class CBeeperFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;

    public:
        CBeeperFactory(void);
        ~CBeeperFactory(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP     CreateInstance(LPUNKNOWN, REFIID, PPVOID);
        STDMETHODIMP     LockServer(BOOL);
    };

typedef CBeeperFactory *PCBeeperFactory;

#endif //_DBEEPER_H_
