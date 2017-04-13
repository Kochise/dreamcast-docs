/*************************************************************************\
*
* TP Installer
*
* This program brings up a dialog box that prompts for TP configuration
* information.  The information is then placed in the registry under
* Windows NT, and in the WIN.INI file under Windows.  The WIN32 compiler
* flag specifies the NT version, while the WINDOWS flag specifies the
* Windows version.
*
* 6/93 Initial coding    ARK
*
\*************************************************************************/

#define STRICT
#include <windows.h>
#ifdef WIN32
#include <winsvc.h>
#endif

#ifdef        WIN32
        #include <windowsx.h>

BOOL IsWin95Client( void );

#else
        #include <windowsx.h16>
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "install.h"

HANDLE  hInst;                       // This program's instance
HWND    hDialog;                     // Global handle to main dialog
HWND    hTimeout;                    // A handle to the "timeout" window
HWND    hList;                       // Handle to the "users" list box

WNDPROC lPrevWndProcInt = NULL,      // Holds original integer edit box window proc
		lPrevWndProcAppc = NULL,     // Holds original APPC edit box window proc
        lPrevWndProcInfinite = NULL, // Original window proc for "infinite"
                                     // radio button
        lPrevWndProcConvSec = NULL,  // Same for "conversation security" box
        lPrevWndProcService = NULL;  // Same for "service" box

FARPROC lpfnInt = NULL,              // Pointer to the ValidateFieldInt
                                     // procedure; becomes non-NULL upon
                                     // initialization in ValidateField().
        lpfnAppc = NULL;	     // Pointer to ValidateFieldAppc procedure



/*************************************************************************\
*
*  FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
*
*  PURPOSE: Creates the dialog box.
*
*  COMMENTS:
*
\*************************************************************************/

int PASCAL WinMain (HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPSTR     lpCmdLine,
                      int       nCmdShow)
{
  DWORD retCode;
  FARPROC lpfn;

  hInst   = hInstance;

  lpfn = (FARPROC) MakeProcInstance( (FARPROC)MainDlgProc, hInst);
  retCode = DialogBoxParam ((HANDLE)hInst,
                            (LPCSTR)"MainDlg",
                            NULL,
                            (DLGPROC) lpfn,
                            0);
  FreeProcInstance(lpfn);

  return  (retCode);
}
/************************************************************************/
/*
 *  MainDlgProc: Handle messages to the main dialog.
 *  Note:  Under Windows NT, installation consists of creating a service
 *         and creating some keys in the registry, while under Windows
 *         we instead add slightly different information to the WIN.INI file.
 *         So two different dialogs are necessary for the different operating
 *         systems.  Appropriate sections of the procedure below are
 *         #ifdef'ed to handle parts of the installation that are unique
 *         to a particular operating system.
 */
