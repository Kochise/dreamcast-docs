/*
 * INTERFAC.H
 *
 * Definition of IAnimal and IKoala used to demonstrate
 * reusability mechanisms.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _INTERFAC_H_
#define _INTERFAC_H_


DECLARE_INTERFACE_(IAnimal, IUnknown)
    {
    //IUnknown members
    STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
    STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    //IAnimal members
    STDMETHOD(Eat)(THIS) PURE;
    STDMETHOD(Sleep)(THIS) PURE;
    STDMETHOD(Procreate)(THIS) PURE;
    };

typedef IAnimal *PANIMAL;


DECLARE_INTERFACE_(IKoala, IUnknown)
    {
    //IUnknown members
    STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
    STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    //IKoala members
    STDMETHOD(ClimbEucalyptusTrees)(THIS) PURE;
    STDMETHOD(PouchOpensDown)(THIS) PURE;
    STDMETHOD(SleepForHoursAfterEating)(THIS) PURE;
    };

typedef IKoala *PKOALA;


#endif //_INTERFAC_H_
