/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1992-1996   Microsoft Corporation

Module Name:

    counters.c  

Abstract:

    This module contains the routines to calculate "DataPoint" values from
    the registry data.

    The algoritms were lifted from RussBls's "Data.C" in winmeter.

    All the math is done in floating point to get the correct results, at
    the sacrifice of efficiency on a 386 with not 387. We can always
    revisit these routines later.

Revision History:

    Bob Watson  11/04/92
        -- modified calculations to use more integer math and "early
            exits" to improve efficiency on slower & non-coprocessor
            machines
--*/

//==========================================================================//
//                                  Includes                                //
//==========================================================================//


#include "perfmon.h"       // perfmon include files
#include "counters.h"      // Exported declarations for this file


//==========================================================================//
//                                  Constants                               //
//==========================================================================//


#define INVERT             PERF_COUNTER_TIMER_INV
#define NS100_INVERT       PERF_100NSEC_TIMER_INV
#define NS100              PERF_100NSEC_TIMER
#define TIMER_MULTI        PERF_COUNTER_MULTI_TIMER
#define TIMER_MULTI_INVERT PERF_COUNTER_MULTI_TIMER_INV
#define NS100_MULTI        PERF_100NSEC_MULTI_TIMER
#define NS100_MULTI_INVERT PERF_100NSEC_MULTI_TIMER_INV


#define FRACTION 1
#define BULK     1

#define TOO_BIG   (FLOAT)1500000000

//==========================================================================//
//                              Local Functions                             //
//==========================================================================//



FLOAT
eGetTimeInterval(
    IN LONGLONG *pliCurrentTime,
    IN LONGLONG *pliPreviousTime,
    IN LONGLONG *pliFreq
)
/*++

Routine Description:

    Get the difference between the current and previous time counts,
        then divide by the frequency.
    
Arguments:

    IN pCurrentTime
    IN pPreviousTime
        used to compute the duration of this sample (the time between
        samples

    IN pliFreq
        # of  counts (clock ticks) per second

Return Value:

    Floating point representation of Time Interval (seconds)
--*/
{
    FLOAT   eTimeDifference;
    FLOAT   eFreq;
    FLOAT   eTimeInterval ;

    LONGLONG liDifference;

    // Get the number of counts that have occured since the last sample

    liDifference = *pliCurrentTime - *pliPreviousTime;

    if (liDifference <= (LONGLONG)0) {
        return (FLOAT) 0.0f;
    } else {
        eTimeDifference = (FLOAT)liDifference;

        // Get the counts per second

        eFreq = (FLOAT)(*pliFreq) ;
        if (eFreq <= 0.0f)
           return (FLOAT) 0.0f;

        // Get the time since the last sample.

        eTimeInterval = eTimeDifference / eFreq ;

        return (eTimeInterval) ;
    }
} // eGetTimeInterval

FLOAT
Counter_Counter_Common(
    IN PLINESTRUCT pLineStruct,
    IN INT iType
)
/*++

Routine Description:

    Take the difference between the current and previous counts
        then divide by the time interval
    
Arguments:

    IN pLineStruct
        Line structure containing data to perform computations on

    IN iType
        Counter Type
        

Return Value:

    Floating point representation of outcome
--*/
{
    FLOAT   eTimeInterval;
    FLOAT   eDifference;
    FLOAT   eCount ;
    BOOL    bValueDrop = FALSE ;

    LONGLONG   liDifference;

    if (iType != BULK) {

        // check if it is too big to be a wrap-around case
        if (pLineStruct->lnaCounterValue[0] <
            pLineStruct->lnaOldCounterValue[0])
           {
           if (pLineStruct->lnaCounterValue[0] -
               pLineStruct->lnaOldCounterValue[0] > (DWORD)0x00ffff0000)
              {
              return (FLOAT) 0.0f;
              }
           bValueDrop = TRUE ;
           }

        liDifference = pLineStruct->lnaCounterValue[0] -
                       pLineStruct->lnaOldCounterValue[0];

        liDifference &= (DWORD)(0x0ffffffff);

    } else {
        liDifference = pLineStruct->lnaCounterValue[0] -
                       pLineStruct->lnaOldCounterValue[0];
    }
    
    if (liDifference <= (LONGLONG) 0) {
        return (FLOAT) 0.0f;
    } else {
        eTimeInterval = eGetTimeInterval(&pLineStruct->lnNewTime,
                                        &pLineStruct->lnOldTime,
                                        &pLineStruct->lnPerfFreq) ;
        if (eTimeInterval <= 0.0f) {
            return (FLOAT) 0.0f;
        } else {
            eDifference = (FLOAT)(liDifference);

            eCount         = eDifference / eTimeInterval ;
            
            if (bValueDrop && eCount > (FLOAT) TOO_BIG) {
                // ignore this bogus data since it is too big for 
                // the wrap-around case
                eCount = (FLOAT) 0.0f ;
            }
            return(eCount) ;
        }
    }
} // Counter_Counter_Common


