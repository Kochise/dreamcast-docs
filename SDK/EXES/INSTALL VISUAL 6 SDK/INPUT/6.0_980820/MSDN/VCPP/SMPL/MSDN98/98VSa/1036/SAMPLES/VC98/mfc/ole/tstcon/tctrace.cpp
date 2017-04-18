#include "StdAfx.H"
#include "TestCon.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int g_nTraceLevel = TRACELEVEL_NORMAL;

int GetTraceLevel()
{
   return( g_nTraceLevel );
}

void SetTraceLevel( int nLevel )
{
   g_nTraceLevel = nLevel;
}

void __cdecl TCControlTrace( int nLevel, CTestContainer98Item* pItem,
   LPCTSTR pszFormat, ... )
{
   va_list args;
   va_start( args, pszFormat );

   int nBuf;
   TCHAR szBuffer[512];
   CString strItemName;

   if( g_nTraceLevel < nLevel )
   {
	  return;
   }

   strItemName = pItem->GetDisplayName();
   sprintf( szBuffer, "TestCon: %s: ", LPCTSTR( strItemName ) );
   OutputDebugString( szBuffer );

   nBuf = _vstprintf( szBuffer, pszFormat, args );
   ASSERT( nBuf < sizeof( szBuffer ) );

   OutputDebugString( szBuffer );

   va_end( args );
}

void __cdecl TCTrace( int nLevel, LPCTSTR pszFormat, ... )
{
   va_list args;
   va_start( args, pszFormat );

   int nBuf;
   TCHAR szBuffer[512];

   if( g_nTraceLevel < nLevel )
   {
	  return;
   }

   nBuf = _vstprintf( szBuffer, pszFormat, args );
   ASSERT( nBuf < sizeof( szBuffer ) );

   OutputDebugString( _T( "TestCon: " ) );
   OutputDebugString( szBuffer );

   va_end( args );
}
