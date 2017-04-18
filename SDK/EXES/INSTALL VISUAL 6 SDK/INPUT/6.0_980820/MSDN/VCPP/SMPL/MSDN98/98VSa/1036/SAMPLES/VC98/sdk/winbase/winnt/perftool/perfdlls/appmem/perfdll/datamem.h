/*++

Copyright (c) 1995-1997 Microsoft Corporation

Module Name:

      datamem.h

Abstract:

    Header file for the application help performance Object data
    definitions

    This file contains definitions to construct the dynamic data
    which is returned by the Configuration Registry.  Data from
    various system API calls is placed into the structures shown
    here.

Author:

   Bob Watson 24-aug-95

Revision History:


--*/

#ifndef _DATAMEM_H_
#define _DATAMEM_H_

//
//  pack on 8-byte boundries so any longlong fields won't cause alignment
//  faults on RISC platforms
//
//
#pragma pack (8)

//
//  Extensible Object definitions
//

//  Update the following sort of define when adding an object type.

#define APP_MEM_NUM_PERF_OBJECT_TYPES 1

//----------------------------------------------------------------------------

//  Application memory counters
//  
//
//  This is the counter structure presently returned by Nbf for
//  each Resource.  Each Resource is an Instance, named by its number.
//
typedef struct _APPMEM_DATA_DEFINITION {
    PERF_OBJECT_TYPE		AppMemObjectType;
    PERF_COUNTER_DEFINITION AppMemBytesAllocated;
    PERF_COUNTER_DEFINITION AppMemAllocs;
    PERF_COUNTER_DEFINITION AppMemAllocsSec;
    PERF_COUNTER_DEFINITION AppMemReAllocs;
    PERF_COUNTER_DEFINITION AppMemReAllocsSec;
    PERF_COUNTER_DEFINITION AppMemFrees;
    PERF_COUNTER_DEFINITION AppMemFreesSec;
} APPMEM_DATA_DEFINITION;

typedef struct _APPMEM_COUNTERS {
    PERF_COUNTER_BLOCK  CounterBlock;
    DWORD               dwAppMemBytesAllocated;
    DWORD               dwAppMemAllocs;
    DWORD               dwAppMemAllocsSec;
    DWORD               dwAppMemReAllocs;
    DWORD               dwAppMemReAllocsSec;
    DWORD               dwAppMemFrees;
    DWORD               dwAppMemFreesSec;
} APPMEM_COUNTERS, *PAPPMEM_COUNTERS;

#pragma pack ()

#endif //_DATAMEM_H_
