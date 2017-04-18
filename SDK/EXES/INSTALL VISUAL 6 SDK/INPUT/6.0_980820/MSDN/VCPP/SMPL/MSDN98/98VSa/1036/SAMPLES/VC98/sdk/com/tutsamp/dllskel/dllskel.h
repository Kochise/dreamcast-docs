/*+==========================================================================
  File:      DLLSKEL.H

  Summary:   Include file for the DLLSKEL.DLL dynamic link library.  This
             include file is meant to serve double duty as providing
             general set of macros that (1) when included in a DLLSKEL
             implementation file wherein it provides a DLLENTRY
             designation for the definition of exported functions and (2)
             when included in an app that uses these function calls it
             provides a DLLENTRY designation for the declaration of
             imported functions.  The default behavior is to serve
             consumer apps that import the functions in the providing
             DLLSKEL.DLL.  Prior to the #include of this DLLSKEL.H if
             _DLLEXPORT_ is #defined, the bahavior is to serve the DLLSKEL
             itself in defining the functions as exported.

             For a comprehensive tutorial code tour of DLLSKEL's contents
             and offerings see the tutorial DLLSKEL.HTM file. For more
             specific technical details on the internal workings see the
             comments dispersed throughout the DLLSKEL source code.

  Classes:   none

  Functions: none

  Origin:    12-9-96: atrent - Revised.

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

#if !defined(DLLSKEL_H)
#define DLLSKEL_H

#if !defined(RC_INCLUDE)

#if !defined(_DLLEXPORT_)

// If _DLLEXPORT_ is not defined then the default is to import.
#if defined(__cplusplus)
#define DLLENTRY extern "C" __declspec(dllimport)
#else
#define DLLENTRY extern __declspec(dllimport)
#endif
#define STDENTRY DLLENTRY HRESULT WINAPI
#define STDENTRY_(type) DLLENTRY type WINAPI

// Here is the list of service APIs offered by the DLL (using the
// appropriate entry API declaration macros just #defined above).
STDENTRY_(BOOL) DllHelloBox (HWND);
STDENTRY_(BOOL) DllAboutBox (HWND);

#else  // _DLLEXPORT_

// Else if _DLLEXPORT_ is defined then we've been told to export.
#if defined(__cplusplus)
#define DLLENTRY extern "C" __declspec(dllexport)
#else
#define DLLENTRY __declspec(dllexport)
#endif
#define STDENTRY DLLENTRY HRESULT WINAPI
#define STDENTRY_(type) DLLENTRY type WINAPI

#endif // _DLLEXPORT_

#endif // RC_INCLUDE

#endif // DLLSKEL_H