/************************************************************************/
BOOL CALLBACK MainDlgProc (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam)
  {
  static   HWND hInfinite;
  char     *lpPathName, *lpTPName, *lpParameters, *lpTimeout, *lpLocalLUName;
  char     *divider;
  FARPROC  lpfn;
  INT      nIndex, cmd;
  BOOL     bService;
  HWND	   hwndCntl;
#ifdef WIN32
  DWORD	   dwVersion;
  HANDLE   hEvent;
#endif

  switch (wMsg)
    {
      case WM_INITDIALOG:
        hDialog = hDlg;

        // Set maximum pathname to 512 characters
        SendMessage(GetDlgItem(hDlg, IDE_PATHNAME),
                    EM_LIMITTEXT, MAXBINPATHLEN, 0);

        // Set maximum TP name to 128 characters
        SendMessage(GetDlgItem(hDlg, IDE_TPNAME),
                    EM_LIMITTEXT, MAXTPLEN, 0);

        // Default for timeout is "infinite"
        CheckRadioButton(hDlg, IDD_FINITE, IDD_INFINITE, IDD_INFINITE);

        hTimeout = GetDlgItem(hDlg, IDE_TIMEOUT);
        hList = GetDlgItem(hDlg, IDC_LIST);

        // Allow only numbers to be typed into the timeout box.
        ValidateField(hTimeout, VALIDATE_INT);

        // Set maximum length of number to be a few digits
        SendMessage(hTimeout, EM_LIMITTEXT, MAXTIMEOUTLEN, 0);

		// Allow only legal characters in "Local LU Alias" box:
		ValidateField(GetDlgItem(hDlg, IDE_LOCALLU), VALIDATE_APPC);

        // Set maximum length of LU name to be 8 characters
        SendMessage(GetDlgItem(hDlg, IDE_LOCALLU), EM_LIMITTEXT, MAXLULEN, 0);

        // Put an initial value in the "timeout" box & grey it out
        SetDlgItemInt(hDlg, IDE_TIMEOUT, INIT_TIMEOUT, FALSE);
        EnableWindow(hTimeout, FALSE);

        // Set callback procedure for radiobutton to make the timeout box
        // sensitive only when "finite" is selected.
        InstallCallback(hDlg, IDD_INFINITE, &lPrevWndProcInfinite, (FARPROC)InfiniteWndProc);

        // Set callback for "conversation security" to grey out user group
        // box when it's turned off.
        InstallCallback(hDlg, IDC_CONVSEC, &lPrevWndProcConvSec, (FARPROC)ConvSecWndProc);
        // Uncheck conversation security to force grey out of user group box
        SendMessage(GetDlgItem(hDlg, IDC_CONVSEC), BM_SETCHECK, 0, 0L);

#ifdef WIN32
		//
		// On Win95 don't allow TP to be configured as an NT service
		//
		dwVersion = GetVersion();
		if( dwVersion < 0x80000000 &&		// Windows NT
			!IsWin95Client() )				// Not Win95 client
		{
        	// Set callback for "service" to grey out queued
        	// box when it's turned on.
        	InstallCallback(hDlg, IDC_SERVICE, &lPrevWndProcService, (FARPROC)ServiceWndProc);

        	// Default for serviec is "yes"
        	CheckDlgButton(hDlg, IDC_SERVICE, 1);
		}
		else	// Non-NT or Win95 client on NT
		{
        	// Default for service is "no"
        	CheckDlgButton(hDlg, IDC_SERVICE, 0);

			// Disable the whole service option
    		hwndCntl = GetDlgItem( hDialog, IDC_SERVICE );
    		EnableWindow( hwndCntl, FALSE );
		}
#endif

        // Default for queued is "yes"
        CheckDlgButton(hDlg, IDC_QUEUED, 1);

        return TRUE;

      case WM_COMMAND:
        switch (cmd = GET_WM_COMMAND_ID(wParam, lParam))
          {
            case IDOK:
              // User hits OK; we get relevant info & try to install.

              // If TP name field is blank, error out
              if (ReadString(hDlg, IDE_TPNAME, &lpTPName, MAXTPLEN) == 0)
                {
                  DisplayError(hDlg, IDS_BADTPNAME);
                  free(lpTPName);
                  return TRUE;
                }

              // read path name
              ReadString(hDlg, IDE_PATHNAME, &lpPathName, MAXBINPATHLEN);

		      // read Local LU Alias
		      ReadString(hDlg, IDE_LOCALLU, &lpLocalLUName, MAXLULEN);

              // Get "timeout" value
              if (IsDlgButtonChecked(hDlg, IDD_INFINITE) == 1)
                lpTimeout = INFINITE_TIMEOUT;
              else
                {
                  // Number must be filled in, or else we complain
                  if (ReadString(hDlg, IDE_TIMEOUT, &lpTimeout, MAXTIMEOUTLEN + 3)
                      == 0)
                    {
                      DisplayError(hDlg, IDS_BADTIMEOUT);
				      free(lpPathName);
				      free(lpTimeout);
                      free(lpTPName);
                      return TRUE;
                    }
				  else
				    {
					  //
					  // convert to milliseconds the hard way
					  //
					  strcat( lpTimeout, "000" );
				    }
                }

              // Split off command-line parameters from executable name.
			  // Win95 and NT support spaces in pathnames, it is not safe
			  // to assume that first space marks the end of the executable name.
			  // It is quite safe to assume that executable programs stil end
			  // with extension .exe

			  if (divider = strstr(lpPathName, ".exe" ))
			  {
              	if (divider = strchr(divider, ' '))
              	{
                  lpParameters = divider + 1;
                  *divider = '\0';
              	}
                else
				{
				  lpParameters = "";
				}
			  }
              else lpParameters = "";

#ifdef WIN32
              bService = IsDlgButtonChecked(hDlg, IDC_SERVICE) == 1;

              // Install the new service; if successful, set subkeys
              if (bService && InstallServiceNT(hDlg, lpTPName, lpPathName) != 0)
                {
                  free(lpPathName);
                  free(lpTPName);
                  return TRUE;
                }

              if (CreateKeys(  lpTPName,
							   bService,
		                       lpLocalLUName,
                               IsDlgButtonChecked(hDlg, IDC_CONVSEC) == 1,
                               IsDlgButtonChecked(hDlg, IDC_ALREADYVER) == 1,
                               IsDlgButtonChecked(hDlg, IDC_QUEUED) == 1,
                               lpTimeout,
							   lpParameters,
							   lpPathName
                               )
                               != 0)
                {
                  free(lpPathName);
                  free(lpTPName);
                  return TRUE;
                }

			  //
			  // Now try to open the "SNABASE_NEWTP_EVENT" event and signal
			  // the SnaBase to dynamically register this new TP. NOTE this will
			  // only work with the WIN95 SnaBase. WinNT SnaBase doesn't create
			  // this event.
			  //
			  hEvent = OpenEvent( EVENT_MODIFY_STATE, FALSE, "SNABASE_NEWTP_EVENT" );
			  if( hEvent != NULL )
			  {
				  SetEvent( hEvent );
				  CloseHandle( hEvent );
			  }

              DisplayInfo(hDlg, IDS_SUCCESS);

#else

              // Add entries to WIN.INI
              if (InstallWindows(hDlg, lpTPName, lpPathName,
					 lpLocalLUName, lpParameters,
                                 IsDlgButtonChecked(hDlg, IDC_CONVSEC) == 1,
                                 IsDlgButtonChecked(hDlg, IDC_ALREADYVER) == 1,
                                 IsDlgButtonChecked(hDlg, IDC_QUEUED) == 1,
                                 lpTimeout
                                 ) != 0)
                {
                  free(lpPathName);
                  free(lpTPName);
                  return TRUE;
                }
              DisplayInfo(hDlg, IDS_SUCCESS);

#endif //ifdef WIN32

              EndDialog(hDlg, TRUE);
              free(lpPathName);
              free(lpTPName);
              return TRUE;

            case IDCANCEL:
              EndDialog(hDlg, FALSE);
              return TRUE;

            case IDC_ADD:
            case IDC_EDIT:
              // Bring up a dialog to add or edit username & password.
              // The last argument to DialogBoxParam is passed to the dialog
              // procedure and used to determine whether the procedure was
              // called from Add or Edit.
              lpfn = (FARPROC) MakeProcInstance( (FARPROC)UserDlgProc, hInst);
              DialogBoxParam (hInst,
                            (LPCSTR)"UserDlg",
                            hDialog,
                            (DLGPROC) lpfn,
                            cmd);
              FreeProcInstance(lpfn);
              return TRUE;

            case IDC_DELETE:
              nIndex = SendMessage(hList, LB_GETCURSEL, 0, 0);
              if (nIndex == LB_ERR)
                break;

              DeleteListItem(nIndex);
              break;

            default:
              return FALSE;
          }

        break;

      case WM_DESTROY:
        PostQuitMessage(0);
        return TRUE;
    }

#ifdef WIN32
  UNREFERENCED_PARAMETER(divider);
  UNREFERENCED_PARAMETER(lpParameters);
#endif

    return FALSE;
}
/*****************************************************************************/
/*
 * UserDlgProc: Dialog procedure for adding or editing a username/password
 *   pair.
 */
