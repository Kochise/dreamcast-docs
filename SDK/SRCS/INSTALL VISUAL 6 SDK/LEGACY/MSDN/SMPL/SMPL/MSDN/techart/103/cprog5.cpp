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

class CProg5 {
	private:
		int nCount ;

		// Use a static variable to pass an object pointer
		static CProg5 * psuedoThis ;

		// Use a static function for callbacks
		static int FAR PASCAL EXPORT 
			EnumObjectsProc( LPSTR lpLogObject, LPSTR lpData) ;
		
		// Use a non-static function as a helper for the callback
		int EnumObjectsHelper( LPSTR lpLogObject, LPSTR lpData) ;
		
	public:		
		 CProg5() :nCount(0) {};
		 void enumIt(CDC & dc) ;
 };

CProg5 * CProg5::psuedoThis = NULL ;

void CProg5::enumIt(CDC & dc)
 {	 
     psuedoThis = this ;
	  dc.EnumObjects(OBJ_BRUSH, EnumObjectsProc, NULL) ;
	  psuedoThis = NULL ;
 }
 
int FAR PASCAL EXPORT 
CProg5::EnumObjectsProc( LPSTR lpLogObject, LPSTR lpData)
{
	if ( psuedoThis != (CProg5 *)NULL )
		return psuedoThis->EnumObjectsHelper(lpLogObject, lpData) ;
	else
		return 0 ;
}

int CProg5::EnumObjectsHelper( LPSTR lpLogObject, LPSTR lpData)
{
	nCount++ ;
	MessageBeep(0) ;
	return 1 ;
}


//////////////////////////////////////////////////////
//
// helloapp.cpp : Minimal MFC Windows app.
//
// Define a window class derived from CFrameWnd
class CHelloWindow : public CFrameWnd
{ 
public:
	CHelloWindow() 
		{ Create(NULL, "Hello World!", WS_OVERLAPPEDWINDOW, rectDefault);
      	CClientDC dc(this) ;
			CProg5 cprog5;
			cprog5.enumIt(dc) ;				
		}
};

// Define an application class derived from CWinApp
class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

// Construct the CHelloApp's m_pMainWnd data member
BOOL CHelloApp::InitInstance()
{
	m_pMainWnd = new CHelloWindow();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

CHelloApp HelloApp;  // HelloApp's constructor initializes and runs the app
