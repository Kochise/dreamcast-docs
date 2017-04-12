//-----------------------------------------------------------------------------------
// Microsoft OLE DB Provider For Oracle 
// (C) Copyright 1997 By Microsoft Corporation.
//
// @doc
//
// @module GUIDS.H | Internal GUIDS
//
// $Header: /Canoe/source/guids.h 4     9/25/97 4:50p Stevesta $
// $Log: /Canoe/source/guids.h $
// 
// 4     9/25/97 4:50p Stevesta
// Remove IDL and TypeLib (no longer necessary)
// 
// 3     9/09/97 11:02a Wlodekn
// 
// 2     7/21/97 9:21a Stevesta
// IDBCreateSession::CreateSession; Fixup precompiled headers; etc.
// 
// 1     7/17/97 12:22p Stevesta
// Initial Checkin
//

#ifndef __MSDAORAGUIDS_DEFINED__
#define __MSDAORAGUIDS_DEFINED__

#ifdef DBINITCONSTANTS

EXTERN_C const CLSID CLSID_MSDAORA			= {0xE8CC4CBE,0xFDFF,0x11D0,{0xB8,0x65,0x00,0xA0,0xC9,0x08,0x1C,0x1D}};
EXTERN_C const CLSID CLSID_MSDAORA_ERROR	= {0xE8CC4CBF,0xFDFF,0x11D0,{0xB8,0x65,0x00,0xA0,0xC9,0x08,0x1C,0x1D}};

#else //DBINITCONSTANTS

EXTERN_C const CLSID CLSID_MSDAORA;
EXTERN_C const CLSID CLSID_MSDAORA_ERROR;

#endif //DBINITCONSTANTS

class DECLSPEC_UUID("E8CC4CBE-FDFF-11D0-B865-00A0C9081C1D")
MSDAORA;

class DECLSPEC_UUID("E8CC4CBF-FDFF-11D0-B865-00A0C9081C1D")
MSDAORA_ERROR;

#endif // __MSDAORAGUIDS_DEFINED__