FLOAT
Counter_Average_Timer(
    IN PLINESTRUCT pLineStruct
)
/*++

Routine Description:

    Take the differences between the current and previous times and counts
    divide the time interval by the counts multiply by 10,000,000 (convert
    from 100 nsec to sec)
    
Arguments:

    IN pLineStruct
        Line structure containing data to perform computations on

Return Value:

    Floating point representation of outcome
--*/
{
    FLOAT   eTimeInterval;
    FLOAT   eCount;

    LONGLONG    liDifference;

    // Get the current and previous counts.

    liDifference = (DWORD)pLineStruct->lnaCounterValue[1] - 
            (DWORD)pLineStruct->lnaOldCounterValue[1];

    if ( liDifference <= 0) {
        return (FLOAT) 0.0f;
    } else {
        // Get the amount of time that has passed since the last sample
        eTimeInterval = eGetTimeInterval(&pLineStruct->lnaCounterValue[0],
                                            &pLineStruct->lnaOldCounterValue[0],
                                            &pLineStruct->lnPerfFreq) ;

        if (eTimeInterval < 0.0f) { // return 0 if negative time has passed
            return (0.0f);
        } else {
            // Get the number of counts in this time interval.
            eCount = eTimeInterval / (FLOAT)(liDifference);
            return(eCount) ;
        }
    }
} //Counter_Average_Timer



FLOAT
Counter_Average_Bulk(
    IN PLINESTRUCT pLineStruct
)
/*++

Routine Description:

    Take the differences between the current and previous byte counts and
    operation counts divide the bulk count by the operation counts
    
Arguments:

    IN pLineStruct
        Line structure containing data to perform computations on

Return Value:

    Floating point representation of outcome
--*/
{
    FLOAT   eBulkDelta;
    FLOAT   eDifference;
    FLOAT   eCount;

    LONGLONG liDifference;
    LONGLONG liBulkDelta;

    // Get the bulk count increment since the last sample

    liBulkDelta = pLineStruct->lnaCounterValue[0] -
            pLineStruct->lnaOldCounterValue[0];

    if (liBulkDelta <= (LONGLONG) 0) {
        return (FLOAT) 0.0f;
    } else {
        // Get the current and previous counts.
        liDifference = (DWORD)pLineStruct->lnaCounterValue[1] -
                (DWORD) pLineStruct->lnaOldCounterValue[1];
        liDifference &= (DWORD) (0x0ffffffff);

        // Get the number of counts in this time interval.

        if ( liDifference <= (LONGLONG) 0) {
            // Counter value invalid
            return (FLOAT) 0.0f;
        } else {
            eBulkDelta = (FLOAT) (liBulkDelta);
            eDifference = (FLOAT) (liDifference);
            eCount = eBulkDelta / eDifference ;

            // Scale the value to up to 1 second

            return(eCount) ;
        }
    }
} // Counter_Average_Bulk



