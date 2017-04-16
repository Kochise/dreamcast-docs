// -sgwdata.h-------------------------------------------------------------------
// Defines the configuration extension data for the Sample Gateway.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _SGWDATA_H_
#define _SGWDATA_H_

// Name of cfg extension data blob.
#define SGWBLOBNAME     "SGWData"
#define SGWBLOBNAMEW    L"SGWData"

// -----------------------------------------------------------------------------
// Index of properties within the extension data blob.
//
// NOTE: If you add a property, add it to the end of the array.  The SGWAdmin 
//       code is designed to handle a growing property array with ease.  If you 
//       remove one it would be easier to just make it an unused place holder.
// -----------------------------------------------------------------------------

typedef enum {          
    // PT_BOOLEAN
    IDX_CHECK_IN_BOUND = 0,
    IDX_CHECK_OUT_BOUND, 

    // PT_LONG
    IDX_EDIT_THREADS_IN, 
    IDX_EDIT_THREADS_OUT,
    IDX_EDIT_MSGS_IN,    
    IDX_EDIT_MSGS_OUT,   
    IDX_EDIT_SLEEP_IN,   
    IDX_EDIT_SLEEP_OUT,  
    IDX_EDIT_POLLING_IN, 
    IDX_EDIT_POLLING_OUT,

    // PT_STRING8
    IDX_ADDR_TYPE,       
    IDX_DISP_NAME,       
    IDX_EMAIL_ADDR,      
    IDX_DIR_IN,          
    IDX_DIR_OUT,
    IDX_CONVERTER_IN,
    IDX_CONVERTER_OUT,

    // Total number of properties in Extension Data Blob.
    // Keep this one at the very end of list.
    SGWDATA_PROP_COUNT
} PropIndex;

// -----------------------------------------------------------------------------

#endif // _SGWDATA_H_
