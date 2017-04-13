
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

//---------------------------------------------------------------------------
//
//  Module: tty.c
//
//  Purpose:
//     The sample application demonstrates the usage of the COMM
//     API.  It implements the new COMM API of Windows 3.1.
//
//     NOTE:  no escape sequences are translated, only
//            the necessary control codes (LF, CR, BS, etc.)
//
//  Description of functions:
//     Descriptions are contained in the function headers.
//
//---------------------------------------------------------------------------
//
//  Written by Microsoft Product Support Services, Windows Developer Support.
//
//---------------------------------------------------------------------------

#include "tty.h"

//---------------------------------------------------------------------------
//  int PASCAL WinMain( HANDLE hInstance, HANDLE hPrevInstance,
//                      LPSTR lpszCmdLine, int nCmdShow )
//
//  Description:
//     This is the main window loop!
//
//  Parameters:
//     As documented for all WinMain() functions.
//
//---------------------------------------------------------------------------

int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpszCmdLine, int nCmdShow )
{
   MSG   msg ;

   if (!hPrevInstance)
      if (!InitApplication( hInstance ))
         return ( FALSE ) ;

   if (NULL == (hTTYWnd = InitInstance( hInstance, nCmdShow )))
      return ( FALSE ) ;

   while (GetMessage( &msg, NULL, 0, 0 ))
   {
      if (!TranslateAccelerator( hTTYWnd, ghAccel, &msg ))
      {
         TranslateMessage( &msg ) ;
         DispatchMessage( &msg ) ;
      }
   }
   return ( (int) msg.wParam ) ;

} // end of WinMain()

//---------------------------------------------------------------------------
//  BOOL NEAR InitApplication( HANDLE hInstance )
//
//  Description:
//     First time initialization stuff.  This registers information
//     such as window classes.
//
//  Parameters:
//     HANDLE hInstance
//        Handle to this instance of the application.
//
//---------------------------------------------------------------------------

BOOL NEAR InitApplication( HANDLE hInstance )
{
   WNDCLASS  wndclass ;

   // register tty window class

   wndclass.style =         0 ;
   wndclass.lpfnWndProc =   TTYWndProc ;
   wndclass.cbClsExtra =    0 ;
   wndclass.cbWndExtra =    TTYEXTRABYTES ;
   wndclass.hInstance =     hInstance ;
   wndclass.hIcon =         LoadIcon( hInstance, MAKEINTRESOURCE( TTYICON ) );
   wndclass.hCursor =       LoadCursor( NULL, IDC_ARROW ) ;
   wndclass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1) ;
   wndclass.lpszMenuName =  MAKEINTRESOURCE( TTYMENU ) ;
   wndclass.lpszClassName = gszTTYClass ;

   return( RegisterClass( &wndclass ) ) ;

} // end of InitApplication()

//---------------------------------------------------------------------------
//  HWND NEAR InitInstance( HANDLE hInstance, int nCmdShow )
//
//  Description:
//     Initializes instance specific information.
//
//  Parameters:
//     HANDLE hInstance
//        Handle to instance
//
//     int nCmdShow
//        How do we show the window?
//
//---------------------------------------------------------------------------

HWND NEAR InitInstance( HANDLE hInstance, int nCmdShow )
{
   HWND  hTTYWnd ;

   // load accelerators
   ghAccel = LoadAccelerators( hInstance, MAKEINTRESOURCE( TTYACCEL ) ) ;

   // create the TTY window
   hTTYWnd = CreateWindow( gszTTYClass, gszAppName,
                           WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT,
                           CW_USEDEFAULT, CW_USEDEFAULT,
                           NULL, NULL, hInstance, NULL ) ;

   if (NULL == hTTYWnd)
      return ( NULL ) ;

   ShowWindow( hTTYWnd, nCmdShow ) ;
   UpdateWindow( hTTYWnd ) ;

   return ( hTTYWnd ) ;

} // end of InitInstance()

//---------------------------------------------------------------------------
//  LRESULT FAR PASCAL TTYWndProc( HWND hWnd, UINT uMsg,
//                                 WPARAM wParam, LPARAM lParam )
//
//  Description:
//     This is the TTY Window Proc.  This handles ALL messages
//     to the tty window.
//
//  Parameters:
//     As documented for Window procedures.
//
//  Win-32 Porting Issues:
//     - WM_HSCROLL and WM_VSCROLL packing is different under Win-32.
//     - Needed LOWORD() of wParam for WM_CHAR messages.
//
//---------------------------------------------------------------------------

LRESULT FAR PASCAL TTYWndProc( HWND hWnd, UINT uMsg,
                               WPARAM wParam, LPARAM lParam )
{

   DWORD dwBlockSize=512;
   char * szBuffer;

   switch (uMsg)
   {

      case WM_CREATE:
         return ( CreateTTYInfo( hWnd ) ) ;

      case WM_COMMAND:
      {
         switch ( LOWORD( wParam ) )
         {
            case IDM_CONNECT:
               if (!OpenConnection( hWnd ))
                  MessageBox( hWnd, "Connection failed.", gszAppName,
                              MB_ICONEXCLAMATION ) ;
               break ;

            case IDM_DISCONNECT:
               KillTTYFocus( hWnd ) ;
               CloseConnection( hWnd ) ;
               break ;

            case IDM_SETTINGS:
            {
               NPTTYINFO  npTTYInfo ;

               if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
                  return ( FALSE ) ;
               GoModalDialogBoxParam( GETHINST( hWnd ),
                                      MAKEINTRESOURCE( SETTINGSDLGBOX ), hWnd,
                                      (DLGPROC) SettingsDlgProc,
                                      (LPARAM) (LPSTR) npTTYInfo ) ;

               // if fConnected, set new COM parameters

               if (CONNECTED( npTTYInfo ))
               {
                  if (!SetupConnection( hWnd ))
                     MessageBox( hWnd, "Settings failed!", gszAppName,
                                 MB_ICONEXCLAMATION ) ;
               }
            }
            break ;

            case IDM_SENDBLOCK:
               // This function is very useful to test how
               // your comm application handles large blocks
               // of data

               szBuffer = malloc(dwBlockSize);
               memset(szBuffer, 'X', dwBlockSize);
               WriteCommBlock( hWnd, szBuffer, dwBlockSize);
               free(szBuffer);

               break;

            case IDM_ABOUT:
               GoModalDialogBoxParam ( GETHINST( hWnd ),
                                       MAKEINTRESOURCE( ABOUTDLGBOX ),
                                       hWnd,
                                       (DLGPROC) AboutDlgProc, 0L ) ;
               break;

            case IDM_EXIT:
               PostMessage( hWnd, WM_CLOSE, 0, 0L ) ;
               break ;
         }
      }
      break ;

      case WM_PAINT:
         PaintTTY( hWnd ) ;
         break ;

      case WM_SIZE:
         SizeTTY( hWnd, HIWORD( lParam ), LOWORD( lParam ) ) ;
         break ;

      case WM_HSCROLL:
         ScrollTTYHorz( hWnd, LOWORD( wParam ), HIWORD( wParam ) ) ;
         break ;

      case WM_VSCROLL:
         ScrollTTYVert( hWnd, LOWORD( wParam ), HIWORD( wParam ) ) ;
         break ;

      case WM_CHAR:
         ProcessTTYCharacter( hWnd, LOBYTE( LOWORD( wParam ) ) ) ;
         break ;

      case WM_SETFOCUS:
         SetTTYFocus( hWnd ) ;
         break ;

      case WM_KILLFOCUS:
         KillTTYFocus( hWnd ) ;
         break ;

      case WM_DESTROY:
         DestroyTTYInfo( hWnd ) ;
         PostQuitMessage( 0 ) ;
         break ;

      case WM_CLOSE:
         if (IDOK != MessageBox( hWnd, "OK to close window?", "TTY Sample",
                                 MB_ICONQUESTION | MB_OKCANCEL ))
            break ;

         // fall through

      default:
         return( DefWindowProc( hWnd, uMsg, wParam, lParam ) ) ;
   }
   return 0L ;

} // end of TTYWndProc()

//---------------------------------------------------------------------------
//  LRESULT NEAR CreateTTYInfo( HWND hWnd )
//
//  Description:
//     Creates the tty information structure and sets
//     menu option availability.  Returns -1 if unsuccessful.
//
//  Parameters:
//     HWND  hWnd
//        Handle to main window.
//
//  Win-32 Porting Issues:
//     - Needed to initialize TERMWND( npTTYInfo ) for secondary thread.
//     - Needed to create/initialize overlapped structures used in reads &
//       writes to COMM device.
//
//---------------------------------------------------------------------------

