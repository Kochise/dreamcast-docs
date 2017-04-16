// WINDOWS.C -- Your Basic, boring Windows Skelton!

#define INMAIN       // Only define this for the file with WinMain in it!

#include "windonut.h"

// Private function prototypes (this file scope only)

LONG    WndProc_WM_COMMAND ( WINDOWS_PARAMS );
WINPROC WndProc            ( WINDOWS_PARAMS );

/**************************************************************
*                                                             *
*                      WinMain                                *
*                                                             *
**************************************************************/

int PASCAL WinMain (HANDLE hInstance,  HANDLE hPrevInstance, 
                    LPSTR lpszCmdLine, int    nCmdShow       )
{
  MSG         msg       ;
  WNDCLASS    wndclass  ;
             
  if (!hPrevInstance) 
    {
    // Register Parent Window Class
    wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_BYTEALIGNCLIENT;
    wndclass.lpfnWndProc   = (WNDPROC)WndProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = 0 ;
    wndclass.hInstance     = hInstance ;
    wndclass.hIcon         = LoadIcon ( hInstance, szAppName);
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = GetStockObject ( GRAY_BRUSH ) ;
    wndclass.lpszMenuName  = (LPSTR)NULL ;
    wndclass.lpszClassName = szAppName ;

    if (!RegisterClass (&wndclass))
         return FALSE;
    }

  ghInst   = hInstance;

  ghWnd    = CreateWindowEx (WS_EX_TOPMOST,
                              szAppName, 
                              szCaption,
                              WS_POPUP,

                              0, 0, 640, 480,  //640480

                              (HWND)NULL, 
                              (HMENU)NULL, 
                              hInstance, 
                              (LPVOID)NULL) ;

  ShowWindow ( ghWnd, nCmdShow );
  UpdateWindow ( ghWnd );

  gbGameLoop = TRUE;

  while( 1 )
    {
    if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
      {
      if( !GetMessage( &msg, NULL, 0, 0 ) )
         {
         return msg.wParam;
         }
      TranslateMessage(&msg); 
      DispatchMessage(&msg);
      }
    else if( gbGameLoop )
      {
      WINDONUT_GameHeartBeat();
      }
    }
}

/********************************************************************
*                                                                   *
*                     Err: Displays this error message              *
*                                                                   *
********************************************************************/

void __cdecl Err( LPSTR szFmt, ... )
{
    char        szBuff[256];

    *szBuff = 0;
    wvsprintf( &szBuff[strlen(szBuff)], szFmt, (LPVOID)(&szFmt+1) );
    MessageBox(ghWnd, szBuff, szCaption, MB_OK);

}

/*********************************************************************
*                                                                    *
*                       WndProc: Main Message Translator             *
*                                                                    *
*********************************************************************/

WINPROC WndProc ( WINDOWS_PARAMS )
{
  switch ( msg )                                                                  
    {
    case WM_SETCURSOR:

      SetCursor(NULL);
      return TRUE;

    case WM_KEYDOWN:

      if (VK_ESCAPE == wParam)
        PostMessage ( hWnd, WM_CLOSE, 0, 0);
      break;

    case WM_CREATE:

      // Post ourselves a message to get things rolling
      PostMessage ( hWnd, WM_USER+1000, 0, 0L );
      break;

    case WM_USER+1000:

      ShowCursor(FALSE);
      if (!WINDONUT_InitGame())
        PostMessage ( hWnd, WM_CLOSE, 0, 0);
      break;

    case WM_DESTROY :

      gbGameLoop = FALSE;
      if (glpDirectDraw)  DIRECTDRAW_Disable (glpDirectDraw);
      if (glpSoundFire      )       DIRECTSOUND_UnLoad ( glpDirectSound, glpSoundFire      );
      if (glpSoundExplosion )       DIRECTSOUND_UnLoad ( glpDirectSound, glpSoundExplosion );
      if (glpSoundThrust    )       DIRECTSOUND_UnLoad ( glpDirectSound, glpSoundThrust    );
      if (glpSoundBackground)       DIRECTSOUND_UnLoad ( glpDirectSound, glpSoundBackground);
      if (glpDirectSound) DIRECTSOUND_Disable( glpDirectSound );

      ShowCursor(TRUE);
      PostQuitMessage (0) ;
      break ;

    default :

      return DefWindowProc ( hWnd, msg, wParam, lParam );

    }
  return 0L ;
}

