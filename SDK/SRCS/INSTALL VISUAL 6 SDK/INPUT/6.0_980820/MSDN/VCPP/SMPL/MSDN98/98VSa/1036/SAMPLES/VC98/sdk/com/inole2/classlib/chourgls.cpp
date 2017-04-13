/*
 * CHOURGLS.CPP
 * Sample Code Class Libraries
 *
 * Implementation of the CHourglass class.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include <windows.h>
#include "classlib.h"


/*
 * CHourglass::CHourglass
 * CHourglass::~CHourglass
 *
 * Constructor Parameters (optional):
 *  hWnd            HWND of a window that wants capture.  Can
 *                  be NULL in which case it is ignored.
 */

CHourglass::CHourglass(void)
    {
    m_hCur=SetCursor(LoadCursor(NULL, IDC_WAIT));
    m_hWndCapture=NULL;
    return;
    }

CHourglass::CHourglass(HWND hWnd)
    {
    m_hCur=SetCursor(LoadCursor(NULL, IDC_WAIT));

    if (NULL!=hWnd)
        {
        m_hWndCapture=hWnd;
        SetCapture(hWnd);
        }

    return;
    }


CHourglass::~CHourglass(void)
    {
    if (NULL!=m_hWndCapture)
        ReleaseCapture();

    SetCursor(m_hCur);
    return;
    }
