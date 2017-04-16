//====================================================
// File: SHOWTITL.CPP
// Author: Matt Pietrek
// From: Microsoft Systems Journal
//       "Under the Hood", March 1996
// To Build: CL [arguments] SHOWTITL.CPP CTITLEDB.CPP
//====================================================
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#pragma hdrstop
#include "ctitledb.h"

int main()
{
    CPerfTitleDatabase counterTitles( PERF_TITLE_COUNTER );
    CPerfTitleDatabase explainTitles( PERF_TITLE_EXPLAIN );
    unsigned i;
    PTSTR psz;

    // Display the counter title strings
    for ( i = 0; i < counterTitles.GetLastTitleIndex(); i++ )
    {
        psz = counterTitles.GetTitleStringFromIndex( i );
        if ( psz )
            _tprintf( TEXT("%u %s\n"), i, psz );
    }

    // Display the "Explain" (help) title strings
    for ( i = 0; i < explainTitles.GetLastTitleIndex(); i++ )
    {
        psz = explainTitles.GetTitleStringFromIndex( i );
        if ( psz )
            _tprintf( TEXT("%u %s\n"), i, psz );
    }
    
    return 0;
}