LRESULT NEAR CreateTTYInfo( HWND hWnd )
{
   HMENU       hMenu ;
   NPTTYINFO   npTTYInfo ;

   if (NULL == (npTTYInfo =
                   (NPTTYINFO) LocalAlloc( LPTR, sizeof( TTYINFO ) )))
      return ( (LRESULT) -1 ) ;

   // initialize TTY info structure

   COMDEV( npTTYInfo )        = 0 ;
   CONNECTED( npTTYInfo )     = FALSE ;
   CURSORSTATE( npTTYInfo )   = CS_HIDE ;
   LOCALECHO( npTTYInfo )     = FALSE ;
   AUTOWRAP( npTTYInfo )      = TRUE ;
   PORT( npTTYInfo )          = 1 ;
   BAUDRATE( npTTYInfo )      = CBR_9600 ;
   BYTESIZE( npTTYInfo )      = 8 ;
   //FLOWCTRL( npTTYInfo )      = FC_RTSCTS ;
   FLOWCTRL( npTTYInfo )      = FC_XONXOFF ;
   PARITY( npTTYInfo )        = NOPARITY ;
   STOPBITS( npTTYInfo )      = ONESTOPBIT ;
   XONXOFF( npTTYInfo )       = FALSE ;
   XSIZE( npTTYInfo )         = 0 ;
   YSIZE( npTTYInfo )         = 0 ;
   XSCROLL( npTTYInfo )       = 0 ;
   YSCROLL( npTTYInfo )       = 0 ;
   XOFFSET( npTTYInfo )       = 0 ;
   YOFFSET( npTTYInfo )       = 0 ;
   COLUMN( npTTYInfo )        = 0 ;
   ROW( npTTYInfo )           = 0 ;
   HTTYFONT( npTTYInfo )      = NULL ;
   FGCOLOR( npTTYInfo )       = RGB( 0, 0, 0 ) ;
   USECNRECEIVE( npTTYInfo )  = TRUE ;
   DISPLAYERRORS( npTTYInfo ) = TRUE ;
   WRITE_OS( npTTYInfo ).Offset = 0 ;
   WRITE_OS( npTTYInfo ).OffsetHigh = 0 ;
   READ_OS( npTTYInfo ).Offset = 0 ;
   READ_OS( npTTYInfo ).OffsetHigh = 0 ;
   TERMWND( npTTYInfo ) =       hWnd ;

   // create I/O event used for overlapped reads / writes

   READ_OS( npTTYInfo ).hEvent = CreateEvent( NULL,    // no security
                                              TRUE,    // explicit reset req
                                              FALSE,   // initial event reset
                                              NULL ) ; // no name
   if (READ_OS( npTTYInfo ).hEvent == NULL)
   {
      LocalFree( npTTYInfo ) ;
      return ( -1 ) ;
   }
   WRITE_OS( npTTYInfo ).hEvent = CreateEvent( NULL,    // no security
                                               TRUE,    // explicit reset req
                                               FALSE,   // initial event reset
                                               NULL ) ; // no name
   if (NULL == WRITE_OS( npTTYInfo ).hEvent)
   {
      CloseHandle( READ_OS( npTTYInfo ).hEvent ) ;
      LocalFree( npTTYInfo ) ;
      return ( -1 ) ;
   }

   // clear screen space

   _fmemset( SCREEN( npTTYInfo ), ' ', MAXROWS * MAXCOLS ) ;

   // setup default font information

   LFTTYFONT( npTTYInfo ).lfHeight =         9 ;
   LFTTYFONT( npTTYInfo ).lfWidth =          0 ;
   LFTTYFONT( npTTYInfo ).lfEscapement =     0 ;
   LFTTYFONT( npTTYInfo ).lfOrientation =    0 ;
   LFTTYFONT( npTTYInfo ).lfWeight =         0 ;
   LFTTYFONT( npTTYInfo ).lfItalic =         0 ;
   LFTTYFONT( npTTYInfo ).lfUnderline =      0 ;
   LFTTYFONT( npTTYInfo ).lfStrikeOut =      0 ;
   LFTTYFONT( npTTYInfo ).lfCharSet =        OEM_CHARSET ;
   LFTTYFONT( npTTYInfo ).lfOutPrecision =   OUT_DEFAULT_PRECIS ;
   LFTTYFONT( npTTYInfo ).lfClipPrecision =  CLIP_DEFAULT_PRECIS ;
   LFTTYFONT( npTTYInfo ).lfQuality =        DEFAULT_QUALITY ;
   LFTTYFONT( npTTYInfo ).lfPitchAndFamily = FIXED_PITCH | FF_MODERN ;
   lstrcpy( LFTTYFONT( npTTYInfo ).lfFaceName, "FixedSys" ) ;

   // set TTYInfo handle before any further message processing.

   SETNPTTYINFO( hWnd, npTTYInfo ) ;

   // reset the character information, etc.

   ResetTTYScreen( hWnd, npTTYInfo ) ;

   hMenu = GetMenu( hWnd ) ;
   EnableMenuItem( hMenu, IDM_DISCONNECT,
                   MF_GRAYED | MF_DISABLED | MF_BYCOMMAND ) ;
   EnableMenuItem( hMenu, IDM_CONNECT, MF_ENABLED | MF_BYCOMMAND ) ;

   return ( (LRESULT) TRUE ) ;

} // end of CreateTTYInfo()

//---------------------------------------------------------------------------
//  BOOL NEAR DestroyTTYInfo( HWND hWnd )
//
//  Description:
//     Destroys block associated with TTY window handle.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  Win-32 Porting Issues:
//     - Needed to clean up event objects created during initialization.
//
//---------------------------------------------------------------------------

BOOL NEAR DestroyTTYInfo( HWND hWnd )
{
   NPTTYINFO npTTYInfo ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   // force connection closed (if not already closed)

   if (CONNECTED( npTTYInfo ))
      CloseConnection( hWnd ) ;

   // clean up event objects

   CloseHandle( READ_OS( npTTYInfo ).hEvent ) ;
   CloseHandle( WRITE_OS( npTTYInfo ).hEvent ) ;
   CloseHandle( POSTEVENT( npTTYInfo ) ) ;

   DeleteObject( HTTYFONT( npTTYInfo ) ) ;

   LocalFree( npTTYInfo ) ;
   return ( TRUE ) ;

} // end of DestroyTTYInfo()

//---------------------------------------------------------------------------
//  BOOL NEAR ResetTTYScreen( HWND hWnd, NPTTYINFO npTTYInfo )
//
//  Description:
//     Resets the TTY character information and causes the
//     screen to resize to update the scroll information.
//
//  Parameters:
//     NPTTYINFO  npTTYInfo
//        pointer to TTY info structure
//
//---------------------------------------------------------------------------

BOOL NEAR ResetTTYScreen( HWND hWnd, NPTTYINFO npTTYInfo )
{
   HDC         hDC ;
   TEXTMETRIC  tm ;
   RECT        rcWindow ;

   if (NULL == npTTYInfo)
      return ( FALSE ) ;

   if (NULL != HTTYFONT( npTTYInfo ))
      DeleteObject( HTTYFONT( npTTYInfo ) ) ;

   HTTYFONT( npTTYInfo ) = CreateFontIndirect( &LFTTYFONT( npTTYInfo ) ) ;

   hDC = GetDC( hWnd ) ;
   SelectObject( hDC, HTTYFONT( npTTYInfo ) ) ;
   GetTextMetrics( hDC, &tm ) ;
   ReleaseDC( hWnd, hDC ) ;

   XCHAR( npTTYInfo ) = tm.tmAveCharWidth  ;
   YCHAR( npTTYInfo ) = tm.tmHeight + tm.tmExternalLeading ;

   // a slimy hack to force the scroll position, region to
   // be recalculated based on the new character sizes

   GetWindowRect( hWnd, &rcWindow ) ;
   SendMessage( hWnd, WM_SIZE, SIZENORMAL,
                (LPARAM) MAKELONG( rcWindow.right - rcWindow.left,
                                   rcWindow.bottom - rcWindow.top ) ) ;

   return ( TRUE ) ;

} // end of ResetTTYScreen()

//---------------------------------------------------------------------------
//  BOOL NEAR PaintTTY( HWND hWnd )
//
//  Description:
//     Paints the rectangle determined by the paint struct of
//     the DC.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window (as always)
//
//---------------------------------------------------------------------------

