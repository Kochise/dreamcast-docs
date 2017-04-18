// ltbulb.h

#ifndef _LTBULB_
#define _LTBULB_

class CLightBulb : public CObject
{
public:
    CLightBulb();
    ~CLightBulb();
    BOOL Create(UINT uiResourceID, CPalette* pPal = NULL);
    void Draw(CDC* pDC, int x, int y);

protected:
    CDIB m_dibImage;
    CPalette* m_pPal;
};

#endif // _LTBULB_
