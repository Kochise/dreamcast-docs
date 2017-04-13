/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/
/******************************************************************************\
*                                                              
*   Implementation file for SetDisp                           
*                                                              
*   SetDisp creates a tray Notification Icon                  
*   that you can use to dynamically change your srceen         
*   resolution. The core APIs used are:                        
*                                                              
*   Shell_NotifyIcon -- to create and maintain the tray icon   
*   TrackPopupMenu   -- to implement the icon resolution       
*                       context menu                           
*   ChangeDisplaySettings -- to test and set the display       
*                       settings dynamically and to update     
*                       the registry with these setttings      
*   EnumDisplaySettings -- to get the display settings that are
*                       supported by the video driver          
*
*   KNOWN ISSUES:  On Windows 95 one cannot use the EnunDisplaySettings
*   to get the current settings.  This causes the check mark to not
*   be displayed and the current setting to not be bolded.  This 
*   information could be obtained from the registry. Also on Windows 95
*   color depth changes require a reboot.  None of the possible returns
*   from ChangeDisplaySettings are currently handled execpt for 
*   success and a message is displayed indicated the sample does not
*   support a reboot. If your driver has many resolutions, the menu
*   may not fit on some resolutions.  This could be resolved with 
*   the use of sub menus for different settings such as color depth
*   or frequencies.
*                                                                 
\******************************************************************************/

#if DBG

#define TRC(_x) OutputDebugString(TEXT(_x))

#else

#define TRC(_x)

#endif

#include "setdisp.h"
#include <windowsx.h>
#include <winuser.h>
#include "resource.h"


/**************************************************************\
*                                                              * 
*  Tray Icon Structure taken from Win32\TrayNot sample         *
*                                                              * 
\**************************************************************/

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

//
// Data for one tray icon
//

{
	{
		0, IDC_NOTIFY1, IDC_DELAY1, IDC_STATE11, IDC_TIP11, IDC_STATE12, IDC_TIP12,
	},
} ;


 /****************************************************************************
 *                                                                          
 *  FUNCTION   : WinMain (HINSTANCE hInstance,  HINSTANCE hPrevInstance, 
 *                        LPSTR lpCmdLine, int nCmdShow )
 *                                                                          
 *  PURPOSE    : Creates a dialog box which implements the tray icon
 *               and which handles the resolution changes
 *                                                                          
 \****************************************************************************/

int WINAPI WinMain (

  HINSTANCE hInstance, 
  HINSTANCE hPrevInstance, 
  LPSTR lpCmdLine, 
  int nCmdShow )
{

    g_hinst = hInstance;
	
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_SETDISP), NULL, SetDispDlgProc);
	
    if (gpDevModes)
    {
        free(gpDevModes);
    }

    return(FALSE);

}

 /****************************************************************************
 *                                                                          
 *  FUNCTION   : SetDispDlgProc (HWND hDlg, UINT uMsg,
 *                                WPARAM wParam, LPARAM lParam)
 *                                                                          
 *  PURPOSE    : Dialog box callback which manages the tray icon
 *               and which handles the resolution changes
 *                                                                          
 \****************************************************************************/

