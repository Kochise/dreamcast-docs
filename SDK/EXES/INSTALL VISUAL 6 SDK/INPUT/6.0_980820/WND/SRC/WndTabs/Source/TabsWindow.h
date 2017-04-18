/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// TabsWindow.h : header file
//

#if !defined(AFX_TABSWINDOW_H__6A06C13B_4748_11D1_BC91_0000010016A6__INCLUDED_)
#define AFX_TABSWINDOW_H__6A06C13B_4748_11D1_BC91_0000010016A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BCGSupp.h"
#include "FancyTabCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CTabsWindow window

class CCommands;

struct WTSDK_CommandContext;


class CTabsWindow : public CReBar
{
    friend class CTabManagerWindow;

// Construction
public:
    CTabsWindow(CCommands* pCommands);

// Attributes
public:
    CFancyTabCtrl *     m_pTabCtrl;
    int                 m_iLockUpdates;
    bool                m_bAboutToUpdate;
    IApplication *      m_pApplication;
    CCommands *         m_pCommands;
    CMainFrameHolder    m_mfh;
    CPen                m_penShadowTop;
    CPen                m_penShadowBottom;
    bool                m_bIsWTTab;

// Operations
public:
	void Reorder();
	void Renumber();

    void UpdateReBar();

    void ForceTabUpdate();

    void ApplyWindowLimit();

    bool GetDocumentObject(
        CComPtr<IGenericWindow> pWindow,
        CComPtr<IGenericDocument>& pDoc);

    void ResyncActiveTab();

	bool FindDSWindow(int iSel, IGenericWindow **ppWindow, HWND *phWnd = NULL);
    bool FindDSWindow(HWND hWnd, IGenericWindow **ppWindow);
	void ActivateWindow(HWND hWnd, bool bZoomOnly = false);

    bool UpdateCommandContext(int iTab);
    bool UpdateCommandContext(CPoint ptHitTest);
    bool GetCommandContext(int iTab, WTSDK_CommandContext& ctx);
    bool CheckRowCount();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTabsWindow)
	//}}AFX_VIRTUAL

// Implementation
public:
	void ActivateTab(int iIndex);
	void UpdateStyle();
    virtual ~CTabsWindow();

    struct tabdata_t
    {
        HWND    hWnd;       // corresponding window
        CString cTitle;     // window title (file path)
        CString cPath;      // (file path)
        CString cName;      // mangled name
        int     iNumber;    // displayed tab number
        int     iIndex;     // index in tab control
        CComPtr<IGenericWindow>    pWindow;
        CComPtr<IGenericDocument>  pDoc;

        void UpdatePath();
    };

	tabdata_t * GetTabData(int iTabIndex);

    typedef void (* pfnWndCmd)(HWND);
    void DoForGroup(pfnWndCmd cmdfn, int iTab = -1, boolean bInverse = false);
    
    // Generated message map functions
protected:
    void MangleName(CString& sPathIn, CString& sNameIn, 
        int iNum, CString &sNameOut);

    //{{AFX_MSG(CTabsWindow)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndDrag(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnToolBarQueryDelete(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnToolTipTabCtrl  (NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnToolTipTabCtrlW (NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnSelChangeTabCtrl(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnLClickTabCtrl   (NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnRClickTabCtrl   (NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnWTXTabClose     (NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnWTXRTabClose    (NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT UpdateTabs(WPARAM wParam = 0, LPARAM lParam = 0);
	afx_msg LRESULT OnTabInfoUpdate(WPARAM wParam = 0, LPARAM lParam = 0);
    DECLARE_MESSAGE_MAP();

    CImageList          m_TabImages;
    CImageList          m_NumberOverlays;
    CRect               m_RectGripper;
    CRect               m_RectTracking;
    CRect               m_RectBounding;
    BOOL                m_bTracking;
    bool                m_bVisibleTracking;
    bool                m_bIsDragging;
    SnapOrientations    m_TrackingOrientation;
    CString             m_sToolTip;
    HCURSOR             m_hSavedCursor;

    CTypedPtrMap<CMapPtrToPtr, HWND, tabdata_t *> m_TabData;

    void DrawTrackingRect();
    void RecalcTrackingRect();
    SnapOrientations CalcTrackingOrientation(CPoint pt);

    void FreeData();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABSWINDOW_H__6A06C13B_4748_11D1_BC91_0000010016A6__INCLUDED_)
