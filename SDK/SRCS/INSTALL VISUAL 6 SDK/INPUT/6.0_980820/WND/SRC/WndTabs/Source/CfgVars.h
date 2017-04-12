/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

#include "resource.h"

// == configuration variable list - may be #included more than once == //

// general user options            
CFG_VAR(DoWizAtStartup,       int,      cfg_iDoWizAtStartup,       1)
CFG_VAR(UseWWhiz,             BOOL,     cfg_bUseWorkspaceUtils,    FALSE)
CFG_VAR(ShowAttribsTT,        BOOL,     cfg_bShowAttribsTT,        TRUE)
CFG_VAR(UseVA_RTF,            BOOL,     cfg_bUseVA_RTF,            FALSE)
CFG_VAR(MenuArrows,           BOOL,     cfg_bMenuArrows,           TRUE)
CFG_VAR(ReBarWidth,           int,      cfg_iReBarWidth,           48)
CFG_VAR(VerCheckLastDate,     int,      cfg_iVerCheckLastDate,     0)  
CFG_VAR(LastOptionTreeSel,    int,      cfg_iLastOptionTreeSel,    1)
CFG_STR(VerCheckLast,                   cfg_sVerCheckLast,         "")
CFG_STR(OptionsDlgTree,                 cfg_sOptionsDlgTree,       "1111111111111")

// tab general
CFG_VAR(AutoRefresh,          BOOL,     cfg_bAutoRefresh,          FALSE)
CFG_VAR(FixedRowCount,        BOOL,     cfg_bFixedRowCount,        FALSE)
CFG_VAR(Orientation,          int,      cfg_iOrientation,          soBottom)
CFG_VAR(Snap,                 int,      cfg_iSnap,                 ssMDI)
CFG_VAR(TabRows,              UINT,     cfg_iRows,                 1)
CFG_VAR(NoRaggedRight,        BOOL,     cfg_bNoRaggedRight,        FALSE)
CFG_VAR(RefreshInterval,      UINT,     cfg_iRefreshInterval,      50)

// tab display
CFG_VAR(DispRC,               BOOL,     cfg_bDispRC,               TRUE)
CFG_VAR(DispRID,              BOOL,     cfg_bDispRID,              TRUE)
CFG_VAR(DispResLang,          BOOL,     cfg_bDispResLang,          TRUE)
CFG_VAR(DispResType,          BOOL,     cfg_bDispResType,          TRUE)
CFG_VAR(ShowIcons,            BOOL,     cfg_bShowIcons,            TRUE)
CFG_VAR(ShowNumbers,          BOOL,     cfg_bShowNumbers,          TRUE)
CFG_VAR(StripExt,             BOOL,     cfg_bStripExt,             FALSE)
CFG_VAR(StripPath,            BOOL,     cfg_bStripPath,            TRUE)
CFG_VAR(FontType,             BOOL,     cfg_ftFontType,            ftSansSerif)
CFG_VAR(ButtonTabs,           BOOL,     cfg_bButtonTabs,           FALSE)      

// ordering
CFG_VAR(TabOrdering,          int,      cfg_TabOrdering,           toControlled)
CFG_VAR(Fill1To9,             BOOL,     cfg_bFill1To9,             TRUE)
CFG_VAR(PreserveNumbering,    BOOL,     cfg_bPreserveNumbering,    TRUE)
CFG_VAR(SaveTabNumbers,       BOOL,     cfg_bSaveTabNumbers,       TRUE)

// trimming
CFG_VAR(CharLimit,            int,      cfg_iCharLimit,            8)
CFG_VAR(LimitCharacter,       int,      cfg_LimitCharacter,        167)
CFG_VAR(LimitChars,           BOOL,     cfg_bLimitChars,           FALSE)
CFG_VAR(LimitIgnoreExt,       BOOL,     cfg_bLimitIgnoreExt,       TRUE)
CFG_VAR(LimitResChars,        BOOL,     cfg_bLimitResChars,        FALSE)
CFG_VAR(UseLimitChar,         BOOL,     cfg_bUseLimitChar,         TRUE)
CFG_VAR(TrimPrefixes,         BOOL,     cfg_bTrimPrefixes,         FALSE)
CFG_VAR(TrimSuffixes,         BOOL,     cfg_bTrimSuffixes,         FALSE)
CFG_VAR(UseTrimPrefixChar,    BOOL,     cfg_bUseTrimPrefixChar,    TRUE)
CFG_VAR(UseTrimSuffixChar,    BOOL,     cfg_bUseTrimSuffixChar,    TRUE)
CFG_VAR(TrimPrefixChar,       int,      cfg_TrimPrefixChar,        187)
CFG_VAR(TrimSuffixChar,       int,      cfg_TrimSuffixChar,        171)
CFG_STR(TrimablePrefixes,               cfg_sTrimablePrefixes,     "")
CFG_STR(TrimableSuffixes,               cfg_sTrimableSuffixes,     "")

