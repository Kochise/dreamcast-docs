/*************************************************************************
**
**    Automation Controller that uses vtable binding.
**    Controls the HELLO automation object.
**
**    hellctrl.cpp
**
**
**     Written by Microsoft Product Support Services, Windows Developer Support
**    (c) Copyright Microsoft Corp. 1994 - 1996 All Rights Reserved
**
*************************************************************************/
#define STRICT

#include <windows.h>
#include <windowsx.h>
#ifdef WIN16   
  #include <ole2.h>
  #include <compobj.h>    
  #include <dispatch.h> 
  #include <variant.h>
  #include <olenls.h>
  #include <commdlg.h>  
#endif  
#include <initguid.h>   
#include "tlb.h" 
#include "hellctrl.h"      

// Globals
HINSTANCE g_hinst;                          // Instance of application
HWND      g_hwnd;                           // Toplevel window handle

// String resource buffers
TCHAR g_szTitle[STR_LEN];                    // Main window caption
TCHAR g_szResult[STR_LEN];                   // "Result"
TCHAR g_szError[STR_LEN];                    // "Error"

/*
 * WinMain
 *
 * Purpose:
 *  Main entry point of application. Should register the app class
 *  if a previous instance has not done so and do any other one-time
 *  initializations.
 *
 */
int APIENTRY WinMain (HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR lpCmdLine, int nCmdShow)
{
   MSG msg;
       
#ifdef WIN16
   //  It is recommended that all 16 bit OLE applications set
   //  their message queue size to 96. This improves the capacity
   //  and performance of OLE's LRPC mechanism.
   int cMsg = 96;                  // Recommend msg queue size for OLE
   while (cMsg && !SetMessageQueue(cMsg))  // take largest size we can get.
       cMsg -= 8;
   if (!cMsg)
       return -1;  // ERROR: we got no message queue       
#endif
   
   // Load string constants
   LoadString(hinst, IDS_PROGNAME, g_szTitle, STR_LEN);
   LoadString(hinst, IDS_RESULT, g_szResult, STR_LEN);
   LoadString(hinst, IDS_ERROR, g_szError, STR_LEN);
   
   if (!hinstPrev)
      if (!InitApplication(hinst))
         return (FALSE);

   if(OleInitialize(NULL) != NOERROR)
      return FALSE;
      
   if (!InitInstance(hinst, nCmdShow))
      return (FALSE);

   while (GetMessage(&msg, NULL, NULL, NULL))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   
   OleUninitialize();
   
   return (msg.wParam); // Returns the value from PostQuitMessage
}

/*
 * InitApplication
 *
 * Purpose:
 *  Registers window class
 *
 * Parameters:
 *  hinst       hInstance of application
 *
 * Return Value:
 *  TRUE if initialization succeeded, FALSE otherwise.
 */
BOOL InitApplication (HINSTANCE hinst)
{
   WNDCLASS wc;

   wc.style = CS_DBLCLKS;
   wc.lpfnWndProc = MainWndProc;
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hInstance = hinst;
   wc.hIcon = LoadIcon(hinst, TEXT("ControlIcon"));
   wc.hCursor = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
   wc.lpszMenuName = TEXT("ControlMenu");
   wc.lpszClassName = TEXT("MainWndClass");
     
   return RegisterClass(&wc);
 }

/*
 * InitInstance
 *
 * Purpose:
 *  Creates and shows main window
 *
 * Parameters:
 *  hinst           hInstance of application
 *  nCmdShow        specifies how window is to be shown
 *
 * Return Value:
 *  TRUE if initialization succeeded, FALSE otherwise.
 */
BOOL InitInstance (HINSTANCE hinst, int nCmdShow)
{
  
   g_hinst = hinst;
   // Create Main Window
   g_hwnd = CreateWindow(TEXT("MainWndClass"), g_szTitle,
                       WS_OVERLAPPEDWINDOW,
                       CW_USEDEFAULT, CW_USEDEFAULT,
                       400, 200,
                       NULL, NULL, hinst, NULL);
   if (!g_hwnd)
      return FALSE;
   
   ShowWindow(g_hwnd, nCmdShow);                  
   UpdateWindow(g_hwnd);            
   return TRUE;
}

/*
 * MainWndProc
 *
 * Purpose:
 *  Window procedure for main window
 *
 */