BOOL CALLBACK SetDispDlgProc (
  
   HWND hDlg, 
   UINT uMsg, 
   WPARAM wParam, 
   LPARAM lParam)
{

    switch (uMsg)
    {
	
    case WM_INITDIALOG:
    {
	BOOL bRet;

	//
	//Get DEVMODES
	//

	bRet = GetDevModes (hDlg);

        if (bRet == FALSE)
        {
            //
            // Failed to get DEVMODES so end the dialog
            //
        
	    EndDialog(hDlg, TRUE);

	    break;
        }
        
	//
	// Initialize Menu with Resolutions
	//

	SetResolutionMenu (hDlg);
        
	//
	// Add Tray Notify Icon
	//

	NotifyAdd(hDlg, 0);
        
	//
	// Update Tip to current settings
	//
	{
        
	    char szTip[50];

	    //
	    // Set the menu text
	    //

	    if (IsNT())
            {
                wsprintf(szTip,"%d x %d, %d bit color at %d hz",
                         gpCurrentMode->dmPelsWidth,
                         gpCurrentMode->dmPelsHeight,
                         gpCurrentMode->dmBitsPerPel,
                         gpCurrentMode->dmDisplayFrequency);
            }
            else
            {
                szTip[0] = '\0';
            }
	        
	    //
	    // For the current mode, set the tool tip
            //

	    TrayMessage(hDlg, NIM_MODIFY, g_sDlgItems[0].uNotify,
                        LoadImage(g_hinst, MAKEINTRESOURCE(IDI_SETDISP),
                        IMAGE_ICON, 16, 16, 0), szTip);
	}
 
	SetForegroundWindow (hDlg);

	break;
    
    }	// WM_INITDIALOG:

    case WM_DESTROY:	NotifyDelete(hDlg, 0);
			break;

    case WM_COMMAND:
    {
	switch (GET_WM_COMMAND_ID(wParam, lParam))
	{
	    case IDCANCEL:   EndDialog(hDlg, TRUE);
			     break;

	    case IDABORT:    ShowWindow(hDlg, SW_HIDE);
			     break;
        
	    case IDM_ABOUT:
		  DialogBox(g_hinst, MAKEINTRESOURCE(IDD_ABOUT),
			    hDlg, (DLGPROC)About);
		  break;

	    default:
        
	    //
	    // handle MYWM_NOTIFYICON + 10 + i for diffent devmodes
	    //

            if ( MYWM_NOTIFYICON + 10  <= GET_WM_COMMAND_ID(wParam, lParam) &&
		 MYWM_NOTIFYICON + 11 + gnModes >= GET_WM_COMMAND_ID(wParam, lParam))
	    {
		UINT nNewMode;
                
                nNewMode = GET_WM_COMMAND_ID(wParam, lParam) - (MYWM_NOTIFYICON + 10);
                
		//
		// Only update if the chose a new setting
		//

                if (gnCurrentMode != nNewMode)
                {            
		   ChangeResolution (nNewMode, hDlg);
		}

		break;
            
            }


	} //WM_COMMAN switch

    } //WM_COMMAND

    case MYWM_NOTIFYICON:
    {
	switch (lParam)
	{

	    case WM_LBUTTONDOWN:
        
		 //
		 // Handle popup here when user right mouse clicks tray icon
		 //
		 {
            
		     //
		     // Handle popup here
		     //

		     POINT point;
 
		     GetCursorPos (&point);

		     HandlePopupMenu (hDlg, point);
            
		     break;
    
		 }
	    
		
	    case WM_RBUTTONDOWN:
		 switch (wParam)
		 {
            
		    //
		    // Diplay the dialog box on Left mouse click
		    // this is how the user gets the dialog back if it is hidden
		    //

		    case IDC_NOTIFY1:  ShowWindow (hDlg, SW_RESTORE);
				       SetForegroundWindow (hDlg);
				       break;

		    default:
			 break;
			
		  }
			
       
	    default:
		 break;

	}  // lParam switch

    }// MYWM_NOTIFYICON

    default:
	 return(FALSE);
    
    }  // switch (uMsg)

    return(TRUE);

}

