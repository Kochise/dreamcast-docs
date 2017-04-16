// spelldoc.cpp : implementation of the CSpellDoc class
//

#include "stdafx.h"
#include "speledit.h"
#include "spelldoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpellDoc

IMPLEMENT_DYNCREATE(CSpellDoc, CDocument)

BEGIN_MESSAGE_MAP(CSpellDoc, CDocument)
    //{{AFX_MSG_MAP(CSpellDoc)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpellDoc construction/destruction

CSpellDoc::CSpellDoc()
{
    // TODO: add one-time construction code here
}

CSpellDoc::~CSpellDoc()
{
    m_WordMap.DeleteAll();
}

BOOL CSpellDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;
    m_WordMap.DeleteAll();
    UpdateAllViews(NULL);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSpellDoc serialization

void CSpellDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        m_WordMap.Serialize(ar);
    } else {
        m_WordMap.Serialize(ar);
        UpdateAllViews(NULL);
    }
}


/////////////////////////////////////////////////////////////////////////////
// CSpellDoc diagnostics

#ifdef _DEBUG
void CSpellDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CSpellDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpellDoc commands

BOOL CSpellDoc::AddWord(const char* pszWord, CWave* pWave)
{
    m_WordMap.Add(pszWord, pWave);
    SetModifiedFlag(TRUE);
    UpdateAllViews(NULL, HINT_NEW_WORD, (CObject*)pszWord);
    return TRUE;
}

BOOL CSpellDoc::DeleteWord(const char* pszWord)
{
    if (m_WordMap.Remove(pszWord)) {
        SetModifiedFlag(TRUE);
        UpdateAllViews(NULL);
        return TRUE;
    }
    return FALSE;
}

void CSpellDoc::PlayWord(const char* pszWord)
{
    CWave* pWave = m_WordMap.Find(pszWord);
    if (!pWave) return;
    pWave->Play();
}
