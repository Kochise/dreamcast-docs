/*
 *  net.c
 *  
 *  Purpose:
 *      net functions
 *  
 *  Owner:
 *      MikeSart
 */
#define UNICODE 1

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <string.h>
#include <time.h>
#include <lm.h>
#include "netwatch.h"
#include "rcids.h"

ASSERTDATA

// From lmcons.h:
//  NNLEN: max share name
//  UNLEN: max user name
//  MAXCOMMENTSZ: max comment length
//  PATHLEN: max path

// From datetime.c
TCHAR	*PutTime(time_t tm_t, TCHAR *szStr, UINT cch);
TCHAR	*PutDate(time_t tm_t, TCHAR *szStr, UINT cch);
TCHAR	*PutCounterTime(DWORD dw, TCHAR *szStr, UINT cch);

/*
 *	Useful macros
 */
// Should we consider szShare hidden?
#define FIsShareHidden(_szShare) \
	((_szShare)[lstrlen(_szShare) - 1] == TEXT('$'))
// Is the lParam in the TV_ITEM a pointer to TVDATA or just a type?
#define FIsLParamTVData(_lp) \
	(((_lp) + 1) > 1)

/*
 *	Globules
 */
SCONST TCHAR	szFmtNum[]      = TEXT("%lu");

/*
 *	Typedefs
 */
typedef struct tagTVDATA
{
	DWORD	dwType;
} TVDATA;

typedef struct tagTVDATASHARE
{
	DWORD	dwType;					// TYPE_SHARE, TYPE_USER, or TYPE_FILE
	DWORD	dwShareType;			// STYPE_IPC, etc.
	TCHAR	szShareName[NNLEN + 1];	// e$, etc.

	TCHAR	szServerName[UNCLEN + 1];
} TVDATASHARE;

typedef struct tagTVDATAUSER
{
	DWORD	dwType;					// TYPE_SHARE, TYPE_USER, or TYPE_FILE
	TCHAR	szUserName[UNLEN + 1];	// BillG, etc.
	TCHAR	szNetName[UNCLEN + 1];	// \\BILLG1, etc.

	TVDATASHARE	*pTVDataShare;		// Parent data
} TVDATAUSER;

typedef struct tagTVDATAFILE
{
	DWORD	dwType;					// TYPE_SHARE, TYPE_USER, or TYPE_FILE
	DWORD	dwFileId;				// fi3_id

	TVDATAUSER	*pTVDataUser;		// Parent data
} TVDATAFILE;

/*
 *	Treeview nonsense
 */

/*
 *	TreeView_FindExactString
 *
 *	Purpose:
 *		Find a szText starting from hItemStart
 *
 *	Arguments:
 *		hParent, hItemStart, szText
 *
 *	Returns:
 *		hItem or NULL
 */
HTREEITEM
TreeView_FindExactString(HWND hwndTV, HTREEITEM hParent, HTREEITEM hItemStart,
	TCHAR *szText)
{
	TCHAR	szT[cchTVSzMax];

	// Start looking one node after us
	hItemStart = hItemStart ? TreeView_GetNextSibling(hwndTV, hItemStart) :
		TreeView_GetChild(hwndTV, hParent);

	// Loop through looking for that baby
	while(hItemStart)
	{
		// Get the text
		if(FTreeView_GetString(hwndTV, hItemStart, szT, cchTVSzMax))
		{
			UINT nRet = lstrcmp(szText, szT);

			// Strings should be in the treeview control like:
			//   aaaa$
			//   bbbb$
			//   zzzz$
			//   bbbb
			//   ffff

			// So, if the strings match, return em
			// Else szText is larger than szT and we're past the hidden shares
			// so the item shouldn't be here
			if(!nRet)
				return hItemStart;
			else if((nRet < 0) && !FIsShareHidden(szT))
				return NULL;
		}

		hItemStart = TreeView_GetNextSibling(hwndTV, hItemStart);
	}

	return hItemStart;
}

/*
 *	FTreeView_DeleteRange
 *
 *	Purpose: Delete hItemStart+1 to hItemEnd-1
 *		hItemStart
 *		hItemStart+1
 *		...
 *		HItemEnd-1
 *		HItemEnd
 *
 *	Arguments:
 *		hwndTV, hItemStart, hItemEnd
 *
 *	Returns:
 *		TRUE - success, FALSE - failure
 */
BOOL
FTreeView_DeleteRange(HWND hwndTV, HTREEITEM hParent, HTREEITEM hItemStart,
	HTREEITEM hItemEnd)
{
	// If NULL, we want the first item, else we want hItemStart + 1
	hItemStart = hItemStart ? TreeView_GetNextSibling(hwndTV, hItemStart) :
		TreeView_GetChild(hwndTV, hParent);

	while(hItemStart && (hItemStart != hItemEnd))
	{
		HTREEITEM	hItemT;

		hItemT = TreeView_GetNextSibling(hwndTV, hItemStart);
		TreeView_DeleteItem(hwndTV, hItemStart);
		hItemStart = hItemT;
	}

	return TRUE;
}

/*
 *	TreeView_TVReplacelParam
 *
 *	Purpose:
 *		Replace an lparam and free any associated memory
 *
 *	Arguments:
 *		hItem to replace and lParamNew
 *
 *	Returns:
 *		TRUE - success, FALSE - failed
 */