/*****************************************************************************/
BOOL CALLBACK UserDlgProc (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
  char *szUsername, *szPassword, *szPasswd;
  WORD nIndex;
  INT  nPasswdLen;
  LOCALHANDLE hLocalMem;

  switch(wMsg)
    {
      case WM_INITDIALOG:
        // Set maximum username length
        SendMessage(GetDlgItem(hDlg, IDE_USERNAME),
                    EM_LIMITTEXT, MAXUSERNAMELEN, 0);

        // Set maximum password length
        SendMessage(GetDlgItem(hDlg, IDE_PASSWORD),
                    EM_LIMITTEXT, MAXPASSWORDLEN, 0);

        // If we were called from the Edit button, we should fill in the
        // edit boxes with strings from the current selection
        if (lParam == IDC_EDIT)
          {
            // Make sure something is currently selected
            if ((nIndex = (WORD) SendMessage(hList, LB_GETCURSEL, 0, 0)) != LB_ERR)
              {
                szUsername = (char *) malloc(MAXUSERNAMELEN + 1);
                SendMessage(hList, LB_GETTEXT, (WPARAM) nIndex,
                            (LPARAM)(LPSTR)szUsername);
                SendMessage(GetDlgItem(hDlg, IDE_USERNAME), WM_SETTEXT, 0,
                            (LPARAM)(LPSTR)szUsername);
                free(szUsername);

                // Get pointer to password and then get password
                hLocalMem = (LOCALHANDLE) SendMessage(hList, LB_GETITEMDATA,
                                                      nIndex, 0);
                if (hLocalMem != NULL)
                  {
                    szPasswd = (char *) LocalLock(hLocalMem);
                    SendMessage(GetDlgItem(hDlg, IDE_PASSWORD), WM_SETTEXT, 0,
                                    (LPARAM)(LPSTR)szPasswd);
                    LocalUnlock(hLocalMem);
                  }
              }
          }

        break;

      case WM_COMMAND:
        switch(GET_WM_COMMAND_ID(wParam, lParam))
          {
            case IDOK:
              // Complain if username is blank
              if (ReadString(hDlg, IDE_USERNAME, &szUsername, MAXUSERNAMELEN)
                == 0)
                {
                  DisplayError(hDlg, IDS_NOUSERNAME);
                  free(szUsername);
                  return TRUE;
                }

              // Read password
              nPasswdLen = ReadString(hDlg, IDE_PASSWORD,
                                      &szPassword, MAXPASSWORDLEN);

              // Complain if password is blank
              if (nPasswdLen == 0)
                {
                  DisplayError(hDlg, IDS_NOPASSWORD);
                  free(szUsername);
                  free(szPassword);
                  return TRUE;
                }

              // If user is already listed, replace him by first deleting.
              // This also takes care of the Edit button, which presumably
              // will often have a username that already exists in the list.
              nIndex = (WORD) SendMessage(hList, LB_SELECTSTRING, (WPARAM) -1,
                                  (LPARAM) (LPSTR)szUsername);
              if (nIndex != LB_ERR)
                DeleteListItem(nIndex);

              // Add the new user to the "users" list in the main dialog
              nIndex = (WORD) SendMessage(hList, LB_ADDSTRING, 0,
                                    (LPARAM) (LPSTR) szUsername);

		      // Allocate some space for the password & store handle in list
		      hLocalMem = LocalAlloc(LHND, nPasswdLen + 1);
		      if (hLocalMem == NULL)
			{
			  DisplayError(hDlg, IDS_OUTOFMEMORY);
			  SendMessage(hList, LB_SETITEMDATA, nIndex, (LPARAM) NULL);
		        }
		      else
			{
			  szPasswd = (char *) LocalLock(hLocalMem);
			  strcpy(szPasswd, szPassword);
			  SendMessage(hList, LB_SETITEMDATA, nIndex, (LPARAM)(LPVOID)hLocalMem);
			  LocalUnlock(hLocalMem);
                }

              // Force highlight to newly inserted user, & enable Delete & Edit
              SendMessage(hList, LB_SETCURSEL, nIndex, 0L);
              EnableWindow(GetDlgItem(hDialog, IDC_DELETE), TRUE);
              EnableWindow(GetDlgItem(hDialog, IDC_EDIT), TRUE);

              EndDialog(hDlg, TRUE);
              return TRUE;

            case IDCANCEL:
              EndDialog(hDlg, FALSE);
              return TRUE;

            default:
              return FALSE;

          }
        break;
    }
  return FALSE;
}

#ifdef WIN32

/*****************************************************************************/
/*
 * InstallServiceNT( HWND hDlg, LPSTR lpServiceName, LPSTR lpPath )
 *
 * Windows NT version of installation--register a new service.
 *
 * Parameters
 * ----------
 *
 * hDlg: Handle to top level dialog; used for error messages.
 * lpServiceName: A string giving the name of the TP.
 * lpPath: A string giving the full pathname of the TP's executable.
 *
 * Returns
 * -------
 *
 *  Zero upon successful completion, nonzero otherwise.
 *
 * Comments
 * --------
 *  Installs new service if possible.  Puts up appropriate message boxes if
 *  installation fails.
 */
