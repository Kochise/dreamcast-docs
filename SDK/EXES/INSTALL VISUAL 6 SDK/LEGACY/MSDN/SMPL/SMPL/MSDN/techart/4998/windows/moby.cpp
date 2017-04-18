/* Moby Windows v. 1.0
   by Peter Donnelly

   Copyright (c) 1996 Microsoft Corporation

   This simple game illustrates some basic game-programming concepts
   for comparison with the DOS version.

   Moby moves at random but tends to stay on the same course for a
   while at least. He spouts at intervals, and his spout persists
   on the screen until he spouts again, giving a clue to his
   whereabouts.

   The player moves Captain Ahab's ship with the arrow keys or the numeric
   keypad. As the ship moves, it paints the screen with its wake. Whenever
   Moby crosses the wake, he becomes visible. Moby can only be caught on
   a square that has already been painted.

   The player wins by intercepting Moby. In this version there is no
   time-limit.

   The code was developed with Microsoft Visual C++ v. 4.0.
*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>       // for multimedia timer
//#include <assert.h>
#include "resource.h"

#define TITLE "Moby Windows"
#define NAME "Moby"

#define MOBY_INTERVAL 250       // Moby's speed (milliseconds per move)
#define AHAB_INTERVAL 200       // ditto for Ahab
#define CLOUD_INTERVAL 20       // milliseconds per pixel of cloud move
#define MOBY_COURSE 8           // average no. of moves on same course
#define TIME_TO_BLOW 6          // number of moves between spouts

// directions for key table
#define DIR_N  0                
#define DIR_NE 1
#define DIR_E  2
#define DIR_SE 3
#define DIR_S  4
#define DIR_SW 5
#define DIR_W  6
#define DIR_NW 7

// indices into arrow key state table
#define INDEX_UPLEFT    0
#define INDEX_UP        1
#define INDEX_UPRIGHT   2
#define INDEX_RIGHT     3
#define INDEX_DOWNRIGHT 4
#define INDEX_DOWN      5
#define INDEX_DOWNLEFT  6
#define INDEX_LEFT      7

#define GRIDHT         15        // height of grid in cells
#define GRIDWD         15        // width of grid in cells
#define SPRITE_HT      20        // height of sprites in pixels
#define SPRITE_WD      32        // width of sprites in pixels

// User-defined messages
#define WM_MOVE_MOBY   WM_USER + 1
#define WM_MOVE_AHAB   WM_USER + 2

/*
  Global variables
*/
int painted[GRIDHT][GRIDWD];     // array for ship's wake
BOOL paused;
long mytime;
int MobyX, MobyY;                // Moby's coordinates in grid
int OldMobyX, OldMobyY;
int AhabX, AhabY;                // Ahab's coordinates in grid
int AhabMoved;
int OldAhabX, OldAhabY;
int CloudX, CloudY;              // cloud coordinates on screen  
int CloudRow;                    // cloud's row in grid
int MobyDir;                     // Moby's current direction of travel
int TimeToBlow;                  // counter for spouting
int BlowX, BlowY;                // location of last spout

HBITMAP bm_wake;                 // handles to sprites
HBITMAP bm_moby;
HBITMAP bm_spout;
HBITMAP bm_ahab;
HBITMAP bm_cloud;

HWND hMainWindow;
HDC  hMainDC;
HINSTANCE hTheInstance;

RECT DirtyRect;

HANDLE  hCloudThread;
HANDLE  hMainThread;
DWORD   CloudThreadID;



/*
   Function prototypes
*/
void ChangeDir(int);
void Move_Moby();
int Move_Ahab();
DWORD MoveCloud(LPVOID);
void PutSprite(int, int, HBITMAP);
void EraseSprite(int, int);
void UpdateScreen();
BOOL CALLBACK SettingsDlgProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK MobyTimer_Proc(UINT, UINT, DWORD, DWORD, DWORD); 
void CALLBACK AhabTimer_Proc(UINT, UINT, DWORD, DWORD, DWORD); 
void InitializeGame();
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

/* IMPLEMENTATION */

/* ****************************************************************
   ChangeDir()
   Sets Moby's direction at random
  ***************************************************************** */
void ChangeDir(int old_dir)
{
  while (MobyDir == old_dir)
  {
    MobyDir = rand() % 8;
  }
} // end ChangeDir()


