// MRUStrings.h: interface for the CMRUStrings class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MRUSTRINGS_H__BF23C403_9135_11D1_8302_00A0C91BC942__INCLUDED_)
#define AFX_MRUSTRINGS_H__BF23C403_9135_11D1_8302_00A0C91BC942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMRUStrings  
{
public:
	BOOL Create(CRegKey& key);
	CMRUStrings();
	virtual ~CMRUStrings();

protected:
	int m_cElementsMax;
};

#endif // !defined(AFX_MRUSTRINGS_H__BF23C403_9135_11D1_8302_00A0C91BC942__INCLUDED_)
