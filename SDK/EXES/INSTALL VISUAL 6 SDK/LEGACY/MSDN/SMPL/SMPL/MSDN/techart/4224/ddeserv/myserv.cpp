// myserv.cpp

#include "stdafx.h"
#include "ddeserv.h"
#include "myserv.h"

CMyServer::CMyServer()
{
}

CMyServer::~CMyServer()
{
}

void CMyServer::Status(const char* pszFormat, ...)
{
    char buf[1024];
	va_list arglist;
	va_start(arglist, pszFormat);
    vsprintf(buf, pszFormat, arglist);
	va_end(arglist);

    STATUS(buf);
}

BOOL CMyServer::OnCreate()
{
    //
    // Add our own topics and items
    //

    m_DataTopic.Create("Data");
    AddTopic(&m_DataTopic);

    m_StringItem1.Create("String1");
    m_DataTopic.AddItem(&m_StringItem1);

    m_StringItem2.Create("String2");
    m_DataTopic.AddItem(&m_StringItem2);

    //
    // Set up some data in the strings
    //

    m_StringItem1.SetData("This is string 1");
    m_StringItem2.SetData("This is string 2");

    return TRUE;
}

void CMyStringItem::OnPoke()
{
    STATUS("%s is now %s",
           (const char*)m_strName,
           GetData());
}

CMyTopic::CMyTopic()
{
}

BOOL CMyTopic::Exec(void* pData, DWORD dwSize)
{
    STATUS("Exec: %s", (char*)pData);
    return TRUE;
}
