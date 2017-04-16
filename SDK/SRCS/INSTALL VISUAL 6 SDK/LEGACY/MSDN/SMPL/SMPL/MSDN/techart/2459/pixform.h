// pixform.h : header file
//
#include "COpenGL.h"
/////////////////////////////////////////////////////////////////////////////
// CPixForm dialog

class CPixForm : public CDialog
{
// Construction
public:
	CPixForm(CWnd* pParent = NULL);	// standard constructor

	int m_nID;
	void SetID(int nID) {m_nID = nID;};

	COpenGL *m_glptr;
	void SetGLptr(COpenGL *opengl) {m_glptr = opengl;};

// Dialog Data
	//{{AFX_DATA(CPixForm)
	enum { IDD = IDD_CHOOSEPF };
	int		m_accumbits;
	int		m_alphabits;
	int		m_auxbuffers;
	int		m_colorbits;
	BOOL	m_dbufferdontcare;
	int		m_depthbits;
	BOOL	m_doublebuffer;
	BOOL	m_drawbitmap;
	BOOL	m_drawwindow;
	int		m_stencilbits;
	BOOL	m_stereo;
	BOOL	m_stereodontcare;
	BOOL	m_supportgdi;
	BOOL	m_supportopengl;
	int		m_layertype;
	int		m_pixeltype;
	int		m_index;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CPixForm)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedMorepfd();
	afx_msg void OnClickedLastPfd();
	afx_msg void OnClickedNextPfd();
	afx_msg void OnClickedEndPfd();
	afx_msg void OnClickedFirstPfd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
  int m_nNextID;
  void UpdateDlg(PIXELFORMATDESCRIPTOR *pfd, int idx);
  void CPixForm::CheckDwFlagButton(PIXELFORMATDESCRIPTOR *pfd, int idButton, DWORD dwFlag) ;

};
