//+-----------------------------------------------------------------------
//
// File:        KERBEROS.H
//
// Contents:    Public Kerberos Security Package structures for use
//              with APIs from SECURITY.H
//
//
// History:     26 Feb 92,  RichardW    Compiled from other files
//
//------------------------------------------------------------------------

#ifndef __KERBEROS_H__
#define __KERBEROS_H__
#include <ntmsv1_0.h>
#include <kerbcon.h>

#define MICROSOFT_KERBEROS_NAME_A   "Kerberos"
#define MICROSOFT_KERBEROS_NAME_W   L"Kerberos"
#ifdef WIN32_CHICAGO
#define MICROSOFT_KERBEROS_NAME MICROSOFT_KERBEROS_NAME_A
#else
#define MICROSOFT_KERBEROS_NAME MICROSOFT_KERBEROS_NAME_W
#endif


typedef struct _KERB_INIT_CONTEXT_DATA {
    TimeStamp StartTime;            // Start time
    TimeStamp EndTime;              // End time
    TimeStamp RenewUntilTime;       // Renew until time
    ULONG TicketOptions;            // From krb5.h
    ULONG RequestOptions;           // Options on what to return
} KERB_INIT_CONTEXT_DATA, *PKERB_INIT_CONTEXT_DATA;

#define KERB_INIT_RETURN_TICKET             0x1     // return raw ticket
#define KERB_INIT_RETURN_MIT_AP_REQ         0x2     // return MIT style AP request




typedef enum _KERB_LOGON_SUBMIT_TYPE {
    KerbInteractiveLogon = 2
} KERB_LOGON_SUBMIT_TYPE, *PKERB_LOGON_SUBMIT_TYPE;


typedef struct _KERB_INTERACTIVE_LOGON {
    KERB_LOGON_SUBMIT_TYPE MessageType;
    UNICODE_STRING LogonDomainName;
    UNICODE_STRING UserName;
    UNICODE_STRING Password;
    UNICODE_STRING SubAuthData;
    ULONG Flags;
} KERB_INTERACTIVE_LOGON, *PKERB_INTERACTIVE_LOGON;


#define KERB_LOGON_SUBUATH               0x1
#define KERB_LOGON_EMAIL_NAMES           0x2
#define KERB_LOGON_UPDATE_STATISTICS     0x4

//
// Use the same profile structure as MSV1_0
//

typedef MSV1_0_INTERACTIVE_PROFILE KERB_INTERACTIVE_PROFILE, *PKERB_INTERACTIVE_PROFILE;



typedef enum _KERB_PROTOCOL_MESSAGE_TYPE {
    KerbDebugRequestMessage = 0,
    KerbQueryTicketCacheMessage,
    KerbChangeMachinePasswordMessage,
    KerbVerifyPacMessage,
    KerbRetrieveTicketMessage
} KERB_PROTOCOL_MESSAGE_TYPE, *PKERB_PROTOCOL_MESSAGE_TYPE;

//
// Structure for a debuggin requequest
//

#define KERB_DEBUG_REQ_BREAKPOINT       0x1
#define KERB_DEBUG_REQ_CALL_PACK        0x2
#define KERB_DEBUG_REQ_DATAGRAM         0x3

typedef struct _KERB_DEBUG_REQUEST {
    KERB_PROTOCOL_MESSAGE_TYPE MessageType;
    ULONG DebugRequest;
} KERB_DEBUG_REQUEST, *PKERB_DEBUG_REQUEST;

//
// Used both for retrieving tickets and for querying ticket cache
//

typedef struct _KERB_QUERY_TKT_CACHE_REQUEST {
    KERB_PROTOCOL_MESSAGE_TYPE MessageType;
    LUID LogonId;
} KERB_QUERY_TKT_CACHE_REQUEST, *PKERB_QUERY_TKT_CACHE_REQUEST;

typedef struct _KERB_TICKET_CACHE_INFO {
    UNICODE_STRING ServerName;
    TimeStamp EndTime;
    TimeStamp RenewTime;
} KERB_TICKET_CACHE_INFO, *PKERB_TICKET_CACHE_INFO;

typedef struct _KERB_QUERY_TKT_CACHE_RESPONSE {
    KERB_PROTOCOL_MESSAGE_TYPE MessageType;
    ULONG CountOfTickets;
    KERB_TICKET_CACHE_INFO Tickets[ANYSIZE_ARRAY];
} KERB_QUERY_TKT_CACHE_RESPONSE, *PKERB_QUERY_TKT_CACHE_RESPONSE;



//
// This must match NT_OWF_PASSWORD_LENGTH
//

#define KERB_MACH_PWD_LENGTH 16

typedef struct _KERB_CHANGE_MACH_PWD_REQUEST {
    KERB_PROTOCOL_MESSAGE_TYPE MessageType;
    UCHAR NewPassword[KERB_MACH_PWD_LENGTH];
} KERB_CHANGE_MACH_PWD_REQUEST, *PKERB_CHANGE_MACH_PWD_REQUEST;

//
// These messages are used by the kerberos package to verify that the PAC in a
// ticket is valid. It is remoted from a workstation to a DC in the workstation's
// domain. On failure there is no response message. On success there may be no
// message or the same message may be used to send back a PAC updated with
// local groups from the domain controller. The checksum is placed in the
// final buffer first, followed by the signature.
//

#include <pshpack1.h>
typedef struct _KERB_VERIFY_PAC_REQUEST {
    KERB_PROTOCOL_MESSAGE_TYPE MessageType;
    ULONG ChecksumLength;
    ULONG SignatureType;
    ULONG SignatureLength;
    UCHAR ChecksumAndSignature[ANYSIZE_ARRAY];
} KERB_VERIFY_PAC_REQUEST, *PKERB_VERIFY_PAC_REQUEST;
#include <poppack.h>


#endif  // __KERBEROS_H__


