/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// WndTabs.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxsock.h>
#include <initguid.h>

#include "WndTabs.h"
#include "DSAddIn.h"
#include "TabsWindow.h"
#include "Commands.h"
#include "Config.h"
#include "Extensions.h"
#include "AddInComm\AICLoader.h"
#include "Help\HelpIDs.h"
#include "MainFrame.h"
#include "DevStudioWnd.h"
#include "SDK_Supp.h"
#include "VCVerMgr.h"
#include "3rdParty\WWhizInterface2.h"
#include "3rdParty\WWhizInterface2Loader.h"
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString g_cVersion;
bool    g_bResetLanguage = false;

#define REG_KEY_BASE    "WndTabs.com\\WndTabs"
#define REG_KEY_SUB     "Options"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
    OBJECT_ENTRY(CLSID_DSAddIn, CDSAddIn)
END_OBJECT_MAP()


class WTLogger : public CLogger
{
protected:
    virtual void OutputBasicInfo();
} wtLogger;


void WTLogger::OutputBasicInfo()
{
    CLogger::OutputBasicInfo();
    OutputIt("\n");
}


/////////////////////////////////////////////////////////////////////////////
// CWndTabsApp

BEGIN_MESSAGE_MAP(CWndTabsApp, CWinApp)
    //{{AFX_MSG_MAP(CWndTabsApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// The one and only CWndTabsApp object

CWndTabsApp theApp;
CWinApp *pTheApp = &theApp;

/////////////////////////////////////////////////////////////////////////////
// CWndTabsApp construction

CWndTabsApp::CWndTabsApp()
{
    m_iFocusCount = 0;
    m_pMainFrame = NULL;
    m_bDoDeleteVS6KeyBindings = false;
    m_pWWhizInterface = NULL;
    m_bAllowWWhizInterface = true;
}

CWndTabsApp::~CWndTabsApp()
{
    if (m_bDoDeleteVS6KeyBindings)
    {
        CRegKey key;

        if (key.Open(HKEY_CURRENT_USER, DS6_AUT_KEY) == ERROR_SUCCESS)
        {
            for (int i = 0; i < cAddInCommands; i++)
            {
                key.DeleteValue(AddInCommands[i].szCommand);
            }
        }
    }
    if (m_pWWhizInterface)
    {
        WWhizInterface2Destroy();
        m_pWWhizInterface = NULL;
    }
}


/////////////////////////////////////////////////////////////////////////////
// CWndTabsApp initialization

CString GetVersionForRegKey()
{
    char s[256];

    char path[MAX_PATH];
    GetModuleFileName(AfxGetInstanceHandle(), path, sizeof(path));
    aiclGetFileVersion(path, s);

    char *pos = strchr(s, '.');
    if (pos == NULL) return "0.0";
    ++pos;
    if (!*pos) return "0.0";
    if (isdigit(*pos)) { ++pos; }
    *pos = '\0';

    return s;
}

CString GetRegKeyBase()
{
    return ("Software\\" REG_KEY_BASE "\\") + GetVersionForRegKey();

}

