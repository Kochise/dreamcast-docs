// DirList.cpp: implementation of the CDirList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "DirList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirList::CDirList()
{

}

CDirList::~CDirList()
{
	POSITION p;
	CFileItem *pFileItem;

	p = m_dirList.GetHeadPosition();
	while (p)
	{
		pFileItem = m_dirList.GetNext(p);
		delete pFileItem;
	}

}

BOOL CDirList::FAddDir(LPCTSTR szDir, LPCTSTR szFile, CRect& rectWnd, BOOL fInDebugger, BOOL fTouch /* = TRUE*/)
{
	POSITION p;
	BOOL fOK = FALSE;
	CFileItem *pFileItem = NULL;
	BOOL fAdd = TRUE;

	p = m_dirList.GetHeadPosition();
	while (p)
	{
		pFileItem = m_dirList.GetNext(p);
		if (pFileItem->IsDir(szDir))
		{
			if (pFileItem->IsFile(szFile))
			{
				fAdd = FALSE;
				break;
			}
		}
	}
	if (fAdd)
	{
		pFileItem = new CFileItem(szDir, szFile, rectWnd, fInDebugger);
		m_dirList.AddTail(pFileItem);
		fOK = TRUE;
	}
	else
	{
		if (pFileItem)
			pFileItem->Touch(rectWnd, fInDebugger, fTouch);
	}
	return(fOK);
}

POSITION CDirList::GetHeadPosition()
{
	return(m_dirList.GetHeadPosition());
}

CFileItem * CDirList::GetNextPos(POSITION &p)
{
	CFileItem *pItem;
	pItem = m_dirList.GetNext(p);
	return(pItem);
}

int CDirList::Count()
{
	return(m_dirList.GetCount());
}

void CDirList::Reset()
{
	POSITION p;
	CFileItem *pFileItem;

	p = m_dirList.GetHeadPosition();
	while (p)
	{
		pFileItem = m_dirList.GetNext(p);
		delete pFileItem;
	}
	m_dirList.RemoveAll();
}
