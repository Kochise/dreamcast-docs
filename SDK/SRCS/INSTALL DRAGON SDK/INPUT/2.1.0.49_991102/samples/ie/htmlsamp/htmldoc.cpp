/********************************************************************
 * htmldoc.cpp
 *
 * Description
 *    CHTMLDoc - class that handles the display and input of HTML
 *    documents. It also does all the work required to host the HTML
 *    control.
 *    See MSDN or online documentation for additional information 
 *    on interfaces implemented in this object.
 *    Many functions in the interfaces do not have to be implemented.
 *    In some cases, none of the functions in an interface are 
 *    implemented, but the interface must still be available. You may
 *    want to implement some of the functions not implemented in this 
 *    sample depending on how you want things to work.
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include "htmldoc.h"            // CHTMLDoc
#include "editbox.h"            // TKIME edit box
#include "status.h"             // CStatusBar
#include "titlebar.h"           // CTitleBar
#include "toolbar.h"            // CToolBar
#include "statanim.h"           // CStatusAnimated
#include "external.h"           // wrapper prototypes
#include <perhist.h>            // mshtml history
#include <keybd.h>              // keyboard scan codes
#include <mshtmdid.h>           // mshtml dispatch IDs
#ifdef USE_FLASH
#include "flashapi.h"           // MM Flash
#endif // USE_FLASH

#ifdef GAME_SAMPLE
#include "memstm.h"             // CMemoryStream
#endif // GAME_SAMPLE

/********************************************************************
 * Defines - URLs
 ********************************************************************/
#define PAGE_BLANK          TEXT("about:blank")
#define PAGE_HOME           TEXT("http://hpux.microsoft.com/wince4dc/")
#ifdef KANJI
#define PAGE_SEARCH         TEXT("http://search.microsoft.com/japan")
#else  // KANJI
#define PAGE_SEARCH         TEXT("http://search.microsoft.com/")
#endif // KANJI
#define PAGE_DIALER         TEXT("res://reshelp.dll/dialer.htm")
#define PAGE_HELP           TEXT("res://reshelp.dll/toc.htm")
#define PAGE_GOTOURL        TEXT("res://reshelp.dll/gotourl.dlg")

/********************************************************************
 * Macros
 ********************************************************************/
#define ISREMOTEFILE(pszURL)  (_tcsnicmp(pszURL, TEXT("res:"),         4) != 0   \
                            && _tcsnicmp(pszURL, TEXT("x-avefront:"), 10) != 0   \
                            && _tcsnicmp(pszURL, TEXT("file:"),        5) != 0   \
                            && _tcsnicmp(pszURL, TEXT("mailto:"),      7) != 0   \
                            && _tcsnicmp(pszURL, TEXT("about:"),       6) != 0)

/********************************************************************
 * Global variables
 ********************************************************************/
#ifdef GAME_SAMPLE
CMemoryStream *g_pLastSite        = NULL;       // page displayed right
                                                // before user hides
                                                // HTML window
BSTR           g_bstrLastTypedURL = NULL;       // URL last typed by user
                                                // before user hides
                                                // HTML window
#endif // GAME_SAMPLE

/********************************************************************
 * CHTMLDoc::CHTMLDoc
 *
 * Description
 *    Constructor. Initializes internal data and the window. Creates
 *    the HTML control and gets needed interfaces from the control.
 *    Activates the control and initializes event notification.
 *
 * Parameters
 *    hwndParent       main application window
 *    x		       left position of window
 *    y                top position of window
 *    w                width of window
 *    h                height of window
 *    pStatus          status bar for HTML control
 *    pTitleBar        title bar for HTML control 
 *    pToolBar         tool bar for HTML control commands
 *    pSecurityStatus  bitmap status bar for HTML control security 
 *                     icon (https page)
 *    pLogoStatus      bitmap status bar that "spins" when HTML 
 *                     control is downloading a page
 * 
 * Returns
 *    N/A
 ********************************************************************/
CHTMLDoc::CHTMLDoc(HWND hwndParent, WORD x, WORD y, WORD w, WORD h, 
                   CStatusBar *pStatus, CTitleBar *pTitle, 
                   CToolBar *pToolBar, CStatusBitmap *pSecurityStatus, 
                   CStatusAnimated *pLogoStatus)
         :CWindow(x, y, w, h)
{
    // initialize internal data
    _hwnd                   = NULL;
    _hwndParent             = hwndParent;
    _ulRefs                 = 1;
    _pStatus                = pStatus;
    _pTitle                 = pTitle;
    _pToolBar               = pToolBar;
    _pSecurityStatus        = pSecurityStatus;
    _pLogoStatus            = pLogoStatus;
    _pWebBrowser2           = NULL;
    _pOleObject             = NULL;
    _pOleInPlaceActiveObject= NULL;
    _pConnectionPoint       = NULL;
    _dwEventCookie          = 0;
    _pDialer                = new CDialer();
    _dwDisconnectIdleTime   = 0;
    _dwTimeToDisconnect     = 0;
    _bLastURLRemote         = FALSE;
    _bstrLastTypedURL       = NULL;

    // get idle time information
    HKEY hModemKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                     TEXT("Modem"),
                     0,
                     KEY_READ,
                     &hModemKey) == ERROR_SUCCESS)
    {
        DWORD dwSize = sizeof(_dwDisconnectIdleTime);
        RegQueryValueEx(hModemKey,
                        TEXT("DisconnectIdleTime"),
                        NULL,
                        NULL,
                        (LPBYTE)&_dwDisconnectIdleTime,
                        &dwSize);
        RegCloseKey(hModemKey);
    }

#ifndef GAME_SAMPLE
    SetCursorType(CURSOR_HTML);