BOOL CWndTabsApp::InitInstance()
{
    // check for execution out-side of MSDEV (for instance, regsvr32)
    if (g_VCVer == Unknown)
    {
        _Module.Init(ObjectMap, m_hInstance);
        return CWinApp::InitInstance();
    }

    char path[MAX_PATH];
    GetModuleFileName(AfxGetInstanceHandle(), path, sizeof(path));
    aiclGetFileVersion(path, g_cVersion.GetBuffer(50));
    g_cVersion.ReleaseBuffer();

    SetRegistryKey(REG_KEY_BASE);
    CString sVerForReg = GetVersionForRegKey();
    WT_ASSERT(strlen(m_pszProfileName) > (size_t)sVerForReg.GetLength());
    strcpy((char *)m_pszProfileName, sVerForReg);

    // get logger settings directly from registry
    CRegKey rk;
    if (rk.Open(HKEY_CURRENT_USER, GetRegKeyBase() + ("\\" REG_KEY_SUB), KEY_READ) == ERROR_SUCCESS)
    {
        char filename[512];
        DWORD dw = sizeof(filename);
        if (rk.QueryValue((LPTSTR)filename, "LogFile", &dw) != ERROR_SUCCESS)
            strcpy(filename, "c:\\WndTabs.log");
        if (rk.QueryValue(dw, "LogLevel") != ERROR_SUCCESS)
            dw = 0;
//        g_pTheLogger->UseExtrnLogger(&wtLogger);
        g_pTheLogger = &wtLogger;
        g_pTheLogger->SetTraceLevel(dw);
        g_pTheLogger->SetFileName(filename);
    }

    WT_L1_TRACE("Retrieved version: %s\n", g_cVersion);

    WT_L2_TRACE("Initializing OLE... ");
    AfxOleInitModule();
	_AFX_THREAD_STATE* pState = AfxGetThreadState();
	if (!pState->m_bNeedTerm)
    {
        if (!AfxOleInit())
        {
            AfxMessageBox(IDP_OLE_INIT_FAILED);
            return FALSE;
        }
        WT_L2_TRACE("done\n");
    }
    else
    {
        WT_L2_TRACE("already inited\n");
    }

    WT_L1_TRACE("Loading configuration\n");
    SetRegistryBase(_T("Layout"));
    CfgSetRegSection(REG_KEY_SUB);
    GetConfiguration();
    LoadAddonConfiguration();

    LoadLangDLLs();
    if (!cfg_sLangDLL.IsEmpty())
    {
        CLanguageDLL *pDLL = GetLanguageDLL(cfg_sLangDLL);
        if (pDLL)
        {
            if (!pDLL->Apply())
            {
                pDLL = NULL;
            }
        }
        if (pDLL == NULL)
        {
            CString msg;
            AfxFormatString1(msg, IDS_ERR_LANG_CANT_LOAD, cfg_sLangDLL);
            AfxMessageBox(msg, MB_OK | MB_ICONEXCLAMATION);
            cfg_sLangDLL = "";
        }
    }

    WT_L1_TRACE("Socket init... ");
    if (!AfxSocketInit())
    {
        WT_L1_TRACE("FAILED! ");
    };
    WT_L1_TRACE("done\n");

    WT_L2_TRACE("BCG context menu manager initialization...\n");
    CBCGPopupMenu::SetAnimationType(CBCGPopupMenu::NO_ANIMATION);    
    CBCGMenuBar::HighlightDisabledItems();
    InitContextMenuManager();
    InitKeyboardManager();
    EnableAutoUserImages(IDB_USERBTNS);
    
    WT_L3_TRACE("CComModule::Init\n");
    _Module.Init(ObjectMap, m_hInstance);

    WT_L3_TRACE("End Init\n");
    return CWinApp::InitInstance();
}

CLanguageDLL *CWndTabsApp::GetLanguageDLL(LPCTSTR lpszDLLName)
{
    for (int i = 0 ; i < m_LangDLLs.GetSize(); ++i)
    {
        if (m_LangDLLs[i].m_sDLLName.CompareNoCase(lpszDLLName) == 0)
        {
            return &m_LangDLLs[i];
        }
    }
    return NULL;
}

#include <RegPath.h>

int CWndTabsApp::ExitInstance()
{
    WT_FN_TRACE("ExitInstance");

    // check for execution out-side of MSDEV (for instance, regsvr32)
    if (g_VCVer != Unknown)
    {
        BCGCBCleanUp ();
        WriteConfiguration();
        WriteAddonConfiguration();
        Sleep(500); // give BCG sound thread chance to exit properly!
    }
    
    _Module.Term();

    if (g_bResetLanguage)
    {
        // Reset the menu bar
	    CString strProfileName = ::BCGGetRegPath("Layout");
        const int nIndex = BCG_IDW_MENUBAR;
	    CString strSection;
        strSection.Format ("BCGToolBar-%d%x", nIndex, 0);
        CRegKey key;
        VERIFY(key.Open(HKEY_CURRENT_USER, strProfileName) == ERROR_SUCCESS);
        VERIFY(key.DeleteSubKey(strSection) == ERROR_SUCCESS);
    }

    RETURN_INT(CWinApp::ExitInstance());
}


