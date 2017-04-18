//=--------------------------------------------------------------------------=
// CardDraw.Cpp
//=--------------------------------------------------------------------------=
// Copyright  1996-1997  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
//

#include <windows.h>

extern HINSTANCE g_hInstance;

#include "Resource.H"
#include "carddraw.h"

const POINT CCardDraw::CardBorder[9] = 
		{ { 0, 2 }, { 2, 0 }, 
		  { CardSizeX-3, 0 }, 
		  { CardSizeX-1, 2 }, 
		  { CardSizeX-1, CardSizeY-3 },
		  { CardSizeX-3, CardSizeY-1 }, 
		  { 2, CardSizeY-1 },
		  { 0, CardSizeY-3 }, { 0, 2 } };

const RECT CCardDraw::CardRect = { 0, 0, CardSizeX, CardSizeY };

CCardDraw::CCardDraw( int number )
{
	symsDc = symsiDc = centerDc = jokerDc = NULL;

	// Symbols bitmaps, used by all cards
	if( number != DrawBack )
	{
		symsDc = CreateCompatibleDC( NULL );
		symsMem = (HBITMAP) SelectObject( symsDc, 
			LoadBitmap( g_hInstance, MAKEINTRESOURCE(IDB_SYMS) ) );
		symsiDc = CreateCompatibleDC( symsDc );
		symsiMem = (HBITMAP) SelectObject( symsiDc,
			CreateCompatibleBitmap( symsiDc, SymsSizeX, SymsSizeY ) );
		StretchBlt( symsiDc, SymsSizeX-1, SymsSizeY-1, -SymsSizeX, -SymsSizeY,
			symsDc, 0, 0, SymsSizeX, SymsSizeY, SRCCOPY );
	}

	// faces, used > 10
	if( number > 10 && number != 14 ) 
	{
		centerDc = CreateCompatibleDC( NULL );
		centerMem = (HBITMAP) SelectObject( centerDc, 
			LoadBitmap( g_hInstance, MAKEINTRESOURCE(IDB_FACES)) );
	}

	// joker
	if( number >= 14 )
	{	
		jokerDc = CreateCompatibleDC( NULL );
		jokerMem = (HBITMAP) SelectObject( jokerDc,
		     LoadBitmap( g_hInstance, MAKEINTRESOURCE(IDB_JOKER) ) );
	}
}

