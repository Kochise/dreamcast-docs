// MatrixDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Modelview.h"
#include "MatrixDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatrixDialog dialog


CMatrixDialog::CMatrixDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMatrixDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatrixDialog)
		// NOTE: the ClassWizard will add member initialization here
	m_Matrix[0][0] = 0.0f;
	m_Matrix[0][1] = 0.0f;
	m_Matrix[0][2] = 0.0f;
	m_Matrix[0][3] = 0.0f;
	m_Matrix[1][0] = 0.0f;
	m_Matrix[1][1] = 0.0f;
	m_Matrix[1][2] = 0.0f;
	m_Matrix[1][3] = 0.0f;
	m_Matrix[2][0] = 0.0f;
	m_Matrix[2][1] = 0.0f;
	m_Matrix[2][2] = 0.0f;
	m_Matrix[2][3] = 0.0f;
	m_Matrix[3][0] = 0.0f;
	m_Matrix[3][1] = 0.0f;
	m_Matrix[3][2] = 0.0f;
	m_Matrix[3][3] = 0.0f;
	m_ShowTeapot = 0;
	//}}AFX_DATA_INIT

	ResetToIdentity(m_PreMatrix);
	ResetToInitialValue();

	m_pView = 0;

}


/////////////////////////////////////////////////////////////////////////////
// CDialogMatrix Matrix initialization
void CMatrixDialog::ResetToIdentity(float lhs_matrix[4][4] ) 
{
	for ( int x=0; x < 4 ; x++ )
		{
		for ( int y = 0; y < 4 ; y++ )
			{
			// Set diagonals to 1, all else to 0
			lhs_matrix[x][y] = (x==y ? 1.0f : 0.0f );
			}
		}
}

void CMatrixDialog::ResetToInitialValue() 
{
	ResetToIdentity(m_Matrix); // Initialize to identity matrix
//	m_Matrix[3][2] = -5.0;  // translate on Z axis
}

void CMatrixDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DialogMatrix)
	DDX_Text(pDX, IDC_EDIT11, m_Matrix[0][0]);
	DDX_Text(pDX, IDC_EDIT12, m_Matrix[1][0]);
	DDX_Text(pDX, IDC_EDIT13, m_Matrix[2][0]);
	DDX_Text(pDX, IDC_EDIT14, m_Matrix[3][0]);
	DDX_Text(pDX, IDC_EDIT21, m_Matrix[0][1]);
	DDX_Text(pDX, IDC_EDIT22, m_Matrix[1][1]);
	DDX_Text(pDX, IDC_EDIT23, m_Matrix[2][1]);
	DDX_Text(pDX, IDC_EDIT24, m_Matrix[3][1]);
	DDX_Text(pDX, IDC_EDIT31, m_Matrix[0][2]);
	DDX_Text(pDX, IDC_EDIT32, m_Matrix[1][2]);
	DDX_Text(pDX, IDC_EDIT33, m_Matrix[2][2]);
	DDX_Text(pDX, IDC_EDIT34, m_Matrix[3][2]);
	DDX_Text(pDX, IDC_EDIT41, m_Matrix[0][3]);
	DDX_Text(pDX, IDC_EDIT42, m_Matrix[1][3]);
	DDX_Text(pDX, IDC_EDIT43, m_Matrix[2][3]);
	DDX_Text(pDX, IDC_EDIT44, m_Matrix[3][3]);
	DDX_Radio(pDX, IDC_B_LETTER, m_ShowTeapot);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatrixDialog, CDialog)
	//{{AFX_MSG_MAP(DialogMatrix)
	ON_BN_CLICKED(ID_B_RESET_APPLY, OnBResetApply)
	ON_BN_CLICKED(IDC_B_LETTER, OnBLetter)
	ON_BN_CLICKED(IDC_B_TEAPOT, OnBTeapot)
	ON_BN_CLICKED(ID_B_APPEND_APPLY, OnBAppendApply)
	ON_BN_CLICKED(ID_B_IDENTITY, OnBIdentity)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// DialogMatrix message handlers

void CMatrixDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CMatrixDialog::Create( CView * pView ) 
{
	// TODO: Add your specialized code here and/or call the base class

	m_pView = pView;

	return CDialog::Create( CMatrixDialog::IDD );
}


void CMatrixDialog::OnBResetApply() 
{
	// TODO: Add your control notification handler code here

	ResetToIdentity(m_PreMatrix); // Clear out the pre matrix
	UpdateData( TRUE );

	m_pView->SendMessage( WM_PAINT );
	
}

void CMatrixDialog::OnBAppendApply() 
{
	// TODO: Add your control notification handler code here
	
	// copy original m_Matrix into m_PreMatrix
	float result[4][4] = {0.0f};

	for (int i = 0; i < 4 ; i++ )
	  {
	  for ( int j = 0; j < 4 ; j++ )
	    {
		 result[i][j] = 0.0f;
		 for ( int k = 0 ; k < 4 ; k++ )
		   {
			result[i][j] += m_PreMatrix[i][k] * m_Matrix[k][j];
		   }
	    }
	  }

//	memcpy( m_PreMatrix, result, sizeof( m_Matrix ) );
	memcpy( m_PreMatrix, result, sizeof(float)*4*4 );

	// fetch data from the DB into our data
	UpdateData( TRUE );
	
	m_pView->SendMessage( WM_PAINT );
}

void CMatrixDialog::OnBIdentity() 
{
	// TODO: Add your control notification handler code here
	float TemporaryMatrix[4][4];

	// copy the current modelview matrix
	memcpy( TemporaryMatrix, m_Matrix, sizeof(float)*4*4 );

	// reset it and reset the dialog box values
	ResetToInitialValue(); 
	UpdateData( FALSE );

	// Copy the original values back, since we just wanted
	// to clear the DB values, not the modelview matrix values
	memcpy( m_Matrix, TemporaryMatrix, sizeof(float)*4*4 );
}

void CMatrixDialog::OnBLetter() 
{
	// TODO: Add your control notification handler code here
	UpdateData( TRUE );
 
 	m_pView->SendMessage( WM_PAINT );
}

void CMatrixDialog::OnBTeapot() 
{
	// TODO: Add your control notification handler code here
	UpdateData( TRUE );

	m_pView->SendMessage( WM_PAINT );
}

void CMatrixDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}
