// LISTVIEW.H

// constants                            
#define ID_LISTVIEW     1000

#define NUM_ITEMS       9
#define NUM_COLUMNS     5
#define MAX_ITEMLEN     64
#define MAX_ADDRESS     64
#define MAX_CITY        16
#define MAX_PRICE       12
#define BITMAP_WIDTH    16
#define BITMAP_HEIGHT   16
#define LG_BITMAP_WIDTH	32
#define LG_BITMAP_HEIGHT 32

// menu commands

// Options menu

#define IDM_LARGEICON   100
#define IDM_SMALLICON   101
#define IDM_LISTVIEW    102
#define IDM_REPORTVIEW  103
#define IDM_EXIT        104

// Help menu
#define IDM_ABOUT       300

// icons
#define APP_ICON        400
#define REDMOND         401
#define BELLEVUE        402
#define SEATTLE         403

// stringtable defines
#define IDS_ADDRESS     1
#define IDS_CITY        2
#define IDS_PRICE       3
#define IDS_BEDS        4
#define IDS_BATHS       5

// Function prototypes

// procs
long APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);

//functions
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
HWND CreateListView(HWND);
LRESULT NotifyHandler(HWND, UINT, WPARAM, LPARAM);
int CALLBACK ListViewCompareProc(LPARAM, LPARAM, LPARAM);

// structures
typedef struct tagHOUSEINFO
{
    char szAddress[MAX_ADDRESS];
    char szCity[MAX_CITY];
    int iPrice;
    int iBeds;
    int iBaths;
} HOUSEINFO;



