[!if=(FreeThreadedMarshaler, "TRUE")]
	[!set(NeedsGetControllingUnknown, "TRUE")]
[!endif]
// [!HeaderName] : Declaration of the [!ClassName]
[!crlf]

[!if=(FileExists, "FALSE")]
#ifndef __[!UpperShortName]_H_
#define __[!UpperShortName]_H_
[!crlf]
#include "resource.h"       // main symbols
[!else]
[!AddIncludeFile(TargetFile, "resource.h")]
[!endif]

[!crlf]
EXTERN_C const CLSID CLSID_[!CoClassName];
[!crlf]
/////////////////////////////////////////////////////////////////////////////
// [!ClassName]

class ATL_NO_VTABLE [!ClassName] :
[!if=(ThreadingModel, "Single")]
	public CComObjectRootEx<CComSingleThreadModel>,
[!endif]
[!if=(ThreadingModel, "Apartment")]
	public CComObjectRootEx<CComSingleThreadModel>,
[!endif]
[!if=(ThreadingModel, "Both")]
	public CComObjectRootEx<CComMultiThreadModel>,
[!endif]
[!if=(ThreadingModel, "Free")]
	public CComObjectRootEx<CComMultiThreadModel>,
[!endif]
	public CComCoClass<[!ClassName], &CLSID_[!CoClassName]>,
	public IPropertyPageImpl<[!ClassName]>,
	public CDialogImpl<[!ClassName]>
{
public:
	[!ClassName]() 
	{
[!if=(FreeThreadedMarshaler, "TRUE")]
		m_pUnkMarshaler = NULL;
[!endif]
		m_dwTitleID = [!IDS_TITLE];
		m_dwHelpFileID = [!IDS_HELPFILE];
		m_dwDocStringID = [!IDS_DOCSTRING];
	}

[!crlf]
	enum {IDD = IDD_[!UpperShortName]};

[!crlf]
[!if=(NeedsGetControllingUnknown, "TRUE")]
DECLARE_GET_CONTROLLING_UNKNOWN()
[!endif]
DECLARE_REGISTRY_RESOURCEID([!IDR_REGISTRYID])

[!if=(Aggregatable, "NO")]
DECLARE_NOT_AGGREGATABLE([!ClassName])
[!endif]
[!if=(Aggregatable, "ONLY")]
DECLARE_ONLY_AGGREGATABLE([!ClassName])
[!endif]
[!crlf]
DECLARE_PROTECT_FINAL_CONSTRUCT()

[!crlf]
BEGIN_COM_MAP([!ClassName]) 
	COM_INTERFACE_ENTRY(IPropertyPage)
[!if=(FreeThreadedMarshaler, "TRUE")]
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
[!endif]
END_COM_MAP()

[!crlf]
BEGIN_MSG_MAP([!ClassName])
	CHAIN_MSG_MAP(IPropertyPageImpl<[!ClassName]>)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

[!if=(FreeThreadedMarshaler, "TRUE")]
[!crlf]
	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

[!crlf]
	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

[!crlf]
	CComPtr<IUnknown> m_pUnkMarshaler;
[!endif]

[!crlf]
	STDMETHOD(Apply)(void)
	{
		ATLTRACE(_T("[!ClassName]::Apply\n"));
		for (UINT i = 0; i < m_nObjects; i++)
		{
			// Do something interesting here
			// ICircCtl* pCirc;
			// m_ppUnk[i]->QueryInterface(IID_ICircCtl, (void**)&pCirc);
			// pCirc->put_Caption(CComBSTR("something special"));
			// pCirc->Release();
		}
		m_bDirty = FALSE;
		return S_OK;
	}
};

[!crlf]
[!if=(FileExists, "FALSE")]
#endif //__[!UpperShortName]_H_
[!endif]
