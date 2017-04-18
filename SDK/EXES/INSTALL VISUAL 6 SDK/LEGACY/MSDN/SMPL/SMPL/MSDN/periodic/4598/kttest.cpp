/*****************************************************************************
Module:  KTTest.CPP
Notices: Written 1995 by Jeffrey Richter
Purpose: Demonstrates how to kill a thread cleanly.
*****************************************************************************/


#define STRICT
#include <windows.h>
#include <windowsx.h>
#pragma warning(disable: 4001)    /* Single line comment */

#include <tchar.h>

#include "resource.h"
#include "KillThrd.h"             // Kill Thread functions


//////////////////////////////////////////////////////////////////////////////


// This simple C++ class exists in order to test C++ EH.
class CTestClass {
   HWND   m_hwnd;       // Handle of window
   HANDLE m_hThread;    // Handle to worker thread's kernel object

public:
   CTestClass (HWND hwnd);
   ~CTestClass ();

   // This cast operator simply returns the thread handle
   operator HANDLE() const { return(m_hThread); }
};


CTestClass::CTestClass (HWND hwnd) {
   m_hwnd = hwnd;

   // Create a "real" handle to the thread kernel object
   DuplicateHandle(GetCurrentProcess(), GetCurrentThread(),
      GetCurrentProcess(), &m_hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);

   ListBox_SetCurSel(m_hwnd,
      ListBox_AddString(m_hwnd, _T("C++ object created")));
}


CTestClass::~CTestClass () {
   // Close the thread handle
   CloseHandle(m_hThread);
   ListBox_SetCurSel(m_hwnd,
      ListBox_AddString(m_hwnd, _T("C++ object destroyed")));
}


///////////////////////////// HANDLE_DLGMSG Macro ////////////////////////////