/****************************************************************************
*                                                                          
*  FUNCTION   : GetDevModes (hwnd)
*                                                                          
*  PURPOSE    : Get the display modes supported by the current driver
*
\****************************************************************************/
BOOL GetDevModes (
                  
  HWND hwnd)
{
	
    BOOL bRet = TRUE;
    BOOL bAddDM;
    UINT iModeNum = 0;
    DEVMODE CurrentDM, WorkingDM;
    INT i;
    UINT nlist;
    LPDEVMODE pDM;

    //
    // setting param 1 to NULL (lpszDeviceName) uses current device on NT
    // and NULL is required on Win95
    //

    if (IsNT())
    {
	//
	// NT specific; returns current devmode when param 2 set to ENUM_CURRENT_SETTINGS,
	//

	EnumDisplaySettings (NULL, ENUM_CURRENT_SETTINGS, &CurrentDM);
    }

    //
    // Determine how much memory we need
    //

    for (iModeNum = 0, gnModes = -1;
         bRet && (gnModes <= MAX_MODES); 
         iModeNum++)
    {
        bRet = EnumDisplaySettings 
                     (NULL,            // use default device
                     iModeNum,         // DEVMODEs start at 0
                     &WorkingDM);      // if successful the system
                                       // fills in the DEVMODE
                                       // structure

        //
        // For some reason my driver supports 1 hz display frequency
        // So filter out settings we do not want to display
        //
        
        if ( bRet & 
	     WorkingDM.dmPelsWidth	  >= MIN_WIDTH &&
            (WorkingDM.dmDisplayFrequency >= MIN_FREQUENCY  ||
	     WorkingDM.dmDisplayFrequency == 0) )

	    //
	    // Accept 0 frequency since windows 95 does return frequency
	    //
        {
            //
            // Increment to use next DEVMODE
            //

            gnModes++;
	}

    } // for loop
    
    if(-1 == gnModes)
    {
        MessageBox(hwnd, "No Display modes available.", "SetDisp Error", IDOK);
        return (FALSE);
    }

    //
    // We need gnModes worth of DEVMODE Structures
    //
    
    gpDevModes = (PDEVMODE) malloc ((size_t) (gnModes + 1) * sizeof(DEVMODE));

    if (gpDevModes == NULL)
    {
        return (FALSE);
    }

    //
    // Loop through EnumDisplaySetting to get each supported DEVMODE
    // When returns false we have them all
    //
    
    for (iModeNum = 0, i = 0, bRet = TRUE; 
         bRet && i <= gnModes; 
         iModeNum++)
    {
        bRet = EnumDisplaySettings 
                     (NULL,            // use default device
                     iModeNum,         // DEVMODEs start at 0
                     &WorkingDM);      // if successful the system
                                       // fills in the DEVMODE
                                       // structure

        //
        // Miniport drivers support 1 hz display frequency representing the default
        // and older drivers support 0 hz display frequency representing the default
        // So filter out settings we do not want to display
        //
        
        if ( bRet && 
             WorkingDM.dmPelsWidth        >= MIN_WIDTH      && 
            (WorkingDM.dmDisplayFrequency >= MIN_FREQUENCY  ||
             WorkingDM.dmDisplayFrequency == 0              ||
             WorkingDM.dmDisplayFrequency == 1))
             // Accept 0 or 1 frequency which represent default frequencies
        {
            bAddDM = TRUE;

            //
            // We will take this one unless another default has already been 
            // added at these settings
            //

            if (WorkingDM.dmDisplayFrequency == 0 || 
                WorkingDM.dmDisplayFrequency == 1)
            {
                for (nlist = 0; nlist <= gnCurrentMode; nlist++)
                {
                      pDM = gpDevModes + nlist;

                      if (pDM->dmPelsWidth  == WorkingDM.dmPelsWidth   &&
                          pDM->dmPelsHeight == WorkingDM.dmPelsHeight  &&
                          pDM->dmBitsPerPel == WorkingDM.dmBitsPerPel)
                      {
                          //
                          // If everything else is the same do not add another default
                          //

                          bAddDM = FALSE;
                      }
                } // end for nlist

            } // end if default

            if (bAddDM)
            {
                //
                // Increment to use next DEVMODE
                //

                if (i == 0)
                {
                    gpCurrentMode = gpDevModes;
                }
                else
                {
                    gpCurrentMode += 1;
                }

                EnumDisplaySettings (NULL, iModeNum, gpCurrentMode);
                i++;

            } // end if bAddDM

        } // end bRet and hz if

    } // end for EnumDisplaySettings


    //
    // Sort the array for display; default sort
    // A different compare routine could sort by different attributes
    //
    
    qsort((void *) gpDevModes, 
          (size_t) gnModes + 1,  // add one since gnModes is zero based 
          (size_t) sizeof(DEVMODE), 
          ( int (_cdecl*)(const void*,const void*) )CompareDevModes);
     
    //
    // Set gCurrentMode to CurrentDM
    //
    if (IsNT())
    {
        for (i =0; i <= gnModes; i++)
        {
            
            if (i == 0)
            {
                gpCurrentMode = gpDevModes;
            }
            else
            {
                gpCurrentMode += 1;
            }

            if (0 == CompareDevModes (&CurrentDM, gpCurrentMode))
            {
                gnCurrentMode = i;
                break;
            }
        }
    }
    else
    {
        //
        // Default to the first one
        // since we error out if there is not even this one
        //

        gnCurrentMode = 0;
    }

    //
    // TODO: What if some of the DEVMODES are not supported on 
    //       the physical Device?
    //
    
    return (TRUE);

}  //GetDevModes scope


