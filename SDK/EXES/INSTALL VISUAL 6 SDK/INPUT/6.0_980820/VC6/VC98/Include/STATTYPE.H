// --stattype.h-----------------------------------------------------------------
//
// Defines types used in the stats component.
// 
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef __stattype_h
#define __stattype_h

// Flags for metric to calculate.
// ------------------------------
#define FM_CMESSAGES        0x00000001
#define FM_LONGEST_WAIT     0x00000002
#define FM_TOTAL_WAIT       0x00000004



typedef enum _jswindowtype
{
    JSWINDOW_MIN = 0,       // calculate the minimum in a window
    JSWINDOW_MAX,           // calculate the maximum in a window
    JSWINDOW_AVERAGE,       // calculate the average of a window
    JSWINDOW_TOTAL_RATE,    // calculate the total of a window
    JSWINDOW_LAST           // all types are less than this
} JSWINDOWTYPE;

#endif

