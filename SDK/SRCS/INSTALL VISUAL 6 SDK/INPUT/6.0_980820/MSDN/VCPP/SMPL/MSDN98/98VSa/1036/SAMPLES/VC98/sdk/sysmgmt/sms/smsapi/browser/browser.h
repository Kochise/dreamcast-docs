//***************************************************************************
//
//  browser.h
//
//  Sample Windows app for SMS API.
//
//  This program illustrates the use of most of the SMS API set in order to
//  implement a generic Objectity browser.
//  Since this program is statically linked with smsapi.lib/dll it acts as
//  an SMS objectity browser only.
//
//  Using this program it is possible to view all containers and folders
//  that are implemented in the SMS API.
//
//  Jonathan Shuval     September 1994.
//
//***************************************************************************


// ==========================================================================
//
//      Function prototypes.
//
// ==========================================================================

extern "C" BOOL CALLBACK LoginDlg(  HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam);


extern "C" BOOL CALLBACK MainDlg(   HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam);


extern "C" BOOL CALLBACK ContainerViewDlg(
                                    HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam);

extern "C" BOOL CALLBACK ConfigFilterDlg(
                                    HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam);

extern "C" BOOL CALLBACK FolderViewDlg(
                                    HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam);

extern "C" BOOL CALLBACK ScalarViewDlg(
                                    HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam);

extern "C" BOOL CALLBACK ExpressionViewDlg(
                                    HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam);

extern "C" BOOL CALLBACK ViewSelFiltersDlg(
                                    HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam);

// ==========================================================================
//
//      Globals.
//
// ==========================================================================

char szMsg[100];            // Message buffer. Used in formatting MessageBox
                            // strings.

static HINSTANCE _hInstance;


// Get the available filter types and insert them into the menu
FILTER_INFO    *gpAvailFilterList = NULL;
DWORD ctFilters = 0;

// =============================================================
// Define a structure that we use in the main dlg for selected
// filters.
// This is the same as FILTER_INFO but we have an additional
// field for the filter handle. A handle of NULL means that the
// filter has not been opened.
typedef struct _MY_FILTER_INFO {
    FILTER_INFO *pF;
    HANDLE hFilter;
} MY_FILTER_INFO;

// =============================================================

// Connection handle, make global.
HANDLE ghConnect;

// Handle of current top-level folder/container.
HANDLE ghFolder;

// Used to connect to datasource. Global so that LoginDlg can fill it in.
DATASOURCE gdsParams;
char gszServer[33];
char gszDbName[33];
char gszUserName[33];
char gszPasswd[33];

FOLDER_INFO *gpCInfo;
MY_FILTER_INFO *gpMyFilter;



HANDLE ghFilter;        // filter handle. Set in the filter stuff.
                        // Use in main dlg.

HANDLE ghContainer;                 // Container handle.

// [02-May-96] Changed from struct into class.
// Used in folder view.
class CFrame {
public:
    CFrame() {
        // Clear everything.
        hFolder = NULL;
        memset(szFolderID, 0, 256);
        memset(szfType, 0, 256);
        fType = 0;
        ctScalars = 0;
        ctFolders = 0;
        ctFolderTypes = 0;
        phFolders = NULL;
        ctTokens = 0;
    };
    ~CFrame() {};

    HANDLE   hFolder;           // Make local copy of current folder.
    char     szFolderID[256];   // This folder's ID.
    char     szfType[256];      // Folder tag.
    DWORD    fType;             // Folder type.
    DWORD    ctScalars;         // Number of scalars.
    DWORD    ctFolders;         // Number of sub-folders.
    DWORD    ctFolderTypes;     // Number of sub-folder types.
    HANDLE   *phFolders;        // Array of handles to the folders.
    CObArray aszID;             // Array of sub-folder's IDs.
    // 02-May-96
    DWORD    ctTokens;          // Num of tokens in expression (if supported).
};
CFrame *CreateFolderFrame( HWND hDlg, HANDLE hFolder );

// Display the given folder frame. This is part of the Folder view dialogue.
void DisplayFolderFrame( HWND hDlg, CFrame *pFrame );



class CFrameStack
{
public:
    CFrameStack(HWND hDlg);

    ~CFrameStack();

    void push( CFrame *pFrame );

    CFrame *pop();

    void Dump( const char *psz );   // debug

    int sp;
    CObArray stack;
    HWND _hDlg;

};  /* CFrameStack */

/* EOF: browser.h */

