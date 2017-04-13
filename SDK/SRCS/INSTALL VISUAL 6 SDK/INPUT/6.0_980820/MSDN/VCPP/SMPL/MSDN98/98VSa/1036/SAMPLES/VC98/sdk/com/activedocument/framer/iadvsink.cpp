/*
 * IADVSINK.CPP
 * IAdviseSink for Document Objects CSite class
 *
 * Copyright (c)1995-1997 Microsoft Corporation, All Rights Reserved
 */


#include "framer.h"


/*
 * CImpIAdviseSink::CImpIAdviseSink
 * CImpIAdviseSink::~CImpIAdviseSink
 *
 * Parameters (Constructor):
 *  pSite           PCSite of the site we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIAdviseSink::CImpIAdviseSink(PCSite pSite
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pSite=pSite;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIAdviseSink::~CImpIAdviseSink(void)
    {
    return;
    }




/*
 * CImpIAdviseSink::QueryInterface
 * CImpIAdviseSink::AddRef
 * CImpIAdviseSink::Release
 *
 * Purpose:
 *  IUnknown members for CImpIAdviseSink object.
 */

STDMETHODIMP CImpIAdviseSink::QueryInterface(REFIID riid, void **ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIAdviseSink::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIAdviseSink::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * Unused members in CImpIAdviseSink
 *  OnDataChange
 *  OnViewChange
 *  OnRename
 *  OnSave
 */

STDMETHODIMP_(void) CImpIAdviseSink::OnDataChange(LPFORMATETC pFEIn
    , LPSTGMEDIUM pSTM)
    {
    return;
    }

STDMETHODIMP_(void) CImpIAdviseSink::OnViewChange(DWORD dwAspect
    , LONG lindex)
    {    
    return;
    }

STDMETHODIMP_(void) CImpIAdviseSink::OnRename(LPMONIKER pmk)
    {
    return;
    }

STDMETHODIMP_(void) CImpIAdviseSink::OnSave(void)
    {
    return;
    }




/*
 * CImpIAdviseSink::OnClose
 *
 * Purpose:
 *  Informs the advise sink that the OLE object has closed and is
 *  no longer bound in any way.  We use this to do a File/Close
 *  to delete the object since we don't hold onto any.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

STDMETHODIMP_(void) CImpIAdviseSink::OnClose(void)
    {
	//This does the same as File/Close
	//Not quite because CFrame::Close requires some synchronous
	//calls that will fail if done here, so just post a message to
	//do this
    //m_pSite->m_pFR->Close();

	HWND		hwnd;
	m_pSite->m_pFR->GetWindow(&hwnd);
	PostMessage(
		hwnd, 
		WM_COMMAND,
		MAKELONG(IDM_FILECLOSE, 0),
		0);
    return;
    }
