// menu commands

// menu constants
#define IDM_ABOUT          200
#define IDM_EXIT           300

// icons & bitmaps
#define TOOLBAR_ICON       300
#define IDB_TOOLBAR        400

// toolbar constants
#define ID_TOOLBAR         1

// Function prototypes

// procs
LONG APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);
LRESULT CALLBACK ComboWndProc( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

//functions
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);

//string constants
char *hello = "Hi there!";

