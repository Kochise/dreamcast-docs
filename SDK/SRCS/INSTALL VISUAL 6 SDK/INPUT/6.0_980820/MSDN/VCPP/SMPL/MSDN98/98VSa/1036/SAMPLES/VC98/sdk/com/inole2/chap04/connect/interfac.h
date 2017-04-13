/*
 * INTERFAC.H
 *
 * Definition of IDuckEvents used to demonstrate a connection
 * point implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _INTERFAC_H_
#define _INTERFAC_H_


DECLARE_INTERFACE_(IDuckEvents, IUnknown)
    {
    //IUnknown members
    STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
    STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    //IDuckEvents members
    STDMETHOD(Quack)(THIS) PURE;
    STDMETHOD(Flap)(THIS) PURE;
    STDMETHOD(Paddle)(THIS) PURE;
    };

typedef IDuckEvents *PDUCKEVENTS;


#endif //_INTERFAC_H_