// The normal HANDLE_MSG macro in WINDOWSX.H does not work properly for dialog
// boxes because DlgProc's return a BOOL instead of an LRESULT (like
// WndProcs). This HANDLE_DLGMSG macro corrects the problem:
#define HANDLE_DLGMSG(hwnd, message, fn)                    \
   case (message): return (SetDlgMsgResult(hwnd, uMsg,      \
      HANDLE_##message((hwnd), (wParam), (lParam), (fn))))


//////////////////////////////////////////////////////////////////////////////


BOOL KTTest_OnInitDialog (HWND hwnd, HWND hwndFocus, LPARAM lParam) {

   // Disable the "End" button since the worker thread hasn't started yet
   EnableWindow(GetDlgItem(hwnd, IDC_END), FALSE);

   return(TRUE);                  // Accept default focus window.
}


//////////////////////////////////////////////////////////////////////////////


// This is the interesting test code. This function even creates a stack-based
// C++ object so that you can see that the object's destructor is called when
// the thread is forcibly terminated.
DWORD WINAPI WorkerThreadWithoutSEH (LPVOID pvParam) {
   HWND hwnd = (HWND) pvParam;

   // Windows 95 has a bug which causes an exception to be raised when a
   // thread is waiting in a call WaitForSingleObject/WaitForMultipleObjects
   // and the thread's instruction pointer is changed. Using the fIsWin95
   // flag ensures that the is bug does not expose itself.
   OSVERSIONINFO osvi;
   osvi.dwOSVersionInfoSize = sizeof(osvi);
   GetVersionEx(&osvi);
   BOOL fIsWin95 = (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS);

   ListBox_SetCurSel(hwnd, 
      ListBox_AddString(hwnd, _T("Starting Worker thread")));

   // Create a C++ object to test C++ EH. The C++ object creates a handle to
   // this thread's kernel object.
   CTestClass TestClass(hwnd);


   ListBox_SetCurSel(hwnd, ListBox_AddString(hwnd, _T("Sleep (3 seconds)")));
   Sleep(3000);


   ListBox_SetCurSel(hwnd,
      ListBox_AddString(hwnd, _T("WaitForSingleObject (3 seconds)")));
   // Wait on this thread's kernel object - it will never be signalled.
   WaitForSingleObject((HANDLE) TestClass, 3000);


   ListBox_SetCurSel(hwnd,
      ListBox_AddString(hwnd, _T("WaitForMultipleObjects (3 seconds)")));
   HANDLE h = (HANDLE) TestClass;
   // Wait on this thread's kernel object - it will never be signalled.
   WaitForMultipleObjects(1, &h, TRUE, 3000);


   // Don't allow the UI thread to terminate us until our loop terminates
   KillThrd_DelayDeath(TRUE);
   ListBox_SetCurSel(hwnd,
      ListBox_AddString(hwnd, _T("Looping a lot, can't be broken")));
   for (int n = 0 ; n < 200000; n++) {

      // We can delay the thread's death multiple times.
      KillThrd_DelayDeath(TRUE);

      // We would usually want to delay our death when using functions
      // that wait on CriticalSections or other thread synchronization
      // objects so that we don't get them and then die leaving other
      // threads suspended forever.
      free(malloc(10));
      KillThrd_DelayDeath(FALSE);
   }
   KillThrd_DelayDeath(FALSE);


   // The UI thread can terminate this loop at any time.
   ListBox_SetCurSel(hwnd, 
      ListBox_AddString(hwnd, _T("Looping a lot, can be broken")));
   for (n = 0 ; n < 50000000; n++) {
      // Do nothing
   }

   // We made it to the end of the function
   ListBox_SetCurSel(hwnd, 
      ListBox_AddString(hwnd, _T("Finished looping")));

   return(0);
}


//////////////////////////////////////////////////////////////////////////////


DWORD WINAPI WorkerThreadExcFilter (DWORD dwExceptionCode, HWND hwnd) {

   // Exception filter used for testing. It adds an entry to the listbox
   // when the worker thread is termiante with KillThrd_Kill.
   if (dwExceptionCode == SE_KILLTHREAD) {
      ListBox_SetCurSel(hwnd, 
         ListBox_AddString(hwnd, _T("SE_KILLTHREAD detected")));
   }

   return(EXCEPTION_CONTINUE_SEARCH);
}


//////////////////////////////////////////////////////////////////////////////


// This is the worker thread.
DWORD WINAPI WorkerThread (LPVOID pvParam) {

   HWND hwnd = (HWND) pvParam;
   DWORD dwExitCode = 0;

   __try {
      __try {
         // Because we can't mix SEH and C++ EH in the same function, call
         // another function so that C++ objects are destructed properly.
         dwExitCode = WorkerThreadWithoutSEH(pvParam);
      }
      __except (WorkerThreadExcFilter(GetExceptionCode(), hwnd)) {
         // We never get in here because WorkerThreadExcFilter always
         // returns EXCEPTION_CONTINUE_SEARCH.
      }
   }
   __finally {
      // This executes even if the thread is dying.
      ListBox_SetCurSel(hwnd,
         ListBox_AddString(hwnd, _T("Inside __finally block")));
   }

   // This executes only if the thread dies naturally. It does execute
   // if KillThrd_Kill is used to kill this thread.
   ListBox_SetCurSel(hwnd,
      ListBox_AddString(hwnd, _T("Worker thread is dying on its own")));

   return(dwExitCode);
}


//////////////////////////////////////////////////////////////////////////////


// Special watchdog thread used for testing.  This thread just waits for
// the worker thread to terminate and then adds an entry to the listbox.
DWORD WINAPI WorkerMonitorThread (LPVOID pvParam) {

   HANDLE hThread = (HANDLE) pvParam;
   HWND hwnd = GetForegroundWindow();

   WaitForSingleObject(hThread, INFINITE);

   // When the worker thread dies, add an entry to the listbox.
   HWND hwndLB = GetDlgItem(hwnd, IDC_PROGRESS);
   ListBox_SetCurSel(hwndLB,
      ListBox_AddString(hwndLB, _T("--> Worker thread is definitely dead")));

   // Re-enable the "Start" button and disable the "End" button
   EnableWindow(GetDlgItem(hwnd, IDC_START), TRUE);
   EnableWindow(GetDlgItem(hwnd, IDC_END), FALSE);

   // Give focus to the "Start" button. NOTE: Because the "Start" button
   // was created with another thread, we have to attach our input queues
   // together first before calling SetFocus.
   AttachThreadInput(GetCurrentThreadId(),
      GetWindowThreadProcessId(hwnd, NULL), TRUE);
   SetFocus(GetDlgItem(hwnd, IDC_START));
   return(0);
}


//////////////////////////////////////////////////////////////////////////////


void KTTest_OnCommand (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
   static PKILLTHRD s_pkt = NULL;
   HWND hwndLB = GetDlgItem(hwnd, IDC_PROGRESS);
   DWORD dwThreadId;

   switch (id) {
      case IDC_START:
         ListBox_ResetContent(hwndLB);

         // Create the worker thread using KillThrd_CreateThread so that
         // the thread can be killed cleanly at any time. This function
         // allocates a block of memory and returns the pointer. This
         // pointer is saved in a static so that we can use it when
         // the user presses the "End" button.
         s_pkt = KillThrd_CreateThread(NULL, 0, WorkerThread,
            hwndLB, 0, &dwThreadId);

         // For testing purposes, create a watchdog thread that sleeps
         // until the worker thread dies. This thread adds a message to
         // the listbox when the worker thread is truely dead.
         CloseHandle(CreateThread(NULL, 0, WorkerMonitorThread,
            (PVOID) s_pkt->m_hThread, 0, &dwThreadId));

         // Disable the "Start" button and enable the "End" button.
         EnableWindow(hwndCtl, FALSE);
         EnableWindow(GetDlgItem(hwnd, IDC_END), TRUE);
         SetFocus(GetDlgItem(hwnd, IDC_END));
         break;

      case IDC_END:
         // The worker thread should die now!  Disable the "End" button.
         EnableWindow(hwndCtl, FALSE);

         // Kill the worker thread passing the address of the block
         // returned from KillThrd_CreateThread.
         KillThrd_Kill(s_pkt);

         // Cleanup the resources.  If you'd like, you can use the thread
         // handle in this structure BEFORE calling KillThrd_Close
         KillThrd_Close(s_pkt);
         break;

      case IDCANCEL:              // Allows dialog box to close
         EndDialog(hwnd, id);
         break;
   }
}


//////////////////////////////////////////////////////////////////////////////


BOOL WINAPI KTTest_DlgProc (HWND hwnd, UINT uMsg,
   WPARAM wParam, LPARAM lParam) {

   switch (uMsg) {

      // Standard Window's messages
      HANDLE_DLGMSG(hwnd, WM_INITDIALOG, KTTest_OnInitDialog);
      HANDLE_DLGMSG(hwnd, WM_COMMAND,    KTTest_OnCommand);
   }
   return(FALSE);                 // We didn't process the message.
}


//////////////////////////////////////////////////////////////////////////////


int WINAPI WinMain (HINSTANCE hinstExe, HINSTANCE hinstPrev,
   LPSTR lpszCmdLine, int nCmdShow) {

   DialogBox(hinstExe, MAKEINTRESOURCE(IDD_KILLTHRDTEST), NULL,
      KTTest_DlgProc);

   return(0);
}


//////////////////////////////// End of File /////////////////////////////////
