/* Moby Dick for Windows v. 3.0
   by Peter Donnelly

   Copyright (c) 1996 Microsoft Corporation

   This simple game illustrates some basic game-programming concepts
   for comparison with the MS-DOS version.

   Moby moves at random but tends to stay on the same course for a
   while at least. He spouts at intervals, and his spout persists
   on the screen until he spouts again, giving a clue to his
   whereabouts.

   The player moves Captain Ahab's ship with the arrow keys, the numeric
   keypad, the joystick, or the mouse. As the ship moves, it paints the 
   screen with its wake. Whenever Moby crosses the wake, he becomes visible. 
   Moby can only be caught on a square that has already been painted.

   The player wins by intercepting Moby. In this version there is no
   time-limit.

   The code was developed with Microsoft Visual C++ v. 4.0.
*/

#define USE_DIRECTSOUND

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>           // for debugging
#include <mmsystem.h>        // link WINMM.LIB as well
#include "resource.h"
#include "draw.h"

#ifdef USE_DIRECTSOUND
  #include "sound.h"
#endif

#define TITLE "Moby Windows"
#define NAME "Moby"

#define MOBY_INTERVAL 250       // Moby's speed (milliseconds per move)
#define AHAB_INTERVAL 200       // Ahab's default speed
#define UPDATE_INTERVAL 40      // controls frame rate 
#define MOBY_COURSE 8           // average no. of moves on same course
#define TIME_TO_BLOW 15         // number of moves between spouts

#define MUSICFILE "sacdan.mid"

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

// User-defined messages
#define WM_MOVE_MOBY   WM_USER + 1
#define WM_MOVE_AHAB   WM_USER + 2
#define WM_UPDATE      WM_USER + 3

#define JOY_DEADZONE   20        // percentage of range that makes up dead zone

/* *******************                                
 Global variables
******************** */

int painted[GRIDHT][GRIDWD];     // array for ship's wake
BOOL paused;
long mytime;
int MobyX, MobyY;                // Moby's coordinates in grid
int OldMobyX, OldMobyY;
int AhabX, AhabY;                // Ahab's coordinates in grid
int OldAhabX, OldAhabY;
int MobyDir;                     // Moby's current direction of travel
int TimeToBlow;                  // counter for spouting
int BlowX, BlowY;                // location of last spout
UINT AhabSpeed;                  // ms per move - can be reset with "throttle"
BOOL MusicOn;

// other global handles
HWND        hMainWindow;                
HINSTANCE   hTheInstance;
MMRESULT    MobyTimer, AhabTimer, UpdateTimer;

// joystick stuff
JOYINFOEX   joyInfoEx;              
JOYCAPS     joyCaps;
BOOL        JoyPresent;
BOOL        JoyHasThrottle;
BOOL        JoyActive;
// define boundaries of joystick dead zone
UINT        JoyDeadXMax, JoyDeadXMin, JoyDeadYMax, JoyDeadYMin;

// mouse stuff
BOOL        MousePresent;                
BOOL        MouseActive;
POINT       MouseXY;

// sound
BOOL        SoundOn;
UINT        wMidiDeviceID;


/* ***************************
   Function prototypes
 ***************************** */

void ChangeDir(int);
void Move_Moby();
void Move_Ahab();
void UpdateSprites();
DWORD PlayMusic(HWND hwnd, LPSTR lpszMIDIFileName);
void  CloseMusic();
void CALLBACK MobyTimer_Proc(UINT, UINT, DWORD, DWORD, DWORD); 
void CALLBACK AhabTimer_Proc(UINT, UINT, DWORD, DWORD, DWORD); 
void InitializeGame();
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);


/* IMPLEMENTATION */


/* ****************************************************************
   Functions to tell whether joystick is pushed in any of the four
   cardinal directions
  ***************************************************************** */
BOOL GetJoyCoords(JOYINFOEX *info)
  // returns TRUE if successful
  {
  if (!JoyActive) return FALSE;
  info->dwSize = sizeof(joyInfoEx);
  info->dwFlags = JOY_RETURNX | JOY_RETURNY;   // | JOY_USEDEADZONE;
  return (!joyGetPosEx(JOYSTICKID1, info));
  }

