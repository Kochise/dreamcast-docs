//
//  C M C C L I . C
//
//      Sample CMC mail client for the MAPI 1.0 PDK.
//      Uses the CMC interface without extensions.
//
//

#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <lzexpand.h>
#include <xcmc.h>
#include <xcmcext.h>
#include <xcmcmsxt.h>
#include "pvalloc.h"
#include "cmccli.h"

HINSTANCE hInst;
HINSTANCE hlibCMC = (HINSTANCE)NULL;

LPFNCMCQUERYCONFIGURATION lpfnCMCQueryConfiguration = NULL;
LPFNCMCLOGON lpfnCMCLogon = NULL;
LPFNCMCLOGOFF lpfnCMCLogoff = NULL;
LPFNCMCFREE lpfnCMCFree = NULL;
LPFNCMCLOOKUP lpfnCMCLookUp = NULL;
LPFNCMCLIST lpfnCMCList = NULL;
LPFNCMCSEND lpfnCMCSend = NULL;
LPFNCMCREAD lpfnCMCRead = NULL;
LPFNCMCACTON lpfnCMCActOn = NULL;

// Static Data

static BOOL fPriority = 0;
static BOOL fReturn = 0;
static CMC_extension extMsgOpt[2] = \
                     {{CMC_X_COM_PRIORITY, CMC_X_COM_NORMAL, NULL, 0}, \
                      {CMC_X_MS_MESSAGE_DATA, 0, NULL, CMC_EXT_LAST_ELEMENT}};

static CMC_session_id lhSession = 0;
static HBITMAP hReadBmp;
static HBITMAP hReadABmp;
static HBITMAP hUnReadBmp;
static HBITMAP hUnReadABmp;
static HCURSOR hWaitCur;
static LPMSGID lpReadMsgNode=NULL;
static CMC_message FAR *CmcMsg = NULL;

int PASCAL
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmd, int nCmdShow)
{
    MSG msg;

    hlibCMC = (HINSTANCE) NULL;

    if (!hPrevInst)
        if (!InitApplication (hInstance))
            return (FALSE);

    if (!InitInstance (hInstance, nCmdShow))
        return (FALSE);

    while (GetMessage (&msg, (HWND) NULL, 0, 0))
    {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }

    if (hReadBmp)
        DeleteObject (hReadBmp);
    if (hReadABmp)
        DeleteObject (hReadABmp);
    if (hReadBmp)
        DeleteObject (hUnReadBmp);
    if (hReadBmp)
        DeleteObject (hUnReadABmp);

    DeinitApplication ();

    return (msg.wParam);
}

//
//  InitApplication
//
//  Purpose:
//      Initialize the application.
//
//  Parameters:
//      hInstance   - Instance handle
//
//  Returns:
//      True/False
//
//

BOOL
InitApplication (HINSTANCE hInstance)
{
    WNDCLASS wc;

    wc.style = 0;
    wc.lpfnWndProc = MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (hInstance, "NoMail");
    wc.hCursor = LoadCursor ((HINSTANCE) hInstance, IDC_ARROW);
    wc.hbrBackground = GetStockObject (WHITE_BRUSH);
    wc.lpszMenuName = "MailMenu";
    wc.lpszClassName = "Client";

    return (RegisterClass (&wc));
}

//
//  InitInstance
//
//  Purpose:
//      Initialize this instance.
//
//  Parameters:
//      hInstance   - Instance handle
//      nCmdShow    - Do we show the window?
//
//  Returns:
//      True/False
//
//

BOOL
InitInstance (HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;
    BOOL fInit;
    CMC_return_code ulResult;
    CMC_boolean UI_available;
    CMC_extension ext;
    CMC_X_COM_support sup[2];

    hInst = hInstance;

    hWnd = CreateWindow ("Client", "CMC Sample Mail Client", WS_OVERLAPPEDWINDOW,
        5, 5, 300, 75, (HWND) NULL, (HMENU) NULL, hInst, NULL);

    if (!hWnd)
        return (FALSE);

    ShowWindow (hWnd, nCmdShow);
    UpdateWindow (hWnd);

    hReadBmp = LoadBitmap (hInst, MAKEINTRESOURCE (IDREAD));
    hReadABmp = LoadBitmap (hInst, MAKEINTRESOURCE (IDREADA));
    hUnReadBmp = LoadBitmap (hInst, MAKEINTRESOURCE (IDUNREAD));
    hUnReadABmp = LoadBitmap (hInst, MAKEINTRESOURCE (IDUNREADA));

    hWaitCur = LoadCursor( (HINSTANCE) NULL, IDC_WAIT);

    if (fInit = InitSimpleCMC ())
    {
        if((ulResult = CMCQueryConfiguration(
           (CMC_session_id) NULL, // no session handle yet!
           CMC_CONFIG_UI_AVAIL,   // Make sure UI is available
           &UI_available,         // return value
           NULL))==CMC_SUCCESS)
        {
            sup[0].item_code = CMC_XS_COM;
            sup[0].flags = 0;
            sup[1].item_code = CMC_XS_MS;
            sup[1].flags = 0;
            ext.item_code = CMC_X_COM_SUPPORT_EXT;
            ext.item_data = 2;
            ext.item_reference = sup;
            ext.extension_flags = CMC_EXT_LAST_ELEMENT;

            /* CMCLogon might yield control to Windows. So to prevent the user
            from clicking "logon" while we are in the process of loggin on we
            have to disable it*/
            SecureMenu(hWnd, TRUE);

            if ((ulResult = CMCLogon (NULL, NULL, NULL, (CMC_enum)0,
                                  (CMC_ui_id)hWnd, CMC_VERSION,
                                  CMC_LOGON_UI_ALLOWED | CMC_ERROR_UI_ALLOWED,
                                  &lhSession, &ext))==CMC_SUCCESS)
            {
                if(sup[0].flags & CMC_X_COM_SUPPORTED)
                    fPriority = TRUE;
                else
                    fPriority = FALSE;
                if(sup[1].flags & CMC_X_COM_SUPPORTED)
                    fReturn = TRUE;
                else
                    fReturn = FALSE;

                ToggleMenuState (hWnd, TRUE);
            }
            else
            {
                SecureMenu(hWnd, FALSE);
                lhSession = 0;
                MakeMessageBox (hWnd, ulResult, IDS_LOGONFAIL, MBS_ERROR);
            }
        }
        else
        {
            lhSession = 0;
            MakeMessageBox (hWnd, ulResult, IDS_LOGONFAIL, MBS_ERROR);
        }
    }
    return (fInit);
}

//
//  InitSimpleCMC
//
//  Purpose:
//      Loads the DLL containing the simple CMC functions and sets
//      up a pointer to each. Wrappers for the  function pointers
//      are declared in CLIENT.H.
//
//  Returns:
//      TRUE if sucessful, else FALSE
//
//  Side effects:
//      Loads a DLL and sets up function pointers
//
BOOL
InitSimpleCMC (void)
{
    char    szMsgBuf[512]="";
    char    szLibName[32]
        #ifdef WIN16
            ="MAPI.DLL";
        #else
            ="MAPI32.dll";
        #endif

    /*
     *Check if CMC is installed on the system
     */
    if(!fCMCInstalled())
        return FALSE;


    // Get INI directives for alternate DLL PATH
    
#ifdef WIN16
    GetProfileString( "Mail", "CMCDLLNAME", szLibName, szLibName, 
            sizeof(szLibName) - 1 );
#else
    GetProfileString( "Mail", "CMCDLLNAME32", szLibName, szLibName, 
            sizeof(szLibName) - 1 );
#endif  

#ifdef WIN16
    if ((hlibCMC = LoadLibrary (szLibName)) <  32)
#else
    if ((hlibCMC = LoadLibrary (szLibName)) <  (HINSTANCE) 32)
#endif
    {
        wsprintf(szMsgBuf,"Cannot Load %s.  Check to see that you have %s in your path or '~SystemRoot~\\System' "
                          "directory.  You may change the CMC dll path by adding a [MAIL] section to your "
                          "WIN.INI file wtih the following entry: CMCDLLNAME=\\MAPI.REL\\MAPI.DLL",
                          szLibName,szLibName);
        MessageBox(NULL, szMsgBuf,"Error", MB_ICONSTOP | MB_OK);
        return FALSE;
    }

    if (!(lpfnCMCQueryConfiguration = (LPFNCMCQUERYCONFIGURATION)GetProcAddress (hlibCMC, "cmc_query_configuration") ))
    {
        wsprintf(szMsgBuf,"Cannot Load CMC process functions from %s.  Check that you do not have an "
                          "outdated version of %s in your '~SystemRoot~\\System' directory.  If you do then you "
                          "may change the CMC dll path by adding a [MAIL] section to your WIN.INI file with the "
                          "following entry: CMCDLLNAME=\\MAPI.REL\\%s",szLibName,szLibName,szLibName);
        MessageBox(NULL, szMsgBuf,"Error", MB_ICONSTOP | MB_OK);
        return FALSE;
    }

    if (!(lpfnCMCLogon  =  (LPFNCMCLOGON)GetProcAddress (hlibCMC, "cmc_logon") ))
    {
        MessageBox(NULL, "Cannot Load cmc_logon process address.","Error", MB_ICONSTOP | MB_OK);
        return FALSE;
    }

    if (!(lpfnCMCLogoff  =  (LPFNCMCLOGOFF)GetProcAddress (hlibCMC, "cmc_logoff") ))
    {
        MessageBox(NULL, "Cannot Load cmc_logoff process address.","Error", MB_ICONSTOP | MB_OK);
        return FALSE;
    }

    if (!(lpfnCMCFree  =  (LPFNCMCFREE)GetProcAddress (hlibCMC, "cmc_free") ))
    {
        MessageBox(NULL, "Cannot Load cmc_free process address.","Error", MB_ICONSTOP | MB_OK);
        return FALSE;
    }

    if (!(lpfnCMCLookUp  =  (LPFNCMCLOOKUP)GetProcAddress (hlibCMC, "cmc_look_up") ))
    {
        MessageBox(NULL, "Cannot Load cmc_look_up process address.","Error", MB_ICONSTOP | MB_OK);
        return FALSE;
    }

    if (!(lpfnCMCList  =  (LPFNCMCLIST)GetProcAddress (hlibCMC, "cmc_list") ))
    {
        MessageBox(NULL, "Cannot Load cmc_list process address.","Error", MB_ICONSTOP | MB_OK);
        return FALSE;
    }

    if (!(lpfnCMCSend  =  (LPFNCMCSEND)GetProcAddress (hlibCMC, "cmc_send") ))
    {
        MessageBox(NULL, "Cannot Load cmc_send process address.","Error", MB_ICONSTOP | MB_OK);
        return FALSE;
    }

    if (!(lpfnCMCRead  =  (LPFNCMCREAD)GetProcAddress (hlibCMC, "cmc_read") ))
    {
        MessageBox(NULL, "Cannot Load cmc_read process address.","Error", MB_ICONSTOP | MB_OK);
        return FALSE;
    }

    if (!(lpfnCMCActOn  =  (LPFNCMCACTON)GetProcAddress (hlibCMC, "cmc_act_on") ))
    {
        MessageBox(NULL, "Cannot Load cmc_acto_on process address.","Error", MB_ICONSTOP | MB_OK);
        return FALSE;
    }

    return (TRUE);

}