#endif // GAME_SAMPLE

    IUnknown *pUnk = NULL;

    // create HTML control
    if (SUCCEEDED(CoCreateInstance(CLSID_WebBrowser, NULL, 
                                   CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER,
                                   IID_IUnknown, (LPVOID *)&pUnk)))
    {
        // get useful interfaces from the control
        if (SUCCEEDED(pUnk->QueryInterface(IID_IOleObject, 
                                           (LPVOID *)&_pOleObject)))
        {
            DWORD dwFlags;
            if (SUCCEEDED(_pOleObject->GetMiscStatus(DVASPECT_CONTENT, &dwFlags)))
            {
                if (dwFlags & OLEMISC_SETCLIENTSITEFIRST)
                {
                    IOleClientSite *pClientSite;
                    if (SUCCEEDED(QueryInterface(IID_IOleClientSite, 
                                                 (LPVOID *)&pClientSite)))
                    {
                        _pOleObject->SetClientSite(pClientSite);
                        pClientSite->Release();
                    }
                }
            }
     
            // activate the control
            if (SUCCEEDED(_pOleObject->DoVerb(OLEIVERB_UIACTIVATE, NULL, this, 
                                              0, _hwndParent, &_rc)))
            {
                BOOL bLoadDefault = TRUE;

                if (SUCCEEDED(_pOleObject->QueryInterface(IID_IWebBrowser2, 
                                                          (LPVOID *)&_pWebBrowser2)))
                {
#ifdef GAME_SAMPLE
                    // if the control has been shown and hidden before, load up the
                    // control with the previous page
                    if (g_pLastSite)
                    {
                        IPersistHistory *pph = NULL;
                        if (SUCCEEDED(_pOleObject->QueryInterface(IID_IPersistHistory, 
                                                                  (LPVOID *)&pph)))
                        {
                            IStream *pStream;
                            if (SUCCEEDED(g_pLastSite->Clone(&pStream)))
                            {
                                if (SUCCEEDED(pph->LoadHistory(pStream, NULL)))
                                {
                                    bLoadDefault = FALSE;
                                }
                                pStream->Release();
                            }

                            pph->Release();
                        }
                        g_pLastSite->Release();
                        g_pLastSite = NULL;
                    }

                    // if the control has been shown and hidden before, remember the
                    // last typed URL from earlier
                    if (g_bstrLastTypedURL)
                    {
                        if (!bLoadDefault)
                        {
                            _bstrLastTypedURL = g_bstrLastTypedURL;
                        }
                        else
                        {
                            SysFreeString(g_bstrLastTypedURL);
                        }
                        g_bstrLastTypedURL = NULL;    
                     }
#endif // GAME_SAMPLE

                    // if not loading from history, load up intro page                    
                    if (bLoadDefault)
                    {
                        _bstrLastTypedURL = SysAllocString(PAGE_BLANK);
                        NavigateTo(_pDialer->IsInit() == S_OK ? PAGE_BLANK : PAGE_DIALER);
                    }
                }
            }

            // initialize events 
            InitEvents();
        }

        pUnk->QueryInterface(IID_IOleInPlaceActiveObject, 
                             (LPVOID *)&_pOleInPlaceActiveObject);

        pUnk->Release();
    }

    // get HWND of HTML control
    if (_pWebBrowser2)
    {
        IOleWindow *pOleWindow = NULL;
        if (SUCCEEDED(_pWebBrowser2->QueryInterface(IID_IOleWindow, 
                                                    (LPVOID *)&pOleWindow)))
        {
            pOleWindow->GetWindow(&_hwnd);
            pOleWindow->Release();
        }
    }

    // put borders on the control window
    if (_hwnd)
    {
        SetWindowLong(_hwnd, GWL_EXSTYLE, GetWindowLong(_hwnd, 
                      GWL_EXSTYLE) | WS_EX_CLIENTEDGE);
        SetFocus(_hwnd);
    }
}

/********************************************************************
 * CHTMLDoc::~CHTMLDoc
 *
 * Description
 *    Destructor. Destroys allocated data.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    N/A
 ********************************************************************/
CHTMLDoc::~CHTMLDoc(void)
{
    // everything else should be taken care of in ShutDown
    if (_bstrLastTypedURL) 
    {
        SysFreeString(_bstrLastTypedURL);
        _bstrLastTypedURL = NULL;
    }
}

/********************************************************************
 * CHTMLDoc::ShutDown
 *
 * Description
 *    Uninitializes the HTML control and saves off some data (current
 *    page, last typed URL) in case control is re-created. 
 *
 * Parameters
 *    bFinal   TRUE  if the application is shutting down
 *             FALSE if only the control is shutting down
 * 
 * Returns
 *    None
 ********************************************************************/
void CHTMLDoc::ShutDown(BOOL bFinal)
{
    // release interfaces that are no longer needed
    if (_pOleInPlaceActiveObject)
    {
        _pOleInPlaceActiveObject->Release();
        _pOleInPlaceActiveObject = NULL;
    }

    // stop event notification
    if (_pConnectionPoint)
    {
        _pConnectionPoint->Unadvise(_dwEventCookie);
        _pConnectionPoint->Release();
        _pConnectionPoint = NULL;
    }

#ifdef GAME_SAMPLE
    // on application shutdown, get rid of global variables
    if (bFinal && g_pLastSite)
    {
        g_pLastSite->Release();
        g_pLastSite = NULL;
    }
    if (bFinal && g_bstrLastTypedURL)
    {
        SysFreeString(g_bstrLastTypedURL);
        g_bstrLastTypedURL = NULL;   
    }
#endif // GAME_SAMPLE

    if (_pOleObject)
    {
#ifdef GAME_SAMPLE
        // on object shutdown, save current page in memory stream in case 
        // HTML control is re-shown
        if (!bFinal)
        {
            if (!g_pLastSite)
            {
                g_pLastSite = new CMemoryStream;
            }
 
            if (g_pLastSite)
            {
                IPersistHistory *pph;
                if (SUCCEEDED(_pOleObject->QueryInterface(IID_IPersistHistory, 
                              (LPVOID *)&pph)))
                {
                    pph->SaveHistory(g_pLastSite);
                }
                else
                {
                    OutputDebugString(TEXT("Didnt save history\n"));
                }

                pph->Release();
            }

            g_bstrLastTypedURL = _bstrLastTypedURL;
            _bstrLastTypedURL = NULL;
        }
#endif GAME_SAMPLE
 
        // close HTML control
        _pOleObject->Close(OLECLOSE_NOSAVE);
        _pOleObject->Release();
        _pOleObject = NULL;
    }

    // close browser control
    if (_pWebBrowser2)
    {
        _pWebBrowser2->Quit(); 
        _pWebBrowser2->Release();
        _pWebBrowser2 = NULL;
    }

    // destroy dialer
    if (_pDialer)
    {
        delete _pDialer;
        _pDialer = NULL;
    }

    // destroy window if needed
    if (_hwnd && IsWindow(_hwnd))
    {
        DestroyWindow(_hwnd);
    }
    _hwnd = NULL;
}

/********************************************************************
 * CHTMLDoc::CheckConnection
 *
 * Description
 *    Checks for user having been idle for specified time and
 *    disconnects RAS connection if needed.
 *
 * Parameters
 *    bDontAllowDisconnect TRUE  if it should just increase disconnect
 *                               time and not actually disconnect now
 *                         FALSE if it should disconnect as soon as
 *                               idle time is reached
 * 
 * Returns
 *    None
 ********************************************************************/
void CHTMLDoc::CheckConnection(BOOL bDontAllowDisconnect)
{
    // don't bother if infinite time out
    if (_dwDisconnectIdleTime && _pDialer)
    {
        // if busy, dont allow disconnect by increasing next check time
        if (bDontAllowDisconnect)
        {
            DWORD dwNow = GetTickCount();
            if ((dwNow > _dwTimeToDisconnect) || 
                ((_dwTimeToDisconnect - dwNow) < 5000))
            {
                _dwTimeToDisconnect = dwNow + 10000;
            }
        }
        else
        {
            // if been idle for required time, disconnect
            if ((GetTickCount() > _dwTimeToDisconnect) && 
                (_pDialer->IsConnect() == S_OK))
            {
                _pDialer->HangUp();
                _dwTimeToDisconnect = 0;
                _pToolBar->ChangeButton(ID_DISCONNECT, 9, ID_CONNECT, 8);
            }
        }
    }
}

