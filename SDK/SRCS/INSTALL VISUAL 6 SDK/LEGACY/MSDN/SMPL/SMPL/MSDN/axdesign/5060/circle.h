//=--------------------------------------------------------------------------=
// Circle.H
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
#ifndef _CIRCLEOBJECT_H_
#define _CIRCLEOBJECT_H_

#include "IPServer.H"
#include "AutoObj.H"
#include "CircleCoInterfaces.H"
#include "Dispids.H"

typedef struct tagCIRCLESTATE {

    BOOL        fActing;
    COLOR_TYPE color;
    BSTR        bstrName;
    

} CIRCLEOBJECTSTATE;

class CCircleObject : 
    public CAutomationObjectWEvents,
    public ICircle
{
    
public:
    // IUnknown methods
    //
    DECLARE_STANDARD_UNKNOWN();

    // IDispatch methods
    //
    DECLARE_STANDARD_DISPATCH();

    CCircleObject(IUnknown *pUnkOuter);
    virtual ~CCircleObject();

    // static creation function.  all objects must have one of these!
    //
    static IUnknown *Create(IUnknown *);
    
    // user methods:
    //
    STDMETHOD(get_Name)(THIS_ BSTR FAR* pbstrName);
    STDMETHOD(put_Name)(THIS_ BSTR bstrName);
    STDMETHOD(get_Color)(THIS_ COLOR_TYPE FAR* pCV);
    STDMETHOD(put_Color)(THIS_ COLOR_TYPE CV);
    STDMETHOD(Act)(THIS);


  private:
    // overridables that the object must implement.
    //

    virtual HRESULT InternalQueryInterface(REFIID, void **);

    // private state information.
    //
    CIRCLEOBJECTSTATE m_state;
};


DEFINE_AUTOMATIONOBJECTWEVENTS(Circle,
    &CLSID_Circle,
    "ClassesByCategoryIteratorObject",
    CCircleObject::Create,
    1,
    &IID_ICircle,
    &DIID_DCircleEvents,			       
    "iter.HLP");



#endif // _CIRCLEOBJECT_H_
