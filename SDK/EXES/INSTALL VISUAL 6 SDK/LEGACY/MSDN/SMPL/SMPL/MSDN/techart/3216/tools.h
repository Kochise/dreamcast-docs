// tools.h
//

/////////////////////////////////////////////////////////////////////////
// CDrawingTool


class CDrawingTool : public CSprite
{
    DECLARE_DYNCREATE(CDrawingTool)
public:
    CDrawingTool();
    virtual ~CDrawingTool();
    void Load(UINT uiID, CPalette* pPal);
    virtual int GetSize()
        {return 0;}
    virtual COLORREF GetColor()
        {return RGB(0,0,0);}

private:

};

class CCrayon : public CDrawingTool
{
public:
    CCrayon();
    virtual ~CCrayon();
    virtual int GetSize()
        {return 5;}
    virtual COLORREF GetColor();

private:

};

class CEraser : public CDrawingTool
{
public:
    CEraser();
    virtual ~CEraser();
    virtual int GetSize()
        {return 50;}
    virtual COLORREF GetColor();

private:

};


