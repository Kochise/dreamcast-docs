[!if=(FileExists, "FALSE")]
#ifndef __[!UpperShortName]_H_
#define __[!UpperShortName]_H_
#include "resource.h"
#include <atlsnap.h>
[!else]
[!AddIncludeFile(TargetFile,"resource.h")]
[!AddIncludeFile(TargetFile, "<atlsnap.h>")]
[!endif]
[!crlf]
[!if=(IExtendPropertySheet, "TRUE")]
class [!ClassName]Page : public CSnapInPropertyPageImpl<[!ClassName]Page>
{
public :
	[!ClassName]Page(long lNotifyHandle, bool bDeleteHandle = false, TCHAR* pTitle = NULL) : 
		CSnapInPropertyPageImpl<[!ClassName]Page> (pTitle),
		m_lNotifyHandle(lNotifyHandle),
		m_bDeleteHandle(bDeleteHandle) // Should be true for only page.
	{
	}
[!crlf]
	~[!ClassName]Page()
	{
		if (m_bDeleteHandle)
			MMCFreeNotifyHandle(m_lNotifyHandle);
	}
[!crlf]
	enum { IDD = [!IDD_PROPPAGE] };
[!crlf]
BEGIN_MSG_MAP([!ClassName]Page)
	CHAIN_MSG_MAP(CSnapInPropertyPageImpl<[!ClassName]Page>)
END_MSG_MAP()
// Handler prototypes:
//	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//	LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
[!crlf]
	HRESULT PropertyChangeNotify(long param)
	{
		return MMCPropertyChangeNotify(m_lNotifyHandle, param);
	}
[!crlf]
public:
	long m_lNotifyHandle;
	bool m_bDeleteHandle;
};
[!crlf]
[!endif]
[!if=(IComponentData, "TRUE")]
class [!ClassName]Data : public CSnapInItemImpl<[!ClassName]Data>
{
public:
	static const GUID* m_NODETYPE;
	static const OLECHAR* m_SZNODETYPE;
	static const OLECHAR* m_SZDISPLAY_NAME;
	static const CLSID* m_SNAPIN_CLASSID;
[!crlf]
	CComPtr<IControlbar> m_spControlBar;
[!crlf]
[!if=(IExtendContextMenu, "TRUE")]
	BEGIN_SNAPINCOMMAND_MAP([!ClassName]Data, FALSE)
	END_SNAPINCOMMAND_MAP()
[!crlf]
[!else]
[!if=(IExtendControlBar, "TRUE")]
	BEGIN_SNAPINCOMMAND_MAP([!ClassName]Data, FALSE)
	END_SNAPINCOMMAND_MAP()
[!crlf]
[!endif]
[!endif]
[!if=(IExtendContextMenu, "TRUE")]
	SNAPINMENUID([!IDR_MENU])
[!crlf]
[!endif]
[!if=(IExtendControlBar, "TRUE")]
	BEGIN_SNAPINTOOLBARID_MAP([!ClassName]Data)
		// Create toolbar resources with button dimensions 16x16 
		// and add an entry to the MAP. You can add multiple toolbars
		// SNAPINTOOLBARID_ENTRY(Toolbar ID)
	END_SNAPINTOOLBARID_MAP()
[!crlf]
[!endif]
	[!ClassName]Data()
	{
		// Image indexes may need to be modified depending on the images specific to 
		// the snapin.

		memset(&m_scopeDataItem, 0, sizeof(SCOPEDATAITEM));
		m_scopeDataItem.mask = SDI_STR | SDI_IMAGE | SDI_OPENIMAGE | SDI_PARAM;
		m_scopeDataItem.displayname = MMC_CALLBACK;
		m_scopeDataItem.nImage = 0; 		// May need modification
		m_scopeDataItem.nOpenImage = 0; 	// May need modification
		m_scopeDataItem.lParam = (LPARAM) this;

		memset(&m_resultDataItem, 0, sizeof(RESULTDATAITEM));
		m_resultDataItem.mask = RDI_STR | RDI_IMAGE | RDI_PARAM;
		m_resultDataItem.str = MMC_CALLBACK;
		m_resultDataItem.nImage = 0;		// May need modification
		m_resultDataItem.lParam = (LPARAM) this;
	}
[!crlf]
	~[!ClassName]Data()
	{
	}
[!crlf]
[!if=(IExtendPropertySheet, "TRUE")]
	STDMETHOD(CreatePropertyPages)(LPPROPERTYSHEETCALLBACK lpProvider,
		long handle, 
		IUnknown* pUnk,
		DATA_OBJECT_TYPES type);
[!crlf]
	STDMETHOD(QueryPagesFor)(DATA_OBJECT_TYPES type)
	{
		if (type == CCT_SCOPE || type == CCT_RESULT)
			return S_OK;
		return S_FALSE;
	}
[!crlf]
[!endif]