/*
 -  fCMCInstalled
 -
 *  Purpose:
 *      Checks the appropriate win.ini/registry value to see if CMC is
 *      installed in the system. 
 *  
 *  Returns:
 *      TRUE if CMC is installed, else FALSE
 *
 */
BOOL
fCMCInstalled(void)
{
#ifdef _WIN32
    /* on win32 the value to check is 
        HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows Messaging Subsystem\CMC
    */
    
    LONG lr;
    HKEY hkWMS;
    
    #define CMCVSize 8
    char szCMCValue[CMCVSize];
    DWORD dwType;
    DWORD cbCMCValue = CMCVSize;

    lr = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                    "SOFTWARE\\Microsoft\\Windows Messaging Subsystem",
                     0, KEY_READ, &hkWMS);
    if(ERROR_SUCCESS == lr)
    {
        lr = RegQueryValueEx(hkWMS, "CMC", 0, &dwType, szCMCValue, &cbCMCValue);
        RegCloseKey(hkWMS);
        if(ERROR_SUCCESS == lr)
        {
            if(lstrcmp(szCMCValue, "1") == 0)
                return TRUE;
        }
    }
    
    return FALSE;

#else /*_WIN32*/
    
    /*check the win.ini value*/
    return GetProfileInt("Mail", "CMC", 0);

#endif /*_WIN32*/
}


void
DeinitSimpleCMC ()
{
    if (hlibCMC)
    {
        FreeLibrary (hlibCMC);
        hlibCMC = (HINSTANCE) NULL;
    }
}


void
DeinitApplication ()
{
    DeinitSimpleCMC ();
}


//
//  MainWndProc
//
//  Purpose:
//      Main Window Procedure for test program.
//
//  Parameters:
//      hWnd
//      message
//      wParam
//      lParam
//
//  Returns:
//
//
//

LONG FAR PASCAL
MainWndProc (HWND hWnd, UINT msg, UINT wParam, LPARAM lParam)
{
    CMC_return_code ulResult;
    CMC_boolean UI_available;
    CMC_message far *lpmsg;
    ULONG cNewRecips;
    CMC_recipient FAR *lpNewRecips;
    CMC_extension ext;
    char *szFoo[2];

    switch (msg)
    {
    case WM_COMMAND:
        switch (LOWORD (wParam)) {
        case IDM_LOGON:
            if (!lhSession) {
                if ( (ulResult = CMCQueryConfiguration(
                     (CMC_session_id) NULL, // no session handle yet!
                    CMC_CONFIG_UI_AVAIL, // Make sure UI is available
                    &UI_available, // return value
                    NULL))==CMC_SUCCESS) { // no extensions

                    SecureMenu(hWnd, TRUE);

                    if ((ulResult = CMCLogon (NULL,  // Default service
                           NULL,  // Prompt for username
                           NULL,  // Prompt for password
                           (CMC_enum)NULL, // Default Character set
                           (CMC_ui_id) NULL, // Default UI ID
                           CMC_VERSION,  // Version 1 CMC calls
                           CMC_LOGON_UI_ALLOWED | CMC_ERROR_UI_ALLOWED, // full logon and allow errors
                           &lhSession, // returned session id
                           NULL))==CMC_SUCCESS) { // no extensions

                        ToggleMenuState (hWnd, TRUE);
                    } else {
                        SecureMenu(hWnd, FALSE);
                        lhSession = 0;
                        MakeMessageBox (hWnd, ulResult, IDS_LOGONFAIL, MBS_ERROR);
                    }
                }
            }
            break;

        case IDM_LOGOFF:
            if (lhSession) {
               CMCLogoff (lhSession, (CMC_ui_id) NULL, 0, 0);
               ToggleMenuState (hWnd, FALSE);
                lhSession = 0;
            }
            break;

        case IDM_COMPOSE_CUSTOM:
            DialogBox (hInst, "ComposeNote", hWnd, ComposeDlgProc);
            break;

        case IDM_COMPOSE_CMC:
            lpmsg = (CMC_message far *)GlobalAllocPtr(GPTR, sizeof(CMC_message));
            ulResult = CMCSend(lhSession, 
                            lpmsg, 
                            CMC_SEND_UI_REQUESTED | CMC_ERROR_UI_ALLOWED,
                            (CMC_ui_id)hWnd, NULL);
            if (ulResult != CMC_SUCCESS)
            {
                if (ulResult != CMC_E_USER_CANCEL)
                MakeMessageBox (hWnd, ulResult, IDS_SENDERROR, MBS_ERROR);
            }
            else
            GlobalFreePtr(lpmsg);
            break;

        case IDM_READ:
            DialogBox (hInst, "InBox", hWnd, InBoxDlgProc);
            break;

        case IDM_ADDRBOOK:
            if (lhSession)
            {
                szFoo[0] = "";
                szFoo[1] = "";
                cNewRecips = 0;
                ext.item_code = CMC_X_MS_ADDRESS_UI;
                ext.item_data = 0;
                ext.item_reference = szFoo;
                ext.extension_flags = CMC_EXT_LAST_ELEMENT;
                ulResult = CMCLookUp (lhSession, NULL, CMC_LOOKUP_ADDRESSING_UI,
                    (CMC_ui_id)hWnd, &cNewRecips, &lpNewRecips, &ext);

                if (ulResult != CMC_SUCCESS)
                {
                    if (ulResult != CMC_E_USER_CANCEL)
                        MakeMessageBox (hWnd, ulResult, IDS_ADDRBOOKFAIL, MBS_ERROR);
                }
            }
            break;

        case IDM_ABOUT:
            DialogBox (hInst, "AboutBox", hWnd, AboutDlgProc);
            break;

        case IDM_EXIT:
            if (lhSession) {
               CMCLogoff (lhSession, (CMC_ui_id) NULL, 0, 0);
               ToggleMenuState (hWnd, FALSE);
                lhSession = 0;
            }

            PostQuitMessage (0);
            break;

        default:
            return (DefWindowProc (hWnd, msg, wParam, lParam));
        }
        break;

    case WM_ENDSESSION:
        DestroyWindow (hWnd);
        break;

    case WM_CLOSE:
    case WM_DESTROY:
        if (lhSession) {
           CMCLogoff (lhSession, (CMC_ui_id) NULL, 0, 0);
           ToggleMenuState (hWnd, FALSE);
            lhSession = 0;
        }
        PostQuitMessage (0);
        break;

    default:
        return (DefWindowProc (hWnd, msg, wParam, lParam));
    }
    return FALSE;
}

//
//  AboutDlgProc
//
//  Purpose:
//      About box dialog procedure
//
//  Parameters:
//      hDlg
//      message
//      wParam
//      lParam
//
//  Returns:
//      True/False
//
//

BOOL FAR PASCAL
AboutDlgProc (HWND hDlg, UINT msg, UINT wParam, LONG lParam)
{
    char    rgchVersion[80];

    switch (msg)
    {
    case WM_INITDIALOG:
        sprintf(rgchVersion, "Version %01.1f", ((float)CMC_VERSION)/100);
        SetDlgItemText(hDlg, IDC_VERSION, rgchVersion);
        return TRUE;

    case WM_COMMAND:
        if (wParam == IDOK || wParam == IDCANCEL)
        {
            EndDialog (hDlg, TRUE);
            return TRUE;
        }
        break;
    }
    return FALSE;
}


//
//  ComposeDlgProc
//
//  Purpose:
//      Dialog procedure for the ComposeNote dialog.
//
//  Parameters:
//      hDlg
//      message
//      wParam
//      lParam
//
//  Returns:
//      True/False
//
//

