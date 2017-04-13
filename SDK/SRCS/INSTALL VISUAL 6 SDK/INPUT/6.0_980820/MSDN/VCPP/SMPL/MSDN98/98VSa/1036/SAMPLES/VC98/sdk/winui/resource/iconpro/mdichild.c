/****************************************************************************\
*            
*     FILE:     MDIChild.C
*
*     PURPOSE:  IconPro Project MDI Child Window handling c file
*
*     COMMENTS: This file contains the MDI Child Window handling code
*
*     FUNCTIONS:
*      EXPORTS: 
*               IconChildWndProc   - Window Procedure for the MDI children
*      LOCALS:
*               Draw3DRect         - Draws a rectangle using 3D colors
*               EraseBackground    - Draws the MDI child's background
*               CreateChildren     - Creates MDI child's child windows
*               CreateChildListBox - Creates and shows a list box
*               AddFormatDlgProc   - Dialog Proc for AddFormat dialog
*
*     Copyright 1995 - 1997 Microsoft Corp.
*
*
* History:
*                July '95 - Created
*
\****************************************************************************/
#include <windows.h>
#include <commctrl.h>
#include "Icons.h"
#include "IconPro.h"
#include "Resource.h"
#include "MDIChild.H"


/****************************************************************************/
// External Globals
extern HINSTANCE    hInst;
extern HWND        	hWndMain, hMDIClientWnd;
/****************************************************************************/


/****************************************************************************/
// Prototypes for local functions
BOOL Draw3DRect( HDC hDC, RECT Rect, BOOL bSunken );
void EraseBackground( HWND hWnd, HDC hDC );
BOOL CreateChildren( HWND hWnd );
HWND CreateChildListBox( HWND hWndParent, UINT ID, LPRECT lpRect );
BOOL CALLBACK AddFormatDlgProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
/****************************************************************************/