	STDMETHOD(GetScopePaneInfo)(SCOPEDATAITEM *pScopeDataItem);
[!crlf]
	STDMETHOD(GetResultPaneInfo)(RESULTDATAITEM *pResultDataItem);
[!crlf]
	STDMETHOD(Notify)( MMC_NOTIFY_TYPE event,
		long arg,
		long param,
		IComponentData* pComponentData,
		IComponent* pComponent,
		DATA_OBJECT_TYPES type);
[!crlf]
	LPOLESTR GetResultPaneColInfo(int nCol);
};
[!endif]
[!if=(EXTENSIONSNAPIN, "TRUE")]
[!crlf]
class [!ClassName]ExtData : public CSnapInItemImpl<[!ClassName]ExtData, TRUE>
{
public:
	static const GUID* m_NODETYPE;
	static const OLECHAR* m_SZNODETYPE;
	static const OLECHAR* m_SZDISPLAY_NAME;
	static const CLSID* m_SNAPIN_CLASSID;
[!crlf]
[!if=(IExtendContextMenu, "TRUE")]
	BEGIN_SNAPINCOMMAND_MAP([!ClassName]ExtData, FALSE)
	END_SNAPINCOMMAND_MAP()
[!crlf]
[!else]
[!if=(IExtendControlBar, "TRUE")]
	BEGIN_SNAPINCOMMAND_MAP([!ClassName]ExtData, FALSE)
	END_SNAPINCOMMAND_MAP()
[!crlf]
[!endif]
[!endif]
[!if=(IExtendContextMenu, "TRUE")]
	SNAPINMENUID([!IDR_MENU])
[!crlf]
[!endif]
[!if=(IExtendControlBar, "TRUE")]
	BEGIN_SNAPINTOOLBARID_MAP([!ClassName]ExtData)
		// Create toolbar resources with button dimensions 16x16 
		// and add an entry to the MAP. You can add multiple toolbars
		// SNAPINTOOLBARID_ENTRY(Toolbar ID)
	END_SNAPINTOOLBARID_MAP()
[!crlf]
[!endif]
	[!ClassName]ExtData()
	{
		memset(&m_scopeDataItem, 0, sizeof(SCOPEDATAITEM));
		memset(&m_resultDataItem, 0, sizeof(RESULTDATAITEM));
	}
[!crlf]
	~[!ClassName]ExtData()
	{
	}
[!crlf]
[!if=(IExtendPropertySheet, "TRUE")]
	STDMETHOD(CreatePropertyPages)(LPPROPERTYSHEETCALLBACK lpProvider,
		long handle, 
		IUnknown* pUnk,
		DATA_OBJECT_TYPES type);
[!crlf]
	STDMETHOD(QueryPagesFor)(DATA_OBJECT_TYPES type)
	{
		if (type == CCT_SCOPE || type == CCT_RESULT)
			return S_OK;
		return S_FALSE;
	}
[!crlf]
[!endif]
	IDataObject* m_pDataObject;

	virtual void InitDataClass(IDataObject* pDataObject, CSnapInItem* pDefault)
	{
		m_pDataObject = pDataObject;
		// The default code stores off the pointer to the Dataobject the class is wrapping
		// at the time. 
		// Alternatively you could convert the dataobject to the internal format
		// it represents and store that information
	}
[!crlf]
	CSnapInItem* GetExtNodeObject(IDataObject* pDataObject, CSnapInItem* pDefault)
	{
		// Modify to return a different CSnapInItem* pointer.

		return pDefault;
	}
[!crlf]
};
[!endif]
[!if=(IComponent, "TRUE")]
[!crlf]
class [!ClassName];
[!crlf]
class [!ClassName]Component : public CComObjectRootEx<CComSingleThreadModel>,
	public CSnapInObjectRoot<2, [!ClassName] >,
[!if=(IExtendPropertySheet, "TRUE")]
	public IExtendPropertySheetImpl<[!ClassName]Component>,
[!endif]
[!if=(IExtendContextMenu, "TRUE")]
	public IExtendContextMenuImpl<[!ClassName]Component>,
[!endif]
[!if=(IExtendControlBar, "TRUE")]
	public IExtendControlbarImpl<[!ClassName]Component>,
