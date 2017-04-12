/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// DevStudioWnd.cpp : implementation file
//
// This class is used to capture messages sent to DevStudio's main window.
// Currently, the WM_GETTEXT message is captured.  Each time WM_GETTEXT is
// used, WndTabs checks if the title of the DevStudio window was changed.  A
// change in the title indicates that the tabs need to be updated.


#include "stdafx.h"
#include "wndtabs.h"
#include "DevStudioWnd.h"
#include "TabsWindow.h"
#include "TabManagerWindow.h"
#include "MainFrame.h"
#include "Imports.h"
#include "AddInComm\AICLoader.h"
#include "Config.h"
#include "Commands.h"
#include "DS_MDIWnd.h"
#include "..\WndTabsSDK\WTSDKDefs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CArray<WTSDK_CommandContext, WTSDK_CommandContext&> s_NonDebugWndTabs;
CStringArray s_DbgClosePaths;
int s_NumDynPathsUsed;

/////////////////////////////////////////////////////////////////////////////
// CDevStudioWnd

IMPLEMENT_DYNAMIC(CDevStudioWnd, CSubclassWnd)


CDevStudioWnd::CDevStudioWnd(HWND hWndDevStudio) : 
    CSubclassWnd(hWndDevStudio), m_bInDebuggingSession(false)
{
    DoSubclass();
}

CDevStudioWnd::~CDevStudioWnd()
{
    s_NonDebugWndTabs.RemoveAll();
}


BEGIN_MESSAGE_MAP(CDevStudioWnd, CSubclassWnd)
	//{{AFX_MSG_MAP(CDevStudioWnd)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_GETTEXT, OnGetWindowText)
    ON_MESSAGE(WM_APPCOMMAND, OnAppCommand)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDevStudioWnd message handlers

void ReplaceSingleInstance(CString& src, LPCTSTR pszReplaceWhat,
    LPCTSTR pszReplaceWith)                           
{
    CString_Replace(src, pszReplaceWhat, pszReplaceWith);

    while (src.Find(pszReplaceWhat) >= 0)
    {
        CString_Replace(src, pszReplaceWhat, "");
    }
}

void SubsituteDir(CRegKey& reg, LPCTSTR pszKeyName, LPCTSTR pszNameInStr,
    CString& str)
{
    char buf[2048];
    DWORD dwCount = sizeof(buf);
    if (reg.QueryValue(buf, pszKeyName, &dwCount) == ERROR_SUCCESS)
    {
        ReplaceSingleInstance(str, pszNameInStr, buf);
    }
}

inline void FixPath(CString& s)
{
    if (s.IsEmpty()) return;
    if (s[s.GetLength() - 1] == '/') s.SetAt(s.GetLength() -1, '\\');
    if (s[s.GetLength() - 1] != '\\') s += '\\';
}

inline bool IsSameProjectPath(IGenericProject *pPrj, const CString& cPath)
{
    char buf[1024];
    CComBSTR bStr;
    CString cStr;
    pPrj->get_FullName(&bStr);
    cStr = bStr;
    int pos = cStr.ReverseFind('\\');
    WT_ASSERT(pos >= 0);
    pos++;
    cStr.Delete(pos, cStr.GetLength() - pos);
    _fullpath(buf, cStr, sizeof(buf));
    
    return (stricmp(cPath, buf) == 0);
}

inline bool IsDynPath(const char *pszTemplate, const CString& cPath)
{
    if (strcmp(pszTemplate, PATH_WORKSPACE) == 0)
    {
        if (CCommands::m_sWorkspacePath.GetLength())
        {
            return (CCommands::m_sWorkspacePath.CompareNoCase(cPath) == 0);
        }
        return false;
    }

    IApplication *pApplication = pGlobalTabs->m_pApplication;
    CComPtr<IDispatch> pDisp;
    CString cStr;
    
    if (strcmp(pszTemplate, PATH_ACTIVE_PRJ) == 0)
    {
        CComQIPtr<IGenericProject, &IID_IGenericProject> pPrj;

        pApplication->get_ActiveProject(&pDisp);
        pPrj = pDisp;
        pDisp = NULL;
        return IsSameProjectPath(pPrj, cPath);
    }

    if (strcmp(pszTemplate, PATH_ALL_PRJS) == 0)
    {
        CComQIPtr<IProjects, &IID_IProjects> pPrjs;

        pApplication->get_Projects(&pDisp);
        pPrjs = pDisp;
        pDisp = NULL;

        long count;
        pPrjs->get_Count(&count);

        for (int i = 0; i < count; i++)
        {
            CComQIPtr<IGenericProject, &IID_IGenericProject> pPrj;
            pPrjs->Item(CComVariant(i + 1), &pPrj);
            if (IsSameProjectPath(pPrj, cPath))
            {
                return true;
            }
        }

        return false;
    }

    WT_ASSERT(FALSE);
    return false;
}

