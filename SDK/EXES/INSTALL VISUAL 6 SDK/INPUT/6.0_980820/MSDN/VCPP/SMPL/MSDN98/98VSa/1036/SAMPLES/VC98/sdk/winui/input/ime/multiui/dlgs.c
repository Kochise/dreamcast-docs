/**********************************************************************/
/*                                                                    */
/*      DLGS.C                                                        */
/*                                                                    */
/*      Copyright (c) 1995-1996  Microsoft Corporation                     */
/*                                                                    */
/**********************************************************************/

#include "windows.h"
#include "imm.h"
#include "resource.h"
#include "multiui.h"

/**********************************************************************/
/*                                                                    */
/*    About(HWND, UINT, WPARAM, LPARAM)                               */
/*                                                                    */
/**********************************************************************/
BOOL FAR PASCAL AboutDlg(hDlg, message, wParam, lParam)
HWND hDlg;
unsigned message;
WPARAM wParam;
LPARAM lParam;
{
    switch (message) {
        case WM_INITDIALOG:
            return (TRUE);

        case WM_COMMAND:
            if (wParam == IDOK
                || wParam == IDCANCEL) {
                EndDialog(hDlg, TRUE);
                return (TRUE);
            }
            break;
    }
    return (FALSE);
}

