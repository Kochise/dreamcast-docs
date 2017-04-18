/*+==========================================================================
  File:      REMCLIEN.CPP

  Summary:   Based largely on the APTCLIEN.EXE application code, this
             module is meant to use COM to load and access some COM
             components in a separate Remote EXE COM Server (APTSERVE
             located on a separate machine). Thus to run REMCLIEN you must
             build or copy APTSERVE on the remote machine first. Like
             APTCLIEN, this application composes its own native composite
             COM object, COUtilityCruiseCar. In this client application,
             COUtilityCruiseCar is constructed by containment reuse of the
             existing COCruiseCar COM component (provided by the
             APTSERVE.EXE remote server). This application augments that
             existing component with a native implementation of the
             IUtility interface.  Thus, this application illustrates
             object composition through containment of an existing
             composite object that is itself constructed via containment.

             Also like APTCLIEN this client application separately
             instantiates the other car-related objects of APTSERVE on the
             remote machine and exercises them (ie, for Car, UtilityCar,
             CruiseCar, and UtilityCruiseCar).  To this end, REMCLIEN
             provides a set of menus for these Car related objects with
             choices for the respective methods of the Interfaces exposed
             by those COM Objects.

             For a comprehensive tutorial code tour of REMCLIEN's
             contents and offerings see the tutorial REMCLIEN.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the REMCLIEN source code.
             For more details on the APTSERVE.EXE that REMCLIEN works with
             see the APTSERVE.HTM file in the main tutorial directory.

  Classes:   CMainWindow

  Functions: InitApplication, WinMain

  Origin:    3-27-96: atrent - Editor-inheritance from APTCLIEN source.

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/

/*--------------------------------------------------------------------------
  We include WINDOWS.H for all Win32 applications.
  We include OLE2.H because we will be calling the COM/OLE Libraries.
  We include INITGUID.H only once (here) in the entire app because we
    will be defining GUIDs and want them as constants in the data segment.
  We include COMMDLG.H because we will be using the Open File and
    potentially other Common dialogs.
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include MICARS.H and CARGUIDS.H for the common car-related Interface
    class, GUID, and CLSID specifications.
  We include REMCLIEN.H because it has class and resource definitions
    specific to this REMCLIEN application.
  We include UTCRUCAR.H because it has COUtilityCar object class.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <initguid.h>
#include <commdlg.h>
#include <apputil.h>
#include <micars.h>
#include <carguids.h>
#include "remclien.h"
#include "utcrucar.h"


// Here is a pointer for use by the global Trace Message logging macros.
CMsgLog* g_pMsgLog = NULL;

// Here is a structure for storing the remote server info.
COSERVERINFO g_ServerInfo;
// Storage for the user entered remote machine name.
TCHAR g_szMachineName[MAX_PATH] = TEXT("");
OLECHAR g_wszMachineName[MAX_PATH];

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::CMainWindow

  Summary:  CMainWindow Constructor.

  Args:     .

  Modifies: .

  Returns:  .
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CMainWindow::CMainWindow()
{
  // Ensure these member variable strings are null strings.
  m_szFileName[0] = 0;
  m_szFileTitle[0] = 0;

  // Fill in the Open File Name Common Dialog's OPENFILENAME structure.
  m_ofnFile.lStructSize = sizeof(OPENFILENAME);
  m_ofnFile.hwndOwner = m_hWnd;
  m_ofnFile.hInstance = m_hInst;
  m_ofnFile.lpstrFilter = TEXT(OFN_DEFAULTFILES_STR);
  m_ofnFile.lpstrCustomFilter = NULL;
  m_ofnFile.nMaxCustFilter = 0;
  m_ofnFile.nFilterIndex = 1;
  m_ofnFile.lpstrFile = m_szFileName;
  m_ofnFile.nMaxFile = MAX_PATH;
  m_ofnFile.lpstrInitialDir = TEXT(".");
  m_ofnFile.lpstrFileTitle = m_szFileTitle;
  m_ofnFile.nMaxFileTitle = MAX_PATH;
  m_ofnFile.lpstrTitle = TEXT(OFN_DEFAULTTITLE_STR);
  m_ofnFile.lpstrDefExt = NULL;
  m_ofnFile.Flags = OFN_HIDEREADONLY;

  m_pCar = NULL;
  m_pUtilityCar = NULL;
  m_pCruiseCar = NULL;
  m_pUtilityCruiseCar = NULL;

  // Null the Message object pointers.
  m_pMsgBox = NULL;
  m_pMsgLog = NULL;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::~CMainWindow

  Summary:  CMainWindow Destructor.  Destruction of the main window
            indicates that the application should quit and thus the
            PostQuitMessage API is called.

  Args:     .

  Modifies: .

  Returns:  .
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CMainWindow::~CMainWindow()
{
  // CMainWindow is derived from CVirWindow which traps the WM_DESTROY
  // message and causes a delete of CMainWindow which in turn causes this
  // destructor to run. The WM_DESTROY results when the window is destoyed
  // after a close of the window. Prior to exiting the main message loop:

  // We release any and all of the pointers to instantiated COM objects.
  RELEASE_INTERFACE(m_pCar);
  RELEASE_INTERFACE(m_pUtilityCar);
  RELEASE_INTERFACE(m_pCruiseCar);
  RELEASE_INTERFACE(m_pUtilityCruiseCar);

  // We delete the CMsgBox and CMsgLog objects that were made in
  // Initinstance.
  DELETE_POINTER(m_pMsgBox);
  DELETE_POINTER(m_pMsgLog);

  // We then post a WM_QUIT message to cause an exit of the main thread's
  // message loop and an exit of this instance of the application.
  PostQuitMessage(0);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::GetInterface

  Summary:  Convenience method that wraps the QueryInterface call
            and accepts a main COM object IUnknown pointer as an argument.

  Args:     IUnknown* pObj,
              Pointer to the COM Object we are getting an interface on.
            REFIID riid,
              The GUID for the interface that we are seeking.
            PPVOID ppv);
              Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Modifies: .

  Returns:  BOOL.
              TRUE if succeeded.
              FALSE if failed.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CMainWindow::GetInterface(
       IUnknown* pObj,
       REFIID riid,
       PPVOID ppv)
{
  BOOL bResult = FALSE;
  HRESULT hr;

  *ppv=NULL;

  if (NULL != pObj)
  {
    LOG("C: --Obtaining Interface Pointer.");
    hr = pObj->QueryInterface(riid, ppv);

    if (FAILED(hr))
    {
      LOGERROR("C: ???? QueryInterface", hr);
    }
    else
    {
      LOGF1("C: Interface obtained. *ppv=0x%X", *ppv);
      bResult = TRUE;
    }
  }
  else
  {
    LOG("C: ???? Create an object first.");
  }

  return (bResult);
}


/*F+F++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: CreateRemote

  Summary:  Creates a Remote COM object.

  Args:     COSERVERINFO* pServerInfo
              Pointer to server info structure having remote machine name.
            REFCLSID rclsid,
              The class id of the object to create.
            PPVOID ppv
              Address of the caller's pointer variable that will
              receive the requested IUnknown interface pointer.

  Returns:  HRESULT
              Standard return code.
------------------------------------------------------------------------F-F*/
HRESULT CreateRemote(
          COSERVERINFO* pServerInfo,
          REFCLSID rclsid,
          PPVOID ppv)
{
  HRESULT hr = E_FAIL;
  IClassFactory* pICF = NULL;
  HCURSOR hCurPrev;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);

  // Ensure a remote machine name was specified by user.
  if (pServerInfo->pwszName[0])
  {
    // Change cursor to the hour glass.  Things could take awhile working
    // across the network.
    hCurPrev = SetCursor(hCurWait);

    // Get the COM Object Class Factory.
    hr = CoGetClassObject(
           rclsid,
           CLSCTX_REMOTE_SERVER,
           pServerInfo,
           IID_IClassFactory,
           (PPVOID)&pICF);
    LOGERROR("C:CoGetClassObject.",hr);
    if (SUCCEEDED(hr))
    {
      // Use Class Factory to create an instance of the COM object.
      hr = pICF->CreateInstance(
                   NULL,
                   IID_IUnknown,
                   ppv);
      pICF->Release();
      LOGERROR("C:CreateInstance.",hr);
    }

    // Set Cursor back to what it was.
    SetCursor(hCurPrev);
  }
  else
  {
    LOG("C: ???? Specify remote machine name first.");
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::DoMenu

  Summary:  Dispatch and handle the main menu commands.

  Args:     WPARAM wParam,
              First message parameter (word sized).
            LPARAM lParam)
              Second message parameter (long sized).

  Modifies: m_ofnFile, ...

  Returns:  LRESULT
              Standard Windows WindowProc return value.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CMainWindow::DoMenu(
          WPARAM wParam,
          LPARAM lParam)
{
  LRESULT lResult = FALSE;
  HRESULT hr;
  HMENU hMenu  = ::GetMenu(m_hWnd);
  HCURSOR hCurPrev;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  // Here are some interface pointers used to call methods on
  // our COUtilityCar, COCruiseCar, and COUtilityCruiseCar COM objects.
  ICar* pICar;
  IUtility* pIUtility;
  ICruise* pICruise;

  switch (LOWORD(wParam))
  {
    //----------------------------------------------------------------------
    // Handle File Menu Commands.
    //----------------------------------------------------------------------
    case IDM_FILE_MACHINE:
      // Ask the user for the name of the machine where the remote
      // server is.
      {
        CDlgRemoteInfo dlgRemoteInfo;

        dlgRemoteInfo.ShowDialog(
          m_hInst,
          MAKEINTRESOURCE(IDD_REMOTE_INFO),
          m_hWnd);
      }
      break;
    case IDM_FILE_EXIT:
      // The user commands us to exit this application so we tell the
      // Main window to close itself.
      ::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
      break;

    //----------------------------------------------------------------------
    // Handle Car Menu Commands.
    //----------------------------------------------------------------------
    case IDM_CAR_CREATE:
      LOG("C: === Car Menu: Create.");
      if (NULL == m_pCar)
      {
        // Call COM services to create a remote instance.
        hr = CreateRemote(
               &g_ServerInfo,
               CLSID_AptCar,
               (PPVOID)&m_pCar);
        if (SUCCEEDED(hr))
        {
          ::CheckMenuItem(
              hMenu,
              IDM_CAR_CREATE,
              MF_BYCOMMAND | MF_CHECKED);
          LOG("C: Car creation succeeded.");
        }
        else
          LOG("C: ???? Car creation failed.");
      }
      else
        LOG("C: ???? Car already exists.");
      break;
    case IDM_CAR_RELEASE:
      LOG("C: === Car Menu: Release.");
      if (NULL != m_pCar)
      {
        // Change cursor to the hour glass.
        hCurPrev = SetCursor(hCurWait);
        RELEASE_INTERFACE(m_pCar);
        // We ask COM to unload any unused COM Servers.
        CoFreeUnusedLibraries();
        // Set Cursor back to what it was.
        SetCursor(hCurPrev);
        ::CheckMenuItem(
            hMenu,
            IDM_CAR_CREATE,
            MF_BYCOMMAND | MF_UNCHECKED);
      }
      else
        LOG("C: ???? No Car to Release.");
      break;
    case IDM_CAR_SHIFT:
      LOG("C: === Car Menu: ICar::Shift");
      if (GetInterface(m_pCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Shift");
        pICar->Shift(1);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;
    case IDM_CAR_CLUTCH:
      LOG("C: === Car Menu: ICar::Clutch");
      if (GetInterface(m_pCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Clutch");
        pICar->Clutch(100);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;
    case IDM_CAR_SPEED:
      LOG("C: === Car Menu: ICar::Speed");
      if (GetInterface(m_pCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Speed");
        pICar->Speed(20);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;
    case IDM_CAR_STEER:
      LOG("C: === Car Menu: ICar::Steer");
      if (GetInterface(m_pCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Steer");
        pICar->Steer(0);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;

    //----------------------------------------------------------------------
    // Handle UtilityCar Menu Commands.
    //----------------------------------------------------------------------
    case IDM_UCAR_CREATE:
      LOG("C: === UtilityCar Menu: Create.");
      if (NULL == m_pUtilityCar)
      {
        // Call COM services to create a remote instance.
        hr = CreateRemote(
               &g_ServerInfo,
               CLSID_AptUtilityCar,
               (PPVOID)&m_pUtilityCar);
        if (SUCCEEDED(hr))
        {
          ::CheckMenuItem(
              hMenu,
              IDM_UCAR_CREATE,
              MF_BYCOMMAND | MF_CHECKED);
          LOG("C: UtilityCar creation succeeded.");
        }
        else
          LOG("C: ???? UtilityCar creation failed.");
      }
      else
        LOG("C: ???? UtilityCar already exists.");
      break;
    case IDM_UCAR_RELEASE:
      LOG("C: === UtilityCar Menu: Release.");
      if (NULL != m_pUtilityCar)
      {
        // Change cursor to the hour glass.
        hCurPrev = SetCursor(hCurWait);
        RELEASE_INTERFACE(m_pUtilityCar);
        // We ask COM to unload any unused COM Servers.
        CoFreeUnusedLibraries();
        // Set Cursor back to what it was.
        SetCursor(hCurPrev);
        ::CheckMenuItem(
            hMenu,
            IDM_UCAR_CREATE,
            MF_BYCOMMAND | MF_UNCHECKED);
      }
      else
        LOG("C: ???? No UtilityCar to Release.");
      break;
    case IDM_UCAR_SHIFT:
      LOG("C: === UtilityCar Menu: ICar::Shift");
      if (GetInterface(m_pUtilityCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Shift");
        pICar->Shift(2);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;
    case IDM_UCAR_CLUTCH:
      LOG("C: === UtilityCar Menu: ICar::Clutch");
      if (GetInterface(m_pUtilityCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Clutch");
        pICar->Clutch(100);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;
    case IDM_UCAR_SPEED:
      LOG("C: === UtilityCar Menu: ICar::Speed");
      if (GetInterface(m_pUtilityCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Speed");
        pICar->Speed(30);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;
    case IDM_UCAR_STEER:
      LOG("C: === UtilityCar Menu: ICar::Steer");
      if (GetInterface(m_pUtilityCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Steer");
        pICar->Steer(10);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;
    case IDM_UCAR_OFFROAD:
      LOG("C: === UtilityCar Menu: IUtility::Offroad");
      if (GetInterface(m_pUtilityCar, IID_IUtility, (PPVOID)&pIUtility))
      {
        LOG("C: --Calling pIUtility->Offroad");
        pIUtility->Offroad(1);
        LOG("C: --Releasing pIUtility");
        pIUtility->Release();
      }
      break;
    case IDM_UCAR_WINCH:
      LOG("C: === UtilityCar Menu: IUtility::Winch");
      if (GetInterface(m_pUtilityCar, IID_IUtility, (PPVOID)&pIUtility))
      {
        LOG("C: --Calling pIUtility->Winch");
        pIUtility->Winch(0);
        LOG("C: --Releasing pIUtility");
        pIUtility->Release();
      }
      break;

    //----------------------------------------------------------------------
    // Handle CruiseCar Menu Commands.
    //----------------------------------------------------------------------
    case IDM_CCAR_CREATE:
      LOG("C: === CruiseCar Menu: Create.");
      if (NULL == m_pCruiseCar)
      {
        // Call COM services to create a remote instance.
        hr = CreateRemote(
               &g_ServerInfo,
               CLSID_AptCruiseCar,
               (PPVOID)&m_pCruiseCar);
        if (SUCCEEDED(hr))
        {
          ::CheckMenuItem(
              hMenu,
              IDM_CCAR_CREATE,
              MF_BYCOMMAND | MF_CHECKED);
          LOG("C: CruiseCar creation succeeded.");
        }
        else
          LOG("C: ???? CruiseCar creation failed.");
      }
      else
        LOG("C: ???? CruiseCar already exists.");
      break;
    case IDM_CCAR_RELEASE:
      LOG("C: === CruiseCar Menu: Release.");
      if (NULL != m_pCruiseCar)
      {
        // Change cursor to the hour glass.
        hCurPrev = SetCursor(hCurWait);
        RELEASE_INTERFACE(m_pCruiseCar);
        // We ask COM to unload any unused COM Servers.
        CoFreeUnusedLibraries();
        // Set Cursor back to what it was.
        SetCursor(hCurPrev);
        ::CheckMenuItem(
            hMenu,
            IDM_CCAR_CREATE,
            MF_BYCOMMAND | MF_UNCHECKED);
      }
      else
        LOG("C: ???? No CruiseCar to Release.");
      break;
    case IDM_CCAR_SHIFT:
      LOG("C: === CruiseCar Menu: ICar::Shift");
      if (GetInterface(m_pCruiseCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Shift");
        pICar->Shift(4);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;
    case IDM_CCAR_CLUTCH:
      LOG("C: === CruiseCar Menu: ICar::Clutch");
      if (GetInterface(m_pCruiseCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Clutch");
        pICar->Clutch(100);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;
    case IDM_CCAR_SPEED:
      LOG("C: === CruiseCar Menu: ICar::Speed");
      if (GetInterface(m_pCruiseCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Speed");
        pICar->Speed(60);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;
    case IDM_CCAR_STEER:
      LOG("C: === CruiseCar Menu: ICar::Steer");
      if (GetInterface(m_pCruiseCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Steer");
        pICar->Steer(0);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;
    case IDM_CCAR_ENGAGE:
      LOG("C: === CruiseCar Menu: ICruise::Engage");
      if (GetInterface(m_pCruiseCar, IID_ICruise, (PPVOID)&pICruise))
      {
        LOG("C: --Calling pICruise->Engage");
        pICruise->Engage(TRUE);
        LOG("C: --Releasing pICruise");
        pICruise->Release();
      }
      break;
    case IDM_CCAR_ADJUST:
      LOG("C: === CruiseCar Menu: ICruise::Adjust");
      if (GetInterface(m_pCruiseCar, IID_ICruise, (PPVOID)&pICruise))
      {
        LOG("C: --Calling pICruise->Adjust");
        pICruise->Adjust(FALSE);
        LOG("C: --Releasing pICruise");
        pICruise->Release();
      }
      break;

    //----------------------------------------------------------------------
    // Handle UtilityCruiseCar Menu Commands.
    //----------------------------------------------------------------------
    case IDM_UCRU_CREATE:
      LOG("C: === UtilityCruiseCar Menu: Create.");
      if (NULL == m_pUtilityCruiseCar)
      {
        if (g_ServerInfo.pwszName[0])
        {
          // Call a create function to create an instance.
          hr = CreateUtilityCruiseCar(
                 NULL,
                 IID_IUnknown,
                 (PPVOID)&m_pUtilityCruiseCar);
          if (SUCCEEDED(hr))
          {
            ::CheckMenuItem(
                hMenu,
                IDM_UCRU_CREATE,
                MF_BYCOMMAND | MF_CHECKED);
          }
          else
            LOG("C: ???? UtilityCruiseCar creation failed.");
        }
        else
          LOG("C: ???? Specify remote machine name first.");
      }
      else
        LOG("C: ???? UtilityCruiseCar already exists.");
      break;
    case IDM_UCRU_RELEASE:
      LOG("C: === UtilityCruiseCar Menu: Release.");
      if (NULL != m_pUtilityCruiseCar)
      {
        // Change cursor to the hour glass.
        hCurPrev = SetCursor(hCurWait);
        RELEASE_INTERFACE(m_pUtilityCruiseCar);
        // We ask COM to unload any unused COM Servers.
        CoFreeUnusedLibraries();
        // Set Cursor back to what it was.
        SetCursor(hCurPrev);
        ::CheckMenuItem(
            hMenu,
            IDM_UCRU_CREATE,
            MF_BYCOMMAND | MF_UNCHECKED);
      }
      else
        LOG("C: ???? No UtilityCruiseCar to Release.");
      break;
    case IDM_UCRU_SHIFT:
      LOG("C: === UtilityCruiseCar Menu: ICar::Shift");
      if (GetInterface(m_pUtilityCruiseCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Shift");
        pICar->Shift(1);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;
    case IDM_UCRU_CLUTCH:
      LOG("C: === UtilityCruiseCar Menu: ICar::Clutch");
      if (GetInterface(m_pUtilityCruiseCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Clutch");
        pICar->Clutch(80);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;
    case IDM_UCRU_SPEED:
      LOG("C: === UtilityCruiseCar Menu: ICar::Speed");
      if (GetInterface(m_pUtilityCruiseCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Speed");
        pICar->Speed(10);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;
    case IDM_UCRU_STEER:
      LOG("C: === UtilityCruiseCar Menu: ICar::Steer");
      if (GetInterface(m_pUtilityCruiseCar, IID_ICar, (PPVOID)&pICar))
      {
        LOG("C: --Calling pICar->Steer");
        pICar->Steer(10);
        LOG("C: --Releasing pICar");
        pICar->Release();
      }
      break;
    case IDM_UCRU_ENGAGE:
      LOG("C: === UtilityCruiseCar Menu: ICruise::Engage");
      if (GetInterface(m_pUtilityCruiseCar, IID_ICruise, (PPVOID)&pICruise))
      {
        LOG("C: --Calling pICruise->Engage");
        pICruise->Engage(FALSE);
        LOG("C: --Releasing pICruise");
        pICruise->Release();
      }
      break;
    case IDM_UCRU_ADJUST:
      LOG("C: === UtilityCruiseCar Menu: ICruise::Adjust");
      if (GetInterface(m_pUtilityCruiseCar, IID_ICruise, (PPVOID)&pICruise))
      {
        LOG("C: --Calling pICruise->Adjust");
        pICruise->Adjust(FALSE);
        LOG("C: --Releasing pICruise");
        pICruise->Release();
      }
      break;
    case IDM_UCRU_OFFROAD:
      LOG("C: === UtilityCruiseCar Menu: IUtility::Offroad");
      if (GetInterface(m_pUtilityCruiseCar, IID_IUtility, (PPVOID)&pIUtility))
      {
        LOG("C: --Calling pIUtility->Offroad");
        pIUtility->Offroad(3);
        LOG("C: --Releasing pIUtility");
        pIUtility->Release();
      }
      break;
    case IDM_UCRU_WINCH:
      LOG("C: === UtilityCruiseCar Menu: IUtility::Winch");
      if (GetInterface(m_pUtilityCruiseCar, IID_IUtility, (PPVOID)&pIUtility))
      {
        LOG("C: --Calling pIUtility->Winch");
        pIUtility->Winch(0);
        LOG("C: --Releasing pIUtility");
        pIUtility->Release();
      }
      break;

    //----------------------------------------------------------------------
    // Handle Log Menu Commands.
    //----------------------------------------------------------------------
    case IDM_LOG_LOGCLEAR:
      // Clear the message log.
      m_pMsgLog->Clear();
      // Use macro to log messages.
      LOGID(IDS_START_MESSAGE_LOG);
      break;
    case IDM_LOG_LOGGING:
      // Toggle the state of the Message Logging.
      // Toggle the checkmark indicator on the menu selection as well.
      {
        HMENU hMenu  = ::GetMenu(m_hWnd);
        BOOL bLogging = ::GetMenuState(
                            hMenu,
                            IDM_LOG_LOGGING,
                            MF_BYCOMMAND) & MF_CHECKED;
        if (bLogging)
        {
          m_pMsgLog->Logging(FALSE);
          ::CheckMenuItem(
              hMenu,
              IDM_LOG_LOGGING,
              MF_BYCOMMAND | MF_UNCHECKED);
        }
        else
        {
          m_pMsgLog->Logging(TRUE);
          ::CheckMenuItem(
              hMenu,
              IDM_LOG_LOGGING,
              MF_BYCOMMAND | MF_CHECKED);
        }
      }
      break;
    case IDM_LOG_COPYCLIP:
      // Copy trace message log to clipboard.
      m_pMsgLog->Copy();
      break;

    //----------------------------------------------------------------------
    // Handle Help Menu Commands.
    //----------------------------------------------------------------------
    case IDM_HELP_CONTENTS:
      // We have some stubbed support here for bringing up the online
      // Help for this application.
      ReadHelp(m_hWnd, m_szHelpFile);
      break;
    case IDM_HELP_TUTORIAL:
      // Call the APPUTIL utility function, ReadTutorial, to Browse the HTML
      // tutorial narrative file associated with this tutorial code sample.
      ReadTutorial(m_hInst, m_hWnd, TEXT(HTML_FILE_EXT));
      break;
    case IDM_HELP_TUTSERVER:
      // Call the APPUTIL utility function, ReadTutorial, to Browse the HTML
      // tutorial narrative file associated with the APTSERVE COM server.
      ReadTutorial(m_hInst, m_hWnd, TEXT(SERVER_TUTFILE_STR));
      break;
    case IDM_HELP_TUTMARSHAL:
      // Call the APPUTIL utility function, ReadTutorial, to Browse the HTML
      // tutorial narrative file associated with the COM marshaling server.
      ReadTutorial(m_hInst, m_hWnd, TEXT(MARSHAL_TUTFILE_STR));
      break;
    case IDM_HELP_READSOURCE:
      // Call the APPUTIL utility function ReadSource to allow the
      // user to open and read any of the source files of REMCLIEN.
      ReadSource(m_hWnd, &m_ofnFile);
      break;
    case IDM_HELP_ABOUT:
      {
        CAboutBox dlgAboutBox;

        LOG("C: === Help Menu: About REMCLIEN.");
        // Show the standard About Box dialog for this EXE by telling the
        // dialog C++ object to show itself by invoking its ShowDialog
        // method.  Pass it this EXE instance and the parent window handle.
        // Use a dialog resource ID for the dialog template stored in
        // this EXE module's resources.
        dlgAboutBox.ShowDialog(
          m_hInst,
          MAKEINTRESOURCE(IDM_HELP_ABOUT),
          m_hWnd);
      }
      break;

    default:
      // Defer all messages NOT handled here to the Default Window Proc.
      lResult = ::DefWindowProc(m_hWnd, WM_COMMAND, wParam, lParam);
      break;
  }

  return(lResult);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::InitInstance

  Summary:  Instantiates an instance of the main application window.
            This method must be called only once, immediately after
            window class construction.  We take care to delete 'this'
            CMainWindow if we must return the error condition FALSE.

  Args:     HINSTANCE hInstance,
              Handle of the application instance.
            int nCmdShow)
              Command to pass to ShowWindow.

  Modifies: m_szHelpFile, m_pMsgBox, m_pMsgLog.

  Returns:  BOOL.
              TRUE if succeeded.
              FALSE if failed.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CMainWindow::InitInstance(
       HINSTANCE hInstance,
       int nCmdShow)
{
  BOOL bOk = FALSE;
  HWND hWnd;

  // Create the Message Box and Message Log objects.
  m_pMsgBox = new CMsgBox;
  m_pMsgLog = new CMsgLog;

  if (NULL != m_pMsgBox && NULL != m_pMsgLog)
  {
    // Note, the Create method sets the m_hWnd member so we don't
    // need to set it explicitly here first.

    // Here is the create of this window.  Size the window reasonably.
    // Create sets both m_hInst and m_hWnd.
    hWnd = Create(
             TEXT(MAIN_WINDOW_CLASS_NAME_STR),
             TEXT(MAIN_WINDOW_TITLE_STR),
             WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
               | WS_MAXIMIZEBOX | WS_THICKFRAME,
             CW_USEDEFAULT,
             CW_USEDEFAULT,
             ::GetSystemMetrics(SM_CXSCREEN)*3/5,
             ::GetSystemMetrics(SM_CYSCREEN)*3/5,
             NULL,
             NULL,
             hInstance);
    if (hWnd)
    {
      // Ensure the new window is shown on screen and its content is painted.
      ::ShowWindow(m_hWnd, nCmdShow);
      ::UpdateWindow(m_hWnd);

      // Build a path to where the help file should be (it should be in
      // the same directory as the .EXE but with the .HTM extension.
      MakeFamilyPath(hInstance, m_szHelpFile, TEXT(HELP_FILE_EXT));

      // Init the Message Box object.
      if (m_pMsgBox->Init(m_hInst, m_hWnd))
      {
        // Create the Trace Message Log ListBox as a child window that
        // fits the client area of the Main Window (the TRUE 3rd argument
        // specifies such an inside child). If you want the Trace Message
        // Log in a separate (but owned) window, then pass a FALSE instead
        // for the 3rd argument.
        if (m_pMsgLog->Create(m_hInst, m_hWnd, TRUE))
        {
          // Assign the global MsgLog pointer.
          g_pMsgLog = m_pMsgLog;
          // Use macro to log an initial start messsage.
          LOGID(IDS_START_MESSAGE_LOG);
          bOk = TRUE;
        }
      }
    }
  }

  if (!bOk)
  {
    DELETE_POINTER(m_pMsgBox);
    DELETE_POINTER(m_pMsgLog);
  }

  return (bOk);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CDlgRemoteInfo::DialogProc

  Summary:  Dialog proc for the Remote Info dialog box.  This DialogProc
            method definition overrides the same-named pure virtual
            function in abstract base class CVirDialog thus giving unique
            message dispatching behavior to this derivation of CVirDialog.
            The remaining behavior of CDlgRemoteInfo is inherited from
            CVirDialog and is common to all CVirDialogs.

  Args:     HWND hWndDlg,
              Handle to the dialog.
            UINT uMsg,
              Windows message to dialog.
            WPARAM wParam,
              First message parameter (word sized).
            LPARAM lParam)
              Second message parameter (long sized).

  Modifies: .

  Returns:  BOOL.  TRUE if message was handled; FALSE otherwise.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CDlgRemoteInfo::DialogProc(
       HWND hWndDlg,
       UINT uMsg,
       WPARAM wParam,
       LPARAM lParam)
{
  BOOL bResult = TRUE;
  HWND hCtrl = GetDlgItem(hWndDlg, IDC_EDIT_MACHINE);

  switch (uMsg)
  {
    case WM_INITDIALOG:
      SetDlgItemText(hWndDlg, IDC_EDIT_MACHINE, g_szMachineName);
      SetFocus(hCtrl);
      bResult = FALSE;
      break;

    case WM_COMMAND:
      {
        WORD wCmd = LOWORD(wParam);

        if (wCmd == IDOK)
        {
          // Obtain the machine name from the edit control.
          GetDlgItemText(hWndDlg, IDC_EDIT_MACHINE, g_szMachineName, MAX_PATH);
#if !defined(UNICODE)
          // Convert to WideChar Unicode if we are NOT compiled for Unicode.
          AnsiToUc(g_szMachineName, g_wszMachineName, 0);
#endif
          ::EndDialog(hWndDlg, TRUE);
        }
        else if (wCmd == IDCANCEL)
          ::EndDialog(hWndDlg, TRUE);
      }
      break;

    default:
      bResult = FALSE;
      break;
  }

  return(bResult);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::WindowProc

  Summary:  Main window procedure for this window object.  See CVirWindow
            in the APPUTIL library (APPUTIL.CPP) for details on how this
            method gets called by the global WindowProc.

  Args:     UINT uMsg,
              Windows message that is "sent" to this window.
            WPARAM wParam,
              First message parameter (word sized).
            LPARAM lParam)
              Second message parameter (long sized).

  Modifies: ...

  Returns:  LRESULT
              Standard Windows WindowProc return value.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CMainWindow::WindowProc(
          UINT uMsg,
          WPARAM wParam,
          LPARAM lParam)
{
  LRESULT lResult = FALSE;

  switch (uMsg)
  {
    case WM_CREATE:
      {
        // Setup for painting text in this window.
        HDC hdc = GetDC(m_hWnd);
        ::GetTextMetrics(hdc, &m_tm);
        ::ReleaseDC(m_hWnd, hdc);
      }
      break;

    case WM_MEASUREITEM:
      // Get setup for painting text in this window.
      {
        LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam;
        lpmis->itemHeight = m_tm.tmHeight + m_tm.tmExternalLeading;
        lpmis->itemWidth = m_wWidth;
        lResult = TRUE;
      }

    case WM_SIZE:
      // Handle a resize of this window.
      m_wWidth = LOWORD(lParam);
      m_wHeight = HIWORD(lParam);
      // Resize the Message Log ListBox
      m_pMsgLog->Resize(m_wWidth, m_wHeight);
      break;

    case WM_COMMAND:
      // Dispatch and handle any Menu command messages received.
      lResult = DoMenu(wParam, lParam);
      break;

    case WM_COPYDATA:
      // We have been sent a trace log message from a server.
      // Log it to our own Client's display.
      {
        LPTSTR pszMsg = (LPTSTR)((COPYDATASTRUCT*)lParam)->lpData;
        g_pMsgLog->Msg(pszMsg);
      }
      break;

    case WM_CLOSE:
      // The user selected Close on the main window's System menu
      // or Exit on the File menu.
    case WM_QUIT:
      // If the app is being quit then close any associated help windows.
    default:
      // Defer all messages NOT handled here to the Default Window Proc.
      lResult = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
      break;
  }

  return(lResult);
}


/*F+F++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: UnicodeOk

  Summary:  Checks if the platform will handle unicode versions of
            Win32 string API calls.

  Args:     void

  Returns:  BOOL
              TRUE if unicode support; FALSE if not.
------------------------------------------------------------------------F-F*/
BOOL UnicodeOk(void)
{
  BOOL bOk = TRUE;
  TCHAR szUserName[MAX_STRING_LENGTH];
  DWORD dwSize = MAX_STRING_LENGTH;

  if (!GetUserName(szUserName, &dwSize))
    bOk = ERROR_CALL_NOT_IMPLEMENTED == GetLastError() ? FALSE : TRUE;

  return bOk;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: InitApplication

  Summary:  Initializes the application and registers its main window
            class. InitApplication is called only once (in WinMain).

  Args:     HINSTANCE hInstance)
              Handle to the first instance of the application.

  Returns:  BOOL.
              TRUE if success.
              FALSE if fail.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
BOOL InitApplication(
       HINSTANCE hInstance)
{
  BOOL bOk;
  // The window class for all instances of the main frame window.
  WNDCLASSEX wcf;

  // Assign the appropriate values for this main frame window class.
  wcf.cbSize        = sizeof(WNDCLASSEX);
  wcf.cbClsExtra    = 0;            // No per-class extra data.
  wcf.cbWndExtra    = 0;            // No per-window extra data.
  wcf.hInstance     = hInstance;    // Application module instance.
  wcf.lpfnWndProc   = &WindowProc;  // Global Window Procedure (defined in
                                    // APPUTIL for all CVirWindows).
  wcf.hCursor       = LoadCursor(NULL, IDC_ARROW); // Load app cursor.
  wcf.hIcon         = (HICON) LoadIcon(            // Load app icon.
                                hInstance,
                                TEXT("AppIcon"));
  wcf.hIconSm       = (HICON) LoadImage(           // Load small icon.
                                hInstance,
                                TEXT("AppIcon"),
                                IMAGE_ICON,
                                16, 16,
                                0);
  wcf.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // Default backgnd color.
  wcf.style         = CS_HREDRAW | CS_VREDRAW;     // Class style(s).
  wcf.lpszClassName = TEXT(MAIN_WINDOW_CLASS_NAME_STR); // Class name.
  wcf.lpszMenuName  = TEXT(MAIN_WINDOW_CLASS_MENU_STR); // Menu name.

  // Register the window class and return FALSE if unsuccesful.
  bOk = RegisterClassEx(&wcf);

  // Zero the g_ServerInfo structure.
  memset(&g_ServerInfo, 0, sizeof(COSERVERINFO));

  // Init the remote machine name.
  g_wszMachineName[0] = 0;
#ifdef UNICODE
  g_ServerInfo.pwszName = &g_szMachineName[0];
#else
  g_ServerInfo.pwszName = &g_wszMachineName[0];
#endif

  return (bOk);
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: WinMain

  Summary:  The Windows main entry point function for this application.
            Initializes the application, the COM Libraries, and starts
            the main application message loop.

  Args:     HINSTANCE hInstance,
              Instance handle; a new one for each invocation of this app.
            HINSTANCE hPrevInstance,
              Instance handle of the previous instance. NULL in Win32.
            LPSTR lpCmdLine,
              Windows passes a pointer to the application's
              invocation command line.
            int nCmdShow)
              Bits telling the show state of the application.

  Returns:  int
              msg.wParam (upon exit of message loop).
              FALSE if this instance couldn't initialize and run.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
extern "C" int PASCAL WinMain(
                        HINSTANCE hInstance,
                        HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine,
                        int nCmdShow)
{
  CMainWindow* pWin = NULL;
  MSG msg;
  HACCEL hAccel;
  int iRun = FALSE;

  // If we were compiled for UNICODE and the platform seems OK with this
  // then proceed.  Else we error and exit the app.
  if (UnicodeOk())
  {
    // Call to initialize the COM Library.  Use the SUCCEEDED macro
    // to detect success.  If fail then exit app with error message.
    if (SUCCEEDED(CoInitialize(NULL)))
    {
      // Ensure that DCOM (Distributed COM) is installed.
      if (DComOk())
      {
        // If we succeeded in initializing the COM Library and confirming
        // adequate DCOM support, we proceed to initialize the
        // application.  If we can't init the application then we signal
        // shut down with an error message exit.
        iRun = InitApplication(hInstance);
        if (iRun)
        {
          // Assume we'll set iRun to TRUE when initialization is done.
          iRun = FALSE;
          // We are still go for running so we try to create a nifty new
          // CMainWindow object for this app instance.
          pWin = new CMainWindow;
          if (NULL != pWin)
          {
            // Now we initialize an instance of the new CMainWindow.
            // This includes creating the main window.
            if (pWin->InitInstance(hInstance, nCmdShow))
            {
              // Load the keyboard accelerators from the resources.
              hAccel = LoadAccelerators(hInstance, TEXT("AppAccel"));
              if (NULL != hAccel)
              {
                // Signal App Initialization is successfully done.
                iRun = TRUE;
              }
            }
          }
        }

        if (iRun)
        {
          // If we initialized the app instance properly then we are still
          // go for running.  We then start up the main message pump for
          // the application.
          while (GetMessage(&msg, NULL, 0, 0))
          {
            if (!TranslateAccelerator(
                   pWin->GetHwnd(),
                   hAccel,
                   &msg))
            {
              TranslateMessage(&msg);
              DispatchMessage(&msg);
            }
          }

          // We ask COM to unload any unused COM Servers.
          CoFreeUnusedLibraries();

          // We'll pass to Windows the reason why we exited the message loop.
          iRun = msg.wParam;
        }
        else
        {
          // We failed to initialize the application. Put up error message
          // box saying that application couldn't be initialized.  Parent
          // window is desktop (ie, NULL). Exit the failed application
          // (ie, by returning FALSE to WinMain).
          ErrorBox(hInstance, NULL, IDS_APPINITFAILED);

          // Delete the CMainWindow object.
          DELETE_POINTER(pWin);
        }

        // We're exiting this app (either normally or by init failure) so
        // shut down the COM Library.
        CoUninitialize();
      }
      else
      {
        // If DCOM is not installed indicate an error and
        // exit the app immediately.
        ErrorBox(hInstance, NULL, IDS_NODCOM);
      }
    }
    else
    {
      // We failed to Initialize the COM Library. Put up error message
      // box saying that COM Library couldn't be initialized.  Parent
      // window is desktop (ie, NULL). Exit the failed application
      // (ie, by returning FALSE to WinMain).
      ErrorBox(hInstance, NULL, IDS_COMINITFAILED);
    }
  }
  else
  {
    // If we were compiled for UNICODE but the platform has problems with
    // this then indicate an error and exit the app immediately.
    CHAR szMsg[MAX_STRING_LENGTH];

    if (LoadStringA(
          hInstance,
          IDS_NOUNICODE,
          szMsg,
          MAX_STRING_LENGTH))
    {
      MessageBoxA(
        NULL,
        szMsg,
        ERROR_TITLE_STR,
        MB_OK | MB_ICONEXCLAMATION);
    }
  }

  return iRun;
}
