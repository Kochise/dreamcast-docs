/*+==========================================================================
  File:      APPUTIL.H

  Summary:   Include file for the general application utility classes
             and functions offered by the APPUTIL library.  APPUTIL is
             meant to be statically linked to applications that want
             to exploit it.

             For a comprehensive tutorial code tour of APPUTIL's
             contents and offerings see the tutorial APPUTIL.HTM file.
             For more specific details on the internal workings see the
             comments dispersed throughout the APPUTIL source code.

  Classes:   CVirWindow, CVirDialog, CAboutBox, CDelayBox, CMsgBox, CMsgLog,
             CSendLog, CThreaded.

  Functions: WindowProc, DialogProc, SkipAnsi, FileExist, MakeFamilyPath,
             GetExeName, CmdExec, HrMsg, HrMsgId, ReadHelp, ReadTutorial,
             GoWeb, ReadSource, OutputDebugFmt, DComOk, lRandom, AnsiToUc,
             UcToAnsi, A_StringFromGUID2, A_WriteFmtUserTypeStg,
             A_StgIsStorageFile, A_StgCreateDocfile, A_StgOpenStorage,
             DelayBox, ErrorBox, CreateColorScalePalette, PaintWindow,
             GetErrorMsg.

  Origin:    8-28-97: atrent - Revised (based on WINHLPRS by stevebl).

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

// Don't allow recursive includes of this file.
#ifndef APPUTIL_H
#define APPUTIL_H


/*--------------------------------------------------------------------------
  The following pragma disables the C4355 warning which reads:

  "'this': used in base member initializer list."

  This warning is triggered by the nested interface implementation
  classes--a coding technique used throughout the sample series. The
  warning says: "The 'this' pointer is only valid within nonstatic member
  functions, but was used in the initializer list for a base class. This
  is a level 1 warning when Microsoft extensions are enabled (/Ze) but a
  level 4 warning otherwise."  The initializer technique is necessary for
  the coding of nested class interface implementations. See COMOBJ.HTM for
  details on the technique.
--------------------------------------------------------------------------*/
#pragma warning( disable : 4355 )


// Convenient typedefs.
#ifndef PPVOID
typedef LPVOID* PPVOID;
#endif


// Convenient macros.

#define DELETE_POINTER(p)\
{\
  if (NULL != p)\
  {\
    delete p;\
    p = NULL;\
  }\
}

#define RELEASE_INTERFACE(p)\
{\
  IUnknown* pTmp = (IUnknown*)p;\
  p = NULL;\
  if (NULL != pTmp)\
    pTmp->Release();\
}

// An enumeration of persistent storage states for use in the
// implementation of IPersistStorage.
typedef enum
{
  PERS_UNINIT = 0,  // Uninitialized.
  PERS_SCRIBBLE,    // Write     permitted; Read     permitted.
  PERS_NOSCRIBBLE,  // Write NOT permitted; Read     permitted.
  PERS_HANDSOFF     // Write NOT permitted; Read NOT permitted.
} PERSTGSTATE;

// PCRTTHREADPROC is a type for pointer variables that hold addresses of
// C-RunTime thread procedures.
typedef unsigned (WINAPI *PCRTTHREADPROC)(LPVOID pThreadProc);

#define GETINSTANCE(hWnd)   (HANDLE)GetWindowLong(hWnd,GWL_HINSTANCE)
#define GETCLASSBRUSH(hWnd) (HBRUSH)GetClassLong(hWnd,GCL_HBRBACKGROUND)


// Some General defines for Message Boxes and Dialogs
#define GUID_SIZE 128
#define MAX_STRING_LENGTH 256
#define MAXLOGST 128
#define MAX_LOG_LINES 500
#define DELAYBOX_DURATION 3000

#define COLOR_SCALE_RED     1
#define COLOR_SCALE_GREEN   2
#define COLOR_SCALE_BLUE    3
#define COLOR_SCALE_GRAY    4

#define EDITOR_EXE_STR "notepad.exe "
#define TUTORIAL_EXE_STR "tutorial.exe "
#define OFN_SOURCEFILES_STR "Source Files (*.CPP;*.H;*.RC;*.C;*.MAK;*.TXT;*.)\0*.CPP;*.H;*.RC;*.C;*.MAK;*.TXT;makefile\0"
#define OFN_SOURCETITLE_STR "Open Source File"
#define NOTICE_TITLE_STR "-Notice-"
#define ERROR_TITLE_STR "-Error-"
#define NOCOM_ERROR_STR "Can't Init COM."
#define NOEDITOR_ERROR_STR "Can't run editor."
#define NOTUTORIAL_ERROR_STR "Can't run tutorial."
#define NOTXT_ERROR_STR "Can't find .TXT file."
#define NOHTM_ERROR_STR "Can't find .HTM file."
#define NOBROWSE_ERROR_STR "Can't run browser."
#define ASSERTFAIL_ERROR_STR "Assertion Failed."
#define HELP_FILE_EXT    ".htm"
#define HTML_FILE_EXT    ".htm"
#define TXT_FILE_EXT     ".txt"
#define LICENSE_FILE_EXT ".lic"


