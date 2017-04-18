/********************************************************************
 * headers.h
 *
 * Description
 *    General defines, data types, prototypes, and includes for all 
 *    source files.
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include <windows.h>            // Windows main header file
#include <urlmon.h>             // Urlmon main header file, E_PENDING
#include "draw.h"               // DDraw helper functions
#include "input.h"              // DInput helper functions
#include "resource.h"           // resource IDs

/********************************************************************
 * Global variables
 ********************************************************************/
extern HINSTANCE g_hInstance;   // instance of application
extern HWND      g_hwndGame;    // main window of game
extern BOOL      g_f555;        // color type

/********************************************************************
 * Macros - Color helpers
 ********************************************************************/
        // Going from 888 RGB:
        //                    --------BBBBBBBBGGGGGGGGRRRRRRRR
        // to 565 RGB:
        //                    ----------------RRRRRGGGGGGBBBBB
#define COLORREF_TO_565(rgb)                \
            ((WORD) (                       \
            (((rgb) & 0x00f80000) >> 19) |  \
            (((rgb) & 0x0000fc00) >> 5) |   \
            (((rgb) & 0x000000f8) << 8)))   \

        // Going from 888 RGB:
        //                    --------BBBBBBBBGGGGGGGGRRRRRRRR
        // to 555 RGB:
        //                    -----------------RRRRRGGGGGBBBBB
#define COLORREF_TO_555(rgb)                \
            ((WORD) (                       \
            (((rgb) & 0x00f80000) >> 19) |  \
            (((rgb) & 0x0000f800) >> 6) |   \
            (((rgb) & 0x000000f8) << 7)))   \

#define COLORREF_TO_16BPP(rgb)              \
            (g_f555 ?                       \
            COLORREF_TO_555(rgb) :          \
            COLORREF_TO_565(rgb))

/********************************************************************
 * Defines - tool bar command IDs
 ********************************************************************/
#define ID_HOME         100     // go to home page
#define ID_SEARCH       101     // go to search page
#define ID_BACK         102     // go back
#define ID_FORWARD      103     // go forward
#define ID_REFRESH      104     // refresh page
#define ID_STOP         105     // stop loading of page
#define ID_HELP         106     // go to help page
#define ID_KEYBOARD     107     // bring up software keyboard
#define ID_GO           108     // bring up go to url dialog
#define ID_CONNECT      109     // connect through RAS
#define ID_DISCONNECT   110     // disconnect through RAS

/********************************************************************
 * Defines - screen
 ********************************************************************/
#define X_MARGIN        40      // margins of unusable screen area
#define Y_MARGIN        40      // due to rounding of TV corners
#define W_SCREEN        560     // width of usable screen area
#define H_SCREEN        400     // height of usable screen area

/********************************************************************
 * Defines - message IDs
 ********************************************************************/
#define WM_GETDEVICE    (WM_USER + 1000)        // for GetVMUDevice
#define WM_SHOWMSG      (WM_USER + 1001)        // for ShowVMUMessage
#define WM_TOGGLEHTML   (WM_USER + 1002)        // for creating/destroying HTML control

/********************************************************************
 * Defines - font for title bar, status bar, etc.
 ********************************************************************/
#ifdef KANJI
#define FONT_NAME       TEXT("MS Gothic")
#else  // KANJI
#define FONT_NAME       TEXT("Arial")
#endif // KANJI

/********************************************************************
 * Defines - HTML Dialogs
 ********************************************************************/
#define MAX_HTMLDIALOGS     5
