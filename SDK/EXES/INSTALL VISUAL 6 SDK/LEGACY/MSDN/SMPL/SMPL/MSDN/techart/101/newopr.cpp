// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.
//
#include <afxwin.h>
#include <afxcoll.h>
#include "resource.h"

#include "newopr.h"

/////////////////////////////////////////////////////////////////////////////
//
// Global Variables
//
BOOL bAllocDone = FALSE;

// Due to a bug in the /Gx commands the following two objects much be declared
// as near to get multi-instances with the large model.
CObArray NEAR spaceholder;	
CTheApp  NEAR theApp;

/////////////////////////////////////////////////////////////////////////////

// CMainWindow constructor:
// Create the window with the appropriate style, size, menu, etc.
//
CMainWindow::CMainWindow()
{
	LoadAccelTable( "MainAccelTable" );
	Create( NULL, "New Operator Demo App",
		WS_OVERLAPPEDWINDOW, rectDefault, NULL, "MainMenu" );
}

///////////////////////////////////////////////////////////
// OnPaint:
//
void CMainWindow::OnPaint()
{
	TRACE("OnPaint---->\r\n") ;

	CPaintDC dc( this );
	
	if (bAllocDone)
	{

		char s[128] ;
		wsprintf(s, "Total Memory Blocks Allocated is: %d.",spaceholder.GetSize()) ;
		dc.SetTextColor( ::GetSysColor( COLOR_WINDOWTEXT ) );
		dc.TextOut( 10, 10,	s, strlen(s) );			
	}
	else
	{
		CString s = "Perform the DoAlloc command to allocate memory!" ;
		dc.SetTextColor( RGB(128,0,0) );
		dc.TextOut( 10, 10, s, s.GetLength() ) ;
	}

	TRACE("<----OnPaint\r\n") ;
}

///////////////////////////////////////////////////////////
// OnDestroy:
//
void CMainWindow::OnDestroy()
{
	if (bAllocDone)
	{
		// Windows does it for us, but let's do free memory anyway.
			TRACE("Freeing spaceWastes from memory. \r\n") ;
			int limit = spaceholder.GetSize() ;
			for(int i = 0 ; i < limit ; i++ )
			{
				delete spaceholder.GetAt(i) ;
			}
	}
	
	PostQuitMessage(0) ;
}

///////////////////////////////////////////////////////////
// OnAbout:
//
void CMainWindow::OnAbout()
{
	CModalDialog about( "AboutBox", this );
	about.DoModal();
}

////////////////////////////////////////////////////
// OnAlloc:
//
void CMainWindow::OnAlloc()
{
	if (bAllocDone)
	{
		MessageBeep(0) ;
		MessageBox("Memory has already been allocated!","New Operator Demo",
						MB_OK | MB_ICONEXCLAMATION ) ;					
	}
	else
	{
		TRACE("OnAlloc----->\r\n") ;
		
		const maxblocks = 128 ;
		CSpaceWaste *pwaste;

		TRACE("Setting Size. \r\n") ;
		spaceholder.SetSize(maxblocks) ;
		bAllocDone = TRUE ;

		for (int i = 0 ; i < maxblocks ; i++)
		{
			TRY
			{
				pwaste = new CSpaceWaste ;
			}
			CATCH( CMemoryException, theException)
			{
				TRACE("!!!Catching CMemoryException!!! \r\n") ;
				spaceholder.SetSize(i) ;
				break;
			}
			END_CATCH

			spaceholder.SetAt(i,pwaste) ;			
		}
		Invalidate() ;
		UpdateWindow() ;
		
		TRACE("<-----OnAlloc\r\n") ;
		
	}
	
}

// CMainWindow message map:
BEGIN_MESSAGE_MAP( CMainWindow, CFrameWnd )
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_COMMAND( IDM_ABOUT, OnAbout )
	ON_COMMAND( IDM_ALLOC, OnAlloc )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTheApp

// InitInstance:
BOOL CTheApp::InitInstance()
{
	TRACE( "HELLO WORLD\n" );

	m_pMainWnd = new CMainWindow();
	m_pMainWnd->ShowWindow( m_nCmdShow );
	m_pMainWnd->UpdateWindow();

	return TRUE;
}
