
// dbgwnd.h : header file
//
// You should include this file in you main project header file after
// the stdafx header so that these definitions will be available in
// all modules.
// The app main CPP file should include:
//
//      CDbgWnd theDbgWnd;      // debug window
//      int theDbgLevel;        // debug level
//
// right after the line which says:
//
//      CAnimApp NEAR theApp; 
//
// During InitInstance you need to include:
//
//      // Create the debug window
//      theDbgWnd.Create();
//      dprintf("Started");
//
// You need to add an ExitInstance routine:
//
//  int CAnimApp::ExitInstance()
//  {
//      theDbgWnd.DestroyWindow();
//      return CWinApp::ExitInstance();
//  }
//
// Now you can use the dprintf, dprintf1, dprintf2 and so on
// macros to add debug output
//

#ifndef __DBGWND__
#define __DBGWND__

// local defines
#define IDC_LIST    1
#define MAXLISTLINES    100

/////////////////////////////////////////////////////////////////////////////
// CDbgWnd window

class CDbgWnd : public CWnd
{
public:
    CDbgWnd();
    ~CDbgWnd();
    void Create();
    void SetDebugLevel(int i);
    void DbgOut(LPSTR lpFormat, ...);

protected:
    CListBox m_wndList;         // listbox

    // Generated message map functions
    //{{AFX_MSG(CDbgWnd)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnDebug0();
    afx_msg void OnUpdateDebug0(CCmdUI* pCmdUI);
    afx_msg void OnDebug1();
    afx_msg void OnUpdateDebug1(CCmdUI* pCmdUI);
    afx_msg void OnDebug2();
    afx_msg void OnUpdateDebug3(CCmdUI* pCmdUI);
    afx_msg void OnUpdateDebug2(CCmdUI* pCmdUI);
    afx_msg void OnDebug3();
    afx_msg void OnDebug4();
    afx_msg void OnUpdateDebug4(CCmdUI* pCmdUI);
    afx_msg void OnDebugClear();
    afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
    afx_msg void OnDestroy();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

extern CDbgWnd theDbgWnd;
extern int theDbgLevel;
extern DWORD dbgGetTime();
extern void dbgShowElapsedTime(LPSTR pMsg, DWORD dwStartTime);

#ifdef _DEBUG
    #define dprintf                        theDbgWnd.DbgOut
    #define dprintf1 if (theDbgLevel >= 1) theDbgWnd.DbgOut
    #define dprintf2 if (theDbgLevel >= 2) theDbgWnd.DbgOut
    #define dprintf3 if (theDbgLevel >= 3) theDbgWnd.DbgOut
    #define dprintf4 if (theDbgLevel >= 4) theDbgWnd.DbgOut
#else // not _DEBUG
    #define dprintf  if (0) ((int (*)(char *, ...)) 0)
    #define dprintf1 if (0) ((int (*)(char *, ...)) 0)
    #define dprintf2 if (0) ((int (*)(char *, ...)) 0)
    #define dprintf3 if (0) ((int (*)(char *, ...)) 0)
    #define dprintf4 if (0) ((int (*)(char *, ...)) 0)
#endif // _DEBUG




#endif // __DBGWND__