FLOAT
Counter_Timer_Common(
    IN  PLINESTRUCT pLineStruct,
    IN  INT iType
)
/*++

Routine Description:

    Take the difference between the current and previous counts,
        Normalize the count (counts per interval)
        divide by the time interval (count = % of interval)
        if (invert)
            subtract from 1 (the normalized size of an interval)
        multiply by 100 (convert to a percentage)
        this value from 100.
    
Arguments:

    IN pLineStruct
        Line structure containing data to perform computations on

    IN iType
        Counter Type

Return Value:

    Floating point representation of outcome
--*/
{
    FLOAT   eTimeInterval;
    FLOAT   eDifference;
    FLOAT   eFreq;
    FLOAT   eFraction;
    FLOAT   eMultiBase;
    FLOAT   eCount ;

    LONGLONG   liTimeInterval;
    LONGLONG   liDifference;

    // Get the amount of time that has passed since the last sample

    if (iType == NS100 ||
        iType == NS100_INVERT ||
        iType == NS100_MULTI ||
        iType == NS100_MULTI_INVERT) {
            liTimeInterval = pLineStruct->lnNewTime100Ns -
                pLineStruct->lnOldTime100Ns ;
            eTimeInterval = (FLOAT) (liTimeInterval);
    } else {
            eTimeInterval = eGetTimeInterval(&pLineStruct->lnNewTime,
                                            &pLineStruct->lnOldTime,
                                            &pLineStruct->lnPerfFreq) ;
    }

    if (eTimeInterval <= 0.0f)
       return (FLOAT) 0.0f;

    // Get the current and previous counts.

    liDifference = pLineStruct->lnaCounterValue[0] -
            pLineStruct->lnaOldCounterValue[0] ;

    // Get the number of counts in this time interval.
    // (1, 2, 3 or any number of seconds could have gone by since
    // the last sample)

    eDifference = (FLOAT) (liDifference) ;

    if (iType == 0 || iType == INVERT)
    {
        // Get the counts per interval (second)

        eFreq = (FLOAT) (pLineStruct->lnPerfFreq) ;
        if (eFreq <= 0.0f)
           return (FLOAT) 0.0f;

        // Calculate the fraction of the counts that are used by whatever
        // we are measuring

        eFraction = eDifference / eFreq ;
    }
    else
    {
        eFraction = eDifference ;
    }

    // Calculate the fraction of time used by what were measuring.

    eCount = eFraction / eTimeInterval ;

    // If this is  an inverted count take care of the inversion.

    if (iType == INVERT || iType == NS100_INVERT)
        eCount = (FLOAT) 1.0 - eCount ;

    // If this is  an inverted multi count take care of the inversion.

    if (iType == TIMER_MULTI_INVERT || iType == NS100_MULTI_INVERT) {
        eMultiBase  = (FLOAT)pLineStruct->lnaCounterValue[1] ;
        eCount = (FLOAT) eMultiBase - eCount ;
    }

    // Scale the value to up to 100.

    eCount *= 100.0f ;

    if (eCount < 0.0f) eCount = 0.0f ;

    if (eCount > 100.0f &&
        iType != NS100_MULTI &&
        iType != NS100_MULTI_INVERT &&
        iType != TIMER_MULTI &&
        iType != TIMER_MULTI_INVERT) {

        eCount = 100.0f;
    }

    return(eCount) ;
} // Counter_Timer_Common


FLOAT
Counter_Raw_Fraction(
    IN PLINESTRUCT pLineStruct
)
/*++

Routine Description:

    Evaluate a raw fraction (no time, just two values: Numerator and
        Denominator) and multiply by 100 (to make a percentage;

Arguments:

    IN pLineStruct
        Line structure containing data to perform computations on

Return Value:

    Floating point representation of outcome
--*/
{
    FLOAT   eCount ;

    LONGLONG   liNumerator;

    if ( pLineStruct->lnaCounterValue[0] == 0 ||
            pLineStruct->lnaCounterValue[1] == 0 ) {
        // invalid value
        return (0.0f);
    } else {
        liNumerator = pLineStruct->lnaCounterValue[0] * 100;
        eCount = (FLOAT) (liNumerator)  /
                 (FLOAT) pLineStruct->lnaCounterValue[1];
        return(eCount) ;
    }
} // Counter_Raw_Fraction


FLOAT
eElapsedTime(
    PLINESTRUCT pLineStruct,
    INT iType
)
/*++

Routine Description:

    Converts 100NS elapsed time to fractional seconds

Arguments:

    IN pLineStruct
        Line structure containing data to perform computations on

    IN iType
        Unused.

Return Value:

    Floating point representation of elapsed time in seconds
--*/
{
    FLOAT   eSeconds ;

    LONGLONG   liDifference;

    if (pLineStruct->lnaCounterValue[0] <= (LONGLONG) 0) {
        // no data [start time = 0] so return 0
        return (FLOAT) 0.0f;
    } else {
        LONGLONG PerfFreq;
       
        PerfFreq = *(LONGLONG UNALIGNED *)(&pLineStruct->lnObject.PerfFreq) ;

        // otherwise compute difference between current time and start time
        liDifference = 
            pLineStruct->lnNewTime - pLineStruct->lnaCounterValue[0];

        if (liDifference <= (LONGLONG) 0 ||
            PerfFreq <= 0) {
            return (FLOAT) 0.0f;
        } else {
            // convert to fractional seconds using object counter
            eSeconds = (FLOAT) (liDifference) /
                (FLOAT) (PerfFreq);

            return (eSeconds);
        }
    }
    
} // eElapsedTime


