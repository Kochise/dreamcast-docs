/********************************************************************
 * device.cpp
 *
 * Description
 *    CVMUSelection - class that handles the display and input of the
 *    VMU selection window (call back from vmimime.dll -- see HTML
 *    control documentation). This window is on its own "screen" --
 *    see draw.cpp.
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include "device.h"             // CVMUSelection

/********************************************************************
 * Defines - screen object positioning
 ********************************************************************/
#define SCREEN_DEVICE   1       // screen ID of screen on which to 
                                // display device selection window

#define CANCEL_BUTTON   8       // ID of canceled selection 
#define INITIAL_SELECT  0xff    // initial selection (default to first
                                // found)

#define W_BITMAP        330     // size of bitmap of display pieces
#define H_BITMAP        87

#define X_CONTROL       0       // position of control in bitmap
#define Y_CONTROL       0
#define W_CONTROL       83
#define H_CONTROL       87

#define X_SELECTED      83      // position of selection in bitmap
#define Y_SELECTED      0
#define W_SELECTED      43
#define H_SELECTED      62

#define X_DEVICE        89      // position of VMU in bitmap
#define Y_DEVICE        6
#define W_DEVICE        31
#define H_DEVICE        50

#define X_INTERIOR      126     // position of VMU guts in bitmap
#define Y_INTERIOR      0
#define W_INTERIOR      26
#define H_INTERIOR      40

#define X_LETTER        83      // position of letter A in bitmap
#define Y_LETTER        72      // (other letters/numbers offset 
#define W_LETTER        20      // from this position horizontally)
#define H_LETTER        15

#define X_BUTTON        158     // position of cancel btn in bitmap
#define Y_BUTTON        6
#define W_BUTTON        68
#define H_BUTTON        30

#define X_SELBUTTON     152     // position of cancel btn selected
#define Y_SELBUTTON     0       // in bitmap
#define W_SELBUTTON     80
#define H_SELBUTTON     42

#define X_INFO          232     // position of info box in bitmap
#define Y_INFO          0
#define W_INFO          98
#define H_INFO          87

#define X_BAR           126     // position of filled bar in bitmap
#define Y_BAR           47
#define W_BAR           84
#define H_BAR           15
                                    
#define X_COLUMN        (175 + 40)  // positon to display devices in
#define Y_ROW           (235 + 40)  // window
#define W_COLUMN        95
#define H_ROW           80

#define X_CANCEL        (60 + 40)   // position to display cancel
#define Y_CANCEL        (380 + 40)  // button in window

#define X_INFOBOX       (20 + 40)   // position to display info box
#define Y_INFOBOX       (120 + 40)  // in window

#define X_TEXT          9       // offset to display info box text
#define Y_TEXT          8       // in window
#define H_TEXT          25

#define X_OFFSET        2       // offset to display vmu interior
#define Y_OFFSET        4       // in window

#define X_STARTBAR      7       // offset to display filled bar in
#define Y_STARTBAR      66      // window
				    
#define X_PROMPT        (20 + 40)   // position to display prompt in
#define Y_PROMPT        (20 + 40)   // window

#define X_CURSOR        320     // position of invisible cursor
#define Y_CURSOR        240    
#define OFFSET_CURSOR   25      // movement of cursor to simulate
                                // direction button press

                                // Done event
#define EVENT_DEVICE_SCREEN_DONE    TEXT("HTMLSAMP_EVENT_DEVICE_SCREEN_DONE")

/********************************************************************
 * CVMUSelection::CVMUDeviceData::CVMUDeviceData
 *
 * Description
 *    Constructor. Initializes the internal data.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    N/A
 ********************************************************************/
CVMUSelection::CVMUDeviceData::CVMUDeviceData(void)   
{   
    // initialize to no found device
    _pDevice        = NULL; 
    _dwTotalBlocks  = 0; 
    _dwFreeBlocks   = 0; 
}

/********************************************************************
 * CVMUSelection::CVMUDeviceData::~CVMUDeviceData
 *
 * Description
 *    Destructor. Destroys the VMU device object.
 *
 * Parameters
 *    N/A
 * 
 * Returns
 *    N/A
 ********************************************************************/
