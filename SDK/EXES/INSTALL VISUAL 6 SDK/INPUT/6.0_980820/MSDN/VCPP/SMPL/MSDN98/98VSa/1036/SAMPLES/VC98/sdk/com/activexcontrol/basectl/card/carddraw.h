//=--------------------------------------------------------------------------=
// CardDraw.Cpp
//=--------------------------------------------------------------------------=
// Copyright 1996 - 1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
//

class CCardDraw {
	public:
		CCardDraw( int number );
		~CCardDraw();
		BOOL DrawCard( HDC hdcMem, int suite, int number );
		BOOL DrawCardBack( HDC hdcMem, int backnum );
		HBITMAP CreateDIBCard( HDC drawDc );

		// size of the card
		enum { CardSizeX = 71, CardSizeY = 96 };

		// constants to use in constructor
		enum { DrawBack = -1, DrawAll = 15 };

		// rect for filling in the card blank, 
		// POINT array for drawing the border with PolyLine()
		static const POINT CardBorder[9];
		static const RECT CardRect;

	private:
		// DC's for drawing, Mem's hold old DC bitmap contents
		HDC symsDc, symsiDc;
		HBITMAP symsMem, symsiMem;
		HDC centerDc;
		HBITMAP centerMem;
		HDC jokerDc;
		HBITMAP jokerMem;

		// constants for locations of card elements
		enum { SymsSizeX = 73, SymsSizeY = 51 };

		enum { JokerCornerSizeY = 49, JokerCornerSizeX = 38 };
		enum { JokerCornerSrcX = 0, JokerCornerSrcY = 0 };
		enum { JokerCornerY = 5, JokerCornerX = 4 };
		enum { JokerCornerRectSX = 13, JokerCornerRectSY = 15 };
		enum { JokerCornerRectEX = 13, JokerCornerRectEY = 15 };

		enum { LargeSymSrcX = 9, LargeSymSrcY = 36 };
		enum { LargeSymSizeX = 15, LargeSymSizeY = 15 };

		enum { SmallSymSizeX = 9, SmallSymSizeY = 10 };
		enum { SmallSymSrcX = 38, SmallSymSrcY = 0 };
		enum { SmallSymY = 19 };

		enum { NumberSrcX = 12, NumberSrcY = 10 };
		enum { NumberSizeX = 9, NumberSizeY = 12 };
		enum { NumberY = 5 };

		enum { JokerSizeY = 63, JokerSizeX = 45 };
		enum { JokerY = 17, JokerX = 13 };

		enum { PictSizeY = 72, PictSizeX = 45 };
	 	enum { PictY = 11, PictX = 12 };

};

