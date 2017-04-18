// -mbxdata.h-------------------------------------------------------------------
// Defines the configuration extension data for the Sample Mailbox Extension.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _MBXDATA_H_
#define _MBXDATA_H_

// Name of cfg extension data blob.
#define MBXBLOBNAME     "MBXData"
#define MBXBLOBNAMEW    L"MBXData"

// -----------------------------------------------------------------------------
// Index of properties within the extension data blob.
//
// NOTE: If you add a property, add it to the end of the array.  The MBXAdmin 
//       code is designed to handle a growing property array with ease.  If you 
//       remove one it would be easier to just make it an unused place holder.
// -----------------------------------------------------------------------------

typedef enum {          
    // PT_STRING8
    IDX_PASSWORD,       

    // Total number of properties in Extension Data Blob.
    // Keep this one at the very end of list.
    MBXDATA_PROP_COUNT
} PropIndex;

// -----------------------------------------------------------------------------

#endif // _MBXDATA_H_
