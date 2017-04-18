#include <windows.h>
#include <windowsx.h>
#include <string.h>
#include "app.h"

#include "grid.hxx"

// These are global variables set by CFontRange::SetFontRange()
// and used by CTextGrid::SetCharTable(). This is safe as only
// one font is selected at a given time by the program.

int             vSegCount;
USHORT *        vStartCount;
USHORT *        vEndCount;

CSet   * 		vpCSet;

//+--------------------------------------------------------
// Class:       CFontSelect
//
// Purpose:     Select/Deselect a font
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------

// pure inline

//+--------------------------------------------------------
// Class:       CGridIt
//
// Purpose:     Iterate over a grid
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------

// pure inline

//+--------------------------------------------------------
// Class:       CLineGrid
//
// Purpose:     Create an n x m Grid of lines
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------

CLineGrid::CLineGrid(UINT cCol, UINT cRow, SIZE size ) 
{
    _size = size;
    _cCol = cCol;
    _cRow = cRow;
    SetStyle();
    SetWeight();
}

void CLineGrid::SetStyle(int iStyle)
{
    _iStyle = iStyle;
}

void CLineGrid::SetWeight(int nWeight)
{
    _nWeight = nWeight*20;  // internal twips, API is points
}

void CLineGrid::Paint(CCanvas& canvas, RECT rc, POINT pt)
{
    int cx, cy;
    UINT i;

    // set up pen
    CBlackPen pen(canvas, _iStyle, _nWeight);

    // Draw the grid
    for(cx = pt.x, i=0; i<=_cCol; i++, cx+=_size.cx )
    {
        if( cx >= rc.left && cx <= rc.right )
        {
            canvas.Line(cx, pt.y,
                        cx, pt.y+_cRow*_size.cy);
        }
    }
    for(cy = pt.y, i=0; i<=_cRow; i++, cy+=_size.cy )
    {
        if( cy >= rc.top && cy <= rc.bottom )
        {
            canvas.Line(pt.x,                cy,
                        pt.x+_cCol*_size.cx, cy);
        }
    }
}

//+--------------------------------------------------------
// Class:       CTextGrid
//
// Purpose:     Create an n x m grid of textual elements
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------

void CTextGrid::SetFont(HFONT hfont)
{
    _font = hfont;
}

void CTextGrid :: Paint(CCanvas& canvas, RECT rc, POINT pt)
{
    // Choose text alignment
    SetTextAlign(HDC(canvas), TA_BASELINE|TA_CENTER);

    CFontSelect fs(canvas, _font);

    for( CGridIt It( _cCol, _cRow, _size, pt ); !It.Done(); ++It)
    {
        if( It.Cx()+_size.cx > rc.left && It.Cx() < rc.right &&
                It.Cy()+_size.cy > rc.top && It.Cy() < rc.bottom )
        {
            DrawElement(canvas, It.Cx()+_ptOrg.x, It.Cy()+_ptOrg.y, 
                                It.Col(), It.Row());
        }
    }
}

UINT CTextGrid::Hittest(POINT pt, POINT ptTest)
{
    for( CGridIt It( _cCol, _cRow, _size, pt ); !It.Done(); ++It)
    {
        if( It.Cx() <= ptTest.x && It.Cy() <= ptTest.y  &&
            It.Cx()+_size.cx > ptTest.x && It.Cy() +_size.cy > ptTest.y)
            {
                return   _cRow* It.Col()+ It.Row() + _iEltOffset;
            }
    }
    return 0xFFFF;
}