/****************************************************************************
*                                                
*  FUNCTION   : ChangeResolution (UINT nNewMode, HWND hwnd)
*                                                
*  PURPOSE    : Change the resolution to the nNewMode index DEVMODE               
*                                                                          
\****************************************************************************/
BOOL ChangeResolution (
    UINT nNewMode, 
    HWND hwnd )
{
  
    LONG lResult;       //Result of ChangeDisplaySettings
    INT nUserResponse;	//Return from VerifyRes Dlg
    UINT nOldMode;

   /*
    ChangeDisplaySettings can set
	dmBitsPerPel	    Bits per pixel
	dmPelsWidth	    Pixel width
	dmPelsHeight	    Pixel height
	dmDisplayFlags	    Mode flags
	dmDisplayFrequency  Mode frequency
        
        but one of thes must be set in the DEVMODE dmFields
        DM_BITSPERPEL	    Use the dmBitsPerPel value.
        DM_PELSWIDTH	    Use the dmPelsWidth value.
        DM_PELSHEIGHT	    Use the dmPelsHeight value.
        DM_DISPLAYFLAGS	    Use the dmDisplayFlags value.
	DM_DISPLAYFREQENCY  Use the dmDisplayFrequency value.

    */

    //
    // First select a DevMode to use
    // to start, just cycling through them
    //

    nOldMode = gnCurrentMode;
    gnCurrentMode = nNewMode;
    
    //
    // Increment ptr to the new mode
    //

    gpCurrentMode = gpDevModes;
    gpCurrentMode += nNewMode;
    
    //
    // Verify that the DEVMODE select will change something
    //

    if (!(DM_BITSPERPEL	     & gpCurrentMode->dmFields ||
          DM_PELSWIDTH	     & gpCurrentMode->dmFields ||
          DM_PELSHEIGHT	     & gpCurrentMode->dmFields ||
          DM_DISPLAYFLAGS	 & gpCurrentMode->dmFields ||
          DM_DISPLAYFREQUENCY & gpCurrentMode->dmFields ) )
    
    {
    
	//
        // Note our DEVMODE returned from EnumDisplaySettings
	// So we should never enter here
	//

        gnCurrentMode = nOldMode;
        
        gpCurrentMode = gpDevModes;
        gpCurrentMode += gnCurrentMode;

        return (FALSE);
    }


    /************************************************************\
    *                                                            *
    *   Possible Flags for param 2 of ChangeDisplay Settings     *
    *    0	        The graphics mode for the current            *
    *                screen will be changed dynamically.         *
    *    CDS_UPDATEREGISTRY	The graphics mode for the            *
    *                current screen will be changed dynamically  *
    *                and the graphics mode will be updated in    *
    *                the registry. The mode information is       *
    *                stored in the USER profile.                 *
    *    CDS_TEST	The system tests if the requested            *
    *                graphics mode could be set.                 *
    *                                                            *
    \************************************************************/
    
    //
    // First have the system test if we can set it
    //

    //
    // Param 1 is the new DEVMODE
    // Param 2 is Test Flag, 
    // which asks the operating system if this is a valid setting 
    // to change to -- wedon't want to make the system unusable
    //

    lResult = ChangeDisplaySettings
                ( gpCurrentMode, 
                  CDS_TEST );               
                                      
    
    if (lResult == DISP_CHANGE_RESTART)
    {
        MessageBox(hwnd, "This mode requires a reboot which\n"  \
                         "is not supported in this sample.", 
			 "SetDisp Message", IDOK);
        
        gnCurrentMode = nOldMode;
        gpCurrentMode = gpDevModes;
        gpCurrentMode += gnCurrentMode;

        return FALSE;
    }

    if (DISP_CHANGE_SUCCESSFUL ==lResult)
    {
    
	 //
	 // Param 2 is 0 to change dynamically
	 // hence the app name SetDisp!
	 //

         lResult = ChangeDisplaySettings
                     ( gpCurrentMode,
                       0 );  
    }
    


    switch (lResult)
    {

    case DISP_CHANGE_SUCCESSFUL:  //The settings change was successful.
	 TRC("DISP_CHANGE_SUCCESSFUL\n");
	 break;

    case DISP_CHANGE_RESTART:	  //The computer must be restarted in order 
                                  //  for the graphics mode to work.
         TRC("DISP_CHANGE_RESTART\n");
         break;

    case DISP_CHANGE_BADFLAGS:	  //An invalid set of flags was passed in.
         TRC("DISP_CHANGE_BADFLAGS\n");
         break;

    case DISP_CHANGE_FAILED:	  //The display driver failed the specified 
                                  //  graphics mode.
         TRC("DISP_CHANGE_FAILED\n");
         break;

    case DISP_CHANGE_BADMODE:	  //The graphics mode is not supported.
         TRC("DISP_CHANGE_BADMODE\n");
         break;

    case DISP_CHANGE_NOTUPDATED:  //Windows NT only: Unable to write settings 
                                  //  to the registry.                        
         TRC("DISP_CHANGE_NOTUPDATED\n");
         break;
    default:
	 TRC("Undocumented return value!!!!\n");
	 break;
    }


    //
    // Set a timer to only give the user so much
    // time to dedice incase the screen is garbled
    //

    SetTimer(hwnd,	VERIFY_RESCHANGE, VERIFY_TIMEOUT, VerifyTimerProc);

    //
    // Have the user verify the new resolution and depth
    //

    nUserResponse = DialogBox(g_hinst,// handle this application 
                              MAKEINTRESOURCE(IDD_VERIFYRES),// identifies dialog box template
                              NULL,               // handle to owner window
                              VerifyDlgProc);  // the dialog box procedure


    //
    // The verification is over, kill the timer
    //

    KillTimer(hwnd,	VERIFY_RESCHANGE);
    
    if (IDYES == nUserResponse)
    {
    
	//
	// Keep resolution and update registry
	//

        char szTip[50];

	//
	// TODO: give them three choices:
        //       Dynamic only, Registry too, or Abort
	//

        lResult = ChangeDisplaySettings
                    ( gpCurrentMode,
                      CDS_UPDATEREGISTRY );  //  Flag to update registry
        
        switch (lResult)
        
        {
        
        case DISP_CHANGE_SUCCESSFUL: 
            
	    //
	    // The settings change was successful.
	    //

            TRC("DISP_CHANGE_SUCCESSFUL - reg\n");
            
            wsprintf(szTip,"%d x %d, %d bit color at %d hz", 
                 gpCurrentMode->dmPelsWidth,
                 gpCurrentMode->dmPelsHeight,
                 gpCurrentMode->dmBitsPerPel,
                 gpCurrentMode->dmDisplayFrequency);

             {

		 //
		 // Update the Menu informtion, just a check mark for now
		 //

                 HMENU hMenu, hMenu2;
                 
                 hMenu = GetMenu(hwnd);
                 
                 hMenu2 = GetSubMenu (hMenu, 0);

		 //
		 // Uncheck the old
		 //

                 CheckMenuItem (hMenu2, nOldMode, MF_BYPOSITION | MF_UNCHECKED);
                 
		 //
		 // Check the new
		 //

		 CheckMenuItem (hMenu2, gnCurrentMode, MF_BYPOSITION | MF_CHECKED);
             
             }

	     //
	     // Update the Notify_Icon quick tip
	     //

             TrayMessage(hwnd, NIM_MODIFY, g_sDlgItems[0].uNotify,
                    LoadImage(g_hinst, MAKEINTRESOURCE(IDI_SETDISP),
                    IMAGE_ICON, 16, 16, 0), szTip);

             break;

        case DISP_CHANGE_RESTART:	  //The computer must be restarted in order 
                                      //  for the graphics mode to work.
             TRC("DISP_CHANGE_RESTART - reg\n");
             break;

        case DISP_CHANGE_BADFLAGS:	  //An invalid set of flags was passed in.
             TRC("DISP_CHANGE_BADFLAGS - reg\n");
             break;

        case DISP_CHANGE_FAILED:	  //The display driver failed the specified 
                                      //  graphics mode.
             TRC("DISP_CHANGE_FAILED - reg\n");
             break;

        case DISP_CHANGE_BADMODE:	  //The graphics mode is not supported.
             TRC("DISP_CHANGE_BADMODE - reg\n");
             break;

        case DISP_CHANGE_NOTUPDATED:  //Windows NT only: Unable to write settings 
                                      //  to the registry.                        
             TRC("DISP_CHANGE_NOTUPDATED - reg\n");
             break;
        default:
              TRC("Undocumented return value!!!! - reg\n");
              break;
        }
    
    }
    
    else
    
    {
	//
	// The user chose to not keep the setting or	we timed out
        // so they may not have seen the dialog box to choose
        //
        // Change resolution back by calling
        // ChangeDisplaySettings 
        // with a NULL DEVMODE which returns us to the current
        // registry settings
	//

        lResult = ChangeDisplaySettings
                    ( NULL, 
                      0 );  // 0 to change dynamically
        
        gnCurrentMode = nOldMode;
        
        gpCurrentMode = gpDevModes;
        gpCurrentMode += gnCurrentMode;
    
    }

    return (TRUE);

}


 /****************************************************************************
 *                                                                          
 *  FUNCTION   : SetResolutionMenu (hwnd)                              
 *                                                                          
 *  PURPOSE    : Create a context menu with all of the resolutions
 *               that are in the devmodes we obtained from the drive
 *                                                                          
 \****************************************************************************/
