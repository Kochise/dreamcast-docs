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



#ifndef _RATING_H_
#define _RATING_H_


#include "dbsets.h"


/*

Rating objects are constructed from database records of the Rating table.

The CRatingRecordset class is used to select and create CRating objects
from the Rating table via functions in the CDatabaseRecordset parent class.

*/



class COMMMSTVEXPORT CRatingRecordset : public CDatabaseRecordset
{

// This class provides Rating recordset manipulation via parent functions


virtual CString GetTableName( VOID);

virtual BOOL    SetRecordsetObject( VOID* cRecordsetObject);

public:
virtual VOID*   GetRecordsetObject( VOID);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, LONG lRatingID);
};




class COMMMSTVEXPORT CRating : public CObject
{

    friend class CRatingRecordset; // generates the CRating record object


public:

			CRating(LONG lRatingID = AFX_RFX_LONG_PSEUDO_NULL,
					LONG lRatingSystemID = 0,
					FLOAT flRating = 0,
					CString cszDescription = "",
					CString cszPictogramMoniker = "") :
				    m_lRatingID(lRatingID),
				    m_lRatingSystemID(lRatingSystemID),
				    m_flRating(flRating),
					m_cszDescription(cszDescription),
					m_cszPictogramMoniker(cszPictogramMoniker) { }
			~CRating(VOID) { }

    VOID    SetRatingSystemID( LONG lRatingSystemID) { m_lRatingSystemID = lRatingSystemID; }
    VOID    SetRating( FLOAT flRating) { m_flRating = flRating; }
    VOID    SetDescription( LPCTSTR cszDescription) { m_cszDescription = cszDescription; }
    VOID    SetPictogramMoniker( LPCTSTR cszPictogramMoniker) { m_cszPictogramMoniker = cszPictogramMoniker; }

    LONG            RatingID() { return m_lRatingID; }
    LONG            RatingSystemID() { return m_lRatingSystemID; }
    FLOAT           Rating() { return m_flRating; }
    CString         Description() { return m_cszDescription; }
    CString         PictogramMoniker() { return m_cszPictogramMoniker; }


private:

    LONG            m_lRatingID;
    LONG            m_lRatingSystemID;
    FLOAT           m_flRating;
    CString         m_cszDescription;
    CString         m_cszPictogramMoniker;


};

// Table: Rating

#define  TBL_Rating  _T("Rating")

//      Field:                          Name                     Type    Size

#define FLD_Rating_RatingID         _T("R Rating ID")         // AutoLong  4
#define FLD_Rating_RatingSystemID   _T("R Rating System ID")  // Long      4
#define FLD_Rating_Rating           _T("R Rating")            // Float     4
#define FLD_Rating_Description      _T("R Description")       // Text     50
#define FLD_Rating_PictogramMoniker _T("R Pictogram Moniker") // Text    255


#endif