BOOL
TreeView_TVReplacelParam(HWND hwndTV, HTREEITEM hItem, LPARAM lParamNew)
{
	TV_ITEM		tvItem;
	LPARAM		lParamOld;

	tvItem.mask = TVIF_PARAM;
	tvItem.hItem = hItem;
	TreeView_GetItem(hwndTV, &tvItem);
	lParamOld = tvItem.lParam;

	tvItem.lParam = lParamNew;
	TreeView_SetItem(hwndTV, &tvItem);

	if(FIsLParamTVData(lParamOld))
		GlobalFreePtr((TVDATA *)lParamOld);
	return TRUE;
}

/*
 *	TreeView_TVDataInsert
 *
 *	Purpose:
 *		Try to be smart when inserting TV items
 *
 *	Arguments:
 *		ptvis to insert
 *
 *	Returns:
 *		hItem of newly inserted item
 */
HTREEITEM
TreeView_TVDataInsert(HWND hwndTV, TV_INSERTSTRUCT *ptvis)
{
	HTREEITEM	hItem;

	// See if this item exists anywhere already
	hItem = TreeView_FindExactString(hwndTV, ptvis->hParent,
		ptvis->hInsertAfter, ptvis->item.pszText);

	// It does: del everything from the last inserted node to right before us
	if(hItem)
	{
		OutputDbgStr("TreeView_TVDataInsert found '%ls'", ptvis->item.pszText);
		FTreeView_DeleteRange(hwndTV, ptvis->hParent, ptvis->hInsertAfter,
			hItem);
		TreeView_TVReplacelParam(hwndTV, hItem, ptvis->item.lParam);
		ptvis->hInsertAfter = hItem;
		return hItem;
	}

	// ok, it's a new string, insert it
	// If this is the first one, make sure it's the first one
	OutputDbgStr("TreeView_TVDataInsert inserting '%ls'", ptvis->item.pszText);
	if(!ptvis->hInsertAfter)
		ptvis->hInsertAfter = TVI_FIRST;
	hItem = TreeView_InsertItem(hwndTV, ptvis);
	// Store away the last item we've inserted
	ptvis->hInsertAfter = hItem;

	return hItem;
}

/*
 *	TreeView_FreeItemData
 *
 *	Purpose:
 *		Free our alloc'd lParam (called via DELETEITEM)
 *
 *	Arguments:
 *		ptvItem of item being deleted
 *
 *	Returns:
 *		nada
 */
VOID
TreeView_FreeItemData(TV_ITEM *ptvItem)
{
	if(FIsLParamTVData(ptvItem->lParam))
	{
		OutputDbgStr("TreeView_FreeItemData '%d'",
			((TVDATA *)ptvItem->lParam)->dwType);
		GlobalFreePtr((TVDATA *)ptvItem->lParam);
		ptvItem->lParam = 0;
	}
}

/*
 *	TreeView_GetSelectedItemData
 *
 *	Purpose:
 *		Get type and lParam of selected item
 *
 *	Arguments:
 *		pdwType
 *
 *	Returns:
 *		lParam of selected item
 */
LPARAM
TreeView_GetSelectedItemData(HWND hwndTV, DWORD *pdwType)
{
	HTREEITEM	hItem;
	TV_ITEM		tvItem;

	*pdwType = TYPE_ERROR;
	if(!(hItem = TreeView_GetSelection(hwndTV)))
		return 0;

	tvItem.mask = TVIF_PARAM;
	tvItem.hItem = hItem;
	tvItem.lParam = TYPE_ERROR;
	TreeView_GetItem(hwndTV, &tvItem);

	*pdwType = FIsLParamTVData(tvItem.lParam) ?
		((TVDATA *)tvItem.lParam)->dwType : tvItem.lParam;
	return tvItem.lParam;
}

/*
 *	Sorting routines
 */

/*
 *	CompareShareNames
 *
 *	Purpose:
 *		compare two share names being 'smart' about hidden shares
 *
 *	Arguments:
 *		share1, share2
 *
 *	Returns:
 *		-1, 0, 1
 */
int
CompareShareNames(TCHAR *szShareName1, TCHAR *szShareName2)
{
	BOOL	fShare1Hidden;
	BOOL	fShare2Hidden;

	fShare1Hidden = FIsShareHidden(szShareName1);
	fShare2Hidden = FIsShareHidden(szShareName2);

	// If they're the same type, just string compare them
	if(fShare1Hidden == fShare2Hidden)
		return lstrcmpi(szShareName1, szShareName2);

	// Otherwise we want hidden shares to go first
	return fShare1Hidden ? -1 : 1;
}

/*
 *	QSortCallbacks
 *
 *	Purpose:
 *		called from qsort to figure what goes where
 *
 *	Arguments:
 *		elements to compare
 *
 *	Returns:
 *		< 0: elem1 less than elem2
 *		= 0: elem1 equivalent to elem2
 *		> 0: elem1 greater than elem2
 */
int __cdecl
CompareShareNamesQSortCallback(const void *elem1, const void *elem2)
{
	return CompareShareNames(((SHARE_INFO_2 *)elem1)->shi2_netname,
		((SHARE_INFO_2 *)elem2)->shi2_netname);
}

