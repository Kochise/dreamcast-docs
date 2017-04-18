#include <windows.h>
#include <windowsx.h>
#include <string.h>
#include "app.h"

#include "cset.hxx"

//+--------------------------------------------------------
// Class:       CSet
//
// Purpose:     Set of characters
//
// History:     03-Aug-1994     asmusf  created
//----------------------------------------------------------

// pure inline

//+--------------------------------------------------------
// Class:       CCTypesSet
//
// Purpose:     Set of chars defined by common CType
//
// History:     03-Aug-1994     asmusf  created
//----------------------------------------------------------

CCTypeSet :: CCTypeSet(WORD fC1Mask, WORD fC2Test, WORD fC3Mask)
{
	_fC1Mask = fC1Mask;
	_fC2Test = fC2Test;
	_fC3Mask = fC3Mask;
	GetPageData( 0 );  // Page 0 is ALWAYS the default
}

CCTypeSet :: In(WORD iChar)
{
	WORD iPage = iChar & 0xFF00;
	if( iPage != _iPage )
	{
		GetPageData(iPage);
	}	
	return _pCharInSet[iChar &0xFF];
}


void CCTypeSet :: GetPageData(WORD iPage)
{
	WORD i;
	TCHAR vchTemp[256];
	WORD vCtype[256];

	for ( i=0; i < 256; i++ )
	{
		vchTemp[i] = iPage+i;
		_pCharInSet[i] = FALSE;
	}
	if( _fC1Mask )
	{
		GetStringTypeEx(0,CT_CTYPE1,vchTemp,256, vCtype);
		for( i=0; i<256;i++ ){
			_pCharInSet[i] = _pCharInSet[i] || (vCtype[i] & _fC1Mask);
		}
	}
	if( _fC2Test )
	{
		GetStringTypeEx(0,CT_CTYPE2,vchTemp,256, vCtype);
		for( i=0; i<256;i++ ){
			_pCharInSet[i] = _pCharInSet[i] || (vCtype[i] == _fC2Test);  //enumerated value
		}
	}
	if( _fC3Mask )
	{
		GetStringTypeEx(0,CT_CTYPE3,vchTemp,256, vCtype);
		for( i=0; i<256;i++ ){
			_pCharInSet[i] = _pCharInSet[i] || (vCtype[i] & _fC3Mask);
		}
	}
	_iPage = iPage;
}