void CTextGrid::SetCharTable()
{
     USHORT i;
	 UINT imin = _iEltOffset;
	 UINT imax = imin + _cCol*_cRow - 1;

	 // Make sure the block is used by the font
	 if (_pCharUsed != NULL)
	     LocalFree (LocalHandle(_pCharUsed));
	 // Allocate buffer and make it not used (LPTR put zero in memory)
	 if ((_pCharUsed = (USHORT *)LocalAlloc(LPTR, _cCol*_cRow*sizeof(USHORT))) == NULL)
	     return;
	 if (imin > vEndCount[vSegCount-1] || imax < vStartCount[0])
	     return;
	 for (i = 0; i < vSegCount; i++)
	     {
	     if (imax < vStartCount[i])	 // no more useful cmap ranges
	         break;
	     if (imin <= vEndCount[i] && imax >= vStartCount[i]) // check for include
		     {
	         UINT icur = imin;
	         while (icur++ < vStartCount[i]);  // scan until reaching vStartCount
			 icur--;
			 while (icur <= imax && icur <= vEndCount[i])
				 _pCharUsed[icur++ - imin] = TRUE;
			 }
		  }
}	

//+--------------------------------------------------------
// Class:       CCharGrid
//
// Purpose:     Create an n x m Grid of single characters
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------

CCharGrid :: CCharGrid(UINT cCol, UINT cRow, SIZE size, UINT iEltOffset) 
{
    _size  = size;
    _cCol  = cCol;
    _cRow  = cRow;
    _iEltOffset = iEltOffset;
    SetTextOrg();
}

#define NBSP 0x00A0	// no break space

void CCharGrid::DrawElement(CCanvas& canvas, COORD x, COORD y, UINT i, UINT j)
{
	WORD iChar = _cRow*i+j+_iEltOffset;
#ifdef UNICODE
	static CCTypeSet Combining(0,0,C3_NONSPACING || C3_DIACRITIC || C3_VOWELMARK);
	static CCTypeSet Alpha(C1_ALPHA, 0, 0);
#endif

	if ( vpCSet && vpCSet->In(iChar) )
	{
    	SetTextColor(canvas, RGB(128,0,128));
	}
    if (_pCharUsed == NULL || _pCharUsed[_cRow*i+j]) // if char exists draw it
	{
#ifdef UNICODE
		if( Combining.In(iChar) && !Alpha.In(iChar) )
		{
			TCHAR pch[2] = { iChar,0 };
			CFontSelect fs(canvas, _font);
			//SIZE size;
    		//GetTextExtentPoint(canvas, pch, 2, &size);
			//canvas.Text(x, y, pch, 2 );
			canvas.Char(x+_size.cx/4/*+size.cx/2*/,y, iChar);

		    // set up pen												
		    CBlackPen pen(canvas, PS_DOT, 0);
			CBrush brush(canvas);

			// draw dotted circle
			int r = 7*_size.cx/16;	 
			canvas.Circle(x, y-r/2, r);
		}
		else
		{
        	canvas.Char(x, y, iChar);
		}
#else
		canvas.Char(x, y, iChar);
#endif
	}
    SetTextColor(canvas, RGB(0,0,0));
}

//+--------------------------------------------------------
// Class:       CCodeGrid
//
// Purpose:     Create an n x m Grid, numbered in sequence
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------
CCodeGrid :: CCodeGrid(UINT cCol, UINT cRow, SIZE size, UINT iEltOffset) 
{
    _size  = size;
    _cCol  = cCol;
    _cRow  = cRow;
    _iEltOffset = iEltOffset;
    SetTextOrg();
    SetFormat();
}

void CCodeGrid :: SetFormat(UINT fuFormat, UINT cDigits)
{
    _cDigits = cDigits;

    _szFormat[0]='%';
    if( fuFormat == DECIMAL )
    {
        _cDigits = 4;       // Constraint:
                            // This format for Decimal
        _szFormat[1]='3';   // really only works with _cDigits == 4
        _szFormat[2]='d';   // 
        _szFormat[3]=' ';   // (blank padding for better positioning)
    } 
    else // 
    {
        _szFormat[1]='0';
        _szFormat[2]=_cDigits%10+'0';
        _szFormat[3]='X';
    }
    _szFormat[4]='\0';
}