BOOL FAR PASCAL
ComposeDlgProc (HWND hDlg, UINT msg, UINT wParam, LONG lParam)
{
    char szUnResNames[TO_EDIT_MAX];
    char szDisplayNames[TO_EDIT_MAX];
    char szAttach[FILE_ATTACH_MAX];
    BOOL fUnResTo, fUnResCc;
    LONG cb, cLines;
    ULONG ulResult;
    HCURSOR hOldCur;
    static CMC_string lpszSubject;
    static CMC_string lpszTextNote;
    static ULONG cRecips;
    static ULONG cNewRecips;
    static ULONG cAttach;
    static CMC_recipient FAR *lpRecips;
    static CMC_recipient FAR *lpNewRecips;
    static CMC_attachment FAR *lpAttach;
    CMC_extension ext;
    char *szFoo[2]={"",""};

    switch (msg) {
    case WM_INITDIALOG:
        if (CmcMsg)
        {
            //  ComposeNote is being called to either forward or reply
            //  to a message in the Inbox.  So, we'll initialize the
            //  ComposeNote form with data from the global CMC_message

            lpszSubject = CmcMsg->subject;
            lpszTextNote = CmcMsg->text_note;

            lpRecips = CmcMsg->recipients;
            lpAttach = CmcMsg->attachments;

            if (lpRecips == NULL)
            {
              cRecips = 0;
            }
            else
            {
                cRecips = 0;
                while(!(lpRecips[cRecips].recip_flags & CMC_RECIP_LAST_ELEMENT))
                    cRecips++;

                cRecips++;
            }

            if (lpAttach == NULL)
            {
              cAttach = 0;
            }
            else
            {
                cAttach = 0;
                while(!(lpAttach[cAttach].attach_flags & CMC_ATT_LAST_ELEMENT))
                    cAttach++;

                cAttach++;
            }

            if (cRecips)
            {
                MakeDisplayNameStr (szDisplayNames, CMC_ROLE_TO, cRecips, lpRecips);
                if (*szDisplayNames)
                    SetDlgItemText (hDlg, IDC_TO, szDisplayNames);

                MakeDisplayNameStr (szDisplayNames, CMC_ROLE_CC, cRecips, lpRecips);
                if (*szDisplayNames)
                    SetDlgItemText (hDlg, IDC_CC, szDisplayNames);
            }
            SetDlgItemText (hDlg, IDC_SUBJECT, CmcMsg->subject);
            SetDlgItemText (hDlg, IDC_NOTE, CmcMsg->text_note);

            SendDlgItemMessage (hDlg, IDC_TO, EM_SETMODIFY, FALSE, 0);
            SendDlgItemMessage (hDlg, IDC_CC, EM_SETMODIFY, FALSE, 0);
            SendDlgItemMessage (hDlg, IDC_SUBJECT, EM_SETMODIFY, FALSE, 0);
            SendDlgItemMessage (hDlg, IDC_NOTE, EM_SETMODIFY, FALSE, 0);
            if(cRecips)
                SetFocus (GetDlgItem (hDlg, IDC_NOTE));
            else
                SetFocus (GetDlgItem (hDlg, IDC_TO));
        }

        else
        {
            if(CmcMsg)
                PvFree(CmcMsg);

            CmcMsg = (CMC_message *)PvAlloc(sizeof(CMC_message));
            if (!CmcMsg)
                goto cleanup;

            _fmemset (CmcMsg, 0, sizeof (CMC_message));

            lpszSubject = NULL;
            lpszTextNote = NULL;
            cRecips = 0;
            cAttach = 0;
            lpRecips = NULL;
            lpNewRecips = NULL;
            lpAttach = NULL;

            SetFocus (GetDlgItem (hDlg, IDC_TO));
        }
        return FALSE;

    case WM_COMMAND:
        switch (LOWORD (wParam))
        {
        case IDC_ATTACH:
            if (GetNextFile (hDlg, (ULONG) -1, &cAttach, &lpAttach) == CMC_SUCCESS)
            {
                //   Now, send a little render message to the text_note edit

                wsprintf (szAttach, "<<File: %s>>",
                    lpAttach[cAttach - 1].attach_title);

                SendDlgItemMessage (hDlg, IDC_NOTE, EM_REPLACESEL, 0,
                    (LPARAM) ((LPSTR) szAttach));
            }
            break;

        case IDC_ADDRBOOK:
        
            // To do:
            // Add a parameter to ResolveFriendlyNames to prepare unresolved names
            // but only as DN strings in recip list.
            // When call returns from Address, rebuild the edit fields.

            cNewRecips = 0;
            ext.item_code = CMC_X_MS_ADDRESS_UI;
            ext.item_data = 2;
            ext.item_reference = szFoo;
            ext.extension_flags = CMC_EXT_LAST_ELEMENT;
            
            // include any recipients we've already resolved.
            
            ulResult = CMCLookUp (lhSession, lpRecips, CMC_LOOKUP_ADDRESSING_UI,
                          (CMC_ui_id)hDlg, &cNewRecips, &lpNewRecips, &ext);


//            cNewRecips = 0; // set to NULL to allow maximum number of names to be allocated
//            ulResult = CMCLookUp (lhSession, lpRecips, CMC_LOOKUP_ADDRESSING_UI,
//                                  (CMC_ui_id)hDlg, &cNewRecips, &lpNewRecips, NULL);

            if (ulResult)
            {
                if (ulResult != CMC_E_USER_CANCEL)
                    MakeMessageBox (hDlg, ulResult, IDS_ADDRBOOKFAIL, MBS_ERROR);
            }
            else
            {
                if (cNewRecips)
                {
                    PvFree(lpRecips);
                    cRecips = 0;

                    lpRecips = (CMC_recipient far *)PvAlloc(cNewRecips * sizeof(CMC_recipient));

                    while(cRecips < cNewRecips)
                    {
                        if(CopyRecipient(lpRecips, &lpRecips[cRecips],
                                         &lpNewRecips[cRecips]))
                        {
                            PvFree(lpRecips);
                            lpRecips = NULL;
                            cRecips = 0;
                            break;
                        }
                        cRecips++;
                    }

                    CMCFree(lpNewRecips);
                    lpNewRecips = NULL;
                    cNewRecips = 0;

                    MakeDisplayNameStr(szDisplayNames, CMC_ROLE_TO,
                                       cRecips, lpRecips);
                    if (*szDisplayNames)
                        SetDlgItemText (hDlg, IDC_TO, szDisplayNames);

                    MakeDisplayNameStr(szDisplayNames, CMC_ROLE_CC,
                                       cRecips, lpRecips);
                    if (*szDisplayNames)
                        SetDlgItemText (hDlg, IDC_CC, szDisplayNames);

                    SendDlgItemMessage (hDlg, IDC_TO, EM_SETMODIFY, FALSE, 0);
                    SendDlgItemMessage (hDlg, IDC_CC, EM_SETMODIFY, FALSE, 0);
                }
            }
            break;

        case IDC_OPTIONS:
            DialogBox (hInst, "Options", hDlg, OptionsDlgProc);
            break;

        case IDC_SEND:
        case IDC_RESOLVE:
            fUnResTo = FALSE;
            fUnResCc = FALSE;

            hOldCur = SetCursor(hWaitCur);

            //   Get the names from the To: field and resolve them first

            if (SendDlgItemMessage (hDlg, IDC_TO, EM_GETMODIFY, 0, 0) &&
                (cb = SendDlgItemMessage (hDlg, IDC_TO, WM_GETTEXT,
                    (WPARAM)sizeof(szUnResNames),
                    (LPARAM) (LPSTR) szUnResNames)))
            {
                if (!ResolveFriendlyNames (hDlg, szUnResNames, CMC_ROLE_TO,
                        &cRecips, &lpRecips))
                {
                    MakeDisplayNameStr (szDisplayNames, CMC_ROLE_TO,
                        cRecips, lpRecips);
                    if (*szDisplayNames)
                    {
                        if (*szUnResNames)
                        {
                            lstrcat (szDisplayNames, "; ");
                            lstrcat (szDisplayNames, szUnResNames);
                            fUnResTo = TRUE;
                        }

                        SetDlgItemText (hDlg, IDC_TO, szDisplayNames);
                    }
                    else
                    {
                        if (*szUnResNames)
                        {
                            SetDlgItemText (hDlg, IDC_TO, szUnResNames);
                            fUnResTo = TRUE;
                        }
                    }
                }
                SendDlgItemMessage (hDlg, IDC_TO, EM_SETMODIFY, FALSE, 0);
            }

            //   Now, get the names from the Cc: field and resolve them

            if (SendDlgItemMessage (hDlg, IDC_CC, EM_GETMODIFY, 0, 0) &&
                (cb = SendDlgItemMessage (hDlg, IDC_CC, WM_GETTEXT,
                    (WPARAM)sizeof(szUnResNames), (LPARAM)(LPSTR)szUnResNames)))
            {
                if (!ResolveFriendlyNames (hDlg, szUnResNames, CMC_ROLE_CC,
                        &cRecips, &lpRecips))
                {
                    MakeDisplayNameStr (szDisplayNames, CMC_ROLE_CC,
                        cRecips, lpRecips);
                    if (*szDisplayNames)
                    {
                        if (*szUnResNames)
                        {
                            lstrcat (szDisplayNames, "; ");
                            lstrcat (szDisplayNames, szUnResNames);
                            fUnResCc = TRUE;
                        }

                        SetDlgItemText (hDlg, IDC_CC, szDisplayNames);
                    }
                    else
                    {
                        if (*szUnResNames)
                        {
                            SetDlgItemText (hDlg, IDC_CC, szUnResNames);
                            fUnResCc = TRUE;
                        }
                    }
                }
                SendDlgItemMessage (hDlg, IDC_CC, EM_SETMODIFY, FALSE, 0);
            }

            //   If we were just Resolving Names then we can leave now

            if (LOWORD (wParam) == IDC_RESOLVE)
            {
                SetCursor(hOldCur);
                break;
            }

            if (cRecips == 0 || fUnResTo || fUnResCc)
            {
                if (!cRecips)
                    MakeMessageBox (hDlg, 0, IDS_NORECIPS, MBS_OOPS);

                if (fUnResTo)
                    SetFocus (GetDlgItem (hDlg, IDC_TO));
                else if (fUnResCc)
                    SetFocus (GetDlgItem (hDlg, IDC_CC));
                else
                    SetFocus (GetDlgItem (hDlg, IDC_TO));

                SetCursor(hOldCur);
                break;
            }

            //   Everything is OK so far, lets get the Subject
            //   and the text_note and try to send the message.

            //   Get Subject from Edit

            if (SendDlgItemMessage (hDlg, IDC_SUBJECT, EM_GETMODIFY, 0, 0))
            {
                cb = SendDlgItemMessage (hDlg, IDC_SUBJECT, EM_LINELENGTH, 0, 0L);

                CMCFree (lpszSubject);
                lpszSubject = (LPSTR)PvAlloc(cb + 1);
                if (!lpszSubject)
                    goto cleanup;

                GetDlgItemText (hDlg, IDC_SUBJECT, lpszSubject, (int)cb+1);
            }

            //   Get the text_note from Edit

            if (SendDlgItemMessage (hDlg, IDC_NOTE, EM_GETMODIFY, 0, 0))
            {
                cLines = SendDlgItemMessage (hDlg, IDC_NOTE,
                    EM_GETLINECOUNT, 0, 0L);

                if (cLines)
                {
                    //   Get the total number of bytes in the multi-line

                    cb = SendDlgItemMessage (hDlg, IDC_NOTE, EM_LINEINDEX,
                        (WPARAM) cLines - 1, 0L);
                    cb += SendDlgItemMessage (hDlg, IDC_NOTE, EM_LINELENGTH,
                        (WPARAM)cb, 0L);

                    //   The next line is to account for CR-LF pairs per line.

                    cb += cLines * 2;

                    CMCFree (lpszTextNote);
                    lpszTextNote = (LPSTR)PvAlloc(cb + 1);
                    if (!lpszTextNote)
                        goto cleanup;

                    //   Get the Note Text from the edit

                    GetDlgItemText (hDlg, IDC_NOTE, lpszTextNote, (int)cb);
                }
                else
                {
                    //   Make an empty string for text_note

                    lpszTextNote = (LPSTR)PvAlloc(1);
                    *lpszTextNote = '\0';
                }
            }

            CmcMsg->subject = lpszSubject;
            CmcMsg->text_note = lpszTextNote;
            CmcMsg->recipients = lpRecips;
            CmcMsg->attachments = lpAttach;
            CmcMsg->message_extensions = extMsgOpt;

            ulResult = CMCSend(lhSession, CmcMsg, CMC_ERROR_UI_ALLOWED,
                               (CMC_ui_id)hDlg, (CMC_extension far *)NULL);

            LogSendMail(ulResult);

            if (ulResult)
            {
                MakeMessageBox (hDlg, ulResult, IDS_SENDERROR, MBS_ERROR);
                SetCursor(hOldCur);
                break;
            }
cleanup:
        case IDCANCEL:
            SetCursor(hOldCur);
            PvFree(CmcMsg->message_type);
            PvFree(CmcMsg);
            PvFree(lpRecips);
            PvFree(lpAttach);
            PvFree(lpszSubject);
            PvFree(lpszTextNote);
            CmcMsg = NULL;

            EndDialog (hDlg, TRUE);
            return TRUE;
            break;

        default:
            break;
        }
        break;
    }
    return FALSE;
}

/*
 -  OptionsDlgProc
 -
 *  Purpose:
 *      Message Options dialog procedure
 *
 *  Parameters:
 *      hDlg
 *      message
 *      wParam
 *      lParam
 *
 *  Returns:
 *      True/False
 *
 */

BOOL FAR PASCAL
OptionsDlgProc (HWND hDlg, UINT msg, UINT wParam, LONG lParam)
{
    switch (msg)
    {
    case WM_INITDIALOG:
        CheckDlgButton (hDlg, IDC_RETURN,
            (UINT)(extMsgOpt[1].item_data & (CMC_uint32)CMC_X_MS_MSG_RECEIPT_REQ));

        switch(extMsgOpt[0].item_data)
        {
        case CMC_X_COM_URGENT:
            CheckRadioButton(hDlg, IDC_URGENT, IDC_LOW, IDC_URGENT);
            break;

        case CMC_X_COM_NORMAL:
            CheckRadioButton(hDlg, IDC_URGENT, IDC_LOW, IDC_NORMAL);
            break;

        case CMC_X_COM_LOW:
            CheckRadioButton(hDlg, IDC_URGENT, IDC_LOW, IDC_LOW);
            break;
        }
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD (wParam))
        {
        case IDC_RETURN:
            CheckDlgButton(hDlg, IDC_RETURN,
                         !IsDlgButtonChecked(hDlg, IDC_RETURN));
            break;

        case IDC_URGENT:
            CheckRadioButton(hDlg, IDC_URGENT, IDC_LOW, IDC_URGENT);
            extMsgOpt[0].item_data = CMC_X_COM_URGENT;
            break;

        case IDC_NORMAL:
            CheckRadioButton(hDlg, IDC_URGENT, IDC_LOW, IDC_NORMAL);
            extMsgOpt[0].item_data = CMC_X_COM_NORMAL;
            break;

        case IDC_LOW:
            CheckRadioButton(hDlg, IDC_URGENT, IDC_LOW, IDC_LOW);
            extMsgOpt[0].item_data = CMC_X_COM_LOW;
            break;

        case IDOK:
            if (IsDlgButtonChecked (hDlg, IDC_RETURN))
                extMsgOpt[1].item_data |= CMC_X_MS_MSG_RECEIPT_REQ;
            else
                extMsgOpt[1].item_data &= ~CMC_X_MS_MSG_RECEIPT_REQ;

        case IDCANCEL:
            EndDialog (hDlg, TRUE);
            return TRUE;
        }
        break;
    }
    return FALSE;
}