/********************************************************************
 * CHTMLDoc::DoActivation
 *
 * Description
 *    Activates or deactivates HTML control (when window gets focus,
 *    it should be activated to ensure focus rectangle is displayed).
 *
 * Parameters
 *    bActivate    TRUE  if time to activate object
 *                 FALSE if time to deactivate object
 * 
 * Returns
 *    None
 ********************************************************************/
void CHTMLDoc::DoActivation(BOOL bActivate)
{
    if (_pOleInPlaceActiveObject)
    {
        _pOleInPlaceActiveObject->OnFrameWindowActivate(bActivate);    
    }
}

/********************************************************************
 * CHTMLDoc::PreTranslateMessage
 *
 * Description
 *    Allows HTML control a chance to proces keyboard messages.
 *
 * Parameters
 *    pMsg     current message queue message
 * 
 * Returns
 *    S_OK     message handled by HTML control
 *    S_FALSE  message should be handled as normal in message loop
 ********************************************************************/
HRESULT CHTMLDoc::PreTranslateMessage(MSG *pMsg)
{
    // check if message is for HTML control
    if ((pMsg->hwnd == _hwnd) || IsChild(_hwnd, pMsg->hwnd))
    {
        // check if message is keyboard message
        if ((WM_KEYFIRST <= pMsg->message) && (pMsg->message <= WM_KEYLAST) && 
            _pOleInPlaceActiveObject)
        {
            // allow HTML control to handle message
            return _pOleInPlaceActiveObject->TranslateAccelerator(pMsg);
        }
    }

    return S_FALSE;
}

/********************************************************************
 * CHTMLDoc::InitEvents
 *
 * Description
 *    Requests that the HTML control notify the container when certain
 *    events occur.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK     notification request initialization successful
 *    S_FALSE  notification request failed
 *    other    internal error
 ********************************************************************/
HRESULT CHTMLDoc::InitEvents(void)
{
    IConnectionPointContainer  *pCPC = NULL;
    HRESULT hr = S_FALSE;

    // get connection point container
    if (!_pWebBrowser2 || 
        FAILED(_pWebBrowser2->QueryInterface(IID_IConnectionPointContainer, 
                                             (LPVOID *)&pCPC)))
    {
        return hr;
    }

    // find desired connection point
    if (SUCCEEDED(pCPC->FindConnectionPoint(DIID_DWebBrowserEvents2, 
                  &_pConnectionPoint)))
    {
        DWebBrowserEvents *pEvents;
        if (SUCCEEDED(QueryInterface(DIID_DWebBrowserEvents2, (LPVOID *)&pEvents)))
        {
            // request notification of events
            hr = _pConnectionPoint->Advise(pEvents, &_dwEventCookie);
            pEvents->Release();
        }
    }

    pCPC->Release();

    return hr;
}

/********************************************************************
 * CHTMLDoc::StopNavigation
 *
 * Description
 *    Stops navigation, animation, etc. of current web page.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    result of webbrowser stop request
 *    E_FAIL    internal error
 ********************************************************************/
HRESULT CHTMLDoc::StopNavigation(void)
{
    // validate internal data
    if (!_pWebBrowser2)
    {
        return E_FAIL;
    }

    // request stop
    return _pWebBrowser2->Stop();
}

/********************************************************************
 * CHTMLDoc::Refresh
 *
 * Description
 *    Refreshes current web page.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    result of webbrowser refresh request
 *    E_FAIL    internal error
 ********************************************************************/
HRESULT CHTMLDoc::RefreshPage(void)
{
    // validate internal data
    if (!_pWebBrowser2)
    {
        return E_FAIL;
    }

    // make sure on line if needed
    if (_bLastURLRemote)
    {
        CheckConnection();
    }

    // request refresh
    return _pWebBrowser2->Refresh();
}

/********************************************************************
 * CHTMLDoc::NavigateTo
 *
 * Description
 *    Displays requested URL in HTML control (download, parse, and 
 *    show requested web page).
 *
 * Parameters
 *    pszURL    URL of web page to which to navigate
 * 
 * Returns
 *    result of webbrowser navigation request
 *    E_FAIL    internal error
 ********************************************************************/
HRESULT CHTMLDoc::NavigateTo(LPTSTR pszURL)
{
    // validate internal data
    if (!_pWebBrowser2)
    {
        return E_FAIL;
    }
   
    // request navigation
    return _pWebBrowser2->Navigate(pszURL, NULL, NULL, NULL, NULL);
}

/********************************************************************
 * CHTMLDoc::GetHWND
 *
 * Description
 *    Returns window handle of the HTML control.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    HWND of HTML control
 ********************************************************************/
HWND CHTMLDoc::GetHWND(void)
{
    return _hwnd;
}

/********************************************************************
 * CHTMLDoc::StopOrHome
 *
 * Description
 *    Depending on the status of the current page (whether it has 
 *    fully loaded or not), navigation (loading) is either stopped
 *    or sent to the home page.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    result of webbrowser stop or navigation request
 *    E_FAIL    internal error
 ********************************************************************/
HRESULT CHTMLDoc::StopOrHome(void)
{
    // get interface that will allow checking of status
    IDispatch * pDispatch = NULL;

    if (FAILED(_pOleObject->QueryInterface(IID_IDispatch, 
               (LPVOID *)&pDispatch)))
    {
        return E_FAIL;
    }

    READYSTATE lReadyState = READYSTATE_UNINITIALIZED;

    // get status of page
    if (_pWebBrowser2)
    {
        _pWebBrowser2->get_ReadyState(&lReadyState);
    }

    // if page has been loaded, then navigate to home page
    HRESULT hr;
    if (lReadyState == READYSTATE_COMPLETE)
    {   
        hr = NavigateTo(PAGE_HOME);
    }
    // if page has not been loaded, stop loading
    else
    {
        hr = StopNavigation();
    }

    return hr;
}

/********************************************************************
 * CHTMLDoc::GoBack
 *
 * Description
 *    Navigates back in history (loads previous page in HTML control)
 *    if possible.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    result of webbrowser history request
 *    E_FAIL    internal error
 ********************************************************************/
HRESULT CHTMLDoc::GoBack(void)
{
    // validate internal data
    if (!_pWebBrowser2)
    {
        return E_FAIL;
    }

    // navigate back in history
    HRESULT hr = _pWebBrowser2->GoBack();

    // if could not navigate back, display message in status bar
    if ((S_OK != hr) && _pStatus)
    {
        _pStatus->SetText(g_hInstance, IDS_NO_MORE_BACK);
    }

    return hr;
}

/********************************************************************
 * CHTMLDoc::GoForward
 *
 * Description
 *    Navigates forward in history (loads next page in HTML control)
 *    if possible.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    result of webbrowser history request
 *    E_FAIL    internal error
 ********************************************************************/
