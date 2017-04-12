//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This source code is a part of BCGControlBar library.
// You may use, compile or redistribute it as part of your application 
// for free. You cannot redistribute it as a part of a software development 
// library without the agreement of the author. If the sources are 
// distributed along with the application, you should leave the original 
// copyright notes in the source code without any changes.
// This code can be used WITHOUT ANY WARRANTIES on your own risk.
// 
// For the latest updates to this library, check my site:
// http://welcome.to/bcgsoft
// 
// Stas Levin <bcgsoft@yahoo.com>
//*******************************************************************************

#if !defined(AFX_BCGCOMMANDMANAGER_H__C089C790_8038_11D3_A9E7_005056800000__INCLUDED_)
#define AFX_BCGCOMMANDMANAGER_H__C089C790_8038_11D3_A9E7_005056800000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * This class is responsible for:
 * - knowledge about all commands
 * - images for all commands
 * - command categories
 * - default toolbars
 */

#include "bcgcontrolbar.h"
#include "BCGToolBarImages.h"
#include "BCGToolbarButton.h"
#include "CmdUsageCount.h"

class CBCGCommandManager;

BCGCONTROLBARDLLEXPORT CBCGCommandManager* GetCmdMgr();
#define CMD_MGR (*GetCmdMgr())

#ifndef _NO_BCG_LEGACY_
class BCGCONTROLBARDLLEXPORT CImageHash
{
public:
	static UINT	GetImageOfCommand(UINT nID, BOOL bUser = false);
};
#endif

class BCGCONTROLBARDLLEXPORT CBCGCommandManager
{
friend class _STATIC_CREATOR_;
protected:
	CBCGCommandManager();

public:
	virtual ~CBCGCommandManager();

	//----------------------------------------------------------------
	// Set toolbar buttons image resources.
	// You should use SINGLE CBCGToolBarImages for ALL your toolbars!
	//----------------------------------------------------------------
	BOOL SetUserImages (CBCGToolBarImages* pUserImages);

	//------------------------------
	// Clear all images except user:
	//------------------------------
	void ResetAllImages();
	
	void CleanUp ();	// Final cleaning

	BOOL LoadBitmap (UINT uiResID, UINT uiColdResID = 0, 
					UINT uiMenuResID = 0, BOOL bLocked = FALSE,
					UINT uiDisabledResID = 0, UINT uiMenuDisabledResID = 0);
	BOOL LoadToolBar (UINT uiResID, UINT uiColdResID = 0, 
					UINT uiMenuResID = 0, BOOL bLocked = FALSE,
					UINT uiDisabledResID = 0, UINT uiMenuDisabledResID = 0);


	BOOL IsLastCommandFromButton (CBCGToolbarButton* pButton);
	BOOL AddToolBarForImageCollection (UINT uiResID);

	void SetNonPermittedCommands (CList<UINT, UINT>& lstCommands);
	BOOL IsCommandPermitted (UINT uiCmd)
	{
		return m_lstUnpermittedCommands.Find (uiCmd) == NULL;
	}

	void SetBasicCommands (CList<UINT, UINT>& lstCommands);	
	BOOL IsBasicCommand (UINT uiCmd)
	{
		return m_lstBasicCommands.Find (uiCmd) != NULL;
	}

	BOOL IsCommandRarelyUsed (UINT uiCmd);
	void AddCommandUsage (UINT uiCommand)
	{
		m_UsageCount.AddCmd (uiCommand);
	}

	CBCGToolBarImages* GetImages ()
	{
		return &m_Images;
	}
	CBCGToolBarImages* GetUserImages ()
	{
		return m_pUserImages;
	}

	int GetDefaultImage (UINT uiID)
	{
		int iImage;
		if (m_DefaultImages.Lookup (uiID, iImage))
		{
			return iImage;
		}

		return -1;
	}

/*
	virtual BOOL LoadState (LPCTSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT) -1);
	virtual BOOL SaveState (LPCTSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT) -1);
	virtual BOOL RemoveStateFromRegistry (LPCTSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT) -1);

	virtual BOOL RestoreOriginalstate ();
*/

	// Image functions
	void SetCmdImage (UINT uiCmd, int iImage, BOOL bUserImage);
	int  GetCmdImage (UINT uiCmd, BOOL bUserImage) const;
	void ClearCmdImage (UINT uiCmd);
	void ClearAllCmdImages ();

protected:
	CMap<UINT, UINT, int, int>	m_CommandIndex;
	CMap<UINT, UINT, int, int>	m_CommandIndexUser;
	CMap<UINT, UINT, int, int>	m_DefaultImages;

	CCmdUsageCount				m_UsageCount;
	
	UINT m_iImagesOffset;

	CList<UINT, UINT>	m_lstUnpermittedCommands;
	CList<UINT, UINT>	m_lstBasicCommands;

	// Image store
	CBCGToolBarImages	m_Images;				// Shared toolbar images
	CBCGToolBarImages	m_ColdImages;			// Shared toolbar "cold" images
	CBCGToolBarImages	m_DisabledImages;		// Shared disabled images

	CBCGToolBarImages	m_ImagesBig;			// Shared toolbar images
	CBCGToolBarImages	m_ColdImagesBig;		// Shared toolbar "cold" images
	CBCGToolBarImages	m_DisabledImagesBig;	// Shared disabled images

	CBCGToolBarImages*	m_pUserImages;			// Shared user-defined images
	CBCGToolBarImages*	m_pUserImagesBig;		// Shared user-defined images

	CBCGToolBarImages	m_MenuImages;			// Shared menu images
	CBCGToolBarImages	m_DisabledMenuImages;	// Shared disabled menu images
};

#endif // !defined(AFX_BCGCOMMANDMANAGER_H__C089C790_8038_11D3_A9E7_005056800000__INCLUDED_)
