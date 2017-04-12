/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// Commands.cpp : implementation file
//

#include "stdafx.h"
#include "WndTabs.h"
#include "Commands.h"
#include "TabManagerWindow.h"
#include "DevStudioWnd.h"
#include "DSWindow.h"
#include "TabsWindow.h"
#include "DS_MDIWnd.h"
#include "Options.h"
#include "Config.h"
#include "HHSupp.h"
#include "Help\HelpIDs.h"
#include "AddInComm\AddInComm.h"
#include "Extensions.h"
#include "VCVerMgr.h"
#include "MainFrame.h"
#include "3rdParty\WWhizInterface2.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTabManagerWindow * pGlobalActiveManager  = NULL;
CDSWindow *         pGlobalActiveDSWindow = NULL;
CDS_MDIWnd *        pGlobalMDIManager     = NULL;

CString              CCommands::m_sPositionsFile;
CString              CCommands::m_sWorkspacePath;
CCommands::Positions CCommands::m_Positions;

static bool bIsWorkspaceOpen = false;

/////////////////////////////////////////////////////////////////////////////
// locating a window through it's title:

HWND    __searchWnd;
int     __searchWnd_ttl_len;

BOOL CALLBACK __enumerator(HWND hwnd, LPARAM lParam)
{
    if (GetWindowTextLength(hwnd) != __searchWnd_ttl_len)
    {
        return TRUE;
    }

    char buffer[1024];

    GetWindowText(hwnd, buffer, sizeof(buffer));
    if (!strcmp(buffer, (char *)lParam))
    {
        // ignore edit controls
        ::GetClassName(hwnd, buffer, sizeof(buffer));
        if (strcmp(buffer, "Edit"))
        {
            __searchWnd = hwnd;
            return FALSE;
        }
    }

    return TRUE;
}


HWND GetHWND(LPCTSTR cTitle)
{
    ASSERT(g_pDevStudioWnd->m_hWnd != NULL);
    __searchWnd = NULL;
    __searchWnd_ttl_len = strlen(cTitle);
    ::EnumChildWindows(
        pGlobalMDIManager->m_hWnd? pGlobalMDIManager->m_hWnd :
        g_pDevStudioWnd->m_hWnd, __enumerator, (LPARAM)cTitle);
    return __searchWnd;
}

HWND GetHWND(CComBSTR& bStr)
{
    CString cStr = bStr;
    return GetHWND(cStr);
}

HWND GetHWND(IGenericWindow *pWindow)
{
    CComBSTR bStr;
    pWindow->get_Caption(&bStr);
    return GetHWND(bStr);
}



/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CCommands

CCommands::CCommands()
{
    m_pApplication = NULL;
    m_pApplicationEventsObj = NULL;
    m_pDebuggerEventsObj = NULL;

    m_Positions.data.RemoveAll();
    m_Positions.iActiveTab = 0;
    
    pGlobalMDIManager = new CDS_MDIWnd();
}

void CCommands::Cleanup()
{
    WT_FN_TRACE("Cleanup");
    WT_ASSERT (!theApp.m_pMainWnd  ||  
               ::IsWindow(theApp.m_pMainWnd->GetSafeHwnd()));
    if (::IsWindow(theApp.m_pMainWnd->GetSafeHwnd()))
    {
        g_pMainFrame->m_bCanClose = true;
        theApp.m_pMainWnd->ShowWindow(SW_HIDE);
        theApp.m_pMainWnd->SetParent(NULL);
    	theApp.m_pMainWnd->SendMessage(WM_CLOSE);
        theApp.m_pMainWnd = NULL;
    }
    if (pGlobalTabs)
    {
        delete pGlobalActiveDSWindow;
        pGlobalActiveDSWindow = NULL;
        delete pGlobalMDIManager;
        pGlobalMDIManager = NULL;
        delete pGlobalTabs;
        pGlobalTabs = NULL;
    }
}

CCommands::~CCommands()
{
    ASSERT (m_pApplication != NULL);
    m_pApplication->Release();
}

