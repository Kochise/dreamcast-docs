////////////////////////////////////////////////////////////////////////
//
// CSTEXT
// A sample application that shows how to display complex scripts such
// as Arabic, Hebrew, Thai, or Indic scripts.
//
// This sample works best if executed on a platform enabled for complex 
// scripts, such as Arabic, Hebrew, or Thai Windows NT 4.0 or Windows 95,
// or Windows NT 5.0 with the appropriate locale installed.
//
// The WndProc function puts out text typed by the user to the client area
// in two ways: 1) using ExtTextOut to put out each character as it 
// is typed by the user, and 2) saving each character typed in a 
// buffer and putting out the whole buffer using ExtTextOut.
//
// If you run the program on a system that supports complex scripts, such as
// Arabic, Hebrew, or Thai Windows NT, and switch the keyboard to one of 
// those languages, you will see different results in the two output lines.
// For example, on Arabic Windows NT, the line of characters displayed one 
// by one will show only the stand-alone Arabic characters, without joining, 
// and without the proper bidirectional layout. The line displayed using 
// the whole buffer will be shown correctly
//
// Choose the help menu for guidelines on programming for complex scripts.
//
// Written by F. Avery Bishop, with advice from David C. W. Brown.
//
// Copyright (c) 1997, Microsoft Corporation. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////

#include "cstext.h"
#include <stdarg.h>
#include <windows.h>
#include <tchar.h>
#include "resource.h"

#ifndef UNICODE
#pragma message("Warning: This sample works best as a Unicode application")
#endif

// Global variables
int         g_xStartOneChar = XSTART ;  // X position to display next character
HINSTANCE   g_hInstance ;
TCHAR       g_szTitle[MAX_MESSAGE] ;    // Title bar text

// Function Prototypes, in the order defined
LRESULT CALLBACK WndProc         (HWND , UINT , WPARAM , LPARAM) ;
BOOL CALLBACK    EditDialogProc  (HWND , UINT , WPARAM , LPARAM) ;
BOOL CALLBACK    HelpDialogProc  (HWND , UINT , WPARAM , LPARAM) ;
void             InitializeFont  (HWND , LONG, LPCHOOSEFONT , LPLOGFONT) ;
BOOL             InitApplication (HINSTANCE , LPTSTR) ;
BOOL             InitInstance    (HINSTANCE , LPTSTR , int) ;
int              RcMessageBox    (HWND , int , int , ...) ;

