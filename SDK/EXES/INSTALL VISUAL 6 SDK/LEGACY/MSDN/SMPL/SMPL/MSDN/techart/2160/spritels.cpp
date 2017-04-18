// spritels.cpp : implementation file
//

#include "stdafx.h"
#include "anim32.h"
#include "spritels.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpriteList

IMPLEMENT_SERIAL(CSpriteList, CObList, 0 /* schema number*/ )

CSpriteList::CSpriteList()
{
    // set up the notification object
    m_NotifyObj.SetList(this);
    m_pDoc = NULL; // no doc attached yet    
}

CSpriteList::~CSpriteList()
{
}

/////////////////////////////////////////////////////////////////////////////
// CSpriteList serialization

void CSpriteList::Serialize(CArchive& ar)
{
    dprintf2("CSpriteList::Serialize()");
    DWORD dw;
    POSITION pos;
    CSprite *pSprite;
    if (ar.IsStoring()) {
        // Write the number of sprites in the list
        dw = GetCount();
        ar << dw;
        // write out the sprites
        for (pos = GetHeadPosition(); pos != NULL;) {
            pSprite = GetNext(pos); // inc pos
            ar.WriteObject(pSprite);
            dw--;    
        }
        ASSERT (dw == 0);
    } else {
        // get the count
        ar >> dw;
        while (dw--) {
            pSprite = (CSprite *) ar.ReadObject(RUNTIME_CLASS(CSprite));
            ASSERT(pSprite);
            ASSERT(pSprite->IsKindOf(RUNTIME_CLASS(CSprite)));
            // Add it to the list
            Insert(pSprite);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// CSpriteList commands

// Remove everything from the list deleting all the sprites we remove
void CSpriteList::RemoveAll()
{
    dprintf2("CSpriteList::RemoveAll()");
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

// Add a sprite to the list, placing it according to its z-order value
BOOL CSpriteList::Insert(CSprite *pNewSprite)
{
    dprintf2("CSpriteList::Insert()");
    // Walk down the list until we either get to the end
    // or we find a sprite with the same or higher z order
    // in which case we insert just before that one.

    POSITION pos, posThis;
    CSprite *pSprite;
    // Set the callback object pointer to our handler
    pNewSprite->SetNotifyHandler(&m_NotifyObj);
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
    dprintf2("CSpriteList::Remove()");
    POSITION pos = Find(pSprite);
    if (pos == NULL) {
        dprintf3(" not found");
        return NULL;
    }
    RemoveAt(pos);
    // remove the callback handler pointer
    pSprite->SetNotifyHandler(NULL);
    return pSprite;
}

// Move a sprite to its correct z-order position
void CSpriteList::Reorder(CSprite *pSprite)
{
    dprintf2("CSpriteList::Reorder()");
    // Remove the sprite from the list
    if (!Remove(pSprite)) {
        dprintf1("Unable to find sprite");
        return; // not there
    }
    // Now insert it again in the right place
    Insert(pSprite);
}

// Test for a mouse hit on any sprite in the list
CSprite *CSpriteList::HitTest(CPoint point)
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

