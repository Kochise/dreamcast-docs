/**********************************************************************/
/**                         Microsoft Exchange                       **/
/**  Copyright (c) Microsoft Corp. 1986-1996. All Rights Reserved.   **/
/**********************************************************************/

/*
	adminext.h
	This file contains the common messages, manifests, types, and
	structures used by Microsoft Exchange Administration Extensions.

	NOTE:  You must include windows.h and mapix.h before this file.

*/



#ifndef _ADMINEXT_H_
#define _ADMINEXT_H_


#ifdef __cplusplus
extern "C"
{
#endif



// Miscellanous definitions

#define	ADMIN_ExtensionAPIVersion	0x000d


// List of dialog page IDs passed to the ShowPage proc in the
// extension DLL for approval.

// for gateway objects (ObjID_GW)
#define	iddGWGeneral				3020
#define	iddGWPermissions			3500
#define	iddGWSchedule				4011
#define	iddGWConnected_Sites		4020
#define	iddGWAddress_Space			3021
#define	iddGWDelivery_Restrictions	4008
#define	iddGWAdvanced				3022
#define	iddGWImportContainer		3063
#define	iddGWExportContainers		3067
#define iddGWDiagLogSetting			4030

// for mail agent objects (ObjID_MA)
#define	iddMAGeneral				4028
#define	iddMAPermissions			3500
#define	iddMADistributionList		4090
#define	iddMAEMailAddresses			4014
#define	iddMADeliveryRestrictions	4008
#define	iddMADeliveryOptions		4007
#define	iddMASecurity				4051
#define	iddMACustomAttributes		4022
#define	iddMASchedule				4011
#define	iddMAAdvanced				4040



typedef struct _ADMIN_ObjectInfo
{
	LPWSTR		szComputerName;			// Computer on which the gateway runs, when applicable
	LPWSTR		szDistinguishedName;	// of the object administered
	LPWSTR		szDNHomeMDB;			// Distinguished name of the server running the home message database
	LPWSTR		szDNHomeMTA;			// Distinguished name of the server running the home message transport agent
	LCID		lcid;					// locale ID
	UINT		uObjectID;				// object ID code
	HFONT		hfontDialog;			// font handle
} ADMIN_ObjectInfo;


// Object ID codes
#define ObjID_UK			0		// UnKnown

#define ObjID_DSFirst		1		// first DS DOC

#define ObjID_EP			2		// Enterprise
#define ObjID_DM			3		// Domain (Site)
#define ObjID_CT			4		// Container
#define ObjID_SV			5		// Server

	// Recipients
#define ObjID_MR			6		// Mail Recipients
#define ObjID_MB			7		// Mailbox
#define ObjID_DL			8		// Distribution List
#define ObjID_RR			9		// Remote Recipient
#define ObjID_PF			10		// Public Folder
#define ObjID_MA			11		// Mail Agent

	// Connections
#define ObjID_GW			12		// Gateway
#define ObjID_MGW			13		// Special Gateway for Goalline
#define ObjID_DXAREQ		14		// DXA requestor, was Remote DXA
#define ObjID_DXASV			15		// DXA Site server
#define ObjID_DXACONN		16		// DXA Server Connection
#define ObjID_ISC			17		// Site Connector
#define ObjID_LNKRAS		18		// Dynamic RAS Connector
#define ObjID_LNKTCP		19		// TCP (RFC1006) X.400 Connector
#define ObjID_LNKTP4		20		// TP4 X.400 Connector
#define ObjID_LNKX25		21		// X.25 X.400 Connector
#define ObjID_DRC			22		// Directory Replication Connector

	// Server Objects
#define ObjID_MTA			23		// MTA
#define ObjID_DSA			24		// Directory
#define ObjID_MDB			26		// Private Information Store
#define ObjID_PMDB			27		// Public Information Store
#define ObjID_LDXA			28		// Local DXA
#define ObjID_SAA			29		// System Attendant
#define ObjID_STKRAS		30		// RAS MTA Transport Stack
#define ObjID_STKTCP		31		// TCP (RFC1006) MTA Transport Stack
#define ObjID_STKTP4		32		// TP4 MTA Transport Stack
#define ObjID_STKX25		33		// X.25 MTA Transport Stack

	// Monitor Configurations
#define ObjID_MSV			34		// Monitoring Server Configuration (DS)
#define ObjID_MLK			35		// Monitoring Link Configuration (DS)

	// Templates
#define ObjID_ATP			36		// Address Type
#define ObjID_ATL			37		// Address Template
#define ObjID_DTL			38		// Display Template

	// Schema Objects
#define ObjID_Schema		39		// The Schema container (DMD)
#define ObjID_SchemaAttr	40		// Schema Attribute
#define ObjID_SchemaObj		41		// Schema Object

	// Site Configurations
#define ObjID_ENC			42		// Encryption Configuration
#define ObjID_SADR			43		// Site Addressing
#define ObjID_SDSA			44		// Site Directory Configuration
#define ObjID_SMDB			45		// Site Information Store Configuration
#define ObjID_SMTA			46		// Site MTA Configuration

#define ObjID_ADDIN			47		// Add-In
#define ObjID_EXT			48		// Admin Extension





typedef struct _ADMIN_SheetInfo
{
	HINSTANCE	hInstance;
	UINT		iddDialog;		// To pass to MAKEINTRESOURCE()
	DLGPROC		lpfnDlgProc;
	UINT		idsName;		// For LoadString()
	LPARAM		lParam;			// Passed to DlgProc on WM_INITDIALOG
	LANGID 		langid;			// language ID of dialog to be loaded
} ADMIN_SheetInfo;


/*********************************************************************************/
/*********************************************************************************/

// Functions implemented by the Extension DLL
// and called by the Microsoft Exchange Administrator program.

typedef BOOL (PASCAL * PADMIN_InstallExtension) (ADMIN_ObjectInfo * poi);
typedef BOOL (PASCAL * PADMIN_DeinstallExtension) (ADMIN_ObjectInfo * poi);
typedef BOOL (PASCAL * PADMIN_ShowPage) (UINT iddAdminPage);
typedef INT (PASCAL * PADMIN_StartPage) (void);
typedef BOOL (PASCAL * PADMIN_InitSheet)
			(	ADMIN_ObjectInfo * poi,
				ULONG fFlags,
				ADMIN_SheetInfo ** ppsi,
				UINT * pcsi,
				VOID ** ppvExtensionData);

// PADMIN_InitSheet definitions for fFlags
#define fxfReadOnly					0x00000001
// high byte of fFlags reserved as private for extension dll writers to use as they see fit.
#define MaskExtensionPrivateFlags	0x00ffffff

/*********************************************************************************/
/*********************************************************************************/

// FSetActive()   typedef BOOL (PASCAL * PADMIN_RefreshDisplay) (VOID * pvExtensionData, HWND hwnd);
typedef BOOL (PASCAL * PADMIN_HasHelp) (VOID * pvExtensionData, HWND hwnd);
typedef VOID (PASCAL * PADMIN_DoHelp) (VOID * pvExtensionData, HWND hwnd);
typedef BOOL (PASCAL * PADMIN_SaveData) (VOID * pvExtensionData, HWND hwnd);
typedef BOOL (PASCAL * PADMIN_CommitData) (VOID * pvExtensionData, HWND hwnd);

typedef VOID (PASCAL * PADMIN_DeinitSheet)
				(VOID * pvExtensionData);


// The pointers in this structure (except pfnInitSheet) can be NULL
// if a pointer is null, no call is made.
typedef struct _ADMIN_ExtensionFunction
{
	int							nAPIVersion;
	PADMIN_InstallExtension		pfnInstallExtension;
	PADMIN_DeinstallExtension	pfnDeinstallExtension;
	PADMIN_InitSheet			pfnInitSheet;
	PADMIN_ShowPage				pfnShowPage;
	PADMIN_StartPage			pfnStartPage;
	PADMIN_HasHelp				pfnHasHelp;
	PADMIN_DoHelp				pfnDoHelp;
	PADMIN_SaveData				pfnSaveData;
	PADMIN_CommitData			pfnCommitData;
	PADMIN_DeinitSheet			pfnDeinitSheet;
} ADMIN_ExtensionFunction;



// Functions implemented by the Microsoft Exchange Administrator Program
// and called by the Extension DLL.

typedef RC (PASCAL * PADMIN_GetObjectDataSize)
				(HWND hwnd, LPWSTR wszBlobName, UINT * pcb);

typedef RC (PASCAL * PADMIN_GetObjectData)
				(HWND hwnd, LPWSTR wszBlobName, BYTE * pb, UINT cb);

typedef RC (PASCAL * PADMIN_SetObjectData)
				(HWND hwnd, BYTE * pb, UINT cb, BOOL fNew);

// These 2 APIs take WCHAR *, NOT TCHAR!!!
// szServiceName is the SHORT name of the service.
typedef BOOL (PASCAL * PADMIN_AddService)
				(HWND hwnd, LPWSTR wszServiceName);
typedef BOOL (PASCAL * PADMIN_RemoveService)
				(HWND hwnd, LPWSTR wszServiceName);

typedef VOID (PASCAL * PADMIN_InfoHasChanged)
				(HWND hwnd);

typedef VOID (PASCAL * PADMIN_SetIcon)
				(HWND hwnd, int id);

typedef VOID (PASCAL * PADMIN_SetTitle)
				(HWND hwnd, int id);

typedef BOOL (PASCAL * PADMIN_LoadDialogResource)
				(HINSTANCE hinst, UINT iddDialog, LANGID langid, BYTE ** ppbDialog);

// *ppbDialog will be set to NULL after being freed in this call
typedef VOID (PASCAL * PADMIN_FreeDialogResource)
				(BYTE ** ppbDialog);

/*
 *		psz is a pointer to an array of string pointers. The array is
 *		cstr elements long.
 *			Name 0:		psz[0], etc.
 *		The extension is responsible for calling FreeNameList to reelease the memory
 */
typedef BOOL (PASCAL * PADMIN_GetNameList)
				(HWND hwnd, int * pcstr, LPWSTR ** ppsz);
typedef void (PASCAL * PADMIN_FreeNameList)
				(int cstr, LPWSTR * psz);
/*
 *	Admin will make a copy of the strings, so the extension can release the memory
 *	it allocated when the SetProxy call returns.
 */
typedef BOOL (PASCAL * PADMIN_SetNameList)
				(HWND hwnd, int cstr, LPWSTR * psz);
// NOTE on both GetNameList and SetNameList: Admin will issue the error message if appropriate


typedef struct _ADMIN_AdministratorFunction
{
	PADMIN_GetObjectDataSize	pfnGetObjectDataSize;
	PADMIN_GetObjectData		pfnGetObjectData;
	PADMIN_SetObjectData		pfnSetObjectData;
	PADMIN_AddService			pfnAddService;
	PADMIN_RemoveService		pfnRemoveService;
	PADMIN_InfoHasChanged		pfnInfoHasChanged;
	PADMIN_SetIcon				pfnSetIcon;
	PADMIN_SetTitle				pfnSetTitle;
	PADMIN_GetNameList			pfnGetNameList;
	PADMIN_FreeNameList			pfnFreeNameList;
	PADMIN_SetNameList			pfnSetNameList;
	PADMIN_LoadDialogResource	pfnLoadDialogResource;
	PADMIN_FreeDialogResource	pfnFreeDialogResource;
} ADMIN_AdministratorFunction;

typedef struct _ADMIN_AdministratorConnections
{
	IMAPISession *		psesMapi;
	IAddrBook *			pab;
	IABContainer *		pabContainer;
} ADMIN_AdministratorConnections;


// Initialization function where the API is clarified.

typedef VOID (PASCAL * PADMIN_Initialize)
			(	ADMIN_AdministratorConnections * pac,
				ADMIN_AdministratorFunction * pAdminFunction,
				ADMIN_ExtensionFunction ** ppExtensionFunction);


#ifdef __cplusplus
}
#endif

#endif		// #ifndef _ADMINEXT_H_
