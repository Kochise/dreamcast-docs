/*************************************************************************
**
**  This is a part of the Microsoft Source Code Samples.
**
**  Copyright (C) 1992-1997 Microsoft Corporation. All rights reserved.
**
**  This source code is only intended as a supplement to Microsoft Development
**  Tools and/or WinHelp documentation.  See these sources for detailed
**  information regarding the Microsoft samples programs.
**
**  OLE Automation Lines Object.
**
**  main.cpp
**
**  Written by Microsoft Product Support Services, Windows Developer Support
**
*************************************************************************/
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
#include "lines.h"        

// Globals  
CApplication FAR* g_pApplication;
 
SCODE g_scodes[SCODE_COUNT] =                // Array of SCODEs for easy lookup
{    LINES_E_UNEXPECTED,
     LINES_E_OUTOFMEMORY,
     LINES_E_INVALIDINDEX,
     LINES_E_COLLECTIONFULL,
     LINES_E_LINEFROMOTHERINSTANCE,
     LINES_E_CANTADDENDPOINTS,
     LINES_E_POINTFROMOTHERINSTANCE,
     LINES_E_NOVISIBLEXCOORDINATE,
     LINES_E_NOVISIBLEYCOORDINATE,
     LINES_E_NOSTARTPOINT,
     LINES_E_NOENDPOINT
};

/*
 * WinMain
 *
 * Purpose:
 *  Main entry point of application. 
 *
 */
int APIENTRY WinMain (HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR pCmdLine, int nCmdShow)
{
    MSG msg;
    DWORD dwRegisterCF;     
    DWORD dwRegisterActiveObject;

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
   
    if (!hinstPrev)
       if (!InitApplication(hinst)) // Register window class        
          return FALSE;
    
    if (!InitInstance(hinst))   // Initialize OLE and create Lines application object
        return (FALSE);    
    
    // Determine if /Automation was specified in command line and register class
    // factory and active object. Show window if application was started stand alone.
    if (!ProcessCmdLine(pCmdLine, &dwRegisterCF, &dwRegisterActiveObject, nCmdShow))   
    {
       Uninitialize(dwRegisterCF, dwRegisterActiveObject);   
       return (FALSE);    
    }

    while (GetMessage(&msg, NULL, 0, 0))
    {
       TranslateMessage(&msg);
       DispatchMessage(&msg);
    }
   
    Uninitialize(dwRegisterCF, dwRegisterActiveObject);   
    return (msg.wParam); 
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
   
   wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc = MainWndProc;
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hInstance = hinst;
   wc.hIcon = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON));
   wc.hCursor = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
   wc.lpszMenuName = TEXT("AppMenu");
   wc.lpszClassName = TEXT("MainWndClass"); 
     
   return RegisterClass(&wc);        
}

/*
 * InitInstance
 *
 * Purpose:
 *  Intializes OLE and creates Lines Application object
 *
 * Parameters:
 *  hinst           hInstance of application
 *
 * Return Value:
 *  TRUE if initialization succeeded, FALSE otherwise.
 */
BOOL InitInstance (HINSTANCE hinst)
{  
    HRESULT hr;
    
    // Intialize OLE
    hr = OleInitialize(NULL);
    if (FAILED(hr))
       return FALSE; 
    
    // Create an instance of the Lines Application object. Object is
    // created with refcount 0.
    hr = CApplication::Create(hinst, &g_pApplication);       
    if (FAILED(hr))
        return FALSE;
    return TRUE;          
}

/*
 * ProcessCmdLine
 *
 * Purpose:
 *  Check if command line contains /Automation. If so, the class factory of the 
 *  application object is registered.  If not, the application was started stand-alone and
 *  so the window is shown. The application object is registered using RegisterActiveObject.
 *
 * Parameters:
 *  pCmdLine       Command line passed to application
 *  pdwRegisterCF   Returns id returned after class factory registration. Can be used to 
 *                  revoke class factory registration. 
 *  pdwRegisterActiveObject   Returns id returned after active object registration. Can be used to 
 *                  revoke active object registration.   
 *  nCmdShow        Specifies how window is to be shown if application was started stand alone.
 *
 * Return Value:
 *    TRUE if OLE initialization succeeded, FALSE otherwise.
 *
 */
