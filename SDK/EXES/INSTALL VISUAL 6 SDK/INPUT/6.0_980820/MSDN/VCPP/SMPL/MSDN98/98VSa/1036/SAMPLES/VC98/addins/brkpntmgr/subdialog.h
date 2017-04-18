// SubDialog.h
#ifndef _SUBDIALOG_
#define _SUBDIALOG_

class CBrkPnts;

class CSubDialog : public CDialog
{
public:
	CBrkPnts * m_pbrksmgr;
	CSubDialog(UINT idTemplate, CWnd *pParent): CDialog(idTemplate, pParent) {}
	virtual BOOL Create(CWnd *pParent) PURE;
};

#endif 