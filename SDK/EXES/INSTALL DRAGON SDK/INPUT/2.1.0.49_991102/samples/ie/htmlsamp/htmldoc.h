#ifndef __HTMLDOC_H             // guard against multiple inclusion
#define __HTMLDOC_H

/********************************************************************
 * htmldoc.h
 *
 * Description
 *    CHTMLDoc
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "window.h"             // base class CWindow
#include "dialer.h"             // CDialer
#include <mshtmhst.h>           // IHTMLDocument2, IHTMLElement, etc.
#include <objbase.h>            // OLE
#include <exdisp.h>             // DWebBrowserEvents2
#include <exdispid.h>           // DISPID_* for DWebBrowserEvents2 

/********************************************************************
 * Forward declarations
 ********************************************************************/
class CStatusBar;               // status.h
class CStatusBitmap;            // statbmp.h
class CStatusAnimated;          // statanim.h
class CTitleBar;                // titlebar.h
class CToolBar;                 // toolbar.h

/********************************************************************
 * class CHTMLDoc
 *
 * Description
 *    Class for the container for the HTML control. It handles all of
 *    the communication between the control and the application by
 *    implementing certain interfaces (see HTML control documentation
 *    online on in MSDN) in this container and using certain 
 *    interfaces in the control.
 ********************************************************************/
class CHTMLDoc : public CWindow,
                 public IOleContainer,
                 public IOleClientSite,
                 public IOleInPlaceSite,
                 public IOleCommandTarget,
                 public DWebBrowserEvents2
{
    public:
        // Constructor/Destructor
        CHTMLDoc(HWND hwndParent, WORD x, WORD y, WORD w, WORD h, CStatusBar *pStatus, CTitleBar *pTitle, CToolBar *pToolBar, CStatusBitmap *pSecurityStatus, CStatusAnimated *pLogoStatus);
        virtual ~CHTMLDoc(void);
     
        // Public functions
        HRESULT PreTranslateMessage(MSG *pMsg);
        void    ShutDown(BOOL bFinal);
        void    CheckConnection(BOOL bDontAllowDisconnect);
        void    DoActivation(BOOL bActivate);
        HRESULT NavigateTo(LPTSTR pszURL);
        HWND    GetHWND(void);
        HRESULT ShowURLGotoDialog(void);

        // CWindow overrides
        HRESULT Draw(LPDIRECTDRAWSURFACE pDDS, LPDIRECTDRAWSURFACE pDDSTexture);
        HRESULT Joystick(DWORD dwButtons, DWORD dwButtonsHeld, WORD x, WORD y);
        HRESULT Command(WORD nCommand);

        // IUnknown methods
        STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppvObj);
        STDMETHOD_(ULONG, AddRef)(void);
        STDMETHOD_(ULONG, Release)(void);

        // IOleContainer methods
        STDMETHOD(ParseDisplayName)(IBindCtx *, LPOLESTR, ULONG *, IMoniker **);
        STDMETHOD(EnumObjects)(DWORD, IEnumUnknown **);
        STDMETHOD(LockContainer)(BOOL);

        // IOleClientSite methods
        STDMETHOD(SaveObject)(void);
        STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, LPMONIKER *ppmk);
        STDMETHOD(GetContainer)(LPOLECONTAINER *ppContainer);
        STDMETHOD(ShowObject)(void);
        STDMETHOD(OnShowWindow)(BOOL fShow);
        STDMETHOD(RequestNewObjectLayout)(void);

        // IOleWindow methods
        STDMETHOD(GetWindow)(HWND *pHhwnd);
        STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode);

        // IOleInPlaceSite
        STDMETHOD(CanInPlaceActivate)(void);
        STDMETHOD(OnInPlaceActivate)(void);
        STDMETHOD(OnUIActivate)(void);
        STDMETHOD(GetWindowContext)(LPOLEINPLACEFRAME *ppFrame, 
                                    LPOLEINPLACEUIWINDOW *ppDoc, LPRECT prcPosRect,
                                    LPRECT prcClipRect, 
                                    LPOLEINPLACEFRAMEINFO pFrameInfo);
        STDMETHOD(Scroll)(SIZE scrollExtent);
        STDMETHOD(OnUIDeactivate)(BOOL fUndoable);
        STDMETHOD(OnInPlaceDeactivate)(void);
        STDMETHOD(DiscardUndoState)(void);
        STDMETHOD(DeactivateAndUndo)(void);
        STDMETHOD(OnPosRectChange)(LPCRECT prcPosRect);

        // IOleCommandTarget methods
        STDMETHOD(QueryStatus)(const GUID *pguidCmdGroup, ULONG cCmds, MSOCMD rgCmds[],
                               MSOCMDTEXT *pcmdtext);
        STDMETHOD(Exec)(const GUID *pguidCmdGroup, DWORD nCmdID, DWORD nCmdexecopt,
                        VARIANTARG *pvarargIn, VARIANTARG *pvarargOut);

        // DWebBrowserEvents2
        // IDispatch methods
        STDMETHOD(GetTypeInfoCount)(UINT *pctinfo);
        STDMETHOD(GetTypeInfo)(UINT itinfo,LCID lcid,ITypeInfo **pptinfo);
        STDMETHOD(GetIDsOfNames)(REFIID riid,OLECHAR **rgszNames, UINT cNames,
                  LCID lcid, DISPID FAR* rgdispid);
        STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags,
                          DISPPARAMS *pdispparams, VARIANT *pvarResult, 
                          EXCEPINFO *pexcepinfo, UINT *puArgErr);
    private:
        // Internal functions
        HRESULT InitEvents(void);

        HRESULT StopNavigation(void);
        HRESULT RefreshPage(void);
        HRESULT StopOrHome(void);
        HRESULT GoBack(void);
        HRESULT GoForward(void);
        HRESULT CheckConnection(void);

        HRESULT GetActiveElement(IHTMLElement **ppElement);
        HRESULT DoInputIME(IHTMLElement *pElement, REFIID iid);

        // Internal static functions
        static  LRESULT CALLBACK WndProc(HWND hwnd, UINT wm, WPARAM wParam, LPARAM lParam);
     
    private:
        ULONG                   _ulRefs;                        // reference count of object
        HWND                    _hwnd;                          // window handle of HTML control
        HWND                    _hwndParent;                    // window handle of parent container
        BOOL                    _bInPlaceActive;                // flag for has been activated
        CStatusBar *            _pStatus;                       // status bar to display text
        CTitleBar *             _pTitle;                        // title bar to display text
        CToolBar *              _pToolBar;                      // tool bar of commands
        CStatusBitmap *         _pSecurityStatus;               // status bitmap to display secrurity
        CStatusAnimated *       _pLogoStatus;                   // status animated to display downloading
        IWebBrowser2 *          _pWebBrowser2;                  // web browser (main interface for control)
        IOleObject *            _pOleObject;                    // IOleObject interface of _pWebBrowser2
        IOleInPlaceActiveObject*_pOleInPlaceActiveObject;       // IOleInPlaceActiveObject iface of _pWebBrowser2
        IConnectionPoint *      _pConnectionPoint;              // connection point for _pWebBrowser2
        DWORD                   _dwEventCookie;                 // cookie for registered connection point
        CDialer *               _pDialer;                       // RAS connection object
        DWORD                   _dwDisconnectIdleTime;          // amount of idle time before disconnecting
        DWORD                   _dwTimeToDisconnect;            // disconnect time if still idle
        BOOL                    _bLastURLRemote;                // flag for whether last URL was local
        BSTR                    _bstrLastTypedURL;              // last URL typed into go to url dialog
};

#endif // __HTMLDOC_H