//
//   FUNCTION: WndProc (HWND, UINT, WPARAM, LPARAM)
//
//   PURPOSE: Window Procedure
//
//   COMMENTS:
//          This function puts out text typed by the user to the client area
//          in two ways: 1) using ExtTextOut to put out each character as it 
//          is typed by the user, and 2) saving each character typed in a 
//          buffer and putting out the whole buffer using ExtTextOut. 
//
LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HFONT    hTextFont ;        // Font for text typed by user
    static TCHAR    szOutputBuffer[BUFFER_SIZE] ; // Buffer of characters typed
    static int      nChars = 0 ;       // Current size of buffer
    static RECT     rcBufferLine = {0,0,0,0} ;// Rectangle for the text to be displayed
    static UINT     uiAlign = TA_LEFT ;// Alignment and reading order flag
    static CHOOSEFONT cf ;             // This is static to keep last values as defaults
    static LOGFONT  lf ;               // Same for this.
    
    PAINTSTRUCT     ps ;               // Standard paint structure
    HDC             hDc ;              // HDC used in two ways. See WM_CHAR and WM_PAINT below
    SIZE            sOneChar ;         // Used in GetTextExtentPoint32.
    // Normally these should be in resources so they can be localized.
    TCHAR           szCharLabel[] 
                    = TEXT("Characters displayed one by one, as typed:") ;
    TCHAR           szBuffLabel[] 
                    = TEXT("All text in the line displayed in one call to ExtTextOut:") ;
    TEXTMETRIC      tm ;
    
    int nxStartBuffer, nyStartBuffer ;  // x and y positions to display text.
    int cCharWidths ;                   // Count of character widths, used in GetCharWidth32
    
    switch (message)
    {
    case WM_CREATE :
        
        InitializeFont (hWnd, 20, &cf, &lf) ; // Routine defined below
        hTextFont = CreateFontIndirect (&lf) ;
        
        if (NULL == hTextFont) {
            RcMessageBox (hWnd, IDS_CHOOSEFONT_FAILED, MB_ICONEXCLAMATION | MB_OK);
            break ;
        } ;
        
        return 0 ;
        
    case WM_CHAR :  // Process keyboard input
        
        switch ((TCHAR) wParam)
        {
        case VK_BACK :
            
            if (nChars > 0){
                nChars-- ;
                
                // Reset starting point for next character output
                hDc = GetDC(hWnd) ;
                SelectObject(hDc, hTextFont) ;
                GetTextExtentPoint32(hDc, szOutputBuffer, nChars, &sOneChar) ;
                ReleaseDC(hWnd, hDc) ;
                g_xStartOneChar = sOneChar.cx + XSTART;
                
                InvalidateRect (hWnd, NULL, TRUE) ;
            }
            break ;
            
        case VK_RETURN :    
            
            // This sample ignores return. Most apps will add CR/LF or exit.
            break ;
            
        case VK_ESCAPE :
        case VK_END :
        case VK_HOME :
            
            // Processing other non-printable characters is left as an exercise
            break ;
            
        default:
            
            // Process all normal characters
            
        // First use the old (incorrect) method to display only the last
        // character typed
        
            // NOTE: This is an example of what *not* to do, because
            // characters that should join or otherwise interact 
            // typographically will show as separate, stand alone characters.
            hDc = GetDC (hWnd) ;
            SelectObject (hDc, hTextFont) ;
            SetBkMode (hDc, TRANSPARENT) ;
            ExtTextOut (hDc, g_xStartOneChar, YSTART, 0,
                NULL, (LPCTSTR) &wParam, 1, NULL) ;
            
            // Get the next character position
            GetCharWidth (hDc, (UINT) wParam, (UINT) wParam, &cCharWidths) ;
            // This assumes left to right scripts, so it will break on
            // Arabic and Hebrew!
            g_xStartOneChar += cCharWidths ; 

            ReleaseDC (hWnd, hDc) ;
            
        // Next, display the whole buffer of all characters typed in so far

            szOutputBuffer[nChars] = (TCHAR) wParam ;
            if (nChars < BUFFER_SIZE-1) {
                nChars++ ;
            }
            // This will generate a WM_PAINT message. In the processing 
            // of WM_PAINT below, we display the text buffer in the 
            // rectangle rcBufferLine. This is the recommended approach.
            InvalidateRect (hWnd, &rcBufferLine, TRUE) ;
        }
        
        return 0 ;
    
    case WM_PAINT :
        
        hDc = BeginPaint (hWnd, &ps) ;
        
        SelectObject (hDc, hTextFont) ;
        
        // Get line positions for the current font
        GetTextMetrics (hDc, &tm) ;
        
        nyStartBuffer = YSTART + 3*tm.tmHeight ;
        
        GetClientRect (hWnd, &rcBufferLine) ;
        
        rcBufferLine.top = nyStartBuffer ;
        rcBufferLine.bottom = nyStartBuffer + tm.tmHeight ;
        
        // Set the x position for right or left aligned text
        if (uiAlign & TA_RIGHT) {
            nxStartBuffer = rcBufferLine.right - XSTART ;
        } else {
            nxStartBuffer = XSTART ;
        }
        
        SetTextAlign (hDc, uiAlign) ;
        
        // Write the whole text buffer in the "character by character" rectangle
        // Note how the complex script comes out right this time.
        // This only happens when the whole client area is invalidated, i.e., 
        // when the user types backspace, clears the buffer, or changes the 
        // font, or when the window is covered and uncovered.
        ExtTextOut (hDc, nxStartBuffer, YSTART, ETO_OPAQUE, 
            NULL, szOutputBuffer, nChars, NULL) ;
        
        // Write the whole text buffer in the line buffer rectangle
        // This happens every time the user enters a character, which 
        // is why this line always looks right, even for complex scripts.
        ExtTextOut (hDc, nxStartBuffer, nyStartBuffer, ETO_OPAQUE, 
            &rcBufferLine, szOutputBuffer, nChars, NULL) ;
        
        // Write out labels describing the text
        SelectObject(hDc, GetStockObject(ANSI_VAR_FONT)) ;
        SetTextAlign(hDc, TA_LEFT) ;
        GetTextMetrics (hDc, &tm) ;
        
        ExtTextOut (hDc, XSTART, YSTART-tm.tmHeight, ETO_OPAQUE, 
            NULL, szCharLabel, lstrlen(szCharLabel), NULL) ;

        ExtTextOut (hDc, XSTART, nyStartBuffer-tm.tmHeight, ETO_OPAQUE, 
            NULL, szBuffLabel, lstrlen(szBuffLabel), NULL) ;
        
        EndPaint (hWnd, &ps) ;
        
        return 0 ;
        
    case WM_COMMAND :
        
        switch (LOWORD(wParam)) 
        {
        case IDM_EDIT_CLEAR :
            // Clear the character buffer
            nChars = 0 ;
            
            // Reset starting point for next character output
            g_xStartOneChar = XSTART ;
            InvalidateRect (hWnd, NULL, TRUE) ;
            
            break ;
            
        case IDM_EDITCONTROL :
            // Use an edit control to enter and display text.
            // This is the recommended approach, because all
            // complex script processing is handled by the system.
            // Complex script support is also available in the 
            // Richedit control (not shown here).
            DialogBox (g_hInstance, MAKEINTRESOURCE(IDD_CSSAMPLE), NULL, EditDialogProc) ;
            
            break ;
            
        case IDM_EDIT_TOGGLEALIGN :
            // This aligns the text to the left or right
            // edge of the client area. It is NOT the same
            // as reading order.
            if (uiAlign & TA_RIGHT){
                uiAlign = uiAlign & ~TA_RIGHT ;
            } else {
                uiAlign = uiAlign | TA_RIGHT & ~TA_LEFT ;
            }
            
            InvalidateRect (hWnd, NULL, TRUE) ;
            
            break ;
            
        case IDM_EDIT_TOGGLEREADING :
            // This will set the reading order as LTR, as is used
            // for European and Asian scripts, or RTL, the most common
            // reading area in Middle Eastern scripts such as Arabic
            // and Hebrew.
            uiAlign ^= TA_RTLREADING ;
            InvalidateRect (hWnd, NULL, TRUE) ;
            
            break ;
            
        case IDM_EDIT_SETFONT :
            // Let the user change font.
            ChooseFont (&cf) ;
            if (hTextFont){
                DeleteObject (hTextFont) ;
            }
            
            hTextFont = CreateFontIndirect (&lf) ;
            
            if (NULL == hTextFont) {
                RcMessageBox (hWnd, IDS_CHOOSEFONT_FAILED, MB_ICONEXCLAMATION | MB_OK) ;
                break ;
            }
            
            RcMessageBox(hWnd, IDS_FONTCHANGED , MB_OK, lf.lfFaceName) ;
            
            // Reset starting point for next character output
            hDc = GetDC(hWnd) ;
            SelectObject(hDc, hTextFont) ;
            GetTextExtentPoint32(hDc, szOutputBuffer, nChars, &sOneChar) ;
            ReleaseDC(hWnd, hDc) ;
            g_xStartOneChar = sOneChar.cx + XSTART ;
            
            InvalidateRect (hWnd, NULL, TRUE) ;
            
            break ;
            
        case IDM_ABOUT_HELP :
            
            DialogBox (g_hInstance, MAKEINTRESOURCE(IDD_HELP), NULL, HelpDialogProc) ;
            
            break;
            
        case IDM_ABOUT_ABOUT :
            
            DialogBox (g_hInstance, MAKEINTRESOURCE(IDD_ABOUT), NULL, HelpDialogProc);
            
            break ;
            
        case IDM_EXIT :
            
            DestroyWindow (hWnd) ;
            
            break ;
            
        default :
            
            return 0 ;  
        }
        
        return 0 ;
        
        case WM_DESTROY :
            
            PostQuitMessage (0) ;
            
            return 0 ;
            
        default : 
            return (DefWindowProc(hWnd, message, wParam, lParam)) ;
   }
}

