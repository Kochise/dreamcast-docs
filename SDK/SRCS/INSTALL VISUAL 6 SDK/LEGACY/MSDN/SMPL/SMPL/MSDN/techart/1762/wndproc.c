#include <windows.h>
#include <commdlg.h>
#include <colordlg.h>
#include "resource.h"
#include "w32pen.h"

/***********************************************************************

  FUNCTION   : SetPenAttr

  PARAMETERS : HWND hwndDlg
               UINT uMsg
               UINT wParam
               LONG lParam

  PURPOSE    : callback for the pen attributes dialog box

  CALLS      : 

  MESSAGES   : none

  RETURNS    : void

  COMMENTS   : modified from callback sample in Win32 docs (in section on 
               pens)

  HISTORY    : 

************************************************************************/


LRESULT CALLBACK SetPenAttr(HWND hwndDlg, UINT uMsg, UINT wParam, LONG lParam)
{
    static HWND hwndLineType;
    static HWND hwndLineStyle;
    static HWND hwndJoinStyle;
	static HWND hwndEndCapStyle;
	static HWND hwndPatternStyle;
    static HWND hwndWidth;

    DWORD adwLineType[] = {
                            PS_COSMETIC,
                            PS_GEOMETRIC
                          };
    DWORD adwLineStyle[] = {
                            PS_DASH,
                            PS_DASHDOT,
                            PS_DOT,
                            PS_INSIDEFRAME,
                            PS_NULL,
                            PS_SOLID,
							PS_ALTERNATE
                          };
    DWORD adwJoinStyle[] = {
                            PS_JOIN_BEVEL,
                            PS_JOIN_MITER,
                            PS_JOIN_ROUND
                           };

    DWORD adwEndCapStyle[] = {
	                       PS_ENDCAP_FLAT,
						   PS_ENDCAP_ROUND,
						   PS_ENDCAP_SQUARE
						 };
	DWORD adwPattern[] = {
	                       BS_SOLID,
                           BS_HATCHED,	
                           BS_PATTERN,	
                           BS_HOLLOW,	
						 };

    CHAR  chWidth[3];

    int iCount;
    int  index;
	BOOL bTrans;

	//
	// declare function to be used later
	//
	int FindIndex(DWORD *, int, DWORD);


    switch(uMsg){

        case WM_INITDIALOG:

            /* Initialize each custom control with the required data. */

            hwndLineType = GetDlgItem(hwndDlg, IDD_PEN_TYPE);

            /* Use the PenType constants as indices. */

            SendMessage(hwndLineType, CB_ADDSTRING, 0, (LONG) "COSMETIC");
            SendMessage(hwndLineType, CB_ADDSTRING, 0, (LONG) "GEOMETRIC");
			
			//
			// Select an initial value for the list box
			//
			if (pPenList)
				SendMessage(hwndLineType, CB_SETCURSEL, 
					FindIndex(adwLineType, sizeof(adwLineType) / 
							sizeof(adwLineType[0]),(DWORD)pPenList->prev->dwPenType), 0L);
			else 
				SendMessage(hwndLineType, CB_SETCURSEL, 0, 0L);
            /* Initialize each custom control with the required data. */

            hwndLineStyle = GetDlgItem(hwndDlg, IDD_PEN_STYLE);

            /* Use the PenStyle constants as indices. */

            SendMessage(hwndLineStyle, CB_ADDSTRING, 0,
                        (LONG) "DASH");
            SendMessage(hwndLineStyle, CB_ADDSTRING, 0,
                        (LONG) "DASHDOT");
            SendMessage(hwndLineStyle, CB_ADDSTRING, 0,
                        (LONG) "DOT");
            SendMessage(hwndLineStyle, CB_ADDSTRING, 0,
                        (LONG) "INSIDEFRAME");
            SendMessage(hwndLineStyle, CB_ADDSTRING, 0,
                        (LONG) "NULL");
            SendMessage(hwndLineStyle, CB_ADDSTRING, 0,
                        (LONG) "SOLID");
            SendMessage(hwndLineStyle, CB_ADDSTRING, 0,
                        (LONG) "ALTERNATE");

			if (pPenList)	
				SendMessage(hwndLineStyle, CB_SETCURSEL, 
					FindIndex(adwLineStyle, sizeof(adwLineStyle) / 
							sizeof(adwLineStyle[0]),pPenList->prev->dwPenStyle), 0L);
			else 
				SendMessage(hwndLineStyle, CB_SETCURSEL, 0, 0L);

            /* Use the JoinStyle constants as indices. */

            hwndJoinStyle = GetDlgItem(hwndDlg, IDD_JOIN_STYLE);

            SendMessage(hwndJoinStyle, CB_ADDSTRING, PS_JOIN_BEVEL,
                        (LONG) "BEVEL");
            SendMessage(hwndJoinStyle, CB_ADDSTRING, PS_JOIN_MITER,
                        (LONG) "MITER");
            SendMessage(hwndJoinStyle, CB_ADDSTRING, PS_JOIN_ROUND,
                        (LONG) "ROUND");

			if (pPenList)
				SendMessage(hwndJoinStyle, CB_SETCURSEL, 
					FindIndex(adwJoinStyle, sizeof(adwJoinStyle) / 
							sizeof(adwJoinStyle[0]),pPenList->prev->dwJoinStyle), 0L);
			else 
				SendMessage(hwndJoinStyle, CB_SETCURSEL, 0, 0L);


            /* Use the EndCap constants as indices. */

            hwndEndCapStyle = GetDlgItem(hwndDlg, IDD_ENDCAP_STYLE);

            SendMessage(hwndEndCapStyle, CB_ADDSTRING, PS_ENDCAP_FLAT,
                        (LONG) "FLAT");
            SendMessage(hwndEndCapStyle, CB_ADDSTRING, PS_ENDCAP_ROUND,
                        (LONG) "ROUND");
            SendMessage(hwndEndCapStyle, CB_ADDSTRING, PS_ENDCAP_SQUARE,
                        (LONG) "SQUARE");

			if (pPenList)
				SendMessage(hwndEndCapStyle, CB_SETCURSEL, 
					FindIndex(adwEndCapStyle, sizeof(adwEndCapStyle) / 
							sizeof(adwEndCapStyle[0]),pPenList->prev->dwEndCapStyle), 0L);
			else
				SendMessage(hwndEndCapStyle, CB_SETCURSEL, 0, 0L);


            /* Use the Pattern constants as indices. */

            hwndPatternStyle = GetDlgItem(hwndDlg, IDD_PATTERN_STYLE);

            SendMessage(hwndPatternStyle, CB_ADDSTRING, BS_SOLID,
                        (LONG) "SOLID");
            SendMessage(hwndPatternStyle, CB_ADDSTRING, BS_HATCHED,
                        (LONG) "HATCHED");
            SendMessage(hwndPatternStyle, CB_ADDSTRING, BS_PATTERN,
                        (LONG) "PATTERN");
            SendMessage(hwndPatternStyle, CB_ADDSTRING, BS_HOLLOW,
                        (LONG) "HOLLOW");

			if (pPenList)
				SendMessage(hwndPatternStyle, CB_SETCURSEL, 
					FindIndex(adwPattern, sizeof(adwPattern) / 
							sizeof(adwPattern[0]),pPenList->prev->lb.lbStyle), 0L);
			else 
				SendMessage(hwndPatternStyle, CB_SETCURSEL, 0, 0L);

            
            if (pPenList)
            	SetDlgItemInt(hwndDlg, IDD_PEN_WIDTH, pPenList->prev->dwWidth, FALSE);
			else
				SetDlgItemInt(hwndDlg, IDD_PEN_WIDTH, 1, FALSE);


        return TRUE;

        case WM_COMMAND:
		  switch (HIWORD(wParam))
		  {
		    case CBN_SELCHANGE:
			  if (LOWORD(wParam) == IDD_PEN_STYLE || LOWORD(wParam) == IDD_PEN_TYPE)
			  {
			    DWORD dwStyle;
				DWORD dwType;

                index = SendMessage(hwndLineStyle, CB_GETCURSEL, 0, 0L);
				dwStyle = adwLineStyle[index];

                index = SendMessage(hwndLineType, CB_GETCURSEL, 0, 0L);
				dwType = adwLineType[index];

				if (dwType == PS_GEOMETRIC && dwStyle == PS_ALTERNATE)
				{
				  MessageBeep(0);
				  MessageBox(hwndDlg, (LPSTR)"Alternate style doesn't work with Geometric pens", 
				             NULL, MB_OK);

				}
			  }
		      break;
		    default:
			  break;
		  }
          switch (LOWORD(wParam)) 
          {
		  
		    case IDOK:
              /* Retrieve the requested pen type */

              index = SendMessage(hwndLineType, CB_GETCURSEL, 0, 0L);

              PenRecord.dwPenType = adwLineType[index];

              /* Retrieve the requested pen style. */

              index = SendMessage(hwndLineStyle, CB_GETCURSEL, 0, 0L);

              PenRecord.dwPenStyle = adwLineStyle[index];

              /* Retrieve the requested join style. */

              index = SendMessage(hwndJoinStyle, CB_GETCURSEL, 0, 0L);
              PenRecord.dwJoinStyle = adwJoinStyle[index];

              /* Retrieve the requested endcap style. */

              index = SendMessage(hwndEndCapStyle, CB_GETCURSEL, 0, 0L);
              PenRecord.dwEndCapStyle = adwEndCapStyle[index];

              /* Retrieve the requested pattern. */

              index = SendMessage(hwndPatternStyle, CB_GETCURSEL, 0, 0L);
              PenRecord.lb.lbStyle = adwPattern[index];

              /* Retrieve the requested width. */

              GetDlgItemText(hwndDlg, IDD_PEN_WIDTH, chWidth, 3);
              PenRecord.dwWidth = GetDlgItemInt(hwndDlg, IDD_PEN_WIDTH, &bTrans, FALSE);

			  //
			  // Make sure that the user hasn't tried to build a Cosmetic Pen
			  // with width greater than 1
			  //
			  if (PenRecord.dwPenType == PS_COSMETIC) {
			  		if (PenRecord.dwWidth != 1L) {
			  			MessageBox(hwndMain, "Cosmetic Pen Type must have pen width of one...Changing",
							"Pen Type/Width Mismatch", MB_APPLMODAL | MB_ICONEXCLAMATION | MB_OK);
			  			PenRecord.dwWidth = 1L;
					}
					if (PenRecord.lb.lbStyle != BS_SOLID) {
			  			MessageBox(hwndMain, "Cosmetic Pen Pattern must be solid...Changing",
							"Pen Type/Pattern Mismatch", MB_APPLMODAL | MB_ICONEXCLAMATION | MB_OK);
						PenRecord.lb.lbStyle = BS_SOLID;
					}
			  }

			  //init all xform to identity
			  PenRecord.xf.eM11 = 1.0f;
			  PenRecord.xf.eM12 = 0.0f;
			  PenRecord.xf.eM21 = 0.0f;
			  PenRecord.xf.eM22 = 1.0f;
			  PenRecord.xf.eDx  = 0.0f;
			  PenRecord.xf.eDy  = 0.0f;
			  break;
			default:
			  break;
		  } 
		 
        return FALSE;
    }
    return FALSE;

    UNREFERENCED_PARAMETER(wParam);

    UNREFERENCED_PARAMETER(lParam);
    UNREFERENCED_PARAMETER(iCount);
}


