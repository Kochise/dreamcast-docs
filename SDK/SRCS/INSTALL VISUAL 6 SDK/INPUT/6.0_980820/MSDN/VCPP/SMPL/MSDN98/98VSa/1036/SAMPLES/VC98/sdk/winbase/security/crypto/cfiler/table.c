
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1996-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

// TABLE.C

#include "cfiler.h"
#include <malloc.h>

/******************************************************************\
* CheckHeap()
*
* input: 
*
* message - buffer containing information to display on the
* debug window
*
* purpose:
*
* Calls _heapchk and outputs a formatted message onto the
* debug window.
\******************************************************************/

VOID CheckHeap(LPTSTR message) {
	INT rv = _heapchk();

	if (rv == _HEAPBADBEGIN) {
		ErrorMsg(message);
		ErrorMsg(TEXT("Initial header information is bad or cannot be found."));
		return;
	}
	else if (rv == _HEAPBADNODE) {
		ErrorMsg(message);
		ErrorMsg(TEXT("Bad node has been found or heap is damaged."));
		return;
	}
	else if (rv == _HEAPBADPTR) {
		ErrorMsg(message);
		ErrorMsg(TEXT("Pointer into heap is not valid."));
		return;
	}
	else if (rv == _HEAPEMPTY) {
		ErrorMsg(message);
		ErrorMsg(TEXT("Heap has not been initialized."));
		return;
	}
	else if (rv == _HEAPOK) {
		ErrorMsg(message);
		ErrorMsg(TEXT("Heap appears to be consistent."));
		return;
	}
	else {
		ErrorMsg(message);
		ErrorMsg(TEXT("_heapcheck did not return a valid value."));
	}
	return;
}

/******************************************************************\
* GetSize()
*
* in parameters:
* pTable - pointer to string table
*
* returns
* number of elements of pTable
* -1 if error
\******************************************************************/

INT GetSize(TABLE pTable) {
	if (!pTable) {
		ErrorMsg(TEXT("GetSize: pTable is NULL."));
		return -1;
	}
	
	return pTable->iNumElems;
}

/******************************************************************\
* TableNew()
*
* Returns a new string table with no elements or NULL
* if unsuccessful
\******************************************************************/

TABLE TableNew(VOID) {
	TABLE pTable;

	pTable = malloc(sizeof(*pTable) + 100);
	
	if (!pTable) {
		ErrorMsg(TEXT("TableNew: malloc failed."));
		return FALSE;
	}
	
	pTable->iNumElems = 0;
	pTable->pCurrentFiles = NULL;
	
	return pTable;
}

/******************************************************************\
* TableFree()
*
* input: pTable - pointer to a table
*
* purpose:
* 
* Frees the string table pointed to by pTable.
*
* return value:
*
* TRUE if successful
* FALSE if unsuccessful
\******************************************************************/

BOOL TableFree(TABLE pTable) {
	ELEM *p, *q;

    if (!pTable) {
    	ErrorMsg(TEXT("TableFree: pTable is NULL."));
    	return FALSE;
    }
    
    for (p = pTable->pCurrentFiles; p; p = q) {
		q = p->next;
		free(p->hidden);
		free(p->displayed);
		free(p);
		p = NULL;
	}

	free(pTable);

	pTable = NULL;

	return TRUE;
}

/******************************************************************\
* TableFind()
*
* input: pTable - pointer to a table
* szFindString - string in question.
*
* purpose:
* Searches for szFindString in table pTable.
*
* return value:
*
* TRUE if szFindString is in table
* FALSE if otherwise
\******************************************************************/

BOOL TableFind(TABLE pTable, LPTSTR szFindString) {
	ELEM *p, *q;

    if (!pTable) {
    	ErrorMsg(TEXT("TableFree: pTable is NULL."));
    	return FALSE;
    }
    
    for (p = pTable->pCurrentFiles; p; p = q) {
		q = p->next;
		if (!CFilerlstrcmp(p->displayed, szFindString)) {
			return TRUE;
		}
	}

	return FALSE;
}

/******************************************************************\
* TableAdd()
*
* input:
*
* pTable - pointer to a string table
*
* szHidden, szDisplayed: pair of strings to insert into table
*
*
* purpose:
*
* Inserts a string pair at the end of the string table pointed
* to by pTable.
\******************************************************************/

BOOL TableAdd(TABLE pTable, TCHAR *szHidden, LPTSTR szDisplayed) {
	return TableInsert(pTable, szHidden, szDisplayed, pTable->iNumElems);
}