BOOL NEAR PaintTTY( HWND hWnd )
{
   int          nRow, nCol, nEndRow, nEndCol, nCount, nHorzPos, nVertPos ;
   HDC          hDC ;
   HFONT        hOldFont ;
   NPTTYINFO    npTTYInfo ;
   PAINTSTRUCT  ps ;
   RECT         rect ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   hDC = BeginPaint( hWnd, &ps ) ;
   hOldFont = SelectObject( hDC, HTTYFONT( npTTYInfo ) ) ;
   SetTextColor( hDC, FGCOLOR( npTTYInfo ) ) ;
   SetBkColor( hDC, GetSysColor( COLOR_WINDOW ) ) ;
   rect = ps.rcPaint ;
   nRow =
      min( MAXROWS - 1,
           max( 0, (rect.top + YOFFSET( npTTYInfo )) / YCHAR( npTTYInfo ) ) ) ;
   nEndRow =
      min( MAXROWS - 1,
           ((rect.bottom + YOFFSET( npTTYInfo ) - 1) / YCHAR( npTTYInfo ) ) ) ;
   nCol =
      min( MAXCOLS - 1,
           max( 0, (rect.left + XOFFSET( npTTYInfo )) / XCHAR( npTTYInfo ) ) ) ;
   nEndCol =
      min( MAXCOLS - 1,
           ((rect.right + XOFFSET( npTTYInfo ) - 1) / XCHAR( npTTYInfo ) ) ) ;
   nCount = nEndCol - nCol + 1 ;
   for (; nRow <= nEndRow; nRow++)
   {
      nVertPos = (nRow * YCHAR( npTTYInfo )) - YOFFSET( npTTYInfo ) ;
      nHorzPos = (nCol * XCHAR( npTTYInfo )) - XOFFSET( npTTYInfo ) ;
      rect.top = nVertPos ;
      rect.bottom = nVertPos + YCHAR( npTTYInfo ) ;
      rect.left = nHorzPos ;
      rect.right = nHorzPos + XCHAR( npTTYInfo ) * nCount ;
      SetBkMode( hDC, OPAQUE ) ;
      ExtTextOut( hDC, nHorzPos, nVertPos, ETO_OPAQUE | ETO_CLIPPED, &rect,
                  (LPSTR)( SCREEN( npTTYInfo ) + nRow * MAXCOLS + nCol ),
                  nCount, NULL ) ;
   }
   SelectObject( hDC, hOldFont ) ;
   EndPaint( hWnd, &ps ) ;
   MoveTTYCursor( hWnd ) ;
   return ( TRUE ) ;

} // end of PaintTTY()

//---------------------------------------------------------------------------
//  BOOL NEAR SizeTTY( HWND hWnd, WORD wVertSize, WORD wHorzSize )
//
//  Description:
//     Sizes TTY and sets up scrolling regions.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     WORD wVertSize
//        new vertical size
//
//     WORD wHorzSize
//        new horizontal size
//
//---------------------------------------------------------------------------

BOOL NEAR SizeTTY( HWND hWnd, WORD wVertSize, WORD wHorzSize )
{
   int        nScrollAmt ;
   NPTTYINFO  npTTYInfo ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   YSIZE( npTTYInfo ) = (int) wVertSize ;
   YSCROLL( npTTYInfo ) = max( 0, (MAXROWS * YCHAR( npTTYInfo )) -
                               YSIZE( npTTYInfo ) ) ;
   nScrollAmt = min( YSCROLL( npTTYInfo ), YOFFSET( npTTYInfo ) ) -
                     YOFFSET( npTTYInfo ) ;
   ScrollWindow( hWnd, 0, -nScrollAmt, NULL, NULL ) ;

   YOFFSET( npTTYInfo ) = YOFFSET( npTTYInfo ) + nScrollAmt ;
   SetScrollPos( hWnd, SB_VERT, YOFFSET( npTTYInfo ), FALSE ) ;
   SetScrollRange( hWnd, SB_VERT, 0, YSCROLL( npTTYInfo ), TRUE ) ;

   XSIZE( npTTYInfo ) = (int) wHorzSize ;
   XSCROLL( npTTYInfo ) = max( 0, (MAXCOLS * XCHAR( npTTYInfo )) -
                                XSIZE( npTTYInfo ) ) ;
   nScrollAmt = min( XSCROLL( npTTYInfo ), XOFFSET( npTTYInfo )) -
                     XOFFSET( npTTYInfo ) ;
   ScrollWindow( hWnd, 0, -nScrollAmt, NULL, NULL ) ;
   XOFFSET( npTTYInfo ) = XOFFSET( npTTYInfo ) + nScrollAmt ;
   SetScrollPos( hWnd, SB_HORZ, XOFFSET( npTTYInfo ), FALSE ) ;
   SetScrollRange( hWnd, SB_HORZ, 0, XSCROLL( npTTYInfo ), TRUE ) ;

   InvalidateRect( hWnd, NULL, TRUE ) ;

   return ( TRUE ) ;

} // end of SizeTTY()

//---------------------------------------------------------------------------
//  BOOL NEAR ScrollTTYVert( HWND hWnd, WORD wScrollCmd, WORD wScrollPos )
//
//  Description:
//     Scrolls TTY window vertically.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     WORD wScrollCmd
//        type of scrolling we're doing
//
//     WORD wScrollPos
//        scroll position
//
//---------------------------------------------------------------------------

BOOL NEAR ScrollTTYVert( HWND hWnd, WORD wScrollCmd, WORD wScrollPos )
{
   int        nScrollAmt ;
   NPTTYINFO  npTTYInfo ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   switch (wScrollCmd)
   {
      case SB_TOP:
         nScrollAmt = -YOFFSET( npTTYInfo ) ;
         break ;

      case SB_BOTTOM:
         nScrollAmt = YSCROLL( npTTYInfo ) - YOFFSET( npTTYInfo ) ;
         break ;

      case SB_PAGEUP:
         nScrollAmt = -YSIZE( npTTYInfo ) ;
         break ;

      case SB_PAGEDOWN:
         nScrollAmt = YSIZE( npTTYInfo ) ;
         break ;

      case SB_LINEUP:
         nScrollAmt = -YCHAR( npTTYInfo ) ;
         break ;

      case SB_LINEDOWN:
         nScrollAmt = YCHAR( npTTYInfo ) ;
         break ;

      case SB_THUMBPOSITION:
         nScrollAmt = wScrollPos - YOFFSET( npTTYInfo ) ;
         break ;

      default:
         return ( FALSE ) ;
   }
   if ((YOFFSET( npTTYInfo ) + nScrollAmt) > YSCROLL( npTTYInfo ))
      nScrollAmt = YSCROLL( npTTYInfo ) - YOFFSET( npTTYInfo ) ;
   if ((YOFFSET( npTTYInfo ) + nScrollAmt) < 0)
      nScrollAmt = -YOFFSET( npTTYInfo ) ;
   ScrollWindow( hWnd, 0, -nScrollAmt, NULL, NULL ) ;
   YOFFSET( npTTYInfo ) = YOFFSET( npTTYInfo ) + nScrollAmt ;
   SetScrollPos( hWnd, SB_VERT, YOFFSET( npTTYInfo ), TRUE ) ;

   return ( TRUE ) ;

} // end of ScrollTTYVert()

//---------------------------------------------------------------------------
//  BOOL NEAR ScrollTTYHorz( HWND hWnd, WORD wScrollCmd, WORD wScrollPos )
//
//  Description:
//     Scrolls TTY window horizontally.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     WORD wScrollCmd
//        type of scrolling we're doing
//
//     WORD wScrollPos
//        scroll position
//
//---------------------------------------------------------------------------

BOOL NEAR ScrollTTYHorz( HWND hWnd, WORD wScrollCmd, WORD wScrollPos )
{
   int        nScrollAmt ;
   NPTTYINFO  npTTYInfo ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   switch (wScrollCmd)
   {
      case SB_TOP:
         nScrollAmt = -XOFFSET( npTTYInfo ) ;
         break ;

      case SB_BOTTOM:
         nScrollAmt = XSCROLL( npTTYInfo ) - XOFFSET( npTTYInfo ) ;
         break ;

      case SB_PAGEUP:
         nScrollAmt = -XSIZE( npTTYInfo ) ;
         break ;

      case SB_PAGEDOWN:
         nScrollAmt = XSIZE( npTTYInfo ) ;
         break ;

      case SB_LINEUP:
         nScrollAmt = -XCHAR( npTTYInfo ) ;
         break ;

      case SB_LINEDOWN:
         nScrollAmt = XCHAR( npTTYInfo ) ;
         break ;

      case SB_THUMBPOSITION:
         nScrollAmt = wScrollPos - XOFFSET( npTTYInfo ) ;
         break ;

      default:
         return ( FALSE ) ;
   }
   if ((XOFFSET( npTTYInfo ) + nScrollAmt) > XSCROLL( npTTYInfo ))
      nScrollAmt = XSCROLL( npTTYInfo ) - XOFFSET( npTTYInfo ) ;
   if ((XOFFSET( npTTYInfo ) + nScrollAmt) < 0)
      nScrollAmt = -XOFFSET( npTTYInfo ) ;
   ScrollWindow( hWnd, -nScrollAmt, 0, NULL, NULL ) ;
   XOFFSET( npTTYInfo ) = XOFFSET( npTTYInfo ) + nScrollAmt ;
   SetScrollPos( hWnd, SB_HORZ, XOFFSET( npTTYInfo ), TRUE ) ;

   return ( TRUE ) ;

} // end of ScrollTTYHorz()