void CCodeGrid::DrawElement(CCanvas &canvas, COORD x, COORD y, UINT i, UINT j)
{
     TCHAR sz[10];
	 if (_pCharUsed == NULL || _pCharUsed[_cRow*i+j]) // if char exists draw it
         {
         wsprintf( sz,_szFormat, (_cRow*i+j+_iEltOffset));
         canvas.Text(x, y, sz, _cDigits);
		 }
}


//+--------------------------------------------------------
// Class:       CCharBlock
//
// Purpose:     Create an n x m lined block of characters and codes
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------

CCharBlock::CCharBlock(UINT cCol, UINT cRow, UINT iBlockOffset, const CBlockFormat &bf) :
     _Line(cCol, cRow, bf._size),
     _Char(cCol, cRow, bf._size, iBlockOffset),
     _Code(cCol, cRow, bf._size, iBlockOffset)
{
     // LINE GRID
     _Line.SetStyle(PS_SOLID);

     // LARGE CHARACTER each cell
     _Char.SetFont(bf._fontChar); 

     // CODE POINT label each cell
     _Code.SetTextOrg(bf._size.cx/2, 9*bf._size.cy/10);
     _Code.SetFont(bf._fontCode);
     _Code.SetFormat(HEXADECIMAL,4);
}

void CCharBlock::Paint(CCanvas& canvas, RECT rc, POINT pt)
{
    _Line.Paint(canvas, rc, pt);
#ifdef UNICODE            
    _Char.SetCharTable();
    _Code.SetCharTable();
#endif            
    _Char.Paint(canvas, rc, pt);
    _Code.Paint(canvas, rc, pt);
}

UINT CCharBlock::Hittest(POINT pt, POINT ptTest)
{
    return _Code.Hittest(pt, ptTest);
}

void CCharBlock :: SetFormat(UINT fuFormat)
{
    _Code.SetFormat(fuFormat&DECIMAL,4);
}

void CCharBlock::SetFont(HFONT font)
{
    _Char.SetFont(font);
}

//+--------------------------------------------------------
// Class:       CBlockFrame
//
// Purpose:     Create an n x m frame around a block of characters
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------

CBlockFrame::CBlockFrame(UINT cCol, UINT cRow, POINT pt, UINT iBlockOffset, 
                                TCHAR * szHeader, const CFrameFormat &ff):
     CCharBlock(cCol, cRow, iBlockOffset, ff ),
     _size(ff._size),
     _Cols(cCol,    1, ff._size, iBlockOffset/16),
     _cRow(cRow),
     _cCol(cCol)
{

     // COLUMN label above first row
     _Cols.SetFormat(HEXADECIMAL,3);
     _Cols.SetFont(ff._fontLabel);      


     // if not first block on page, suppress row labels
     if( iBlockOffset % 0x100 )
     {
        _pRows = NULL;
     }
     else
     {
        // ROW label to left of first column
        _pRows = new CCodeGrid(1, cRow,  ff._size);
        _pRows->SetFont(ff._fontLabel); 
     }

     // BLOCK HEADER
     _szHeader = new TCHAR[lstrlen(szHeader)+sizeof(TCHAR)];
     lstrcpy(_szHeader, szHeader);
     _fontHeader = ff._fontHeader;

}

CBlockFrame::~CBlockFrame()
{
    delete _pRows;
    delete _szHeader;
}


void CBlockFrame::Paint(CCanvas& canvas, RECT rc, POINT pt)
{
    Draw(canvas, pt);
    {
        POINT ptCols = {pt.x, pt.y-_size.cy};
        _Cols.Paint(canvas, rc, ptCols);  
    } 
    CCharBlock::Paint(canvas, rc, pt);  
    
    // these two are optional. Test first, then draw
    if(_pRows )
    {   
        POINT ptRows = {pt.x-_size.cx, pt.y};
        _pRows->Paint(canvas, rc, ptRows);
    }   
}