void CDevStudioWnd::OnEndDebugSession()
{
    WT_FN_TRACE("OnEndDebugSession");
    static const char *DynPaths[] = 
    { 
        PATH_WORKSPACE, PATH_ACTIVE_PRJ, PATH_ALL_PRJS 
    };

    if (!cfg_bAutoCloseDbgWins)
        return;

    int pos1, i, j;
    CString cStr;
    char buf[1024];
    if (m_sCloseDebWndPath.IsEmpty())
    {
        s_DbgClosePaths.RemoveAll();
        m_sCloseDebWndPath = cfg_sAutoCloseDirsDbg;
        char buf[1024];

        cStr = m_sCloseDebWndPath;
        s_NumDynPathsUsed = 0;

        for (i = 0; i < countof(DynPaths); i++)
        {
            if (cStr.Find(DynPaths[i]) >= 0)
            {
                s_DbgClosePaths.Add(DynPaths[i]);
                ReplaceSingleInstance(cStr, DynPaths[i], "");
                ++s_NumDynPathsUsed;
            }
        }

        if (aiclGetDSCurrentUserRegKey(buf))
        {
            CRegKey reg;
            strcat(buf, 
                "\\Build System\\Components\\Platforms\\Win32 (x86)\\Directories");
            if (reg.Open(HKEY_CURRENT_USER, buf, KEY_READ) == ERROR_SUCCESS)
            {
                SubsituteDir(reg, "Include Dirs", PATH_DS_INCLUDE, cStr);
                SubsituteDir(reg, "Library Dirs", PATH_DS_LIB,     cStr);
                SubsituteDir(reg, "Path Dirs",    PATH_DS_EXEC,    cStr);
                SubsituteDir(reg, "Source Dirs",  PATH_DS_SOURCE,  cStr);
            }
        }

        while ((pos1 = cStr.Find(';')) >= 0)
        {
            if (pos1)
            {
                if (pos1)
                {
                    _fullpath(buf, cStr.Left(pos1) + "\\", sizeof(buf));
                    s_DbgClosePaths.Add(buf);
                }
            }
            cStr.Delete(0, pos1 + 1);
        }
        if (cStr.GetLength() != 0)
        {
            cStr += "\\";
            _fullpath(buf, cStr, sizeof(buf));
            s_DbgClosePaths.Add(buf);
        }
    }


    const CTabCtrl& tabCtrl = *pGlobalTabs->m_pTabCtrl;
    for (i = 0; i < tabCtrl.GetItemCount(); i++)
    {
        WTSDK_CommandContext ctx;
        ctx.cbSize = sizeof(ctx);
        pGlobalTabs->GetCommandContext(i, ctx);

        if (!ctx.bHasFile)
            continue;

        for (j = 0; j < s_NonDebugWndTabs.GetSize(); j++)
        {
            if (stricmp(s_NonDebugWndTabs[j].szFullPath, ctx.szFullPath) == 0)
            {
                break;
            }
        }

        // new window
        if (j == s_NonDebugWndTabs.GetSize())
        {
            _fullpath(buf, ctx.szFullPath, sizeof(buf));
            cStr = buf;
            pos1 = cStr.ReverseFind('\\');
            if (pos1 < 0)
                continue;
            pos1++;
            cStr.Delete(pos1, cStr.GetLength() - pos1);

            for (int n = 0; n < s_DbgClosePaths.GetSize(); n++)
            {
                if (n < s_NumDynPathsUsed)
                {
                    if (!IsDynPath(s_DbgClosePaths[n], cStr))
                    {
                        continue;
                    }
                }
                else
                {
                    if (s_DbgClosePaths[n].CompareNoCase(cStr) != 0)
                    {
                        continue;
                    }
                }

                // it's a window to close!
                ::PostMessage(ctx.hWnd, WM_CLOSE, 0, 0);
                break;
            }
        }
    }
}