FLOAT
Sample_Common(
    PLINESTRUCT pLineStruct,
    INT iType
)
/*++

Routine Description:

    Divites "Top" differenced by Base Difference

Arguments:

    IN pLineStruct
        Line structure containing data to perform computations on

    IN iType
        Counter Type

Return Value:

    Floating point representation of outcome
--*/
{
    FLOAT   eCount ;

    LONG    lDifference;
    LONG    lBaseDifference;

    lDifference = (DWORD)pLineStruct->lnaCounterValue[0] -
        (DWORD)pLineStruct->lnaOldCounterValue[0] ;
    lDifference &= (DWORD) (0x0ffffffff);

    if (lDifference <= 0) {
        return (FLOAT) 0.0f;
    } else {
        lBaseDifference = (DWORD)pLineStruct->lnaCounterValue[1] -
            (DWORD)pLineStruct->lnaOldCounterValue[1] ;

        if ( lBaseDifference <= 0 ) {
            // invalid value
            return (0.0f);
        } else {
            eCount = (FLOAT)lDifference / (FLOAT)lBaseDifference ;

            if (iType == FRACTION) {
                eCount *= (FLOAT) 100.0f ;
            }
            return(eCount) ;
        }
    }
} // Sample_Common


//==========================================================================//
//                             Exported Functions                           //
//==========================================================================//


/*****************************************************************************
 * Counter_Counter - Take the difference between the current and previous
 *                   counts then divide by the time interval
 ****************************************************************************/
#define Counter_Counter(pLineStruct)      \
        Counter_Counter_Common(pLineStruct, 0)
#if 0
FLOAT Counter_Counter(PLINESTRUCT pLineStruct)
{
        return Counter_Counter_Common(pLineStruct, 0) ;
}
#endif

/*****************************************************************************
 * Counter_Bulk    - Take the difference between the current and previous
 *                   counts then divide by the time interval
 *                   Same as a Counter_counter except it uses lognlong
 ****************************************************************************/
#define Counter_Bulk(pLineStruct)         \
        Counter_Counter_Common(pLineStruct, BULK)
#if 0
FLOAT Counter_Bulk(PLINESTRUCT pLineStruct)
{
        return Counter_Counter_Common(pLineStruct, BULK) ;
}
#endif


/*****************************************************************************
 * Counter_Timer100Ns -
 *
 *      Need to review with RussBl exactly what he is doing here.
 ****************************************************************************/
#define Counter_Timer100Ns(pLineStruct)     \
        Counter_Timer_Common(pLineStruct, NS100)
#if 0
FLOAT Counter_Timer100Ns(PLINESTRUCT pLineStruct)
{
        return Counter_Timer_Common(pLineStruct, NS100) ;
}
#endif

/*****************************************************************************
 * Counter_Timer100Ns_Inv -
 *
 *      Need to review with RussBl exactly what he is doing here.
 ****************************************************************************/
#define Counter_Timer100Ns_Inv(pLineStruct)     \
        Counter_Timer_Common(pLineStruct, NS100_INVERT)
#if 0
FLOAT Counter_Timer100Ns_Inv(PLINESTRUCT pLineStruct)
{
        return Counter_Timer_Common(pLineStruct, NS100_INVERT) ;

}
#endif

/*****************************************************************************
 * Counter_Timer_Multi -
 *
 *      Need to review with RussBl exactly what he is doing here.
 ****************************************************************************/
#define Counter_Timer_Multi(pLineStruct)     \
        Counter_Timer_Common(pLineStruct, TIMER_MULTI)
#if 0
FLOAT Counter_Timer_Multi(PLINESTRUCT pLineStruct)
{
        return Counter_Timer_Common(pLineStruct, TIMER_MULTI) ;
}
#endif

/*****************************************************************************
 * Counter_Timer_Multi_Inv -
 *
 *      Need to review with RussBl exactly what he is doing here.
 ****************************************************************************/
#define Counter_Timer_Multi_Inv(pLineStruct)       \
        Counter_Timer_Common(pLineStruct, TIMER_MULTI_INVERT)
#if 0
FLOAT Counter_Timer_Multi_Inv(PLINESTRUCT pLineStruct)
{
        return Counter_Timer_Common(pLineStruct, TIMER_MULTI_INVERT) ;
}
#endif


