/////////////////////////////////////////////////////////////////////////////
// CListen.h : interface of the CListen class
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

#ifndef __CLISTEN_H__
#define __CLISTEN_H__

class CWebDoc;	// fwd ref

class CListen : public CSocket
{
	DECLARE_DYNAMIC(CListen);
private:
	CListen(const CListen& rSrc);         // no implementation
	void operator=(const CListen& rSrc);  // no implementation

// Construction
public:
	CListen(CWebDoc* pDoc);

// Attributes
public:
	CWebDoc* m_pDoc;

// Overridable callbacks
protected:
	virtual void OnAccept(int nErrorCode);

// Implementation
public:
	virtual ~CListen();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
#endif // __CLISTEN_H__
