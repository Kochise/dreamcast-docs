/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// TreePropertySheet.h : header file
//

#if !defined(AFX_TREEPROPERTYSHEET_H__A8622AD5_D4C8_4348_AC80_AD32C907EB35__INCLUDED_)
#define AFX_TREEPROPERTYSHEET_H__A8622AD5_D4C8_4348_AC80_AD32C907EB35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HHSupp.h"

/////////////////////////////////////////////////////////////////////////////
// CTreePropertySheet

class CTreePropertySheet : public CHHPropSheet
{
    DECLARE_DYNAMIC(CTreePropertySheet)

// Construction
public:
    CTreePropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
    CTreePropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
    CTreeCtrl    m_TreeCtrl;
    CStatic      m_SepLine;
    int          m_iTreeWidth;

// Operations
public:
    CString GetTreeConfig();
    void SetTreeConfig(LPCTSTR pszTreeCfg);


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTreePropertySheet)
    public:
    virtual BOOL OnInitDialog();
    //}}AFX_VIRTUAL


// Implementation
public:
    virtual ~CTreePropertySheet();

    // Generated message map functions
protected:
    //{{AFX_MSG(CTreePropertySheet)
    afx_msg void OnDestroy();
    //}}AFX_MSG
    afx_msg void OnSelChangedW(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnSelChangedA(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNotifyKeyDown(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg LRESULT OnResyncTree(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()

    CRect       m_rectPages;        
    CRect       m_rectTreeCtrl;
    bool        m_bChangingPages;
    CString     m_sTreeCfg;
    int         m_iSel;
    class CXTabCtrl *m_pTabCtrl;

    void CommonInit();
    void UpdateTreeFromConfig();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEPROPERTYSHEET_H__A8622AD5_D4C8_4348_AC80_AD32C907EB35__INCLUDED_)
