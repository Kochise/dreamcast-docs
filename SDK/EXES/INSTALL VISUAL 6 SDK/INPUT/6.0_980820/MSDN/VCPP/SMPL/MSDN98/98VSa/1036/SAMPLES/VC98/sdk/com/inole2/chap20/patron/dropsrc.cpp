/*
 * DROPSRC.CPP
 * Patron Chapter 20
 *
 * Implementation of a DropSource object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CDropSource::CDropSource
 * CDropSource::~CDropSource
 *
 * Constructor Parameters:
 *  None
 */

CDropSource::CDropSource(void)
    {
    m_cRef=0;
    return;
    }

CDropSource::~CDropSource(void)
    {
    return;
    }




/*
 * CDropSource::QueryInterface
 * CDropSource::AddRef
 * CDropSource::Release
 *
 * Purpose:
 *  IUnknown members for CDropSource object.
 */

STDMETHODIMP CDropSource::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IDropSource==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CDropSource::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CDropSource::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }





/*
 * CDropSource::QueryDragContinue
 *
 * Purpose:
 *  Determines whether to continue a drag operation or cancel it.
 *
 * Parameters:
 *  fEsc            BOOL indicating that the ESC key was pressed.
 *  grfKeyState     DWORD providing states of keys and mouse buttons
 *
 * Return Value:
 *  HRESULT         DRAGDROP_S_CANCEL to stop the drag,
 *                  DRAGDROP_S_DROP to drop the data where it is,
 *                  or NOERROR to continue.
 */

STDMETHODIMP CDropSource::QueryContinueDrag(BOOL fEsc, DWORD grfKeyState)
    {
    if (fEsc)
        return ResultFromScode(DRAGDROP_S_CANCEL);

    if (!(grfKeyState & MK_LBUTTON))
        return ResultFromScode(DRAGDROP_S_DROP);

    return NOERROR;
    }






/*
 * CDropSource::GiveFeedback
 *
 * Purpose:
 *  Provides cursor feedback to the user since the source task
 *  always has the mouse capture.  We can also provide any other
 *  type of feedback above cursors if we so desire.
 *
 * Parameters:
 *  dwEffect        DWORD effect flags returned from the last target
 *
 * Return Value:
 *  HRESULT         NOERROR if you set a cursor yourself or
 *                  DRAGDROP_S_USEDEFAULTCURSORS to let OLE do
 *                  the work.
 */

STDMETHODIMP CDropSource::GiveFeedback(DWORD dwEffect)
    {
    return ResultFromScode(DRAGDROP_S_USEDEFAULTCURSORS);
    }