/* ****************************************************************
   Move_Moby()
   Timed event. .
  ***************************************************************** */
void Move_Moby()
{
static int first_time=1;
static long old_time;

if (first_time)
{
   // reset first time
   first_time=0;
   old_time = mytime;
} // end if first time
else
{ // not first time
   if (1)
   // Time to move!
   {
      if (TimeToBlow++ > TIME_TO_BLOW) TimeToBlow = 0;
      old_time = mytime; 
      // See if Moby changes course
      if (rand() % MOBY_COURSE == 0) ChangeDir(MobyDir);
      // Move Moby on his course
      switch (MobyDir)
      {
        case DIR_N:
        case DIR_NE:
        case DIR_NW: MobyY--;
          break;
        case DIR_S:
        case DIR_SW:
        case DIR_SE: MobyY++;           // E
          break;
      }
      switch (MobyDir)
      {
        case DIR_NE:
        case DIR_E:
        case DIR_SE: MobyX++;
                 break;
        case DIR_NW:
        case DIR_SW:
        case DIR_W: MobyX--;
                break;
      } // end switch

      // Check for legality of move. If Moby is moving off the map,
      // change his direction. Note the new direction may not be legal
      // but that will be checked next time.
      if (MobyX >= GRIDWD)
      {
        MobyX = GRIDWD-1;
        ChangeDir(MobyDir);
      }
      if (MobyY >= GRIDHT)
      {
        MobyY = GRIDHT-1;
        ChangeDir(MobyDir);
      }
      if (MobyX < 0)
      {
        MobyX = 0;
        ChangeDir(MobyDir);
      }
      if (MobyY < 0)
      {
        MobyY = 0;
        ChangeDir(MobyDir);
      }
    }
  } // end else
} // end Move_Moby


/* ******************************************************************
  Move_Ahab()
  Timed event. Check the state of the keys and move Ahab accordingly.
 ******************************************************************** */
int Move_Ahab()
{
  int key_table[8];  
  
         
  // Update the lookup table according to the current state of the 
  //   direction keys. For our purposes, the key is down if either
  //   the most-significant bit (key is down) or the least-significant 
  //   (key has been down since the last time we checked) is set. 
  key_table[INDEX_RIGHT]     = GetAsyncKeyState(VK_RIGHT);
  key_table[INDEX_DOWNRIGHT] = GetAsyncKeyState(VK_NEXT);
  key_table[INDEX_DOWN]      = GetAsyncKeyState(VK_DOWN);
  key_table[INDEX_DOWNLEFT]  = GetAsyncKeyState(VK_END);
  key_table[INDEX_LEFT]      = GetAsyncKeyState(VK_LEFT);
  key_table[INDEX_UPLEFT]    = GetAsyncKeyState(VK_HOME);
  key_table[INDEX_UP]        = GetAsyncKeyState(VK_UP);
  key_table[INDEX_UPRIGHT]   = GetAsyncKeyState(VK_PRIOR);

  // Change Ahab's row and column according to key table
  if (key_table[INDEX_DOWN]
  || key_table[INDEX_DOWNLEFT]
  || key_table[INDEX_DOWNRIGHT])
    AhabY++;
  if (key_table[INDEX_UP]
  || key_table[INDEX_UPRIGHT]
  || key_table[INDEX_UPLEFT])
    AhabY--;
  if (key_table[INDEX_LEFT]
  || key_table[INDEX_UPLEFT]
  || key_table[INDEX_DOWNLEFT])
    AhabX--;
  if (key_table[INDEX_RIGHT]
  || key_table[INDEX_DOWNRIGHT]
  || key_table[INDEX_UPRIGHT])
    AhabX++;

  // Bring within bounds
  if (AhabX >= GRIDWD) AhabX = GRIDWD-1;
  if (AhabY >= GRIDHT) AhabY = GRIDHT-1;
  if (AhabX < 0) AhabX = 0;
  if (AhabY < 0) AhabY = 0;

  AhabMoved = ((OldAhabX != AhabX) || (OldAhabY != AhabY));
  return AhabMoved;
} // end Move_Ahab


/* ********************************************************
   MoveCloud()
   This function is a separate thread. For the purposes of the
   demonstration we do the screen update for the cloud here, so
   that we can monitor its progress independently of normal
   updates. 
   ******************************************************** */
