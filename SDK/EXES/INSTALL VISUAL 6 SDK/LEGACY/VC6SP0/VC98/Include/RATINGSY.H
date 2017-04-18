/***********************************************************************
**      R A T I N G . H                                                *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*

        RATING.H

        Rating record object class definitions for Microsoft Guide



*/



#ifndef _RATINGSYSTEM_H_
#define _RATINGSYSTEM_H_


#include "dbsets.h"


/*

Rating objects are constructed from database records of the RatingSystem table.

The CRatingSystemRecordset class is used to select and create CRatingSystem objects
from the RatingSystem table via functions in the CDatabaseRecordset parent class.

*/


class COMMMSTVEXPORT CRatingSystemRecordset : public CDatabaseRecordset
{
// This class provides RatingSystem recordset manipulation via parent functions

	virtual CString GetTableName(VOID);

	virtual BOOL    SetRecordsetObject(VOID *cRecordsetObject);

public:
virtual VOID*   GetRecordsetObject(VOID);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, LONG lRatingSystemID);
};


class COMMMSTVEXPORT CRatingSystem : public CObject
{
    friend class CRatingSystemRecordset; // generates the CRating record object

private:

    LONG            m_lRatingSystemID;
	LONG            m_lTuningSpace;
    CString         m_cszName;
    CString         m_cszDescription;
    
public:
			CRatingSystem(LONG lRatingSystemID = AFX_RFX_LONG_PSEUDO_NULL,
							LONG lTuningSpace = 0,
							CString cszName = "",
							CString cszDescription = "") :
						    m_lRatingSystemID(lRatingSystemID),
						    m_lTuningSpace(lTuningSpace),
							m_cszName(cszName),
							m_cszDescription(cszDescription){ }
			~CRatingSystem(VOID) { }

    VOID    SetTuningSpace( LONG lTuningSpace) { m_lTuningSpace = lTuningSpace; }
    VOID    SetName( LPCTSTR cszName) { m_cszName = cszName; }
    VOID    SetDescription( LPCTSTR cszDescription) { m_cszDescription = cszDescription; }

    LONG            RatingSystemID() { return m_lRatingSystemID; }
    LONG            TuningSpace() { return m_lTuningSpace; }
    CString         Name() { return m_cszName; }
    CString         Description() { return m_cszDescription; }
};


// Table: Rating

#define  TBL_RatingSystem  _T("[Rating System]")

//      Field:									Name					Type		Size

#define FLD_RatingSystem_RatingSystemID		_T("RS Rating System ID")	// Long		4
#define FLD_RatingSystem_TuningSpace		_T("RS Tuning Space")		// Long		4
#define FLD_RatingSystem_Name				_T("RS Name")				// Text		255
#define FLD_RatingSystem_Description		_T("RS Description")		// Text     50

#endif