BOOL SetResolutionMenu ( 
    HWND hwnd)
{
  
    HMENU hMenu, hWndMenu; //hMenuTrackPopup;
    INT i;
    BOOL bRet;
    PDEVMODE pDevMode;
    
    //
    // Create new Resolutions menu from the DevModes collected
    //

    hMenu = CreateMenu(); 
    
    if (!hMenu)
    {
       return (FALSE);
    }

    //
    // For each devmode add an menu item
    // TODO: make the description on BitPerPel better
    //

    for(i=0; i<= gnModes; i++)
    {
    
        char szRes[50];

	    
        if (i == 0)
        {
            pDevMode = gpDevModes;
        }
        else
        {
            pDevMode += 1;
	}

        //
	// Set the menu text
	//

        if (pDevMode->dmDisplayFrequency == 0 ||
            pDevMode->dmDisplayFrequency == 1)
	{
	    wsprintf(szRes,"%d x %d, %d bit color, default frequency",
                 pDevMode->dmPelsWidth,
                 pDevMode->dmPelsHeight,
                 pDevMode->dmBitsPerPel);
	}
	else
	{
	    wsprintf(szRes,"%d x %d, %d bit color at %d hz",
                 pDevMode->dmPelsWidth,
                 pDevMode->dmPelsHeight,
                 pDevMode->dmBitsPerPel,
                 pDevMode->dmDisplayFrequency);
	}
        
        bRet = AppendMenu (hMenu, MF_STRING, MYWM_NOTIFYICON + 10 + i, szRes);
        
        SetMenuItemBitmaps(
		  hMenu,	 // handle of menu
		  gnCurrentMode, // menu item to receive new bitmaps
                  MF_BYPOSITION, // menu item flags
                  NULL,	         // handle of unchecked bitmap
		  NULL);	 // handle of checked bitmap
                                 // if last two are NULL the default 
                                 // bitmap is used

    
    } // for loop to set menu
    
    if (!bRet)
    {
   
        //
        // if the last one worked they all likely worked
        // otherwise let's clean up
        //

        DestroyMenu(hMenu);
        
        return(FALSE);
    
    }
    else
    {

        if (IsNT())
        {
            //
            // Check the Current one
            //

            CheckMenuItem (hMenu, gnCurrentMode, MF_BYPOSITION | MF_CHECKED);
    
            //
            // Set it as the default so it is easy to go back to
            //

	    SetMenuDefaultItem(hMenu, gnCurrentMode, TRUE ); //TRUE if for by Position

        }

        hWndMenu = GetMenu (hwnd);
        
        InsertMenu (hWndMenu, 0, MF_POPUP|MF_BYPOSITION, (DWORD)hMenu, "&Resolutions");
        
        return(TRUE);
    
    }
    
}


 /****************************************************************************
 *                                                                          
 *  FUNCTION   : TrayMessage (HWND hDlg, DWORD dwMessage, UINT uID, 
 *                            HICON hIcon, PSTR pszTip )
 *                                                                          
 *  PURPOSE    : Creates, Modifies or deletes the tray icon 
 *               If pszTip is not null, it uses that for the tip
 *               otherwise it sets a default tip
 *                                                                          
 \****************************************************************************/

