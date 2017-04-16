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

class CProg4 {
	private:
		static int statCount ;		
		int nCount;
		
		// Use a static member function for callbacks
		static int FAR PASCAL EXPORT 
			EnumObjectsProc( LPSTR lpLogObject, LPSTR lpData) ;

	public:
		// Constructor
		 CProg4() : nCount(0) {} ;
	 // Member function
		 void enumIt(HDC hdc) ;
 };
		
// Static Data Members must be defined
//
int CProg4::statCount = 0;

///////////////////////////////////////////////////////////////////
// Implementation
//
void CProg4::enumIt(HDC hdc)	 
 {	 
	  // Register Callback using the Windows Functions
	 ::EnumObjects(hdc, OBJ_BRUSH, (FARPROC)EnumObjectsProc, NULL) ;	
 }
 
// Callback Handler 
//
int FAR PASCAL EXPORT 
CProg4::EnumObjectsProc( LPSTR lpLogObject, LPSTR lpData)
{
//	nCount++ ; This line would cause an error if not commented.
	statCount++ ;
	MessageBeep(0) ;
	return TRUE ;
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
   		CProg4 cprog4;
			cprog4.enumIt( ::GetDC(GetSafeHwnd()) );
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
