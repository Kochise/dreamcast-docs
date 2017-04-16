// strlist.cpp : implementation file
//

#include "stdafx.h"
#include "strlist.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrList

IMPLEMENT_SERIAL(CStrList, CPtrList, 0 /* schema number*/ )

CStrList::CStrList()
{
}

CStrList::~CStrList()
{
    DeleteAll();
}

void CStrList::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        ar << (DWORD) GetCount();
        POSITION pos = GetHeadPosition();
        while (pos) {
            CString* pStr = GetNext(pos);
            ar << *pStr  ;
        }
    } else {
        DWORD dw;
        ar >> dw;
        int iCount = dw;
        while (iCount--) {
            CString* pStr = new CString;
            ar >> *pStr;
            AddTail(pStr);
        }
    }
}

void CStrList::DeleteAll()
{
    while (!IsEmpty()) {
        CString* pStr = RemoveHead();
        delete pStr;
    }
}
