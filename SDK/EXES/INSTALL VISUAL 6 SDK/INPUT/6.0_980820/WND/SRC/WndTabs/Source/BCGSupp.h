/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


#ifndef __BCGSUPP_H
#define __BCGSUPP_H

// Hooks
void StopBCGHooks();
void ResetBCGHooks();


class CWTMenuBar : public CBCGMenuBar
{
	DECLARE_SERIAL(CWTMenuBar)

    //{{AFX_MSG(CWTMenuBar)
    afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
    virtual CSize CalcLayout(DWORD dwMode, int nLength = -1);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP();          

    CToolTipCtrl m_ToolTipCtrl;

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWTMenuBar)
	//}}AFX_VIRTUAL

public:
    void CalculateCustomizeButton();

    void DoTooltipRelay(CPoint& point);
    bool VerifyPointAndRelayTooltip(CPoint& point);
	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;

    bool WillCrashOnMultipleMonitors(CPoint pt);

    int m_nLastHit;
    CWnd *m_pLastHit;
};


class CMainFrameHolder : public CWnd
{
public:
    CFrameWnd *m_pWndMF;

    CMainFrameHolder() : CWnd(), m_pWndMF(NULL) {}
    void SetMF(CFrameWnd *pWndMF);

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMainFrameHolder)
	//}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CMainFrameHolder)
    afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP();
};



#endif // __BCGSUPP_H