void CCommands::SetApplicationObject(IApplication* pApplication)
{
    // This function assumes pApplication has already been AddRef'd
    //  for us, which CDSAddIn did in its QueryInterface call
    //  just before it called us.
    m_pApplication = pApplication;

    // Create Application event handlers
    XApplicationEventsObj::CreateInstance(&m_pApplicationEventsObj);
    m_pApplicationEventsObj->AddRef();
    m_pApplicationEventsObj->Connect(m_pApplication);
    m_pApplicationEventsObj->m_pCommands = this;

    // Create Debugger event handler
    m_pDebuggerEventsObj = NULL;
//  CComPtr<IDispatch> pDebugger;
//  if (SUCCEEDED(m_pApplication->get_Debugger(&pDebugger)) 
//      && pDebugger != NULL)
//  {
//      XDebuggerEventsObj::CreateInstance(&m_pDebuggerEventsObj);
//      m_pDebuggerEventsObj->AddRef();
//      m_pDebuggerEventsObj->Connect(pDebugger);
//      m_pDebuggerEventsObj->m_pCommands = this;
//  }

}

void CCommands::UnadviseFromEvents()
{
    ASSERT (m_pApplicationEventsObj != NULL);
    m_pApplicationEventsObj->Disconnect(m_pApplication);
    m_pApplicationEventsObj->Release();
    m_pApplicationEventsObj = NULL;
  
    if (m_pDebuggerEventsObj != NULL)
    {
        // Since we were able to connect to the Debugger events, we
        //  should be able to access the Debugger object again to
        //  unadvise from its events (thus the VERIFY_OK below--see stdafx.h).
        CComPtr<IDispatch> pDebugger;
        VERIFY_OK(m_pApplication->get_Debugger(&pDebugger));
        ASSERT (pDebugger != NULL);
        m_pDebuggerEventsObj->Disconnect(pDebugger);
        m_pDebuggerEventsObj->Release();
        m_pDebuggerEventsObj = NULL;
    }
}


/////////////////////////////////////////////////////////////////////////////
// Event handlers

// Application events

HRESULT CCommands::XApplicationEvents::BeforeBuildStart()
{
    WT_MANAGE_STATE();
    return S_OK;
}

HRESULT CCommands::XApplicationEvents::BuildFinish(long nNumErrors, long nNumWarnings)
{
    WT_MANAGE_STATE();

    // A build command issues an implicit "Save All".  The only problem is
    // that DevStudio updates the names of the saved windows (i.e. removes
    // the asterisks) only after it finishes building the project.
    // We'll catch that here:
    WT_L2_TRACE("Build Finish\n");
    pGlobalActiveManager->PostUpdateMessage();

    return S_OK;
}

HRESULT CCommands::XApplicationEvents::BeforeApplicationShutDown()
{
    WT_MANAGE_STATE();

	if( bIsWorkspaceOpen )
	{
		WritePositionsFile();
	}
    Cleanup();
    return S_OK;
}

HRESULT CCommands::XApplicationEvents::DocumentOpen(IDispatch* theDocument)
{
    static boolean bIsAutoOpen = false;

    WT_MANAGE_STATE();

    if (theDocument  &&  cfg_bAutoOpenAlt  &&  !bIsAutoOpen  &&
        !CCommands::IsWorkspaceOpening())
    {
        bIsAutoOpen = true;
        CWnd *pWndOld = pGlobalMDIManager->GetTopWindow();
        BSTR strTmp;
        CString cStr;
        CComQIPtr<IGenericDocument, &IID_IGenericDocument_Resolved> 
            pDocument(theDocument);
        
        if (pDocument)
        {
            pDocument->get_FullName(&strTmp);
            cStr = strTmp;
            if (pGlobalTabs)            
            {
                pGlobalTabs->m_pCommands->DoHeaderFlip(cStr,
                    cfg_bUseWorkspaceUtils, false, false);
            }
        }

        pGlobalMDIManager->SendMessage(WM_MDIACTIVATE, 
            (WPARAM)pWndOld->m_hWnd, 0);

        bIsAutoOpen = false;
    }

    return S_OK;
}

