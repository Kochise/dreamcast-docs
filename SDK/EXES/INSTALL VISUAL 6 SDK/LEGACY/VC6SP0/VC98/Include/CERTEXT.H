//+--------------------------------------------------------------------------
//
// Microsoft Windows
// Copyright 1996 - 1998 Microsoft Corporation
//
// File:        certext.h
//
// Contents:    Definitions and OIDs for standard Certificate Extensions
//
//---------------------------------------------------------------------------

//+--------------------------------------------------------------------------
// Predefined certificate extension data structures that can be encoded/decoded
// via wincrypt.h's CryptEncodeObject/CryptDecodeObject.
//---------------------------------------------------------------------------

#ifndef __CERTEXT_H__
#define __CERTEXT_H__

#ifdef __cplusplus
extern "C" {
#endif

// Table entries
#define ENC_SAMPLE1_REQUEST_STRUCT	((LPCSTR) 3000)
#define ENC_SAMPLE2_REQUEST_STRUCT	((LPCSTR) 3001)

typedef struct _CERT_SAMPLE_STRUCTURE1_INFO
{
    DWORD           dwVersion;
    WCHAR          *pwszField1;
    WCHAR          *pwszField2;
    LONG            lField3;
    CRYPT_DATA_BLOB blobField4;
    FILETIME        dateField5;
} CERT_SAMPLE_STRUCTURE1_INFO;

typedef struct _CERT_SAMPLE_STRUCTURE2_INFO
{
    DWORD           dwVersion;
    LONG            lField1;
    WCHAR          *pwszField2;
    FILETIME        dateField3;
} CERT_SAMPLE_STRUCTURE2_INFO;

#ifdef __cplusplus
}
#endif

#endif // __CERTEXT_H__
