// ddlstbox.h : header file
//

#ifndef __DDLSTBOX__
#define __DDLSTBOX__

/////////////////////////////////////////////////////////////////////////////
// CDDListBox window

class CDDListBox : public CListBox
{
public:
    CDDListBox();
    virtual ~CDDListBox();

private:
    int IndexFromPoint(CPoint point);
    void UpdateSelection(int iSel, UINT nFlags, CPoint point);

    CPoint m_ptMouseDown;
    int m_iFirstIndex;
    BOOL m_bMouseOpPending;
    BOOL m_bCaptured;

    // Generated message map functions
protected:
    //{{AFX_MSG(CDDListBox)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg LRESULT OnQueryDrop(WPARAM wParam,LPARAM lParam);
    afx_msg LRESULT OnDoDrop(WPARAM wParam,LPARAM lParam);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif // __DDLSTBOX__
