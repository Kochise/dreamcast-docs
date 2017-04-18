// --rulecls.h-----------------------------------------------------------------
//
// Rule class interface header.
//
// Copyright (C) Microsoft Corp. 1986-1998. All rights reserved.
//
// ----------------------------------------------------------------------------

#if !defined(_RULECLS_H_)
#define _RULECLS_H_

// $$--LPACTIONS---------------------------------------------------------------
//
// Pointer to ACTIONS structure defined in edkmdb.h.
//
// ----------------------------------------------------------------------------

typedef ACTIONS FAR *   LPACTIONS;  // should be moved to edkmdb.h

// $$--IExchangeFolderRules----------------------------------------------------
//
// Definition of interface for folder rules class CFolderRules.
//
// ----------------------------------------------------------------------------

#undef		 INTERFACE
#define		 INTERFACE  IExchangeFolderRules

// Manifest for cursor position indicating we are at the end of the rules table.

#define	RULE_PAST_END		((LONG) -1)

DECLARE_INTERFACE_(IExchangeFolderRules, IUnknown)
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

    /* IExchangeFolderRules methods */

    STDMETHOD(HrDelete)(
		THIS
		)													PURE;

    STDMETHOD(HrDisable)(
		THIS
		)													PURE;

    STDMETHOD(HrEnable)(
		THIS
		)													PURE;

    STDMETHOD(HrGet)(
		THIS_
		LPLONG					lplState,
		LPSRestriction FAR *	lppRestriction,
		LPACTIONS FAR *			lppActions,
		LPLONG					lplLevel,
		LPSTR FAR *				lppszName
		)													PURE;

    STDMETHOD(HrInsert)(
		THIS_
		LONG					lState,
		LPSRestriction			lpRestriction,
		LPACTIONS				lpActions,
		LONG					lLevel,
		LPSTR					lpszName
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

// $$--LPFOLDERRULES-----------------------------------------------------------
//
// Pointer to IExchangeFolderRules interface.
//
// ----------------------------------------------------------------------------

typedef IExchangeFolderRules FAR* LPFOLDERRULES;

//
// Helper functions defined in module RULECLS.
//

// $--HrCopyActions------------------------------------------------------------
//
// DESCRIPTION:	Make a copy of an ACTIONS structure and all its subelements.
//
// INPUT:
//
//	[lpActsSrc]		-- Ptr to ACTIONS structure to be copied.
//	[lpObject]		-- Ptr to an existing MAPI buffer allocated by 
//					   MAPIAllocateBuffer(), or NULL if the returned structure
//					   is to be allocated using MAPIAllocateBuffer().
// OUTPUT:
//
//	[lppActsDest]	-- Ptr to be set to copy of ACTIONS structure.
//
// RETURNS:     HRESULT --  NOERROR			if successful;
//							E_INVALIDARG	if bad input;
//							E_OUTOFMEMORY	if insufficient memory;
//              			E_FAIL			otherwise.
//
//-----------------------------------------------------------------------------

STDAPI
HrCopyActions(							// RETURNS: HRESULT
	IN		LPACTIONS		lpActsSrc,  // source action ptr
	IN		LPVOID			lpObject,	// ptr to existing MAPI buffer
	OUT		LPACTIONS FAR *	lppActsDest // ptr to destination ACTIONS buffer
	);


// $--HrCopyRestriction--------------------------------------------------------
//
// DESCRIPTION:	Make a copy of an SRestriction structure and all its
//				subelements.
//
// INPUT:
//
//	[lpResSrc]		-- Ptr to restriction to be copied.
//	[lpObject]		-- Ptr to an existing MAPI buffer allocated by 
//					   MAPIAllocateBuffer(), or NULL if the returned structure
//					   is to be allocated using MAPIAllocateBuffer().
//
// OUTPUT:
//
//	[lppResDest]	-- Ptr to be set to copy of restriction.
//
// RETURNS:     NOERROR			if successful;
//				E_INVALIDARG	if bad input;
//				E_OUTOFMEMORY	if insufficient memory;
//              E_FAIL			otherwise.
//
//-----------------------------------------------------------------------------

STDAPI
HrCopyRestriction(								// RETURNS: HRESULT
	IN		LPSRestriction			lpResSrc,   // source restriction ptr
	IN		LPVOID					lpObject,	// ptr to existing MAPI buffer
	OUT		LPSRestriction FAR *	lppResDest  // dest restriction buffer ptr
	);


// $--HrFolderRulesGetProviders------------------------------------------------
//
// DESCRIPTION:	Get an array of rules provider names for a given folder.
//
// INPUT:
//
//	[lpMDB]				-- Pointer to message store containing folder.
//  [cbentryid]			-- Number of bytes in folder's entry identifier.
//  [lpentryid]			-- Folder's entry identifier.
//
// OUTPUT:
//
//  [lpcProviders]		-- Pointer to ulong that will be set to count of
//						   providers on successful return.
//	[lpppszProviders]	-- Pointer to array of string pointers that will be set
//						   to point at an array of provider name string pointers
//						   on successful return.
//
// RETURNS:     NOERROR				if successful;
//				E_INVALIDARG		if bad input;
//				E_OUTOFMEMORY		if not enough memory;
//				E_NOINTERFACE		if rules table does not exist on folder;
//              E_FAIL 				otherwise.
//
//-----------------------------------------------------------------------------

STDAPI
HrFolderRulesGetProviders(						// RETURNS: HRESULT
	IN		LPMDB				lpMDB,			// MAPI MDB store ptr
	IN		ULONG				cbentryid,		// # bytes in entry ID
	IN		LPENTRYID			lpentryid,		// entry ID ptr
	OUT		LPULONG				lpcProviders,	// count of providers
	OUT		LPSTR FAR * FAR *	lpppszProviders	// ptr to array of providers
	);


// $--HrFolderRulesOpen--------------------------------------------------------
//
// DESCRIPTION:	Get a pointer to an object which implements the
//				IExchangeFolderRules interface defined in rulecls.h.
//
// INPUT:
//
//	[lpMDB]				-- Pointer to message store containing folder.
//  [cbentryid]			-- Number of bytes in folder's entry identifier.
//  [lpentryid]			-- Folder's entry identifier.
//  [lpszProvider]		-- Provider for rules.  Multiple providers may have
//						   rules on a folder. The IExchangeFolderRules interface
//						   provides access to the rules associated with a
//						   single specified provider.
//
// OUTPUT:
//
//  [lppFolderRules]	-- Pointer to object which supports interface.
//
// RETURNS:     NOERROR				if successful;
//				E_INVALIDARG		if bad input;
//				E_OUTOFMEMORY		if not enough memory;
//				E_NOINTERFACE		if rules table does not exist on folder;
//              E_FAIL 				otherwise.
//
//-----------------------------------------------------------------------------

STDAPI
HrFolderRulesOpen(								// RETURNS: HRESULT
	IN		LPMDB				lpMDB,			// MAPI MDB store ptr
	IN		ULONG				cbentryid,		// # bytes in entry ID
	IN		LPENTRYID			lpentryid,		// entry ID ptr
	IN		LPSTR				lpszProvider,	// provider name
	OUT		LPFOLDERRULES FAR *	lppFolderRules  // ptr to folder rules buffer
	);


// $--HrActionToString---------------------------------------------------------
//
// DESCRIPTION:	Get a string representation of an ACTION.
//
// INPUT:
//
//  [lpSession]		-- MAPI session ptr.
//	[lpAction]		-- Ptr to ACTION.
//
// OUTPUT:
//
//	[lppszString]	-- Ptr to ptr that will be set to point at generated
//					   string representation on successful return.
//
// RETURNS:     NOERROR             if successful;
//              E_INVALIDARG    	if bad input;
//              E_OUTOFMEMORY		if not enough memory;
//              E_FAIL				otherwise.
//
//-----------------------------------------------------------------------------

STDAPI
HrActionToString(							// RETURNS: HRESULT
	IN		LPMAPISESSION	lpSession,  	// MAPI session ptr
	IN		LPACTION		lpAction,		// action ptr
	OUT		LPSTR FAR *		lppszString		// string ptr ptr
	);


// $--HrRestrictionToString----------------------------------------------------
//
// DESCRIPTION:	Get a string representation of an SRestriction.
//
// INPUT:
//
//	[lpRestriction]	-- Ptr to restriction.
//
// OUTPUT:
//
//	[lppszString]	-- Ptr to ptr that will be set to point at generated
//					   string representation on successful return.
//
// RETURNS:     NOERROR             if successful;
//              E_INVALIDARG    	if bad input;
//              E_OUTOFMEMORY		if not enough memory;
//              E_FAIL				otherwise.
//
//-----------------------------------------------------------------------------

STDAPI
HrRestrictionToString(						// RETURNS: HRESULT
	IN		LPSRestriction	lpRestriction,	// restriction ptr
	OUT		LPSTR FAR *		lppszString		// string ptr ptr
	);


// $--HrStringToAction---------------------------------------------------------
//
// DESCRIPTION:	Generate an ACTION structure that describes the action
//				provided in *lpszString.
//
// INPUT:
//
//	[lpSession]		-- Ptr to MAPI session.
//	[lpFolder]		-- Ptr to MAPI folder action applies to.  MUST have been
//					   opened with MAPI_MODIFY access.
//	[lpszString]	-- Action string specifying ACTION to be generated.
//	[lpObject]		-- Ptr to an existing MAPI buffer allocated by 
//					   MAPIAllocateBuffer().  NULL is not permitted. Ideally,
//					   this is a ptr to the parent ACTIONS structure.
//
// INPUT/OUTPUT:
//
//	[lpAction]		-- Ptr to ACTION structure that will be filled in.  This
//					   is allocated by the caller.  Ideally, this is a ptr to
//					   an ACTION array element that was allocated by the caller
//					   using a MAPIAllocateMore() that referenced the parent
//					   ACTIONS structure.
//
// RETURNS:     NOERROR				if successful;
//				E_INVALIDARG		if bad input;
//              E_OUTOFMEMORY		if out of memory;
//              E_FAIL				otherwise.
//-----------------------------------------------------------------------------

STDAPI
HrStringToAction(							// RETURNS: HRESULT
	IN		LPMAPISESSION	lpSession,		// ptr to MAPI session
	IN		LPMAPIFOLDER	lpFolder,		// ptr to MAPI folder
	IN		LPSTR			lpszString,		// string ptr
	IN		LPVOID			lpObject,		// ptr to existing MAPI buf
	IN OUT	LPACTION		lpAction  		// ACTION ptr
	);


// $--HrStringToRestriction----------------------------------------------------
//
// DESCRIPTION:	Generate an SRestriction structure that describes the 
//				restriction condition provided in *lpszString.
//
// INPUT:
//
//	[lpszString]	-- Condition string specifying restriction to be generated.
//	[lpObject]		-- Ptr to an existing MAPI buffer allocated by 
//					   MAPIAllocateBuffer(), or NULL if the returned structure
//					   is to be allocated using MAPIAllocateBuffer().
//
// OUTPUT:
//
//	[lppRestriction]	-- Ptr to ptr that will be set to point at generated
//						   restriction on successful return.
//
// RETURNS:     NOERROR			if successful;
//				E_INVALIDARG	if bad input;
//              E_FAIL 			otherwise.
//
// Conditional expression grammar used for HrStringToRestriction()
// lpszString parameter:
// 
// Condition ::=	SimpleCondition						|
//					Condition "|" Condition				|
//					Condition "&" Condition				|
//					"(" Condition ")"					|
//					"!" Condition
//
// "|" is the logical OR operator.
// "&" is the logical AND operator.
// "!" is the logical NOT operator.
//
// Conditional expressions are evaluated from left to right with "|" and "&"
// having equal precedence. "!" is a unary operator that applies to the operand
// to its immediate right.
//
// SimpleCondition ::=	BooleanCondition				|
//						NumericCondition				|
//						StringCondition					|
//						TimeCondition
//
// BooleanCondition ::=	BoolTag "=" BooleanLiteral
//
// NumericCondition ::=	NumericTag "=" NumericLiteral	|
//						NumericTag "#" NumericLiteral	|
//						NumericTag ">" NumericLiteral	|
//						NumericTag "<" NumericLiteral
//
// The meaning of the NumericCondition operators should be evident.
//
// StringCondition ::=	StringTag "=" StringLiteral		|
//						StringTag "#" StringLiteral		|
//						StringTag "}" StringLiteral
//
// "=" is the equality operator.
// "#" is the inequality operator.
// "}" is the contains operator (a "}" b means a contains b).
//
// TimeCondition ::=	TimeTag "=" TimeLiteral			|
//						TimeTag "#" TimeLiteral			|
//						TimeTag ">" TimeLiteral			|
//						TimeTag "<" TimeLiteral
//
// Note that time literals have a resolution of 1 second, so equality and 
// inequality may not be the best conditional tests.
//
// BoolTag ::=		PT_xxx for a property with a boolean (PT_BOOLEAN) value	|
//					"[B" HexNumber "]"
//
// NumericTag ::=	PR_xxxx for a property with a numeric (PT_LONG) value	|
//					"[N" HexNumber "]"
//
// StringTag ::=	PR_xxxx for a property with a string
//                  (PT_STRING8 or PT_UNICODE) value						|
//					"[S" HexNumber "]"
//
// TimeTag ::=		PR_xxxx for a property with a time (PT_SYSTIME) value	|
//					"[T" HexNumber "]"
//
// BooleanLiteral ::=	"0"					|
//						"1"
//
// NumericLiteral ::=	DecimalNumber
//
// StringLiteral ::=	String enclosed in quotes ("xxx").
//
// TimeLiteral ::=		HH:MM{:SS} YYYY-MM-DD (24 hour clock, local time)
//
// DecimalNumber ::= 	DecimalDigit...		|
//						+DecimalDigit...	|
//						-DecimalDigit...
//
// HexNumber ::=		HexDigit...
//
//-----------------------------------------------------------------------------

STDAPI
HrStringToRestriction(								// RETURNS: HRESULT
	IN		LPSTR					lpszString,		// string
	IN		LPVOID					lpObject,		// ptr to existing MAPI buf
	OUT		LPSRestriction FAR *	lppRestriction  // restriction buffer ptr
	);


#endif