#ifdef __cplusplus
// If compiling under C++ Ensure that Windows callbacks are
// undecorated extern C calls.
extern "C" {
#endif


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: WindowProc

  Summary:  Standard WindowProc callback function that forwards Windows
            messages on to the CVirWindow::WindowProc method.  This
            Window procedure expects that it will receive a "this"
            pointer as the lpCreateParams member passed as part of the
            WM_NCCREATE message.  It saves the "this" pointer in the
            GWL_USERDATA field of the window structure.

  Args:     HWND hWnd,
              Window handle
            UINT uMsg,
              Windows message
            WPARAM wParam,
              First message parameter (word sized)
            LPARAM lParam);
              Second message parameter (long sized)

  Returns:  LRESULT.  Windows window procedure callback return value.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
LRESULT CALLBACK WindowProc(
                   HWND hWnd,
                   UINT uMsg,
                   WPARAM wParam,
                   LPARAM lParam);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DialogProc

  Summary:  The general dialog procedure callback function.  Used by all
            CVirDialog class objects.  This procedure is the DialogProc
            registered for all dialogs created with the CVirDialog class.
            It uses the parameter passed with the WM_INITDIALOG message
            to identify the dialog classes' "this" pointer which it then
            stores in the window structure's GWL_USERDATA field.
            All subsequent messages can then be forwarded on to the
            correct dialog class's DialogProc method by using the pointer
            stored in the GWL_USERDATA field.

  Args:     HWND hWndDlg,
              Handle of dialog box.
            UINT uMsg,
              Message
            WPARAM wParam,
              First message parameter (word sized).
            LPARAM lParam);
              Second message parameter (long sized).

  Returns:  BOOL.  Return of the CVirDialog::DialogProc method.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
BOOL CALLBACK DialogProc(
                HWND hWndDlg,
                UINT uMsg,
                WPARAM wParam,
                LPARAM lParam);


