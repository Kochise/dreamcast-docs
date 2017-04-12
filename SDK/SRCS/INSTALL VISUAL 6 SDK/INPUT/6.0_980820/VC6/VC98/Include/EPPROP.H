/***********************************************************************
**      E P P R O P . H                                                *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*

        EPPROP.H

        EpisodeProperty record object class definitions for Microsoft Guide



*/



#ifndef _EPPROP_H_
#define _EPPROP_H_


#include "dbsets.h"


/*

EpisodeProperty objects are constructed from database records of the EpisodeProperty table.

The CEpisodePropertyRecordset class is used to select and create CEpisodeProperty objects
from the EpisodeProperty table via functions in the CDatabaseRecordset parent class.

*/



class  COMMMSTVEXPORT CEpisodePropertyRecordset : public CDatabaseRecordset
{

// This class provides EpisodeProperty recordset manipulation via parent functions

virtual CString GetTableName( VOID);

virtual BOOL    SetRecordsetObject( VOID* cRecordsetObject);

public:
virtual VOID*   GetRecordsetObject( VOID);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);
};




class COMMMSTVEXPORT CEpisodeProperty : public CObject
{

    friend class CEpisodePropertyRecordset; // generates the CEpisodeProperty record object


public:

	CEpisodeProperty(LONG m_lEpisodeID = 0,
						LONG lBroadcastPropertyID = 0) :
					    m_lEpisodeID(m_lEpisodeID),
					    m_lBroadcastPropertyID(lBroadcastPropertyID) { }

	~CEpisodeProperty(VOID) { }

    VOID    SetEpisodeID( LONG lEpisodeID) { m_lEpisodeID = lEpisodeID; }
    VOID    SetBroadcastPropertyID( LONG lBroadcastPropertyID) { m_lBroadcastPropertyID = lBroadcastPropertyID; }

    LONG            EpisodeID() { return m_lEpisodeID; }
    LONG            BroadcastPropertyID() { return m_lBroadcastPropertyID; }


private:

    LONG            m_lEpisodeID;
    LONG            m_lBroadcastPropertyID;


};

// Table: EpisodeProperty

#define  TBL_EpisodeProperty  _T("[Episode Property]")

//      Field:                                      Name                          Type    Size

#define FLD_EpisodeProperty_EpisodeID           _T("EP Episode ID")            // Long      4
#define FLD_EpisodeProperty_BroadcastPropertyID _T("EP Broadcast Property ID") // Long      4


#endif