CCardDraw::~CCardDraw()
{
	HBITMAP tempMem;

#define freeDc( s ) \
       if( s##Dc ) \
	  { tempMem = (HBITMAP) SelectObject( s##Dc, s##Mem ); \
	    DeleteObject( tempMem ); \
	    DeleteDC( s##Dc ); }

	freeDc( syms );
	freeDc( symsi );
	freeDc( joker );
	freeDc( center );

#undef freeDc
}
	
BOOL CCardDraw::DrawCard( HDC hdcMem, int suite, int number )
{
	int LocX, LocY;

	const static struct { unsigned char x, y; } LargeSymLoc[10][10] = 
	{ { {29,42} },
	  { {29,11}, {29,86} },
	  { {29,11}, {29,42}, {29,86} },
	  { {16,11}, {42,11}, {16,86}, {42,86} },
	  { {16,11}, {42,11}, {16,86}, {42,86}, {29,42} },
	  { {16,11}, {42,11}, {16,86}, {42,86}, {16,42}, {42,42} },
	  { {16,11}, {42,11}, {16,86}, {42,86}, {16,42}, {42,42}, {29,26} },
	  { {16,11}, {42,11}, {16,86}, {42,86}, {16,32}, {42,32}, {16,65}, {42,65} },
	  { {16,11}, {42,11}, {16,86}, {42,86}, {16,32}, {42,32}, {16,65}, {42,65}, {29,42} },
	  { {16,11}, {42,11}, {16,86}, {42,86}, {16,32}, {42,32}, {16,65}, {42,65}, {29,21}, {29,76} } };

	const static signed char LargeSymLoc9[] = { -2, -2, 3, 0 };

// Macros for working with the Sym DC's
#define SymBitBltTop( x, y, dx, dy, sx, sy, copy ) \
	BitBlt( hdcMem, x, y, dx, dy, symsDc, sx, sy, copy );
#define SymBitBltBottom( x,y, dx, dy, sx, sy, copy ) \
	BitBlt( hdcMem, CardSizeX - (x) - (dx), CardSizeY - (y) - (dy), \
		dx, dy, symsiDc,	\
		SymsSizeX - (sx) - (dx), SymsSizeY - (sy) - (dy), copy );
#define SymBitBlt( x, y, dx, dy, sx, sy, copy ) \
	{ SymBitBltTop( x, y, dx, dy, sx, sy, copy ); \
	  SymBitBltBottom( x, y, dx, dy, sx, sy, copy ); }
#define SymBitBltBottomNoTransX( x,y, dx, dy, sx, sy, copy ) \
	BitBlt( hdcMem, x, y - (dy), \
		dx, dy, symsiDc,	\
		SymsSizeX - (sx) - (dx), SymsSizeY - (sy) - (dy), copy );

	if( suite < 0 ) 
		return( DrawCardBack( hdcMem, -suite ) );

	// white middle
	FillRect( hdcMem, &CardRect, (HBRUSH)GetStockObject(WHITE_BRUSH) );

	// set background color for monochrome bitmap blt's
	SetTextColor( hdcMem, RGB((suite >= 3 ? 255:0),0,0) );

	// Joker
	if( number == 14 )
	{
		static const RECT JokerCornerRect = 
			{ JokerCornerRectSX, JokerCornerRectSY,
			  CardSizeX - JokerCornerRectEX, CardSizeY - JokerCornerRectEY };

		SymBitBlt( JokerCornerX, JokerCornerY,
			   JokerCornerSizeX, JokerCornerSizeY, 
			   JokerCornerSrcX, JokerCornerSrcY, SRCCOPY );

		FillRect( hdcMem, &JokerCornerRect, 
			  (HBRUSH)GetStockObject(WHITE_BRUSH) );

		BitBlt( hdcMem, JokerX, JokerY,	JokerSizeX, JokerSizeY,
		               jokerDc, 0, 0, SRCCOPY) ;
	}

	if( number < 14 ) 
	{				
		long SrcY, SrcX;

		// fill number
		LocX = (number > 10 ? 2 : 3 );
		SrcY = (number & 0x8 ? NumberSizeY : 0);
		SrcX = (number & 0x8 ? (number-8) : (number-1));
		SymBitBlt( LocX, NumberY, 
			   NumberSizeX, 
			   NumberSizeY + ((number & 0x8) >> 2),
			   NumberSrcX + SrcX * NumberSizeX,
			   NumberSrcY + SrcY,
			   SRCCOPY );

		// Small symbols
		SymBitBlt( LocX, SmallSymY,
			 SmallSymSizeX, SmallSymSizeY,
			 SmallSymSrcX + (suite-1) * SmallSymSizeX,
			 SmallSymSrcY, SRCCOPY );
	}

	// center of card, symbols
	if( number <= 10 )
	{
		for( int i = 0; i < number; i++ )
		{
			LocX = LargeSymLoc[number-1][i].x;
			LocY = LargeSymLoc[number-1][i].y;
			if( number == 9 && i == 8 )	// adjustment for 9
				LocY += LargeSymLoc9[suite-1];
			if( LocY <= CardSizeY/2 ) 
			{
				SymBitBltTop( LocX, LocY-1,
					LargeSymSizeX, LargeSymSizeY,
					LargeSymSrcX + (4-suite)*LargeSymSizeX,
					LargeSymSrcY, SRCAND );
			}
			else
			{
				SymBitBltBottomNoTransX( LocX, LocY,
					LargeSymSizeX, LargeSymSizeY,
					LargeSymSrcX + (4-suite)*LargeSymSizeX,
					LargeSymSrcY, SRCAND );
			}
		}
	}

	// center of card, face
	if( number > 10 && number < 14 )
	{
		HPEN oldPen;
		static const POINT centerBorder[] = 
			{ { PictX, PictY }, { PictX, PictY+PictSizeY+1 },
			  { PictX+PictSizeX+1, PictY+PictSizeY+1 },
			  { PictX+PictSizeX+1, PictY }, { PictX, PictY } };

		BitBlt( hdcMem, PictX+1, PictY+1, 
	                PictSizeX, PictSizeY/2,
	                centerDc,
	                (number-11)*PictSizeX,
	                (suite-1)*PictSizeY/2,
	                SRCCOPY) ;
		StretchBlt( hdcMem, PictX+PictSizeX, PictY+PictSizeY,
			-PictSizeX, -PictSizeY/2,
			centerDc,
	                (number-11)*PictSizeX,
	                (suite-1)*PictSizeY/2,
			PictSizeX, PictSizeY/2, SRCCOPY );
		oldPen = (HPEN) SelectObject( hdcMem, GetStockObject( BLACK_PEN ) );
		Polyline( hdcMem, centerBorder, sizeof(centerBorder)/sizeof(POINT) );
		SelectObject( hdcMem, oldPen );
	}

	return( TRUE );
}

BOOL CCardDraw::DrawCardBack( HDC hdcMem, int backnum )
{
	if( backnum >= 1 && backnum <= 12 )
	{
		HDC backDc;
		HBITMAP backMem;
		if( !(backDc = CreateCompatibleDC( NULL )) )
			return( FALSE );
		if( !(backMem = (HBITMAP) SelectObject( backDc,
				LoadBitmap( g_hInstance,
					MAKEINTRESOURCE(backnum+IDB_BACKBASE)))) )
		{
			DeleteDC( backDc );
			return( FALSE );
		}
		BitBlt( hdcMem, 1, 1, CardSizeX-2, CardSizeY-2,
	 	        backDc, 0, 0, SRCCOPY );
		DeleteObject( backMem );
		DeleteDC( backDc );
	}
	else
	{
		FillRect( hdcMem, &CardRect, 
			  (HBRUSH)GetStockObject(WHITE_BRUSH) );

		for( int x = 1; x < CardSizeX-1; x++ )
		    for( int y = 1; y < CardSizeY-1; y++ )
			if( ((x+y-2) & 3) < 2 ) 
				SetPixelV( hdcMem, x, y, RGB( 0,0,128 ) );
	}

	return( TRUE );
}

HBITMAP CCardDraw::CreateDIBCard( HDC drawDc )
{
	void *bits;
	static struct {
		BITMAPINFOHEADER bi;
		long colors[16];
	} b = { { sizeof(b.bi), 
		  (((CardSizeX + 3)>>2)<<2),
		  CardSizeY, 1, 4, BI_RGB, 0, 0, 0, 16, 16 },
		{ 0x000000, 0x800000, 0x008000, 0x808000,
		  0x000080, 0x800080, 0x808080, 0xc0c0c0,
		  0x808080, 0xff0000, 0x00ff00, 0xffff00,
	          0x0000ff, 0xff00ff, 0x00ffff, 0xffffff } };

	return CreateDIBSection( drawDc, (BITMAPINFO *) &b,
				 DIB_RGB_COLORS, 	
				 &bits, NULL, 0 );	
}