BOOL JoyNorth(void)
  {
  if (!GetJoyCoords(&joyInfoEx)) return FALSE;  
  return (joyInfoEx.dwYpos < JoyDeadYMin);
  }

BOOL JoySouth(void)
  {
  if (!GetJoyCoords(&joyInfoEx)) return FALSE;  
  return (joyInfoEx.dwYpos > JoyDeadYMax); 
  }

BOOL JoyEast(void)
  {
  if (!GetJoyCoords(&joyInfoEx)) return FALSE;  
  return (joyInfoEx.dwXpos > JoyDeadXMax); 
  }

BOOL JoyWest(void)
  {
  if (!GetJoyCoords(&joyInfoEx)) return FALSE;  
  return (joyInfoEx.dwXpos < JoyDeadXMin); 
  }

/* ***************************************************
   Functions to tell whether Ahab needs to be moved 
   in response to mouse.
  **************************************************** */

BOOL MouseNorth(RECT Ahab)
  {
  if (!MouseActive) return FALSE;
  return (MouseXY.y < Ahab.top);
  }

BOOL MouseSouth(RECT Ahab)
  {
  if (!MouseActive) return FALSE;
  return (MouseXY.y > Ahab.bottom);
  }

BOOL MouseEast(RECT Ahab)
  {
  if (!MouseActive) return FALSE;
  return (MouseXY.x > Ahab.right);
  }

BOOL MouseWest(RECT Ahab)
  {
  if (!MouseActive) return FALSE;
  return (MouseXY.x < Ahab.left);
  }


/* ******************************************************
   ChangeDir()
   Sets Moby's direction at random
  ******************************************************* */
void ChangeDir(int old_dir)
  {
  while (MobyDir == old_dir)
    {
    MobyDir = rand() % 8;
    }
  } // end ChangeDir()


/* ******************************************************
   Move_Moby()
   Timed event. .
  ******************************************************* */
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
        case DIR_SE: MobyY++; 
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
      // change his direction. 
      if (MobyX >= GRIDWD)
        {
        MobyX = GRIDWD-1;
        MobyDir = DIR_W;
        }
      else if (MobyX < 0)
        {
        MobyX = 0;
        MobyDir = DIR_E;
        }
      if (MobyY >= GRIDHT)
        {
        MobyY = GRIDHT-1;
        MobyDir = DIR_N;
        }
      else if (MobyY < 0)
        {
        MobyY = 0;
        MobyDir = DIR_S;
        }
      }
    } // end else
  } // end Move_Moby


/* ******************************************************************
  Move_Ahab()
  Timed event. Check the state of the keys and move Ahab accordingly.
 ******************************************************************** */
