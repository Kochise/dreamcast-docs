// --convcwrp.h-----------------------------------------------------------------
// 
//  C callable code that wraps the conversion engine class.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#if !defined(_CONVCWRP_H)
#define _CONVCWRP_H

#ifdef __cplusplus
extern "C" {
#endif

//$--HrConvInitGlobals-------------------------------------------------
//
// DESCRIPTION: Called once by the gateway to initalize common data areas.
//
// INPUT:   none
//
// RETURNS: HRESULT --  NOERROR if successfull,
//                      E_NOTENOUGHMEMORY if memory problems
//
//---------------------------------------------------------------------
HRESULT HrConvInitGlobals();

//$--ConvUninitGlobals-------------------------------------------------
//
// DESCRIPTION: Called once by the gateway to de-initalize common data areas.
//
// INPUT:   none
//
// RETURNS: VOID
//
//---------------------------------------------------------------------
VOID ConvUninitGlobals();

//$--HrConvInitInstance-----------------------------------------------
//
//  DESCRIPTION: Called to create a new instance of the conversion engine.  Each
//  instance of the conversion engine is single-threaded.  Multiple
//  instances can be used in separate threads.
//
//  INPUT:   hEventSource   --  event source handle
//
//  OUTPUT:  ppvConvInst --  conversion engine instance
//
//  RETURNS:    HRESULT --  NOERROR if no error,
//                          E_INVALIDARG if bad input,
//                          E_FAIL if failure
//
//---------------------------------------------------------------------
HRESULT HrConvInitInstance(      // RETURNS: HRESULT
    IN HANDLE hEventSource,         // filled in with instance handle.
    OUT PVOID * ppvConvInst);       // new conversion engine instance

//$--HrConvUninitInstance----------------------------------------------
//
// DESCRIPTION: Called to dispose of a previously allocated conversion engine.
//
// INPUT:   pvConvInst  --  conversion engine instance to free.
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input
//                      E_FAIL otherwise.
//
//---------------------------------------------------------------------
HRESULT HrConvUninitInstance(     // RETURNS: HRESULT
    IN PVOID pvConvInst);                    // handle to instance to free.

//$--HrConvConvert----------------------------------------------------
//
// DESCRIPTION: called to initiate a conversion.
//
// INPUT:   pvConvInst  --  conversion engine instance
//          pEnv    --  conversion environment
//          pszContentClass --  class of source
//          pContentIn  --  source to be converted
//          pContentOut --  converted object
// 
// OUTPUT:  
//          pcrResult   --  result
//
// RETURNS: HRESULT --  NOERROR if no error,
//                      E_INVALIDARG if bad input,
//                      E_FAIL otherwise.
//
//---------------------------------------------------------------------
HRESULT HrConvConvert(           // RETURNS: HRESULT
    IN PVOID pvConvInst,            // handle to instance of engine.
    IN PEDKCNVENV pEnv,             // environment of the convrsion
    IN LPCWSTR pszContentClass,     // class of source to be converted.
    IN PVOID pContentIn,            // source to be converted.
    IN PVOID pContentOut,           // converted object
    OUT EDKCNVRES *pcrResult);      // result.

#ifdef __cplusplus
}
#endif

#endif