/****************************************************************************
*
*     FUNCTION: IconChildWndProc
*
*     PURPOSE:  Window Procedure for MDI child window
*
*     PARAMS:   HWND hWnd     - This window handle
*               UINT Msg      - Which Message?
*               WPARAM wParam - message parameter
*               LPARAM lParam - message parameter
*
*     RETURNS:  LRESULT - depends on message
*
* History:
*                July '95 - Created
*
\****************************************************************************/
LRESULT CALLBACK IconChildWndProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    // Which message is it?
    switch( Msg )
    {
        // User pressed left mouse button
        // Should be re-generate the AND mask?
        case WM_LBUTTONDOWN:
        {
            LPCHILDWINDOWDATA	lpcwd;

            // Get the icon resource data aassociated with this window
            if( (lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA )) == NULL )
                break;

            // Do something only if the CNTRL key is pressed too
            if( MK_CONTROL & wParam )
            {
                POINTS	pts = MAKEPOINTS(lParam);
                POINT	pt;
                RECT    ImageRect;
                DWORD	nIndex;

                pt.x = pts.x; pt.y = pts.y;
                // Do we have some icon resource data?
                if( lpcwd->lpIR != NULL )
                {
                    // Which image is selected right now?
                    if( (nIndex = SendMessage( lpcwd->hWndFormatListBox, CB_GETCURSEL, 0, 0 )) != CB_ERR )
                    {
                        // Where is it drawn
                        ImageRect = GetXORImageRect( lpcwd->XORRect, &(lpcwd->lpIR->IconImages[nIndex]) );
                        // Is the mouse click in the image?
                        if( PtInRect( &ImageRect, pt ) )
                        {
                            HCURSOR	hOldCursor;

                            // This might take a while :(
                            hOldCursor = SetCursor( LoadCursor(NULL,IDC_WAIT) );
                            pt.x -= ImageRect.left;
                            pt.y -= ImageRect.top;
                            // generate the new AND mask
                            MakeNewANDMaskBasedOnPoint( &(lpcwd->lpIR->IconImages[nIndex]), pt );
                            // force a redraw
                            InvalidateRect( hWnd, NULL, TRUE );
                            //  Set changed flag
                            lpcwd->lpIR->bHasChanged = TRUE;
                            // finally, its over, put the cursor back
                            SetCursor( hOldCursor );
                        }
                    }
                }
            }
        }
        break; // End WM_LBUTTONDOWN

        // Time to say "Goodbye"
        case WM_CLOSE:
        {
            LPCHILDWINDOWDATA	lpcwd;
            TCHAR	szWindowTitle[MAX_PATH];

            // Get the data associated with this window
            lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA );
            // Is there data associated with this window?
            if( lpcwd != NULL )
            {
                // Does the data include an icon resource
                if( lpcwd->lpIR != NULL )
                {
                    // Has the resource changed?
                    if( lpcwd->lpIR->bHasChanged )
                    {
                        // Get the title for the message box
                        GetWindowText( hWnd, szWindowTitle, MAX_PATH );
                        if( lstrlen( szWindowTitle ) < 1 )
                            lstrcpy( szWindowTitle, "UnKnown" );
                        // User want to save changes?
                        switch( MessageBox( hWnd, "Icon has Changed, Save Changes?", szWindowTitle, MB_ICONSTOP | MB_YESNOCANCEL ) )
                        {
                            case IDYES:
                                SendMessage( hWnd, WM_COMMAND, ID_FILE_SAVE, 0 );
                                // Fall through to IDNO and kill window
                            case IDNO:
                                DefMDIChildProc( hWnd, Msg, wParam, lParam );
                                return 0;
                            break;
                            case IDCANCEL:
                                return 1;
                            break;
                        }
                    }
                }
            }
            DefMDIChildProc( hWnd, Msg, wParam, lParam );
            return 0;
        }
        break; // End WM_CLOSE

        // We are being created
        case WM_CREATE:
        {
            LPCHILDWINDOWDATA	lpcwd;

            // Need new data for this new window
            lpcwd = malloc( sizeof( CHILDWINDOWDATA ) );
            SetWindowLong( hWnd, GWL_USERDATA, (LONG)lpcwd );
            lpcwd->lpIR = NULL;
            // If a resource was passed in, use it
            if( (LPVOID)lParam != NULL )
                lpcwd->lpIR = (LPICONRESOURCE)(((MDICREATESTRUCT *)(((CREATESTRUCT *)lParam)->lpCreateParams))->lParam);
            // If no resource was passed in, do minimal initialization
            if( lpcwd->lpIR == NULL )
            {
                lpcwd->lpIR = malloc(sizeof(ICONRESOURCE));
                lstrcpy( lpcwd->lpIR->szOriginalICOFileName, "Untitled" );
                lstrcpy( lpcwd->lpIR->szOriginalDLLFileName, "" );
                lpcwd->lpIR->nNumImages = 0;
            }
            // Nothing has changed
            lpcwd->lpIR->bHasChanged = FALSE;
            // Create the list box, etc
            CreateChildren( hWnd );
            return DefMDIChildProc( hWnd, Msg, wParam, lParam );
        }
        break; // End WM_CREATE

        // Won't let window get too small to show our main area
        case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO    lpmmi = (LPMINMAXINFO)lParam;

            lpmmi->ptMinTrackSize.x = WINDOW_WIDTH;
            lpmmi->ptMinTrackSize.y = WINDOW_HEIGHT;
            return 0;
        }
        break; // End WM_GETMINMAXINFO

        // Yikes! We're being destroyed!
        case WM_DESTROY:
        {
            LPCHILDWINDOWDATA	lpcwd;

            // Get the data associated with this window 
            lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA );
            // Is there some?
            if( lpcwd != NULL )
            {
                // Is there a resource?
                if( lpcwd->lpIR != NULL )
                {
                    UINT i;

                    // Free all the bits
                    for( i=0; i< lpcwd->lpIR->nNumImages; i++ )
                    {
                        if( lpcwd->lpIR->IconImages[i].lpBits != NULL )
                            free( lpcwd->lpIR->IconImages[i].lpBits );
                    }
                    free( lpcwd->lpIR );
                }
                free( lpcwd );
            }
            SetWindowLong( hWnd, GWL_USERDATA, 0 );
        }
        break; // End WM_DESTROY

        // Draw our background (white and black squares, etc)
        case WM_ERASEBKGND:
            EraseBackground( hWnd, (HDC)wParam );
            return 1;
        break; // End WM_ERASEBKGND

        // Ok, time to paint
        case WM_PAINT:
        {
            LPCHILDWINDOWDATA	lpcwd;
            HDC                	hDC;
            PAINTSTRUCT        	ps;
            DWORD            	nIndex;
            HICON            	hIcon = NULL;

            // Obligatory BeginPaint()
            hDC = BeginPaint( hWnd, &ps );
            // Get the data associated with this window
            lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA );
            // Is there some?
            if( lpcwd != NULL )
            {
                // Is there a resource?
                if( lpcwd->lpIR != NULL )
                {
                    // Which image is selected?
                    if( (nIndex = SendMessage( lpcwd->hWndFormatListBox, CB_GETCURSEL, 0, 0 )) != CB_ERR )
                    {
                        int        	Width, Height;

                        // Get an HICON for the currently selected image
                        hIcon = MakeIconFromResource( &(lpcwd->lpIR->IconImages[nIndex]) );
                        // How big is the icon?
                        Width = lpcwd->lpIR->IconImages[nIndex].Width;
                        Height = lpcwd->lpIR->IconImages[nIndex].Height;
                        // Check to see if the icon is NULL
                        // If it is, consider it "unsupported"
                        // In the future, maybe we should look into MakeIconFromResource() and
                        // see why it is null - it may be for another reason than "unsupported"
                        if( hIcon == NULL )
                        {
                            SIZE    Size, Position;

                            // Draw some text in the black rect
                            SetTextColor( hDC, RGB(255,255,255) );
                            GetTextExtentPoint32( hDC, "Unsupported", 11, &Size );
                            Position.cx = lpcwd->BlackRect.left + ((RectWidth(lpcwd->BlackRect)-Size.cx)/2);
                            Position.cy = lpcwd->BlackRect.top + (RectHeight(lpcwd->BlackRect)/2) - Size.cy;
                            TextOut( hDC, Position.cx, Position.cy, "Unsupported", 11 );
                            GetTextExtentPoint32( hDC, "Format", 6, &Size );
                            Position.cx = lpcwd->BlackRect.left + ((RectWidth(lpcwd->BlackRect)-Size.cx)/2);
                            Position.cy = lpcwd->BlackRect.top + (RectHeight(lpcwd->BlackRect)/2) + 1;
                            TextOut( hDC, Position.cx, Position.cy, "Format", 6 );

                            // Draw some text in the white rect
                            SetTextColor( hDC, RGB(0,0,0) );
                            GetTextExtentPoint32( hDC, "Unsupported", 11, &Size );
                            Position.cx = lpcwd->WhiteRect.left + ((RectWidth(lpcwd->WhiteRect)-Size.cx)/2);
                            Position.cy = lpcwd->WhiteRect.top + (RectHeight(lpcwd->WhiteRect)/2) - Size.cy;
                            TextOut( hDC, Position.cx, Position.cy, "Unsupported", 11 );
                            GetTextExtentPoint32( hDC, "Format", 6, &Size );
                            Position.cx = lpcwd->WhiteRect.left + ((RectWidth(lpcwd->WhiteRect)-Size.cx)/2);
                            Position.cy = lpcwd->WhiteRect.top + (RectHeight(lpcwd->WhiteRect)/2) + 1;
                            TextOut( hDC, Position.cx, Position.cy, "Format", 6 );
                        }
                        else
                        {
                            // Draw it on the black background
                            DrawIconEx( hDC, lpcwd->BlackRect.left + ((RectWidth(lpcwd->BlackRect)-Width)/2),
                                            lpcwd->BlackRect.top + ((RectHeight(lpcwd->BlackRect)-Height)/2), 
                                            hIcon, Width, Height, 0, NULL, DI_NORMAL );
                            // Draw it on the white background
                            DrawIconEx( hDC, lpcwd->WhiteRect.left + ((RectWidth(lpcwd->WhiteRect)-Width)/2),
                                            lpcwd->WhiteRect.top + ((RectHeight(lpcwd->WhiteRect)-Height)/2), 
                                            hIcon, Width, Height, 0, NULL, DI_NORMAL );
                        }
                        // Draw just the XOR mask
                        DrawXORMask( hDC, lpcwd->XORRect, &(lpcwd->lpIR->IconImages[nIndex]) );
                        // Draw just the AND mask
                        DrawANDMask( hDC, lpcwd->ANDRect, &(lpcwd->lpIR->IconImages[nIndex]) );
                        // Kill the icon, we're one with it
                        if( hIcon != NULL )
                            DestroyIcon( hIcon );
                    }
                }
            }
            // Obligtory EndPaint()
            EndPaint( hWnd, &ps );
        }
        break; // End WM_PAINT

        // WM_COMMAND - menu options, etc
        case WM_COMMAND:
            // which one is it?
            switch( LOWORD(wParam) )
            {
                // Edit->Export BMP - write icon image as BMP file
                case ID_EDIT_EXPORTBMP:
                {
                    LPCHILDWINDOWDATA	lpcwd;
                    DWORD            	nIndex;
                    TCHAR            	szFileName[MAX_PATH];

                    // Get the data associated this window 
                    lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA );
                    // If we have some data, including an icon resource
                    if( (lpcwd != NULL ) && (lpcwd->lpIR != NULL) && (lpcwd->hWndFormatListBox!= NULL) )
                    {
                        // Which image is currently selected?
                        if( (nIndex = SendMessage( lpcwd->hWndFormatListBox, CB_GETCURSEL, 0, 0 )) != CB_ERR )
                        {
                            // Get the name of the file from which to import the image
                            if( GetSaveIconFileName( szFileName, IDS_BMPFILTERSTRING, "Export to BMP File" ) )
                            {
                                HCURSOR	hOldCursor;

                                // This might take a while :(
                                hOldCursor = SetCursor( LoadCursor(NULL,IDC_WAIT) );
                                IconImageToBMPFile( szFileName, &(lpcwd->lpIR->IconImages[nIndex]) );
                                SetCursor( hOldCursor );
                            }
                        }
                    }
                }
                break; // End ID_EDIT_EXPORTBMP

                // Edit->Import BMP and Edit->Stretch-Import BMP - convert BMP file to icon
                case ID_EDIT_IMPORTBMP:
                case ID_EDIT_STRETCHIMPORTBMP:
                {
                    LPCHILDWINDOWDATA	lpcwd;
                    DWORD            	nIndex;
                    TCHAR            	szFileName[MAX_PATH];

                    // Get the data associated this window 
                    lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA );
                    // If we have some data, including an icon resource
                    if( (lpcwd != NULL ) && (lpcwd->lpIR != NULL) && (lpcwd->hWndFormatListBox!= NULL) )
                    {
                        // Which image is currently selected?
                        if( (nIndex = SendMessage( lpcwd->hWndFormatListBox, CB_GETCURSEL, 0, 0 )) != CB_ERR )
                        {
                            // Get the name of the file from which to import the image
                            if( GetOpenIconFileName( szFileName, IDS_BMPFILTERSTRING, "Import from BMP File" ) )
                            {
                                HCURSOR	hOldCursor;

                                // This might take a while :(
                                hOldCursor = SetCursor( LoadCursor(NULL,IDC_WAIT) );
                                // Import the BMP image data
                                if( IconImageFromBMPFile( szFileName, &(lpcwd->lpIR->IconImages[nIndex]), (LOWORD(wParam)==ID_EDIT_STRETCHIMPORTBMP)?TRUE:FALSE ) )
                                {
                                    // which, of course, changes things
                                    lpcwd->lpIR->bHasChanged = TRUE;
                                    // Force a repaint
                                    InvalidateRect( hWnd, NULL, TRUE );
                                }
                                SetCursor( hOldCursor );
                            }
                        }
                    }
                }
                break; // End ID_EDIT_IMPORTBMP/ID_EDIT_STRETCHIMPORTBMP

                // User wants to add an image format
                case ID_EDIT_ADDFORMAT:
                {
                    LPICONIMAGE	lpii;
                    TCHAR	szBuffer[256];
                    
                    // Launch the dialog to ask which size and color depth
                    if( DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_ADDFORMATDLG), hWndMain, AddFormatDlgProc, (LPARAM)(&lpii) ) )
                    {
                        LPCHILDWINDOWDATA	lpcwd;
                        LPICONRESOURCE    	lpNewIR;
                        DWORD            	nIndex, i;

                        // Get the data associated this window 
                        lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA );
                        // If we have some data, including an icon resource
                        if( (lpcwd != NULL ) && (lpcwd->lpIR != NULL) && (lpcwd->hWndFormatListBox!= NULL) )
                        {
                            // Need to see if the new format already exists in the resource
                            // We don't want dupes, so check each image for dupe
                            for(i=0;i<lpcwd->lpIR->nNumImages;i++)
                            {
                                // Is it the same as the new one?
                                if( (lpcwd->lpIR->IconImages[i].Width==lpii->Width) &&
                                    (lpcwd->lpIR->IconImages[i].Height==lpii->Height) && 
                                    (lpcwd->lpIR->IconImages[i].Colors==lpii->Colors) )
                                {
                                    // Yikes! It is - bail and select the old one
                                    MessageBox( hWnd, "That format already exists - format not added", "Error", MB_OK );
                                    SendMessage( lpcwd->hWndFormatListBox, 	CB_SETCURSEL, (WPARAM)i, (LPARAM)0 );
                                    break;
                                }
                            }
                            // Need bigger block of memory to hold an extra image format
                            lpNewIR = malloc( sizeof( ICONRESOURCE ) + ( ( lpcwd->lpIR->nNumImages + 1) * sizeof(ICONIMAGE) ) );
                            // Of course this changes things
                            lpNewIR->bHasChanged = TRUE;
                            // Copy old to new
                            lstrcpy( lpNewIR->szOriginalICOFileName, lpcwd->lpIR->szOriginalICOFileName );
                            lstrcpy( lpNewIR->szOriginalDLLFileName, lpcwd->lpIR->szOriginalDLLFileName );
                            lpNewIR->nNumImages = lpcwd->lpIR->nNumImages + 1;
                            for(i=0;i<lpcwd->lpIR->nNumImages;i++)
                            {
                                memcpy( &(lpNewIR->IconImages[i]), &(lpcwd->lpIR->IconImages[i]), sizeof( ICONIMAGE ) );
                            }
                            // Add in the new one
                            memcpy( &(lpNewIR->IconImages[i]), lpii, sizeof( ICONIMAGE ) );
                            // Add this new one to the list box
                            wsprintf( szBuffer, "%dx%d, %d Bit Color", lpii->Width, lpii->Height, lpii->Colors );
                            nIndex = SendMessage( lpcwd->hWndFormatListBox, CB_ADDSTRING, 0, (LPARAM)szBuffer );
                            // Select the new one
                            SendMessage( lpcwd->hWndFormatListBox, 	CB_SETCURSEL, (WPARAM)i, (LPARAM)0 );
                            // clean up
                            free( lpii );
                            free( lpcwd->lpIR );
                            lpcwd->lpIR = lpNewIR;
                            // Create a nice new blank image for this format
                            CreateBlankNewFormatIcon( &(lpcwd->lpIR->IconImages[i]) );
                            // force a repaint
                            InvalidateRect( hWnd, NULL, TRUE );
                        }
                    }
                }
                break; // End WM_COMMAND -> ID_EDIT_ADDFORMAT
                
                // User wants to remove an image format
                case ID_EDIT_REMOVEFORMAT:
                {
                    LPCHILDWINDOWDATA	lpcwd;
                    DWORD            	nIndex, i;
                    LPICONRESOURCE    	lpNewIR;

                    // Get the data associated this window 
                    lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA );
                    // If we have some data, including an icon resource
                    if( (lpcwd != NULL ) && (lpcwd->lpIR != NULL) && (lpcwd->hWndFormatListBox!= NULL) )
                    {
                        // Which image is currently selected?
                        if( (nIndex = SendMessage( lpcwd->hWndFormatListBox, CB_GETCURSEL, 0, 0 )) != CB_ERR )
                        {
                            // Remove the entry from the list box
                            SendMessage( lpcwd->hWndFormatListBox, CB_DELETESTRING, nIndex, 0 );
                            // Need less memory now
                            lpNewIR = malloc( sizeof( ICONRESOURCE ) + ( ( lpcwd->lpIR->nNumImages - 1) * sizeof(ICONIMAGE) ) );
                            // Of course this changes things
                            lpNewIR->bHasChanged = TRUE;
                            // Copy old to new
                            lstrcpy( lpNewIR->szOriginalICOFileName, lpcwd->lpIR->szOriginalICOFileName );
                            lstrcpy( lpNewIR->szOriginalDLLFileName, lpcwd->lpIR->szOriginalDLLFileName );
                            lpNewIR->nNumImages = lpcwd->lpIR->nNumImages - 1;
                            // Copy the rest of the images from old to new
                            for(i=0;i<nIndex;i++)
                            {
                                memcpy( &(lpNewIR->IconImages[i]), &(lpcwd->lpIR->IconImages[i]), sizeof( ICONIMAGE ) );
                            }
                            for(;i<lpcwd->lpIR->nNumImages-1;i++)
                            {
                                memcpy( &(lpNewIR->IconImages[i]), &(lpcwd->lpIR->IconImages[i+1]), sizeof( ICONIMAGE ) );
                            }
                            // Clean up
                            free( lpcwd->lpIR );
                            lpcwd->lpIR = lpNewIR;
                            // Select a different image
                            if( --nIndex < 0 ) nIndex = 0;
                            SendMessage( lpcwd->hWndFormatListBox, CB_SETCURSEL, (WPARAM)nIndex, 0 );
                            // Force a repaint
                            InvalidateRect( hWnd, NULL, TRUE );
                        }
                    }
                }
                break; // End WM_COMMAND -> ID_EDIT_REMOVEFORMAT

                // User wants to paste CF_DIB from clipboard into current image
                case ID_EDIT_STRETCHPASTE:
                case ID_EDIT_PASTE:
                {
                    LPCHILDWINDOWDATA	lpcwd;
                    DWORD            	nIndex;

                    // Get the data associated this window 
                    lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA );
                    // If we have some data, including an icon resource
                    if( (lpcwd != NULL ) && (lpcwd->lpIR != NULL) && (lpcwd->hWndFormatListBox!= NULL) )
                    {
                        // Which image is currently selected?
                        if( (nIndex = SendMessage( lpcwd->hWndFormatListBox, CB_GETCURSEL, 0, 0 )) != CB_ERR )
                        {
                            HCURSOR	hOldCursor;

                            // This might take a while :(
                            hOldCursor = SetCursor( LoadCursor(NULL,IDC_WAIT) );

                            // Paste over it from the clipboard
                            if( IconImageFromClipBoard( &(lpcwd->lpIR->IconImages[nIndex]), LOWORD(wParam)!=ID_EDIT_PASTE ) )
                                // which, of course, changes things
                                lpcwd->lpIR->bHasChanged = TRUE;
                            // Force a repaint
                            InvalidateRect( hWnd, NULL, TRUE );
                            SetCursor( hOldCursor );
                        }
                    }
                }
                break; // End WM_COMMAND -> ID_EDIT_STRETCHPASTE/ID_EDIT_PASTE

                // Put current image on the clipboard in CF_DIB format
                case ID_EDIT_COPY:
                {
                    LPCHILDWINDOWDATA	lpcwd;
                    DWORD            	nIndex;

                    // Get the data associated this window 
                    lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA );
                    // If we have some data, including an icon resource
                    if( (lpcwd != NULL ) && (lpcwd->lpIR != NULL) && (lpcwd->hWndFormatListBox!= NULL) )
                    {
                        // Which image is currently selected?
                        if( (nIndex = SendMessage( lpcwd->hWndFormatListBox, CB_GETCURSEL, 0, 0 )) != CB_ERR )
                        {
                            // Send this image to the clipboard
                            IconImageToClipBoard( &(lpcwd->lpIR->IconImages[nIndex]) );
                        }
                    }
                }
                break; // End WM_COMMAND -> ID_EDIT_COPY

                // The filename has changed, update the window title
                case ID_UPDATETITLE:
                {
                    TCHAR	szFileTitle[MAX_PATH];
                    LPCHILDWINDOWDATA	lpcwd;

                    // Get the data associated this window 
                    lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA );
                    // If we have some data
                    if( lpcwd != NULL )
                    {
                        // including an icon resource
                        if( lpcwd->lpIR != NULL )
                        {
                            // The calculate and set the new title
                            if( GetFileTitle( lpcwd->lpIR->szOriginalICOFileName, szFileTitle, MAX_PATH ) == 0 )
                            {
                                SetWindowText( hWnd, szFileTitle );
                            }
                        }
                    }
                }
                break; // End WM_COMMAND -> ID_UPDATETITLE

                // How many image formats in the icon resource? (return that number)
                case ID_GETNUMFORMATS:
                {
                    LPCHILDWINDOWDATA	lpcwd;
                    UINT nNum = 0;

                    // Get the data associated this window 
                    lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA );
                    // If we have some data
                    if( lpcwd != NULL )
                    {
                        // If we have a listbox, get its count, else 0
                        if( lpcwd->hWndFormatListBox != NULL )
                            nNum = (UINT)SendMessage( lpcwd->hWndFormatListBox, CB_GETCOUNT, 0, 0 );
                        else
                            nNum = 0;
                        // If an error occurred, default to 0
                        if( nNum == (UINT)CB_ERR )
                            nNum = 0;
                    }
                    // Send it back
                    return nNum;
                }
                break; // End WM_COMMAND -> ID_GETNUMFORMATS

                // Has this icon resource changed? return TRUE=yes, FALSE=no
                case ID_HASFILECHANGED:
                {
                    LPCHILDWINDOWDATA	lpcwd;
                    UINT nRet = 0;

                    // Get the data associated this window 
                    lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA );
                    // If we have some data
                    if( lpcwd != NULL )
                        // And it includes an icon resource
                        if( lpcwd->lpIR != NULL )
                            // then check whether it has changed
                            return lpcwd->lpIR->bHasChanged == TRUE;
                    // Otherwise, return FALSE
                    return nRet;
                }
                break; // End WM_COMMAND -> ID_HASFILECHANGED

                // Handle selection changes, etc from listbox
                case ID_FORMAT_BOX:
                    switch( HIWORD(wParam) )
                    {
                        // If a selection is made, or changes, repaint
                        case CBN_SELCHANGE:
                        case CBN_SELENDOK:
                            InvalidateRect( hWnd, NULL, TRUE );
                        break;
                    }
                break; // End WM_COMMAND -> ID_FORMAT_BOX
            
                // User wants to save the ICO file
                case ID_FILE_SAVEAS:
                case ID_FILE_SAVE:
                {
                    TCHAR	szFileName[MAX_PATH];
                    LPCHILDWINDOWDATA	lpcwd;

                    // Get the data associated this window 
                    if( ( lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA ) ) != NULL )
                    {
                        // See if it includes an icon resource
                        if( lpcwd->lpIR != NULL )
                        {
                            HCURSOR	hOldCursor;

                            // This might take a while :(
                            hOldCursor = SetCursor( LoadCursor(NULL,IDC_WAIT) );

                            // If we have an original filename, and user did *NOT* 'Save As'
                            if( ( lstrlen(lpcwd->lpIR->szOriginalICOFileName) > 0 ) && (LOWORD(wParam)!=ID_FILE_SAVEAS) )
                            {
                                // The just write it out
                                WriteIconToICOFile( lpcwd->lpIR, lpcwd->lpIR->szOriginalICOFileName );
                                // which, of course, brings it up to date
                                lpcwd->lpIR->bHasChanged = FALSE;
                            }
                            else
                            {
                                // Either we have no name, or user hit 'Save As'
                                if( GetSaveIconFileName( szFileName, IDS_FILTERSTRING, LOWORD(wParam)==ID_FILE_SAVE?"Save Icon File":"Save Icon File As" ) )
                                {
                                    // So, write it out
                                    WriteIconToICOFile( lpcwd->lpIR, szFileName );
                                    // Update the name associated with the resource
                                    lstrcpy( lpcwd->lpIR->szOriginalICOFileName, szFileName );
                                    // Inform window to update title
                                    SendMessage( hWnd, WM_COMMAND, ID_UPDATETITLE, 0 );
                                    // and, of course, it is now up to date
                                    lpcwd->lpIR->bHasChanged = FALSE;
                                }
                            }
                            SetCursor( hOldCursor );
                        }
                        else
                            MessageBox( hWnd, "Error Getting Icon Info - File Not Saved", "Error", MB_OK );
                    }
                }
                break; // End WM_COMMAND -> ID_FILE_SAVE/ID_FILE_SAVEAS
            }
        break; // End WM_COMMAND
    }
    return DefMDIChildProc( hWnd, Msg, wParam, lParam );
}
/* End IconChildWndProc() **************************************************/