void Move_Ahab(void)
  {
  int key_table[8];
  RECT AhabRect;

  JoyActive = (!MouseActive) && JoyPresent;

  /* Get sprite and mouse positions */

  // get position of sprite, for mouse movement
  AhabRect.top = AhabY * SPRITE_HT;
  AhabRect.bottom = AhabRect.top + SPRITE_HT;
  AhabRect.left = AhabX * SPRITE_WD;
  AhabRect.right = AhabRect.left + SPRITE_WD;

  // convert sprite position to screen coordinates
  ClientToScreen(hMainWindow, (POINT*) &AhabRect);
  ClientToScreen(hMainWindow, (POINT*) &AhabRect.right);

  // Get cursor position in screen coordinates
  if (MouseActive && MousePresent)
      GetCursorPos(&MouseXY);  

  /* Read keyboard */

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

  /* Move */

  // Change Ahab's row and column according to key table or
  //   mouse or joystick input
  if (key_table[INDEX_DOWN]
  || key_table[INDEX_DOWNLEFT]
  || key_table[INDEX_DOWNRIGHT]
  || JoySouth()
  || MouseSouth(AhabRect))
    AhabY++;
  if (key_table[INDEX_UP]
  || key_table[INDEX_UPRIGHT]
  || key_table[INDEX_UPLEFT]
  || JoyNorth()
  || MouseNorth(AhabRect))
    AhabY--;
  if (key_table[INDEX_LEFT]
  || key_table[INDEX_UPLEFT]
  || key_table[INDEX_DOWNLEFT]
  || JoyWest()
  || MouseWest(AhabRect))
    AhabX--;
  if (key_table[INDEX_RIGHT]
  || key_table[INDEX_DOWNRIGHT]
  || key_table[INDEX_UPRIGHT]
  || JoyEast()
  || MouseEast(AhabRect))
    AhabX++;
  // Bring within bounds
  if (AhabX >= GRIDWD) AhabX = GRIDWD-1;
  if (AhabY >= GRIDHT) AhabY = GRIDHT-1;
  if (AhabX < 0) AhabX = 0;
  if (AhabY < 0) AhabY = 0;

    /* Joystick throttle */

  // If speed is user-changeable, set a new timer
  if (JoyHasThrottle && JoyActive)
    {
    // We've already used joyInfoEx so we don't need to set dwSize
    joyInfoEx.dwFlags = JOY_RETURNZ;   
    joyGetPosEx(JOYSTICKID1, &joyInfoEx);

    if (joyInfoEx.dwZpos < (joyCaps.wZmax - joyCaps.wZmin) * 0.33)
      AhabSpeed = AHAB_INTERVAL - 100;
    else if (joyInfoEx.dwZpos < (joyCaps.wZmax - joyCaps.wZmin) * 0.66)
      AhabSpeed = AHAB_INTERVAL;
    else AhabSpeed = AHAB_INTERVAL + 100;
    timeKillEvent(AhabTimer);
    AhabTimer = timeSetEvent(AhabSpeed, 100, AhabTimer_Proc, NULL, TIME_PERIODIC);
    }

  /* Read mouse buttons */

  else if (MouseActive)
    {
     // here we can check on the state of the buttons with GetAsyncKeyState
    }

  return;
  } // end Move_Ahab


/* ******************************************************************
   UpdateSprites()
   Updates sprites as necessary
  ******************************************************************* */
void UpdateSprites()
  {
  int X, Y;
  float pan;

  if ((OldMobyY != MobyY) || (OldMobyX != MobyX))
    {
    // Blow if it's time
    if (TimeToBlow == 0)
      {
      // erase old spout
      X = BlowX * SPRITE_WD; 
      Y = BlowY * SPRITE_HT;
      EraseSprite(X,Y);
      if (painted[BlowY][BlowX])
        PutSprite(X,Y,BM_WAKE);
      // paint new spout
      X = MobyX * SPRITE_WD; Y = MobyY * SPRITE_HT;
      PutSprite(X,Y,BM_SPOUT);
      // save spout's position
      BlowX = MobyX; BlowY = MobyY;
      TimeToBlow = 1; 
      if (SoundOn) 
        {
        #ifdef USE_DIRECTSOUND
       // calculate the pan (stereo effect) in the range -10000..10000
        pan = (float) MobyX / GRIDWD;
        Blow(-10000 + (int) (pan * 20000));         
        #else     
        PlaySound(MAKEINTRESOURCE(IDR_WAVE_BLOW), hTheInstance, 
                  SND_ASYNC | SND_RESOURCE);   
        #endif
        } // end of sound
      }  //  end of blowing
    else  // not time to blow; paint Moby if he's surfaced
      {
      // paint new Moby
      if ((painted[MobyY][MobyX])
     // but not if there's a spout there already
         && ((MobyY != BlowY) 
         || (MobyX != BlowX)))
        {
        X = MobyX * SPRITE_WD;
        Y = MobyY * SPRITE_HT;
        PutSprite(X,Y,BM_MOBY);
        }
      }  // end of painting Moby

    // Redraw Ahab if Moby overwrote him
    if ((MobyX == AhabX) && (MobyY == AhabY))
      {
      X = AhabX * SPRITE_WD; Y = AhabY * SPRITE_HT;
      PutSprite(X,Y,BM_AHAB);
      }
    // erase old Moby - if we saw him, it's a wake.
    if ((painted[OldMobyY][OldMobyX])
    // but don't erase if it's a spout
         && ((OldMobyY != BlowY) 
         || (OldMobyX != BlowX)))
      {
      X = OldMobyX * SPRITE_WD; 
      Y = OldMobyY * SPRITE_HT;
      PutSprite(X, Y, BM_WAKE);
      }

    OldMobyX = MobyX; 
    OldMobyY = MobyY;
    } // end Moby move

  // Update Ahab's position and draw wake if he moved.
  if ((AhabX != OldAhabX) || (AhabY != OldAhabY))
    {
    painted[OldAhabY][OldAhabX] = 1;
    X = OldAhabX * SPRITE_WD; 
    Y = OldAhabY * SPRITE_HT;
    PutSprite(X,Y,BM_WAKE);
    X = AhabX * SPRITE_WD; 
    Y = AhabY * SPRITE_HT;
    PutSprite(X,Y,BM_AHAB);
    OldAhabX = AhabX; 
    OldAhabY = AhabY;
    } // end Ahab move
  } // UpdateSprites()

