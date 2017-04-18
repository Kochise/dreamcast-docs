// myoblist.cpp : implementation file
//

#include "stdafx.h"
#include "myobj.h"
#include "myoblist.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyObList

IMPLEMENT_SERIAL(CMyObList, CObList, 0)

CMyObList::CMyObList()
{
}

CMyObList::~CMyObList()
{
    DeleteAll();
}

/////////////////////////////////////////////////////////////////////////////
// CMyObjMode serialization

void CMyObList::Serialize(CArchive& ar)
{
    CObList::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CMyObList commands

// Delete al objects in the list
void CMyObList::DeleteAll()
{
    while(!IsEmpty()) {
        CMyObj* ptr = RemoveHead();
        ASSERT(ptr);
        delete ptr;
    }
}

// Add a new object to the end of the list
void CMyObList::Append(CMyObj* pMyObj)
{
    ASSERT(pMyObj);
    ASSERT(pMyObj->IsKindOf(RUNTIME_CLASS(CMyObj)));
    CObList::AddTail(pMyObj);
}

// Remove an object from the list but don't delete it
BOOL CMyObList::Remove(CMyObj* pMyObj)
{
    POSITION pos = Find(pMyObj);
    if (!pos) return FALSE;
    RemoveAt(pos);
    return TRUE;
}






