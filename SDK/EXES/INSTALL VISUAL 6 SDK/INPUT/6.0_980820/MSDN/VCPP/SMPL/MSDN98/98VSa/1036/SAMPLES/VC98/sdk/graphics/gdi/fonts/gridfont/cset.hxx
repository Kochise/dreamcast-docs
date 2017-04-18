
/*
  	this option allows to select a type of characters 
  	and either print/display only the characters in the
	set, or to color them, whatever.

	To make this work i need to
		a) have a way to
			1) identify
			2) create
			3) combine
		    the subsets

		b) be able to determin whether a character
			 IsInSet
			 and which is the next character in the set

		c) associate an action with the set
			actions are
				fg, bg color and ignore 
				(can use fg color=white for ignore)
			and can be kept in a single WORD

	As sources for subsets I have:
		i)	named subsets (ISO 10646)
		ii) character properties
		
*/

#ifndef _CSET_HXX_
#define _CSET_HXX_

// base class for any form of set

class CSet
{
	public:
		virtual BOOL In(WORD iChar) = 0;
		//virtual WORD Next(WORD iChar) = 0;
		//virtual WORD Prev(WORD iChar) = 0;
	protected:
} ;



// Set based on CType 
class CCTypeSet : public CSet
{
	public:
		CCTypeSet(WORD fC1Mask, WORD fC2Test, WORD fC3Mask);
		BOOL In(WORD iChar);
	protected:
		void GetPageData( WORD iPage );
		BOOL _pCharInSet[256];
		BOOL _pPageInSet[256];
		WORD _fC1Mask;
		WORD _fC2Test;	// C2 is an enumerated field
		WORD _fC3Mask;
		WORD _iPage;
} ;



// Set based on font coverage
class CFontSet: public CSet 
{
	public:
		CFontSet(HWND hwnd, HFONT hfont) ;
} ;

#endif