/*****************************************************************************/
int InstallServiceNT(HWND hDlg, LPSTR lpServiceName, LPSTR lpBinaryPath)
{

  SC_HANDLE hSCManager = NULL;
  SC_HANDLE hService   = NULL;
  SC_LOCK   lSCLock    = NULL;

  hSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );

  if( hSCManager != NULL )
  {
    /*************************************************************************/
    /* Lock the service database                                             */
    /*************************************************************************/
    lSCLock = LockServiceDatabase( hSCManager );
    if ( lSCLock != NULL )
    {
      /***********************************************************************/
      /* Create the service                                                  */
      /***********************************************************************/
      hService = CreateService( hSCManager,
                                lpServiceName,     // Service's name
                                lpServiceName,     // Display name (new for NT)
                                SERVICE_ALL_ACCESS,// Access (allow all)
                                0x10,              // Service type
                                0x3,               // Startup behavior
                                0x1,               // Error control
                                lpBinaryPath,      // Full pathname of binary
                                NULL,              // Load order group
                                NULL,              // Tag ID
                                NULL,              // Dependencies (none)
                                NULL,              // Account name
                                NULL               // Password
                                );
      if ( hService != NULL )
        {
          /*********************************************************************/
          /* Close our handle to the new service                               */
          /*********************************************************************/
          CloseServiceHandle( hService );
        }
      else
        {
          // Try to display the reason for the create failure
          ParseCreateError(hDlg, GetLastError());

          // Must release lock in case we are called again
          UnlockServiceDatabase( lSCLock );

          return 1;
        }

      /***********************************************************************/
      /* Unlock the database                                                 */
      /***********************************************************************/
      UnlockServiceDatabase( lSCLock );
    }
    else
      {
        DisplayError(hDlg, IDS_LOCKFAILED);
        return 1;
      }
    /*************************************************************************/
    /* Free our handle to the service control manager                        */
    /*************************************************************************/
    CloseServiceHandle( hSCManager );
    return 0;
  }

  DisplayError(hDlg, IDS_OPENSCMFAILED);
  return 1;
}

/*****************************************************************************/
/*
 * CreateKeys: Set the required key values for the newly created service.
 *  The keys are:
 *                 Linkage:
 *                        OtherDependencies: REG_MULTI_SZ: SnaBase
 *                Parameters:
 *                        SNAServiceType: REG_DWORD: 0x5
 *                        ConversationSecurity: REG_SZ:  "yes" or "no"
 *                           (depending on setting of radio button in dialog box)
 *				  AlreadyVerified: REG_SZ: "yes" or "no"
 * If the timeout isn't infinite, there appears the key:
 *                        Timeout: REG_DWORD: <timeout in seconds>
 *                        Parameters: REG_SZ: cmd line parameters
 * If ConversationSecurity is yes, there are also these keys:
 *                        <User1>: REG_SZ: <Password1>
 *                                ...
 *                        <Usern>: REG_SZ: <Passwordn>
 *
 *  Note that the users and passwords are read from the list box.
 *
 *  Arguments:
 *    lpServiceName is the name of the TP.
 *    lpLUName is the Local LU Alias.
 *    The two integer arguments give the state of the radio buttons on the
 *      dialog box.  They should be zero to indicate that "No" is selected,
 *      nonzero otherwise.
 *    lpTimeout is a string containing the timeout value; if the timeout is
 *      infinite, it holds the value of INFINITE_TIMEOUT.
 *
 *  Returns: 0 on success, nonzero otherwise.
 */
