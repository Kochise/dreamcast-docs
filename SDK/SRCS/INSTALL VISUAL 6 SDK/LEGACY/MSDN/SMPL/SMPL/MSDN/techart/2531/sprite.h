// sprite.h : header file
//
// CSprite class
//
//

#ifndef __SPRITE__
#define __SPRITE__

#include "dib.h"

class CSpriteNotifyObj;

class CSprite : public CDIB
{
    DECLARE_SERIAL(CSprite)
public:
    CSprite();
    ~CSprite();

    virtual int GetX() { return m_x;}   // get x
    virtual int GetY() { return m_y;}   // get y
    virtual int GetZ() { return m_z;}   // get z order

    virtual void SetPosition(int x, int y);
    virtual void SetZ(int z);           // set Z order
    virtual void SetNotifyHandler(CSpriteNotifyObj * pNotifyObj)
                    {m_pNotifyObj = pNotifyObj;}

    virtual BOOL Load(LPSTR pszFileName = NULL); // load from disk file
    virtual BOOL Load(CFile *fp);                // load from file
    virtual BOOL HitTest(CPoint point);
    virtual void Serialize(CArchive& ar);
    virtual void Render(CDIB *pDIB, LPRECT pClipRect);
    virtual int MapColorsToPalette(CPalette *pPal);
    virtual void InitFromDIB();

protected:
    int m_x;                    // X Coordinate of top-left corner
    int m_y;                    // Y Coordinate of top-left corner
    int m_z;                    // Z order for sprite
    BYTE m_bTrans;              // transparency pixel value
    CSpriteNotifyObj *m_pNotifyObj; // ptr to a notification object

};

#endif // __SPRITE__