void CWndTabsApp::PreLoadState ()
{
    static bool bIsFirstTime = true;

    if (!bIsFirstTime) return;

    bIsFirstTime = false;

    CBCGToolBar::AddToolBarForImageCollection(IDR_ICONS);
    CBCGToolBar::AddToolBarForImageCollection(IDR_TOOLBAR_MEDIUM);

    GetContextMenuManager()->AddMenu(IDS_TAB_CONTEXT_MENU_NAME, IDR_POPUP);
    GetContextMenuManager()->AddMenu(_T("Z] Shell Context Menu"), IDR_SHELL_CONTEXT);
    GetContextMenuManager()->AddMenu(MENU_NAME_CLOSE_BTN, IDR_CLOSEBTN);
}

WWhizInterface *CWndTabsApp::GetWWhizInterface(bool bCreate /*= true*/)
{
    if (m_bAllowWWhizInterface  &&  m_pWWhizInterface == NULL  &&  bCreate)
    {
        m_pWWhizInterface = WWhizInterface2Create(AfxGetInstanceHandle(),
            pGlobalTabs->m_pApplication);
        if (m_pWWhizInterface)
        {
            const DWORD ver = m_pWWhizInterface->GetVersion();
            const int maj = ver >> 24, min = ((ver >> 16) & 0xFF);
            if (maj == 2  &&  min == 15)
            {
                AfxMessageBox(IDS_WARN_BAD_WWHIZINT, 
                    MB_OK | MB_ICONEXCLAMATION);
                WWhizInterface2Destroy();
                m_pWWhizInterface = NULL;
                m_bAllowWWhizInterface = false;
            }
        }
    }
    return m_pWWhizInterface;
}

void CWndTabsApp::ReportWWhizInterfaceException()
{
    if (m_pWWhizInterface)
    {
        WWhizInterface2Destroy();
        m_pWWhizInterface = NULL;
        m_bAllowWWhizInterface = false;
        AfxMessageBox(IDS_WARN_WWHIZINT, MB_OK | MB_ICONEXCLAMATION);
    }
}

class pm : public CBCGPopupMenu
{
    friend class CWndTabsApp;
};

BOOL CWndTabsApp::ShowPopupMenu(UINT uiMenuResId, const CPoint& point, 
    CWnd* pWnd)
{
    return CBCGWorkspace::ShowPopupMenu(uiMenuResId, point, m_pMainWnd); //m_pMainWnd); //pWnd);
}

int CWndTabsApp::AddUserImageUnique(HBITMAP hBMP)
{
    WT_ASSERT(GetUserImages());

    if (!GetUserImages()) return -1;

    CBCGToolBarImages& images = *GetUserImages();

    const int cImages = images.GetCount();
    int iImage = images.AddImage(hBMP);

    if (cImages)
    {
        const CSize sz = images.GetImageSize();
        const int iImageRowBytes = sz.cx * 3 /* 24bpp */;
        const int iEntireRowBytes = (cImages + 1) * iImageRowBytes;
        BITMAPINFOHEADER bih;
        memset(&bih, 0, sizeof(bih));
        bih.biSize = sizeof(bih);
        bih.biPlanes = 1;
        bih.biBitCount = 24;
        bih.biCompression = BI_RGB;
        bih.biHeight = sz.cy;
        bih.biWidth = sz.cx * (cImages + 1);
        BYTE *pBuf = new BYTE[sz.cy * iEntireRowBytes];
        CDC cdc;
        cdc.CreateCompatibleDC(NULL);
        GetDIBits(cdc.m_hDC, images.GetImageWell(), 0, 
            sz.cy, pBuf, (LPBITMAPINFO)&bih, DIB_RGB_COLORS);

        int x, y;

        for (x = 0; x < cImages; ++x)
        {
            for (y = 0; y < sz.cy; ++y)
            {
                if (memcmp(
                    pBuf + (y * iEntireRowBytes) + (x * iImageRowBytes),
                    pBuf + (y * iEntireRowBytes) + (cImages * iImageRowBytes),
                    iImageRowBytes) != 0)
                {
                    break;
                }
            }

            if (y == sz.cy)
            {
                images.DeleteImage(cImages);
                iImage = x;
                break;
            }
        }

        delete [] pBuf;
    }

    return iImage;
}

