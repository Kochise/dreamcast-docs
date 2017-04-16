/***********************************************************************
**      	C H A N S T R . H                     	                   *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*
        CHANSTR.H

        ChannelStream record object class definitions for Microsoft Guide
*/


#ifndef _CHANSTR_H_
#define _CHANSTR_H_


#include "dbsets.h"


/*

ChannelStream objects are constructed from database records of the ChannelStream table.

The CChannelStreamRecordset class is used to select and create CChannelStream objects
from the ChannelStream table via functions in the CDatabaseRecordset parent class.

*/


class  COMMMSTVEXPORT CChannelStreamRecordset : public CDatabaseRecordset
{
// This class provides ChannelStream recordset manipulation via parent functions

virtual CString GetTableName( VOID);

virtual BOOL    SetRecordsetObject( VOID* cRecordsetObject);

public:
virtual VOID*   GetRecordsetObject( VOID);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);
};


class COMMMSTVEXPORT CChannelStream : public CObject
{
    friend class CChannelStreamRecordset; // generates the CChannelStream record object

private:

	LONG		m_lChannelID;
	LONG		m_lStreamTypeID;
    LONG		m_lSubChannel;
    CString		m_cszName;

public:

	CChannelStream(LONG lChannelID = 0,
					LONG lStreamTypeID = 0,
					LONG lSubChannel = 0,
					CString cszName = "") :
					m_lChannelID(lChannelID),
					m_lStreamTypeID(lStreamTypeID),
					m_lSubChannel(lSubChannel),
					m_cszName(cszName) { }

	~CChannelStream(VOID) { }

    VOID    SetChannelID( LONG lChannelID) { m_lChannelID = lChannelID; }
    VOID    SetStreamTypeID( LONG lStreamTypeID) { m_lStreamTypeID = lStreamTypeID; }
    VOID    SetSubChannel( LONG lSubChannel) { m_lSubChannel = lSubChannel; }
    VOID    SetName( CString cszName) { m_cszName = cszName; }

    LONG            ChannelID() { return m_lChannelID; }
    LONG            StreamTypeID() { return m_lStreamTypeID; }
    LONG            SubChannel() { return m_lSubChannel; }
    CString         Name() { return m_cszName; }
};

// Table: ChannelStream

#define TBL_ChannelStream  _T("[Channel Stream]")

//      Field:                          Name                    	Type    	Size

#define FLD_ChannelStream_ChannelID		_T("CSR Channel ID")			// Long  	4
#define FLD_ChannelStream_StreamTypeID	_T("CSR Stream Type ID")		// Long  	4
#define FLD_ChannelStream_SubChannel	_T("CSR SubChannel")			// Long     4
#define FLD_ChannelStream_Name			_T("CSR Name")      			// Memo     255

#endif