HRESULT CHTMLDoc::GoForward(void)
{
    // validate internal data
    if (!_pWebBrowser2)
    {
        return E_FAIL;
    }

    // navigate forward in history
    HRESULT hr = _pWebBrowser2->GoForward();

    // if could not navigate forward, display message in status bar
    if ((S_OK != hr) && _pStatus)
    {
        _pStatus->SetText(g_hInstance, IDS_NO_MORE_FORWARD);
    }

    return hr;
}

/********************************************************************
 * CHTMLDoc::CheckConnection
 *
 * Description
 *    Ensures the user is connected to the Internet through RAS by
 *    either verifying existing connection or create a new one.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK     still connected or connection successful
 *    E_FAIL   could not connect
 ********************************************************************/
HRESULT CHTMLDoc::CheckConnection(void)
{
    HRESULT hr = S_OK;
 
    // only bother if not already connected
    if (_pDialer && (_pDialer->IsConnect() != S_OK))
    {
        _dwTimeToDisconnect = 0;

        // clean up first
        _pDialer->HangUp();

        // try to connect
        if (_pDialer->Dial() == S_OK)
        {
            // connected. change tool bar button to be a disconnect
            // button
            _pToolBar->ChangeButton(ID_CONNECT, 8, ID_DISCONNECT, 9);
            _dwTimeToDisconnect = GetTickCount() + 
                _dwDisconnectIdleTime * 60000;
        }
        else    
        {
            // not connected. change tool bar button to be a sconnect
            // button (to allow user to try again). display error page
            _pToolBar->ChangeButton(ID_DISCONNECT, 9, ID_CONNECT, 8);
            NavigateTo(PAGE_DIALER);
            hr = E_FAIL;
        }
    }
    return hr;
}

/********************************************************************
 * CHTMLDialog::Draw
 *
 * Description
 *    Copies the GDI data of the HTML control to the main DDraw surface.
 *
 * Parameters
 *    pDDS          destination direct draw surface (screen)
 *    pDDSTexture   DDraw surface of GDI data
 * 
 * Returns
 *    S_OK          drawn successfully
 *    E_INVALIDARG  NULL DDraw surface(s)
 ********************************************************************/
HRESULT CHTMLDoc::Draw(LPDIRECTDRAWSURFACE pDDS, 
                       LPDIRECTDRAWSURFACE pDDSTexture)
{
    // validate parameters
    if (!pDDS || !pDDSTexture)
    {
        return E_INVALIDARG;
    }

    // copy over data only if window is valid and visible
    if (_hwnd && IsWindowVisible(_hwnd))
    {
        // copy over whole HTML dialog from GDI
        pDDS->BltFast(_rc.left, _rc.top, pDDSTexture, &_rc, 0);
    }

    return S_OK;
}

/********************************************************************
 * CHTMLDoc::Joystick
 *
 * Description
 *    Sets cursor to HTML cursor and handles controller button presses.
 *
 * Parameters
 *    dwButtons       flags describing which buttons were pressed
 *    dwButtondsHelp  flags desribing which buttons are still down 
 *                    from last time
 *    x               x coorinate of current cursor position
 *    y               x coorinate of current cursor position
 * 
 * Returns
 *    S_OK            handled
 *    S_FALSE         cursor outside of window
 ********************************************************************/
HRESULT CHTMLDoc::Joystick(DWORD dwButtons, DWORD dwButtonsHeld, 
                           WORD x, WORD y)
{
    // set cursor type
    SetCursorType(CURSOR_HTML);

    if (dwButtons & (JOYSTICK_B | JOYSTICK_Y))
    {
        // see draw.cpp for more information on ShowCursor check

        // check for GDI cursor being active (inside server-side image map)
        if (ShowCursor(TRUE))
        {
            // B/Y buttons cancel activating server-side image map
            UINT wChar = 0;
            PostKeybdMessage((HWND)-1, VK_HOME, KeyShiftNoCharacterFlag | 
                             KeyStateDownFlag, 1, &wChar, &wChar);
            wChar = 0;
            PostKeybdMessage((HWND)-1, VK_HOME, KeyShiftNoCharacterFlag, 1, 
                             &wChar, &wChar);
        }
        else if (dwButtons & JOYSTICK_B)
        {
            // when no GDI cursor up, B button goes back in history
            GoBack();
        }
        else 
        {
            // when no GDI cursor up, Y button goes forward in history
            GoForward();
        }

        ShowCursor(FALSE);
    }
    else if (dwButtons & JOYSTICK_A)
    {
        if (ShowCursor(TRUE))
        {
            // click in server-side image map
            UINT wChar = VK_RETURN;
            PostKeybdMessage((HWND)-1, wChar, KeyStateDownFlag,
                             1, &wChar, &wChar);
            wChar = VK_RETURN;
            PostKeybdMessage((HWND)-1, wChar, KeyShiftNoCharacterFlag, 
                             1, &wChar, &wChar);
        }
        else
        {
            // on A button, do IME or simulate click (send ALT+ENTER key)
            BOOL bHandled = FALSE;
            IHTMLElement *pElement = NULL;

            // get active element to see if we need to IME
            if (GetActiveElement(&pElement) == S_OK)
            {
                if ((DoInputIME(pElement, IID_IHTMLInputTextElement) == S_OK) ||   
                    (DoInputIME(pElement, IID_IHTMLTextAreaElement ) == S_OK))
                {
                    bHandled = TRUE;
                } 

                pElement->Release();
            }

            // no IME, send ALT+ENTER
            if (!bHandled)
            {
                UINT wChar = VK_RETURN;
                PostKeybdMessage((HWND)-1, wChar, KeyStateDownFlag | 
                                 KeyShiftAnyAltFlag | KeyShiftLeftAltFlag, 
                                 1, &wChar, &wChar);
                wChar = 0;
                PostKeybdMessage((HWND)-1, wChar, KeyShiftNoCharacterFlag | 
                                 KeyShiftAnyAltFlag | KeyShiftLeftAltFlag, 
                                 1, &wChar, &wChar);
            }
        }

        ShowCursor(FALSE);
    }
    // on start button, either stop loading current page or go to home page
    else if (dwButtons & JOYSTICK_START)
    {
        StopOrHome();
    }
    // on left trigger, bring up dialog to allow user to enter URL to visit
    else if (dwButtons & JOYSTICK_LTRIG)
    {
        ShowURLGotoDialog();
    }
    // on right trigger, go to top of page (send HOME key)
    else if (dwButtons & JOYSTICK_RTRIG)
    {
        UINT wChar = 0;
        PostKeybdMessage((HWND)-1, VK_HOME, KeyShiftNoCharacterFlag | 
                         KeyStateDownFlag, 1, &wChar, &wChar);
        wChar = 0;
        PostKeybdMessage((HWND)-1, VK_HOME, KeyShiftNoCharacterFlag, 1, 
                         &wChar, &wChar);
    }
    // on direction button, move in document (send arrow key)
    else
    {
        UINT vKey = 0;

        if (dwButtons & JOYSTICK_LA)
        {
            vKey = VK_LEFT;
        }
        else if (dwButtons & JOYSTICK_RA)
        {
            vKey = VK_RIGHT;
        }
        else if (dwButtons & JOYSTICK_DA)
        {
            vKey = VK_DOWN;
        }
        else if (dwButtons & JOYSTICK_UA)
        {
            vKey = VK_UP;
        }

        if (vKey)
        {
            UINT wChar = 0;
            PostKeybdMessage((HWND)-1, vKey, KeyShiftNoCharacterFlag | 
                             KeyStateDownFlag, 1, &wChar, &wChar);
            wChar = 0;
            PostKeybdMessage((HWND)-1, vKey, KeyShiftNoCharacterFlag, 1, 
                             &wChar, &wChar);
        }
    }

#ifdef USE_FLASH
    extern DWORD g_dwButtonsReleased;

    int flashX = x - _rc.left;
    int flashY = y - _rc.top;
    if ((dwButtons & JOYSTICK_RTRIG) != 0)
    {
        FlashMouseDown(flashX, flashY);
    }
    else if ((g_dwButtonsReleased & JOYSTICK_RTRIG) != 0)
    {
        FlashMouseUp(flashX, flashY);
    }
    else 
    {
        FlashMouseMove(flashX, flashY);
    }
#endif // USE_FLASH

    return S_OK;
}