/*****************************************************************************/
INT CreateKeys(LPSTR lpServiceName, BOOL bService, LPSTR lpLUName, int iConvSec,
               int iAlreadyVer, int iQueued, LPSTR lpTimeout, LPSTR lpParameters,
			   LPSTR lpExeName)
{
  LPSTR  lpServiceFullName;
  int    bufsize, i, nCount;
  LOCALHANDLE hLocalMem;

  // If any of the buttons says "no", change the key values so that they
  // will be inserted into the registry below.  This is kind of gross, but
  // it keeps the loop below simple.
  if (iConvSec == 0)
    {
      keyinfo[CONVSEC].lpData = "no";
      keyinfo[CONVSEC].iDataSize = 3;
    }
  if (iAlreadyVer == 0)
    {
      keyinfo[ALREADYVER].lpData = "no";
      keyinfo[ALREADYVER].iDataSize = 3;
    }
  if (bService == FALSE && iQueued == 0)
    {
	  //
	  // the default of 5 is OK for queued support.
	  // needs to be redefined to 6 for nonqueued.
	  //
      keyinfo[SNASRVTYPE].lpData = "6";
      keyinfo[SNASRVTYPE].iDataSize = 4;
    }

  // Put timeout in structure (it won't be written out if infinite)
  keyinfo[TIMEOUT].lpData = lpTimeout;

  // Put Parameters in structure
  keyinfo[PARAMETERS].lpData = lpParameters;
  keyinfo[PARAMETERS].iDataSize = strlen(lpParameters) + 1;   // Count null

  // Put Local LU Alias in structure; it won't be written out if blank
  keyinfo[LUNAME].lpData = lpLUName;
  keyinfo[LUNAME].iDataSize = strlen(lpLUName) + 1;   // Count null

  // Create full path of TP by concatenating the registry path with the
  // TP's name
  bufsize = MAXREGPATHLEN + 1;
  lpServiceFullName = (LPSTR) malloc(bufsize);

  i = bService ? IDS_REGISTRYPATH : IDS_REGISTRYAPPLPATH ;

#ifdef WIN32
  if( IsWin95Client() )
  {
      i = bService ? IDS_REGISTRYPATH_WIN95 : IDS_REGISTRYAPPLPATH_WIN95;
  }
#endif

  LoadString( hInst, i, lpServiceFullName, bufsize );
  lstrcat(lpServiceFullName, lpServiceName);

  // Write out the basic keys; first key is skipped for non-service tps
  for ( i = bService ? 0 : 1; i < NUMKEYS; i++ )
    {
      if ( WriteKeyNT(lpServiceFullName, keyinfo[i], TRUE ) )
          return 1;
    }

  // if not a service then write out the path name
  if ( bService == FALSE )
    {
      keyinfo[EXENAME].lpData = lpExeName;
      keyinfo[EXENAME].iDataSize = strlen(lpExeName) + 1;   // Count null
      if (WriteKeyNT(lpServiceFullName, keyinfo[EXENAME], TRUE ) )
          return 1;
    }

  // If timeout isn't infinite, write out the "timeout" key
  if (lstrcmp(lpTimeout, INFINITE_TIMEOUT))
    {
      if (WriteKeyNT(lpServiceFullName, keyinfo[TIMEOUT], TRUE ) )
          return 1;
    }

  // If Local LU Alias isn't blank, write out its key
  if (strlen(lpLUName) > 0)
	 {
      if (WriteKeyNT(lpServiceFullName, keyinfo[LUNAME], TRUE ) )
          return 1;
    }

  // Only write out user stuff if conversation security is "yes"
  if (iConvSec)
    {
      keyinfo[USER].lpName = (LPSTR) malloc(MAXUSERNAMELEN + 1);
      nCount = SendMessage(hList, LB_GETCOUNT, 0, 0);
      for (i = 0; i < nCount; i++)
        {
          // Get username & make it the name of this key
          SendMessage(hList, LB_GETTEXT, (WPARAM) i,
                                  (LPARAM) keyinfo[USER].lpName);

          // Get pointer to password and then get password
          hLocalMem = (LOCALHANDLE) SendMessage(hList, LB_GETITEMDATA, i, 0);
          keyinfo[USER].lpData = (LPSTR) LocalLock(hLocalMem);

          // Password shouldn't be blank, but just in case...
          if (keyinfo[USER].lpData == NULL)
            keyinfo[USER].iDataSize = 0;
          else
            keyinfo[USER].iDataSize = strlen(keyinfo[USER].lpData);

          if (WriteKeyNT(lpServiceFullName, keyinfo[USER], TRUE ) )
            {
              LocalUnlock(hLocalMem);
              return 1;
            }
          LocalUnlock(hLocalMem);
        }
    }

  free(lpServiceFullName);
  return 0;
}
/*****************************************************************************/
/*
 * WriteKeyNT: Write out the given key to the registry.
 * Return 0 on success, nonzero otherwise.
 */
/*****************************************************************************/
INT WriteKeyNT(LPSTR lpServiceFullName, KEYENTRY keyinfo, BOOL bAppendParent )
{
static BOOL	bAskToReplace = TRUE;
  DWORD     dwResult;
  HKEY      hKey;
  LPSTR     lpKeyName;
  DWORD		dwTemp;

  lpKeyName = (LPSTR) malloc(MAXREGPATHLEN + 1);

  // Build full pathname of key by appending a backslash and the name of the
  // key to the full pathname of the TP.
  lstrcpy(lpKeyName, lpServiceFullName);
  lstrcat(lpKeyName, TEXT("\\"));
  lstrcat(lpKeyName, keyinfo.lpParent);

  // Now create the subkeys and set their values
  if (RegCreateKeyEx(HKEY_LOCAL_MACHINE,      // Predefined key
      lpKeyName,                      // Our subkey's name
      0,                       // Reserved
      NULL,                    // Class string
      REG_OPTION_NON_VOLATILE, // Option type (value is saved)
      KEY_ALL_ACCESS,          // Access mask
      NULL,                    // Security attributes
      &hKey,                   // Handle to key is put here
      &dwResult)               // Was key opened or created?
      == ERROR_SUCCESS)
        {
          if ( bAskToReplace && dwResult == REG_OPENED_EXISTING_KEY )
		    {
			char szCaption[64];
			char szText[256];
			  LoadString( hInst, IDS_REPLACECAPTION, szCaption, sizeof(szCaption) );
			  LoadString( hInst, IDS_REPLACETEXT, szText, sizeof(szText) );
			  switch( MessageBox( hDialog, szText, szCaption, MB_OKCANCEL|MB_ICONQUESTION ) )
			    {
			  case IDCANCEL:
				  return 1;

			    }
		    }

		  //
		  // after first successful pass no need to query
		  //
		  bAskToReplace = FALSE;

          // We stored all the values as strings, but some are actually numbers.
          // So we have to make a temporary buffer to pass RegSetValueEx the
          // pointer to a DWORD that it wants for DWORD data.
          if ( keyinfo.iDataType == REG_DWORD )
            {
              dwTemp = atol(keyinfo.lpData);
              keyinfo.lpData = (LPSTR) &dwTemp;
              keyinfo.iDataSize = sizeof(DWORD);
            }

          if (RegSetValueEx(hKey,
                        keyinfo.lpName,    // Key name
                        0,                    // Reserved
                        keyinfo.iDataType, // Type of key data
                        keyinfo.lpData,    // Key's value
                        keyinfo.iDataSize  // Length of value (incl. nulls)
                        )
                        != ERROR_SUCCESS)
            {
              DisplayError(hDialog, IDS_SETKEYFAILED);
              return 1;
            }
        }
      else
        {
          DisplayError(hDialog, IDS_OPENKEYFAILED);
          return 1;
        }

  free(lpKeyName);
  return 0;
}
/*****************************************************************************/
/*
 * ParseCreateError: Given an error code from a registry operation, attempt
 *   to give an appropriate error message.
 */