int __cdecl
CompareUserNamesQSortCallback(const void *elem1, const void *elem2)
{
	return lstrcmp(((CONNECTION_INFO_1 *)elem1)->coni1_username,
		((CONNECTION_INFO_1 *)elem2)->coni1_username);
}

int __cdecl
CompareFileNamesQSortCallback(const void *elem1, const void *elem2)
{
	return lstrcmp(((FILE_INFO_3 *)elem1)->fi3_pathname,
		((FILE_INFO_3 *)elem2)->fi3_pathname);
}

/*
 *	Enumeration routines
 */

/*
 *	FilesEnum
 *
 *	Purpose:
 *		Enumerate the open files on a sharepath, username, and server
 *
 *	Arguments:
 *		all kinds of stuff
 *
 *	Returns:
 *		nas
 */
NET_API_STATUS
FilesEnum(HWND hwndTV, HTREEITEM hParent, LPTSTR szServerName, TCHAR *username,
	TCHAR *sharepath, TVDATAUSER *pTVDataUser)
{
	NET_API_STATUS	nas;
	TV_INSERTSTRUCT	tvis;
	FILE_INFO_3		*pfi3;
	FILE_INFO_3		*fi3 = NULL;
	DWORD			dwentriesread;
	DWORD			dwtotalentries;
	TCHAR			*psharepathend;

	// Some stuff doesn't change
	tvis.hInsertAfter = NULL;
	tvis.hParent = hParent;
	tvis.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;

	// Reasoning: if you are passed c:\ as a sharepath, sometimes c: is opened
	// as execute. But since we would be qualifying paths on c:\, it won't show
	// c: as being open.  So - remove the last \ if it's there.
	if(sharepath && sharepath[0])
	{
		psharepathend = sharepath + lstrlen(sharepath) - 1;
		if(*psharepathend == TEXT('\\'))
			*psharepathend = '\0';
	}

	nas = NetFileEnum(szServerName, sharepath, username, 3,
		(LPBYTE *)&fi3, MAX_PREFERRED_LENGTH, 
		&dwentriesread, &dwtotalentries, NULL);
	if(nas || !dwentriesread)
		goto err;

	qsort(fi3, dwentriesread, sizeof(fi3[0]), CompareFileNamesQSortCallback);
	for(pfi3 = fi3; dwentriesread; pfi3++, dwentriesread--)
	{
		TVDATAFILE	*pTVDataFile;
		UINT		nBitmap = BMP_READ;

		// And our bmp is...
		if((pfi3->fi3_permissions & PERM_FILE_WRITE) ||
			(pfi3->fi3_permissions & PERM_FILE_CREATE))
				nBitmap = BMP_WRITE;

		// Things to remember for properties, delete, etc.
		if(pTVDataFile = (TVDATAFILE *)GlobalAllocPtr(GHND, sizeof(TVDATAFILE)))
		{
			pTVDataFile->dwType = TYPE_FILE;
			pTVDataFile->dwFileId = pfi3->fi3_id;
			pTVDataFile->pTVDataUser = pTVDataUser;
		}

		// Insert that baby
		tvis.item.lParam = (LPARAM)pTVDataFile;
		tvis.item.pszText = pfi3->fi3_pathname;
		tvis.item.iImage = tvis.item.iSelectedImage = nBitmap;
		TreeView_TVDataInsert(hwndTV, &tvis);
	}

err:
	// Whack any stragglers hanging at the end
	FTreeView_DeleteRange(hwndTV, hParent, tvis.hInsertAfter, NULL);

	NetApiBufferFree(fi3);
	if(nas)
		AddErrorStringToTV(hwndTV, hParent, IDS_ERRENUMFILES, nas);
	return nas;
}

/*
 *	UsersEnum
 *
 *	Purpose:
 *		Enumerate the users on a sharepath and server
 *
 *	Arguments:
 *		lots o garbage
 *
 *	Returns:
 *		nas
 */
