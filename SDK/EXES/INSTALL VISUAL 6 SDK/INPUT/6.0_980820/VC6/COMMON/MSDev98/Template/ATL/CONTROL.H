[!if=(SubclassWindow, "SysListView32")][!set(UseCommonControls, "TRUE")][!endif]
[!if=(SubclassWindow, "SysTreeView32")][!set(UseCommonControls, "TRUE")][!endif]
[!if=(SubclassWindow, "SysAnimate32")][!set(UseCommonControls, "TRUE")][!endif]
[!if=(SubclassWindow, "SysHeader32")][!set(UseCommonControls, "TRUE")][!endif]
[!if=(SubclassWindow, "SysTabControl32")][!set(UseCommonControls, "TRUE")][!endif]

[!if=(SubclassWindow, "Edit")][!set(UseArrowKeys, "TRUE")][!endif]
[!if=(SubclassWindow, "ListBox")][!set(UseArrowKeys, "TRUE")][!endif]
[!if=(SubclassWindow, "ComboBox")][!set(UseArrowKeys, "TRUE")][!endif]
[!if=(SubclassWindow, "ScrollBar")][!set(UseArrowKeys, "TRUE")][!endif]
[!if=(SubclassWindow, "RichEdit")][!set(UseArrowKeys, "TRUE")][!endif]
[!if=(SubclassWindow, "SysListView32")][!set(UseArrowKeys, "TRUE")][!endif]
[!if=(SubclassWindow, "SysTreeView32")][!set(UseArrowKeys, "TRUE")][!endif]
[!if=(SubclassWindow, "SysTabControl32")][!set(UseArrowKeys, "TRUE")][!endif]

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
#include <atlctl.h>
[!if=(UseCommonControls, "TRUE")]#include <commctrl.h>[!endif]
[!if=(SubclassWindow, "RichEdit")]#include <richedit.h>[!endif]
[!else]
[!AddIncludeFile(TargetFile, "resource.h")]
[!AddIncludeFile(TargetFile, "<atlctl.h>")]
[!if=(UseCommonControls, "TRUE")][!AddIncludeFile(TargetFile, "<commctrl.h>")][!endif]
[!if=(SubclassWindow, "RichEdit")][!AddIncludeFile(TargetFile, "<richedit.h>")][!endif]
[!endif]

[!crlf]
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
[!if=(StockPropEnabled, "TRUE")]
	public CStockPropImpl<[!ClassName], [!InterfaceName], &IID_[!InterfaceName], &LIBID_[!LibName]>,
[!else]
	[!if=(Dual, "TRUE")]public IDispatchImpl<[!InterfaceName], &IID_[!InterfaceName], &LIBID_[!LibName]>,[!else]public [!InterfaceName],[!endif]
[!endif]
[!if=(HTMLControl, "TRUE")]
	public IDispatchImpl<[!InterfaceName]UI, &IID_[!InterfaceName]UI, &LIBID_[!LibName]>,
[!endif]
[!if=(CompositeControl, "TRUE")]
	public CComCompositeControl<[!ClassName]>,
[!else]
	public CComControl<[!ClassName]>,
[!endif]
	public IPersistStreamInitImpl<[!ClassName]>,
	public IOleControlImpl<[!ClassName]>,
	public IOleObjectImpl<[!ClassName]>,
	public IOleInPlaceActiveObjectImpl<[!ClassName]>,
	public IViewObjectExImpl<[!ClassName]>,
	public IOleInPlaceObjectWindowlessImpl<[!ClassName]>,
[!if=(ErrorInfoEnabled, "TRUE")]
	public ISupportErrorInfo,
[!endif]
[!if=(ConnectionPointsEnabled, "TRUE")]
	public IConnectionPointContainerImpl<[!ClassName]>,
[!endif]
[!if=(IOBJECTWITHSITE, "TRUE")]
	public IObjectWithSiteImpl<[!ClassName]>,
[!endif]
[!if=(ISERVICEPROVIDER, "TRUE")]
	public IServiceProviderImpl<[!ClassName]>,
[!endif]

[!if=(IPERSISTSTORAGE, "TRUE")]
	public IPersistStorageImpl<[!ClassName]>,
[!endif]
[!if=(ISPECIFYPROPERTYPAGES, "TRUE")]
	public ISpecifyPropertyPagesImpl<[!ClassName]>,
