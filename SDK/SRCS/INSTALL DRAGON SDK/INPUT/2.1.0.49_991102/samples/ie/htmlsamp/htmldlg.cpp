/********************************************************************
 * htmldlg.cpp
 *
 * Description
 *    CHTMLDialog - class that handles the display and input of HTML
 *    dialogs (such as alerts, prompts, confirms, other scripting
 *    HTML dialogs, and the Go To URL dialog -- see htmldoc.cpp for
 *    the invokation of the Go To dialog).
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include "htmldlg.h"            // CHTMLDialog
#include "editbox.h"            // TKIME edit box
#include "external.h"           // wrapper prototypes
#include <keybd.h>              // keyboard scan codes

/********************************************************************
 * External prototypes
 ********************************************************************/
extern CHTMLDialog *GetHTMLDialogForHWND(HWND hwnd);

/********************************************************************
 * CHTMLDialog::HTMLDialog
 *
 * Description
 *    Constructor. Initializes internal data and subclasses the HTML
 *    Dialog window.
 *
 * Parameters
 *    HWND             window handle of HTML dialog
 *    pHTMLDocument2   document inside HTML dialog
 * 
 * Returns
 *    N/A
 ********************************************************************/
CHTMLDialog::CHTMLDialog(HWND hwnd, IHTMLDocument2 *pHTMLDocument2)
            :CWindow(0, 0, 0, 0)
{
    // set internal data
    _hwnd                   = hwnd;
    _bCaptured              = FALSE;

    _pHTMLDocument2         = pHTMLDocument2;
    if (_pHTMLDocument2)
    {
        _pHTMLDocument2->AddRef();
    }

    // sub class dialog window    
    _pfnOldWndProc = (WNDPROC)GetWindowLong(_hwnd, GWL_WNDPROC);
    SetWindowLong(_hwnd, GWL_WNDPROC, (ULONG)StaticWndProc);
}

/********************************************************************
 * CHTMLDialog::~CHTMLDialog
 *
 * Description
 *    Destructor. Destroys internal data and un-subclasses window.
 *
 * Parameters
 *    N/A
 * 
 * Returns
 *    N/A
 ********************************************************************/
CHTMLDialog::~CHTMLDialog(void)
{
    // un-subclass dialog window
    if (_hwnd)
    {
        SetWindowLong(_hwnd, GWL_WNDPROC, (ULONG)_pfnOldWndProc);
    }

    // release document
    if (_pHTMLDocument2)
    {
        _pHTMLDocument2->Release();
        _pHTMLDocument2 = NULL;
    }

    // release captured cursor
    if (_bCaptured)
    {
        ReleaseCursorCapture(this);
        _bCaptured = FALSE;
    }
}

/********************************************************************
 * CHTMLDialog::Draw
 *
 * Description
 *    Copies the GDI data of the HTML dialog to the main DDraw surface.
 *
 * Parameters
 *    pDDS          destination direct draw surface (screen)
 *    pDDSTexture   DDraw surface of GDI data
 * 
 * Returns
 *    S_OK          drawn successfully
 *    E_INVALIDARG  NULL DDraw surface(s)
 ********************************************************************/
HRESULT CHTMLDialog::Draw(LPDIRECTDRAWSURFACE pDDS, 
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
        GetWindowRect(_hwnd, &_rc);
        if ((_rc.right != _rc.left) && (_rc.bottom != _rc.top))
        {
            pDDS->BltFast(_rc.left, _rc.top, pDDSTexture, &_rc, 0);
        }
    }

    return S_OK;
}

