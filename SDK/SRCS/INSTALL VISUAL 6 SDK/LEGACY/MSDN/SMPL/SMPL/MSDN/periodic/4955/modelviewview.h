// ModelviewView.h : interface of the CModelviewView class
//
/////////////////////////////////////////////////////////////////////////////

#include "MatrixDialog.h"
#include "COpenGLView.h"

class CModelviewView : public COpenGLView
{
protected: // create from serialization only
	CModelviewView();
	DECLARE_DYNCREATE(CModelviewView)

// Attributes
public:
	CModelviewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModelviewView)
	public:
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CModelviewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual BOOL RenderScene();



	void	DrawLeftView();
	void	DrawRightView();
	void	DrawCommonStockScene();
	void	DrawCommonScene();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CModelviewView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	int	m_width, m_height; // the size of the window
	GLfloat	m_ModelingMatrix[4][4];
	CMatrixDialog m_ViewMatrixDlg;


};

#ifndef _DEBUG  // debug version in ModelviewView.cpp
inline CModelviewDoc* CModelviewView::GetDocument()
   { return (CModelviewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
