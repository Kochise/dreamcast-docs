/***********************************************************************
**      G E N R E . H                                                  *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*

        GENRE.H

        Genre record object class definitions for Microsoft Guide



*/



#ifndef _GENRE_H_
#define _GENRE_H_

/*

Genre objects are constructed from database records of the Genre table.

The CGenreRecordset class is used to select and create CGenre objects
from the Genre table via functions in the CDatabaseRecordset parent class.

*/


#include "dbsets.h"



class COMMMSTVEXPORT CGenreRecordset : public CDatabaseRecordset
{

// This class provides Genre recordset manipulation via parent functions


virtual CString GetTableName( VOID);

virtual BOOL    SetRecordsetObject( VOID* cRecordsetObject);

public:
virtual VOID*   GetRecordsetObject( VOID);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, LONG lGenreID);
};




class COMMMSTVEXPORT CGenre : public CObject
{
    friend class CGenreRecordset; // generates the CGenre record object

private:

    LONG			m_lGenreID;
	LONG			m_lTuningSpace;
	CString         m_cszName;

public:

	CGenre(LONG lGenreID = AFX_RFX_LONG_PSEUDO_NULL,
			LONG lTuningSpace = 0,
			CString cszName = "") :
			m_lGenreID(lGenreID),
			m_lTuningSpace(lTuningSpace),
			m_cszName(cszName) { }

	~CGenre(VOID) { }

    VOID    SetTuningSpace( LONG lTuningSpace) { m_lTuningSpace = lTuningSpace; }
	VOID    SetName( LPCTSTR cszName) { m_cszName = cszName; }

    LONG       		GenreID() { return m_lGenreID; }
    LONG        	TuningSpace() { return m_lTuningSpace; }
	CString         Name() { return m_cszName; }
};


// Table: Genre

#define  TBL_Genre  _T("Genre")

//      Field:                      Index   Name             Type    Size

#define FLD_Genre_GenreID		_T("G Genre ID")		// GenreID          long      4
#define FLD_Genre_TuningSpace	_T("G Tuning Space")	// Tuning Space		long      4
#define FLD_Genre_Name			_T("G Name")			// Title            Text     50

#endif

