/* @doc
 *
 * @module DKOALA.H - Koala Object DLL Chapter 4 |
 *
 * Definitions, classes, and prototypes for a DLL that
 * provides Koala objects to any other object user.
 *
 * Copyright (c)1993 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Autoduck example by Eric Artzt (erica@microsoft.com)
 */


#ifndef _DKOALA_H_
#define _DKOALA_H_


//Get the object definitions
#include "koala.h"


void FAR PASCAL ObjectDestroyed(void);


//DKOALA.CPP
int FAR PASCAL WEP(int);


//@class This class factory object creates Koala objects.
//
//@base public | IClassFactory

class __far CKoalaClassFactory : public IClassFactory
    {
    //@access Protected Members

    protected:
        //@cmember Reference count.

        ULONG           m_cRef;

    //@access Public Members

    public:
        //@cmember Constructor.

        CKoalaClassFactory(void);

        //@cmember Destructor.

        ~CKoalaClassFactory(void);

        //IUnknown members

        //@cmember Obtains interface pointer.

        STDMETHODIMP QueryInterface(REFIID, LPLPVOID);

        //@cmember Increments reference count.

        STDMETHODIMP_(ULONG) AddRef(void);

        //@cmember Decrements reference count.

        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members

        //@cmember Decrements reference count.

        STDMETHODIMP CreateInstance(LPUNKNOWN, REFIID, LPLPVOID);

        //@cmember Lock the server (duh).

        STDMETHODIMP LockServer(BOOL);
    };

typedef CKoalaClassFactory FAR *LPCKoalaClassFactory;

#endif //_DKOALA_H_
