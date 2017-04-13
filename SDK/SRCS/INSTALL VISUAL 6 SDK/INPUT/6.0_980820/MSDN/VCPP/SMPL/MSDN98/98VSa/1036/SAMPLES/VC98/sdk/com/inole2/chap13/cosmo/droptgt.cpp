/*
 * DROPTGT.CPP
 * Cosmo Chapter 13
 *
 * Implementation of the IDropTarget interface.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "cosmo.h"


/*
 * CDropTarget::CDropTarget
 * CDropTarget::~CDropTarget
 *
 * Constructor Parameters:
 *  pDoc            PCCosmoDoc of the document containing us.
 */

CDropTarget::CDropTarget(PCCosmoDoc pDoc)
    {
    m_cRef=0;
    m_pDoc=pDoc;

    m_pIDataObject=NULL;
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
 *  IUnknown members for CDropTarget object.
 */

STDMETHODIMP CDropTarget::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IDropTarget==riid)
        *ppv=this;

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
    if (0!=--m_cRef)
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
 *  something we're interested in or not.
 *
 * Parameters:
 *  pIDataSource    LPDATAOBJECT providing the source data.
 *  grfKeyState     DWORD flags: states of keys and mouse buttons.
 *  pt              POINTL coordinates in the document client space.
 *  pdwEffect       LPDWORD into which we'll place the
 *                  appropriate effect flag for this point.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CDropTarget::DragEnter(LPDATAOBJECT pIDataSource
    , DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect)
    {
    HWND        hWnd;

    /*
     * 1.  Check if we can paste from the pIDataSource we're
     *     provided. We already made this nice useful function
     *     to test.
     */

    m_pIDataObject=NULL;

    if (!m_pDoc->FQueryPasteFromData(pIDataSource))
        {
        *pdwEffect=DROPEFFECT_NONE;
        return NOERROR;
        }


    /*
     * 2.  We can always drop anywhere in our document,
     *     so pt is uninteresting.
     */


    /*
     * 3. We return either a COPY or MOVE effect flag, depending on
     *    the state of the grfKeyState flags.  We MOVE on no key or
     *    Shift key, COPY on Ctrl key.
     */

    //Default is move
    *pdwEffect=DROPEFFECT_MOVE;

    if (grfKeyState & MK_CONTROL)
        *pdwEffect=DROPEFFECT_COPY;

    /*
     * 4. We really don't need to keep the IDataObject around since
     *    we're not interested in it in DragOver.  However, we'll
     *    save it just for demonstration.
     */
    m_pIDataObject=pIDataSource;
    m_pIDataObject->AddRef();

    /*
     * 5.  We always accept drops of our data on us, so we only need
     *     to provide some UI feedback here which we do by inverting
     *     the edge of the polyline window in this document.  We'll
     *     remove this in DragLeave and in Drop.  DragOver won't
     *     effect it since we can always drop.
     *
     *     Since we're inverting a border, insure that this window is
     *     on top.
     */

    hWnd=m_pDoc->Window();
    BringWindowToTop(hWnd);
    UpdateWindow(hWnd);
    m_pDoc->DropSelectTargetWindow();

    return NOERROR;
    }






/*
 * CDropTarget::DragOver
 *
 * Purpose:
 *  Indicates that the mouse was moved inside the window represented
 *  by this drop target. This happens on every WM_MOUSEMOVE, so this
 *  function should be very efficient.
 *
 * Parameters:
 *  grfKeyState     DWORD providing current keyboard/mouse states
 *  pt              POINTL where the mouse currently is.
 *  pdwEffect       LPDWORD to store the effect flag for this point.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CDropTarget::DragOver(DWORD grfKeyState, POINTL pt
    , LPDWORD pdwEffect)
    {
    if (NULL==m_pIDataObject)
        {
        *pdwEffect=DROPEFFECT_NONE;
        return NOERROR;
        }

    //We can always drop; return effect flags based on keys.
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
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CDropTarget::DragLeave(void)
    {
    //1.  Remove the UI feedback
    m_pDoc->DropSelectTargetWindow();

    //2.  Release the held IDataObject
    ReleaseInterface(m_pIDataObject);
        
    return NOERROR;
    }





/*
 * CDropTarget::Drop
 *
 * Purpose:
 *  Instructs the drop target to paste data that was just now
 *  dropped on it.
 *
 * Parameters:
 *  pIDataSource    LPDATAOBJECT from which we'll paste.
 *  grfKeyState     DWORD providing current keyboard/mouse state.
 *  pt              POINTL at which the drop occurred.
 *  pdwEffect       LPDWORD to store what you do with the data.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CDropTarget::Drop(LPDATAOBJECT pIDataSource
    , DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect)
    {
    BOOL        fRet=TRUE;

    *pdwEffect=DROPEFFECT_NONE;

    if (NULL==m_pIDataObject)
        return ResultFromScode(E_FAIL);

    //1.  Remove the UI feedback, release pointer
    DragLeave();
    
    //No point in drag-drop to ourselves (for Cosmo, at least)
    if (m_pDoc->m_fDragSource)
        return ResultFromScode(E_FAIL);

    //2.  Try a paste
    fRet=m_pDoc->PasteFromData(pIDataSource);

    //3.  Store the effect
    if (!fRet)
        return ResultFromScode(E_FAIL);

    *pdwEffect=DROPEFFECT_MOVE;

    if (grfKeyState & MK_CONTROL)
        *pdwEffect=DROPEFFECT_COPY;

    return NOERROR;
    }
