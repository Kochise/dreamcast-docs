// binddoc.h : interface of the BinderDocObject OLE server document class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#ifndef __BINDDOC_H__
#define __BINDDOC_H__

#include <docobj.h>     // defines Document Object interfaces


/////////////////////////////////////////////////////////////////////////////
// OLECMD Map definitions

struct OLE_CMDMAP_ENTRY  
{
   const GUID* pguid;   // id of the command group
   ULONG       cmdID;   // OLECMD ID
   UINT        nID;     // corresponding WM_COMMAND message ID 
};

struct OLE_CMDMAP
{
#ifdef _AFXDLL
	const OLE_CMDMAP* (PASCAL* pfnGetBaseMap)();
#else
	const OLE_CMDMAP* pBaseMap;
#endif
	const OLE_CMDMAP_ENTRY* lpEntries;
};

#ifdef _AFXDLL
#define DECLARE_OLECMD_MAP() \
private: \
	static const OLE_CMDMAP_ENTRY _commandEntries[]; \
protected: \
	static AFX_DATA const OLE_CMDMAP commandMap; \
	static const OLE_CMDMAP* PASCAL _GetBaseCommandMap(); \
	virtual const OLE_CMDMAP* GetCommandMap() const; \

#else
#define DECLARE_OLECMD_MAP() \
private: \
	static const OLE_CMDMAP_ENTRY _commandEntries[]; \
protected: \
	static AFX_DATA const OLE_CMDMAP commandMap; \
	virtual const OLE_CMDMAP* GetCommandMap() const; \

#endif

