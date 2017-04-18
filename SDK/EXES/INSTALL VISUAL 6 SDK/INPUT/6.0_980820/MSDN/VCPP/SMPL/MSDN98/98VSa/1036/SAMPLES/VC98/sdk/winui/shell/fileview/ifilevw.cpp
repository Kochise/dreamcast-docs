//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright  1994-1996  Microsoft Corporation.  All Rights Reserved.
//
//	PROGRAM:	IFILEVW.CPP	
//
//	PURPOSE: IFileViewer interface implementation for a FileViewer.
// Custom FileViewer objects should modify the Show member
// to suit its own needs. 
//
//	PLATFORMS:	Windows 95
//
//	SPECIAL INSTRUCTIONS: N/A
//

#include "fileview.h"

//
//   FUNCTION: CImpIFileViewer::CImpIFileViewer	
//
//   PURPOSE:   Constructor
//
//   PARAMETERS: 
//	  pObj            PCFileViewer of the object we're in.
//    pUnkOuter       LPUNKNOWN to which we delegate.
//
CImpIFileViewer::CImpIFileViewer(PCFileViewer pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }	 
//
//   FUNCTION: 	CImpIFileViewer::~CImpIFileViewer
//
//   PURPOSE:   Destructor
//
CImpIFileViewer::~CImpIFileViewer(void)
    {
    return;			   
    }
//
//   FUNCTION: 	CImpIFileViewer::QueryInterface
//							 CImpIFileViewer::AddRef	  
//							 CImpIFileViewer::Release
//
//   PURPOSE:    IUnknown members for CImpIFileViewer object that only delegate.
//
STDMETHODIMP CImpIFileViewer::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIFileViewer::AddRef(void)
    {
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIFileViewer::Release(void)
    {
    return m_pUnkOuter->Release();
    }
//
//   FUNCTION:CImpIFileViewer::PrintTo 	
//
//   PURPOSE:    Asks a FileViewer to print the file that came through
//  IPersistFile::Load to a specific device with or without
//  any user interaction.  This function should not return
//  until the printing is complete.
//
//   PARAMETERS: 
//	    pszDriver       LPSTR with the path of the driver to use.  If NULL, use the default driver.
//      fSuppressUI     BOOL indicating if this function is to show any	UI or not.
//
//   RETURN VALUE:
//  HRESULT         NOERROR on success, error code otherwise.
//
STDMETHODIMP CImpIFileViewer::PrintTo(LPSTR pszDriver
    , BOOL fSuppressUI)
    {
     // Printing not implemented in this sample, but
     // make a stub call anyway.
    return m_pObj->PrintTo(pszDriver, fSuppressUI);
    }
//
//   FUNCTION: CImpIFileViewer::ShowInitialize	
//
//   PURPOSE:  Initializes everything necessary to display the FileViewer
//  window but does not show it.  The FileViewer should do all
//  the necessary pre-visible work here as this is the only
//  time the FileViewer is allowed to fail. 
//
//   PARAMETERS: 
//
//   RETURN VALUE:
//	   HRESULT         NOERROR or an appropriate error code such as
//                  E_UNEXPECTED, E_FAIL, or E_OUTOFMEMORY.
//
STDMETHODIMP CImpIFileViewer::ShowInitialize(LPFILEVIEWERSITE lpfsi)
    {
    return m_pObj->FileShowInit(lpfsi);
    }
//
//   FUNCTION:CImpIFileViewer::Show 	
//
//   PURPOSE:    Displays the FileViewer's window in which the file is
//  displayed.  This function cannot be called unless
//  Initialize has already been called.  If Initialize has
//  been called then this function is not allowed to fail and
//  should do little more than show the window and enter a
//  message loop, that is, perform no allocations or anything
//  else that may fail due to low-memory conditions.
//
//  Treat this function like a WinMain function.
//
//   PARAMETERS: 
//	    nCmdShow        int indicating how to initially show the FileViewer window.
//
//   RETURN VALUE:
//	    HRESULT         E_UNEXPECTED if Initalize has not been called, otherwise must be NOERROR.
//
STDMETHODIMP CImpIFileViewer::Show(LPFVSHOWINFO pvsi)
    {
    if (!m_pObj->m_fShowInit)
        return ResultFromScode(E_UNEXPECTED);

    m_pObj->FileShow(pvsi);
    return NOERROR;
    }
