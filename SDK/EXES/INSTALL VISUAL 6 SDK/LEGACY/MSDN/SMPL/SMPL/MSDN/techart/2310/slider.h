                            
// menu commands

// Find menu
#define IDM_SETRANGE    100
#define IDM_SETFREQ     101
#define IDM_SETPAGE     102
#define IDM_SETLINE     103
#define IDM_EXIT        105

// Help menu
#define IDM_ABOUT       200

// icons
#define SLIDER_ICON     300

//dialog box defines

#define IDE_MIN         500
#define IDE_MAX         501
#define IDE_FREQ        502
#define IDE_PAGE        503
#define IDE_LINE        504
#define IDE_BAR         505

// setttings box
#define IDE_MIN2        506
#define IDE_MIN3        507
#define IDE_MAX2        508
#define IDE_MAX3        509
#define IDE_LINE2       510
#define IDE_LINE3       511
#define IDE_PAGE2       512
#define IDE_PAGE3       513

// Function prototypes

// procs
long APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);
BOOL APIENTRY Range(HWND, UINT, UINT, LONG);
BOOL APIENTRY Frequency(HWND, UINT, UINT, LONG);  
BOOL APIENTRY PageSize(HWND, UINT, UINT, LONG);  
BOOL APIENTRY LineSize(HWND, UINT, UINT, LONG);  

//functions
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);


