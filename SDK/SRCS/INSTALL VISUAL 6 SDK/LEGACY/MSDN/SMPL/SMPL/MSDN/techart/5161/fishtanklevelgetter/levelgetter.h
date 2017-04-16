// LevelGetter.h: Definition of the LevelGetter class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEVELGETTER_H__7F0DFAA4_F56D_11D0_A980_0020182A7050__INCLUDED_)
#define AFX_LEVELGETTER_H__7F0DFAA4_F56D_11D0_A980_0020182A7050__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// LevelGetter

class LevelGetter : 
	public ILevelGetter,
	public CComObjectRoot,
	public CComCoClass<LevelGetter,&CLSID_LevelGetter>
{
public:
	LevelGetter(){}

BEGIN_COM_MAP(LevelGetter)
	COM_INTERFACE_ENTRY(ILevelGetter)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(LevelGetter) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_LevelGetter)

// ILevelGetter
public:
	STDMETHOD (GetLowestPossibleSafeLevel)  (long* plLowestSafeLevel);
	STDMETHOD (GetHighestPossibleSafeLevel) (long* plHighestSafeLevel);
	STDMETHOD (GetCurrentLevel)				(long* plCurrentLevel);
	STDMETHOD (GetTextMessage)				(BSTR* ppbstrMessage);
};


#endif // !defined(AFX_LEVELGETTER_H__7F0DFAA4_F56D_11D0_A980_0020182A7050__INCLUDED_)
