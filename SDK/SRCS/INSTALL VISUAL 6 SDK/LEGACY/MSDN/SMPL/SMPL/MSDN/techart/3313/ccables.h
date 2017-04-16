// CCables
//
/////////////////////////////////////////////////////////////////////////////

class CCables : public CObject
{
//operations
public:
	CCables();
	virtual ~CCables();
	CCables& CCables::operator=(const CCables & ccables);
    CCables::CCables(const CCables& ccables);
    BOOL     HittestConnector(CPoint point);
	CPoint   GetConnectorPoint(int nConnectorNum);
	BOOL     SetConnectorPoint(CPoint point, int nConnectorNum, CRect *prectHittest = NULL);
    virtual  BOOL SetGestureLimit(CPoint point);
	virtual  BOOL OnDrawConnector(CDC *pdc, int nConnectorNum);
	virtual  BOOL OnDrawCable(CDC *pdc, int nViewLandmarks);

protected:
	void     SetControlPoints();
    void     GetGestureOrientation(CPoint XY0, CPoint XY1);
//attributes
public:
	const DWORD FIRSTCONNECT;
	const DWORD SECONDCONNECT;
protected:
	enum   {NUMCONTROLPTS = 4};
	enum   {BADQUAD, QUAD1, QUAD2, QUAD3, QUAD4}; 
	enum   {CONNECTORRADIUS = 7};
	enum   {HITTESTRECTS = 2};
    CPoint m_FirstConnector;
    CPoint m_SecondConnector;
    POINT  m_CtrlPts[NUMCONTROLPTS];
    int    m_GestureLimit;
	int    m_GestureOrient;
	CRect  m_Hittest[HITTESTRECTS];
};