HRESULT CCommands::XApplicationEvents::BeforeDocumentClose(IDispatch* theDocument)
{    
    WT_MANAGE_STATE();
    return S_OK;     
}

HRESULT CCommands::XApplicationEvents::DocumentSave(IDispatch* theDocument)
{
    WT_MANAGE_STATE();

    WT_L2_TRACE("Document Saved\n");

    // we want to make sure that the tabs are updated if the user issues a
    // "Save All" command - if an inactive window gets saved, the asterisk
    // will be removed without WndTabs otherwise knowing it
    pGlobalActiveManager->SetDirty();

    return S_OK;
}

HRESULT CCommands::XApplicationEvents::NewDocument(IDispatch* theDocument)
{
    WT_MANAGE_STATE();
    return S_OK;
}

HRESULT CCommands::XApplicationEvents::WindowActivate(IDispatch* theWindow)
{
    WT_MANAGE_STATE();
    return S_OK;
}

HRESULT CCommands::XApplicationEvents::WindowDeactivate(IDispatch* theWindow)
{
    WT_MANAGE_STATE();
    return S_OK;
}

bool CCommands::IsWorkspaceOpening()
{
    if (bIsWorkspaceOpen)
    {
        return m_Positions.data.GetSize() != 0;
    }

    return false;    
}

HRESULT CCommands::XApplicationEvents::WorkspaceOpen()
{
    WT_MANAGE_STATE();

    ::GetCurrentDirectory(_MAX_PATH, m_sWorkspacePath.GetBuffer(_MAX_PATH));
    m_sWorkspacePath.ReleaseBuffer();
    
    // Make sure it ends in a closing backslash.
    if (m_sWorkspacePath[m_sWorkspacePath.GetLength() - 1] != '\\')
    {
        m_sWorkspacePath += "\\";
    }

    // try to find a locked .ncb file and assume it belongs to the active
    // workspace
    HANDLE FindHandle;
    WIN32_FIND_DATA fd;
    CString s, s2;

    m_sPositionsFile.Empty();

    FindHandle = FindFirstFile(m_sWorkspacePath + "*.ncb", &fd);
    if (FindHandle != INVALID_HANDLE_VALUE)
    {
        do
        {
            s = m_sWorkspacePath;
            s += fd.cFileName;
            s2 = s;
            s += "___temp.tmp";
            if (MoveFile(s2, s) == 0)
            {
                int err = GetLastError();    
                if (err = ERROR_SHARING_VIOLATION)
                {
                    m_sPositionsFile = m_sWorkspacePath;
                    m_sPositionsFile += fd.cFileName;
                    m_sPositionsFile.Delete(m_sPositionsFile.GetLength() - 3, 3);
                    m_sPositionsFile += "positions";
                    break;
                }
            }
            else
            {
                // rename to original name
                MoveFile(s, s2);
            }
        } while (FindNextFile(FindHandle, &fd));

        FindClose(FindHandle);
    }

    ReadPositionsFile();

    if (cfg_bAutoOpenAlt)
    {
        pGlobalTabs->m_pCommands->FlashWindows();
    }

    bIsWorkspaceOpen = true;

    WWhizInterface *pWWI = theApp.GetWWhizInterface();
    if (pWWI)
    {
        try
        {
            pWWI->SetWorkspaceLocation();
            pWWI->RefreshFileList();
        }
        catch (...)
        {
            theApp.ReportWWhizInterfaceException();
        }
    }

    return S_OK;
}

HRESULT CCommands::XApplicationEvents::WorkspaceClose()
{
    WT_MANAGE_STATE();
    WritePositionsFile();
    bIsWorkspaceOpen = false;
    m_sPositionsFile.Empty();
    m_Positions.data.RemoveAll();
    m_Positions.iActiveTab = 0;

    WWhizInterface *pWWI = theApp.GetWWhizInterface(false);
    if (pWWI)
    {
        try
        {
            pWWI->RemoveAllFiles();
        }
        catch (...)
        {
            theApp.ReportWWhizInterfaceException();
        }
    }

    return S_OK;
}

