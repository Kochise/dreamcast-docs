                            
// menu commands

// Find menu
#define IDM_PROPERTIES   100
#define IDM_EXIT         101

// Help menu
#define IDM_ABOUT       200

// icons
#define EXE_ICON     300

//dialog box defines
#define IDD_RANGE       400
#define IDD_PROPS       401


#define IDE_MIN         500
#define IDE_MAX         501
#define IDE_PAGE        502
#define IDE_LINE        503
#define IDE_BAR         504

// Function prototypes

// procs
long APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);
BOOL APIENTRY Range(HWND, UINT, UINT, LONG);
BOOL APIENTRY PageSize(HWND, UINT, UINT, LONG);  
BOOL APIENTRY LineSize(HWND, UINT, UINT, LONG);  

//functions
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
int CreatePropertySheet(HWND);


