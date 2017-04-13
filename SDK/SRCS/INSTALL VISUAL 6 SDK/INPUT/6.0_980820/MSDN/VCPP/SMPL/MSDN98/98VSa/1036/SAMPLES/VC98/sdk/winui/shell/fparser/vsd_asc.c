#include "vsp_asc.h"
#include "vsdtop.h"

#ifndef VW_SEPARATE_DATA
SHORT	NTypesPerFilter = 1;
#endif

#define FI_EXTERNAL	1997	// Always use this particular value.

FILTER_DESC	VwStreamIdName[VwStreamIdCount] =
{
	{ FI_EXTERNAL, SO_WORDPROCESSOR, "Your Format Name Here!", },
};

#ifndef VW_SEPARATE_DATA
SHORT	InitDataOffset = 0; /*sizeof (VwStreamDynamicType) - sizeof (VwStreamStaticType);*/
#endif

/*
VwStreamStaticType VwStreamStaticName =
{
};
*/

#ifndef VW_SEPARATE_DATA
char	FillerData [ sizeof ( union all_structs ) /*- sizeof ( VwStreamStaticType )*/ + 2 ] = {0};
#endif

