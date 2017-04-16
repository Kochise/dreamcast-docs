// spritels.h : header file
//
// CSpriteList class
// This is a type safe version of CObList for CSprite objects
// It is mostly a set of inline casts
//

#ifndef __SPRITELS__
#define __SPRITELS__

#include "sprite.h"
#include "splsno.h"


class CSpriteList : private CObList
{
    DECLARE_SERIAL(CSpriteList)
public:
    CSpriteList();
    ~CSpriteList();
    void RemoveAll();
    BOOL Insert(CSprite *pSprite);
    void Reorder(CSprite *pSprite);
    CSprite *Remove(CSprite *pSprite);
    CSprite *GetNext(POSITION &pos)
        {return (CSprite *) CObList::GetNext(pos);}
    CSprite *GetPrev(POSITION &pos)
        {return (CSprite *) CObList::GetPrev(pos);}
    POSITION GetTailPosition() const
        {return CObList::GetTailPosition();}
    POSITION GetHeadPosition() const
        {return CObList::GetHeadPosition();}
    CSprite *HitTest(CPoint point);
    void AttachDoc(CDocument *pDoc)
        {m_pDoc = pDoc; m_NotifyObj.AttachDoc(pDoc);}
    virtual void Serialize(CArchive& ar);

public:
    CSpriteListNotifyObj m_NotifyObj;

private:
    CDocument *m_pDoc;

};

#endif // __SPRITELS__
