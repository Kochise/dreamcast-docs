#ifndef __FONT_HXX_
#define __FONT_HXX_

#include "canvas.hxx"

//========== CFont =============================================
class CFont
{      
public: 
        CFont(HFONT hfont);
        CFont(TCHAR * szFace, int iHeight, 
              BOOL fBold = FALSE, BOOL fItalic = FALSE, BOOL fUnder = FALSE);
        ~CFont();
        BOOL Create(LOGFONT& lf);
        BOOL Update(int iHeight, BOOL fBold=FALSE);
        operator HFONT() const
                { return _hfont; }
        BOOL Choose(HWND hwnd);
protected:
        HFONT _hfont;
        BOOL _fDel;
};

//========== CFontSelect =======================================
class CFontSelect
{
public:
        CFontSelect(CCanvas &canvas, HFONT hfont) :
            _canvas(canvas)
        {
            _hfontOld = SelectFont(_canvas, hfont);
        };

        ~CFontSelect()
        {
            // Make sure font is not selected, so it can be deleted
            SelectFont(_canvas, _hfontOld);
        }
protected:
        HFONT _hfontOld;
        CCanvas &_canvas;
};

//========== CBlackPen =======================================
class CBlackPen
{
public:
        CBlackPen(CCanvas &canvas, int iStyle, int iWidth) :
            _canvas(canvas)
        {
            _hPen = CreatePen(iStyle,iWidth,RGB(0,0,0)); 
            _hPenOld = SelectPen(_canvas, _hPen);
        };

        ~CBlackPen()
        {
            // release pen
            _hPen = SelectPen(_canvas, _hPenOld);
            DeleteObject(_hPen);
        }
protected:
        HPEN _hPen;     
        HPEN _hPenOld;
        CCanvas &_canvas;
};

//========== CBrush =====================================
class CBrush
{
public:
		CBrush(CCanvas &canvas, int iStyle=BS_NULL, COLORREF color=RGB(0,0,0))	:
			_canvas(canvas)
		{
			LOGBRUSH lb;
			lb.lbStyle= iStyle;
			lb.lbColor= color;
			lb.lbHatch = NULL;

			_hBrush = CreateBrushIndirect(&lb);

			_hBrushOld = SelectBrush(_canvas, _hBrush);
		}

		~CBrush()
		{
			//release brush
			_hBrush = SelectBrush(_canvas, _hBrushOld);
			DeleteObject(_hBrush);
		}
protected:
		HBRUSH _hBrush;
		HBRUSH _hBrushOld;
		CCanvas _canvas;
};

#endif
