/*
 * IENUMCON.H
 *
 * Definitions of a template IEnumConnections enumerator.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IENUMCON_H_
#define _IENUMCON_H_

#define INC_CONTROLS
#include <inole.h>

class CEnumConnections;
typedef class CEnumConnections *PCEnumConnections;

class CEnumConnections : public IEnumConnections
    {
    private:
        ULONG           m_cRef;       //Object reference count
        LPUNKNOWN       m_pUnkRef;    //IUnknown for ref counting
        ULONG           m_iCur;       //Current element
        ULONG           m_cConn;      //Number of connections
        LPCONNECTDATA   m_rgConnData; //Source of connections

    public:
        CEnumConnections(LPUNKNOWN, ULONG, LPCONNECTDATA);
        ~CEnumConnections(void);

        //IUnknown members that delegate to m_pUnkRef.
        STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IEnumConnections members
        STDMETHODIMP Next(ULONG, LPCONNECTDATA, ULONG *);
        STDMETHODIMP Skip(ULONG);
        STDMETHODIMP Reset(void);
        STDMETHODIMP Clone(IEnumConnections **);
    };


#endif //_IENUMCON_H_
