// splsno.cpp : implementation file
//

#include "stdafx.h"
#include "gravity.h" // for debug macros only
#include "animdoc.h"
#include "splsno.h"
#include "spritels.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpriteListNotifyObj

CSpriteListNotifyObj::CSpriteListNotifyObj()
{
    m_pList = NULL;
    m_pDoc = NULL;
}

CSpriteListNotifyObj::~CSpriteListNotifyObj()
{
}

// Notification callback from a CSprite object
void CSpriteListNotifyObj::Change(CSprite *pSprite,
                                  CHANGETYPE change,
                                  LPVOID p1,
                                  LPVOID p2)
{
    if (change &CSpriteNotifyObj::ZORDER) {
        // reposition the sprite in the z-order list
        ASSERT(m_pList);
        m_pList->Reorder(pSprite);
    }
    if (change &CSpriteNotifyObj::POSITION) {
        // p1 and p2 point to old and new rect positions
        // add these rects to the dirty list
        ASSERT(m_pDoc);
        m_pDoc->UpdateAllViews(NULL, HINT_DIRTY, (CObject *)p1);
        m_pDoc->UpdateAllViews(NULL, HINT_DIRTY, (CObject *)p2);
    }
}
