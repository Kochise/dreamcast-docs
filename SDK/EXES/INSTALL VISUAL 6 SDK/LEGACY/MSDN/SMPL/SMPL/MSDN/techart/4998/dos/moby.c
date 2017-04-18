/* Moby Dick v. 1.0
   by Peter Donnelly
   Copyright (c) 1996 Microsoft Corporation

   This is a simple MS-DOS game demonstrating the use of keyboard and
   timer interrupt handlers, the game loop, and basic VGA animation
   techniques.

   Moby moves at random but tends to stay on the same course for a
   while at least. He spouts at intervals, and his spout persists
   on the screen until he spouts again, giving a clue to his
   whereabouts.

   The player moves Captain Ahab's ship with the arrow keys or the numeric
   keypad. As the ship moves, it paints the screen with its wake. Whenever
   Moby crosses the wake, he becomes visible. Moby can only be caught on
   a square that has already been painted.

   The player wins by intercepting Moby within the time allotted.
   Note that the timing is machine-independent.

   The code as written compiles under Borland Turbo C++ 3.0. Compile for
   Large model, with 80286 instructions enabled. Link with VIDEO.C.

   Portions of this code were modified from Tricks of the Game Programming 
   Gurus (0-672-30507-0) (C) Copyright Sams Publishing, 1994.  All Rights 
   Reserved. Please call 1-800-428-5331 to order this book/cd.

*/

#include "video.h"
#include <dos.h>
#include <bios.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>

#define MOBY_CLICKS 4       // default speed at which Moby moves
#define AHAB_CLICKS 2       // default speed at which Ahab moves
#define MOBY_COURSE 8       // average clicks to maintain course
#define TIME_TO_BLOW 6      // number of Moby-moves between spouts
#define MAX_TIME 500        // length of game in ticks
#define DIR_N  0
#define DIR_NE 1
#define DIR_E  2
#define DIR_SE 3
#define DIR_S  4
#define DIR_SW 5
#define DIR_W  6
#define DIR_NW 7

#define TIME_KEEPER_INT 0x1C
#define KBD_INTRPT      0x09
#define KBD_CONTROL     0x61
#define INT_CONTROL     0x20

#ifdef DEBUG
#define GRIDHT 5          // half-screen, for debugging in memory-short IDE
#else
#define GRIDHT 10
#endif
#define GRIDWD 10

#define MAKE_ESC         1

/* The following are the make (i.e. key press) codes for the cursor keys.
   These defines are commented out because we only use the numerical values
   in our arrays; they are shown here for reference.
   The break (key release) code for a key is 128 more than the make code.

#define MAKE_RIGHT      77
#define MAKE_LEFT       75
#define MAKE_UP         72
#define MAKE_DOWN       80
#define MAKE_HOME       71
#define MAKE_PGUP       73
#define MAKE_END        79
#define MAKE_PGDN       81
*/

// indices into arrow key state table
#define INDEX_UPLEFT    0
#define INDEX_UP        1
#define INDEX_UPRIGHT   2
#define INDEX_RIGHT     3
#define INDEX_DOWNRIGHT 4
#define INDEX_DOWN      5
#define INDEX_DOWNLEFT  6
#define INDEX_LEFT      7

/*
  Global variables
*/
int raw_key;                                   // global raw keyboard data
int key_table[8] = {0,0,0,0,0,0,0,0};          // cursor key state table
int make_codes[8] = { 71,72,73,77,81,80,79,75};// lookup for key presses,
                                               //   clockwise from upper left
int painted[GRIDHT][GRIDWD];                   // array for ship's wake
cregisters rgb256;

void (_interrupt _far *Old_Kbd_Isr)();         // to save old ISRs
void (_interrupt _far *Old_Timer_Isr)();

long time;
int TimesUp;
int MobyClicks = MOBY_CLICKS;      // could be changed for difficulty level
int MobyX, MobyY;                  // Moby's coordinates
int OldMobyX, OldMobyY;
int AhabX, AhabY;                  // Ahab's coordinates
int AhabMoved;
int OldAhabX, OldAhabY;
int MobyDir;                       // Moby's current direction of travel
int TimeToBlow;                    // counter for spouting
int BlowX, BlowY;                  // location of last spout
byte far *VScreen;                 // dynamically allocated background buffer
ICON icon_wake;                    // sprite buffers
ICON icon_sea;
ICON icon_moby;
ICON icon_spout;
ICON icon_ahab;


/*
  Interrupt functions
*/

