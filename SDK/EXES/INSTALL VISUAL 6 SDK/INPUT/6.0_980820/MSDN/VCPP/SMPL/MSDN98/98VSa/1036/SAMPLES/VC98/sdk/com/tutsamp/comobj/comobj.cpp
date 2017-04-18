/*+==========================================================================
  File:      COMOBJ.CPP

  Summary:   Implementation file for a primitive DLL server providing
             several Car-related COM Objects.  This is not a full-blown
             COM Server.  Rather it is a primitive COM Object server
             offering the following COM objects: Car, UtilityCar, and
             CruiseCar.  Appropriate create functions are exported from
             this DLL: CreateCar, CreateUtilityCar, and CreateCruiseCar.

             For a comprehensive tutorial code tour of COMOBJ's
             contents and offerings see the tutorial COMOBJ.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the COMOBJ source code.

  Classes:   none.

  Functions: DllMain, ComObjInitMsgLog, ComObjAboutBox, CreateCar,
             CreateUtilityCar, CreateCruiseCar

  Origin:    8-20-95: atrent - Editor-inheritance from DLLSKEL.CPP in
               the DLLSKEL Tutorial Code Sample.

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

/*---------------------------------------------------------------------------
  We include WINDOWS.H for all Win32 applications.
  We include OLE2.H because we will make calls to the COM/OLE Libraries.
  We include INITGUID.H only once (here) in the entire DLL because we
    will be defining GUIDs and want them as constants in the data segment.
  We include APPUTIL.H because we will be building this DLL using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include ICARS.H and CARGUIDS.H for the common car-related Interface
    class, GUID, and CLSID specifications.
  We include COMOBJI.H because it has the necessary internal class and
    resource definitions for this DLL.
  We include COMOBJ.H because it has the necessary DLLENTRY function
    prototypes.  The _DLLEXPORT_ #define is used to tell COMOBJ.H to
    define the appropriate functions as exported from this DLL.
    Otherwise, COMOBJ.H is included by users of this DLL who do not
    define _DLLEXPORT_ so that the appropriate functions are then
    declared as imports rather than defined as exports.  COMOBJ.H also
    has the necessary interface declarations for ICar, IUtility, and ICruise.
  We include CAR.H, UTILCAR,H, and, CRUCAR.H for the object class
    declarations for the COCar, COUtilityCar, and COCruiseCar COM objects.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <initguid.h>
#include <apputil.h>
#include <icars.h>
#include <carguids.h>
#include "comobji.h"
#define _DLLEXPORT_
#include "comobj.h"
#include "car.h"
#include "utilcar.h"
#include "crucar.h"


// Global variable definitions. Initialized in DllMain() below.

// Here is a pointer for use by the global Debug Message logging macros.
// Set by the ComObjInitMsgLog function call from an outside EXE user.
CMsgLog* g_pMsgLog;

// We encapsulate most of the global data for clarity.  Here is a
// global pointer to the DllData object.
CDllData* g_pDll;


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
  Function: DllMain

  Summary:  Like WinMain is for an EXE application, this DllMain function
            is the main entry point for this DLL.  It is called when the
            DLL is loaded by a process, and when new threads are created
            by a process that has already loaded this DLL.  DllMain is also
            called when threads of a process that has loaded the DLL exit
            cleanly and when the process itself unloads the DLL.

            If you want to use C runtime libraries, keep this function
            named "DllMain" and you won't have to do anything special to
            initialize the runtime libraries.

            When fdwReason == DLL_PROCESS_ATTACH, the return value is used
            to determine if the DLL should remain loaded, or should be
            immediately unloaded depending upon whether the DLL could be
            initialized properly.  For all other values of fdwReason,
            the return value is ignored.

  Args:     HINSTANCE hDLLInst,
              Instance handle of the DLL.
            DWORD fdwReason,
              Process attach/detach or thread attach/detach.
              Reason for calling.
            LPVOID lpvReserved)
              Reserved and not used.

  Returns:  BOOL,
              Return value is used only when fdwReason == DLL_PROCESS_ATTACH.
              TRUE  -  Used to signify that the DLL should remain loaded.
              FALSE -  Used to signify that the DLL should be
                immediately unloaded.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
BOOL WINAPI DllMain(
              HINSTANCE hDllInst,
              DWORD fdwReason,
              LPVOID lpvReserved)
{
  BOOL bResult = TRUE;

  // Dispatch this main call based on the reason it was called.
  switch (fdwReason)
  {
    case DLL_PROCESS_ATTACH:
      // The DLL is being loaded for the first time by a given process.
      // Perform per-process initialization here.  If the initialization
      // is successful, return TRUE; if unsuccessful, return FALSE.
      bResult = FALSE;
      if (UnicodeOk())
      {
        // Instantiate a DLL global data encapsulator class.
        g_pDll = new CDllData;
        if (NULL != g_pDll)
        {
          // Remember the DLL Instance handle.
          g_pDll->hDllInst = hDllInst;
          // Create a MsgBox object.
          g_pDll->pMsgBox = new CMsgBox;
          if (NULL != g_pDll->pMsgBox)
            bResult = TRUE;
        }
      }
      break;

    case DLL_PROCESS_DETACH:
      // The DLL is being unloaded by a given process.  Do any
      // per-process clean up here, such as undoing what was done in
      // DLL_PROCESS_ATTACH.  The return value is ignored.
      if (NULL != g_pDll)
      {
        DELETE_POINTER(g_pDll->pMsgBox);
        DELETE_POINTER(g_pDll);
      }
      break;

    case DLL_THREAD_ATTACH:
      // A thread is being created in a process that has already loaded
      // this DLL.  Perform any per-thread initialization here.  The
      // return value is ignored.
      break;

    case DLL_THREAD_DETACH:
      // A thread is exiting cleanly in a process that has already
      // loaded this DLL.  Perform any per-thread clean up here.  The
      // return value is ignored.
      break;

    default:
      break;
  }

  return (bResult);
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: ComObjInitMsgLog

  Summary:  Initialize a pointer inside this DLL to an outside EXE's
            Message Log facility.  We want to see LOG macro output used
            inside this DLL in the host EXE's message log window.

  Args:     CMsgLog* pMsgLog
              Pointer to a message log object.

  Returns:  BOOL
              TRUE.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
DLLENTRY BOOL WINAPI ComObjInitMsgLog(
                       CMsgLog* pMsgLog)
{
  // Set up a pointer to the host EXE's Message Log facility so that any
  // LOG macros used in this DLL will log to the host EXE's log window.
  g_pMsgLog = pMsgLog;

  LOG("D: --- COMOBJ.DLL now logging ---");

  return TRUE;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: ComObjAboutBox

  Summary:  One of the exported service functions of this DLL.  In this
            simple code sample, ComObjAboutBox showcases use of the
            CAboutBox class (from the APPUTIL utility library).  It also
            illustrates how to implement this dialog using resources
            stored in this DLL itself.

  Args:     HWND hWnd)
              Handle of window that is to be parent of the dialog window.

  Returns:  BOOL,
              Always returns TRUE.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
DLLENTRY BOOL WINAPI ComObjAboutBox(
                       HWND hWnd)
{
  // Define one of those nifty APPUTIL CAboutBox modal dialog objects.
  CAboutBox dlgAboutBox;

  // Show the standard About Box dialog for this DLL by telling the dialog
  // C++ object to show itself by invoking its ShowDialog method.
  // Pass it this DLL instance and the parent window handle.  Use a dialog
  // resource ID for the dialog stored in this DLL module's resources.
  dlgAboutBox.ShowDialog(
    g_pDll->hDllInst,
    MAKEINTRESOURCE(IDD_ABOUTBOX),
    hWnd);

  return TRUE;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: CreateCar

  Summary:  Creates an instance of the COCar COM object class
            returning a requested interface pointer.

  Args:     IUnknown* pUnkOuter,
              Pointer the outer Unknown interface.  Non NULL implies
              that the new COM object is being created via an
              aggregation with an Outer object.  NULL implies that the
              object is not being created via aggregation.
            REFIID riid,
              The GUID of the interface requested on the new COM Object.
            PPVOID ppv)
              Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              NOERROR if successful, CLASS_E_NOAGREGATION if IUnknown is
              not requested with non-NULL pUnkOuter, or other errors as
              appropriate.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
DLLENTRY HRESULT WINAPI CreateCar(
                          IUnknown* pUnkOuter,
                          REFIID riid,
                          PPVOID ppv)
{
  HRESULT hr;
  COCar* pCob;

  LOGF1("D: CreateCar. pUnkOuter=0x%X.",pUnkOuter);

  // If the creation call is requesting aggregation (pUnkOuter != NULL),
  // the COM rules state the IUnknown interface MUST also be concomitantly
  // be requested.  If it is not so requested (riid != IID_IUnknown) then
  // an error must be returned indicating that no aggregate creation of
  // the COCar COM Object can be performed.
  if (NULL != pUnkOuter && riid != IID_IUnknown)
    hr = CLASS_E_NOAGGREGATION;
  else
  {
    // Instantiate a CCar COM Object.
    pCob = new COCar(pUnkOuter);

    // We QueryInterface this new COM Object not only to deposit the
    // requested interface pointer into the caller's pointer variable,
    // but to also automatically bump the Reference Count on the new
    // COM Object after handing out this reference to it.
    if (NULL != pCob)
      hr = pCob->QueryInterface(riid, (PPVOID)ppv);
    else
      hr = E_OUTOFMEMORY;
  }

  if (SUCCEEDED(hr))
    LOGF1("D: CreateCar Succeeded. *ppv=0x%X.",*ppv);

  return hr;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: CreateUtilityCar

  Summary:  Creates an instance of the COUtilityCar COM object class
            returning a requested interface pointer. COUtilityCar uses the
            Containment reuse technique to incorporate COCar features
            (ie, ICar implementation) into its Interface offerings
            (ie, IUnknown, ICar, and IUtility).

  Args:     IUnknown* pUnkOuter,
              Pointer the outer Unknown interface.  Non NULL implies
              that the new COM object is being created via an
              aggregation with an Outer object.  NULL implies that the
              object is not being created via aggregation.
            REFIID riid,
              The GUID of the interface requested on the new COM Object.
            PPVOID ppv)
              Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              NOERROR if successful, CLASS_E_NOAGREGATION if IUnknown is
              not requested with non-NULL pUnkOuter, or other errors as
              appropriate.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
DLLENTRY HRESULT WINAPI CreateUtilityCar(
                          IUnknown* pUnkOuter,
                          REFIID riid,
                          PPVOID ppv)
{
  HRESULT hr;
  COUtilityCar* pCob;

  LOGF1("D: CreateUtilityCar. pUnkOuter=0x%X.",pUnkOuter);

  // If the creation call is requesting aggregation (pUnkOuter != NULL),
  // the COM rules state the IUnknown interface MUST also be concomitantly
  // be requested.  If it is not so requested (riid != IID_IUnknown) then
  // an error must be returned indicating that no aggregate creation of
  // the COUtilityCar COM Object can be performed.
  if (NULL != pUnkOuter && riid != IID_IUnknown)
    hr = CLASS_E_NOAGGREGATION;
  else
  {
    // Instantiate a CUtilityCar COM Object.
    pCob = new COUtilityCar(pUnkOuter);
    if (NULL != pCob)
    {
      // If we have succeeded in instantiating the COUtilityCar object
      // we initialize it to set up any subordinate objects (ie, via
      // containment or aggregation).
      hr = pCob->Init();
      if (SUCCEEDED(hr))
      {
        // We QueryInterface this new COM Object not only to deposit the
        // requested interface pointer into the caller's pointer variable,
        // but to also automatically bump the Reference Count on the new
        // COM Object after handing out this reference to it.
        hr = pCob->QueryInterface(riid, (PPVOID)ppv);
      }
    }
    else
      hr = E_OUTOFMEMORY;
  }

  if (SUCCEEDED(hr))
    LOGF1("D: CreateUtilityCar Succeeded. *ppv=0x%X.",*ppv);

  return hr;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: CreateCruiseCar

  Summary:  Creates an instance of the COCruiseCar COM object class
            returning a requested interface pointer. COCruiseCar uses the
            Aggregation reuse technique to incorporate COCar features
            (ie, ICar implementation) into its Interface offerings
            (ie, IUnknown, ICar, and ICruise).  With this aggregation,
            the ICar interface is not implemented in COCruiseCar.  It is
            instead solely implemented in a COCar object that
            CreateCruiseCar instantiates.  That COCar's ICar implementation
            is used directly in this aggregation.

  Args:     IUnknown* pUnkOuter,
              Pointer the outer Unknown interface.  Non NULL implies
              that the new COM object is being created via an
              aggregation with an Outer object.  NULL implies that the
              object is not being created via aggregation.
            REFIID riid,
              The GUID of the interface requested on the new COM Object.
            PPVOID ppv)
              Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              NOERROR if successful, CLASS_E_NOAGREGATION if IUnknown is
              not requested with non-NULL pUnkOuter, or other errors as
              appropriate.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
DLLENTRY HRESULT WINAPI CreateCruiseCar(
                          IUnknown* pUnkOuter,
                          REFIID riid,
                          PPVOID ppv)
{
  HRESULT hr;
  COCruiseCar* pCob;

  LOGF1("D: CreateCruiseCar. pUnkOuter=0x%X.",pUnkOuter);

  // If the creation call is requesting aggregation (pUnkOuter != NULL),
  // the COM rules state the IUnknown interface MUST also be concomitantly
  // be requested.  If it is not so requested (riid != IID_IUnknown) then
  // an error must be returned indicating that no aggregate creation of
  // the COCruiseCar COM Object can be performed.
  if (NULL != pUnkOuter && riid != IID_IUnknown)
    hr = CLASS_E_NOAGGREGATION;
  else
  {
    // Instantiate a COCruiseCar COM Object.
    pCob = new COCruiseCar(pUnkOuter);
    if (NULL != pCob)
    {
      // If we have succeeded in instantiating the COCruiseCar object
      // we initialize it to set up any subordinate objects (ie, via
      // containment or aggregation).
      hr = pCob->Init();
      if (SUCCEEDED(hr))
      {
        // We QueryInterface this new COM Object not only to deposit the
        // requested interface pointer into the caller's pointer variable,
        // but to also automatically bump the Reference Count on the new
        // COM Object after handing out this reference to it.
        hr = pCob->QueryInterface(riid, (PPVOID)ppv);
      }
    }
    else
      hr = E_OUTOFMEMORY;
  }

  if (SUCCEEDED(hr))
    LOGF1("D: CreateCruiseCar Succeeded. *ppv=0x%X.",*ppv);

  return hr;
}
