// peview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPEView view



class CPEView : public CFileView
{

public:
	CPEView();           // protected constructor used by dynamic creation
	virtual ~CPEView();
    DECLARE_DYNCREATE(CPEView)

// Attributes
public:

// Operations
public:

// helper functions


void DetermineCharacteristics(WORD wCharacteristics,ANYELEMENT *aTags,WORD wLength);
void DumpDataDirectories(PIMAGE_DATA_DIRECTORY pDataDirectories,int iSize,char *szTemplate[]);
void DumpSectionTable(PIMAGE_SECTION_HEADER section,unsigned cSections,BOOL IsEXE);
CPEView *GetDLLPane();
char *GetDLLName();
static BOOL IsMyKindOfFile(BYTE *lpImage);



PIMAGE_SECTION_HEADER GetSectionHdrByName (LPVOID lpImage,char *szSection);
//LPVOID	ImageDirectoryOffset (LPVOID lpFile,DWORD dwIMAGE_DIRECTORY);

// code stolen from Matt Pietrek

void DumpResourceDirectory(PIMAGE_RESOURCE_DIRECTORY,DWORD,DWORD,DWORD);
void DumpResourceEntry(PIMAGE_RESOURCE_DIRECTORY_ENTRY,DWORD,DWORD);
void GetResourceNameFromId(DWORD,DWORD,PSTR,UINT);
void GetResourceTypeName(DWORD type, PSTR buffer, UINT cBytes);
void DumpImportsSection(char *base, PIMAGE_SECTION_HEADER pHeader);
void DumpExportsSection(char *base, PIMAGE_SECTION_HEADER pHeader);
void DumpDebugDirectory(char *base, PIMAGE_SECTION_HEADER pHeader, IMAGE_DATA_DIRECTORY va_debug_dir);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPEView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL
    void DispatchDoubleClick(int iVal);


// Implementation
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPEView)
    afx_msg long OnLoadDLL(WPARAM wParam, LPARAM lParam);
	afx_msg long OnRefresh(WPARAM wParam, LPARAM lParam);
	afx_msg void OnFileExecute();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
