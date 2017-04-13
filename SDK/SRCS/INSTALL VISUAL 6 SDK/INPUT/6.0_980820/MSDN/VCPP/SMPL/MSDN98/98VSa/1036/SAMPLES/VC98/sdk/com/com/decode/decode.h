
// Dialog IDs
#define IDD_HRESULTDIALOG  100

// Control IDs
#define IDC_EDIT        200
#define IDC_DECODE      201
#define IDC_ERRORNAME   202
#define IDC_ERRORDESC   203
#define IDC_WIN32ERROR  204
#define IDC_OLEERROR    205
#define IDC_STATIC      -1

// Function prototypes
int PASCAL WinMain (HINSTANCE, HINSTANCE, LPSTR, int);
void DecodeHResult(HRESULT, HWND, HWND, BOOL);
BOOL CALLBACK HResultDialogFunc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);
