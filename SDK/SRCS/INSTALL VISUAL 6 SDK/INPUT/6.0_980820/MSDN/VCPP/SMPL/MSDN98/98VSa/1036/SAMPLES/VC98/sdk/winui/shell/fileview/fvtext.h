//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright  1994-1996  Microsoft Corporation.  All Rights Reserved.
//
//	PROGRAM: FVTEXT.H	
//
//	PURPOSE:   Classes that implement the CFileViewer object for integration
// with the Windows 95 Explorer.  Necessary modifications for a
// custom viewer marked with MODIFY 
//
//	PLATFORMS:	Windows 95
//
//	SPECIAL INSTRUCTIONS: 
//
//DO NOT USE THESE GUIDS:  These are for this sample ONLY
//File CLSID for the text compound file example:  this is nothing official.
//Forward class references

DEFINE_GUID(CLSID_SampleTextFile, 0x00021116, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

//MODIFY:  Define your custom FileViewer CLSID(s) here.
DEFINE_GUID(CLSID_FileViewerText, 0x00021117, 0, 0, 0xC0,0,0,0,0,0,0,0x46);

#ifndef _FVTEXT_H_
#define _FVTEXT_H_

class CImpIPersistFile;
typedef class CImpIPersistFile *PIMPIPERSISTFILE;

class CImpIFileViewer;
typedef class CImpIFileViewer *PIMPIFILEVIEWER;

//FVPROC.CPP
//MODIFY:  Window procedures for frame and viewport windows
long WINAPI FileViewerFrameProc(HWND, UINT, WPARAM, LPARAM);

//Extra bytes for frame
#define CBWNDEXTRAFRAME             sizeof(LPVOID)
#define FVWL_OBJECTPOINTER          0

/*
 * MODIFY:  Change viewport window procedure and defintions
 * to be specific to the file viewer in use.
 */
long WINAPI ViewportWndProc(HWND, UINT, WPARAM, LPARAM);

//Extra bytes for viewport
#define CBWNDEXTRAVIEWPORT          sizeof(LPVOID)
#define VPWL_OBJECTPOINTER          0


BOOL APIENTRY AboutProc(HWND, UINT, WPARAM, LPARAM);


//Child window IDs
#define ID_TOOLBAR                  50
#define ID_STATUSBAR                51
#define ID_VIEWPORT                 52


//Options for CFileViewer::FontChange.
typedef enum
    {
    VIEWFONT_SELECT=0,
    VIEWFONT_INCREASESIZE,
    VIEWFONT_DECREASESIZE
    } VIEWFONTOPTION;

/*
 * Limits to font sizes for the Font dialog.  The increase and
 * decrease buttons change the point size by different amounts
 * (FONTSIZEDELTA*) depending on the size of the current font
 * (where it falls in the FONTSIZETHRESHOLD*).  Note that these
 * values have to be multiplied by logical_pixels_per_inch/72
 * on the display to be accurate.  See CFileViewer::FontChange.
 *
 * Of course, there are better ways to do this that are font
 * specific.  This way works well for stock fonts (Arial, Courier
 * New, Times New Roman).
 */
#define FONTSIZETHRESHOLDMIN    4
#define FONTSIZETHRESHOLDLOW    32
#define FONTSIZETHRESHOLDMID    48
#define FONTSIZETHRESHOLDMAX    120
#define FONTSIZEDELTASMALL      2       //4 to 32pt
#define FONTSIZEDELTAMEDIUM     8       //32 to 48pt
#define FONTSIZEDELTALARGE      24      //48 to 120pt

//FVTEXT.CPP, FVINIT.CPP
/*
 * MODIFY:  Change this CFileViewer object to be more specific to
 * your implementations.  Specific parts are listed below.
 *
 * The CFileViewer object is implemented in its own class with its own
 * IUnknown to support aggregation.  It contains two interface
 * implementation objects (CImpIPersistFile and CImpIFileViewer)
 * to implement the externally exposed interfaces.
 */

class CFileViewer : public IUnknown
    {
    //Make any contained interfaces your friends
    friend class CImpIPersistFile;
    friend class CImpIFileViewer;

    friend long WINAPI FileViewerFrameProc(HWND, UINT, WPARAM, LPARAM);
    friend long WINAPI ViewportWndProc(HWND, UINT, WPARAM, LPARAM);

    protected:
        //NOTE:  These members usually need no modification
        ULONG               m_cRef;             //Object reference count

        LPUNKNOWN           m_pUnkOuter;        //Controlling unknown
        HINSTANCE           m_hInst;            //Module instance
        PFNDESTROYED        m_pfnDestroy;       //To call on closure
        LPFILEVIEWERSITE m_lpfsi;       // file viewer site

        CLSID               m_clsID;            //CLSID of this FileViewer
        LPSTR               m_pszPath;          //Path from IPersitFile::Load
        DWORD               m_grfMode;          //Open mode for the file
        BOOL                m_fLoadCalled;      //Load called already?
        BOOL                m_fShowInit;        //ShowInitialize called?

        BOOL                m_fClassReg;        //RegisterClass work?
        BOOL                m_fPostQuitMsg;     // Should destroy post quit
        HWND                m_hWnd;             //Main window
        HWND                m_hWndOld;          // Old Main window.
        HWND                m_hWndToolbar;      //Child windows
        HWND                m_hWndStatus;
        HWND                m_hWndViewport;
        HACCEL              m_hAccel;

        UINT                m_cyTools;          //Child window heights
        UINT                m_cyStatus;

        BOOL                m_fToolsVisible;    //Visible child windows.
        BOOL                m_fStatusVisible;

        PCStringTable       m_pST;              //Stringtable object
        PCStatusHelper      m_pSH;              //For WM_MENUSELECT

        //Interface implementations
        PIMPIPERSISTFILE    m_pIPersistFile;
        PIMPIFILEVIEWER     m_pIFileViewer;
        LPFVSHOWINFO        m_pvsi;

        /*
         * MODIFY:  Change these to your own FileViewer specifics.
         * The variables here are specific to text viewing.
         */
        HGLOBAL             m_hMemText;         //Loaded text.
        HFONT               m_hFont;            //Current viewport font
        int                 m_cyPPI;            //logical pix/inch
        int                 m_xPos;             //Scroll positions
        int                 m_yPos;

    protected:
        BOOL                FInitFrameControls(void);
        HRESULT             FileLoad(void);

        void                OnCommand(WORD, WORD, HWND);
        void                ChildrenResize(void);
        void                ViewportResize(void);
        BOOL                FOpenAs(void);
        LPSTR               PszToolTip(UINT);

        //MODIFY:  These may be irrelevant for a custom viewer
        void                ViewportScrollSet(void);
        void                FontChange(VIEWFONTOPTION);
        void                ReplaceWindowModeChange(void);
        BOOL                DropFiles(HDROP);

    public:
        CFileViewer(LPUNKNOWN, HINSTANCE, PFNDESTROYED);
        ~CFileViewer(void);

        HRESULT             Init(void);        //Called from IClassFactory::CreateInstance
        LPSTR               String(UINT);      //inline--see FVTEXT.CPP
        LPVOID              MemAlloc(ULONG);   //IMalloc helpers
        void                MemFree(LPVOID);

        //IFileViewer implementataions (called from CImpIFileViewer)
        STDMETHODIMP        FileShowInit(LPFILEVIEWERSITE lpfsi);
        STDMETHODIMP        FileShow(LPFVSHOWINFO pvsi);
        STDMETHODIMP        PrintTo(LPSTR, BOOL);


        //Non-delegating object IUnknown interface
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);
    };

