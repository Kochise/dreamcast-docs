// --ipmdefs.h-----------------------------------------------------------------
//
// Common definitions for the IPM Inbound and Outbound conversion
// DLLs.
//
// Copyright (C) Microsoft Corp., 1986-1996.  All rights reserved.
//
// ----------------------------------------------------------------------------

#ifndef _IPMCDEFS_H
#define _IPMCDEFS_H

#ifdef __cplusplus
extern "C" {
#endif

// Constants used for TNEFed messages:

// associated TNEFed file name
LPCSTR     szTnefFileName  = "MAPIMAIL.DAT";

// TNEF "unique" key
const WORD wTnefKey        = 0x01AF;

#ifdef __cplusplus
}
#endif

#endif
