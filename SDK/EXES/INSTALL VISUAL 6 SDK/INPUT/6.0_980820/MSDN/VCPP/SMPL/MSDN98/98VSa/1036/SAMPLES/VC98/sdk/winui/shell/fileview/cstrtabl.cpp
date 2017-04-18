//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright  1994-1996  Microsoft Corporation.  All Rights Reserved.
//
//	PROGRAM:		CSTRTABL.CPP
//
//	PURPOSE:   Implementation of a string table handler.  The CStringTable
// class hides details of storage from the user.  The strings might
// be cached, or they might be loaded as necessary.  In either case,
// we must know the number of strings so we know whether or not to
// reload strings.
//
//	PLATFORMS:	Windows 95
//
//	FUNCTIONS:	
//   
//
//	SPECIAL INSTRUCTIONS: N/A
//
#include "fileview.h"

//
//   FUNCTION: CStringTable::CStringTable	
//
//   PURPOSE: 	Constructor
//
//   PARAMETERS: 
//	     hInst           HANDLE to the module instance from which we  load strings.
// 
CStringTable::CStringTable(HINSTANCE hInst)
    {
    m_hInst=hInst;
    m_pszStrings=NULL;
    m_ppszTable=NULL;
    return;
    }

//
//   FUNCTION:  CStringTable::~CStringTable	
//
//   PURPOSE: 	Destructor
//
CStringTable::~CStringTable(void)
    {
    if (NULL!=m_pszStrings)
        free(m_pszStrings);

    if (NULL!=m_ppszTable)
        free(m_ppszTable);

    return;
    }
//
//   FUNCTION: CStringTable::FInit	
//
//   PURPOSE:    Initialization function for a StringTable that is prone to
//  failure.  If this fails then the caller is responsible for
//  guaranteeing that the destructor is called quickly.
//
//   PARAMETERS: 
//   idsMin          UINT first identifier in the stringtable
//  idsMax          UINT last identifier in the stringtable.
//  cchMax          UINT with the maximum string length allowed.
//
//   RETURN VALUE:
// 	   BOOL            TRUE if the function is successful,  FALSE otherwise.
//
BOOL CStringTable::FInit(UINT idsMin, UINT idsMax, UINT cchMax)
    {
    UINT        i;
    UINT        cch;
    UINT        cchUsed=0;
    LPSTR       psz;

    m_idsMin=idsMin;
    m_idsMax=idsMax;
    m_cStrings=(idsMax-idsMin+1);

    //Allocate space for the pointer table.
    m_ppszTable=(LPSTR *)malloc(sizeof(LPSTR)*m_cStrings);

    if (NULL==m_ppszTable)
        return FALSE;
     // Allocate enough memory for cStrings*cchMax characters.  80
     // characters is the maximum string length we allow.  This
     // will result in some unused memory, but a few K is not
     // worth quibbling over.
    m_pszStrings=(LPSTR)malloc(m_cStrings * cchMax);

    if (NULL==m_pszStrings)
        {
        free(m_ppszTable);
        m_ppszTable=NULL;
        return FALSE;
        }
     // Load the strings:  we load each string in turn into psz,
     // store the string pointer into the table and increment psz
     // to the next positions.
    psz=m_pszStrings;

    for (i=idsMin; i <= idsMax; i++)
        {
        m_ppszTable[i-idsMin]=psz;
        cch=LoadString(m_hInst, i, psz, 255);

        //Account for a null terminator with +1
        psz    +=cch+1;
        cchUsed+=cch;
        }

    return TRUE;
    }
//
//   FUNCTION: CStringTable::operator[]	
//
//   PURPOSE:  Returns a pointer to the requested string in the stringtable
//  or NULL if the specified string does not exist.
// 
const LPSTR CStringTable::operator[](const UINT uID) const
    {
    if (uID < m_idsMin || uID > m_idsMax)
        return NULL;

    return (const LPSTR)m_ppszTable[uID-m_idsMin];
    }
