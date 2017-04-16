/***********************************************************************
**      C H A N N E L T . H                                            *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*

        CHANNELT.H

        ChannelT record object class definitions for Microsoft Guide



*/



#ifndef _CHANNELT_H_
#define _CHANNELT_H_


/*

ChannelT objects are constructed from database records of the ChannelT table.

The CChannelTRecordset class is used to select and create CChannelT objects
from the ChannelT table via functions in the CDatabaseRecordset parent class.

*/


#include "dbsets.h"


class COMMMSTVEXPORT CChannelTRecordset : public CDatabaseRecordset
{

// This class provides ChannelT recordset manipulation via parent functions


virtual CString GetTableName( VOID);

virtual BOOL    SetRecordsetObject( VOID* cRecordsetObject);

public:
virtual VOID*   GetRecordsetObject( VOID);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, LONG lChannelID);
};




class COMMMSTVEXPORT CChannelT : public CObject
{

    friend class CChannelTRecordset; // generates the CChannelT record object


public:

	CChannelT(LONG lChannelID = AFX_RFX_LONG_PSEUDO_NULL,
				LONG lTuningSpace = 0,
				LONG lChannelNumber = 0,
				COleDateTime codtStartTime = (DATE) 0,
				COleDateTime codtEndTime = (DATE) 0,
				LONG lLength = 0,
				LONG lStationID = 0,
				CString cszDescription = "",
				LONG lEnhMapID = 0,
				LONG lRatingID = 0,
				LONG lDisplayMask = 0,
				LONG lPaymentAddress = -1,
				LONG lPaymentToken = 0,
				COleDateTime codtLastUpdate = (DATE) 0,
				BOOL bTunable = TRUE) :
				m_lChannelID(lChannelID),
				m_lTuningSpace(lTuningSpace),
				m_lChannelNumber(lChannelNumber),
				m_codtStartTime(codtStartTime),
				m_codtEndTime(codtEndTime),
				m_lLength(lLength),
				m_lStationID(lStationID),
				m_cszDescription(cszDescription),
				m_lEnhMapID(lEnhMapID),
				m_lRatingID(lRatingID),
				m_lDisplayMask(lDisplayMask),
				m_lPaymentAddress(lPaymentAddress),
				m_lPaymentToken(lPaymentToken),
				m_LastUpdate(codtLastUpdate),
				m_bTunable(bTunable) { }
	~CChannelT(VOID) { }

    void SetTuningSpace( long lTuningSpace ) { m_lTuningSpace = lTuningSpace; }
    void SetChannelNumber( long lChannelNumber ) { m_lChannelNumber = lChannelNumber; }
    void SetStartTime( COleDateTime& codtStartTime ) { m_codtStartTime = codtStartTime; }
    void SetEndTime( COleDateTime& codtEndTime ) { m_codtEndTime = codtEndTime; }
    void SetLength( long lLength ) { m_lLength = lLength; }
	void SetStationID( long lStationID ) { m_lStationID = lStationID; }
	void SetDescription( LPCTSTR szDescription ) { m_cszDescription = szDescription; }
    void SetEnhMapID( LONG lEnhMapID) { m_lEnhMapID = lEnhMapID; }
    void SetRatingID( long lRatingID ) { m_lRatingID = lRatingID; }
    void SetDisplayMask( long lDisplayMask ) { m_lDisplayMask = lDisplayMask; }
    void SetPaymentAddress( long lPaymentAddress ) { m_lPaymentAddress = lPaymentAddress; }
    void SetPaymentToken( long lPaymentToken ) { m_lPaymentToken = lPaymentToken; }
    void SetLastUpdate( COleDateTime& codtLastUpdate ) { m_LastUpdate = codtLastUpdate; }
	void SetTunable ( BOOL bTunable ) { m_bTunable = bTunable; }

    long ChannelID() { return m_lChannelID; }
	long TuningSpace() { return m_lTuningSpace; }
	long ChannelNumber() { return m_lChannelNumber; }
	COleDateTime StartTime() { return m_codtStartTime; }
	COleDateTime EndTime() { return m_codtEndTime; }
	long Length() { return m_lLength; }
    long StationID( ) { return m_lStationID; }
	CString Description() { return m_cszDescription; }
    LONG EnhMapID() { return m_lEnhMapID; }
	long RatingID() { return m_lRatingID; }
	long DisplayMask() { return m_lDisplayMask; }
	long PaymentAddress() { return m_lPaymentAddress; }
	long PaymentToken() { return m_lPaymentToken; }
	COleDateTime LastUpdate() { return m_LastUpdate; }
	BOOL Tunable() { return m_bTunable; }

protected:

	long m_lChannelID;
	long m_lTuningSpace;
	long m_lChannelNumber;
	COleDateTime m_codtStartTime;
	COleDateTime m_codtEndTime;
	long m_lLength;
	long m_lStationID;
	CString m_cszDescription;
    LONG m_lEnhMapID;
	long m_lRatingID;
	long m_lDisplayMask;
	long m_lPaymentAddress;
	long m_lPaymentToken;
	COleDateTime m_LastUpdate;
	BOOL m_bTunable;
};

// Table: ChannelT

#define  TBL_ChannelT	_T("Channel")

#define FLD_ChannelT_ChannelID		_T("C Channel ID")		// C ChannelID		AutoLong  4
#define FLD_ChannelT_TuningSpace	_T("C Tuning Space")
#define FLD_ChannelT_ChannelNumber	_T("C Channel Number")
#define FLD_ChannelT_StartTime		_T("C Start Time")
#define FLD_ChannelT_EndTime		_T("C End Time")
#define FLD_ChannelT_Length			_T("C Length")
#define FLD_ChannelT_StationID		_T("C Station ID")
#define FLD_ChannelT_Description	_T("C Description")
#define FLD_ChannelT_EnhMapID		_T("C Enhancement Mapping ID")
#define FLD_ChannelT_RatingID		_T("C Rating ID")
#define FLD_ChannelT_DisplayMask	_T("C Display Mask")
#define FLD_ChannelT_PaymentAddress	_T("C Payment Address")
#define FLD_ChannelT_PaymentToken	_T("C Payment Token")
#define FLD_ChannelT_LastUpdate		_T("C Last Update")
#define FLD_ChannelT_Tunable		_T("C Tunable")

#endif

