/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// Commands.h : header file
//

#if !defined(AFX_COMMANDS_H__6A06C138_4748_11D1_BC91_0000010016A6__INCLUDED_)
#define AFX_COMMANDS_H__6A06C138_4748_11D1_BC91_0000010016A6__INCLUDED_

#include "WndTabsTypes.h"

class CCommands : 
    public CComDualImpl<ICommands, &IID_ICommands, &LIBID_WndTabs>, 
    public CComObjectRoot,
    public CComCoClass<CCommands, &CLSID_Commands>
{
protected:
    IApplication* m_pApplication;

public:
    CCommands();
    ~CCommands();
    void SetApplicationObject(IApplication* m_pApplication);
    IApplication* GetApplicationObject() { return m_pApplication; }
    void UnadviseFromEvents();

    static void Cleanup();

    BEGIN_COM_MAP(CCommands)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(ICommands)
    END_COM_MAP()
    DECLARE_NOT_AGGREGATABLE(CCommands)

protected:
    // This class template is used as the base class for the Application
    //  event handler object and the Debugger event handler object,
    //  which are declared below.
    template <class IEvents, const IID* piidEvents, const GUID* plibid,
        class XEvents, const CLSID* pClsidEvents>
    class XEventHandler :
        public CComDualImpl<IEvents, piidEvents, plibid>,
        public CComObjectRoot,
        public CComCoClass<XEvents, pClsidEvents>
    {
    public:
        BEGIN_COM_MAP(XEvents)
            COM_INTERFACE_ENTRY(IDispatch)
            COM_INTERFACE_ENTRY_IID(*piidEvents, IEvents)
        END_COM_MAP()
        DECLARE_NOT_AGGREGATABLE(XEvents)
        void Connect(IUnknown* pUnk)
        { VERIFY(SUCCEEDED(AtlAdvise(pUnk, this, *piidEvents, &m_dwAdvise))); }
        void Disconnect(IUnknown* pUnk)
        { AtlUnadvise(pUnk, *piidEvents, m_dwAdvise); }

        CCommands* m_pCommands;

    protected:
        DWORD m_dwAdvise;
    };

    // This object handles events fired by the Application object
    class XApplicationEvents : public XEventHandler<IApplicationEvents, 
        &IID_IApplicationEvents, &LIBID_WndTabs, 
        XApplicationEvents, &CLSID_ApplicationEvents>
    {
    public:
        // IApplicationEvents methods
        STDMETHOD(BeforeBuildStart)(THIS);
        STDMETHOD(BuildFinish)(THIS_ long nNumErrors, long nNumWarnings);
        STDMETHOD(BeforeApplicationShutDown)(THIS);
        STDMETHOD(DocumentOpen)(THIS_ IDispatch * theDocument);
        STDMETHOD(BeforeDocumentClose)(THIS_ IDispatch * theDocument);
        STDMETHOD(DocumentSave)(THIS_ IDispatch * theDocument);
        STDMETHOD(NewDocument)(THIS_ IDispatch * theDocument);
        STDMETHOD(WindowActivate)(THIS_ IDispatch * theWindow);
        STDMETHOD(WindowDeactivate)(THIS_ IDispatch * theWindow);
        STDMETHOD(WorkspaceOpen)(THIS);
        STDMETHOD(WorkspaceClose)(THIS);
        STDMETHOD(NewWorkspace)(THIS);
    };
    typedef CComObject<XApplicationEvents> XApplicationEventsObj;
    XApplicationEventsObj* m_pApplicationEventsObj;

    // This object handles events fired by the Application object
    class XDebuggerEvents : public XEventHandler<IDebuggerEvents, 
        &IID_IDebuggerEvents, &LIBID_WndTabs, 
        XDebuggerEvents, &CLSID_DebuggerEvents>
    {
    public:
        // IDebuggerEvents method
        STDMETHOD(BreakpointHit)(THIS_ IDispatch * pBreakpoint);
    };
    typedef CComObject<XDebuggerEvents> XDebuggerEventsObj;
    XDebuggerEventsObj* m_pDebuggerEventsObj;

public:
    BOOL DoHeaderFlip(CString cFullPath, BOOL bUseWorkspaceUtils = FALSE, 
        BOOL bSimulate = false, BOOL bShowWarnings = true);
    void DoOpenAsText(CString cFullName);
    void DoSetCurrDir(CString cFullName); 
    void FlashWindows(bool bAsterisksOnly = false) const;

    static bool IsWorkspaceOpening();

    static void ReadPositionsFile();
    static void WritePositionsFile();
    static CString m_sPositionsFile;
    static CString m_sWorkspacePath;

    struct Positions
    {
        struct tab_data
        {
            tab_data(const CString& s, int num) : cPath(s), iNumber(num) {};
            tab_data() : iNumber(-1) {}
            
            CString cPath;
            int     iNumber;
        };

        int                          iActiveTab;
        CArray<tab_data, tab_data&>  data;
    };
    static Positions m_Positions;

    void CycleGroup(int iDelta);

// ICommands methods
    STDMETHOD(WTHeaderFlip)(THIS);
    STDMETHOD(WTSetCurrDir)(THIS);
    STDMETHOD(WTOpenAsText)(THIS);
	STDMETHOD(WTHelp)      (THIS);
    STDMETHOD(WTAbout)     (THIS);
    STDMETHOD(WTOptions)   (THIS);
    STDMETHOD(WTRenumber)  (THIS);
    STDMETHOD(WTReorder)   (THIS);
    STDMETHOD(WTGoToTab1)  (THIS);
    STDMETHOD(WTGoToTab2)  (THIS);
    STDMETHOD(WTGoToTab3)  (THIS);
    STDMETHOD(WTGoToTab4)  (THIS);
    STDMETHOD(WTGoToTab5)  (THIS);
    STDMETHOD(WTGoToTab6)  (THIS);
    STDMETHOD(WTGoToTab7)  (THIS);
    STDMETHOD(WTGoToTab8)  (THIS);
    STDMETHOD(WTGoToTab9)  (THIS);
	STDMETHOD(WTGroupPrev) (THIS);
	STDMETHOD(WTGroupNext) (THIS);

protected:
    CString GetActiveDocumentName() const;
};

typedef CComObject<CCommands> CCommandsObj;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDS_H__6A06C138_4748_11D1_BC91_0000010016A6__INCLUDED)
