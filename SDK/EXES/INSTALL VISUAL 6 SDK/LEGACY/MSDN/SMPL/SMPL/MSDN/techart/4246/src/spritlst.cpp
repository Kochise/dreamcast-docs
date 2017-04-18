// spritlst.cpp : implementation file
// @doc

#include "stdafx.h"
#include "animate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpriteList

IMPLEMENT_SERIAL(CSpriteList, CObList, 0 /* schema number*/ )

CSpriteList::CSpriteList()
{
    // give the sprite notification object
    // a pointer to the list object 
    m_NotifyObj.SetList(this);
}

CSpriteList::~CSpriteList()
{
}

/////////////////////////////////////////////////////////////////////////////
// CSpriteList serialization

void CSpriteList::Serialize(CArchive& ar)
{
    // let the base class create the set of objects
    CObList::Serialize(ar);

    // If we just loaded, initialize each sprite
    if (ar.IsLoading()) {
        for (POSITION pos = GetHeadPosition(); pos != NULL;) {
            CSprite *pSprite = GetNext(pos); // inc pos
            pSprite->SetNotificationObject(&m_NotifyObj);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// CSpriteList commands

/*
@mfunc void | CSpriteList | RemoveAll | Remove everything from the list
deleting all the sprites removed.
@syntax void RemoveAll();
@rdesc There is no return value.
@xref <c CSpriteList> <c CSprite>
*/

void CSpriteList::RemoveAll()
{
    // Walk down the list deleting objects as we go.
    // We need to do this here because the base class
    // simply deletes the pointers.
    POSITION pos;
    CSprite *pSprite;
    for (pos = GetHeadPosition(); pos != NULL;) {
        pSprite = GetNext(pos); // inc pos
        if (pSprite) {
            ASSERT(pSprite->IsKindOf(RUNTIME_CLASS(CSprite)));
            delete pSprite;
        }
    }
    // now call the base class to remove the pointers
    CObList::RemoveAll();
}

/*
@mfunc BOOL | CSpriteList | Insert | Add a sprite to the list,
placing it according to its z-order value.
@syntax BOOL Insert(CSprite* pNewSprite);
@parm CSprite* | pSprite | A pointer to the sprite to be inserted.
@rdesc The return value is TRUE if the function succeeds, FALSE if not.
@comm The position of the sprite in the list is detrmined by its z order.
If more than one sprite has the same z order value, then the sprite most
recently added to the list will appear frontmost when the list is rendered
and draw.
@xref <c CSpriteList> <c CSprite>
*/

// Add a sprite to the list, placing it according to its z-order value
BOOL CSpriteList::Insert(CSprite* pNewSprite)
{
    // Set the notification object pointer in the sprite
    // to the list's notifiaction object
    pNewSprite->SetNotificationObject(&m_NotifyObj);

    // Walk down the list until we either get to the end
    // or we find a sprite with the same or higher z order
    // in which case we insert just before that one.

    POSITION pos, posThis;
    CSprite *pSprite;
    for (pos = GetHeadPosition(); pos != NULL;) {
        posThis = pos;
        pSprite = GetNext(pos); // inc pos
        if (pSprite->GetZ() >= pNewSprite->GetZ()) {
            InsertBefore(posThis, pNewSprite);
            return TRUE;
        }
    }
    // nothing with same or higher z-order so add it to the end
    AddTail(pNewSprite); 
    return TRUE;
}

// remove a sprite from the list, but do not delete it
CSprite *CSpriteList::Remove(CSprite *pSprite)
{
    POSITION pos = Find(pSprite);
    if (pos == NULL) {
        return NULL;
    }
    RemoveAt(pos);
    return pSprite;
}

/*
@mfunc void | CSpriteList | Reorder | Move a sprite to its
correct z-order position in the list.
@syntax void Reorder(CSprite* pSprite);
@parm CSprite* | pSprite | A pointer to the sprite to be adjusted.
@rdesc There is no return value.
@xref <c CSpriteList> <c CSprite>
*/

void CSpriteList::Reorder(CSprite *pSprite)
{
    // Remove the sprite from the list
    if (!Remove(pSprite)) {
        TRACE("Unable to find sprite");
        return; // not there
    }
    // Now insert it again in the right place
    Insert(pSprite);
}

/*
@mfunc CSprite* | CSpriteList | HitTest | Test for a mouse hit
on any sprite in the list.
@syntax CSprite* HitTest(CPoint point);
@parm CPoint | point | The point to be tested.
@rdesc If a hit occurs in the visible area of a sprite in the list, the
return value is a pointer to the frontmost sprite hit. If not hit occurs,
the return value is NULL.
@xref <c CSpriteList> <c CSprite>
*/
// Test for a mouse hit on any sprite in the list
CSprite* CSpriteList::HitTest(CPoint point)
{
    // Walk the list top down
    POSITION pos;
    CSprite *pSprite;
    for (pos = GetHeadPosition(); pos != NULL;) {
        pSprite = GetNext(pos); // inc pos
        if (pSprite->HitTest(point)) {
            return pSprite;
        }
    }
    return NULL;
}

