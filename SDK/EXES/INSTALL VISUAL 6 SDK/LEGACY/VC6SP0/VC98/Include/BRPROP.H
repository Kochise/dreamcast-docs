/***********************************************************************
**      B R P R O P . H                                                *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*

        BRPROP.H

        BroadcastProperty record object class definitions for Microsoft Guide



*/



#ifndef _BRPROP_H_
#define _BRPROP_H_


#include "dbsets.h"


/*

BroadcastProperty objects are constructed from database records of the BroadcastProperty table.

The CBroadcastPropertyRecordset class is used to select and create CBroadcastProperty objects
from the BroadcastProperty table via functions in the CDatabaseRecordset parent class.

*/



class  COMMMSTVEXPORT CBroadcastPropertyRecordset : public CDatabaseRecordset
{

// This class provides BroadcastProperty recordset manipulation via parent functions


virtual CString GetTableName( VOID);


virtual BOOL    SetRecordsetObject( VOID* cRecordsetObject);

public:
virtual VOID*   GetRecordsetObject( VOID);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, LONG lBroadcastPropertyID);
};




class COMMMSTVEXPORT CBroadcastProperty : public CObject
{

    friend class CBroadcastPropertyRecordset; // generates the CBroadcastProperty record object

private:

    LONG            m_lBroadcastPropertyID;
    LONG            m_lTuningSpace;
    CString         m_cszAbbreviation;
    CString         m_cszName;
    LONG            m_lDisplayOrder;
    CString         m_cszPictogramMoniker;

public:

	CBroadcastProperty(LONG lBroadcastPropertyID = AFX_RFX_LONG_PSEUDO_NULL,
						LONG lTuningSpace = 0,
						CString cszAbbreviation = "",
						CString cszName = "",
						LONG lDisplayOrder = 0,
						CString cszPictogramMoniker = "") :
					    m_lBroadcastPropertyID(lBroadcastPropertyID),
					    m_lTuningSpace(lTuningSpace),
					    m_cszAbbreviation(cszAbbreviation), 
					    m_cszName(cszName),
					    m_lDisplayOrder(lDisplayOrder),
					    m_cszPictogramMoniker(cszPictogramMoniker) { }

	~CBroadcastProperty(VOID) { }


    VOID    SetTuningSpace( LONG lTuningSpace) { m_lTuningSpace = lTuningSpace; }
    VOID    SetAbbreviation( LPCTSTR cszAbbreviation) { m_cszAbbreviation = cszAbbreviation; }
    VOID    SetName( LPCTSTR cszName) { m_cszName = cszName; }
    VOID    SetDisplayOrder( LONG lDisplayOrder) { m_lDisplayOrder = lDisplayOrder; }
    VOID    SetPictogramMoniker( LPCTSTR cszPictogramMoniker) { m_cszPictogramMoniker = cszPictogramMoniker; }

    LONG            BroadcastPropertyID() { return m_lBroadcastPropertyID; }
    LONG            TuningSpace() { return m_lTuningSpace; }
    CString         Abbreviation() { return m_cszAbbreviation; }
    CString         Name() { return m_cszName; }
    LONG            DisplayOrder() { return m_lDisplayOrder; }
    CString         PictogramMoniker() { return m_cszPictogramMoniker; }
};


// Table: BroadcastProperty

#define  TBL_BroadcastProperty  _T("[Broadcast Property]")

//      Field:                                        Name                          Type    Size

#define FLD_BroadcastProperty_BroadcastPropertyID _T("BP Broadcast Property ID") // AutoLong  4
#define FLD_BroadcastProperty_TuningSpace         _T("BP Tuning Space")          // Long      4
#define FLD_BroadcastProperty_Abbreviation        _T("BP Abbreviation")          // Text      4
#define FLD_BroadcastProperty_Name                _T("BP Name")                  // Text    128
#define FLD_BroadcastProperty_DisplayOrder        _T("BP Display Order")         // Long      4
#define FLD_BroadcastProperty_PictogramMoniker    _T("BP Pictogram Moniker")     // Text    255

#endif