void CBlockFrame::Draw(CCanvas& canvas, POINT pt)
{
    UINT dy = 3*_size.cy/2;     // height of short uprights
    UINT cx = _cCol*_size.cx;   
    UINT cy = _cRow*_size.cy;
	RECT rc;
        
    // set up pen
    CBlackPen pen(canvas, PS_SOLID, 40);    // Solid Black 40/20 points

    //Draw block divider lines
    
    canvas.Line(pt.x,    pt.y-dy, pt.x,    pt.y+cy);  // left edge
    canvas.Line(pt.x+cx, pt.y-dy, pt.x+cx, pt.y+cy);  // right edge
    canvas.Line(pt.x,    pt.y,    pt.x+cx, pt.y);     // top edge
    canvas.Line(pt.x,    pt.y+cy, pt.x+cx, pt.y+cy);  // bottom
    
    CFontSelect fs(canvas, _fontHeader);

    SetTextAlign(canvas, TA_BASELINE|TA_LEFT);
	rc.left = pt.x + _size.cx/12;
	rc.top = pt.y - 6*_size.cy/5;
	rc.right = pt.x + cx - _size.cx/12;
	rc.bottom = pt.y;
    canvas.RCText(&rc,
    			  _szHeader,
                 lstrlen(_szHeader));
}

// The following Array contains the widhts of the Unicode blocks in
// columns. Each Block has a corresponding entry in the stringtable
// giving its block header. "Unassigned" blocks can span page boun-
// daries. 

static UINT aBlockWidth[]=
{
    2,6,2,6,   // 0000
    8,8,       // 0100
    5,6,5,     // 0200
    7,6,3,     // 0300
    16,        // 0400
    3,6,7,     // 0500
    16,        // 0600
    32,        // 0700 - 08FF 
    8,8,       // 0900
    8,8,       // 0A00
    8,8,       // 0B00
    8,8,       // 0C00
    8,8,       // 0D00
    8,8,       // 0E00
    16,        // 0F00
    10,6,  	   // 1000
	16,		   // 1100
    192,       // 1200 - 1DFF
	16,		   // 1E00
	16,		   // 1F00
    7,3,3,3,   // 2000
    5,4,7,     // 2100
    16,        // 2200
    16,        // 2300
    4,2,10,    // 2400
    8,2,6,     // 2500
    16,        // 2600
    12,4,      // 2700
    128,       // 2800 - 2FFF 
    4,6,6,     // 3000
    3,6,1,6,   // 3100
    16,        // 3200
    16,        // 3300
    144,       // 3400 - 3CFF
    3,13,      // 3D00
    96,        // 3E00 - 43FF
	16,		   // 4400
	144,	   // 4500 - 4DFF
    82*16,     // 4E00 - 9FFF
    64*16,     // A000 - DFFF
    25*16,     // E000 - F8FF
    32,        // F900 - FAFF
	5,11,	   // FB00 
    32,        // FC00 - FDFF 
    2,5,9,     // FE00
    15,1,      // FF00
    200        // Sentinel
};

//+--------------------------------------------------------
// Class:       CBlockFormat
//
// Purpose:     Block formatting
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------

CBlockFormat::CBlockFormat() :
    _fontCode    (TEXT("Arial Narrow"), -6),
#ifdef UNICODE
    _fontChar    (TEXT("Lucida Sans Unicode"), -16, TRUE)
#else
    _fontChar    (TEXT("Lucida Sans"), -16, TRUE)
#endif
{
};

//+--------------------------------------------------------
// Class:       CFrameFormat
//
// Purpose:     Frame formatting
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------

CFrameFormat::CFrameFormat() :
    _fontHeader  (TEXT("Arial"), -12, TRUE),
    _fontLabel   (TEXT("Arial"), -10, TRUE)
{
}

//+--------------------------------------------------------
// Class:       CPageFormat
//
// Purpose:     Page formatting
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------
CPageFormat::CPageFormat(UINT fuFormat) :
    _fontPageNum (TEXT("Times New Roman"), -10, FALSE)
{
    _size.cx =  4*INCH2/5;
    _size.cy =  INCH2;

    SetFormat(fuFormat);
}

