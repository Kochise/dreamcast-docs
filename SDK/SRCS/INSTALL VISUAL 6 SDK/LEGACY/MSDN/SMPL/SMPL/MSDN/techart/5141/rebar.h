// menu commands
#define IDM_ABOUT			200
#define IDM_EXIT			201

// icons & bitmaps
#define REBAR_ICON		   300

// identifiers
#define ID_TOOLBAR         1000
#define ID_REBAR           13001
#define ID_COMBO		   1002

// other constants
#define NUM_BUTTONS			3
#define NUM_BITMAPS			10
#define BMP_CX				32
#define BMP_CY				32
#define MAX_LENGTH			64
#define NUM_LINKS			7
#define NUM_TBBUTTONS		8
#define NUM_TBBITMAPS		8
#define MIN_TBCX			200
#define MIN_COMBOCX			113
#define MIN_COMBOCY			42
#define MIN_CY				50


// Structure used for cool links
typedef struct tagCOOLLINKS 
{
   char szName [MAX_LENGTH];
   char szURL [MAX_PATH];
   int iBmp;
   int idx;
} COOLLINKS;

// Function prototypes

// procs
LONG APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY About(HWND, UINT, UINT, LONG);
BOOL APIENTRY BarInfo(HWND, UINT, UINT, LONG);
LRESULT CALLBACK ComboWndProc( HWND, UINT, WPARAM, LPARAM);

//functions
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
HWND CreateComboBox(HWND, HWND);
HWND CreateTheToolBar(HWND);
UINT CreateRebar(HWND);
