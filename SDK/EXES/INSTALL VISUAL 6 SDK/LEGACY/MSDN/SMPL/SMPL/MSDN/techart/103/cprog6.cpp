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

class CProg6 {
	private:
		int nCount ;
		
		// Use a Static member function for callbacks
		static int FAR PASCAL EXPORT 
			EnumObjectsProc( LPSTR lpLogObject, LPSTR lpData) ;
		
		// Use a non-static member function as a helper
		int EnumObjectsHelper( LPSTR lpLogObject) ;
		
	public:		
		 CProg6() :nCount(0) {};
		 void enumIt(CDC & dc) ;
 };

//////////////////////////////////////////////////////////////////////////
// Implementation
//
 
void CProg6::enumIt(CDC & dc)
 {	 
	  dc.EnumObjects(OBJ_BRUSH, EnumObjectsProc, (LPSTR)this) ;
 }
 
// Callback Handler
//
int FAR PASCAL EXPORT 
CProg6::EnumObjectsProc( LPSTR lpLogObject, LPSTR lpData)
{
	CProg6 * psuedoThis = (CProg6 *) lpData ;
	
	if (psuedoThis)
		psuedoThis->EnumObjectsHelper(lpLogObject) ;
	return TRUE ;
}

// Callback Helper Function
int CProg6::EnumObjectsHelper( LPSTR lpLogObject)
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
			CProg6 cprog6;
			cprog6.enumIt(dc) ;				
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
