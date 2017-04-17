/*++

Copyright (c) 1992-1998 Microsoft Corporation

Module Name: security.h

Purpose: Top-level include file for security aware components.

--*/

// This file will go out and pull in all the header files that you need,
// based on defines that you issue.  The following macros are used.

// NOTE:  Update this section if you add new files:
//
// SECURITY_KERNEL      Use the kernel interface, not the usermode
// SECURITY_PACKAGE     Include defines necessary for security packages
// SECURITY_KERBEROS    Include everything needed to talk to the kerberos pkg.
// SECURITY_NTLM        Include everything to talk to ntlm package.
// SECURITY_OBJECTS     Include all Security Admin Object definitions.

//
// Each of the files included here are surrounded by guards, so you don't
// need to worry about including this file multiple times with different
// flags defined
//

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef SSPI_PROXY_CLASS
#define SSPI_PROXY_CLASS    PROXY_CLASS
#endif

#include <windows.h>

#include <sspi.h>

#include <secext.h>

//
// Include the error codes:
//

#include <issperr.h>


// Include security package headers:

#ifdef SECURITY_PACKAGE

#include <secpkg.h>

#endif  // SECURITY_PACKAGE


#ifdef SECURITY_NTLM

// #include <ntlmsp.h>

#endif // SECURITY_NTLM


// Include security object definitions


#ifdef __cplusplus
}
#endif

