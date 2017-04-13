
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1994-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

//
//
//  This wizard code is adapted from the mstools\win32\wizard
//  sample, refer to the wizard sample and the online help for 
//  more information about wizards and property pages
//
//
//  Functions:
//      CreateWizard(HWND, HINSTANCE) - starts the wizard
//    	FillInPropertyPage() - Fills in a PROPSHEETPAGE structure
//
//    	Welcome(),License(),YourInfo(),Install_Type(),Install_Destination(),
//      Custom_Options(),Install()
//           - Process the respective Install pages
//
//

#include <windows.h>
#include "instwiz.h"
#include "infinst.h"

// global license flag
BOOL gLicenseAccepted = FALSE;

//
//
//    FUNCTION: CreateWizard(HWND)
//
//    PURPOSE: Create the Install control. 
//
//   COMMENTS:
//    
//      This function creates the install property sheet.
//
int CreateWizard(HWND hwndOwner, HINSTANCE hInst)
{
    PROPSHEETPAGE psp[NUM_PAGES];
    PROPSHEETHEADER psh;

    FillInPropertyPage( &psp[0], IDD_WELCOME, TEXT("Welcome"), Welcome);
    //FillInPropertyPage( &psp[1], IDD_LICENSE, TEXT("Software License Agreement"), License);
    FillInPropertyPage( &psp[1], IDD_INFO, TEXT("Your Information"), YourInfo);
    FillInPropertyPage( &psp[2], IDD_INSTALL_TYPE, TEXT("Installation Type"), Install_Type);
    FillInPropertyPage( &psp[3], IDD_INSTALL_DESTINATION, TEXT("Installation Location"), Install_Destination);
    FillInPropertyPage( &psp[4], IDD_CUSTOM_OPTIONS, TEXT("Custom Installation Options"), Custom_Options);
    FillInPropertyPage( &psp[5], IDD_INSTALL, TEXT("Finish Installation"), Install);
                   
    psh.dwSize = sizeof(PROPSHEETHEADER);
    psh.dwFlags = PSH_PROPSHEETPAGE | PSH_WIZARD | PSH_NOAPPLYNOW;
    psh.hwndParent = hwndOwner;
    psh.pszCaption = (LPSTR) TEXT("Product Install");
    psh.nPages = sizeof(psp) / sizeof(PROPSHEETPAGE);
    psh.nStartPage = 0;
    psh.ppsp = (LPCPROPSHEETPAGE) &psp;

    return (PropertySheet(&psh));
}


//
//
//  FUNCTION: FillInPropertyPage(PROPSHEETPAGE *, int, LPSTR, LPFN) 
//
//  PURPOSE: Fills in the given PROPSHEETPAGE structure 
//
//  COMMENTS:
//
//      This function fills in a PROPSHEETPAGE structure with the
//      information the system needs to create the page.
// 
void FillInPropertyPage( PROPSHEETPAGE* psp, int idDlg, LPSTR pszProc, DLGPROC pfnDlgProc)
{
    psp->dwSize = sizeof(PROPSHEETPAGE);
    psp->dwFlags = 0;
    psp->hInstance = setupInfo.hInst;
    psp->pszTemplate = MAKEINTRESOURCE(idDlg);
    psp->pszIcon = NULL;
    psp->pfnDlgProc = pfnDlgProc;
    psp->pszTitle = pszProc;
    psp->lParam = 0;

}

//////////////////////////////////////////
//
// Wizard procs
//
//////////////////////////////////////////

