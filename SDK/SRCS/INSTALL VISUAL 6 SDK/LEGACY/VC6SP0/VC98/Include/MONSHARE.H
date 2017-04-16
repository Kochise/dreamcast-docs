// --monshare.h-----------------------------------------------------------------
//
//  Header file containing the definition of the performance monitoring shared 
//  memory structure.  The shared memory is used to communicate between the 
//  monitored object side and the performance DLL called by the NT Performance 
//  Monitor.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------
#if !defined(_MONSHARE_H)
#define _MONSHARE_H

//
// Mapping and Mutex Object Names
//

// NOTE: "" and L"" versions must be the same!!!

#define MON_MAPPING_NAME_TEMPLATE	"MS Exchange SDK PerfMon Mapping %s"
#define MON_MAPPING_NAME_TEMPLATE_W	L"MS Exchange SDK PerfMon Mapping %s"

#define MON_MUTEX_NAME_TEMPLATE 	"MS Exchange SDK PerfMon Mutex %s"
#define MON_MUTEX_NAME_TEMPLATE_W	L"MS Exchange SDK PerfMon Mutex %s"

//
// Defined Constants
//

// MON_SHARED_MEMORY_SIGNATURE identifies the shared memory section as an 
// Exchange SDK performance monitoring shared memory communication block.
// This constant should be incremented when the structure of the shared 
// memory section is changed to catch version mismatches between the  
// monitored object and the DLL.

#define MON_SHARED_MEMORY_SIGNATURE     0x47575011

// MON_DATA_BLOCK_SIZE is the size of the buffer within the shared block 
// in which is built the structure that is sent to the Windows NT 
// Performance Monitor.  This value may be increased if needed to hold 
// a larger number of counters.  A change in this value does not require 
// any other values to be changed.

#define MON_DATA_BLOCK_SIZE			    4000

// MON_MUTEX_TIMEOUT is the number of miliseconds to wait for the 
// mutex that locks the shared memory section.  May be defined as 
// INFINITE to wait forever.

#define MON_MUTEX_TIMEOUT               (5*60*1000)

//
// Structure Definitions
//

//$--MONSHAREDMEMORY------------------------------------------------------------
//  This is the structure of the shared memory block used to communicate with 
//  the performance DLL.  The _PERF_* structures are all built inside the 
//  rgbDataBlock array within this structure.
// -----------------------------------------------------------------------------
typedef struct _MonSharedMemory			// (hungarian notation = msm)
{
    DWORD dwSignature;                  // value that identifies this as an 
                                        // Exchange SDK perf mon memory block
	DWORD fDataIsValid;					// safe for DLL to use shared mem data
	DWORD ibHeaderOffset;				// offset of _PERF_OBJECT_TYPE and 
										// _PERF_COUNTER_DEFINITION structures
										// in this shared memory block
	DWORD cbHeaderSize;					// size of _PERF_OBJECT_TYPE and 
										// _PERF_COUNTER_DEFINITION structures
										// in this shared memory block
	DWORD ibInstanceOffset;				// offset of _PERF_INSTANCE_DEFINITION,
										// _PERF_COUNTER_BLOCK and counters
										// in this shared memory block
	DWORD cbInstanceSize;				// size of _PERF_INSTANCE_DEFINITION,
										// _PERF_COUNTER_BLOCK and counters
										// in this shared memory block
	BYTE rgbDataBlock[MON_DATA_BLOCK_SIZE];	// the actual data block containing
										// both of the structures listed above
} MONSHAREDMEMORY, *LPMONSHAREDMEMORY;

#endif