/****************************************************************************
*
*     FUNCTION: Draw3DRect
*
*     PURPOSE:  draws a rectangle in 3d colors
*
*     PARAMS:   HDC hDC      - The DC on which to draw
*               RECT Rect    - The rectangle itself
*               BOOL bSunken - TRUE  = rect should look sunken
*                              FALSE = rect should look raised
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL Draw3DRect( HDC hDC, RECT Rect, BOOL bSunken )
{
    HBRUSH	hBrush;
    HPEN    hPen, hOldPen;

    // Get the color for the main foreground
    hBrush = CreateSolidBrush( GetSysColor(COLOR_3DFACE) );
    // paint it
    FillRect( hDC, &Rect, hBrush );
    DeleteObject( hBrush );
    // Get the pen for the top and left sides
    if( bSunken )
        hPen = CreatePen( PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW) );
    else
        hPen = CreatePen( PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT) );
    hOldPen = SelectObject( hDC, hPen);
    // Draw the top and left sides
    MoveToEx( hDC, Rect.right, Rect.top, NULL );
    LineTo( hDC, Rect.left, Rect.top );
    LineTo( hDC, Rect.left, Rect.bottom );
    SelectObject( hDC, hOldPen);
    DeleteObject( hPen );
    // Get the pen for the bottom and right sides
    if( bSunken )
        hPen = CreatePen( PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT) );
    else
        hPen = CreatePen( PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW) );
    hOldPen = SelectObject( hDC, hPen);
    // Draw the bottom and right sides
    LineTo( hDC, Rect.right, Rect.bottom );
    LineTo( hDC, Rect.right, Rect.top );
    SelectObject( hDC, hOldPen);
    DeleteObject( hPen );
    return TRUE;
}
/* End Draw3DRect() *******************************************************/




