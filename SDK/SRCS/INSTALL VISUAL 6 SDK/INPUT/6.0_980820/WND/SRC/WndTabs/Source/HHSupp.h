////////////////////////////////////////////////////////////////////
// HHSupp.h : HTML Help Support Module Header File
//

#ifndef __HHSUPPORT_H
#define __HHSUPPORT_H

#include <afxdlgs.h>


/* ============================================================== []
   Help ID Ranges and Their Meaning
   --------------------------------
   HHSupp defines a few special help ID ranges.  Help topics are 
   displayed differently, depending on which range the help ID 
   falls in:

     0x00000000-0x1FFFFFFF: Text Popups/Default HTML Window Type
         This range plays a double role, depending on the
         context of the help call.
         For dialog/property page controls with help IDs in this 
         range, a text popup is displayed (the control's help ID 
         should match a .Topic entry in the cshelp.txt file).
         When used with ShowHTMLHelp(), or when context help is
         called for a menu item, a full HTML topic will be 
         displayed using the default window type.

         NOTE: The 0x00000000-0x0000FFFF range is used by
         Windows/MFC for menu and dialog control command codes
         (for example, see your project's Resource.h file). 
         You should refrain from defining your own help IDs in 
         this range.

     0x20000000-0x2FFFFFFF: HTML Popups
         This range is reserved for dialog/property-page controls 
         that require a complex (HTML) popup.  This popup is 
         actually a regular HTML page in the .CHM file, but it is 
         displayed in a special window type.
         The default window type name (PopupTopicWnd) should be 
         defined in the help project file.  Alternatively, you can
         use a different window type name for this range by 
         setting the g_pszPopupWinTypeName variable.

     0x30000000-0x30FFFFFF: User Defined/Default Window Type
         The ID numbers in this range use window types registered
         with the RegisterHHWindowType() function.
         The type number is designated in the lower byte of the 
         high word, i.e. the number format is 0x30NNxxxx where NN 
         denotes the type number.
         When NN == 0, the default window type is used.

     0x31000000-0x30FFFFFF: Reserved

     0x40000000-0xFFFFFFFF: Default Window Type
         This range gets no special treatment.  Topics with help 
         IDs in this range are displayed using the .CHM's default 
         window type.
[] ============================================================== */

// g_pszPopupWinTypeName points to the name of the default HH window
// type used with help IDs in the range 0x20000000...0x2FFFFFFF
extern LPCTSTR g_pszPopupWinTypeName;

// true/false: display a popup error message when no help ID is 
// available for a control (default: true)
extern bool g_bHTMLHelp_ShowNoHelpMessage;

// APP_CHM: When passed as the pszFile parameter for HHSupp's 
// implementation of the HtmlHelp() function, the application's
// default .chm file is used.
#define APP_CHM   ((LPCTSTR)-1)


/* ============================================================== []
   WinHelpToHTMLHelp() - Translates MFC WinHelp calls to 
   equivalent HTML Help calls.  Use the ClassWizard to add the
   "WinHelp" message to your application class, and make sure it
   reads:
       WinHelpToHTMLHelp(this, dwData, nCmd); 
[] ============================================================== */

void WinHelpToHTMLHelp(CWinApp *pApp, DWORD dwData, UINT nCmd);


/* ============================================================== []
   ShowHTMLHelp() - Displays a help topic using the rules 
   described above ("Help ID Ranges and Their Meaning").  
[] ============================================================== */

void ShowHTMLHelp(HWND hWnd, DWORD helpID, 
    LPCTSTR pszHelpWndType = NULL, LPCTSTR pszHelpFile = APP_CHM);


/* ============================================================== []
   RegisterHHWindowType() - Registers window type for use with
   the 0x30NN0000 range.  (See "Help ID Ranges and Their Meaning"
   above).
[] ============================================================== */

bool RegisterHHWindowType(int n, LPCTSTR name);


/////////////////////////////////////////////////////////////////////////////
// Help ID Mapping Support