[!endif]
[!if=(PERSIST, "TRUE")]
[!if=(IPersistStorage, "TRUE")]	public IPersistStorage,[!endif]
[!if=(IPersistStream, "TRUE")]	public IPersistStream,[!endif]
[!if=(IPersistStreamInit, "TRUE")]	public IPersistStreamInit,[!endif]
[!endif]
	public IComponentImpl<[!ClassName]Component>
{
public:
BEGIN_COM_MAP([!ClassName]Component)
	COM_INTERFACE_ENTRY(IComponent)
[!if=(IExtendPropertySheet, "TRUE")]    COM_INTERFACE_ENTRY(IExtendPropertySheet)[!endif]
[!if=(IExtendContextMenu, "TRUE")]    COM_INTERFACE_ENTRY(IExtendContextMenu)[!endif]
[!if=(IExtendControlBar, "TRUE")]    COM_INTERFACE_ENTRY(IExtendControlbar)[!endif]
[!if=(PERSIST, "TRUE")]
[!if=(IPersistStorage, "TRUE")]	COM_INTERFACE_ENTRY(IPersistStorage)[!endif]
[!if=(IPersistStream, "TRUE")]	COM_INTERFACE_ENTRY(IPersistStream)[!endif]
[!if=(IPersistStreamInit, "TRUE")]	COM_INTERFACE_ENTRY(IPersistStreamInit)[!endif]
[!endif]
END_COM_MAP()
[!crlf]
public:
	[!ClassName]Component()
	{
	}
[!crlf]
	STDMETHOD(Notify)(LPDATAOBJECT lpDataObject, MMC_NOTIFY_TYPE event, long arg, long param)
	{
		if (lpDataObject != NULL)
			return IComponentImpl<[!ClassName]Component>::Notify(lpDataObject, event, arg, param);

		// TODO : Add code to handle notifications that set lpDataObject == NULL.
		return E_NOTIMPL;
	}
[!crlf]
[!if=(PERSIST, "TRUE")]
	STDMETHOD(GetClassID)(CLSID *pClassID)
	{
		ATLTRACENOTIMPL(_T("[!ClassName]Component::GetClassID"));
	}	
[!crlf]
	STDMETHOD(IsDirty)()
	{
		ATLTRACENOTIMPL(_T("[!ClassName]Component::IsDirty"));
	}
[!crlf]
[!if=(IPersistStorage, "TRUE")]
	STDMETHOD(InitNew)(IStorage *pStg)
	{
		ATLTRACE(_T("[!ClassName]Component::InitNew\n"));
		return S_OK;
	}
[!crlf]
	STDMETHOD(Load)(IStorage *pStg)
	{
		ATLTRACENOTIMPL(_T("[!ClassName]Component::Load"));
	}
[!crlf]
	virtual HRESULT STDMETHODCALLTYPE Save(IStorage *pStgSave,
		BOOL fSameAsLoad)
	{
		ATLTRACENOTIMPL(_T("[!ClassName]Component::Save"));
	}
[!crlf]
	virtual HRESULT STDMETHODCALLTYPE SaveCompleted(IStorage *pStgNew)
	{
		ATLTRACENOTIMPL(_T("[!ClassName]Component::SaveCompleted"));
	}
[!crlf]
	virtual HRESULT STDMETHODCALLTYPE HandsOffStorage()
	{
		ATLTRACENOTIMPL(_T("[!ClassName]Component::HandsOffStorage"));
	}
[!else]
	STDMETHOD(Load)(IStream *pStm)
	{
		ATLTRACENOTIMPL(_T("[!ClassName]Component::Load"));
	}
[!crlf]
	STDMETHOD(Save)(IStream *pStm, BOOL fClearDirty)
	{
		ATLTRACENOTIMPL(_T("[!ClassName]Component::Save"));
	}
[!crlf]
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize)
	{
		ATLTRACENOTIMPL(_T("[!ClassName]Component::GetSizeMax"));
	}
[!crlf]
[!if=(IPersistStreamInit, "TRUE")]
	STDMETHOD(InitNew)()
	{
		ATLTRACE(_T("[!ClassName]Component::InitNew\n"));
		return S_OK;
	}
[!crlf]

[!endif]
[!endif]
[!endif]
};
[!crlf]
[!endif]

class [!ClassName] : public CComObjectRootEx<CComSingleThreadModel>,
public CSnapInObjectRoot<[!if=(IComponentData, "TRUE")]1[!else]0[!endif], [!ClassName]>,
[!if=(IComponentData, "TRUE")]
	public IComponentDataImpl<[!ClassName], [!ClassName]Component>,
