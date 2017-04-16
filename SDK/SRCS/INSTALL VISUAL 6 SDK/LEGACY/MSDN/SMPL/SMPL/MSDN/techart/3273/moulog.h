/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1992, 1993  Microsoft Corporation

Module Name:

    moulog.mc

Abstract:

    Constant definitions for the I/O error code log values.

Revision History:

--*/

#ifndef _MOULOG_
#define _MOULOG_

//
//  Status values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-------------------------+-------------------------------+
//  |Sev|C|       Facility          |               Code            |
//  +---+-+-------------------------+-------------------------------+
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
//      Facility - is the facility code
//
//      Code - is the facility's status code
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
#define FACILITY_RPC_STUBS               0x3
#define FACILITY_RPC_RUNTIME             0x2
#define FACILITY_MOUCLASS_ERROR_CODE     0x5
#define FACILITY_IO_ERROR_CODE           0x4


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: MOUCLASS_INSUFFICIENT_RESOURCES
//
// MessageText:
//
//  Not enough memory was available to allocate internal storage needed for the device %1.
//
#define MOUCLASS_INSUFFICIENT_RESOURCES  ((NTSTATUS)0xC0050001L)

//
// MessageId: MOUCLASS_NO_BUFFER_ALLOCATED
//
// MessageText:
//
//  Not enough memory was available to allocate the ring buffer that holds incoming data for %1.
//
#define MOUCLASS_NO_BUFFER_ALLOCATED     ((NTSTATUS)0xC0050002L)

//
// MessageId: MOUCLASS_NOT_ENOUGH_CONFIG_INFO
//
// MessageText:
//
//  Some firmware configuration information was incomplete, so defaults were used.
//
#define MOUCLASS_NOT_ENOUGH_CONFIG_INFO  ((NTSTATUS)0x40050003L)

//
// MessageId: MOUCLASS_USER_OVERRIDE
//
// MessageText:
//
//  User configuration data is overriding firmware configuration data.
//
#define MOUCLASS_USER_OVERRIDE           ((NTSTATUS)0x40050004L)

//
// MessageId: MOUCLASS_NO_DEVICEMAP_CREATED
//
// MessageText:
//
//  Unable to create the device map entry for %1.
//
#define MOUCLASS_NO_DEVICEMAP_CREATED    ((NTSTATUS)0x80050005L)

//
// MessageId: MOUCLASS_NO_DEVICEMAP_DELETED
//
// MessageText:
//
//  Unable to delete the device map entry for %1.
//
#define MOUCLASS_NO_DEVICEMAP_DELETED    ((NTSTATUS)0x80050006L)

//
// MessageId: MOUCLASS_NO_PORT_DEVICE_OBJECT
//
// MessageText:
//
//  Could not locate the device object for one or more pointer port devices.
//
#define MOUCLASS_NO_PORT_DEVICE_OBJECT   ((NTSTATUS)0xC0050007L)

//
// MessageId: MOUCLASS_NO_PORT_CONNECT
//
// MessageText:
//
//  Could not connect to port device %1.
//
#define MOUCLASS_NO_PORT_CONNECT         ((NTSTATUS)0xC0050008L)

//
// MessageId: MOUCLASS_PORT_INTERRUPTS_NOT_ENABLED
//
// MessageText:
//
//  Could not enable interrupts on connected port device %1.
//
#define MOUCLASS_PORT_INTERRUPTS_NOT_ENABLED ((NTSTATUS)0xC0050009L)

//
// MessageId: MOUCLASS_PORT_INTERRUPTS_NOT_DISABLED
//
// MessageText:
//
//  Could not disable interrupts on connected port device %1.
//
#define MOUCLASS_PORT_INTERRUPTS_NOT_DISABLED ((NTSTATUS)0xC005000AL)

//
// MessageId: MOUCLASS_MOU_BUFFER_OVERFLOW
//
// MessageText:
//
//  The ring buffer that stores incoming mouse data has overflowed (buffer size is configurable via the registry).
//
#define MOUCLASS_MOU_BUFFER_OVERFLOW     ((NTSTATUS)0x4005000BL)

//
// MessageId: MOUCLASS_INTERNAL_ERROR
//
// MessageText:
//
//  The driver for device %1 encountered an internal driver error.
//
#define MOUCLASS_INTERNAL_ERROR          ((NTSTATUS)0xC005000CL)

#endif /* _MOULOG_ */