/* ********************************************************* 
   PlayMusic()
   Uses MCI to play a MIDI file. The window procedure
   is notified when playback is complete.
 *********************************************************** */

DWORD PlayMusic(HWND hwnd, LPSTR lpszMIDIFileName)
  {
  MCI_OPEN_PARMS mciOpenParms;
  MCI_PLAY_PARMS mciPlayParms;
  DWORD dwReturn;

  // Open the device by specifying the device and filename.
  // MCI will attempt to choose the MIDI mapper as the output port.
  mciOpenParms.lpstrDeviceType = "sequencer";
  mciOpenParms.lpstrElementName = lpszMIDIFileName;
  if (dwReturn = mciSendCommand(NULL, MCI_OPEN,
      MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
      (DWORD)(LPVOID) &mciOpenParms))
  {
      // Failed to open device. Don't close it; just return error.
      return dwReturn;
  }

  // The device opened successfully; get the device ID.
  wMidiDeviceID = mciOpenParms.wDeviceID;

  // Begin playback. 
  mciPlayParms.dwCallback = (DWORD) hwnd;
  if (dwReturn = mciSendCommand(wMidiDeviceID, MCI_PLAY, MCI_NOTIFY, 
      (DWORD)(LPVOID) &mciPlayParms))
    {
    CloseMusic();
    return dwReturn;
    }
  return 0L;
  } // PlayMusic()


