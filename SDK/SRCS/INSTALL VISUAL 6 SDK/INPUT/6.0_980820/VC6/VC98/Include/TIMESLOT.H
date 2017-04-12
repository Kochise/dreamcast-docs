/***********************************************************************
**      T I M E S L O T . H                                            *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*

        TIMESLOT.H

        TimeSlot record object class definitions for Microsoft Guide



*/



#ifndef _TIMESLOT_H_
#define _TIMESLOT_H_

#include "dbsets.h"


/*

TimeSlot objects are constructed from database records of the TimeSlot table.

The CTimeSlotRecordset class is used to select and create CTimeSlot objects
from the TimeSlot table via functions in the CDatabaseRecordset parent class.

*/



class COMMMSTVEXPORT CTimeSlotRecordset : public CDatabaseRecordset
{

// This class provides TimeSlot recordset manipulation via parent functions


virtual CString GetTableName( VOID);

virtual BOOL    SetRecordsetObject( VOID* cRecordsetObject);

public:
virtual VOID*   GetRecordsetObject( VOID);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, LONG lTimeSlotID);
};




class COMMMSTVEXPORT CTimeSlot : public CObject
{

    friend class CTimeSlotRecordset; // generates the CTimeSlot record object


private:

    LONG            m_lTimeSlotID;
    LONG            m_lChannelID;
    LONG            m_lEpisodeID;
    COleDateTime    m_codtStartTime;
    COleDateTime    m_codtEndTime;
    LONG            m_lLength;
    LONG            m_lPaymentAddress;
    LONG            m_lPaymentToken;
    COleDateTime    m_codtLastUpdate;
	BOOL			m_bPayPerView;
	BOOL			m_bClosedCaption;
	BOOL			m_bStereo;
	BOOL			m_bRerun;
	BOOL			m_bTapeInhibited;
	BOOL			m_bOtherPropertiesExist;
	BOOL			m_bAlternateDataExists;
	BOOL			m_bAlternateAudioExists;
    LONG			m_lEnhMapID;

public:

	CTimeSlot(LONG lTimeSlotID = AFX_RFX_LONG_PSEUDO_NULL,
				LONG lChannelID = 0,
				LONG lEpisodeID = 0,
				COleDateTime codtStartTime = (DATE) 0,
				COleDateTime codtEndTime = (DATE) 0,
				LONG lLength = 0,
				LONG lPaymentAddress = -1,
				LONG lPaymentToken = 0,
				COleDateTime codtLastUpdate = (DATE) 0,
				BOOL bPayPerView = FALSE,
				BOOL bClosedCaption = FALSE,
				BOOL bStereo = FALSE,
				BOOL bRerun = FALSE,
				BOOL bTapeInhibited = FALSE,
				BOOL bOtherPropertiesExist = FALSE,
				BOOL bAlternateDataExists = FALSE,
				BOOL bAlternateAudioExists = FALSE,
				LONG lEnhMapID = 0) :
				m_lTimeSlotID(lTimeSlotID),
				m_lChannelID(lChannelID),
				m_lEpisodeID(lEpisodeID),
				m_codtStartTime(codtStartTime),
				m_codtEndTime(codtEndTime),
				m_lLength(lLength),
				m_lPaymentAddress(lPaymentAddress),
				m_lPaymentToken(lPaymentToken),
				m_codtLastUpdate(codtLastUpdate),
				m_bPayPerView(bPayPerView),
				m_bClosedCaption(bClosedCaption),
				m_bStereo(bStereo),
				m_bRerun(bRerun),
				m_bTapeInhibited(bTapeInhibited),
				m_bOtherPropertiesExist(bOtherPropertiesExist),
				m_bAlternateDataExists(bAlternateDataExists),
				m_bAlternateAudioExists(bAlternateAudioExists),
				m_lEnhMapID(lEnhMapID) { }

	~CTimeSlot(VOID) { }

