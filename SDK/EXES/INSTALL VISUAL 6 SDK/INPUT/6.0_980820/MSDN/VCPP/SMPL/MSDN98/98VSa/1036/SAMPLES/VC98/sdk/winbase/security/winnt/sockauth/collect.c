/*++

Copyright 1996-1997 Microsoft Corporation

Module Name:

    collect.c

Abstract:

    Implements a very simple collection for mapping DWORD key values
	to a blob of data.

Revision History:

--*/

#include <windows.h>
#include <stdlib.h>
#include "collect.h"

typedef struct _node_tag  {
	DWORD dwKey;
	PVOID *pData;
	struct _node_tag *pNext;
} NODE, *PNODE;

static NODE Head = {(DWORD)-1, NULL, NULL};

BOOL GetEntry (DWORD dwKey, PVOID *ppData)
{
	PNODE pCurrent;

	pCurrent = Head.pNext;
	while (NULL != pCurrent) {
		if (dwKey == pCurrent->dwKey)  {
			*ppData = pCurrent->pData;
			return(TRUE);
		}
		pCurrent = pCurrent->pNext;
	}

	return(FALSE);
}

BOOL AddEntry (DWORD dwKey, PVOID pData)
{
	PNODE pTemp;

	pTemp = (PNODE) malloc (sizeof (NODE));
	if (NULL == pTemp)  {
		return(FALSE);
	}

	pTemp->dwKey = dwKey;
	pTemp->pData = pData;
	pTemp->pNext = Head.pNext;
	Head.pNext = pTemp;

	return(TRUE);
}	

BOOL DeleteEntry (DWORD dwKey, PVOID *ppData)
{
	PNODE pCurrent, pTemp;

	pTemp = &Head;
	pCurrent = Head.pNext;

	while (NULL != pCurrent) {
		if (dwKey == pCurrent->dwKey)  {
			pTemp->pNext = pCurrent->pNext;
			*ppData = pCurrent->pData;
			free (pCurrent);
			return(TRUE);
		}
		else {
			pTemp = pCurrent;
			pCurrent = pCurrent->pNext;
		}
	}

	return(FALSE);
}	