BOOL TrayMessage (
                  
  HWND hDlg, 
  DWORD dwMessage, 
  UINT uID, 
  HICON hIcon, 
  PSTR pszTip )

{
    BOOL res;
    NOTIFYICONDATA tnd;

    //
    // Get the Tray Icon
    //

    hIcon = (HICON)LoadImage(g_hinst, MAKEINTRESOURCE(IDI_SETDISP), IMAGE_ICON,
			     16, 16, 0);
    
    tnd.cbSize		= sizeof(NOTIFYICONDATA);
    tnd.hWnd		= hDlg;
    tnd.uID		= uID;
    tnd.uFlags		= NIF_MESSAGE|NIF_ICON|NIF_TIP;
    tnd.uCallbackMessage= MYWM_NOTIFYICON;
    tnd.hIcon		= hIcon;
	
    //
    // If there is a specific tip, set it
    // otherwise use SetDisp as the default
    //

    if (pszTip)
    {
	lstrcpyn(tnd.szTip, pszTip, sizeof(tnd.szTip));
    }
    else
    {
	lstrcpyn(tnd.szTip, "SetDisp", sizeof("SetDisp"));;
    }

	
    //
    //	Use the Shell_NotifyIcon API to setup the tray icon
    //

    res = Shell_NotifyIcon(dwMessage, &tnd);

    if (hIcon)
    {
	 DestroyIcon(hIcon);
    }


    return res;

}


 /****************************************************************************
 *                                                                          
 *  FUNCTION   : NotifyDelete (HWND hDlg, UINT uIndex)
 *                                                                          
 *  PURPOSE    : Deletes a tray icon based on the uIndex .
 *               In this SetDisp sample, it is only used for a single icon
 *                                                                          
 \****************************************************************************/

