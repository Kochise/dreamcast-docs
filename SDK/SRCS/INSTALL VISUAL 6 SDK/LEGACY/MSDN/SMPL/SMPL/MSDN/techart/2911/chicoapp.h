// CHICOAPP.H
 
// Constants

#define MAX_LEN         32
#define NUM_COLUMNS     5
#define MAX_ITEMLEN     64
#define MAX_ADDRESS     64
#define MAX_CITY        16
#define MAX_PRICE       12
#define BITMAP_WIDTH    16
#define BITMAP_HEIGHT   16
#define MAX_HOUSES      256
#define MAX_CITIES      16

#define NUM_BUTTONS			8
#define NUM_BITMAPS			7
#define LG_BITMAP_WIDTH		32
#define LG_BITMAP_HEIGHT 	32
#define NUM_WINDOWS			4
#define STATUS_BAR_HEIGHT	20
#define TOOLBAR_HEIGHT		20
#define TEMP_LEN			10

#define ID_ADDHOUSE		0
#define ID_REMHOUSE		1
#define ID_ADDCITY		2

// Window IDs
#define ID_STATUS       1000
#define ID_TOOLBAR      1001
#define ID_LISTVIEW     1002
#define ID_TREEVIEW     1003

// menu commands

// File menu
#define IDM_NEW         100
#define IDM_OPEN        101
#define IDM_SAVE        102
#define IDM_SAVEAS      103
#define IDM_EXIT        104

// Options menu
#define IDM_ADDHOUSE    110
#define IDM_REMHOUSE    111
#define IDM_ADDCITY     112
#define IDM_HOUSEPROPS  113
#define IDM_DETAILS		114

// View menu
#define IDM_LARGEICON   120
#define IDM_SMALLICON   121
#define IDM_LISTVIEW    122
#define IDM_REPORTVIEW  123

// Help menu
#define IDM_ABOUT       130

// icons & bitmaps
#define CHICOAPP        400
#define HOUSE_ICON      401
#define FORSALE         402
#define IDB_TOOLBAR     403
#define FORSALE_BMP     404
#define CITY_BMP        405
#define SELCITY_BMP     406

// stringtable defines
#define IDS_FORSALE     1
#define IDS_REDMOND     2
#define IDS_BELLEVUE    3
#define IDS_SEATTLE     4
#define IDS_ADDRESS     5
#define IDS_CITY        6
#define IDS_PRICE       7
#define IDS_BEDS        8
#define IDS_BATHS       9
#define IDS_SELECTED    10
#define IDS_NUMHOUSES   11

// common dialog error string constants

#define IDS_DIALOGFAILURE     20
#define IDS_STRUCTSIZE        21
#define IDS_INITIALIZATION    22
#define IDS_NOTEMPLATE        23
#define IDS_NOHINSTANCE       24
#define IDS_LOADSTRFAILURE    25
#define IDS_FINDRESFAILURE    26
#define IDS_LOADRESFAILURE    27
#define IDS_LOCKRESFAILURE    28
#define IDS_MEMALLOCFAILURE   29
#define IDS_MEMLOCKFAILURE    30
#define IDS_NOHOOK            31
#define IDS_SETUPFAILURE      32
#define IDS_PARSEFAILURE      33
#define IDS_RETDEFFAILURE     34
#define IDS_LOADDRVFAILURE    35
#define IDS_GETDEVMODEFAIL    36
#define IDS_INITFAILURE       37
#define IDS_NODEVICES         38
#define IDS_NODEFAULTPRN      39
#define IDS_DNDMMISMATCH      40
#define IDS_CREATEICFAILURE   41
#define IDS_PRINTERNOTFOUND   42
#define IDS_NOFONTS           43
#define IDS_SUBCLASSFAILURE   44
#define IDS_INVALIDFILENAME   45
#define IDS_BUFFERTOOSMALL    46
#define IDS_FILTERSTRING      47
#define IDS_UNKNOWNERROR      48


// dialog box constants
// Add city dialog
#define IDD_ADDCITY     500
#define IDE_CITY        501

