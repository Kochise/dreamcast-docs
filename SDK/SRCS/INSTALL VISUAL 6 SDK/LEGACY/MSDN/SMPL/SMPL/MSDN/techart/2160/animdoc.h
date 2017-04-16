// animdoc.h : interface of the CAnimDoc class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __ANIMDOC__
#define __ANIMDOC__

#include "dib.h"
#include "spritels.h"
#include "animsp.h"

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
    BOOL SetBkgnd(CDIB *pdib);
    BOOL AddSprite(CAnimSprite *psprite);
    void DeleteAllSprites();
    CDIB *GetBkgnd() 
        {return m_pdibBkgnd;}
    CSpriteList *GetSpriteList()
        {return &m_spList;}
    void UpdateSpritePositions();
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
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // __ANIMDOC__
