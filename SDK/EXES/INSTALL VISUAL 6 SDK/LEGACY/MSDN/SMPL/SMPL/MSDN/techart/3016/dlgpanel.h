// dlgpanel.h : header file
//

#define DLGPANELMSG_SETPALETTE (WM_USER+100)

/////////////////////////////////////////////////////////////////////////////
// CDlgPanel window

class CDlgPanel : public CDialogBar
{
// Construction
public:
    CDlgPanel();
    BOOL Create(CWnd* pParentWnd, UINT nIDTemplate,
                UINT nStyle, UINT nID, CPalette* pPal);
    void GetPanelRect(RECT* pRect);

    virtual ~CDlgPanel();
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
    CPalette* m_pPal;
    UINT m_uiIDTemplate;

    // Generated message map functions
    //{{AFX_MSG(CDlgPanel)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
