
// dbgwnd.h : header file
//
// You should include this file in you main project header file after
// the stdafx header so that these definitions will be available in
// all modules.
//
// Now you can use the dprintf, dprintf1, dprintf2 and so on
// macros to add debug output
//

#ifndef __DBGWND__
#define __DBGWND__

/////////////////////////////////////////////////////////////////////////////
// CDbgWnd window

class CDbgWnd : public CWnd
{
public:
    CDbgWnd();
    ~CDbgWnd();
    void Create();
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
    afx_msg void OnDebug1();
    afx_msg void OnDebug2();
    afx_msg void OnDebug3();
    afx_msg void OnDebug4();
    afx_msg void OnDebugClear();
    afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
    afx_msg void OnDestroy();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

extern int dbgLevel;                          
extern void dbgSetLevel(int i);
extern void dbgOut(LPSTR lpFormat, ...);
extern DWORD dbgGetTime();
extern void dbgShowElapsedTime(LPSTR pMsg, DWORD dwStartTime);
extern void dbgDestroy();

#ifdef _DEBUG
    #define dprintf                     dbgOut
    #define dprintf1 if (dbgLevel >= 1) dbgOut
    #define dprintf2 if (dbgLevel >= 2) dbgOut
    #define dprintf3 if (dbgLevel >= 3) dbgOut
    #define dprintf4 if (dbgLevel >= 4) dbgOut
    #define ExitDebug() dbgDestroy()
#else // not _DEBUG
    #define dprintf  if (0) ((int (*)(char *, ...)) 0)
    #define dprintf1 if (0) ((int (*)(char *, ...)) 0)
    #define dprintf2 if (0) ((int (*)(char *, ...)) 0)
    #define dprintf3 if (0) ((int (*)(char *, ...)) 0)
    #define dprintf4 if (0) ((int (*)(char *, ...)) 0)
    #define ExitDebug()
#endif // _DEBUG

#endif // __DBGWND__
