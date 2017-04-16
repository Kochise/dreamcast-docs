// ErrCpp.h---------------------------------------------------------------------
// Defines a helper class for mapi errors.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _ERRCPP_H_
#define _ERRCPP_H_

#include "EdkUtCpp.H"

// -----------------------------------------------------------------------------
// This class is intended as a replacement for the HRESULT type defined by MAPI.
// It has two advantages over MAPI's version.
//   1) You can report the error code as a readable string using the Msg() 
//      member function.
//   2) When in debug mode you can view this object and see the return code
//      as a readable string by viewing the contents of the m_sMsg member object.
//
// You can use this exactly like you use HRESULT.  In other words you can assign
// an HRESULT return value directly to it.  You can test it using FAILED.  You
// can assign it back to a type HRESULT or return it from a function whose return
// type is HRESULT.  You can even assign it to a const char* or pass it to a 
// function that takes a const char* and you will get the readable string version
// of the HRESULT.
// -----------------------------------------------------------------------------

class CHRESULT
{
public:
    // CONSTRUCTOR: defaults to NOERROR or uses the value you pass in.
    CHRESULT( HRESULT hr = NOERROR)
    {
        m_hr = hr;
        #if DEBUG
            m_sMsg = m_idlMAPIErr.Find( m_hr);
        #endif
    }
    
    // Returns TRUE if the HRESULT failed.
    BOOL bFailed() {return( FAILED( m_hr));}

    // Returns the defined constant for the error as a string constant. Usage example:
    //   CHRESULT hr = MAPI_E_NOT_FOUND;
    //   char chBuf[500];
    //   sprintf( chBuf, "Error: %s occurred", hr.Msg());
    const LPSTR Msg()
    {
        #if DEBUG
            return( m_sMsg.GetBuffer(0));
        #else
            return( m_idlMAPIErr.Find( m_hr));
        #endif
    }
    
    // Returns the defined constant for the error as a string. Usage example:
    //   CHRESULT hr = MAPI_E_NOT_FOUND;
    //   const char* pErrMsg = hr;    // returns "MAPI_E_NOT_FOUND".
    operator LPSTR()                {return( Msg());}                   

    // Returns the HRESULT. Usage example:
    //   CHRESULT hr = MAPI_E_NOT_FOUND;
    //   HRESULT mapiHR = hr;
    operator HRESULT()              {return( m_hr);}                    

    // Assigns an HRESULT to CHRESULT. Usage example:
    //   CHRESULT hr;       // Defaults to SUCCESS_SUCCESS
    //   hr = imapiProp->GetProps( ...
    const CHRESULT& operator=( HRESULT hr)
    {
        m_hr = hr;
        #if DEBUG
            m_sMsg = m_idlMAPIErr.Find( m_hr);
        #endif
        return( *this);
    }

protected:
    static CIDList  m_idlMAPIErr;   // Static ID list of MAPI Errors.
    HRESULT         m_hr;           // Contains the actual HRESULT.
    
    #if DEBUG
    CString         m_sMsg;         // In the dubugger look at this to see the 
    #endif                          // current HRESULT as a readable string.
};

// -----------------------------------------------------------------------------
#ifdef _GLOBAL_OBJECTS_
#pragma message("Declaration of global objects for: " __FILE__)

#include "ErrCppD.h"
CIDList CHRESULT::m_idlMAPIErr( MAPIErrors, ARRAY_CNT( MAPIErrors));

#endif //_GLOBAL_OBJECTS_
// -----------------------------------------------------------------------------

#endif // _ERRCPP_H_
