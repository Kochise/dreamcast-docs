//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   CHILD.H
//|      This files sole purpose in life is to define the CHILDINFO type
//|         which is the main data structure for a connection window.
//*---------------------------------------------------------------------------------
#ifndef child_DEFS
#define child_DEFS

#include <Windows.h>
#include <stdlib.h>
#include "commdlg.h"
#include "standard.h"
#include "menu.h"
#include "results.h"
#include "sql.h"
#include "sqlext.h"

#define MAXCONNECTS        15


//*------------------------------------------------------------------------
//|  The following structure is used to keep track of the vital pieces of
//|      information for each child MDI window.  The actual structure is
//|      stored with the window and can be extracted with only the window
//|      handle.
//*------------------------------------------------------------------------
typedef struct tagCHILDINFO {
   HINSTANCE      hInst;                        // Handle to our data segment
   HWND           hwndClient;                   // Handle to client window
   HWND           hwnd;                         // Handle to the child window
   HWND           hwndIn;                       // Input window
   HWND           hwndOut;                      // Output window
   HENV           henv;                         // Environment handle for application
   HDBC           hdbc;                         // Connection handle of this window
   HSTMT          hstmt;                        // Statement handle for this window

   // Display information
   int            dx;                           // Width of client area
   int            dy;                           // Height of client area

   char           szConnStrOut[DFTBUFFSIZE];    // Save returned connect string
   char           CurrentUser[DFTBUFFSIZE];     // Name of user logged on this window
   char           CurrentServer[DFTBUFFSIZE];   // Server connected to in this window
   int            listtype;                     // What are we listing
   char           szClientTitle[MAXBUFF];       // Title for the window
   UDWORD         fFunctions[MINREQUIREDINTS(NUM_MENU_FLAGS)];
                                                // bitmask to track supported functions
   HFILE          hFile;                        // Pointer to file
   char           szFile[_MAX_PATH];            // Name of the file
   int            cbFileSize;                   // How big is the file
   LPSTR          szFileBuff;                   // Memory for the file
   int            cbResultCount;                // Incremental counter of results windows
   int            cbMaxRS;                      // Maximum results windows
   int            cbResults;                    // Current count of results sets
   LPVOID         lprihead;                     // Head node
   LPVOID         lpritail;                     // Tail node
   } CHILDINFO, FAR * lpCHILDINFO;


// Since this is an MDI app, we will store the connection window information with
// the window handle and must then get this value for each message processed.
// This little macro simply sets the value of ci based on the window
#define GETCIPOINTER(hwnd) (lpCHILDINFO)(GetWindowLong(hwnd, 0))
#define SETCIPOINTER(hwnd, x) SetWindowLong(hwnd, 0, (LONG)(x))

#endif
