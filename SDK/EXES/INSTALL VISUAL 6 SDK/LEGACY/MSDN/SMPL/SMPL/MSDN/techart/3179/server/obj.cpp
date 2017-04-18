//**********************************************************************
// File name: obj.cpp
//
//Implementation file for the CPDSvrObj Class
//
// Functions:
//
//    See obj.h for a list of member functions.
//
// Copyright (c) 1994 Microsoft Corporation. All rights reserved.
//**********************************************************************

#include "pre.h"
#include "obj.h"
#include "icf.h"
#include "app.h"
#include <tchar.h>
#include "..\guids.h"

typedef ILookup * LPLOOKUP;

//**********************************************************************
// CPDSvrObj::QueryInterface
//
// Purpose: Used for interface negotiation at the "Object" level.
//
// Parameters:
//      REFIID riid         -   A reference to the interface that is
//                              being queried.
//      LPVOID FAR* ppvObj  -   An out parameter to return a pointer to
//                              the interface.
// Return Value:
//      S_OK          -   The interface is supported.
//      E_NOINTERFACE -   The interface is not supported
//
// Function Calls:
//      Function                    Location
//      OutputDebugString           Windows API
//      ResultFromScode             OLE API
//      IUnknown::AddRef            OBJ.CPP
//********************************************************************
STDMETHODIMP CPDSvrObj::QueryInterface ( REFIID riid, LPVOID FAR* ppvObj)
{
	OutputDebugString(TEXT("In CPDSvrObj::QueryInterface\r\n"));

	SCODE sc = S_OK;

	if (IsEqualIID(riid, IID_IUnknown))  // asking for IUnknown
		*ppvObj = (LPUNKNOWN)this;
	else if (IsEqualIID(riid, IID_ILookup)) // asking for ILookup
		*ppvObj = (LPLOOKUP)this;
	else  // asking for something we don't implement
	{
		*ppvObj = NULL;
		sc = E_NOINTERFACE;
	}

	if (*ppvObj)  // increment ref count
		((LPUNKNOWN)*ppvObj)->AddRef();

	return ResultFromScode( sc );
};

//**********************************************************************
// CPDSvrObj::AddRef
//
// Purpose:      Increments the object's reference count.
// Parameters:   None
// Return Value: The object's new reference count
//
// Function Calls:
//      Function                    Location
//      OutputDebugString           Windows API
//********************************************************************
STDMETHODIMP_(ULONG) CPDSvrObj::AddRef ()
{
	OutputDebugString(TEXT("In CPDSvrObj::AddRef\r\n"));
	return ++m_nCount;
};

//**********************************************************************
// CPDSvrObj::Release
//
// Purpose:      Decrements the object's reference count
// Parameters:   None
// Return Value: The object's new reference count
//
// Function Calls:
//      Function                    Location
//      OutputDebugString           Windows API
//********************************************************************

STDMETHODIMP_(ULONG) CPDSvrObj::Release ()
{
 	TCHAR szBuff[64];

 	wsprintf(szBuff, 
	         TEXT("In CPDSvrObj::Release. m_nCount = %d\r\n"), 
	         m_nCount -1);

	OutputDebugString(szBuff);

	if (--m_nCount == 0)  // ref count is zero - we can safely unload now
	{
		m_lpApp->m_lpObj = NULL ;
        m_lpApp->ObjectDestroyed() ;  
		delete this;
        return 0;
    }

	return m_nCount;
}

