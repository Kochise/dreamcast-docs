/*
 * IPARSEDN.H
 *
 * Definitions of a template IParseDisplayName interface
 * implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IPARSEDN_H_
#define _IPARSEDN_H_

#include <inole.h>

class CImpIParseDisplayName;
typedef class CImpIParseDisplayName *PCImpIParseDisplayName;

class CImpIParseDisplayName : public IParseDisplayName
    {
    private:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIParseDisplayName(LPVOID, LPUNKNOWN);
        ~CImpIParseDisplayName(void);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IParseDisplayName members
        STDMETHODIMP ParseDisplayName(LPBC, LPOLESTR
            , ULONG *, LPMONIKER *);
    };


#endif //_IPARSEDN_H_
