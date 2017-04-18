// --edktrack.h-----------------------------------------------------------------
//
//  Header file for module containing gateway tracking functions and structures.
// 
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _EDKTRACK_H
#define _EDKTRACK_H

#include "rpcpub.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//$--HrTrackInitLog-------------------------------------------------------------
//  This function initializes the gateway event tracking module.
// -----------------------------------------------------------------------------
HRESULT HrTrackInitLog(
	IN LPSTR lpszComputer,          // name of the remote computer
    OUT PVOID *ppvSession);         // pointer to gateway tracking session

//$--HrTrackWriteLog@-------------------------------------------------------
//  This function logs a gateway tracking event.
// ----------------------------------------------------------------------------
HRESULT HrTrackWriteLogW(
    IN PVOID           pvSession,       // gateway tracking session
    IN UINT            nEventType,      // gateway tracking event type
    IN SYSTEMTIME      stEvent,         // time event took place
    IN LPCWSTR         lpszGatewayName, // gateway name
    IN LPCWSTR         lpszPartner,     // pointer to entity name string
    IN LPCWSTR         lpszMTSID,       // pointer to MTS-ID string
    IN LPCWSTR         lpszSubjectMTSID,// pointer to subject MTS-ID string
    IN LPCWSTR         lpszRemoteID,    // pointer to foreign ID string
    IN LPCWSTR         lpszOriginator,  // pointer to originator string
    IN INT             nPriority,       // message priority
    IN INT             nLength,         // message length
    IN INT             nSeconds,        // seconds to process this message
    IN INT             nCost,           // cost of processing this message
    IN INT             cRecipients,     // count of recipients
    IN LPCWSTR        *lppszRecipients);// pointer to recipient pointers

HRESULT HrTrackWriteLogA(
    IN PVOID           pvSession,       // gateway tracking session
    IN UINT            nEventType,      // gateway tracking event type
    IN SYSTEMTIME      stEvent,         // time event took place
    IN LPCSTR          lpszGatewayName, // gateway name
    IN LPCSTR          lpszPartner,     // pointer to entity name string
    IN LPCSTR          lpszMTSID,       // pointer to MTS-ID string
    IN LPCSTR          lpszSubjectMTSID,// pointer to subject MTS-ID string
    IN LPCSTR          lpszRemoteID,    // pointer to foreign ID string
    IN LPCSTR          lpszOriginator,  // pointer to originator string
    IN INT             nPriority,       // message priority
    IN INT             nLength,         // message length
    IN INT             nSeconds,        // seconds to process this message
    IN INT             nCost,           // cost of processing this message
    IN INT             cRecipients,     // count of recipients
    IN LPCSTR         *lppszRecipients);// pointer to recipient pointers

#ifdef UNICODE
#define HrTrackWriteLog  HrTrackWriteLogW
#else
#define HrTrackWriteLog  HrTrackWriteLogA
#endif

//$--HrTrackUninitLog----------------------------------------------------------
//  This function uninitializes the gateway event tracking module.
// ----------------------------------------------------------------------------
HRESULT HrTrackUninitLog(
    IN OUT PVOID *ppvSession);          // pointer to gateway tracking session

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif
