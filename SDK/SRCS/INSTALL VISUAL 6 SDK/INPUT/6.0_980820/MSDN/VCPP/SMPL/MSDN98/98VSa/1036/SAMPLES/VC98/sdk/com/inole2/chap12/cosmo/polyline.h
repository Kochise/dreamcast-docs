/*
 * POLYLINE.H
 * Cosmo Chapter 12
 *
 * Definitions and function prototypes for the PolyLine window
 * class that can be treated like its own control.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _POLYLINE_H_
#define _POLYLINE_H_

//Versioning.
#define VERSIONMAJOR                2
#define VERSIONMINOR                0
#define VERSIONCURRENT              0x00020000

//Classname
#define SZCLASSPOLYLINE             TEXT("polyline")

//Stream Name that holds the data
#define SZSTREAM                    OLETEXT("CONTENTS")

#define HIMETRIC_PER_INCH           2540
#define CPOLYLINEPOINTS             20

//Window extra bytes and offsets
#define CBPOLYLINEWNDEXTRA          (sizeof(LONG))
#define PLWL_STRUCTURE              0


//Version 2.0 Polyline Structure
typedef struct tagPOLYLINEDATA
    {
    WORD        wVerMaj;                //Major version number.
    WORD        wVerMin;                //Minor version number.
    WORD        cPoints;                //Number of points.
    short       fReserved;              //Obsolete from v1.0
    RECTS       rc;                     //Rectangle of this figure
    POINTS      rgpt[CPOLYLINEPOINTS];  //Points (0-32767 grid)

    //Version 2.0 additions
    COLORREF    rgbBackground;          //Background color
    COLORREF    rgbLine;                //Line color
    short       iLineStyle;             //Line style
    } POLYLINEDATA, *PPOLYLINEDATA;

#define CBPOLYLINEDATA   sizeof(POLYLINEDATA)
#define CBPOLYLINEDATA20 sizeof(POLYLINEDATA)


//Version 1.0 Polyline Structure
typedef struct tagPOLYLINEDATA10
    {
    WORD        wVerMaj;                //Major version number.
    WORD        wVerMin;                //Minor version number.
    WORD        cPoints;                //Number of points.
    short       fDrawEntire;            //Flag to draw entire figure
    RECTS       rc;                     //Rectangle of this figure
    POINTS      rgpt[CPOLYLINEPOINTS];  //Points (scaled to rc)
    } POLYLINEDATA10, *PPOLYLINEDATA10;

#define CBPOLYLINEDATA10 sizeof(POLYLINEDATA10)


//POLYWIN.CPP
LRESULT APIENTRY PolylineWndProc(HWND, UINT, WPARAM, LPARAM);


class CPolyline : public CWindow
    {
    friend LRESULT APIENTRY PolylineWndProc(HWND, UINT, WPARAM
        , LPARAM);

    private:
        POLYLINEDATA   m_pl;

        class CPolylineAdviseSink * m_pAdv;

    private:
        HFILE     OpenFileW(LPTSTR, LPOFSTRUCT, UINT);
        void      PointScale(LPRECT, LPPOINTS, BOOL);
        void      Draw(HDC, BOOL, BOOL);
        void      RectConvertMappings(LPRECT, BOOL);

    public:
        CPolyline(HINSTANCE);
        ~CPolyline(void);

        BOOL      Init(HWND, LPRECT, DWORD, UINT
            , class CPolylineAdviseSink *);

        void      New(void);
        BOOL      Undo(void);

        //File functions
        LONG      ReadFromStorage(LPSTORAGE);
        LONG      WriteToStorage(LPSTORAGE, LONG);

        LONG      ReadFromFile(LPTSTR);
        LONG      WriteToFile(LPTSTR, LONG);

        //Data transfer functions
        LONG      DataSet(PPOLYLINEDATA, BOOL, BOOL);
        LONG      DataGet(PPOLYLINEDATA, LONG);
        LONG      DataSetMem(HGLOBAL, BOOL, BOOL, BOOL);
        LONG      DataGetMem(LONG, HGLOBAL *);
        HBITMAP   RenderBitmap(void);
        HMETAFILE RenderMetafile(void);
        HGLOBAL   RenderMetafilePict(void);

        void      RectGet(LPRECT);
        void      SizeGet(LPRECT);
        void      RectSet(LPRECT, BOOL);
        void      SizeSet(LPRECT, BOOL);
        COLORREF  ColorSet(UINT, COLORREF);
        COLORREF  ColorGet(UINT);
        UINT      LineStyleSet(UINT);
        UINT      LineStyleGet(void);
    };

typedef CPolyline *PCPolyline;


//Error values for data transfer functions
#define POLYLINE_E_NONE                    0
#define POLYLINE_E_UNSUPPORTEDVERSION      -1
#define POLYLINE_E_INVALIDPOINTER          -2
#define POLYLINE_E_READFAILURE             -3
#define POLYLINE_E_WRITEFAILURE            -4




class CPolylineAdviseSink
    {
    private:
        LPVOID      m_pv;           //Customizable structure

    public:
        CPolylineAdviseSink(LPVOID);
        ~CPolylineAdviseSink(void);

        void OnPointChange(void);
        void OnSizeChange(void);
        void OnDataChange(void);
        void OnColorChange(void);
        void OnLineStyleChange(void);
    };

typedef CPolylineAdviseSink *PCPolylineAdviseSink;


//Color indices for color messages
#define POLYLINECOLOR_BACKGROUND    0
#define POLYLINECOLOR_LINE          1



#endif  //_POLYLINE_H_
