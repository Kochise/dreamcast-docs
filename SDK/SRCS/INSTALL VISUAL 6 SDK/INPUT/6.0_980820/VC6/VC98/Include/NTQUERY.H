//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright 1996 - 1998 Microsoft Corporation-1997.
//
//  File:       NtQuery.h
//
//  Contents:   Main query header; Defines all exported query API
//
//----------------------------------------------------------------------------

#if !defined(__NTQUERY_H__)
#define __NTQUERY_H__

#if defined(__cplusplus)
extern "C"
{
#endif

//
// Use this path for the null catalog, one that doesn't have an index.
// Use it to search for properties of files that are not indexed.
//

#define CINULLCATALOG L"::_noindex_::"

//
// Minimal support for persistent handlers.
//

STDAPI LoadIFilter( WCHAR const * pwcsPath,
                    IUnknown *    pUnkOuter,
                    void **       ppIUnk );

STDAPI BindIFilterFromStorage( IStorage * pStg,
                               IUnknown * pUnkOuter,
                               void **    ppIUnk );

STDAPI BindIFilterFromStream( IStream *  pStm,
                              IUnknown * pUnkOuter,
                              void **    ppIUnk );

STDAPI LocateCatalogsW( WCHAR const * pwszScope,
                        ULONG         iBmk,
                        WCHAR *       pwszMachine,
                        ULONG *       pccMachine,
                        WCHAR *       pwszCat,
                        ULONG *       pccCat );

//
// For calling from VB
//

STDAPI LocateCatalogsA( char const * pwszScope,
                        ULONG        iBmk,
                        char  *      pwszMachine,
                        ULONG *      pccMachine,
                        char *       pwszCat,
                        ULONG *      pccCat );

#ifdef UNICODE
#define LocateCatalogs  LocateCatalogsW
#else
#define LocateCatalogs  LocateCatalogsA
#endif // !UNICODE

// The Index Server Data Source Object CLSID

#define CLSID_INDEX_SERVER_DSO \
    { 0xd7a2b01a, 0xa47d, 0x11d0, \
      { 0x8c, 0x55, 0x0, 0xc0, 0x4f, 0xc2, 0xdb, 0x8d } }

// The storage property set

#define PSGUID_STORAGE \
    { 0xb725f130, 0x47ef, 0x101a, \
      { 0xa5, 0xf1, 0x02, 0x60, 0x8c, 0x9e, 0xeb, 0xac } }

//#define PID_STG_DICTIONARY            ((PROPID) 0x00000000) //reserved
//#define PID_STG_CODEPAGE              ((PROPID) 0x00000001) //reserved
#define PID_STG_DIRECTORY               ((PROPID) 0x00000002)
#define PID_STG_CLASSID                 ((PROPID) 0x00000003)
#define PID_STG_STORAGETYPE             ((PROPID) 0x00000004)
#define PID_STG_VOLUME_ID               ((PROPID) 0x00000005)
#define PID_STG_PARENT_WORKID           ((PROPID) 0x00000006)
// unused #define PID_STG_              ((PROPID) 0x00000007)
#define PID_STG_FILEINDEX               ((PROPID) 0x00000008)
#define PID_STG_LASTCHANGEUSN           ((PROPID) 0x00000009)
#define PID_STG_NAME                    ((PROPID) 0x0000000a)
#define PID_STG_PATH                    ((PROPID) 0x0000000b)
#define PID_STG_SIZE                    ((PROPID) 0x0000000c)
#define PID_STG_ATTRIBUTES              ((PROPID) 0x0000000d)
#define PID_STG_WRITETIME               ((PROPID) 0x0000000e)
#define PID_STG_CREATETIME              ((PROPID) 0x0000000f)
#define PID_STG_ACCESSTIME              ((PROPID) 0x00000010)
// unused #define PID_STG_              ((PROPID) 0x00000011)
#define PID_STG_ALLOCSIZE               ((PROPID) 0x00000012)
#define PID_STG_CONTENTS                ((PROPID) 0x00000013)
#define PID_STG_SHORTNAME               ((PROPID) 0x00000014)
#define PID_STG_MAX                     PID_STG_SHORTNAME
#define CSTORAGEPROPERTY                0x15

// File System Content Index Framework property set

#define DBPROPSET_FSCIFRMWRK_EXT \
    { 0xA9BD1526, 0x6A80, 0x11D0, \
      { 0x8C, 0x9D, 0x00, 0x20, 0xAF, 0x1D, 0x74, 0x0E } }

#define DBPROP_CI_CATALOG_NAME     2
#define DBPROP_CI_INCLUDE_SCOPES   3
#define DBPROP_CI_DEPTHS           4 // obsolete
#define DBPROP_CI_SCOPE_FLAGS      4
#define DBPROP_CI_EXCLUDE_SCOPES   5
#define DBPROP_CI_SECURITY_ID      6
#define DBPROP_CI_QUERY_TYPE       7

// Query Extension property set

#define DBPROPSET_QUERYEXT \
    { 0xA7AC77ED, 0xF8D7, 0x11CE, \
      { 0xA7, 0x98, 0x00, 0x20, 0xF8, 0x00, 0x80, 0x25 } }

#define DBPROP_USECONTENTINDEX           2
#define DBPROP_DEFERNONINDEXEDTRIMMING   3
#define DBPROP_USEEXTENDEDDBTYPES        4

// Content Index Framework Core property set

#define DBPROPSET_CIFRMWRKCORE_EXT \
    { 0xafafaca5, 0xb5d1, 0x11d0, \
      { 0x8c, 0x62, 0x00, 0xc0, 0x4f, 0xc2, 0xdb, 0x8d } }

#define DBPROP_MACHINE      2
#define DBPROP_CLIENT_CLSID 3

// Scope flags

#define QUERY_SHALLOW        0
#define QUERY_DEEP           1
#define QUERY_PHYSICAL_PATH  0
#define QUERY_VIRTUAL_PATH   2

// query property set (PSGUID_QUERY) properties not defined in oledb.h

#define PROPID_QUERY_WORKID        5
#define PROPID_QUERY_UNFILTERED    7
#define PROPID_QUERY_VIRTUALPATH   9
#define PROPID_QUERY_LASTSEENTIME 10

#if defined __oledb_h__

typedef struct tagCIPROPERTYDEF
{
    LPWSTR wcsFriendlyName;
    DWORD  dbType;
    DBID   dbCol;
} CIPROPERTYDEF;

//
// Create an ICommand, specifying scopes, catalogs, and machines
// (obsolete)
//
STDAPI CIMakeICommand( ICommand **           ppCommand,
                       ULONG                 cScope,
                       DWORD const *         aDepths,
                       WCHAR const * const * awcsScope,
                       WCHAR const * const * awcsCatalogs,
                       WCHAR const * const * awcsMachine );

//
// Create an ICommand, specifying a catalog and machine
//

STDAPI CICreateCommand( IUnknown **   ppCommand,     // New object
                        IUnknown *    pUnkOuter,     // Outer unknown
                        REFIID        riid,          // IID of returned object.
                                                     // Must be IID_IUnknown unless pUnkOuter == 0
                        WCHAR const * pwcsCatalog,   // Catalog
                        WCHAR const * pwcsMachine ); // Machine

//
// Convert pwszRestriction in Triplish to a command tree.
//
STDAPI CITextToSelectTree( WCHAR const *     pwszRestriction,
                           DBCOMMANDTREE * * ppTree,
                           ULONG             cProperties,
             /*optional*/  CIPROPERTYDEF *   pProperties,
                           LCID              LocaleID );

//
// Convert pwszRestriction in Triplish, project columns, sort columns
// and grouping columns to a command tree.
//
STDAPI CITextToFullTree( WCHAR const *     pwszRestriction,
                         WCHAR const *     pwszColumns,
                         WCHAR const *     pwszSortColumns, // may be NULL
                         WCHAR const *     pwszGroupings,   // may be NULL
                         DBCOMMANDTREE * * ppTree,
                         ULONG             cProperties,
           /*optional*/  CIPROPERTYDEF *   pProperties,
                         LCID              LocaleID );
//
// Build a simple restriction node.
//

STDAPI CIBuildQueryNode( WCHAR const *wcsProperty,    // friendly property name
                         DBCOMMANDOP dbOperator,    // enumerated constant
                         PROPVARIANT const *pvarPropertyValue, // value of the property
                         DBCOMMANDTREE ** ppTree, // ptr to tree returned here. should be non-null
                         ULONG cProperties,
                         CIPROPERTYDEF const * pProperty, // Can be 0.
                         LCID LocaleID );  // locale id to interpret strings

//
// Build a restriction tree from an existing tree (could be empty) and a newly added node/tree.
//

STDAPI CIBuildQueryTree( DBCOMMANDTREE const *pExistingTree,  // existing tree. can be null.
                         DBCOMMANDOP dbBoolOp,   // enumerator constant
                         ULONG cSiblings, // number of siblings in the array
                         DBCOMMANDTREE const * const *ppSibsToCombine,
                         DBCOMMANDTREE ** ppTree);   // ptr to tree returned here. should be non-null

//
// Convert restriction tree, project columns, sort columns
// and grouping columns to a command tree.
//
STDAPI CIRestrictionToFullTree( DBCOMMANDTREE const *pTree,
                         WCHAR const * pwszColumns,
                         WCHAR const * pwszSortColumns, // may be NULL
                         WCHAR const * pwszGroupings,   // may be NULL
                         DBCOMMANDTREE * * ppTree,
                         ULONG cProperties,
           /*optional*/  CIPROPERTYDEF * pReserved,
                         LCID LocaleID );

#endif  // __oledb_h__

#if defined(__cplusplus)
}
#endif

#endif // __NTQUERY_H__

