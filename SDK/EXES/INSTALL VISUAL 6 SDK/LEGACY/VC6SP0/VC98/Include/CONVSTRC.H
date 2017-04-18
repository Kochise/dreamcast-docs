// --convstrc.h-----------------------------------------------------------------
//
//  Defines common public conversion structures.
// 
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#if !defined(_CONVSTRC_H)
#define _CONVSTRC_H

#ifdef __cplusplus
extern "C" {
#endif

//$$--EDKCNVENV---------------------------------------------------------
//
//  DESCRIPTION: Structure that represents the environment of a conversion.
//
//---------------------------------------------------------------------
typedef struct _EDKCNVENV
{
    INT nVersionEDKCNVENV ;
    LPCWSTR pszConversionPoint ;

    // connection to MAPI system
    LHANDLE lphSession ;
    LPMDB lpMDB ;
    LPADRBOOK lpAB ;
    
    // connection to foreign system
    LPVOID pGatewayDefined ;
} EDKCNVENV ;

typedef EDKCNVENV * PEDKCNVENV ;

//$$--EDKCNVRES---------------------------------------------------------
//  Enumerated type indicating the result of a conversion.
//---------------------------------------------------------------------
typedef enum _EDKCNVRES
{
    GCR_OK = 0,
    GCR_CANNOT_CONVERT,
    GCR_CANNOT_LOAD,
    GCR_NO_CANDIDATE,
    GCR_CONVERSION_FAILED
} EDKCNVRES ;


//---------------------------------------------------------------------
//  Types representing methods of a conversion DLL.
//---------------------------------------------------------------------

typedef HRESULT (*PCONVDLLQUERY)(
    IN LPCWSTR pszOptions,      // options pointer
    IN LPCWSTR pszClass,        // class name pointer
    IN PVOID pContent,          // object to convert pointer
    IN PEDKCNVENV pEnv,         // environment pointer
    OUT BOOL * pfAmCandidate);  // pointer to candidate status

typedef HRESULT (*PCONVDLLCONV)(
    IN LPCWSTR pszOptions,      // options pointer
    IN LPCWSTR pszClass,        // class name pointer
    IN PVOID pContent,          // pointer to object to convert
    IN PVOID pContentOut,       // pointer to converted object
    IN PEDKCNVENV pEnv,         // environment pointer
    OUT EDKCNVRES * pcr) ;      // pointer to conversion result

//$$--CONVDLLVECT-------------------------------------------------------
//
//  DESCRIPTION: Vector representing the entry points to a conversion.
//
//---------------------------------------------------------------------
typedef struct _CONVDLLVECT
{
    short nVectorVersion ;
    PCONVDLLQUERY pfnCnvQueryCapability ;
    PCONVDLLCONV pfnCnvConvert ;
} CONVDLLVECT ;
typedef CONVDLLVECT * PCONVDLLVECT ;

typedef HRESULT (*PCONVDLLENTRYFN)(
    IN DWORD,                   // version number desired
    OUT PCONVDLLVECT FAR *) ;   // entry point function declaration

#define nDesiredConvDllVersion ((DWORD)1)           // current conversion vector version number.

#ifdef __cplusplus
}
#endif

#endif
