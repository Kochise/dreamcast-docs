#ifndef __GRID_HXX_
#define __GRID_HXX_

#include "canvas.hxx"
#include "cset.hxx"

#include "font.hxx"

//========== CGridIt ===========================================
class CGridIt
{
public:
        CGridIt(UINT cCol, UINT cRow, SIZE size, POINT pt) :
                _pt(pt), _size(size), _cCol(cCol), _cRow(cRow), 
                _iRow(0), _iCol(0), _cx(pt.x), _cy(pt.y)
        {}
        
        BOOL Done() { return _iCol == _cCol; };

        UINT Row()  { return _iRow; };
        UINT Col()  { return _iCol; };
        
        COORD Cx() { return _cx; }
        COORD Cy() { return _cy; }

        void operator++()
        {
            if( !Done())
            {
                _iRow++;
                _cy+=_size.cy;
                if( _iRow == _cRow )
                {
                    _iRow = 0;
                    _cy = _pt.y;
                    _iCol++;
                    _cx += _size.cx;
                }
            }
        }
protected:
        POINT   _pt;
        SIZE    _size;
        UINT    _cRow;
        UINT    _iRow;
        UINT    _cCol;
        UINT    _iCol;
        COORD _cx, _cy;
};

//========== CGrid =============================================

class CGrid
{
public:
        virtual void Paint(CCanvas& canvas, RECT rc, POINT pt)=0;
protected:
        SIZE    _size;
        UINT    _cCol;
        UINT    _cRow;
};

//========== CLineGrid =========================================

class CLineGrid : public CGrid
{
public:
        CLineGrid(UINT cCol, UINT cRow, SIZE size);
        void SetStyle(int iStyle = PS_DOT );
        void SetWeight(int nWeight = 1 );
        void Paint(CCanvas& canvas, RECT rc, POINT pt);
protected:
        int     _iStyle;
        int     _nWeight;
};

//========== CTextGrid =========================================

class CTextGrid : public CGrid
{
public:
        CTextGrid() { _pCharUsed = NULL;};
        ~CTextGrid() { if (_pCharUsed != NULL) _pCharUsed = (USHORT*)LocalFree(LocalHandle(_pCharUsed));};
        void SetFont(HFONT hfont);
        void SetTextOrg() 
        {
            _ptOrg.x = _size.cx/2;
            _ptOrg.y=7*_size.cy/11;
        };
        
        void SetTextOrg(COORD x, COORD y) 
        {
            _ptOrg.x=x; 
            _ptOrg.y=y;
        };
        
        virtual void Paint(CCanvas& canvas, RECT rc, POINT pt);
        virtual void DrawElement(CCanvas& canvas, COORD x, COORD y, UINT i, UINT j)=0;
        UINT Hittest(POINT pt, POINT ptTest);
		void SetCharTable();
protected:
        POINT   _ptOrg;
        HFONT   _font;
        UINT    _iEltOffset;
		USHORT * _pCharUsed;
};

//========== CCharGrid =============================================

class CCharGrid : public CTextGrid
{
public:
        CCharGrid(UINT cCol, UINT cRow, SIZE size, UINT iEltOffset=0);
        virtual void DrawElement(CCanvas& canvas, COORD x, COORD y, UINT i, UINT j);
//protected:
};


//========== CCodeGrid =============================================

#define HEXADECIMAL 0
#define DECIMAL     1
#define MASKROOT    1

class CCodeGrid : public CTextGrid
{
public:
        CCodeGrid(UINT cCol, UINT cRow, SIZE size, UINT iEltOffset=0);
        void SetFormat(UINT fuFormat=HEXADECIMAL, UINT cDigits=1);
        void DrawElement(CCanvas& canvas, COORD x, COORD y, UINT i, UINT j);
protected:
        UINT    _cDigits;
        TCHAR   _szFormat[5];
};

//========== CBlockFormat =============================================
// formatting elements common to all blocks 


class CBlockFormat
{
public:
        SIZE    _size;          // size of grid cell
        CFont   _fontChar;
        CFont   _fontCode;
		UINT	_fuFormat;
protected:
        CBlockFormat();
};

//========== CFrameFormat =============================================
// formatting elements common to all frames
class CFrameFormat : public CBlockFormat
{
public:
        CFont   _fontHeader;
        CFont   _fontLabel;
protected:
        CFrameFormat();
};       

//========== CPageFormat =============================================
//
#define PAGEELEMS 2
#define PAGEPRINT 4

class CPageFormat : public CFrameFormat
{
public: 
        CPageFormat(UINT fuFormat);
        void SetFormat(UINT fuFormat=HEXADECIMAL);

