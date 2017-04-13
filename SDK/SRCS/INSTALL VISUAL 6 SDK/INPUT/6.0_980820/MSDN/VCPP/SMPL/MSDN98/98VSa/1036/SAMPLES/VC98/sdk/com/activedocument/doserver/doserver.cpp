/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          DOServer.cpp
   
   Description:   General function implementation.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "DOServer.h"
#include "ClsFact.h"
#include <windowsx.h>
#include <CommDlg.h>

#include <initguid.h>

// {F0FD0C00-65BA-11d0-B66F-00A0C90348D6}
DEFINE_GUID(   CLSID_SimpleDocObject, 
               0xf0fd0c00, 
               0x65ba, 
               0x11d0, 
               0xb6, 
               0x6f, 
               0x0, 
               0xa0, 
               0xc9, 
               0x3, 
               0x48, 
               0xd6);

/**************************************************************************
   private function prototypes
**************************************************************************/

BOOL InitApp(BOOL, int);
void CenterWindow(HWND);

/**************************************************************************
   global variables
**************************************************************************/

HINSTANCE      g_hInst;
DWORD          g_DllRefCount;
DWORD          g_dwRegister;

/**************************************************************************

   WinMain

**************************************************************************/

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
BOOL  fEmbedding;
MSG   msg;

g_hInst = hInstance;

//check for the embedding switch
ParseCommandLine(lpCmdLine, &fEmbedding, NULL);
 
if(!fEmbedding)
   {
   DialogBox(g_hInst, MAKEINTRESOURCE(IDD_MAIN_DIALOG), NULL, (DLGPROC)MainDlgProc);
   return 0;
   }

if(!InitApp(fEmbedding, nCmdShow))
   return 0;

//DebugBreak();

//The message loop will only exit when the main object gets destroyed.
while(GetMessage(&msg, NULL, 0, 0))
   {
   TranslateMessage(&msg);
   DispatchMessage(&msg);
   }

OutputDebugString(TEXT("Exiting WinMain\n"));

if(g_dwRegister)
   CoRevokeClassObject(g_dwRegister);

CoUninitialize();

return msg.wParam;
}                                 

/**************************************************************************

   InitApp()
   
**************************************************************************/

BOOL InitApp(BOOL fEmbedding, int nCmdShow)
{
//initialize OLE
if(FAILED(CoInitialize(NULL)))
   return FALSE;

CClassFactory  *pClassFactory = new CClassFactory();

if(NULL == pClassFactory)
   {
   CoUninitialize();
   return FALSE;
   }

LPUNKNOWN   pUnknown;
HRESULT     hr;

hr = pClassFactory->QueryInterface(IID_IUnknown, (LPVOID*)&pUnknown);
if(FAILED(hr))
   {
   pClassFactory->Release();
   return FALSE;
   }

//register the class object
hr = CoRegisterClassObject(   CLSID_SimpleDocObject,
                              pUnknown,
                              CLSCTX_LOCAL_SERVER,
                              REGCLS_MULTIPLEUSE,
                              &g_dwRegister);

if(FAILED(hr))
   {
   pClassFactory->Release();
   return FALSE;
   }

return TRUE;
}

/**************************************************************************

   MainDlgProc()
   
**************************************************************************/

BOOL CALLBACK MainDlgProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
static COleDocument  *pOleDoc;

switch(uMessage)
   {
   case WM_INITDIALOG:
      CenterWindow(hWnd);
      
      pOleDoc = new COleDocument();

      if(pOleDoc)
         {
         EnableWindow(GetDlgItem(hWnd, IDC_REGISTER), TRUE);
         EnableWindow(GetDlgItem(hWnd, IDC_CREATE_FILE), TRUE);
         }

      break;
   
   case WM_DESTROY:
      if(pOleDoc)
         {
         delete pOleDoc;
         }

      break;
   
   case WM_COMMAND:
      switch(GET_WM_COMMAND_ID(wParam, lParam))
         {
         case IDOK:
         case IDCANCEL:
            EndDialog(hWnd, 0);
            break;
         
         case IDC_REGISTER:
            if(pOleDoc)
               {
               pOleDoc->RegisterServer();
               }
            break;

         case IDC_CREATE_FILE:
            if(pOleDoc)
               {
               pOleDoc->CreateFile(hWnd);
               }
            break;
         }
      return FALSE;
   }

return FALSE;
}


/**************************************************************************

   ColorHookProc()
   
**************************************************************************/

BOOL CALLBACK ColorHookProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
static COleDocument  *pOleDoc;
static UINT          uSaveOK;

switch(uMessage)
   {
   case WM_INITDIALOG:
      {
      UINT  uSelect;

      pOleDoc = (COleDocument*)((LPOPENFILENAME)(lParam))->lCustData;

      uSaveOK = RegisterWindowMessage(FILEOKSTRING);

      switch(pOleDoc->m_Color)
         {
         default:
         case RED_COLOR:
            uSelect = IDC_RED;
            break;

         case GREEN_COLOR:
            uSelect = IDC_GREEN;
            break;

         case BLUE_COLOR:
            uSelect = IDC_BLUE;
            break;
         }

      CheckRadioButton(hWnd, IDC_RED, IDC_BLUE, uSelect);
      }
      break;

   case WM_DESTROY:
      break;

   default:
      if(uMessage == uSaveOK)
         {
         //Save button pressed
         if(IsDlgButtonChecked(hWnd, IDC_GREEN))
            {
            pOleDoc->m_Color = GREEN_COLOR;
            }
         else if(IsDlgButtonChecked(hWnd, IDC_BLUE))
            {
            pOleDoc->m_Color = BLUE_COLOR;
            }
         else
            {
            pOleDoc->m_Color = RED_COLOR;
            }
			}
      
      break;
   }

return FALSE;
}

/*****************************************************************************

   CenterWindow

*****************************************************************************/

void CenterWindow(HWND hWnd)
{
RECT  rc;
int   x,
      y;

GetWindowRect(hWnd, &rc);

x = GetSystemMetrics(SM_CXSCREEN)/2 - ((rc.right - rc.left)/2);
y = GetSystemMetrics(SM_CYSCREEN)/2 - ((rc.bottom - rc.top)/2);

//don't move the window if it's already in the right position
if((x != rc.left) || (y != rc.top))
   MoveWindow(hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, TRUE);
}

