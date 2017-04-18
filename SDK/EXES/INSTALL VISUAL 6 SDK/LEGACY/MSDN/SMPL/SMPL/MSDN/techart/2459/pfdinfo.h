// pfdinfo.h : header file
//
#include "COpenGL.h"
/////////////////////////////////////////////////////////////////////////////
// CPFDInfo dialog

class CPFDInfo : public CDialog
{
// Construction
public:
	void SetID(int nID) {m_nID = nID;};
	void SetGLptr(COpenGL *opengl) {m_glptr = opengl;};
	CPFDInfo(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPFDInfo)
	enum { IDD = IDD_PFDINFO };
	int		m_curpfd;
	BOOL	m_devfmt;
	BOOL	m_genfmt;
	int		m_maxpfd;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	// Generated message map functions
	//{{AFX_MSG(CPFDInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_nID;
	COpenGL *m_glptr;

};