/*
  New_Key_Int()
  Replaces the DOS keyboard interrupt handler. This enables us to trap
  every key press or release, so we can update the keyboard state table.
*/
void _interrupt _far New_Key_Int()
  {
  int x;

  asm {
   sti;                  // enable interrupts
   in al, 60h;           // get keypress from I/O port
   xor ah,ah;            // zero out upper byte of AX
   mov raw_key, ax;      // store key in global
   in al, 61h;           // read the control register
   or al, 82h;           //
   out 61h, al;          // send the new data back to the control register
   and al, 7fh;
   out 61h, al;          // reset the register
   mov al, 20h;
   out 20h, al;
    } // end inline assembly


/* Process the key and update the cursor-key state table. If the key
   matches a make code in the lookup table, set the cursor-key state on.
   If it matches a break code (make code+128), set the state off.
   This function could be improved by always preserving a key-down state
   until the next time Ahab actually moves. As it is, if the key is pressed
   and released before it is time for Ahab to move, the keystroke is lost.
*/
   for (x = 0; x < 8; x++)
     {
     if (raw_key == make_codes[x]) key_table[x] = 1;
     else if (raw_key == (make_codes[x] + 128)) key_table[x] = 0;
     }
  } // New_Key_Int


/*
  Timer()
  Replaces the DOS timer interrupt. Enables us to time game events
  independently of processor speed.
*/
void _interrupt _far Timer()
  {
// increment global time variable
time++;
TimesUp--;     // game over when it reaches zero
  } // end Timer

/*
  Routines to move the sprites
*/
/*
  ChangeDir()
  Sets Moby's direction at random
*/
void ChangeDir(int old_dir)
  {
  while (MobyDir == old_dir)
    {
    MobyDir = rand() % 8;
    }
  } // end ChangeDir()