    VOID    SetChannelID( LONG lChannelID) { m_lChannelID = lChannelID; }
    VOID    SetEpisodeID( LONG lEpisodeID) { m_lEpisodeID = lEpisodeID; }
    VOID    SetStartTime( COleDateTime StartTime) { m_codtStartTime = StartTime; }
    VOID    SetEndTime( COleDateTime EndTime) { m_codtEndTime = EndTime; }
    VOID    SetLength( LONG lLength) { m_lLength = lLength; }
    VOID    SetPaymentAddress( LONG lPaymentAddress) { m_lPaymentAddress = lPaymentAddress; }
    VOID    SetPaymentToken( LONG lPaymentToken) { m_lPaymentToken = lPaymentToken; }
    VOID    SetLastUpdate( COleDateTime LastUpdate) { m_codtLastUpdate = LastUpdate; }
    VOID    SetPayPerView( BOOL bPayPerView) { m_bPayPerView = bPayPerView; }
    VOID    SetClosedCaption( BOOL bClosedCaption) { m_bClosedCaption = bClosedCaption; }
    VOID    SetStereo( BOOL bStereo) { m_bStereo = bStereo; }
    VOID    SetRerun( BOOL bRerun) { m_bRerun = bRerun; }
    VOID    SetTapeInhibited( BOOL bTapeInhibited) { m_bTapeInhibited = bTapeInhibited; }
    VOID    SetOtherPropertiesExist( BOOL bOtherPropertiesExist) { m_bOtherPropertiesExist = bOtherPropertiesExist; }
    VOID    SetAlternateDataExists( BOOL bAlternateDataExists) { m_bAlternateDataExists = bAlternateDataExists; }
    VOID    SetAlternateAudioExists( BOOL bAlternateAudioExists) { m_bAlternateAudioExists = bAlternateAudioExists; }
    VOID	SetEnhMapID( LONG lEnhMapID) { m_lEnhMapID = lEnhMapID; }

    LONG            TimeSlotID() { return m_lTimeSlotID; }
    LONG            ChannelID() { return m_lChannelID; }
    LONG            EpisodeID() { return m_lEpisodeID; }
    COleDateTime    StartTime() { return m_codtStartTime; }
    COleDateTime    EndTime() { return m_codtEndTime; }
    LONG            Length() { return m_lLength; }
    LONG            PaymentAddress() { return m_lPaymentAddress; }
    LONG            PaymentToken() { return m_lPaymentToken; }
    COleDateTime    LastUpdate() { return m_codtLastUpdate; }
    BOOL   			PayPerView() { return m_bPayPerView; }
    BOOL   			ClosedCaption() { return m_bClosedCaption; }
    BOOL   			Stereo() { return m_bStereo; }
    BOOL   			Rerun() { return m_bRerun; }
    BOOL   			TapeInhibited() { return m_bTapeInhibited; }
    BOOL   			OtherPropertiesExist() { return m_bOtherPropertiesExist; }
    BOOL   			AlternateDataExists() { return m_bAlternateDataExists; }
    BOOL   			AlternateAudioExists() { return m_bAlternateAudioExists; }
    LONG			EnhMapID() { return m_lEnhMapID; }
};


// Table: TimeSlot

#define  TBL_TimeSlot  _T("[Time Slot]")

//      Field:                          Name                    Type    Size

#define FLD_TimeSlot_TimeSlotID     _T("TS Time Slot ID")    // AutoLong  4
#define FLD_TimeSlot_ChannelID      _T("TS Channel ID")      // Long      4
#define FLD_TimeSlot_EpisodeID      _T("TS Episode ID")      // Long      4
#define FLD_TimeSlot_StartTime      _T("TS Start Time")      // Date      8
#define FLD_TimeSlot_EndTime        _T("TS End Time")        // Date      8
#define FLD_TimeSlot_Length         _T("TS Length")          // Long      4
#define FLD_TimeSlot_PaymentAddress _T("TS Payment Address") // Long      4
#define FLD_TimeSlot_PaymentToken   _T("TS Payment Token")   // Long      4
#define FLD_TimeSlot_LastUpdate     _T("TS Last Update")     // Date      8
#define FLD_TimeSlot_PayPerView		_T("TS Pay Per View")     // Bool      4
#define FLD_TimeSlot_ClosedCaption      _T("TS Closed Caption")     // Bool      4
#define FLD_TimeSlot_Stereo				_T("TS Stereo")     // Bool      4
#define FLD_TimeSlot_Rerun				_T("TS Rerun")     // Bool      4
#define FLD_TimeSlot_TapeInhibited      _T("TS Tape Inhibited")     // Bool      4
#define FLD_TimeSlot_OtherPropertiesExist	_T("TS Other Properties Exist")     // Bool      4
#define FLD_TimeSlot_AlternateDataExists	_T("TS Alternate Data Exists")     // Bool      4
#define FLD_TimeSlot_AlternateAudioExists	_T("TS Alternate Audio Exists")     // Bool      4
#define FLD_TimeSlot_EnhMapID		_T("TS Enhancement Mapping ID")


#endif

