/*==========================================================================
 *
 *  Copyright (C) 1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       cGrpTree.cpp
 *  Content:	An abstracted Tree control that knows how to handle
 *              DirectPlay system messages and enumerations.
 *
 ***************************************************************************/

#include "cgrptree.h"

WNDPROC			gwpOrigEditProc;

///////////////////////////////////////////////////////////////////////////////////////
long FAR PASCAL EditCtrlSubProc(HWND hWnd, WORD wMessage,WORD wParam,LONG lParam)
{
 
    switch (wMessage)
     {
 
          case WM_GETDLGCODE:
            return (DLGC_WANTALLKEYS |
                    CallWindowProc( gwpOrigEditProc, hWnd, wMessage,
                                   wParam, lParam));
 
          case WM_CHAR:
          //Process this message to avoid message beeps.
				if ((wParam == VK_RETURN) || (wParam == VK_TAB))
					return 0;
			break ;
 
       default:
            break;
 
     } /* end switch */

	return (CallWindowProc( gwpOrigEditProc, hWnd, wMessage,
                                   wParam, lParam));

}

///////////////////////////////////////////////////////////////////////////////////////
BOOL FAR PASCAL TV_EnumPlayersCallback(	DPID dpId,
										DWORD dwPlayerType, 
										LPCDPNAME lpName,
										DWORD dwFlags, 
										LPVOID lpContext)
{
	LPENUMTREESTRUCT lp = (LPENUMTREESTRUCT) lpContext;

	if (DPPLAYERTYPE_GROUP == dwPlayerType)
	{
		if (DPENUMGROUPS_SHORTCUT & dwFlags)
		{
			lp->lpTree->AddGroupToGroup( lp->dpidParent, dpId, dwFlags );
		}
		else
		{
			HRESULT	hr;
			ENUMTREESTRUCT	ets;

			ets.dpidParent = dpId;
			ets.lpTree = lp->lpTree;
			ets.bRecursive = lp->bRecursive;

			if (NULL == lp->dpidParent)
			{
				lp->lpTree->CreateGroup( dpId, lpName->lpszShortNameA, dwFlags );
			}
			else
			{
				lp->lpTree->CreateGroupInGroup( lp->dpidParent, dpId, lpName->lpszShortNameA, dwFlags );
			}

			if (ets.bRecursive)
			{
				hr = lp->lpTree->m_lpDP3A->EnumGroupsInGroup(	dpId, NULL, 
															TV_EnumPlayersCallback, 
															&ets, DPENUMPLAYERS_ALL );

				hr = lp->lpTree->m_lpDP3A->EnumGroupPlayers(	dpId, NULL, 
															TV_EnumPlayersCallback, 
															&ets, DPENUMPLAYERS_ALL );
			}

		}
	}
	else
	{
		if (lp->dpidParent)
		{
			lp->lpTree->AddPlayerToGroup( lp->dpidParent, dpId, dwFlags );
		}
		else
		{
			lp->lpTree->CreatePlayer( dpId, lpName->lpszShortNameA, dwFlags );
		}
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////
int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	LPBRANCHSTRUCT	lp1 = (LPBRANCHSTRUCT) lParam1,
					lp2 = (LPBRANCHSTRUCT) lParam2;

	if ( lp1->btType < lp2->btType )
	{
		return -1;
	}

	if (lp1->btType > lp2->btType )
	{
		return 1;
	}

	//if we got here, they are of the same type
	//so sort alphabetically

	LPDPNAME		lpdpn1 = NULL,
					lpdpn2 = NULL;
	int				iRes = 0;
	HRESULT			hr = DPERR_GENERIC;
	CGroupTree *	lpgt = (CGroupTree *) lParamSort;

	if ((lp1->btType == BT_PLAYER ) || (lp1->btType == BT_PLAYER_IN_GROUP ))
	{
		hr = lpgt->GetPlayerName( lp1->dpid, &lpdpn1 );
	}
	else
	{
		hr = lpgt->GetGroupName( lp1->dpid, &lpdpn1 );
	}

	if FAILED(hr)
	{
		goto FAILURE;
	}

	if ((lp2->btType == BT_PLAYER ) || (lp2->btType == BT_PLAYER_IN_GROUP ))
	{
		hr = lpgt->GetPlayerName( lp2->dpid, &lpdpn2 );
	}
	else
	{
		hr = lpgt->GetGroupName( lp2->dpid, &lpdpn2 );
	}

	if FAILED(hr)
	{
		goto FAILURE;
	}


	iRes = strcmp( lpdpn1->lpszShortNameA, lpdpn2->lpszShortNameA );

	if ( 0 == iRes )
	{
		//The groups have the same name.
		if ( lp1->dpid <  lp2->dpid )
		{
			iRes = -1;
		}
		else if ( lp1->dpid >  lp2->dpid )
		{
			iRes = 1;
		}
		else
		{
			iRes = -1;
		}
	}

FAILURE:
	if (lpdpn1)
		LocalFree(lpdpn1);

	if (lpdpn2)
		LocalFree(lpdpn2);


	return iRes;
}

///////////////////////////////////////////////////////////////////////////////////////
CGroupTree::CGroupTree()
{

	m_hInst = GetModuleHandle( NULL );
	m_hwndTreeView = NULL;
	m_hwndParent = NULL;
	m_lpDP3A = NULL;
	m_fDragging = FALSE;
	m_dpidPlayer = 0;
	m_dpidLastGroup = NULL;

	// Prepare popup menus
	m_hMenu = LoadMenu( m_hInst, MAKEINTRESOURCE(IDM_MENU) );
	m_hRootMenu = GetSubMenu( m_hMenu, 0 );
	m_hGroupMenu = GetSubMenu( m_hMenu, 1 );
	m_hPlayerMenu = GetSubMenu( m_hMenu, 2 );
	m_hShortcutMenu = GetSubMenu( m_hMenu, 3 );
	m_hPlayerInGroupMenu= GetSubMenu( m_hMenu, 4 );

	// Prepare tree icons
	m_hImageList = ImageList_Create(32, 32, 0, 8, 8);
	ImageList_SetBkColor(m_hImageList, GetSysColor(COLOR_WINDOW));
	m_nGroupImg = ImageList_AddIcon(m_hImageList, LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_CLOSEDDOOR)));
	m_nInGroupImg = ImageList_AddIcon(m_hImageList, LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_OPENDOOR)));
	m_nPlayerImg = ImageList_AddIcon(m_hImageList, LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_PLAYER)));
	m_nShortcutInGroupImg = ImageList_AddIcon(m_hImageList, LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_SHORTCUT)));
	m_nStagingAreaImg = ImageList_AddIcon(m_hImageList, LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_STAGINGAREA)));
	m_nSpectatorImg = ImageList_AddIcon(m_hImageList, LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_SPECTATOR)));
	m_nSessionInProgressImg = ImageList_AddIcon(m_hImageList, LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_SESSIONINPROGRESS)));

	ZeroMemory( &m_bsDragging, sizeof( BRANCHSTRUCT ) );

}

