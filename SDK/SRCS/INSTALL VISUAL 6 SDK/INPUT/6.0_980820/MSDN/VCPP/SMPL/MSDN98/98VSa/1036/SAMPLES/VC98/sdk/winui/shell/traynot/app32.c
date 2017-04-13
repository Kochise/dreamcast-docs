//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include "app32.h"
#include <windowsx.h>

#include "resource.h"

#define MYWM_NOTIFYICON		(WM_APP+100)

//---------------------------------------------------------------------------
// Global to everybody...
HINSTANCE g_hinst;

#ifndef ARRAYSIZE
#define ARRAYSIZE(a)    (sizeof(a)/sizeof(a[0]))
#endif

struct _DLGITEMS
{
	DWORD dwStart;
	UINT uNotify;
	UINT uDelayID;
	UINT uState1;
	UINT uTip1;
	UINT uState2;
	UINT uTip2;
} g_sDlgItems [] =
{
	{
		0, IDC_NOTIFY1, IDC_DELAY1, IDC_STATE11, IDC_TIP11, IDC_STATE12, IDC_TIP12,
	},
	{
		0, IDC_NOTIFY2, IDC_DELAY2, IDC_STATE21, IDC_TIP21, IDC_STATE22, IDC_TIP22,
	},
	{
		0, IDC_NOTIFY3, IDC_DELAY3, IDC_STATE31, IDC_TIP31, IDC_STATE32, IDC_TIP32,
	},
} ;


BOOL TrayMessage(HWND hDlg, DWORD dwMessage, UINT uID, HICON hIcon, PSTR pszTip)
{
        BOOL res;

	NOTIFYICONDATA tnd;

	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= hDlg;
	tnd.uID			= uID;

	tnd.uFlags		= NIF_MESSAGE|NIF_ICON|NIF_TIP;
	tnd.uCallbackMessage	= MYWM_NOTIFYICON;
	tnd.hIcon		= hIcon;
	if (pszTip)
	{
		lstrcpyn(tnd.szTip, pszTip, sizeof(tnd.szTip));
	}
	else
	{
		tnd.szTip[0] = '\0';
	}

	res = Shell_NotifyIcon(dwMessage, &tnd);

	if (hIcon)
	    DestroyIcon(hIcon);

	return res;
}


LRESULT IconDrawItem(LPDRAWITEMSTRUCT lpdi)
{
	HICON hIcon;

	hIcon = (HICON)LoadImage(g_hinst, MAKEINTRESOURCE(lpdi->CtlID), IMAGE_ICON,
		16, 16, 0);
	if (!hIcon)
	{
		return(FALSE);
	}

	DrawIconEx(lpdi->hDC, lpdi->rcItem.left, lpdi->rcItem.top, hIcon,
		16, 16, 0, NULL, DI_NORMAL);

	return(TRUE);
}


void StateChange(HWND hDlg, UINT uIndex, UINT uSelect)
{
	UINT uState1, uState2;
	HWND hwndIcon;
	LPCSTR pszIDIcon;
	UINT uTip;
	char szTip[64];

	uState1 = g_sDlgItems[uIndex].uState1;
	uState2 = g_sDlgItems[uIndex].uState2;

	// if !uSelect, find out which button is selected
	if (!uSelect)
	{
		uSelect = IsDlgButtonChecked(hDlg, uState2) ? uState2 : uState1;
	}
	// if uSelect<0, find out shich button is NOT selected
	else if ((int)uSelect < 0)
	{
		uSelect = IsDlgButtonChecked(hDlg, uState2) ? uState1 : uState2;
	}

	CheckRadioButton(hDlg, uState1, uState2, uSelect);

	// If there is a tip specified, use it, otherwise use the default
	uTip = uSelect==uState1
		? g_sDlgItems[uIndex].uTip1 : g_sDlgItems[uIndex].uTip2;
	if (!GetDlgItemText(hDlg, uTip, szTip, sizeof(szTip))
		&& !LoadString(g_hinst, uSelect, szTip, sizeof(szTip)))
	{
		*szTip = '\0';
	}

	// HACK: The ID of window after the radio button is the ID of the icon
	hwndIcon = GetWindow(GetDlgItem(hDlg, uSelect), GW_HWNDNEXT);
	pszIDIcon = MAKEINTRESOURCE(GetDlgCtrlID(hwndIcon));

	TrayMessage(hDlg, NIM_MODIFY, g_sDlgItems[uIndex].uNotify,
		LoadImage(g_hinst, pszIDIcon, IMAGE_ICON, 16, 16, 0), szTip);
}


