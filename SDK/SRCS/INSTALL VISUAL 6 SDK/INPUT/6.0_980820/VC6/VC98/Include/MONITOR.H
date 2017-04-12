// --monitor.h------------------------------------------------------------------
//
// Header file for module containing performance monitoring functions.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------
#if !defined(_MONITOR_H)
#define _MONITOR_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//
// Enumerated Types
//

//$--DIRECTIONTYPE--------------------------------------------------------------
//  Tells shether a statistic applies to messages going into or out of Exchange.
// -----------------------------------------------------------------------------
typedef enum _DirectionType				// (hungarian notation = dir)
{
	DIRECTIONTYPE_IN = 0, 				// coming into Exchange
	DIRECTIONTYPE_OUT, 					// going out of Exchange
	DIRECTIONTYPE_LAST					// all direction types less than this
} DIRECTIONTYPE;

//$--COUNTERTYPE----------------------------------------------------------------
//  Tells what statistic is to be counted.
// -----------------------------------------------------------------------------
typedef enum _CounterType				// (hungarian notation = ct)
{
	COUNTERTYPE_MESSAGES_IN_FOLDER = 0,	// total number of messages in folder
	COUNTERTYPE_BYTES_IN_FOLDER,		// total number of bytes in folder
	COUNTERTYPE_MESSAGES_ENTERING_FOLDER, // number of messages entering folder
	COUNTERTYPE_BYTES_ENTERING_FOLDER,	// number of bytes entering folder
	COUNTERTYPE_MESSAGES_LEAVING_FOLDER, // number of messages leaving folder
	COUNTERTYPE_BYTES_LEAVING_FOLDER,	// NOT IMPLEMENTED!!! (placeholder)
	COUNTERTYPE_MESSAGES_TRANSFERRED_IN, // messages transferred into Exchange
	COUNTERTYPE_BYTES_TRANSFERRED_IN,	// bytes transferred into Exchange
	COUNTERTYPE_MESSAGES_TRANSFERRED_OUT, // msgs transferred out of Exchange
	COUNTERTYPE_BYTES_TRANSFERRED_OUT,	// bytes transferred out of Exchange
	COUNTERTYPE_NDRS_IN,				// number of NDRs into Exchange
	COUNTERTYPE_NDRS_OUT,				// number of NDRs out of Exchange
	COUNTERTYPE_ASSOCIATIONS, 			// total number of associations
	COUNTERTYPE_USER_DEFINED, 			// counter maintained by user
	COUNTERTYPE_LAST					// all counter types are less than this
} COUNTERTYPE;

//$--PERIODTYPE-----------------------------------------------------------------
//  Tells what period the given statistic is to be totaled over.
// -----------------------------------------------------------------------------
typedef enum _PeriodType				// (hungarian notation = per)
{
	PERIODTYPE_NONE = 0,				// not a period statistic
	PERIODTYPE_CONTINUOUS,				// last Perf. Monitor sampling period
	PERIODTYPE_LAST_N_MINUTES,			// past N 1-minute intervals
	PERIODTYPE_TOTAL,					// since gateway started
	PERIODTYPE_LAST						// all period types are less than this
} PERIODTYPE;

//
// Structure Definitions
//

//$--COUNTER--------------------------------------------------------------------
//  The type for a variable that is being used as a counter.
// -----------------------------------------------------------------------------
typedef DWORD COUNTER, *LPCOUNTER;      // (hungarian notation = cnt)

