// animsp.cpp : implementation file
//

#include "stdafx.h"
#include "anim32.h"
#include "animdoc.h"
#include "animsp.h"
#include "spritedl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimSprite

IMPLEMENT_SERIAL(CAnimSprite, CPhasedSprite, 0 /* schema number*/ )

CAnimSprite::CAnimSprite()
{
    m_dx = 0;
    m_dy = 0;
    m_vx = 0;
    m_vy = 0;
    m_bSelectable = TRUE;
    m_iCycle = 0;
}

CAnimSprite::~CAnimSprite()
{
}

/////////////////////////////////////////////////////////////////////////////
// CAnimSprite serialization

void CAnimSprite::Serialize(CArchive& ar)
{
    CPhasedSprite::Serialize(ar);
    if (ar.IsStoring()) {
        ar << (DWORD) m_vx;
        ar << (DWORD) m_vy;
        ar << (DWORD) m_bSelectable;
    } else  {
        DWORD dw;
        ar >> dw; m_vx = (int) dw;
        ar >> dw; m_vy = (int) dw;
        ar >> dw; m_bSelectable = (BOOL) dw;
    }
}

/////////////////////////////////////////////////////////////////////////////
// CAnimSprite commands

// Do any initialization after file load etc.
void CAnimSprite::InitFromDIB()
{
    CPhasedSprite::InitFromDIB();
    m_iPhaseHeight = CSprite::GetHeight();
    m_iNumPhases = 1;
    m_iPhase = 0;
}

// Show the sprite parameter dialog
BOOL CAnimSprite::DoDialog()
{
    CSpriteDlg dlg;
    dlg.m_x = m_x;
    dlg.m_y = m_y;
    dlg.m_z = m_z;
    dlg.m_vx = m_vx;
    dlg.m_vy = m_vy;
    dlg.m_bSelectable = m_bSelectable;
    dlg.m_phases = m_iNumPhases;
    dlg.pSprite = this;
    if (dlg.DoModal() == IDOK) {
        // Update sprite params and send notifications
        SetVelocity(dlg.m_vx, dlg.m_vy);
        SetSelectable(dlg.m_bSelectable);
        SetZ(dlg.m_z);
        SetPosition(dlg.m_x, dlg.m_y);
        SetNumPhases(dlg.m_phases);
        return TRUE;
    }
    return FALSE;
}

// Update the position
int CAnimSprite::UpdatePosition(CAnimDoc *pDoc)
{
    int d, x, y;
    x = m_x;
    y = m_y;
    CSize sizeDoc = pDoc->GetSize();
    BOOL bChanged = FALSE;
    if (m_vx != 0) {
        m_dx += m_vx;
        d = m_dx / 100;
        if (d != 0) {
            x = m_x + d;
            m_dx = m_dx % 100;
            bChanged = TRUE;
            if (m_vx > 0) {
                if (x > sizeDoc.cx) x = -GetWidth();
            } else {
                if (x < -GetWidth()) x = sizeDoc.cx;
            }
        }
    }
    if (m_vy != 0) {
        m_dy += m_vy;
        d = m_dy / 100;
        if (d != 0) {
            y = m_y + d;
            m_dy = m_dy % 100;
            bChanged = TRUE;
            if (m_vy > 0) {
                if (y > sizeDoc.cy) y = -GetHeight();
            } else {
                if (y < -GetHeight()) y = sizeDoc.cy;
            }
        }
    }
    if (bChanged) {
        m_iCycle++;
        if (m_iCycle >= 10) {
            m_iCycle = 0;
            // new phase
            if (GetNumPhases() > 1) {
                SetPhase((GetPhase()+1)%GetNumPhases());
            }
        }
        SetPosition(x, y);
        return 1;
    }
    return 0;
}