NET_API_STATUS
UsersEnum(HWND hwndTV, HTREEITEM hParent, LPTSTR szServerName, TCHAR *sharename,
	TCHAR *sharepath, TVDATASHARE *pTVDataShare)
{
	NET_API_STATUS		nas;
	TV_INSERTSTRUCT		tvis;
	HTREEITEM			hItem;
	CONNECTION_INFO_1	*pci1;
	CONNECTION_INFO_1	*ci1 = NULL;
	DWORD				dwentriesread;
	DWORD				dwtotalentries;
	static TCHAR		szFmtUser[cchSzMax + 1];
	TCHAR				szUserT[NNLEN + UNLEN + cchSzMax + 1];

	// Some stuff doesn't change
	tvis.hInsertAfter = NULL;
	tvis.hParent = hParent;
	tvis.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;

	if(!szFmtUser[0])
		lstrcpy(szFmtUser, szFromIDS1(IDS_FMTUSER));

	nas = NetConnectionEnum(szServerName, sharename, 1, (LPBYTE *)&ci1,
		MAX_PREFERRED_LENGTH, &dwentriesread, &dwtotalentries, NULL);
	if(nas || !dwentriesread)
		goto err;

	qsort(ci1, dwentriesread, sizeof(ci1[0]), CompareUserNamesQSortCallback);
	for(pci1 = ci1; dwentriesread; pci1++, dwentriesread--)
	{
		TCHAR		*netname;
		TCHAR		*username;
		TVDATAUSER	*pTVDataUser;

		username = pci1->coni1_username;
		netname = pci1->coni1_netname;
		if(!username || !username[0])
			username = szNil;
		else
			CharLower(username);
		if(!netname || !netname[0])
			netname = szNil;
		else
			CharUpper(netname);

		if(lstrlen(netname) > CNLEN)
			netname[CNLEN] = 0;
		if(lstrlen(username) > UNLEN)
			username[UNLEN] = 0;

		wsprintf(szUserT, szFmtUser, username, netname);

		// Things to remember for properties, delete, etc.
		if(pTVDataUser = (TVDATAUSER *)GlobalAllocPtr(GHND, sizeof(TVDATAUSER)))
		{
			pTVDataUser->dwType = TYPE_USER;
			lstrcpy(pTVDataUser->szUserName, username);
			pTVDataUser->szNetName[0] = pTVDataUser->szNetName[1] = '\\';
			lstrcpy(&pTVDataUser->szNetName[2], netname);
			pTVDataUser->pTVDataShare = pTVDataShare;
		}

		tvis.item.lParam = (LPARAM)pTVDataUser;
		tvis.item.pszText = szUserT;
		tvis.item.iImage = tvis.item.iSelectedImage = BMP_USER;
		hItem = TreeView_TVDataInsert(hwndTV, &tvis);

		// If we haven't run into any errors and the user wants to see files
		if(pci1->coni1_num_opens &&
			unMenuFlags[IDM_SHOWFILES & 0xff] == MF_CHECKED && !nas)
		{
			// Enum the files
			nas = FilesEnum(hwndTV, hItem, szServerName, username,
				sharepath, pTVDataUser);
			// make sure we're expanded
			TreeView_Expand(hwndTV, hItem, TVE_EXPAND);
		}
		else
		{
			// Delete all our children
			FTreeView_DeleteRange(hwndTV, hItem, NULL, NULL);
		}
	}

	// reset any filesenum errors we may have encountered
	nas = 0;

err:
	// Whack any stragglers hanging at the end
	FTreeView_DeleteRange(hwndTV, hParent, tvis.hInsertAfter, NULL);

	NetApiBufferFree(ci1);
	if(nas)
		AddErrorStringToTV(hwndTV, hParent, IDS_ERRENUMUSERS, nas);
	return nas;
}

/*
 *	SharesEnum
 *
 *	Purpose:
 *		Enumerate the shares on a server
 *
 *	Arguments:
 *		server to enum
 *
 *	Returns:
 *		nas
 */