//
//  InBoxDlgProc
//
//  Purpose:
//      Dialog procedure for the InBox dialog.
//
//  Parameters:
//      hDlg
//      message
//      wParam
//      lParam
//
//  Returns:
//      True/False
//


BOOL FAR PASCAL
InBoxDlgProc (HWND hDlg, UINT msg, UINT wParam, LONG lParam)
{
    MEASUREITEMSTRUCT* pmis;
    DRAWITEMSTRUCT *pdis;
    CMC_message_summary far * lpMsgSum = NULL;
    LPMSGID lpMsgNode;
    static LPMSGID lpMsgIdList = NULL;
    CMC_return_code ulResult;
    WORD nIndex;
    RECT Rect;
    HCURSOR hOldCur;

    CMC_uint32 iCount = 0;
    CMC_uint32 i;

    switch (msg)
    {
    case WM_INITDIALOG:
        hOldCur = SetCursor(hWaitCur);

        //   Populate List Box with all messages in InBox.

        ulResult = CMCList(lhSession, NULL, (CMC_flags) 0, NULL,
                           &iCount, (CMC_ui_id)hDlg, &lpMsgSum, NULL);

        if (ulResult == CMC_SUCCESS)
        {
            for (i = 0; i < iCount; i++)
            {
                lpMsgNode = MakeMsgNode (&lpMsgSum[i]);

                if (lpMsgNode)
                {
                    InsertMsgNode (lpMsgNode, &lpMsgIdList);

                    SendDlgItemMessage (hDlg, IDC_MSG, LB_ADDSTRING,
                        0, (LONG) lpMsgNode);
                }
            }
            CMCFree (lpMsgSum);
        }
        else
        {
            MakeMessageBox(hDlg, ulResult, IDS_READFAIL, MBS_ERROR);
        }

        SetCursor(hOldCur);
        SetFocus (GetDlgItem (hDlg, IDC_MSG));
        return TRUE;
        break;

    case WM_SETFOCUS:
        SetFocus (GetDlgItem (hDlg, IDC_MSG));
        break;

    case WM_MEASUREITEM:
        //   Sets the height of the owner-drawn List-Box
        pmis = (MEASUREITEMSTRUCT *) lParam;
        pmis->itemHeight = 15;
        break;

    case WM_DRAWITEM:
        pdis = (DRAWITEMSTRUCT *) lParam;
        DrawMsgItem (pdis);
        break;

    case WM_DELETEITEM:
        //   This message is handled by the IDC_DELETE message
        return TRUE;
        break;

    case WM_COMMAND:
        switch (LOWORD (wParam))
        {
        case IDC_NEW:
            hOldCur = SetCursor(hWaitCur);

            ulResult = CMCList(lhSession, NULL, CMC_LIST_UNREAD_ONLY, NULL,
                               &iCount, (CMC_ui_id)hDlg, &lpMsgSum, NULL);

            if (ulResult == CMC_SUCCESS) {
                for (i = 0; i < iCount; i++) {
                    if (!FindNode(lpMsgIdList,lpMsgSum[i].message_reference))
                    {
                        lpMsgNode = MakeMsgNode (&lpMsgSum[i]);

                        if (lpMsgNode)
                        {
                            InsertMsgNode (lpMsgNode, &lpMsgIdList);

                            SendDlgItemMessage (hDlg, IDC_MSG, LB_ADDSTRING,
                                0, (LONG) lpMsgNode);
                        }
                    }
                }
                CMCFree (lpMsgSum);
            }

            SetCursor(hOldCur);
            break;

        case IDC_MSG:
#ifdef _WIN32
            if(HIWORD(wParam) != LBN_DBLCLK)
#else
            if(HIWORD(lParam) != LBN_DBLCLK)
#endif
                break;

        case IDC_READ:
            nIndex = (WORD) SendDlgItemMessage (hDlg, IDC_MSG, LB_GETCURSEL, 0, 0);

            if (nIndex == LB_ERR)
                break;

            lpReadMsgNode = (LPMSGID) SendDlgItemMessage(hDlg, IDC_MSG,
                                                    LB_GETITEMDATA, nIndex, 0L);

            if (lpReadMsgNode == (LPMSGID) LB_ERR || !lpReadMsgNode) // Nothing is selected
                break;
            else
                DialogBox(hInst, "ReadNote", hDlg, ReadMailDlgProc);

            //   Update the Messages List-Box with new icon

            SendDlgItemMessage (hDlg, IDC_MSG, LB_GETITEMRECT,
                                (WPARAM)nIndex, (LPARAM)(RECT far *)&Rect);
            InvalidateRect(GetDlgItem(hDlg, IDC_MSG), &Rect, FALSE);
            break;

        case IDC_DELETE:
            nIndex = (WORD) SendDlgItemMessage (hDlg, IDC_MSG, LB_GETCURSEL,
                                                (WPARAM) 0, (LPARAM) 0);

            if (nIndex == LB_ERR)
                break;

            lpMsgNode = (LPMSGID) SendDlgItemMessage (hDlg, IDC_MSG,
                                                      LB_GETITEMDATA, nIndex, 0);

            if (lpMsgNode == (LPMSGID) LB_ERR || !lpMsgNode) // Nothing is selected
                break;
            else
            {
                ulResult = CMCActOn(lhSession, lpMsgNode->message_reference,
                                    CMC_ACT_ON_DELETE, CMC_ERROR_UI_ALLOWED,
                                    (CMC_ui_id)hDlg, NULL);

                DeleteMsgNode (lpMsgNode, &lpMsgIdList);
            }

            SendDlgItemMessage (hDlg, IDC_MSG, LB_DELETESTRING, nIndex, 0);
            break;

        case IDC_CLOSE:
        case IDCANCEL:
            FreeMsgList (lpMsgIdList);
            lpMsgIdList = NULL;
            EndDialog (hDlg, TRUE);
            return TRUE;
            break;

        default:
            break;
        }
        break;
    }

    return FALSE;
}


//
//  ReadMailDlgProc
//
//  Purpose:
//      Dialog procedure for the ReadMail dilaog.
//
//  Parameters:
//      hDlg
//      message
//      wParam
//      lParam
//
//  Returns:
//      True/False
//

