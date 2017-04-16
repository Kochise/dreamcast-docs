// --edkcfg.h-------------------------------------------------------------------
// 
//  EDK Gateway Configuration Routines
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#ifndef _EDKCFG_H_
#define _EDKCFG_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//
// Type Definitions
//

//$--ADVISECALLBACK-------------------------------------------------------------
//  Function type for routine to be called when a binary blob changes.
// -----------------------------------------------------------------------------
typedef HRESULT (ADVISECALLBACK) (
    LPVOID              lpvUserContext, 
    LPWSTR              lpwszOwnerTag, 
    ULONG               cProps, 
    LPSPropValue        lpProps);

typedef ADVISECALLBACK *LPADVISECALLBACK;

//$--ADVISENOTIFY---------------------------------------------------------------
//  Object attached to an ADVISEOBJ, which represents a single blob and the 
//  callback routine to call when it is modified.
// -----------------------------------------------------------------------------
typedef struct _AdviseNotify {
    struct _AdviseNotify * lpNext;
    LPSTR              lpszOwnerTag;
    LPWSTR              lpwszOwnerTag;
    LPBYTE              lpbBlob;
    ULONG               cbBlob;
    LPADVISECALLBACK    lpfnCallback;
    LPVOID              lpvUserContext;
    BOOL                fFirstTime;
} ADVISENOTIFY, *LPADVISENOTIFY;

//$--ADVISEOBJ------------------------------------------------------------------
//  Object representing a MAPI session whose extension data is being monitored.
// -----------------------------------------------------------------------------
typedef struct {
    LPMAPISESSION       lpSession;
    LPMAPIPROP          lpCurrentObject;
    ULONG               nPollInterval;
    ULONG               ulUSNChangedPropTag;
    ULONG               ulExtensionDataPropTag;
    CRITICAL_SECTION    csCriticalSection;
    HANDLE              hPollThreadStop;
    HANDLE              hPollThread;
    ULONG               ulPollThreadID;
    ULONG               ulUSNChanged;
    LPSPropValue        lpExtensionData;
    LPADVISENOTIFY      lpNotifyList;
} ADVISEOBJ, *LPADVISEOBJ;

//
// Function Prototypes
//

//$--HrCfgCreateAdviseObj-------------------------------------------------------
//  Begin monitoring of a MAPI session for changes to extension data.
//  This routine should be called once to create an advise object for a MAPI 
//  session that is being monitored.  Then, HrCfgAdvise() should be called 
//  once for each extension data section that is being monitored.
//  If nPollInterval == 0 then no monitoring thread is created, and the user 
//  must do polling manually by calling HrCfgPollAdviseObj().
// -----------------------------------------------------------------------------
HRESULT HrCfgCreateAdviseObj(               // RETURNS: HRESULT
    IN  LPMAPISESSION       lpSession,      // MAPI session to monitor
    IN  ULONG               nPollInterval,  // milliseconds between polling
    OUT LPADVISEOBJ *       lppAdviseObj);  // created advise object

//$--HrCfgPollAdviseObj---------------------------------------------------------
//  Checks an advise object against what is stored in the DSA.  Calls the 
//  notification routines if there are any changes.
// -----------------------------------------------------------------------------
HRESULT HrCfgPollAdviseObj(                 // RETURNS: HRESULT
    IN  LPADVISEOBJ     lpAdviseObj);       // advise object to poll

//$--HrCfgDestroyAdviseObj------------------------------------------------------
//  End monitoring of a MAPI session.  This routine calls HrCfgUnadvise() for 
//  any extension data sections that are actively being monitored.
// -----------------------------------------------------------------------------
HRESULT HrCfgDestroyAdviseObj(              // RETURNS: HRESULT
    IN  LPADVISEOBJ         lpAdviseObj);   // advise object to destroy

//$--HrCfgAdvise----------------------------------------------------------------
//  Begin monitoring of an extension data section.  When the extension data 
//  changes, the specified callback routine is called.  Note: The callback 
//  routine will be called once from hrCfgAdvise() to set the initial extension 
//  data values.
// -----------------------------------------------------------------------------
HRESULT HrCfgAdvise(                        // RETURNS: HRESULT
    IN  LPADVISEOBJ         lpAdviseObj,    // advise object
    IN  LPSTR               lpszSection,    // name of extension data section
    IN  LPADVISECALLBACK    lpfnCallback,   // function to call on changes
    IN  LPVOID              lpvUserContext); // user-defined context

//$--HrCfgUnadvise--------------------------------------------------------------
//  End monitoring of an extension data section.
// -----------------------------------------------------------------------------
HRESULT HrCfgUnadvise(                      // RETURNS: HRESULT
    IN  LPADVISEOBJ         lpAdviseObj,    // advise object
    IN  LPSTR               lpszSection);   // name of extension data section

