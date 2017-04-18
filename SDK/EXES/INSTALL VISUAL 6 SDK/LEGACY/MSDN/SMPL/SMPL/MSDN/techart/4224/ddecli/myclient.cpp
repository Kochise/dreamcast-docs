// myclient.cpp

#include "stdafx.h"
#include "ddecli.h"
#include "myclient.h"

IMPLEMENT_DYNCREATE(CMyClient, CDDEServer);

void CMyClient::Status(const char* pszFormat, ...)
{
    char buf[1024];
	va_list arglist;
	va_start(arglist, pszFormat);
    vsprintf(buf, pszFormat, arglist);
	va_end(arglist);

    STATUS(buf);
}