//
//   FUNCTION: BOOL CALLBACK EditDialogProc (HWND , UINT , WPARAM , LPARAM)
//
//   PURPOSE: Dialog procedure for the edit control dialog box.
//
//   COMMENTS:
//        This is standard processing for edit controls.
//
BOOL CALLBACK EditDialogProc (HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HFONT        hEditFont ;
    static CHOOSEFONT   cf ; 
    static LOGFONT      lf ;

    HWND                hWndEdit ;
    
    switch (uMsg)
    {
    case WM_INITDIALOG :
        
        InitializeFont (hDlg, 24, &cf, &lf) ;
        hEditFont = CreateFontIndirect (&lf) ;
        
        // Set font of edit control
        SendDlgItemMessage (hDlg, ID_EDITCONTROL, WM_SETFONT, 
            (WPARAM) hEditFont,  MAKELPARAM(TRUE, 0)) ;
        
        return TRUE ;
        
    case WM_CLOSE :
        
        EndDialog (hDlg, wParam) ; 
        
        return 0 ;
        
    case WM_COMMAND :
        
        switch (wParam)
        {
        case IDE_EDIT_FONT :
            
            if (hEditFont) {
                DeleteObject (hEditFont) ;
            }
            
            ChooseFont (&cf) ;
            hEditFont = CreateFontIndirect (&lf) ;
            
            SendDlgItemMessage (hDlg, ID_EDITCONTROL, WM_SETFONT, 
                (WPARAM) hEditFont,  MAKELPARAM(TRUE, 0)) ;
            
            break ;
            
        case IDE_CLEAR :
            
            hWndEdit = GetDlgItem (hDlg, ID_EDITCONTROL) ;
            SetWindowText (hWndEdit, TEXT("")) ;
            
            break ;
            
        case IDE_CLOSE :
            
            DeleteObject (hEditFont) ;
            EndDialog (hDlg, wParam) ; 
        }
    }
    
    return FALSE ;
}

