//+---------------------------------------------------------------------------
//  Copyright (C) 1996, Microsoft Corporation.
//
//  File:       adsdb.h
//
//  Contents:   Definitions for the OLE DB provider for ADSI
//
//----------------------------------------------------------------------------

//
// printer status values
//

#ifdef __cplusplus
extern "C" {
#endif

// 
// Properties that belong to the property set DBPROPSET_ADSISEARCH

#define ADSIPROP_ASYNCHRONOUS           0x00000000
#define ADSIPROP_DEREF_ALIASES          0x00000001
#define ADSIPROP_SIZE_LIMIT             0x00000002
#define ADSIPROP_TIME_LIMIT             0x00000003
#define ADSIPROP_ATTRIBTYPES_ONLY       0x00000004
#define ADSIPROP_SEARCH_SCOPE           0x00000005
#define ADSIPROP_TIMEOUT                0x00000006
#define ADSIPROP_PAGESIZE               0x00000007
#define ADSIPROP_PAGED_TIME_LIMIT       0x00000008
#define ADSIPROP_CHASE_REFERRALS        0x00000009


#define DBPROPFLAGS_ADSISEARCH          0x0000C000

#define ADSI_DIALECT_LDAP               0x00000000
#define ADSI_DIALECT_SQL                0x00000001

#ifdef __cplusplus
}
#endif
