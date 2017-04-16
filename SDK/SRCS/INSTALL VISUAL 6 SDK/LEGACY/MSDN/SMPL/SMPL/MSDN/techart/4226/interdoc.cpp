// Interdoc.cpp : implementation of the CInterpDoc class
//

#include "stdafx.h"
#include "Interp.h"

#include "Interdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInterpDoc

IMPLEMENT_DYNCREATE(CInterpDoc, CDocument)

BEGIN_MESSAGE_MAP(CInterpDoc, CDocument)
	//{{AFX_MSG_MAP(CInterpDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterpDoc construction/destruction

CInterpDoc::CInterpDoc()
{
    m_pal.CreateWash();
}

CInterpDoc::~CInterpDoc()
{
}

BOOL CInterpDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CInterpDoc serialization

void CInterpDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring()){
		ASSERT(0);
	} else {
        CFile *fp = ar.GetFile();
        ASSERT(fp);
        ar.Flush();

        // Get the file from the archive
        // Load the DIB from the file
        if (!m_dib.Load(fp)) {
            AfxMessageBox("Failed to load DIB file");
            return;
        }

        // Create the palette from the DIB
        if (!m_pal.Create(&m_dib)) {
            // No palette in the DIB so create one
            m_pal.CreateWash();
        }

        // make an identity palette
        m_pal.SetSysPalColors();

        // map the dib to the new palette
        m_dib.MapColorsToPalette(&m_pal);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CInterpDoc diagnostics

#ifdef _DEBUG
void CInterpDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CInterpDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInterpDoc commands
