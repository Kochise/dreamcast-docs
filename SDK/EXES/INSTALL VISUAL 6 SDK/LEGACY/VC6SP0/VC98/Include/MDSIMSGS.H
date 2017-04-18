/************************************************************************
*                                                                        *
*   Copyright (c) 1996, Microsoft Corp. All rights reserved.             *
*                                                                        *
*   mdsimsg.h -- message code definitions for the MDSI functions         *  
*                                                                        *
************************************************************************/

#ifndef __MDSIMSGS_H__
#define __MDSIMSGS_H__

//
// Define the message IDs
//
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_MDSI                    0x900


//
// Define the severity codes
//


//
// MessageId: HOSTSEC_ERROR_UNABLE_TO_PROCESS_REQUEST
//
// MessageText:
//
//  Security DLL was unable to queue the request for processing.
//
#define HOSTSEC_ERROR_UNABLE_TO_PROCESS_REQUEST ((DWORD)0xE90005DDL)

//
// MessageId: HOSTSEC_ERROR_REMOTE_UNREACHABLE
//
// MessageText:
//
//  Host Process could not establish network connection to other NT side components.
//
#define HOSTSEC_ERROR_REMOTE_UNREACHABLE ((DWORD)0xE90005DEL)

//
// MessageId: HOSTSEC_ERROR_INVALID_USERNAME
//
// MessageText:
//
//  Invalid user name was specified or user does not exist.
//
#define HOSTSEC_ERROR_INVALID_USERNAME   ((DWORD)0xE90005DFL)

//
// MessageId: HOSTSEC_ERROR_INVALID_PASSWORD
//
// MessageText:
//
//  Invalid password was specified for the user.
//
#define HOSTSEC_ERROR_INVALID_PASSWORD   ((DWORD)0xE90005E0L)

//
// MessageId: NTSEC_ERROR_UNABLE_TO_PROCESS_REQUEST
//
// MessageText:
//
//  Host Process was unable to process the request.
//
#define NTSEC_ERROR_UNABLE_TO_PROCESS_REQUEST ((DWORD)0xE90005E1L)

//
// MessageId: NTSEC_ERROR_REMOTE_UNREACHABLE
//
// MessageText:
//
//  Security DLL could not establish network connection to host side components.
//
#define NTSEC_ERROR_REMOTE_UNREACHABLE   ((DWORD)0xE90005E2L)

//
// MessageId: NTSEC_ERROR_INVALID_USERNAME
//
// MessageText:
//
//  Invalid user name was specified or user does not exist on the host.
//
#define NTSEC_ERROR_INVALID_USERNAME     ((DWORD)0xE90005E3L)

//
// MessageId: NTSEC_ERROR_INVALID_OLD_PASSWORD
//
// MessageText:
//
//  Invalid old password for the host user was specified.
//
#define NTSEC_ERROR_INVALID_OLD_PASSWORD ((DWORD)0xE90005E4L)

//
// MessageId: NTSEC_ERROR_NOT_IMPLEMENTED
//
// MessageText:
//
//  Host Process function not implemented.
//
#define NTSEC_ERROR_NOT_IMPLEMENTED      ((DWORD)0xE90005E5L)

//
// MessageId: HOSTSEC_ERROR_NOT_IMPLEMENTED
//
// MessageText:
//
//  Security DLL function not implemented.
//
#define HOSTSEC_ERROR_NOT_IMPLEMENTED    ((DWORD)0xE90005E6L)

//
// MessageId: NTSEC_ERROR_INVALID_NEW_PASSWORD
//
// MessageText:
//
//  Invalid new password for the host user was specified.
//
#define NTSEC_ERROR_INVALID_NEW_PASSWORD ((DWORD)0xE90005E7L)

//
// MessageId: NTSEC_ERROR_NEW_PASSWORD_HAS_REPEATING_CHARS
//
// MessageText:
//
//  New host password supplied has repeating characters.
//
#define NTSEC_ERROR_NEW_PASSWORD_HAS_REPEATING_CHARS ((DWORD)0xE90005E8L)