/****************************************************************************
*
*     FUNCTION: EraseBackground
*
*     PURPOSE:  Draws the background for the MDI child
*
*     PARAMS:   HWND hWnd - The MDI window of interest
*               HDC  hDC  - The DC on which to draw
*
*     RETURNS:  void
*
* History:
*                July '95 - Created
*
\****************************************************************************/
void EraseBackground( HWND hWnd, HDC hDC )
{
    RECT                Rect;
    LPCHILDWINDOWDATA	lpcwd;
    HBRUSH            	hBrush;
    SIZE                TextSize;

    // Just how big is this window?
    GetClientRect( hWnd, &Rect );
    // Paint the background
    Draw3DRect( hDC, Rect, FALSE );

    // If there is no icon resource yet, bail out
    if( ( lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA ) ) == NULL )
        return;
    // Draw 3d rectangles around areas of interest
    Draw3DRect( hDC, lpcwd->WhiteRect, TRUE );
    Draw3DRect( hDC, lpcwd->WhiteTextRect, TRUE );
    Draw3DRect( hDC, lpcwd->BlackRect, TRUE );
    Draw3DRect( hDC, lpcwd->BlackTextRect, TRUE );
    Draw3DRect( hDC, lpcwd->XORRect, TRUE );
    Draw3DRect( hDC, lpcwd->XORTextRect, TRUE );
    Draw3DRect( hDC, lpcwd->ANDRect, TRUE );
    Draw3DRect( hDC, lpcwd->ANDTextRect, TRUE );
    // Fill in the white area
    hBrush = GetStockObject( WHITE_BRUSH );
    SelectObject( hDC, hBrush );
    Rectangle( hDC, lpcwd->WhiteRect.left, lpcwd->WhiteRect.top, lpcwd->WhiteRect.right, lpcwd->WhiteRect.bottom );
    // Fill in the black area
    hBrush = GetStockObject( BLACK_BRUSH );
    SelectObject( hDC, hBrush );
    Rectangle( hDC, lpcwd->BlackRect.left, lpcwd->BlackRect.top, lpcwd->BlackRect.right, lpcwd->BlackRect.bottom );

    // Set texts for the various sections
    SetBkMode( hDC, TRANSPARENT );
    GetTextExtentPoint32( hDC, "Icon On Black", 13, &TextSize );
    TextOut( hDC, lpcwd->BlackTextRect.left + ((RectWidth(lpcwd->BlackTextRect)-TextSize.cx)/2),
                    lpcwd->BlackTextRect.top + ((RectHeight(lpcwd->BlackTextRect)-TextSize.cy)/2), "Icon On Black", 13 );
    GetTextExtentPoint32( hDC, "Icon On White", 13, &TextSize );
    TextOut( hDC, lpcwd->WhiteTextRect.left + ((RectWidth(lpcwd->WhiteTextRect)-TextSize.cx)/2),
                    lpcwd->WhiteTextRect.top + ((RectHeight(lpcwd->WhiteTextRect)-TextSize.cy)/2), "Icon On White", 13 );
    GetTextExtentPoint32( hDC, "XOR Mask", 8, &TextSize );
    TextOut( hDC, lpcwd->XORTextRect.left + ((RectWidth(lpcwd->XORTextRect)-TextSize.cx)/2),
                    lpcwd->XORTextRect.top + ((RectHeight(lpcwd->XORTextRect)-TextSize.cy)/2), "XOR Mask", 8 );
    GetTextExtentPoint32( hDC, "AND Mask", 8, &TextSize );
    TextOut( hDC, lpcwd->ANDTextRect.left + ((RectWidth(lpcwd->ANDTextRect)-TextSize.cx)/2),
                    lpcwd->ANDTextRect.top + ((RectHeight(lpcwd->ANDTextRect)-TextSize.cy)/2), "AND Mask", 8 );
}
/* End EraseBackground() ***************************************************/