//---------------------------------------------------------------------------
//  BOOL NEAR SetTTYFocus( HWND hWnd )
//
//  Description:
//     Sets the focus to the TTY window also creates caret.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//---------------------------------------------------------------------------

BOOL NEAR SetTTYFocus( HWND hWnd )
{
   NPTTYINFO  npTTYInfo ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   if (CONNECTED( npTTYInfo ) && (CURSORSTATE( npTTYInfo ) != CS_SHOW))
   {
      CreateCaret( hWnd, NULL, XCHAR( npTTYInfo ), YCHAR( npTTYInfo ) ) ;
      ShowCaret( hWnd ) ;
      CURSORSTATE( npTTYInfo ) = CS_SHOW ;
   }
   MoveTTYCursor( hWnd ) ;
   return ( TRUE ) ;

} // end of SetTTYFocus()

//---------------------------------------------------------------------------
//  BOOL NEAR KillTTYFocus( HWND hWnd )
//
//  Description:
//     Kills TTY focus and destroys the caret.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//---------------------------------------------------------------------------

BOOL NEAR KillTTYFocus( HWND hWnd )
{
   NPTTYINFO  npTTYInfo ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   if (CONNECTED( npTTYInfo ) && (CURSORSTATE( npTTYInfo ) != CS_HIDE))
   {
      HideCaret( hWnd ) ;
      DestroyCaret() ;
      CURSORSTATE( npTTYInfo ) = CS_HIDE ;
   }
   return ( TRUE ) ;

} // end of KillTTYFocus()

//---------------------------------------------------------------------------
//  BOOL NEAR MoveTTYCursor( HWND hWnd )
//
//  Description:
//     Moves caret to current position.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//---------------------------------------------------------------------------

BOOL NEAR MoveTTYCursor( HWND hWnd )
{
   NPTTYINFO  npTTYInfo ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   if (CONNECTED( npTTYInfo ) && (CURSORSTATE( npTTYInfo ) & CS_SHOW))
      SetCaretPos( (COLUMN( npTTYInfo ) * XCHAR( npTTYInfo )) -
                   XOFFSET( npTTYInfo ),
                   (ROW( npTTYInfo ) * YCHAR( npTTYInfo )) -
                   YOFFSET( npTTYInfo ) ) ;

   return ( TRUE ) ;

} // end of MoveTTYCursor()

//---------------------------------------------------------------------------
//  BOOL NEAR ProcessTTYCharacter( HWND hWnd, BYTE bOut )
//
//  Description:
//     This simply writes a character to the port and echos it
//     to the TTY screen if fLocalEcho is set.  Some minor
//     keyboard mapping could be performed here.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     BYTE bOut
//        byte from keyboard
//
//---------------------------------------------------------------------------

BOOL NEAR ProcessTTYCharacter( HWND hWnd, BYTE bOut )
{
   NPTTYINFO  npTTYInfo ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   if (!CONNECTED( npTTYInfo ))
      return ( FALSE ) ;

   // a robust app would take appropriate steps if WriteCommBlock failed
   WriteCommBlock( hWnd, &bOut, 1 ) ;
   if (LOCALECHO( npTTYInfo ))
      WriteTTYBlock( hWnd, &bOut, 1 ) ;

   return ( TRUE ) ;

} // end of ProcessTTYCharacter()

//---------------------------------------------------------------------------
//  BOOL NEAR OpenConnection( HWND hWnd )
//
//  Description:
//     Opens communication port specified in the TTYINFO struct.
//     It also sets the CommState and notifies the window via
//     the fConnected flag in the TTYINFO struct.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  Win-32 Porting Issues:
//     - OpenComm() is not supported under Win-32.  Use CreateFile()
//       and setup for OVERLAPPED_IO.
//     - Win-32 has specific communication timeout parameters.
//     - Created the secondary thread for event notification.
//
//---------------------------------------------------------------------------

BOOL NEAR OpenConnection( HWND hWnd )
{
   char       szPort[ 15 ], szTemp[ 10 ] ;
   BOOL       fRetVal ;
   HCURSOR    hOldCursor, hWaitCursor ;
   HMENU      hMenu ;
   NPTTYINFO  npTTYInfo ;

   HANDLE        hCommWatchThread ;
   DWORD         dwThreadID ;
   COMMTIMEOUTS  CommTimeOuts ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   // show the hourglass cursor
   hWaitCursor = LoadCursor( NULL, IDC_WAIT ) ;
   hOldCursor = SetCursor( hWaitCursor ) ;

   // load the COM prefix string and append port number

   LoadString( GETHINST( hWnd ), IDS_COMPREFIX, szTemp, sizeof( szTemp ) ) ;
   wsprintf( szPort, "%s%d", (LPSTR) szTemp, PORT( npTTYInfo ) ) ;

   // open COMM device

   if ((COMDEV( npTTYInfo ) =
      CreateFile( szPort, GENERIC_READ | GENERIC_WRITE,
                  0,                    // exclusive access
                  NULL,                 // no security attrs
                  OPEN_EXISTING,
                  FILE_ATTRIBUTE_NORMAL |
                  FILE_FLAG_OVERLAPPED, // overlapped I/O
                  NULL )) == (HANDLE) -1 )
      return ( FALSE ) ;
   else
   {
      // get any early notifications

      SetCommMask( COMDEV( npTTYInfo ), EV_RXCHAR ) ;

      // setup device buffers

      SetupComm( COMDEV( npTTYInfo ), 4096, 4096 ) ;

      // purge any information in the buffer

      PurgeComm( COMDEV( npTTYInfo ), PURGE_TXABORT | PURGE_RXABORT |
                                      PURGE_TXCLEAR | PURGE_RXCLEAR ) ;

      // set up for overlapped I/O

      CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF ;
      CommTimeOuts.ReadTotalTimeoutMultiplier = 0 ;
      CommTimeOuts.ReadTotalTimeoutConstant = 1000 ;
      // CBR_9600 is approximately 1byte/ms. For our purposes, allow
      // double the expected time per character for a fudge factor.
      CommTimeOuts.WriteTotalTimeoutMultiplier = 2*CBR_9600/BAUDRATE( npTTYInfo ) ;
      CommTimeOuts.WriteTotalTimeoutConstant = 0 ;
      SetCommTimeouts( COMDEV( npTTYInfo ), &CommTimeOuts ) ;
   }

   fRetVal = SetupConnection( hWnd ) ;

   if (fRetVal)
   {
      CONNECTED( npTTYInfo ) = TRUE ;

      // Create a secondary thread
      // to watch for an event.

      if (NULL == (hCommWatchThread =
                      CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
                                    0,
                                    (LPTHREAD_START_ROUTINE) CommWatchProc,
                                    (LPVOID) npTTYInfo,
                                    0, &dwThreadID )))
      {
         CONNECTED( npTTYInfo ) = FALSE ;
         CloseHandle( COMDEV( npTTYInfo ) ) ;
         fRetVal = FALSE ;
      }
      else
      {
         THREADID( npTTYInfo ) = dwThreadID ;
         HTHREAD( npTTYInfo ) = hCommWatchThread ;

         // assert DTR

         EscapeCommFunction( COMDEV( npTTYInfo ), SETDTR ) ;

         SetTTYFocus( hWnd ) ;

         hMenu = GetMenu( hWnd ) ;
         EnableMenuItem( hMenu, IDM_DISCONNECT,
                        MF_ENABLED | MF_BYCOMMAND ) ;
         EnableMenuItem( hMenu, IDM_CONNECT,
                        MF_GRAYED | MF_DISABLED | MF_BYCOMMAND ) ;

      }
   }
   else
   {
      CONNECTED( npTTYInfo ) = FALSE ;
      CloseHandle( COMDEV( npTTYInfo ) ) ;
   }

   // restore cursor

   SetCursor( hOldCursor ) ;

   return ( fRetVal ) ;

} // end of OpenConnection()

