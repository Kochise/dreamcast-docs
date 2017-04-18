#ifndef __WININETUI_H
#define __WININETUI_H

#define MB_OK                       0x00000000L
#define MB_YESNO                    0x00000004L
#define MB_ICONEXCLAMATION          0x00000030L
#define MB_SETFOREGROUND            0x00010000L
#define IDNO                        7

DWORD LaunchDlg(HWND hWnd, LPVOID lpParam, DWORD dwDlgResource);

int LaunchMessageBox(HWND hWnd, DWORD dwMsgBoxID);

#endif // __WININETUI_H
