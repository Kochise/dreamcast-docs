/******************************************************************************
Module name: DispRes.cpp
Written by:  Jeffrey Richter
Notices:     Written 1995 by Jeffrey Richter
******************************************************************************/


#define STRICT
#include <Windows.H>
#include <WindowsX.H>
#include "Resource.H"


///////////////////////////////////////////////////////////////////////////////


// The normal HANDLE_MSG macro in WINDOWSX.H does not work properly for dialog
// boxes because DlgProc's return a BOOL instead of an LRESULT (like
// WndProcs). This adgHANDLE_DLGMSG macro corrects the problem:
#define adgHANDLE_DLGMSG(hwnd, message, fn)                          \
   case (message): return (SetDlgMsgResult(hwnd, uMsg,               \
      HANDLE_##message((hwnd), (wParam), (lParam), (fn))))


///////////////////////////////////////////////////////////////////////////////


// The name of our application.
static TCHAR g_szAppName[] = __TEXT("Change Display Resolution");

// Msg ID that is sent to us by the system when the user's performs mouse 
// actions over the icon that we added to the tray.
#define UM_DISPRESICONNOTIFY     (WM_USER + 100)

// The starting menu item ID for display resolutions.
#define IDM_DISPRES  200


///////////////////////////////////////////////////////////////////////////////


BOOL DispRes_OnInitDialog (HWND hwnd, HWND hwndFocus, LPARAM lParam) {

   // Add the notification icon to the taskbar
   NOTIFYICONDATA nid;
   nid.cbSize = sizeof(nid);
   nid.hWnd = hwnd;        
   nid.uID = IDI_DISPRES;   
   nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
   nid.uCallbackMessage = UM_DISPRESICONNOTIFY;
   nid.hIcon = LoadIcon(GetWindowInstance(hwnd), MAKEINTRESOURCE(IDI_DISPRES));
   lstrcpyn(nid.szTip, g_szAppName, sizeof(nid.szTip) / sizeof(nid.szTip[0]));
   Shell_NotifyIcon(NIM_ADD, &nid);

   // Set an icon with our window
   SendMessage(hwnd, WM_SETICON, (WPARAM) TRUE, (LPARAM) nid.hIcon);

   return(TRUE);
}


///////////////////////////////////////////////////////////////////////////////


void DispRes_OnDestroy (HWND hwnd) {

   // Remove the notification icon from the taskbar
   NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = hwnd;
	nid.uID = IDI_DISPRES;
	Shell_NotifyIcon(NIM_DELETE, &nid);
}


///////////////////////////////////////////////////////////////////////////////


// Sort all of the display modes:
// 1: Resolution (width), 2: color depth, 3: frequency.
int _cdecl DispRes_DevModeCompare (const void *elem1, const void *elem2) {
   PDEVMODE pdvmd1 = (PDEVMODE) elem1, pdvmd2 = (PDEVMODE) elem2;

   int n = pdvmd1->dmPelsWidth - pdvmd2->dmPelsWidth;
   if (n != 0) return(n);

   n = pdvmd1->dmBitsPerPel - pdvmd2->dmBitsPerPel;
   if (n != 0) return(n);

   n = pdvmd1->dmDisplayFrequency - pdvmd2->dmDisplayFrequency;
   return(n);
}
  

///////////////////////////////////////////////////////////////////////////////


// A mouse message occured over our notification icon.
void DispRes_OnIconNotify (HWND hwnd, UINT uID, UINT uMsg) {

   // This sample only processes WM_LBUTTONUP messages
   if (uMsg != WM_LBUTTONUP)
      return;

   // Prepare the context menu for display by 
   // adding all the possible display resolutions.

   // Load the empty, default menu resource.
   HMENU hmenuMain = LoadMenu(GetWindowInstance(hwnd), 
      MAKEINTRESOURCE(IDR_DISPRES));

   // Get the handle of the first popup menu
   HMENU hmenuContext = GetSubMenu(hmenuMain, 0);

   DWORD dwModeNum = (DWORD) -1; // # of DEVMODEs
   DEVMODE dvmd[200];      // Information about supported display resolutions
   TCHAR szBuf[100];       // String to display in context menu
   DWORD dwMenuIndex = 0;  // Index into menu where item should be inserted
   HDC hdc = GetDC(hwnd);  // Screen DC used to get current resolution info

   // Get all of the possible display modes
   ZeroMemory(&dvmd, sizeof(dvmd));
   do {
      dwModeNum++;
      dvmd[dwModeNum].dmSize = sizeof(DEVMODE);
      dvmd[dwModeNum].dmDriverExtra = 0;
   } while (EnumDisplaySettings(NULL, dwModeNum, &dvmd[dwModeNum]));

   // Sort all of the display modes:
   // 1: Resolution (width), 2: color depth, 3: frequency.
   qsort(&dvmd[0], dwModeNum, sizeof(DEVMODE), DispRes_DevModeCompare);

   for (DWORD dw = 0; dw < dwModeNum; dw++) {

      if (dw > 0) {
         // If this is not the first DEVMODE entry, possibly add a seperator bar

         if ((dvmd[dw].dmPelsWidth  == dvmd[dw - 1].dmPelsWidth) &&
             (dvmd[dw].dmPelsHeight == dvmd[dw - 1].dmPelsHeight) &&
             (dvmd[dw].dmBitsPerPel == dvmd[dw - 1].dmBitsPerPel)) {
            // This entry is identical to the previous entry except for refrash rate
            // Let's not add this entry to the menu
            continue;
         }
         
         if ((dvmd[dw].dmPelsWidth  != dvmd[dw - 1].dmPelsWidth) || 
             (dvmd[dw].dmPelsHeight != dvmd[dw - 1].dmPelsHeight)) {

            // We started a new resolution, insert a seperator bar
            InsertMenu(hmenuContext, dwMenuIndex++, 
               MF_BYPOSITION | MF_SEPARATOR, 0, NULL);
         }
      }

      // Construct the menu item text
      wsprintf(szBuf, __TEXT("%dx%d (%d bit)"),
         dvmd[dw].dmPelsWidth, dvmd[dw].dmPelsHeight, dvmd[dw].dmBitsPerPel);

      // Determine if the current display resolution matches the menu item
      BOOL fCurrentRes = 
         (dvmd[dw].dmPelsWidth  == (DWORD) GetDeviceCaps(hdc, HORZRES)) &&
         (dvmd[dw].dmPelsHeight == (DWORD) GetDeviceCaps(hdc, VERTRES)) &&
         (dvmd[dw].dmBitsPerPel == (DWORD) GetDeviceCaps(hdc, BITSPIXEL));

      InsertMenu(hmenuContext, dwMenuIndex++, 
         MF_BYPOSITION | MFS_ENABLED | (fCurrentRes ? MFS_CHECKED : MFS_UNCHECKED),
         IDM_DISPRES + dw, szBuf);
   }

   // Now, we can display the context menu on the screen.

   // First, connect our thread to the raw-input-thread so that 
   // keyboard messages go to our thread and the menu.
	SetForegroundWindow(hwnd);	

   // Display the context menu near the mouse cursor
   POINT pt;
   GetCursorPos(&pt);
   UINT uMenuID = TrackPopupMenu(hmenuContext, 
      TPM_BOTTOMALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON | TPM_RETURNCMD,
      pt.x, pt.y, 0, hwnd, NULL);

   // We no longer need the menu
   DestroyMenu(hmenuMain);

   // Fixes a bug in TrackPopupMenu that causes the menu 
   // to appear and immediately disappear
	PostMessage(hwnd, WM_NULL, 0, 0);	

   switch (uMenuID) {
      case 0:  // The menu was cancelled
         break;

      case ID_ABOUT:
         // Center the dialog box on the screen.  We can't do this during
         // OnInitDialog because the screen resolution will change.
         RECT rc;
         GetWindowRect(hwnd, &rc);
         SetWindowPos(hwnd, NULL, 
            (GetSystemMetrics(SM_CXSCREEN) - (rc.right - rc.left)) / 2,
            (GetSystemMetrics(SM_CYSCREEN) - (rc.bottom - rc.top)) / 2,
            0, 0, SWP_NOZORDER | SWP_NOSIZE);

         ShowWindow(hwnd, SW_SHOW);
         break;

      case ID_EXIT:
         PostQuitMessage(1);
         break;

      default:
         // Get the display resolution info for the selected menu item
         // Message box text and buttons
         LPCTSTR psz;
         int nMBBtn = MB_OK;

         // Kepp the current refresh rate
         dvmd[uMenuID - IDM_DISPRES].dmDisplayFrequency = GetDeviceCaps(hdc, VREFRESH);

         // Attempt to change the display resolution.
         switch (ChangeDisplaySettings(&dvmd[uMenuID - IDM_DISPRES], CDS_UPDATEREGISTRY)) {

            case DISP_CHANGE_SUCCESSFUL:
               psz = __TEXT("Display change successful."); 
               break;

            case DISP_CHANGE_RESTART:
               psz = __TEXT("You must restart your computer before the ")
                  __TEXT("new settings will take effect.\n\n")
                  __TEXT("Do you want to restart your computer now?"); 
               nMBBtn = MB_YESNO; 
               break;

            case DISP_CHANGE_BADFLAGS:
               psz = __TEXT("An invalid set of flags was passed in."); 
               break;

            case DISP_CHANGE_FAILED:
               psz =__TEXT("The display driver couldn't change the display.");
               break;

            case DISP_CHANGE_BADMODE:
               psz = __TEXT("Invalid settings."); 
               break;

            case DISP_CHANGE_NOTUPDATED:
               psz = __TEXT("Unable to write settings to the registry."); 
               break;
         }

         // Show the user the results
         if (IDYES == MessageBox(NULL, psz, g_szAppName, 
            nMBBtn | MB_ICONINFORMATION)) {

            // If the user wants to reboot the computer, do so.
            // Windows NT: We must enable our shutdown privilege 
            //             assumming we have it.
            // Windows 95: OpenProcessToken, LookupPrivilegeValue, and 
            //             AdjustTokenPrivileges are not implemented and
            //             are ignored.
            HANDLE hToken;
            TOKEN_PRIVILEGES tkp;

            // We want to adjust our process's privileges.
            OpenProcessToken(GetCurrentProcess(), 
               TOKEN_ADJUST_PRIVILEGES, &hToken);

            // Get the LUID for shutdown privilege
            LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
            tkp.PrivilegeCount = 1;  // one privilege to set
            tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

            // Turn the SE_SHUTDOWN_NAME privilege on for our process
            AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0);
            CloseHandle(hToken);

            // Shut down and reboot the system.
            ExitWindowsEx(EWX_REBOOT, 0);
         }
         break;
   }         
   ReleaseDC(hwnd, hdc);
}


///////////////////////////////////////////////////////////////////////////////


void DispRes_OnCommand (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {

   switch (id) {
      case IDOK:
      case IDCANCEL:
         // We just hide the box instead of destroying it.  We destroy the
         // box when the user chooses Exit from the conext menu
         ShowWindow(hwnd, SW_HIDE);
         break;
   }
}


///////////////////////////////////////////////////////////////////////////////


BOOL WINAPI DispRes_WndProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

   switch (uMsg) {

      case UM_DISPRESICONNOTIFY:
         // A mouse message occured over our notification icon
         DispRes_OnIconNotify(hwnd, (UINT) wParam, (UINT) lParam);
         return(TRUE);

      adgHANDLE_DLGMSG(hwnd, WM_INITDIALOG, DispRes_OnInitDialog);
      adgHANDLE_DLGMSG(hwnd, WM_DESTROY,    DispRes_OnDestroy);
      adgHANDLE_DLGMSG(hwnd, WM_COMMAND,    DispRes_OnCommand);
   }

   return(FALSE);
}


///////////////////////////////////////////////////////////////////////////////


// Variables shared across all instances of our application which ensure
// that only one instance of this application  will run at a given time.
#pragma data_seg("Shared")
static LONG g_lInstanceCount = -1;
#pragma data_seg()

#pragma data_seg(".drectve")
static char szShared[] = "-section:Shared,rws";
#pragma data_seg()


///////////////////////////////////////////////////////////////////////////////


int WINAPI WinMain (HINSTANCE hinstExe, HINSTANCE hinstExePrev, 
                    LPSTR pszCmdLine, int nCmdShow) {

   // Only allow one instance of our application to execute
   if (InterlockedIncrement(&g_lInstanceCount) > 0) {

      InterlockedDecrement(&g_lInstanceCount);
      MessageBox(NULL, __TEXT("Display Resolution is already running"), 
         g_szAppName, MB_ICONINFORMATION | MB_OK);

   } else {

      // Create our modeless dialog About dialog box.
      HWND hwnd = CreateDialog(hinstExe, MAKEINTRESOURCE(IDD_DISPRES), 
         NULL, DispRes_WndProc);

      // Keep our process running
      MSG msg;
      while (GetMessage(&msg, hwnd, 0, 0)) {
         if (!IsDialogMessage(hwnd, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
         }
      }

      // Destroy the dialog box (which removes the notification icon)
      DestroyWindow(hwnd);
   }

   return(0);
}


///////////////////////////////// End of File /////////////////////////////////
