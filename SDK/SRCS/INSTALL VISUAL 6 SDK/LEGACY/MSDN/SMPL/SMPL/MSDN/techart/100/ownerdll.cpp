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
///////////////////////////////////////////////////////////////////////////
// OwnerDLL - Memory Ownership Demonstration DLL 
//
#include <afxwin.h>
#include "ownerdll.h"

extern "C" int FAR PASCAL _WEP(int nExitType);

/////////////////////////////////////////////////////////////
// Constructor 
//
CFooInDLL::CFooInDLL()
{
	aString = new char[1024] ;  // DLL wil own a String memory 
	TRACE("aString(%Fp)  \r\n",aString ) ;
}

/////////////////////////////////////////////////////////////
// Constructor 
//
CFooInDLL::~CFooInDLL()
{
	if (aString)
		delete aString ;
}

/////// OUTLINE FUNCTION ///////
void CFooInDLL::myString()
{
	if (aString)
		delete aString ; // This line will fail an assertion in memory.cpp
							  // when compiled with the MFC debug libraries, if
							  // an attempt is made to delete memory owned by
							  // the app.

	aString = new char[1024] ;  // DLL will own memory
	
	TRACE("aString(%Fp)  \r\n",aString ) ;
}

/////////////////////////////////////////////////////////////////////////////
// Library init

class COwnerDLL : public CWinApp
{
public:
    virtual BOOL InitInstance();
//    virtual int ExitInstance();

    // nothing special for the constructor
    COwnerDLL(const char* pszAppName)
        : CWinApp(pszAppName)
        { }
};

BOOL COwnerDLL::InitInstance()
{
    // any DLL initialization goes here
    TRACE("OwnerDLL.DLL initializing\n");
    return TRUE;
}

/*
BOOL COwnerDLL::ExitInstance()
{
    TRACE("OwnerDLL.DLL exiting\n");
    return 0; // Return exit code
}

*/

COwnerDLL  ownerDLL("ownerDLL.dll");

/////////////////////////////////////////////////////////////////////////////

#pragma alloc_text(WEP_TEXT, _WEP) 

extern "C" int FAR PASCAL _WEP(int nExitType)
{
	TRACE("Calling _WEP\r\n") ;
	AfxWinTerm() ;
	return nExitType ;
}
