/***********************************************************************
**      T H E M E . H												   *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*
        THEME.H

        Theme record object class definitions for Microsoft Guide
*/

#ifndef _THEME_H_
#define _THEME_H_

/*
Theme objects are constructed from database records of the Theme table.

The CThemeRecordset class is used to select and create CTheme objects
from the Theme table via functions in the CDatabaseRecordset parent class.
*/
#include "dbsets.h"

class COMMMSTVEXPORT CThemeRecordset : public CDatabaseRecordset
{
// This class provides Theme recordset manipulation via parent functions

virtual CString GetTableName( VOID);

virtual BOOL    SetRecordsetObject( VOID* cRecordsetObject);

public:
virtual VOID*   GetRecordsetObject( VOID);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, LONG lThemeID);
};


class COMMMSTVEXPORT CTheme : public CObject
{

    friend class CThemeRecordset; // generates the CTheme record object

private:
    LONG        m_lThemeID;
    LONG        m_lGenreID;
	LONG		m_lSubGenreID;

public:
	CTheme(LONG lThemeID = AFX_RFX_LONG_PSEUDO_NULL,
			LONG lGenreID = 0,
			LONG lSubGenreID = 0) :
			    m_lThemeID(lThemeID),
			    m_lGenreID(lGenreID),
				m_lSubGenreID(lSubGenreID) { }
	~CTheme(VOID) { }

    VOID    SetThemeID( LONG lThemeID) { m_lThemeID = lThemeID; }
	VOID    SetGenreID( LONG lGenreID) { m_lGenreID = lGenreID; }
    VOID    SetSubGenreID( LONG lSubGenreID) { m_lSubGenreID = lSubGenreID; }

    LONG    ThemeID() { return m_lThemeID; }
    LONG    GenreID() { return m_lGenreID; }
	LONG	SubGenreID() { return m_lSubGenreID; }
};


// Table: Theme
#define  TBL_Theme  _T("Theme")

//      Field:                         Index			Name     Type    Size
#define FLD_Theme_ThemeID		_T("T Theme ID")	// ThemeID   Long     4
#define FLD_Theme_GenreID		_T("T Genre ID")	// GenreID   Long     4
#define FLD_Theme_SubGenreID	_T("T SubGenre ID")	// GenreID   Long     4

#endif

