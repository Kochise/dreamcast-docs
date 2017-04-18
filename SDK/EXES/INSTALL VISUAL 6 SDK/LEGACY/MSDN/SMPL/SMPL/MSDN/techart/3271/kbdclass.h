/*++

Copyright (c) 1989, 1990, 1991, 1992, 1993  Microsoft Corporation

Module Name:

    KBDCLASS.h

Abstract:

    These are the structures and defines that are used in the
    mouse class driver.

Revision History:

--*/

// RAc --

/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1992, 1993  Microsoft Corporation

Module Name:

    moulog.mc

Abstract:

    Constant definitions for the I/O error code log values.

Revision History:

--*/
/*
#ifndef _MOULOG_
#define _MOULOG_

#define FACILITY_RPC_STUBS               0x3
#define FACILITY_RPC_RUNTIME             0x2
#define FACILITY_KBDCLASS_ERROR_CODE     0x5
#define FACILITY_IO_ERROR_CODE           0x4
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3
*/
#define INPUTCLASS_INSUFFICIENT_RESOURCES KBDCLASS_INSUFFICIENT_RESOURCES 
#define INPUTCLASS_NO_BUFFER_ALLOCATED KBDCLASS_NO_BUFFER_ALLOCATED    
#define INPUTCLASS_NOT_ENOUGH_CONFIG_INFO KBDCLASS_NOT_ENOUGH_CONFIG_INFO 
#define INPUTCLASS_USER_OVERRIDE KBDCLASS_USER_OVERRIDE          
#define INPUTCLASS_NO_DEVICEMAP_CREATED KBDCLASS_NO_DEVICEMAP_CREATED   
#define INPUTCLASS_NO_DEVICEMAP_DELETED KBDCLASS_NO_DEVICEMAP_DELETED   
#define INPUTCLASS_NO_PORT_DEVICE_OBJECT KBDCLASS_NO_PORT_DEVICE_OBJECT  
#define INPUTCLASS_NO_PORT_CONNECT KBDCLASS_NO_PORT_CONNECT        
#define INPUTCLASS_PORT_INTERRUPTS_NOT_ENABLED KBDCLASS_PORT_INTERRUPTS_NOT_ENABLED
#define INPUTCLASS_PORT_INTERRUPTS_NOT_DISABLED KBDCLASS_PORT_INTERRUPTS_NOT_DISABLED
#define INPUTCLASS_BUFFER_OVERFLOW KBDCLASS_BUFFER_OVERFLOW    
#define INPUTCLASS_INTERNAL_ERROR KBDCLASS_INTERNAL_ERROR 

#define INPUT_DATA KEYBOARD_INPUT_DATA
#define PINPUT_DATA PKEYBOARD_INPUT_DATA
#define INPUT_ATTRIBUTES KEYBOARD_ATTRIBUTES

#define INPUT_ERROR_VALUE_BASE KEYBOARD_ERROR_VALUE_BASE

#define IO_INPUT_INCREMENT IO_KEYBOARD_INCREMENT

#define INPUT_UNIT_ID_PARAMETER KEYBOARD_UNIT_ID_PARAMETER
#define PINPUT_UNIT_ID_PARAMETER PKEYBOARD_UNIT_ID_PARAMETER

#define INPUTCLASS_PORT_INTERRUPTS_NOT_ENABLED KBDCLASS_PORT_INTERRUPTS_NOT_ENABLED
#define INPUTCLASS_PORT_INTERRUPTS_NOT_DISABLED KBDCLASS_PORT_INTERRUPTS_NOT_DISABLED

#define FILE_DEVICE_INPUT FILE_DEVICE_KEYBOARD

#define IOCTL_INTERNAL_INPUT_ENABLE IOCTL_INTERNAL_KEYBOARD_ENABLE
#define IOCTL_INTERNAL_INPUT_DISABLE IOCTL_INTERNAL_KEYBOARD_DISABLE

#define IOCTL_INTERNAL_INPUT_CONNECT IOCTL_INTERNAL_KEYBOARD_CONNECT




#define QSIZESTRING L"KeyboardDataQueueSize"
#define BASENAMESTRING L"KeyboardDeviceBaseName"
#define SERVICEDNOSTRING L"MaximumPortsServiced"
#define CONNECTMULTIPLESTRING L"ConnectMultiplePorts"

#ifndef _KBDCLASS_
#define _KBDCLASS_

#include <ntddkbd.h>

//
// Define the default number of elements in the class input data queue.
//

#define DATA_QUEUE_SIZE 100

// we only need one of those ever... this contains the global data that every device
// object needs to access...

class CGlobalInputClassData
{ public:
  NTSTATUS m_status;
  INPUT_ATTRIBUTES InputAttributes;
  ULONG MaximumPortsServiced;
  ULONG ConnectOneClassToOnePort;
  PDEVICE_OBJECT *PortDeviceObjectList;
  CGlobalInputClassData();
  ~CGlobalInputClassData();
  BOOLEAN InitializePortDeviceObjectList();

};

//
// Class device extension.
//

class CInputClassDeviceExt 
{ private:
    int m_iStructureSize; // to make the class more generic...
    PCHAR m_InputData;
    PCHAR m_DataIn;
    PCHAR m_DataOut;
  public:
    NTSTATUS m_status;

  public:   // data members
    BOOLEAN RequestIsPending;
    BOOLEAN CleanupWasInitiated;
    ULONG InputCount;
    KSPIN_LOCK SpinLock;
    ULONG SequenceNumber;
    BOOLEAN OkayToLogOverflow;
    CGlobalInputClassData *cData;
  public:
    CInputClassDeviceExt(CGlobalInputClassData *);
	~CInputClassDeviceExt();
    void FlushDataQueue();
    int Insert(PCHAR source, int iSize);
	int Remove(PCHAR dest, int iSize);
}; 

//
// Mouse configuration information.  
//

typedef struct _KEYBOARD_CONFIGURATION_INFORMATION {

    //
    // Maximum size of class input data queue, in bytes.
    //

    ULONG  DataQueueSize;

} KEYBOARD_CONFIGURATION_INFORMATION, *PKEYBOARD_CONFIGURATION_INFORMATION;

#endif // _KBDCLASS_
