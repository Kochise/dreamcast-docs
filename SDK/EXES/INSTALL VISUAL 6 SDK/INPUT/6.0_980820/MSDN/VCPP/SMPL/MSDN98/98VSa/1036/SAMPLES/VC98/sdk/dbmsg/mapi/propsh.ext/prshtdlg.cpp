///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      PRSHTDLG.CPP
//
//  Description
//      This file contains the dialogproc that handles messages for
//      the property page extended onto the Exchange property sheet.
//
//
//  Revision: 1.00
//
//  Copyright (c) 1992-1995 Microsoft Corporation. All rights reserved.
//
#include "EXTPRSHT.H"

///////////////////////////////////////////////////////////////////////////////
//    Office document summary sheet information data
//    Pointers to items in pSummaryProps.  See GetPages function 
//    in EXTPRSHT.CPP
//
LPSTR szDocComments = NULL;
LPSTR szDocApplication = NULL;
LPSTR szDocTitle = NULL;
LPSTR szDocSubject = NULL;
LPSTR szDocAuthor = NULL;
SLPSTRArray mvszKeywords;
LPSTR szDocKeywords = NULL;  
LPSTR szDocLastSaved = NULL;
LPSTR szDocEditTime = NULL;
LPSTR szDocCategory = NULL;
LPSTR szDocCompany = NULL;



///////////////////////////////////////////////////////////////////////////////
//    FUNCTION SummaryPageDlgProc
//
//    Parameters
//    hDlg   - handle to modeless dialog, the property page
//    uMsg   - message
//    wParam - wParam of wndproc, not used
//    lParam - lParam of wndproc, points to NMHDR for notifications
//
//    Purpose
//    Handles the notifications sent for managing a custom property page
//    appended to those on an Exchange Client property sheet.
//
//    Return Value
//    Appropriate return values are set in the DWL_MSGRESULT longword
//    of the dialog handle.  See Win95 Common Controls documentation on
//    Property Sheets for more information.
//


BOOL CALLBACK SummaryPageDlgProc(HWND hDlg, UINT uMsg, 
        WPARAM wParam, LPARAM lParam)
{
 BOOL bMsgResult = FALSE;
 UINT i;
 static HBRUSH hBrush;
 static COLORREF GrayColor;

 switch (uMsg)
 {

  case WM_INITDIALOG:
  {
   LPSTR szTemp;
   LOGBRUSH lb;

   // build a string of space delimited keywords from the mvstring.
        for (i=0; i<mvszKeywords.cValues; i++)
        {
           if (szDocKeywords == NULL)
           {
                szDocKeywords = (LPSTR)malloc(lstrlen(mvszKeywords.lppszA[i]) + 1);
                lstrcpy(szDocKeywords, mvszKeywords.lppszA[i]);
           }
           else
           {
            szTemp = (LPSTR) malloc(lstrlen(szDocKeywords) + lstrlen(mvszKeywords.lppszA[i]) + 3);
            lstrcpy(szTemp, szDocKeywords);
            lstrcat(szTemp, " ");
            lstrcat(szTemp, mvszKeywords.lppszA[i]);

            free(szDocKeywords);
            szDocKeywords = szTemp;
           }

        }

        GrayColor = (COLORREF)GetSysColor(COLOR_BTNFACE);

        memset(&lb, 0, sizeof(LOGBRUSH));
        lb.lbStyle = BS_SOLID;
        lb.lbColor = GrayColor;
        hBrush = CreateBrushIndirect(&lb);


    return TRUE;
  }
  break;

  case WM_CTLCOLORDLG:
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
    
   free(szDocKeywords);
   szDocKeywords = NULL;

   szDocComments = NULL;
   szDocApplication = NULL;
   szDocTitle = NULL;
   szDocSubject = NULL;
   szDocAuthor = NULL;
   szDocLastSaved = NULL;
   szDocEditTime = NULL;
   szDocCategory = NULL;
   szDocCompany = NULL;

   return TRUE;
  }
  
  case WM_NOTIFY:
  {
   switch ( ((LPNMHDR) lParam)->code)
   {
    case PSN_KILLACTIVE:
        bMsgResult = FALSE;  // allow this page to receive PSN_APPLY
        break;

    case PSN_SETACTIVE:

        //  fill the controls in the page with information
        SetDlgItemText( hDlg, IDC_COMMENTS, szDocComments);
        SetDlgItemText( hDlg, IDC_APP, szDocApplication);
        SetDlgItemText( hDlg, IDC_TITLE, szDocTitle);
        SetDlgItemText( hDlg, IDC_SUBJECT, szDocSubject);
        SetDlgItemText( hDlg, IDC_AUTHOR, szDocAuthor);
        SetDlgItemText( hDlg, IDC_CATEGORY, szDocCategory);
        SetDlgItemText( hDlg, IDC_COMPANY, szDocCompany);
        SetDlgItemText( hDlg, IDC_LASTSAVE, szDocLastSaved);
        SetDlgItemText( hDlg, IDC_KEYWORDS, szDocKeywords);


        bMsgResult = FALSE;  // accepts activation
        break;

    case PSN_APPLY:
        bMsgResult = PSNRET_NOERROR;
        break;

    case PSN_HELP:                                              
        MessageBox( ((LPNMHDR)lParam)->hwndFrom,
                    "Microsoft Exchange Client\n"
                    "Property Sheet Extension Sample\n"
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
