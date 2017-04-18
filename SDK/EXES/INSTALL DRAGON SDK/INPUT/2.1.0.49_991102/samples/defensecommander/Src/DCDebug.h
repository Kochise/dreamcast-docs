/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCDebug.h

Abstract:

    Debug functions. 
	(Never actually got around to implementing much).

-------------------------------------------------------------------*/

#ifdef _DEBUG
#define DC_DPRINT(a) OutputDebugString a
#define DC_WARNING(a) OutputDebugString a
#define DC_ERROR(a)
#define DC_ASSERT_SLOW(a)
#else
#define DC_DPRINT(a)
#define DC_WARNING(a)
#define DC_ERROR(a)
#define DC_ASSERT_SLOW(a)
#endif

#define DC_ASSERT(a)