// Emp.h : main header file for the EMP application
//

#include <objbase.h>
#include <afxdisp.h>
#include <tchar.h>			// Unicode
#include <adoid.h>			// ADO C++ header	 
#include <adoint.h>			// ADO C++ header

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


/////////////////////////////////////////////////////////////////////////////
// CEmpApp:
// See Emp.cpp for the implementation of this class
//

class CEmpApp : public CWinApp
{
public:
	CEmpApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmpApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEmpApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Conversion macros/inline functions - Variant 
		  		
inline CString VTOCSTR(VARIANT *v)
{
	if(v->vt==VT_BSTR)
	{
		CString str((LPCWSTR)v->bstrVal);
		return str;
	}
	else
	{
		return CString("");
	}
}

#define VTOLONG(v)	((v).vt==VT_I4 ? (LONG)(v).lVal:0L)
#define VTODATE(v)	((v).vt==VT_DATE ? (CTime)(v).iVal:0L)


class CVar : public VARIANT
	{
public:
	CVar()
		{
		VariantInit(this);
		}
	CVar(VARTYPE vt, SCODE scode = 0)
		{
		VariantInit(this);
		this->vt = vt;
		this->scode = scode;
		}
	CVar(VARIANT var)
		{
		*this = var;
		}
	~CVar()
		{
		VariantClear(this);
		}

	// ASSIGNMENT OPS.
	CVar & operator=(PCWSTR pcwstr)
		{
		VariantClear(this);
		if (NULL == (this->bstrVal = SysAllocStringLen(pcwstr, wcslen(pcwstr))))
			throw E_OUTOFMEMORY;
		this->vt = VT_BSTR;
		return *this;
		}
	CVar & operator=(VARIANT var)
		{
		HRESULT hr;

		VariantClear(this);
		if (FAILED(hr = VariantCopy(this, &var)))
			throw hr;
		return *this;
		}

	// CAST OPS.
	// doesn't change type. only returns BSTR if variant is of type
	// bstr. asserts otherwise.
	operator BSTR() const
	{
		if(VT_BSTR == this->vt)
			return this->bstrVal;
		else
			return NULL;
	}

	HRESULT Clear()
	{
		return VariantClear(this);
	}
};
