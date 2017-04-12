
#if !defined(UTIL_H)
#define UTIL_H

/*
================================================================================
    ========================================================================
    ========================================================================

    File:           util.h
    Description:    
    Created:        9/3/1997
    Author:         Matthijs Gates
    Mail:           mgates@microsoft.com

    Copyright (C) 1997  Microsoft Corporation.  All Rights Reserved.

    ========================================================================
    ========================================================================
================================================================================
*/

#include "brtest.h"
#include <string.h>
#include "util.h"

//==============================================================================
//
//  Class:  CUtil
//
//------------------------------------------------------------------------------
//  Description:
//
//  Public methods:
//
//  Public properties:
//
//  9/4/1997
//  mgates
//
//==============================================================================
class CUtil
{
    // P U B L I C

    public :
    
        static INT BandwidthThrottledSend(CSession   &session,
                                          CData      &data,
                                          DWORD      &cBytesSentToNow,
                                          DWORD      &dwFirstSendTick,
                                          DWORD      &dwLastSendTick,
                                          DWORD      dwBitsPerSec,
                                          HANDLE     hAbortEvent = NULL) ;
        
        static BOOL IsValidIP(char *szIP) { return inet_addr(szIP) != INADDR_NONE ; }
        static BOOL IsValidIP(CString &cstrIP) { return inet_addr(cstrIP) != INADDR_NONE ; }
		static BOOL ChangeIP(CString &cstrIP, long ulIncrement) ;
		static BOOL IncrementIP(CString &cstrIP) { return ChangeIP(cstrIP, 1) ; }
		static BOOL DecrementIP(CString &cstrIP) { return ChangeIP(cstrIP, -1) ; }
		static BOOL ulIPtoCString(u_long ip, CString &cstrIP) ;
        enum { ABORTEVENT = -1 
             } ;
} ;

//==============================================================================
//
//  Class:  CNetworkInterface
//
//------------------------------------------------------------------------------
//  Description:        provides a class for an array of NIC IP addresses for
//                      the host
//
//  Public methods:
//
//  Public properties:
//
//  9/14/1997
//  mgates@microsoft.com
//
//==============================================================================
class CNIC
{
    CString **m_ppNIC ;
    INT        m_cNIC ;
    CString &Get_(INT index) ;
    
    // P U B L I C -------------------------------------------------------------

    public :
    
        CNIC() ;
        ~CNIC() ;
        
        INT Enumerate()    { return m_cNIC ; }
        CString &Get(INT index) ;
        CString &operator[](INT index) ;
} ;

#endif  // UTIL_H