void CPageFormat::SetFormat(UINT fuFormat)
{
    _fuFormat = fuFormat;

    if( fuFormat & PAGEPRINT )
    {
        _pt.x=     INCH2+(INCH2*7)/10;
        _pt.y=     INCH1+(INCH1*7)/10;
    } 
    else
    {
        _pt.x=     INCH2;
        _pt.y=     INCH1;
    }

    // locations of headers / footers
    _ptPE[0].x = _pt.x-_size.cx; 
    _ptPE[0].y = _size.cy/2;
    _ptPE[1].x = _pt.x+_size.cx*16; 
    _ptPE[1].y = _size.cy/2;
    _ptPE[2].x = _pt.x+(_size.cx*15)/2;
    _ptPE[2].y = _pt.y+(_size.cy*33)/2;
}

//+--------------------------------------------------------
// Class:       CPage
//
// Purpose:     One or more blocks
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------
CPage::CPage(HINSTANCE hInst, CPageFormat &pf, UINT nPage) :
    _cBlock(0),
    _pf(pf),
    _hInst(hInst),
    _PageHeadL (1, 1, pf._size,nPage*256      ),
    _PageHeadR (1, 1, pf._size,(nPage+1)*256-1),
    _PageNums  (1, 1, pf._size,nPage+1        )        
                                // page numbers are 1 based on output
{
    // Set up page elementss

    _PageHeadL.SetFont(pf._fontLabel);
    _PageHeadR.SetFont(pf._fontLabel);
    _PageNums.SetFont(pf._fontPageNum);

    InitPage( nPage);
    SetFormat(_pf._fuFormat);
}

CPage::~CPage()
{
    while( _cBlock )
    {
        delete _apBlock[--_cBlock];
    }   
}



void CPage::SetFormat(UINT fuFormat)
{
    // set it
    _pf.SetFormat(fuFormat);

    // apply it
    for( UINT i = 0; i < _cBlock ; ++i )
    {
        _apBlock[i]->SetFormat(fuFormat&MASKROOT);
    }

    _PageHeadL.SetFormat(HEXADECIMAL, 4);
    _PageHeadR.SetFormat(HEXADECIMAL, 4);
    _PageNums.SetFormat(DECIMAL);
}


void CPage::Paint(CCanvas& canvas, RECT rc)
{
    for( UINT i = 0; i < _cBlock; ++i )
    {
        _apBlock[i]->Paint(canvas, rc, _aptBlock[i]);
    }

    if( _pf._fuFormat & PAGEELEMS )
    {
        _PageHeadL.Paint(canvas, rc, _pf._ptPE[0]);
        _PageHeadR.Paint(canvas, rc, _pf._ptPE[1]);
        _PageNums.Paint (canvas, rc, _pf._ptPE[2]);
    }   
}

UINT CPage::Hittest(POINT ptTest)
{
    UINT uHit = 0xFFFF;

    for( UINT i = 0; i < _cBlock && uHit ==0xFFFF ; ++i )
    {
        uHit = _apBlock[i]->Hittest(_aptBlock[i], ptTest);
    }
    return uHit;
}

//-- protected member functions...