#define offsetof(s, m)  (size_t)&(((s *)0)->m)
#define shoffset(l, m)  (offsetof(SHARE_INFO_##l, m))
NET_API_STATUS
SharesEnum(HWND hwndTV, HTREEITEM hParent, LPTSTR szServerName, UINT *pcUsers,
	INT nLevel)
{
	NET_API_STATUS	nas;
	TV_INSERTSTRUCT	tvis;
	HTREEITEM		hItem;
	SHARE_INFO_2	*pshi2;
	UINT			cbStruct;
	SHARE_INFO_2	*shi2 = NULL;
	DWORD			dwentriesread;
	DWORD			dwtotalentries;
	SCONST TCHAR	szEndSep[] = TEXT(")");
	SCONST TCHAR	szBegSep[] = TEXT(" (");
	// +3 for the begsep and endsep
	TCHAR			szShareT[NNLEN + MAXCOMMENTSZ + 3 + 1];

	Assert(nLevel == 1 || nLevel == 2);
	// We assume the first three parts of these structs are the same. Make sure.
	// Using cbStruct here cause the compiler loses the entire line if I don't?
	Assert((cbStruct = shoffset(1, shi1_netname)) == shoffset(2, shi2_netname));
	Assert((cbStruct = shoffset(1, shi1_type)) == shoffset(2, shi2_type));
	Assert((cbStruct = shoffset(1, shi1_remark)) == shoffset(2, shi2_remark));

	cbStruct = nLevel == 2 ? sizeof(SHARE_INFO_2) : sizeof(SHARE_INFO_1);
	// WARNING: don't use the following members of shi2 without checking nLevel!
	//	shi2_permissions;
	//	shi2_max_uses;
	//	shi2_current_uses
	//	shi2_path;
	//	shi2_passwd;

	// Some stuff doesn't change
	tvis.hInsertAfter = NULL;
	tvis.hParent = hParent;
	tvis.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;

	nas = NetShareEnum(szServerName, nLevel, (LPBYTE *)&shi2,
		MAX_PREFERRED_LENGTH, &dwentriesread, &dwtotalentries, NULL);
	if(nas || !dwentriesread)
		goto err;

	// Sort the shares and then cruise through adding em all to the TV
	qsort(shi2, dwentriesread, cbStruct, CompareShareNamesQSortCallback);
	for(pshi2 = shi2; dwentriesread; ((LPBYTE)pshi2) += cbStruct, dwentriesread--)
	{
		TCHAR			*sharename;
		TCHAR			*shareremark;
		UINT			nCurrentUses;
		TVDATASHARE		*pTVDataShare;

		sharename = pshi2->shi2_netname;
		shareremark = pshi2->shi2_remark;
		nCurrentUses = (nLevel == 2) ? pshi2->shi2_current_uses : 0;

		if(!sharename)
			continue;
		if(!shareremark)
			shareremark = szNil;

		if(lstrlen(sharename) > NNLEN)
			sharename[NNLEN] = 0;
		if(lstrlen(shareremark) > MAXCOMMENTSZ)
			shareremark[MAXCOMMENTSZ] = 0;

		// skip hidden shares
		if((unMenuFlags[IDM_SHOWHIDDEN & 0xff] == MF_UNCHECKED) &&
			FIsShareHidden(sharename))
				continue;

		// Keep a running total
		*pcUsers += nCurrentUses;

		// If we have any users connected or the onlyshowinuse isn't checked
		if(nCurrentUses || (unMenuFlags[IDM_SHOWINUSE & 0xff] != MF_CHECKED))
		{
			int nBitmap = ((pshi2->shi2_type & 0xf) == STYPE_IPC) ?
				BMP_IPC : BMP_SHARE;

			// Copy over the share name and comment
			lstrcpy(szShareT, sharename);
			if(shareremark[0])
			{
				lstrcat(szShareT, szBegSep);
				lstrcat(szShareT, shareremark);
				lstrcat(szShareT, szEndSep);
			}

			// Things to remember for properties, delete, etc.
			if(pTVDataShare = (TVDATASHARE *)GlobalAllocPtr(GHND,
				sizeof(TVDATASHARE)))
			{
				pTVDataShare->dwType = TYPE_SHARE;
				pTVDataShare->dwShareType = pshi2->shi2_type;
				lstrcpy(pTVDataShare->szShareName, sharename);
				lstrcpy(pTVDataShare->szServerName, szServerName);
			}

			tvis.item.lParam = (LPARAM)pTVDataShare;
			tvis.item.pszText = szShareT;
			tvis.item.iImage = tvis.item.iSelectedImage = nBitmap;
			hItem = TreeView_TVDataInsert(hwndTV, &tvis);

			// If we previously got an error enuming users, don't waste our time
			// trying again.
			if(!nas && nCurrentUses)
			{
				Assert(nLevel == 2);
				nas = UsersEnum(hwndTV, hItem, szServerName,
					sharename, pshi2->shi2_path, pTVDataShare);
				// Make sure we're showing it all
				TreeView_Expand(hwndTV, hItem, TVE_EXPAND);
			}
			else
			{
				// Delete all our children
				FTreeView_DeleteRange(hwndTV, hItem, NULL, NULL);
			}
		}
	}

	// reset any errors UsersEnum may have trickled up
	nas = 0;

err:
	// Whack any stragglers hanging at the end
	FTreeView_DeleteRange(hwndTV, hParent, tvis.hInsertAfter, NULL);

	if(nas)
		AddErrorStringToTV(hwndTV, hParent, IDS_ERRENUMSHARES, nas);
	NetApiBufferFree(shi2);
	return nas;
}

/*
 *	RefreshDisplay
 *
 *	Purpose:
 *		Update the treeview with piping hot info
 *
 *	Arguments:
 *		main hwnd
 *
 *	Returns:
 *		Count of uses connected to shares
 */
UINT
RefreshDisplay(HWND hwnd, HWND hwndTV)
{
	HTREEITEM		hItem;
	HCURSOR			hCursor;
	UINT			cUsers = 0;
	static UINT		cRefreshes = 0;

	// Turn off the timer
	PunchTimer(hwnd, FALSE);
	OutputDbgStr("RefreshDisplay (%d): 0x%08lx", cRefreshes, GetTickCount());

	// This may take a while
	hCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));

	// Enumerate all the shares
	hItem = TreeView_GetRoot(hwndTV);
	while(hItem)
	{
		TV_ITEM		tvItem;
		HTREEITEM	hItemChild;
		TCHAR		szT[UNCLEN + 1];

		// Check to see if the first child is an error
		if((cRefreshes % 4) && (hItemChild = TreeView_GetChild(hwndTV, hItem)))
		{
			// If it is, only update it 1 out of 4 times
			tvItem.mask = TVIF_PARAM;
			tvItem.hItem = hItemChild;
			if(TreeView_GetItem(hwndTV, &tvItem) && tvItem.lParam == TYPE_ERROR)
			{
				OutputDbgStr("Skipping errored out server");
				goto nextserver;
			}
		}

		// Get the server name and server image
		tvItem.mask = TVIF_TEXT | TVIF_IMAGE;
		tvItem.hItem = hItem;
		tvItem.pszText = szT;
		tvItem.cchTextMax = UNCLEN + 1;
		if(TreeView_GetItem(hwndTV, &tvItem) && (szT[0] == '\\'))
		{
			// Enumerate all the shares under here
			SharesEnum(hwndTV, hItem, szT, &cUsers,
				tvItem.iImage == BMP_COMPUTER ? 2 : 1);
			// Make sure we're showing it all
			TreeView_Expand(hwndTV, hItem, TVE_EXPAND);
		}

		// Next server
nextserver:
		hItem = TreeView_GetNextSibling(hwndTV, hItem);
	}

	// Bring back our arrow
	SetCursor(hCursor);

	// Swing the selection back into view
	if(hItem = TreeView_GetSelection(hwndTV))
		TreeView_EnsureVisible(hwndTV, hItem);

	// Resume the timer again
	PunchTimer(hwnd, TRUE);

	// Update our number of refreshes and return the count of users
	cRefreshes++;
	return cUsers;
}

