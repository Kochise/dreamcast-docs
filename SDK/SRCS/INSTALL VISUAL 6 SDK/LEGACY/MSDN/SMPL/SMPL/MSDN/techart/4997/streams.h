// streams.h

#ifndef __STREAMS_H__
#define __STREAMS_H__

/////////////////////////////////////////////////////////////////////////////

// CMainWindow:
// See streams.cpp for the code to the member functions and the message map.
//
class CMainWindow : public CFrameWnd
{
public:
    AudioStreamServices * m_pass;   // ptr to AudioStreamServices object
    AudioStream *m_pasCurrent;      // ptr to current AudioStream object
    
    CMainWindow();

    //{{AFX_MSG( CMainWindow )
    afx_msg void OnAbout();
    afx_msg void OnFileOpen();
    afx_msg void OnTestPlay();
    afx_msg void OnTestStop();
    afx_msg void OnUpdateTestPlay(CCmdUI* pCmdUI);
    afx_msg void OnUpdateTestStop(CCmdUI* pCmdUI);
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

// CTheApp:
// See hello.cpp for the code to the InitInstance member function.
//
class CTheApp : public CWinApp
{
public:
    virtual BOOL InitInstance();
};

/////////////////////////////////////////////////////////////////////////////

#endif // __STREAMS_H__