#ifdef __cplusplus
}


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CVirWindow

  Summary:  Abstract base class for wrapping a window.

            This class allows a window to be cleanly wrapped in a
            c++ class.  Specifically, it provides a way for a c++ class
            to use one of its methods as a WindowProc, giving it a "this"
            pointer and allowing it to have direct access to all of its
            private members.

  Methods:  Create:
              Maps to Windows' CreateWindow function.
            WindowProc:
              Pure virtual WindowProc for the window.
            Gethwnd:
              Get the handle to the window.
            CVirWindow:
              Constructor.
            ~CVirWindow:
              Destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CVirWindow
{
public:
  // Constructor
  CVirWindow()
  {
    m_hInst = NULL;
    m_hWnd = NULL;
  };

  // Destructor
  virtual ~CVirWindow(){};

  // Envelopes the Windows' CreateWindow function call.
  HWND Create(
         LPTSTR lpszClassName,   // Address of registered class name
         LPTSTR lpszWindowName,  // Address of window name
         DWORD dwStyle,          // Window style
         int x,                  // Horizontal position of window
         int y,                  // Vertical position of window
         int nWidth,             // Window width
         int nHeight,            // Window height
         HWND hWndParent,        // Handle of parent or owner window
         HMENU hmenu,            // Handle of menu, or child window identifier
         HINSTANCE hinst);       // Handle of application instance

  // Get the protected handle of this window.
  HWND GetHwnd(void)
  {
    return(m_hWnd);
  }

  // WindowProc is a pure virtual member function and MUST be over-ridden
  // in any derived classes.
  virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

protected:
  // Application instance handle.
  HINSTANCE m_hInst;
  // Handle of this window.
  HWND m_hWnd;

  // Tell the compiler that the outside WindowProc callback is a friend
  // of this class and can get at its protected data members.
  friend LRESULT CALLBACK ::WindowProc(
                              HWND hWnd,
                              UINT uMsg,
                              WPARAM wParam,
                              LPARAM lParam);
};


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CVirDialog

  Summary:  Abstract base class for wrapping a Windows dialog box window.

            This class allows a dialog box to be cleanly wrapped in
            a c++ class.  Specifically, it provides a way for a c++ class
            to use one of its methods as a DialogProc, giving it a "this"
            pointer and allowing it to have direct access to all of its
            private members.

  Methods:  ShowDialog:
              Maps to Windows' DialogBox function.
            GetHwnd:
              Get the handle to the dialog window.
            DialogProc:
              Pure virtual DialogProc for the dialog box
            ~CVirDialog:
              Destructor
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CVirDialog
{
public:
  // Destructor
  virtual ~CVirDialog(){};

  // ShowDialog creates the Dialog (using the DialogBoxParam API).
  virtual int ShowDialog(
                HINSTANCE hInst,
                LPTSTR lpszTemplate,
                HWND hWndOwner);

  // DialogProc is a pure virtual member function and MUST be over-ridden
  // in any derived classes.
  virtual BOOL DialogProc(
                 HWND hWndDlg,
                 UINT uMsg,
                 WPARAM wParam,
                 LPARAM lParam) = 0;

protected:
  HINSTANCE m_hInst;
  HWND m_hWnd;

  // Tell the compiler that the outside DialogProc callback is a friend
  // of this class and can get at its protected data members.
  friend BOOL CALLBACK ::DialogProc(
                           HWND hWndDlg,
                           UINT uMsg,
                           WPARAM wParam,
                           LPARAM lParam);
};


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CAboutBox

  Summary:  A class that implements a common About Dialog Box
            functionality for the APPUTIL library.

  Methods:  DialogProc
              Dialog procedure
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CAboutBox: public CVirDialog
{
public:
  // This DialogProc method definition overrides the same-named pure
  // virtual function in abstract base class CVirDialog thus giving
  // AboutBox-unique message dispatching behavior to this derivation
  // of CVirDialog.  The remaining behavior of CAboutBox is inherited
  // from CVirDialog and is common to all CVirDialogs.
  BOOL DialogProc(
         HWND hWndDlg,
         UINT uMsg,
         WPARAM wParam,
         LPARAM lParam);
};


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CDelayBox

  Summary:  A class that implements a common Dialog Box functionality for
            the APPUTIL library. This dialog box has no buttons and and
            appears on screen for 8 seconds.

  Methods:  DialogProc
              Dialog procedure
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CDelayBox: public CVirDialog
{
public:
  // This DialogProc method definition overrides the same-named pure
  // virtual function in abstract base class CVirDialog thus giving
  // AboutBox-unique message dispatching behavior to this derivation
  // of CVirDialog.  The remaining behavior of CAboutBox is inherited
  // from CVirDialog and is common to all CVirDialogs.
  BOOL DialogProc(
         HWND hWndDlg,
         UINT uMsg,
         WPARAM wParam,
         LPARAM lParam);
};


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DelayBox

  Summary:  Uses the specified dialog template from the caller's resources
            and shows a buttonless dialog message box that remains on
            screen for about 3 seconds.

  Args:     HINSTANCE hInst,
              Handle of the module instance.  Needed to specify the
              module instance for fetching the dialog template resource
              (ie, from either a host EXE or DLL).
            LPTSTR pszTemplate,
              Identifies the dialog box template.
            HWND hwndOwner)
              Handle of the owner window. NULL for desktop.

  Returns:  void
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
void DelayBox(
      HINSTANCE hInst,
      LPTSTR pszTemplate,
      HWND hWndOwner);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: ErrorBox

  Summary:  The ErrorBox function displays an error message dialog box. It
            displays an error message string in the dialog that is
            specified in the call by a resource ID.

  Args:     HINSTANCE hInst,
              Handle of the module instance.  Needed to specify the
              module instance for fetching the specified string resource.
            HWND hwndOwner,
              Handle of the owner window. NULL for desktop.
            INT iStringID
              Resource ID of the error message sting.

  Returns:  void
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
void ErrorBox(
      HINSTANCE hInst,
      HWND hWndOwner,
      INT iStringID);


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CMsgBox

  Summary:  Class for showing messages in a Message Box dialog.  Uses the
            standard Windows MessageBox function but retrieves the box
            title and message strings from the application's resources
            using specified resource IDs.  These message boxes have only
            an OK button.

  Methods:  Init
              Initializes the owner window and the module instance.
            Error
              Shows a message string in an Error MessageBox Dialog.
            ErrorID
              Shows a resource message string in an Error MessageBox Dialog.
            Note
              Shows a message string in a Notice MessageBox Dialog.
            NoteID
              Shows a resource message string in a Notice MessageBox Dialog.
            NoteFmt
              Shows a printf-style formatted message string in a Notice
              MessageBox Dialog.
            NoteFmtID
              Shows a printf-style formatted resource message string in a
              Notice MessageBox Dialog.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CMsgBox
{
public:
  // Constructor.
  CMsgBox()
  {
    m_hInst = 0;
    m_hWndOwner = 0;
  };

  BOOL Init(HINSTANCE hInst, HWND hWndOwner);
  int  Error(LPTSTR szMsg);
  int  ErrorID(UINT uMsgID);
  int  Note(LPTSTR szMsg);
  int  NoteID(UINT uMsgID);
  int  NoteFmt(LPTSTR szFmtMsg, ...);
  int  NoteFmtID(UINT uMsgID, ...);

private:
  // Remember the App Instance Handle.
  HINSTANCE m_hInst;
  // Remember the Owner Window Handle.
  HWND m_hWndOwner;
};


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CMsgLog

  Summary:  Class for logging messages to a Listbox.  This is for tutorial
            code samples that employ debug messages to announce internal
            activity in the code being studied.  When used, this Message
            Log listbox occupies the entire client area of the parent
            window.  The various message output functions use string
            resource IDs to retrieve the message strings from the app's
            resources.

  Methods:  Create
              Creates the Trace Message Log ListBox window.
            Logging
              Toggles logging on or off.
            Msg
              Logs a message as a separate line.
            MsgFmt
              Logs a printf-style formated message as a separate line.
            Resize
              Resizes the listbox to a new width and height.
            Clear
              Clears all logged messages from the message log.
            CMsgLog
              Constructor.
            ~CMsgLog
              Destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CMsgLog
{
public:
  // Constructor.
  CMsgLog()
  {
    m_hInstLog = 0;
    m_hWndLog = 0;
    m_bChild = FALSE;
    m_bLogging = FALSE;
    m_hLogData = 0;
  };

  BOOL Create(HINSTANCE hInst, HWND hWndParent, BOOL bChild);
  BOOL Logging(BOOL bLogging);
  BOOL Msg(LPTSTR szMsg);
  BOOL MsgFmt(LPTSTR szFmtMsg, ...);
  BOOL MsgID(int iMsgID);
  BOOL MsgFmtID(int iFmtID, ...);
  BOOL Resize(int nWidth, int nHeight);
  BOOL Clear(void);
  BOOL Copy(void);

private:
  // Remember the App Instance Handle.
  HINSTANCE m_hInstLog;
  // Remember the handle of the listbox window.
  HWND m_hWndLog;
  // Remember if CMsgLog was created as child window.
  BOOL m_bChild;
  // Remember whether logging or not.
  BOOL m_bLogging;
  // Remember the global handle to clipboard data.
  HGLOBAL m_hLogData;
};


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CSendLog

  Summary:  Class for logging messages to a CMsgLog facility in another
            application process. This is for tutorial code samples that
            employ debug messages to announce internal activity in the
            code being studied.  Uses the WM_COPYDATA message of the
            Win32 SendMessage API.

  Methods:  CreateServerLog
              Initializes the SendLog facility and creates the Trace
              Message Log ListBox window shown in the local server app.
            SetClient
              Sets destination client window handle.
            LogToServer
              Set whether logging is to local server or to client.
            Msg
              Logs a message as a separate line.
            MsgFmt
              Logs a printf-style formated message as a separate line.
            Resize
              Resizes the listbox to a new width and height.
            Clear
              Clears all logged messages from the message log.
            CSendLog
              Constructor.
            ~CSendLog
              Destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CSendLog
{
public:
  // Constructor.
  CSendLog()
  {
    m_hInstSender = 0;
    m_hWndSender = 0;
    m_hWndReceiver = 0;
    m_hWndListBox = 0;
    m_bLogToServer = FALSE;
    m_bChild = FALSE;
    m_hLogData = 0;
  };

  BOOL CreateServerLog(HINSTANCE hInst, HWND hWndParent, BOOL bChild);
  BOOL SetClient(HINSTANCE hInstSender, HWND hWndSender, HWND hWndReceiver);
  BOOL LogToServer(BOOL bLogToServer);
  BOOL Msg(LPTSTR szMsg);
  BOOL MsgFmt(LPTSTR szFmtMsg, ...);
  BOOL MsgID(int iMsgID);
  BOOL MsgFmtID(int iFmtID, ...);
  BOOL Resize(int nWidth, int nHeight);
  BOOL Clear(void);
  BOOL Copy(void);

private:
  // Remember the Sender App Instance Handle.
  HINSTANCE m_hInstSender;
  // Remember the handle of the sending application main window.
  HWND m_hWndSender;
  // Remember the handle of the destination receiving window.
  HWND m_hWndReceiver;
  // Remember the handle of the server's listbox window.
  HWND m_hWndListBox;
  // Boolean for logging to client or logging to server.
  BOOL m_bLogToServer;
  // Remember if CMsgLog was created as child window.
  BOOL m_bChild;
  // Remember the global handle to clipboard data.
  HGLOBAL m_hLogData;
};


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CThreaded

  Summary:  Derive a class from this class to provide multi-threaded
            access to objects of the derived class. This is a utility
            base class providing useful methods for achieving mutually
            exclusive access to data in objects of the derived class.

  Methods:  OwnThis
              Blocks executing thread until access to this object is
              permitted at which point the thread "owns" this object.
            UnOwnThis
              Executed by owning thread to relinquish ownership of
              this object.
            CThreaded
              Constructor. Creates mutex to govern mutually exclusive
              access to data in this object by multiple threads.
            ~CThreaded
              Destructor. Destroys mutex.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CThreaded
{
  protected:
    // Variables for providing mutually exclusive access by multiple
    // threads to objects of classes derived from this class.
    HANDLE m_hOwnerMutex;
    BOOL   m_bOwned;

  public:
    // Methods.
    CThreaded(void) :
      m_hOwnerMutex(CreateMutex(0,FALSE,0)),
      m_bOwned(FALSE)
    {
    };

    ~CThreaded(void)
    {
      // Close down the mutex.
      CloseHandle(m_hOwnerMutex);
    };

    // The following virtual functions have overriding definitions in
    // the derived class to provide convenient trace logging. Rely on
    // the below default definitions for non-tutorial applications.

    virtual BOOL OwnThis(void)
    {
      BOOL bOwned = FALSE;

      if (WAIT_OBJECT_0 == WaitForSingleObject(m_hOwnerMutex, INFINITE))
        m_bOwned = bOwned = TRUE;

      return bOwned;
    };

    virtual void UnOwnThis(void)
    {
      if (m_bOwned)
      {
        m_bOwned = FALSE;
        ReleaseMutex(m_hOwnerMutex);
      }

      return;
    };
};


