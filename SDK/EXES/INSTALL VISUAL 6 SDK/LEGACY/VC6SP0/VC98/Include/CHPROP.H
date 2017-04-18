/***********************************************************************
**      C P R O P . H												   *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*
        CPROP.H

        ChannelProperty record object class definitions for Microsoft Guide
*/


#ifndef _CPROP_H_
#define _CPROP_H_


#include "dbsets.h"


/*

ChannelProperty objects are constructed from database records of the ChannelProperty table.

The CChannelPropertyRecordset class is used to select and create CChannelProperty objects
from the ChannelProperty table via functions in the CDatabaseRecordset parent class.

*/


class  COMMMSTVEXPORT CChannelPropertyRecordset : public CDatabaseRecordset
{
// This class provides ChannelProperty recordset manipulation via parent functions

virtual CString GetTableName( VOID);

virtual BOOL    SetRecordsetObject( VOID* cRecordsetObject);

public:
virtual VOID*   GetRecordsetObject( VOID);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);
};


class COMMMSTVEXPORT CChannelProperty : public CObject
{
    friend class CChannelPropertyRecordset; // generates the CChannelProperty record object

private:

    LONG            m_lChannelID;
    LONG            m_lBroadcastPropertyID;

public:

	CChannelProperty(LONG lChannelID = 0,
						LONG lBroadcastPropertyID = 0) :
					    m_lChannelID(lChannelID),
					    m_lBroadcastPropertyID(lBroadcastPropertyID) { }

	~CChannelProperty(VOID) { }


    VOID    SetChannelID( LONG lChannelID) { m_lChannelID = lChannelID; }
    VOID    SetBroadcastPropertyID( LONG lBroadcastPropertyID) { m_lBroadcastPropertyID = lBroadcastPropertyID; }

    LONG            ChannelID() { return m_lChannelID; }
    LONG            BroadcastPropertyID() { return m_lBroadcastPropertyID; }
};


// Table: Channel

#define  TBL_ChannelProperty  _T("[Channel Property]")

//      Field:                                        Name                          Type    	Size

#define FLD_ChannelProperty_ChannelID				_T("CP Channel ID")          	// Long		4
#define FLD_ChannelProperty_BroadcastPropertyID		_T("CP Broadcast Property ID") 	// Long		4

#endif