//
//  FUNCTION: Welcome (HWND, UINT, UINT, LONG)
//
//  PURPOSE:  Processes messages for "Welcome" page 
//
//  MESSAGES:
//    
//    WM_INITDIALOG - intializes the page
//    WM_NOTIFY - processes the notifications sent to the page
//    WM_COMMAND - saves the id of the choice selected
//
BOOL APIENTRY Welcome(
    HWND hDlg,
    UINT message,
    UINT wParam,
    LONG lParam)
{

    switch (message)
    {
    	case WM_INITDIALOG:
    		setupInfo.iWelcome = 0;
           	SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
    		break;

    					
    	case WM_NOTIFY:
        	switch (((NMHDR FAR *) lParam)->code) 
        	{

      			case PSN_KILLACTIVE:
               		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
    				return 1;
    				break;

    			case PSN_RESET:
    				// rest to the original values
    				setupInfo.iWelcome = 0;
               		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
    				break;

     			case PSN_SETACTIVE:
     				PropSheet_SetWizButtons(GetParent(hDlg),  PSWIZB_NEXT);
    				SendMessage(GetDlgItem(hDlg,0x3024 ), BM_SETSTYLE,
                                                   (WPARAM)BS_PUSHBUTTON, MAKELONG(FALSE, 0));
    				break;

                case PSN_WIZNEXT:
                    //
                    // If they haven't accepted the license 
                    // take them there, otherwise proceed with the wizard
                    //
                    if (TRUE != gLicenseAccepted) 
                    {
                        int nUserResponse;
                        
                        // Ask them to accept the license
                        nUserResponse = DialogBox
                            (setupInfo.hInst,
                             MAKEINTRESOURCE(IDD_LICENSE),
                             hDlg,
                             (DLGPROC) License);
                        
                        if (IDC_LICENSE_ACCEPT == nUserResponse) 
                        {
                            // They agreed, now we won't show them the
                            // license again
                            gLicenseAccepted = TRUE;
                        } 
                        else
                        {
                            // the user just cancelled the install
                            // by declining the license agreement
                            // you could put dialog box here
                            // making sure they realize that this will
                            // cancel the installation
                            PostQuitMessage(0);
                            return 1;
                        }
                    }

                    break;

                    default:
                        return FALSE;

        }
    	break;

    	default:
    		return FALSE;
    }
    return TRUE;   
}

//
//  FUNCTION: License (HWND, UINT, UINT, LONG)
//
//  PURPOSE:  Processes messages for "License Agreement" page 
//
//  MESSAGES:
//    
//    WM_INITDIALOG - intializes the page
//    WM_NOTIFY - processes the notifications sent to the page
//    WM_COMMAND - saves the id of the choice selected
//
BOOL APIENTRY License(
    HWND hDlg,
    UINT message,
    UINT wParam,
    LONG lParam)
{

    switch (message)
    {
    	case WM_INITDIALOG:
            {
                //Read in License fiel
                char szLicenseFile[MAX_PATH], ReturnTextBuffer[MAX_PATH]; 

                LPSTR lpszLicenseFile = (char *) &szLicenseFile ;
                LPSTR lpszLicenseText;
                
                HWND hEditCtl;
                HANDLE hFile;

                DWORD NumberOfBytesRead, dwFileSize;

                //
                // Determine where we are installing from
                // and specific the license file there
                //
                GetModuleFileName(NULL, szLicenseFile, _MAX_PATH);
                *(strrchr(szLicenseFile, '\\') + 1) = '\0';        // Strip setup.exe off path
                
                strcat(szLicenseFile,TEXT("license.txt"));

                // Open License file
                hFile = CreateFile(
                                   lpszLicenseFile,       // pointer to name of the file 
                                   GENERIC_READ,          // access (read-write) mode 
                                   FILE_SHARE_READ,       // share mode 
                                   NULL,                  // pointer to security descriptor 
                                   OPEN_EXISTING,         // how to create 
                                   FILE_ATTRIBUTE_NORMAL, // file attributes 
                                   NULL);                 // handle to file with attributes to copy  
    	            
                    if(INVALID_HANDLE_VALUE == hFile)
                    {
                        wsprintf(ReturnTextBuffer, "Error accessing file: %s", szLicenseFile);

                        MessageBox(hDlg, ReturnTextBuffer, 
                                   "Sample Installation Critical Error", 0);

                        //install cannot proceed so go away
                      
                        PostQuitMessage(0);
                        return FALSE;
                    }

                    // Read License file into string
                    // setup memory
                    dwFileSize = GetFileSize (hFile, NULL) ;

                    lpszLicenseText = malloc ((dwFileSize + 1));
                    
                    if(NULL == lpszLicenseText)
                    {
                        wsprintf(ReturnTextBuffer, "Error allocating memory for license text.");
    		            CloseHandle(hFile);

                        MessageBox(hDlg, ReturnTextBuffer, 
                            "Sample Installation Critical Error", 0);

                        //install cannot proceed so go away
                        
                        free(lpszLicenseText);
                        PostQuitMessage(0);
                        return FALSE;
                    }

                    //read file
                    if (!ReadFile(hFile,    	// handle of file to read 
                                  lpszLicenseText,    // address of buffer that receives data  
                                  dwFileSize,    	// number of bytes to read 
                                  &NumberOfBytesRead,    // address of number of bytes read 
                                  NULL))                // address of structure for data 
                    {
                        wsprintf(ReturnTextBuffer, "Error reading license file: %s", szLicenseFile);

                        // clean up
                        free(lpszLicenseText);
                        CloseHandle(hFile);
                        
                        MessageBox(hDlg, "Sample Installation Critical Error", 
                                   ReturnTextBuffer, 0);

                        //install cannot proceed so go away

                        PostMessage(hDlg, WM_DESTROY, 0, 0 );
                        return FALSE;
                    }
      	            
                //Done with file
                CloseHandle(hFile);
                hFile = NULL;
                                    
                // Be sure the file string is null terminated
                lpszLicenseText[dwFileSize] = '\0';
                    
                SetDlgItemText(hDlg, LICENSE_TEXT, lpszLicenseText);
       
                //set focus to license text
                hEditCtl = GetDlgItem(hDlg, LICENSE_TEXT);
                SetFocus(hEditCtl);

                // the control now has the text
                // so free the memory
                free(lpszLicenseText);
                return(FALSE);
            }

            break;

        case WM_COMMAND:
            //
            // LOWORD added for portability
            //
            switch(LOWORD(wParam)) {
            case IDC_LICENSE_ACCEPT:
                EndDialog(hDlg, IDC_LICENSE_ACCEPT);
                return 0;
            case IDC_LICENSE_DECLINE:
                EndDialog(hDlg, IDC_LICENSE_DECLINE);
                return 0;
            }
            break;
        }
    return(FALSE);

    UNREFERENCED_PARAMETER(lParam);
}