/*****************************************************************************/
void ParseCreateError(HWND hDlg, UINT uError)
{
  UINT code;
  switch (uError)
    {
      case ERROR_INVALID_PARAMETER:
        // "Invalid parameter" is a rather generic error name.  Since a blank
        // service name is the most probable way the error arose, say so:
        code = IDS_BADPATHNAME;
        break;

      case ERROR_INVALID_NAME:
        code = IDS_BADTPNAME;
        break;

      case ERROR_SERVICE_EXISTS:
        code = IDS_SERVICEEXISTS;
        break;

      default:
        // Since we don't have a code for this error, the following will bring
        // up the "unknown" error message
        code = uError;
    }
  DisplayError(hDlg, code);
}

#else

/*****************************************************************************/
/*
 * InstallWindows: Windows version of installation; add lines to WIN.INI
 *
 * First we must add an entry under the heading SNAServerAutoTPs.  This entry
 * has the name of the TP and points to another heading that contains TP-
 * specific data.  Sample WIN.INI:
 *
 * [SNAServerAutoTPs]
 * BounceTP = BounceTPParams
 *
 * [BounceTPParams]
 * PathName = c:\sna\bounce.exe
 * Parameters = /t
 * etc....
 *
 * For a list of entries, see the comment at CreateKeys().  The only difference
 * is that WIN.INI also contains an entry for the "queued" toggle.
 *
 *
 * Parameters:
 *    szTPName: The name of the TP
 *    szBinaryPath: The full pathname of the executable
 *    szLUName: Local LU Alias
 *    szParameters: The list of command line parameters
 *    iConvSec: "Conversation security" toggle (1 = yes, 0 = no)
 *    iAlreadyVer: "Already verified" toggle
 *    iQueued: "Queued" toggle
 *    lpTimeout: A string specifying the timeout in seconds, e.g. "2"
 *
 * Returns: zero on success, nonzero otherwise
 */
/*****************************************************************************/
INT InstallWindows(HWND hDlg, char *szTPName, char *szBinaryPath, char *szLUName,
                   char *szParameters,
                   int iConvSec, int iAlreadyVer, int iQueued, char *lpTimeout
                   )
{
  char szNewKeyName[MAXTPLEN + 6];
  int  i, nCount;
  LOCALHANDLE hLocalMem;

  // Make new heading by concatenating TP's name and the string "Params"
  strcpy(szNewKeyName, szTPName);
  strcat(szNewKeyName, "Params");

  // Now add the key to the SNAServerAutoTPs heading
  if (WriteKeyWindows("SNAServerAutoTPs", szTPName, szNewKeyName))
    return 1;

  // Set the data fields of the keys, one at a time
  keyinfo[PATHNAME].data    = szBinaryPath;
  keyinfo[PARAMETERS].data  = szParameters;
  keyinfo[LUNAME].data      = szLUName;
  keyinfo[QUEUED].data      = iQueued ? "yes" : "no";
  keyinfo[TIMEOUT].data     = lpTimeout;
  keyinfo[CONVSEC].data     = iConvSec ? "yes" : "no";
  keyinfo[ALREADYVER].data  = iAlreadyVer ? "yes" : "no";

  // Loop through all the keys and add them under the new "Params" heading
  for (i=0; i < NUMKEYS; i++)
    if (WriteKeyWindows(szNewKeyName, keyinfo[i].name, keyinfo[i].data))
      return 1;

  // Only write out Local LU Alias if it's not blank
  if (strlen(szLUName) > 0)
    if (WriteKeyWindows(szNewKeyName, keyinfo[LUNAME].name, keyinfo[LUNAME].data))
      return 1;

  // If conversation security is on, write out users & passwords
  if (iConvSec)
    {
      keyinfo[USER].name = (char *) malloc(MAXUSERNAMELEN + 1);
      nCount = SendMessage(hList, LB_GETCOUNT, 0, 0);

      // Read usernames and passwords from list box & create keys
      for (i = 0; i < nCount; i++)
        {
          // Get username & make it the name of this key
          SendMessage(hList, LB_GETTEXT, (WPARAM) i,
                                  (LPARAM)(LPSTR)keyinfo[USER].name);

          // Get pointer to password and then get password
          hLocalMem = (LOCALHANDLE) SendMessage(hList, LB_GETITEMDATA, i, 0);
          keyinfo[USER].data = (char *) LocalLock(hLocalMem);

          if (WriteKeyWindows(szNewKeyName, keyinfo[USER].name,
                                keyinfo[USER].data))
            {
              LocalUnlock(hLocalMem);
              return 1;
            }
          LocalUnlock(hLocalMem);
        }
      free(keyinfo[USER].name);

    }

  return 0;
}
/*****************************************************************************/
/*
 * WriteKeyWindows:  Write the given key out to WIN.INI
 * Return 0 on success, nonzero otherwise.
 */
/*****************************************************************************/
INT WriteKeyWindows(char *heading, char *keyname, char *value)
{
  if (WriteProfileString(heading, keyname, value) == FALSE)
    {
      DisplayError(hDialog, IDS_INIWRITEFAILED);
      return 1;
    }
  return 0;
}

#endif //ifdef WIN32