void NotifyDelete (
                   
  HWND hDlg, 
  UINT uIndex )

{

    TrayMessage(hDlg, NIM_DELETE, g_sDlgItems[uIndex].uNotify, NULL, NULL);

}


 /****************************************************************************
 *                                                                          
 *  FUNCTION   : NotifyAdd (HWND hDlg, UINT uIndex)
 *                                                                          
 *  PURPOSE    : Creates tray icons based on the uIndex .
 *               In this SetDisp sample, it is only used for a single icon
 *                                                                          
 \****************************************************************************/

void NotifyAdd (
               
  HWND hDlg, 
  UINT uIndex )

{

    TrayMessage(hDlg, NIM_ADD, g_sDlgItems[uIndex].uNotify, NULL, NULL);

}


 /****************************************************************************
 *                                                                          
 *  FUNCTION   : VerifyTimerProc (HWND hwnd, UINT uMsg, 
 *                                UINT idEvent, DWORD dwTime )
 *                                                                          
 *  PURPOSE    : Simply sends an IDNO to the Verify Dialog
 *               This is setup to give the user a limited amount of time
 *               to approve
 *                                                                          
 \****************************************************************************/

VOID CALLBACK VerifyTimerProc (
                               
  HWND hwnd, 
  UINT uMsg, 
  UINT idEvent,
  DWORD dwTime )
{

    SendMessage(ghVerifyDlg, WM_COMMAND, IDNO, 0);

}

 /****************************************************************************
 *                                                                          
 *  FUNCTION   : VerifyTimerProc (HWND hDlg, UINT uMsg,
 *                                WPARAM wParam, LPARAM lParam)
 *
 *                                                                          
 *  PURPOSE    : Ask the user if they want to keep the new resolution
 *                                                                          
 \****************************************************************************/

BOOL CALLBACK VerifyDlgProc(
    HWND hDlg,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch(uMsg)
    {
	case WM_INITDIALOG:	ghVerifyDlg = hDlg;
				return(TRUE);
    
	case WM_COMMAND:
    
	     //
	     // LOWORD added for portability
	     //
        
	     switch (LOWORD(wParam))
	     {
        
		 case IDNO:
		 case IDCANCEL:	ghVerifyDlg = NULL;
				EndDialog(hDlg, IDNO);
				return 0;
        

		 case IDYES:	ghVerifyDlg = NULL;
				EndDialog(hDlg, IDYES);
				return 0;
	      }
       
	default:
	     break;
   
    }
   
    return(FALSE);

    UNREFERENCED_PARAMETER(lParam);

}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : HandlePopupMenu (hwnd, point)                              *
 *                                                                          *
 *  PURPOSE    : Handles the display of the "floating" popup that appears   *
 *               on a mouse click in the app's client area.                 *
 *                                                                          *
 ****************************************************************************/

