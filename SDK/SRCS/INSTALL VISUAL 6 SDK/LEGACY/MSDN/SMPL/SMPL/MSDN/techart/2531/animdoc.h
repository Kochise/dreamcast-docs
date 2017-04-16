// animdoc.h : interface of the CAnimDoc class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __ANIMDOC__
#define __ANIMDOC__

#include "dib.h"
#include "spritels.h"
#include "body.h"/*DER -- "animsp.h"*/

// Flags used to define hints in UpdateAllViews()
#define HINT_NEWBKGNDDIB    1      // new palette and buffer. CObj is CDIB
#define HINT_NEWSPRITE      2      // new sprite is to be rendered and painted
                                   // CObj is CSprite
#define HINT_DIRTY          3      // CObj is CRect
#define HINT_DIRTYLIST      4      // CObj not used

class CAnimDoc : public CDocument
{
protected: // create from serialization only
    CAnimDoc();
    DECLARE_DYNCREATE(CAnimDoc)

// Attributes
protected:

    CDIB        *m_pdibBkgnd;   // ptr to background DIB
    CSpriteList m_spList;       // sprite list

// Operations
public:
	 BOOL m_bSimulate ; 		//DER
	 void ResetBodies() ; 	//DER

	 BOOL AnySprites() {return !m_spList.IsEmpty();} 

    BOOL SetBkgnd(CDIB *pdib);
    BOOL AddSprite(CBody *psprite);
    void DeleteAllSprites();
    CDIB *GetBkgnd() 
        {return m_pdibBkgnd;}
    CSpriteList *GetSpriteList()
        {return &m_spList;}
    BOOL UpdateSpritePositions();
    CSize GetSize();

// Implementation
public:
    virtual ~CAnimDoc();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
protected:
    virtual void DeleteContents();
    virtual BOOL OnNewDocument();

// Generated message map functions
protected:
    //{{AFX_MSG(CAnimDoc)
	afx_msg void OnSimulateReset();
	afx_msg void OnOptionsTimer();
	afx_msg void OnUpdateSimulateReset(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsTimer(CCmdUI* pCmdUI);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // __ANIMDOC__