UINT CPage::InitPage(UINT nPage)
{
    UINT iEnd = 0;
    TCHAR szBlockHeader[40];
    UINT i;
    POINT ptBlock=_pf._pt;

    // Set up blocks

    for( i=0; i < sizeof(aBlockWidth)/sizeof(UINT); i++ )
    {
        if( nPage*16 < (iEnd+=aBlockWidth[i]) )
        {
            break;
        }
    }
    UINT iStart = max(nPage*16, iEnd-aBlockWidth[i]);

    do
    {
        LoadString(_hInst, i, szBlockHeader, 40);
        _apBlock[_cBlock]= new CBlockFrame(
                  min( aBlockWidth[i],      // grid width in columns
                       (nPage+1)*16-iStart),// (but at most to end of page)
                  16,                       // cRow always 16
                  ptBlock,                  // grid origin
                  iStart*16,                // first char offset
                  szBlockHeader,            // header string
                  _pf);                     // common formatting

        _aptBlock[_cBlock] = ptBlock;
        _cBlock++;

        ptBlock.x+=_pf._size.cx*aBlockWidth[i];
        iStart=iEnd;
    } 
    while(
            (i++ < sizeof(aBlockWidth)/sizeof(UINT))
                &&
            ((nPage+1)*16 >= (iEnd+=aBlockWidth[i]))
                &&
            (_cBlock < 4)  
         );


    return _cBlock;
}


void CPage::SetFont(HFONT hfont)
{
    for( UINT i = 0; i < _cBlock ; ++i )
    {
        _apBlock[i]->SetFont(hfont);
    }
}

//+--------------------------------------------------------
// Class:       CModel  
//
// Purpose:     Iterator over pages
//
// History:     22-Jan-1993     asmusf  created
//----------------------------------------------------------
CModel::CModel(HINSTANCE hInst, HWND hwnd, UINT fuFormat, UINT fPageMode) :
    _iPage(0),
#ifdef UNICODE
    _macPage(0x100),
#else
    _macPage(1),
#endif
    _pf(fuFormat),
    _hInst(hInst),
    _fPageMode(fPageMode)
{
    _pPage = new CPage(hInst, _pf, _iPage);
    _fr.SetFontRange(hwnd, _pf._fontChar);
}

CModel::~CModel()
{
    delete _pPage;      
}

void CModel::NextPage()
{

    if (_fPageMode == ALLPAGES)
        SetPage(_iPage+=(_iPage+1<_macPage? 1 : 0));
	else
	    {
	   	int iNewPage = _iPage;
        while (!_fr.IsPageUsed(++iNewPage) && iNewPage < (int)_macPage);// scan until first found
		if (iNewPage < (int)_macPage)							   // change only if under boundary
		    SetPage(_iPage = (UINT)iNewPage);
		}
}

void CModel::PrevPage()
{
    if (_fPageMode == ALLPAGES)
        SetPage(_iPage-=(_iPage? 1 : 0));
	else
	    {
	   	int iNewPage = _iPage;
        while (!_fr.IsPageUsed(--iNewPage) && iNewPage >= 0); // scan until first found
		if (iNewPage >= 0)                                // change only if above boundary
		    SetPage(_iPage = (UINT)iNewPage);
		}
}

void CModel::NextSection()
{
	_iPage+=(_iPage+16<_macPage? 16 : 0);			 // increment by 16 pages
    if (_fPageMode == ALLPAGES || _fr.IsPageUsed(_iPage)) // if in USEDONLY mode and
        SetPage(_iPage);							 // the page is not used
	else
		NextPage();
}													 // we skip to the next

void CModel::PrevSection()
{
    _iPage-=(_iPage >= 16 ? 16 : 0);
    if (_fPageMode == ALLPAGES || _fr.IsPageUsed(_iPage)) // if in USEDONLY mode and
        SetPage(_iPage);							 // the page is not used
	else
		PrevPage();									 // we skip to the previous
}

void CModel::SetPage(UINT nPage)
{
    delete _pPage;
    _pPage = new CPage(_hInst, _pf, nPage);     
}

void CModel::GetFormat(UINT &fuFormat) 
{
    fuFormat=_pf._fuFormat; 
}

void CModel::SetFormat(UINT fuFormat) 
{
    _pPage->SetFormat(fuFormat);
}

HFONT CModel::GetFont()
{
    return _pf._fontChar;
}

BOOL CModel::CreateFont(LOGFONT &lf)
{
    if(_pf._fontChar.Create(lf))
    {
         _pPage->SetFont(_pf._fontChar);
         return TRUE;
    }
    return FALSE;
}

