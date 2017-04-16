//--vsop.h-----------------------------------------------------------------
//
// Header file for the property stream wrapper class.
//
// Copyright (C) Microsoft Corp., 1986-1996.  All rights reserved.
//
//-----------------------------------------------------------------------------

#ifndef _VSOP_H
#define _VSOP_H

#ifdef __cplusplus
extern "C" {
#endif

//$--IEDKVirtualStreamOnProperty---------------------------------------------------------
//
// Buffers access to a property stream
//
//----------------------------------------------------------------------------

#undef		 INTERFACE
#define		 INTERFACE  IEDKVirtualStreamOnProperty

DECLARE_INTERFACE_(IEDKVirtualStreamOnProperty, IUnknown)
{
    // Notes:  Order IS important.  The IEDKVirtualStreamOnProperty interface
    // must have the same vtable order as the IStream interface.
	//
	// The Read(), Write(), CopyTo() and Commit() methods will return
	// MAPI_E_* error codes if an attempt to access the underlying property
	// fails.  Otherwise, the IStream methods will return IStream STG_E_* errors.
	 
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */

	STDMETHOD(QueryInterface)(
		THIS_
		REFIID riid,
		LPVOID * ppvObj
		)										PURE;

    STDMETHOD_(ULONG, AddRef)(
		THIS
		)										PURE;

    STDMETHOD_(ULONG, Release)(
		THIS
		)										PURE;

#endif

    // IEDKVirtualStreamOnProperty methods (same as IStream methods)

    STDMETHOD(Read)(
		THIS_
        IN LPVOID pv,       // output buffer pointer
        IN ULONG cb,        // maximum # of bytes to read
        OUT ULONG * pcb     // # of bytes read
		)													PURE;

    STDMETHOD(Write)(
		THIS_
        IN VOID const * pv, // data to write
        IN ULONG cb,        // # bytes to write
        OUT ULONG *pcb      // # bytes written
		)													PURE;

    STDMETHOD(Seek)(
		THIS_
        IN LARGE_INTEGER cbOffset,      // byte offset
        IN DWORD dwOrigin,              // origin
        OUT ULARGE_INTEGER * pcbPos     // new position
		)													PURE;

    STDMETHOD(SetSize)(
		THIS_
        IN ULARGE_INTEGER nSize     // new size
		)													PURE;

    STDMETHOD(CopyTo)(
		THIS_
        IN LPSTREAM pStrm,              // destination stream pointer
        IN ULARGE_INTEGER cb,           // # bytes to copy
        OUT ULARGE_INTEGER * pcbRead,   // # bytes read
        OUT ULARGE_INTEGER * pcbWritten // # bytes written
		)													PURE;

    STDMETHOD(Commit)(
		THIS_
        IN DWORD dwFlags    // flags
		)													PURE;

    STDMETHOD(Revert)(
		THIS
		)													PURE;

    STDMETHOD(LockRegion)(
		THIS_
        IN ULARGE_INTEGER cbOffset, // offset
        IN ULARGE_INTEGER cbLength, // length
        IN DWORD dwFlags            // flags
		)													PURE;

    STDMETHOD(UnlockRegion)(
		THIS_
        IN ULARGE_INTEGER cbOffset, // offset
        IN ULARGE_INTEGER cbLength, // length
        IN DWORD dwFlags            // flags
		)													PURE;

    STDMETHOD(Stat)(
		THIS_
        OUT STATSTG * pStatStg,     // stream statistic pointer
        IN DWORD dwFlags            // flags
		)													PURE;

    STDMETHOD(Clone)(
		THIS_
        OUT LPSTREAM * ppStrm       // pointer to new stream
		)													PURE;

};

//$--PVIRTUALSTREAMONPROPERTY-----------------------------------------------------------
//
// Pointer to IEDKVirtualStreamOnProperty interface.
//
//----------------------------------------------------------------------------

typedef IEDKVirtualStreamOnProperty * PVIRTUALSTREAMONPROPERTY;

//$--HrOpenVirtualStreamOnProperty------------------------------------------
//
// DESCRIPTION:
// API to open a buffered stream on a binary or string property
// Callable from "C" or "C++"
//
// INPUT:	pPropObject	--	MAPI property object pointer
//			ulPropTag	--	property tag to open stream on
//			ulFlags		--	MAPI property flags (MAPI_MODIFY, MAPI_CREATE)
//
// OUTPUT:	ppVirtualStreamOnProperty	--	 pointer to buffered stream on property
//
// RETURNS:	HRESULT	--	NOERROR if successful,
//						E_INVALIDARG if bad input,
//						E_OUTOFMEMORY if memory problems,
//						E_FAIL otherwise
//
//-----------------------------------------------------------------------------
STDAPI HrOpenVirtualStreamOnProperty(
    IN LPMAPIPROP pPropObject,	// MAPI property object pointer
    IN ULONG ulPropTag,     	// property tag to open virtual stream on
	IN ULONG ulFlags,			// MAPI property flags
    OUT PVIRTUALSTREAMONPROPERTY * ppVirtualStreamOnProperty);  // pointer buffered stream

#ifdef __cplusplus
}
#endif

#endif
