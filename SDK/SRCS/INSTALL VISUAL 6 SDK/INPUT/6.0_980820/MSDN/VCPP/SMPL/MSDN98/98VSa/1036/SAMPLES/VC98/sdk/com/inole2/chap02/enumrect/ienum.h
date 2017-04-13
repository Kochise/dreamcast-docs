/*
 * IENUM0.H
 *
 * Definition of an IEnumRECT interface as an example of OLE
 * interfaces as they appear in C and C++.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IENUM0_H_
#define _IENUM0_H_


//C++ Definition of an interface.
#ifdef __cplusplus

typedef struct IEnumRECT IEnumRECT;
typedef IEnumRECT *PENUMRECT;


//This is the interface:  a struct of pure virtual functions.
struct IEnumRECT
    {
    STDMETHOD(QueryInterface)(REFIID, PPVOID)=0;
    STDMETHOD_(ULONG,AddRef)(void)=0;
    STDMETHOD_(ULONG,Release)(void)=0;
    STDMETHOD(Next)(DWORD, LPRECT, LPDWORD)=0;
    STDMETHOD(Skip)(DWORD)=0;
    STDMETHOD(Reset)(void)=0;
    STDMETHOD(Clone)(PENUMRECT *)=0;
    };

#else   //!__cplusplus

/*
 * A C interface is explicitly a structure containing a long
 * pointer to a virtual function table that we have to
 * initialize explicitly.
 */

typedef struct
    {
    struct IEnumRECTVtbl FAR *lpVtbl;
    } IEnumRECT, *PENUMRECT;

//This is just a convenient naming
typedef struct IEnumRECTVtbl IEnumRECTVtbl;


struct IEnumRECTVtbl
    {
    STDMETHOD(QueryInterface)(PENUMRECT, REFIID, PPVOID);
    STDMETHOD_(ULONG, AddRef)(PENUMRECT);
    STDMETHOD_(ULONG, Release)(PENUMRECT);
    STDMETHOD(Next)(PENUMRECT, DWORD, LPRECT, LPDWORD);
    STDMETHOD(Skip)(PENUMRECT, DWORD);
    STDMETHOD(Reset)(PENUMRECT);
    STDMETHOD(Clone)(PENUMRECT, PENUMRECT *);
    };

#endif  //!__cplusplus

#endif //_IENUM0_H_