//---------------------------------------------------------------------------
//  BOOL NEAR SetupConnection( HWND hWnd )
//
//  Description:
//     This routines sets up the DCB based on settings in the
//     TTY info structure and performs a SetCommState().
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  Win-32 Porting Issues:
//     - Win-32 requires a slightly different processing of the DCB.
//       Changes were made for configuration of the hardware handshaking
//       lines.
//
//---------------------------------------------------------------------------

BOOL NEAR SetupConnection( HWND hWnd )
{
   BOOL       fRetVal ;
   BYTE       bSet ;
   DCB        dcb ;
   NPTTYINFO  npTTYInfo ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   dcb.DCBlength = sizeof( DCB ) ;

   GetCommState( COMDEV( npTTYInfo ), &dcb ) ;

   dcb.BaudRate = BAUDRATE( npTTYInfo ) ;
   dcb.ByteSize = BYTESIZE( npTTYInfo ) ;
   dcb.Parity = PARITY( npTTYInfo ) ;
   dcb.StopBits = STOPBITS( npTTYInfo ) ;

   // setup hardware flow control

   bSet = (BYTE) ((FLOWCTRL( npTTYInfo ) & FC_DTRDSR) != 0) ;
   dcb.fOutxDsrFlow = bSet ;
   if (bSet)
      dcb.fDtrControl = DTR_CONTROL_HANDSHAKE ;
   else
      dcb.fDtrControl = DTR_CONTROL_ENABLE ;

   bSet = (BYTE) ((FLOWCTRL( npTTYInfo ) & FC_RTSCTS) != 0) ;
	dcb.fOutxCtsFlow = bSet ;
   if (bSet)
      dcb.fRtsControl = RTS_CONTROL_HANDSHAKE ;
   else
      dcb.fRtsControl = RTS_CONTROL_ENABLE ;

   // setup software flow control

   bSet = (BYTE) ((FLOWCTRL( npTTYInfo ) & FC_XONXOFF) != 0) ;

   dcb.fInX = dcb.fOutX = bSet ;
   dcb.XonChar = ASCII_XON ;
   dcb.XoffChar = ASCII_XOFF ;
   dcb.XonLim = 100 ;
   dcb.XoffLim = 100 ;

   // other various settings

   dcb.fBinary = TRUE ;
   dcb.fParity = TRUE ;

   fRetVal = SetCommState( COMDEV( npTTYInfo ), &dcb ) ;

   return ( fRetVal ) ;

} // end of SetupConnection()

//---------------------------------------------------------------------------
//  BOOL NEAR CloseConnection( HWND hWnd )
//
//  Description:
//     Closes the connection to the port.  Resets the connect flag
//     in the TTYINFO struct.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  Win-32 Porting Issues:
//     - Needed to stop secondary thread.  SetCommMask() will signal the
//       WaitCommEvent() event and the thread will halt when the
//       CONNECTED() flag is clear.
//     - Use new PurgeComm() API to clear communications driver before
//       closing device.
//
//---------------------------------------------------------------------------

BOOL NEAR CloseConnection( HWND hWnd )
{
   HMENU      hMenu ;
   NPTTYINFO  npTTYInfo ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   // set connected flag to FALSE

   CONNECTED( npTTYInfo ) = FALSE ;

   // disable event notification and wait for thread
   // to halt

   SetCommMask( COMDEV( npTTYInfo ), 0 ) ;

   // block until thread has been halted

   while(THREADID(npTTYInfo) != 0);

   // kill the focus

   KillTTYFocus( hWnd ) ;

   // drop DTR

   EscapeCommFunction( COMDEV( npTTYInfo ), CLRDTR ) ;

   // purge any outstanding reads/writes and close device handle

   PurgeComm( COMDEV( npTTYInfo ), PURGE_TXABORT | PURGE_RXABORT |
                                   PURGE_TXCLEAR | PURGE_RXCLEAR ) ;
   CloseHandle( COMDEV( npTTYInfo ) ) ;

   // change the selectable items in the menu

   hMenu = GetMenu( hWnd ) ;
   EnableMenuItem( hMenu, IDM_DISCONNECT,
                   MF_GRAYED | MF_DISABLED | MF_BYCOMMAND ) ;
   EnableMenuItem( hMenu, IDM_CONNECT,
                   MF_ENABLED | MF_BYCOMMAND ) ;

   return ( TRUE ) ;

} // end of CloseConnection()

//---------------------------------------------------------------------------
//  int NEAR ReadCommBlock( HWND hWnd, LPSTR lpszBlock, int nMaxLength )
//
//  Description:
//     Reads a block from the COM port and stuffs it into
//     the provided buffer.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     LPSTR lpszBlock
//        block used for storage
//
//     int nMaxLength
//        max length of block to read
//
//  Win-32 Porting Issues:
//     - ReadComm() has been replaced by ReadFile() in Win-32.
//     - Overlapped I/O has been implemented.
//
//---------------------------------------------------------------------------

int NEAR ReadCommBlock( HWND hWnd, LPSTR lpszBlock, int nMaxLength )
{
   BOOL       fReadStat ;
   COMSTAT    ComStat ;
   DWORD      dwErrorFlags;
   DWORD      dwLength;
   DWORD      dwError;
   char       szError[ 10 ] ;
   NPTTYINFO  npTTYInfo ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   // only try to read number of bytes in queue
   ClearCommError( COMDEV( npTTYInfo ), &dwErrorFlags, &ComStat ) ;
   dwLength = min( (DWORD) nMaxLength, ComStat.cbInQue ) ;

   if (dwLength > 0)
   {
      fReadStat = ReadFile( COMDEV( npTTYInfo ), lpszBlock,
		                    dwLength, &dwLength, &READ_OS( npTTYInfo ) ) ;
      if (!fReadStat)
      {
         if (GetLastError() == ERROR_IO_PENDING)
         {
            OutputDebugString("\n\rIO Pending");
            // We have to wait for read to complete.
            // This function will timeout according to the
            // CommTimeOuts.ReadTotalTimeoutConstant variable
            // Every time it times out, check for port errors
            while(!GetOverlappedResult( COMDEV( npTTYInfo ),
               &READ_OS( npTTYInfo ), &dwLength, TRUE ))
            {
               dwError = GetLastError();
               if(dwError == ERROR_IO_INCOMPLETE)
                  // normal result if not finished
                  continue;
               else
               {
                  // an error occurred, try to recover
                  wsprintf( szError, "<CE-%u>", dwError ) ;
                  WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
                  ClearCommError( COMDEV( npTTYInfo ), &dwErrorFlags, &ComStat ) ;
                  if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo ))
                  {
	                  wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
	                  WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
                  }
                  break;
               }

            }

	      }
         else
         {
            // some other error occurred
            dwLength = 0 ;
            ClearCommError( COMDEV( npTTYInfo ), &dwErrorFlags, &ComStat ) ;
            if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo ))
            {
	            wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
	            WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
            }
         }
      }
   }

   return ( dwLength ) ;

} // end of ReadCommBlock()

//---------------------------------------------------------------------------
//  BOOL NEAR WriteCommBlock( HWND hWnd, BYTE *pByte )
//
//  Description:
//     Writes a block of data to the COM port specified in the associated
//     TTY info structure.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     BYTE *pByte
//        pointer to data to write to port
//
//  Win-32 Porting Issues:
//     - WriteComm() has been replaced by WriteFile() in Win-32.
//     - Overlapped I/O has been implemented.
//
//---------------------------------------------------------------------------

