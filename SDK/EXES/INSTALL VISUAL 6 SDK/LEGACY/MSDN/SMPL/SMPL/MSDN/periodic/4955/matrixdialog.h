// dialog.h : header file
//

// MS supplied file to turn off compiler warnings
//#include "glos.h"

// OpenGL, utility, and aux header files
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

/////////////////////////////////////////////////////////////////////////////
// DialogMatrix dialog

class CMatrixDialog : public CDialog
{
// Construction
public:
	CMatrixDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DialogMatrix)
	enum { IDD = IDD_DIALOG1 };
	// removed the numerous AFX array elements
	int		m_ShowTeapot;
	//}}AFX_DATA

	GLfloat	m_Matrix[4][4];
	GLfloat	m_PreMatrix[4][4];

	CView* m_pView; // pointer to our parent

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DialogMatrix)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	BOOL Create( CView* );

// Implementation
private:
	void ResetToIdentity( float m_Matrix[4][4] );
	void ResetToInitialValue( void );

protected:

	// Generated message map functions
	//{{AFX_MSG(DialogMatrix)
	virtual void OnOK();
	afx_msg void OnBResetApply();
	afx_msg void OnBLetter();
	afx_msg void OnBTeapot();
	afx_msg void OnBAppendApply();
	afx_msg void OnBIdentity();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