[!endif]
[!if=(IQUICKACTIVATE, "TRUE")]
	public IQuickActivateImpl<[!ClassName]>,
[!endif]
[!if=(IDATAOBJECT, "TRUE")]
	public IDataObjectImpl<[!ClassName]>,
[!endif]
[!if=(ConnectionPointsEnabled, "TRUE")]
[!if=(IPROVIDECLASSINFO2, "TRUE")]
	public IProvideClassInfo2Impl<&CLSID_[!CoClassName], &DIID__[!InterfaceName]Events, &LIBID_[!LibName]>,
[!endif]
[!if=(IPROPERTYNOTIFYSINK, "TRUE")]
	public IPropertyNotifySinkCP<[!ClassName]>,
[!endif]
[!else]
[!if=(IPROVIDECLASSINFO2, "TRUE")]
	public IProvideClassInfo2Impl<&CLSID_[!CoClassName], [!ConnectionPointInterface], &LIBID_[!LibName]>,
[!endif]
[!endif]
	public CComCoClass<[!ClassName], &CLSID_[!CoClassName]>
{
public:
[!if!=(SubclassWindow, "")]
	CContainedWindow m_ctl[!SubclassWindowSymbol];
	[!crlf]
[!endif]

	[!ClassName]()[!if!=(SubclassWindow, "")] :	
		m_ctl[!SubclassWindowSymbol](_T("[!SubclassWindow]"), this, 1)[!endif]
	{
[!if=(FreeThreadedMarshaler, "TRUE")]
		m_pUnkMarshaler = NULL;
[!endif]
[!if!=(SubclassWindow, "")]
[!set(WindowedOnlyEnabled,"TRUE")]
[!endif]
[!if=(WindowedOnlyEnabled, "TRUE")]
		m_bWindowOnly = TRUE;
[!endif]
[!if=(CompositeControl, "TRUE")]
		CalcExtent(m_sizeExtent);
[!endif]
	}
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
	COM_INTERFACE_ENTRY([!InterfaceName])
[!if=(HTMLControl, "TRUE")]
	COM_INTERFACE_ENTRY([!InterfaceName]UI)
[!endif]
[!if=(Dual, "TRUE")]
[!if=(HTMLControl, "TRUE")]
	COM_INTERFACE_ENTRY2(IDispatch, [!InterfaceName])
[!else]
	COM_INTERFACE_ENTRY(IDispatch)
[!endif]
[!else]
[!if=(HTMLControl, "TRUE")]
	COM_INTERFACE_ENTRY(IDispatch)
[!endif]
[!endif]
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
[!if=(ErrorInfoEnabled, "TRUE")]
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
[!endif]
[!if=(ConnectionPointsEnabled, "TRUE")]
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
[!endif]

[!if=(ISPECIFYPROPERTYPAGES, "TRUE")]
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
[!endif]
[!if=(IQUICKACTIVATE, "TRUE")]
	COM_INTERFACE_ENTRY(IQuickActivate)
[!endif]
[!if=(IPERSISTSTORAGE, "TRUE")]
	COM_INTERFACE_ENTRY(IPersistStorage)
[!endif]
[!if=(IDATAOBJECT, "TRUE")]
	COM_INTERFACE_ENTRY(IDataObject)
[!endif]
[!if=(IPROVIDECLASSINFO2, "TRUE")]
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
[!endif]
[!if=(IOBJECTWITHSITE, "TRUE")]
	COM_INTERFACE_ENTRY(IObjectWithSite)
[!endif]
[!if=(ISERVICEPROVIDER, "TRUE")]
	COM_INTERFACE_ENTRY(IServiceProvider)
[!endif]

[!if=(FreeThreadedMarshaler, "TRUE")]
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
[!endif]
END_COM_MAP()

[!crlf]
BEGIN_PROP_MAP([!ClassName])
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
[!if=(SP_APPEARANCE, "TRUE")]	PROP_ENTRY("Appearance", DISPID_APPEARANCE, CLSID_NULL)[!endif]
[!if=(SP_AUTOSIZE, "TRUE")]	PROP_ENTRY("AutoSize", DISPID_AUTOSIZE, CLSID_NULL)[!endif]
[!if=(SP_BACKCOLOR, "TRUE")]	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)[!endif]
[!if=(SP_BACKSTYLE, "TRUE")]	PROP_ENTRY("BackStyle", DISPID_BACKSTYLE, CLSID_NULL)[!endif]
[!if=(SP_BORDERCOLOR, "TRUE")]	PROP_ENTRY("BorderColor", DISPID_BORDERCOLOR, CLSID_StockColorPage)[!endif]
[!if=(SP_BORDERSTYLE, "TRUE")]	PROP_ENTRY("BorderStyle", DISPID_BORDERSTYLE, CLSID_NULL)[!endif]
[!if=(SP_BORDERVISIBLE, "TRUE")]	PROP_ENTRY("BorderVisible", DISPID_BORDERVISIBLE, CLSID_NULL)[!endif]
[!if=(SP_BORDERWIDTH, "TRUE")]	PROP_ENTRY("BorderWidth", DISPID_BORDERWIDTH, CLSID_NULL)[!endif]
[!if=(SP_CAPTION, "TRUE")]	PROP_ENTRY("Caption", DISPID_CAPTION, CLSID_NULL)[!endif]
[!if=(SP_DRAWMODE, "TRUE")]	PROP_ENTRY("DrawMode", DISPID_DRAWMODE, CLSID_NULL)[!endif]
[!if=(SP_DRAWSTYLE, "TRUE")]	PROP_ENTRY("DrawStyle", DISPID_DRAWSTYLE, CLSID_NULL)[!endif]
[!if=(SP_DRAWWIDTH, "TRUE")]	PROP_ENTRY("DrawWidth", DISPID_DRAWWIDTH, CLSID_NULL)[!endif]
[!if=(SP_ENABLED, "TRUE")]	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)[!endif]
[!if=(SP_FILLCOLOR, "TRUE")]	PROP_ENTRY("FillColor", DISPID_FILLCOLOR, CLSID_StockColorPage)[!endif]
[!if=(SP_FILLSTYLE, "TRUE")]	PROP_ENTRY("FillStyle", DISPID_FILLSTYLE, CLSID_NULL)[!endif]
[!if=(SP_FONT, "TRUE")]	PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)[!endif]
[!if=(SP_FORECOLOR, "TRUE")]	PROP_ENTRY("ForeColor", DISPID_FORECOLOR, CLSID_StockColorPage)[!endif]
[!if=(SP_HWND, "TRUE")]	PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL)[!endif]
[!if=(SP_MOUSEICON, "TRUE")]	PROP_ENTRY("MouseIcon", DISPID_MOUSEICON, CLSID_StockPicturePage)[!endif]
[!if=(SP_MOUSEPOINTER, "TRUE")]	PROP_ENTRY("MousePointer", DISPID_MOUSEPOINTER, CLSID_NULL)[!endif]
[!if=(SP_PICTURE, "TRUE")]	PROP_ENTRY("Picture", DISPID_PICTURE, CLSID_StockPicturePage)[!endif]
[!if=(SP_READYSTATE, "TRUE")]	PROP_ENTRY("ReadyState", DISPID_READYSTATE, CLSID_NULL)[!endif]
[!if=(SP_TABSTOP, "TRUE")]	PROP_ENTRY("TabStop", DISPID_TABSTOP, CLSID_NULL)[!endif]
[!if=(SP_TEXT, "TRUE")]	PROP_ENTRY("Text", DISPID_TEXT, CLSID_NULL)[!endif]
[!if=(SP_VALID, "TRUE")]	PROP_ENTRY("Valid", DISPID_VALID, CLSID_NULL)[!endif]
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()
[!crlf]

