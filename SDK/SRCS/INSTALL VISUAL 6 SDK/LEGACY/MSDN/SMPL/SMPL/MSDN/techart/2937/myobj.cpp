// myobj.cpp : implementation of the CMyObj class
//

#include "stdafx.h"
#include "mfcclip.h"
#include "myobjdlg.h"
#include "myobj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyObj

IMPLEMENT_SERIAL(CMyObj, CObject, 0)

/////////////////////////////////////////////////////////////////////////////
// CMyObj construction/destruction

CMyObj::CMyObj()
{
    m_strText = "Some text.";
}

CMyObj::~CMyObj()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMyObj serialization

void CMyObj::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        ar << m_strText;
    } else {
        ar >> m_strText;
    }
}

int CMyObj::DoEditDialog()
{
    CMyObjDlg dlg;
    dlg.m_strText = m_strText;
    int iRes;
    if ((iRes = dlg.DoModal()) == IDOK) {
        m_strText = dlg.m_strText;
    }
    return iRes;
}