void CWndTabsApp::LoadLangDLL(HMODULE hDLL)
{
    CLanguageDLL dll;
    CString cStr;
    int p;

    // temporarily switch resource handles
    HINSTANCE hResOld = AfxGetResourceHandle();
    AfxSetResourceHandle((HINSTANCE)hDLL);

    if (!dll.m_sAuthor.             LoadString(IDS_LANG_AUTHOR)       ||
        !dll.m_sLanguageNameEnglish.LoadString(IDS_LANG_NAME_ENGLISH) ||
        !dll.m_sLanguageNameNative. LoadString(IDS_LANG_NAME_NATIVE)  ||
        !dll.m_sFont.               LoadString(IDS_LANG_FONT) )
    {
        // not a valid dll - do nothing
        goto out;
    }

    p = dll.m_sFont.ReverseFind(',');
    if (p < 0) goto out;
    if (sscanf(dll.m_sFont.Mid(p + 1), "%d", &dll.m_iFontPoint) != 1)
    {
        goto out;
    }
    cStr = dll.m_sFont;
    dll.m_sFont = cStr.Left(p);

    if (!::GetModuleFileName(hDLL, dll.m_sDLLPath.GetBuffer(10240), 10240))
    {
        goto out;
    }
    dll.m_sDLLPath.ReleaseBuffer();
    p = dll.m_sDLLPath.ReverseFind('\\');
    dll.m_sDLLName = dll.m_sDLLPath.Mid(p + 1);
    dll.m_sDLLName.MakeLower();
    m_LangDLLs.Add(dll);

out:
    AfxSetResourceHandle(hResOld);
}

void CWndTabsApp::LoadLangDLLs()
{
    // add WndTabs.dll - it is the English language dll
    LoadLangDLL(AfxGetInstanceHandle());
    m_LangDLLs[0].m_sDLLName.Empty();  // use blank to indicate this option

    CPushCurrentDirectory pushDir;
    GoToModuleDirectory(AfxGetInstanceHandle());
    CFileFind f;
    BOOL bMore = f.FindFile("WndTabsLang*.dll");
    while (bMore)
    {
        bMore = f.FindNextFile();
        HMODULE hDLL = ::LoadLibrary(f.GetFilePath());
        if (hDLL)
        {
            LoadLangDLL(hDLL);
        }
    }

    ASSERT(m_LangDLLs.GetSize() >= 1);
}



// add-in entry functions adapted from Joshua Jensen's Workspace Whiz!
#define ADDIN_NAME      "Window Tabs"
#define ADDIN_KEY_NAME  "Window Tabs"
#define ADDIN_CONF_BASE "Software\\Freeware"
#define ADDIN_CONF_KEY  "WndTabs"

static const char * const ds_addin_keys[] = 
{
    DS6_ADDIN_KEY,
    DS5_ADDIN_KEY,
    EVC3_ADDIN_KEY,
    EVC4_ADDIN_KEY
};