#endif //__cplusplus



/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: AnsiToUc

  Summary:  Convert an ANSI 'multibyte' string into a UNICODE 'wide
            character' string.

  Args:     LPSTR pszAnsi
              Pointer to a caller's input ANSI string.
            LPWSTR pszUc
              Pointer to a caller's output UNICODE wide string.
            int cch
              Character count. If 0 then use length of pszAnsi.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
HRESULT AnsiToUc(
          LPSTR pszAnsi,
          LPWSTR pszUc,
          int cch);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: UcToAnsi

  Summary:  Convert a UNICODE 'wide character' input string to an output
            ANSI 'multi-byte' string.

  Args:     LPWSTR pwszUc
              Pointer to a caller's input UNICODE wide string.
            LPSTR pszAnsi
              Pointer to a caller's output ANSI string.
            int cch
              Character count. If 0 then use length of pwszUc.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
HRESULT UcToAnsi(
          LPWSTR pwszUc,
          LPSTR pszAnsi,
          int cch);


/*---------------------------------------------------------------------------
  Here are some surrogate API macro prototypes--all names begin with A_.
  These are for use when the code sample is being compiled for ANSI
  strings (the default) and the calls they stand in place of only support
  UNICODE (thus forcing some string conversions from ANSI to UNICODE
  before the real call is made inside the surrogate). For example, if
  UNICODE is NOT defined during the compile then any calls in the samples
  to the StringFromGUID2 function are actually changed (by the below
  macros) into calls to an A_StringFromGUID2 function implemented in
  APPUTIL. This function accepts the ANSI input string pointer, calls the
  actual StringFromGUID2 call, and does the necessary Unicode to ANSI
  conversion. Other A_ calls will convert input ANSI strings to Unicode
  strings prior to calling the actual COM/OLE function.
---------------------------------------------------------------------------*/
#if !defined(UNICODE)

