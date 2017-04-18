
/*
================================================================================
    ========================================================================
    ========================================================================

    File:           cdata.h
    Description:    headers for CData and child classes
    Created:        9/3/1997
    Author:         Matthijs Gates
    Mail:           mgates@microsoft.com

    Copyright (C) 1997  Microsoft Corporation.  All Rights Reserved.

    ========================================================================
    ========================================================================
================================================================================
*/

#if !defined(DATA_H)
#define DATA_H

#include "brtest.h"
#include "util.h"

//==============================================================================
//
//  Class:  CData
//
//------------------------------------------------------------------------------
//  Description:        root class for data.
//
//  Public methods:
//
//  Public properties:
//
//  9/3/1997
//  mgates
//
//==============================================================================
class CData
{
    CRITICAL_SECTION    m_crtCDataLock ;    // critical section lock
    INT                 m_iBufferSize ;     // buffer sizes are always in bytes !

    VOID InitCData() ;
    
    // P U B L I C

    public :
    
        CData() ;
        virtual ~CData() ;
    
        virtual BYTE    *GetBuffer() { return m_lpbBuffer ; }
        virtual INT     GetBufferSize() { return m_iBufferSize ; }
        
    // P R O T E C T E D
        
    protected :

        virtual BOOL    CDataSetBuffer(BYTE *lpbBuffer, INT iBufferSize) ;
        VOID    Lock()      { EnterCriticalSection(&m_crtCDataLock) ; }
        VOID    Unlock()    { LeaveCriticalSection(&m_crtCDataLock) ; }

        BYTE *m_lpbBuffer ;
} ;

//==============================================================================
//
//  Class:  CDataCountup
//
//------------------------------------------------------------------------------
//  Description:
//
//  Public methods:
//
//  Public properties:
//
//  9/12/1997
//  mgates
//
//==============================================================================
class CDataCountup : public CData
{
    BOOL    m_fFirst ;
    INT     m_cDword ;
    BOOL    m_fFreeze ;
    
    // P U B L I C -------------------------------------------------------------

    public :
    
        CDataCountup(INT iBufferSize = DEF_DATABUFFERSIZE) ;
        ~CDataCountup() ;
        
        virtual BYTE    *GetBuffer() ;
        BOOL SetBufferSize(INT iBufferSize) ;
        VOID Reset(INT iBaseNumber = 0) ;
        BOOL FreezeCountup(BOOL fFreeze) { m_fFreeze = fFreeze ; return TRUE ; }
        BOOL IsCountupFrozen()  { return m_fFreeze ; }
        
        enum { DEF_DATABUFFERSIZE   = 1024,
               MIN_BUFFERSIZE       = 100,
               MAX_BUFFERSIZE       = 65504     // max UDP is 65507, aligned on
                                                //  DWORD boundary is 65504
             } ;
} ;

//==============================================================================
//
//  Class:  CDataString
//
//------------------------------------------------------------------------------
//  Description:        CData derivative to hold a regular null-terminated
//                      string.
//
//  Public methods:
//                      Set()           sets the content
//                      GetBuffer()     retrieves the null-terminated string
//                      GetBufferSize() returns the length of the string,
//                                        excluding the null-terminator
//
//  Public properties:
//                      - none -
//
//  9/4/1997
//  mgates
//
//==============================================================================
class CDataString : public CData
{
    CString m_strBuffer ;
    
    // P U B L I C

    public :
    
        CDataString() { ; }
        CDataString(CString &strBuffer) : m_strBuffer(strBuffer) { ; }
        CDataString(const char *szBuffer) : m_strBuffer(szBuffer) { ; }
        ~CDataString() ;
        
        BOOL Set(CString &strBuffer) ;
        BOOL Set(const char *szBuffer) ;
        
        BYTE *GetBuffer() { return (BYTE *) m_strBuffer.GetBuffer(0) ; }
        INT GetBufferSize() { return m_strBuffer.GetLength() ; }
} ;

#endif  // DATA_H
