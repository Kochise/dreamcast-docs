/*
 * CSTRTABL.CPP
 * Sample Code Class Libraries
 *
 * Implementation of a string table handler.  The CStringTable
 * class hides details of storage from the user.  The strings might
 * be cached, or they might be loaded as necessary.  In either case,
 * we must know the number of strings so we know whether or not to
 * reload strings.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include <windows.h>
#include <malloc.h>
#include "classlib.h"



/*
 * CStringTable::CStringTable
 * CStringTable::~CStringTable
 *
 * Constructor Parameters:
 *  hInst           HANDLE to the application instance from which we
 *                  load strings.
 */

CStringTable::CStringTable(HINSTANCE hInst)
    {
    m_hInst=hInst;
    m_pszStrings=NULL;
    m_ppszTable=NULL;
    return;
    }


CStringTable::~CStringTable(void)
    {
    if (NULL!=m_pszStrings)
        free(m_pszStrings);

    if (NULL!=m_ppszTable)
        free(m_ppszTable);

    return;
    }







/*
 * CStringTable::Init
 *
 * Purpose:
 *  Initialization function for a StringTable that is prone to
 *  failure.  If this fails then the caller is responsible for
 *  guaranteeing that the destructor is called quickly.
 *
 * Parameters:
 *  idsMin          UINT first identifier in the stringtable
 *  idsMax          UINT last identifier in the stringtable.
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful, FALSE
 *                  otherwise.
 */


BOOL CStringTable::Init(UINT idsMin, UINT idsMax)
    {
    UINT        i;
    UINT        cch;
    UINT        cchUsed=0;
    LPTSTR      psz;

    m_idsMin=idsMin;
    m_idsMax=idsMax;
    m_cStrings=(idsMax-idsMin+1);


    //Allocate space for the pointer table.
    m_ppszTable=(LPTSTR *)malloc(sizeof(LPTSTR)*m_cStrings);

    if (NULL==m_ppszTable)
        return FALSE;


    //Allocate enough memory for cStrings of CCHSTRINGMAX.
    m_pszStrings=(LPTSTR)malloc(m_cStrings * CCHSTRINGMAX * sizeof(TCHAR));

    if (NULL==m_pszStrings)
        {
        free(m_ppszTable);
        m_ppszTable=NULL;
        return FALSE;
        }


    /*
     * Load the strings:  we load each string in turn into psz,
     * store the string pointer into the table and increment psz
     * to the next positions.
     */

    psz=m_pszStrings;

    for (i=idsMin; i <= idsMax; i++)
        {
        m_ppszTable[i-idsMin]=psz;
        cch=LoadString(m_hInst, i, psz, CCHSTRINGMAX-1);

        //Account for a null terminator
        psz+=cch+1;
        cchUsed+=cch;
        }

    return TRUE;
    }






/*
 * CStringTable::operator[]
 *
 * Purpose:
 *  Returns a pointer to the requested string in the stringtable or
 *  NULL if the specified string does not exist.
 */

const LPTSTR CStringTable::operator[](const UINT uID) const
    {
    if (uID < m_idsMin || uID > m_idsMax)
        return NULL;

    return (const LPTSTR)m_ppszTable[uID-m_idsMin];
    }
