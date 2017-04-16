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
///////////////////////////////////////////////////////////////////
//	Owner -  Demonstrates that object memory can be owned by either				
//				an application or a DLL.  In fact memory ownership can 
//				swap back and forth between the two.
//
#include <afxwin.h>
#include "ownerdll.h"		// DLL include file

/////////////////////////////////////////////////////////////////
//	Prototypes
//
void somefunc();

////////////////////////////////////////////////////////////////
//	Declare objects in DLL.
// Since owner is compiled large model, the object aFoo
//	will be placed in its own far data segment.
//
CFooInDLL aFoo ;

///////////////////////////////////////////////////////////////
// The yourString and myString functions have the exact
// same code.  The only difference is that yourString is
// an inline function.  This means that the memory associated
//	with aFoo.aString will be owned by the application after
// a call to yourString, but will be owned by the DLL after a
// call to myString.
//
// NOTE: The debugging versions of the MFC libraries track all
// memory objects that have be allocated.  If a MFC program tries
// to free an object that it has not allocated, an assertion in
// memory.cpp will fail.  The line aFoo.yourString() will first
// execute a delete aFoo.aString.  Since the memory for aString 
// was allocated by the DLL, the MFC libraries have no record of
// it being allocated and will fail the assertion.  
//
// This code will run fine with the 'retail' build.  Use CodeView 
// and HeapWalker to watch the object change ownership.
//
void somefunc()
{
	aFoo.yourString() ;
	aFoo.myString() ;
	aFoo.yourString() ;
}

/////////////////////////////////////////////////////////////
// Yes, you guessed it.  This code started life as hello.cpp
//
class CHelloWindow : public CFrameWnd
{ 
public:
	CHelloWindow() 
		{ Create(NULL, "Memory OwnerShip Application ", 
					WS_OVERLAPPEDWINDOW, rectDefault);
		}
};

class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

BOOL CHelloApp::InitInstance()
{

	somefunc() ;
	
	m_pMainWnd = new CHelloWindow();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

CHelloApp HelloApp;  
