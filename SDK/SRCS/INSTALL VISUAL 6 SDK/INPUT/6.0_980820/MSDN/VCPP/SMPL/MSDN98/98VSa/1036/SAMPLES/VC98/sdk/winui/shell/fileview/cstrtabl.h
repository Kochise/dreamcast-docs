//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright  1994-1996  Microsoft Corporation.  All Rights Reserved.
//
//	PROGRAM:CSTRTABL.H	
//
//	PURPOSE: Class and structure definitions for the CStringTable class
//   that helps to manage and retrieve strings from stringtables. 
//
//	PLATFORMS:	Windows 95
//
//	SPECIAL INSTRUCTIONS: N/A
//
#ifndef _CSTRTABL_H_
#define _CSTRTABL_H_


/*
 * CStringTable providing string table management.  Provides
 * simple [] array lookup using a stringtable ID to obtain
 * string pointers.
 */

class CStringTable
    {
    protected:
        HINSTANCE       m_hInst;
        UINT            m_idsMin;
        UINT            m_idsMax;
        USHORT          m_cStrings;
        LPSTR           m_pszStrings;
        LPSTR          *m_ppszTable;

    public:
        CStringTable(HINSTANCE);
        ~CStringTable(void);

        BOOL FInit(UINT, UINT, UINT);

        //Function to resolve an ID into a string pointer.
        const LPSTR operator [](const UINT) const;
    };

typedef CStringTable * PCStringTable;


#endif //_CSTRTABL_H_