void CDevStudioWnd::OnStartDebugSession()
{
    WT_FN_TRACE("OnStartDebugSession");

    s_NonDebugWndTabs.RemoveAll();

    if (pGlobalTabs)
    {
        const CTabCtrl& tabCtrl = *pGlobalTabs->m_pTabCtrl;
        for (int i = 0; i < tabCtrl.GetItemCount(); i++)
        {
            WTSDK_CommandContext ctx;
            ctx.cbSize = sizeof(ctx);
            pGlobalTabs->GetCommandContext(i, ctx);
            s_NonDebugWndTabs.Add(ctx);
        }
    }
}


LRESULT CDevStudioWnd::OnGetWindowText(WPARAM wParam, LPARAM lParam)
{
    LRESULT lResult = Default();
    WT_FN_TRACE_PARAMS("OnGetWindowText", "%p, %s", wParam);

    // ignore if less than 10 characters returned.  the real title should
    // have much more.
    if (lResult < 10)
        RETURN_INT(lResult);

    static HWND hWndLast = NULL;
    HWND hWndCurr = NULL;
    if (pGlobalMDIManager->GetSafeHwnd())
    {
        hWndCurr = (HWND)(pGlobalMDIManager)->SendMessage(WM_MDIGETACTIVE);
    }

	CString sNewTitle = (LPCTSTR)lParam;
	// Strip [Run]/[Break] from title in order to reduce unnecessary tab
	// refreshing during single-stepping.
	// CString::Delete() not used in order to preserve compatibility with 
	// old MFC
	int iPosEnd = sNewTitle.Find("] - [");
	if (iPosEnd >= 0)
	{
		int iPosStart = iPosEnd - 1;
		while (iPosStart >= 0  &&  sNewTitle[iPosStart] != '[') --iPosStart;
		CString cStrTemp = sNewTitle.Left(iPosStart + 1);
		cStrTemp += sNewTitle.Mid(iPosEnd);
		sNewTitle = cStrTemp;
	}

    if (m_cTitle.Compare(sNewTitle) != 0)
    {
        WT_L3_TRACE("New title: %s\nOld title: %s\n", sNewTitle,
            (LPCTSTR)m_cTitle);
        CString cStr(sNewTitle);
        const int len = cStr.GetLength();

        // check debugging/non-debugging
        const bool bInDebugger = 
            cStr.Find("C++ [")    != -1  || 
            cStr.Find("Studio [") != -1;
        if (bInDebugger != m_bInDebuggingSession)
        {
            WT_MANAGE_STATE();
            m_bInDebuggingSession = bInDebugger;
            if (!bInDebugger)
            {
                OnEndDebugSession();
            }
            else
            {
                OnStartDebugSession();
            }
        }

        if (pGlobalActiveManager  &&  !pGlobalTabs->m_bAboutToUpdate)
        {
            if (cStr.Right(3) == " *]")
            {
                cStr = m_cTitle.Left(len - 3);
                cStr += ']';
            }
            else
            {
                cStr = m_cTitle.Left(len - 1);
                cStr += " *]";
            }

            if (m_cTitle == cStr  ||  hWndCurr != hWndLast)
                pGlobalActiveManager->PostUpdateMessage();
        }
        m_cTitle = sNewTitle;
    }

    RETURN_INT(lResult);
}

void CDevStudioWnd::PreSubclassWindow() 
{
    GetWindowText(m_cTitle);     
	CSubclassWnd::PreSubclassWindow();
}

void CDevStudioWnd::OnSetFocus(CWnd* pOldWnd) 
{
    if (theApp.IsFocused() ||  IsCustomizing()) 
    {
    	g_pMainFrame->SetFocus();
        g_pMainFrame->SetWindowPos(g_pDevStudioWnd->GetNextWindow(GW_HWNDPREV),
            0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
    else
    {
        CSubclassWnd::OnSetFocus(pOldWnd);

        // force an update so tabs can catch external file changes
        // also - it is a good idea to force addons to update tab information 
        // at this time
        pGlobalActiveManager->PostUpdateMessage();
    }
    ResetBCGHooks();
}

LRESULT CDevStudioWnd::OnAppCommand(WPARAM wParam, LPARAM lParam)
{
    if (!g_pMainFrame)
    {
        return FALSE;
    }
    if (g_pMainFrame->SendMessage(WM_APPCOMMAND, wParam, lParam))
    {
        return TRUE;
    }
    return Default();
}
