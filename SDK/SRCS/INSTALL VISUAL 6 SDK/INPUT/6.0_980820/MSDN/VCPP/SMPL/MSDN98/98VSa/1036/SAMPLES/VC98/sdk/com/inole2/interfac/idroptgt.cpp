/*
 * IDROPTGT.CPP
 *
 * Template implementation of a DropTarget object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "idroptgt.h"


/*
 * CDropTarget::CDropTarget
 * CDropTarget::~CDropTarget
 *
 * Constructor Parameters:
 *  pBack           LPVOID back pointer to whatever we're related to.
 */

CDropTarget::CDropTarget(LPVOID pBack)
    {
    m_cRef=0;
    m_pBack=pBack;
    return;
    }


CDropTarget::~CDropTarget(void)
    {
    return;
    }




/*
 * CDropTarget::QueryInterface
 * CDropTarget::AddRef
 * CDropTarget::Release
 *
 * Purpose:
 *  Non-delegating IUnknown members for CDropTarget.
 */

STDMETHODIMP CDropTarget::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IDropTarget==riid)
        *ppv=(LPVOID)this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CDropTarget::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CDropTarget::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }






/*
 * CDropTarget::DragEnter
 *
 * Purpose:
 *  Indicates that data in a drag operation has been dragged over
 *  our window that's a potential target.  We are to decide if it's
 *  something in which we're interested.
 *
 * Parameters:
 *  pIDataSource    LPDATAOBJECT providing the source data.
 *  grfKeyState     DWORD flags: states of keys and mouse buttons.
 *  pt              POINTL coordinates in the client space of
 *                  the document.
 *  pdwEffect       LPDWORD into which we'll place the appropriate
 *                  effect flag for this point.
 */

STDMETHODIMP CDropTarget::DragEnter(LPDATAOBJECT pIDataSource
    , DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect)
    {
    *pdwEffect=DROPEFFECT_NONE;
    return NOERROR;
    }






/*
 * CDropTarget::DragOver
 *
 * Purpose:
 *  Indicates that the mouse was moved inside the window represented
 *  by this drop target.  This happens on every WM_MOUSEMOVE, so
 *  this function should be very efficient.
 *
 * Parameters:
 *  grfKeyState     DWORD providing the current keyboard and
 *                  mouse states
 *  pt              POINTL where the mouse currently is.
 *  pdwEffect       LPDWORD in which to store the effect flag
 *                  for this point.
 */

STDMETHODIMP CDropTarget::DragOver(DWORD grfKeyState, POINTL pt
    , LPDWORD pdwEffect)
    {
    //Since we can always drop, we just return effect flags
    *pdwEffect=DROPEFFECT_MOVE;

    if (grfKeyState & MK_CONTROL)
        *pdwEffect=DROPEFFECT_COPY;

    return NOERROR;
    }






/*
 * CDropTarget::DragLeave
 *
 * Purpose:
 *  Informs the drop target that the operation has left its window.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CDropTarget::DragLeave(void)
    {
    return NOERROR;
    }





/*
 * CDropTarget::Drop
 *
 * Purpose:
 *  Instructs the drop target to paste the data that was just now
 *  dropped on it.
 *
 * Parameters:
 *  pIDataSource    LPDATAOBJECT from which we'll paste.
 *  grfKeyState     DWORD providing current keyboard/mouse state.
 *  pt              POINTL at which the drop occurred.
 *  pdwEffect       LPDWORD in which to store what you did.
 */

STDMETHODIMP CDropTarget::Drop(LPDATAOBJECT pIDataSource
    , DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect)
    {
    return NOERROR;
    }