        CFont   _fontPageNum;
        UINT    _fuFormat;
        POINT   _ptPE[3];
        POINT   _pt;            // "origin" of page proper
};

//========== CCharBlock =============================================
class CCharBlock
{
public:
        CCharBlock(UINT cCol, UINT cRow, UINT iBlockOffset, const CBlockFormat &bf);

        void Paint(CCanvas& canvas, RECT rc, POINT pt);
        UINT Hittest(POINT pt, POINT ptTest);
        void SetFormat(UINT fuFormat=HEXADECIMAL);
        void SetFont(HFONT font);
protected:
        CLineGrid       _Line;
        CCharGrid       _Char;
        CCodeGrid       _Code;
};


//========== CBlockFrame =============================================

class CBlockFrame : public CCharBlock
{
public:
        CBlockFrame(UINT cCol, UINT cRow, POINT pt, UINT iBlockOffset, 
                                    TCHAR *szHeader, const CFrameFormat &ff);
        ~CBlockFrame();
        void Paint(CCanvas& canvas, RECT rc, POINT pt);

protected:
        void Draw(CCanvas& canvas, POINT pt);
        TCHAR *         _szHeader;
        SIZE            _size;
        UINT            _cCol;
        UINT            _cRow;   
        HFONT           _fontHeader;
        CCodeGrid       _Cols;

        // optional
        CCodeGrid *     _pRows;
};
//========== CPage ===================================================

class CPage
{
public:
        CPage(HINSTANCE hInst, CPageFormat& pf, UINT nPage=0);
        ~CPage();
      
        void Paint(CCanvas& canvas, RECT rc);
        void SetFormat(UINT fuFormat=HEXADECIMAL);
        void SetFont( HFONT hfont);
        UINT Hittest( POINT pt);
        
protected:
        UINT InitPage(UINT nPage);
        HINSTANCE       _hInst;
        CPageFormat&    _pf;

        UINT            _cBlock;        // 0..4
        CBlockFrame*    _apBlock[4];    // at most 4 blocks/page
        POINT           _aptBlock[4];

        CCodeGrid       _PageHeadR;     // Right header 
        CCodeGrid       _PageHeadL;     // Left  header 
        CCodeGrid       _PageNums;      // Page number
};

//========== CFontRange ===================================================

class CFontRange
{
friend class CTextGrid;
public:
        void SetFontRange(HWND hwnd, HFONT hfont);
        ~CFontRange();
        BOOL IsPageUsed(UINT nPage) { return _fPageUsed[nPage]; };
              
private:
        void SwapShort (PUSHORT p);
        void SwapULong (PULONG p);
        BOOL CountUCSegments(HDC hdc);

        UINT _fPageUsed[256];
};

//========== CModel ==================================================
#define USEDONLY    0
#define ALLPAGES    1

class CModel
{
public:
        CModel(HINSTANCE hInst, HWND hwnd, UINT fuFormat=HEXADECIMAL, UINT fUsedPageOnly=USEDONLY);
        ~CModel();

        // iteration
        void NextPage();
        void PrevPage();
        void NextSection();
        void PrevSection();
        BOOL CanNextPage()      { return _iPage + 1 < _macPage; };
        BOOL CanPrevPage()      { return _iPage;                };
        BOOL CanNextSection()   { return _iPage +16 < _macPage; };
        BOOL CanPrevSection()   { return _iPage + 1 >= 16;      };
        UINT GetPage()          { return _iPage;                };
        void SetPage(UINT nPage);
        UINT GetMaxPage()       { return _macPage; };
        UINT GetMaxSection()    { return _macPage / 16; };

        // Layout
        void Paint(CCanvas& canvas, RECT rc){_pPage->Paint(canvas, rc);};
        UINT Hittest( POINT pt);
        void GetLineSize( SIZE * psize) { psize->cx = 4*INCH2/5;
                                          psize->cy = INCH2;
                                        }

        // Formatting
        BOOL ChooseFont(HWND hwnd);
        HFONT GetFont();
        BOOL CreateFont(LOGFONT &lf);
        void GetFormat(UINT &fuFormat);
        void SetFormat(UINT fuFormat=HEXADECIMAL);
        void GetPageMode(UINT &fPageMode);
        void SetPageMode(UINT fPageMode=USEDONLY);
		void SetCSet(CSet * pCset);
		BOOL IsModelPageUsed(UINT nPage) {return _fr.IsPageUsed(nPage);}

protected:
        UINT            _iPage;
        UINT            _macPage;
        CPageFormat     _pf;
        CPage *         _pPage;
        HINSTANCE       _hInst;
        UINT            _fPageMode;
        CFontRange      _fr;
};



#endif
