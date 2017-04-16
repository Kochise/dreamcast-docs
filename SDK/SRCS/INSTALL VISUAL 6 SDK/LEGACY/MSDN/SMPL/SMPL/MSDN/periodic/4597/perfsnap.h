#ifndef __Perfsnap_h__
#define __Perfsnap_h__

#ifndef _WINPERF_
#include <winperf.h>
#endif

class CPerfTitleDatabase;

class CPerfSnapshot
{
    private:
        
    PPERF_DATA_BLOCK    m_pPerfDataHeader;      // Points to snapshot data
    CPerfTitleDatabase  * m_pCounterTitles;     // The title conversion object

    // Private function to convert the ASCII strings passedto TakeSnapshot()
    // into a suitable form for the RegQueryValue call
    BOOL ConvertSnapshotItemName( PTSTR pszIn, PTSTR pszOut, DWORD nSize );

    public:

    CPerfSnapshot( CPerfTitleDatabase * pCounterTitles );
    
    ~CPerfSnapshot( void );

    BOOL TakeSnapshot( PTSTR pszSnapshotItems );

    void DisposeSnapshot( void );

    DWORD GetNumObjectTypes( void );    // # of objects the snapshot includes

    BOOL GetSystemName( PTSTR pszSystemName, DWORD nSize );
    
    PVOID GetPostHeaderPointer( void ); // Pointer to data following the header
};

#endif