CVMUSelection::CVMUDeviceData::~CVMUDeviceData(void)  
{ 
    // destroy VMU device 
    if (_pDevice) 
    {
        _pDevice->Release(); 
        _pDevice = NULL;
    }
}

/********************************************************************
 * CVMUSelection::CVMUSelection
 *
 * Description
 *    Constructor. Initializes the bitmap surface, the strings, the
 *    events, and the font for the window.
 *
 * Parameters
 *    hEventAbort       event signalled by vmimime.dll to indicate
 *                      procedure aborted
 *    pdwResults        filled with user device selection
 * 
 * Returns
 *    N/A
 ********************************************************************/
CVMUSelection::CVMUSelection(HANDLE hEventAbort, DWORD *pdwResults)
              :CWindow(0, 0, GetSystemMetrics(SM_CXSCREEN), 
                       GetSystemMetrics(SM_CYSCREEN), TRUE, 1)
{
    // set internal data
    _hEventAbort    = hEventAbort;
    _hEventDone     = CreateEvent(NULL, TRUE, FALSE, EVENT_DEVICE_SCREEN_DONE);
    _bRunning       = FALSE;
    _nSelected      = INITIAL_SELECT;
    _pBitmap        = NULL;
    _idThread       = 0;
    _dwTotalBlocks  = 0; 
    _dwFreeBlocks   = 0; 
    _nDevices       = 0;
    _pdwResults     = pdwResults;
    if (_pdwResults)
    {
        *_pdwResults = DEVICE_SELECT_ABORT;
    }

    // load prompt
    LoadString(g_hInstance, IDS_PROMPT_SELECTVMU, _szPrompt, 
               sizeof(_szPrompt) / sizeof(_szPrompt[0]));
    
    // create font for text drawing
    LOGFONT lf;
    memset(&lf, 0, sizeof(lf));
    lf.lfHeight         = H_TEXT;
    lf.lfWeight         = FW_NORMAL;
    lf.lfCharSet        = DEFAULT_CHARSET;
    lf.lfOutPrecision   = OUT_DEFAULT_PRECIS;
    lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
    lf.lfQuality        = DEFAULT_QUALITY;
    lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    _tcscpy(lf.lfFaceName, FONT_NAME);

    _hFont = CreateFontIndirect(&lf);

    // create bitmap surface (which contains pieces for drawing)
    _pBitmap = CreateBitmapSurface(MAKEINTRESOURCE(IDB_DEVICE), W_BITMAP, 
                                   H_BITMAP, FALSE, 0);
}

/********************************************************************
 * CVMUSelection::~CVMUSelection
 *
 * Description
 *    Destructor. Destroy the bitmap surface, the events, and the font.
 *    If the helper thread is still running, it aborts the thread.
 *
 * Parameters
 *    N/A
 * 
 * Returns
 *    N/A
 ********************************************************************/
CVMUSelection::~CVMUSelection(void)
{
    // make sure the thread has stopped
    if (_bRunning)
    {
        // This should not happen.
        Stop();
    }

    // destroy font
    if (_hFont)
    {
        DeleteObject(_hFont);
        _hFont = NULL;
    }

    // destroy bitmap surface
    if (_pBitmap)
    {
        _pBitmap->Release();
        _pBitmap = NULL;
    }

    // destroy event
    if (_hEventDone)
    {
        CloseHandle(_hEventDone);
        _hEventDone = NULL;
    }
}

/********************************************************************
 * CVMUSelection::Draw
 *
 * Description
 *    Draws the device selection window -- cancel buttons, current
 *    device info box, and pictures of plugged in devices.
 *
 * Parameters
 *    pDDS          destination direct draw surface (screen)
 * 
 * Returns
 *    S_OK          drawn successfully
 *    E_INVALIDARG  NULL pDDS
 ********************************************************************/
