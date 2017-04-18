const TRACELEVEL_NONE = 0;
const TRACELEVEL_NORMAL = 1;
const TRACELEVEL_VERBOSE = 2;

class CTestContainer98Item;

int GetTraceLevel();
void SetTraceLevel( int nLevel );
void __cdecl TCTrace( int nLevel, LPCTSTR pszFormat, ... );
void __cdecl TCControlTrace( int nLevel, CTestContainer98Item* pItem,
   LPCTSTR pszFormat, ... );