///////////////////////////////////////////////////////////////////////////////////////
CGroupTree::~CGroupTree()
{
	if (m_hImageList)
	{
		ImageList_Destroy( m_hImageList );
		m_hImageList = NULL;
	}

	DestroyMenu( m_hPlayerInGroupMenu );
	DestroyMenu( m_hShortcutMenu );
	DestroyMenu( m_hPlayerMenu );
	DestroyMenu( m_hGroupMenu );
	DestroyMenu( m_hRootMenu );
	DestroyMenu( m_hMenu );
}

///////////////////////////////////////////////////////////////////////////////////////
BOOL CGroupTree::Init( HWND hWnd, LPDIRECTPLAY3A lpDP3A, DPID dpidPlayer )
{
	if ( (hWnd) && (lpDP3A) && (dpidPlayer) )
	{
		m_hwndTreeView = hWnd;
		m_hwndParent = GetParent( m_hwndTreeView );
		m_lpDP3A = lpDP3A;
		m_dpidPlayer = dpidPlayer;

		TreeView_SetImageList(hWnd, m_hImageList, TVSIL_NORMAL);
		return TRUE;
	}
	else
		return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::GetPlayerName( DPID dpidPlayer, LPDPNAME * lplpn)
{
	HRESULT	hr		= DPERR_GENERIC;
	LPVOID	lpData	= NULL;
	DWORD	dwSize	= 0;

	hr = m_lpDP3A->GetPlayerName( dpidPlayer, NULL, &dwSize );

	if (DPERR_BUFFERTOOSMALL == hr )
	{
		lpData = LocalAlloc( LPTR, dwSize );

		if ( NULL != lpData )
		{
			hr = m_lpDP3A->GetPlayerName( dpidPlayer, lpData, &dwSize );

			if (FAILED(hr))
			{
				LocalFree( lpData );
				lpData = NULL;
			}
		}
		else
		{
			hr = DPERR_OUTOFMEMORY;
		}
	}

	*lplpn = (LPDPNAME) lpData;

	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::GetGroupName( DPID dpidGroup, LPDPNAME * lplpn)
{
	HRESULT	hr		= DPERR_GENERIC;
	LPVOID			lpData = NULL;

	DWORD	dwSize	= 0;

	hr = m_lpDP3A->GetGroupName( dpidGroup, lpData, &dwSize );

	if (DPERR_BUFFERTOOSMALL == hr )
	{
		lpData = LocalAlloc( LPTR,  dwSize );

		if ( NULL != lpData )
		{
			hr = m_lpDP3A->GetGroupName( dpidGroup, lpData, &dwSize );

			if (FAILED(hr))
			{
				LocalFree( lpData );
				lpData = NULL;
			}
		}
		else
		{
			hr = DPERR_OUTOFMEMORY;
		}
	}


	*lplpn = (LPDPNAME) lpData;

	return hr;
}


///////////////////////////////////////////////////////////////////////////////////////
HTREEITEM CGroupTree::FindItem( HTREEITEM htiSearchRoot, 
								DPID dpidTarget, 
								BRANCH_TYPE bt, 
								DWORD dwSearch )
{
    TV_ITEM tvi;
	HTREEITEM	hItem,
				htiSubSearch;
	LPBRANCHSTRUCT lpbs = NULL;

    if(TVI_ROOT == htiSearchRoot)
    {
        hItem = TreeView_GetRoot(m_hwndTreeView);
    }
	else
	{
		hItem = TreeView_GetChild( m_hwndTreeView, htiSearchRoot );
	}

    while(hItem)
    {
        ZeroMemory( &tvi, sizeof(TV_ITEM));
        
        tvi.mask            = TVIF_PARAM;
        tvi.hItem           = hItem;

        TreeView_GetItem(m_hwndTreeView, &tvi);
		lpbs = (LPBRANCHSTRUCT) tvi.lParam;

        if ( (lpbs->dpid == dpidTarget) && ( bt == lpbs->btType))
        {
			return tvi.hItem;
        }

        if ( (lpbs->btType == BT_GROUP) && (ST_SEARCH_SUBGROUPS & dwSearch) )
		{
			htiSubSearch = FindItem( hItem, dpidTarget, bt, dwSearch );
			if (htiSubSearch)
				return (htiSubSearch);
		}

		hItem = TreeView_GetNextSibling(m_hwndTreeView, hItem);
    }

    return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////
HTREEITEM CGroupTree::Insert( HTREEITEM htiParent, DPID dpID, LPSTR lpszShortNameA, BRANCH_TYPE bt, DWORD dwFlags )
{
    LPBRANCHSTRUCT		lpbs	= NULL;
	HTREEITEM			htrItem	= NULL;

	if ( lpbs = (LPBRANCHSTRUCT) LocalAlloc( LPTR,  sizeof(BRANCHSTRUCT) ) )
	{
		TV_INSERTSTRUCT		tvi;
		TV_SORTCB			tvscb; 

		ZeroMemory(lpbs, sizeof( BRANCHSTRUCT ) );
		ZeroMemory(&tvscb, sizeof(tvscb));
		ZeroMemory(&tvi, sizeof(tvi));
		tvi.hParent				= htiParent;
		tvi.hInsertAfter		= TVI_LAST;

		tvi.item.mask			= TVIF_IMAGE | TVIF_PARAM | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		tvi.item.pszText		= lpszShortNameA;
		tvi.item.cchTextMax		= strlen(lpszShortNameA)+1;

		switch( bt)
		{
			case BT_PLAYER:
			case BT_PLAYER_IN_GROUP:
				tvi.item.iImage = (DPPLAYER_SPECTATOR & dwFlags) ?  m_nSpectatorImg: m_nPlayerImg;
				tvi.item.iSelectedImage	= tvi.item.iImage;
			break;

			case BT_GROUP:
				if (DPGROUP_STAGINGAREA & dwFlags)
				{
					HRESULT hr;
					LPDPLCONNECTION lp = NULL;
					DWORD			dwSize = 0;
					BOOL			bSessionInProgress = FALSE;

					// if it is a staging area, check to see if the session is in progress.
					hr = IDirectPlay3_GetGroupConnectionSettings( m_lpDP3A, 0, dpID, NULL, &dwSize );
					if (DPERR_BUFFERTOOSMALL == hr )
					{
						lp = (LPDPLCONNECTION) GlobalAllocPtr( GHND, dwSize );

						if (lp)
						{
							hr = IDirectPlay3_GetGroupConnectionSettings( m_lpDP3A, 0, dpID, lp, &dwSize );

							if (!IsEqualGUID(lp->lpSessionDesc->guidInstance, GUID_NULL))
							{
								// If the server has assigned an instance guid 
								// to our connection structure, the session 
								// has already started.

								bSessionInProgress = TRUE;
							}
							GlobalFreePtr(lp);
						}
					}


					tvi.item.iImage = (bSessionInProgress)?m_nSessionInProgressImg:m_nStagingAreaImg;
					tvi.item.iSelectedImage = tvi.item.iImage;
				}
				else
				{
					tvi.item.iImage = m_nGroupImg;
					tvi.item.iSelectedImage = m_nInGroupImg;
				}
				break;

			case BT_SHORTCUT_IN_GROUP:
				tvi.item.iImage = m_nShortcutInGroupImg;
				tvi.item.iSelectedImage	= tvi.item.iImage;
			break;

			default:
				//Invalid BranchType
			break;
		}
		tvi.item.lParam			= (LPARAM) lpbs;

		lpbs->dpid		= dpID;
		lpbs->btType	= bt;
		lpbs->dwFlags	= dwFlags;

		htrItem = TreeView_InsertItem( m_hwndTreeView, &tvi );

		tvscb.hParent = htiParent; 
		tvscb.lpfnCompare = CompareFunc; 
		tvscb.lParam = (LPARAM) this; 

		TreeView_SortChildrenCB( m_hwndTreeView, &tvscb, 0 );

		if(TVI_ROOT != htiParent)
		{
			TreeView_Expand(m_hwndTreeView, htiParent, TVE_EXPAND);
		}

		Redraw();
	}

	return htrItem;
}


///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::CreatePlayer( DPID dpidPlayer, LPSTR lpszShortNameA, DWORD dwFlags )
{
	/*
	// We currently support only one local player. This section of code would create a
	// new player at the root for each create player message received.

	LPDPNAME lpn = NULL;

	if (NULL == lpszShortNameA)
	{
		GetPlayerName(dpidPlayer, &lpn );
		lpszShortNameA = lpn->lpszShortNameA;
	}

	if (lpszShortNameA)
	{
		Insert( TVI_ROOT, dpidPlayer, lpszShortNameA, BT_PLAYER, dwFlags );
	}

	if (lpn)
		LocalFree(lpn);
	*/

	return DP_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::CreateGroup( DPID dpidGroup, LPSTR lpszShortNameA, DWORD dwFlags  )
{
	LPDPNAME lpn = NULL;

	if (NULL == lpszShortNameA)
	{
		GetGroupName(dpidGroup, &lpn );
		lpszShortNameA = lpn->lpszShortNameA;
	}

	if (lpszShortNameA)
	{
		Insert( TVI_ROOT, dpidGroup, lpszShortNameA, BT_GROUP, dwFlags );
	}

	if (lpn)
		LocalFree(lpn);


	return DP_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::CreateGroupInGroup( DPID dpidParentGroup, DPID dpidChildGroup, LPSTR lpszShortNameA, DWORD dwFlags   )
{
	HTREEITEM hParentItem = NULL;

	if ( hParentItem = FindItem( TVI_ROOT, dpidParentGroup, BT_GROUP, ST_SEARCH_SUBGROUPS ) )
	{
		LPDPNAME lpn = NULL;

		if (NULL == lpszShortNameA)
		{
			GetGroupName(dpidChildGroup, &lpn );
			lpszShortNameA = lpn->lpszShortNameA;
		}

		if (lpszShortNameA)
		{
			Insert( hParentItem, dpidChildGroup, lpszShortNameA, BT_GROUP, dwFlags );
		}

		if (lpn)
			LocalFree(lpn);


	}

	return DP_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::AddPlayerToGroup( DPID dpidGroup, DPID dpidPlayer, DWORD dwFlags )
{
	HRESULT	hr = DPERR_GENERIC;
	LPDPNAME lpPlayerName = NULL;

	hr = GetPlayerName( dpidPlayer, &lpPlayerName );

	if (SUCCEEDED(hr))
	{
		HTREEITEM hParentItem = NULL;

		if ( hParentItem = FindItem( TVI_ROOT, dpidGroup, BT_GROUP, ST_SEARCH_SUBGROUPS ) )
		{
			Insert( hParentItem, dpidPlayer, lpPlayerName->lpszShortNameA, BT_PLAYER_IN_GROUP, dwFlags );
		}
	}

	if (lpPlayerName)
		LocalFree( lpPlayerName);

	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::AddGroupToGroup( DPID dpidParentGroup, DPID dpidShortcut, DWORD dwFlags )
{
	HRESULT	hr = DPERR_GENERIC;
	LPDPNAME lpGroupName = NULL;

	hr = GetGroupName( dpidShortcut, &lpGroupName );

	if (SUCCEEDED(hr))
	{
		HTREEITEM hParentItem = NULL;

		if ( hParentItem = FindItem( TVI_ROOT, dpidParentGroup, BT_GROUP, ST_SEARCH_SUBGROUPS ) )
		{
			Insert( hParentItem, dpidShortcut, lpGroupName->lpszShortNameA, BT_SHORTCUT_IN_GROUP, dwFlags );
		}
	}

	if (lpGroupName)
		LocalFree( lpGroupName);

	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::DestroyPlayer(DPID dpidPlayer)
{
    /*

	// We are not currently adding additional players to the tree view. The 
	// Code below would add a player to the root of the tree control. If you
	// want that functionality.

	HTREEITEM	htiPlayer = FindItem( TVI_ROOT, dpidPlayer, BT_PLAYER, ST_NO_SUBGROUPS );

	if ( htiPlayer )
    {
		TreeView_DeleteItem(m_hwndTreeView, htiPlayer);
		Redraw();
    }
	*/

	return DP_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::DestroyGroup(DPID dpidGroup)
{
    HTREEITEM	htiGroup = FindItem( TVI_ROOT, dpidGroup, BT_GROUP, ST_SEARCH_SUBGROUPS );

	if ( htiGroup )
    {
		TreeView_DeleteItem(m_hwndTreeView, htiGroup);
		Redraw();
	}

	return DP_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::DeletePlayerFromGroup( DPID dpidGroup, DPID dpidPlayer )
{
	HRESULT	hr = DPERR_GENERIC;
	HTREEITEM	htiParent = NULL,
				htiPlayer = NULL;

	if ( htiParent = FindItem( TVI_ROOT, dpidGroup, BT_GROUP, ST_SEARCH_SUBGROUPS ) )
	{
		if ( htiPlayer = FindItem( htiParent, dpidPlayer, BT_PLAYER_IN_GROUP, ST_NO_SUBGROUPS ) )
		{
			TreeView_DeleteItem(m_hwndTreeView, htiPlayer);
			hr = DP_OK;

			Redraw();
		}
	}

	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::DeleteGroupFromGroup( DPID dpidParentGroup, DPID dpidShortcut )
{
	HRESULT	hr = DPERR_GENERIC;
	HTREEITEM	htiParent = NULL,
				htiShortcut = NULL;

	if ( htiParent = FindItem( TVI_ROOT, dpidParentGroup, BT_GROUP, ST_SEARCH_SUBGROUPS ) )
	{
		if ( htiShortcut = FindItem( htiParent, dpidShortcut, BT_SHORTCUT_IN_GROUP, ST_NO_SUBGROUPS ) )
		{
			TreeView_DeleteItem(m_hwndTreeView, htiShortcut );
			hr = DP_OK;

			Redraw();
		}
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::SetPlayerName( DPID dpidPlayer, LPSTR lpszShortName )
{
	HRESULT		hr		= DPERR_GENERIC;

	hr = RecursiveRename( TVI_ROOT, dpidPlayer, lpszShortName );

	return hr; 
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::SetGroupName( DPID dpidPlayer, LPSTR lpszShortName )
{
	HRESULT		hr		= DPERR_GENERIC;

	hr = RecursiveRename( TVI_ROOT, dpidPlayer, lpszShortName );

	return hr; 

}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::RecursiveRename(	HTREEITEM htiSearchRoot, 
										DPID dpidTarget, 
										LPSTR lpszName )
{
    TV_ITEM tvi;
	HTREEITEM	hItem;
	LPBRANCHSTRUCT lpbs = NULL;

    if(TVI_ROOT == htiSearchRoot)
    {
        hItem = TreeView_GetRoot(m_hwndTreeView);
    }
	else
	{
		hItem = TreeView_GetChild( m_hwndTreeView, htiSearchRoot );
	}

    while(hItem)
    {
        ZeroMemory( &tvi, sizeof(TV_ITEM));
        
        tvi.mask            = TVIF_PARAM;
        tvi.hItem           = hItem;

        TreeView_GetItem(m_hwndTreeView, &tvi);
		lpbs = (LPBRANCHSTRUCT) tvi.lParam;

        if (lpbs->dpid == dpidTarget)
        {
	        ZeroMemory( &tvi, sizeof(TV_ITEM));

            tvi.hItem = hItem;
			tvi.mask = TVIF_TEXT;
			tvi.pszText = lpszName;
			tvi.cchTextMax = strlen(lpszName)+1;

			TreeView_SetItem( m_hwndTreeView, &tvi );
        }

        if (lpbs->btType == BT_GROUP)
		{
			RecursiveRename( hItem, dpidTarget, lpszName );
		}

		hItem = TreeView_GetNextSibling(m_hwndTreeView, hItem);
    }

    return DP_OK;

}


///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::Refresh( BOOL bRecursive )
{
	HRESULT			hr = DPERR_GENERIC;
	ENUMTREESTRUCT	ets;

	ets.dpidParent = NULL;
	ets.lpTree	   = this;
	ets.bRecursive = bRecursive;

	TreeView_DeleteAllItems( m_hwndTreeView );

	if (m_lpDP3A)
	{

		//We don't see other root level players in the lobby world.

		//hr = m_lpDP3A->EnumPlayers( NULL, TV_EnumPlayersCallback, &ets, DPENUMPLAYERS_ALL );

		//if (SUCCEEDED( hr ))
		//{
			hr = m_lpDP3A->EnumGroups( NULL, TV_EnumPlayersCallback, &ets, DPENUMPLAYERS_ALL );
		//}
	}

	return hr;
}


///////////////////////////////////////////////////////////////////////////////////////
BOOL CGroupTree::Update(LPVOID lpvMsg)
{

	DWORD	dwMsgType		= ((LPDPMSG_GENERIC)lpvMsg)->dwType;
	LPSTR	lpszShortName	= NULL;
	BOOL	bReturn			= TRUE;

	// Draws the tree based strictly on system messages.
	// If you place a call to this method in the area where you process
	// your system messages, it should give you a good representation
	// of the DirectPlay group structure as it is created.

    switch(dwMsgType)
    {
	case DPSYS_CREATEPLAYERORGROUP:
		{
			LPDPMSG_CREATEPLAYERORGROUP lp = (LPDPMSG_CREATEPLAYERORGROUP)lpvMsg;

			lpszShortName = lp->dpnName.lpszShortNameA;
			if (DPPLAYERTYPE_PLAYER == lp->dwPlayerType)
			{
				CreatePlayer(lp->dpId, lpszShortName, lp->dwFlags );
			}
			else
			{
				if (NULL == lp->dpIdParent)
				{
					CreateGroup(lp->dpId, lpszShortName, lp->dwFlags );
				}
				else
				{
					CreateGroupInGroup(lp->dpIdParent, lp->dpId, lpszShortName, lp->dwFlags );
				}

			}
        }
		break;

        case DPSYS_ADDPLAYERTOGROUP:
		{
			LPDPMSG_ADDPLAYERTOGROUP lp = (LPDPMSG_ADDPLAYERTOGROUP)lpvMsg;
			DWORD	dwFlags;
			HRESULT hr = IDirectPlay3_GetPlayerFlags( m_lpDP3A, lp->dpIdPlayer, &dwFlags );

			if (SUCCEEDED(hr))
			{
				// If I can't get his flags, he must have deleted himself
				// by the time I got this message.
				AddPlayerToGroup(lp->dpIdGroup, lp->dpIdPlayer,	dwFlags );
			}

		}
		break;

        case DPSYS_ADDGROUPTOGROUP:
		{
			LPDPMSG_ADDGROUPTOGROUP lp = (LPDPMSG_ADDGROUPTOGROUP)lpvMsg;
			DWORD	dwFlags;
			HRESULT hr = IDirectPlay3_GetGroupFlags( m_lpDP3A, lp->dpIdGroup, &dwFlags );

			if (SUCCEEDED(hr))
			{
				// If I can't get his flags, he must have deleted himself
				// by the time I got this message.
				AddGroupToGroup(lp->dpIdParentGroup, lp->dpIdGroup, dwFlags );
			}
		}
		break;

        case DPSYS_DESTROYPLAYERORGROUP:
		{
			LPDPMSG_DESTROYPLAYERORGROUP lp = (LPDPMSG_DESTROYPLAYERORGROUP) lpvMsg;

			if ( DPPLAYERTYPE_PLAYER == lp->dwPlayerType )
			{
				DestroyPlayer( lp->dpId );
			}
			else
			{
				DestroyGroup( lp->dpId );
			}
   
        }
		break;

        case DPSYS_DELETEGROUPFROMGROUP:
		{
			LPDPMSG_DELETEGROUPFROMGROUP lp =(LPDPMSG_DELETEGROUPFROMGROUP)lpvMsg;

			DeleteGroupFromGroup( lp->dpIdParentGroup, lp->dpIdGroup );
		}
        break;

        case DPSYS_DELETEPLAYERFROMGROUP:
		{
			LPDPMSG_DELETEPLAYERFROMGROUP lp =(LPDPMSG_DELETEPLAYERFROMGROUP)lpvMsg;

			DeletePlayerFromGroup( lp->dpIdGroup, lp->dpIdPlayer );
		}
        break;

        case DPSYS_SETPLAYERORGROUPDATA:
		//Nothing for right now.
		break;

        case DPSYS_SETPLAYERORGROUPNAME:
		{
			LPDPMSG_SETPLAYERORGROUPNAME lp = (LPDPMSG_SETPLAYERORGROUPNAME)lpvMsg;

		    lpszShortName = lp->dpnName.lpszShortNameA;
			
			if ( DPPLAYERTYPE_PLAYER == lp->dwPlayerType )
			{
				SetPlayerName(lp->dpId, lpszShortName );
			}
			else
			{
				SetGroupName(lp->dpId, lpszShortName );
			}

		}
        break;

		default:
			//Code a new message...
			bReturn = FALSE;
			break;
    }

    return bReturn;
}

///////////////////////////////////////////////////////////////////////////////////////
DPID CGroupTree::GetDPIDOfCurrentSelection( LPBRANCHSTRUCT lpbt)
{

	HTREEITEM	htItem;
	TV_ITEM	tvi;

	ZeroMemory( &tvi, sizeof( TV_ITEM ) );

	htItem = TreeView_GetSelection(m_hwndTreeView);

	if (htItem)
	{

		tvi.mask            = TVIF_PARAM;
		tvi.hItem           = htItem;

		TreeView_GetItem(m_hwndTreeView, &tvi);

		if (lpbt)
		{
			lpbt->dpid = ((LPBRANCHSTRUCT)(tvi.lParam))->dpid;
			lpbt->btType = ((LPBRANCHSTRUCT)(tvi.lParam))->btType;
		}

		return ((LPBRANCHSTRUCT) (tvi.lParam))->dpid;
	}

	return 0;

}

///////////////////////////////////////////////////////////////////////////////////////
DPID CGroupTree::GetDPIDOfCurrentSelectionParent( LPBRANCHSTRUCT lpbt)
{

	HTREEITEM	htChildItem, htItem;
	TV_ITEM	tvi;

	ZeroMemory( &tvi, sizeof( TV_ITEM ) );

	htChildItem = TreeView_GetSelection(m_hwndTreeView);

	htItem = TreeView_GetParent( m_hwndTreeView, htChildItem );

	if (htItem)
	{

		tvi.mask            = TVIF_PARAM;
		tvi.hItem           = htItem;

		TreeView_GetItem(m_hwndTreeView, &tvi);

		if (lpbt)
		{
			lpbt->dpid = ((LPBRANCHSTRUCT)(tvi.lParam))->dpid;
			lpbt->btType = ((LPBRANCHSTRUCT)(tvi.lParam))->btType;
		}

		return ((LPBRANCHSTRUCT) (tvi.lParam))->dpid;
	}

	return 0;

}

///////////////////////////////////////////////////////////////////////////////////////
void CGroupTree::OnBeginDrag(NM_TREEVIEW *lpnmtv) 
{ 
    HIMAGELIST himl;    // handle of image list 
	LPBRANCHSTRUCT	lp = NULL;
	int level = 0;
	UINT	xIndent = 0;
	HTREEITEM htItem = NULL;

 	lp = (LPBRANCHSTRUCT)lpnmtv->itemNew.lParam;
	m_bsDragging = *((LPBRANCHSTRUCT)(lpnmtv->itemNew.lParam));
	GetBranchStructOfParent( lpnmtv->itemNew.hItem, &m_bsParentOfDragging );

   // Tell the tree-view control to create an image to use 
    // for dragging. 
    himl = TreeView_CreateDragImage(m_hwndTreeView, lpnmtv->itemNew.hItem); 
 
    // Start the drag operation. 
	RECT rcItem;

	TreeView_GetItemRect(m_hwndTreeView, lpnmtv->itemNew.hItem, &rcItem, FALSE);

	htItem = lpnmtv->itemNew.hItem;

	do
	{
		htItem = TreeView_GetParent( m_hwndTreeView, htItem );
		level++;
	}
	while (htItem); 

	xIndent = TreeView_GetIndent( m_hwndTreeView ) * level;

    BOOL b = ImageList_BeginDrag(	himl, 0, 
									lpnmtv->ptDrag.x-rcItem.left - xIndent, 
									lpnmtv->ptDrag.y-rcItem.top); 
  
	// Hide the mouse cursor, and direct mouse input to the 
    // parent window. 

    ShowCursor( FALSE );
	SetCapture(m_hwndParent); 
    m_fDragging = TRUE;
	
	ImageList_DragEnter( m_hwndTreeView, 
						lpnmtv->ptDrag.x-rcItem.left - xIndent, 
						lpnmtv->ptDrag.y);
    return; 
} 

///////////////////////////////////////////////////////////////////////////////////////
void CGroupTree::OnMouseMove( LONG xCur, LONG yCur) 
{ 
    HTREEITEM htiTarget;  // handle of target item 
    TV_HITTESTINFO tvht;  // hit test information 
 
	TV_ITEM	tvi;

	ZeroMemory(&tvi, sizeof(TV_ITEM ) );

    if (m_fDragging) 
	{ 
 
        // Drag the item to the current position of the mouse cursor. 
		RECT rcTree, rcParent;

		GetWindowRect( m_hwndParent, &rcParent );
		GetWindowRect( m_hwndTreeView, &rcTree );
		ImageList_DragMove(xCur, yCur); 
 
        // Find out if the cursor is on the item. If it is, highlight 
        // the item as a drop target. 
        tvht.pt.x = xCur; 
        tvht.pt.y = yCur; 
        if ((htiTarget = TreeView_HitTest(m_hwndTreeView, &tvht)) != NULL) 
		{ 
	  		ImageList_DragLeave( m_hwndTreeView );
			TreeView_SelectDropTarget(m_hwndTreeView, htiTarget);
			ImageList_DragEnter( m_hwndTreeView, xCur, yCur);

			tvi.mask            = TVIF_PARAM;
			tvi.hItem           = htiTarget;

			TreeView_GetItem(m_hwndTreeView, &tvi);

		  	memcpy( &m_bsDropTarget, (LPBRANCHSTRUCT)(tvi.lParam), sizeof(BRANCHSTRUCT) );

		}
		else
		{
			ZeroMemory( &m_bsDropTarget, sizeof(BRANCHSTRUCT) );
		}
    } 
    return; 
} 
 
///////////////////////////////////////////////////////////////////////////////////////
void CGroupTree::OnLButtonUp(void) 
{ 
    if (m_fDragging) 
	{ 
        ImageList_EndDrag(); 
        ReleaseCapture(); 
	    ShowCursor( TRUE );
        m_fDragging = FALSE;
  		ImageList_DragLeave( m_hwndTreeView );
	
		if (m_bsDropTarget.dpid)
		{
			switch (m_bsDragging.btType )
			{
				case BT_PLAYER:
					m_lpDP3A->AddPlayerToGroup(m_bsDropTarget.dpid, m_bsDragging.dpid ); 
					break;

				case BT_GROUP:
					m_lpDP3A->AddGroupToGroup(m_bsDropTarget.dpid, m_bsDragging.dpid );
					break;

				case BT_PLAYER_IN_GROUP:
					if (m_bsDropTarget.dpid != m_bsParentOfDragging.dpid)
					{
						m_lpDP3A->AddPlayerToGroup(m_bsDropTarget.dpid, m_bsDragging.dpid );
						m_lpDP3A->DeletePlayerFromGroup(m_bsParentOfDragging.dpid, m_bsDragging.dpid ); 
					}
					break;

				case BT_SHORTCUT_IN_GROUP:
					if (m_bsDropTarget.dpid != m_bsParentOfDragging.dpid)
					{
						m_lpDP3A->AddGroupToGroup(m_bsDropTarget.dpid, m_bsDragging.dpid ); 
						m_lpDP3A->DeleteGroupFromGroup(m_bsParentOfDragging.dpid, m_bsDragging.dpid ); 
					}
					break;
			}
		}

		TreeView_SelectDropTarget( m_hwndTreeView, (HTREEITEM) NULL );
    } 
    return; 
} 


///////////////////////////////////////////////////////////////////////////////////////
void CGroupTree::Redraw(void) 
{
	RECT r;
	
	GetWindowRect(m_hwndTreeView, &r );
	InvalidateRect(m_hwndTreeView, &r, TRUE);
	UpdateWindow(m_hwndParent);

}

///////////////////////////////////////////////////////////////////////////////////////
void CGroupTree::OnRButtonDown( LONG xCur, LONG yCur) 
{ 
    HTREEITEM htiTarget;  // handle of target item 
    TV_HITTESTINFO tvht;  // hit test information 
	LPBRANCHSTRUCT lpbs = NULL;
	HMENU hMenu = NULL;
 
	TV_ITEM	tvi;

	ZeroMemory(&tvi, sizeof(TV_ITEM ) );
	RECT rc;

	GetWindowRect( m_hwndTreeView, &rc );

    // Find out if the cursor is on the item. If it is, highlight 
    // the item as a drop target. 
    tvht.pt.x = xCur - rc.left; 
    tvht.pt.y = yCur - rc.top; 
    if ((htiTarget = TreeView_HitTest(m_hwndTreeView, &tvht)) != NULL) 
	{ 
		TreeView_SelectItem(m_hwndTreeView, htiTarget);

		tvi.mask            = TVIF_PARAM;
		tvi.hItem           = htiTarget;

		TreeView_GetItem(m_hwndTreeView, &tvi);

		if (lpbs = (LPBRANCHSTRUCT)tvi.lParam)
		{
			m_dpidMenuTarget = lpbs->dpid;

			switch (lpbs->btType)
			{
			case BT_GROUP:
				hMenu = m_hGroupMenu;
				EnableMenuItem(	hMenu,	ID_GROUP_STARTSESSION,	
					(DPGROUP_STAGINGAREA & lpbs->dwFlags)?MF_ENABLED:MF_GRAYED ); 
				EnableMenuItem(	hMenu,	ID_GROUP_CONNECTIONSETTINGS,	
					(DPGROUP_STAGINGAREA & lpbs->dwFlags)?MF_ENABLED:MF_GRAYED ); 
				break;

			case BT_PLAYER:
				hMenu = m_hPlayerMenu;
				break;

			case BT_SHORTCUT_IN_GROUP:
				hMenu = m_hShortcutMenu;
				break;

			case BT_PLAYER_IN_GROUP:
				hMenu = m_hPlayerInGroupMenu;
				break;

			default:
				hMenu = m_hRootMenu;
				break;
			}
		}
	}
	else
	{
			hMenu = m_hRootMenu;
	}

	TrackPopupMenuEx(	hMenu,	
						TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, 
						xCur, yCur, m_hwndParent, NULL );	
} 

///////////////////////////////////////////////////////////////////////////////////////
void CGroupTree::OnDblClk( LONG xCur, LONG yCur) 
{ 
    HTREEITEM htiTarget;  // handle of target item 
    TV_HITTESTINFO tvht;  // hit test information 
	LPBRANCHSTRUCT lpbs = NULL;
	HMENU hMenu = NULL;
 
	TV_ITEM	tvi;

	ZeroMemory(&tvi, sizeof(TV_ITEM ) );
	RECT rc;

	GetWindowRect( m_hwndTreeView, &rc );

    // Find out if the cursor is on the item. If it is, highlight 
    // the item as a drop target. 
    tvht.pt.x = xCur - rc.left; 
    tvht.pt.y = yCur - rc.top; 
    if ((htiTarget = TreeView_HitTest(m_hwndTreeView, &tvht)) != NULL) 
	{ 
		TreeView_SelectItem(m_hwndTreeView, htiTarget);

		tvi.mask            = TVIF_PARAM;
		tvi.hItem           = htiTarget;

		TreeView_GetItem(m_hwndTreeView, &tvi);

		if (lpbs = (LPBRANCHSTRUCT)tvi.lParam)
		{
			m_dpidMenuTarget = lpbs->dpid;

			switch (lpbs->btType)
			{
			case BT_SHORTCUT_IN_GROUP:
			case BT_GROUP:
				if (m_dpidLastGroup != lpbs->dpid)
				{
					m_lpDP3A->AddPlayerToGroup(lpbs->dpid, m_dpidPlayer );

					m_lpDP3A->DeletePlayerFromGroup(m_dpidLastGroup, m_dpidPlayer ); 
					m_dpidLastGroup = lpbs->dpid;
				}
				break;

			default:
				break;
			}
		}
	}
} 

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CGroupTree::BeginLabelEdit() 
{
	// Workaround for Windows tree control/dialog odd behavior
	// Retrieve the handle of the edit control. 
	m_hwndEditCtrl = TreeView_GetEditControl( m_hwndTreeView ); 

	// Subclass the edit control. 
	gwpOrigEditProc = (WNDPROC) SetWindowLong(m_hwndEditCtrl, GWL_WNDPROC, (LONG) EditCtrlSubProc );

	return DP_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
void CGroupTree::EndLabelEdit( TV_DISPINFO FAR * lpTVDisp ) 
{
	HRESULT hr;

	// Subclass the edit control. 
	SetWindowLong(m_hwndEditCtrl, GWL_WNDPROC, (LONG) gwpOrigEditProc);

	if (lpTVDisp->item.pszText)
	{
		LPBRANCHSTRUCT lpbs = (LPBRANCHSTRUCT) lpTVDisp->item.lParam;

		hr = CheckAccessRights(lpTVDisp);

		if (SUCCEEDED(hr))
		{	
			DPNAME dpn;
			dpn.dwSize = sizeof(DPNAME);
			dpn.lpszShortNameA = lpTVDisp->item.pszText;
			dpn.lpszLongNameA = lpTVDisp->item.pszText;

			switch (lpbs->btType)
			{
			case  BT_GROUP:
				m_lpDP3A->SetGroupName(lpbs->dpid, &dpn, DPSET_REMOTE );
				break;

			case BT_PLAYER_IN_GROUP:
			case BT_PLAYER:
				m_lpDP3A->SetPlayerName(lpbs->dpid, &dpn,  DPSET_REMOTE );
				break;
			}
		}
		else
		{
			MessageBox( m_hwndParent, "Cannot change the name of remote players or groups", "Error", MB_OK);
			return;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////
DPID CGroupTree::GetBranchStructOfParent( HTREEITEM htChildItem, LPBRANCHSTRUCT lpbt)
{

	HTREEITEM	htItem;
	TV_ITEM	tvi;

	ZeroMemory( &tvi, sizeof( TV_ITEM ) );
	ZeroMemory( lpbt, sizeof( BRANCHSTRUCT ) );

	htItem = TreeView_GetParent( m_hwndTreeView, htChildItem );

	if (htItem)
	{

		tvi.mask            = TVIF_PARAM;
		tvi.hItem           = htItem;

		TreeView_GetItem(m_hwndTreeView, &tvi);

		if (lpbt)
		{
			*lpbt = *((LPBRANCHSTRUCT)(tvi.lParam));
		}

		return ((LPBRANCHSTRUCT) (tvi.lParam))->dpid;
	}

	return 0;

}

///////////////////////////////////////////////////////////////////////////////////////
BOOL CGroupTree::OnWM_NOTIFY( WPARAM wParam, LPARAM lParam )
{
	int idCtrl = (int) wParam;
	LPNMHDR pnmh = (LPNMHDR)lParam;
	if (NULL == pnmh)
		return FALSE;
  	NM_TREEVIEW		*nmtv;
	TV_ITEM			*	pItemNew = NULL;
	TV_ITEM			*	pItemOld = NULL;
	LPBRANCHSTRUCT	lpBranch = NULL;
	HRESULT hr;

	switch(pnmh->code)
	{
		case NM_RCLICK:
		{
			POINT p;
			GetCursorPos(&p);
			OnRButtonDown(p.x, p.y );
		}
		break;

		case NM_DBLCLK:
		{
			POINT p;
			GetCursorPos(&p);
			OnDblClk(p.x, p.y );
		}
		break;

		case TVN_BEGINLABELEDIT:
			hr = BeginLabelEdit();

			if (FAILED(hr))
				return TRUE;
		break;

		case TVN_ENDLABELEDIT:
			EndLabelEdit((TV_DISPINFO FAR *) lParam);
		break;

		case TVN_SELCHANGING:
		break;

		case TVN_DELETEITEM:
			nmtv	= (NM_TREEVIEW *)lParam;
			pItemOld	= &nmtv->itemOld;
			LocalFree( (LPVOID) pItemOld->lParam );
		break;

		case TVN_BEGINDRAG: 
			OnBeginDrag((NM_TREEVIEW *) lParam); 
			break; 

	}

	return 0;
}

HRESULT	CGroupTree::EditLabel()
{
	HRESULT hr; // Initialized by call to CheckAccessRights()
	HTREEITEM	htItem;
	TV_ITEM	tvi;

	ZeroMemory( &tvi, sizeof( TV_ITEM ) );

	htItem = TreeView_GetSelection(m_hwndTreeView);

	if (htItem)
	{
		HWND hwnd = NULL;

		hwnd = TreeView_EditLabel( m_hwndTreeView, htItem );
		hr = (hwnd ? DP_OK : DPERR_ACCESSDENIED); 
	}
	else
	{
		hr = DPERR_ACCESSDENIED;
	}

	return hr;
}


HRESULT CGroupTree::CheckAccessRights(TV_DISPINFO FAR * lpTVDisp)
{
	HRESULT hr = DPERR_GENERIC;
	DWORD	dwFlags = 0;
	BRANCHSTRUCT bsCurSel;

	if (NULL == lpTVDisp)
	{
		GetDPIDOfCurrentSelection( &bsCurSel );
	}
	else
	{	
		bsCurSel = *((LPBRANCHSTRUCT) lpTVDisp->item.lParam);
	}

	switch ( bsCurSel.btType )
	{
		case BT_PLAYER:
		case BT_PLAYER_IN_GROUP:
			hr = m_lpDP3A->GetPlayerFlags( bsCurSel.dpid, &dwFlags );
			break;

		case BT_GROUP:
			hr = m_lpDP3A->GetGroupFlags( bsCurSel.dpid, &dwFlags );
			break;

		default:
			break;
	}

	if (FAILED(hr))
		return hr;

	if (dwFlags & DPPLAYER_LOCAL )
	{
		hr = DP_OK;
	}
	else
	{
		hr = DPERR_ACCESSDENIED;
	}

	return hr;
}