STDAPI A_StringFromGUID2(REFGUID, LPSTR, int);

STDAPI A_WriteFmtUserTypeStg(IStorage*, CLIPFORMAT, LPSTR);

STDAPI A_StgIsStorageFile(LPSTR);
STDAPI A_StgCreateDocfile(LPSTR, DWORD, DWORD, IStorage**);
STDAPI A_StgOpenStorage(LPSTR, IStorage*, DWORD, SNB, DWORD, IStorage**);

#if !defined(_NOANSIMACROS_)

#undef StringFromGUID2
#define StringFromGUID2(a, b, c) A_StringFromGUID2(a, b, c)

#undef WriteFmtUserTypeStg
#define WriteFmtUserTypeStg(a, b, c) A_WriteFmtUserTypeStg(a, b, c)

#undef StgIsStorageFile
#define StgIsStorageFile(a) A_StgIsStorageFile(a)

#undef StgCreateDocfile
#define StgCreateDocfile(a, b, c, d) A_StgCreateDocfile(a, b, c, d)

#undef StgOpenStorage
#define StgOpenStorage(a, b, c, d, e, f) A_StgOpenStorage(a, b, c, d, e, f)

#endif

#endif


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DComOk

  Summary:  Determine if DCOM (Distributed COM) can be used. It can if it
            is installed and is enabled on the current machine.

  Args:     void

  Returns:  BOOL
              TRUE - DCOM installed and enabled; FALSE - NOT.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
BOOL DComOk(void);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: lRandom

  Summary:  Simple random number generator. Returns a random DWORD.

  Args:     void

  Returns:  DWORD
              Random number.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
DWORD lRandom(void);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: CreateColorScalePalette

  Summary:  This function creates a palette representing the scale values
            of a particular RGB color.  A gray-scale palette can also be
            created.

  Args:     HDC hDC,
              Handle to device context.
            int nColor
              New color.

  Returns:  HPALETTE
              Handle to new pallete.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