void NotifyDelete(HWND hDlg, UINT uIndex)
{
	TrayMessage(hDlg, NIM_DELETE, g_sDlgItems[uIndex].uNotify, NULL, NULL);
}


void NotifyAdd(HWND hDlg, UINT uIndex)
{
	TrayMessage(hDlg, NIM_ADD, g_sDlgItems[uIndex].uNotify, NULL, NULL);

	StateChange(hDlg, uIndex, 0);
}


void NotifyChange(HWND hDlg, UINT uIndex)
{
	UINT uDelay;
	BOOL bTranslated;
	BOOL bEnable;

	if (IsDlgButtonChecked(hDlg, g_sDlgItems[uIndex].uNotify))
	{
		uDelay = GetDlgItemInt(hDlg, g_sDlgItems[uIndex].uDelayID,
			&bTranslated, FALSE);
		if (uDelay)
		{
			g_sDlgItems[uIndex].dwStart = GetTickCount() + uDelay*60000;
			SetTimer(hDlg, uIndex, 60000, NULL);
		}
		else
		{
			NotifyAdd(hDlg, uIndex);
		}
	}
	else
	{
		NotifyDelete(hDlg, uIndex);
	}

	for (uIndex=0, bEnable=FALSE; uIndex<ARRAYSIZE(g_sDlgItems); ++uIndex)
	{
		if (IsDlgButtonChecked(hDlg, g_sDlgItems[uIndex].uNotify))
		{
			bEnable = TRUE;
		}
	}
	EnableWindow(GetDlgItem(hDlg, IDABORT), bEnable);
}


BOOL CALLBACK TestAppDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;

	case WM_DRAWITEM:
		return(IconDrawItem((LPDRAWITEMSTRUCT)lParam));
		break;

	case WM_DESTROY:
		NotifyDelete(hDlg, 0);
		NotifyDelete(hDlg, 1);
		NotifyDelete(hDlg, 2);
		break;

	case WM_TIMER:
		if (wParam >= ARRAYSIZE(g_sDlgItems))
		{
			break;
		}

		if ((int)(GetTickCount() - g_sDlgItems[wParam].dwStart) < 0)
		{
			break;
		}

		KillTimer(hDlg, wParam);
		NotifyAdd(hDlg, wParam);
		break;

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDCANCEL:
			EndDialog(hDlg, TRUE);
			break;

		case IDABORT:
			ShowWindow(hDlg, SW_HIDE);
			break;

		case IDC_NOTIFY1:
			NotifyChange(hDlg, 0);
			break;

		case IDC_NOTIFY2:
			NotifyChange(hDlg, 1);
			break;

		case IDC_NOTIFY3:
			NotifyChange(hDlg, 2);
			break;

		case IDC_STATE11:
		case IDC_STATE12:
			StateChange(hDlg, 0, GET_WM_COMMAND_ID(wParam, lParam));
			break;

		case IDC_STATE21:
		case IDC_STATE22:
			StateChange(hDlg, 1, GET_WM_COMMAND_ID(wParam, lParam));
			break;

		case IDC_STATE31:
		case IDC_STATE32:
			StateChange(hDlg, 2, GET_WM_COMMAND_ID(wParam, lParam));
			break;
		}
		break;

	case MYWM_NOTIFYICON:
		switch (lParam)
		{
		case WM_LBUTTONDOWN:
			switch (wParam)
			{
			case IDC_NOTIFY1:
				StateChange(hDlg, 0, (UINT)-1);
				break;

			case IDC_NOTIFY2:
				StateChange(hDlg, 1, (UINT)-1);
				break;

			case IDC_NOTIFY3:
				StateChange(hDlg, 2, (UINT)-1);
				break;

			default:
				break;
			}
			break;

		case WM_RBUTTONDOWN:
			ShowWindow(hDlg, SW_SHOW);
			SetForegroundWindow(hDlg);	// make us come to the front
			break;

		default:
			break;
		}
		break;

	default:
		return(FALSE);
	}

	return(TRUE);
}


//---------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_hinst = hInstance;
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_APP32), NULL, TestAppDlgProc);
	return(FALSE);
}

