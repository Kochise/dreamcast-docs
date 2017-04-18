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
	int		m_phases;
	double	m_vx;
	double	m_vy;
	double	m_x;
	double	m_y ;
	double	m_mass;
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
