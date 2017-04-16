// wordview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWordView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CWordView : public CFormView
{
    DECLARE_DYNCREATE(CWordView)
protected:
    CWordView();            // protected constructor used by dynamic creation

// Form Data
public:
    //{{AFX_DATA(CWordView)
    enum { IDD = IDD_WORDDLG };
    CButton m_wndTryit;
    CEdit   m_wndWord;
    CStatic m_wndScore;
    CString m_strWord;
    //}}AFX_DATA

// Attributes
public:

// Operations
public:
    CSpellerDoc* GetDocument()
        {return (CSpellerDoc*) CFormView::GetDocument();}

// Implementation
protected:
    virtual ~CWordView();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnInitialUpdate();
    virtual void OnUpdate(CView* pView, LPARAM lHint, CObject* pObj);


private:
    CFont m_fntEdit;        // font for the edit control
    CWave m_wavRight;
    CWave m_wavWrong;
    CWave m_wavSilence;
    CWave m_wavInstruct;
    CWave m_wavNoWords;
    int m_iRight;
    int m_iWrong;
    UINT m_uiTimer;

    void RestartTimer();

    // Generated message map functions
    //{{AFX_MSG(CWordView)
    afx_msg void OnClickedPlaysound();
    afx_msg void OnClickedTryit();
    afx_msg void OnDestroy();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnClickedHelp();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