BOOL ProcessCmdLine(LPSTR pCmdLine, LPDWORD pdwRegisterCF, LPDWORD pdwRegisterActiveObject, int nCmdShow)
{
   LPCLASSFACTORY pcf = NULL;
   HRESULT hr;
   
   *pdwRegisterCF = 0;     
   *pdwRegisterActiveObject = 0;
   
   // Expose class factory for application object if command line contains the 
   // Automation switch       
   if (_fstrstr(pCmdLine, "-Automation") != NULL
       || _fstrstr(pCmdLine, "/Automation") != NULL)
   {
       pcf = new CApplicationCF;
       if (!pcf)
           goto error;  
       pcf->AddRef();           
       hr = CoRegisterClassObject(CLSID_Lines, pcf,
                                     CLSCTX_LOCAL_SERVER, REGCLS_SINGLEUSE,
                                     pdwRegisterCF);
       if (hr != NOERROR)
           goto error;           
       pcf->Release();
   }  
   else g_pApplication->ShowWindow(nCmdShow);    // Show window if started stand-alone       
   
   // Register Lines application object in the Running Object Table (ROT). This 
   // allows controllers to connect to a running application object instead of creating
   // a new instance. Use weak registration so that the ROT releases it's reference when 
   // all external references are released. If strong registration is used, the ROT will not
   // release it's reference until RevokeActiveObject is called and so will keep
   // the object alive even after all external references have been released.
   RegisterActiveObject(g_pApplication, CLSID_Lines, ACTIVEOBJECT_WEAK, pdwRegisterActiveObject);
   return TRUE;           
           
error:
    if (pcf)
        pcf->Release();
    return FALSE;
}

/*
 * Uninitialize
 *
 *  Purpose:
 *   Revoke class factory and active object registration and uninitialize OLE.
 *
 * Parameters:
 *  dwRegisterCF ID returned after class factory registration. 
 *  dwRegisterActiveObject ID returned after active object registration.
 *
 */
void Uninitialize(DWORD dwRegisterCF, DWORD dwRegisterActiveObject)
{
    if (dwRegisterCF != 0)
        CoRevokeClassObject(dwRegisterCF);
    if (dwRegisterActiveObject != 0)
        RevokeActiveObject(dwRegisterActiveObject, NULL);   
    OleUninitialize();
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
   switch (msg)
   {           
      case WM_PAINT:          
          g_pApplication->Draw();            
          break;
      
      case WM_SIZE:
          g_pApplication->OnSize(LOWORD(lParam), HIWORD(lParam));        
          break; 
          
      case WM_COMMAND:
      {   
          switch(GET_WM_COMMAND_ID(wParam,lParam))
          {
              case IDM_DRAWLINE:
                  g_pApplication->CreateAndDrawLine();
                  break;
                  
              case IDM_CLEAR:
                  g_pApplication->ClearPane();              
                  break;
                  
              case IDM_EXIT: 
                  PostMessage(hwnd, WM_CLOSE, 0, 0L);
                  break; 
          }              
      }
      break;
          
      case WM_CLOSE: 
         // Hide the window to release the refcount added by CoLockObjectExternal
         // (See CLines::ShowWindow)
         g_pApplication->m_bUserClosing = TRUE;
         g_pApplication->ShowWindow(SW_HIDE); 
         DestroyWindow(hwnd);
         return 0L;
      
      case WM_DESTROY:            
         PostQuitMessage(0);
         break;
      
      default:                         
         return DefWindowProc(hwnd, msg, wParam, lParam);
   }
   
   return NULL;
} 

/*
 * DrawLineDialogFunc
 *
 * Purpose:
 *  Dialog function of DrawLine dialog. Prompts user and returns information to draw a line.
 *
 */ 
BOOL CALLBACK DrawLineDialogFunc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
   static LPLINEINFO plineinfo;      
   BOOL b;  
   CHOOSECOLOR cc;     
   COLORREF clrCustom[16];
   int n;
   
   switch (msg)
   {
      case WM_INITDIALOG:
         plineinfo = (LPLINEINFO)lParam;   
         // Initialize edit controls. Units are twips.
         SetDlgItemText(hwndDlg, IDC_STARTPOINT_X, TEXT("4500"));
         SetDlgItemText(hwndDlg, IDC_STARTPOINT_Y, TEXT("4500"));
         SetDlgItemText(hwndDlg, IDC_ENDPOINT_X, TEXT("8000"));
         SetDlgItemText(hwndDlg, IDC_ENDPOINT_Y, TEXT("8000"));
         SetDlgItemText(hwndDlg, IDC_THICKNESS, TEXT("100"));
         plineinfo->colorref = 0; 
         return TRUE;

      case WM_COMMAND:
         switch(GET_WM_COMMAND_ID(wParam,lParam))
         {
             case IDOK:
                 plineinfo->ptStart.x = GetDlgItemInt(hwndDlg, IDC_STARTPOINT_X, &b, TRUE); 
                 plineinfo->ptStart.y = GetDlgItemInt(hwndDlg, IDC_STARTPOINT_Y, &b, TRUE);
                 plineinfo->ptEnd.x = GetDlgItemInt(hwndDlg, IDC_ENDPOINT_X, &b, TRUE);
                 plineinfo->ptEnd.y = GetDlgItemInt(hwndDlg, IDC_ENDPOINT_Y, &b, TRUE);
                 plineinfo->nThickness = GetDlgItemInt(hwndDlg, IDC_THICKNESS, &b, TRUE);        
                 EndDialog(hwndDlg, IDOK);
                 return TRUE;
                 
             case IDCANCEL:
                 EndDialog(hwndDlg, IDCANCEL);
                 return TRUE;
                 
             case IDC_CHOOSECOLOR:    
                 memset(&cc, 0, sizeof(CHOOSECOLOR)); 
                 cc.lStructSize = sizeof(CHOOSECOLOR); 
                 cc.hwndOwner = hwndDlg;
                 cc.rgbResult = RGB(0, 0, 0);
                 cc.Flags = CC_RGBINIT;  
                 for (n=0; n<16; n++)
                    clrCustom[n] = RGB(255, 255, 255);
                 cc.lpCustColors = clrCustom;
                 if (ChooseColor(&cc))
                     plineinfo->colorref = cc.rgbResult;                                                               
         }
         break;
   }
   return FALSE;
}