DWORD MoveCloud(LPVOID lpParam)
{
  static _int64 newtime, oldtime;
  _int64 LeftOver;
  int x, Updates;

  oldtime = timeGetTime();
  do  // forever
  {
    Updates = 0;
    newtime = timeGetTime();
    if (((newtime - oldtime) >= CLOUD_INTERVAL)
          && (!paused))
    {
      Updates = (int) ((newtime - oldtime) / CLOUD_INTERVAL);
      LeftOver = (newtime - oldtime) % CLOUD_INTERVAL;
      oldtime = newtime - LeftOver;
    }
    DirtyRect.top = CloudY;
    DirtyRect.bottom = CloudY + SPRITE_HT;
    DirtyRect.left = CloudX;
    DirtyRect.right = 0;
    // update the position 
    for (x = 0; x < Updates; x++)
    {
      // Reach right edge; erase and start again at left edge
      if (CloudX++ > (GRIDWD * SPRITE_WD)) 
      { 
        EraseSprite(CloudX-1, CloudY);
        CloudX = 0;
        CloudRow = rand() % GRIDHT;
        CloudY = CloudRow * SPRITE_HT;
      }
      else DirtyRect.right = CloudX;
      // Clear wake condition for this cell
      if ((CloudX / SPRITE_WD) < GRIDWD)
        painted[CloudRow][CloudX / SPRITE_WD] = 0;
    } // end updating loop

      // Draw the cloud if necessary
    if (Updates) 
    {
      // Erase the dirty sliver
      if (DirtyRect.right)
        InvalidateRect(hMainWindow, &DirtyRect, TRUE);
      // Draw the cloud       
      PutSprite(CloudX, CloudY, bm_cloud);
    }
  } while (1);
  return 0;
}  // Move_Cloud


/* ****************************************************************** 
   PutSprite()
   Paints a sprite directly to the screen, without transparency
  ******************************************************************* */
void PutSprite(int X, int Y, HBITMAP sprite)
{
  BITMAP    bm;
  HDC       hdcMem;
  POINT     ptSize; 

  hdcMem = CreateCompatibleDC(hMainDC);
  SelectObject(hdcMem, sprite);
  GetObject(sprite, sizeof(BITMAP), (LPVOID) &bm);
  ptSize.x = bm.bmWidth;
  ptSize.y = bm.bmHeight;
  BitBlt(hMainDC, X, Y, ptSize.x, ptSize.y, hdcMem, 0, 0, SRCCOPY);
  DeleteDC(hdcMem);
} // PutSprite()


/* ******************************************************************
   EraseSprite()
   Erases any sprite at the coordinates and paints with the background
   brush
  ******************************************************************* */

void EraseSprite(int X, int Y)
{
  RECT rect;

  rect.left =  X;
  rect.top  =  Y;
  rect.right = X + SPRITE_WD;
  rect.bottom= Y + SPRITE_HT;
  InvalidateRect(hMainWindow, &rect, 1);
} // EraseSprite()


/* ******************************************************************
   UpdateScreen()
   Updates sprites as necessary
  ******************************************************************* */
void UpdateScreen()
{
  int X, Y;
  static LastMobyX = 0;
  static LastMobyY = 0;   // last Moby actually drawn

  // Erase old Moby 
  if (painted[LastMobyY][LastMobyX])
  {
    X = LastMobyX * SPRITE_WD; Y = LastMobyY * SPRITE_HT;
    PutSprite(X, Y, bm_wake);
  }
  // Update spout if it's time
  if (TimeToBlow == 0)
  {
    // erase old spout
    X = BlowX * SPRITE_WD; Y = BlowY * SPRITE_HT;
    if (painted[BlowY][BlowX])
      PutSprite(X,Y,bm_wake);
      else EraseSprite(X,Y);
    // paint new spout
    X = MobyX * SPRITE_WD; Y = MobyY * SPRITE_HT;
    PutSprite(X,Y,bm_spout);
    // save spout's position
    BlowX = MobyX; BlowY = MobyY;
    TimeToBlow = 1;    
  } // end paint spout
  else  // not time to blow; paint Moby if he's surfaced
  {
    X = MobyX * SPRITE_WD;
    Y = MobyY * SPRITE_HT;
    if (painted[MobyY][MobyX])
    {
      PutSprite(X,Y,bm_moby);
      LastMobyX = MobyX; LastMobyY = MobyY;
    }
  }
  OldMobyX = MobyX; OldMobyY = MobyY;

  // Always redraw Ahab in case Moby overwrote him
  X = AhabX * SPRITE_WD; Y = AhabY * SPRITE_HT;
  PutSprite(X,Y,bm_ahab);

  // Update Ahab's position and draw wake if he moved.
  if ((OldAhabX != AhabX) || (OldAhabY != AhabY))
  {
    painted[OldAhabY][OldAhabX] = 1;
    X = OldAhabX * SPRITE_WD; Y = OldAhabY * SPRITE_HT;
    PutSprite(X,Y,bm_wake);
    OldAhabX = AhabX; OldAhabY = AhabY;
  }

  AhabMoved = 0;
} // UpdateScreen()