HPALETTE CreateColorScalePalette(HWND hDC, int nColor);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: PaintWindow

  Summary:  This function is used to wash the background of a window.

  Args:     HWND hWnd,
              Window handle.
            int nColor
              New window color.

  Returns:  void.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
VOID PaintWindow(HWND hWnd, int nColor);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: SkipAnsi

  Summary:  Utility function to scan an input ANSI string and either skips
            white characters or skips non-white characters.

  Args;     LPSTR psz,
              Input ANSI string to be scanned.
            BOOL bSkip)
              Input boolean determining whether to skip white space
              or not.  TRUE means skip white space; FALSE means skip
              non-white chars.

  Returns:  LPSTR
              String pointer after the skip (ANSI)
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
LPSTR SkipAnsi(
         LPSTR psz,
         BOOL bSkipWhite);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: FileExist

  Summary:  Function to test for the existance of a file.

  Args:     TCHAR* szFileName
              String pointer to file's path/name.

  Returns:  BOOL.  TRUE if file exists; FALSE if not.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
BOOL FileExist(TCHAR *szFileName);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: MakeFamilyPath

  Summary:  Function to make a family file/path/name string using the
            detetected pathname of the current executable module.

  Args:     HINSTANCE hInst
              Handle to the module intstance.
            TCHAR* pszNewPath
              String pointer to the new path/name.
            TCHAR* pszFileExt
              String pointer to the filename extension for the new path.

  Returns:  BOOL.  TRUE if success; FALSE if not.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
BOOL MakeFamilyPath(
       HINSTANCE hInst,
       TCHAR* pszNewPath,
       TCHAR* pszFileExt);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: GetExeName

  Summary:  Function to get the executable file name of the current
            module. Makes names like: MyApp.EXE or MyDll.DLL.

  Args:     HINSTANCE hInst
              Handle to the module intstance.
            TCHAR* pszExeName
              String pointer to the new executable file name.
              A char string allocated by user.

  Returns:  BOOL.  TRUE if success; FALSE if not.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
BOOL GetExeName(
       HINSTANCE hInst,
       TCHAR* pszExeName);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: CmdExec

  Summary:  Execute an EXE Win32 program by creating a process and
            running the specified EXE in it.  A Unicode version of
            WinExec that always has SW_SHOW.

  Args:     LPTSTR szCmd,
              Entire command line (eg, "notepad.exe mytext.txt")

  Returns:  BOOL
              TRUE if succeed; FALSE if fail.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
