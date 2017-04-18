//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   MENU.H
//|      This file contains our menu ids.
//*---------------------------------------------------------------------------------
#ifndef menu_DEFS
#define menu_DEFS

#include <Windows.h>

//
// Following are indexes into the menu table
//
enum {
   MENU_SQLTABLES,
   MENU_SQLCOLUMNS,
   MENU_SQLSTATISTICS,
   MENU_SQLPRIMARYKEYS,
   MENU_SQLFOREIGNKEYS,
   MENU_SQLTABLEPRIVILEGES,
   MENU_SQLCOLUMNPRIVILEGES,
   MENU_SQLSPECIALCOLUMNS,
   MENU_SQLPROCEDURES,
   MENU_SQLPROCEDURECOLUMNS,
   MENU_SQLTRANSACT
   };

#define NUM_MENU_FLAGS     MENU_SQLTRANSACT


#define  IDM_WINDOW_POS      6
#define  IDM_FIRSTCHILD       200

#define  IDM_FILE_MENU        0
#define  IDM_CONNECT          100
#define  IDM_DISCONNECT       101
#define  IDM_EXECUTE_FILE     102
#define  IDM_OPEN             103
#define  IDM_CLOSE            104
#define  IDM_SAVE             105
#define  IDM_SAVEAS           106
#define  IDM_EXIT             107

#define  IDM_EDIT_MENU        1
#define  IDM_UNDO             108
#define  IDM_CUT              109
#define  IDM_COPY             110
#define  IDM_PASTE            111
#define  IDM_SELECT_ALL       112

#define  IDM_EXECUTE_MENU     2
#define  IDM_EXECUTE_NOW      113
#define  IDM_COMMIT           115
#define  IDM_ROLLBACK         116

#define  IDM_PIPE_MENU        3
#define  IDM_PIPE_EDIT        120
#define  IDM_PIPE_DO          121

#define  IDM_INFO_MENU        4
#define  IDM_MANAGE_DSNS      125
#define  IDM_DATA_SOURCES     126
#define  IDM_DATA_TYPES       127
#define  IDM_FUNCTIONS        128
#define  IDM_ODBC_INFO        129

#define  IDM_LIST_MENU        5
#define  IDM_TABLES           131
#define  IDM_COLUMNS          132
#define  IDM_STATISTICS       133
#define  IDM_PRIMARY_KEYS     134
#define  IDM_FOREIGN_KEYS     135
#define  IDM_TABLE_PRIVS      136
#define  IDM_COLUMN_PRIVS     137
#define  IDM_SPECIAL_COLUMNS  138
#define  IDM_PROCEDURES       139
#define  IDM_PROC_COLUMNS     140


#define  IDM_WINDOW_MENU      6
#define  IDM_FONT             150
#define  IDM_CASCADE          151
#define  IDM_TILE             152
#define  IDM_ARRANGE          153
#define  IDM_CLOSEALL         154

#define  IDM_ABOUT_MENU       7
#define  IDM_HELP             160
#define  IDM_ABOUT            161

#define  IDM_MOVE_WINDOW      165         // F6 key





#define MNU_HAVE_CONNECTS ((lpActiveConn) ? MF_ENABLED : MF_GRAYED)

// Normally menu numbers start at 0 and go up, which is how each offset is shown
//    in this file.  If a child MDI window is zoomed, however, then the child
//    system menu becomes menu number 0 and others are offset.  The following
//    macro will look at the current active window and return the correct
//    0 based menu number.
#define GETMENUNUM(iMenu) (iMenu - ((hwndCurMDIChild) ? (int)IsZoomed(hwndCurMDIChild) : 0))


#define CBITS (sizeof(UDWORD) * 8)
#define BitSet(lpa, pos)   \
   (lpa[((pos) / CBITS)] |= 1 << ((pos) - (CBITS * ((pos) / CBITS))))
#define BitClear(lpa, pos) \
   (lpa[((pos) / CBITS)] &= ~(1 << ((pos) - (CBITS * ((pos) / CBITS)))))
#define BitGet(lpa, pos)   \
   (lpa[((pos) / CBITS)] & (1 << ((pos) - (CBITS * ((pos) / CBITS)))))
#define BitFlip(lpa,pos)   \
   (BitGet(lpa,pos)) ? BitClear(lpa,pos) : BitSet(lpa,pos)
#define MINREQUIREDINTS(items) (UDWORD)((items / CBITS) + ((items % CBITS) ? 1 : 0))





//*---------------------------------------------------------------------------------
//|   Function prototypes
//*---------------------------------------------------------------------------------
VOID WINAPI ResetMenu(HMENU hMenu, int iMenu);



#endif