//$--COUNTERDEF-----------------------------------------------------------------
//  A table of these structures is passed into rcMonitorInit() to describe the 
//  counters used in performance monitoring.  A counter table consisting of a 
//  table of COUNTER's is created, and it is guaranteed that the counters will 
//  be contiguous and in the same order as they are described in this table.
//  Contiguity is needed for some cases of calculated counters using user 
//  defined counters.
// -----------------------------------------------------------------------------
typedef struct _CounterDef				// (hungarian notation = cd)
{
	DWORD iCounterTitleOffset;			// index to counter name in registry 
										// (offset from First Counter)
	COUNTERTYPE ctStatistic;			// which statistic this counter monitors
	LPMAPIFOLDER lpFolder;				// folder that counter is from (if 
										// applicable)
	PERIODTYPE perPeriod;				// Period to total statistic (if 
										// applicable)
	DWORD cMinutes;						// N for PERIODTYPE_LAST_N_MINUTES
	LPCOUNTER * lppcntUserCounter;		// address to return a pointer to 
										// actual counter (for a user defined 
										// counter), or NULL if not needed
	DWORD dwUserCounterType;			// counter type as defined in winperf.h
										// (for a user defined counter)
	DWORD dwDetailLevel;				// counter complexity (from winperf.h)
	DWORD dwDefaultScale;				// default scale (from winperf.h)
} COUNTERDEF, *LPCOUNTERDEF;

//
// Public Function Declarations
//

//$--HrMonInit--------------------------------------------------------------
//  Begins performance monitoring of the current monitored object.
//
//  If lpszObjectClass != NULL, then use lpszObjectClass as the class of the  
//  monitored object.
//  If lpszObjectClass == NULL, then read the object class from the 
//  Parameters\ObjectClass value under the object's registry key, or if 
//  it's not present, assume that the object class is the same as the object 
//  name.
// -----------------------------------------------------------------------------
HRESULT HrMonInit( 					// RETURNS: HRESULT
	IN DWORD dwFlags,					// for future use--must be zero
	IN LPSTR lpszObjectClass,			// class of monitored object, or NULL
	IN LPSTR lpszObjectName, 			// gateway instance name
	IN DWORD dwObjectTitleOffset,		// index number of object name in 
										// the registry database (offset from
										// First Counter)
	IN DWORD dwObjectDetailLevel,		// complexity of object (see winperf.h)
	IN LONG dwDefaultCounter,			// zero-based number of default counter 
										// for this object
	IN DWORD ccdNumberOfCounters,		// number of counter structures
										// being passed in
	IN LPCOUNTERDEF lpcdCounters);		// pointer to array of counter
										// structures

//$--HrMonUninit----------------------------------------------------------
//  Ends performance monitoring of the current gateway.
// -----------------------------------------------------------------------------
HRESULT HrMonUninit(void);	    // RETURNS: HRESULT

//$--HrMonCollectNDRStats----------------------------------------------------
//  Call this after processing an NDR.
// -----------------------------------------------------------------------------
HRESULT HrMonCollectNDRStats(		// RETURNS: HRESULT
	IN DWORD cNDRs,						// number of NDR's processed
	IN DIRECTIONTYPE dir);				// direction of NDR's

//$--HrMonCollectMessageXferStats-------------------------------------
//  Call this after transferring a message.
// -----------------------------------------------------------------------------
HRESULT HrMonCollectMessageXferStats( // RETURNS: HRESULT
	IN DWORD cMessages, 				// number of messages transferred
	IN DWORD cBytes, 					// number of bytes transferred
	IN DIRECTIONTYPE dir);				// direction of message transfer

//$--HrMonCollectAssociationStats--------------------------------------------
//  Call this after making or breaking an association, or to set a new total 
//  number of associations.
// -----------------------------------------------------------------------------
HRESULT HrMonCollectAssociationStats( // RETURNS: HRESULT
	IN BOOL fSetNewTotal,				// if TRUE, iAssociations becomes 
										// the new total of associations.
										// if FALSE, iAssociations is added 
										// to the number of associations.

	IN LONG cAssociations);				// number of associations to add to
										// total (can be negative), or new 
										// total if fSetNewTotal == TRUE

//$--HrMonLockCounters------------------------------------------------------
//  Locks the block of counters against access by other threads/processes.
//  This should be called before accessing a user defined counter.
// -----------------------------------------------------------------------------
HRESULT HrMonLockCounters(void);	// RETURNS: HRESULT

//$--HrMonUnlockCounters----------------------------------------------------
//  Unlocks the block of counters to allow access by other threads/processes.
//  This should be called after accessing a user defined counter.
// -----------------------------------------------------------------------------
HRESULT HrMonUnlockCounters(void);	// RETURNS: HRESULT

#ifdef __cplusplus
}
#endif

#endif