//**********************************************************************
// LookupByName
//
// Purpose:      Given a name, finds the corresponding number in the 
//               phone directory database
// Parameters:   
//      LPTSTR lpName      -Name to look up. (in parameter)
//      TCHAR **lplpNumber -Pointer to number found (out parameter)
// Return Value: 
//      S_OK    - Number found - Successful return
//      S_FALSE - Number not found - Successful return
//      E_FAIL  - function failed.
//********************************************************************
STDMETHODIMP CPDSvrObj::LookupByName(LPTSTR lpName, TCHAR ** lplpNumber)
{
    int i;
	LPMALLOC pMalloc;
	HRESULT  hRes;

    OutputDebugString(TEXT("In CPDSvrObj::LookupByName\r\n"));

	*lplpNumber = NULL;

    for(i=0; i < MAX_RECORDS; i++)
    {
		if(_tcscmp(theDatabase[i].name,lpName)==0)
		{
		  	hRes = CoGetMalloc(MEMCTX_TASK, &pMalloc);
			if (SUCCEEDED(hRes))
				*lplpNumber = (LPTSTR)pMalloc->Alloc(25*sizeof(TCHAR));
			else
				return (E_FAIL);

	    	_tcscpy(*lplpNumber, theDatabase[i].phone_number);

			pMalloc->Release();
			return ResultFromScode(S_OK);
    	}
	}
    return ResultFromScode(S_FALSE);
}
										   
//**********************************************************************
// LookupByNumber
//
// Purpose:      Given a number, finds the corresponding name in the 
//               phone directory database
// Parameters:   
//      LPTSTR lpNumber  -Number to look up. (in parameter)
//      TCHAR **lplpName -Pointer to name found (out parameter)
// Return Value: 
//      S_OK    - Name found - Successful return
//      S_FALSE - Name not found - Successful return
//      E_FAIL  - function failed.
//********************************************************************
STDMETHODIMP CPDSvrObj::LookupByNumber(LPTSTR lpNumber, TCHAR ** lplpName)
{
    int i;
	LPMALLOC pMalloc;
	HRESULT  hRes;

    OutputDebugString(TEXT("In CPDSvrObj::LookupByNumber\r\n"));

	*lplpName = NULL;

    for(i=0; i < MAX_RECORDS; i++)
    {
		if(_tcscmp(theDatabase[i].phone_number,lpNumber)==0)
		{
		  	hRes = CoGetMalloc(MEMCTX_TASK, &pMalloc);
			if (SUCCEEDED(hRes))
				*lplpName = (LPTSTR)pMalloc->Alloc(25*sizeof(TCHAR));
			else
				return (E_FAIL);

	    	_tcscpy(*lplpName, theDatabase[i].name);

			pMalloc->Release();
			return ResultFromScode(S_OK);
    	}
	}
    return ResultFromScode(S_FALSE);
}

//**********************************************************************
// CPDSvrObj::CPDSvrObj
//
// Purpose:      Constructor for CPDSvrObj
// Parameters:   None
// Return Value: None
//********************************************************************
CPDSvrObj::CPDSvrObj(CPDSvrApp FAR * lpApp) 
{
    OutputDebugString(TEXT("In CPDSvrObj constructor\r\n"));

	m_nCount = 0;
    m_lpApp = lpApp ;

	m_dwRegister = 0; 

	Initialize();  // initialize phone book database
}

//**********************************************************************
// CPDSvrObj::~CPDSvrObj
//
// Purpose:      Destructor for CPDSvrObj
// Parameters:   None
// Return Value: None
//********************************************************************

CPDSvrObj::~CPDSvrObj()
{
	OutputDebugString(TEXT("In CPDSvrObj's Destructor \r\n"));
}
//**********************************************************************
// Initialize
// - helper function to intialize phone directory database
//**********************************************************************
BOOL CPDSvrObj::Initialize(void)
{
    CreateRecord(0,TEXT("Daffy Duck"),         TEXT("310-555-1212"));
    CreateRecord(1,TEXT("Wile E. Coyote"),     TEXT("408-555-1212"));
    CreateRecord(2,TEXT("Scrooge McDuck"),     TEXT("206-555-1212"));
    CreateRecord(3,TEXT("Huey Lewis"),         TEXT("415-555-1212"));
    CreateRecord(4,TEXT("Thomas Dewey"),       TEXT("617-555-1212"));
    return TRUE; /* success */
}


//**********************************************************************
// CreateRecord
// - helper function to set up phone directory database
//**********************************************************************
void CPDSvrObj::CreateRecord(int i,LPTSTR lpName, LPTSTR lpNumber)
{
    theDatabase[i].name         = lpName;
    theDatabase[i].phone_number = lpNumber;
}