//
//   FUNCTION: BOOL CALLBACK HelpDialogProc (HWND , UINT , WPARAM , LPARAM)
//
//   PURPOSE: Dialog procedure for the Help dialog box.
//
//   COMMENTS:
//        This does nothing but close the dialog box.
//
BOOL CALLBACK HelpDialogProc (HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE :
        
        EndDialog (hDlg, wParam) ; 
        return 0 ;
        
    case WM_COMMAND :
        
        switch (wParam)
        {
        case IDOK :
            
            EndDialog (hDlg, wParam) ; 
        }
    }
    
    return FALSE ;
}

//
//   FUNCTION: _tWinMain (HINSTANCE , HINSTANCE , LPTSTR , int)
//
//   PURPOSE: Standard WinMain function
//
//   COMMENTS:
//        The prototype is _tWinMain, so it can be compiled either as
//        a Unicode or an ANSI application. 
//
int WINAPI _tWinMain (HINSTANCE hInstance, HINSTANCE hPrev, 
                      LPSTR pszCmdLine, int nCmdShow) 
{
    TCHAR szAppName[] = TEXT("Complex Script Display") ;
    MSG msg ;
    HANDLE hAccelTable ;
    
    // Perform application initialization:
    if (!InitApplication (hInstance, szAppName)) {
        return FALSE ;
    }
    // Perform instance initialization:
    if (!InitInstance (hInstance, szAppName, nCmdShow)) {
        return FALSE ;
    }
    
    hAccelTable = LoadAccelerators (hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1)) ;
    
    if (!hAccelTable) {
        return 0 ;
    }
    
    // Main message loop:
    while (GetMessage (&msg, NULL, 0, 0)) 
    {
        if (!TranslateAccelerator (msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage (&msg) ;
            DispatchMessage (&msg) ;
        }
    }
    return 0 ;
} 