HRESULT CVMUSelection::Draw(LPDIRECTDRAWSURFACE pDDS)
{
    // validate data
    if (!_pBitmap)
    {
        return S_OK;
    }

    // set up initial state or find which devices are still plugged in
    if (_nSelected == INITIAL_SELECT)
    {
        Joystick(0, 0, 0, 0);
    }
    else
    {
        _nDevices = FindAvailableDevices();
    }

    // find which controllers are plugged in
    BYTE nControllers = FindAvailableControllers();

    // if no devices plugged in, set focus to cancel button
    if (!(_nDevices & (1 << _nSelected)))
    {
        _nSelected = CANCEL_BUTTON;
    }

    RECT r = _rc;
    WORD x;
    WORD y;

    // draw background
    DDBLTFX ddbltfx;
    memset(&ddbltfx, 0, sizeof(ddbltfx));
    ddbltfx.dwSize = sizeof(DDBLTFX);
    ddbltfx.dwFillColor = COLORREF_TO_16BPP(RGB(0xC0, 0xC0, 0xC0));
    pDDS->Blt(&r, NULL, NULL, DDBLT_COLORFILL, &ddbltfx);

    // draw devices
    if (_pBitmap)
    {
        short i;

        for (i = 0; i < NUM_DEVICES; i++)
        {
            // if selected device, draw it as selected
            if (_nSelected == i)
            {
                x = X_COLUMN + (i >> 1)   * W_COLUMN - (W_SELECTED / 2);
                y = Y_ROW    + (i & 0x01) * H_ROW    - (H_SELECTED / 2);

                r.left   = X_SELECTED;
                r.top    = Y_SELECTED;
                r.right  = r.left + W_SELECTED;
                r.bottom = r.top  + H_SELECTED;
            }
            // if not selected device, draw normal
            else
            {
                x = X_COLUMN + (i >> 1)   * W_COLUMN - (W_DEVICE / 2);
                y = Y_ROW    + (i & 0x01) * H_ROW    - (H_DEVICE / 2);

                r.left   = X_DEVICE;
                r.top    = Y_DEVICE;
                r.right  = r.left + W_DEVICE;
                r.bottom = r.top  + H_DEVICE;
            }

            pDDS->BltFast(x, y, _pBitmap, &r, 0);

            // if device is plugged in, draw guts of device 
            if (_nDevices & (1 << i))
            {

                x = X_COLUMN + (i >> 1)   * W_COLUMN + X_OFFSET - (W_DEVICE / 2);
                y = Y_ROW    + (i & 0x01) * H_ROW    + Y_OFFSET - (H_DEVICE / 2);

                r.left   = X_INTERIOR;
                r.top    = Y_INTERIOR;
                r.right  = r.left + W_INTERIOR;
                r.bottom = r.top  + H_INTERIOR;
                pDDS->BltFast(x, y, _pBitmap, &r, 0);
            }
        }

        // draw device number labels
        for (i = 0; i < 2; i++)
        {
            x = X_COLUMN - (W_LETTER * 4);
            y = Y_ROW    + i * H_ROW - (H_LETTER / 2);

            r.left   = X_LETTER + (W_LETTER * (i + 4));
            r.top    = Y_LETTER;
            r.right  = r.left + W_LETTER;
            r.bottom = r.top  + H_LETTER;

            pDDS->BltFast(x, y, _pBitmap, &r, 0);
        }

        // draw controller letter labels
        for (i = 0; i < 4; i++)
        {
            if (nControllers & (1 << i))
            {
                x = X_COLUMN + i * W_COLUMN - (W_CONTROL / 2);
                y = Y_ROW    - H_CONTROL - (H_LETTER * 3) - (H_DEVICE / 2);

                r.left   = X_CONTROL;
                r.top    = Y_CONTROL;
                r.right  = r.left + W_CONTROL;
                r.bottom = r.top  + H_CONTROL;

                pDDS->BltFast(x, y, _pBitmap, &r, 0);
            }

            x = X_COLUMN + i * W_COLUMN - (W_LETTER / 2);
            y = Y_ROW    - (H_LETTER * 2) - (H_SELECTED / 2);

            r.left   = X_LETTER + (W_LETTER * i);
            r.top    = Y_LETTER;
            r.right  = r.left + W_LETTER;
            r.bottom = r.top  + H_LETTER;

            pDDS->BltFast(x, y, _pBitmap, &r, 0);
        }

        // if cancel button is selected, draw it selected
        if (_nSelected == CANCEL_BUTTON)
        {
            x = X_CANCEL - (W_SELBUTTON / 2);
            y = Y_CANCEL - (H_SELBUTTON / 2);

            r.left   = X_SELBUTTON;
            r.top    = Y_SELBUTTON;
            r.right  = r.left + W_SELBUTTON;
            r.bottom = r.top  + H_SELBUTTON;
        }
        // if cancel button is not selected, draw it normal
        else
        {
            x = X_CANCEL - (W_BUTTON / 2);
            y = Y_CANCEL - (H_BUTTON / 2);

            r.left   = X_BUTTON;
            r.top    = Y_BUTTON;
            r.right  = r.left + W_BUTTON;
            r.bottom = r.top  + H_BUTTON;
        }

        pDDS->BltFast(x, y, _pBitmap, &r, 0);

        // if cancel button is not selected, display data about
        // selected device
        if (_nSelected != CANCEL_BUTTON)
        {
            // draw the info box
            x = X_INFOBOX;
            y = Y_INFOBOX;

            r.left   = X_INFO;
            r.top    = Y_INFO;
            r.right  = r.left + W_INFO;
            r.bottom = r.top  + H_INFO;

            pDDS->BltFast(x, y, _pBitmap, &r, 0);

            _dwTotalBlocks = 0;
            _dwFreeBlocks  = 0;

            // get the device data for display in other draw routine
            _cs.Enter();
            _dwTotalBlocks = _aData[_nSelected]._dwTotalBlocks;
            _dwFreeBlocks  = _aData[_nSelected]._dwFreeBlocks;
            _cs.Leave();

            x = X_INFOBOX + X_STARTBAR;
            y = Y_INFOBOX + Y_STARTBAR;

            // draw filled bar indicating percentage of device used
            if (_dwTotalBlocks)
            {
                r.left   = X_BAR;
                r.top    = Y_BAR;
                r.right  = r.left + 
                    (W_BAR * (_dwTotalBlocks - _dwFreeBlocks) / _dwTotalBlocks);
                r.bottom = r.top  + H_BAR;

                pDDS->BltFast(x, y, _pBitmap, &r, 0);
            }
        }
    }        

    return S_OK;
}

