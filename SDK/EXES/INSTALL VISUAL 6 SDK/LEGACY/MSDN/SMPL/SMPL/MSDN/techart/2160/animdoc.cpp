// animdoc.cpp : implementation of the CAnimDoc class
//

#include "stdafx.h"
#include "anim32.h"
#include "animdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimDoc

IMPLEMENT_DYNCREATE(CAnimDoc, CDocument)

BEGIN_MESSAGE_MAP(CAnimDoc, CDocument)
    //{{AFX_MSG_MAP(CAnimDoc)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimDoc construction/destruction

CAnimDoc::CAnimDoc()
{
    m_pdibBkgnd = NULL;
    m_spList.AttachDoc(this);
}

CAnimDoc::~CAnimDoc()
{
}

void CAnimDoc::DeleteContents()
{
    dprintf2("CAnimDoc::DeleteContents()");
    m_spList.RemoveAll();
    if (m_pdibBkgnd) {
        delete m_pdibBkgnd;
        m_pdibBkgnd = NULL;
    }
}

BOOL CAnimDoc::OnNewDocument()
{
    dprintf2("CAnimDoc::OnNewDocument");
    if (!CDocument::OnNewDocument()) return FALSE;

    // Create a new default background DIB just so
    // there will be something to look at
    CDIB *pdib = new CDIB;
    pdib->Create(640, 480);
    SetBkgnd(pdib); // nukes old bkgnd and sprites
    SetModifiedFlag(FALSE);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAnimDoc serialization

void CAnimDoc::Serialize(CArchive& ar)
{
    dprintf2("CAnimDoc::Serialize()");
    CDocument::Serialize(ar);
    if (ar.IsStoring()) {
        if (m_pdibBkgnd) {
            ar << (DWORD) 1; // say we have a bkgnd
            ar.WriteObject(m_pdibBkgnd);
        }
        m_spList.Serialize(ar);
    } else {
        DWORD dw;
        // see if we have a background to load
        ar >> dw;
        if (dw != 0) {
            CDIB *pdib;
            pdib = (CDIB *) ar.ReadObject(RUNTIME_CLASS(CDIB));
            ASSERT(pdib);
            ASSERT(pdib->IsKindOf(RUNTIME_CLASS(CDIB)));
            // Attach it to the document
            SetBkgnd(pdib);
        }
        // read the sprite list
        m_spList.Serialize(ar);
        SetModifiedFlag(FALSE);
        UpdateAllViews(NULL, 0, NULL);
    }
}


/////////////////////////////////////////////////////////////////////////////
// CAnimDoc diagnostics

#ifdef _DEBUG
void CAnimDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CAnimDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnimDoc commands

CSize CAnimDoc::GetSize()
{
    CSize s;
    if (!m_pdibBkgnd) {
        s.cx = s.cy = 0;
    } else {
        s.cx = m_pdibBkgnd->GetWidth();
        s.cy = m_pdibBkgnd->GetHeight();
    }
    return s;
}

// Load a new background DIB.  All  current sprites are deleted
BOOL CAnimDoc::SetBkgnd(CDIB *pdib)
{
    dprintf2("CAnimDoc::SetBkgnd()");
    if (!pdib) return FALSE;

    // Delete the current sprite set
    DeleteAllSprites();

    // Delete any existing background DIB and set the new one
    if (m_pdibBkgnd) delete m_pdibBkgnd;
    m_pdibBkgnd = pdib;

    // Note that the doc has changed
    SetModifiedFlag(TRUE);

    // Update all the views.  Send a hint to say that
    // the palette needs to be rebuilt from the new dib. 
    UpdateAllViews(NULL, HINT_NEWBKGNDDIB, pdib);
    return TRUE;
}

// Add a new sprite to the list and show the change
BOOL CAnimDoc::AddSprite(CAnimSprite *psprite)
{
    dprintf2("CAnimDoc::AddSprite()");
    if (!m_spList.Insert(psprite)) return FALSE;
    SetModifiedFlag(TRUE);
    // Just redraw the bit where the sprite is
    UpdateAllViews(NULL, HINT_NEWSPRITE, psprite);
    return TRUE;
}

void CAnimDoc::DeleteAllSprites()
{
    m_spList.RemoveAll();
}

// Update the positions of all the sprites
void CAnimDoc::UpdateSpritePositions()
{
    int i = 0;
    POSITION pos;
    CAnimSprite *pSprite;
    for (pos = m_spList.GetHeadPosition(); pos != NULL;) {
        pSprite = (CAnimSprite *)m_spList.GetNext(pos);
        ASSERT(pSprite->IsKindOf(RUNTIME_CLASS(CAnimSprite))); 
        i += pSprite->UpdatePosition(this);
    }
    if (i) {
        // draw the changes
        UpdateAllViews(NULL, HINT_DIRTYLIST, 0);
    }
}
