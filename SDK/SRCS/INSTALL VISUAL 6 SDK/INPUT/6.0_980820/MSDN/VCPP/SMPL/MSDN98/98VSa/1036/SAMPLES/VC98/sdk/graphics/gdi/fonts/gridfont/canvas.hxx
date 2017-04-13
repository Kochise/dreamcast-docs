#ifndef __CANVAS_HXX_
#define __CANVAS_HXX_

//--------------------------------------------------------------------
// File: Canvas.hxx
//
// Classes:
//      CPoint - POINT with vector operations 
//      CCanvas - Base class for Device contexts
//      CScreenCanvas - Device context for client area or display
//      CPaintCanvas  - Device context for WM_PAINT message handling
//
// History: 22-Jan-1993 Asmusf  Created
//
// Copyright (C) 1993-1997 Microsoft Corp. All Rights reserved
//
//--------------------------------------------------------------------

//========= CPoint ==========================================

class CPoint: public tagPOINT
{
public:
        CPoint()                    {x=0; y=0;  };
        CPoint(COORD X, COORD Y) {x = X; y = Y;     };
        CPoint(POINT pt)     {x = pt.x; y=pt.y; };

        CPoint operator +(CPoint &pt){ return CPoint(x+pt.x, y+pt.y); };
        CPoint operator -(CPoint &pt){ return CPoint(x-pt.x, y-pt.y); };
        CPoint operator *(int c)           { return CPoint(x*c, y*c); };
        CPoint operator /(int c)           { return CPoint(x/c, y/c); };
};

//======== CCanvas ==========================================
// Base class: Any form of canvas
// Inline methods only for speed.

class CCanvas
{
public:
    CCanvas():_hdc(0) 
    {
    }

    operator HDC() { return _hdc; }

    void TextAlign( WORD aligntype )
    {
        SetTextAlign(_hdc, aligntype );
    }

    void Line ( COORD x1, COORD y1, COORD x2, COORD y2 )
    {
        MoveToEx ( _hdc, x1, y1, NULL );
        LineTo   ( _hdc, x2, y2 );
    }

    void Clear ( RECT& rect )
    {
        // Trick: fast erase with Extended Text Out     
        ExtTextOut (_hdc, rect.left, rect.top, ETO_OPAQUE, &rect, TEXT(""), 0, NULL );
    }

    void Text ( int x, int y, LPTSTR buf, int cBuf )
    {
        TextOut ( _hdc, x, y, buf, cBuf );
    }

    void RCText ( LPRECT lprc, LPTSTR buf, int cBuf )
    {
        DrawText ( _hdc, buf, cBuf, lprc, DT_LEFT | DT_WORDBREAK | DT_NOCLIP | DT_NOPREFIX);
    }

    void Char ( int x, int y, TCHAR ch )
    {
        TextOut ( _hdc, x, y,(LPTSTR) &ch, 1 );
    }


	void Circle (int x, int y, int r)
	{
		Ellipse (_hdc,  x-r/2, y-r/2, x+r/2, y+r/2 );
	}

    void Scale(UINT iScale)
    {
        // Logical TWIPS
        SetMapMode (_hdc, MM_ANISOTROPIC);

        SetWindowExtEx (_hdc, MulDiv(INCH1,iScale,100), MulDiv(INCH1,iScale,100), NULL);
        SetViewportExtEx (_hdc, GetDeviceCaps (_hdc, LOGPIXELSX),
                GetDeviceCaps (_hdc, LOGPIXELSY), NULL);
    }
    
    void Scroll(int dx, int dy)
    {
        SetWindowOrgEx(_hdc, dx, dy, NULL );
    }

    void DPtoLP( LPPOINT lppt )
    {
        ::DPtoLP(_hdc, lppt, 1);
    };

    void LPtoDP( LPPOINT lppt )
    {
        ::LPtoDP(_hdc, lppt, 1);
    };

protected:
    void Init ( HDC hdc ) 
    { 
        _hdc = hdc;
        TextAlign(TA_CENTER | TA_BASELINE );
    };

    HDC  _hdc;
};

//======== CScreenCanvas ====================================
// Device Context
// Use for painting on client area other than WM_PAINT

class CScreenCanvas: public CCanvas
{
public:
    CScreenCanvas ( HWND hwnd ): _hwnd(hwnd)
    {
        Init (GetDC ( hwnd ));
    }

    ~CScreenCanvas ()
    {
        ReleaseDC ( _hwnd, _hdc );
    }

protected:

    HWND _hwnd;
};

//======== CPaintCanvas =====================================
// Use for painting after WM_PAINT

class CPaintCanvas: public CCanvas
{
public:
    CPaintCanvas ( HWND hwnd ): _hwnd(hwnd)
    {
        BeginPaint ( _hwnd, &_paint );
        Init ( _paint.hdc );
    }

    ~CPaintCanvas ()
    {
        EndPaint(_hwnd, &_paint );
    }

    RECT GetRect() { return _paint.rcPaint; };
protected:

    PAINTSTRUCT _paint;
    HWND        _hwnd;
};

#endif
