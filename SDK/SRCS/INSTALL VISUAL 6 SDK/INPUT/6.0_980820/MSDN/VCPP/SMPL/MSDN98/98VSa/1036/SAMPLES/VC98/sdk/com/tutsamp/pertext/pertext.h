/*+==========================================================================
  File:      PERTEXT.H

  Summary:   Main include file for the PERTEXT.DLL dynamic link library.
             Intended primarily for external users of this DLL who exploit
             it via static linkage to the DllRegisterServer and
             DllUnregisterServer exported service calls.

             For a comprehensive tutorial code tour of PERTEXT's contents
             and offerings see the tutorial PERTEXT.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the PERTEXT source code.

  Classes:   none.

  Functions: DllRegisterServer, DllUnregisterServer.

  Origin:    5-20-97: atrent - Editor-inheritance from STOSERVE.H in
               the STOSERVE Tutorial Code Sample.

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/

#if !defined(PERTEXT_H)
#define PERTEXT_H

#if !defined(RC_INCLUDE)

#if !defined(_DLLEXPORT_)

// If _DLLEXPORT_ is NOT defined then the default is to import.
#if defined(__cplusplus)
#define DLLENTRY extern "C" __declspec(dllimport)
#else
#define DLLENTRY extern __declspec(dllimport)
#endif
#define STDENTRY DLLENTRY HRESULT WINAPI
#define STDENTRY_(type) DLLENTRY type WINAPI

// Here is the list of server APIs offered by the DLL (using the
// appropriate entry API declaration macros just #defined above).

STDENTRY DllRegisterServer(void);

STDENTRY DllUnregisterServer(void);

#else  // _DLLEXPORT_

// Else if _DLLEXPORT_ is indeed defined then we've been told to export.
#if defined(__cplusplus)
#define DLLENTRY extern "C" __declspec(dllexport)
#else
#define DLLENTRY __declspec(dllexport)
#endif
#define STDENTRY DLLENTRY HRESULT WINAPI
#define STDENTRY_(type) DLLENTRY type WINAPI

#endif // _DLLEXPORT_

#endif // RC_INCLUDE

#endif // PERTEXT_H