/*
  Move_Moby()
  Timed event.
*/
void Move_Moby()
  {
  static int first_time=1;
  static long old_time;

  if (first_time)
    {
   // reset first time
    first_time=0;
    old_time = time;
    } // end if first time
  else
    { // not first time
    if ( (time - old_time) >= MOBY_CLICKS)
     // Time to move!
      {
      if (TimeToBlow++ > TIME_TO_BLOW) TimeToBlow = 0;
      old_time = time; // save new old time
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

/*
  Move_Ahab()
  Timed event.
*/
int Move_Ahab()
  {
  static int first_time=1;
  static long old_time;

  if (first_time)
    {
   // reset first time
   first_time=0;
   old_time = time;
    } // end if first time
  else
    { // not first time
    if ( (time - old_time) >= AHAB_CLICKS)
      {
      old_time = time; // save new old time
    // Move Ahab on his course
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
      // Check for legality of move.
      if (AhabX >= GRIDWD) AhabX = GRIDWD-1;
      if (AhabY >= GRIDHT) AhabY = GRIDHT-1;
      if (AhabX < 0) AhabX = 0;
      if (AhabY < 0) AhabY = 0;
      return 1;   // he moved
      } // end if (time to move)
    } // end else (not first time)
  return 0;
  } // end Move_Ahab

/*
   Graphics routines
*/

/* InitGraphics()
   Sets up the off-screen buffer, reads the sprites from file,
   sets graphics mode
*/
int InitGraphics()
  {

// Create the off-screen buffer
  VScreen = MakeBuffer(SCREENWORDS * 2);
  if (!VScreen) return 0;  // ERROR

  // get the sprites from file
  if (!read_PCX("wake.pcx", &rgb256, icon_wake)) return 0; // ERROR
  if (!read_PCX("wake.pcx", &rgb256, icon_wake)) return 0;
  if (!read_PCX("sea.pcx", &rgb256, icon_sea)) return 0;
  if (!read_PCX("moby.pcx", &rgb256, icon_moby)) return 0;
  if (!read_PCX("spout.pcx", &rgb256, icon_spout)) return 0;
  if (!read_PCX("ahab.pcx", &rgb256, icon_ahab)) return 0;

  // Change to graphics mode
  SetMCGA();

  // The palette structure, rgb256, holds the values from the last file read.
  // We now use it to program the registers.
  set_color_registers(rgb256);

  return 1;  // success
  } // InitGraphics()

/* DrawSea()
   Resets the background to clear sea. Ahab is drawn on the first pass
   through the game loop.
*/
void DrawSea()
  {
  int x, y, X, Y;

  for (y = 0; y< GRIDHT; y++)
    {
    Y = ICON_HT * y;
    for (x = 0; x < GRIDWD; x++)
      {
       X = ICON_WD * x;
       PutSprite(X, Y, (byte*)icon_sea, VScreen);
      }
    }
  }  // DrawSea()

/*
  UpdateScreen()
  Updates sprites as necessary, and flips the back buffer to the screen.
*/
void UpdateScreen()
  {
  int X, Y;
  static LastMobyX = 0;
  static LastMobyY = 0;   // last Moby actually drawn

  // Erase old Moby. Moby is replaced by clear sea
  // or wake, as appropriate.
  X = LastMobyX * ICON_WD; Y = LastMobyY * ICON_HT;
  if (painted[LastMobyY][LastMobyX])
    PutSprite(X, Y, (byte*)icon_wake, VScreen);
    else PutSprite(X, Y, (byte*)icon_sea, VScreen);

  // Update spout if it's time
  if (TimeToBlow == 0)
    {
    // erase old spout
    X = BlowX * ICON_WD; Y = BlowY * ICON_HT;
    if (painted[BlowY][BlowX])
      PutSprite(X, Y, (byte*)icon_wake, VScreen);
      else PutSprite(X, Y, (byte*)icon_sea, VScreen);
    // paint new spout
    X = MobyX * ICON_WD; Y = MobyY * ICON_HT;
    PutSprite(X, Y, (byte*)icon_spout, VScreen);
    // save spout's position
    BlowX = MobyX; BlowY = MobyY;
    } // end paint spout
  else  // not time to blow; paint Moby if he's surfaced
    {
    X = MobyX * ICON_WD;
    Y = MobyY * ICON_HT;
    if (painted[MobyY][MobyX])
      {
      PutSprite(X, Y, (byte*)icon_moby, VScreen);
      LastMobyX = MobyX; LastMobyY = MobyY;
      }
    }
  OldMobyX = MobyX; OldMobyY = MobyY;

  // Always redraw Ahab in case Moby overwrote him
  X = AhabX * ICON_WD; Y = AhabY * ICON_HT;
  PutSprite(X, Y, (byte*)icon_ahab, VScreen);

  // Update Ahab's position and draw wake if he moved.
  if ((OldAhabX != AhabX) || (OldAhabY != AhabY))
    {
    painted[OldAhabY][OldAhabX] = 1;
    X = OldAhabX * ICON_WD; Y = OldAhabY * ICON_HT;
    PutSprite(X, Y, (byte*)icon_wake, VScreen);
    OldAhabX = AhabX; OldAhabY = AhabY;
    }
  // Flip the offscreen buffer to the screen.
  Flip(VScreen, VGA);
  } // UpdateScreen()


/*
  Main()
*/
main()
  {
  int progdone = 0;
  int gamedone;
  char c;

  clrscr();
  printf("Move the ship with any combination of cursor or numpad keys.\n");
  printf("Moby surfaces and can be caught only where there is a wake.\n\n");
  printf("Any key to begin.");
  c = getch();

  // Initialize the graphics system
  if (!InitGraphics()) {
    cprintf("Failed to initialize graphics.");
    return;
    }

  // Seed random number generator
  srand();
  // enable text printing to graphics screen (Borland-specific)
  directvideo = 0;

  // Save old ISRs
  Old_Timer_Isr = _dos_getvect(TIME_KEEPER_INT);
  Old_Kbd_Isr = _dos_getvect(KBD_INTRPT);

  // Program loop -- repeats game until ESC pressed
  while (!progdone)
    {
    TimesUp = MAX_TIME;            // countdown to game over
    gamedone = 0;
    // Place Moby at random
    OldMobyX = MobyX = rand() % GRIDWD;
    OldMobyY = MobyY = rand() % GRIDHT;

    // Randomize his direction of travel
    ChangeDir(0);

    // Place Ahab at center of screen
    OldAhabX = AhabX = GRIDWD / 2;
    OldAhabY = AhabY = GRIDHT / 2;

    // Draw the background
    DrawSea();

   // Install our interrupt handlers
    _dos_setvect(TIME_KEEPER_INT, Timer);
    _dos_setvect(KBD_INTRPT, New_Key_Int);

    // Initialize the key table so Ahab doesn't move spontaneously
    memset(key_table, 0, sizeof(key_table));
    // Clear the sea
    memset(painted, 0, sizeof(painted));
    // Reset the text origin
    gotoxy(1,1);
    // Game loop -- repeats until game finished or aborted with ESC
    while (!gamedone)
      {
      // call timed routines -- no response if it's not time yet
      AhabMoved = Move_Ahab();
      // Only move Moby if Ahab hasn't moved. Otherwise they can
      // cross paths without intercepting.
      if (!AhabMoved) Move_Moby();

      // Update the screen if anyone has moved
      if ((MobyX != OldMobyX) || (MobyY != OldMobyY)
         || (AhabMoved))
        {
        UpdateScreen();

        // Check for victory or loss
        if ((MobyX == AhabX) && (MobyY == AhabY)
             && (painted[MobyY][MobyX]))
          {
          gamedone = 1;
          cprintf("\a");
          cprintf("You win!");
          }
        if (TimesUp <= 0)
          {
          cprintf("\a");
          cprintf("Time's up!");
          gamedone = 1;
          }
        if (raw_key == MAKE_ESC)
          {
          gamedone = 1;
          progdone = 1;
          }
        } // end update
      } // end of inner game loop (while !gamedone)

    // If not quitting program, wait for key before beginning new game
    // replace old ISRs. Do it here so we can get a keystroke
    _dos_setvect(TIME_KEEPER_INT, Old_Timer_Isr);
    _dos_setvect(KBD_INTRPT, Old_Kbd_Isr);

    if (!progdone)
      {
      cprintf(" Space: play again  Esc: quit");
      c = 0;
      // spacebar for new game, ESC to quit
      while ((c != 32) && (c != 27))
        {
        c = getch();
        progdone = (c == 27);
        };
      }
    } // end of outer game loop (while !progdone)

  // release dynamically allocated memory
  free(VScreen);

  // Restore text mode
  SetText();

  // All done!
  return;
  } // end main

/*
Copyright (c) 1996 Microsoft Corporation
*/