[!endif]
[!if=(EXTENSIONSNAPIN, "TRUE")]
[!if=(IExtendControlBar, "TRUE")]
	public IExtendControlbarImpl<[!ClassName]>,
[!endif]
[!endif]
[!if=(IExtendPropertySheet, "TRUE")]
	public IExtendPropertySheetImpl<[!ClassName]>,
[!endif]
[!if=(IExtendContextMenu, "TRUE")]
	public IExtendContextMenuImpl<[!ClassName]>,
[!endif]
[!if=(PERSIST, "TRUE")]
[!if=(IPersistStorage, "TRUE")]	public IPersistStorage,[!endif]
[!if=(IPersistStream, "TRUE")]	public IPersistStream,[!endif]
[!if=(IPersistStreamInit, "TRUE")]	public IPersistStreamInit,[!endif]
[!endif]
	public CComCoClass<[!ClassName], &CLSID_[!CoClassName]>
{
public:
	[!ClassName]()
	{
[!if=(IComponentData, "TRUE")]
		m_pNode = new [!ClassName]Data;
		_ASSERTE(m_pNode != NULL);
[!endif]
		m_pComponentData = this;
	}
[!if=(IComponentData, "TRUE")]
[!crlf]
	~[!ClassName]()
	{
		delete m_pNode;
		m_pNode = NULL;
	}

[!crlf]
[!endif]
[!if=(EXTENSIONSNAPIN, "TRUE")]
EXTENSION_SNAPIN_DATACLASS([!ClassName]ExtData)
[!crlf]
BEGIN_EXTENSION_SNAPIN_NODEINFO_MAP([!ClassName])
	EXTENSION_SNAPIN_NODEINFO_ENTRY([!ClassName]ExtData)
END_EXTENSION_SNAPIN_NODEINFO_MAP()
[!crlf]
[!endif]
BEGIN_COM_MAP([!ClassName])
[!if=(IComponentData, "TRUE")]	  COM_INTERFACE_ENTRY(IComponentData)[!endif]
[!if=(EXTENSIONSNAPIN, "TRUE")][!if=(IExtendControlBar, "TRUE")]	COM_INTERFACE_ENTRY(IExtendControlbar)[!endif][!endif]
[!if=(IExtendPropertySheet, "TRUE")]    COM_INTERFACE_ENTRY(IExtendPropertySheet)[!endif]
[!if=(IExtendContextMenu, "TRUE")]    COM_INTERFACE_ENTRY(IExtendContextMenu)[!endif]
[!if=(PERSIST, "TRUE")]
[!if=(IPersistStorage, "TRUE")]	COM_INTERFACE_ENTRY(IPersistStorage)[!endif]
[!if=(IPersistStream, "TRUE")]	COM_INTERFACE_ENTRY(IPersistStream)[!endif]
[!if=(IPersistStreamInit, "TRUE")]	COM_INTERFACE_ENTRY(IPersistStreamInit)[!endif]
[!endif]
END_COM_MAP()
[!crlf]
DECLARE_REGISTRY_RESOURCEID([!IDR_REGISTRYID])
[!crlf]
DECLARE_NOT_AGGREGATABLE([!ClassName])
[!crlf]
[!if=(PERSIST, "TRUE")]
	STDMETHOD(GetClassID)(CLSID *pClassID)
	{
		ATLTRACENOTIMPL(_T("[!ClassName]::GetClassID"));
	}	
[!crlf]
	STDMETHOD(IsDirty)()
	{
		ATLTRACENOTIMPL(_T("[!ClassName]::IsDirty"));
	}
[!crlf]
[!if=(IPersistStorage, "TRUE")]
	STDMETHOD(InitNew)(IStorage *pStg)
	{
		ATLTRACE(_T("[!ClassName]::InitNew\n"));
		return S_OK;
	}
[!crlf]
	STDMETHOD(Load)(IStorage *pStg)
	{
		ATLTRACENOTIMPL(_T("[!ClassName]::Load"));
	}
[!crlf]
	virtual HRESULT STDMETHODCALLTYPE Save(IStorage *pStgSave,
		BOOL fSameAsLoad)
	{
		ATLTRACENOTIMPL(_T("[!ClassName]::Save"));
	}
[!crlf]
	virtual HRESULT STDMETHODCALLTYPE SaveCompleted(IStorage *pStgNew)
	{
		ATLTRACENOTIMPL(_T("[!ClassName]::SaveCompleted"));
	}
[!crlf]
	virtual HRESULT STDMETHODCALLTYPE HandsOffStorage()
	{
		ATLTRACENOTIMPL(_T("[!ClassName]::HandsOffStorage"));
	}
[!crlf]
[!else]
	STDMETHOD(Load)(IStream *pStm)
	{
		ATLTRACENOTIMPL(_T("[!ClassName]::Load"));
	}
[!crlf]
	STDMETHOD(Save)(IStream *pStm, BOOL fClearDirty)
	{
		ATLTRACENOTIMPL(_T("[!ClassName]::Save"));
	}
[!crlf]
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize)
	{
		ATLTRACENOTIMPL(_T("[!ClassName]::GetSizeMax"));
	}