BOOL NEAR WriteCommBlock( HWND hWnd, LPSTR lpByte , DWORD dwBytesToWrite)
{

   BOOL        fWriteStat ;
   DWORD       dwBytesWritten ;
   NPTTYINFO   npTTYInfo ;
   DWORD       dwErrorFlags;
   DWORD   	dwError;
   DWORD       dwBytesSent=0;
   COMSTAT     ComStat;
   char        szError[ 128 ] ;


   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   fWriteStat = WriteFile( COMDEV( npTTYInfo ), lpByte, dwBytesToWrite,
                           &dwBytesWritten, &WRITE_OS( npTTYInfo ) ) ;

   // Note that normally the code will not execute the following
   // because the driver caches write operations. Small I/O requests
   // (up to several thousand bytes) will normally be accepted
   // immediately and WriteFile will return true even though an
   // overlapped operation was specified

   if (!fWriteStat)
   {
      if(GetLastError() == ERROR_IO_PENDING)
      {
         // We should wait for the completion of the write operation
         // so we know if it worked or not

         // This is only one way to do this. It might be beneficial to
         // place the write operation in a separate thread
         // so that blocking on completion will not negatively
         // affect the responsiveness of the UI

         // If the write takes too long to complete, this
         // function will timeout according to the
         // CommTimeOuts.WriteTotalTimeoutMultiplier variable.
         // This code logs the timeout but does not retry
         // the write.

         while(!GetOverlappedResult( COMDEV( npTTYInfo ),
            &WRITE_OS( npTTYInfo ), &dwBytesWritten, TRUE ))
         {
            dwError = GetLastError();
            if(dwError == ERROR_IO_INCOMPLETE)
            {
               // normal result if not finished
               dwBytesSent += dwBytesWritten;
               continue;
            }
            else
            {
               // an error occurred, try to recover
               wsprintf( szError, "<CE-%u>", dwError ) ;
               WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
               ClearCommError( COMDEV( npTTYInfo ), &dwErrorFlags, &ComStat ) ;
               if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo ))
               {
                  wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
                  WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
               }
               break;
            }
         }

         dwBytesSent += dwBytesWritten;

         if( dwBytesSent != dwBytesToWrite )
             wsprintf(szError,"\nProbable Write Timeout: Total of %ld bytes sent", dwBytesSent);
         else
             wsprintf(szError,"\n%ld bytes written", dwBytesSent);

         OutputDebugString(szError);

      }
      else
      {
         // some other error occurred
         ClearCommError( COMDEV( npTTYInfo ), &dwErrorFlags, &ComStat ) ;
         if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo ))
         {
            wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
            WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
         }
         return ( FALSE );
      }
   }
   return ( TRUE ) ;

} // end of WriteCommBlock()

//---------------------------------------------------------------------------
//  BOOL NEAR WriteTTYBlock( HWND hWnd, LPSTR lpBlock, int nLength )
//
//  Description:
//     Writes block to TTY screen.  Nothing fancy - just
//     straight TTY.
// gl
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     LPSTR lpBlock
//        far pointer to block of data
//
//     int nLength
//        length of block
//
//---------------------------------------------------------------------------

BOOL NEAR WriteTTYBlock( HWND hWnd, LPSTR lpBlock, int nLength )
{
   int        i ;
   NPTTYINFO  npTTYInfo ;
   RECT       rect ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   for (i = 0 ; i < nLength; i++)
   {
      switch (lpBlock[ i ])
      {
         case ASCII_BEL:
            // Bell
            MessageBeep( 0 ) ;
            break ;

         case ASCII_BS:
            // Backspace
            if (COLUMN( npTTYInfo ) > 0)
               COLUMN( npTTYInfo ) -- ;
            MoveTTYCursor( hWnd ) ;
            break ;

         case ASCII_CR:
            // Carriage return
            COLUMN( npTTYInfo ) = 0 ;
            MoveTTYCursor( hWnd ) ;
            if (!NEWLINE( npTTYInfo ))
               break;

            // fall through

         case ASCII_LF:
            // Line feed
            if (ROW( npTTYInfo )++ == MAXROWS - 1)
            {
               _fmemmove( (LPSTR) (SCREEN( npTTYInfo )),
                          (LPSTR) (SCREEN( npTTYInfo ) + MAXCOLS),
                          (MAXROWS - 1) * MAXCOLS ) ;
               _fmemset( (LPSTR) (SCREEN( npTTYInfo ) + (MAXROWS - 1) * MAXCOLS),
                         ' ', MAXCOLS ) ;
               InvalidateRect( hWnd, NULL, FALSE ) ;
               ROW( npTTYInfo )-- ;
            }
            MoveTTYCursor( hWnd ) ;
            break ;

         default:
            *(SCREEN( npTTYInfo ) + ROW( npTTYInfo ) * MAXCOLS +
                COLUMN( npTTYInfo )) = lpBlock[ i ] ;
            rect.left = (COLUMN( npTTYInfo ) * XCHAR( npTTYInfo )) -
                        XOFFSET( npTTYInfo ) ;
            rect.right = rect.left + XCHAR( npTTYInfo ) ;
            rect.top = (ROW( npTTYInfo ) * YCHAR( npTTYInfo )) -
                       YOFFSET( npTTYInfo ) ;
            rect.bottom = rect.top + YCHAR( npTTYInfo ) ;
            InvalidateRect( hWnd, &rect, FALSE ) ;

            // Line wrap
            if (COLUMN( npTTYInfo ) < MAXCOLS - 1)
               COLUMN( npTTYInfo )++ ;
            else if (AUTOWRAP( npTTYInfo ))
               WriteTTYBlock( hWnd, "\r\n", 2 ) ;
            break;
      }
   }
   return ( TRUE ) ;

} // end of WriteTTYBlock()

//---------------------------------------------------------------------------
//  VOID NEAR GoModalDialogBoxParam( HINSTANCE hInstance,
//                                   LPCSTR lpszTemplate, HWND hWnd,
//                                   DLGPROC lpDlgProc, LPARAM lParam )
//
//  Description:
//     It is a simple utility function that simply performs the
//     MPI and invokes the dialog box with a DWORD paramter.
//
//  Parameters:
//     similar to that of DialogBoxParam() with the exception
//     that the lpDlgProc is not a procedure instance
//
//---------------------------------------------------------------------------

VOID NEAR GoModalDialogBoxParam( HINSTANCE hInstance, LPCSTR lpszTemplate,
                                 HWND hWnd, DLGPROC lpDlgProc, LPARAM lParam )
{
   DLGPROC  lpProcInstance ;

   lpProcInstance = (DLGPROC) MakeProcInstance( (FARPROC) lpDlgProc,
                                                hInstance ) ;
   DialogBoxParam( hInstance, lpszTemplate, hWnd, lpProcInstance, lParam ) ;
   FreeProcInstance( (FARPROC) lpProcInstance ) ;

} // end of GoModalDialogBoxParam()

//---------------------------------------------------------------------------
//  BOOL FAR PASCAL AboutDlgProc( HWND hDlg, UINT uMsg,
//                                WPARAM wParam, LPARAM lParam )
//
//  Description:
//     Simulates the Windows System Dialog Box.
//
//  Parameters:
//     Same as standard dialog procedures.
//
//---------------------------------------------------------------------------

BOOL FAR PASCAL AboutDlgProc( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
   switch (uMsg)
   {
      case WM_INITDIALOG:
      {
         char         szBuffer[ MAXLEN_TEMPSTR ], szTemp[ MAXLEN_TEMPSTR ];
         WORD         wRevision, wVersion ;

#ifdef ABOUTDLG_USEBITMAP
         // if we are using the bitmap, hide the icon

         ShowWindow( GetDlgItem( hDlg, IDD_ABOUTICON ), SW_HIDE ) ;
#endif
         // sets up the version number for Windows

         wVersion = LOWORD( GetVersion() ) ;
         wRevision = HIBYTE( wVersion ) ;
         wVersion = LOBYTE( wVersion ) ;

         GetDlgItemText( hDlg, IDD_TITLELINE, szTemp, sizeof( szTemp ) ) ;
         wsprintf( szBuffer, szTemp, wVersion, wRevision ) ;
         SetDlgItemText( hDlg, IDD_TITLELINE, szBuffer ) ;

         // sets up version number for TTY

         GetDlgItemText( hDlg, IDD_VERSION, szTemp, sizeof( szTemp ) ) ;
         wsprintf( szBuffer, szTemp, VER_MAJOR, VER_MINOR, VER_BUILD ) ;
         SetDlgItemText( hDlg, IDD_VERSION, (LPSTR) szBuffer ) ;

         // get by-line

         LoadString( GETHINST( hDlg ), IDS_BYLINE, szBuffer,
                     sizeof( szBuffer ) ) ;
         SetDlgItemText( hDlg, IDD_BYLINE, szBuffer ) ;

         SetDlgItemText( hDlg, IDD_WINDOWSMODE, "NT Mode" ) ;

      }
      return ( TRUE ) ;

#ifdef ABOUTDLG_USEBITMAP
      // used to paint the bitmap

      case WM_PAINT:
      {
         HBITMAP      hBitMap ;
         HDC          hDC, hMemDC ;
         PAINTSTRUCT  ps ;

         // load bitmap and display it

         hDC = BeginPaint( hDlg, &ps ) ;
         if (NULL != (hMemDC = CreateCompatibleDC( hDC )))
         {
            hBitMap = LoadBitmap( GETHINST( hDlg ),
                                  MAKEINTRESOURCE( TTYBITMAP ) ) ;
            hBitMap = SelectObject( hMemDC, hBitMap ) ;
            BitBlt( hDC, 10, 10, 64, 64, hMemDC, 0, 0, SRCCOPY ) ;
            DeleteObject( SelectObject( hMemDC, hBitMap ) ) ;
            DeleteDC( hMemDC ) ;
         }
         EndPaint( hDlg, &ps ) ;
      }
      break ;
#endif

      case WM_COMMAND:
         if (LOWORD( wParam ) == IDD_OK)
         {
            EndDialog( hDlg, TRUE ) ;
            return ( TRUE ) ;
         }
         break;
   }
   return ( FALSE ) ;

} // end of AboutDlgProc()