/********************************************************************
 * CVMUSelection::Draw
 *
 * Description
 *    Draw the prompt text and device data text (other verion of Draw 
 *    has already been called to draw the background and other 
 *    pictures).
 *
 * Parameters
 *    hdc           destination device context
 * 
 * Returns
 *    S_OK      drawn successfully
 ********************************************************************/
HRESULT CVMUSelection::Draw(HDC hdc)
{
    RECT r;

    // if selection is not cancel button, draw the device info
    if (_nSelected != CANCEL_BUTTON)
    {
        TCHAR szFormat[32];
        TCHAR szText[64];

        // set color, mode and font
        COLORREF clrOld  = SetTextColor(hdc, RGB(255, 255, 255));
        UINT     modeOld = SetBkMode(hdc, TRANSPARENT);
        HFONT    fontOld = (HFONT)SelectObject(hdc, _hFont);

        r.left   = X_INFOBOX + X_TEXT;
        r.top    = Y_INFOBOX + Y_TEXT;

        // display device ID
        LoadString(g_hInstance, IDS_DEVICE_TITLE, szFormat, 
                   sizeof(szFormat) / sizeof(szFormat[0]));
        _stprintf(szText, szFormat, TEXT('A') + (_nSelected >> 1), TEXT('1') + 
                  (_nSelected & 0x01));
        ExtTextOut(hdc, r.left, r.top, 0, NULL, szText, _tcslen(szText), NULL);

        r.left   = X_INFOBOX + X_TEXT;
        r.top    = Y_INFOBOX + Y_TEXT + H_TEXT;

        // display device data
        if (_dwTotalBlocks)
        {
            LoadString(g_hInstance, IDS_DEVICE_SIZE, szFormat, 
                       sizeof(szFormat) / sizeof(szFormat[0]));
            _stprintf(szText, szFormat, _dwFreeBlocks);
            ExtTextOut(hdc, r.left, r.top, 0, NULL, szText, _tcslen(szText), NULL);
        }

        // reset color, mode and font
        SelectObject(hdc, fontOld);
        SetBkMode(hdc, modeOld);
        SetTextColor(hdc, clrOld);

    }

    if (_szPrompt[0])
    {
        COLORREF clrOld  = SetTextColor(hdc, RGB(255, 0, 0));
        UINT     modeOld = SetBkMode(hdc, TRANSPARENT);
        HFONT    fontOld = (HFONT)SelectObject(hdc, _hFont);

        r.left   = X_PROMPT;
        r.top    = Y_PROMPT;

        ExtTextOut(hdc, r.left, r.top, 0, NULL, _szPrompt, _tcslen(_szPrompt), NULL);

        SelectObject(hdc, fontOld);
        SetBkMode(hdc, modeOld);
        SetTextColor(hdc, clrOld);
    }

    return S_OK;
}