/* ********************************************************* 
   CloseMusic()
   Shuts down the MIDI player
 *********************************************************** */

 void CloseMusic(void)
   {
   if (wMidiDeviceID)
      mciSendCommand(wMidiDeviceID, MCI_CLOSE, 0, NULL);
   wMidiDeviceID = 0; 
   } // CloseMusic

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
  int CheckIt;

  
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

        case ID_SETTINGS_MOUSEMOVEMENT:
              if (!MousePresent) break;
              CheckIt = MouseActive ? MF_UNCHECKED : MF_CHECKED;
              CheckMenuItem(GetMenu(hWnd), ID_SETTINGS_MOUSEMOVEMENT,
                            MF_BYCOMMAND | CheckIt);
              MouseActive = !MouseActive;

              break;               

        case ID_SETTINGS_SOUND:
              CheckIt = SoundOn ? MF_UNCHECKED : MF_CHECKED;
              CheckMenuItem(GetMenu(hWnd), ID_SETTINGS_SOUND,
                            MF_BYCOMMAND | CheckIt);
              SoundOn = !SoundOn;

              break;               

        case ID_SETTINGS_MUSIC:
              CheckIt = MusicOn ? MF_UNCHECKED : MF_CHECKED;
              CheckMenuItem(GetMenu(hWnd), ID_SETTINGS_MUSIC,
                            MF_BYCOMMAND | CheckIt);
              MusicOn = !MusicOn;
              if (MusicOn)
                PlayMusic(hWnd, MUSICFILE);
              else 
                CloseMusic();

              break;               
          }  // case WM_COMMAND
        break;

    case WM_MOVE_MOBY:
        if (!paused) 
          {
          Move_Moby();
          }
        break;

    case WM_MOVE_AHAB:
        if (!paused) 
          {
          Move_Ahab();
          }
        break;

    case WM_UPDATE:
        UpdateSprites();
        UpdateScreen(hMainWindow);
        break;

    case WM_KEYDOWN:
      switch( wParam )
        {
        case VK_F7:
          PostMessage(hWnd, WM_COMMAND, ID_SETTINGS_SOUND, 0);
          break;

        case VK_F8:
          PostMessage(hWnd, WM_COMMAND, ID_SETTINGS_MUSIC, 0);
          break;

        case VK_ESCAPE:
          PostMessage(hWnd, WM_CLOSE, 0, 0);
          break;
        }
      break;

    case WM_LBUTTONDOWN:
      if (SoundOn)
        #ifdef USE_DIRECTSOUND
        Boing(1);
        #else
        PlaySound(MAKEINTRESOURCE(IDR_WAVE_BOING), hTheInstance, 
                  SND_ASYNC | SND_RESOURCE | SND_LOOP);   
        #endif
      break;

    case WM_RBUTTONDOWN:
      if (SoundOn)
        #ifdef USE_DIRECTSOUND
        Boing(0);
        #else
        PlaySound(MAKEINTRESOURCE(IDR_WAVE_BOING), hTheInstance, 
                  SND_PURGE);   
        #endif
      break;

    case MM_MCINOTIFY:
      // music over, play it again
      CloseMusic();
      // if music finished, play it again. Otherwise assume that
      // it was aborted by the user or otherwise
      if (wParam == MCI_NOTIFY_SUCCESSFUL)
        PlayMusic(hWnd, MUSICFILE);
      break;

    case WM_ACTIVATEAPP:
      paused = (wParam == 0);
      if (paused)
        {
        SetWindowText(hWnd, "Moby Dick -- paused");
        // probably want to pause the music here too
        }
      else 
        {
        SetWindowText(hWnd, "Moby Dick");
        }
      return 0;

    case WM_DESTROY:
      // release the system resources we used
      timeKillEvent(MobyTimer);
      timeKillEvent(AhabTimer);
      timeKillEvent(UpdateTimer);
    #ifdef USE_DIRECTSOUND
      CleanupSound();
    #endif
      CleanupGraphics();
      CloseMusic();
      PostQuitMessage(0);
      break;
    } // switch (message)

  return DefWindowProc(hWnd, message, wParam, lParam);

  } // WindowProc 


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

void CALLBACK UpdateTimer_Proc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1,
    DWORD dw2) 
  {
  PostMessage(hMainWindow, WM_UPDATE, NULL, NULL);
  return;
  }


/* ****************************************************************** 
   InitializeGame()
   Resets the game state for the start of a new game
  ******************************************************************* */

