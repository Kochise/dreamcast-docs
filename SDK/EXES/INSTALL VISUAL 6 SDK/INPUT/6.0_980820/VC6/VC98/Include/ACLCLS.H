// --aclcls.h------------------------------------------------------------------
//
// Interface to library: aclcls.
//
// Copyright 1986 - 1998 Microsoft Corporation. All rights reserved.
//
// ----------------------------------------------------------------------------

#if !defined(_ACLCLS_H_)
#define _ACLCLS_H_


// $$--IExchangeFolderACLs-----------------------------------------------------
//
// Definition of interface for folder ACLs class CFolderACLs.
//
// ----------------------------------------------------------------------------

#undef		 INTERFACE
#define		 INTERFACE  IExchangeFolderACLs

// Manifest for cursor position indicating we are at the end of the ACLs table.

#define	ACL_PAST_END		((LONG) -1)


// Special ACL positions.  The special ACL's at these position may not be
// deleted, and there are also special rules (coming from Exchange) with
// regard to how rights will be modified.  Also, other ACL's may not be inserted
// at these positions.

#define	ACL_POS_DEFAULT		((LONG) 0)
#define	ACL_POS_CREATOR		((LONG) 1)

DECLARE_INTERFACE_(IExchangeFolderACLs, IUnknown)
{
#ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */

	STDMETHOD(QueryInterface)(
		THIS_
		REFIID					riid,
		LPVOID FAR *			ppvObj
		)										PURE;

    STDMETHOD_(ULONG, AddRef)(
		THIS
		)										PURE;

    STDMETHOD_(ULONG, Release)(
		THIS
		)										PURE;

#endif

    /* IExchangeFolderACLs methods */

    STDMETHOD(HrDelete)(
		THIS
		)													PURE;

    STDMETHOD(HrGet)(
		THIS_
		LPLONG					lplRights,
		LPSTR FAR *				lppszDisplayName,
		ULONG FAR *				lpcbentryid,
		LPENTRYID FAR *			lppentryid
		)													PURE;

    STDMETHOD(HrInsert)(
		THIS_
		LONG					lRights,
		LPSTR					lpszDisplayName,
		ULONG					cbentryid,
		LPENTRYID				lpentryid,
		LPLONG					lplRights
		)													PURE;

    STDMETHOD(HrModify)(
		THIS_
		LONG					lRights,
		LPLONG					lplRights
		)													PURE;

    STDMETHOD(HrSeek)(
		THIS_
		LONG					lPos
		)													PURE;

    STDMETHOD(HrTell)(
		THIS_
		LPLONG					lplPos
		)													PURE;
};

// $$--LPFOLDERACLS------------------------------------------------------------
//
// Pointer to IExchangeFolderACLs interface.
//
// ----------------------------------------------------------------------------

typedef IExchangeFolderACLs FAR * LPFOLDERACLS;

//
// Helper functions defined in module ACLCLS.
//

// $--HrFolderACLsOpen---------------------------------------------------------
//
// DESCRIPTION:	Get a pointer to an object which implements the
//				IExchangeFolderACLs interface defined in aclcls.h.
//
// INPUT:
//
//  [lpSession]         -- Pointer to MAPI session.
//	[lpMDB]				-- Pointer to message store containing folder.
//  [cbentryid]			-- Number of bytes in folder's entry identifier.
//  [lpentryid]			-- Folder's entry identifier.
//
// OUTPUT:
//
//  [lppFolderACLs]		-- Pointer to object which supports interface.
//						   NULL if none.
//
// RETURNS:     NOERROR			if successful;
//				E_INVALIDARG	if bad input;
//				E_OUTOFMEMORY	if not enough memory;
//				E_NOINTERFACE	if acl table does not exist on folder;
//              E_FAIL 			otherwise.
//
//-----------------------------------------------------------------------------

STDAPI
HrFolderACLsOpen(								// RETURNS: HRESULT
    IN      LPMAPISESSION       lpSession,      // MAPI session pointer
	IN		LPMDB				lpMDB,			// MAPI MDB store ptr
	IN		ULONG				cbentryid,		// # bytes in entry ID
	IN		LPENTRYID			lpentryid,		// entry ID ptr
	OUT		LPFOLDERACLS FAR *	lppFolderACLs	// IExchangeFolderACLs ptr ptr
	);

#endif