#ifdef _AFXDLL
#define BEGIN_OLECMD_MAP(theClass, baseClass) \
	const OLE_CMDMAP* PASCAL theClass::_GetBaseCommandMap() \
		{ return &baseClass::commandMap; } \
	const OLE_CMDMAP* theClass::GetCommandMap() const \
		{ return &theClass::commandMap; } \
	AFX_DATADEF const OLE_CMDMAP theClass::commandMap = \
	{ &theClass::_GetBaseCommandMap, &theClass::_commandEntries[0] }; \
	const OLE_CMDMAP_ENTRY theClass::_commandEntries[] = \
	{ \

#else
#define BEGIN_OLECMD_MAP(theClass, baseClass) \
	const OLE_CMDMAP* theClass::GetCommandMap() const \
		{ return &theClass::commandMap; } \
	AFX_DATADEF const OLE_CMDMAP theClass::commandMap = \
	{ &baseClass::commandMap, &theClass::_commandEntries[0] }; \
	const OLE_CMDMAP_ENTRY theClass::_commandEntries[] = \
	{ \

#endif

#define END_OLECMD_MAP() \
		{NULL, 0, 0} \
	}; \

#define ON_OLECMD(pguid, olecmdid, id) \
	{ pguid, (ULONG)olecmdid, (UINT)id },

/////////////////////////////////////////////////////////////////////////////
// CDocObjectServerDoc

class CDocObjectServerDoc : public COleServerDoc
{
   DECLARE_DYNAMIC(CDocObjectServerDoc)

// Constructors 
public:
	CDocObjectServerDoc(); 

// Attributes
public:
   BOOL IsDocObject() const;

// Operations
public:
   void ActivateDocObject();

// Overridables
protected:
   // Document Overridables

   // View Overridables
   virtual void    OnApplyViewState(CArchive& ar);
   virtual HRESULT OnActivateView();

// Implementation
public:
	virtual ~CDocObjectServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   // Overrides
protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocObjectServerDoc)
	public:
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

   // Implementation Data
protected:
   // Document Data
   LPOLEDOCUMENTSITE m_pDocSite;

   // View Data
   LPOLEINPLACESITE  m_pViewSite;

   // Implementation Helpers
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDocObjectServerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Interface Maps
public:
	BEGIN_INTERFACE_PART(DocOleObject, IOleObject)
		INIT_INTERFACE_PART(CDocObjServerDoc, DocOleObject)
		STDMETHOD(SetClientSite)(LPOLECLIENTSITE);
		STDMETHOD(GetClientSite)(LPOLECLIENTSITE*);
		STDMETHOD(SetHostNames)(LPCOLESTR, LPCOLESTR);
		STDMETHOD(Close)(DWORD);
		STDMETHOD(SetMoniker)(DWORD, LPMONIKER);
		STDMETHOD(GetMoniker)(DWORD, DWORD, LPMONIKER*);
		STDMETHOD(InitFromData)(LPDATAOBJECT, BOOL, DWORD);
		STDMETHOD(GetClipboardData)(DWORD, LPDATAOBJECT*);
		STDMETHOD(DoVerb)(LONG, LPMSG, LPOLECLIENTSITE, LONG, HWND, LPCRECT);
		STDMETHOD(EnumVerbs)(IEnumOLEVERB**);
		STDMETHOD(Update)();
		STDMETHOD(IsUpToDate)();
		STDMETHOD(GetUserClassID)(CLSID*);
		STDMETHOD(GetUserType)(DWORD, LPOLESTR*);
		STDMETHOD(SetExtent)(DWORD, LPSIZEL);
		STDMETHOD(GetExtent)(DWORD, LPSIZEL);
		STDMETHOD(Advise)(LPADVISESINK, LPDWORD);
		STDMETHOD(Unadvise)(DWORD);
		STDMETHOD(EnumAdvise)(LPENUMSTATDATA*);
		STDMETHOD(GetMiscStatus)(DWORD, LPDWORD);
		STDMETHOD(SetColorScheme)(LPLOGPALETTE);
	END_INTERFACE_PART(DocOleObject)

	BEGIN_INTERFACE_PART(OleDocument, IOleDocument)
		INIT_INTERFACE_PART(CDocObjectServerDoc, OleDocument)
		STDMETHOD(CreateView)(LPOLEINPLACESITE, LPSTREAM, DWORD, LPOLEDOCUMENTVIEW*);
		STDMETHOD(GetDocMiscStatus)(LPDWORD);
		STDMETHOD(EnumViews)(LPENUMOLEDOCUMENTVIEWS*, LPOLEDOCUMENTVIEW*);
	END_INTERFACE_PART(OleDocument)

   BEGIN_INTERFACE_PART(OleDocumentView, IOleDocumentView)
      INIT_INTERFACE_PART(CDocObjectServerDoc, OleDocumentView)
      STDMETHOD(SetInPlaceSite)(LPOLEINPLACESITE);
      STDMETHOD(GetInPlaceSite)(LPOLEINPLACESITE*);
      STDMETHOD(GetDocument)(LPUNKNOWN*);        
      STDMETHOD(SetRect)(LPRECT);
      STDMETHOD(GetRect)(LPRECT);
      STDMETHOD(SetRectComplex)(LPRECT, LPRECT, LPRECT, LPRECT); 
      STDMETHOD(Show)(BOOL);        
      STDMETHOD(UIActivate)(BOOL);        
      STDMETHOD(Open)();        
      STDMETHOD(CloseView)(DWORD);
      STDMETHOD(SaveViewState)(LPSTREAM);
      STDMETHOD(ApplyViewState)(LPSTREAM);
      STDMETHOD(Clone)(LPOLEINPLACESITE, LPOLEDOCUMENTVIEW*);        
   END_INTERFACE_PART(OleDocumentView)

   BEGIN_INTERFACE_PART(OleCommandTarget, IOleCommandTarget)
      INIT_INTERFACE_PART(CDocObjectServerDoc, OleCommandTarget)
      STDMETHOD(QueryStatus)(const GUID*, ULONG, OLECMD*, OLECMDTEXT*);
      STDMETHOD(Exec)(const GUID*, DWORD, DWORD, VARIANTARG*, VARIANTARG*);        
   END_INTERFACE_PART(OleCommandTarget)

   BEGIN_INTERFACE_PART(Print, IPrint)
      INIT_INTERFACE_PART(COleServerDoc, Print)
      STDMETHOD(SetInitialPageNum)(LONG);
      STDMETHOD(GetPageInfo)(LPLONG, LPLONG);
      STDMETHOD(Print)(DWORD, DVTARGETDEVICE**, PAGESET**, LPSTGMEDIUM,
                       LPCONTINUECALLBACK, LONG, LPLONG, LPLONG);        
   END_INTERFACE_PART(Print)

   DECLARE_INTERFACE_MAP()

// OLECMD map - for handling commands sent via IOleCommandTarget
   DECLARE_OLECMD_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Inline Functions

inline BOOL CDocObjectServerDoc::IsDocObject() const
   { return (m_pDocSite != NULL) ? TRUE : FALSE; }

/////////////////////////////////////////////////////////////////////////////

#endif // #ifndef __BINDDOC_H__