//---------------------------------------------------------------------------
//  VOID NEAR FillComboBox( HINSTANCE hInstance, HWND hCtrlWnd, int nIDString,
//                          WORD NEAR *npTable, WORD wTableLen,
//                          WORD wCurrentSetting )
//
//  Description:
//     Fills the given combo box with strings from the resource
//     table starting at nIDString.  Associated items are
//     added from given table.  The combo box is notified of
//     the current setting.
//
//  Parameters:
//     HINSTANCE hInstance
//        handle to application instance
//
//     HWND hCtrlWnd
//        handle to combo box control
//
//     int nIDString
//        first resource string id
//
//     DWORD NEAR *npTable
//        near point to table of associated values
//
//     WORD wTableLen
//        length of table
//
//     DWORD dwCurrentSetting
//        current setting (for combo box selection)
//
//---------------------------------------------------------------------------

VOID NEAR FillComboBox( HINSTANCE hInstance, HWND hCtrlWnd, int nIDString,
                        DWORD NEAR *npTable, WORD wTableLen,
                        DWORD dwCurrentSetting )
{
   char  szBuffer[ MAXLEN_TEMPSTR ] ;
   WORD  wCount, wPosition ;

   for (wCount = 0; wCount < wTableLen; wCount++)
   {
      // load the string from the string resources and
      // add it to the combo box

      LoadString( hInstance, nIDString + wCount, szBuffer, sizeof( szBuffer ) ) ;
      wPosition = LOWORD( SendMessage( hCtrlWnd, CB_ADDSTRING, 0,
                                       (LPARAM) (LPSTR) szBuffer ) ) ;

      // use item data to store the actual table value

      SendMessage( hCtrlWnd, CB_SETITEMDATA, (WPARAM) wPosition,
                   (LPARAM) *(npTable + wCount) ) ;

      // if this is our current setting, select it

      if (*(npTable + wCount) == dwCurrentSetting)
         SendMessage( hCtrlWnd, CB_SETCURSEL, (WPARAM) wPosition, 0L ) ;
   }

} // end of FillComboBox()

//---------------------------------------------------------------------------
//  BOOL NEAR SettingsDlgInit( HWND hDlg )
//
//  Description:
//     Puts current settings into dialog box (via CheckRadioButton() etc.)
//
//  Parameters:
//     HWND hDlg
//        handle to dialog box
//
//  Win-32 Porting Issues:
//     - Constants require DWORD arrays for baud rate table, etc.
//     - There is no "MAXCOM" function in Win-32.  Number of COM ports
//       is assumed to be 4.
//
//---------------------------------------------------------------------------

BOOL NEAR SettingsDlgInit( HWND hDlg )
{
   char       szBuffer[ MAXLEN_TEMPSTR ], szTemp[ MAXLEN_TEMPSTR ] ;
   NPTTYINFO  npTTYInfo ;
   WORD       wCount, wMaxCOM, wPosition ;

   if (NULL == (npTTYInfo = (NPTTYINFO) GET_PROP( hDlg, ATOM_TTYINFO )))
      return ( FALSE ) ;

   wMaxCOM = MAXPORTS ;

   // load the COM prefix from resources

   LoadString( GETHINST( hDlg ), IDS_COMPREFIX, szTemp, sizeof( szTemp ) ) ;

   // fill port combo box and make initial selection

   for (wCount = 0; wCount < wMaxCOM; wCount++)
   {
      wsprintf( szBuffer, "%s%d", (LPSTR) szTemp, wCount + 1 ) ;
      SendDlgItemMessage( hDlg, IDD_PORTCB, CB_ADDSTRING, 0,
                          (LPARAM) (LPSTR) szBuffer ) ;
   }

   SendDlgItemMessage( hDlg, IDD_PORTCB, CB_SETCURSEL,
                       (WPARAM) (PORT( npTTYInfo ) - 1), 0L ) ;

   // disable COM port combo box if connection has already been
   // established (e.g. OpenComm() already successful)

   EnableWindow( GetDlgItem( hDlg, IDD_PORTCB ), !CONNECTED( npTTYInfo ) ) ;

   // fill baud combo box and make initial selection

   FillComboBox( GETHINST( hDlg ), GetDlgItem( hDlg, IDD_BAUDCB ),
                 IDS_BAUD110, BaudTable,
                 sizeof( BaudTable ) / sizeof( BaudTable[ 0 ] ),
                 BAUDRATE( npTTYInfo ) ) ;

   // fill data bits combo box and make initial selection

   for (wCount = 5; wCount < 9; wCount++)
   {
      wsprintf( szBuffer, "%d", wCount ) ;
      wPosition = LOWORD( SendDlgItemMessage( hDlg, IDD_DATABITSCB,
                                              CB_ADDSTRING, 0,
                                              (LPARAM) (LPSTR) szBuffer ) ) ;

      // if current selection, tell the combo box

      if (wCount == BYTESIZE( npTTYInfo ))
         SendDlgItemMessage( hDlg, IDD_DATABITSCB, CB_SETCURSEL,
                             (WPARAM) wPosition, 0L ) ;
   }

   // fill parity combo box and make initial selection

   FillComboBox( GETHINST( hDlg ), GetDlgItem( hDlg, IDD_PARITYCB ),
                 IDS_PARITYNONE, ParityTable,
                 sizeof( ParityTable ) / sizeof( ParityTable[ 0 ] ),
                 PARITY( npTTYInfo ) ) ;

   // fill stop bits combo box and make initial selection

   FillComboBox( GETHINST( hDlg ), GetDlgItem( hDlg, IDD_STOPBITSCB ),
                 IDS_ONESTOPBIT, StopBitsTable,
                 sizeof( StopBitsTable ) / sizeof ( StopBitsTable ),
                 STOPBITS( npTTYInfo ) ) ;

   // initalize the flow control settings

   CheckDlgButton( hDlg, IDD_DTRDSR,
                   (FLOWCTRL( npTTYInfo ) & FC_DTRDSR) > 0 ) ;
   CheckDlgButton( hDlg, IDD_RTSCTS,
                   (FLOWCTRL( npTTYInfo ) & FC_RTSCTS) > 0 ) ;
   CheckDlgButton( hDlg, IDD_XONXOFF,
                   (FLOWCTRL( npTTYInfo ) & FC_XONXOFF) > 0 ) ;

   // other TTY settings

   CheckDlgButton( hDlg, IDD_AUTOWRAP, AUTOWRAP( npTTYInfo ) ) ;
   CheckDlgButton( hDlg, IDD_NEWLINE, NEWLINE( npTTYInfo ) ) ;
   CheckDlgButton( hDlg, IDD_LOCALECHO, LOCALECHO( npTTYInfo ) ) ;

   // control options

   // "Use CN_RECEIVE" is not valid under Win-32

   EnableWindow( GetDlgItem( hDlg, IDD_USECNRECEIVE ), FALSE ) ;

   CheckDlgButton( hDlg, IDD_DISPLAYERRORS, DISPLAYERRORS( npTTYInfo ) ) ;

   return ( TRUE ) ;

} // end of SettingsDlgInit()

//---------------------------------------------------------------------------
//  BOOL NEAR SelectTTYFont( HWND hDlg )
//
//  Description:
//     Selects the current font for the TTY screen.
//     Uses the Common Dialog ChooseFont() API.
//
//  Parameters:
//     HWND hDlg
//        handle to settings dialog
//
//---------------------------------------------------------------------------

BOOL NEAR SelectTTYFont( HWND hDlg )
{
   CHOOSEFONT  cfTTYFont ;
   NPTTYINFO   npTTYInfo ;

   if (NULL == (npTTYInfo = (NPTTYINFO) GET_PROP( hDlg, ATOM_TTYINFO )))
      return ( FALSE ) ;

   cfTTYFont.lStructSize    = sizeof( CHOOSEFONT ) ;
   cfTTYFont.hwndOwner      = hDlg ;
   cfTTYFont.hDC            = NULL ;
   cfTTYFont.rgbColors      = FGCOLOR( npTTYInfo ) ;
   cfTTYFont.lpLogFont      = &LFTTYFONT( npTTYInfo ) ;
   cfTTYFont.Flags          = CF_SCREENFONTS | CF_FIXEDPITCHONLY |
                              CF_EFFECTS | CF_INITTOLOGFONTSTRUCT ;
   cfTTYFont.lCustData      = 0 ;
   cfTTYFont.lpfnHook       = NULL ;
   cfTTYFont.lpTemplateName = NULL ;
   cfTTYFont.hInstance      = GETHINST( hDlg ) ;

   if (ChooseFont( &cfTTYFont ))
   {
     FGCOLOR( npTTYInfo ) = cfTTYFont.rgbColors ;
     ResetTTYScreen( GetParent( hDlg ), npTTYInfo ) ;
   }

   return ( TRUE ) ;

} // end of SelectTTYFont()

