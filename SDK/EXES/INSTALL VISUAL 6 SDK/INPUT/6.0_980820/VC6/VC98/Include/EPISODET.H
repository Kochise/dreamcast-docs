/***********************************************************************
**      E P I S O D E T. H                                              *
**                                                                     *
************************************************************************
** Copyright (C) 1996 by Microsoft Corporation                         *
**                 All Rights Reserved                                 *
************************************************************************/
/*
        EPISODET.H

        EpisodeT record object class definitions for Microsoft Guide

	This code controls the Episode table.  The code in Episode.cpp
	controls the SQ_EPG query.

*/


#ifndef __EPISODET_H__
#define __EPISODET_H__


/*

EpisodeT objects are constructed from database records of the EpisodeT table.

The CEpisodeTRecordset class is used to select and create CEpisodeT objects
from the EpisodeT table via functions in the CDatabaseRecordset parent class.

*/


#include "dbsets.h"


class COMMMSTVEXPORT CEpisodeTRecordset : public CDatabaseRecordset
{
// This class provides EpisodeT recordset manipulation via parent functions
protected:

virtual CString GetTableName( VOID);

virtual BOOL    SetRecordsetObject( VOID* cRecordsetObject);

public:
virtual VOID*   GetRecordsetObject( VOID);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, CObject &coo);
virtual BOOLEAN Seek(LPCTSTR lpszComparison, LONG lEpisodeID);
};


class COMMMSTVEXPORT CEpisodeT : public CObject
{

    friend class CEpisodeTRecordset; // generates the CEpisodeT record object

private:

	LONG			m_lEpisodeID;
	CString			m_cszTitle;
	CString			m_cszDescription;
	LONG			m_lEnhMapID;
	LONG			m_lDisplayMask;
	LONG			m_lThemeID;
	LONG			m_lRatingID;
	LONG			m_lAbbreviation;
	COleDateTime	m_codtLastUpdate;

public:

	CEpisodeT(LONG lEpisodeID = AFX_RFX_LONG_PSEUDO_NULL,
				CString cszTitle = "",
				CString cszDescription = "",
				LONG lEnhMapID = 0,
				LONG lDisplayMask = 0,
				LONG lThemeID = 0,
				LONG lRatingID = 0,
				LONG lAbbreviation = 0,
				COleDateTime codtLastUpdate = (DATE) 0) :
			m_lEpisodeID(lEpisodeID),
			m_cszTitle(cszTitle),
			m_cszDescription(cszDescription),
			m_lEnhMapID(lEnhMapID),
			m_lDisplayMask(lDisplayMask),
			m_lThemeID(lThemeID),
			m_lRatingID(lRatingID),
			m_lAbbreviation(lAbbreviation),
			m_codtLastUpdate(codtLastUpdate) { }
	~CEpisodeT(VOID) { }
	
    VOID    SetTitle( LPCTSTR cszTitle) { m_cszTitle = cszTitle; }
    VOID    SetDescription( LPCTSTR cszDescription) { m_cszDescription = cszDescription; }
    VOID	SetEnhMapID( LONG lEnhMapID) { m_lEnhMapID = lEnhMapID; }
	VOID	SetDisplayMask( LONG lDisplayMask) { m_lDisplayMask = lDisplayMask; }
	VOID	SetThemeID( LONG lThemeID) { m_lThemeID = lThemeID; }
	VOID	SetRatingID( LONG lRatingID) { m_lRatingID = lRatingID; }
	VOID	SetAbbreviation( LONG lAbbreviation) { m_lAbbreviation = lAbbreviation; }
	VOID	SetLastUpdate( COleDateTime codtLastUpdate) { m_codtLastUpdate = codtLastUpdate; }


	LONG			EpisodeID() { return m_lEpisodeID; }
	CString			Title() { return m_cszTitle; }
	CString			Description() { return m_cszDescription; }
    LONG			EnhMapID() { return m_lEnhMapID; }
	LONG			DisplayMask() { return m_lDisplayMask; }
	LONG			ThemeID() { return m_lThemeID; }
	LONG			RatingID() { return m_lRatingID; }
	LONG			Abbreviation() { return m_lAbbreviation; }
	COleDateTime	LastUpdate() { return m_codtLastUpdate; }
};

// Table: EpisodeT

#define  TBL_EpisodeT  _T("Episode")

//      Field:                          Name                            Type    Size

#define FLD_EpisodeT_EpisodeID            _T("E Episode ID")              // Auto-Count
#define FLD_EpisodeT_Title                _T("E Title")                   // Text    255
#define FLD_EpisodeT_Description          _T("E Description")             // Text    255
#define FLD_EpisodeT_EnhMapID			  _T("E Enhancement Mapping ID")
#define FLD_EpisodeT_DisplayMask          _T("E Display Mask")            // Long      4
#define FLD_EpisodeT_ThemeID			  _T("E Theme ID")				  // Long	   4
#define FLD_EpisodeT_RatingID             _T("E Rating ID")               // Long      4
#define FLD_EpisodeT_Abbreviation         _T("E Abbreviation")            // Long      4
#define FLD_EpisodeT_LastUpdate			  _T("E Last Update")             // Date      4


#endif // __EPISODET_H__