/* ******************************************************************
   SettingsDlgProc()
   The Settings Dialog procedure, called by Windows to respond
   to messages sent to the dialog
  ******************************************************************* */
BOOL CALLBACK SettingsDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, 
                                                    LPARAM lParam)
{
  // the currently selected buttons
  static int AppCheck = IDC_APP_NORMAL;
  static int MainThreadCheck = IDC_THREAD_NORMAL2;
  static int CloudThreadCheck = IDC_THREAD_NORMAL;

  int priority;

  switch (iMsg)
  {
    case WM_INITDIALOG:
      // set the radio buttons to the current selection
      CheckRadioButton(hDlg, IDC_APP_REALTIME, IDC_APP_IDLE, AppCheck);
      CheckRadioButton(hDlg, IDC_THREAD_CRITICAL, IDC_THREAD_IDLE, CloudThreadCheck);
      CheckRadioButton(hDlg, IDC_THREAD_CRITICAL2, IDC_THREAD_IDLE2, MainThreadCheck);
      return TRUE;

    case WM_COMMAND:
      switch (LOWORD (wParam))
      {
      // Respond to click on radio button by resetting the static
      //  variable holding the current setting. Since the radio buttons
      //  are "automatic" we don't have to update the buttons themselves.
        case IDC_APP_REALTIME:
        case IDC_APP_HIGH:
        case IDC_APP_NORMAL:
        case IDC_APP_IDLE:
          AppCheck = LOWORD (wParam);
          return TRUE;

        case IDC_THREAD_CRITICAL:
        case IDC_THREAD_HIGHEST:
        case IDC_THREAD_ABOVE: 
        case IDC_THREAD_NORMAL: 
        case IDC_THREAD_BELOW: 
        case IDC_THREAD_LOWEST: 
        case IDC_THREAD_IDLE: 
          CloudThreadCheck = LOWORD (wParam);
          return TRUE;

        case IDC_THREAD_CRITICAL2:
        case IDC_THREAD_HIGHEST2:
        case IDC_THREAD_ABOVE2: 
        case IDC_THREAD_NORMAL2: 
        case IDC_THREAD_BELOW2: 
        case IDC_THREAD_LOWEST2: 
        case IDC_THREAD_IDLE2: 
          MainThreadCheck = LOWORD (wParam);
          return TRUE;

        // When the dialog is closed, we check the current state of
        // the radio buttons and make the appropriate changes to the
        // class and thread priorities.
        case IDOK:
        case IDCANCEL:
          switch (AppCheck)
          {
            case IDC_APP_REALTIME: priority = REALTIME_PRIORITY_CLASS; break;
            case IDC_APP_HIGH:     priority = HIGH_PRIORITY_CLASS; break;
            case IDC_APP_NORMAL:   priority = NORMAL_PRIORITY_CLASS; break;
            case IDC_APP_IDLE:     priority = IDLE_PRIORITY_CLASS;
          } 
          SetPriorityClass(GetCurrentProcess(), priority);

          switch (CloudThreadCheck)
          {
            case IDC_THREAD_CRITICAL: 
                   priority = THREAD_PRIORITY_TIME_CRITICAL;
                   break;
            case IDC_THREAD_HIGHEST:
                   priority = THREAD_PRIORITY_HIGHEST;
                   break;
            case IDC_THREAD_ABOVE: 
                   priority = THREAD_PRIORITY_ABOVE_NORMAL;
                   break;
            case IDC_THREAD_NORMAL: 
                   priority = THREAD_PRIORITY_NORMAL;
                   break;
            case IDC_THREAD_BELOW: 
                   priority = THREAD_PRIORITY_BELOW_NORMAL;
                   break;
            case IDC_THREAD_LOWEST: 
                   priority = THREAD_PRIORITY_LOWEST;
                   break;
            case IDC_THREAD_IDLE: 
                   priority = THREAD_PRIORITY_IDLE;
          } 
          SetThreadPriority(hCloudThread, priority);

          switch (MainThreadCheck)
          {
            case IDC_THREAD_CRITICAL2: 
                   priority = THREAD_PRIORITY_TIME_CRITICAL;
                   break;
            case IDC_THREAD_HIGHEST2:
                   priority = THREAD_PRIORITY_HIGHEST;
                   break;
            case IDC_THREAD_ABOVE2: 
                   priority = THREAD_PRIORITY_ABOVE_NORMAL;
                   break;
            case IDC_THREAD_NORMAL2: 
                   priority = THREAD_PRIORITY_NORMAL;
                   break;
            case IDC_THREAD_BELOW2: 
                   priority = THREAD_PRIORITY_BELOW_NORMAL;
                   break;
            case IDC_THREAD_LOWEST2: 
                   priority = THREAD_PRIORITY_LOWEST;
                   break;
            case IDC_THREAD_IDLE2: 
                   priority = THREAD_PRIORITY_IDLE;
          } 
          SetThreadPriority(hMainThread, priority);

          EndDialog(hDlg, 0);
          return TRUE;
      }  
      break;

  } // switch (iMsg)

  return FALSE;
} // SettingsDlgProc



