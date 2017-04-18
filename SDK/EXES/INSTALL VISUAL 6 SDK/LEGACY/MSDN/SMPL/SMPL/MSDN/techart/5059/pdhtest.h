// PDH_TEST constants

// This file must be compiled with the PDH.H file from the Win32 SDK
#ifndef _PDH_H_
#include <pdh.h>
#endif // _PDH_H_

// Column definitions
#define COL_COUNTERNAME         0
#define COL_COUNTERVALUE        1
#define COL_COUNTERMIN          2
#define COL_COUNTERMAX          3
#define COL_COUNTERAVG          4
#define COL_FINALCOLUMN         4

// Buffer size definitions
#define INIT_RETURNPATH         1024
#define BUFFER_INCREMENT        1024
#define MAX_STRING              1024
#define FILE_BUFFER_SIZE        1024

// Number of raw values we will keep 
// track of for statistical purposes
#define MAX_RAW_VALUES          20

// Structure definition
typedef struct _tag_PDHCounterStruct {
    HCOUNTER hCounter;      // Handle to the counter - given to use by PDH Library
    int nNextIndex;         // element to get the next raw value
    int nOldestIndex;       // element containing the oldes raw value
    int nRawCount;          // number of elements containing raw values
    PDH_RAW_COUNTER a_RawValue[MAX_RAW_VALUES]; // Ring buffer to contain raw values
} PDHCOUNTERSTRUCT, *PPDHCOUNTERSTRUCT;


// Function prototypes
void ReportError( LPTSTR );

// Functions in PDHFns.c
BOOL PDH_Initialize();
BOOL PDH_Uninitialize();
BOOL PDH_BrowseCounters( HWND );
BOOL PDH_ToggleFlag( int );
BOOL PDH_CheckMenuItem( HMENU, int );
BOOL PDH_RemoveCounter( LPTSTR, PPDHCOUNTERSTRUCT );
BOOL PDH_CollectQueryData();
BOOL PDH_UpdateValue( PPDHCOUNTERSTRUCT, int );
BOOL PDH_GetCounterInfo( HINSTANCE, HWND, PPDHCOUNTERSTRUCT );
BOOL PDH_SetCounterScale( HINSTANCE, HWND, PPDHCOUNTERSTRUCT );
BOOL PDH_UpdateRawValue( PPDHCOUNTERSTRUCT, int );
BOOL PDH_DisplayStatistics( PPDHCOUNTERSTRUCT, int );
BOOL PDH_AddCounter( LPTSTR );

// Functions in Window.c
LRESULT CALLBACK MainWindowProc( HWND, UINT, WPARAM, LPARAM );
BOOL ItemDisplayPopup( HMENU );

// List view functions
HWND CreateListView( HWND);
BOOL AddListViewItem( LPTSTR, PPDHCOUNTERSTRUCT );
BOOL RemoveItem( int );
BOOL SetSubItemText( int, int, LPTSTR );
BOOL RemoveCounter( HWND );
BOOL RemoveAllCounters( HWND );
BOOL RemoveItem( int );
BOOL UpdateListView();
BOOL GetCounterInfo();
BOOL SetCounterScale();
BOOL UpdateRawValues();
BOOL DisplayStatistics();

// Status function
HWND InitStatusWindow( HWND );
BOOL UpdateStatus( LPTSTR );

// Timer related functions
BOOL AutoStart();
BOOL AutoStop();
BOOL AutoToggleStatistics( HMENU );

// File functions
void FileImport( HWND );
void FileExport( HWND );
BOOL File_GetName( HWND, LPTSTR, DWORD );
BOOL File_SaveName( HWND, LPTSTR, DWORD );
BOOL TraverseAndWriteItems( HANDLE );
BOOL WriteItem( HANDLE, LPTSTR );
BOOL TraverseFileAndAddCounters( HANDLE );


// Help Functions
void HelpInfo( HWND );
BOOL CALLBACK HelpInfoDialogProcedure( HWND, UINT, WPARAM, LPARAM );
void HelpInfoInit( HWND );
