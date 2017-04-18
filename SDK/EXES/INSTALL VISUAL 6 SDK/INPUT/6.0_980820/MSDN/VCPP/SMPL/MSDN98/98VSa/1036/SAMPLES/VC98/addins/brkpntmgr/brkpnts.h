// BrkPnts.h : Declaration of the CBrkPnts

#ifndef __BRKPNTS_H_
#define __BRKPNTS_H_

#include "DlgBrkPnts.h"	// Added by ClassView
#include "resource.h"       // main symbols
#include <ObjModel\addguid.h>
#include <ObjModel\appguid.h>
#include <ObjModel\bldguid.h>
#include <ObjModel\textguid.h>
#include <ObjModel\dbgguid.h>

/////////////////////////////////////////////////////////////////////////////
// CBrkPnts
class ATL_NO_VTABLE CBrkPnts : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBrkPnts, &CLSID_BrkPnts>,
	public IDispatchImpl<IApplicationEvents, &IID_IApplicationEvents, &LIBID_BRKPNTMGRLib>,
	public IDispatchImpl<IDebuggerEvents, &IID_IDebuggerEvents, &LIBID_BRKPNTMGRLib>,
	public IDSAddIn,
	public IDispatchImpl<IBrkPnts, &IID_IBrkPnts, &LIBID_BRKPNTMGRLib>
{
public:
	CBrkPnts();
	~CBrkPnts();
	HRESULT GetBrkPnts();

DECLARE_REGISTRY_RESOURCEID(IDR_BRKPNTS)

BEGIN_COM_MAP(CBrkPnts)
	COM_INTERFACE_ENTRY_IID(IID_IBrkPnts, IBrkPnts)
	COM_INTERFACE_ENTRY2(IDispatch, IBrkPnts)
	COM_INTERFACE_ENTRY_IID(IID_IDSAddIn, IDSAddIn)
	COM_INTERFACE_ENTRY_IID(IID_IApplicationEvents, IApplicationEvents)
	COM_INTERFACE_ENTRY_IID(IID_IDebuggerEvents, IDebuggerEvents)
END_COM_MAP()

	CComPtr<IApplication> m_spApplication;
	CComPtr<IDispatch> m_pDispBrkPnts;
	CComQIPtr<IBreakpoints, &IID_IBreakpoints> m_pBrkPnts;
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

// IBrkPnts
public:
	void GetCounts(long &lTotal, long &lEnabled);
	void SetFile(LPCTSTR szFile);
	void SetSaveOnlyEnabled(BOOL fSaveOnlyEnabled);
	HRESULT ClearAll();
	HRESULT FindDoc(LPCTSTR szFile, CComPtr<IGenericDocument>& pDoc, BOOL fOkToOpen = TRUE);
	HRESULT Save(BOOL fToOutputWindow, LPCTSTR szFile, BOOL fSaveOnlyEnabled, CString& strComment);
	HRESULT Load(LPCTSTR szFile, CString& strComment);
	STDMETHOD(BrkPntMgr)();
protected:
	BOOL	m_fSaveOnlyEnabled;
	CString	m_strFile;
	BOOL	m_fOutputWnd;

};

#endif //__BRKPNTS_H_
