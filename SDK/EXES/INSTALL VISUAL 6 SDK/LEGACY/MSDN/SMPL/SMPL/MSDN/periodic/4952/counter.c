/*************************************************************
Module name: Counter.c
Notices: Copyright (c) 1996 Jeffrey Richter
Description: Demonstrates background processing using fibers
*************************************************************/


#define STRICT 
#define _WIN32_WINNT  0x0400  // for Fiber function prototypes
#include <Windows.h>
#include <WindowsX.h>
#include "Resource.h"


//////////////////////////////////////////////////////////////


// The possible state of the background processing
typedef enum { 
   BPS_STARTOVER,  // Start the background processing from beginning
   BPS_CONTINUE,   // Continue the background processing 
   BPS_DONE        // There is no background processing to do
} BKGNDPROCSTATE;


typedef struct {
   // User-interface fiber execution context
   PVOID pFiberUI;

   // Handle of main UI window
   HWND  hwnd;

   // State of background processing
   BKGNDPROCSTATE bps;
} FIBERINFO, *PFIBERINFO;


// A global that contains application state information. This 
// global is accessed directly by the UI fiber and indirectly
// by the background processing fiber.
FIBERINFO g_FiberInfo;


//////////////////////////////////////////////////////////////


void WINAPI Counter_FiberFunc (LPVOID pvParam) {
   PFIBERINFO pFiberInfo = (PFIBERINFO) pvParam;
   BOOL fTranslated;
   int x, nCount;

   // Update the window showing which fiber is executing
   SetDlgItemText(pFiberInfo->hwnd, 
      IDC_FIBER, __TEXT("Recalculation"));

   // Get the current count in the EDIT control
   nCount = GetDlgItemInt(
      pFiberInfo->hwnd, IDC_COUNT, &fTranslated, FALSE);
   
   // Count from 0 to nCount updating the STATIC control
   for (x = 0; x <= nCount; x++) {

      // UI events have higher priority than counting.
      // If there are any UI events, handle them ASAP.
      if (HIWORD(GetQueueStatus(QS_ALLEVENTS)) != 0) {

         // The UI fiber has something to do, temporarily
         // pause counting, and handle the UI events.
         SwitchToFiber(pFiberInfo->pFiberUI);

         // The UI has no more events, continue counting
         SetDlgItemText(pFiberInfo->hwnd, 
            IDC_FIBER, __TEXT("Recalculation"));
      }

      // Update the STATIC control with the most recent count
      SetDlgItemInt(pFiberInfo->hwnd, IDC_ANSWER, x, FALSE);

      // Sleep for a while to exaggerate the effect; remove 
      // the call to Sleep in production code.
      Sleep(200);
   }


   // Indicate that counting is complete.
   pFiberInfo->bps = BPS_DONE;

   // Reschedule the UI thread. When the UI thread is running
   // and has no events to process, the thread is put to sleep
   // NOTE: If we just allow the fiber function to return,
   // the thread and the UI fiber die -- we don't want this!
   SwitchToFiber(pFiberInfo->pFiberUI);
}


//////////////////////////////////////////////////////////////


BOOL Counter_OnInitDialog(HWND hwnd, 
   HWND hwndFocus, LPARAM lParam) {

#ifdef _DEBUG
   // In debug versions, move the window to the top, left so
   // that the rest of the screen is available to the debugger.
   SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
#endif
   SetDlgItemInt(hwnd, IDC_COUNT, 0, FALSE);
   return(TRUE);
}


//////////////////////////////////////////////////////////////


void Counter_OnCommand(HWND hwnd, 
   int id, HWND hwndCtl, UINT codeNotify) {

   switch (id) {
      case IDCANCEL: 
         // If the Escape key is hit, destroy the modeless 
         // dialog box, terminating the application.
         DestroyWindow(hwnd); 
         break;

      case IDC_COUNT:
         if (codeNotify == EN_CHANGE) {

            // When the user changes the count, start the 
            // background processing over from the beginning
            g_FiberInfo.bps = BPS_STARTOVER; 
         }
         break;
   }
}


//////////////////////////////////////////////////////////////


BOOL WINAPI Counter_DlgProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
   switch (uMsg) {
      HANDLE_MSG(hwnd, WM_INITDIALOG, Counter_OnInitDialog);
      HANDLE_MSG(hwnd, WM_COMMAND, Counter_OnCommand);
   }
   return(FALSE);
}


//////////////////////////////////////////////////////////////


int WINAPI WinMain (HINSTANCE hinstExe, 
   HINSTANCE hinstExePrev, LPSTR pszCmdLine, int nCmdShow) {

   // Counter fiber execution context
   PVOID pFiberCounter = NULL;   

   // Convert this thread to a fiber
   g_FiberInfo.pFiberUI = ConvertThreadToFiber(NULL);

   // Create the appication's UI window
   g_FiberInfo.hwnd = CreateDialog(hinstExe, 
      MAKEINTRESOURCE(IDD_COUNTER), NULL, Counter_DlgProc);

   // Update the window showing which fiber is executing
   SetDlgItemText(g_FiberInfo.hwnd, 
      IDC_FIBER, __TEXT("User-interface"));

   // Initially, there is no background processing to be done
   g_FiberInfo.bps = BPS_DONE;

   // While the UI window still exists...
   while (IsWindow(g_FiberInfo.hwnd)) {

      // UI messages are higher priority 
      // than background processing
      MSG msg;
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

         // If a message exists in the queue, process it
         if (!IsDialogMessage(g_FiberInfo.hwnd, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
         }

      } else {

         // If no UI messages exist, check the 
         // state of the background processing
         switch (g_FiberInfo.bps) {
            case BPS_DONE:
               // No messages exist and there is no background 
               // processing to do; wait for a UI event
               WaitMessage();
               break;

            case BPS_STARTOVER:
               // The user has changed the count, start the 
               // background processing over from the beginning.

               if (pFiberCounter != NULL) { 
                  // If a recaulculation fiber already exists,
                  // delete it so that background processing 
                  // will start all over from the beginning
                  DeleteFiber(pFiberCounter); 
                  pFiberCounter = NULL; 
               }

               // Create a new recalc fiber that
               // starts over from the beginning
               pFiberCounter = CreateFiber(
                  0, Counter_FiberFunc, &g_FiberInfo);

               // Indicate that we have started the background 
               // processing and that it should continue
               g_FiberInfo.bps = BPS_CONTINUE;

               // Fall through to BPS_CONTINUE case...

            case BPS_CONTINUE:
               // Allow the background processing to execute...
               SwitchToFiber(pFiberCounter);

               // The background processing has been paused (because 
               // a UI message showed up) or has been stopped (because
               // the counting completed).

               // Update the window showing which fiber is executing
               SetDlgItemText(g_FiberInfo.hwnd, 
                  IDC_FIBER, __TEXT("User-interface"));

               if (g_FiberInfo.bps == BPS_DONE) { 
                  // If the background processing ran to completion,
                  // delete the background fiber so that background 
                  // processing will start all over from the 
                  // beginning next time
                  DeleteFiber(pFiberCounter); 
                  pFiberCounter = NULL; 
               }
               break;
         }  // switch on background processing state

      }  // No UI messages exist
   }  // while the window still exists

   return(0);  // End the application
}


//////////////////////// End Of File /////////////////////////
