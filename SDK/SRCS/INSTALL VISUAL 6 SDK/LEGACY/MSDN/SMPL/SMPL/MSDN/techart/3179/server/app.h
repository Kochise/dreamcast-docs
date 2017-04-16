//**********************************************************************
// File name: app.h
//
//      Definition of CPDSvrApp
//
// Copyright (c) 1993 Microsoft Corporation. All rights reserved.
//**********************************************************************

#if !defined( _APP_H_)
#define _APP_H_

class CClassFactory;
class CPDSvrObj ;

class CPDSvrApp 
{
public:
	int                 m_nObjCount;          // number of instances we've
                                              // created (can only be 1 or 0)
 	DWORD               m_dwRegisterClass;    // returned by RegisterClassFactory

	CPDSvrObj FAR*    	m_lpObj;        // pointer to object

	BOOL                m_fInitialized; // OLE initialization flag

	// Initialization methods
	CPDSvrApp();           // Constructor
	virtual ~CPDSvrApp();          // Destructor
	BOOL fInitInstance (HANDLE hInstance, int nCmdShow, CClassFactory FAR * lpClassFactory);

    void ObjectCreated() ;
    void ObjectDestroyed() ;

	friend class CClassFactory;  // make the contained class a friend
    friend class CPDSvrObj ;  
};

#endif

int PASCAL WinMain(HANDLE hInstance,HANDLE hPrevInstance,LPSTR lpCmdLine,int nCmdShow);
BOOL InitApplication(HANDLE hInstance);
BOOL InitInstance(HANDLE hInstance, int nCmdShow);
