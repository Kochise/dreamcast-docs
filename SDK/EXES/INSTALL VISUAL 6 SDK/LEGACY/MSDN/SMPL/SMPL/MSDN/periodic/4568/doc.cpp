//////////////////
// Typical document implementation, nothing special
//
#include "stdafx.h"
#include "doc.h"

IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
	//{{AFX_MSG_MAP(CMyDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMyDoc::CMyDoc()
{
}

CMyDoc::~CMyDoc()
{
}