LRESULT CALLBACK MainWndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   static IHello FAR* phello = NULL;    
   HRESULT hr;
   LPUNKNOWN punk;
   
   switch (msg)
   {
      case WM_COMMAND:
         switch (wParam)
         {
            case IDM_CREATEHELLO:   
                // Create Hello object and QueryInterface for IHello interface.
                hr = CoCreateInstance(CLSID_Hello, NULL, CLSCTX_SERVER, 
                     IID_IUnknown, (void FAR* FAR*)&punk);
                if (FAILED(hr))  
                {
                    MessageBox(NULL, TEXT("CoCreateInstance"), g_szError, MB_OK); 
                    return 0L;
                }                     
                hr = punk->QueryInterface(IID_IHello,  (void FAR* FAR*)&phello);   
                if (FAILED(hr))  
                {
                    MessageBox(NULL, TEXT("QueryInterface(IID_IHello)"), g_szError, MB_OK);
                    punk->Release(); 
                    return 0L;
                }
                punk->Release();
                return 0L;
                               
            case IDM_SETVISIBLE:  
                // Set Visible property to TRUE
                hr = phello->put_Visible(TRUE);
                if (FAILED(hr))
                    DisplayError(phello);
                return 0L;
                
            case IDM_SETINVISIBLE:    
                // Set visible property to FALSE
                hr = phello->put_Visible(FALSE);
                if (FAILED(hr))
                    DisplayError(phello);
                return 0L;
                
            case IDM_GETHELLOMESSAGE:    
            {   
                // Access Hello Message property and display it
                // in a MessageBox
                BSTR bstr = NULL;   // BSTR must be intialized before passing
                                    // to get_HelloMessage.
                hr = phello->get_HelloMessage(&bstr);
                if (FAILED(hr))
                    DisplayError(phello);
                else MessageBox(NULL, FROM_OLE_STRING(bstr), g_szResult, MB_OK); 
                
                // Caller is responsible for freeing parameters and return values.
                if (bstr)
                    SysFreeString(bstr);
                return 0L;   
            }
              
            case IDM_SAYHELLO:    
                // Invoke SayHello method
                hr = phello->SayHello();
                if (FAILED(hr))
                    DisplayError(phello);
                return 0L;
                
            case IDM_RELEASEHELLO:
                // Release the Hello object
                phello->Release();
                phello = NULL;
                return 0L;
         }
         break;
         
      case WM_INITMENUPOPUP:
      {
         HMENU hmenu = (HMENU)wParam;
         
         if (LOWORD(lParam) != 0)
            return 0L;
            
         // Enable or gray the appropriate menu items. phello indicates if an automation object
         //  is currently being controlled.   
         EnableMenuItem(hmenu, IDM_CREATEHELLO,  MF_BYCOMMAND | (phello?MF_GRAYED:MF_ENABLED));
         EnableMenuItem(hmenu, IDM_SETVISIBLE,   MF_BYCOMMAND | (phello?MF_ENABLED:MF_GRAYED)); 
         EnableMenuItem(hmenu, IDM_SETINVISIBLE,   MF_BYCOMMAND | (phello?MF_ENABLED:MF_GRAYED));
         EnableMenuItem(hmenu, IDM_GETHELLOMESSAGE,   MF_BYCOMMAND | (phello?MF_ENABLED:MF_GRAYED));
         EnableMenuItem(hmenu, IDM_SAYHELLO,  MF_BYCOMMAND | (phello?MF_ENABLED:MF_GRAYED));
         EnableMenuItem(hmenu, IDM_RELEASEHELLO, MF_BYCOMMAND | (phello?MF_ENABLED:MF_GRAYED));
         return 0L;
      }
      
      case WM_DESTROY:
         if (phello)
            phello->Release();                
         PostQuitMessage(0);
         break;

      default:                         
         return DefWindowProc(hwnd, msg, wParam, lParam);
   }
   
   return NULL;
}

/*
 * DisplayError
 *
 * Purpose:
 *  Obtains Rich Error Information about the automation error from
 *  the IErrorInfo interface.
 *
 */
void DisplayError(IHello FAR* phello)
{  
   IErrorInfo FAR* perrinfo;    
   BSTR bstrDesc;
   HRESULT hr;
   ISupportErrorInfo FAR* psupporterrinfo;  

   hr = phello->QueryInterface(IID_ISupportErrorInfo, (LPVOID FAR*)&psupporterrinfo);
   if (FAILED(hr)) 
   {
      MessageBox(NULL, TEXT("QueryInterface(IID_ISupportErrorInfo)"), g_szError, MB_OK);
      return;
   }
   
   hr = psupporterrinfo->InterfaceSupportsErrorInfo(IID_IHello);   
   if (hr != NOERROR)
   {   
       psupporterrinfo->Release();
       return;
   }
   psupporterrinfo->Release();
  
   // In this example only the error description is obtained and displayed. 
   // See the IErrorInfo interface for other information that is available. 
   hr = GetErrorInfo(0, &perrinfo); 
   if (FAILED(hr))
       return;   
   hr = perrinfo->GetDescription(&bstrDesc);
   if (FAILED(hr)) 
   {
       perrinfo->Release(); 
       return;
   }  
   
   MessageBox(NULL, FROM_OLE_STRING(bstrDesc), g_szError, MB_OK);   
   SysFreeString(bstrDesc);
}

/*
 * Quick & Dirty ANSI/Unicode conversion routines. These routines use a static
 * buffer of fixed size to hold the converted string. Consequently these
 * routines are limited to strings of size STRCONVERT_MAXLEN. Also the same
 * buffer is reused when the routine is called a second time. So make sure
 * that the converted string is used before the conversion routine is called
 * again
 */
#ifdef WIN32

#ifndef UNICODE
char* ConvertToAnsi(OLECHAR FAR* szW)
{
  static char achA[STRCONVERT_MAXLEN]; 
  
  WideCharToMultiByte(CP_ACP, 0, szW, -1, achA, STRCONVERT_MAXLEN, NULL, NULL);  
  return achA; 
} 

OLECHAR* ConvertToUnicode(char FAR* szA)
{
  static OLECHAR achW[STRCONVERT_MAXLEN]; 

  MultiByteToWideChar(CP_ACP, 0, szA, -1, achW, STRCONVERT_MAXLEN);  
  return achW; 
}
#endif

#endif   
   
