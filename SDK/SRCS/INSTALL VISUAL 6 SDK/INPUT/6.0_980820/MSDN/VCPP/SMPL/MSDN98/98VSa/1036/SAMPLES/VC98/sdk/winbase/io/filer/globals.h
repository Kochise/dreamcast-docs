
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

#include<windows.h>

//
// Accellerator IDs
//
#define ACCEL_ID        1001

//
// Icon IDs
//
#define UI_FILERICON    2001

//
// DialogBox Control IDs
//
#define SB_OK           3001
#define SB_CANCEL       3002
#define SB_ACTION       3003
#define SB_TOFROM       3004
#define SB_SOURCE       3005
#define SB_DEST         3006
#define SB_STATIC       3007
#define SB_KEY          3008
#define SB_VALUE        3009
#define SB_SCROLL       3010

//
// String Table IDs
//
#define STR_EXE         4001
#define STR_COM         4002
#define STR_CMD         4003
#define STR_BAT         4004
#define IDS_ABOUTDLGERR 4005
#define IDS_DRVBUTTNERR 4006
#define IDS_CHNGDRVERR  4007
#define IDS_SELOBJERR   4008
#define IDS_BITBLTERR   4009
#define IDS_DRVNOTACTVE 4010
#define IDS_INSRTMEDIA  4011
#define IDS_SRCSTRNGERR 4012
#define IDS_CANTSPAWN   4013
#define IDS_MENUERR1    4014
#define IDS_MENUERR2    4015
#define IDS_MENUERR3    4016
#define IDS_MENUERR4    4017
#define	IDS_ENUMDRVERR	4018
#define	IDS_ENUMALOCERR 4019
#define	IDS_ENUMSTRERR	4020
#define	IDS_DRVALOCERR	4021
#define IDS_DCCDRVLST	4022
#define IDS_DCCCURDIR   4023
#define IDS_DCCTABSTP   4024
#define IDS_MMOPENERR   4025
#define IDS_COPYING     4026
#define IDS_COPYINGTO   4027
#define IDS_DELETING    4028
#define IDS_DELETINGFRM 4029
#define IDS_MOVING      4030
#define IDS_RENAMEERR   4031
#define IDS_MKDIRERR    4032
#define IDS_VERDLGERR   4033
#define IDS_MMEXPAND    4034
#define IDS_REFRESH1    4035
#define IDS_REFRESH2    4036
#define IDS_REFRESH3    4037
#define IDS_FILDIRERR   4038
#define IDS_FILDIRERR2  4039
#define IDS_FILDIRERR3  4040
#define IDS_FILDIRERR4  4041
#define IDS_DBLCLKERR   4042
#define IDS_SELCNGERR   4043
#define IDS_CONDIRERR   4044
#define IDS_LBNOTFYERR  4045
#define IDS_PARNTFYERR  4046
#define IDS_GETLBTXTERR 4047
#define IDS_OPENLBERR   4048 
#define IDS_CANTEDIT    4050
#define IDS_FILE        4051
#define IDS_DIR         4052
#define IDS_GETVERERR   4053
#define IDS_GETVERERR2  4054
#define IDS_GETVERERR3  4055
#define IDS_GETVERERR4  4056
#define IDS_GETVERERR5  4057
#define IDS_GETVERERR6  4058
#define IDS_GETVERERR7  4059
#define IDS_GETVERERR8  4060
#define IDS_ISDIRERR    4061
#define IDS_EXEFILEERR  4062
#define IDS_SELPROCERR  4063
#define IDS_SELDLGERR   4064
#define IDS_SELDLGERR2  4065
#define IDS_SELDLGERR3  4066
#define IDS_SELDLGERR4  4067
#define IDS_SELDLGERR5  4068
#define IDS_SELDLGERR6  4069
#define IDS_SELDLGERR7  4070
#define IDS_FILEIOERR   4071
#define IDS_FILEIOERR2  4072
#define IDS_FILEIOERR3  4073
#define IDS_HNDIOMSG    4074
#define IDS_HNDIOMSG2   4075
#define IDS_HNDIOMSG3   4076
#define IDS_HNDIOMSG4   4077
#define IDS_HNDIOMSG5   4078
#define IDS_RENMEMSG    4079
#define IDS_RENMEMSG2   4080
#define IDS_RENMEMSG3   4081
#define IDS_RENMEMSG4   4082
#define IDS_RENMEMSG5   4083
#define IDS_RENMEMSG6   4084
#define IDS_RENMEMSG7   4085
#define IDS_MKDIRMSG    4086
#define IDS_MKDIRMSG2   4087
#define IDS_MKDIRMSG3   4088
#define IDS_TXTMSG      4089

#define STR_DEF_EDITOR  4101

//
// Bitmap IDs
//
#define UB_BMP_MARKER   5001    // This should be the same as the first bitmap.
#define UB_FLOPPY1      5001    // THESE BITMAP IDs MUST BE CONTIGUOUS AND
#define UB_FLOPPY2      5002    //   IN THIS ORDER!  For 'ease of loading'.
#define UB_REMOTE1      5003
#define UB_REMOTE2      5004
#define UB_CD1          5005
#define UB_CD2          5006
#define UB_FIXED1       5007
#define UB_FIXED2       5008

