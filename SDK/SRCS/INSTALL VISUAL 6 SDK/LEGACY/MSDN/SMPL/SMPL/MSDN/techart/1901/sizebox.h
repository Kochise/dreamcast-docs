
// menu commands

// Find menu
#define IDM_EXIT            100

// Help menu
#define IDM_ABOUT           200

// icons
#define SIZEBOX_ICON        300

// Function prototypes

// procs
long APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);

//functions
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);

//string constants
char *instruct1 = "Click the mouse on the grey box in";
char *instruct2 = "the upper-left hand corner of the window.";
char *instruct3 = "Then drag the box to resize the window.";
