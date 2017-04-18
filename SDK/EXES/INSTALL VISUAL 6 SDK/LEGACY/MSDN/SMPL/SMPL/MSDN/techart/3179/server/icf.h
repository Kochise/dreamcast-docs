//**********************************************************************
// File name: icf.h
//
//      Definition of CClassFactory
//
// Copyright (c) 1993 Microsoft Corporation. All rights reserved.
//**********************************************************************

#if !defined( _ICF_H_)
#define _ICF_H_

class CPDSvrApp;

class CClassFactory : public IClassFactory
{
private:
	int m_nCount;               // reference count
	CPDSvrApp FAR * m_lpApp;  // pointer to application

public:
	CClassFactory::CClassFactory(CPDSvrApp FAR * lpApp)
   {
		OutputDebugString(TEXT("In CClassFactory's Constructor\r\n"));
		m_lpApp = lpApp;
		m_nCount = 0;
	};
	virtual CClassFactory::~CClassFactory()
	{
	   OutputDebugString(TEXT("In CClassFactory's Destructor\r\n"));
	};

	// IUnknown Methods

	STDMETHODIMP QueryInterface (REFIID riid, LPVOID FAR* ppvObj);
	STDMETHODIMP_(ULONG) AddRef ();
	STDMETHODIMP_(ULONG) Release ();

	STDMETHODIMP CreateInstance (LPUNKNOWN pUnkOuter,
							  REFIID riid,
							  LPVOID FAR* ppvObject);
	STDMETHODIMP LockServer ( BOOL fLock);


	friend class CPDSvrApp;
	friend class CPDSvrObj;

};

#endif