/****************************************************************************

        FUNCTION: About(HWND, UINT, WPARAM, LPARAM)

        PURPOSE:  Processes messages for "About" dialog box

        MESSAGES:

        WM_INITDIALOG - initialize dialog box
        WM_COMMAND    - Input received

        COMMENTS:

        Display version information from the version section of the
        application resource.

        Wait for user to click on "Ok" button, then close the dialog box.

****************************************************************************/

LRESULT CALLBACK About(HWND hDlg,UINT message,WPARAM uParam,LPARAM lParam)
{
        static  HFONT hfontDlg;
        LPSTR   lpVersion;       
        DWORD   dwVerInfoSize;
        DWORD   dwVerHnd;
        UINT    uVersionLen;
        WORD    wRootLen;
        BOOL    bRetCode;
        int     i;
        char    szFullPath[256];
        char    szResult[256];
        char    szGetName[256];

        switch (message) {
                case WM_INITDIALOG:  // message: initialize dialog box
                        // Create a font to use
                        hfontDlg = CreateFont(14, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0,
                                VARIABLE_PITCH | FF_SWISS, "");

                        // Center the dialog over the application window
                        CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));

                        // Get version information from the application
                        GetModuleFileName (hInst, szFullPath, sizeof(szFullPath));
                        dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);
                        if (dwVerInfoSize) {
                                // If we were able to get the information, process it:
                                LPSTR   lpstrVffInfo;
                                HANDLE  hMem;
                                hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
                                lpstrVffInfo  = GlobalLock(hMem);
                                GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, lpstrVffInfo);
                                lstrcpy(szGetName, "\\StringFileInfo\\040904E4\\");
                                wRootLen = lstrlen(szGetName);

                                // Walk through the dialog items that we want to replace:
                                for (i = DLG_VERFIRST; i <= DLG_VERLAST; i++) {
                                        GetDlgItemText(hDlg, i, szResult, sizeof(szResult));
                                        szGetName[wRootLen] = (char)0;
                                        lstrcat (szGetName, szResult);
                                        uVersionLen   = 0;
                                        lpVersion     = NULL;
                                        bRetCode      =  VerQueryValue((LPVOID)lpstrVffInfo,
                                                (LPSTR)szGetName,
                                                (LPVOID)&lpVersion,
                                                (LPDWORD)&uVersionLen); // For MIPS strictness

                                        if ( bRetCode && uVersionLen && lpVersion) {
                                                // Replace dialog item text with version info
                                                lstrcpy(szResult, lpVersion);
                                                SetDlgItemText(hDlg, i, szResult);
                                                SendMessage (GetDlgItem (hDlg, i), WM_SETFONT, (UINT)hfontDlg, TRUE);
                                        }
                                } // for (i = DLG_VERFIRST; i <= DLG_VERLAST; i++)

                                GlobalUnlock(hMem);
                                GlobalFree(hMem);
                        } // if (dwVerInfoSize)

                        return (TRUE);

                case WM_COMMAND:                      // message: received a command
                        if (LOWORD(uParam) == IDOK        // "OK" box selected?
                        || LOWORD(uParam) == IDCANCEL) {  // System menu close command?
                                EndDialog(hDlg, TRUE);        // Exit the dialog
                                DeleteObject (hfontDlg);
                                return (TRUE);
                        }
                        break;
        }
        return (FALSE); // Didn't process the message

        lParam; // This will prevent 'unused formal parameter' warnings
}


/****************************************************************************

        FUNCTION: FindIndex(DWORD *, DWORD)

        PURPOSE:  Finds the position of Pen attributes in their respective
					arrays in SetPenAttr()

        MESSAGES:

        None

        COMMENTS:

        None so far.

****************************************************************************/

int FindIndex(DWORD *pdwAttribs, int iLength, DWORD dwAttribute)
{
	int i;

	if (iLength) {
		for (i = 0; i < iLength; i++) {
			if (pdwAttribs[i] == dwAttribute)
				return i;
		}
	}

	//
	// Couldn't find the attribute value in the attribute list...warn the user
	//

	return 0;
}
