// wordmap.cpp : implementation file
//

#include "stdafx.h"
#include "wordmap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWordMap

IMPLEMENT_SERIAL(CWordMap, CMapStringToOb, 0 /* schema number*/ )

CWordMap::CWordMap()
{
}

CWordMap::~CWordMap()
{
}

/////////////////////////////////////////////////////////////////////////////
// CWordMap serialization

void CWordMap::Serialize(CArchive& ar)
{
    // let the base class create the set of objects
    CMapStringToOb::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CWordMap commands

BOOL CWordMap::Add(const char* pszWord, CWave* pWave)
{
    SetAt(pszWord, pWave);
    return TRUE;
}

BOOL CWordMap::Remove(const char *pszWord)
{
    CWave* pWave = Find(pszWord);
    if (!pWave) return FALSE;
    RemoveKey(pszWord);
    delete pWave;
    return TRUE;
}

CWave* CWordMap::Find(const char* pszWord)
{
    CWave* pWave;
    if (Lookup(pszWord, (CObject*&)pWave)) {
        return pWave;
    }
    return NULL;
}

POSITION CWordMap::GetStartPosition()
{
    return CMapStringToOb::GetStartPosition();
}

void CWordMap::GetNextAssoc(POSITION& rPos, CString& rKey,CWave*& rWave)
{
    CMapStringToOb::GetNextAssoc(rPos, rKey, (CObject*&)rWave);
}

void CWordMap::DeleteAll()
{
    POSITION pos;
    while(pos = GetStartPosition()) {
        CString strWord;
        CWave* pWave;
        GetNextAssoc(pos, strWord, pWave);
        RemoveKey(strWord);
        delete pWave;
    }
}