HRESULT AddDSAddInEntries(CString &strDisplayName, CString& strDescription)
{
    // Get the module name.
    TCHAR moduleName[_MAX_PATH];
    moduleName[0] = 0;
    ::GetModuleFileName(AfxGetInstanceHandle(), (TCHAR*)&moduleName, 
        _MAX_PATH);

    // Get the module path.
    TCHAR modulePath[_MAX_PATH];
    _tcscpy(modulePath, moduleName);
    TCHAR* ptr = _tcsrchr(modulePath, '\\');
    *(ptr + 1) = 0;

    CString cStr;

    for (int i = 0; i < countof(ds_addin_keys); i++)
    {
        CRegKey devKey;

        // Create the add-in key.
        cStr = ds_addin_keys[i];
        cStr += '\\';
        cStr += ADDIN_KEY_NAME;

        if (devKey.Create(HKEY_CURRENT_USER, cStr) == ERROR_SUCCESS)
        {
            // Set entries
            devKey.SetValue("1");
            devKey.SetValue(strDescription, _T("Description"));
            devKey.SetValue(strDisplayName, _T("DisplayName"));
            devKey.SetValue(moduleName,     _T("Filename"));
        }
    }

    return S_OK;
}

HRESULT RemoveDSAddInEntries()
{
    CRegKey key;

    // Remove VC/eVC addin entries
    for (int i = 0; i < countof(ds_addin_keys); ++i)
    {
        if (key.Open(HKEY_CURRENT_USER, ds_addin_keys[i]) == ERROR_SUCCESS)
        {
            key.RecurseDeleteKey(ADDIN_KEY_NAME);
        }
    }

    // Remove WndTabs options in registry
    if (AfxMessageBox(IDS_REMOVE_CUSTOM_SETTINGS, MB_YESNO | MB_ICONQUESTION) 
        == IDYES)
    {
        CString sKeyBase = GetRegKeyBase();
        int pos = sKeyBase.ReverseFind('\\');
        if (pos > 0)
        {
            if (key.Open(HKEY_CURRENT_USER, sKeyBase.Left(pos)) == 
                ERROR_SUCCESS)
            {
                key.RecurseDeleteKey(sKeyBase.Mid(pos + 1));
            }
        }
    }

    return S_OK;
}