BOOL FAR PASCAL
ReadMailDlgProc (HWND hDlg, UINT msg, UINT wParam, LONG lParam)
{
    ULONG ulResult;
    char szTo[TO_EDIT_MAX];
    char szCc[TO_EDIT_MAX];
    char szChangeMsg[512];
    ULONG idx;
    static CMC_message far *lpReadMsg;
    char lpszDateDisplay[TO_EDIT_MAX];
    static ULONG cRecips;
    static ULONG cNewRecips;
    static ULONG cAttach;
    static CMC_recipient FAR *lpRecips;
    static CMC_recipient FAR *lpNewRecips;
    static CMC_attachment FAR *lpAttach;
    CMC_return_code rc;
    OFSTRUCT ofs;

    switch (msg)
    {
    case WM_INITDIALOG:
        ulResult = CMCRead(lhSession, lpReadMsgNode->message_reference,
                        CMC_ERROR_UI_ALLOWED, &lpReadMsg, (CMC_ui_id)hDlg, NULL);
        if (ulResult)
        {
            MakeMessageBox(hDlg, ulResult, IDS_READFAIL, MBS_ERROR);
            EndDialog (hDlg, TRUE);
            return TRUE;
        }

        lpReadMsgNode->fRead = TRUE;

        szTo[0] = '\0';
        szCc[0] = '\0';

        idx = 0;
        do
        {
            if (lpReadMsg->recipients[idx].role == CMC_ROLE_TO)
            {
                lstrcat (szTo, lpReadMsg->recipients[idx].name);
                lstrcat (szTo, "; ");
            }
            else if (lpReadMsg->recipients[idx].role == CMC_ROLE_CC)
            {
                lstrcat (szCc, lpReadMsg->recipients[idx].name);
                lstrcat (szCc, "; ");
            }
            else
            {
                //   Must be Bcc, lets ignore it!
            }

        }while(!(lpReadMsg->recipients[idx++].recip_flags & CMC_RECIP_LAST_ELEMENT));

        if(*szTo)
            szTo[lstrlen (szTo) - 2] = '\0';
        if(*szCc)
            szCc[lstrlen (szCc) - 2] = '\0';

        SetDlgItemText (hDlg, IDC_RFROM,
            (lpReadMsgNode->from ? lpReadMsgNode->from : ""));
        ConvertDateRec (&lpReadMsgNode->time_sent,
            lpszDateDisplay);

        SetDlgItemText (hDlg, IDC_RDATE,  (lpszDateDisplay ? lpszDateDisplay : ""));
        SetDlgItemText (hDlg, IDC_RTO, szTo);
        SetDlgItemText (hDlg, IDC_RCC, szCc);
        SetDlgItemText (hDlg, IDC_RSUBJECT, (lpReadMsg->subject ? lpReadMsg->subject : ""));
        SetDlgItemText (hDlg, IDC_READNOTE, (lpReadMsg->text_note ? lpReadMsg->text_note : ""));

        if (!lpReadMsg->attachments)
        {
            EnableWindow (GetDlgItem (hDlg, IDC_SAVEATTACH), FALSE);
            EnableWindow (GetDlgItem (hDlg, IDC_ATTACHMENT), FALSE);
            EnableWindow (GetDlgItem (hDlg, IDT_ATTACHMENT), FALSE);
        }
        else
        {
            idx = 0;
            do
            {
                if (lpReadMsg->attachments[idx].attach_title)
                    SendDlgItemMessage(hDlg, IDC_ATTACHMENT, LB_ADDSTRING, 0,
                        (LPARAM)lpReadMsg->attachments[idx].attach_title);
            }while(!(lpReadMsg->attachments[idx++].attach_flags & CMC_ATT_LAST_ELEMENT));

            SendDlgItemMessage(hDlg, IDC_ATTACHMENT, LB_SETCURSEL, 0, 0L);
        }

        SetFocus (GetDlgItem (hDlg, IDC_READNOTE));
        return FALSE;

    case WM_COMMAND:
        switch (LOWORD (wParam))
        {
        case IDC_SAVECHANGES:
            if (SendDlgItemMessage (hDlg, IDC_READNOTE, EM_GETMODIFY, 0, 0))
                ulResult = SaveMsgChanges (hDlg, lpReadMsg);
            SendDlgItemMessage (hDlg, IDC_READNOTE, EM_SETMODIFY, 0, 0);
            break;

        case IDC_ATTACHMENT:
#ifdef _WIN32
            if(HIWORD(wParam) != LBN_DBLCLK)
#else
            if(HIWORD(lParam) != LBN_DBLCLK)
#endif
                break;

        case IDC_SAVEATTACH:
            idx = SendDlgItemMessage(hDlg, IDC_ATTACHMENT, LB_GETCURSEL, 0, 0L);

            if(idx != LB_ERR)
            {
                SaveFileAttachments(hDlg, &lpReadMsg->attachments[idx]);
                SetFocus(GetDlgItem (hDlg, IDC_ATTACHMENT));
                return FALSE;

            }
            break;

        case IDC_REPLY:
        case IDC_REPLYALL:
        case IDC_FORWARD:
            if(rc = MakeNewMessage (lpReadMsg, LOWORD (wParam)))
                MakeMessageBox(hDlg, rc, IDS_MAKENEWFAIL, MBS_ERROR);

            if(rc = CMCSend(lhSession, CmcMsg, CMC_SEND_UI_REQUESTED | CMC_ERROR_UI_ALLOWED,
                    (CMC_ui_id)hDlg, NULL))
                MakeMessageBox(hDlg, rc, IDS_SENDERROR, MBS_ERROR);

            PvFree(CmcMsg->message_type);
            PvFree(CmcMsg->subject);
            PvFree(CmcMsg->text_note);
            PvFree(CmcMsg->recipients);
            PvFree(CmcMsg->attachments);
            PvFree(CmcMsg);
            CmcMsg = NULL;
            break;

        case IDCANCEL:
            if (SendDlgItemMessage (hDlg, IDC_READNOTE, EM_GETMODIFY, 0, 0))
            {
                wsprintf (szChangeMsg, "Save changes to: '%s' in Inbox?",
                    (lpReadMsg->subject ? lpReadMsg->subject : ""));

                if(MessageBox (hDlg, szChangeMsg, "Mail", MB_YESNO) == IDYES)
                {
                    ulResult = SaveMsgChanges (hDlg, lpReadMsg);
                }
            }

            //   If there were file attachments, then delete the temps

            if(lpReadMsg->attachments)
            {
                idx = 0;
                do
                {
                    if (lpReadMsg->attachments[idx].attach_filename)
                        OpenFile(lpReadMsg->attachments[idx].attach_filename, &ofs, OF_DELETE);

                }while(!(lpReadMsg->attachments[idx++].attach_flags & CMC_ATT_LAST_ELEMENT));
            }

            CMCFree (lpReadMsg);
            lpReadMsg = NULL;
            EndDialog (hDlg, TRUE);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

//
//  MakeMessageBox
//
//  Purpose:
//      Gets resource string and displays an error message box.
//
//  Parameters:
//      hWnd            - Handle to parent window
//      idString        - Resource ID of message in StringTable
//
//  Returns:
//      Void
//
//

void
MakeMessageBox (HWND hWnd, CMC_return_code ulResult, UINT idString, UINT fStyle)
{
    char szMessage[512];
    char szCmcReturn[256];
    UINT uResult;

    LoadString (hInst, idString, szMessage, sizeof(szMessage)-sizeof(szCmcReturn)-1);

    if (ulResult)
    {
        uResult = (UINT) ulResult;
        LoadString (hInst, uResult, szCmcReturn, sizeof(szCmcReturn)-1);
        lstrcat (szMessage, "\nReturn Code: ");
        lstrcat (szMessage, szCmcReturn);
    }

    MessageBox (hWnd, szMessage, "Problem", fStyle);
}


//
//  ResolveFriendlyNames
//
//  Purpose:
//      Helper function to convert a string of ';' delimited friendly
//      names into an array of CMC_recipients.
//
//  Side Effects:
//      The display string passed in is modified to contain the
//      friendly names of the mail users as found in the sample
//      address book.
//
//  Note:
//      Duplicate names in the address book will result in undefined
//      behavior.
//
//  Parameters:
//      hWnd                - Handle to parent window
//      lpszDisplayNames    - string of ';' delimited user names
//      ulRecipRole         - either CMC_ROLE_TO, CMC_ROLE_CC, or CMC_BCC
//      lpcRecips           - Address of recipient count to be returned
//      lppRecips           - Address of recipient array to be returned
//
//  Return:
//      ulResult


CMC_return_code
ResolveFriendlyNames(HWND hWnd, LPSTR lpszDisplayNames, CMC_enum ulRecipRole,
                     ULONG * lpcRecips, CMC_recipient FAR * * lppRecips)
{
    char szResolve[TO_EDIT_MAX];
    LPSTR lpszNameToken;
    ULONG cRecips = 0;
    ULONG cFails = 0;
    ULONG idx;
    CMC_return_code ulResult;
    CMC_recipient Recip;
    CMC_recipient FAR * lpNewRecip;
    CMC_recipient FAR * lpRecipList;
    CMC_uint32 cNewRecip;

    *szResolve = '\0';
    lpszNameToken = _fstrtok (lpszDisplayNames, ";\n");

    while (lpszNameToken)
    {
        //   Strip leading blanks from name

        while (*lpszNameToken == ' ')
            lpszNameToken++;

        //   Check if name has already been resolved

        if (!FNameInList (lpszNameToken, *lpcRecips, *lppRecips))
        {
            lstrcat (szResolve, lpszNameToken);
            lstrcat (szResolve, "; ");
            cRecips++;
        }

        //   Get Next Token

        lpszNameToken = _fstrtok (NULL, ";\n");
    }

    *lpszDisplayNames = '\0';

    if (!szResolve[0])
    {
        ulResult = CMC_SUCCESS;
        goto err;
    }

    szResolve[lstrlen (szResolve) - 2] = '\0';

    lpRecipList = (CMC_recipient *)PvAlloc((cRecips + *lpcRecips) * sizeof (CMC_recipient));
    if (!lpRecipList)
    {
        ulResult = CMC_E_INSUFFICIENT_MEMORY;
        goto err;
    }
    _fmemset (lpRecipList, 0, (UINT)(cRecips + *lpcRecips) * sizeof (CMC_recipient));

    cRecips = 0;

    while (cRecips < *lpcRecips)
    {
        ulResult = CopyRecipient (lpRecipList, &lpRecipList[cRecips],
            *lppRecips + cRecips);

        if (ulResult)
        {
            PvFree(lpRecipList);
            goto err;
        }

        cRecips++;
    }

    PvFree(*lppRecips);

    lpszNameToken = _fstrtok (szResolve, ";\n");

    while (lpszNameToken)
    {
        //   Strip leading blanks

        while (*lpszNameToken == ' ')
            lpszNameToken++;

        cNewRecip = 1; // just looking for one resolved name
        Recip.name      = lpszNameToken;
        Recip.name_type = CMC_TYPE_INDIVIDUAL;
        Recip.role      = ulRecipRole;
        Recip.recip_flags = CMC_RECIP_LAST_ELEMENT;
        Recip.address     = NULL;
        Recip.recip_extensions = NULL;

        ulResult = CMCLookUp(lhSession, (CMC_recipient far *)&Recip,
                             CMC_LOOKUP_RESOLVE_UI | CMC_ERROR_UI_ALLOWED
                             | CMC_LOOKUP_RESOLVE_PREFIX_SEARCH,
                             (CMC_ui_id)hWnd, &cNewRecip, &lpNewRecip, NULL);

        if (ulResult == CMC_SUCCESS)
        {
            lpNewRecip->role = ulRecipRole;
            ulResult = CopyRecipient (lpRecipList, &lpRecipList[cRecips], lpNewRecip);

            CMCFree(lpNewRecip);

            if(ulResult)
                goto cleanup;

            cRecips++;
        }
        else
        {
            MakeMessageBox (NULL, ulResult, IDS_ADDRBOOKFAIL, MBS_ERROR);
            lstrcat (lpszDisplayNames, lpszNameToken);
            lstrcat (lpszDisplayNames, "; ");
            cFails++;
        }
        lpszNameToken = _fstrtok (NULL, ";\n");
    }

    //   if cFails > 0 then we have partial success

    ulResult = CMC_SUCCESS;

    if (cFails)
        MakeMessageBox (hWnd, 0, IDS_UNRESOLVEDNAMES, MBS_INFO);

cleanup:
    /* Re-position our LAST_ELEMENT flag in the list */
    if(*lpcRecips = cRecips)
    {
        for(idx = 0; idx < cRecips-1; idx++)
            lpRecipList[idx].recip_flags &= ~CMC_RECIP_LAST_ELEMENT;
        lpRecipList[idx].recip_flags |= CMC_RECIP_LAST_ELEMENT;

        *lppRecips = lpRecipList;
    }
    else
    {
        *lppRecips = NULL;
        PvFree(lpRecipList);
    }

err:
    if (*lpszDisplayNames)
        lpszDisplayNames[lstrlen (lpszDisplayNames) - 2] = '\0';

    return ulResult;
}


//
//  CopyRecipient
//
//  Purpose:
//      Called in support of ResolveFriendlyNames() to build an array
//      of chained CMC_recipients.
//
//  Parameters:
//      lpParent        - Parent memory that allocations get chained to
//      lpDest          - Destination Recipient
//      lpSrc           - Source Recipient
//
//  Return:
//      ulResult


CMC_return_code
CopyRecipient (CMC_recipient FAR * lpParent,
    CMC_recipient FAR * lpDest,
    CMC_recipient FAR * lpSrc)
{
    ULONG cRecipExt,cRE;
    lpDest->role = lpSrc->role;
    lpDest->name_type = lpSrc->name_type;
    lpDest->recip_flags = lpSrc->recip_flags;


    if (lpSrc->name)
    {
        lpDest->name = (CMC_string)PvAllocMore(lstrlen(lpSrc->name) + 1, lpParent);
        if (!lpDest->name)
                return CMC_E_INSUFFICIENT_MEMORY;

        lstrcpy (lpDest->name, lpSrc->name);
    }
    else
        lpDest->name = NULL;

    if (lpSrc->address)
    {
        lpDest->address = (CMC_string)PvAllocMore(lstrlen(lpSrc->address) + 1, lpParent);
        if (!lpDest->address)
            return CMC_E_INSUFFICIENT_MEMORY;

        lstrcpy (lpDest->address, lpSrc->address);
    }
    else
        lpDest->address = NULL;

    if(lpSrc->recip_extensions && (lpSrc->recip_extensions->item_code == CMC_X_COM_RECIP_ID))
    {

        cRecipExt = 0;
        while (!(lpSrc->recip_extensions[cRecipExt].extension_flags & CMC_EXT_LAST_ELEMENT))
            cRecipExt++;

        cRecipExt++;

        lpDest->recip_extensions = (CMC_extension *)PvAllocMore(sizeof(CMC_extension)*cRecipExt, lpParent);
        if(!lpDest->recip_extensions)
               return CMC_E_INSUFFICIENT_MEMORY;

        for (cRE = 0;cRE < cRecipExt;cRE++)
        {

            lpDest->recip_extensions[cRE].item_reference = \
                   (CMC_buffer)PvAllocMore( sizeof(CMC_message_reference)+
                   lpSrc->recip_extensions[cRE].item_data, lpParent);
            if(!lpDest->recip_extensions[cRE].item_reference)
                return CMC_E_INSUFFICIENT_MEMORY;

            lpDest->recip_extensions[cRE].item_code = CMC_X_COM_RECIP_ID;
            lpDest->recip_extensions[cRE].item_data = lpSrc->recip_extensions[cRE].item_data;
            lpDest->recip_extensions[cRE].extension_flags = lpSrc->recip_extensions[cRE].extension_flags;
            if (lpSrc->recip_extensions[cRE].item_reference)
                _fmemcpy(lpDest->recip_extensions[cRE].item_reference,
                    lpSrc->recip_extensions[cRE].item_reference,
                    sizeof(CMC_message_reference)+(size_t)lpSrc->recip_extensions[cRE].item_data);
            else
                // NULL item_reference (BUG?)
                lpDest->recip_extensions[cRE].item_reference = lpSrc->recip_extensions[cRE].item_reference;

        }

    }
    else
        lpDest->recip_extensions = NULL;

    return CMC_SUCCESS;
}

//
//  GetNextFile
//
//  Purpose:
//      Called when user clicks 'Attach' button in Compose Note form.
//      We will build a chained memory chunk for more than one file
//      attachment so the memory can be freed with a single call to
//      CMCFree.
//
//  Parameters:
//      hWnd            - Window handle of Compose Note dialog
//      nPos            - Render position of attachment in Notetext.
//      lpcAttach       - Pointer to the count of attachments.
//      lppAttach       - Pointer to the CMC_attachment array.
//
//  Return:
//      ulResult.

CMC_return_code
GetNextFile (HWND hWnd, ULONG nPos, ULONG * lpcAttach,
    CMC_attachment FAR * * lppAttach)
{
    CMC_attachment FAR * lpAttach;
    CMC_attachment FAR * lpAttachT;
    OPENFILENAME ofn;
    char szAttachFilename[256] = "";
    char szFilter[256];
    static char szFileTitle[16];
    static char szDirName[256] = "";
    LPSTR lpszEndPath;
    ULONG idx;
    CMC_return_code ulResult = CMC_SUCCESS;

    if (!szDirName[0])
        GetSystemDirectory ((LPSTR) szDirName, 255);
    else
        lstrcpy (szAttachFilename, szFileTitle);

    LoadString(hInst, IDS_FILTER, szFilter, sizeof(szFilter));

    for (idx = 0; szFilter[idx] != '\0'; idx++)
        if (szFilter[idx] == '|')
            szFilter[idx] = '\0';

    ofn.lStructSize = sizeof (OPENFILENAME);
    ofn.hwndOwner = (HWND) NULL;
    ofn.hInstance = (HINSTANCE) NULL;
    ofn.lpstrFilter = szFilter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = 0L;
    ofn.nFilterIndex = 1L;
    ofn.lpstrFile = szAttachFilename;
    ofn.nMaxFile = 256;
    ofn.lpstrFileTitle = szFileTitle;
    ofn.nMaxFileTitle = 16;
    ofn.lpstrInitialDir = szDirName;
    ofn.lpstrTitle = "Attach";
    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    if (!GetOpenFileName (&ofn))
        return CMC_E_USER_CANCEL;

    //   Save the directory for the next time we call this

    lstrcpy (szDirName, szAttachFilename);
    if (lpszEndPath = strstr (szDirName, szFileTitle))
        *(--lpszEndPath) = '\0';

    lpAttach = (CMC_attachment *)PvAlloc((*lpcAttach + 1) * sizeof(CMC_attachment));
    if (!lpAttach)
        goto err;

    _fmemset (lpAttach, 0, ((UINT) *lpcAttach + 1) *sizeof (CMC_attachment));

    lpAttachT = *lppAttach;

    for (idx = 0; idx < *lpcAttach; idx++)
        if(ulResult = CopyAttachment (lpAttach, &lpAttach[idx], &lpAttachT[idx]))
            goto err;

    lpAttach[idx-1].attach_flags &= ~CMC_ATT_LAST_ELEMENT;
    lpAttach[idx].attach_flags = CMC_ATT_LAST_ELEMENT;
    lpAttach[idx].attach_type = NULL;
    lpAttach[idx].attach_extensions = NULL;

    lpAttach[idx].attach_filename = (CMC_string)PvAllocMore(lstrlen(szAttachFilename) + 1,  lpAttach);
    if(!lpAttach[idx].attach_filename)
        goto err;

    lpAttach[idx].attach_title = (CMC_string)PvAllocMore(lstrlen(szFileTitle) + 1, lpAttach);
    if (!lpAttach[idx].attach_title)
        goto err;

    lstrcpy (lpAttach[idx].attach_filename, szAttachFilename);
    lstrcpy (lpAttach[idx].attach_title, szFileTitle);

    PvFree(lpAttachT);

    *lppAttach = lpAttach;
    (*lpcAttach)++;

err:
    if(ulResult)
        PvFree(lpAttach);

    return ulResult;
}


//
//  CopyAttachment
//
//  Purpose:
//      Called in support of GetNextFile() to re-build an array
//      of chained CMC_attachments.
//
//  Parameters:
//      lpParent        - Parent memory that allocations get chained to
//      lpDest          - Destination Recipient
//      lpSrc           - Source Recipient
//
//  Return:
//      Void.

ULONG
CopyAttachment(CMC_attachment FAR * lpParent,
               CMC_attachment FAR * lpDest,
               CMC_attachment FAR * lpSrc)
{
    lpDest->attach_flags = lpSrc->attach_flags;

    if (lpSrc->attach_title)
    {
        lpDest->attach_title = (CMC_string)PvAllocMore(lstrlen(lpSrc->attach_title) + 1, (LPVOID)lpParent);
        if (!lpDest->attach_title)
            return CMC_E_INSUFFICIENT_MEMORY;

        lstrcpy (lpDest->attach_title, lpSrc->attach_title);
    }
    else
        lpDest->attach_title = NULL;

    if (lpSrc->attach_type)
    {
        lpDest->attach_type = (CMC_object_identifier)PvAllocMore(lstrlen(lpSrc->attach_type) + 1, (LPVOID)lpParent);
        if (!lpDest->attach_type)
            return CMC_E_INSUFFICIENT_MEMORY;

        lstrcpy (lpDest->attach_type, lpSrc->attach_type);
    }
    else
        lpDest->attach_type = NULL;

    if (lpSrc->attach_filename)
    {
        lpDest->attach_filename = (CMC_string)PvAllocMore(lstrlen(lpSrc->attach_filename) + 1, (LPVOID)lpParent);
        if (!lpDest->attach_filename)
            return CMC_E_INSUFFICIENT_MEMORY;

        lstrcpy (lpDest->attach_filename, lpSrc->attach_filename);
    }
    else
        lpDest->attach_filename = NULL;

    lpDest->attach_extensions = NULL;

    return CMC_SUCCESS;
}


//
//  FNameInList
//
//  Purpose:
//      To find lpszName in an array of recipients.  Used to determine
//      if user name has already been resolved.
//
//  Parameters:
//      lpszName        - Friendly name to search for
//      cRecips         - Count of recipients in lpRecips
//      lpRecips        - Array of CMC_recipients
//
//  Return:
//      TRUE/FALSE


BOOL
FNameInList (LPSTR lpszName, ULONG cRecips, CMC_recipient FAR * lpRecips)
{
    //   Case sensitive compare of each friendly name in list.

    if (!cRecips || !lpRecips)
        return FALSE;

    while (cRecips--)
        if (!lstrcmp (lpszName, lpRecips[cRecips].name))
            return TRUE;

    return FALSE;
}


//
//  DrawMsgItem
//
//  Purpose:
//      Paint the client area of the owner drawn listbox.
//
//  Parameters:
//      pdis        - Pointer to a DRAWITEMSTRUCT
//      cMsgIds     - Count of MsgId structs in List of current messages
//      lpMsgIds    - Pointer to linked-list of MsgIds
//
//  Returns:
//      void
//


void
DrawMsgItem (DRAWITEMSTRUCT * pdis)
{
    LPMSGID lpMsg;
    HBITMAP hBmp;
    char szDateRec[32];
    HBRUSH hSolidBrush, hOldBrush;

    hSolidBrush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
    hOldBrush = SelectObject(pdis->hDC, hSolidBrush);

    if (ODA_DRAWENTIRE & pdis->itemAction)
    {
        //   Clear the item Rectangle

        PatBlt (pdis->hDC, pdis->rcItem.left, pdis->rcItem.top,
            pdis->rcItem.right - pdis->rcItem.left,
            pdis->rcItem.bottom - pdis->rcItem.top, PATCOPY);

        //   Draw the item

        lpMsg = (LPMSGID) pdis->itemData;

        if (lpMsg->fRead)
        {
            if (lpMsg->fHasAttach)
                hBmp = hReadABmp;
            else
                hBmp = hReadBmp;
        }
        else
        {
            if (lpMsg->fHasAttach)
                hBmp = hUnReadABmp;
            else
                hBmp = hUnReadBmp;
        }

        DrawMsgIcon (pdis->hDC, hBmp, pdis->rcItem.left + 2, pdis->rcItem.top,
            pdis->rcItem.left + 18, pdis->rcItem.top + 15);


        // Show originator
        TextOut (pdis->hDC, pdis->rcItem.left + 20, pdis->rcItem.top+2,
            (lpMsg->from ? lpMsg->from : ""),
            lstrlen ((lpMsg->from ? lpMsg->from : "")));


        // Show subject
        TextOut (pdis->hDC, pdis->rcItem.left + 120, pdis->rcItem.top+2,
            (lpMsg->subject ? lpMsg->subject : ""),
            lstrlen ((lpMsg->subject ? lpMsg->subject : "")));

        // Show time sent
        ConvertDateRec (&lpMsg->time_sent, szDateRec);
        TextOut (pdis->hDC, pdis->rcItem.left + 270, pdis->rcItem.top+2,
            szDateRec, lstrlen (szDateRec));

        //   Invert item rectangle if item is selected

        if (ODS_SELECTED & pdis->itemState)
            PatBlt (pdis->hDC, pdis->rcItem.left, pdis->rcItem.top,
                pdis->rcItem.right - pdis->rcItem.left,
                pdis->rcItem.bottom - pdis->rcItem.top, DSTINVERT);

        //   Draw a focus rectangle if item has focus

        if (ODS_FOCUS & pdis->itemState)
            DrawFocusRect (pdis->hDC, &pdis->rcItem);
    }
    else
    {
        //   Invert the item if the selection state is changing

        if (ODA_SELECT & pdis->itemAction)
            PatBlt (pdis->hDC, pdis->rcItem.left, pdis->rcItem.top,
                pdis->rcItem.right - pdis->rcItem.left,
                pdis->rcItem.bottom - pdis->rcItem.top, DSTINVERT);

        //   Draw a focus if the focus state is changing

        if (ODA_FOCUS & pdis->itemAction)
            DrawFocusRect (pdis->hDC, &pdis->rcItem);
    }

    SelectObject(pdis->hDC, hOldBrush);
    DeleteObject(hSolidBrush);
}

//
//  DrawMsgIcon
//
//  Purpose:
//      Paint the client area of an owner drawn List Box.
//
//  Parameters:
//      hDC         - Device context of button to be drawn on
//      hBitMap     - Handle to a bitmap
//      lx          - Upper left x coordinate
//      ly          - Upper left y coordinate
//      lcx         - Width of paint area
//      lcy         - Height of paint area
//
//  Returns:
//      None.
//


void
DrawMsgIcon (HDC hDC, HBITMAP hBmp, int x, int y, int cx, int cy)
{
    HDC hDCMem;
    HBITMAP hBmpOld;

    hDCMem = CreateCompatibleDC (hDC);
    hBmpOld = SelectObject (hDCMem, hBmp);

    if (hBmpOld)
    {
        BitBlt (hDC, x, y, cx, cy, hDCMem, 0, 0, SRCCOPY);
        SelectObject (hDCMem, hBmpOld);
    }

    DeleteDC (hDCMem);
}

//
//  ConvertDateRec
//
//  Purpose:
//      To convert the CMC_time field of a message to a
//      more paletable display format; namely: mm/dd/yy hh:mmAM.
//
//  Parameters:
//      stime         - Original format
//      lpszDateDisplay     - Display format
//
//  Return:
//      Void.


void
ConvertDateRec (CMC_time far *lpTime, LPSTR lpszDateDisplay)
{
    static char szCentury[2][3] =
    {"19", "20"};

    static char szAMPM[2][3] =
    {"AM", "PM"};


    wsprintf (lpszDateDisplay, "%i/%i/%s%2.2i %i:%2.2i%s",
        lpTime->month+1, // zero based
        lpTime->day,
         szCentury[(lpTime->year > 99 ? 1 : 0)],
        (lpTime->year > 99) ? lpTime->year - 100 : lpTime->year,
        (lpTime->hour == 0) ? 12 : ((lpTime->hour > 12) ? lpTime->hour - 12 : lpTime->hour),
        lpTime->minute,
        szAMPM[(lpTime->hour > 11 ? 1 : 0)]);
}

//
//  MakeMsgNode
//
//  Purpose:
//      Allocate memory for a new MSGID node and initialize its
//      data members to the values passed in.
//
//  Parameters:
//      lpMsg           - Pointer to a CMC_message
//      msgReference       - Opaque message identifier
//
//  Return:
//      lpMsgNode       - Pointer to new node


LPMSGID
MakeMsgNode (CMC_message_summary FAR *lpMsgSummary)
{
    CMC_return_code ulResult;
    LPMSGID lpMsgNode = NULL;
    CMC_message far * lpMessage;

    if (!lpMsgSummary)
        goto err;


    lpMsgNode = (LPMSGID)PvAlloc(sizeof(MSGID));
    if (!lpMsgNode)
        goto err;

    _fmemset (lpMsgNode, 0, sizeof (MSGID));

    // copy message regerence
    lpMsgNode->message_reference = (CMC_message_reference *)PvAllocMore( \
            sizeof(CMC_message_reference)+lpMsgSummary->message_reference->length,
            lpMsgNode);

    _fmemcpy(lpMsgNode->message_reference->string,
             lpMsgSummary->message_reference->string,
             (size_t) lpMsgSummary->message_reference->length);

    lpMsgNode->message_reference->length = lpMsgSummary->message_reference->length;

    // Who is the originator?
    if (lpMsgSummary->originator)
    {
        if (lpMsgSummary->originator->name)
        {
            lpMsgNode->from = (CMC_string)PvAllocMore(lstrlen(lpMsgSummary->originator->name) + 1, lpMsgNode);
            if (!lpMsgNode->from)
                goto err;
    
            lstrcpy (lpMsgNode->from, lpMsgSummary->originator->name);
        }
        else
        {
            lpMsgNode->from = NULL;
        }
    }
    else
    {
        lpMsgNode->from = NULL;
    }


    // What is the subject?
    if (lpMsgSummary->subject)
    {
        lpMsgNode->subject = (CMC_string)PvAllocMore(lstrlen(lpMsgSummary->subject) + 1, lpMsgNode);
        if (!lpMsgNode->subject)
            goto err;

        lstrcpy (lpMsgNode->subject, lpMsgSummary->subject);
    }
    else
    {
        lpMsgNode->subject = NULL;
    }

    // Time sent
    _fmemcpy(&lpMsgNode->time_sent, &lpMsgSummary->time_sent, sizeof(CMC_time));

    // Query Attachments and Read/Unread status
    ulResult = CMCRead( lhSession, lpMsgSummary->message_reference,
                CMC_MSG_AND_ATT_HDRS_ONLY | CMC_DO_NOT_MARK_AS_READ, 
                &lpMessage, (CMC_ui_id)NULL, NULL );
        
    if ( ulResult )
        goto err;

    if (!ulResult && lpMessage->attachments)
        lpMsgNode->fHasAttach = CMC_TRUE;

    // Has the message been read?
    if (lpMessage->message_flags & CMC_MSG_READ)
        lpMsgNode->fRead = CMC_TRUE;
    else
        lpMsgNode->fRead = CMC_FALSE;

    
    CMCFree( lpMessage );

    lpMsgNode->lpPrev = NULL;
    lpMsgNode->lpNext = NULL;

    return lpMsgNode;

err:
    PvFree(lpMsgNode);
    return NULL;
}

//
//  InsertMsgNode
//
//  Purpose:
//      Currently (for simplicity) we will insert the nodes
//      at the beginning of the list.  This can later be
//      replaced with a routine that can insert sorted on
//      different criteria, like DateReceived, From, or
//      Subject.  But for now...
//
//  Parameters:
//      lpMsgNode       - Pointer to a MSGID node
//      lppMsgHead      - Pointer to the head of the list
//
//  Return:
//      Void.


void
InsertMsgNode (LPMSGID lpMsgNode, LPMSGID  * lppMsgHead)
{
    if (*lppMsgHead)
    {
        lpMsgNode->lpNext = *lppMsgHead;
        (*lppMsgHead)->lpPrev = lpMsgNode;
    }
    else
        lpMsgNode->lpNext = NULL;

    //   The next 2 assignments are here in case the node came from somewhere
    //   other than a call to MakeMsgNode () in which case we aren't sure
    //   they're already NULL.

    lpMsgNode->lpPrev = NULL;
    *lppMsgHead = lpMsgNode;
}

//
//  DeleteMsgNode
//
//  Purpose:
//      Removes the node passed in from the list.  This
//      may seem like a strange way to do this but it's
//      not, because the Owner-Drawn List Box gives us
//      direct access to elements in the list that makes
//      it easier to do things this way.
//
//  Parameters:
//      lpMsgNode       - Pointer to the MSGID node to delete
//      lppMsgHead      - Pointer to the head of the list
//
//  Return:
//      Void.


void
DeleteMsgNode (LPMSGID lpMsgNode, LPMSGID * lppMsgHead)
{
    if (!lpMsgNode)
        return;

    //   Check if we are the first node

    if (lpMsgNode->lpPrev)
        lpMsgNode->lpPrev->lpNext = lpMsgNode->lpNext;

    //   Check if we are the last node

    if (lpMsgNode->lpNext)
        lpMsgNode->lpNext->lpPrev = lpMsgNode->lpPrev;

    //   check if we are the only node

    if(lpMsgNode == *lppMsgHead)
        *lppMsgHead = NULL;

    PvFree(lpMsgNode);
    return;
}



//
//  FindNode
//
//  Purpose:
//      Returns a pointer to the node containing msgReference.
//      Returns NULL if node doesn't exist or msgReference is NULL.
//
//  Parameters:
//      lpMsgHead       - Pointer to the head of the list
//      msgReference       - Message ID to search for
//
//  Return:
//      lpMsgNode       - Pointer to the node returned


LPMSGID
FindNode (LPMSGID lpMsgHead, CMC_message_reference FAR *msgReference)
{
    if (!msgReference)
        return NULL;

    while (lpMsgHead)
    {
        if ((lpMsgHead->message_reference->length == msgReference->length) &&
                !_fmemcmp((void far *)lpMsgHead->message_reference->string,
                      (void far *)msgReference->string, (size_t)msgReference->length))
            break;

        lpMsgHead = lpMsgHead->lpNext;
    }

    return lpMsgHead;
}



//
//  FreeMsgList
//
//  Purpose:
//      Walks down the MsgList and frees each node.
//
//  Parameters:
//      lpMsgHead       - Pointer to the head of the list
//
//  Return:
//      Void.


void
FreeMsgList (LPMSGID lpMsgHead)
{
    LPMSGID lpT;

    while (lpMsgHead)
    {
        lpT = lpMsgHead;
        lpMsgHead = lpMsgHead->lpNext;
        PvFree(lpT);
    }
}

//
//  MakeDisplayNameStr
//
//  Purpose:
//      Finds all recipients of type ulRecipRole in lpRecips and adds
//      their friendly name to the display string.
//
//  Parameters:
//      lpszDisplay         - Destination string for names
//      ulRecipRole        - Recipient types to search for
//      cRecips             - Count of recipients in lpRecips
//      lpRecips            - Pointer to array of CMC_recipients
//
//  Return:
//      Void.


void
MakeDisplayNameStr (LPSTR lpszDisplay, CMC_enum ulRecipRole,
    ULONG cRecips, CMC_recipient FAR * lpRecips)
{
    ULONG idx;

    *lpszDisplay = '\0';

    for (idx = 0; idx < cRecips; idx++)
    {
        if (lpRecips[idx].role == ulRecipRole)
        {
            lstrcat (lpszDisplay, lpRecips[idx].name);
            lstrcat (lpszDisplay, "; ");
        }
    }

    if (*lpszDisplay)
        lpszDisplay[lstrlen (lpszDisplay) - 2] = '\0';
}


//
//  SaveMsgChanges
//
//  Purpose:
//      If while reading a message the user changes the notetext at all
//      then this function is called to save those changes in the Inbox.
//
//  Parameters:
//      hWnd            - handle to the window/dialog who called us
//      lpMsg           - pointer to the CMC message to be saved
//      msgReference       - ID of the message to save
//
//  Return:
//      ulResult        - Indicating success/failure


CMC_return_code
SaveMsgChanges (HWND hWnd, CMC_message far *lpMsg)
{
    LPSTR lpszT;
    LPSTR lpszTextNote = NULL;
    LONG cLines, cb;
    CMC_return_code ulResult = CMC_SUCCESS;
    CMC_extension   ext;

    lpszT = lpMsg->text_note;

    cLines = SendDlgItemMessage (hWnd, IDC_READNOTE, EM_GETLINECOUNT, 0, 0L);
    cb = (LRESULT) SendDlgItemMessage (hWnd,
                IDC_READNOTE,
                EM_LINEINDEX,
                (WPARAM) cLines - 1,
                0L);
    cb += (LRESULT) SendDlgItemMessage (hWnd, IDC_READNOTE, EM_LINELENGTH, (WPARAM)cb, 0L);
    cb += cLines * 2;

    lpszTextNote = (LPSTR)PvAlloc(cb + 1 );

    if (!lpszTextNote)
        goto err;

    SendDlgItemMessage (hWnd, IDC_READNOTE, WM_GETTEXT,
        (WPARAM) cb, (LPARAM) lpszTextNote);

    lpMsg->text_note = lpszTextNote;

    ext.item_data       = 0;
    ext.item_code       = CMC_X_COM_SAVE_MESSAGE;
    ext.item_reference  = (CMC_buffer)lpMsg;
    ext.extension_flags = CMC_EXT_REQUIRED | CMC_EXT_LAST_ELEMENT;

    ulResult = CMCActOn(lhSession, lpMsg->message_reference, CMC_ACT_ON_EXTENDED,
                        CMC_ERROR_UI_ALLOWED, (CMC_ui_id)hWnd, &ext);

    PvFree(lpszTextNote);

err:
    lpMsg->text_note = lpszT;
    return ulResult;
}

//
//  MakeNewMessage
//
//  Purpose:
//      This function is used to construct a new message for the
//      ComposeNote UI.  This gets called as a result of a Reply,
//      ReplyAll, or a Forward action on a message being read.
//      The destination for the new message is CmcMsg, the global
//      CMC_message struct pointer used by ComposeNoteDlgProc.
//      ComposeNoteDlgProc always frees the memory consumed by
//      this object whether it allocated it or not.
//
//  Parameters:
//      lpSrcMsg            - CMC_message to be copied
//      flType              - Specifies the action that caused this call
//                            either: IDC_REPLY, IDC_REPLYALL, or IDC_FORWARD
//
//  Return:
//      ulResult            - Indicates success/failure


CMC_return_code
MakeNewMessage (CMC_message far *lpSrcMsg, CMC_flags flType)
{

#define REPLY_SEPERATOR "\r\n--------------------------\r\n"

    ULONG cOldRecips;
    ULONG cNewRecips;
    ULONG cAttach;
    ULONG idx;
    CMC_return_code     ulResult = CMC_SUCCESS;
    CMC_uint32          cCurrentUser = 1;
    CMC_recipient FAR * CurrentUser = NULL;


    if (!lpSrcMsg)
        return CMC_E_FAILURE;

    if(CmcMsg)
        PvFree(CmcMsg);

    CmcMsg = (CMC_message far *)PvAlloc(sizeof(CMC_message));

    if (!CmcMsg)
        goto err;

    _fmemset (CmcMsg, 0, sizeof (CMC_message));

    if (lpSrcMsg->subject)
    {
        CmcMsg->subject = (LPSTR)PvAlloc(lstrlen(lpSrcMsg->subject) + 5);
        if (!CmcMsg->subject)
            goto err;

        if (flType == IDC_FORWARD)
            lstrcpy (CmcMsg->subject, "FW: ");
        else
            lstrcpy (CmcMsg->subject, "RE: ");

        lstrcat (CmcMsg->subject, lpSrcMsg->subject);
    }

    if (lpSrcMsg->text_note)
    {
        CmcMsg->text_note = (CMC_string)PvAlloc(lstrlen(lpSrcMsg->text_note) + 32);
        if (!CmcMsg->text_note)
            goto err;

        lstrcpy (CmcMsg->text_note, REPLY_SEPERATOR);
        lstrcat (CmcMsg->text_note, lpSrcMsg->text_note);
    }

    if (lpSrcMsg->message_type)
    {
        CmcMsg->message_type = (CMC_string)PvAlloc(lstrlen(lpSrcMsg->message_type) + 1);
        if (!CmcMsg->message_type)
            goto err;

        lstrcpy (CmcMsg->message_type, lpSrcMsg->message_type);
    }

    if (lpSrcMsg->attachments)
    {
        cAttach = 0;
        while (!(lpSrcMsg->attachments[cAttach].attach_flags & CMC_ATT_LAST_ELEMENT))
            cAttach++;

        cAttach++;

        CmcMsg->attachments = (CMC_attachment far *)PvAlloc(cAttach * sizeof(CMC_attachment));
        if (!CmcMsg->attachments)
            goto err;

        _fmemset (CmcMsg->attachments, 0, (size_t)cAttach*sizeof(CMC_attachment));

        for (idx = 0; idx < cAttach; idx++)
            CopyAttachment (CmcMsg->attachments, &CmcMsg->attachments[idx], &lpSrcMsg->attachments[idx]);

    }

    if (flType == IDC_REPLY || flType == IDC_REPLYALL)
    {
        cOldRecips = 0;

        while (!(lpSrcMsg->recipients[cOldRecips].recip_flags & CMC_RECIP_LAST_ELEMENT))
            cOldRecips++;
        cOldRecips++;

        if(flType == IDC_REPLYALL)
            cNewRecips = cOldRecips;
        else
            cNewRecips = 1;

        CmcMsg->recipients = (CMC_recipient far *)PvAlloc(cNewRecips * sizeof(CMC_recipient));

        if (!CmcMsg->recipients)
            goto err;

        _fmemset (CmcMsg->recipients, 0, (size_t)cNewRecips*sizeof(CMC_recipient));

        // Look up current user address
        ulResult = CMCLookUp(lhSession, NULL, CMC_LOOKUP_RESOLVE_IDENTITY,
                             (CMC_ui_id)NULL, &cCurrentUser, &CurrentUser, NULL);

        cNewRecips = 0;
        for (idx = 0; idx < cOldRecips; idx++)
        {
            // Always Reply to the originator and change their role
            if (lpSrcMsg->recipients[idx].role == CMC_ROLE_ORIGINATOR)
            {
                CopyRecipient(CmcMsg->recipients, &CmcMsg->recipients[cNewRecips],
                              &lpSrcMsg->recipients[idx]);
                CmcMsg->recipients[cNewRecips].role = CMC_ROLE_TO;
                cNewRecips++;
                if(flType == IDC_REPLY)
                    break;
            }
            else if((flType == IDC_REPLYALL) &&
                    (ulResult || lstrcmp(lpSrcMsg->recipients[idx].address,
                                         CurrentUser->address)))
            {
                // Don't reply to ourselves if replying to all
                CopyRecipient(CmcMsg->recipients, &CmcMsg->recipients[cNewRecips],
                              &lpSrcMsg->recipients[idx]);
                cNewRecips++;
            }
        }

        if(cNewRecips)
            CmcMsg->recipients[cNewRecips-1].recip_flags |= CMC_RECIP_LAST_ELEMENT;

        CMCFree(CurrentUser);
    }

    return ulResult;

err:
    PvFree(CmcMsg->subject);
    PvFree(CmcMsg->text_note);
    PvFree(CmcMsg->message_type);
    PvFree(CmcMsg->recipients);
    PvFree(CmcMsg->attachments);
    PvFree(CmcMsg);
    CmcMsg = NULL;

    return ulResult;
}

//
//  LogSendMail
//
//  Purpose:
//      Used to track how many messages were sent with this client.
//      This information is used strictly for gathering stats on
//      how many messages were pumped through the spooler/transport.
//
//  Usage:
//      Add the following to the win.ini file:
//          [CMC Client]
//          LogFile=filepath
//
//      where: filepath can be a full UNC path or some local path & file
//
//  Parameters:
//      ulResult        - Currently unused; should be used to count errors
//
//  Result:
//      Void.


void LogSendMail(ULONG ulResult)
{
    char szLogFile[128];
    char szCount[32];
    OFSTRUCT ofs;
    HFILE hf = HFILE_ERROR;
    int cSent = 1;

    if(!GetProfileString("CMC Client", "LogFile", "CMCcli.log",
            szLogFile, sizeof(szLogFile)))
        return;

    if((hf = OpenFile(szLogFile, &ofs, OF_READWRITE)) == HFILE_ERROR)
    {
        if((hf = OpenFile(szLogFile, &ofs, OF_CREATE|OF_READWRITE)) == HFILE_ERROR)
            return;
    }
    else
    {
        if(!_lread(hf, szCount, sizeof(szCount)))
        {
            _lclose(hf);
            return;
        }

        cSent = atoi(szCount) + 1;
    }

    wsprintf(szCount, "%d", cSent);

    _llseek(hf, 0, 0);

    _lwrite(hf, szCount, lstrlen(szCount));
    _lclose(hf);

    return;
}

//
//  SaveFileAttachments
//
//  Purpose:
//      Displays a 'Save As' common dialog to allow the user to save
//      file attachments contained in the current message.
//
//  Parameters:
//      hWnd            - Window handle of calling WndProc
//      cFiles          - Count of the files in the file array
//      lpFiles         - Array of CMC_attachments
//
//  Return:
//      Void.


void SaveFileAttachments(HWND hWnd, CMC_attachment FAR * lpFile)
{
    OPENFILENAME ofn;
    char szFileName[256];
    char szFilter[256];
    static char szFileTitle[16];
    static char szDirName[256] = "";
    LPSTR lpszEndPath;
    ULONG idx;
#ifdef WIN16
    OFSTRUCT ofStrSrc;
    OFSTRUCT ofStrDest;
    HFILE hfSrcFile, hfDstFile;
#endif

    _fmemset(&ofn, 0, sizeof(OPENFILENAME));

    if (!lpFile)
        return;

    if (!szDirName[0])
        GetWindowsDirectory ( szDirName,sizeof(szDirName));

    LoadString(hInst, IDS_FILTER, szFilter, sizeof(szFilter));

    for (idx = 0; szFilter[idx] != '\0'; idx++)
        if (szFilter[idx] == '|')
            szFilter[idx] = '\0';

    lstrcpy(szFileName, lpFile->attach_title);

    ofn.lStructSize = sizeof (OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFilter = szFilter;
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = sizeof(szFileName);
    ofn.lpstrFileTitle = szFileTitle;
    ofn.nMaxFileTitle = sizeof(szFileTitle);
    ofn.lpstrInitialDir = szDirName;
    ofn.lpstrTitle = "Save Attachment";
    ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;

    if (!GetSaveFileName (&ofn))
        return;

    //   Save the directory for the next time we call this

    lstrcpy (szDirName, szFileName);
    if (lpszEndPath = strstr (szDirName, szFileTitle))
        *(--lpszEndPath) = '\0';

#ifdef WIN16
    // Use CopyLZFile to copy the file.
    // Open, copy, and then close the file.

    hfSrcFile = LZOpenFile(lpFile->attach_filename, &ofStrSrc, OF_READ);

    hfDstFile = LZOpenFile(szFileName, &ofStrDest, OF_CREATE);
    if (LZCopy(hfSrcFile, hfDstFile) < 0)
        MakeMessageBox (hWnd, 0, IDS_SAVEATTACHERROR, MBS_ERROR);
    LZClose(hfSrcFile);
    LZClose(hfDstFile);

#else
    /* Use CopyFile to carry out the operation. */

    if(!CopyFile(lpFile->attach_filename, szFileName, FALSE))
        MakeMessageBox (hWnd, 0, IDS_SAVEATTACHERROR, MBS_ERROR);
#endif

}

//
//  ToggleMenuState
//
//  Purpose:
//      Enables/Disables menu items depending on the session state.
//
//  Parameters:
//      hWnd            - handle to the window/dialog who called us
//      fLoggedOn       - TRUE if logged on, FALSE if logged off
//
//  Return:
//      Void.
//

void ToggleMenuState(HWND hWnd, BOOL fLoggedOn)
{
    EnableMenuItem (GetMenu (hWnd), IDM_LOGOFF,         !fLoggedOn);
    EnableMenuItem (GetMenu (hWnd), IDM_COMPOSE_CMC,    !fLoggedOn);
    EnableMenuItem (GetMenu (hWnd), IDM_COMPOSE_CUSTOM, !fLoggedOn);
    EnableMenuItem (GetMenu (hWnd), IDM_READ,           !fLoggedOn);
    EnableMenuItem (GetMenu (hWnd), IDM_ADDRBOOK,       !fLoggedOn);
    EnableMenuItem (GetMenu (hWnd), IDM_LOGON,          fLoggedOn);
    EnableMenuItem (GetMenu (hWnd), IDM_EXIT,           FALSE);
}

//
//  SecureMenu
//
//  Purpose:
//      Enables/Disables Logon and Exit menu items.
//      CMCLogon might yield control to Windows, so the user might be able to
//      access the window menu (for example click Logon) after we call
//      CMCLogon, but before it returns.
//
//  Parameters:
//      hWnd            - handle to the window/dialog who called us
//      fBeforeLogon    - TRUE when this function is called when we are about
//                      to call CMCLogon, FALSE if called after logon (failed)
//                      if Logon succeddes ToggleMenuState is called instead of
//                      this function.
//
//  Return:
//      Void.
//


void SecureMenu(HWND hWnd, BOOL fBeforeLogon)
{
    EnableMenuItem (GetMenu (hWnd), IDM_LOGON, fBeforeLogon);
    EnableMenuItem (GetMenu (hWnd), IDM_EXIT,  fBeforeLogon);
}