//
// Command line window and Drv-CHILD child window IDs
//
#define COMMAND_ID      6001    // Command Line Window
#define TEXT_WINDOW_ID  6002    // Title Bar
#define LISTDIR_ID      6003    // Directory ListBox
#define LISTFILE_ID     6004    // File ListBox

//
// Internal Main window IDs
//
#define MM_FILLDIR      7001
#define MM_FILLFILE     7002

//
// Menu ID's, VKEYs, & other WM_COMMAND messages
//
#define MM_OPEN         8001
#define MM_COPY         8002
#define MM_DELETE       8003
#define MM_MOVE         8004
#define MM_RENAME       8005
#define MM_MKDIR        8006
#define MM_DELDIR       8007
#define MM_VERSION      8008
#define MM_EXIT         8009

#define MM_REFRESH      8101
#define MM_ACTIVEDRV    8102
#define MM_TAB          8103
#define MM_SWAP         8104
#define MM_ORIENT       8105
#define MM_EXPAND       8106
#define MM_KEEPCMD      8107

#define MM_ESCAPE       8112
#define MM_TOGGLE       8113

#define MM_ABOUT        8201

#define MM_DRIVE_NUM    8301       // ...Through 8226, one for each drive letter
                    //   .
                    //   .
                    //  8326


//
// constants
//
#define MAIN_WIDTH          605    // Default width and height of main window
#define MAIN_HEIGHT         400

#define DRIVE_BITMAP_WIDTH  23     // Width and height of drive toolbar bitmaps
#define DRIVE_BITMAP_HEIGHT 14     //   assoc. w/ bitmap IDs above.
#define DRIVE_LETTER_SPACING 2     // Space between drv bmp and drv letter label
#define DRIVE_BITMAP_SPACING 6     // Space on either side of drv bitmap-labels
#define NUM_BITMAPS          8     // # types of Drive Bitmaps to be loaded.

#define DIRECTORY_STRING_SIZE MAX_PATH  // Size of max allowable direcory path

#define LIST_BORDER         2      // Space between listbox and Drv child frame

#define DRIVE_MENU_NUM      2      // This is the 'Drives' submenu

#define LISTBOX_TAB_SIZE    8      // Size of the tabs in the Drv child LBs

#define OVER_UNDER          0      // Relative positions of Drv children
#define SIDE_BY_SIDE        1

#define BOLD_FONT           700    // GetDeviceCaps sez this value is for bold
                                   //   in the lfWeight LOGFONT member

#define NUM_EXTENSION_STRINGS   4  // Lists number of file ext. in stringtable
#define EXTENSION_LENGTH        5  // Tot. number of characters in extension,
                                   //  including '\0' char.

#define FILE_SYSTEM_STRING_SIZE         20      // Must be >= 8

#define NUM_POSSIBLE_REMOVABLE_DRIVES   26      // A-Z

#define MUTEX_TIMEOUT       50     // LB Mutex timeout in milliseconds


// The following are used in the .EXE Version retrieval code in DRVPROC.C
#define NUM_VERSION_INFO_KEYS    12     // See FilerGetVersion()
#define VERSION_DLG_LB_HEIGHT    10     // height in text lines of version dlg LBs

#define VERSION_INFO_KEY_ROOT    TEXT("\\StringFileInfo\\")
// end .EXE Version code constants


//
// Drive enumeration strucure
//
typedef struct _PerDriveInfo {
    TCHAR   DriveLetter;
    LPTSTR  DriveName;
    TCHAR   FileSystem[FILE_SYSTEM_STRING_SIZE];
    UINT    DriveType;
    struct _PerDriveInfo *next;
} DRVINFO, *LPDINFO;

//
// Instance data for each Drv child window
//
typedef struct _PerWndInfo {
    HWND    hwnd;                       // Handle to Drive child window
    HWND    hParent;                    // Handle to Filer main window
    HWND    hTextWnd;                   // Handle to Drive child Title Bar
    HWND    hFileLB;                    // Handle to Drv child File LB
    HWND    hDirLB;                     // Handle to Drv child Dir LB
    HANDLE  hDirThread;                 // Handle to ExpDir or FullExpand thread
    HANDLE  hDirMutex;                  // Protects Dir LB from mult. access
    HANDLE  hFileMutex;                 // Protects File LB from mult. access
    BOOL    fDirLeft;                   // Flag: the Dir LB is on left
    BOOL    fDirExpand;                 // Flag: the Dir LB is fully expanded
    BOOL    fSuicide;                   // Flag: kills ExpDir/FullExpand thread
    BOOL    fEscape;                    // Flag: User aborted Expand thread
    LPDINFO lpDriveInfo;                // pointer to current _PerDriveInfo
    TCHAR   CaptionBarText[DIRECTORY_STRING_SIZE]; // Drv Child Title text
} DRVCHILDINFO, *LPCINFO;

typedef struct _PerButtonInfo {
    HANDLE          hButton;
    BOOL            fButtonDown;
    LPDINFO         lpDrive;
    struct _PerButtonInfo  *next;
}   BINFO, *LPBINFO;

typedef struct _SelectDlgInfo {
    HWND    hwnd;
    DWORD   dwAction;
    LPTSTR  szAction;
    LPTSTR  szToFrom;
} SELECTINFO, *LPSINFO;

//  .EXE version information key structure: for FilerGetVersion() in DRVPROC.C
typedef struct _VersionKeyInfo {
    TCHAR const *szKey;
    TCHAR       *szValue;
} VKINFO, *LPVKINFO;
