// UrlRead.h : Declaration of the CUrlReader

#ifndef __URLREADER_H_
#define __URLREADER_H_

#include "resource.h"       // main symbols
#include "CPRdUrl.h"
#include <ComDef.h>	// for _bstr_t class

/////////////////////////////////////////////////////////////////////////////
// CUrlReader
class ATL_NO_VTABLE CUrlReader : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUrlReader, &CLSID_UrlReader>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CUrlReader>,
	public CProxyDIUrlReaderEvents<CUrlReader>,
	public IDispatchImpl<IUrlReader, &IID_IUrlReader, &LIBID_READURLLib>
{
public:
	CUrlReader()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_URLREADER)
//DECLARE_NOT_AGGREGATABLE(CUrlReader)

BEGIN_COM_MAP(CUrlReader)
	COM_INTERFACE_ENTRY(IUrlReader)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CUrlReader)
	CONNECTION_POINT_ENTRY(DIID_DIUrlReaderEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IUrlReader
public:
	static DWORD WINAPI ProcessUrl(LPVOID pParam);
	STDMETHOD(ReadUrl)(BSTR sURL, BSTR sOutputSpec);
private:
	DWORD m_dwThreadId;
	HANDLE m_hThread;
protected:
	_bstr_t m_OutputFilespec;
	_bstr_t m_URLSpec;
};

#endif //__URLREADER_H_