/******************************************************************\
* TableInsert()
*
* input:
*
* pTable - pointer to a string table
* szHidden, szDisplayed : string pair to be inserted
* i - position to insert the string pair.
*
* purpose:
* inserts a string pair into the table pointed to by pTable
* at position indicated by i.
\******************************************************************/

BOOL TableInsert(TABLE pTable, LPTSTR szHidden, LPTSTR szDisplayed, INT i) {
	ELEM *new, *p = NULL, *q = NULL;
	INT j;

	if (!pTable) {
		ErrorMsg(TEXT("TableInsert: pTable is NULL."));
		return FALSE;
	}
	
	new = malloc(sizeof(*new) + 2);

	new->hidden = malloc(3 + sizeof(*szHidden) * lstrlen(szHidden));
	new->displayed = malloc(3 + sizeof(*szDisplayed) * lstrlen(szDisplayed));
	new->next = NULL;

	lstrcpy(new->hidden, szHidden);
	lstrcpy(new->displayed, szDisplayed);
		
	if (!pTable->pCurrentFiles) {
		pTable->pCurrentFiles = new;
		pTable->iNumElems++;
		return TRUE;
	}
	
	if (!i) {
		ELEM *t;
		t = pTable->pCurrentFiles;
		pTable->pCurrentFiles = new;
		new->next = t;
		pTable->iNumElems++;
		return TRUE;
	}	

	for (j = 0, p = pTable->pCurrentFiles; j < i; j++, p = p->next)
		q = p;
		
	q->next = new;
	new->next = p;

	pTable->iNumElems++;
	
	return TRUE;
}

/******************************************************************\
* TableRemove()
*
* input: 
* pTable - pointer to a string table
* i - index of element to be removed
*
* purpose: 
* Removes the element at position i in the string table 
* pointed to by pTable.
*
* Return values:
* TRUE if successful
* FALSE if unsuccessful
\******************************************************************/

BOOL TableRemove(TABLE pTable, INT i) {
	INT j;
	ELEM *p, *q;
		
	if (!pTable) {
		ErrorMsg(TEXT("TableRemove: pTable is NULL."));
		return FALSE;
	}
	
	if (!pTable->pCurrentFiles) {
		pTable->iNumElems = 0;
		return TRUE;
	}

	if (!i) {
		ELEM *t = pTable->pCurrentFiles->next;
		p = pTable->pCurrentFiles;
		free(p->hidden);
		free(p->displayed);
		free(p);
		pTable->pCurrentFiles = t;
		pTable->iNumElems--;
		return TRUE;
	}

	for (j = 0, p = pTable->pCurrentFiles; j < i; j++, p = p->next) {
		q = p;
	}
	
	q->next = p->next;
	free(p->hidden);
	free(p->displayed);
	free(p);

	pTable->iNumElems--;

	return TRUE;
}

/******************************************************************\
* TableSort()
*
* input:
* pTable - pointer to a string table
* compare - pointer to a compare function to be used in the
* sort process
*
* Purpose: 
* sorts the elements of the string table pointed to by pTable
* on the displayed field.
*
* Return values:
* TRUE if successful
* FALSE if unsuccessful
\******************************************************************/

BOOL TableSort(TABLE pTable, INT compare(LPCTSTR , LPCTSTR)) {
	ELEM *p, *q, *min, *t;
	INT i, j;

	if (!pTable) {
		ErrorMsg(TEXT("TableSort: pTable is NULL."));
		return FALSE;
	}
	
	t = malloc(sizeof(*t));
	
	for (i = 0, p = pTable->pCurrentFiles; p && i < pTable->iNumElems - 1; i++, p = p->next) {
		min = p;
		for (q = p->next, j = 0; q && j < pTable->iNumElems; j++, q = q->next) {
			if (!q->displayed || !p->displayed) {
				ErrorMsg(TEXT("TableSort: parameters to compare are null."));
				return FALSE;
			}
			if (compare(q->displayed, min->displayed) < 0) min = q;
		}
		t->displayed = min->displayed;
		t->hidden = min->hidden; 
		min->displayed = p->displayed; 
		min->hidden = p->hidden;
		p->displayed = t->displayed;
		p->hidden = t->hidden;
	}

	free(t);

	return TRUE;
}

/******************************************************************\
* TableSend()
*
* input:
* pTable - pointer to a string table
* mybox - handle to the listbox to which LB_ADDSTRING
* messages are to be sent
*
* Purpose:
* Sends the displayed members of the string table pointed to by
* pTable to the listbox whose handle is mybox
* by sending LB_ADDSTRING messages to the listbox for each
* element of the table.
*
* Return values:
* TRUE if successful
* FALSE if unsuccessful
\******************************************************************/

