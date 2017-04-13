#ifndef _BOX_HXX_
#define _BOX_HXX_

#include "font.hxx"
#include "grid.hxx"

//====== CTextField =============================
class CTextField
{
public:
        CTextField(TCHAR *sz);
        void Paint(CCanvas &canvas, int x, int y);
        void GetExtent(CCanvas& canvas, SIZE *psize);
        void SetFont(HFONT hfont);
        UINT Hittest(CCanvas& canvas, POINT pt);
protected:
        HFONT _font;
        TCHAR *_sz;
};

//====== CBoxFormat =============================
class CBoxFormat : public CBlockFormat
{
public:
        CFont _fontAlias;
        CFont _fontCtype;
        CBoxFormat(SIZE sizeChar);
};


//====== CBox ===================================
class CBox 
{
public:
        CBox( CBoxFormat &bxf, UINT iChar, HFONT hfont ) ;
        // CBox(CBoxFormat &bxf, UINT iChar);
        //~CBox();
        void Paint(CCanvas &canvas, POINT pt, RECT rc);
        UINT Hittest(CCanvas &canvas, POINT pt);
        SIZE& GetSize() { return _sizeBox; };
		void SetFormat(UINT fuFormat) {_fuFormat = fuFormat; return; };
protected:
        CCharBlock _Block;
        SIZE  _sizeBox;

        CFont _fontBlock;
        CTextField _Alias;
        UINT _iChar;
        CBoxFormat &_bxf;
		UINT _fuFormat;
};

#endif