/********************************************************************
 * CHTMLDoc::Command
 *
 * Description
 *    Handles the command sent by the tool bar when the user clicked
 *    on a button.
 *
 * Parameters
 *    nID      command ID from tool bar
 * 
 * Returns
 *    S_OK     handled
 ********************************************************************/
HRESULT CHTMLDoc::Command(WORD nID)
{
    // put the cursor in the HTML window since just about any one of 
    // these commands means the user will want to next be doing something 
    // in the HTML window (arrow key navigation, tabbing, etc.)

    SetCursorPosition((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2);

    SetCursorCapture(this);
    ReleaseCursorCapture(this);

    // handle commands
    switch (nID)
    {
        case ID_HOME:
            NavigateTo(PAGE_HOME);
            break;

        case ID_SEARCH:
            NavigateTo(PAGE_SEARCH);
            break;

        case ID_HELP:
            NavigateTo(PAGE_HELP);
            break;

        case ID_FORWARD:
            GoForward();
            break;

        case ID_BACK:
            GoBack();
            break;

        case ID_STOP:
            StopNavigation();
            break;

        case ID_REFRESH:
            RefreshPage();
            break;

        case ID_KEYBOARD:
            {
                // check if active element is a text input so IME can be displayed
                IHTMLElement *pElement = NULL;
                if (SUCCEEDED(GetActiveElement(&pElement)) && pElement)
                {
                    if ((DoInputIME(pElement, IID_IHTMLInputTextElement) == S_OK) ||   
                        (DoInputIME(pElement, IID_IHTMLTextAreaElement ) == S_OK))
                    {
                    }

                    pElement->Release();
                }
            }
            break;

        case ID_CONNECT:
            // if connectin is successful, change tool bar button to be a disconnect
            // button
            if (_pDialer && (_pDialer->IsConnect() != S_OK))
            {
                _pDialer->Dial();
                _pToolBar->ChangeButton(ID_CONNECT, 8, ID_DISCONNECT, 9);
                if (_dwDisconnectIdleTime)
                {
                    _dwTimeToDisconnect = GetTickCount() + 
                        _dwDisconnectIdleTime * 60000;
                }
            }
            break;

        case ID_DISCONNECT:
            // disconnect, and change tool bar button to be a connect button
            if (_pDialer)
            {
                StopNavigation();
                _pDialer->HangUp();
                _dwTimeToDisconnect = 0;
                _pToolBar->ChangeButton(ID_DISCONNECT, 9, ID_CONNECT, 8);
            }
            break;

        case ID_GO:
            ShowURLGotoDialog();
            break;
    }

    return S_OK;
}

/********************************************************************
 * CHTMLDoc::GetActiveElement
 *
 * Description
 *    Returns active element (element in the HTML document that has the
 *    focus -- may be embedded in a frame).
 *
 * Parameters
 *    ppElement     filled in with active element pointer
 * 
 * Returns
 *    S_OK          found active element
 *    E_FAIL        internal error
 *    E_INVALIDARG  NULL ppElement
 ********************************************************************/
HRESULT CHTMLDoc::GetActiveElement(IHTMLElement **ppElement)
{
    // validate parameters
    if (!ppElement)
    {
        return E_INVALIDARG;
    }

    // initialize in case of error
    *ppElement = NULL;

    // validate internal data
    if (!_pWebBrowser2)
    {
        return E_FAIL;
    }

    // get HTML document
    IHTMLDocument2 *pHTMLDocument2 = NULL;
    IDispatch *pDispatch = NULL;

    if (SUCCEEDED(_pWebBrowser2->get_Document(&pDispatch)) && pDispatch)
    {
        pDispatch->QueryInterface(IID_IHTMLDocument2, 
                                  (LPVOID *)&pHTMLDocument2);
        pDispatch->Release();
    }

    // call mshtml.dll function to get active element
    if (pHTMLDocument2)
    {
        GetCurrentFocusElement(pHTMLDocument2, ppElement);

        pHTMLDocument2->Release();
    }

    return (*ppElement) ? S_OK : E_FAIL;
}

/********************************************************************
 * CHTMLDoc::DoInputIME
 *
 * Description
 *    Gets original text in a text element, displays the IME, and sets
 *    the new user entered text back to the text element.
 *
 * Parameters
 *    pElement  text element that is to be used for the original text
 *              in the IME and that will be set with the new text the
 *              user enters
 *    iid       interface to query on element
 * 
 * Returns
 *    S_OK      IME handled sucessfully
 *    E_FAIL    failure (not text input element)
 ********************************************************************/
HRESULT CHTMLDoc::DoInputIME(IHTMLElement *pElement, REFIID iid)
{
    // union to make it easier to do QI
    union InputElement
    {
        LPVOID                 pVoid;
        IUnknown              *pUnknown;
        IHTMLInputTextElement *pInputTextElement;
        IHTMLTextAreaElement  *pTextAreaElement;
    };

    VARIANT_BOOL bReadOnly = TRUE;
    TCHAR        achText[EDITBOX_MAXCHARS+1] = TEXT("\0");
    BSTR         bstrValue   = NULL;
    HRESULT      hr          = E_FAIL;
    InputElement Input;

    // query for text interface
    if (SUCCEEDED(pElement->QueryInterface(iid, &(Input.pVoid))))
    {
        // get text currently in text input
        if (iid == IID_IHTMLInputTextElement)
        {
            Input.pInputTextElement->get_readOnly(&bReadOnly);
            hr = Input.pInputTextElement->get_value(&bstrValue);
        }
        else if (iid == IID_IHTMLTextAreaElement)
        {
            Input.pTextAreaElement->get_readOnly(&bReadOnly);
            hr = Input.pTextAreaElement->get_value(&bstrValue);
        }

        // show IME
        if (SUCCEEDED(hr) && !bReadOnly)
        {
            if (bstrValue)
            {
                int nLen = SysStringLen(bstrValue);
                if (nLen > EDITBOX_MAXCHARS)
                {
                    nLen = EDITBOX_MAXCHARS;
                }
                _tcsncpy(achText, bstrValue, nLen);
                SysFreeString(bstrValue);
            }

            GetIMEInput(achText);

            // put new text into text input
            bstrValue = SysAllocString(achText);

            if (iid == IID_IHTMLInputTextElement)
            {
                long lMax = 0;
                Input.pInputTextElement->get_maxLength(&lMax);
                if (lMax && (((long)_tcslen(bstrValue)) > lMax))
                {
                    bstrValue[lMax] = 0;
                }                
                Input.pInputTextElement->put_value(bstrValue);
            }
            else if (iid == IID_IHTMLTextAreaElement)
            {
                Input.pTextAreaElement->put_value(bstrValue);
            }
        }

        // cleanup
        if (bstrValue)
        {
            SysFreeString(bstrValue);
        }

        Input.pUnknown->Release();
    }
    return hr;
}

/********************************************************************
 * IUnknown CHTMLDoc
 ********************************************************************/

/********************************************************************
 * CHTMLDoc::QueryInterface
 *
 * Description
 *    Return pointer to interface if request interface is supported 
 *    by this object. See COM/OLE documentation on IUnknown.
 *
 * Parameters
 *    riid              ID of requested interface
 *    ppvObj	        filled with requested interface pointer if 
 *                      supported
 * 
 * Returns
 *    S_OK              requested interface supported
 *    E_NOINTERFACE     requested interface not supported
 ********************************************************************/
STDMETHODIMP CHTMLDoc::QueryInterface(REFIID iid, LPVOID * ppvObj)
{
    // check for IUnknown
    if (iid == IID_IUnknown)
    {
        *ppvObj = (IUnknown *)(IOleContainer *)this;
    }
    // check for IOleContainer
    else if (iid == IID_IOleContainer)
    {
        *ppvObj = (IOleContainer *)this;
    }
    // check for IOleClientSite
    else if (iid == IID_IOleClientSite)
    {
        *ppvObj = (IOleClientSite *) this;
    }
    // check for IOleWindow
    else if (iid == IID_IOleWindow)
    {
        *ppvObj = (IOleWindow *) this;
    }
    // check for IOleInPlaceSite
    else if (iid == IID_IOleInPlaceSite)
    {
        *ppvObj = (IOleInPlaceSite *) this;
    }
    // check for IOleCommandTarget
    else if (iid == IID_IOleCommandTarget)
    {
        *ppvObj = (IOleCommandTarget *) this;
    }
    // check for DWebBrowserEvents2
    else if (iid == DIID_DWebBrowserEvents2)
    {
       *ppvObj = (DWebBrowserEvents2 *)this;
    }
    // all others are unsupported
    else
    {
        *ppvObj = NULL;
        return E_NOINTERFACE;
    }

    // add reference count and return interface pointer
    ((IUnknown *)*ppvObj)->AddRef();

    return S_OK;
}

/********************************************************************
 * CHTMLDoc::AddRef
 *
 * Description
 *    Increments reference count on object. See COM/OLE documentation
 *    on IUnknown.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    Reference count after addition
 ********************************************************************/
ULONG CHTMLDoc::AddRef(void)
{
    // increment reference count & return new count
    _ulRefs ++;
    return _ulRefs;
}

/********************************************************************
 * CHTMLDoc::Release
 *
 * Description
 *    Decrements reference count on object; deletes object when count
 *    is zero. See COM/OLE documentation on IUnknown.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    Reference count after subtraction
 ********************************************************************/
ULONG CHTMLDoc::Release(void)
{
    // decrement reference count
    _ulRefs--;

    // delete object if no more references    
    if (!_ulRefs)
    {
        delete this;
        // return new count
        return 0;
    }

    // return new count
    return _ulRefs;
}

/********************************************************************
 * IOleContainer CHTMLDoc
 ********************************************************************/

/********************************************************************
 * CHTMLDoc::ParseDisplayName
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleContainer.
 *
 * Parameters
 *    see documenation
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::ParseDisplayName(IBindCtx *, LPOLESTR, ULONG *, 
                                        IMoniker **)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CHTMLDoc::EnumObjects
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleContainer.
 *
 * Parameters
 *    see documenation
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::EnumObjects(DWORD, IEnumUnknown **)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CHTMLDoc::LockContainer
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleContainer.
 *
 * Parameters
 *    see documenation
 * 
 * Returns
 *    S_OK
 ********************************************************************/
STDMETHODIMP CHTMLDoc::LockContainer(BOOL)
{
    return S_OK;
}

/********************************************************************
 * IOleClientSite CHTMLDoc
 ********************************************************************/

/********************************************************************
 * CHTMLDoc::SaveObject
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleClientSite.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::SaveObject(void)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CHTMLDoc::GetMoniker
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleClientSite.
 *
 * Parameters
 *    see documenation
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker,
                                  LPMONIKER *ppMoniker)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CHTMLDoc::GetContainer
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleClientSite.
 *
 * Parameters
 *    see documenation
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::GetContainer(LPOLECONTAINER *ppContainer)
{
    return E_NOINTERFACE;
}

/********************************************************************
 * CHTMLDoc::ShowObject
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleClientSite.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::ShowObject(void)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CHTMLDoc::OnShowWindow
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleClientSite.
 *
 * Parameters
 *    see documenation
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::OnShowWindow(BOOL)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CHTMLDoc::RequestNewObjectLayout
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleClientSite.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::RequestNewObjectLayout(void)
{
    return E_NOTIMPL;
}

/********************************************************************
 * IOleWindow CHTMLDoc
 ********************************************************************/

/********************************************************************
 * CHTMLDoc::GetWindow
 *
 * Description
 *    Returns the window handle of the parent window to the HTML
 *    control. See HTML control documenation on IOleClientSite.
 *
 * Parameters
 *    pHwnd    filled in with window handle of parent
 * 
 * Returns
 *    S_OK     window handled returned
 ********************************************************************/
STDMETHODIMP CHTMLDoc::GetWindow(HWND *pHwnd)
{
    *pHwnd = _hwndParent;

    return S_OK;
}

/********************************************************************
 * CHTMLDoc::ContextSensitiveHelp
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleClientSite.
 *
 * Parameters
 *    see documenation
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::ContextSensitiveHelp(BOOL)
{
    return E_NOTIMPL;
}

/********************************************************************
 * IOleInPlaceSite CHTMLDoc
 ********************************************************************/

/********************************************************************
 * CHTMLDoc::CanInPlaceActivate
 *
 * Description
 *    Returns whether object can in place activate. See HTML control
 *    documentation on IOleInPlaceSite.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK      can in place activate
 ********************************************************************/
STDMETHODIMP CHTMLDoc::CanInPlaceActivate(void)
{
    return S_OK;
}

/********************************************************************
 * CHTMLDoc::OnInPlaceActivate
 *
 * Description
 *    Handles notification that HTML control has been in place
 *    activated. See HTML control documenation on IOleInPlaceSite.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK      notification handled
 ********************************************************************/
STDMETHODIMP CHTMLDoc::OnInPlaceActivate(void)
{
     _bInPlaceActive = TRUE;

     return S_OK;
}

/********************************************************************
 * CHTMLDoc::OnUIActivate
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleInPlace.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::OnUIActivate(void)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CHTMLDoc::GetWindowContext
 *
 * Description
 *    Returns window context (in this case, just the size/position of
 *    the control window). See HTML control documenation on 
 *    IOleInPlaceSite.
 *
 * Parameters
 *    ppFrame      filled in with IOleInPlaceFrame pointer (not used)
 *    ppDoc        filled in with IOleInPlaceUIWindow pointer (not used)
 *    prcPosRect   filled in with desired position of HTML control 
 *                 window
 *    prcClipRect  filled in with desired position of HTML control 
 *                 window
 *    pFI          filled in with frame info (not used)
 * 
 * Returns
 *    S_OK     context data filled in
 ********************************************************************/
STDMETHODIMP CHTMLDoc::GetWindowContext(LPOLEINPLACEFRAME *ppFrame,
                                        LPOLEINPLACEUIWINDOW *ppDoc,
                                        LPRECT prcPosRect, 
                                        LPRECT prcClipRect,
                                        LPOLEINPLACEFRAMEINFO pFI)
{
    // validate parameters
    if (!prcPosRect || !prcClipRect)
    {
        return E_INVALIDARG;
    }

    // set window position
    *prcPosRect  = _rc;
    *prcClipRect = _rc;

    return S_OK;
}

/********************************************************************
 * CHTMLDoc::Scroll
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleInPlace.
 *
 * Parameters
 *    see documenation
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::Scroll(SIZE scrollExtent)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CHTMLDoc::OnUIDeactivate
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleInPlace.
 *
 * Parameters
 *    see documenation
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::OnUIDeactivate(BOOL fUndoable)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CHTMLDoc::OnInPlaceDeactivate
 *
 * Description
 *    Handles notification that HTML control has been in place
 *    deactivated. See HTML control documenation on IOleInPlaceSite.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK      notification handled
 ********************************************************************/
STDMETHODIMP CHTMLDoc::OnInPlaceDeactivate(void)
{
    _bInPlaceActive = FALSE;

    return S_OK;
}

/********************************************************************
 * CHTMLDoc::DiscardUndoState
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleInPlace.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::DiscardUndoState(void)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CHTMLDoc::DeactivateAndUndo
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleInPlace.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::DeactivateAndUndo(void)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CHTMLDoc::OnPosRectChange
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on IOleInPlace.
 *
 * Parameters
 *    see documenation
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::OnPosRectChange(LPCRECT prcPosRect)
{
    return E_NOTIMPL;
}

/********************************************************************
 * IOleCommandTarget CHTMLDoc
 ********************************************************************/

/********************************************************************
 * CHTMLDoc::QueryStatus
 *
 * Description
 *    Returns the status of one or more commands generated by user 
 *    interface events. None are supported. See HTML control 
 *    documentation on IOleCommandTarget.
 *
 * Parameters
 *    pguidCmdGroup     command group ID. NULL is standard group
 *    cCmds             number of commands to query status
 *    rgCmds            commands to query status and resultant status
 *    pcmdtext          resultant status for one command
 * 
 * Returns
 *    S_OK                     status filled in
 *    OLECMDERR_E_UNKNOWNGROUP non NULL command group ID
 ********************************************************************/
STDMETHODIMP CHTMLDoc::QueryStatus(const GUID *pguidCmdGroup, 
                                   ULONG cCmds, MSOCMD rgCmds[],
                                   MSOCMDTEXT *pcmdtext)
{
    // validate parameters
    if (pguidCmdGroup != NULL)
    {
        return OLECMDERR_E_UNKNOWNGROUP;
    }

    // set that none of these are handled
    if (pcmdtext && (pcmdtext->cmdtextf != MSOCMDTEXTF_NONE))
    {
        pcmdtext->cwActual = 0;
    }

    MSOCMD *pCmd;
    INT     c;

    for (pCmd = rgCmds, c = cCmds; --c >= 0; pCmd++)
    {
        pCmd->cmdf = 0;
    }

    return S_OK;
}

/********************************************************************
 * CHTMLDoc::Exec
 *
 * Description
 *    Executes requested command. See HTML control documentation on 
 *    IOleCommandTarget. 
 *
 * Parameters
 *    pguidCmdGroup     command group ID. NULL is standard group
 *    nCmdID            command ID to execute
 *    nCmdexecopt       command options
 *    pvarargIn         arguments for command
 *    pvarargOut        results for command
 * 
 * Returns
 *    S_OK                     command executed
 *    OLECMDERR_E_UNKNOWNGROUP non NULL command group ID
 *    OLECMDERR_E_NOTSUPPORTED unknown command ID
 ********************************************************************/
STDMETHODIMP CHTMLDoc::Exec(const GUID *pguidCmdGroup, DWORD nCmdID, 
                            DWORD nCmdexecopt, VARIANTARG *pvarargIn, 
                            VARIANTARG *pvarargOut)
{
    // validate parameters
    if (pguidCmdGroup)
    {
        return OLECMDERR_E_UNKNOWNGROUP;
    }

    // handle command
    switch (nCmdID)
    {
        case OLECMDID_SETPROGRESSTEXT:
            // validate parameters
            if (pvarargIn && (V_VT(pvarargIn) == VT_BSTR))
            {
                // set status text to requested string
                if (_pStatus)
                {
                    _pStatus->SetText(V_BSTR(pvarargIn));
                }
                return S_OK;
            }
            break;
    }

    return OLECMDERR_E_NOTSUPPORTED;
}

/********************************************************************
 * DWebBrowserEvemts2 IDispatch CHTMLDoc
 ********************************************************************/

/********************************************************************
 * CHTMLDoc::GetTypeInfoCount
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on DWebBrowserEvents2/IDispatch.
 *
 * Parameters
 *    see documenation
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::GetTypeInfoCount(UINT *pctinfo)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CHTMLDoc::GetTypeInfo
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on DWebBrowserEvents2/IDispatch.
 *
 * Parameters
 *    see documenation
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::GetTypeInfo(UINT itinfo, LCID lcid,
                                   ITypeInfo **pptinfo)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CHTMLDoc::GetIDsOfNames
 *
 * Description
 *    Not required to be implemented. See HTML control documentation
 *    on DWebBrowserEvents2/IDispatch.
 *
 * Parameters
 *    see documenation
 * 
 * Returns
 *    E_NOTIMPL
 ********************************************************************/
STDMETHODIMP CHTMLDoc::GetIDsOfNames(REFIID riid,OLECHAR **rgszNames, 
                                     UINT cNames, LCID lcid, 
                                     DISPID FAR* rgdispid)
{
    return E_NOTIMPL;
}

/********************************************************************
 * CHTMLDoc::Invoke
 *
 * Description
 *    Executes requested function. See HTML control documentation on 
 *    DWebBrowserEvents2/IDispatch.
 *
 * Parameters
 *    dispidMember      command ID to execute 
 *    riid              reserved
 *    lcid              locale ID (not used)
 *    wFlags            flags - get, put, invoke (not used)
 *    pdispparams       parameters for command
 *    pvarResult        result for command (not used)
 *    pexcepinfo        execption information (not used)
 *    puArgErr          filled with first argument having error 
 *                      (not used)
 * 
 * Returns
 *    S_OK              handled
 ********************************************************************/
STDMETHODIMP CHTMLDoc::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, 
                              WORD wFlags, DISPPARAMS *pdispparams, 
                              VARIANT *pvarResult, EXCEPINFO *pexcepinfo, 
                              UINT *puArgErr)
{
    switch (dispidMember)
    {
        // set status text
        case DISPID_STATUSTEXTCHANGE:
            if (_pStatus)
            {
                _pStatus->SetText(pdispparams->rgvarg[0].bstrVal);
            }
            break;

        // check for connection
        case DISPID_BEFORENAVIGATE2:
            if ((pdispparams->cArgs > 5) && 
                (pdispparams->rgvarg[5].vt == (VT_BYREF | VT_VARIANT)))
            {
                _bLastURLRemote = FALSE;
                VARIANT *pVariant = pdispparams->rgvarg[5].pvarVal;
                if (pVariant && (pVariant->vt == VT_BSTR))
                {
                    // If not Local File, check for connection
                    _bLastURLRemote = ISREMOTEFILE(pVariant->bstrVal);
                    if (_bLastURLRemote)
                    {
                        CheckConnection();
                    }
                }
            }
            break;

        // start idle time checking for disconnect
        // stop animating logo when download complete
        case DISPID_DOCUMENTCOMPLETE:
        case DISPID_DOWNLOADCOMPLETE:
            if (_pDialer && _dwDisconnectIdleTime && (_pDialer->IsConnect() != S_OK))
            {
                _dwTimeToDisconnect = GetTickCount() + _dwDisconnectIdleTime * 60000;
            }

            if (_pLogoStatus)
            { 
                _pLogoStatus->Animate(FALSE);
            }
            break;

        // set title in title bar as it changes
        case DISPID_TITLECHANGE:
            if (_pTitle && (pdispparams->cArgs > 0) && 
                (pdispparams->rgvarg[0].vt == VT_BSTR))
            {
                _pTitle->SetText(pdispparams->rgvarg[0].bstrVal);
            }
            break;

        // start animating logo when download starts
        case DISPID_DOWNLOADBEGIN:
            if (_pLogoStatus)
            { 
                _pLogoStatus->Animate(TRUE);
            }
            break;

        // display security icon if secure page
        case DISPID_SECURITYICONCHANGE:
        {
            BOOL bSecure = FALSE;

            if (pdispparams->cArgs && (pdispparams->rgvarg[0].vt == VT_BOOL) &&
                pdispparams->rgvarg[0].boolVal)
            {
                bSecure = TRUE;
            }
        
            if (_pSecurityStatus)
            {
                _pSecurityStatus->SetBitmap(bSecure);
            }

            break;
        }
    }
    
    return S_OK;
}

