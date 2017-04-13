// MarkIt.h : Declaration of the CMarkIt

#ifndef __MARKIT_H_
#define __MARKIT_H_

#include "resource.h"       // main symbols
#include <ObjModel\addguid.h>
#include <ObjModel\appguid.h>
#include <ObjModel\bldguid.h>
#include <ObjModel\textguid.h>
#include <ObjModel\dbgguid.h>

/////////////////////////////////////////////////////////////////////////////
// CMarkIt
class ATL_NO_VTABLE CMarkIt : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMarkIt, &CLSID_MarkIt>,
	public IDSAddIn,
	public IDispatchImpl<IMarkIt, &IID_IMarkIt, &LIBID_BOOKNOTELib>
{
public:
	CMarkIt();
	~CMarkIt();

DECLARE_REGISTRY_RESOURCEID(IDR_MARKIT)

BEGIN_COM_MAP(CMarkIt)
	COM_INTERFACE_ENTRY(IMarkIt)
	COM_INTERFACE_ENTRY2(IDispatch, IMarkIt)
	COM_INTERFACE_ENTRY_IID(IID_IDSAddIn, IDSAddIn)
END_COM_MAP()

	CComPtr<IApplication> m_spApplication;
	DWORD m_dwAddInID;

// IDSAddIn methods
public:
	STDMETHOD(OnConnection)(IApplication* pApp, VARIANT_BOOL bFirstTime, long dwCookie, VARIANT_BOOL* bOnConnection);
	STDMETHOD(OnDisconnection)(VARIANT_BOOL bLastTime);

// IMarkIt
public:
	HRESULT Dump(LPCTSTR szFile);
	STDMETHOD(BookNote)();

protected:
	BOOL m_fEcho;
	CString m_strFile;
};

#endif //__MARKIT_H_
