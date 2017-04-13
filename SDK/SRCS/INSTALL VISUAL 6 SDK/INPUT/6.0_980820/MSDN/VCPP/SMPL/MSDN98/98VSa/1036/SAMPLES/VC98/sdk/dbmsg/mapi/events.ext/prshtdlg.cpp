///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      PRSHTDLG.CPP
//
//  Description
//      This file contains the dialogproc that handles messages for
//      the property page extended onto the Tools Options Property Sheet
//
//  Revision: 1.00
//
//  Copyright (c) 1992-1995 Microsoft Corporation. All rights reserved.
//

#include "EVNTEXT.H"


///////////////////////////////////////////////////////////////////////////////
//    FUNCTION SignatureOptionsDlgProc
//
//    Parameters
//    hDlg   - handle to modeless dialog, the property page
//    uMsg   - message
//    wParam - wParam of wndproc, not used
//    lParam - lParam of wndproc, points to NMHDR for notifications
//
//    Purpose
//    Handles the notifications sent for managing a custom property page
//    to allow user to turn Signtures on or off.
//
//    Return Value
//    Appropriate return values are set in the DWL_MSGRESULT longword
//    of the dialog handle.  See Win95 Common Controls documentation on
//    Property Sheets for more information.
//

BOOL CALLBACK SignatureOptionsDlgProc(HWND hDlg, UINT uMsg, 
        WPARAM wParam, LPARAM lParam)
{
 BOOL bMsgResult;
 static HBRUSH hBrush;
 static COLORREF GrayColor;
 static LPNMHDR pnmhdr;
 static HWND hWndPage;

 switch (uMsg)
 {

  case WM_INITDIALOG:
  {
   LOGBRUSH lb;

    GrayColor = (COLORREF)GetSysColor(COLOR_BTNFACE);

    memset(&lb, 0, sizeof(LOGBRUSH));
    lb.lbStyle = BS_SOLID;
    lb.lbColor = GrayColor;
    hBrush = CreateBrushIndirect(&lb);

    return TRUE;
  }
  break;

  case WM_CTLCOLORDLG:
  case WM_CTLCOLORBTN:
  case WM_CTLCOLORSTATIC:
  
    if (hBrush != NULL)
    {
      SetBkColor((HDC)wParam, GrayColor);

      return (BOOL)hBrush;
    }

  break;

  case WM_DESTROY:
  {
   if (hBrush != NULL)
        DeleteObject(hBrush);
    

   return TRUE;
  }
  
  case WM_COMMAND:
  {
   if (LOWORD(wParam) == IDC_ENABLESGN)
   {
      SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);
      bSignatureOn = SendDlgItemMessage(hDlg, IDC_ENABLESGN, BM_GETCHECK, 0, 0L);
      bMsgResult = FALSE;
   }
  }
  break;

  case WM_NOTIFY:
  {
   pnmhdr = ((LPNMHDR) lParam);

   switch ( pnmhdr->code)
   {
    case PSN_KILLACTIVE:
        bMsgResult = FALSE;  // allow this page to receive PSN_APPLY
        break;

    case PSN_SETACTIVE:

        // initialize controls
        if (bSignatureOn)
            SendDlgItemMessage(hDlg, IDC_ENABLESGN, BM_SETCHECK, 1, 0L);
        else
            SendDlgItemMessage(hDlg, IDC_ENABLESGN, BM_SETCHECK, 0, 0L);

        hWndPage = pnmhdr->hwndFrom;   // to be used in WM_COMMAND
             
        bMsgResult = FALSE;  // accepts activation
        break;

    case PSN_APPLY:

        // get user input
        bSignatureOn = SendDlgItemMessage(hDlg, IDC_ENABLESGN, BM_GETCHECK, 0, 0L);

        bMsgResult = PSNRET_NOERROR;
        break;

    case PSN_HELP:                                              
        MessageBox( pnmhdr->hwndFrom,
                    "Microsoft Exchange Client\n"
                    "Message Event Extension Sample\n"
                    "Microsoft (c) Corporation, 1995",
                    "About",
                    MB_OK);
        bMsgResult = TRUE;    // doesn't matter on this notification
        break;


    default:
        bMsgResult = FALSE;
        break;
   }  // switch

    SetWindowLong( hDlg, DWL_MSGRESULT, bMsgResult);
    break;
  
  }   // case WM_NOTIFY

  default:
    bMsgResult = FALSE;
    break;

 }  // switch


 return bMsgResult;
}
