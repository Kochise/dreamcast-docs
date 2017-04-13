/*
 * OBJECT.H
 *
 * Definition of the classes CConnObject, CImpIConnPtCont, and
 * CEnumConnectionPoints for the connectable object;
 * CConnectionPoint, CImpIConnectionPoint, CImpIDuckEvents, and
 * CEnumConnections for the connection point.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _OBJECT_H_
#define _OBJECT_H_


//Number of connection points in this implementation
#define CCONNPOINTS     1


/*
 * The connectable object itself implements IUnknown and
 * IConnectionPointContainer.  It is closely associated with
 * the connection point enumerator, CEnumConnectionPoints.
 */

class CConnectionPoint;
typedef CConnectionPoint *PCConnectionPoint;


//ID's for triggering events
enum
    {
    EVENT_QUACK=1, EVENT_FLAP, EVENT_PADDLE
    };


class CConnObject : public IConnectionPointContainer
    {
    private:
        DWORD             m_cRef;         //Object reference count

        //Array holding all the points we have.
        PCConnectionPoint m_rgpConnPt[CCONNPOINTS];

    public:
        CConnObject(void);
        ~CConnObject(void);

        BOOL Init(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);

        //IConnectionPointContainer members
        STDMETHODIMP EnumConnectionPoints(IEnumConnectionPoints **);
	    STDMETHODIMP FindConnectionPoint(REFIID, IConnectionPoint **);

        //Other members
        BOOL TriggerEvent(UINT);
    };


typedef CConnObject *PCConnObject;



//Enumerator class for EnumConnectionPoints

class CEnumConnectionPoints : public IEnumConnectionPoints
    {
    private:
        ULONG           m_cRef;     //Object reference count
        LPUNKNOWN       m_pUnkRef;  //IUnknown for ref counting
        ULONG           m_iCur;     //Current element
        ULONG           m_cPoints;  //Number of conn points
        IConnectionPoint **m_rgpCP; //Source of conn points

    public:
        CEnumConnectionPoints(LPUNKNOWN, ULONG, IConnectionPoint **);
        ~CEnumConnectionPoints(void);

        //IUnknown members that delegate to m_pUnkRef.
        STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IEnumConnectionPoints members
        STDMETHODIMP Next(ULONG, IConnectionPoint **, ULONG *);
        STDMETHODIMP Skip(ULONG);
        STDMETHODIMP Reset(void);
        STDMETHODIMP Clone(IEnumConnectionPoints **);
    };

typedef CEnumConnectionPoints *PCEnumConnectionPoints;




/*
 * The connection point object iself is contained within the
 * connection point container, which is the connectable object.
 * It therefore manages a back pointer to that connectable object,
 * and implement IConnectionPoint.  This object has a few
 * member functions besides those in IConnectionPoint that are
 * used to fire the outgoing calls.
 */

#define CCONNMAX    2

class CConnectionPoint : public IConnectionPoint
    {
    private:
        ULONG           m_cRef;     //Object reference count
        PCConnObject    m_pObj;     //Containing object

        IID             m_iid;      //Our relevant interface

        /*
         * To keep things simple we'll only support two
         * advise connections at most.  Production quality
         * connection points should supprt any number of
         * connections.  For each connection we need to maintain
         * the sink pointer and the cookie assigned to it.
         */
        IUnknown       *m_rgpIUnknown[CCONNMAX];
        DWORD           m_rgdwCookies[CCONNMAX];

        UINT            m_cConn;
        DWORD           m_dwCookieNext; //Counter

    public:
        CConnectionPoint(PCConnObject, REFIID);
        ~CConnectionPoint(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IConnectionPoint members
        STDMETHODIMP GetConnectionInterface(IID *);
        STDMETHODIMP GetConnectionPointContainer
            (IConnectionPointContainer **);
        STDMETHODIMP Advise(LPUNKNOWN, DWORD *);
        STDMETHODIMP Unadvise(DWORD);
        STDMETHODIMP EnumConnections(IEnumConnections **);
    };


//Enumeration clas for EnumConnections

class CEnumConnections : public IEnumConnections
    {
    private:
        ULONG           m_cRef;     //Object reference count
        LPUNKNOWN       m_pUnkRef;  //IUnknown for ref counting
        ULONG           m_iCur;     //Current element
        ULONG           m_cConn;    //Number of connections
        LPCONNECTDATA   m_rgConnData; //Source of connections

    public:
        CEnumConnections(LPUNKNOWN, ULONG, LPCONNECTDATA);
        ~CEnumConnections(void);

        //IUnknown members that delegate to m_pUnkRef.
        STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IEnumConnections members
        STDMETHODIMP Next(ULONG, LPCONNECTDATA, ULONG *);
        STDMETHODIMP Skip(ULONG);
        STDMETHODIMP Reset(void);
        STDMETHODIMP Clone(IEnumConnections **);
    };

typedef CEnumConnections *PCEnumConnections;


#endif _OBJECT_H_