[!crlf]
[!if=(IPersistStreamInit, "TRUE")]
	STDMETHOD(InitNew)()
	{
		ATLTRACE(_T("[!ClassName]::InitNew\n"));
		return S_OK;
	}
[!crlf]
[!endif]
[!endif]
[!endif]
[!if=(IComponentData, "TRUE")]
	STDMETHOD(Initialize)(LPUNKNOWN pUnknown);
[!endif]
[!crlf]
	static void WINAPI ObjectMain(bool bStarting)
	{
		if (bStarting)
			CSnapInItem::Init();
	}
};
[!crlf]

[!if=(ISnapinAbout, "TRUE")]
class ATL_NO_VTABLE [!ClassName]About : public ISnapinAbout,
	public CComObjectRoot,
	public CComCoClass< [!ClassName]About, &CLSID_[!CoClassName]About>
{
public:
	DECLARE_REGISTRY([!ClassName]About, _T("[!CoClassName]About.1"), _T("[!CoClassName]About.1"), [!IDS_DESC], THREADFLAGS_BOTH);
[!crlf]
	BEGIN_COM_MAP([!ClassName]About)
		COM_INTERFACE_ENTRY(ISnapinAbout)
	END_COM_MAP()
[!crlf]
	STDMETHOD(GetSnapinDescription)(LPOLESTR *lpDescription)
	{
		USES_CONVERSION;
		TCHAR szBuf[256];
		if (::LoadString(_Module.GetResourceInstance(), [!IDS_DESC], szBuf, 256) == 0)
			return E_FAIL;
[!crlf]
		*lpDescription = (LPOLESTR)CoTaskMemAlloc((lstrlen(szBuf) + 1) * sizeof(OLECHAR));
		if (*lpDescription == NULL)
			return E_OUTOFMEMORY;
[!crlf]
		ocscpy(*lpDescription, T2OLE(szBuf));
[!crlf]
		return S_OK;
	}
[!crlf]
	STDMETHOD(GetProvider)(LPOLESTR *lpName)
	{
		USES_CONVERSION;
		TCHAR szBuf[256];
		if (::LoadString(_Module.GetResourceInstance(), [!IDS_PROVIDER], szBuf, 256) == 0)
			return E_FAIL;
[!crlf]
		*lpName = (LPOLESTR)CoTaskMemAlloc((lstrlen(szBuf) + 1) * sizeof(OLECHAR));
		if (*lpName == NULL)
			return E_OUTOFMEMORY;
[!crlf]
		ocscpy(*lpName, T2OLE(szBuf));
[!crlf]
		return S_OK;
	}
[!crlf]
	STDMETHOD(GetSnapinVersion)(LPOLESTR *lpVersion)
	{
		USES_CONVERSION;
		TCHAR szBuf[256];
		if (::LoadString(_Module.GetResourceInstance(), [!IDS_VERSION], szBuf, 256) == 0)
			return E_FAIL;
[!crlf]
		*lpVersion = (LPOLESTR)CoTaskMemAlloc((lstrlen(szBuf) + 1) * sizeof(OLECHAR));
		if (*lpVersion == NULL)
			return E_OUTOFMEMORY;
[!crlf]
		ocscpy(*lpVersion, T2OLE(szBuf));
[!crlf]
		return S_OK;
	}
[!crlf]
	STDMETHOD(GetSnapinImage)(HICON *hAppIcon)
	{
		*hAppIcon = NULL;
		return S_OK;
	}
[!crlf]
	STDMETHOD(GetStaticFolderImage)(HBITMAP *hSmallImage,
		HBITMAP *hSmallImageOpen,
		HBITMAP *hLargeImage,
		COLORREF *cMask)
	{
		*hSmallImageOpen = *hLargeImage = *hLargeImage = 0;
		return S_OK;
	}
};
[!crlf]
[!endif]
[!if=(FileExists, "FALSE")]
#endif
[!endif]