/*
 * SITE.H
 * View Site for Document Objects.
 *
 * Copyright (c)1995-1997 Microsoft Corporation, All Rights Reserved
 */


#ifndef _SITE_H_
#define _SITE_H_


class CImpIOleClientSite : public IOleClientSite
    {
    protected:
        ULONG               m_cRef;
        class CSite        *m_pSite;
        LPUNKNOWN           m_pUnkOuter;

    public:
        CImpIOleClientSite(class CSite *, IUnknown *);
        ~CImpIOleClientSite(void);

        STDMETHODIMP QueryInterface(REFIID, void **);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP SaveObject(void);
        STDMETHODIMP GetMoniker(DWORD, DWORD, LPMONIKER *);
        STDMETHODIMP GetContainer(LPOLECONTAINER *);
        STDMETHODIMP ShowObject(void);
        STDMETHODIMP OnShowWindow(BOOL);
        STDMETHODIMP RequestNewObjectLayout(void);
    };

typedef CImpIOleClientSite *PCImpIOleClientSite;



class CImpIAdviseSink : public IAdviseSink
    {
    protected:
        ULONG               m_cRef;
        class CSite        *m_pSite;
        LPUNKNOWN           m_pUnkOuter;

    public:
        CImpIAdviseSink(class CSite *, IUnknown *);
        ~CImpIAdviseSink(void);

        STDMETHODIMP QueryInterface(REFIID, void **);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP_(void)  OnDataChange(LPFORMATETC, LPSTGMEDIUM);
        STDMETHODIMP_(void)  OnViewChange(DWORD, LONG);
        STDMETHODIMP_(void)  OnRename(LPMONIKER);
        STDMETHODIMP_(void)  OnSave(void);
        STDMETHODIMP_(void)  OnClose(void);
    };


typedef CImpIAdviseSink *PCImpIAdviseSink;


class CImpIOleInPlaceSite : public IOleInPlaceSite
    {
    protected:
        ULONG               m_cRef;
        class CSite        *m_pSite;
        LPUNKNOWN           m_pUnkOuter;

    public:
        CImpIOleInPlaceSite(class CSite *, IUnknown *);
        ~CImpIOleInPlaceSite(void);

        STDMETHODIMP QueryInterface(REFIID, void **);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetWindow(HWND *);
        STDMETHODIMP ContextSensitiveHelp(BOOL);
        STDMETHODIMP CanInPlaceActivate(void);
        STDMETHODIMP OnInPlaceActivate(void);
        STDMETHODIMP OnUIActivate(void);
        STDMETHODIMP GetWindowContext(LPOLEINPLACEFRAME *
                        , LPOLEINPLACEUIWINDOW *, LPRECT, LPRECT
                        , LPOLEINPLACEFRAMEINFO);
        STDMETHODIMP Scroll(SIZE);
        STDMETHODIMP OnUIDeactivate(BOOL);
        STDMETHODIMP OnInPlaceDeactivate(void);
        STDMETHODIMP DiscardUndoState(void);
        STDMETHODIMP DeactivateAndUndo(void);
        STDMETHODIMP OnPosRectChange(LPCRECT);
    };

typedef CImpIOleInPlaceSite *PCImpIOleInPlaceSite;


class CImpIOleDocumentSite : public IOleDocumentSite
    {
    protected:
        ULONG               m_cRef;
        class CSite        *m_pSite;
        LPUNKNOWN           m_pUnkOuter;

    public:
        CImpIOleDocumentSite(class CSite *, IUnknown *);
        ~CImpIOleDocumentSite(void);

        STDMETHODIMP QueryInterface(REFIID, void **);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP ActivateMe(IOleDocumentView *);
    };

typedef CImpIOleDocumentSite *PCImpIOleDocumentSite;



/*
 * The CSite class, a COM object with the interfaces IOleClientSite,
 * IAdviseSink, IOleInPlaceSite, and IOleDocumentSite.
 */


class CSite : public IUnknown
    {
    friend CImpIOleClientSite;
    friend CImpIAdviseSink;
    friend CImpIOleInPlaceSite;
    friend CImpIOleDocumentSite;

    private:
        ULONG           m_cRef;
        DWORD           m_dwID;
        HWND            m_hWnd; //Client area window of parent

        class CFrame   *m_pFR;

        BOOL            m_fInitialized; //Something here?
        LPSTORAGE       m_pIStorage;    //Storage for object
		LPSTREAM		m_pIStream;		//Info stream for object

        //Object interfaces
        IUnknown          *m_pObj;
        IOleObject        *m_pIOleObject;
        IOleInPlaceObject *m_pIOleIPObject;
        IOleDocumentView  *m_pIOleDocView;

        BOOL               m_fDocObj;   //Document object here?

        //Our interfaces
        PCImpIOleClientSite   m_pImpIOleClientSite;
        PCImpIAdviseSink      m_pImpIAdviseSink;
        PCImpIOleInPlaceSite  m_pImpIOleIPSite;
        PCImpIOleDocumentSite m_pImpIOleDocumentSite;


    protected:
        BOOL    ObjectInitialize(LPUNKNOWN);

    public:
        CSite(DWORD, HWND, CFrame *);
        ~CSite(void);

        //Gotta have an IUnknown for delegation
        STDMETHODIMP QueryInterface(REFIID, void **);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        BOOL        Create(LPTSTR, IStorage *);
        BOOL        CreateStorage(IStorage *);
        void        Close(BOOL);
        void        Update(void);
        void        Destroy(IStorage *);
        void        Activate(LONG);
        void        UpdateObjectRects(void);
    };


typedef CSite *PCSite;

#endif //_SITE_H_
