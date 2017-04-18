//--vsof.h---------------------------------------------------------------------
//
// Virtual Stream On File interface header file.
//
//
// Copyright (C) Microsoft Corp., 1986-1996.  All Rights Reserved.
//    
//-----------------------------------------------------------------------------

#ifndef __VSOF_H__
#define __VSOF_H__

/* VirtualStreamOnFile (VSOF) */

/*
 *	Methods and #define's for implementing an OLE 2.0 storage stream
 *	(as defined in the OLE 2.0 specs) on top of a system file.
 */

#ifdef __cplusplus
extern "C" {
#endif

// Flags unique to VSOF IStream implementation
#define VSOF_CLONEABLE      ((ULONG) 0x40000000)	// allow stream to be cloned
#define VSOF_UNIQUEFILENAME	((ULONG) 0x80000000)	// Want unique temporary file name

//$--HrOpenVirtualStreamOnFile---------------------------------------------------
//
// DESCRIPTION:	Opens a virtual (buffered) stream on a file.
//
// INPUT:	lpAllocateBuffer	--	allocate routine
//			lpFreeBuffer	--	de-allocation routine
//			ulFlags	--	IStream interface flags--see notes
//			lpszFileName	--	file name with complete path
//			lpszPrefix	--	file name prefix
//			
//
// OUTPUT:	lppStream	--	stream pointer
//
// RETURNS:	HRESULT	--	NOERROR if successful,
//						E_INVALIDARG if bad input,
//						E_FAIL otherwise.
//
// ulFlag notes:
//
// Specifying STGM_DELETEONRELEASE makes the file opened a temporary file (It
// will be deleted when the stream is released).
//
// Specifying STGM_SHARE_EXCLUSIVE makes the file accessible by only one application
// at a time.
//
// Specifying STGM_SHARE_DENY_READ makes the file readable by only one application
// at a time.
//
// Specifying STGM_SHARE_DENY_WRITE makes the file writable by only one application
// at a time.
//
// Failing to specify a STGM_SHARE flag makes the file readable and writable
// by mutliple applications at the same time.
//
//-----------------------------------------------------------------------------
STDMETHODIMP HrOpenVirtualStreamOnFile(
	IN LPALLOCATEBUFFER	lpAllocateBuffer,	// allocation routine
	IN LPFREEBUFFER		lpFreeBuffer,		// de-allocation routine
	IN ULONG			ulFlags,			// stream interface flags
	IN LPSTR			lpszFileName,		// file name
	IN LPSTR			lpszPrefix,			// file name prefix
	OUT LPSTREAM FAR *	lppStream);			// pointer to stream

typedef HRESULT (STDMETHODCALLTYPE FAR * LPOPENVIRTUALSTREAMONFILE) 
(
	LPALLOCATEBUFFER	lpAllocateBuffer,
	LPFREEBUFFER		lpFreeBuffer,
	ULONG				ulFlags,
	LPSTR				lpszFileName,
	LPSTR				lpszPrefix,
	LPSTREAM FAR *		lppStream
);

// Special virtual stream interface extensions for performance...
// There are certain situations where knowing if the stream has changed can be
// used to make desicions that will improve performance.

//$--VSOF_SetClean-------------------------------------------------------------
//
// DESCRIPTION:	Unsets stream dirty flag
//
// INPUT:	lpStream	--	stream pointer
//
// RETURNS:	HRESULT	--	NOERROF if successful,
//						E_INVALIDARG if bad input.
//
//-----------------------------------------------------------------------------
HRESULT VSOF_SetClean(
	IN LPSTREAM lpStream);	// stream pointer

//$--VSOF_IsDirty-------------------------------------------------------------
//
// DESCRIPTION:	Returns stream dirty flag
//
// INPUT:	lpStream	--	stream pointer
//
// RETURNS:	HRESULT	--	NOERROF if successful,
//						E_INVALIDARG if bad input.
//
//-----------------------------------------------------------------------------
HRESULT VSOF_IsDirty(	
	IN LPSTREAM lpStream,		// stream pointer
	OUT BOOL * pfDirty);		// dirty flag pointer

#ifdef	WIN32
#define OPENVIRTUALSTREAMONFILE "HrOpenVirtualStreamOnFile"
#endif
#ifdef	WIN16
#define OPENVIRTUALSTREAMONFILE "_OPENVIRTUALSTREAMONFILE"
#endif

#ifdef __cplusplus
}
#endif
  
#endif //__VSOF_H__
