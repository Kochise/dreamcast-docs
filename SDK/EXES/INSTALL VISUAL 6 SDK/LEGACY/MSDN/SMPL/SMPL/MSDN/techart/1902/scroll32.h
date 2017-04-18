
// menu commands

// Options menu
#define IDM_SETPOS         100
#define IDM_SETRANGE       101

#define IDM_ABOUT          102
#define IDM_EXIT           103

//dialog constants
#define IDC_VERTICAL       200
#define IDC_HORIZONTAL     201
#define IDE_VERTPOS        202
#define IDE_HORZPOS        203

//other constants
#define MAX_RANGE          0x7fffffff
#define SCROLL32_ICON      300

// Function prototypes

// procs
long APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY SetPos(HWND, UINT, UINT, LONG);
BOOL APIENTRY SetRange(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);

//functions
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
