/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    Tracker.cxx

Abstract:

    CTracker implementation

-------------------------------------------------------------------*/

class CTracker {
public:
	float m_rXTrans, m_rYTrans, m_rZTrans, m_rXRot, m_rYRot, m_rZRot;
	D3DMATRIX m_matRotAndTrans, m_matOrientation;
	void Move();
	void Randomize(float rX, float rY, float rZ);
	void SetMatrix();
};