/*****************************************************************************/
/*
 * ValidateField: Install a window procedure that handles messages to the
 *   given edit window.
 *
 * Parameters: hwnd is the edit window, usType an identifier for the window
 *   procuedure to install.  Currently the only allowed type is VALIDATE_INT,
 *   which allows only digits to be typed into the edit box.
 *
 * Returns:  TRUE if window procedure is successfully installed,
 *   FALSE otherwise.
/*****************************************************************************/
BOOL ValidateField( HWND hwnd, USHORT usType)
{
        FARPROC lpfn = NULL;
        LONG        lPrevWndProc;
        LONG FAR *lplNewWndProc;

        if (hwnd == NULL) {
                return(FALSE);
        }

        lPrevWndProc = GetWindowLong( hwnd, GWL_WNDPROC );

        if (lPrevWndProc == 0) {
                return(FALSE);
        }

        // check that the old wndproc is the same as the one we have stored
        // also, get the new wndproc, based on contents of edit field

        // We only need two validation procedures, but if you want others
        // (such as hexadecimal, filenames, etc.) you can add extra cases
        // and procedures below.

        switch (usType) {
          case VALIDATE_INT:
            if (lpfnInt == NULL) {
              lpfnInt = MakeProcInstance( (FARPROC)ValidateFieldInt, hInst );
            }
            lpfn = lpfnInt;

            lplNewWndProc = (LONG FAR *) &lPrevWndProcInt;
            break;

		  case VALIDATE_APPC:
            if (lpfnAppc == NULL) {
              lpfnAppc = MakeProcInstance( (FARPROC)ValidateFieldAppc, hInst );
            }
            lpfn = lpfnAppc;

            lplNewWndProc = (LONG FAR *) &lPrevWndProcAppc;
            break;

          default:
            return(FALSE);
          }

        if (*lplNewWndProc == (LONG) NULL) {

                *lplNewWndProc = lPrevWndProc;

        } else {

                if (*lplNewWndProc != lPrevWndProc) {
                        return(FALSE);
                }

                *lplNewWndProc = lPrevWndProc;
        }

        if (lpfn == NULL ||
                SetWindowLong(hwnd, GWL_WNDPROC, (LONG) lpfn) == (LONG) NULL) {

                return(FALSE);
        }
        return(TRUE);
}

/*****************************************************************************/
/*
 * ValidateFieldInt: A window proc that allows only 0 through 9 to be typed to
 *   an edit box.
 */
/*****************************************************************************/
LRESULT CALLBACK ValidateFieldInt( HWND hwnd, WORD msg, WPARAM wParam, LPARAM lParam )
{
        if (msg == WM_CHAR) {

                char ch = LOBYTE(LOWORD(wParam));

                if ((ch < '0' || ch > '9') && ch != VK_BACK )
                  return(0);
        }
        // If character was legal or message wasn't WM_CHAR,
        // pass message on to default window proc.
        return CallWindowProc( lPrevWndProcInt, hwnd, msg, wParam, lParam);
}
/*****************************************************************************/
/*
 * ValidateFieldAppc: A window proc that allows only legal APPC name characters
 *    to be typed to an edit box.
 */
/*****************************************************************************/
LRESULT CALLBACK ValidateFieldAppc( HWND hwnd, WORD msg, WPARAM wParam, LPARAM lParam )
{
	if (msg == WM_CHAR) {

		char ch = LOBYTE(LOWORD(wParam));

		if (!(ch >= '0' && ch <= '9' ||
			ch >= 'A' && ch <= 'Z' ||
			ch >= 'a' && ch <= 'z' ||
			ch == '@'	||
			ch == '#'	||
			ch == '$'	||
			ch == '%'	||
			ch == VK_BACK ))
		    return(0);
	}
	return CallWindowProc( lPrevWndProcAppc, hwnd, msg, wParam, lParam);
}
/*****************************************************************************/
/*
 * InstallCallback: Install a callback window proc.
 *   Arguments:
 *        hDlg: Handle of the parent dialog
 *      uId: ID of window for which callback will be installed
 *      OldWndProc: Handle for previous window proc
 *      NewWndProc: Pointer to new window proc
 */
/*****************************************************************************/
void InstallCallback(HWND hDlg, UINT uId, WNDPROC *OldWndProc, FARPROC NewWndProc)
{
  HANDLE hTemp;

  hTemp = GetDlgItem(hDlg, uId);
  *OldWndProc = (WNDPROC) GetWindowLong(hTemp, GWL_WNDPROC);
  SetWindowLong(hTemp, GWL_WNDPROC,
               (LONG) MakeProcInstance( (FARPROC)NewWndProc, hInst));
}
/*****************************************************************************/
/*
 * InfiniteWndProc: Disable "timeout" box when the "infinite"
 *   button is pressed, and enable it when "finite" is pressed.
 */
/*****************************************************************************/
LRESULT CALLBACK InfiniteWndProc( HWND hwnd, WORD msg, WPARAM wParam, LPARAM lParam )
{
  if (msg == BM_SETCHECK)
    // wParam is 0 if button is being turned off, 1 if being turned on
    EnableWindow(hTimeout, (wParam == 0));
  return CallWindowProc(lPrevWndProcInfinite, hwnd, msg, wParam, lParam);
}


/*****************************************************************************/
/*
 * ServiceWndProc: Disable "queued" box when the "service" button is pressed
 */
/*****************************************************************************/
LRESULT CALLBACK ServiceWndProc( HWND hwnd, WORD msg, WPARAM wParam, LPARAM lParam )
{
  HWND hwndCntl;

  if (msg == BM_SETCHECK) {
	//
    // wParam is 0 if button is being turned off, 1 if being turned on
	//
    hwndCntl = GetDlgItem( hDialog, IDC_QUEUED );
    EnableWindow( hwndCntl, wParam == 1 ? FALSE : TRUE );

	if ( wParam == 1 ) {
		SendMessage( hwndCntl, BM_SETCHECK, 1, 0 );
	}
  }

  return CallWindowProc(lPrevWndProcService, hwnd, msg, wParam, lParam);
}


