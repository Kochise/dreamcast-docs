/*
 * DDATAOBJ.H
 * Data Object DLL Chapter 10
 *
 * Definitions, classes, and prototypes for a DLL that
 * provides DataObject objects to any other object user.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _DDATAOBJ_H_
#define _DDATAOBJ_H_

#include "dataobj.h"


//DDATAOBJ.CPP
void ObjectDestroyed(void);

//This class factory object creates Data Objects.

class CDataObjectClassFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;
        UINT            m_iSize;        //Data size for this class

    public:
        CDataObjectClassFactory(UINT);
        ~CDataObjectClassFactory(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP         CreateInstance(LPUNKNOWN, REFIID
                                 , PPVOID);
        STDMETHODIMP         LockServer(BOOL);
    };

typedef CDataObjectClassFactory *PCDataObjectClassFactory;

#endif //_DDATAOBJ_H_
