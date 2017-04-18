/*
 * IENUMCP.H
 *
 * Definitions of a template IEnumConnectionPoints enumerator.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IENUMCP_H_
#define _IENUMCP_H_

#define INC_CONTROLS
#include <inole.h>

class CEnumConnectionPoints;
typedef class CEnumConnectionPoints *PCEnumConnectionPoints;

class CEnumConnectionPoints : public IEnumConnectionPoints
    {
    private:
        ULONG           m_cRef;     //Object reference count
        LPUNKNOWN       m_pUnkRef;  //IUnknown for ref counting
        ULONG           m_iCur;     //Current element
        ULONG           m_cPoints;  //Number of conn points
        LPCONNECTIONPOINT *m_rgpCP; //Source of conn points

    public:
        CEnumConnectionPoints(LPUNKNOWN, ULONG, LPCONNECTIONPOINT *);
        ~CEnumConnectionPoints(void);

        //IUnknown members that delegate to m_pUnkRef.
        STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IEnumConnectionPoints members
        STDMETHODIMP Next(ULONG, LPCONNECTIONPOINT *, ULONG *);
        STDMETHODIMP Skip(ULONG);
        STDMETHODIMP Reset(void);
        STDMETHODIMP Clone(IEnumConnectionPoints **);
    };


#endif //_IENUMCP_H_