BOOL TableSend(TABLE pTable, HWND mybox) {
	int j;
	ELEM *p;
	LRESULT result;

	if (!pTable) {
		ErrorMsg(TEXT("TableSend: pTable is NULL."));
		return FALSE;
	}
	
	for (j = 0, p = pTable->pCurrentFiles; j < pTable->iNumElems; j++, p = p->next) {
		result = SendMessage(mybox, LB_ADDSTRING, (WPARAM)0, (LPARAM)p->displayed);
		
		if (result == LB_ERR) {
			ErrorMsg(TEXT("TableSend: LB_ADDSTRING failed."));
			return FALSE;
		}
	}
	
	return TRUE;
}

/******************************************************************\
* TableGetHidden()
*
* input:
* pTable - pointer to a string table
* i - index of hidden element to retrieve
* rv - (out parameter): buffer to store the hidden string
*
* Purpose:
* Retrieves the hidden memeber of the table stored at position i
* in the string table pointed to by pTable.
*
* Returns:
* TRUE if successful
* FALSE if unsuccessful
\******************************************************************/

BOOL TableGetHidden(TABLE pTable, INT i, LPTSTR rv) {
	INT j;
	ELEM *p, *q;

	if (!pTable) {
		ErrorMsg(TEXT("TableGetHidden: pTable is NULL."));
		return FALSE;
	}
	
	q = pTable->pCurrentFiles;
	
	if (q) {
		for (p = pTable->pCurrentFiles, j = 0; j <= i; j++, p = p->next)
			q = p;
	}
	else {
		ErrorMsg(TEXT("TableGetHidden: pTable->pCurrentFiles is NULL."));
		lstrcpy(rv, TEXT("error"));
		return FALSE;
	}

	if (q && q->hidden)
		lstrcpy(rv, q->hidden);

	return TRUE;
}

/******************************************************************\
* SimplifyFileName()
*
* input:
* szFileName - buffer of string to be "simplified"
* rv - (out parameter) - buffer where simplified string
* is to be stored
*
* purpose:
* strips the characters [, ], >, |, and ; from szFileName and
* stores the result in rv.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\******************************************************************/

BOOL SimplifyFileName(LPTSTR szFileName, LPTSTR rv) {
	INT i, j;

	for (i = 0, j = 0; szFileName[i]; ) {
		if (szFileName[i] == TEXT('[') || 
			szFileName[i] == TEXT(']') || 
			szFileName[i] == TEXT('|') || 
			szFileName[i] == TEXT('>') ||
			szFileName[i] == TEXT(';'))
			i++;
		else {
			rv[j] = szFileName[i];
			i++;
			j++;
		}
	}

	rv[j] = TEXT('\0');
	return TRUE;
}

/******************************************************************\
* ReplaceEscapeCharacters()
*
* input:
* szFileName - input buffer
* rv - (out parameter) - output buffer
*
* purpose:
* replaces '&' characters in szFileName with '\&' and stores
* the result in rv.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\******************************************************************/

BOOL ReplaceEscapeCharacters(LPTSTR szFileName, LPTSTR rv) {
	INT i, j;

	for (i = 0, j = 0; szFileName[i]; ) {
		if (szFileName[i] == TEXT('&')) {
			rv[j] = TEXT('&');
			rv[j + 1] = TEXT('&');
			i++;
			j += 2;
		}
		else {
			rv[j] = szFileName[i];
			i++;
			j++;
		}
	}

	rv[j] = TEXT('\0');
	return TRUE;
}

/******************************************************************\
* CFilerlstrcmp: Case-insensitive comparison of the strings s and t.
* foo and |foo are the same.
* [foo] and |[foo] are the same.
* [foo] and foo are not the same.
\******************************************************************/

INT CFilerlstrcmp(LPCTSTR s, LPCTSTR t)
{
	int i = 0, j = 0;

	if (s[0] == TEXT('|') || s[0] == TEXT('>') || s[0] == TEXT(';'))
		i++;
	
	if (t[0] == TEXT('|') || t[0] == TEXT('>') || t[0] == TEXT(';'))
		j++;
		
	for ( ; toupper(s[i]) == toupper(t[j]); i++, j++)
		if (toupper(s[i]) == TEXT('\0'))
			return 0;

	return toupper(s[i]) - toupper(t[j]);
}
