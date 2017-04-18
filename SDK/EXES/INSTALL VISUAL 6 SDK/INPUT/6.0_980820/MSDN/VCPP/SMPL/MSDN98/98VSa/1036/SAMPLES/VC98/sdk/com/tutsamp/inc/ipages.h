/*+==========================================================================
  File:      IPAGES.H

  Summary:   This is the common include file for the persistent
             page-related COM Interfaces. The Interface abstract base
             classes are declared.

             This file is global to all the Tutorial Code Samples (kept in
             the ..\INC directory).  It is a good practice to factor out
             Interface and GUID specifications to reduce the possibility
             of GUID or interface conflicts.

  Classes:   IPageList, IPageListSink, ITextPage, ITextPageSink,
             IDrawPage, IDrawPageSink.

  Functions: .

  Origin:    5-26-97: atrent - Revised for the COM Tutorial Samples.

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/

#if !defined(IPAGES_H)
#define IPAGES_H

#if !defined(RC_INCLUDE)

// Here are the page types.
#define PAGETYPE_NONE    0
#define PAGETYPE_DELETED 1
#define PAGETYPE_TEXT    2
#define PAGETYPE_DRAWING 3

// Page Open Status.
#define OPENSTATE_NONE   0
#define OPENSTATE_YES    1
#define OPENSTATE_NO     2

#define PAGE_TITLE_SIZE 64
#define PAGE_NAME_SIZE 16

// Strings used for assembling IStorage/IStream names.
#define PAGELIST_USTR L"PageList"

// Messages for posting events from page windows to main app window.
#define WM_USER_PAGECHANGED WM_USER+400
#define WM_USER_PAGECLOSED  WM_USER+401


/*I+I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I
  Interface: IPageList

  Summary:   Interface for page list features to manipulate the
             encapsulated page list.

  Methods:   Get(
                 INT     iPage,
                 BOOL*   pbOpened,
                 SHORT*  pnType,
                 WCHAR*  pwszTitle,
                 WCHAR*  pwszDataName);
               Get a Page List Item for a given page number. Get back
               open status, page type, page title, and page data name.
             Set(
                 INT     iPage,
                 SHORT   nOpenStatus,
                 WCHAR*  pwszNewTitle);
               Put a Page List Item of specified page number with new
               page open status and page title.
             Add(
                 INT     iPage,
                 SHORT   nType,
                 WCHAR*  pwszTitle,
                 INT*    piPage)
               Add/insert a new Page List Item of specified type with
               specified title.
             Delete(INT  iPage);
               Delete the Page List Item for the specified page number.
             Clear(void);
               Clear/Delete all Page List Items from the Page List.
I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I-I*/
DECLARE_INTERFACE_(IPageList, IUnknown)
{
  // IUnknown methods.
  STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
  STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
  STDMETHOD_(ULONG,Release) (THIS) PURE;

  // IPageList methods.
  STDMETHOD(Get)        (THIS_ INT, BOOL*, SHORT*, WCHAR*, WCHAR*) PURE;
  STDMETHOD(Set)        (THIS_ INT, SHORT, WCHAR*) PURE;
  STDMETHOD(Add)        (THIS_ INT, SHORT, WCHAR*, INT*) PURE;
  STDMETHOD(Delete)     (THIS_ INT) PURE;
  STDMETHOD(Clear)      (THIS) PURE;
};


/*I+I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I
  Interface: IPageListSink

  Summary:   Sink Connection Interface for PageList COM Objects
             that communicate events back to the client.

  Methods:   Loaded
               The PageList was loaded from persistent storage.
             Saved
               The PageList was saved to persistent storage.
             Cleared
               The entire PageList was cleared.
             PageAdded(INT iPage);
               A new PageItem was added to the PageList.
             PageDeleted(INT iPage);
               A PageItem was deleted from the PageList.
             PageSet(INT iPage);
               A PageItem entry was set with new data.
I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I-I*/
DECLARE_INTERFACE_(IPageListSink, IUnknown)
{
  // IUnknown methods.
  STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
  STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
  STDMETHOD_(ULONG,Release) (THIS) PURE;

  // IPageListSink methods.
  STDMETHOD(Loaded)      (THIS) PURE;
  STDMETHOD(Saved)       (THIS) PURE;
  STDMETHOD(Cleared)     (THIS) PURE;
  STDMETHOD(PageAdded)   (THIS_ INT) PURE;
  STDMETHOD(PageDeleted) (THIS_ INT) PURE;
  STDMETHOD(PageSet)     (THIS_ INT) PURE;
};


