/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// WNDTABS SDK - Public Definitions

#ifndef __WTSDKDEFS_H
#define __WTSDKDEFS_H

// DevStudio Automation Headers
#include <ObjModel\addguid.h>
#include <ObjModel\appguid.h>
#include <ObjModel\bldguid.h>
#include <ObjModel\textguid.h>
#include <ObjModel\textauto.h>
#include <ObjModel\dbgguid.h>


struct WTSDK_CommandContext
{
    UINT    cbSize;     /* set to size of this structure */
    BOOL    bHasDoc;
    BOOL    bHasFile;
    BOOL    bIsTextWindow;
    BOOL    bIsActiveWindow;
    BOOL    bIsGroupOperation;
    HWND    hWnd;
    char    szFullPath[MAX_PATH];
    CComPtr<IGenericWindow>    pWindow;
    CComPtr<IGenericDocument>  pDoc;

    int     iTab;  // the tab associated with this command (or -1)
};


enum WTSDK_UIUpadateFlags 
{
    UI_AlwaysAvailable     = 0,

    UI_MustHaveFile        = 1,  // was already saved at least once, i.e.
                                 //  not a new text window 

    UI_MustHaveDoc         = 2,  // any editable window - windows such as
                                 //  "Disassembly" don't have a doc 

    UI_MustHaveTextDoc     = 4,  // same as above, but must be a text 
                                 //  document (for instance, not a resource) 

    UI_MustHaveOpenWindows = 8,  // at least one window must be open

    UI_MustBeActiveWindow  = 16, // command applies only to active windows

    UI_UseCallback         = 128 // call user-defined UI update callback
};


struct WTSDK_CommandDef
{
    int     iCmd;       // the identifier for your command
    LPCSTR  pszName;    // the display name for your command
    int     idBmpRes;   // the resource ID for the menu bitmap (or -1)
    WTSDK_UIUpadateFlags UIUpdateFlags;
};


// object for automatically managing a resource
typedef BOOL(__stdcall wtfreeresfn)(void *);
template <class restype, wtfreeresfn *freefn> 
class wt_auto_res
{
    restype m_hResource;
    bool    m_bAutoDelete;

public:
    wt_auto_res() : m_bAutoDelete(false), m_hResource(NULL) {}
    ~wt_auto_res() 
    { 
        if (m_bAutoDelete  &&  m_hResource) freefn(m_hResource); 
    }

    void Set(restype hRes, bool bAutoDelete)
    {
        if (m_bAutoDelete  &&  m_hResource) freefn(m_hResource);
        m_hResource   = hRes;
        m_bAutoDelete = bAutoDelete;
    }

    wt_auto_res& operator = (const wt_auto_res&op)
    {
        Set(op.m_hResource, false);
        return *this;
    }

    const restype& Get() const { return m_hResource; }
    restype& Get() { return m_hResource; }

    operator restype() const { return m_hResource; }
};

typedef wt_auto_res<HICON, (wtfreeresfn *)&::DestroyIcon> wt_auto_icon;


struct WTSDK_TabUpdateInfo
{
    WTSDK_TabUpdateInfo()
    {
        // WARNING: ZermMemory should not be used if future versions of this
        // object have a virtual method table!
        ZeroMemory(this, sizeof(*this));
        cbSize = sizeof(this);
    }


    UINT cbSize; // Must be set to sizeof(WTSDK_TabUpdateInfo)


    // == Modification Info/Flags ==

    // When stage==change, you should make any modifications to the structure 
    // that involve brute changes (i.e. replacing an icon).  
    // When stage==modify, you should make any modifications that involve
    // alterations (i.e. altering the icon).  This stage will always come
    // after the "change" stage.
    enum { change, modify } stage; 


    // == Text on Tab ==

    //  | WndTabs [1.cpp][2.h] | | 3.AddInInt.cpp |
    //  +----------------------+ +----------------+
    //    \=====/  \/\=/  \/|      \/\======/\==/
    //       b     p  s   p s      p     b     s
    //       a     r  u   r u      r     a     u
    //       s     e  f   e f      e     s     f
    //       e     f  f   f f      f     e     f
    //             i  i   i i      i           i
    //             x  x   x x      x           x
    int iTabNumber;     // the number (0 based index) of the tab - notice,
                        //   however, that the text indexes shown to the
                        //   user start at 1 (i.e. TextIdx==iTabNumber + 1)

    char szPrefix[256]; // the text before the file name (i.e. tab number)
    char szBase[512];   // the text that belongs to the tab's entire group
                        //   (the file name)
    char szSuffix[256]; // the text that is different for each tab in the 
                        //   group (the extension)

    // These are the texts without alterations - DO NOT CHANGE
    const char *pszOrigPrefix, *pszOrigBase, *pszOrigSuffix;


    // == Colors ==
    COLORREF    crTextColorSel;     // when tab is selected
    COLORREF    crTextColorNotSel;  // when tabs isn't selected

    // == Icons ==
    wt_auto_icon  hIcon;
    wt_auto_icon  hIconOverlay;
};


enum WndTabsEvents
{ 
    // WndTabs_Ev_WindowChanged
    // ------------------------
    // Called whenever the active window is changed (or if the last window is
    // closed).
    //
    // Extra parameter: The HWND of the new window (or NULL if there are no
    //                  open windows).
    //
    // NOTE: If the user changes/opens/closes windows very quickly (e.g. by
    // using Close All Windows or opening many files at once), an event might 
    // not be generated for every single window activation/deactivation!
    WndTabs_Ev_WindowChanged   = 0x01,

        
    // WndTabs_Ev_TabClicked
    // ---------------------
    // Called whenever a user left-clicks on a tab.  Note that this does not
    // necessarily mean that a window change will occur.
    //
    // Extra parameter: The number of the tab that was clicked (or -1 if 
    //                  there are no open windows).
    WndTabs_Ev_TabClicked      = 0x02
};

// callback types
typedef void (WTSDK_CmdEvFn)(int iCmd, 
    const WTSDK_CommandContext *pCmdContext);
typedef void (WTSDK_UIUpdateEvFn)
    (int iCmd, CCmdUI *pCmdUI, const WTSDK_CommandContext *pCmdContext);
typedef void (WTSDK_TabUpdateEvFn)(WTSDK_TabUpdateInfo *pTabUpdateInfo,
    const WTSDK_CommandContext *pCmdContext);
typedef void (WTSDK_EvNotificationFn)(WndTabsEvents event, int ExtraInfo);



// misc stuff
#ifndef countof
#define countof(arr) (sizeof(arr)/sizeof(arr[0]))
#endif



#endif // __WTSDKDEFS_H