// spritedl.h : header file
//

#include "sprite.h"

/////////////////////////////////////////////////////////////////////////////
// CSpriteDlg dialog

class CSpriteDlg : public CDialog
{
// Construction
public:
    CSpriteDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CSpriteDlg)
	enum { IDD = IDD_SPRITEDLG };
    CStatic m_wndWidth;
    CStatic m_wndHeight;
    BOOL    m_bSelectable;
    int     m_vx;
    int     m_vy;
    int     m_x;
    int     m_y;
    int     m_z;
	int		m_phases;
	//}}AFX_DATA
    CSprite *pSprite;   // The sprite we are working with
// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(CSpriteDlg)
        // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