/*
 *	Properties
 */

/*
 *	DisplayComputerDetails
 *
 *	Purpose:
 *		Delete/Show property page for computer
 *
 *	Arguments:
 *		hwnd, wAction
 *
 *	Returns:
 *		nas
 */
NET_API_STATUS
DisplayComputerDetails(HWND hwnd, TVDATA *pTVData, WORD wAction)
{
	HTREEITEM		hItem;
	HWND			hwndTV;
	NET_API_STATUS	nas = 0;
	SERVER_INFO_102	*si102 = NULL;

	if(!(hwndTV = GetDlgItem(hwnd, IDD_tvwSHARES)))
		return 0;

	if(!(hItem = TreeView_GetSelection(hwndTV)))
		return 0;

	if(wAction == VK_DELETE)
	{
		TreeView_DeleteItem(hwndTV, hItem);
	}
	else
	{
		TV_ITEM	tvItem;
		HCURSOR	hCursor;
		TCHAR	szT[UNCLEN + 1];
		TCHAR	szVer[cchSzMax + 1];

		szT[0] = 0;
		tvItem.mask = TVIF_TEXT;
		tvItem.hItem = hItem;
		tvItem.pszText = szT;
		tvItem.cchTextMax = UNCLEN + 1;
		TreeView_GetItem(hwndTV, &tvItem);

		hCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
		nas = NetServerGetInfo(szT, 102, (LPBYTE *)&si102);
		SetCursor(hCursor);
		if(nas || !si102)
			goto err;

		wsprintf(szVer, TEXT("%d.%d"),
			si102->sv102_version_major & MAJOR_VERSION_MASK,
			si102->sv102_version_minor);

		PropertyDlg(hwnd,
			IDS_SERVERPROPS,
			0xfffffff1,
			si102->sv102_name,
			si102->sv102_comment,
			si102->sv102_userpath,
			szVer,
			szFromIDS1(IDS_HIDDEN + !!si102->sv102_hidden),
			NULL);
	}

err:
	NetApiBufferFree(si102);
	return nas;
}

/*
 *	DisplayShareDetails
 *
 *	Purpose:
 *		Delete/Show property page for shares
 *
 *	Arguments:
 *		hwnd, pTVDataShare, wAction
 *
 *	Returns:
 *		nas
 */
NET_API_STATUS
DisplayShareDetails(HWND hwnd, TVDATA *pTVData, WORD wAction)
{
	NET_API_STATUS	nas;
	HCURSOR			hCursor;
	SHARE_INFO_2	*shi2 = NULL;
	TVDATASHARE		*pTVDataShare = (TVDATASHARE *)pTVData;

	hCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
	nas = NetShareGetInfo(pTVDataShare->szServerName, pTVDataShare->szShareName,
		2, (LPBYTE *)&shi2);
	SetCursor(hCursor);
	if(!nas && shi2)
	{
		if(wAction == VK_DELETE)
		{
			// if no one is connected, nuke it, else confirm with user
			if(!(shi2->shi2_current_uses) ||
				(MessageBox(hwnd, szFromIDS1(IDS_AREYOUSURE + TYPE_SHARE), 
					szAppName, MB_ICONEXCLAMATION | MB_YESNO | MB_DEFBUTTON2) == 
					IDYES))
			{
				nas = NetShareDel(pTVDataShare->szServerName,
					pTVDataShare->szShareName, 0);
			}
		}
		else
		{
			TCHAR	szMaxUses[11];
			TCHAR	szMaxCurrent[11];

			wsprintf(szMaxUses, szFmtNum, shi2->shi2_max_uses);
			wsprintf(szMaxCurrent, szFmtNum, shi2->shi2_current_uses);

			PropertyDlg(hwnd,
				IDS_SHAREPROPS,
				((shi2->shi2_type & 0xf) == STYPE_IPC) ? 0xfffffff8 : 0xfffffff0,
				shi2->shi2_netname,
				shi2->shi2_path,
				shi2->shi2_remark,
				(shi2->shi2_max_uses == SHI_USES_UNLIMITED) ? 
					szFromIDS1(IDS_NOLIMIT) : szMaxUses,
				szMaxCurrent,
				NULL);
		}
	}

	NetApiBufferFree(shi2);
	return nas;
}

/*
 *	DisplayFileDetails
 *
 *	Purpose:
 *		Delete/Show property page for files
 *
 *	Arguments:
 *		hwnd, pTVDataFile, wAction
 *
 *	Returns:
 *		nas
 */
