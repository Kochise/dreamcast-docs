#include "stdafx.h"
#include "doc.h"

IMPLEMENT_DYNAMIC(CBaseDoc, CDocument)
IMPLEMENT_DYNCREATE(CDocA, CBaseDoc)
IMPLEMENT_DYNCREATE(CDocB, CBaseDoc)

void CDocA::AddTitleToString(CString &msg)
{
   msg += GetTitle();
   msg += " is a CDocA.\n";
}

void CDocB::AddTitleToString(CString &msg)
{
   msg += GetTitle();
   msg += " is a CDocB.\n";
}
