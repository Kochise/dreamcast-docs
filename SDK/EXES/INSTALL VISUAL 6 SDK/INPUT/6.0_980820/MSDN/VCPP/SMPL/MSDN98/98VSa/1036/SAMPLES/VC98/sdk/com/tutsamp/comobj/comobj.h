/*+==========================================================================
  File:      COMOBJ.H

  Summary:   Include file for the COMOBJ.DLL dynamic link library that
             provides access to the services of the COMOBJ DLL.  This
             include file is meant to serve double duty as providing
             general set of macros that (1) when included in a COMOBJ
             implementation file wherein it provides a STDENTRY macro for
             the definition of exported functions and (2) when included in
             an app that uses these function calls it provides a STDENTRY
             macro for the declaration of imported functions.  The default
             behavior is to serve consumer apps that import the functions
             in the providing DLL.  Prior to the #include of this COMOBJ.H
             if _DLLEXPORT_ is #defined, the STDENTRY, STDENTRY_ and
             DLLENTRY macro expansion bahavior is directed to serve the
             COMOBJ itself in defining the functions as exported. If
             _DLLEXPORT_ is not defined and _LOCALCALLS_ is defined before
             the #include then the STDENTRY macro reduces to externs for
             support of local calls within the modules of the DLL.

             This .H file is written to be #included in either C or C++
             programs.

             For a comprehensive tutorial code tour of COMOBJ's
             contents and offerings see the tutorial COMOBJ.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the COMOBJ source code.

  Classes:   none

  Functions: none

  Origin:    10-3-97: atrent - Editor-inheritance from DLLSKEL.H in
               the DLLSKEL Tutorial Code Sample. [Revised]

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

#if !defined(COMOBJ_H)
#define COMOBJ_H

#if !defined(RC_INCLUDE)

#if !defined(_DLLEXPORT_)

// If _DLLEXPORT_ is not defined then the default is to import.
#if defined(__cplusplus)

#if defined(_LOCALCALLS_)
#define DLLENTRY extern "C"
#else
#define DLLENTRY extern "C" __declspec(dllimport)
#endif

#else   // __cplusplus

#if defined(_LOCALCALLS_)
#define DLLENTRY extern
#else
#define DLLENTRY extern __declspec(dllimport)
#endif

#endif  // __cplusplus

#define STDENTRY DLLENTRY HRESULT WINAPI
#define STDENTRY_(type) DLLENTRY type WINAPI

// Here is the list of service APIs offered by the DLL (using the
// appropriate entry API declaration macros just #defined above).

STDENTRY_(BOOL) ComObjInitMsgLog(
                  CMsgLog* pMsgLog);

STDENTRY_(BOOL) ComObjAboutBox (HWND);

STDENTRY CreateCar(
           IUnknown* pUnkOuter,
           REFIID riid,
           PPVOID ppv);

STDENTRY CreateUtilityCar(
           IUnknown* pUnkOuter,
           REFIID riid,
           PPVOID ppv);

STDENTRY CreateCruiseCar(
           IUnknown* pUnkOuter,
           REFIID riid,
           PPVOID ppv);

#else  // _DLLEXPORT_

// Else if _DLLEXPORT_ is defined then we've been told to export.
#if defined(__cplusplus)

#if defined(_LOCALCALLS_)
#define DLLENTRY extern "C"
#else
#define DLLENTRY extern "C" __declspec(dllexport)
#endif

#else   // __cplusplus

#if defined(_LOCALCALLS_)
#define DLLENTRY
#else
#define DLLENTRY __declspec(dllexport)
#endif

#endif  // __cplusplus

#define STDENTRY DLLENTRY HRESULT WINAPI
#define STDENTRY_(type) DLLENTRY type WINAPI

#endif // _DLLEXPORT_

#endif // RC_INCLUDE

#endif // COMOBJ_H