BOOL CModel::ChooseFont(HWND hwnd)
{
    if(_pf._fontChar.Choose(hwnd))
    {
		 _fr.SetFontRange(hwnd, _pf._fontChar);
         _pPage->SetFont(_pf._fontChar);
         return TRUE;
    }
    return FALSE;
}

UINT CModel::Hittest( POINT pt)
{
    return _pPage->Hittest( pt);
}

void CModel::GetPageMode(UINT &fPageMode) 
{
    fPageMode = _fPageMode; 
}

void CModel::SetPageMode(UINT fPageMode) 
{
    _fPageMode = fPageMode;
	if (fPageMode == USEDONLY && !_fr.IsPageUsed(_iPage))//if the current page is empty
	    {
		UINT iCurrentPage = _iPage;
		NextPage();									//we skip to next
		if (iCurrentPage == _iPage)					//if there is no next page
		    PrevPage();								//we go to prev (has to be one)
		}
}

void CModel :: SetCSet(CSet * pCSet)
{
	vpCSet = pCSet;
}

//+----------------------------------------------------------------------
// Class	CFontRange
//
// Purpose:	Set character coverage of the target font
//
// History:	6-Dec-1993	michelsu created
//-----------------------------------------------------------------------
void CFontRange::SetFontRange(HWND hwnd, HFONT hfont)
{
    CScreenCanvas scanvas(hwnd);     // provide the DC
    CFontSelect fs(scanvas, hfont);

    USHORT   i;
 
    for (i=0;i<256;i++)
        _fPageUsed[i]=FALSE;         // assume no page used
#ifdef UNICODE
    if (CountUCSegments(scanvas))    // set page used flag for relevant pages
        for (i=0;i<vSegCount;i++) _fPageUsed[(vStartCount[i] & 0xFF00) >> 8] = TRUE;
    else                             // if the font is not TrueType, set only the 1st page
        _fPageUsed[0] =TRUE;
#else
    _fPageUsed[0] =TRUE;
#endif
}