//
//  FUNCTION: YourInfo(HWND, UINT, UINT, LONG)
//
//  PURPOSE:  Processes messages for "Your Information" page 
//
//  MESSAGES:
//    
//    WM_INITDIALOG - intializes the page
//    WM_NOTIFY - processes the notifications sent to the page
//
BOOL APIENTRY YourInfo(
    HWND hDlg,
    UINT message,
    UINT wParam,
    LONG lParam)
{

    switch (message)
    {
    	case WM_INITDIALOG:
    		break;

    	case WM_NOTIFY:
        	switch (((NMHDR FAR *) lParam)->code) 
        	{

      			case PSN_KILLACTIVE:
               		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
    				return 1;
    				break;

    			case PSN_RESET:
    				// reset to the blank values
    				lstrcpy(setupInfo.pszUserName, TEXT(""));
    				lstrcpy(setupInfo.pszCompany,TEXT(""));
    				lstrcpy(setupInfo.pszProductIdString, TEXT(""));
    				lstrcpy(setupInfo.pszEmailAddress, TEXT(""));
               		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
    				break;

     			case PSN_SETACTIVE:
        			PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK |PSWIZB_NEXT);
    				SendMessage(GetDlgItem(hDlg,0x3024 ), BM_SETSTYLE, (WPARAM)BS_PUSHBUTTON, MAKELONG(FALSE, 0));
    				//SendMessage(GetParent(hDlg), DM_SETDEFID, (WPARAM)IDC_BUTTON1, 0);
    				SendMessage(GetDlgItem(hDlg, IDE_NAME), 
                                     WM_SETTEXT, 0, (LPARAM)setupInfo.pszUserName);
    				SendMessage(GetDlgItem(hDlg, IDE_COMPANY), 
                                     WM_SETTEXT, 0, (LPARAM)setupInfo.pszCompany);
    				SendMessage(GetDlgItem(hDlg, IDE_PRODUCT_ID), 
                                     WM_SETTEXT, 0, (LPARAM)setupInfo.pszProductIdString);
    				SendMessage(GetDlgItem(hDlg, IDE_EMAIL), 
                                     WM_SETTEXT, 0, (LPARAM)setupInfo.pszEmailAddress);
    				break;

                case PSN_WIZBACK:
                    break;

                case PSN_WIZNEXT:
    				// the Next button was pressed
    	 			SendDlgItemMessage(hDlg, IDE_NAME, WM_GETTEXT, 
                                    (WPARAM)MAX_PATH, (LPARAM) setupInfo.pszUserName);
    				SendDlgItemMessage(hDlg, IDE_COMPANY, WM_GETTEXT, 
                                    (WPARAM)MAX_PATH, (LPARAM)setupInfo.pszCompany);
    				SendDlgItemMessage(hDlg, IDE_PRODUCT_ID, WM_GETTEXT, 
                                    (WPARAM)MAX_PATH, (LPARAM)setupInfo.pszProductIdString);
    				SendDlgItemMessage(hDlg, IDE_EMAIL, WM_GETTEXT, 
                                    (WPARAM)MAX_PATH, (LPARAM)setupInfo.pszEmailAddress);
                    break;

    			default:
    				return FALSE;

        }
    	break;

    	default:
    		return FALSE;
    }
    return TRUE;   
}