//
// MessageId: NTSEC_ERROR_NEW_PASSWORD_TOO_LONG
//
// MessageText:
//
//  New host password supplied is longer than maximum allowed.
//
#define NTSEC_ERROR_NEW_PASSWORD_TOO_LONG ((DWORD)0xE90005E9L)

//
// MessageId: NTSEC_ERROR_NEW_PASSWORD_TOO_SHORT
//
// MessageText:
//
//  New host password supplied is shorter than minimum allowed.
//
#define NTSEC_ERROR_NEW_PASSWORD_TOO_SHORT ((DWORD)0xE90005EAL)

//
// MessageId: NTSEC_ERROR_NEW_PASSWORD_BAD_CHAR
//
// MessageText:
//
//  New host password supplied contains invalid characters.
//
#define NTSEC_ERROR_NEW_PASSWORD_BAD_CHAR ((DWORD)0xE90005EBL)

//
// MessageId: NTSEC_ERROR_NEW_PASSWORD_SPACES
//
// MessageText:
//
//  New host password supplied contains spaces.
//
#define NTSEC_ERROR_NEW_PASSWORD_SPACES  ((DWORD)0xE90005ECL)

//
// MessageId: NTSEC_ERROR_NEW_PASSWORD_NULL
//
// MessageText:
//
//  New host password supplied is null.
//
#define NTSEC_ERROR_NEW_PASSWORD_NULL    ((DWORD)0xE90005EDL)

//
// MessageId: NTSEC_ERROR_NEW_PASSWORD_NON_ALPHANUMERIC
//
// MessageText:
//
//  New host password supplied contains non-alphanumeric characters.
//
#define NTSEC_ERROR_NEW_PASSWORD_NON_ALPHANUMERIC ((DWORD)0xE90005EEL)

//
// MessageId: NTSEC_ERROR_NEW_PASSWORD_SAME_AS_PREVIOUS
//
// MessageText:
//
//  New host password supplied is same as the old host password.
//
#define NTSEC_ERROR_NEW_PASSWORD_SAME_AS_PREVIOUS ((DWORD)0xE90005EFL)

//
// MessageId: NTSEC_ERROR_NEW_PASSWORD_NOT_ALLOWED
//
// MessageText:
//
//  New host password supplied matches the one in Not Allowed Dictionary on the host.
//
#define NTSEC_ERROR_NEW_PASSWORD_NOT_ALLOWED ((DWORD)0xE90005F0L)

//
// MessageId: NTSEC_ERROR_NEW_PASSWORD_HISTORY_CONFLICT
//
// MessageText:
//
//  New host password supplied matches one of the previous passwords in the history list of the most recent passwords on the host.
//
#define NTSEC_ERROR_NEW_PASSWORD_HISTORY_CONFLICT ((DWORD)0xE90005F1L)

//
// MessageId: NTSEC_ERROR_REQUEST_REJECTED
//
// MessageText:
//
//  The host rejected the request for an unknown reason.
//
#define NTSEC_ERROR_REQUEST_REJECTED     ((DWORD)0xE90005F2L)

//
// MessageId: NTSEC_ERROR_PASSWORD_EXPIRED
//
// MessageText:
//
//  The password for the host user specified has expired.
//
#define NTSEC_ERROR_PASSWORD_EXPIRED     ((DWORD)0xE90005F3L)

//
// MessageId: NTSEC_ERROR_ACCOUNT_DISABLED
//
// MessageText:
//
//  The user account is disabled on the host.
//
#define NTSEC_ERROR_ACCOUNT_DISABLED     ((DWORD)0xE90005F4L)

//
// MessageId: NTSEC_ERROR_ACCOUNT_LOCKED
//
// MessageText:
//
//  The user account is locked on the host.
//
#define NTSEC_ERROR_ACCOUNT_LOCKED       ((DWORD)0xE90005F5L)

//
// MessageId: NTSEC_ERROR_USER_CANNOT_CHANGE_PASSWORD
//
// MessageText:
//
//  User does not have permission to change the account password on the host.
//
#define NTSEC_ERROR_USER_CANNOT_CHANGE_PASSWORD ((DWORD)0xE90005F6L)

#endif // __MDSIMSGS_H__