/********************************************************************
 * CVMUSelection::Joystick
 *
 * Description
 *    Handles action based on user button press (directional button
 *    and joystick moves selection around,  A button selects current
 *    device or cancel button.
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
 ********************************************************************/
HRESULT CVMUSelection::Joystick(DWORD dwButtons, DWORD dwButtonsHeld, 
                                WORD x, WORD y)
{
    // check for abort from vmimime.dll
    if (WAIT_TIMEOUT != WaitForSingleObject(_hEventAbort, 0))
    {
        Stop();
        return S_OK;
    }

    // do initial set up
    if (_nSelected == INITIAL_SELECT)
    {
        _nDevices  = FindAvailableDevices();
        _nSelected = CANCEL_BUTTON;
        dwButtons = JOYSTICK_RA;
    }

    // if joystick moved, relate it to a direction button
    // press
    if (dwButtons & JOYSTICK_POS)
    {
        dwButtons = 0;

        POINT ptCursor = QueryCursorPosition(SCREEN_DEVICE);

        if (ptCursor.x > (X_CURSOR + OFFSET_CURSOR))
        {
            dwButtons = JOYSTICK_RA;
        }
        else if (ptCursor.x < (X_CURSOR - OFFSET_CURSOR))
        {
            dwButtons = JOYSTICK_LA;
        }
        else if (ptCursor.y > (Y_CURSOR + OFFSET_CURSOR))
        {
            dwButtons = JOYSTICK_DA;
        }
        else if (ptCursor.y < (Y_CURSOR - OFFSET_CURSOR))
        {
            dwButtons = JOYSTICK_UA;
        }
    }

    if (dwButtons)
    {
        // move selection left (through cancel button)
        if ((dwButtons & JOYSTICK_LA) || (dwButtons & JOYSTICK_UA))
        {
            _nSelected = (_nSelected == 0) ? CANCEL_BUTTON : _nSelected - 1;
            while (_nSelected != CANCEL_BUTTON)
            {
                if (_nDevices & (1 << _nSelected))
                {
                    break;
                }

                if (_nSelected)
                {
                    _nSelected--;
                }
                else
                {
                    _nSelected = CANCEL_BUTTON;
                }
            }
        }
        // move selection right (through cancel button)
        else if ((dwButtons & JOYSTICK_RA) || (dwButtons & JOYSTICK_DA))
        {
            _nSelected = (_nSelected == CANCEL_BUTTON) ? 0 : _nSelected + 1;
            while (_nSelected != CANCEL_BUTTON)
            {
                if (_nDevices & (1 << _nSelected))
                {
                    break;
                }

                _nSelected++;
            }
        }
        // select current device or cancel button
        else if (dwButtons & JOYSTICK_A)
        {
            if (_pdwResults)
            {
                if (_nSelected == CANCEL_BUTTON)
                {
                    *_pdwResults = DEVICE_SELECT_CANCEL; 
                }
                else
                {
                    *_pdwResults = (((DWORD)_nSelected >> 1) << 8) | 
                                   (_nSelected & 0x01);
                }
            }
            // user has made selection, stop device info thread
            Stop();
        }
    }

    return S_OK;
}

/********************************************************************
 * CVMUSelection::Start
 *
 * Description
 *    Starts thread that constantly updates device data.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK      thread started
 ********************************************************************/
HRESULT CVMUSelection::Start(void)
{
    // if thread is already running, nevermind
    if (_bRunning)
    {
        return S_FALSE;
    }

    // switch to secondary screen (will hide all regular game/browser
    // windows)
    HideCursor(SCREEN_DEVICE);
    SwitchScreen(SCREEN_DEVICE);

    // set status to thread running
    _bRunning = TRUE;

    // start thread
    CreateThread(NULL, 0, ThreadProc, (LPVOID)this, 0, &_idThread);

    return S_OK;
}