// Add house dialog
#define IDD_ADDHOUSE    700
#define IDE_ADDRESS     701
#define IDE_PRICE       702
#define IDE_BEDS        703
#define IDE_BATHS       704

// Remove house dialog
#define IDD_REMHOUSE    800
#define IDL_HOUSES      801

// House information property sheet
#define IDD_HOUSEINFO	900
#define IDS_HOUSEINFO	901

// Agent information property sheet
#define IDD_AGENTINFO	1000
#define IDS_AGENTINFO	1001
#define IDE_AGENTNAME	1002
#define IDS_AGENTNAME	1003
#define IDE_AGENTNUM	1004
#define IDS_AGENTNUM	1005

// structures
typedef struct tagLISTINFO
{
    HINSTANCE hInst;        // current instance
    HWND hWndMain;          // handle of the main window
    HWND hWndStatus;        // handle of the status window
    HWND hWndToolbar;       // handle of the toolbar window
    HWND hWndListView;      // handle of the list view window
    HWND hWndTreeView;      // handle of the tree view window
    int NumCities;          // the number of cities
    int NumHouses;          // the number of houses
    int iSelected;          // the index to the selected city 
	int iSelHouse;			// the index to the selected house
} LISTINFO;

typedef struct tagCITYINFO
{
    char szCity[MAX_CITY];  // city name
    int NumHouses;          // number of houses listed in this city
    HTREEITEM hItem;        // handle to tree view item
} CITYINFO;

typedef struct tagHOUSEINFO
{
    char szAddress[MAX_ADDRESS];	// address
    char szCity[MAX_CITY];			// city
    int iPrice;						// price
    int iBeds;						// number of bedrooms
    int iBaths;						// number of bathrooms
    int iImage;						// bitmap index for this house
    char szAgent[MAX_CITY];			// listing agent
    char szNumber[MAX_CITY];		// listing agent's phone number
} HOUSEINFO;


// Function prototypes

// procs
long APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);
BOOL APIENTRY AddHouse(HWND, UINT, UINT, LONG);
BOOL APIENTRY RemoveHouse(HWND, UINT, UINT, LONG);
BOOL APIENTRY AddCity(HWND, UINT, UINT, LONG);
BOOL APIENTRY HouseInfoDialog(HWND, UINT, UINT, LONG);
BOOL APIENTRY AgentInfoDialog(HWND, UINT, UINT, LONG);

// functions
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
VOID InitTreeAndList(VOID);
BOOL CreateAppWindows( HWND );
VOID AddOneCity(char *);
VOID AddOneHouse( char *, char *, int, int, int);
VOID RemoveOneHouse(int);
VOID ChangeSBText(HINSTANCE, HWND, int);
BOOL ResizeWindows(HWND );
VOID UpdateListView( HWND, int);
int CreatePropertySheet(HWND);
HWND CreateTheToolbar(HWND);

// list view functions
HWND LV_CreateListView(HWND, HINSTANCE, int, HOUSEINFO *);
LRESULT LV_NotifyHandler(HWND, UINT, WPARAM, LPARAM, HINSTANCE);
VOID LV_ChangeView(HWND, WORD);
BOOL LV_AddItem(HWND, int, HOUSEINFO *);
VOID LV_RemoveOneItem(HWND, int);
VOID LV_RemoveAllItems(HWND);

// tree view functions
HWND TV_CreateTreeView (HWND, HINSTANCE, int, CITYINFO *);
LRESULT TV_NotifyHandler(HWND, UINT, WPARAM, LPARAM, LISTINFO *);
HTREEITEM TV_AddOneItem(LPSTR, HWND, int);
VOID TV_RemoveAllItems(HWND);
VOID TV_InitTreeView(HINSTANCE, HWND);

// file i/i functions
BOOL OpenNewFile( HWND );
BOOL SaveToFile( HWND );
BOOL SaveAs( HWND );
BOOL ParseFile (VOID);
DWORD GetDataBufferAndSize (VOID);
void ProcessCDError(DWORD, HWND);


