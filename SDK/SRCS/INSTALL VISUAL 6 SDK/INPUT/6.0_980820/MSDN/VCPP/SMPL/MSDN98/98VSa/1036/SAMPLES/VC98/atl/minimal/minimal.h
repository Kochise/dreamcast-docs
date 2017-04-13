// minimal.h : interface declarations
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#ifndef _MINIMAL_H
#define _MINIMAL_H

// We could have used MIDL and IDL to define our custom interfaces,
// IID's and CLSID's. Here, assuming that we do not need any
// proxy/stub, we bypass MIDL and have our own header.

////////////////////////////////////////////////////////////////////////////
// {A4E6EAE8-E19A-11CF-9203-00A0C903976F}
DEFINE_GUID(IID_IMinObj,
0xA4E6EAE8, 0xE19A, 0x11CF, 0x92, 0x03, 0x00, 0xA0, 0xC9, 0x03, 0x97, 0x6F);

interface IMinObj : public IUnknown
{
public:
	STDMETHOD(Hello)() = 0 ;
};

////////////////////////////////////////////////////////////////////////////
// {A4E6EAEC-E19A-11CF-9203-00A0C903976F}
DEFINE_GUID(CLSID_CMinObj,
0xA4E6EAEC, 0xE19A, 0x11CF, 0x92, 0x03, 0x00, 0xA0, 0xC9, 0x03, 0x97, 0x6F);


#endif // _MINIMAL_H
