/*++
Copyright (c) 1999  Microsoft Corporation

Module Name:
    timer.h

Abstract:
    This file defines constants, macros, data structures and prototypes/inline
    functions related to a timer device.

Revision History:
    05-12-99    qiangw          created
--*/

#include <windef.h>

#ifndef _TIMER_H_
#define _TIMER_H_

#define TIMER_DEVICE_NAME               TEXT("\\Device\\TMU1")

#define TIMER_INTERVAL_MIN              1
#define TIMER_INTERVAL_MAX              1023

#define TIMER_STATUS_STOPPED            0x00000000
#define TIMER_STATUS_STOPPING           0x00000001
#define TIMER_STATUS_STARTED            0x00000002
#define TIMER_STATUS_STARTING           0x00000003

#define TIMER_FUNCTION_CODE_BASE        0x280

#define IOCTL_TIMER_CONFIG \
            CTL_CODE(FILE_DEVICE_BEEP, \
                     (TIMER_FUNCTION_CODE_BASE + 0), \
                     METHOD_BUFFERED, \
                     FILE_READ_ACCESS)
#define IOCTL_TIMER_START \
            CTL_CODE(FILE_DEVICE_BEEP, \
                     (TIMER_FUNCTION_CODE_BASE + 1), \
                     METHOD_BUFFERED, \
                     FILE_READ_ACCESS)
#define IOCTL_TIMER_STOP \
            CTL_CODE(FILE_DEVICE_BEEP, \
                     (TIMER_FUNCTION_CODE_BASE + 2), \
                     METHOD_BUFFERED, \
                     FILE_READ_ACCESS)
#define IOCTL_TIMER_ASYNC_START \
            CTL_CODE(FILE_DEVICE_BEEP, \
                     (TIMER_FUNCTION_CODE_BASE + 3), \
                     METHOD_BUFFERED, \
                     FILE_READ_ACCESS)
#define IOCTL_TIMER_ASYNC_STOP \
            CTL_CODE(FILE_DEVICE_BEEP, \
                     (TIMER_FUNCTION_CODE_BASE + 4), \
                     METHOD_BUFFERED, \
                     FILE_READ_ACCESS)
#define IOCTL_TIMER_GET_STATUS \
            CTL_CODE(FILE_DEVICE_BEEP, \
                     (TIMER_FUNCTION_CODE_BASE + 5), \
                     METHOD_BUFFERED, \
                     FILE_READ_ACCESS)

typedef DWORD (*PFNTIMERCALLBACK)(PVOID);

typedef struct _TIMER_CONFIG_DATA {
            DWORD nInterval;
            PFNTIMERCALLBACK pfnCallBack;
            PVOID pCallBackContext;
        } TIMER_CONFIG_DATA, *PTIMER_CONFIG_DATA;

#endif
