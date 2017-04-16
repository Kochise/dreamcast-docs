//$--ProxyInf.h-----------------------------------------------------------------
//
// Copyright (c) Microsoft Corp. 1986-1996. All Rights Reserved.
//
//	Definition of structures which are passed to the proxy generation functions
//	in order to generate proxy addresses for installed address types.
//
//	This file should be included by the writer of the proxy generation DLL
//	as well as by the calling code.
//
//------------------------------------------------------------------------------

#if !defined(_PROXYINF_H)
#define _PROXYINF_H



//$--RECIPIENTINFO--------------------------------------------------------------
//	This structure stores the information associated with each user which in 
//	conjunction with a site proxy could be used to generate a 
//	site-unique recipient proxy. This is filled by the calling code and passed
//	to the proxy generation DLL for read-only use. 
//------------------------------------------------------------------------------
typedef struct _RECIPIENTINFO {
	LPWSTR		pszCommonName;		// Common Name (aka mailbox name). 
	LPWSTR		pszFirstName;		// Given Name
	LPWSTR		pszLastName;		// Surname
	LPWSTR		pszDisplayName;		// Display Name
	LPWSTR		pszInitials;		// Initials
} RECIPIENTINFO, * PRECIPIENTINFO;


// Maximum field sizes (in characters, not bytes)

// PC Mail Constants (MS:Network/Postoffice/Name) [See \tr\src\admin\pcproxy\pcproxy.c]
#define cchMaxCreateMSNetwork		(10 + 1)
#define cchMaxCreateMSPostoffice 	(10 + 1)
#define cchMaxCreateMSName			(10 + 1)

#define cchMaxValidateMSNetwork		(10 + 1)
#define cchMaxValidateMSPostoffice	(10 + 1)
#define cchMaxValidateMSName		(10 + 1)

// Maximum Length for Integers (Input numbers up to 4294967295)
#define cchMaxNumber				(10 + 1)

// Number of X400 Organizational Units
#define nMaxOrgUnits			4

#define cchMaxProxyValue			(1110+1)	// maximum character length of a proxy plus a null terminator

#define CP_ANSI						1252		// ANSI code page

#endif