/****************************************************************************
*
*     FUNCTION: CreateChildren
*
*     PURPOSE:  Create the listbox, fills it with entries
*
*     PARAMS:   HWND hWnd - The MDI window of interest
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL CreateChildren( HWND hWnd )
{
    RECT                ClientRect, TempRect;
    LPCHILDWINDOWDATA	lpcwd;
    HDC                	hDC;
    SIZE                size;

    // Get the data associated with this window
    if( (lpcwd = (LPCHILDWINDOWDATA)GetWindowLong( hWnd, GWL_USERDATA )) == NULL )
        return FALSE;
    // Just how big is this window?
    GetClientRect( hWnd, &ClientRect );
    // Calculate listbox size and position
    SetRect( &(lpcwd->BoxRect), 10, ClientRect.bottom-30, (MAX_ICON_WIDTH*2)+14, ClientRect.bottom+50 );
    // Create the listbox
    if((lpcwd->hWndFormatListBox=CreateChildListBox( hWnd, ID_FORMAT_BOX, &(lpcwd->BoxRect) )) == NULL )
        return FALSE;
    // If we have an icon resource
    if( lpcwd->lpIR != NULL )
    {
        UINT    i, nIndex;
        TCHAR	szBuffer[256];

        // For each image in the resoure
        for(i=0;i<lpcwd->lpIR->nNumImages;i++)
        {
            // Add the type of the image to the listbox
            wsprintf( szBuffer, "%dx%d, %d Bit Color", lpcwd->lpIR->IconImages[i].Width, 
                        lpcwd->lpIR->IconImages[i].Height, lpcwd->lpIR->IconImages[i].Colors );
            nIndex = SendMessage( lpcwd->hWndFormatListBox, CB_ADDSTRING, 0, (LPARAM)szBuffer );
        }
        // Select the first entry
        SendMessage( lpcwd->hWndFormatListBox, 	CB_SETCURSEL, (WPARAM)0, (LPARAM)0 );
    }
    // Adjust the box size based on the listbox's real size
    GetClientRect( lpcwd->hWndFormatListBox, &TempRect );
    lpcwd->BoxRect.bottom = lpcwd->BoxRect.top + TempRect.bottom;

    // How big is text these days?
    hDC = GetDC( hWnd );
    GetTextExtentPoint32( hDC, "Icon on Black", 13, &size );
    ReleaseDC( hWnd, hDC );

    // Set the rectangles for the various squares to be drawn later
#define DIVIDER 5
    SetRect( &(lpcwd->DrawingRect), 10, 10, (MAX_ICON_WIDTH*2)+14, 20 + (MAX_ICON_HEIGHT*2) + (TempRect.bottom*2) );
    SetRect( &(lpcwd->BlackRect), lpcwd->DrawingRect.left, lpcwd->DrawingRect.top, lpcwd->DrawingRect.left + MAX_ICON_WIDTH + 1, lpcwd->DrawingRect.top + MAX_ICON_HEIGHT + 1 );
    SetRect( &(lpcwd->BlackTextRect), lpcwd->BlackRect.left, lpcwd->BlackRect.bottom+1, lpcwd->BlackRect.right, lpcwd->BlackRect.bottom + TempRect.bottom + 1 );
    SetRect( &(lpcwd->WhiteRect), lpcwd->BlackRect.right+1, lpcwd->BlackRect.top, lpcwd->DrawingRect.right, lpcwd->BlackRect.bottom );
    SetRect( &(lpcwd->WhiteTextRect), lpcwd->WhiteRect.left, lpcwd->WhiteRect.bottom+1, lpcwd->WhiteRect.right, lpcwd->WhiteRect.bottom + TempRect.bottom + 1 );
    SetRect( &(lpcwd->XORRect),	lpcwd->BlackTextRect.left, lpcwd->BlackTextRect.bottom + 1 + DIVIDER, lpcwd->BlackRect.right, lpcwd->BlackTextRect.bottom + 2 + DIVIDER + MAX_ICON_HEIGHT ); 
    SetRect( &(lpcwd->XORTextRect),	lpcwd->XORRect.left, lpcwd->XORRect.bottom + 1, lpcwd->XORRect.right, lpcwd->DrawingRect.bottom ); 
    SetRect( &(lpcwd->ANDRect),	lpcwd->WhiteTextRect.left, lpcwd->WhiteTextRect.bottom + 1 + DIVIDER, lpcwd->WhiteRect.right, lpcwd->WhiteTextRect.bottom + 2 + DIVIDER + MAX_ICON_HEIGHT ); 
    SetRect( &(lpcwd->ANDTextRect),	lpcwd->ANDRect.left, lpcwd->ANDRect.bottom + 1, lpcwd->ANDRect.right, lpcwd->DrawingRect.bottom ); 
#undef DIVIDER

    return TRUE;
}
/* End CreateChildren() ****************************************************/




