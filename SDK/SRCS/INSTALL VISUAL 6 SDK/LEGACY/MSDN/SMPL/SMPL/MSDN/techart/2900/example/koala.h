/* @doc
 *
 * @module KOALA.H - Koala Object DLL/EXE Chapter 4 |
 *
 * Classes that implement the Koala object independent of
 * whether we live in a DLL or EXE.
 *
 * Copyright (c)1993 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Autoduck example by Eric Artzt (erica@microsoft.com)
 */


#ifndef _KOALA_H_
#define _KOALA_H_


#include <windows.h>
#include <ole2.h>       //ole2.h has IPersist, compobj.h doesn't

#include <bookguid.h>

//Type for an object-destroyed callback
typedef void (FAR PASCAL *LPFNDESTROYED)(void);


//Forward class references
class __far CImpIPersist;
typedef class CImpIPersist FAR *LPIMPIPERSIST;



/* @class The Koala object is implemented in its own class with its own
 * IUnknown to support aggregation.  It contains one CImpIPersist
 * object that we use to implement the externally exposed interfaces.
 *
 * @base public | IUnknown
 */

class __far CKoala : public IUnknown
    {
    //Make any contained interfaces friends
    friend class CImpIPersist;

    //@access Protected Members

    protected:
        //@cmember Object reference count
        ULONG           m_cRef;

        //@cmember Controlling unknown.
        LPUNKNOWN       m_pUnkOuter;

        //@cmember To call on closure
        LPFNDESTROYED   m_pfnDestroy;

        //@cmember Our interface impl.
        LPIMPIPERSIST   m_pIPersist;

    //@access Public Members
    public:
        //@cmember Constructor
        CKoala(LPUNKNOWN, LPFNDESTROYED);

        //@cmember Destructor.
        ~CKoala(void);

        BOOL FInit(void);

        //@cmember Non-delegating object IUnknown
        STDMETHODIMP         QueryInterface(REFIID, LPLPVOID);

        //@cmember Add reference count.
        STDMETHODIMP_(ULONG) AddRef(void);

        //@cmember Release reference count.
        STDMETHODIMP_(ULONG) Release(void);
    };

typedef CKoala FAR *LPCKoala;

/* @class Interface implementations for the CKoala object.
 * @base  public | IPersist
 */

class __far CImpIPersist : public IPersist
    {
    //@access Private Members
    private:
        //@cmember Reference counter.
        ULONG           m_cRef;

        //@cmember Back pointer to object.
        LPCKoala        m_pObj;

        //@cmember Controlling unknown
        LPUNKNOWN       m_pUnkOuter;

    //@access Public Members
    public:
        //@cmember Constructor.

        CImpIPersist(LPCKoala, LPUNKNOWN);

        //@cmember Destructor.

        ~CImpIPersist(void);

        //IUnknown members that delegate to m_pUnkOuter.

        //@cmember QueryInterface method.

        STDMETHODIMP         QueryInterface(REFIID, LPLPVOID);

        //@cmember Add reference count.

        STDMETHODIMP_(ULONG) AddRef(void);

        //@cmember Release reference count.

        STDMETHODIMP_(ULONG) Release(void);

        //IPersist members

        //@cmember Get the class ID.

        STDMETHODIMP         GetClassID(LPCLSID);
    };


#endif //_KOALA_H_