[!if=(ConnectionPointsEnabled, "TRUE")]
BEGIN_CONNECTION_POINT_MAP([!ClassName])
[!if=(IPROPERTYNOTIFYSINK, "TRUE")]
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
[!endif]
END_CONNECTION_POINT_MAP()
[!crlf]
[!endif]

BEGIN_MSG_MAP([!ClassName])
[!if=(HTMLControl, "TRUE")]
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
[!endif]
[!if!=(SubclassWindow, "")]
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
[!if=(SubclassWindow, "RichEdit")]
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
[!endif]
[!endif]
[!if=(CompositeControl, "TRUE")]
	CHAIN_MSG_MAP(CComCompositeControl<[!ClassName]>)
[!else]
	CHAIN_MSG_MAP(CComControl<[!ClassName]>)
[!endif]
[!if!=(SubclassWindow, "")]
ALT_MSG_MAP(1)
	// Replace this with message map entries for superclassed [!SubclassWindow]
[!endif]
[!if=(SubclassWindow, "")]
[!if!(CompositeControl)]
	DEFAULT_REFLECTION_HANDLER()
[!endif]
[!endif]
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

[!if=(CompositeControl, "TRUE")]
[!crlf]
BEGIN_SINK_MAP([!ClassName])
	//Make sure the Event Handlers have __stdcall calling convention