/*****************************************************************************
 * Counter_Timer100Ns_Multi -
 *
 *      Need to review with RussBl exactly what he is doing here.
 ****************************************************************************/
#define Counter_Timer100Ns_Multi(pLineStruct)     \
        Counter_Timer_Common(pLineStruct, NS100_MULTI)
#if 0
FLOAT Counter_Timer100Ns_Multi(PLINESTRUCT pLineStruct)
{
        return Counter_Timer_Common(pLineStruct, NS100_MULTI) ;
}
#endif

/*****************************************************************************
 * Counter_Timer100Ns_Multi_Inv -
 *
 *      Need to review with RussBl exactly what he is doing here.
 ****************************************************************************/
#define Counter_Timer100Ns_Multi_Inv(pLineStruct)    \
        Counter_Timer_Common(pLineStruct, NS100_MULTI_INVERT)
#if 0
FLOAT Counter_Timer100Ns_Multi_Inv(PLINESTRUCT pLineStruct)
{
        return Counter_Timer_Common(pLineStruct, NS100_MULTI_INVERT) ;
}
#endif

/*****************************************************************************
 * Counter_Timer - Take the difference between the current and previous
 *                 counts,
 *                 Normalize the count (counts per interval)
 *                 divide by the time interval (count = % of interval)
 *                 multiply by 100 (convert to a percentage)
 *                 this value from 100.
 ****************************************************************************/
#define Counter_Timer(pLineStruct)       \
        Counter_Timer_Common(pLineStruct, 0)
#if 0
FLOAT Counter_Timer(PLINESTRUCT pLineStruct)
{
        return Counter_Timer_Common(pLineStruct, 0) ;
}
#endif


/*****************************************************************************
 * Counter_Timer_Inv - Take the difference between the current and previous
 *                     counts,
 *                     Normalize the count (counts per interval)
 *                     divide by the time interval (count = % of interval)
 *                     subtract from 1 (the normalized size of an interval)
 *                     multiply by 100 (convert to a percentage)
 *                     this value from 100.
 ****************************************************************************/
#define Counter_Timer_Inv(pLineStruct)         \
      Counter_Timer_Common(pLineStruct, INVERT)
#if 0
FLOAT Counter_Timer_Inv(PLINESTRUCT pLineStruct)
{
        return Counter_Timer_Common(pLineStruct, INVERT) ;
}
#endif

/*****************************************************************************
 * Sample_Counter -
 ****************************************************************************/
#define Sample_Counter(pLineStruct)      \
      Sample_Common(pLineStruct, 0)
#if 0
FLOAT Sample_Counter(PLINESTRUCT pLineStruct)
{
        return Sample_Common(pLineStruct, 0) ;
}
#endif

/*****************************************************************************
 * Sample_Fraction -
 ****************************************************************************/
#define Sample_Fraction(pLineStruct)     \
     Sample_Common(pLineStruct, FRACTION)
#if 0
FLOAT Sample_Fraction(PLINESTRUCT pLineStruct)
{
        return Sample_Common(pLineStruct, FRACTION) ;
}
#endif

/*****************************************************************************
 * Counter_Rawcount - This is just a raw count.
 ****************************************************************************/
#define Counter_Rawcount(pLineStruct)     \
   ((FLOAT) ((DWORD) (pLineStruct->lnaCounterValue[0])))
#if 0
FLOAT Counter_Rawcount(PLINESTRUCT pLineStruct)
   {
   return((FLOAT) (pLineStruct->lnaCounterValue[0])) ;
   }
#endif

/*****************************************************************************
 * Counter_Large_Rawcount - This is just a raw count.
 ****************************************************************************/
#define Counter_Large_Rawcount(pLineStruct)     \
   ((FLOAT) (pLineStruct->lnaCounterValue[0]))

/*****************************************************************************
 * Counter_Elapsed_Time -
 ****************************************************************************/
#define Counter_Elapsed_Time(pLineStruct)         \
    eElapsedTime (pLineStruct, 0)
#if 0
FLOAT Counter_Elapsed_Time (PLINESTRUCT pLineStruct)
{
    return eElapsedTime (pLineStruct, 0);
}
#endif

/*****************************************************************************
 * Counter_Null - The counters that return nothing go here.
 ****************************************************************************/
#define Counter_Null(pline)        \
        ((FLOAT) 0.0)
#if 0
FLOAT Counter_Null(PLINESTRUCT pline)
{
        return((FLOAT) 0.0);
        pline;
}
#endif


