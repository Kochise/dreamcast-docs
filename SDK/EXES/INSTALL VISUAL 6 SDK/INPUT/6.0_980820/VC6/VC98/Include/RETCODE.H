// --retcode.h------------------------------------------------------------------
//
// Copyright (c) Microsoft Corp. 1986-1996. All Rights Reserved.
//
//  Header file for return codes and exit codes.
// 
// -----------------------------------------------------------------------------
#if !defined(_RETCODE_H)
#define _RETCODE_H

//$--_Rc-----------------------------------------------------------------------
//  Available return codes.
// ----------------------------------------------------------------------------
typedef enum _rc {
    RC_SUCCESS = 0,   
    RC_ERROR,               // general error
    RC_PROTOCOL,            // protocol error 
    RC_SYNTAX,              // syntax error
    RC_EOF,                 // end of file
    RC_IMPLEMENTATION,      // not implemented yet
    RC_SOFTWARE,            // error in software
    RC_CONFIG,              // configuration error
    RC_MEMORY,              // memory allocation error 
    RC_CONTENTION,          // contention error
    RC_NOTFOUND,            // not found
    RC_DISKSPACE,           // out of disk space
    RC_SHUTDOWN,            // service shutdown
    RC_EXPIRED,             // expired
    RC_TIMEOUT,             // timeout
    RC_INVALID_PARAMETER,   // invalid parameter
    RC_LAST                 // all errors are less than this
} RC;

//$--_Ec-----------------------------------------------------------------------
//  Available exit codes.
// ----------------------------------------------------------------------------
typedef enum _ec {
    EC_SUCCESS = 0,   
    EC_ERROR,           // general error
    EC_LAST             // all errors are less than this
} EC;

// ----------------------------------------------------------------------------
//  Macros.
// ----------------------------------------------------------------------------

#define RC_SUCCEEDED(x) \
    ((x) == RC_SUCCESS)

#define RC_FAILED(x) \
    ((x) != RC_SUCCESS)

#define EC_SUCCEEDED(x) \
    ((x) == EC_SUCCESS)

#define EC_FAILED(x) \
    ((x) != EC_SUCCESS)

#endif