typedef CFileViewer * PCFileViewer;



/*
 * Interface implementations for the CFileViewer object.
 */

//IPERFILE.CPP
class CImpIPersistFile : public IPersistFile
    {
    private:
        PCFileViewer    m_pObj;         //Back pointer to object
        LPUNKNOWN       m_pUnkOuter;    //Controlling unknown

    public:
        CImpIPersistFile(PCFileViewer, LPUNKNOWN);
        ~CImpIPersistFile(void);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IPersist members
        STDMETHODIMP GetClassID(LPCLSID);

        //IPersistFile members
        STDMETHODIMP IsDirty(void);
        STDMETHODIMP Load(LPCOLESTR, DWORD);
        STDMETHODIMP Save(LPCOLESTR, BOOL);
        STDMETHODIMP SaveCompleted(LPCOLESTR);
        STDMETHODIMP GetCurFile(LPOLESTR *);
    };




//IFILEVW.CPP
class CImpIFileViewer : public IFileViewer
    {
    private:
        PCFileViewer    m_pObj;         //Back pointer to object
        LPUNKNOWN       m_pUnkOuter;    //Controlling unknown

    public:
        CImpIFileViewer(PCFileViewer, LPUNKNOWN);
        ~CImpIFileViewer(void);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IFileViewer members
        STDMETHODIMP PrintTo(LPSTR, BOOL);
        STDMETHODIMP ShowInitialize(LPFILEVIEWERSITE lpfsi);
        STDMETHODIMP Show(LPFVSHOWINFO pvsi);
    };



#endif //_FVTEXT_H_