CFontRange::~CFontRange()
{
    if (vStartCount != NULL)
        LocalFree (LocalHandle (vStartCount));
    if (vEndCount != NULL)
        LocalFree (LocalHandle (vEndCount));
}
//+----------------------------------------------------------------------
// Class	CFontRange
//
// Purpose:	Get character coverage of the target font (_pf._fontChar)
//
// History:	6-Dec-1993	michelsu created (borrowed in large from TTFONTS)
//-----------------------------------------------------------------------
BOOL CFontRange::CountUCSegments(HDC hdc)
{
#define CMAPHEX	0x70616d63 // = "cmap" (reversed)
#define NBYTES   256
#define OFFSETERROR 0
#define MBERROR TEXT("Application Error.")
#define MBERRORFLAGS MB_OK | MB_ICONHAND

typedef struct tagTABLE{
    USHORT platformID;
    USHORT encodingID;
    ULONG  offset;
} TABLE, *PTABLE;

typedef struct tagSUBTABLE{
    USHORT format;
    USHORT length;
    USHORT version;
    USHORT segCountX2;
    USHORT searchRange;
    USHORT entrySelector;
    USHORT rangeShift;
} SUBTABLE, *PSUBTABLE;

    DWORD       cbData;
    USHORT      aShort[2];
    DWORD       nBytes;
    USHORT      i, nTables;
    PTABLE      pTable;
    PSUBTABLE   pSubTable;
    ULONG       offset,offsetFormat4;
    BYTE        buffer[NBYTES];

    // find number of encoding tables, second long in cmap
    nBytes = GetFontData(hdc, CMAPHEX, 0, aShort, 4);
    if (nBytes == GDI_ERROR || nBytes == 0)	//GDI error or no cmap table
        return FALSE;
    nTables = aShort[1];
    SwapShort (&nTables);

    // limit ourself to 32 encoding tables (largely enough)
    cbData = nTables * sizeof(TABLE);
    if (cbData >NBYTES)
    	{
    	MessageBox (NULL, TEXT("cbData >NBYTES"),MBERROR , MBERRORFLAGS);
    	return FALSE;
    	}

    // get array of encoding tables.
    // Check each one for PlatformId = 3, Encoding ID = 1.
    nBytes=GetFontData (hdc, CMAPHEX, 4, buffer, cbData);
    pTable = (PTABLE)buffer;
    offsetFormat4 = OFFSETERROR;
    for (i = 0; i< nTables; i++)
    	{
        SwapShort (&(pTable->encodingID));
        SwapShort (&(pTable->platformID));
        if ((pTable->platformID == 3)&&(pTable->encodingID == 1))
            {
            offsetFormat4 = pTable->offset;
            SwapULong (&offsetFormat4);
            break;
            }
        pTable++;
        }
    if (offsetFormat4 == OFFSETERROR) //Can not find 3,1 subtable 
        return FALSE;

    /* Get the beginning of the subtable, especially the segment count */
    nBytes=GetFontData (hdc, CMAPHEX, offsetFormat4, buffer, sizeof(SUBTABLE));
    pSubTable = (PSUBTABLE) buffer;
    SwapShort (&(pSubTable->format));
    SwapShort (&(pSubTable->segCountX2));
    if (pSubTable->format != 4)
        {
        MessageBox (NULL, TEXT("format !=4"), MBERROR, MBERRORFLAGS);
        return FALSE;
        }
    vSegCount = pSubTable->segCountX2 / 2;

    /* Now that we know how many segments that the font contains,
     *  free up the old memory, and realloc. the two global arrays.
     */
    if (vStartCount != NULL)
        LocalFree (LocalHandle (vStartCount));
    if (vEndCount != NULL)
        LocalFree (LocalHandle (vEndCount));
    vStartCount = (USHORT *)LocalAlloc (LPTR, vSegCount * sizeof(USHORT));
    vEndCount = (USHORT *)LocalAlloc (LPTR, vSegCount * sizeof(USHORT));
    if ((vStartCount == NULL) || (vEndCount == NULL))
        {
        MessageBox (NULL, TEXT("LocalAlloc failed"), MBERROR, MBERRORFLAGS);
        return FALSE;
        }

    /* read in the array of endCount values */
    offset = offsetFormat4
           + (7 * sizeof (USHORT));  /* skip constant # bytes in subtable */
    cbData = vSegCount * sizeof (USHORT);
    nBytes=GetFontData (hdc, CMAPHEX, offset, vEndCount, cbData );
    for (i = 0; i<vSegCount; i++)
        SwapShort (& (vEndCount[i]));

    /* read in the array of startCount values */
    offset = offsetFormat4
           + (7 * sizeof (USHORT))   /* skip constant # bytes in subtable */
           + (vSegCount * sizeof (USHORT)) /* skip endCount array */
           + sizeof (USHORT);             /* skip reservedPad */
    cbData = vSegCount * sizeof (USHORT);
    nBytes=GetFontData (hdc, CMAPHEX, offset, vStartCount, cbData );
    for (i = 0; i<vSegCount; i++)
        SwapShort (& (vStartCount[i]));

    return TRUE;
}


void CFontRange::SwapShort (PUSHORT p)
{
SHORT temp;

    temp =(SHORT)( HIBYTE (*p) + (LOBYTE(*p) << 8));
    *p = temp;
}



void CFontRange::SwapULong (PULONG p)
{
ULONG temp;

    temp = (LONG) ((BYTE) *p);
    temp <<= 8;
    *p >>=8;

    temp += (LONG) ((BYTE) *p);
    temp <<= 8;
    *p >>=8;

    temp += (LONG) ((BYTE) *p);
    temp <<= 8;
    *p >>=8;

    temp += (LONG) ((BYTE) *p);
    *p = temp;
}
			