//---------------------------------------------------------------------------
//  BOOL NEAR SettingsDlgTerm( HWND hDlg )
//
//  Description:
//     Puts dialog contents into TTY info structure.
//
//  Parameters:
//     HWND hDlg
//        handle to settings dialog
//
//  Win-32 Porting Issues:
//     - Baud rate requires DWORD values.
//
//---------------------------------------------------------------------------

BOOL NEAR SettingsDlgTerm( HWND hDlg )
{
   NPTTYINFO  npTTYInfo ;
   WORD       wSelection ;

   if (NULL == (npTTYInfo = (NPTTYINFO) GET_PROP( hDlg, ATOM_TTYINFO )))
      return ( FALSE ) ;

   // get port selection

   PORT( npTTYInfo ) =
      LOBYTE( LOWORD( SendDlgItemMessage( hDlg, IDD_PORTCB,
                                          CB_GETCURSEL,
                                          0, 0L ) ) + 1 ) ;
   // get baud rate selection

   wSelection =
      LOWORD( SendDlgItemMessage( hDlg, IDD_BAUDCB, CB_GETCURSEL,
                                  0, 0L ) ) ;
   BAUDRATE( npTTYInfo ) =
      SendDlgItemMessage( hDlg, IDD_BAUDCB, CB_GETITEMDATA,
                          (WPARAM) wSelection, 0L ) ;

   // get data bits selection

   BYTESIZE( npTTYInfo ) =
      LOBYTE( LOWORD( SendDlgItemMessage( hDlg, IDD_DATABITSCB,
                                          CB_GETCURSEL,
                                          0, 0L ) ) + 5 ) ;

   // get parity selection

   wSelection =
      LOWORD( SendDlgItemMessage( hDlg, IDD_PARITYCB, CB_GETCURSEL,
                                  0, 0L ) ) ;
   PARITY( npTTYInfo ) =
      LOBYTE( LOWORD( SendDlgItemMessage( hDlg, IDD_PARITYCB,
                                          CB_GETITEMDATA,
                                          (WPARAM) wSelection,
                                          0L ) ) ) ;

   // get stop bits selection

   wSelection =
      LOWORD( SendDlgItemMessage( hDlg, IDD_STOPBITSCB, CB_GETCURSEL,
                                  0, 0L ) ) ;
   STOPBITS( npTTYInfo ) =
      LOBYTE( LOWORD( SendDlgItemMessage( hDlg, IDD_STOPBITSCB,
                                          CB_GETITEMDATA,
                                          (WPARAM) wSelection, 0L ) ) ) ;

   // get flow control settings

   FLOWCTRL( npTTYInfo ) = 0 ;
   if (IsDlgButtonChecked( hDlg, IDD_DTRDSR ))
      FLOWCTRL( npTTYInfo ) |= FC_DTRDSR ;
   if (IsDlgButtonChecked( hDlg, IDD_RTSCTS ))
      FLOWCTRL( npTTYInfo ) |= FC_RTSCTS ;
   if (IsDlgButtonChecked( hDlg, IDD_XONXOFF ))
      FLOWCTRL( npTTYInfo ) |= FC_XONXOFF ;

   // get other various settings

   AUTOWRAP( npTTYInfo ) = IsDlgButtonChecked( hDlg, IDD_AUTOWRAP ) ;
   NEWLINE( npTTYInfo ) = IsDlgButtonChecked( hDlg, IDD_NEWLINE ) ;
   LOCALECHO( npTTYInfo ) = IsDlgButtonChecked( hDlg, IDD_LOCALECHO ) ;

   // control options

   USECNRECEIVE( npTTYInfo ) = IsDlgButtonChecked( hDlg, IDD_USECNRECEIVE ) ;
   DISPLAYERRORS( npTTYInfo ) = IsDlgButtonChecked( hDlg, IDD_DISPLAYERRORS ) ;

   return ( TRUE ) ;

} // end of SettingsDlgTerm()

//---------------------------------------------------------------------------
//  BOOL FAR PASCAL SettingsDlgProc( HWND hDlg, UINT uMsg,
//                                   WPARAM wParam, LPARAM lParam )
//
//  Description:
//     This handles all of the user preference settings for
//     the TTY.
//
//  Parameters:
//     same as all dialog procedures
//
//  Win-32 Porting Issues:
//     - npTTYInfo is a DWORD in Win-32.
//
//---------------------------------------------------------------------------

BOOL FAR PASCAL SettingsDlgProc( HWND hDlg, UINT uMsg,
                                 WPARAM wParam, LPARAM lParam )
{
   switch (uMsg)
   {
      case WM_INITDIALOG:
      {
         NPTTYINFO  npTTYInfo ;

         // get & save pointer to TTY info structure

         npTTYInfo = (NPTTYINFO) lParam ;

         SET_PROP( hDlg, ATOM_TTYINFO, (HANDLE) npTTYInfo ) ;

         return ( SettingsDlgInit( hDlg ) ) ;
      }

      case WM_COMMAND:
         switch ( LOWORD( wParam ))
         {
            case IDD_FONT:
               return ( SelectTTYFont( hDlg ) ) ;

            case IDD_OK:
               // Copy stuff into structure
               SettingsDlgTerm( hDlg ) ;
               EndDialog( hDlg, TRUE ) ;
               return ( TRUE ) ;

            case IDD_CANCEL:
               // Just end
               EndDialog( hDlg, TRUE ) ;
               return ( TRUE ) ;
         }
         break;

      case WM_DESTROY:
         REMOVE_PROP( hDlg, ATOM_TTYINFO ) ;
         break ;
   }
   return ( FALSE ) ;

} // end of SettingsDlgProc()

//************************************************************************
//  DWORD FAR PASCAL CommWatchProc( LPSTR lpData )
//
//  Description:
//     A secondary thread that will watch for COMM events.
//
//  Parameters:
//     LPSTR lpData
//        32-bit pointer argument
//
//  Win-32 Porting Issues:
//     - Added this thread to watch the communications device and
//       post notifications to the associated window.
//
//************************************************************************

DWORD FAR PASCAL CommWatchProc( LPSTR lpData )
{
   DWORD       dwEvtMask ;
   NPTTYINFO   npTTYInfo = (NPTTYINFO) lpData ;
   OVERLAPPED  os ;
	int        nLength ;
   BYTE       abIn[ MAXBLOCK + 1] ;

   memset( &os, 0, sizeof( OVERLAPPED ) ) ;

   // create I/O event used for overlapped read

   os.hEvent = CreateEvent( NULL,    // no security
                            TRUE,    // explicit reset req
                            FALSE,   // initial event reset
                            NULL ) ; // no name
   if (os.hEvent == NULL)
   {
      MessageBox( NULL, "Failed to create event for thread!", "TTY Error!",
                  MB_ICONEXCLAMATION | MB_OK ) ;
      return ( FALSE ) ;
   }

   if (!SetCommMask( COMDEV( npTTYInfo ), EV_RXCHAR ))
      return ( FALSE ) ;

   while ( CONNECTED( npTTYInfo ) )
   {
      dwEvtMask = 0 ;

      WaitCommEvent( COMDEV( npTTYInfo ), &dwEvtMask, NULL );

      if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR)
      {
         do
         {
            if (nLength = ReadCommBlock( hTTYWnd, (LPSTR) abIn, MAXBLOCK ))
            {
               WriteTTYBlock( hTTYWnd, (LPSTR) abIn, nLength ) ;

               // force a paint

               UpdateWindow( hTTYWnd ) ;
            }
         }
         while ( nLength > 0 ) ;
      }
   }

   // get rid of event handle

   CloseHandle( os.hEvent ) ;

   // clear information in structure (kind of a "we're done flag")

   THREADID( npTTYInfo ) = 0 ;
   HTHREAD( npTTYInfo ) = NULL ;

   return( TRUE ) ;

} // end of CommWatchProc()


//---------------------------------------------------------------------------
//  End of File: tty.c
//---------------------------------------------------------------------------
