//
// The class ID of this Shell extension class.
//
// class id:  87b9bd00-c65c-11cd-a259-00dd010e8c28
//
//
// NOTE!!!  If you use this shell extension as a starting point, 
//          you MUST change the GUID below.  Simply run UUIDGEN.EXE
//          to generate a new GUID.
//
                                  
#define ODS(sz) OutputDebugString(sz)

#ifndef _SHELLEXT_H
#define _SHELLEXT_H

DEFINE_GUID(CLSID_ShellExtension, 0x87b9bd00L, 0xc65c, 0x11cd, 0xa2, 0x59, 0x00, 0xdd, 0x01, 0x0e, 0x8c, 0x28 );

// this class factory object creates context menu handlers for Windows 95 shell
class CShellExtClassFactory : public IClassFactory
{
protected:
	ULONG	m_cRef;

public:
	CShellExtClassFactory();
	~CShellExtClassFactory();

	//IUnknown members
	STDMETHODIMP			QueryInterface(REFIID, LPVOID FAR *);
	STDMETHODIMP_(ULONG)	AddRef();
	STDMETHODIMP_(ULONG)	Release();

	//IClassFactory members
	STDMETHODIMP		CreateInstance(LPUNKNOWN, REFIID, LPVOID FAR *);
	STDMETHODIMP		LockServer(BOOL);

};
typedef CShellExtClassFactory *LPCSHELLEXTCLASSFACTORY;

// this is the actual OLE Shell context menu handler
class CShellExt : public IContextMenu, 
                         IShellExtInit, 
                         IExtractIcon, 
                         IPersistFile, 
                         IShellPropSheetExt,
                         ICopyHook
{
public:
    char         m_szPropSheetFileUserClickedOn[MAX_PATH];  //This will be the same as
                                                            //m_szFileUserClickedOn but I include
                                                            //here for demonstration.  That is,
                                                            //m_szFileUserClickedOn gets filled in
                                                            //as a result of this sample supporting
                                                            //the IExtractIcon and IPersistFile
                                                            //interface.  If this sample *only* showed
                                                            //a Property Sheet extesion, you would
                                                            //need to use the method I do here to find
                                                            //the filename the user clicked on.


protected:
	ULONG        m_cRef;
	LPDATAOBJECT m_pDataObj;
    char         m_szFileUserClickedOn[MAX_PATH];

	STDMETHODIMP DoGAKMenu1(HWND hParent, 
	                        LPCSTR pszWorkingDir, 
	                        LPCSTR pszCmd,
                            LPCSTR pszParam, 
                            int iShowCmd);

	STDMETHODIMP DoGAKMenu2(HWND hParent, 
	                        LPCSTR pszWorkingDir, 
	                        LPCSTR pszCmd,
                            LPCSTR pszParam, 
                            int iShowCmd);

	STDMETHODIMP DoGAKMenu3(HWND hParent, 
	                        LPCSTR pszWorkingDir, 
	                        LPCSTR pszCmd,
                            LPCSTR pszParam, 
                            int iShowCmd);

	STDMETHODIMP DoGAKMenu4(HWND hParent, 
	                        LPCSTR pszWorkingDir, 
	                        LPCSTR pszCmd,
                            LPCSTR pszParam, 
                            int iShowCmd);
public:
	CShellExt();
	~CShellExt();

	//IUnknown members
	STDMETHODIMP			QueryInterface(REFIID, LPVOID FAR *);
	STDMETHODIMP_(ULONG)	AddRef();
	STDMETHODIMP_(ULONG)	Release();

	//IShell members
	STDMETHODIMP			QueryContextMenu(HMENU hMenu,
	                                         UINT indexMenu, 
	                                         UINT idCmdFirst,
                                             UINT idCmdLast, 
                                             UINT uFlags);

	STDMETHODIMP			InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi);

	STDMETHODIMP			GetCommandString(UINT idCmd, 
	                                         UINT uFlags, 
	                                         UINT FAR *reserved, 
                                             LPSTR pszName, 
                                             UINT cchMax);

	//IShellExtInit methods
	STDMETHODIMP		    Initialize(LPCITEMIDLIST pIDFolder, 
	                                   LPDATAOBJECT pDataObj, 
	                                   HKEY hKeyID);

    //IExtractIcon methods
    STDMETHODIMP GetIconLocation(UINT   uFlags,
                                 LPSTR  szIconFile,
                                 UINT   cchMax,
                                 int   *piIndex,
                                 UINT  *pwFlags);

    STDMETHODIMP Extract(LPCSTR pszFile,
                         UINT   nIconIndex,
                         HICON  *phiconLarge,
                         HICON  *phiconSmall,
                         UINT   nIconSize);

    //IPersistFile methods
    STDMETHODIMP GetClassID(LPCLSID lpClassID);

    STDMETHODIMP IsDirty();

    STDMETHODIMP Load(LPCOLESTR lpszFileName, DWORD grfMode);

    STDMETHODIMP Save(LPCOLESTR lpszFileName, BOOL fRemember);

    STDMETHODIMP SaveCompleted(LPCOLESTR lpszFileName);

    STDMETHODIMP GetCurFile(LPOLESTR FAR* lplpszFileName);

    //IShellPropSheetExt methods
    STDMETHODIMP AddPages(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam);
    
    STDMETHODIMP ReplacePage(UINT uPageID, 
                             LPFNADDPROPSHEETPAGE lpfnReplaceWith, 
                             LPARAM lParam);

    //ICopyHook method
    STDMETHODIMP_(UINT) CopyCallback(HWND hwnd, 
                                     UINT wFunc, 
                                     UINT wFlags, 
                                     LPCSTR pszSrcFile, 
                                     DWORD dwSrcAttribs,
                                     LPCSTR pszDestFile, 
                                     DWORD dwDestAttribs);

};
typedef CShellExt *LPCSHELLEXT;

#endif // _SHELLEXT_H
