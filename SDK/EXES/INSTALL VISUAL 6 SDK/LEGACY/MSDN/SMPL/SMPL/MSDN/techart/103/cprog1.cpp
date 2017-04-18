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

#pragma message()
#pragma message("WARNING:---------------------------")
#pragma message("This program will crash when run!!!")
#pragma message("-----------------------------------")
#pragma message()

class CProg1 {
	private:
		int nCount ;
		
		// Do not use non-static functions for callbacks
		int FAR PASCAL EXPORT 
			EnumObjectsProc( LPSTR lpLogObject, LPSTR lpData) ;

	public:
		//Constructor
		 CProg1() : nCount(0) {};
		//Member Function
		 void enumIt(CDC & dc) ;
 };

///////////////////////////////////////////////////////////////////////
// Implementation
//
void CProg1::enumIt(CDC & dc)
 {	 
	  dc.EnumObjects(OBJ_BRUSH, EnumObjectsProc, NULL) ;
 }
 
int FAR PASCAL EXPORT 
CProg1::EnumObjectsProc( LPSTR lpLogObject, LPSTR lpData)
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
			CProg1 cprog1;
			cprog1.enumIt(dc) ;				
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
