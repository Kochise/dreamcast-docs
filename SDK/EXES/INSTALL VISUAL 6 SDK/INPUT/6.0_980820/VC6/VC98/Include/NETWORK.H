/***********************************************************************
**      N E T W O R K . H         		                               *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*
        NETWORK.H

        Network record object class definitions for Microsoft Guide
*/


#ifndef _NETWORK_H_
#define _NETWORK_H_


/*

Network objects are constructed from database records of the Network table.

The CNetworkRecordset class is used to select and create Network objects
from the Network table via functions in the CDatabaseRecordset parent class.

*/


#include "dbsets.h"


class COMMMSTVEXPORT CNetworkRecordset : public CDatabaseRecordset
{
// This class provides Channel recordset manipulation via parent functions

virtual CString GetTableName( VOID);

virtual BOOL    SetRecordsetObject( VOID* cRecordsetObject);

public:
virtual VOID*   GetRecordsetObject( VOID);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, LONG lNetworkID);
};


class COMMMSTVEXPORT CNetwork : public CObject
{
    friend class CNetworkRecordset; // generates the CNetwork record object

protected:

	long m_lNetworkID;
	CString m_cszName;
	CString m_cszLogoMoniker;
		
public:

	CNetwork(long lNetworkID = AFX_RFX_LONG_PSEUDO_NULL,
				CString cszName = "",
				CString cszLogoMoniker = "") :
				m_lNetworkID(lNetworkID),
				m_cszName(cszName),
				m_cszLogoMoniker(cszLogoMoniker) { }
	~CNetwork() { }

    void SetName( LPCTSTR szName ) { m_cszName = szName; }
    void SetLogoMoniker( LPCTSTR szLogoMoniker ) { m_cszLogoMoniker = szLogoMoniker; }
    
	long NetworkID() { return m_lNetworkID; }
	CString Name() { return m_cszName; }
	CString LogoMoniker() { return m_cszLogoMoniker; }
};


// Table: Network

#define  TBL_Network  _T("Network")

#define FLD_Network_NetworkID		_T("N Network ID")
#define FLD_Network_Name			_T("N Name")
#define FLD_Network_LogoMoniker		_T("N LogoMoniker")


#endif