void InitializeGame()
  {
  // Clear the logical sea
  memset(painted, 0, sizeof(painted));

  // Place Moby at random
  OldMobyX = MobyX = rand() % GRIDWD;
  OldMobyY = MobyY = rand() % GRIDHT;

  // Randomize his direction of travel
  ChangeDir(0);

 // Clear the map
  EraseAllSprites();
 
  // Place Ahab at center of screen
  OldAhabX = AhabX = GRIDWD / 2;
  OldAhabY = AhabY = GRIDHT / 2;
  // place the sprite since this won't be done otherwise till he moves
  int X = AhabX * SPRITE_WD; 
  int Y = AhabY * SPRITE_HT;
  PutSprite(X,Y,BM_AHAB);
  UpdateScreen(hMainWindow);
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
  WNDCLASS            wc;
  RECT                WindowRect;

  // set up and register window class   
  wc.style = 0;
  wc.lpfnWndProc = WindowProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon( hInstance, IDI_APPLICATION);
  wc.hCursor = LoadCursor( NULL, IDC_ARROW);
  wc.hbrBackground = GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName = NAME;
  wc.lpszClassName = NAME;
  RegisterClass(&wc);

  // Get dimensions of window -- size of grid plus frames, menu bar,
  // and caption. Note that AdjustRect adjusts the top left corner,
  // in this case into the negative range
  SetRect(&WindowRect, 0, 0, GRIDWD * SPRITE_WD, GRIDHT * SPRITE_HT);
  AdjustWindowRect(&WindowRect,  WS_POPUPWINDOW | WS_CAPTION, TRUE); 
  
  // Create the window.
  hwnd = CreateWindow(
    NAME,
    TITLE,
    WS_POPUPWINDOW | WS_CAPTION | WS_VISIBLE,
    0, 0,
    WindowRect.right - WindowRect.left,
    WindowRect.bottom - WindowRect.top,
    HWND_DESKTOP,
    NULL,
    hInstance,
    NULL );

  if(!hwnd) return FALSE;
  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  // get some global handles 
  hMainWindow = hwnd;
  hTheInstance = hInstance;

  // check for presence of joystick
  joyInfoEx.dwSize = sizeof(joyInfoEx);
  JoyPresent = (joyGetPosEx(JOYSTICKID1, &joyInfoEx) == JOYERR_NOERROR);
  if (!JoyPresent) 
    OutputDebugString("No joystick.\n");

  // if present, get joystick capabilities
  else 
    {
    joyGetDevCaps(JOYSTICKID1, &joyCaps, sizeof(joyCaps));
    JoyHasThrottle = (joyCaps.wCaps & JOYCAPS_HASZ);

    // calculate boundaries of joystick dead zone
    int JoyDeadSize = (joyCaps.wXmax - joyCaps.wXmin) * JOY_DEADZONE / 100;
    JoyDeadXMax = (joyCaps.wXmax - joyCaps.wXmin) / 2 + (JoyDeadSize / 2);
    JoyDeadXMin = JoyDeadXMax - JoyDeadSize;

    JoyDeadSize = (joyCaps.wYmax - joyCaps.wYmin) * JOY_DEADZONE / 100;
    JoyDeadYMax = (joyCaps.wYmax - joyCaps.wYmin) / 2 + (JoyDeadSize / 2);
    JoyDeadYMin = JoyDeadYMax - JoyDeadSize;
    }  // end joystick initialization 

  // look for mouse
  MousePresent = GetSystemMetrics(SM_MOUSEPRESENT);

  // initialize DirectSound
#ifdef USE_DIRECTSOUND
  if (!InitSound(hMainWindow, hTheInstance))
      OutputDebugString("Failed to initialize DirectSound");
#endif


  // initialize graphics system
  if (!InitGraphics(hwnd))
  {
    MessageBox( hwnd, "DirectDraw initialization failed.", TITLE, MB_OK );
    DestroyWindow(hwnd);
    CleanupGraphics();
    return 0;
  }

  // set multimedia timers
  AhabSpeed = AHAB_INTERVAL;
  MobyTimer = timeSetEvent(MOBY_INTERVAL, 50, MobyTimer_Proc, NULL, TIME_PERIODIC); 
  AhabTimer = timeSetEvent(AhabSpeed, 50, AhabTimer_Proc, NULL, TIME_PERIODIC);
  UpdateTimer = timeSetEvent(UPDATE_INTERVAL, 10, UpdateTimer_Proc, NULL, TIME_PERIODIC);

  // seed random number generator
  srand((unsigned)time(NULL));

  // set up the game and initialize display
  InitializeGame();

  // The main loop.
    do
    {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
      if (msg.message == WM_QUIT) break;  
      TranslateMessage(&msg);
      DispatchMessage(&msg);
      }
    else 
      {
      if (paused) WaitMessage();   // don't gobble CPU time
      else
        {
        // check for win
        if ((AhabX == MobyX) && (AhabY == MobyY) && (painted[AhabY][AhabX]))
          {
          paused = TRUE;  // ignore input
          Control = MessageBoxEx(hwnd, "You caught Moby! Play again?",
                          "Call Me Ishmael", MB_ICONQUESTION | MB_YESNO, 0); 
          paused = FALSE;
          if (Control == IDYES) InitializeGame();
          else break;
          } // end check for victory
        } // end not paused
      } // end non-message action
    } // end of perpetual loop
  while (1);

  return msg.wParam;

  } // WinMain 


/*
   Copyright (c) 1996 Microsoft Corporation
*/