/****************************************************************************
*
*     FUNCTION: CreateChildListBox
*
*     PURPOSE:  Creates a listbox and shows it
*
*     PARAMS:   HWND   hWndParent - The MDI window to be a parent
*               UINT   ID         - the ID of the new listbox
*               LPRECT lpRect     - the RECT for the listbox
*
*     RETURNS:  HWND - handle to listbox window, NULL for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
HWND CreateChildListBox( HWND hWndParent, UINT ID, LPRECT lpRect )
{
    HWND hWnd;

    hWnd = CreateWindow( "COMBOBOX", "", CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL | WS_CHILD | WS_VSCROLL,
                        lpRect->left, lpRect->top, 
                        lpRect->right - lpRect->left + 1, lpRect->bottom - lpRect->top + 1,
                        hWndParent, (HMENU)ID, hInst, 0 );
    if( hWnd != NULL )
        ShowWindow( hWnd, SW_SHOW );
    return hWnd;
}
/* End CreateChildListBox() ************************************************/




/****************************************************************************
*
*     FUNCTION: AddFormatDlgProc
*
*     PURPOSE:  Dialog Procedure for "Add Format" dialog
*
*     PARAMS:   HWND hWnd     - This dialog's window handle
*               UINT Msg      - Which Message?
*               WPARAM wParam - message parameter
*               LPARAM lParam - message parameter
*
*     RETURNS:  BOOL - TRUE for OK, FALSE for Cancel
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL CALLBACK AddFormatDlgProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    // Support all DIB color formats known at this time
    #define MAX_COLOR_FORMAT    5
    TCHAR	ColorFormats[MAX_COLOR_FORMAT+1][20] = { "Monochrome (1bpp)", "16 Color (4bpp)", "256 Color (8bpp)",
                                    "16 Bit Color", "24 Bit Color", "32 Bit Color" };
    UINT    Bits[MAX_COLOR_FORMAT+1] = { 1, 4, 8, 16, 24, 32 };
    static	bSquareOnly = TRUE;
    static	LPARAM lInitParam;


    switch( Msg )
    {
        // Dialog is being initialized
        case WM_INITDIALOG:
        {
            TCHAR	szBuffer[100];

            // We are passed a pointer to a LPICONIMAGE in lParam, save it
            lInitParam = lParam;
            // Set the range and position of the sliders
            SendDlgItemMessage( hWnd, ID_WIDTHSLIDER, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(MIN_ICON_WIDTH,MAX_ICON_WIDTH) );
            SendDlgItemMessage( hWnd, ID_WIDTHSLIDER, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)MIN_ICON_WIDTH );
            wsprintf( szBuffer, "%d Width", MIN_ICON_WIDTH );
            SetDlgItemText( hWnd, ID_WIDTHTEXT, szBuffer );
            SendDlgItemMessage( hWnd, ID_HEIGHTSLIDER, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(MIN_ICON_HEIGHT,MAX_ICON_HEIGHT) );
            SendDlgItemMessage( hWnd, ID_HEIGHTSLIDER, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)MIN_ICON_HEIGHT );
            wsprintf( szBuffer, "%d Height", MIN_ICON_HEIGHT );
            SetDlgItemText( hWnd, ID_HEIGHTTEXT, szBuffer );
            SendDlgItemMessage( hWnd, ID_COLORSLIDER, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0,MAX_COLOR_FORMAT) );
            SendDlgItemMessage( hWnd, ID_COLORSLIDER, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)2);
            SetDlgItemText( hWnd, ID_COLORTEXT, ColorFormats[2] );
            CheckDlgButton( hWnd, IDC_SQUAREONLY, bSquareOnly );
        }
        break; // End WM_INITDIALOG

        // Scroll message from the sliders
        case WM_HSCROLL:
        {
            int	nPos;
            TCHAR	szBuffer[100];

            // Get the current position
            if( ( LOWORD(wParam) == TB_THUMBPOSITION ) || ( LOWORD(wParam) == TB_THUMBTRACK ) )
                nPos = HIWORD( wParam );
            else
                nPos = SendMessage( (HWND)lParam, TBM_GETPOS, 0, 0 );
            // Was it the width slider?
            if( (HWND)lParam == GetDlgItem( hWnd, ID_WIDTHSLIDER) )
            {
                // Update the text
                wsprintf( szBuffer, "%d Width", nPos );
                SetDlgItemText( hWnd, ID_WIDTHTEXT, szBuffer );
                // If dealing with width=height, adjust height too
                if( bSquareOnly )
                {
                    SendDlgItemMessage( hWnd, ID_HEIGHTSLIDER, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)nPos );
                    wsprintf( szBuffer, "%d Height", nPos );
                    SetDlgItemText( hWnd, ID_HEIGHTTEXT, szBuffer );
                }
            }
            else
            {
                // Was it the height slider?
                if( (HWND)lParam == GetDlgItem( hWnd, ID_HEIGHTSLIDER) )
                {
                    // Update the text
                    wsprintf( szBuffer, "%d Height", nPos );
                    SetDlgItemText( hWnd, ID_HEIGHTTEXT, szBuffer );
                    // If dealing with width=height, adjust width too
                    if( bSquareOnly )
                    {
                        SendDlgItemMessage( hWnd, ID_WIDTHSLIDER, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)nPos );
                        wsprintf( szBuffer, "%d Width", nPos );
                        SetDlgItemText( hWnd, ID_WIDTHTEXT, szBuffer );
                    }
                }
                else
                {
                    // Was it the color slider?
                    if( (HWND)lParam == GetDlgItem( hWnd, ID_COLORSLIDER) )
                    {
                        // Update the text
                        SetDlgItemText( hWnd, ID_COLORTEXT, ColorFormats[nPos] );
                    }
                }
            }
        }
        break; // End WM_HSCROLL

        // Time to say 'goodbye'
        case WM_CLOSE:
            PostMessage( hWnd, WM_COMMAND, IDCANCEL, 0l );
        break; // End WM_CLOSE


        // Messages from user items - checkboxes etc
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                // Checkbox for width=height restriction
                case IDC_SQUAREONLY:
                    // Is it checked now?
                    bSquareOnly = IsDlgButtonChecked( hWnd, IDC_SQUAREONLY );
                    // If it is, set height equal to width
                    if( bSquareOnly )
                    {
                        int nPos;
                        TCHAR	szBuffer[100];

                        nPos = SendDlgItemMessage( hWnd, ID_WIDTHSLIDER, TBM_GETPOS, 0, 0 );
                        SendDlgItemMessage( hWnd, ID_HEIGHTSLIDER, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)nPos );
                        wsprintf( szBuffer, "%d Height", nPos );
                        SetDlgItemText( hWnd, ID_HEIGHTTEXT, szBuffer );
                    }
                break; // End IDC_SQUAREONLY

                // Add Format button has been pressed
                case IDOK:
                {
                    LPICONIMAGE	lpii;

                    // Were we passed a valid LPICONIMAGE pointer?
                    if( ((LPICONIMAGE)lInitParam) != NULL )
                    {
                        // allocate the new ICONIMAGE
                        if( (lpii = malloc( sizeof( ICONIMAGE ) )) == FALSE )
                            EndDialog( hWnd, FALSE );
                        else
                        {
                            // initialize it
                            ZeroMemory( lpii, sizeof( ICONIMAGE ) );
                            lpii->Width = SendDlgItemMessage( hWnd, ID_WIDTHSLIDER, TBM_GETPOS, 0, 0 );
                            lpii->Height = SendDlgItemMessage( hWnd, ID_HEIGHTSLIDER, TBM_GETPOS, 0, 0 );
                            lpii->Colors = Bits[SendDlgItemMessage( hWnd, ID_COLORSLIDER, TBM_GETPOS, 0, 0 )];
                            // update the pointer that we were passed
                            *(LPICONIMAGE *)lInitParam = lpii;
                            // bail
                            EndDialog( hWnd, TRUE );
                        }
                    }
                    else
                    {
                        // bail
                        EndDialog( hWnd, FALSE );
                    }
                }
                break; // End IDOK

                // Time to cancel
                case IDCANCEL:
                    EndDialog( hWnd, FALSE );
                break; // End IDCANCEL

            }
        break;
        default:
            return FALSE;
        break;
    }
    return TRUE;
    #undef MAX_COLOR_FORMAT
}
/* End AddFormatDlgProc() ************************************************/
