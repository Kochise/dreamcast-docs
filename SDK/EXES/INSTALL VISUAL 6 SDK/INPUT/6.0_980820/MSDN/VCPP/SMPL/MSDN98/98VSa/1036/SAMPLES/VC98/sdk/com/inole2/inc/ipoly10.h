/*
 * IPOLY10.H
 * Polyline Object Chapter 10
 *
 * Definition of an IPolyline interface for a Polyline object.
 * This custom interface and is only supported from DLL-based
 * objects.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IPOLY10_H_
#define _IPOLY10_H_


//Versioning.
#define VERSIONMAJOR                2
#define VERSIONMINOR                0
#define VERSIONCURRENT              0x00020000

#define CPOLYLINEPOINTS             20

//Version 2.0 Polyline Structure
typedef struct tagPOLYLINEDATA
    {
    WORD        wVerMaj;                //Major version number
    WORD        wVerMin;                //Minor version number
    WORD        cPoints;                //Number of points
    short       fReserved;              //Previously fDrawEntire
    RECTS       rc;                     //Rectangle of figure
    POINTS      rgpt[CPOLYLINEPOINTS];  //Points on 0-32767 grid

    //Version 2.0 additions
    COLORREF    rgbBackground;          //Background color
    COLORREF    rgbLine;                //Line color
    short       iLineStyle;             //Line style
    } POLYLINEDATA, *PPOLYLINEDATA;

#define CBPOLYLINEDATA   sizeof(POLYLINEDATA)


/*
 * !!Addition:  Clipboard format shared with using applications
 * This name matches those in the stringtable of all Cosmo and CoCosmo
 * versions.  All data is interchangable.
 */
#define SZPOLYLINECLIPFORMAT        TEXT("Polyline Figure")


#ifndef OMIT_POLYLINESINK

#undef  INTERFACE
#define INTERFACE IPolylineAdviseSink10


/*
 * When someone initializes a polyline and is interested in receiving
 * notifications on events, then they provide one of these objects.
 */

DECLARE_INTERFACE_(IPolylineAdviseSink10, IUnknown)
    {
    //IUnknown members
    STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
    STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    //Advise members.
    STDMETHOD_(void,OnPointChange)     (THIS) PURE;
    STDMETHOD_(void,OnSizeChange)      (THIS) PURE;
    STDMETHOD_(void,OnColorChange)     (THIS) PURE;
    STDMETHOD_(void,OnLineStyleChange) (THIS) PURE;
    //OnDataChange replaced with IAdviseSink
    };

typedef IPolylineAdviseSink10 *PPOLYLINEADVISESINK;

#endif //OMIT_POLYLINESINK


#undef  INTERFACE
#define INTERFACE IPolyline10

DECLARE_INTERFACE_(IPolyline10, IUnknown)
    {
    //IUnknown members
    STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
    STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    //IPolyline members

    //File-related members use IPersistStorage, IPersistStreamInit
    //Data transfer members use IDataObject

    //Manipulation members:
    STDMETHOD(Init)   (THIS_ HWND, LPRECT, DWORD, UINT) PURE;
    STDMETHOD(New)    (THIS) PURE;
    STDMETHOD(Undo)   (THIS) PURE;
    STDMETHOD(Window) (THIS_ HWND *) PURE;

    STDMETHOD(RectGet) (THIS_ LPRECT) PURE;
    STDMETHOD(SizeGet) (THIS_ LPRECT) PURE;
    STDMETHOD(RectSet) (THIS_ LPRECT, BOOL) PURE;
    STDMETHOD(SizeSet) (THIS_ LPRECT, BOOL) PURE;

    STDMETHOD(ColorSet) (THIS_ UINT, COLORREF, COLORREF *) PURE;
    STDMETHOD(ColorGet) (THIS_ UINT, COLORREF *) PURE;

    STDMETHOD(LineStyleSet) (THIS_ UINT, UINT *) PURE;
    STDMETHOD(LineStyleGet) (THIS_ UINT *) PURE;
    };

typedef IPolyline10 *PPOLYLINE;


//Error values for data transfer functions
#define POLYLINE_E_INVALIDPOINTER   \
    MAKE_SCODE(SEVERITY_ERROR, FACILITY_ITF, 1)
#define POLYLINE_E_READFAILURE      \
    MAKE_SCODE(SEVERITY_ERROR, FACILITY_ITF, 2)
#define POLYLINE_E_WRITEFAILURE     \
    MAKE_SCODE(SEVERITY_ERROR, FACILITY_ITF, 3)


//Color indices for color member functions
#define POLYLINECOLOR_BACKGROUND    0
#define POLYLINECOLOR_LINE          1


#endif //_IPOLY10_H_