BOOL CmdExec(
       LPTSTR szCmd);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: HrMsg

  Summary:  HRESULT Error Message box. Takes standard result code,
            looks it up in the system tables, and shows a message
            box with the error code (in hex) and the associated
            system message.

  Args:     HWND hWndOwner,
              Handle to owner parent window.
            LPTSTR pszTitle
              User message string (eg, designating the attempted function).
              Appears in the dialog title bar.
            HRESULT hr
              Standard return code.

  Returns:  void
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
void HrMsg(
       HWND hWndOwner,
       LPTSTR pszTitle,
       HRESULT hr);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: HrMsgId

  Summary:  HRESULT Error Message box using string resource ID. Takes
            standard result code, looks it up in the system tables, and
            shows a message box with the error code (in hex) and the
            associated system message. An additional user message string
            (specified as a resource ID) is also shown.

  Args:     HINSTANCE hInst,
              Handle of the module instance.  Needed to specify the
              module instance for fetching the specified string resource.
            HWND hwndOwner,
              Handle of the owner window. NULL for desktop.
            INT iStringID
              Resource ID of error message string. Appears in the
              dialog title bar.
            HRESULT hr,
              Standard result code.

  Returns:  void
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
void HrMsgId(
      HINSTANCE hInst,
      HWND hWndOwner,
      INT iStringID,
      HRESULT hr);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: ReadHelp

  Summary:  The ReadHelp function is a general help reader for
            applications. It uses the shell to run the reader application
            associated with the extension of the specified file/path name.
            For example, if the family-named file name is MYAPP.HTM, then
            the web browser will be used to read the HTML help file.

  Args:     HWND hWndOwner,
              Handle to owner parent window.
            LPTSTR pszHelpFile,
              Pointer to the help file/path name string.

  Returns:  void
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
void ReadHelp(
       HWND hWndOwner,
       LPTSTR pszHelpFile);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: ReadTutorial

  Summary:  The ReadTutorial function is for use by tutorial code sample
            applications that study themselves. This function uses simple
            Hyperlinking to launch the web browser to read an HTML web
            page that contains a tutorial covering the sample. If no HTM
            file (in a sibling or parent directory) is specified, this
            function assumes a family-named <sample>.HTM tutorial HTML
            file that is located next to the main .EXE file of the
            application calling ReadTutorial. "Family-named" means that if
            the EXE program calling this function is MYAPP.EXE then the
            associated family-named HTML file is constructed as MYAPP.HTM.

  Args:     HINSTANCE hInst,
              Handle of the executable module instance.
            HWND hWndOwner,
              Handle to owner parent window.
            LPTSTR pszHTMLFile,
              Pointer to an optional HTML FileName string. If this pointer
              is NULL, then the family-named file is assumed for the HTML
              file and is assumed to be located next to the main .EXE file
              of the program executing this function. Non-NULL values are
              of the form "MySiblingDirectory\MyHTMLFile.HTM" or of the
              form "MyHTMLFileInTheParentDirectory.HTM". Special non-NULL
              values beginning with '.' (eg. ".HTM" or ".ASP") specify
              that the family-named file is assumed to be located in the
              parent directory. In this case, the specified file extension
              is used.

  Returns:  void
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
void ReadTutorial(
       HINSTANCE hInst,
       HWND hWndOwner,
       LPTSTR pszHTMLFile);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: GoWeb

  Summary:  General utility function to launch a web browser on a
            specified HTML file via either a URL or a full file path/name.

  Args:     HINSTANCE hInst,
              Handle of the executable module instance.
            LPSTR pszTarget
              Pointer to the Target specification string (must be ANSI).
              If null then call the ReadTutorial function. If pszTarget
              starts with '//' then the target is assumed to be a www URL
              trailer of the form: //www.microsoft.com. If any other
              string, then it is assumed to be a full path/file name.

  Returns:  void
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
void GoWeb(
       HINSTANCE hInst,
       LPSTR pszTarget);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: ReadSource

  Summary:  For use by code sample applications that study themselves
            as it were.  This function allows you to select one of the
            source files of this code sample and launch a reader to
            edit/read it.  NOTEPAD.EXE is the default editor/reader.
            You can change this by changing EDITOR_FILE_STR in
            APPUTIL.H above.

  Args:     HWND hWndOwner
              Handle of parent window.
            OPENFILENAME* pofn,
              Pointer to the Open File Name Common Dialog structure.

  Returns:  void
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
void ReadSource(
       HWND hWndOwner,
       OPENFILENAME* pOfn);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: OutputDebugFmt

  Summary:  Wraps the Win32 OutputDebugString API call to provide
            printf-style formatted (and variable argument) output.

  Args:     LPTSTR szFmt,
              Format string.
            [...]
              Arguments to match those specified in the format string.

  Returns:  void
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
void OutputDebugFmt(
       LPTSTR szFmt,
       ...);


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: GetErrorMsg

  Summary:  Accepts a Win32 error code and retrieves a human readable
            system message for it.

  Args:     HRESULT hr
              SCODE error code.
            LPTSTR pszMsg
              Pointer string where message will be placed.
            UINT uiSize
              Max size of the msg string.

  Returns:  BOOL
              TRUE if hr was error; FALSE if not.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
BOOL GetErrorMsg(
       HRESULT hr,
       LPTSTR pszMsg,
       UINT uiSize);


#define TID GetCurrentThreadId()

#if defined(DEBUG)

//Basic debug and logging macros

// Output debug string; literal or variable.
#define ODS(sMsg) \
{\
  TCHAR szDebug[MAXLOGST];\
  OutputDebugFmt(TEXT("%s"),TEXT(sMsg));\
  wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
  OutputDebugString(szDebug);\
}

// Output debug string formatted; one argument.
#define ODF1(sFmt,x) \
{\
  TCHAR szDebug[MAXLOGST];\
  OutputDebugFmt(TEXT(sFmt),x);\
  wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
  OutputDebugString(szDebug);\
}

// Output debug string formatted; two argument.
#define ODF2(sFmt,x,y) \
{\
  TCHAR szDebug[MAXLOGST];\
  OutputDebugFmt(TEXT(sFmt),x,y);\
  wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
  OutputDebugString(szDebug);\
}

// Output debug string formatted; three argument.
#define ODF3(sFmt,x,y,z) \
{\
  TCHAR szDebug[MAXLOGST];\
  OutputDebugFmt(TEXT(sFmt),x,y,z);\
  wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
  OutputDebugString(szDebug);\
}

// Check condition and Output assertion failed message to debugger.
#define ASSERT(condition) \
{\
  if (!(condition))\
    ODS(TEXT("Assertion Failed"));\
}

