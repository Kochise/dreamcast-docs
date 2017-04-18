// animdoc.cpp : implementation of the CAnimDoc class
//

#include "stdafx.h"
#include "gravity.h"
#include "animdoc.h"
#include "uni.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimDoc

IMPLEMENT_DYNCREATE(CAnimDoc, CDocument)

BEGIN_MESSAGE_MAP(CAnimDoc, CDocument)
    //{{AFX_MSG_MAP(CAnimDoc)
	ON_COMMAND(IDM_SIMULATE_RESET, OnSimulateReset)
	ON_COMMAND(IDM_OPTIONS_TIMER, OnOptionsTimer)
	ON_UPDATE_COMMAND_UI(IDM_SIMULATE_RESET, OnUpdateSimulateReset)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(IDM_OPTIONS_TIMER, OnUpdateOptionsTimer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimDoc construction/destruction

CAnimDoc::CAnimDoc()
	: m_bSimulate(FALSE)
{
    m_pdibBkgnd = NULL;
    m_spList.AttachDoc(this);
}

CAnimDoc::~CAnimDoc()
{
}

void CAnimDoc::DeleteContents()
{
    //dprintf2("CAnimDoc::DeleteContents()");
	 m_bSimulate = FALSE ; //der
    m_spList.RemoveAll();
    if (m_pdibBkgnd) {
        delete m_pdibBkgnd;
        m_pdibBkgnd = NULL;
    }
}

BOOL CAnimDoc::OnNewDocument()
{
//    dprintf2("CAnimDoc::OnNewDocument");
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
    //dprintf2("CAnimDoc::Serialize()");
    CDocument::Serialize(ar);
    if (ar.IsStoring()) {
        if (m_pdibBkgnd) {
            ar << (DWORD) 1; // say we have a bkgnd
            m_pdibBkgnd->Serialize(ar);
        } else {
            ar << (DWORD) 0; // say we have no bkgnd
        }
        m_spList.Serialize(ar);
		  CUniverse::Save(ar) ;
    } else {
        DWORD dw;
        // see if we have a background to load
        ar >> dw;
        if (dw != 0) {
            CDIB *pdib = new CDIB;
            pdib->Serialize(ar);
            // Attach it to the document
            SetBkgnd(pdib);
        }
        // read the sprite list
        m_spList.Serialize(ar);
		  CUniverse::Save(ar) ;
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
    //dprintf2("CAnimDoc::SetBkgnd()");
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
BOOL CAnimDoc::AddSprite(CBody *psprite) //DER was CAnimSprite
{
   // dprintf2("CAnimDoc::AddSprite()");
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
BOOL CAnimDoc::UpdateSpritePositions()
{
	 CBody* pBodyI ;
	 CBody* pBodyJ	;
	 POSITION i,j ;
    if (m_spList.IsEmpty()) return FALSE; // no sprites

	i = m_spList.GetHeadPosition();
	while(i != NULL )
	{
      pBodyI = (CBody *)m_spList.GetNext(i); 
      ASSERT(pBodyI->IsKindOf(RUNTIME_CLASS(CBody)));
		j = m_spList.GetHeadPosition() ; 
		while(j != NULL)
		{
        pBodyJ = (CBody *)m_spList.GetNext(j); 
        ASSERT(pBodyJ->IsKindOf(RUNTIME_CLASS(CBody)));
		  if ( j != i)
		  {
        		pBodyI->ApplyForce(pBodyJ);
		  }
		}   
   }
	
	i = m_spList.GetHeadPosition();
	while (i != NULL)
	{
		pBodyI = (CBody *)m_spList.GetNext(i);
		pBodyI->Update() ;
	}

	UpdateAllViews(NULL, HINT_DIRTYLIST, 0);
	return TRUE; 
}

void CAnimDoc::OnSimulateReset()
{
	ResetBodies() ;
}

void CAnimDoc::OnUpdateSimulateReset(CCmdUI* pCmdUI)
{
	// Only allow a reset if we are not simulating
	pCmdUI->Enable(!m_bSimulate) ;	
}

void CAnimDoc::ResetBodies()
{
	ASSERT(m_bSimulate == FALSE) ;

	CBody* pBodyI ;
	POSITION i = m_spList.GetHeadPosition();
	while (i != NULL)
	{
		pBodyI = (CBody *)m_spList.GetNext(i);
		pBodyI->Reset() ;
	}

	UpdateAllViews(NULL, HINT_DIRTYLIST, 0);		
}


void CAnimDoc::OnOptionsTimer()
{
	if (m_bSimulate)
	{
		MessageBeep(0) ;
		return ;
	}

	if (CUniverse::DoTimeDialog()) SetModifiedFlag() ;
}

void CAnimDoc::OnUpdateOptionsTimer(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!m_bSimulate) ;		
}

void CAnimDoc::OnUpdateFileSave(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!m_bSimulate) ;	
}

void CAnimDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!m_bSimulate) ;	
}



