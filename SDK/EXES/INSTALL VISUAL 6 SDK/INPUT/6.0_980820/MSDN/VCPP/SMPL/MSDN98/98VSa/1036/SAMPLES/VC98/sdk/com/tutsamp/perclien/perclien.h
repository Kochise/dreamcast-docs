/*+==========================================================================
  File:      PERCLIEN.H

  Summary:   Include file for the PERCLIEN code sample application. Has
             class definitions for the the main window and dialogs.

             For a comprehensive tutorial code tour of PERCLIEN's contents
             and offerings see the tutorial PERCLIEN.HTM file. For more
             specific technical details on the internal workings see the
             comments dispersed throughout the PERCLIEN source code.

  Classes:   CMainWindow.

  Functions: WinMain.

  Origin:    5-25-97: atrent - Editor-inheritance from STOCLIEN source.

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

#if !defined(PERCLIEN_H)
#define PERCLIEN_H

#ifdef __cplusplus


extern TCHAR g_szPageTitle[];

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CMainWindow

  Summary:  Class to encapsulate the application's main window, menu, and
            message dispatching behavior. Derives from and extends
            APPUTIL's CVirWindow class.

  Methods:  CMainWindow
              Constructor.
            ~CMainWindow
              Destructor.
            BOOL InitInstance(
                   HINSTANCE hInst,
                   LPSTR pszCmdLine,
                   int nCmdShow);
              Creates a new instance of the main window.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CMainWindow: public CVirWindow
{
  public:
    CMainWindow();
    ~CMainWindow();
    BOOL InitInstance(HINSTANCE hInst, LPSTR pszCmdLine, int nCmdShow);

    TCHAR m_szFileName[MAX_PATH];
    CGuiList*  m_pGuiList;

  protected:
    LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

  private:
    LRESULT DoCommand(WPARAM wParam, LPARAM lParam);

    WORD m_wWidth;
    WORD m_wHeight;
    TCHAR m_szFileTitle[MAX_PATH];
    TCHAR m_szHelpFile[MAX_PATH];
    TEXTMETRIC m_tm;
    OPENFILENAME m_ofnFile;
};


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CDlgPageProps

  Summary:  Class to encapsulate the Page Properties entry Dialog. This
            currently edits a new title for a page. Derived from APPUTIL's
            CVirDialog.

  Methods:  DialogProc
              Dialog procedure
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CDlgPageProps: public CVirDialog
{
public:
  BOOL DialogProc(
         HWND hWndDlg,
         UINT uMsg,
         WPARAM wParam,
         LPARAM lParam);
};


#endif // __cplusplus


#endif
