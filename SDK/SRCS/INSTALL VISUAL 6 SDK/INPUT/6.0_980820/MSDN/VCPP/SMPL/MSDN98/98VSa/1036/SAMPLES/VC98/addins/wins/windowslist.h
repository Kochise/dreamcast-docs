// WindowsList.h : Declaration of the CWindowsList

#ifndef __WINDOWSLIST_H_
#define __WINDOWSLIST_H_

#include "wins.h"
#include "resource.h"       // main symbols
#include <ObjModel\addguid.h>
#include <ObjModel\appguid.h>
#include <ObjModel\bldguid.h>
#include <ObjModel\textguid.h>
#include <ObjModel\dbgguid.h>

#include "dirlist.h"

struct IGenericDocument;

/////////////////////////////////////////////////////////////////////////////
// CWindowsList
class ATL_NO_VTABLE CWindowsList : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWindowsList, &CLSID_WindowsList>,
	public IDispatchImpl<IApplicationEvents, &IID_IApplicationEvents, &LIBID_WINSLib>,
	public IDispatchImpl<IDebuggerEvents, &IID_IDebuggerEvents, &LIBID_WINSLib>,
	public IDSAddIn,
	public IDispatchImpl<IWindowsList, &IID_IWindowsList, &LIBID_WINSLib>
{
public:
	CWindowsList()
	{
		m_cIgnoreSetDir = 0;
		m_fAutoVis = FALSE;
		m_fAutoSize = FALSE;
		m_fAutoDir = FALSE;
		m_lSize = 0;
		m_iSortedCol = 0;
	}
	void SetCurrDir(LPCTSTR szDir);
	void IgnoreNextSetDir();
	HRESULT SetInfo(IGenericDocument *pGenDoc = NULL, BOOL fDoExtras = TRUE);
	BOOL AddToList(LPCTSTR szDir, LPCTSTR szFile, LPCTSTR szFullPath, BOOL fTouch = TRUE);

DECLARE_REGISTRY_RESOURCEID(IDR_WINDOWSLIST)

BEGIN_COM_MAP(CWindowsList)
	COM_INTERFACE_ENTRY(IWindowsList)
	COM_INTERFACE_ENTRY2(IDispatch, IWindowsList)
	COM_INTERFACE_ENTRY_IID(IID_IDSAddIn, IDSAddIn)
	COM_INTERFACE_ENTRY_IID(IID_IApplicationEvents, IApplicationEvents)
	COM_INTERFACE_ENTRY_IID(IID_IDebuggerEvents, IDebuggerEvents)
END_COM_MAP()

	CComPtr<IApplication> m_spApplication;
	DWORD m_dwAddInID;
	DWORD m_dwAppEvents;
	DWORD m_dwDbgEvents;

// IDSAddIn methods
public:
	STDMETHOD(OnConnection)(IApplication* pApp, VARIANT_BOOL bFirstTime, long dwCookie, VARIANT_BOOL* bOnConnection);
	STDMETHOD(OnDisconnection)(VARIANT_BOOL bLastTime);

// IApplicationEvents methods
public:
	STDMETHOD(BeforeBuildStart)();
	STDMETHOD(BuildFinish)(long nNumErrors, long nNumWarnings);
	STDMETHOD(BeforeApplicationShutDown)();
	STDMETHOD(DocumentOpen)(IDispatch *pDocument);
	STDMETHOD(BeforeDocumentClose)(IDispatch *pDocument);
	STDMETHOD(DocumentSave)(IDispatch *pDocument);
	STDMETHOD(NewDocument)(IDispatch *pDocument);
	STDMETHOD(WindowActivate)(IDispatch *pWindow);
	STDMETHOD(WindowDeactivate)(IDispatch *pWindow);
	STDMETHOD(WorkspaceOpen)();
	STDMETHOD(WorkspaceClose)();
	STDMETHOD(NewWorkspace)();

// IDebuggerEvents method
public:
    STDMETHOD(BreakpointHit)(IDispatch *pBreakpoint);

// IWindowsList
public:
	STDMETHOD(CloseDebugWnds)();
	BOOL IsInDebugMode();
	HRESULT GetSize(LPCTSTR szFilePath, CRect& rect);
	STDMETHOD(SetVisible)();
	int m_iSortedCol;
	void Reset();
	HRESULT FindDoc(LPCTSTR szFile, CComPtr<IGenericDocument>& pDoc, BOOL fOkToOpen = TRUE);
	HRESULT DoMinWin();
	STDMETHOD(WindowsManager)();
	STDMETHOD(MinWin)();
	STDMETHOD(SetLimit)();
	STDMETHOD(MakeLimit)(IDispatch* pDispWindow = NULL);

	HRESULT OpenDoc(LPCTSTR szDoc, IGenericDocument **ppDoc = NULL);
	HRESULT CloseDoc(LPCTSTR szDoc);
	HRESULT DoMinWin(LPCTSTR szDoc);
protected:
	long m_lSize;
	BOOL m_fAutoVis;
	BOOL m_fAutoSize;
	BOOL m_fAutoDir;
	CDirList m_dirList;
	int m_cIgnoreSetDir;
};

#endif //__WINDOWSLIST_H_
