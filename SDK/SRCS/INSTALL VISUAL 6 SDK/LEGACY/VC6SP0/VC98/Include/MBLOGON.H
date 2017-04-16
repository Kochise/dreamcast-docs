// --MBLOGON.h------------------------------------------------------------------
// 
//  Header file for module containing message store logon/logoff functions.
// 
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _MBLOGON_H
#define _MBLOGON_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//$--HrMailboxLogon------------------------------------------------------
// -----------------------------------------------------------------------------
HRESULT HrMailboxLogon(
    IN  LPMAPISESSION   lplhSession,                // ptr to MAPI session handle
    IN  LPMDB           lpMDB,                      // ptr to message store
    IN  LPSTR           lpszMsgStoreDN,             // ptr to message store DN
    IN  LPSTR           lpszMailboxDN,              // ptr to mailbox DN
    OUT LPMDB           *lppMailboxMDB);            // ptr to mailbox message store ptr

//$--HrMailboxLogoff-------------------------------------------------------
// -----------------------------------------------------------------------------
HRESULT HrMailboxLogoff(
    IN OUT LPMDB *lppMailboxMDB);                   // mailbox message store pointer

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _MBLOGON_H