END_SINK_MAP()
[!crlf]

	STDMETHOD(OnAmbientPropertyChange)(DISPID dispid)
	{
		if (dispid == DISPID_AMBIENT_BACKCOLOR)
		{
			SetBackgroundColorFromAmbient();
			FireViewChange();
		}
		return IOleControlImpl<[!ClassName]>::OnAmbientPropertyChange(dispid);
	}

[!endif]
[!crlf]
[!if=(UseArrowKeys, "TRUE")]
	BOOL PreTranslateAccelerator(LPMSG pMsg, HRESULT& hRet)
	{
		if(pMsg->message == WM_KEYDOWN && 
			(pMsg->wParam == VK_LEFT || 
			pMsg->wParam == VK_RIGHT ||
			pMsg->wParam == VK_UP ||
			pMsg->wParam == VK_DOWN))
		{
			hRet = S_FALSE;
			return TRUE;
		}
		//TODO: Add your additional accelerator handling code here
		return FALSE;
	}
[!endif]

[!crlf]
[!if!=(SubclassWindow, "")]
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = CComControl<[!ClassName]>::OnSetFocus(uMsg, wParam, lParam, bHandled);
		if (m_bInPlaceActive)
		{
			DoVerbUIActivate(&m_rcPos,  NULL);
			if(!IsChild(::GetFocus()))
				m_ctl[!SubclassWindowSymbol].SetFocus();
		}
		return lRes;
	}
[!if=(SubclassWindow, "RichEdit")]
[!crlf]
	HINSTANCE m_hLibRichEdit;
[!endif]
[!crlf]
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		RECT rc;
		GetWindowRect(&rc);
		rc.right -= rc.left;
		rc.bottom -= rc.top;
		rc.top = rc.left = 0;
[!if=(UseCommonControls, "TRUE")]		InitCommonControls();[!endif]
[!if=(SubclassWindow, "RichEdit")]		m_hLibRichEdit = LoadLibrary(_T("RICHED32.DLL"));[!endif]
		m_ctl[!SubclassWindowSymbol].Create(m_hWnd, rc);
		return 0;
	}
[!if=(SubclassWindow, "RichEdit")]
	LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL&)
	{
		m_ctl[!SubclassWindowSymbol].DestroyWindow();
		FreeLibrary(m_hLibRichEdit);
		return 0;
	}
[!endif]
	STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip)
	{
		IOleInPlaceObjectWindowlessImpl<[!ClassName]>::SetObjectRects(prcPos, prcClip);
		int cx, cy;
		cx = prcPos->right - prcPos->left;
		cy = prcPos->bottom - prcPos->top;
		::SetWindowPos(m_ctl[!SubclassWindowSymbol].m_hWnd, NULL, 0,
			0, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);
		return S_OK;
	}
[!endif]

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

[!if=(ErrorInfoEnabled, "TRUE")]
[!crlf]
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_[!InterfaceName],
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}
[!endif]
[!crlf]
// IViewObjectEx
[!if=(Opaque, "TRUE")]
[!if=(SolidBackground, "TRUE")]
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)
[!else]
	DECLARE_VIEW_STATUS(VIEWSTATUS_OPAQUE)
[!endif]
[!else]
	DECLARE_VIEW_STATUS(0)
[!endif]
[!crlf]
// [!InterfaceName]
public:
[!if!(HTMLControl)]
[!if!(CompositeControl)]
[!if=(SubclassWindow, "")]

[!if=(NormalizeDCEnabled, "TRUE")]
[!crlf]
	HRESULT OnDraw(ATL_DRAWINFO& di)
[!else]
[!crlf]
	HRESULT OnDrawAdvanced(ATL_DRAWINFO& di)