/////////////////////////////////////////////////////////////////////////////
// Special entry points required for inproc servers

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return _Module.GetClassObject(rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

// by exporting DllRegisterServer, you can use regsvr32.exe
STDAPI DllRegisterServer(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    HRESULT hRes = S_OK;
    
    // Registers object, typelib and all interfaces in typelib
    hRes = _Module.RegisterServer(TRUE);
    if (FAILED(hRes))
        return hRes;

    // Register description of this add-in object in its own
    //  "/Description" subkey.
    // TODO:  If you add more add-ins to this module, you need
    //  to register all of their descriptions, each description
    //  in each add-in object's registry CLSID entry:
    // HKEY_CLASSES_ROOT\Clsid\{add-in CLSID}\Description="add-in description"
    _ATL_OBJMAP_ENTRY* pEntry = _Module.m_pObjMap;
    CRegKey key;
    LONG lRes = key.Open(HKEY_CLASSES_ROOT, _T("CLSID"), KEY_READ);
    if (lRes == ERROR_SUCCESS)
    {
        USES_CONVERSION;
        LPOLESTR lpOleStr;
        StringFromCLSID(*pEntry->pclsid, &lpOleStr);
        LPTSTR lpsz = OLE2T(lpOleStr);

        lRes = key.Open(key, lpsz, KEY_WRITE);
        if (lRes == ERROR_SUCCESS)
        {
            CString strDescription;
            strDescription.LoadString(IDS_WNDTABS_DESCRIPTION);
            key.SetKeyValue(_T("Description"), strDescription);
            CString strDisplayName;
            strDisplayName.LoadString(IDS_WNDTABS_LONGNAME);
            char path[MAX_PATH];
            GetModuleFileName(AfxGetInstanceHandle(), path, sizeof(path));
            aiclGetFileVersion(path, g_cVersion.GetBuffer(50));
            strDisplayName += " ";
            strDisplayName += g_cVersion;
            AddDSAddInEntries(strDisplayName, strDescription);
        }
        CoTaskMemFree(lpOleStr);
    }
    if (lRes != ERROR_SUCCESS)
        hRes = HRESULT_FROM_WIN32(lRes);

    return hRes;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    HRESULT hRes;
    hRes = _Module.UnregisterServer();
    if (SUCCEEDED(hRes))
        hRes = RemoveDSAddInEntries();
    return hRes;
}


/////////////////////////////////////////////////////////////////////////////
// Debugging support

// GetLastErrorDescription is used in the implementation of the VERIFY_OK
//  macro, defined in stdafx.h.

#ifdef _DEBUG

void GetLastErrorDescription(CComBSTR& bstr)
{
    CComPtr<IErrorInfo> pErrorInfo;
    if (GetErrorInfo(0, &pErrorInfo) == S_OK)
        pErrorInfo->GetDescription(&bstr);
}

#endif //_DEBUG

bool CWndTabsApp::Focus()
{
    return 1;
    m_iFocusCount++;
    m_pMainWnd->SetFocus();
    if (m_iFocusCount == 1)
    {
/*        pOldParent = m_pMainWnd->GetParent();
        m_pMainWnd->SetParent(NULL);
*/    
/*        hOldParent = ::GetParent(m_pMainWnd->m_hWnd);
        m_pMainWnd->SetParent(NULL);
*/    }
    return (m_iFocusCount == 1);
}

void CWndTabsApp::UnFocus()
{
    if (m_iFocusCount > 0)
    {
        m_iFocusCount--;
/*        if (m_iFocusCount == 0)
            m_pMainWnd->SetParent(CWnd::FromHandle(hOldParent));
*/    }
}

long CWTManageState::m_cRef = 0;

CWTManageState::CWTManageState(AFX_MODULE_STATE* pModuleState) : 
    m_state(pModuleState)
{
    if (!g_pMainFrame) return;

    CFrameWnd *& pRoutingFrame = AfxGetThreadState()->m_pRoutingFrame;
    if (!pRoutingFrame  ||  pRoutingFrame->m_hWnd == g_pMainFrame->m_hWnd)
    {
        pRoutingFrame = (CFrameWnd *)g_pDevStudioWnd;
    }
//    InterlockedIncrement(&m_cRef);
}

CWTManageState::~CWTManageState()
{
//    WT_ASSERT(m_cRef > 0);
//    if (InterlockedDecrement(&m_cRef) == 0)
    {
/*        g_pMainFrame->ModifyStyle(0, WS_CHILD,
            SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOMOVE | SWP_NOREPOSITION);
*///        AfxGetThreadState()->m_pRoutingFrame = g_pMainFrame;
    }
}

bool CLanguageDLL::Apply()
{
    WT_L1_TRACE("Loading language dll %s\n", m_sDLLPath);
    if (!m_hDLL)
    {
        m_hDLL = ::LoadLibrary(m_sDLLPath);
        WT_ASSERT(m_hDLL);
    }
    if (m_hDLL)
    {
        char ver[100];
        aiclGetFileVersion(m_sDLLPath, ver);
        if (g_cVersion != ver)
        {
            CString msg;
            AfxFormatString2(msg, IDS_ERR_LANG_WRONG_VER,
                m_sDLLPath, g_cVersion);
            CString_Replace(msg, "%s", ver);
            AfxMessageBox(msg, MB_OK | MB_ICONEXCLAMATION);
            Release();
            WT_L1_TRACE("  .. dll is wrong version (%s)\n", ver);
        }
        else
        {
            AfxSetResourceHandle(m_hDLL);
        }
    }
    if (!m_hDLL)
    {
        WT_L1_TRACE("  .. dll load failed!");
        return false;
    }
    return true;
}

void CLanguageDLL::Release()
{
    if (m_hDLL) 
    {
        ::FreeLibrary(m_hDLL);
        m_hDLL = NULL;
    }
}