// file/window management
CFG_VAR(UseWindowLimit,       BOOL,     cfg_bUseWindowLimit,       FALSE)
CFG_VAR(UseWindowLimitDbg,    BOOL,     cfg_bUseWindowLimitDbg,    FALSE)
CFG_VAR(WindowLimit,          UINT,     cfg_iWindowLimit,          10)
CFG_VAR(WindowLimitDbg,       UINT,     cfg_iWindowLimitDbg,       10)
CFG_VAR(LimitGroups,          BOOL,     cfg_bLimitGroups,          FALSE)
CFG_VAR(AutoCloseDbgWins,     BOOL,     cfg_bAutoCloseDbgWins,     FALSE)
CFG_VAR(OpenFolderUseExplore, BOOL,     cfg_bOpenFolderUseExplore, FALSE)
CFG_VAR(AutoOpenAlt,          BOOL,     cfg_bAutoOpenAlt,          FALSE)
CFG_STR(AutoCloseDirsDbg,               cfg_sAutoCloseDirsDbg,     "$(DS_INCLUDE);$(DS_SOURCE)")

// show "once" dialogs
CFG_VAR(ShowAddonWTXInfo,     BOOL,     cfg_bShowAddonWTXInfo,     TRUE)
CFG_VAR(ShowMultiUseReg,      BOOL,     cfg_bShowMultiUseReg,      TRUE)
CFG_VAR(ShowKeyBindingsWarn,  BOOL,     cfg_bShowKeyBindingsWarn,  TRUE)
CFG_VAR(ShowWWhizFlipWarn,    BOOL,     cfg_bShowWWhizFlipWarn,    TRUE)
CFG_VAR(ShowUnsubclassErr,    BOOL,     cfg_bShowUnsubclassErr,    TRUE)
 
// menu configuration
CFG_VAR(CascadingAddons,      BOOL,     cfg_bCascadingAddons,      TRUE)
CFG_VAR(SupressNoCmdAddons,   BOOL,     cfg_bSupressNoCmdAddons,   FALSE)
CFG_VAR(ShellKey,             int,      cfg_iShellKey,             VK_SHIFT)
CFG_VAR(MenuClip,             int,      cfg_iMenuClip,             2)
CFG_VAR(MenuDS,               int,      cfg_iMenuDS,               2)
CFG_VAR(MenuFileMan,          int,      cfg_iMenuFileMan,          2)
CFG_VAR(MenuWinMan,           int,      cfg_iMenuWinMan,           2)

// keyboard configuration
CFG_VAR(ModGoToTab,           WORD,     cfg_ModGoToTab,            HOTKEYF_CONTROL)
CFG_VAR(VKsGoToTab,           WORD,     cfg_VKsGoToTab,            VKS1To9)
CFG_VAR(InetKbdStopBuilds,    BOOL,     cfg_bInetKbdStopBuilds,    TRUE)
CFG_VAR(InetKbdBackForward,   int,      cfg_iInetKbdBackForward,   bfTabOrder)

// mouse configuration
CFG_VAR(MidBtnCommand,        WORD,     cfg_iMidBtnCommand,        IDC_CLOSE)

// language selection
CFG_STR(LangDll,                        cfg_sLangDLL,              "")

// WndTabsExt
CFG_VAR(WndTabsExtInUse,      BOOL,     g_bUseWndTabsExt,          FALSE)
CFG_VAR(DisableSplash,        BOOL,     cfg_bDisableSplash,        FALSE)
CFG_VAR(UseWTTabCtrl,         BOOL,     cfg_bUseWTTabCtrl,         TRUE)
CFG_VAR(WTXAllSpecial,        BOOL,     cfg_bWTXAllSpecial,        FALSE)
CFG_VAR(WTXCloseButton,       BOOL,     cfg_bWTXCloseButton,       TRUE)
CFG_VAR(GroupTabs,            BOOL,     cfg_bGroupTabs,            TRUE)
CFG_VAR(GroupDiffPaths,       BOOL,     cfg_bGroupDiffPaths,       TRUE)
CFG_VAR(GroupRes,             BOOL,     cfg_bGroupRes,             FALSE)
CFG_VAR(GroupPrj,             BOOL,     cfg_bGroupPrj,             FALSE)
CFG_VAR(ShowGroupDelim,       BOOL,     cfg_bShowGroupDelim,       TRUE)
CFG_VAR(SortMiniTB,           BOOL,     cfg_bSortMiniTB,           FALSE)
CFG_VAR(UseGroupOps,          BOOL,     cfg_bUseGroupOps,          TRUE)
CFG_VAR(UseRightMostDot,      BOOL,     cfg_bUseRightMostDot,      TRUE)
CFG_VAR(RegTxtColor,          COLORREF, cfg_RegTxtColor,           RGB(0, 0, 0))
CFG_VAR(SelTxtColor,          COLORREF, cfg_SelTxtColor,           RGB(0, 0, 255))