[!endif]
	{
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
[!crlf]
		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("ATL 3.0 : [!ShortName]");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));
[!crlf]
		return S_OK;
	}

[!endif]
[!endif]
[!endif]

[!if=(SP_APPEARANCE, "TRUE")]	short m_nAppearance;[!endif]
[!if=(SP_BACKCOLOR, "TRUE")]	OLE_COLOR m_clrBackColor;[!endif]
[!if=(SP_BACKSTYLE, "TRUE")]	LONG m_nBackStyle;[!endif]
[!if=(SP_BORDERCOLOR, "TRUE")]	OLE_COLOR m_clrBorderColor;[!endif]
[!if=(SP_BORDERSTYLE, "TRUE")]	LONG m_nBorderStyle;[!endif]
[!if=(SP_BORDERVISIBLE, "TRUE")]	BOOL m_bBorderVisible;[!endif]
[!if=(SP_BORDERWIDTH, "TRUE")]	LONG m_nBorderWidth;[!endif]
[!if=(SP_CAPTION, "TRUE")]	CComBSTR m_bstrCaption;[!endif]
[!if=(SP_DRAWMODE, "TRUE")]	LONG m_nDrawMode;[!endif]
[!if=(SP_DRAWSTYLE, "TRUE")]	LONG m_nDrawStyle;[!endif]
[!if=(SP_DRAWWIDTH, "TRUE")]	LONG m_nDrawWidth;[!endif]
[!if=(SP_ENABLED, "TRUE")]	BOOL m_bEnabled;[!endif]
[!if=(SP_FILLCOLOR, "TRUE")]	OLE_COLOR m_clrFillColor;[!endif]
[!if=(SP_FILLSTYLE, "TRUE")]	LONG m_nFillStyle;[!endif]
[!if=(SP_FONT, "TRUE")]	CComPtr<IFontDisp> m_pFont;[!endif]
[!if=(SP_FORECOLOR, "TRUE")]	OLE_COLOR m_clrForeColor;[!endif]
[!if=(SP_MOUSEICON, "TRUE")]	CComPtr<IPictureDisp> m_pMouseIcon;[!endif]
[!if=(SP_MOUSEPOINTER, "TRUE")]	LONG m_nMousePointer;[!endif]
[!if=(SP_PICTURE, "TRUE")]	CComPtr<IPictureDisp> m_pPicture;[!endif]
[!if=(SP_READYSTATE, "TRUE")]	LONG m_nReadyState;[!endif]
[!if=(SP_TABSTOP, "TRUE")]	BOOL m_bTabStop;[!endif]
[!if=(SP_TEXT, "TRUE")]	CComBSTR m_bstrText;[!endif]
[!if=(SP_VALID, "TRUE")]	BOOL m_bValid;[!endif]

[!if=(CompositeControl, "TRUE")]
[!crlf]
	enum { IDD = [!IDD_DIALOGID] };
[!endif]
[!if=(HTMLControl, "TRUE")]
[!crlf]
// [!InterfaceName]UI
public:
	// Example method called by the HTML to change the <BODY> background color
	STDMETHOD(OnClick)(IDispatch* pdispBody, VARIANT varColor)
	{
		CComQIPtr<IHTMLBodyElement> spBody(pdispBody);
		if (spBody != NULL)
			spBody->put_bgColor(varColor);
		return S_OK;
	}

[!crlf]
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CAxWindow wnd(m_hWnd);
		HRESULT hr = wnd.CreateControl([!IDH_HTMLID]);
		if (SUCCEEDED(hr))
			hr = wnd.SetExternalDispatch(static_cast<[!InterfaceName]UI*>(this));
		if (SUCCEEDED(hr))
			hr = wnd.QueryControl(IID_IWebBrowser2, (void**)&m_spBrowser);
		return SUCCEEDED(hr) ? 0 : -1;
	}
[!if=(ISERVICEPROVIDER, "TRUE")]
[!crlf]
	STDMETHOD(_InternalQueryService)(REFGUID guidService, REFIID riid, void** ppvObject)
	{
		return E_NOTIMPL;
	}
[!endif]
[!crlf]
	CComPtr<IWebBrowser2> m_spBrowser;
[!endif]

};

[!crlf]
[!if=(FileExists, "FALSE")]
#endif //__[!UpperShortName]_H_
[!endif]
