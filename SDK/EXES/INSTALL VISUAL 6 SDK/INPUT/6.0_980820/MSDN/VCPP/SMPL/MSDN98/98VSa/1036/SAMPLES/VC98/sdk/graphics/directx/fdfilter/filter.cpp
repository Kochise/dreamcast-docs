#include "fdfilter.h"
#include "filter.h"

HRESULT CFilter::Transform( PBYTE pbIn, int cbLength, PBYTE pbOut )
    {
    if( NULL == pbIn || NULL == pbOut )
	return ResultFromScode( E_POINTER );
    if( 0 == cbLength )
	return NOERROR;

    CopyMemory( pbOut, pbIn, cbLength );
    return NOERROR;
    }


// Merely stubbed out for this simple filter -- we have no need for the
// extra information
HRESULT CFilter::SetFormat( PWAVEFORMATEX pwfx )
    {
    if( NULL == pwfx )
	return ResultFromScode( E_POINTER );

    return NOERROR;    
    }


