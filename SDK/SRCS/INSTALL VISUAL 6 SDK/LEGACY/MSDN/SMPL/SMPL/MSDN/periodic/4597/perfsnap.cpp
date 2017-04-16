//============================================================================
// File: PERFSNAP.CPP
// Author: Matt Pietrek
// From: Microsoft Systems Journal, "Under the Hood", March 1996
//============================================================================
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <winperf.h>
#include <stdlib.h>
#include <tchar.h>
#pragma hdrstop
#include "ctitledb.h"
#include "perfsnap.h"
#include "makeptr.h"

CPerfSnapshot::CPerfSnapshot(
    CPerfTitleDatabase * pCounterTitles )
{
    m_pPerfDataHeader = 0;
    m_pCounterTitles = pCounterTitles;
}

CPerfSnapshot::~CPerfSnapshot( void )
{
    DisposeSnapshot();
}

BOOL
CPerfSnapshot::TakeSnapshot( PTSTR pszSnapshotItems )
{
    DisposeSnapshot();  // Clear out any current snapshot

    // Convert the input string (e.g., "Process") into the form required
    // by the HKEY_PERFORMANCE_DATA key (e.g., "232")

    TCHAR szConvertedItemNames[ 256 ];
    if ( !ConvertSnapshotItemName( pszSnapshotItems, szConvertedItemNames,
                                    sizeof(szConvertedItemNames) ) )
        return FALSE;

    DWORD cbPerfInfo = 0, cbAllocSize = 0;
    LONG retValue;

    m_pPerfDataHeader = 0;
        
    while ( 1 ) // Loop until we get the data, or we fail unexpectedly
    {
        retValue = RegQueryValueEx( HKEY_PERFORMANCE_DATA,
                                    szConvertedItemNames, 0, 0,
                                    (PBYTE)m_pPerfDataHeader, &cbPerfInfo );

        if ( retValue == ERROR_SUCCESS )    // We apparently got the snapshot
        {
            // Verify that the signature is a unicode "PERF"
            if ( memcmp( m_pPerfDataHeader->Signature, L"PERF", 8 ) )
                break;

            return TRUE;
        }
        else if ( retValue != ERROR_MORE_DATA ) // Anything other failure
            break;                              // code means something
                                                // bad happened, so bail out.

        // If we get here, our buffer wasn't big enough.  Delete it and
        // try again with a bigger buffer.
        delete []m_pPerfDataHeader;
        
        // The new buffer size will be 4096 bytes bigger than the larger
        // of: 1) The previous allocation size, or 2) The size that the
        // RegQueryValueEx call said was necessary.
        if ( cbPerfInfo > cbAllocSize )
            cbAllocSize = cbPerfInfo + 4096;
        else
            cbAllocSize += 4096;

        // Allocate a new, larger buffer in preparation to try again.
        m_pPerfDataHeader = (PPERF_DATA_BLOCK) new BYTE[ cbAllocSize ];
        if ( !m_pPerfDataHeader )
            break;

        cbPerfInfo = cbAllocSize;
    }

    // If we get here, the RegQueryValueEx failed unexpectedly.
    delete []m_pPerfDataHeader;
    m_pPerfDataHeader = 0;

    return FALSE;
}

void
CPerfSnapshot::DisposeSnapshot( void )
{
    delete m_pPerfDataHeader;
    m_pPerfDataHeader = 0;
}

DWORD
CPerfSnapshot::GetNumObjectTypes( void )
{
    return m_pPerfDataHeader ? m_pPerfDataHeader->NumObjectTypes: 0;
}

BOOL
CPerfSnapshot::GetSystemName( PTSTR pszSystemName, DWORD nSize )
{
    if ( !m_pPerfDataHeader )   // If no snapshot data, bail out.
        return FALSE;

    // Make sure the input buffer size is big enough
    if ( nSize < m_pPerfDataHeader->SystemNameLength )
        return FALSE;

    // Make a unicode string point to the system name string
    // that's stored in the PERF_DATA_BLOCK
    LPWSTR lpwszName = MakePtr( LPWSTR, m_pPerfDataHeader,
                                m_pPerfDataHeader->SystemNameOffset );

    #ifdef UNICODE  // Copy the PERF_DATA_BLOCK string to the input buffer
    lstrcpy( pszSystemName, lpwszName );
    #else
    wcstombs( pszSystemName, lpwszName, nSize );
    #endif
        
    return TRUE;
}

PVOID
CPerfSnapshot::GetPostHeaderPointer( void )
{
    // Returns a header to the first byte following the PERF_DATA_BLOCK
    // (including the variable length system name string at the end)
    return m_pPerfDataHeader ?
            MakePtr(PVOID, m_pPerfDataHeader,m_pPerfDataHeader->HeaderLength)
            : 0;
}

BOOL
CPerfSnapshot::ConvertSnapshotItemName( PTSTR pszIn,
                                        PTSTR pszOut, DWORD nSize )
{
    if ( IsBadStringPtr( pszIn, 0xFFFFFFFF ) )
        return FALSE;

    PTSTR pszCopy = _tcsdup( pszIn );   // Need a copy because _tcstok will
                                        // modify the string it processes
    PTSTR pszCopy2 = pszCopy, pszToken;
    PTSTR pszOut2 = pszOut;

    // For each token (' ' delimited) from the input string, see if it
    // corresponds to a counter title.  If so, emit the title index as
    // in ASCII form to the output string.  If the input token isn't a
    // counter title, pass it through unmodified to the output string.
    // This allows things like "Global" and "Costly" to go through unscathed.

    while ( pszToken = _tcstok(pszCopy2, TEXT(" ")) )   // _tcstok == strtok
    {
        DWORD objectID = m_pCounterTitles->GetIndexFromTitleString(pszToken);

        // Needs to check output string len!
        if ( objectID )
            pszOut2 += wsprintf( pszOut2, TEXT("%u "), objectID );
        else
            pszOut2 += wsprintf( pszOut2, TEXT("%s "), pszToken );
        
        pszCopy2 = 0;   // Set to 0 for 2nd and later passes through the loop
    }
    
    free( pszCopy );
    return TRUE;
}