//
//   FUNCTION: InitializeFont (HWND , LONG , LPCHOOSEFONT , LPLOGFONT)
//
//   PURPOSE:  Fills in font structures with initial values. 
//
//   REMARKS:  Since it contains only assignment statements, this function does no
//             error checking, has no return value..
//
void InitializeFont (HWND hWnd, LONG lHeight, LPCHOOSEFONT lpCf, LPLOGFONT lpLf)
{
    lpCf->lStructSize   = sizeof (CHOOSEFONT) ;
    lpCf->hwndOwner     = hWnd ;
    lpCf->hDC           = NULL ;
    lpCf->lpLogFont     = lpLf;
    lpCf->iPointSize    = 10;
    lpCf->Flags         = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT
        | CF_NOSIZESEL ;
    lpCf->rgbColors     = RGB (0,0,0);
    lpCf->lCustData     = 0;
    lpCf->lpfnHook      = NULL;
    lpCf->lpTemplateName= NULL;
    lpCf->hInstance     = g_hInstance;
    lpCf->lpszStyle     = NULL;
    lpCf->nFontType     = SIMULATED_FONTTYPE;
    lpCf->nSizeMin      = 0;
    lpCf->nSizeMax      = 0;
    
    lpLf->lfHeight      = lHeight ; 
    lpLf->lfWidth       = 0 ; 
    lpLf->lfEscapement  = 0 ; 
    lpLf->lfOrientation = 0 ; 
    lpLf->lfWeight      = FW_NORMAL ; 
    lpLf->lfItalic      = FALSE ; 
    lpLf->lfUnderline   = FALSE ; 
    lpLf->lfStrikeOut   = FALSE ; 
    lpLf->lfCharSet     = DEFAULT_CHARSET ; 
    lpLf->lfOutPrecision= OUT_DEFAULT_PRECIS ; 
    lpLf->lfClipPrecision = CLIP_DEFAULT_PRECIS ; 
    lpLf->lfQuality     = DEFAULT_QUALITY ; 
    lpLf->lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE ; 
    lstrcpy(lpLf->lfFaceName, TEXT("Arial")) ;
    lpLf->lfFaceName[LF_FACESIZE] = 0 ; 
}

//
//   FUNCTION: InitApplication(HINSTANCE, LPTSTR)
//
//   PURPOSE:  Fills in window class structure with parameters that describe
//   the main window, and registers the window.
//
BOOL InitApplication (HINSTANCE hInstance, LPTSTR szAppName)
{
    
    WNDCLASS  wc ; 
    
    wc.style         = CS_HREDRAW | CS_VREDRAW ;
    wc.lpfnWndProc   = (WNDPROC) WndProc ;
    wc.cbClsExtra    = 0 ;
    wc.cbWndExtra    = 0 ;
    wc.hInstance     = hInstance ;
    wc.hIcon         = LoadIcon  (NULL, IDI_APPLICATION) ; 
    wc.hCursor       = LoadCursor  (NULL, IDC_ARROW) ;
    wc.hbrBackground =  (HBRUSH) (COLOR_WINDOW+1) ;
    wc.lpszMenuName  = MAKEINTRESOURCE (IDR_MENU1) ;
    wc.lpszClassName = szAppName ;
    
    return  (RegisterClass(&wc)) ;
}

//
//   FUNCTION: InitInstance (HANDLE, LPTSTR, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        This function saved the instance handle in a global variable and
//        created and displays the main program window.
//

BOOL InitInstance (HINSTANCE hInstance, LPTSTR szAppName, int nCmdShow)
{
    HWND hWnd ;
    
    g_hInstance = hInstance ; // Store instance handle in global variable
    
    LoadString (hInstance, IDS_TITLE, g_szTitle, MAX_MESSAGE) ;
    
    hWnd = CreateWindow (szAppName, g_szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
        NULL, NULL, hInstance, NULL) ;
    
    if (!hWnd) {
        return FALSE ;
    }
    
    ShowWindow (hWnd, nCmdShow) ;
    UpdateWindow (hWnd) ;
    
    return TRUE ;
}
//
//  Function RcMessageBox (HWND, INT, INT, ...)
//
//  Purpose: Display a message box with formated output similar to sprintf
//
//  Remarks:
//      This function loads the string identified by nMessageID from the 
//      resource segment, uses vsprintf to format it using the variable
//      parameters, and displays it to the user in a message box using the
//      icon specified by nIcons.
//

int RcMessageBox (HWND hWnd, int nMessageID, int nIcons, ...)
{
    // This can be changed to get the current lang id.
    WORD wCurrentLang = MAKELANGID (LANG_ENGLISH, SUBLANG_ENGLISH_US) ;
    TCHAR szLoadBuff[MAX_MESSAGE], szOutPutBuff[3*MAX_MESSAGE] ;
    va_list valArgs ;
    
    va_start (valArgs, nIcons) ;
    
    LoadString (g_hInstance, nMessageID, szLoadBuff, MAX_MESSAGE) ;
    
    wvsprintf (szOutPutBuff, szLoadBuff, valArgs) ;
    
    va_end (valArgs) ;
    
    return (MessageBoxEx (hWnd, szOutPutBuff, g_szTitle, nIcons, wCurrentLang)) ;
}

