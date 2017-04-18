/*****************************************************************************\
*                                                                             *
* coguid.h -    Master definition of GUIDs for COM							  *
*                                                                             *
*               Copyright (c) 1992-1998, Microsoft Corp. All rights reserved. *
*                                                                             *
\*****************************************************************************/

/* This file should NOT have an #ifndef _COGUID_H_ bracket around it.
 * It may be included multiple times.
 */
#include <objbase.h>

DEFINE_GUID(GUID_NULL, 0L, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DEFINE_OLEGUID(IID_IUnknown,            0x00000000L, 0, 0);
DEFINE_OLEGUID(IID_IClassFactory,       0x00000001L, 0, 0);
DEFINE_OLEGUID(IID_IMalloc,             0x00000002L, 0, 0);


/* storage related interfaces */
DEFINE_OLEGUID(IID_IStorage,            0x0000000bL, 0, 0);
DEFINE_OLEGUID(IID_IStream,             0x0000000cL, 0, 0);
DEFINE_OLEGUID(IID_IEnumSTATSTG,        0x0000000dL, 0, 0);

/* property storage related interfaces */
DEFINE_OLEGUID(IID_IPropertySetStorage, 0x00050000,  0x0000,  0x0008);
DEFINE_OLEGUID(IID_IEnumSTATPROPSETSTG, 0x00050001,  0x0000,  0x0008);
DEFINE_OLEGUID(IID_IPropertyStorage,    0x00000014,  0x0000,  0x0008);
DEFINE_OLEGUID(IID_IEnumSTATPROPSTG,    0x00000015,  0x0000,  0x0008);

/* moniker related interfaces */
DEFINE_OLEGUID(IID_IBindCtx,            0x0000000eL, 0, 0);
DEFINE_OLEGUID(IID_IMoniker,            0x0000000fL, 0, 0);
DEFINE_OLEGUID(IID_IRunningObjectTable, 0x00000010L, 0, 0);
DEFINE_OLEGUID(IID_IInternalMoniker,    0x00000011L, 0, 0);


/* NOTE: LSB 0x1a through 0xff are reserved for future use */