// Check standard HRESULT for error and put up message box if error.
// Two arguments. Pfx = Prefix msg string; Ec = error code.
// Eg: CKHR("MyFunction:",hr);
#define CKHR(Pfx,Ec) \
{\
  TCHAR szMsg[MAX_PATH];\
  if (GetErrorMsg(Ec,szMsg,MAX_PATH))\
  {\
    HrMsg(NULL,TEXT(Pfx),Ec);\
    wsprintf(szMsg, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
    OutputDebugString(szMsg);\
  }\
}

// Log debug string (output both to Message Log and to Debugger)
#define LOG(sMsg) \
{\
  TCHAR szDebug[MAXLOGST];\
  if (NULL!=g_pMsgLog)\
    g_pMsgLog->Msg(TEXT(sMsg));\
  wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
  OutputDebugString(szDebug);\
}

// Log debug string (output both to Message Log and to Debugger).
// One argument.
#define LOGF1(sFmt,x) \
{\
  TCHAR szDebug[MAXLOGST];\
  if (NULL!=g_pMsgLog)\
    g_pMsgLog->MsgFmt(TEXT(sFmt),x);\
  wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
  OutputDebugString(szDebug);\
}

// Log debug string (output both to Message Log and to Debugger).
// Two argument.
#define LOGF2(sFmt,x,y) \
{\
  TCHAR szDebug[MAXLOGST];\
  if (NULL!=g_pMsgLog)\
    g_pMsgLog->MsgFmt(TEXT(sFmt),x,y);\
  wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
  OutputDebugString(szDebug);\
}

// Log debug string (output both to Message Log and to Debugger).
// Three argument.
#define LOGF3(sFmt,x,y,z) \
{\
  TCHAR szDebug[MAXLOGST];\
  if (NULL!=g_pMsgLog)\
    g_pMsgLog->MsgFmt(TEXT(sFmt),x,y,z);\
  wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
  OutputDebugString(szDebug);\
}

// Log error message string (output both to Message Log and to Debugger).
// Two arguments. Pfx = Prefix msg string; Ec = error code.
// Eg: LOGERROR("MyFunction:",hr);
#define LOGERROR(Pfx,Ec) \
{\
  TCHAR szMsg[MAX_PATH];\
  if (NULL!=g_pMsgLog && GetErrorMsg(Ec,szMsg,MAX_PATH))\
  {\
    g_pMsgLog->MsgFmt(TEXT("%s Error=0x%X: %s"),TEXT(Pfx),Ec,szMsg);\
    wsprintf(szMsg, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
    OutputDebugString(szMsg);\
  }\
}

// Log debug string (output both to Message Log and to Debugger).
// Use a string resource ID to retrieve the display string.
#define LOGID(id) \
{\
  TCHAR szDebug[MAXLOGST];\
  if (NULL!=g_pMsgLog)\
    g_pMsgLog->MsgID(id);\
  wsprintf(szDebug, TEXT(" [%s, %u]\r\n"), (LPTSTR)__FILE__, __LINE__);\
  OutputDebugString(szDebug);\
}

// Log assertion failure.
#define LOGASSERT(condition) \
{\
  if (!(condition))\
    LOGID(IDS_ASSERT_FAIL);\
}

#else  // !defined(DEBUG)

#define ODS(x)

#define ODF1(sFmt,x)

#define ODF2(sFmt,x,y)

#define ODF3(sFmt,x,y,z)

#define ASSERT(condition)

#define CKHR(Pfx,Ec)

#define LOG(sMsg) \
{\
  if (NULL!=g_pMsgLog)\
    g_pMsgLog->Msg(TEXT(sMsg));\
}

// Log debug string (output both to Message Log and not to Debugger).
// One argument.
#define LOGF1(sFmt,x) \
{\
  if (NULL!=g_pMsgLog)\
    g_pMsgLog->MsgFmt(TEXT(sFmt),x);\
}

// Log debug string (output both to Message Log and not to Debugger).
// Two argument.
#define LOGF2(sFmt,x,y) \
{\
  if (NULL!=g_pMsgLog)\
    g_pMsgLog->MsgFmt(TEXT(sFmt),x,y);\
}

// Log debug string (output both to Message Log and not to Debugger).
// Three argument.
#define LOGF3(sFmt,x,y,z) \
{\
  if (NULL!=g_pMsgLog)\
    g_pMsgLog->MsgFmt(TEXT(sFmt),x,y,z);\
}

// Log error message string (output both to Message Log and not to Debugger).
// Two arguments. Pfx = Prefix msg string; Ec = error code.
// Eg: LOGERROR("MyFunction:",hr);
#define LOGERROR(Pfx,Ec) \
{\
  TCHAR szMsg[MAX_PATH];\
  if (NULL!=g_pMsgLog && GetErrorMsg(Ec,szMsg,MAX_PATH))\
    g_pMsgLog->MsgFmt(TEXT("%s Error=0x%X: %s"),TEXT(Pfx),Ec,szMsg);\
}

// Log debug string (output both to Message Log and not to Debugger).
// Use a string resource ID to retrieve the display string.
#define LOGID(id) \
{\
  if (NULL!=g_pMsgLog)\
    g_pMsgLog->MsgID(id);\
}

// Log assertion failure.
#define LOGASSERT(condition)\
{\
  if (!(condition))\
    LOGID(IDS_ASSERT_FAIL);\
}

#endif // DEBUG

#endif //APPUTIL_H
