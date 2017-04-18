/***********************************************************************
**      	S T R E A M T Y . H                                        *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*
        STREAMTY.H

        StreamType record object class definitions for Microsoft Guide
*/


#ifndef _STREAMTY_H_
#define _STREAMTY_H_


#include "dbsets.h"


/*

StreamType objects are constructed from database records of the StreamType table.

The CStreamTypeRecordset class is used to select and create CStreamType objects
from the StreamType table via functions in the CDatabaseRecordset parent class.

*/


class COMMMSTVEXPORT CStreamTypeRecordset : public CDatabaseRecordset
{

// This class provides StreamType recordset manipulation via parent functions


virtual CString GetTableName( VOID);

virtual BOOL    SetRecordsetObject( VOID* cRecordsetObject);

public:
virtual VOID*   GetRecordsetObject( VOID);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, LONG lStreamTypeID);
};


class COMMMSTVEXPORT CStreamType : public CObject
{

    friend class CStreamTypeRecordset; // generates the CStreamType record object

private:

    LONG		m_lStreamTypeID;
    LONG		m_lTuningSpace;
    LONG		m_lValue;
    CString		m_cszDescription;
    LONG		m_lCategory;
    LONG		m_lLocaleID;

public:

	CStreamType(LONG lStreamTypeID = AFX_RFX_LONG_PSEUDO_NULL,
				LONG lTuningSpace = 0,
				LONG lValue = 0,
				CString cszDescription = "",
				LONG lCategory = 0,
				LONG lLocaleID = 0) :
				m_lStreamTypeID(lStreamTypeID),
				m_lTuningSpace(lTuningSpace),
				m_lValue(lValue),
				m_cszDescription(cszDescription),
				m_lCategory(lCategory),
				m_lLocaleID(lLocaleID) { }

	~CStreamType(VOID) { }

    VOID    SetTuningSpace( LONG lTuningSpace) { m_lTuningSpace = lTuningSpace; }
    VOID    SetValue( LONG lValue) { m_lValue = lValue; }
    VOID    SetDescription( CString cszDescription) { m_cszDescription = cszDescription; }
    VOID    SetCategory( LONG lCategory) { m_lCategory = lCategory; }
    VOID    SetLocaleID( LONG lLocaleID) { m_lLocaleID = lLocaleID; }

    LONG            StreamTypeID() { return m_lStreamTypeID; }
    LONG            TuningSpace() { return m_lTuningSpace; }
    LONG            Value() { return m_lValue; }
    CString         Description() { return m_cszDescription; }
    LONG            Category() { return m_lCategory; }
    LONG            LocaleID() { return m_lLocaleID; }
};


// Table: StreamType

#define TBL_StreamType  _T("[Stream Type]")

//      Field:                          Name                    	Type    		Size

#define FLD_StreamType_StreamTypeID		_T("SR Stream Type ID")		// AutoLong  	4
#define FLD_StreamType_TuningSpace		_T("SR Tuning Space")		// Long      	4
#define FLD_StreamType_Value			_T("SR Value")      		// Long      	4
#define FLD_StreamType_Description		_T("SR Description")		// Text      	Memo
#define FLD_StreamType_Category			_T("SR Category")			// Long      	4
#define FLD_StreamType_LocaleID			_T("SR LocaleID")			// Long      	4

#endif

