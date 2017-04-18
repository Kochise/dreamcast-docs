// splstno.cpp : implementation file
// @doc

#include "stdafx.h"
#include "animate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpriteListNotifyObj

CSpriteListNotifyObj::CSpriteListNotifyObj()
{
    m_pSpriteList = NULL;
    m_pBufferView = NULL;
}

CSpriteListNotifyObj::~CSpriteListNotifyObj()
{
}

/*
@mfunc void | CSpriteListNotifyObj | Change | Called to notify the 
object of changes in the status of a sprite.
@syntax void Change(CSprite* pSprite, CHANGETYPE change,
CRect* pRect1, CRect* pRect2);
@parm CSprite* | pSprite | A pointer to the CSprite object reporting
the change.
@parm CSpriteNotifyObj::CHANGETYPE | change | A flag indication the
type of change that has occured.
@parm CRect* | pRect1 | An optional rectangle used to indicate
an area involved in the change.
@parm CRect* | pRect2 | An optional rectangle used to indicate
an area involved in the change.
@rdesc There is no return value.
@comm There are three change types: ZORDER, IMAGE amd POSITION. For an
IMAGE change, pRect1 indicates the area of the image affected.  For a POSITION
change, pRect1 and pRect2 indicate the old and new positions respectivly.
@xref <c CSpriteListNotifyObj> <c CSpriteNotifyObj>
*/
// Notification callback from a CSprite object
void CSpriteListNotifyObj::Change(CSprite *pSprite,
                                  CHANGETYPE change,
                                  CRect* pRect1,
                                  CRect* pRect2)
{
    if (change & CSpriteNotifyObj::ZORDER) {
        // reposition the sprite in the z-order list
        ASSERT(m_pSpriteList);
        m_pSpriteList->Reorder(pSprite);
        // Add the sprite position to the dirty list
        ASSERT(m_pBufferView);
        m_pBufferView->AddDirtyRegion(pRect1);
    }
    if (change & CSpriteNotifyObj::POSITION) {
        // pRect1 and pRect2 point to old and new rect positions
        // add these rects to the dirty list
        ASSERT(m_pBufferView);
        m_pBufferView->AddDirtyRegion(pRect1);
        m_pBufferView->AddDirtyRegion(pRect2);
    }
    if (change & CSpriteNotifyObj::IMAGE) {
        // redraw the sprite
        // Add the sprite position to the dirty list
        ASSERT(m_pBufferView);
        m_pBufferView->AddDirtyRegion(pRect1);
    }
}