/* ********************************************************* 
   WindowProc()
   This is the function Windows calls in response to messages 
   dispatched in the main loop. Any messages not handled here 
   are handled by a default procedure.
************************************************************ */

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, 
                            WPARAM wParam, LPARAM lParam)
{
  static HINSTANCE   hInstance;

  switch( message )
  {
    case WM_CREATE:
      hInstance = ((LPCREATESTRUCT) lParam)->hInstance;
      return 0;

    case WM_COMMAND:
      switch( LOWORD (wParam))
      {
        case ID_FILE_EXIT:
              SendMessage(hWnd, WM_CLOSE, 0, 0L);
              break;

        case ID_FILE_NEWGAME:
              InitializeGame();
              break;

        case ID_PRIORITIES:
                DialogBox(hInstance, MAKEINTRESOURCE(IDD_SETTINGS_DLG), 
                          hWnd, (DLGPROC) SettingsDlgProc);
              break;
        }  // case WM_COMMAND
        break;

    case WM_MOVE_MOBY:
        if (!paused) Move_Moby();
        break;

    case WM_MOVE_AHAB:
        if (!paused) Move_Ahab();
        break;

    case WM_KEYDOWN:
      switch( wParam )
      {
        case VK_ESCAPE:
        case VK_F12:
          PostMessage(hWnd, WM_CLOSE, 0, 0);
          break;
      }
      break;

    case WM_ACTIVATEAPP:
      paused = !wParam;
      if (paused) SetWindowText(hWnd, "Moby Dick -- paused");
      else SetWindowText(hWnd, "Moby Dick");
      return 0;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;
  } // switch (message)

  return DefWindowProc(hWnd, message, wParam, lParam);

} /* WindowProc */


/* ****************************************************************** 
   Timer functions. 
   These respond to windows timer messages by putting a message in the
   queue. Windows then calls the appropriate functions to deal with these
   messages.
  ******************************************************************* */
void CALLBACK MobyTimer_Proc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1,
    DWORD dw2) 
{
  PostMessage(hMainWindow, WM_MOVE_MOBY, NULL, NULL);
  return;
}

void CALLBACK AhabTimer_Proc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1,
    DWORD dw2) 
{
  PostMessage(hMainWindow, WM_MOVE_AHAB, NULL, NULL);
  return;
}


/* ****************************************************************** 
   InitializeGame()
   Resets the game state for the start of a new game
  ******************************************************************* */
void InitializeGame()
{
  // Place Moby at random
  OldMobyX = MobyX = rand() % GRIDWD;
  OldMobyY = MobyY = rand() % GRIDHT;

  // Randomize his direction of travel
  ChangeDir(0);

  // Place Ahab at center of screen
  OldAhabX = AhabX = GRIDWD / 2;
  OldAhabY = AhabY = GRIDHT / 2;
 
 // Erase all sprites
  InvalidateRect(hMainWindow, NULL, 1);

  // Clear the logical sea
  memset(painted, 0, sizeof(painted));
  CloudX = 9999;      // will randomize row in MoveCloud()
} // InitializeGame()