/********************************************************************
 * CHTMLDialog::Joystick
 *
 * Description
 *    Sets cursor to HTML cursor, constrains the cursor to within 
 *    the HTML dialog window, and handles controller button presses.
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
HRESULT CHTMLDialog::Joystick(DWORD dwButtons, DWORD dwButtonsHeld, 
                              WORD x, WORD y)
{
    // set cursor type
    SetCursorType(CURSOR_HTML);
  
    // check for cursor leaving
    if ((x == 0xffff) || (y == 0xffff))
    {
        if (_bCaptured)
        {
            _bCaptured = FALSE;
            ReleaseCursorCapture(this);
        }

        return S_FALSE;
    }

    // capture cursor
    if (!_bCaptured)
    {
        _bCaptured = TRUE;
        SetCursorCapture(this);
    }

    // constrain cursor to stay in window
    if ((_rc.right != _rc.left) && (_rc.bottom != _rc.top))
    {
        if (x < _rc.left + 8)
        {
            x = _rc.left + 8;
        }
        else if (x > _rc.right - 8)
        {
            x = _rc.right - 8;
        }
        if (y < (_rc.top + 8))
        {
            y = (_rc.top + 8);
        }
        else if (y > (_rc.bottom - 8))
        {
            y = (_rc.bottom - 8);
        }

        SetCursorPosition(x, y);
    }

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
        else 
        {
            // on B/Y button when GDI cursor is not active, close dialog 
            // (send ESCAPE key)
            UINT wChar = VK_ESCAPE;
            PostKeybdMessage((HWND)-1, wChar, KeyStateDownFlag, 1, &wChar, &wChar);
            wChar = 0;
            PostKeybdMessage((HWND)-1, wChar, KeyShiftNoCharacterFlag, 1, 
                             &wChar, &wChar);
        }

        ShowCursor(FALSE);
    }
    else if (dwButtons & JOYSTICK_A)
    {
        // see draw.cpp for more information on ShowCursor check

        // check for GDI cursor being active (inside server-side image map)
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
                // check for text entry
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
            PostKeybdMessage((HWND)-1, vKey, KeyShiftNoCharacterFlag, 
                             1, &wChar, &wChar);
        }
    }

    return S_OK;
}

/********************************************************************
 * CHTMLDialog::GetActiveElement
 *
 * Description
 *    Returns active element (element in the HTML dialog that has the
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
HRESULT CHTMLDialog::GetActiveElement(IHTMLElement **ppElement)
{
    // validate parameters
    if (!ppElement)
    {
        return E_INVALIDARG;
    }

    // initialize in case of error
    *ppElement = NULL;

    // validate internal data
    if (!_pHTMLDocument2)
    {
        return E_FAIL;
    }

    // call mshtml.dll funtion to get active element
    GetCurrentFocusElement(_pHTMLDocument2, ppElement);

    return (*ppElement) ? S_OK : E_FAIL;
}

/********************************************************************
 * CHTMLDialog::DoInputIME
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
HRESULT CHTMLDialog::DoInputIME(IHTMLElement *pElement, REFIID iid)
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

        // clean up
        if (bstrValue)
        {
            SysFreeString(bstrValue);
        }

        Input.pUnknown->Release();
    }
    return hr;
}

/********************************************************************
 * CHTMLDialog::GetHWND
 *
 * Description
 *    Returns window handle of HTML dialog window.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    HWND      window handle
 ********************************************************************/
HWND CHTMLDialog::GetHWND(void)
{
    return _hwnd;
}
 
/********************************************************************
 * CHTMLDialog::WndProc
 *
 * Description
 *    Subclassed window procedure for HTML dialog window. Checks for
 *    dialog window changing size.
 *
 * Parameters
 *    hwnd      window handle of window processing message
 *    uiMsg     message ID
 *    wParam    message data
 *    lParam    message data
 * 
 * Returns
 *    result of original window produre
 ********************************************************************/
LRESULT CHTMLDialog::WndProc(HWND hwnd, UINT uiMsg, WPARAM wParam, 
                             LPARAM lParam)
{
    LRESULT lr = CallWindowProc(_pfnOldWndProc, hwnd, uiMsg, wParam, lParam);

    // get real position of HTML dialog window
    if ((_rc.left == _rc.right) || (_rc.top == _rc.bottom))
    {
        RECT rc;
        GetWindowRect(_hwnd, &rc);   
        if (memcmp(&rc, &_rc, sizeof(rc)))
        {
            _rc = rc;
            // force the cursor to stay inside window
            POINT ptCursor = QueryCursorPosition();
            Joystick(0, 0, (WORD)ptCursor.x, (WORD)ptCursor.y);
        }
    }

    return lr;
}

/********************************************************************
 * CHTMLDialog::StaticWndProc
 *
 * Description
 *    Subclassed window procedure for HTML dialog window. Calls object's
 *    version of function.
 *
 * Parameters
 *    hwnd      window handle of window processing message
 *    uiMsg     message ID
 *    wParam    message data
 *    lParam    message data
 * 
 * Returns
 *    0         handled
 *    other     result of object's window procedure
 ********************************************************************/
LRESULT CHTMLDialog::StaticWndProc(HWND hwnd, UINT uiMsg, WPARAM wParam, 
                                   LPARAM lParam)
{
    // Find CHTMLDialog object that corresponds to given HWND   
    CHTMLDialog *pHTMLDialog = GetHTMLDialogForHWND(hwnd);
    if (pHTMLDialog)
    {
        // call object's version of Window Procedure
        return pHTMLDialog->WndProc(hwnd, uiMsg, wParam, lParam);
    }

    return 0;    
}