/*****************************************************************************/
/*
 * ConvSecWndProc: Window proc for "conversation security" checkbox.  Grey
 *   out "users" group box when checkbox is off
 */
/*****************************************************************************/
LRESULT CALLBACK ConvSecWndProc( HWND hwnd, WORD msg, WPARAM wParam, LPARAM lParam )
{
  int nItems = SendMessage(hList, LB_GETCOUNT, 0, 0L);
  if (msg == BM_SETCHECK)
    {
      EnableWindow(GetDlgItem(hDialog, IDC_USERBOX), wParam == 1 ? TRUE : FALSE);
      EnableWindow(GetDlgItem(hDialog, IDC_ADD), wParam == 1 ? TRUE : FALSE);
      EnableWindow(hList, wParam == 1 ? TRUE : FALSE);
      // Only turn on Delete & Edit if there's something in the list box
      EnableWindow(GetDlgItem(hDialog, IDC_DELETE), wParam == 1 && nItems);
      EnableWindow(GetDlgItem(hDialog, IDC_EDIT), wParam == 1 && nItems);
    }
  return CallWindowProc(lPrevWndProcConvSec, hwnd, msg, wParam, lParam);
}


/*****************************************************************************/
/*
 * DeleteListItem: Handle all aspects of deleting a user from the list box,
 *   given his index.
 */
/*****************************************************************************/
void DeleteListItem(INT nIndex)
{
  LOCALHANDLE hLocalMem;
  INT nUsers;

  // Free associated password memory, if necessary
  if (hLocalMem = (LOCALHANDLE) SendMessage(hList, LB_GETITEMDATA,
                                            nIndex, 0))
    LocalFree(hLocalMem);

  // Simply remove currently selected user
  SendMessage(hList, LB_DELETESTRING, (WPARAM) nIndex, 0);

  nUsers = SendMessage(hList, LB_GETCOUNT, 0, 0);

  // Disable Delete & Edit buttons if no one is left
  if (0 == nUsers)
    {
      EnableWindow(GetDlgItem(hDialog, IDC_DELETE), FALSE);
      EnableWindow(GetDlgItem(hDialog, IDC_EDIT), FALSE);
      return;
    }

  // Move the highlight:
  // 1) If the deleted user was the last one in the list, go to previous user.
  // 2) Otherwise go to the next user.
  SendMessage(hList, LB_SETCURSEL,
              (nUsers == nIndex) ? (nIndex - 1) : nIndex, 0);
}
/*****************************************************************************/
/*
 * ReadString: Get the text from an edit box and turn it into a C string.
 *
 * Parameters:
 *
 * hDlg:  The dialog box.
 * id: The dialog item id.
 * lpString:  A double pointer to a character.  ReadString reserves space
 *            for the incoming string.
 * maxlen: The maximum number of characters to read from the edit box.
 *
 * Returns:
 *   The number of characters read from the edit box.
 */
/*****************************************************************************/
INT ReadString(HWND hDlg, INT id, char **lpString, INT maxlen)
{
  // Leave space for null character
  *lpString = malloc((maxlen + 1) * sizeof(char));

  return GetDlgItemText(hDlg, id, *lpString, maxlen+1);
}
/*****************************************************************************/
/*
 * DisplayError: Bring up MessageBox with given message code's string.
 */
/*****************************************************************************/
void DisplayError( HWND hwnd, UINT uError)
{
        char        sz[256], szFormat[256];

        if ( LoadString( hInst, uError, sz, sizeof(sz)) == 0 ) {
                LoadString( hInst, IDS_UNKNOWN, szFormat, sizeof(szFormat) );
                sprintf( sz, szFormat, uError );
        }

        LoadString( hInst, IDS_ERRORTITLE, szFormat, sizeof(szFormat) );
        MessageBox( hwnd, sz, szFormat, MB_ICONEXCLAMATION | MB_OK);
}
/*****************************************************************************/
/*
 * DisplayInfo:  Put up an information box with given message string.
 */
/*****************************************************************************/
void DisplayInfo( HWND hwnd, UINT uInfo)
{
        char        sz[256], szFormat[256];

        if ( LoadString( hInst, uInfo, sz, sizeof(sz) ) == 0 ) {
                LoadString( hInst, IDS_NOMESSAGE, szFormat, sizeof(szFormat) );
                sprintf( sz, szFormat, uInfo );
        }

        LoadString( hInst, IDS_INFOTITLE, szFormat, sizeof(szFormat) );
        MessageBox( hwnd, sz, szFormat, MB_ICONINFORMATION | MB_OK);
}

#ifdef WIN32
/*****************************************************************************/
/*
 * IsWin95Client( void ):  If this is the Win95 client, return TRUE
 */
/*****************************************************************************/

BOOL IsWin95Client( void )
{
    HKEY hKey;
    BOOL fRetval = FALSE;
    DWORD dwType=0;
    char  szBuffer[ 30 ];
    DWORD dwDataSize = sizeof( szBuffer );


    if( ERROR_SUCCESS != RegOpenKeyEx( HKEY_LOCAL_MACHINE, "Software\\Microsoft\\SNA Server\\CurrentVersion", 0, KEY_QUERY_VALUE, &hKey ) )
    {
        ; // fall through, return FALSE
    }
    else
    {
        if( ERROR_SUCCESS != RegQueryValueEx( hKey, "ClientType", 0, &dwType, szBuffer, &dwDataSize ) )
        {
            ; // fall through, return FALSE
        }
        else if( REG_SZ != dwType )
        {
            ; // fall through, return FALSE
        }
        else if( stricmp( szBuffer, "Windows 95" ) )
        {
            ; // fall through, return FALSE
        }
        else
        {
            fRetval = TRUE;
        }

        RegCloseKey( hKey );
    }

    return fRetval;

}

#endif


