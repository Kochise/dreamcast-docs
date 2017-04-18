/***********************************************************************
**      S T A T I O N . H         		                               *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*
        STATION.H

        Station record object class definitions for Microsoft Guide
*/


#ifndef _STATION_H_
#define _STATION_H_


/*

Station objects are constructed from database records of the Station table.

The CStationRecordset class is used to select and create Station objects
from the Station table via functions in the CDatabaseRecordset parent class.

*/


#include "dbsets.h"


class COMMMSTVEXPORT CStationRecordset : public CDatabaseRecordset
{
// This class provides Channel recordset manipulation via parent functions

virtual CString GetTableName( VOID);

virtual BOOL    SetRecordsetObject( VOID* cRecordsetObject);

public:
virtual VOID*   GetRecordsetObject( VOID);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, LONG lStationID);
};


class COMMMSTVEXPORT CStation : public CObject
{
    friend class CStationRecordset; // generates the CStation record object

protected:

	long m_lStationID;
	CString m_cszCallLetters;
	CString m_cszName;
	long m_lNetworkID;
	CString m_cszLogo;
	CString m_cszDescription;
		
public:

	CStation(LONG lStationID = AFX_RFX_LONG_PSEUDO_NULL,
				CString sCallLetters = "",
				CString sName = "",
				LONG lNetworkID = 0,
				CString sLogo = "",
				CString sDescription = "") :
				m_lStationID(0),
				m_cszCallLetters(sCallLetters),
				m_cszName(sName),
				m_lNetworkID(lNetworkID),
				m_cszLogo(sLogo),
				m_cszDescription(sDescription) { }
	~CStation() { }

    void SetCallLetters( LPCTSTR szCallLetters ) { m_cszCallLetters = szCallLetters; }
    void SetName( LPCTSTR szName ) { m_cszName = szName; }
    void SetNetworkID( long lNetworkID ) { m_lNetworkID = lNetworkID; }
    void SetLogo( LPCTSTR szLogo ) { m_cszLogo = szLogo; }
    void SetDescription( LPCTSTR szDescription ) { m_cszDescription = szDescription; }
    
    long StationID() { return m_lStationID; } 
	CString CallLetters() { return m_cszCallLetters; }
	CString Name() { return m_cszName; }
	long NetworkID() { return m_lNetworkID; }
	CString Logo() { return m_cszLogo; }
	CString Description() { return m_cszDescription; }
};


// Table: Station

#define  TBL_Station  _T("Station")

#define FLD_Station_StationID		_T("S Station ID")
#define FLD_Station_CallLetters		_T("S Call Letters")
#define FLD_Station_Name			_T("S Name")
#define FLD_Station_NetworkID		_T("S Network ID")
#define FLD_Station_Logo			_T("S Logo")
#define FLD_Station_Description		_T("S Description")

#endif


