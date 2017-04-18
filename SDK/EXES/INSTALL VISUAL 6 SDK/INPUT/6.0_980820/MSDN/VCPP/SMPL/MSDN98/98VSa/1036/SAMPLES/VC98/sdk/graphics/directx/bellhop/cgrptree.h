#ifndef __CGRPTREE__
#define __CGRPTREE__

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <dplay.h>
#include <dplobby.h>
#include "resource.h"

//#DEFINES
#define ST_NO_SUBGROUPS			0
#define ST_SEARCH_SUBGROUPS		1

class CGroupTree;

typedef enum {  BT_INVALID = 0,
				BT_GROUP,
				BT_SHORTCUT_IN_GROUP,
				BT_PLAYER_IN_GROUP,
				BT_PLAYER,
			 } BRANCH_TYPE;

typedef struct tagBRANCHSTRUCT
{
    DPID		dpid;
    BRANCH_TYPE	btType;
	DWORD		dwFlags;
} BRANCHSTRUCT, *LPBRANCHSTRUCT;

typedef struct tagENUMTREESTRUCT
{
    DPID			dpidParent;
	CGroupTree *	lpTree;
	BOOL			bRecursive;
} ENUMTREESTRUCT, *LPENUMTREESTRUCT;


class CGroupTree{
private:
	HINSTANCE		m_hInst;
	HWND			m_hwndTreeView;
	HWND			m_hwndParent;
	HWND			m_hwndEditCtrl;
	HIMAGELIST		m_hImageList;
	int				m_nStagingAreaImg;
	int				m_nGroupImg;
	int				m_nInGroupImg;
	int				m_nPlayerImg;
	int				m_nShortcutInGroupImg;
	int				m_nSpectatorImg;
	int				m_nSessionInProgressImg;
	BOOL			m_fDragging;
	BRANCHSTRUCT	m_bsParentOfDragging;
	BRANCHSTRUCT	m_bsDragging;
	BRANCHSTRUCT	m_bsDropTarget;
	HMENU			m_hMenu,
					m_hRootMenu,
					m_hGroupMenu,
					m_hPlayerMenu,
					m_hShortcutMenu,
					m_hPlayerInGroupMenu;
	DPID			m_dpidMenuTarget;
	DPID			m_dpidPlayer;
	DPID			m_dpidLastGroup;

private:
	HTREEITEM FindItem( HTREEITEM htiSearchRoot, 
						DPID dpidTarget, 
						BRANCH_TYPE bt, 
						DWORD dwSearch );
	HTREEITEM Insert(	HTREEITEM htiParent, 
						DPID dpID, 
						LPSTR lpShortNameA, 
						BRANCH_TYPE bt, DWORD dwFlags );
	HRESULT	RecursiveRename(	HTREEITEM htiSearchRoot, 
								DPID dpidTarget, 
								LPSTR lpszName );
	DPID	GetBranchStructOfParent( HTREEITEM htChildItem, LPBRANCHSTRUCT lpbt);

public:
	LPDIRECTPLAY3A	m_lpDP3A;

public:
	CGroupTree();
	~CGroupTree();

	BOOL	Init( HWND hWnd, LPDIRECTPLAY3A lpDP3A, DPID dpidPlayer );
	HRESULT CreateGroup( DPID dpidGroup,  LPSTR lpszShortNameA, DWORD dwFlags );
	HRESULT CreatePlayer( DPID dpidPlayer,  LPSTR lpszShortNameA, DWORD dwFlags );
	HRESULT DestroyGroup( DPID dpidGroup );
	HRESULT DestroyPlayer( DPID dpidPlayer );
	HRESULT CreateGroupInGroup( DPID dpidParentGroup, DPID dpidChildGroup, LPSTR lpszShortNameA, DWORD dwFlags );
	HRESULT AddPlayerToGroup(DPID dpidGroup, DPID dpidPlayer, DWORD dwFlags);
	HRESULT AddGroupToGroup( DPID dpidParentGroup, DPID dpidShortcut, DWORD dwFlags );
	HRESULT DeletePlayerFromGroup(DPID dpidGroup, DPID dpidPlayer );
	HRESULT DeleteGroupFromGroup( DPID dpidParentGroup, DPID dpidShortcut );
	HRESULT GetPlayerName( DPID dpidPlayerName, LPDPNAME * lplpName );
	HRESULT GetGroupName( DPID dpidGroupName, LPDPNAME * lplpName );
	DPID	GetDPIDOfCurrentSelection(LPBRANCHSTRUCT lpbt = NULL);
	DPID	GetDPIDOfCurrentSelectionParent( LPBRANCHSTRUCT lpbt = NULL);
	HRESULT	SetPlayerName( DPID dpidPlayer, LPSTR lpszShortName );
	HRESULT SetGroupName( DPID dpidPlayer, LPSTR lpszShortName );
	HRESULT Refresh( BOOL bRecursive = TRUE );
	BOOL	Update(LPVOID lpvMsg);
	void	OnBeginDrag(NM_TREEVIEW *lpnmtv); 
	void	OnMouseMove( LONG xCur, LONG yCur); 
	void	OnLButtonUp(void); 
	void	OnRButtonDown( LONG xCur, LONG yCur); 
	void	OnDblClk( LONG xCur, LONG yCur);
	void	Redraw();
	HRESULT	BeginLabelEdit(); 
	void	EndLabelEdit(TV_DISPINFO FAR * lpTVDisp );
	BOOL	OnWM_NOTIFY( WPARAM wParam, LPARAM lParam );
	HRESULT	EditLabel();
	HRESULT CheckAccessRights(TV_DISPINFO FAR * lpTVDisp = NULL);

};

#endif
