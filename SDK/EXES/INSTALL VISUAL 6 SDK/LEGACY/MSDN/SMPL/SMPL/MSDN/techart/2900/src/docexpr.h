#ifndef DOCEXPR_H
#define DOCEXPR_H

//@doc DOCEXPR TOKENBASE

//@class Base class for expression tokens.
class CTokenBase  : public CObject
{
public:	
    //@cmember Evaluate the token against a supplied text string.

	virtual int Eval(const char *szSrc)   { return TRUE; }

    //@cmember Set the token using a supplied textual token.

	virtual int Set(const char *szToken, const char *&szCont)  { return 0; }
};


//@doc DOCEXPR IDTOKEN

class CIDToken : public CTokenBase
{
public:
	int Eval(const char *szSrc);
	int Set(const char *szToken, const char *&szCont);

private:
    CString m_sDocID;
};


//@doc DOCEXPR EXPRTOKEN

class CExprToken : public CTokenBase
{
private:
	CTokenBase *m_pLeft;
	CTokenBase *m_pRight;

	int m_nOp;
	BOOL m_bCommasAsOr;

	enum ExprParseState { LOOK_OPERATOR, LOOK_ARGUMENT, };
	enum ExprOps { NONE, OR, AND, };

public:
	CExprToken(void);
	CExprToken(CTokenBase *pLeft, CTokenBase *pRight, int nOp);
	~CExprToken(void);

	int Eval(const char *szSrc);
	int Set(const char *szExpr, const char *&szResume);
	int Set(void);

	void UseCommasAsOr(void) { m_bCommasAsOr = TRUE; }


};



#endif