// you must include this macro somewhere in your dialog/prop. page
// definition to enable mapping support
#define DECLARE_HELP_IDS() \
private: \
    static const DWORD m_dwHelpIDs[]; \
protected: \
    virtual const DWORD *GetHelpIDs() { return m_dwHelpIDs; }

// use these two macros to declare your ID map, i.e.
//      BEGIN_HELP_IDS(CMyDialog)
//          IDC_LEFT,   IDH_DIRECTIONS,
//          IDC_RIGHT,  IDH_DIRECTIONS
//      END_HELP_IDS()
#define BEGIN_HELP_IDS(theClass) \
    const DWORD theClass::m_dwHelpIDs[] = {
#define END_HELP_IDS() \
    ,0 , 0 };


/////////////////////////////////////////////////////////////////////////////
// Common definitions for HTML Help base classes

#define DECLARE_HTMLHELPBASE(classname, baseclass)                 \
protected:                                                         \
    afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);                  \
	afx_msg void OnContextMenu(CWnd*, CPoint point);               \
    afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);   \
    afx_msg void OnIDHelp();                                       \
    DECLARE_MESSAGE_MAP()                                          \
                                                                   \
    DECLARE_HELP_IDS();                                            \
                                                                   \
    DECLARE_DYNCREATE(classname)                                   \
                                                                   \
public:                                                            \
    bool m_bAllowImplicit;                                         \
    int  m_iHelpID;                                                \
                                                                   \
    classname() : baseclass() {}
    


/////////////////////////////////////////////////////////////////////////////
// CHHDialog

class CHHDialog : public CDialog
{
// Construction
public:
    CHHDialog(UINT nIDTemplate, CWnd* pParent = NULL,
        bool bAllowImplicit = true, int iHelpID = -1) :
        m_bAllowImplicit(bAllowImplicit), m_iHelpID(iHelpID),
        CDialog(nIDTemplate, pParent) {}

    DECLARE_HTMLHELPBASE(CHHDialog, CDialog);
};


/////////////////////////////////////////////////////////////////////////////
// CHHPropPage

class CHHPropPage : public CPropertyPage
{
// Construction
public:
    CHHPropPage(UINT nIDTemplate, bool bAllowImplicit = true, 
        int iHelpID = -1, UINT nIDCaption = 0) : 
        m_bAllowImplicit(bAllowImplicit), m_iHelpID(iHelpID),
        CPropertyPage(nIDTemplate, nIDCaption) { CommonInit(); }

    CHHPropPage(LPCTSTR lpszTemplateName, bool bAllowImplicit = true, 
        int iHelpID = -1, UINT nIDCaption = 0) : 
        m_bAllowImplicit(bAllowImplicit), m_iHelpID(iHelpID),
        CPropertyPage(lpszTemplateName, nIDCaption) {CommonInit();}

    DECLARE_HTMLHELPBASE(CHHPropPage, CPropertyPage);

protected:
    void CommonInit();
};

/////////////////////////////////////////////////////////////////////////////
// CHHPropSheet

class CHHPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CHHPropSheet)
public:
	CHHPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, 
        UINT iSelectPage = 0, int iHelpID = -1) : 
        m_iHelpID(iHelpID),
        CPropertySheet(nIDCaption, pParentWnd, iSelectPage) {}
	CHHPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, 
        UINT iSelectPage = 0, int iHelpID = -1) :
        m_iHelpID(iHelpID),
        CPropertySheet(pszCaption, pParentWnd, iSelectPage) {}

    int m_iHelpID;

	virtual int DoModal();

    // NOTE: This function is *not* virtual in the base class, so
    // calling ((CPropertySheet *)mysheet)->AddPage() will not set
    // set the help ID correctly for pages created after DoModal().
    // Instead, use ((CHHPropSheet *)mysheet)->AddPage()
    void AddPage(CHHPropPage* pPage);

protected:
	DECLARE_MESSAGE_MAP()
    virtual BOOL OnInitDialog();
};

/////////////////////////////////////////////////////////////////////////////


#endif // __HHSUPPORT_H