/********************************************************************
 * CVMUSelection::Stop
 *
 * Description
 *    Stops thread that constantly updates device data.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK      thread stopped
 ********************************************************************/
HRESULT CVMUSelection::Stop(void)
{
    // set status to thread not running
    _bRunning = FALSE;

    // switch back to normal screen (hides device selection)
    SwitchScreen(SCREEN_DEFAULT);
    ShowCursor(SCREEN_DEVICE);

    // set event indicating selection is finished
    if (_hEventDone)
    {
        SetEvent(_hEventDone);               
    }

    // if thread was not created, delete this object (thread will 
    // delete it if the thread was created)
    if (!_idThread)
    {
        delete this;
    }

    return S_OK;
}

/********************************************************************
 * CVMUSelection::SetData
 *
 * Description
 *    Sets device data for given device (wrapped in critical section
 *    since device data is used by more than thread).
 *
 * Parameters
 *    nDevice       device ID (0 - 7)
 *    dwTotalBlocks total blocks available on current device
 *    dwFreeBlocks  total blocks free on current device
 * 
 * Returns
 *    None
 ********************************************************************/
void CVMUSelection::SetData(BYTE nDevice, DWORD dwTotalBlocks, DWORD dwFreeBlocks)
{
    // validate parameters
    if (nDevice < NUM_DEVICES)
    {
        // set device data
        _cs.Enter();
        _aData[nDevice]._dwTotalBlocks = dwTotalBlocks;
        _aData[nDevice]._dwFreeBlocks  = dwFreeBlocks;
        _cs.Leave();
    }
}

/********************************************************************
 * CVMUSelection::FindAvailableDevices
 *
 * Description
 *    Enumerates all devices currently plugged in and stores those
 *    available devices in flags.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    BYTE      flags indicating which devices are plugged in
 ********************************************************************/
BYTE CVMUSelection::FindAvailableDevices(void)
{
    BYTE nDevices = 0;

    // enumerate looking for plugged in devices
    MapleEnumerateDevices(MDT_STORAGE, EnumMapleDevicesCallback1, 
                         (LPVOID)(&nDevices), 0);

    return nDevices;
}

/********************************************************************
 * CVMUSelection::FindAvailableControllers
 *
 * Description
 *    Enumerates all controllers currently plugged in and stores those
 *    available controllers in flags.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    BYTE      flags indicating which controllers are plugged in
 ********************************************************************/
BYTE CVMUSelection::FindAvailableControllers(void)
{
    BYTE nControllers = 0;

    // enumerate looking for plugged in controllers
    MapleEnumerateDevices(MDT_CONTROLLER, EnumMapleDevicesCallback2, 
                          (LPVOID)(&nControllers), 0);

    return nControllers;
}

/********************************************************************
 * CVMUSelection::EnumMapleDevicesCallback3
 *
 * Description
 *    Enumeration of devices callback. Extracts data about the current
 *    device, and saves it for later. Data saving is wrapped in a 
 *    critical section since two threads access the data.
 *
 * Parameters
 *    pMDI      current device data
 * 
 * Returns
 *    TRUE      keep enumerating
 ********************************************************************/
BOOL CVMUSelection::EnumMapleDevicesCallback3(LPCMAPLEDEVICEINSTANCE pMDI)
{
    // validate parameters
    if (!pMDI)
    {
        return FALSE;
    }

    // get device data for current device
    BYTE nDevice = (BYTE)((pMDI->dwPort << 1) + pMDI->dwDevNum - 1);
    CVMUDeviceData *pData = _aData + nDevice;
    
    // if no device created yet, create one
    if (!pData->_pDevice)
    {
        SetData(nDevice, 0, 0);

        IUnknown *pUnknown;
        HRESULT hr = MapleCreateDevice(&pMDI->guidDevice, &pUnknown);
        if (SUCCEEDED(hr))
        {
            pUnknown->QueryInterface(_uuidof(IFlashDevice), 
                                     (LPVOID *)&(pData->_pDevice));
            pUnknown->Release();
        }
    }

    // could not create the device, keep enumerating
    if (!pData->_pDevice)
    {
        return TRUE;
    }

    pData->_bFound = TRUE;

    // get device data and set it in array
    FSDEVICEDESC Desc;
    memset(&Desc, 0, sizeof(Desc));
    Desc.dwSize = sizeof(Desc);
    Desc.dwFlags = FSDD_TOTAL_BLOCKS | FSDD_FREE_BLOCKS;

    if (FAILED(pData->_pDevice->GetDeviceDesc(&Desc)))
    {
        SetData(nDevice, 0, 0);
    }
    else
    {
        SetData(nDevice, Desc.dwTotalBlocks, Desc.dwFreeBlocks);
    }

    // keep enumerating
    return TRUE;
}