/********************************************************************
 * CHTMLDoc::ShowURLGotoDialog
 *
 * Description
 *    Displays the Go To URL HTML dialog (found in reshelp.dll) which
 *    allows user to enter a URL to visit. If the user does not 
 *    cancel the dialog, the HTML control navigates to the requested
 *    URL.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK     succeeded
 *    E_FAIL   internal error
 ********************************************************************/
HRESULT CHTMLDoc::ShowURLGotoDialog(void)
{
    // verify internal data
    if (!_hwnd)
    {
        return E_FAIL;
    }

    // create argument list (gotourl.dlg in reshelp.dll takes one 
    // argument -- the last typed URL)

    HRESULT hr = E_FAIL;
    VARIANT varRet   = { 0 };
    VARIANT varArgIn = { 0 };

    varArgIn.vt = VT_BSTR;
    varArgIn.bstrVal = SysAllocString(_bstrLastTypedURL ? _bstrLastTypedURL : TEXT(""));

    // create a URL moniker for the gotourl.dlg file in reshelp.dll
    IMoniker *pMoniker = NULL;
    if (SUCCEEDED(CreateURLMoniker(NULL, PAGE_GOTOURL, &pMoniker)) && 
        pMoniker)
    {
        // show the gotourl dialog
        hr = ShowHTMLDialog(_hwnd, pMoniker, &varArgIn, NULL, &varRet);
        pMoniker->Release();
    }

    POINT ptCursor = QueryCursorPosition();
    if ((ptCursor.x < _rc.left) || (ptCursor.x >= _rc.right) || 
        (ptCursor.y < _rc.top)  || (ptCursor.y >= _rc.bottom))
    {
        SetCursorPosition((_rc.left + _rc.right) / 2, (_rc.top + _rc.bottom) / 2);
        SetCursorCapture(this);
        ReleaseCursorCapture(this);
    }

    // if user did not cancel, navigate to the typed in URL
    if (SUCCEEDED(hr) && (varRet.vt == VT_BSTR) && varRet.bstrVal && 
        varRet.bstrVal[0])
    {
        if (_bstrLastTypedURL)
        {
            SysFreeString(_bstrLastTypedURL); 
        }
        _bstrLastTypedURL = varRet.bstrVal;
        NavigateTo(_bstrLastTypedURL);
        varRet.bstrVal = NULL;
    }

    VariantClear(&varArgIn);
    VariantClear(&varRet);

    return hr;
}

/********************************************************************
 * NOTES
 * 
 * Here are the default settings in the tvstyles.css file for 
 * intrinsic controls (such as combo boxes, edit fields, etc.). You can 
 * change this file to change the sizes, etc, of the controls (unless 
 * the page overrides the settings). For example, you can change the 
 * font size as below:
 *
 * <STYLE type="text/css">
 *     SELECT {margin-top: 2px; margin-bottom: 3px}
 *     INPUT {margin-top: 2px; margin-bottom: 3px; font-size:20pt}
 * </STYLE>
 *
 * See documentation on style sheets for other things you may wish to 
 * default.
 *
 * (Japanese version fo tvstyles.css is tvstylesjpn.css and defaults
 * the font used for controls to MS Gothic)
 ********************************************************************/