/*I+I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I
  Interface: ITextPage

  Summary:   Interface for text page features to manipulate the text
             in the encapsulated text page.

  Methods:   GetLength(INT*    piLength);
               Get the current length (in WCHARs) of the text page.
             GetText(WCHAR* pwszPageText);
               Get the current page text held in this object.
             PutText(WCHAR* pwszPageText, INT iLength);
               Put specified wide character text of specified length
               into this text page object. Does not save persistently.
             Clear(BOOL bSaveNeeded);
               Clears all text from the entire text page.
I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I-I*/
DECLARE_INTERFACE_(ITextPage, IUnknown)
{
  // IUnknown methods.
  STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
  STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
  STDMETHOD_(ULONG,Release) (THIS) PURE;

  // ITextPage methods.
  STDMETHOD(GetLength)  (THIS_ INT*) PURE;
  STDMETHOD(GetText)    (THIS_ WCHAR*) PURE;
  STDMETHOD(PutText)    (THIS_ WCHAR*, INT) PURE;
  STDMETHOD(Clear)      (THIS_ BOOL) PURE;
};


/*I+I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I
  Interface: ITextPageSink

  Summary:   Sink Connection Interface for TextPage COM Objects
             that communicate events back to the client.

  Methods:   Loaded
               The TextPage was loaded from persistent stream.
             Saved
               The TextPage was saved to persistent stream.
             Put
               New text content was put into the TextPage object.
             Cleared
               The entire TextPage was cleared.
I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I-I*/
DECLARE_INTERFACE_(ITextPageSink, IUnknown)
{
  // IUnknown methods.
  STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
  STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
  STDMETHOD_(ULONG,Release) (THIS) PURE;

  // ITextPageSink methods.
  STDMETHOD(Loaded)      (THIS) PURE;
  STDMETHOD(Saved)       (THIS) PURE;
  STDMETHOD(Put)         (THIS) PURE;
  STDMETHOD(Cleared)     (THIS) PURE;
};


/*I+I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I
  Interface: IDrawPage

  Summary:   Interface for free-form drawing on drawing page COM Objects.

  Methods:   InkStart(SHORT nX,SHORT nY,SHORT nInkWidth,COLORREF crInkColor);
               Client starts color ink drawing to the drawing surface.
             InkDraw(SHORT nX, SHORT nY);
               Client puts ink data points on the drawing surface.
             InkStop(SHORT nX, SHORT nY);
               Client stops ink drawing to the drawing surface.
             Clear(BOOL bSaveNeeded);
               Clear the current drawing content. Notify Sinks.
               Mark dirty flag if bSaveNeeded==TRUE.
             Resize(SHORT nWidth, SHORT nHeight);
               Resize the drawing rectangle size.
             Redraw
               Redraw content of drawing object via Sink notification.
I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I-I*/
DECLARE_INTERFACE_(IDrawPage, IUnknown)
{
  // IUnknown methods.
  STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
  STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
  STDMETHOD_(ULONG,Release) (THIS) PURE;

  // IDrawPage methods.
  STDMETHOD(InkStart)   (THIS_ SHORT, SHORT, SHORT, COLORREF) PURE;
  STDMETHOD(InkDraw)    (THIS_ SHORT, SHORT) PURE;
  STDMETHOD(InkStop)    (THIS_ SHORT, SHORT) PURE;
  STDMETHOD(Clear)      (THIS_ BOOL) PURE;
  STDMETHOD(Resize)     (THIS_ SHORT, SHORT) PURE;
  STDMETHOD(Redraw)     (THIS) PURE;
};


/*I+I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I
  Interface: IDrawPageSink

  Summary:   Sink Connection Interface for use by DrawPage COM Objects
             that communicate events back to the client.

  Methods:   Loaded
               The DrawPage was loaded from persistent storage.
             Saved
               The DrawPage was saved to persistent storage.
             InkStart(SHORT nX,SHORT nY,SHORT nInkWidth,COLORREF crInkColor);
               A client started a color ink drawing sequence.
             InkDraw(SHORT nX, SHORT nY);
               A client is putting ink data points on the drawing surface.
             InkStop(SHORT nX, SHORT nY);
               A client stopped its ink drawing sequence.
             Cleared
               A client has erased/cleared the entire DrawPage.
             Resized(SHORT nWidth, SHORT nHeight);
               A client has resized the drawing window.
I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I-I*/
DECLARE_INTERFACE_(IDrawPageSink, IUnknown)
{
  // IUnknown methods.
  STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
  STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
  STDMETHOD_(ULONG,Release) (THIS) PURE;

  // IDrawPageSink methods.
  STDMETHOD(Loaded)      (THIS) PURE;
  STDMETHOD(Saved)       (THIS) PURE;
  STDMETHOD(InkStart)    (THIS_ SHORT, SHORT, SHORT, COLORREF) PURE;
  STDMETHOD(InkDraw)     (THIS_ SHORT, SHORT) PURE;
  STDMETHOD(InkStop)     (THIS_ SHORT, SHORT) PURE;
  STDMETHOD(Cleared)     (THIS) PURE;
  STDMETHOD(Resized)     (THIS_ SHORT, SHORT) PURE;
};


#endif // RC_INCLUDE

#endif // IPAGES_H