NET_API_STATUS
DisplayFileDetails(HWND hwnd, TVDATA *pTVData, WORD wAction)
{
	NET_API_STATUS	nas;
	HCURSOR			hCursor;
	FILE_INFO_3		*fi3 = NULL;
	TCHAR			*szServerName;  
	TVDATAFILE		*pTVDataFile = (TVDATAFILE *)pTVData;

	hCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
	szServerName = pTVDataFile->pTVDataUser->pTVDataShare->szServerName;
	nas = NetFileGetInfo(szServerName, pTVDataFile->dwFileId, 3, (LPBYTE *)&fi3);
	SetCursor(hCursor);
	if(!nas && fi3)
	{
		if(wAction == VK_DELETE)
		{
			TCHAR	szMsg[cchMsgMax];

			wsprintf(szMsg, szFromIDS1(IDS_AREYOUSURE + TYPE_FILE),
				pTVDataFile->pTVDataUser->szUserName, fi3->fi3_pathname);
			if(MessageBox(hwnd, szMsg, szAppName,
				MB_ICONEXCLAMATION | MB_YESNO | MB_DEFBUTTON2) == IDYES)
			{
				nas = NetFileClose(szServerName, pTVDataFile->dwFileId);
			}
		}
		else
		{
			TCHAR	szNumLocks[11];
			UINT	nBitmap = BMP_READ;

			if((fi3->fi3_permissions & PERM_FILE_WRITE) ||
				(fi3->fi3_permissions & PERM_FILE_CREATE))
					nBitmap = BMP_WRITE;

			wsprintf(szNumLocks, szFmtNum, fi3->fi3_num_locks);

			PropertyDlg(hwnd,
				IDS_FILEPROPS,
				0xfffff072 | (nBitmap << 8),
				fi3->fi3_pathname,
				fi3->fi3_username,
				szFromIDS1(IDS_FILEPROPS + 10 + nBitmap),
				szNumLocks,
				NULL,
				NULL);
		}
	}

	NetApiBufferFree(fi3);
	return nas;
}

/*
 *	DisplayUserDetails
 *
 *	Purpose:
 *		Delete/Show property page for users
 *
 *	Arguments:
 *		hwnd, pTVDataUser, wAction
 *
 *	Returns:
 *		nas
 */
NET_API_STATUS
DisplayUserDetails(HWND hwnd, TVDATA *pTVData, WORD wAction)
{
	NET_API_STATUS	nas;
	time_t			tm_t;
	TCHAR			*szServerName;
	SESSION_INFO_2	*sesi2 = NULL;
	TCHAR			szUserName[UNLEN + cchSzMax + 1];
	TVDATAUSER		*pTVDataUser = (TVDATAUSER *)pTVData;

	szServerName = pTVDataUser->pTVDataShare->szServerName;
	nas = NetSessionGetInfo(szServerName, pTVDataUser->szNetName,
		pTVDataUser->szUserName, 2, (LPBYTE *)&sesi2);
	if(!nas && sesi2)
	{
		if(wAction == VK_DELETE)
		{
			UINT	ids;
			TCHAR	szMsg[cchMsgMax];

			// if user has open files, tell the del happy person this
			// otherwise just reaffirm that they wanna hack em.
			ids = sesi2->sesi2_num_opens ?
				IDS_AREYOUSURE + TYPE_USER : IDS_AREYOUSUREDISUSER;
			wsprintf(szMsg, szFromIDS1(ids), pTVDataUser->szUserName);
			if(MessageBox(hwnd, szMsg, szAppName,
				MB_ICONEXCLAMATION | MB_YESNO | MB_DEFBUTTON2) == IDYES)
			{
				nas = NetSessionDel(szServerName, pTVDataUser->szNetName,
					pTVDataUser->szUserName);
			}
		}
		else
		{
			TCHAR	szNumOpens[11];
			TCHAR	szIdleTime[cchSzMax];
			TCHAR	szConnectTime[cchSzMax];
			SCONST TCHAR szSpace[] = TEXT(" ");

			lstrcpy(szUserName, pTVDataUser->szUserName);
			if(sesi2->sesi2_user_flags & SESS_GUEST)
				lstrcat(szUserName, szFromIDS1(IDS_GUEST));

			time(&tm_t);
			PutTime(tm_t - sesi2->sesi2_time, szIdleTime, cchSzMax);
			PutDate(tm_t - sesi2->sesi2_time, szConnectTime, cchSzMax);
			lstrcat(szConnectTime, szSpace);
			lstrcat(szConnectTime, szIdleTime);

			wsprintf(szNumOpens, szFmtNum, sesi2->sesi2_num_opens);

			PropertyDlg(hwnd,
				IDS_USERPROPS,
				pTVDataUser->pTVDataShare->dwShareType == STYPE_IPC ?
					0xfffff817 : 0xfffff017,
				szUserName,
				pTVDataUser->szNetName, 
				pTVDataUser->pTVDataShare->szShareName,
				szConnectTime,
				PutCounterTime(sesi2->sesi2_idle_time, szIdleTime, cchSzMax),
				szNumOpens);
		}
	}

	if(!nas && !sesi2)
		nas = ERROR_NOT_CONNECTED;
	NetApiBufferFree(sesi2);
	return nas;
}

/*
 *	Nifty little array of property functions
 */
typedef NET_API_STATUS (*PFNDISPLAYDETAILS)(HWND hwnd, TVDATA *pTVData, WORD wAction);
SCONST PFNDISPLAYDETAILS pfnDisplayDetails[TYPE_MAX] =
{
	DisplayComputerDetails,
	DisplayShareDetails,
	DisplayUserDetails,
	DisplayFileDetails
};

/*
 *	HandleWM_VKEY
 *
 *	Purpose:
 *		handle WM_VKEYS: VK_DELETE and VK_RETURN
 *
 *	Arguments:
 *		main hwnd and wAction
 *
 *	Returns:
 *		TRUE - success, FALSE - error
 */
