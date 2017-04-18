
// menu commands
// Options menu
#define IDM_SPIN        100
#define IDM_EXIT        102

// Help menu
#define IDM_ABOUT       200

// icons
#define UPDOWN_ICON     300

// dialog constants
#define IDS_SPIN        400
#define IDE_BUDDY       401

// other constants                         
#define MAX_SPIN        10
#define MIN_SPIN        1
#define ID_UPDOWN       1000

// Function prototypes
// procs
long APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);
BOOL APIENTRY Spin(HWND, UINT, UINT, LONG);

//functions
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);

// strings
CHAR *szWelcome = "Welcome!";