FLOAT
CounterEntry (
    PLINESTRUCT pLine
)
{
    switch (pLine->lnCounterType) {
        case  PERF_COUNTER_COUNTER:
            return Counter_Counter (pLine);

        case  PERF_COUNTER_TIMER:
            return Counter_Timer (pLine);

        case  PERF_COUNTER_QUEUELEN_TYPE:
            return Counter_Queuelen(pLine);

        case  PERF_COUNTER_BULK_COUNT:
            return Counter_Bulk (pLine);

        case  PERF_COUNTER_TEXT:
            return Counter_Null (pLine);

        case  PERF_COUNTER_RAWCOUNT:
        case  PERF_COUNTER_RAWCOUNT_HEX:
            return Counter_Rawcount(pLine);

        case  PERF_COUNTER_LARGE_RAWCOUNT:
        case  PERF_COUNTER_LARGE_RAWCOUNT_HEX:
            return Counter_Large_Rawcount(pLine);

        case  PERF_SAMPLE_FRACTION:
            return Sample_Fraction(pLine);

        case  PERF_SAMPLE_COUNTER:
            return Sample_Counter (pLine);

        case  PERF_COUNTER_NODATA:
            return Counter_Null (pLine);

        case  PERF_COUNTER_TIMER_INV:
            return Counter_Timer_Inv (pLine);

        case  PERF_RAW_BASE:
//      case  PERF_SAMPLE_BASE:
//      case  PERF_AVERAGE_BASE:
            return Counter_Null (pLine);

        case  PERF_AVERAGE_TIMER:
            return Counter_Average_Timer (pLine);

        case  PERF_AVERAGE_BULK:
            return Counter_Average_Bulk (pLine);

        case  PERF_100NSEC_TIMER:
            return Counter_Timer100Ns (pLine);

        case  PERF_100NSEC_TIMER_INV:
            return Counter_Timer100Ns_Inv (pLine);

        case  PERF_COUNTER_MULTI_TIMER:
            return Counter_Timer_Multi (pLine);

        case  PERF_COUNTER_MULTI_TIMER_INV:
            return Counter_Timer_Multi_Inv (pLine);

        case  PERF_COUNTER_MULTI_BASE:
            return Counter_Null (pLine);

        case  PERF_100NSEC_MULTI_TIMER:
            return Counter_Timer100Ns_Multi (pLine);
                 
        case  PERF_100NSEC_MULTI_TIMER_INV:
            return Counter_Timer100Ns_Multi_Inv (pLine);

        case  PERF_RAW_FRACTION:
            return Counter_Raw_Fraction (pLine);

        case  PERF_ELAPSED_TIME:
            return Counter_Elapsed_Time (pLine);
           
        default:
            return Counter_Null (pLine);

    }
}


BOOL
IsCounterSupported (
    DWORD dwCounterType
)
{
    switch (dwCounterType) {
// supported counters
        case  PERF_COUNTER_COUNTER:
        case  PERF_COUNTER_TIMER:
        case  PERF_COUNTER_QUEUELEN_TYPE:
        case  PERF_COUNTER_BULK_COUNT:
        case  PERF_COUNTER_RAWCOUNT:
        case  PERF_COUNTER_RAWCOUNT_HEX:
        case  PERF_COUNTER_LARGE_RAWCOUNT:
        case  PERF_COUNTER_LARGE_RAWCOUNT_HEX:
        case  PERF_SAMPLE_FRACTION:
        case  PERF_SAMPLE_COUNTER:
        case  PERF_COUNTER_TIMER_INV:
        case  PERF_AVERAGE_TIMER:
        case  PERF_AVERAGE_BULK:
        case  PERF_100NSEC_TIMER:
        case  PERF_100NSEC_TIMER_INV:
        case  PERF_COUNTER_MULTI_TIMER:
        case  PERF_COUNTER_MULTI_TIMER_INV:
        case  PERF_100NSEC_MULTI_TIMER:
        case  PERF_100NSEC_MULTI_TIMER_INV:
        case  PERF_RAW_FRACTION:
        case  PERF_ELAPSED_TIME:
            return TRUE;

// unsupported counters
        case  PERF_COUNTER_TEXT:
        case  PERF_COUNTER_NODATA:
        case  PERF_RAW_BASE:
//      case  PERF_SAMPLE_BASE:
//      case  PERF_AVERAGE_BASE:
        case  PERF_COUNTER_MULTI_BASE:
        default:
            return FALSE;

    }
}