//$--HrCfgPackData--------------------------------------------------------------
//  Take a configuration name and a set of MAPI properties and pack them into 
//  a binary buffer suitable to be saved in the directory information tree for 
//  the gateway or other object.
// -----------------------------------------------------------------------------
HRESULT HrCfgPackDataA(					    // RETURN: HRESULT
	IN	LPSTR			lpszOwnerTag,		// name of configuration (or NULL)
	IN	ULONG			cProps,				// number of MAPI properties
	IN	LPSPropValue	lpProps,			// MAPI properties for this config.
	OUT	ULONG *			lpcbConfigData,		// size of resulting binary struct.
	OUT	LPBYTE *		lppbConfigData);	// resulting binary structure

HRESULT HrCfgPackDataW(					    // RETURN: HRESULT
	IN	LPWSTR			lpwszOwnerTag,	    // name of configuration (or NULL)
	IN	ULONG			cProps,				// number of MAPI properties
	IN	LPSPropValue	lpProps,			// MAPI properties for this config.
	OUT	ULONG *			lpcbConfigData,		// size of resulting binary struct.
	OUT	LPBYTE *		lppbConfigData);	// resulting binary structure

#ifdef UNICODE
#define HrCfgPackData HrCfgPackDataW
#else
#define HrCfgPackData HrCfgPackDataA
#endif

//$--HrCfgUnpackData------------------------------------------------------------
//  Take a packed binary buffer and unpack it to yield a configuration name, 
//  number of properties, and an array of MAPI properties.  If the number of 
//  properties is zero then NULL is returned for the array of properties.
// -----------------------------------------------------------------------------
HRESULT HrCfgUnpackDataA(					// RETURNS: HRESULT
	IN	ULONG			cbConfigData,		// size of of binary structure
	IN	LPBYTE			lpbConfigData,		// pointer to binary structure
	OUT	LPSTR *		    lppszOwnerTag,      // name of configuration (or NULL)
	OUT	ULONG *			lpcProps,			// number of MAPI properties
	OUT	LPSPropValue *	lppProps);			// MAPI properties for this config.

HRESULT HrCfgUnpackDataW(					// RETURNS: HRESULT
	IN	ULONG			cbConfigData,		// size of of binary structure
	IN	LPBYTE			lpbConfigData,		// pointer to binary structure
	OUT	LPWSTR *		lppwszOwnerTag,     // name of configuration (or NULL)
	OUT	ULONG *			lpcProps,			// number of MAPI properties
	OUT	LPSPropValue *	lppProps);			// MAPI properties for this config.

#ifdef UNICODE
#define HrCfgUnpackData HrCfgUnpackDataW
#else
#define HrCfgUnpackData HrCfgUnpackDataA
#endif

//$--HrOpenSiteContainer-----------------------------------------------------------------
//  Takes a pointer to a MAPI session and returns an IMAPIProp interface for 
//  the current site object.
// -----------------------------------------------------------------------------
HRESULT HrOpenSiteContainer(							// RETURNS: HRESULT
	IN	LPMAPISESSION	lpSession,			// MAPI session
	OUT	LPMAPIPROP *	lppSite);           // current site

//$--HrOpenSiteContainerAddressing-------------------------------------------------------
//  Takes a pointer to a MAPI session and returns an IMAPIProp interface for 
//  the current site addressing object.
// -----------------------------------------------------------------------------
HRESULT HrOpenSiteContainerAddressing(               // RETURNS: HRESULT
	IN	LPMAPISESSION	lpSession,          // MAPI session
	OUT	LPMAPIPROP *	lppSiteAddressing); // current site addressing

//$--HrOpenSessionObject--------------------------------------------------------
//  Takes a pointer to a MAPI session and returns an IMAPIProp interface for 
//  the current object that the session is logged in as.
// -----------------------------------------------------------------------------
HRESULT HrOpenSessionObject(				// RETURNS: HRESULT
	IN	LPMAPISESSION	lpSession,			// MAPI session
	OUT	LPMAPIPROP *	lppCurrentObject);	// current object

//$--HrCfgPropertyTagFromNameId----------------------------------------------------
//  Takes a pointer to an IMAPIProp interface and a name ID, and returns the 
//  MAPI property tag that represents the given name ID for that interface.
// -----------------------------------------------------------------------------
HRESULT HrCfgPropertyTagFromNameId(			// RETURNS: HRESULT
	IN	LPMAPIPROP		lpMAPIProp,			// IMAPIProp interface
    IN  LONG            lNameID,            // Name ID
	OUT	ULONG *			lpulPropTag);		// MAPI property tag of name ID

#ifdef __cplusplus
}
#endif

#endif