/********************************************************************
 * CVMUSelection::ThreadProc
 *
 * Description
 *    Constantly update devices data.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    0         thread result
 ********************************************************************/
DWORD CVMUSelection::ThreadProc(void)
{
    BYTE i;

    // leave thread when stopped
    while (_bRunning)
    {
        // assume we have no devices
        for (i = 0; i < NUM_DEVICES; i++)
        {
            _aData[i]._bFound = FALSE;
        }

        // look for devices and device data
        MapleEnumerateDevices(MDT_STORAGE, EnumMapleDevicesCallback3, 
                              (LPVOID)this, 0);

        // destroy all devices no longer found (removed by user)
        for (i = 0; i < NUM_DEVICES; i++)
        {
            if (!_aData[i]._bFound && _aData[i]._pDevice)
            {
                _aData[i]._pDevice->Release();
                _aData[i]._pDevice = NULL;
                SetData(i, 0, 0);
            }
        }
    }

    return 0;
}

/********************************************************************
 * CVMUSelection::EnumMapleDevicesCallback1
 *
 * Description
 *    Enumeration of devices callback. Stores flags for which devices
 *    are available (plugged in).
 *
 * Parameters
 *    pMDI      current device data
 *    pvData    enumeration context data (pointer to device flags)
 * 
 * Returns
 *    TRUE      keep enumerating
 ********************************************************************/
BOOL CVMUSelection::EnumMapleDevicesCallback1(LPCMAPLEDEVICEINSTANCE pMDI, 
                                              LPVOID pvData)
{
    // validate parameters
    if (!pvData)
    {
        return FALSE;
    }

    BYTE *pnDevices = (BYTE *)pvData;

    // set flag for current device in available devices flags
    *pnDevices |= 1 << ((pMDI->dwPort * 2) + pMDI->dwDevNum - 1);

    return TRUE;
}

/********************************************************************
 * CVMUSelection::EnumMapleDevicesCallback2
 *
 * Description
 *    Enumeration of controllers callback. Stores flags for which 
 *    controllers are available (plugged in).
 *
 * Parameters
 *    pMDI      current device data
 *    pvData    enumeration context data (pointer to controller flags)
 * 
 * Returns
 *    TRUE      keep enumerating
 ********************************************************************/
BOOL CVMUSelection::EnumMapleDevicesCallback2(LPCMAPLEDEVICEINSTANCE pMDI, 
                                              LPVOID pvData)
{
    // validate parameters
    if (!pvData)
    {
        return FALSE;
    }

    BYTE *pnControllers = (BYTE *)pvData;

    // set flag for current controller in available controller flags
    *pnControllers |= 1 << pMDI->dwPort;

    return TRUE;
}

/********************************************************************
 * CVMUSelection::EnumMapleDevicesCallback3
 *
 * Description
 *    Enumeration of controllers callback. Calls object's version of
 *    callback for actual callback handling.
 *
 * Parameters
 *    pMDI      current device data
 *    pvData    enumeration context data (pointer to owning object)
 * 
 * Returns
 *    TRUE      keep enumerating
 ********************************************************************/
BOOL CVMUSelection::EnumMapleDevicesCallback3(LPCMAPLEDEVICEINSTANCE pMDI, 
                                              LPVOID pvData)
{
    // validate parameters
    if (!pvData)
    {
        return FALSE;
    }

    // call object's version of enumeration handler
    CVMUSelection *pVMUSelection = (CVMUSelection *)pvData;

    return pVMUSelection->EnumMapleDevicesCallback3(pMDI);
}