//
//  FUNCTION: Install_Type (HWND, UINT, UINT, LONG)
//
//  PURPOSE:  Processes messages for "Install_Type" page 
//
//  MESSAGES:
//    
//    WM_INITDIALOG - intializes the page
//    WM_NOTIFY - processes the notifications sent to the page
//    WM_COMMAND - saves the id of the choice selected
//
BOOL APIENTRY Install_Type(
    HWND hDlg,
    UINT message,
    UINT wParam,
    LONG lParam)
{

    switch (message)
    {
    	case WM_INITDIALOG:
            // pick normal as the default
            setupInfo.iInstall_Type = IDC_INSTALL_TYPE_NORMAL;
            CheckRadioButton( hDlg, IDC_INSTALL_TYPE_NORMAL, IDC_INSTALL_TYPE_UNINSTALL, 
            IDC_INSTALL_TYPE_NORMAL);
            setupInfo.iCustom_Options1 = 1;
            setupInfo.iCustom_Options2 = 1;
            setupInfo.iCustom_Options3 = 0;
            setupInfo.iCustom_Options4 = 1;
            break;

    	case WM_COMMAND:
            if (HIWORD(wParam) == BN_CLICKED)
            {
                setupInfo.iInstall_Type = LOWORD(wParam);
                CheckRadioButton( hDlg, IDC_INSTALL_TYPE_NORMAL, IDC_INSTALL_TYPE_UNINSTALL, LOWORD(wParam));
    		    
                //TODO: you could change the wizard at this
                // point with add and remove page.
                // We will just set the options of custom options
                // for simplicity 
                
                // change the NEXT to FINISH if they want to uninstall
                if (IDC_INSTALL_TYPE_UNINSTALL == LOWORD(wParam))
                {
                    //TODO: could check that the product is indeed
                    // installed and if not, don't let them select
                    // it--you could grey out the selection or 
                    // you could just uninstall even though
                    // it won't do anything
                    PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK | PSWIZB_FINISH);
                }
                else
                {
                    PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK | PSWIZB_NEXT);
                }
                
                // add in options according to what was seleced
                switch LOWORD(wParam)
                {
                case IDC_INSTALL_TYPE_CUSTOM:
                    // first reset options to off
                    setupInfo.iCustom_Options1 = 0;
                    setupInfo.iCustom_Options2 = 0;
                    setupInfo.iCustom_Options3 = 0;
                    setupInfo.iCustom_Options4 = 0;
                    break;
                case IDC_INSTALL_TYPE_NORMAL:
                    setupInfo.iCustom_Options1 = 1;
                    setupInfo.iCustom_Options2 = 1;
                    setupInfo.iCustom_Options3 = 0;
                    setupInfo.iCustom_Options4 = 1;
                    break;
                case IDC_INSTALL_TYPE_MIN:
                    setupInfo.iCustom_Options1 = 1;
                    setupInfo.iCustom_Options2 = 1;
                    setupInfo.iCustom_Options3 = 0;
                    setupInfo.iCustom_Options4 = 0;
                    break;
                default:
                    break; 
                }
            }

    		break;	
    					
    	case WM_NOTIFY:
        	switch (((NMHDR FAR *) lParam)->code) 
        	{

      			case PSN_KILLACTIVE:
               		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
    				return 1;
    				break;

    			case PSN_RESET:
    				// rest to the original values
    				setupInfo.iInstall_Type = 0;
               		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
    				break;

     			case PSN_SETACTIVE:
                               //if they have selected an install type, be sure
                               //it is checked
                               if (setupInfo.iInstall_Type)
    					SendMessage(GetDlgItem(hDlg, setupInfo.iInstall_Type),
                                            BM_SETCHECK, 1, 0L);

                               // Set the correct button NEXT or FINISH
                               if (IDC_INSTALL_TYPE_UNINSTALL == setupInfo.iInstall_Type)
                               {
                                   //TODO: could check that the product is indeed
                                   // installed and if not, don't let them select
                                   // it--you could grey out the selection or 
                                   // you could just uninstall even though
                                   // it won't do anything
                                   PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK | PSWIZB_FINISH);
                               }
                               else
                               {
                                   PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK | PSWIZB_NEXT);
                               }
			break;

                case PSN_WIZBACK:
                    break;

                case PSN_WIZNEXT:
                    break;

                case PSN_WIZFINISH:
                    // They finished the wizard, now do
                    // what they said
                    break;

                default:
                    return FALSE;

        }
    	break;

    	default:
    		return FALSE;
    }
    return TRUE;   
}
//
//  FUNCTION: Install_Destination(HWND, UINT, UINT, LONG)
//
//  PURPOSE:  Processes messages for "Install Destination" page 
//
//  MESSAGES:
//    
//    WM_INITDIALOG - intializes the page
//    WM_NOTIFY - processes the notifications sent to the page
//
BOOL APIENTRY Install_Destination(
    HWND hDlg,
    UINT message,
    UINT wParam,
    LONG lParam)
{

    switch (message)
    {
    	case WM_INITDIALOG:
    		//lstrcpy(setupInfo.pszDestPath, TEXT(""));
    		break;

    	case WM_NOTIFY:
        	switch (((NMHDR FAR *) lParam)->code) 
        	{
                //TODO: Add code here to check that the user entered
                //      path is valid and show the user disk space available
                //      You can also have more on disk space on the 
                //      customer options page.  
                //      So this sample does NOT verify the path and disk space
                //      requirements.  Note the setupapi functions will gracefully
                //      let the user know there is no disk space avail--at which
                //      time the user can go clean up some space or cancel the install

      			case PSN_KILLACTIVE:
               		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
    				return 1;
    				break;

    			case PSN_RESET:
    				// reset to the original values
    				lstrcpy(setupInfo.pszDestPath, TEXT(""));
               		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
    				break;

     			case PSN_SETACTIVE:
        			PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK |PSWIZB_NEXT);
    				SendMessage(GetDlgItem(hDlg,0x3024 ), BM_SETSTYLE, (WPARAM)BS_PUSHBUTTON, MAKELONG(FALSE, 0));
    				SendMessage(GetDlgItem(hDlg, IDE_PATH), WM_SETTEXT, 0, (LPARAM)setupInfo.pszDestPath);
    				break;

                case PSN_WIZBACK:
                    break;

                case PSN_WIZNEXT:
    				// the Next button was pressed
    	 			SendDlgItemMessage(hDlg, IDE_PATH, WM_GETTEXT, (WPARAM)MAX_PATH, (LPARAM) setupInfo.pszDestPath);
         			break;

    			default:
    				return FALSE;

        }
    	break;

    	default:
    		return FALSE;
    }
    return TRUE;   
}
//
//  FUNCTION: Custom_Options (HWND, UINT, UINT, LONG)
//
//  PURPOSE:  Processes messages for "Custom options" page 
//
//  MESSAGES:
//    
//    WM_INITDIALOG - intializes the page
//    WM_NOTIFY - processes the notifications sent to the page
//    WM_COMMAND - saves the id of the choice selected
//
BOOL APIENTRY Custom_Options(
    HWND hDlg,
    UINT message,
    UINT wParam,
    LONG lParam)
{

    switch (message)
    {
    	case WM_INITDIALOG:
            // these are initialized via the install type page
            // so we don't need to initialize anything
    		break;

    	case WM_COMMAND:
    		if (HIWORD(wParam) == BN_CLICKED)
    		{
                    if (LOWORD(wParam) == IDC_CUSTOM_OPTION1) {
                        if (setupInfo.iCustom_Options1) {
                             setupInfo.iCustom_Options1 = 0;
                         } else {
                             setupInfo.iCustom_Options1 = 1;
                         }
                     }

                     if (LOWORD(wParam) == IDC_CUSTOM_OPTION2) {
                         if (setupInfo.iCustom_Options2) {
                              setupInfo.iCustom_Options2 = 0;
                          } else {
                              setupInfo.iCustom_Options2 = 1;
                          }
                      }

    	  	     if (LOWORD(wParam) == IDC_CUSTOM_OPTION3) {
                         if (setupInfo.iCustom_Options3) {
                              setupInfo.iCustom_Options3 = 0;
                         } else {
                              setupInfo.iCustom_Options3 = 1;
                         }
                      }

    		      if (LOWORD(wParam) == IDC_CUSTOM_OPTION4) {
                          if (setupInfo.iCustom_Options4) {
                               setupInfo.iCustom_Options4 = 0;
                          } else {
                               setupInfo.iCustom_Options4 = 1;
                      }
                   }
    		}
    		break;	
    					
    	case WM_NOTIFY:
        	switch (((NMHDR FAR *) lParam)->code) 
        	{

      			case PSN_KILLACTIVE:
               		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
    				return 1;
    				break;

    			case PSN_RESET:
    				// rest to the original values
    				setupInfo.iCustom_Options1 = 0;
    				setupInfo.iCustom_Options2 = 0;
    				setupInfo.iCustom_Options3 = 0;
    				setupInfo.iCustom_Options4 = 0;
               		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
    				break;

     			case PSN_SETACTIVE:
    				CheckDlgButton (hDlg, IDC_CUSTOM_OPTION1, 
                        setupInfo.iCustom_Options1);
    				CheckDlgButton (hDlg, IDC_CUSTOM_OPTION2, 
                        setupInfo.iCustom_Options2);
    				CheckDlgButton (hDlg, IDC_CUSTOM_OPTION3, 
                        setupInfo.iCustom_Options3);
    				CheckDlgButton (hDlg, IDC_CUSTOM_OPTION4,
                        setupInfo.iCustom_Options4);
     				PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK | PSWIZB_NEXT);
    				break;

                case PSN_WIZBACK:
                    break;

                case PSN_WIZNEXT:
                    break;

                default:
                    return FALSE;

        }
    	break;

    	default:
    		return FALSE;
    }
    return TRUE;   
}
//
//  FUNCTION: Install(HWND, UINT, UINT, LONG)
//
//  PURPOSE:  Processes messages for "Installation" page 
//
//  MESSAGES:
//    
//    WM_INITDIALOG - intializes the page
//    WM_NOTIFY - processes the notifications sent to the page
//    WM_COMMAND - saves the id of the choice selected
//
//
BOOL APIENTRY Install(
    HWND hDlg,
    UINT message,
    UINT wParam,
    LONG lParam)
{

    switch (message)
    {
    	case WM_INITDIALOG:
    		setupInfo.iInstall = 0;
    		break;

    	case WM_NOTIFY:
        	switch (((NMHDR FAR *) lParam)->code) 
        	{
      			case PSN_KILLACTIVE:
               		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
    				return 1;
    				break;

    			case PSN_RESET:
    				// rest to the original values
    				setupInfo.iInstall = 0;
               		SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
    				break;

     			case PSN_SETACTIVE:
    				PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_BACK | PSWIZB_FINISH);
    				break;

                case PSN_WIZBACK:
                    break;


                case PSN_WIZFINISH:
                    // They finished the wizard, now do
                    // what they said
                    break;

                default:
                    return FALSE;
        }
    	break;

    	default:
    		return FALSE;
    }
    return TRUE;   
}