VOID APIENTRY HandlePopupMenu (
    HWND  hwnd,
    POINT point)
{
    
    HMENU hMenu;
    HMENU hMenuTrackPopup;

    //
    // Get the menu for the windows
    //

    hMenu = GetMenu(hwnd);

    if (!hMenu)
    {
	return;
    }

    //
    // Get the first menu in it which we will use for the call to
    // TrackPopup(). This could also have been created on the fly using
    // CreatePopupMenu and then we could have used InsertMenu() or
    // AppendMenu.
    //
    
    hMenuTrackPopup = GetSubMenu (hMenu, 0);

    //
    // Draw and track the "floating" popup
    //

    if (point.x < (long) (gpCurrentMode->dmPelsWidth - 50))
        point.x = (long) (gpCurrentMode->dmPelsWidth - 50);

    if (point.y < (long) (gpCurrentMode->dmPelsHeight - 50))
        point.y = (long) (gpCurrentMode->dmPelsHeight - 50);
    
    
    //
    // This is required when using a notify icon -- see KB article
    // PRB: Menus for Notification Icons Don't Work Correctly
    //

    SetForegroundWindow (hwnd);
    
    TrackPopupMenu (hMenuTrackPopup, TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
                    point.x, point.y, 0, hwnd, NULL);

    //
    // This is required when using a notify icon -- see KB article
    // PRB: Menus for Notification Icons Don't Work Correctly
    //

    PostMessage (hwnd, WM_USER, 0, 0);

}


/****************************************************************************\
*                                                                          
*  FUNCTION   : CompareDevModes (DEVMODE *leftDM, DEVMODE *rightDM)                              
*                                                                          
*  PURPOSE    : Handles the display of the "floating" popup that appears   
*               on a mouse click in the app's client area.                 
*                                                                          
\****************************************************************************/
int CompareDevModes (

    DEVMODE *leftDM,
    DEVMODE *rightDM)
{

    //
    // Return 1  if left is bigger
    //        0  if equal
    //        -1 if right is bigger
    //
    // Comparison order is Width then Height then Bits then Frequency
    // This is an arbitrary order of importance. Often BitPerPels is
    // on considered the most important measure of a display setting
    //
    // return on the first one that is larger between left and right
    //

    if (leftDM->dmPelsWidth  > rightDM->dmPelsWidth)
    {
        return 1;
    }
    else if (leftDM->dmPelsWidth  < rightDM->dmPelsWidth)
    {
        return -1;
    }


    if (leftDM->dmPelsHeight > rightDM->dmPelsHeight)
    {
        return 1;
    }
    else if (leftDM->dmPelsHeight < rightDM->dmPelsHeight)
    {
        return -1;
    }


    if (leftDM->dmBitsPerPel > rightDM->dmBitsPerPel)
    {
        return 1;
    }
    else if (leftDM->dmBitsPerPel < rightDM->dmBitsPerPel)
    {
        return -1;
    }
    

    if (leftDM->dmDisplayFrequency > rightDM->dmDisplayFrequency)
    {
        return 1;
    }
    else if (leftDM->dmDisplayFrequency < rightDM->dmDisplayFrequency)
    {
        return -1;
    }

    //
    // All are equal
    //

    return 0;

}

/****************************************************************************\
*                                                                          
*  FUNCTION: About(HWND, UINT, UINT, LONG)
*
*  PURPOSE:  Processes messages for the "About" dialog box 
*
\****************************************************************************/
BOOL APIENTRY About(
    HWND hDlg,
    UINT message,
    UINT wParam,
    LONG lParam)
{
	switch (message)
	{
	   case WM_INITDIALOG:
		  return TRUE;

	   case WM_COMMAND:              
		 if (LOWORD(wParam) == IDOK)
		 {
			  EndDialog(hDlg, TRUE);
			  return TRUE;
		 }

		 break;

	   default:

		return FALSE;

	}

}

BOOL IsNT()
{
    OSVERSIONINFO          osvi;
    
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    
    GetVersionEx(&osvi);

    if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) 
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
