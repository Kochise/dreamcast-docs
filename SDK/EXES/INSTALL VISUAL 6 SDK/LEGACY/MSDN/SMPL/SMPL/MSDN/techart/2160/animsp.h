// animsp.h : header file
//
// CAnimSprite class
// This is a phased sprite with velocity, selctability and a 
// dialog box to manipulate its parameters
//

#ifndef __ANIMSPRITE__
#define __ANIMSPRITE__

#include "phsprite.h"
class CAnimDoc;

class CAnimSprite : public CPhasedSprite
{
    DECLARE_SERIAL(CAnimSprite)
public:
    CAnimSprite();
    ~CAnimSprite();

    int GetVX() { return m_vx;}   // get vx
    int GetVY() { return m_vy;}   // get vy
    BOOL IsSelectable() {return m_bSelectable;}

    void SetVelocity(int vx, int vy)
        {m_vx = vx; m_vy = vy;}
    void SetSelectable(BOOL b)
        {m_bSelectable = b;}
 
    BOOL DoDialog();
    int UpdatePosition(CAnimDoc *pDoc);

    virtual void Serialize(CArchive& ar);
    virtual void InitFromDIB();

protected:
    int m_vx;                   // X velocity
    int m_vy;                   // Y velocity
    int m_dx;                   // x change fraction
    int m_dy;                   // y change fraction
    BOOL m_bSelectable;         // TRUE if sprite can be mouse selected
    int m_iCycle;               // for changing phase
};

#endif // __ANIMSPRITE__
