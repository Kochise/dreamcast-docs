#ifdef WIN32

#ifdef UNICODE
    #define FROM_OLE_STRING(str) str
    #define TO_OLE_STRING(str) str 
#else
    #define FROM_OLE_STRING(str) ConvertToAnsi(str)
    char* ConvertToAnsi(OLECHAR FAR* szW);  
    #define TO_OLE_STRING(str) ConvertToUnicode(str)
    OLECHAR* ConvertToUnicode(char FAR* szA);   
    // Maximum length of string that can be converted between Ansi & Unicode
    #define STRCONVERT_MAXLEN 500         
#endif

#else  // WIN16
  #define APIENTRY far pascal  
  #define TCHAR char
  #define TEXT(sz) sz 
  #define FROM_OLE_STRING(str) str  
  #define TO_OLE_STRING(str) str 
  #define LPTSTR LPSTR   
  #define LPCTSTR LPCSTR
  
  // Windows NT defines the following in windowsx.h
  #define GET_WM_COMMAND_ID(w,l) (w)
  #define GET_WM_COMMAND_CMD(w,l) HIWORD(l)
  #define GET_WM_COMMAND_HWND(w,l) LOWORD(l)
#endif

// Function prototypes
int APIENTRY WinMain (HINSTANCE, HINSTANCE, LPSTR, int);
#ifdef WIN16
BOOL __export CALLBACK MainDialogFunc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);
#else
BOOL CALLBACK MainDialogFunc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);
#endif
 
void ControlExcel();