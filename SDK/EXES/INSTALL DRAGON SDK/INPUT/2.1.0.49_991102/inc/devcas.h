/*++
Copyright (c) 1999  Microsoft Corporation

Module Name:
    devcas.h

Abstract:
    This file defines constants, macros, data structures and prototypes/inline
    functions releated to Sega DevCas

Revision History:
    03-29-99    qiangw          created
--*/

#ifndef _DEVCAS_H_
#define _DEVCAS_H_

#include <windef.h>
#include <types.h>
#include <winbase.h>
#include <winioctl.h>

#define DEVCAS_PRIMARY_DEVICE_NAME     TEXT("\\Device\\SCSI0")
#define DEVCAS_SECONDARY_DEVICE_NAME   TEXT("\\Device\\SCSI1")

#define DEVCAS_FUNCTION_CODE_BASE      0x200

#define IOCTL_DEVCAS_GET_STATUS \
            CTL_CODE(FILE_DEVICE_CONTROLLER, \
                     (DEVCAS_FUNCTION_CODE_BASE + 0), \
                     METHOD_BUFFERED, \
                     FILE_READ_ACCESS)
#define IOCTL_DEVCAS_HOST_ATTENTION \
            CTL_CODE(FILE_DEVICE_CONTROLLER, \
                     (DEVCAS_FUNCTION_CODE_BASE + 1), \
                     METHOD_BUFFERED, \
                     FILE_READ_ACCESS)
#define IOCTL_DEVCAS_PURGE \
            CTL_CODE(FILE_DEVICE_CONTROLLER, \
                     (DEVCAS_FUNCTION_CODE_BASE + 2), \
                     METHOD_BUFFERED, \
                     FILE_READ_ACCESS)

#define DEVCAS_STATUS_HOST_ATTENTION    0x00000001

#endif
