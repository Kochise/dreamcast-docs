/***********************************************************************
**      S U B G E N R E . H                                            *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*

        SUBGENRE.H

        SubGenre record object class definitions for Microsoft Guide



*/



#ifndef _SUBGENRE_H_
#define _SUBGENRE_H_

/*

SubGenre objects are constructed from database records of the SubGenre table.

The CSubGenreRecordset class is used to select and create CSubGenre objects
from the SubGenre table via functions in the CDatabaseRecordset parent class.

*/


#include "dbsets.h"



class COMMMSTVEXPORT CSubGenreRecordset : public CDatabaseRecordset
{

// This class provides SubGenre recordset manipulation via parent functions


virtual CString GetTableName( VOID);

virtual BOOL    SetRecordsetObject( VOID* cRecordsetObject);

public:
virtual VOID*   GetRecordsetObject( VOID);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, LONG lSubGenreID);
};




class COMMMSTVEXPORT CSubGenre : public CObject
{

    friend class CSubGenreRecordset; // generates the CSubGenre record object

private:

    LONG		m_lSubGenreID;
	CString		m_cszName;

public:

	CSubGenre(LONG lSubGenreID = AFX_RFX_LONG_PSEUDO_NULL,
				CString cszName = "") :
			    m_lSubGenreID(lSubGenreID),
			    m_cszName(cszName) { }

	~CSubGenre(VOID) { }

	VOID    SetName( LPCTSTR cszName) { m_cszName = cszName; }

    LONG           SubGenreID() { return m_lSubGenreID; }
	CString         Name() { return m_cszName; }
};


// Table: SubGenre

#define  TBL_SubGenre  _T("SubGenre")

//      Field:                         Index   Name             Type    Size

#define FLD_SubGenre_SubGenreID	_T("SG SubGenre ID")	// SubGenreID       Long     4
#define FLD_SubGenre_Name		_T("SG Name")			// Name             Text    25


#endif

