#define STRICT
#define INITGUID
#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include "IPoint.h"
#include "CF.h"

const BOOL bIsDll = FALSE;
void SvcLock() {}
void SvcUnlock() {}

extern IPointAndText *g_ppt;
extern DWORD dwReg;

void
ShareCli_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id) {
    case IDC_WRITE:
    {
        BOOL bGood;
        int x = (int)GetDlgItemInt(hwnd, IDC_X, &bGood, TRUE);
        if (!bGood)
        {
            MessageBox(hwnd, "Not an integer", "Error", MB_OK);
            SetFocus(GetDlgItem(hwnd, IDC_X));
            return;
        }

        int y = (int)GetDlgItemInt(hwnd, IDC_Y, &bGood, TRUE);
        if (!bGood)
        {
            MessageBox(hwnd, "Not an integer", "Error", MB_OK);
            SetFocus(GetDlgItem(hwnd, IDC_Y));
            return;
        }
        char sz[256];
        GetDlgItemText(hwnd, IDC_TEXT, sz, sizeof(sz));
        g_ppt->Set(x, y);
        g_ppt->SetText(sz);
        break;
    }
    case IDOK:
    case IDC_READ:
    {
        long x, y;
        char sz[256];
        g_ppt->Get(&x, &y);
        g_ppt->GetText(sz, sizeof(sz));

        SetDlgItemInt(hwnd, IDC_X, x, TRUE);
        SetDlgItemInt(hwnd, IDC_Y, y, TRUE);
        SetDlgItemText(hwnd, IDC_TEXT, sz);
        break;
    }
    case IDCANCEL:
        EndDialog(hwnd, id);
    }
}


inline BOOL
ShareCli_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	BOOL result = TRUE;
    FORWARD_WM_COMMAND(hwnd, IDC_READ, GetDlgItem(hwnd, IDC_READ), BN_CLICKED, PostMessage);
    if (dwReg)
        SetWindowText(hwnd, "Initial Owner");
    return result;
}


BOOL CALLBACK ShareCli_WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		case WM_COMMAND:
			HANDLE_WM_COMMAND(hwnd,wParam,lParam,ShareCli_OnCommand);
			return TRUE;
		case WM_INITDIALOG:
			SetWindowLong(hwnd,DWL_MSGRESULT,(long)HANDLE_WM_INITDIALOG(hwnd,wParam,lParam,ShareCli_OnInitDialog));
			return TRUE;
		default: return FALSE;
	}
}

IPointAndText *g_ppt = 0;
DWORD dwReg = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    CoInitialize(0);
    CoSingletonClassFactory classFactory(0);
    if (FAILED(CoCreateInstance(CLSID_CoSharedPoint,
                                 0,
                                 CLSCTX_LOCAL_SERVER,
                                 IID_IPointAndText,
                                 (void**)&g_ppt)))
    {
        
        CoCreateInstance(CLSID_CoSharedPoint,
                         0,
                         CLSCTX_INPROC_SERVER,
                         IID_IPointAndText,
                         (void**)&g_ppt);
        
        classFactory.SetObject(g_ppt);
        CoRegisterClassObject(CLSID_CoSharedPoint,
                              &classFactory,
                              CLSCTX_LOCAL_SERVER,
                              REGCLS_MULTIPLEUSE,
                              &dwReg);

    }
                               
    
    
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),
              0, ShareCli_WndProc);

    if (dwReg)
        CoRevokeClassObject(dwReg);
    if (g_ppt)
        g_ppt->Release();    
    CoUninitialize();
    return 0;
}