/* ******************************************************************
   WinMain()
   Initialization and game loop
  ******************************************************************* */

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine, int nCmdShow)
{
  MSG         msg;
  int         Control;

  lpCmdLine = lpCmdLine;
  hPrevInstance = hPrevInstance;


  HWND                hwnd;
  HBITMAP             hBG_BMP;
  HBRUSH              hBrush;
  WNDCLASS            wc;
  MMRESULT MobyTimer, AhabTimer;


  // create background brush (clear sea) by loading from resource
  // file and into brush object
  hBG_BMP = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_SEA));
  hBrush = CreatePatternBrush(hBG_BMP);

  // load the sprites from the resource file
  bm_wake = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_WAKE));
  bm_moby = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_MOBY));                    
  bm_spout = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_SPOUT));                    
  bm_ahab = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_AHAB));                    
  bm_cloud = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_CLOUD));                    

  // set up and register window class   
  wc.style = 0;
  wc.lpfnWndProc = WindowProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon( hInstance, IDI_APPLICATION );
  wc.hCursor = LoadCursor( NULL, IDC_ARROW );
  wc.hbrBackground = hBrush;
  wc.lpszMenuName = NAME;
  wc.lpszClassName = NAME;
  RegisterClass( &wc );
    
  // create the window. We calculate its size from the dimensions of the
  // desired client area (i.e. the playing field) plus the size of the
  // caption bar, menu, and borders.
  hwnd = CreateWindow(
    NAME,
    TITLE,
    WS_POPUPWINDOW | WS_CAPTION | WS_VISIBLE,
    0, 0,
    (GRIDWD * SPRITE_WD) + (2 * GetSystemMetrics(SM_CXFIXEDFRAME)), 
    (GRIDHT * SPRITE_HT) + GetSystemMetrics(SM_CYCAPTION) 
      + (2 * GetSystemMetrics(SM_CYFIXEDFRAME)
      + GetSystemMetrics(SM_CYMENU)),
    HWND_DESKTOP,
    NULL,
    hInstance,
    NULL );

  if(!hwnd) return FALSE;
  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  // Get some global handles 
  hMainWindow = hwnd;
  hTheInstance = hInstance;
  hMainDC = GetDC(hwnd);

  // Set multimedia timers. The first argument is the interval in milliseconds.
  //   The second argument is the resolution in ms, i.e. how often Windows checks
  //   to see if the event is due to be triggered. This argument seems to be
  //   ignored if it is greater than the timer interval.
  MobyTimer = timeSetEvent(MOBY_INTERVAL, 200, MobyTimer_Proc, NULL, TIME_PERIODIC); 
  AhabTimer = timeSetEvent(AHAB_INTERVAL, 200, AhabTimer_Proc, NULL, TIME_PERIODIC);

  // set up a separate thread for the cloud animation
  hCloudThread = CreateThread(NULL, NULL, 
                              (LPTHREAD_START_ROUTINE) MoveCloud, 
                              0, 0, &CloudThreadID);

  // get a pseudohandle to the main thread
  hMainThread = GetCurrentThread();

 // seed random number generator
  srand((unsigned)time(NULL));

  // set up the game
  InitializeGame();

  // The main loop. If there's a message to process, do it. Otherwise check
  // whether the screen needs updating and do it if necessary. 
  do
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT) break;   // the only way out of the loop
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else 
    {
      if ((MobyX != OldMobyX) || (MobyY != OldMobyY)
       || (AhabMoved))
      {
        UpdateScreen();
        if ((AhabX == MobyX) && (AhabY == MobyY) && (painted[AhabY][AhabX]))
        {
           Control = MessageBoxEx(hwnd, "You caught Moby! Play again?",
                        "Call Me Ishmael", MB_ICONQUESTION | MB_YESNO, 0); 
           if (Control == IDYES) InitializeGame();
           else break;
        }

      } // if anybody moved
    }  // if screen updated
  } // end of loop
  while (1);

  // release the system resources we used
  timeKillEvent(MobyTimer);
  timeKillEvent(AhabTimer);
  DeleteObject(hBrush); 
  ReleaseDC(hwnd, hMainDC);

  return msg.wParam;

} /* WinMain */


/*
   Copyright (c) 1996 Microsoft Corporation
*/
