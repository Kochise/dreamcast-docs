// -smbdata.h-------------------------------------------------------------------
// Defines the configuration extension data for the Sample Mailbox Agent.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _SMBDATA_H_
#define _SMBDATA_H_

// Name of cfg extension data blob.
#define SMBBLOBNAME     "SMBData"
#define SMBBLOBNAMEW    L"SMBData"

// -----------------------------------------------------------------------------
// Index of properties within the extension data blob.
//
// NOTE: If you add a property, add it to the end of the array.  The SMBAdmin 
//       code is designed to handle a growing property array with ease.  If you 
//       remove one it would be easier to just make it an unused place holder.
// -----------------------------------------------------------------------------

typedef enum {          
    // PT_BOOLEAN
    IDX_PUBLIC_TOPIC_FOLDER = 0,

    // PT_LONG
    IDX_POLL_INBOX_MSEC, 
    IDX_ACL_RIGHTS,

    // PT_STRING8
    IDX_TOPIC_ROOT_FOLDER_NAME,       
    IDX_TOPIC_ROOT_FOLDER_COMMENT,       

    // Total number of properties in Extension Data Blob.
    // Keep this one at the very end of list.
    SMBDATA_PROP_COUNT
} PropIndex;

// -----------------------------------------------------------------------------

#endif // _SMBDATA_H_