HRESULT CCommands::XApplicationEvents::NewWorkspace()
{
    WT_MANAGE_STATE();
    WWhizInterface *pWWI = theApp.GetWWhizInterface(false);
    if (pWWI)
    {
        try
        {
            pWWI->RemoveAllFiles();
        }
        catch (...)
        {
            theApp.ReportWWhizInterfaceException();
        }
    }
    return S_OK;
}

// Debugger event

HRESULT CCommands::XDebuggerEvents::BreakpointHit(IDispatch* pBreakpoint)
{
    WT_MANAGE_STATE();
    return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CCommands methods

CString CCommands::GetActiveDocumentName() const
{
	CComPtr<IDispatch> pActiveDocument;
	m_pApplication->get_ActiveDocument(&pActiveDocument);
	if (!pActiveDocument)
	{
		return "";
	}

	CComQIPtr<IGenericDocument, &IID_IGenericDocument_Resolved> pDoc(pActiveDocument);
    CComBSTR bStr;
	pDoc->get_FullName(&bStr);

    return bStr;
}

BOOL CCommands::DoHeaderFlip(CString cFullName, BOOL bUseWorkspaceUtils, 
    BOOL bSimulate /*=false*/, BOOL bShowWarnings /*=true*/) 
{
    static LPCTSTR sHeaders[] = { "h", "hpp", "hxx", "hm", "inl" };
    static LPCTSTR sSources[] = { "c", "cpp", "cxx", "cc" };
    const          nHeaders   = countof(sHeaders);
    const          nSources   = countof(sSources);

    WT_L2_TRACE("DoHeaderFlip: %s, %d, %d\n", (LPCTSTR)cFullName,
        bUseWorkspaceUtils, bSimulate);

    enum { none = 0, header, source } FileType = none;

    LPCTSTR     sExt, *sAltExt;
    TCHAR       cDrive[_MAX_DRIVE], cDir[_MAX_DIR];
    TCHAR       cFName[_MAX_FNAME], cExt[_MAX_EXT];

    CComBSTR    bStr;
    int         i, nAltExt;

    if (cFullName.GetLength() == 0)
    {
        return FALSE;
    }

    _splitpath(cFullName, cDrive, cDir, cFName, cExt);
    
    // header or source?
    for (i = 0; i < nHeaders; i++)
    {
        if (_tcsicmp(cExt + 1, sHeaders[i]) == 0)
        {
            FileType = header;
            sExt     = sHeaders[i];
            sAltExt  = sSources;
            nAltExt  = nSources;
            break;
        }
    }
    if (FileType == none)
    {
        for (i = 0; i < nSources; i++)
        {
            if (_tcsicmp(cExt + 1, sSources[i]) == 0)
            {
                FileType = source;
                sExt     = sSources[i];
                sAltExt  = sHeaders;
                nAltExt  = nHeaders;
                break;
            }
        }
    }

    if (bSimulate)
    {
        return (FileType != none);
    }

    // not a header or a source...
    if (FileType == none)
    {
        if (bShowWarnings)
        {
            VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
            AfxMessageBox(IDS_HEADERERROR, MB_OK | MB_ICONEXCLAMATION);
            VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
        }
        return FALSE;
    }

    CComPtr<IDispatch> pDisp;
    CComQIPtr<IGenericWindow, &IID_IGenericWindow> pActiveWindow;

    // remember which window was active
    m_pApplication->get_ActiveWindow(&pDisp);
    pActiveWindow = pDisp;
    pDisp = NULL;

    // Workspace Utils. is an add-in by Joshua C. Jensen that can, amongst
    // many other things, perform a source/header flip.  Since Workspace 
    // Utils. has a more comprehensive flip command (it can scan your project
    // unlike WndTabs which just does a disk search), we'll try to use it
    // first.
    //
    // LIMITATION: With versions prior to 2.0, the header flip can only be
    // used on active windows.
    //
    // Starting with v2.0, Workspace Utils. (renamed Workspace Whiz) uses the
    // AddInComm library to allow WndTabs to access it's internal header flip 
    // command. This means that any window can be filpped (i.e. you can right 
    // click on any tab, select the header flip command, and have Workspace 
    // Utils. do the actual flip).
    //
    // Workspace Utils: http://www.workspacewhiz.com

    if (bUseWorkspaceUtils)
    {
        HADDIN hAddIn = AICGetAddIn("WorkspaceWhiz");
        if (hAddIn)
    	{
    		// AddInComm enabled version of WU - send the file name
            CString sCmd;
            sCmd = "HeaderFlip " + cFullName;

            // WU returns -1 for failure, 0 for success.  bUseWorkspaceUtils
            // is set to 0 on failure, in which case WndTabs will try to do
            // the flip itself.
    		bUseWorkspaceUtils = AICSendCommand(hAddIn, sCmd) + 1;
    	}
        else
        {   
            // older versions of WU (no AddInComm support) - use 
            // ExecuteCommand

            // only works for the active window
            if (GetActiveDocumentName() == cFullName) 
            {
                bStr = _T("WUHeaderFlip");
                m_pApplication->ExecuteCommand(bStr);

                // since ExecuteCommand doesn't return any indication of 
                // success, we'll check to see if the active window changed 
                // (meaning that Workspace Utils is installed and did the 
                // flip).
                if (GetActiveDocumentName() == cFullName)
                {
                    // didn't flip :(

                    // indicate that we didn't use WU:
                    bUseWorkspaceUtils = FALSE;  
                }
            }
            else
            {
                // not flipping the active window - indicate that we didn't 
                // use WU                
                bUseWorkspaceUtils = FALSE;
            }
        }
    }

    // if Workspace Utils. didn't flip for us, do it ourselves
    if (!bUseWorkspaceUtils)
    {
        CComQIPtr<IDocuments, &IID_IDocuments_Resolved> pDocuments;
        CComVariant sAuto("Auto"), vFalse(VARIANT_FALSE);

        m_pApplication->get_Documents(&pDisp);
        pDocuments = pDisp;
        pDisp = NULL;

        for (i = 0; i < nAltExt; i++)
        {                                                  
            _makepath(cFullName.GetBuffer(_MAX_PATH), cDrive, cDir, 
                cFName, sAltExt[i]);
            cFullName.ReleaseBuffer();
            bStr = cFullName;
			pDocuments->Open(bStr, sAuto, vFalse, &pDisp);
			if (pDisp != NULL)
			{
				break;
			}
        }

        if (pDisp == NULL)  // none found?
        {
            // reactivate the window that was active before
            HWND hWnd = GetHWND(pActiveWindow);
            ::PostMessage(::GetParent(hWnd), WM_MDIACTIVATE, 
                (WPARAM)hWnd, 0);
            return FALSE;
        }
    }

    return TRUE;
}

void CCommands::DoOpenAsText(CString cFullName)
{
    WT_L2_TRACE("DoOpenAsText: %s", (LPCTSTR)cFullName);
    
    if (cFullName.GetLength() == 0)
    {
        return;
    }

    CComPtr<IDispatch> pDisp;
    CComQIPtr<IDocuments, &IID_IDocuments_Resolved> pDocuments;
	CComQIPtr<IGenericDocument, &IID_IGenericDocument_Resolved> pDoc;
    CComBSTR bStr(cFullName);

    m_pApplication->get_Documents(&pDisp);
    pDocuments = pDisp;
    pDisp = NULL;

    // if this is a resouce, VC will automatically close it for us (and
    // will even display a nice little message box... :).  If not, we have
    // to close the current document before reopening as text...
    bool bIsResource = (cFullName.Find(_T(".rc")) >= 0);

    if (!bIsResource)
    {
        pDocuments->Item(CComVariant(cFullName), &pDisp);
        pDoc = pDisp;
        pDisp = NULL;

        DsSaveStatus iSaved;
        if (pDoc->Close(CComVariant((int)dsSaveChangesPrompt), &iSaved) ==
            dsSaveCanceled)
        {
            // bail out if the user pressed 'cancel'
            return;
        }
    }

	pDocuments->Open(bStr, CComVariant("Text"),
					 CComVariant(VARIANT_FALSE), &pDisp);

    if (pDisp == NULL)
    {
        AfxMessageBox(IDS_NOTTEXT, MB_OK | MB_ICONINFORMATION);
    }

/*    
    // for resources: we have to make sure DevStudio activates the window
    // with the .rc file
    if (bIsResource)
    {
        pDisp = NULL;
        CComQIPtr<IWindows, &IID_IWindows> pWindows;
        pDocuments->Item(CComVariant(cFullName), &pDisp);
        pDoc = pDisp;
        pDisp = NULL;
        pDoc->get_Windows(&pDisp);
        pWindows = pDisp;
        pDisp = NULL;
        CComQIPtr<IGenericWindow, &IID_IGenericWindow> pWindow;
        pWindows->Item(CComVariant(1), &pDisp);
        pWindow = pDisp;
        pDisp = NULL;
        pWindow->put_Active(VARIANT_FALSE);
        pWindow->put_Active(VARIANT_TRUE);
    }
*/
}

void CCommands::FlashWindows(bool bAsterisksOnly) const
{
    WT_FN_TRACE("FlashWindows");

    CWnd *pActiveWnd, *pWnd;
    CString sName;
    bool bSwitch = true;

    pActiveWnd = pGlobalMDIManager->GetTopWindow();

    if (pActiveWnd)
    {
        CWaitCursor wc;

        pGlobalMDIManager->SetRedraw(FALSE);

        pWnd = pActiveWnd->GetWindow(GW_HWNDNEXT);

        CList<HWND, HWND&> lst;

        while (pWnd)
        {
            lst.AddTail(pWnd->m_hWnd);
            pWnd = pWnd->GetWindow(GW_HWNDNEXT);
        }

        POSITION p = lst.GetHeadPosition();
        while (p)
        {
            pWnd = CWnd::FromHandle(lst.GetNext(p));
            WT_ASSERT(pWnd->GetSafeHwnd());
            if (bAsterisksOnly)
            {
                pWnd->GetWindowText(sName);
                bSwitch = (sName.Find('*') >= 0);
            }

            if (bSwitch)
            {
                pGlobalMDIManager->SendMessage(WM_MDIACTIVATE, 
                    (WPARAM)pWnd->m_hWnd, 0);
            }
        }
        pGlobalMDIManager->SendMessage(WM_MDIACTIVATE, 
            (WPARAM)pActiveWnd->m_hWnd, 0);

        ShowCursor(FALSE);

        pGlobalMDIManager->SetRedraw(TRUE);

        ShowCursor(TRUE);
    }

    return;
}

void CCommands::DoSetCurrDir(CString cFullName) 
{
    CComBSTR                            bStr;
    int                                 nPos;
    long                                cWindows;
    CComPtr<IDispatch>                  pDisp;
    CComQIPtr<IWindows, &IID_IWindows>  pWindows;

    if ((nPos = cFullName.ReverseFind('\\')) < 0)
    {
        return;
    }

    cFullName = cFullName.Left(nPos);
    bStr = cFullName;
    m_pApplication->put_CurrentDirectory(bStr);


    m_pApplication->get_Windows(&pDisp);
    pWindows = pDisp;
    pDisp = NULL;
    
    pWindows->get_Count(&cWindows);

    if (cWindows > 1)
    {
       // update window titles by activating each window in turn
       FlashWindows();
    }
    else
    {
        // as far as I can tell there's nothing to do if there's only
        // one open window :(
    }
}

static inline bool UserWantsToSavePositions()
{
    return (cfg_bSaveTabNumbers  &&  cfg_bPreserveNumbering  &&
            cfg_TabOrdering != toMDI);
}

#define POS_FILE_HEADER   "WndTabs Tab Positions File"

void CCommands::ReadPositionsFile()
{
    // read position information
    if (m_sPositionsFile.IsEmpty()  ||  !UserWantsToSavePositions())
        return;

    WT_L1_TRACE("Reading positions file %s\n", (LPCTSTR)m_sPositionsFile);

    bool bIsValid = true;

    TRY
    {
        CFile pos_file(m_sPositionsFile, CFile::modeRead | CFile::typeBinary);
        CArchive pos_ar(&pos_file, CArchive::load);
        float ver;
        CString s;
        char ch;

        // 1. File header + version info
        pos_ar >> s >> ch >> ver;
        if (s != POS_FILE_HEADER  ||  ch != 26)
        {
            return;
        }

        if (!(ver > 3.05))
        {
            // older formats not supported
            return;
        }

        // 2. Active Tab
        pos_ar >> m_Positions.iActiveTab;

        // 3. Tab Count
        int cCount, iNum;
        pos_ar >> cCount;

        // 4. Tab Content
        bool bUsed[512] = { false };
        while (cCount)
        {
            pos_ar >> s >> iNum;

            // check for legal string
            if (!s.IsEmpty()  &&  s.GetLength() < 512)
            {
                int i;
                for (i = 0; i < s.GetLength(); ++i)
                {
                    if (s[i] < 32) goto next;
                }
                    
                for (i = 0; i < m_Positions.data.GetSize(); ++i)
                {
                    if (m_Positions.data[i].cPath == s)
                    {
                        // oops - duplicate...
                        goto next;
                    }
                }

                // fix iNum if needed (might be corrupt)
                if (bUsed[iNum])
                {
                    for (int j = 0; ; ++j)
                    {
                        if (!bUsed[j])
                        {
                            iNum = j;
                            break;
                        }
                    }
                }
                bUsed[iNum] = true;

                m_Positions.data.Add(Positions::tab_data(s, iNum));
            }
next:
            --cCount;
        }
    }
    CATCH (CFileException, e)
    {
        WT_L1_TRACE("File exception while reading from positions file: %d\n",
                    e->m_cause);
        bIsValid = false;
    }
    CATCH (CArchiveException, e)
    {
        WT_L1_TRACE("Archive exception while reading from positions file: %d\n",
                    e->m_cause);
        bIsValid = false;
    }
    CATCH(CException, e)
    {
        WT_L1_TRACE("General exception while reading positions file");
        bIsValid = false;
    }
    END_CATCH

    if (!bIsValid)
    {
        m_Positions.data.RemoveAll();
    }
}

void CCommands::WritePositionsFile()
{
    // save position information
    if (m_sPositionsFile.IsEmpty() || 
		NULL == pGlobalTabs)
	{
        return;
	}

    if (!UserWantsToSavePositions())
    {
        // remove the file
        WT_L1_TRACE("Deleting positions file %s\n", 
            (LPCTSTR)m_sPositionsFile);
        DeleteFile(m_sPositionsFile);
        return;
    }

    WT_L1_TRACE("Writing positions file %s\n", (LPCTSTR)m_sPositionsFile);

    TRY
    {
        CFile pos_file(m_sPositionsFile, 
            CFile::modeWrite | CFile::modeCreate | CFile::typeBinary);
        CArchive pos_ar(&pos_file, CArchive::store);
        float ver;
        sscanf((LPCTSTR)g_cVersion, "%f", &ver);

        // 1. File header + version info
        pos_ar << CString(POS_FILE_HEADER) << (char)26 << ver;

        // 2. Active Tab
        pos_ar << pGlobalTabs->m_pTabCtrl->GetCurSel();

        // 3. Tab Count
        const int cCount = pGlobalTabs->m_pTabCtrl->GetItemCount();
        pos_ar << cCount;

        // 4. Tab Content
        CTabsWindow::tabdata_t *pData;
        for (int i = 0; i < cCount; ++i)
        {
            pData = pGlobalTabs->GetTabData(i);
            pos_ar << (pData->cTitle + "|" + pData->cPath) << pData->iNumber;
        }
    }
    CATCH (CFileException, e)
    {
        WT_L1_TRACE("File exception while writing to positions file: %d\n",
                    e->m_cause);
    }
    CATCH (CArchiveException, e)
    {
        WT_L1_TRACE("Archive exception while writing to positions file: %d\n",
                    e->m_cause);
    }
    CATCH(CException, e)
    {
        WT_L1_TRACE("General exception while writing to positions file");
    }
    END_CATCH
}



STDMETHODIMP CCommands::WTHeaderFlip() 
{
    WT_MANAGE_STATE();
    DoHeaderFlip(GetActiveDocumentName(), cfg_bUseWorkspaceUtils);
    return S_OK;
}

STDMETHODIMP CCommands::WTOpenAsText() 
{
    WT_MANAGE_STATE();
    DoOpenAsText(GetActiveDocumentName());
    return S_OK;
}

STDMETHODIMP CCommands::WTSetCurrDir() 
{
    WT_MANAGE_STATE();
    DoSetCurrDir(GetActiveDocumentName());
    return S_OK;
}


STDMETHODIMP CCommands::WTHelp()
{
	WT_MANAGE_STATE();

    ShowHTMLHelp(::GetDesktopWindow(), IDH_WELCOME);

	return S_OK;
}

STDMETHODIMP CCommands::WTAbout()
{
    WT_MANAGE_STATE();
    COptionsSheet dlg(-1);
    dlg.DoModal();
    theApp.UnFocus();
    return S_OK;
}

STDMETHODIMP CCommands::WTOptions()
{
    WT_MANAGE_STATE();
    COptionsSheet dlg;
    dlg.DoModal();
    return S_OK;
}

STDMETHODIMP CCommands::WTRenumber()
{
    WT_MANAGE_STATE();
    ASSERT(pGlobalTabs);
    pGlobalTabs->Renumber();
    return S_OK;
}

STDMETHODIMP CCommands::WTReorder()
{
    WT_MANAGE_STATE();
    ASSERT(pGlobalTabs);
    pGlobalTabs->Reorder();
    return S_OK;
}

void CCommands::CycleGroup(int iDelta)
{
    WT_ASSERT(iDelta == 1  ||  iDelta == -1);
    
    if (!pGlobalTabs->m_bIsWTTab)
    {
        VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
        AfxMessageBox(IDS_GROUP_NEEDS_WTX, MB_OK | MB_ICONEXCLAMATION);
        VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
        return;
    }

    const int cTabs = pGlobalTabs->m_pTabCtrl->GetItemCount();

    if (cTabs == 0)
    {
        MessageBeep(-1);
        return;
    }

    int *       pInfo = new int[cTabs];
    WTTabCtrlGetGroupInfo(pGlobalTabs->m_pTabCtrl, pInfo);
    int         iTab  = pGlobalTabs->m_pTabCtrl->GetCurSel();
    const int   iGroupID = pInfo[iTab];

    do
    {
        iTab += iDelta;
        if (iTab < 0)
        {
            iTab = cTabs;
        }
        else
        {
            if (iTab > cTabs)
            {
                iTab = 0;
            }
        }
    } while (pInfo[iTab] != iGroupID);

    delete [] pInfo;

    HWND hWnd;

    if (pGlobalTabs->FindDSWindow(iTab, NULL, &hWnd))
    {
        pGlobalTabs->ActivateWindow(hWnd);
    }
}

STDMETHODIMP CCommands::WTGroupNext()
{
    WT_MANAGE_STATE();
    CycleGroup(1);
	return S_OK;
}

STDMETHODIMP CCommands::WTGroupPrev()
{
    WT_MANAGE_STATE();
    CycleGroup(-1);
	return S_OK;
}


#define GOTO_CMD(i)                                     \
    STDMETHODIMP CCommands::WTGoToTab##i()              \
    {                                                   \
        WT_MANAGE_STATE();    \
        ASSERT(pGlobalTabs);                            \
        pGlobalTabs->ActivateTab(i);                    \
        return S_OK;                                    \
    }

GOTO_CMD(1);
GOTO_CMD(2);
GOTO_CMD(3);
GOTO_CMD(4);
GOTO_CMD(5);
GOTO_CMD(6);
GOTO_CMD(7);
GOTO_CMD(8);
GOTO_CMD(9);

