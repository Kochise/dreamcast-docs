/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    Parse.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _PARSE_H_
#define _PARSE_H_

#define MAX_TOKEN_LENGTH       80
#define MAX_KEYWORDS           14

typedef struct _kwdlist {
    DWORD   dwTokenId;
    LPWSTR  Keyword;
} KWDLIST, *PKWDLIST;

class FAR CLexer
{
public:
    CLexer(LPWSTR szBuffer);
    ~CLexer();

    BOOL
    CLexer::IsKeyword(LPWSTR szToken, LPDWORD pdwToken);

    WCHAR
    CLexer::NextChar();

    void
    CLexer::PushbackChar();

    HRESULT
    CLexer::GetNextToken(LPWSTR szToken, LPDWORD pdwToken);

    HRESULT
    CLexer::PushBackToken();

private:

    LPWSTR _ptr;
    LPWSTR _Buffer;
    DWORD  _dwLastTokenLength;
    DWORD  _dwLastToken;
    DWORD  _dwEndofString;

};

HRESULT
ADsObject(CLexer * pTokenizer, POBJECTINFO pObjectInfo);

HRESULT
SampleDSObject(CLexer * pTokenizer, POBJECTINFO pObjectInfo);


HRESULT
DsPathName(CLexer * pTokenizer, POBJECTINFO pObjectInfo);


HRESULT
PathName(CLexer * pTokenizer, POBJECTINFO pObjectInfo);

HRESULT
Component(CLexer * pTokenizer, POBJECTINFO pObjectInfo);

HRESULT
Type(CLexer * pTokenizer, POBJECTINFO pObjectInfo);

HRESULT
ProviderName(CLexer * pTokenizer, POBJECTINFO pObjectInfo);

HRESULT
AddRootRDN(POBJECTINFO pObjectInfo, LPWSTR szToken);

HRESULT
SetType(POBJECTINFO pObjectInfo, DWORD dwToken);

HRESULT
SchemaPathName(CLexer * pTokenizer, POBJECTINFO pObjectInfo);

HRESULT
SchemaComponent(CLexer * pTokenizer, POBJECTINFO pObjectInfo);

#endif

