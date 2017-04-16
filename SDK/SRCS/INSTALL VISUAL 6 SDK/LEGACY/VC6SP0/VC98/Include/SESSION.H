
#if !defined(SESSION_H)
#define SESSION_H

/*
================================================================================
    ========================================================================
    ========================================================================

    File:           csession.h
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
#include "util.h"

//==============================================================================
//
//  Class:  CSession
//
//------------------------------------------------------------------------------
//  Description:        abstract root class for Sessions (Tunnels, Multicasts, 
//                      etc...); provides a set of primitive methods that
//                      sessions must implement
//
//  Public methods:
//                      Send()      send a CData object over the session
//
//  Public properties:
//                      - none -
//
//  9/3/1997
//  mgates
//
//==============================================================================
class CSession
{
    WSADATA m_wsaData ;
    
    enum { WINSOCK_MAJOR_VER = 2, WINSOCK_MINOR_VER = 0 } ;
    
    // P U B L I C

    public :
    
        CSession() ;
        virtual ~CSession() ;
    
        virtual INT Send(CData &data) = 0 ;

    // P R O T E C T E D

    protected :

} ;

//==============================================================================
//
//  Class:  CMulticast
//
//------------------------------------------------------------------------------
//  Description:
//
//  Public methods:
//
//  Public properties:
//
//  9/14/1997
//  mgates@microsoft.com
//
//==============================================================================
class CMulticast : public CSession
{
    CString     m_strIP ;
    CString     m_strNIC ;
    USHORT      m_usPort ;
    SOCKET      m_socket ;
    SOCKADDR_IN m_destinationAddr ;
    SOCKADDR_IN m_thisAddr ;
    USHORT      m_usTTL ;
    
    enum { DEF_TTL = 10 
         } ;
    
    // P U B L I C -------------------------------------------------------------

    public :
    
        CMulticast() ;
        virtual ~CMulticast() ;
        
        BOOL SetIP(CString &strIP) ;
        BOOL SetIP(char *szIP) ;
        
        BOOL SetPort(USHORT usPort)     { m_usPort = usPort ; return TRUE ; }
        
        BOOL SetNIC(CString &strNIC) ;
        BOOL SetNIC(char *szNIC) ;
        
        BOOL SetTTL(USHORT usTTL) { m_usTTL = usTTL ; return TRUE ; }
        USHORT GetTTL() { return m_usTTL ; }
        
        BOOL Create() ;
        INT  Send(CData &data) ;
        
        CString &GetIP()    { return m_strIP ; }
        USHORT      GetPort()   { return m_usPort ; }
        CString &GetNIC()   { return m_strNIC ; }
} ;

#endif  // SESSION_H
