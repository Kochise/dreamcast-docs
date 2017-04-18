// --gwreport.h-----------------------------------------------------------------
// 
//  Gateway report functions.
// 
// Copyright (C) Microsoft Corp., 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------
#if !defined(_GWREPORT_H)
#define _GWREPORT_H

#include <wchar.h>
#include <tchar.h>
#include "edkdebug.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// =============================================================================
//
// Non-Delivery Report Functions
//
// =============================================================================

//$--HrNDRCreateFailedRecipList-------------------------------------------------
//
//  Create an empty list of failed recipients.
//
// -----------------------------------------------------------------------------
HRESULT HrNDRCreateFailedRecipList(         // RETURNS: return code
    OUT    LPADRLIST*    lppAdrList);       // address list

//$--HrNDRGetFailedRecipList----------------------------------------------------
//
//  Create a failed recipient entry.
//
// -----------------------------------------------------------------------------
HRESULT HrNDRGetFailedRecipList(            // RETURNS: return code
    IN     LPADRENTRY    lpAdrEntry,        // address entry
    IN     ULONG         cExtraProps,       // count of extra properties
    IN     LPSPropValue  lpExtraProps,      // extra properties
    OUT    ULONG*        lpcFailedProps,    // count of failed properties
    OUT    LPSPropValue* lppFailedProps);   // failed properties

//$--HrNDRAddToFailedRecipList--------------------------------------------------
//
//  Add a recipient entry to the list of failed recipients.
//
// -----------------------------------------------------------------------------
HRESULT HrNDRAddToFailedRecipList(          // RETURNS: return code
    IN     ULONG         cFailedProps,      // count of failed properties
    IN     LPSPropValue  lpFailedProps,     // failed properties
    IN OUT LPADRLIST*    lppAdrList);       // address list

//$--HrNDRGetFailedProps----------------------------------------------------------
//
//  Get NDR properties from the original message.
//
// -----------------------------------------------------------------------------
HRESULT HrNDRGetFailedProps(                  // RETURNS: return code
    IN     LPMESSAGE     lpMessage,         // message
    OUT    ULONG*        lpcProps,          // count of properties
    OUT    LPSPropValue* lppProps);         // properties

//$--HrNDRCreate----------------------------------------------------------------
//
//  Create a non-delivery report.
//
// -----------------------------------------------------------------------------
HRESULT HrNDRCreate(                        // RETURNS: return code
    IN     LPADRBOOK     lpAdrBook,         // address book
    IN     LPMAPIFOLDER  lpFolder,          // folder
    IN     LPMESSAGE     lpMessage,         // message
    IN     LPADRLIST     lpAdrList,         // address list
    IN     ULONG         cProps,            // count of properties
    IN     LPSPropValue  lpProps,           // properties
    OUT    LPMESSAGE*    lppReport);        // report

// =============================================================================
//
// Delivery Report Functions
//
// =============================================================================

//$--HrDRCreateDeliveredRecipList-----------------------------------------------
//
//  Create an empty list of delivered recipients.
//
// -----------------------------------------------------------------------------
HRESULT HrDRCreateDeliveredRecipList(       // RETURNS: return code
    OUT    LPADRLIST*    lppAdrList);       // address list

//$--HrDRGetDeliveredRecip--------------------------------------------------
//
//  Create a delivered recipient entry.
//
// -----------------------------------------------------------------------------
HRESULT HrDRGetDeliveredRecip(          // RETURNS: return code
    IN     LPADRENTRY    lpAdrEntry,        // address entry
    IN     ULONG         cExtraProps,       // count of extra properties
    IN     LPSPropValue  lpExtraProps,      // extra properties
    OUT    ULONG*        lpcDeliveredProps, // count of delivered properties
    OUT    LPSPropValue* lppDeliveredProps);// delivered properties

//$--HrDRAddToDeliveredRecipList------------------------------------------------
//
//  Add a recipient entry to the list of delivered recipients.
//
// -----------------------------------------------------------------------------
HRESULT HrDRAddToDeliveredRecipList(        // RETURNS: return code
    IN     ULONG         cDeliveredProps,   // count of delivered properties
    IN     LPSPropValue  lpDeliveredProps,  // delivered properties
    IN OUT LPADRLIST*    lppAdrList);       // address list

//$--HrDRGetProps-----------------------------------------------------------
//
//  Get DR properties from the original message.
//
// -----------------------------------------------------------------------------
HRESULT HrDRGetProps(                   // RETURNS: return code
    IN     LPMESSAGE     lpMessage,         // message
    OUT    ULONG*        lpcProps,          // count of properties
    OUT    LPSPropValue* lppProps);         // properties

//$--HrDRCreate-----------------------------------------------------------------
//
//  Create a delivery report.
//
// -----------------------------------------------------------------------------
HRESULT HrDRCreate(                         // RETURNS: return code
    IN     LPADRBOOK     lpAdrBook,         // address book
    IN     LPMAPIFOLDER  lpFolder,          // folder
    IN     LPMESSAGE     lpMessage,         // message
    IN     LPADRLIST     lpAdrList,         // address list
    IN     ULONG         cProps,            // count of properties
    IN     LPSPropValue  lpProps,           // properties
    OUT    LPMESSAGE*    lppReport);        // report

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
