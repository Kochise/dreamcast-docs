// myconv.cpp

#include "stdafx.h"
#include "ddecli.h"
#include "myclient.h"
#include "myconv.h"
#include "ddecldlg.h"

IMPLEMENT_DYNCREATE(CMyConv, CDDEConv);

CMyConv::CMyConv()
{
    m_pDlg = NULL;
}

CMyConv::CMyConv(CDDEServer* pServer, CDDECliDlg* pDlg)
: CDDEConv(pServer)
{
    m_pDlg = pDlg;
}

BOOL CMyConv::AdviseData(UINT wFmt, const char* pszTopic,
                         const char* pszItem,
                         void* pData, DWORD dwSize)
{
    STATUS("AdviseData: %s|%s: %s",
           (const char*) pszTopic,
           (const char*) pszItem,
           (const char*) pData);
    ASSERT(m_pDlg);
    m_pDlg->NewData(pszItem, (const char*)pData);

    return TRUE;
}
