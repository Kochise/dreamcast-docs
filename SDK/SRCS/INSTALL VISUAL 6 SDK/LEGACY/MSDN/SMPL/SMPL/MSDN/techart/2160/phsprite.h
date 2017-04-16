// phsprite.h : header file
//
// CPhasedSprite class
//
//

#ifndef __PHSPRITE__
#define __PHSPRITE__

#include "sprite.h"

class CPhasedSprite : public CSprite
{
    DECLARE_SERIAL(CPhasedSprite)
public:
    CPhasedSprite();
    ~CPhasedSprite();

    virtual int GetHeight() {return m_iPhaseHeight;}
    virtual void GetRect(LPRECT pRect); 
    virtual int GetNumPhases() {return m_iNumPhases;}
    virtual int GetPhase() {return m_iPhase;}

    virtual BOOL SetPhase(int iPhase);
    virtual BOOL SetNumPhases(int iNumPhases);

    virtual BOOL HitTest(CPoint point);
    virtual void Render(CDIB *pDIB, LPRECT pClipRect);
    virtual void Serialize(CArchive& ar);
    virtual void InitFromDIB();

protected:
    int m_iPhaseHeight;     // height of bounding rectangle
    int m_iNumPhases;       // number of images phases in the DIB
    int m_iPhase;           // current phase
};

#endif // __PHSPRITE__
