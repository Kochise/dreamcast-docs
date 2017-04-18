/////////////////////////////////////////////////////////////
//
// SharedPoint.h - Copyright 1996, Don Box
//

#ifndef _SHAREDPOINT_H
#define _SHAREDPOINT_H

#include "SharedObj.h"
#include "IPoint.h"


// shared data members
class PointRep {
    friend class CoSharedPoint;
    long m_x;
    long m_y;
    char m_sz[1024];
public:
    PointRep() : m_x(100), m_y(200) { lstrcpyA(m_sz, "Some Other Model?"); }
    ~PointRep() { OutputDebugString("I am done!\n"); }
};

// handler class that is instantiated in each process
class CoSharedPoint 
		: public CoSharedObject<PointRep,             // Shared state
                                &CLSID_CoSharedPoint, // this CLSID
                                IPointAndText,        // Primary interface
                                &IID_IPointAndText>   // Primary IID
{
public:
// IPointAndText members
    STDMETHODIMP Set(long x, long y);
    STDMETHODIMP Get(long FAR* px, long FAR* py);
    STDMETHODIMP SetText(LPCSTR lpsz);
    STDMETHODIMP GetText(LPSTR lpsz, int cb);
};

#endif
