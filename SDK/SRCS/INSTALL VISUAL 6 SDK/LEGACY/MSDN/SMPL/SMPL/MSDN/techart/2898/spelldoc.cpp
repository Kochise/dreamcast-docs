// spelldoc.cpp : implementation of the CSpellerDoc class
//

#include "stdafx.h"
#include "speller.h"

#include "spelldoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpellerDoc

IMPLEMENT_DYNCREATE(CSpellerDoc, CDocument)

BEGIN_MESSAGE_MAP(CSpellerDoc, CDocument)
    //{{AFX_MSG_MAP(CSpellerDoc)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpellerDoc construction/destruction

CSpellerDoc::CSpellerDoc()
{
    m_strCurrentWord = "";
    m_pCurrentWave = NULL;
    m_posCurrent = 0;
}

CSpellerDoc::~CSpellerDoc()
{
    m_WordMap.DeleteAll();
}

BOOL CSpellerDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;
    m_WordMap.DeleteAll();
    m_posCurrent = 0;
    GetNextWord();
    UpdateAllViews(NULL);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSpellerDoc serialization

void CSpellerDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        m_WordMap.Serialize(ar);
    } else {
        m_WordMap.Serialize(ar);
        m_posCurrent = 0;
        GetNextWord();
        UpdateAllViews(NULL);
    }
}


/////////////////////////////////////////////////////////////////////////////
// CSpellerDoc diagnostics

#ifdef _DEBUG
void CSpellerDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CSpellerDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpellerDoc commands

CString* CSpellerDoc::GetNextWord()
{
    if (!m_posCurrent) {
        m_posCurrent = m_WordMap.GetStartPosition();
        if (!m_posCurrent) return NULL;
    }
    m_WordMap.GetNextAssoc(m_posCurrent, m_strCurrentWord, m_pCurrentWave);
    return &m_strCurrentWord;
}