BOOL
HandleWM_VKEY(HWND hwnd, HWND hwndTV, WORD wAction)
{
	NET_API_STATUS	nas = 0;
	TVDATA			*pTVData;
	DWORD			dwType = TYPE_COMPUTER;

	OutputDbgStr("HandleWM_VKEY");
	// Only handle return and delete keys
	if((wAction != VK_RETURN) && (wAction != VK_DELETE))
		return FALSE;

	// Get the Selected item data
	pTVData = (TVDATA *)TreeView_GetSelectedItemData(hwndTV, &dwType);

	// Ok, do the order
	PunchTimer(hwnd, FALSE);

	// jump to the display page
	if(dwType < TYPE_MAX)
		nas = (pfnDisplayDetails[dwType])(hwnd, pTVData, wAction);

	// Report any errors
	if(nas)
	{
		TCHAR	szMsg[cchErrMax];
		TCHAR	*szErrMessage = NULL;

		lstrcpy(szMsg, szFromIDS1(IDS_ERRACTION));
		if(szErrMessage = GetSystemErrMessage(nas))
			lstrcat(szMsg, szErrMessage);

		MessageBox(hwnd, szMsg, szAppName, MB_ICONEXCLAMATION);
		GlobalFreeNullPtr(szErrMessage);
	}

	// If we hit an error or they whacked something, update now
	if(nas || (wAction == VK_DELETE))
		PostMessage(hwnd, WM_TIMER, 0, 0L);
	else
		PunchTimer(hwnd, TRUE);

	return TRUE;
}

/*
 *	AddErrorStringToTV
 *
 *	Purpose:
 *		Slap an error string in the TV
 *
 *	Arguments:
 *		hParent, ids of error, nas of error
 *
 *	Returns:
 *		nada
 */
VOID
AddErrorStringToTV(HWND hwndTV, HTREEITEM hParent, UINT ids, NET_API_STATUS nas)
{
	TV_INSERTSTRUCT	tvis;
	TCHAR			*szErrMessage;
	SCONST TCHAR	szSep[] = TEXT(": ");
	TCHAR			szErrBuf[cchErrMax];

	// Get the text
	lstrcpy(szErrBuf, szFromIDS1(ids));
	if(szErrMessage = GetSystemErrMessage(nas))
	{
		lstrcat(szErrBuf, szSep);
		lstrcat(szErrBuf, szErrMessage);
		LocalFree((HLOCAL)szErrMessage);
	}

	// Add the error string
	tvis.hParent = hParent;
	tvis.item.mask = TVIF_PARAM | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvis.hInsertAfter = NULL;
	tvis.item.pszText = szErrBuf;
	tvis.item.iImage = tvis.item.iSelectedImage = BMP_DENIED;
	tvis.item.lParam = (LPARAM)TYPE_ERROR;
	TreeView_TVDataInsert(hwndTV, &tvis);

	// Delete all other children
	FTreeView_DeleteRange(hwndTV, hParent, tvis.hInsertAfter, NULL);
}

/*
 *	FAnyRemoteDrives
 *
 *	Purpose:
 *		Checks if there are any remote drives connected
 *
 *	Arguments:
 *		zip
 *
 *	Returns:
 *		Returns TRUE if there are
 */
BOOL
FAnyRemoteDrives()
{
	INT		ch;
	UINT	errmode;
	TCHAR	szRoot[4];
	BOOL	fRet = FALSE;

	errmode = SetErrorMode(SEM_FAILCRITICALERRORS);

	szRoot[1] = ':';
	szRoot[2] = '\\';
	szRoot[3] = 0;
	for (ch = 'C'; ch <= 'Z'; ch++)
	{
		szRoot[0] = ch;
		if(GetDriveType(szRoot) == DRIVE_REMOTE)
		{
			fRet = TRUE;
			break;
		}
	}

	SetErrorMode(errmode);
	return fRet;
}

/*
 *	HandleMenu
 *
 *	Purpose:
 *		Disable\Enable\Change menu according to what is selected
 *
 *	Arguments:
 *		hwnd
 *
 *	Returns:
 *		zip
 */
VOID
HandleMenu(HWND hwnd, HWND hwndTV, HMENU hMenu)
{
	DWORD	dwType = TYPE_COMPUTER;

	TreeView_GetSelectedItemData(hwndTV, &dwType);
	OutputDbgStr("Item type %d selected", dwType);

	// Enable/disable the disconnect network drive menu item
	if(hMenu == ghMenu)
	{
		EnableMenuItem(hMenu, IDM_DISCONNECTDRIVE, FAnyRemoteDrives() ?
			MF_BYCOMMAND | MF_ENABLED : MF_BYCOMMAND | MF_GRAYED);
	}

	if(dwType == TYPE_ERROR)
	{
		EnableMenuItem(hMenu, IDM_DELETERESOURCE, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_PROPERTIES, MF_BYCOMMAND | MF_GRAYED);
	}
	else
	{
		EnableMenuItem(hMenu, IDM_PROPERTIES, MF_BYCOMMAND | MF_ENABLED);
		ModifyMenu(hMenu, IDM_DELETERESOURCE, MF_BYCOMMAND | MF_STRING,
			IDM_DELETERESOURCE, szFromIDS1(IDS_DELETERESOURCE + dwType));
	}
}