/*
 * LoadTypeInfo
 *
 *  Purpose:
 *   Gets type information of an object's interface from type library.
 *
 * Parameters:
 *  ppunkStdDispatch    Returns type information.
 *  clsid               Interface id of object in type library. 
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT LoadTypeInfo(ITypeInfo FAR* FAR* pptinfo, REFCLSID clsid)
{                          
    HRESULT hr;
    LPTYPELIB ptlib = NULL;
    LPTYPEINFO ptinfo = NULL;

    *pptinfo = NULL;     
    
    // Load Type Library. 
    hr = LoadRegTypeLib(LIBID_Lines, 1, 0, 0x09, &ptlib);
    if (FAILED(hr)) 
    {   
        // if it wasn't registered, try to load it from the path
        // if this succeeds, it will have registered the type library for us
        // for the next time.  
        hr = LoadTypeLib(OLESTR("lines.tlb"), &ptlib); 
        if(FAILED(hr))        
            return hr;   
    }
    
    // Get type information for interface of the object.      
    hr = ptlib->GetTypeInfoOfGuid(clsid, &ptinfo);
    if (FAILED(hr))  
    { 
        ptlib->Release();
        return hr;
    }   

    ptlib->Release();
    *pptinfo = ptinfo;
    return NOERROR;
}

/*
 * RaiseException
 *
 * Parameters:
 *  nID                 Error number
 *  rguid               GUID of interface that is raising the exception.
 *
 * Return Value:
 *  HRESULT correspnding to the nID error number.
 *
 * Purpose:
 *  Fills the EXCEPINFO structure. 
 *  Sets ErrorInfo object for vtable-binding controllers.
 *  For id-binding and late binding controllers DispInvoke
 *  will return DISP_E_EXCEPTION and fill the EXCEPINFO parameter
 *  with the error information set by SetErrorInfo.
 *
 */  
HRESULT RaiseException(int nID, REFGUID rguid)
{   
    extern SCODE g_scodes[];
    TCHAR szError[STR_LEN];   
    ICreateErrorInfo *pcerrinfo;  
    IErrorInfo *perrinfo;
    HRESULT hr;
    BSTR bstrDescription = NULL;
    
    if (LoadString(g_pApplication->m_hinst, nID, szError, sizeof(szError)))
        bstrDescription = SysAllocString(TO_OLE_STRING(szError));    
    
    // Set ErrorInfo object so that vtable binding controller can get
    // rich error information. If the controller is using IDispatch
    // to access properties or methods, DispInvoke will fill the
    // EXCEPINFO structure using the values specified in the ErrorInfo
    // object and DispInvoke will return DISP_E_EXCEPTION. The property
    // or method must return a failure SCODE for DispInvoke to do this.
    hr = CreateErrorInfo(&pcerrinfo); 
    if (SUCCEEDED(hr))
    {
       pcerrinfo->SetGUID(rguid);
       pcerrinfo->SetSource(g_pApplication->m_bstrProgID);
       if (bstrDescription)
           pcerrinfo->SetDescription(bstrDescription);  
       hr = pcerrinfo->QueryInterface(IID_IErrorInfo, (LPVOID FAR*) &perrinfo);
       if (SUCCEEDED(hr))
       {
          SetErrorInfo(0, perrinfo);
          perrinfo->Release();
       }  
       pcerrinfo->Release();
    }  
    
    if (bstrDescription)
        SysFreeString(bstrDescription);
    return g_scodes[nID-1001];
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
    


   
    
