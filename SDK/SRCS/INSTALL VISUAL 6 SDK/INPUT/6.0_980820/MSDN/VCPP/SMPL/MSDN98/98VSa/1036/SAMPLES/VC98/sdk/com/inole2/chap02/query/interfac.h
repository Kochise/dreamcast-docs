/*
 * INTERFAC.H
 *
 * Definition of ISampleOne and ISampleTwo used to demonstrate
 * QueryInterface and different techniques of implementing multiple
 * interfaces on an object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _INTERFAC_H_
#define _INTERFAC_H_


DECLARE_INTERFACE_(ISampleOne, IUnknown)
    {
    //IUnknown members
    STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
    STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    //ISampleOne members
    STDMETHOD(GetMessage) (THIS_ LPTSTR, UINT) PURE;
    };

typedef ISampleOne *PSAMPLEONE;


DECLARE_INTERFACE_(ISampleTwo, IUnknown)
    {
    //IUnknown members
    STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
    STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    //ISampleTwo members
    STDMETHOD(GetString) (THIS_ LPTSTR, UINT) PURE;
    };

typedef ISampleTwo *PSAMPLETWO;


#endif //_INTERFAC_H_
