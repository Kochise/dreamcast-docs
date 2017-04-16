// --edkmsg.mc-----------------------------------------------------------------
//
//  This file contains the messages common to the entire EDK.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// ----------------------------------------------------------------------------
//
//
// Message Naming Convention
// -------------------------
//
// Each message has a symbolic name that becomes a #define'ed constant for 
// use in a .C file.  A message's symbolic name should follow this naming 
// convention:
// 
// <COMPONENT>_<MESSAGE_DESCRIPTION>
//
// If a message is used by more than one library and/or application, then 
// <COMPONENT> should be "EDKEVENT".
//
// The <MESSAGE_DESCRIPTION> portion of the name describes what the message 
// is about.  For example, a message called EDKEVENT_INVALID_HEX_DIGIT could 
// indicate that an illegal hexidecimal digit was found.
//
// Only the first message in this file should have a Message ID number--
// the message compiler will then assign consecutive numbers to the rest.
//
//
// Generic Information message allowing user to fill in text or error code.
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


//
// Define the severity codes
//


//
// MessageId: EDKEVENT_INFORMATION
//
// MessageText:
//
//  %1
//
#define EDKEVENT_INFORMATION             ((DWORD)0x60000000L)

// Generic Warning message allowing user to fill in text or error code.
//
// MessageId: EDKEVENT_WARNING
//
// MessageText:
//
//  %1
//
#define EDKEVENT_WARNING                 ((DWORD)0xA0000001L)

// Generic Error message allowing user to fill in text or error code.
//
// MessageId: EDKEVENT_ERROR
//
// MessageText:
//
//  %1
//
#define EDKEVENT_ERROR                   ((DWORD)0xE0000002L)

//
// MessageId: WINWRAP_SERVICE_STARTING
//
// MessageText:
//
//  Service starting.
//
#define WINWRAP_SERVICE_STARTING         ((DWORD)0x60000003L)

//
// MessageId: WINWRAP_SERVICE_STARTED
//
// MessageText:
//
//  Service started.
//
#define WINWRAP_SERVICE_STARTED          ((DWORD)0x60000004L)

//
// MessageId: WINWRAP_SERVICE_STOPPING
//
// MessageText:
//
//  Service stopping.
//
#define WINWRAP_SERVICE_STOPPING         ((DWORD)0x60000005L)

//
// MessageId: WINWRAP_SERVICE_STOPPED
//
// MessageText:
//
//  Service stopped.
//
#define WINWRAP_SERVICE_STOPPED          ((DWORD)0x60000006L)

//
// MessageId: EDKEVENT_CANNOT_INIT_MAPI
//
// MessageText:
//
//  Unable to initialize MAPI.
//
#define EDKEVENT_CANNOT_INIT_MAPI        ((DWORD)0xE0000007L)

//
// MessageId: MESGXLAT_CNV_CONVERT_FAIL
//
// MessageText:
//
//  %1 conversion DLL convert function failed:  point = %2, class = %3, error code = %4.
//
#define MESGXLAT_CNV_CONVERT_FAIL        ((DWORD)0xE0000008L)

//
// MessageId: MESGXLAT_CNV_NO_CANDIDATE
//
// MessageText:
//
//  No conversion DLL candidate found for point = %1 and class = %2.
//
#define MESGXLAT_CNV_NO_CANDIDATE        ((DWORD)0xE0000009L)

//
// MessageId: MESGXLAT_CNV_NO_ACCEPT
//
// MessageText:
//
//  Candidate conversion DLL %1 rejected conversion for point = %2, class = %3.  Error code = %4.
//
#define MESGXLAT_CNV_NO_ACCEPT           ((DWORD)0xE000000AL)

//
// MessageId: MESGXLAT_CNV_QUERY_FAIL
//
// MessageText:
//
//  Conversion DLL %1 query function failed:  point = %2, class = %3.  Error code = %4.
//
#define MESGXLAT_CNV_QUERY_FAIL          ((DWORD)0xE000000BL)

//
// MessageId: MESGXLAT_CNV_BAD_SYNTAX
//
// MessageText:
//
//  Invalid registry key values for MAPI Conversion DLL %1:  entry point = %2 class = %3, options = %4, point = %5.
//
#define MESGXLAT_CNV_BAD_SYNTAX          ((DWORD)0xE000000CL)