/********************************************************************
 * CVMUSelection::ThreadProc
 *
 * Description
 *    Thread procudure. Calls object's version of ThreadProc for 
 *    actual thread handling. Deletes object when thread is done.
 *
 * Parameters
 *    pvData    thread contect data (owning object pointer)
 * 
 * Returns
 *    0         thread result
 ********************************************************************/
DWORD WINAPI CVMUSelection::ThreadProc(LPVOID pvData)
{
    // validate parameters
    if (!pvData)
    {
        return 0;
    }

    CVMUSelection *pVMUSelection = (CVMUSelection *)pvData;

    // call object's version of thread handler
    DWORD dwRet = pVMUSelection->ThreadProc();

    // delete owning object
    delete pVMUSelection;

    return dwRet;
}

/********************************************************************
 * Global variables
 ********************************************************************/
CCriticalSection g_csDeviceScreen;      // critical section for wrapping
                                        // around data accesses of data
                                        // used in multiple threads

/********************************************************************
 * GetVMUDevice
 *
 * Description
 *    This function is made available for VMI Mime Filter (vmimime.dll)
 *    for device selection. It can show UI or it can just return the
 *    port (controller) and device if the application already knows to
 *    which device the file(s) should go.
 *   
 *    This version displays a UI allowing the user to pick to which 
 *    device he wants to store the data.
 *
 * Parameters
 *    dwType        reserved (0)
 *    hEventAbort   event signalled if vmimime.dll aborts procedure
 *    pnPort        filled in with user's controller selection (0-3)
 *    pnDevice      filled in with user's device selection (0-1)
 * 
 * Returns
 *    S_OK          user selected a destination device
 *    E_INVALIDARG  NULL required data
 *    E_FAIL        internal data failure
 *    E_ABORT       procedure aborted
 *    S_FALSE       user canceled
 ********************************************************************/
HRESULT CALLBACK GetVMUDevice(DWORD dwType, HANDLE hEventAbort, 
                              BYTE *pnPort, BYTE *pnDevice)
{
    // validate parameters
    if (!hEventAbort || !pnPort || !pnDevice)
    {
        return E_INVALIDARG;
    }

    // validate internal data
    if (!g_hwndGame)
    {
        return E_FAIL;
    }

    // create finished event    
    HANDLE hEventGetDevice = CreateEvent(NULL, TRUE, FALSE, EVENT_DEVICE_SCREEN_DONE);
    if (!hEventGetDevice)
    {
        return E_FAIL;
    }

    g_csDeviceScreen.Enter();

    // start the device selection screen by posting message to main thread.
    DWORD dwResults = 0;
    PostMessage(g_hwndGame, WM_GETDEVICE, (WPARAM)hEventAbort, 
                (LPARAM)(&dwResults));

    // wait for the user to make selection or cancel.
    WaitForSingleObject(hEventGetDevice, INFINITE);

    g_csDeviceScreen.Leave();

    CloseHandle(hEventGetDevice);

    // get user selection 

    HRESULT hr;
    if (dwResults == DEVICE_SELECT_ABORT)
    {
        hr = E_ABORT;
    }
    else if (dwResults == DEVICE_SELECT_CANCEL)
    {
        hr = S_FALSE;
    }
    else
    {
        *pnPort   = (BYTE)((((DWORD)dwResults) >> 8) & 0xff);
        *pnDevice = (BYTE)(((DWORD)dwResults) & 0xff);
        hr = S_OK;
    }

    return hr;
}

/********************************************************************
 * ShowVMUMessage
 *
 * Description
 *    Posts a message to pop up a message to the user.
 *
 * Parameters
 *    hr        error code of message to display
 *    bLeaveUp  leave vmu message up until next message comes through
 * 
 * Returns
 *    S_OK      request handled
 ********************************************************************/
HRESULT CALLBACK ShowVMUMessage(HRESULT hr, BOOL bLeaveUp)
{
    // post message to main message loop to handle request
    PostMessage(g_hwndGame, WM_SHOWMSG, (WPARAM)bLeaveUp, (LPARAM)hr);

    return S_OK;
}
