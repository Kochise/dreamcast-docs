#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "input.h"
#include "fmt.h"
#include "docexpr.h"
#include "errmsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// *******************************************************
// Implementation of CIDToken class
// *******************************************************

//@doc DOCEXPR IDTOKEN

//@mfunc Search for text token in source string.


int CIDToken::Eval(const char *szSrc)
{
	ASSERT(szSrc);

    if(m_sDocID.IsEmpty())
		return TRUE;

    return strstr(szSrc, m_sDocID) != NULL;
}


// @mfunc Set the text token.

int CIDToken::Set(
	const char *szToken, 		//@parm Text for token.
	const char *&szCont)		//@parm Where to continue after token.
{
	m_sDocID = chSpace;

	for(int i = 0; istagchar(szToken[i]) && i < MAXTAGSIZE; i++)
		m_sDocID += szToken[i];

	if(istagchar(szToken[i]))
		return exprerrDocTokenTooLong;

	m_sDocID += chSpace;

	szCont = szToken+i;

	m_sDocID.MakeUpper();

	return 0;
}


// *******************************************************
// Implementation of CExprToken class
// *******************************************************

//@doc DOCEXPR EXPRTOKEN

// @mfunc Evaluate the doc expression against
// the source text.

int CExprToken::Eval(const char *szSrc)
{
	ASSERT(m_nOp != NONE);

	if(m_pLeft == NULL)
		return TRUE;

	int nLeft = m_pLeft->Eval(szSrc);

	if(m_pRight == NULL)
		return nLeft;

	int nRight = m_pRight->Eval(szSrc);

	switch(m_nOp)
	{
	case OR:
		return nLeft || nRight;

	case AND:
		return nLeft && nRight;
	}

	return FALSE;
}


// @mfunc Construct an expression.

CExprToken::CExprToken(void)
{
	m_nOp = NONE;
	m_pLeft = m_pRight = NULL;
	m_bCommasAsOr = FALSE;
}


// @mfunc Construct an expression.

CExprToken::CExprToken(CTokenBase *pLeft, CTokenBase *pRight, int nOp)
{
	m_nOp = nOp;
	m_pLeft = pLeft;
	m_pRight = pRight;
	m_bCommasAsOr = FALSE;
}


// @mfunc Kill an expression.

CExprToken::~CExprToken(void)
{
	Set();
}


int CExprToken::Set(void)
{
	m_nOp = OR;

	if(m_pLeft)
	{
		delete m_pLeft;
		m_pLeft = NULL;
	}
	if(m_pRight)
	{
		delete m_pRight;
		m_pRight = NULL;
	}
	
	return 0;
}

// @mfunc Parse a user-provided expression
// (from command line or index statement).
//
// Expression consists of multiple tokens,
// with optional subexpressions enclosed in
// parentheses. 
//
// Valid operators are AND (&) or OR (\|).
// A missing operator implies an OR.

int CExprToken::Set(
	const char *szFind, 
	const char *&szResume)
{
TRY
{
	ASSERT(szFind);

	CTokenBase *pNew;
	CExprToken *pExpr;
	int  nRet;
	int  nOp;

	ExprParseState nState;

	// ************************* 
	// Cleanup first.

	Set();

	// See if there is any expression.

	szFind = EatWhite(szFind);
	if(*szFind == '\0')
	{
		szResume = szFind;
		return 0;
	}
	
	// ************************* 
	// Parse.

	for(nState = LOOK_ARGUMENT;
		*szFind;
		szFind = EatWhite(szFind))
	{
		switch(nState)
		{
		case LOOK_OPERATOR:
			// determine operator - if non specified, default is OR

			if(istagchar(*szFind))
			{
				nOp = OR;
			} 
			else if(chPipe == *szFind || chOpenParen == *szFind ||
			        (chComma == *szFind && m_bCommasAsOr))
			{
				nOp = OR;
				
				if(*szFind != chOpenParen)
				    szFind++;
			}
			else if(chAmpersand == *szFind)
			{
				nOp = AND;
				szFind++;
			}
			else
			{
				return exprerrExpectedExprOperator;
			}

			nState = LOOK_ARGUMENT;

			break;

		case LOOK_ARGUMENT:

			// Figure out what kind of argument this
			// is.

		    if(istagchar(*szFind))
			{
				pNew = new CIDToken;

				// Set the values for the argument.		
		
				nRet = pNew->Set(szFind, szResume);
				if(nRet)
					return nRet;

				szFind = szResume;
			}
			else if(chOpenParen == *szFind)
			{
				const char *szEnd;

				pNew = new CExprToken;

				szEnd = MatchParen(szFind, chCloseParen, TRUE);
				if(*szEnd != chCloseParen)
					return exprerrExprMismatchedParens;

				CString sSubExpr(szFind+1, szEnd-szFind-1);

				nRet = pNew->Set(sSubExpr, szResume);
 				if(nRet)
					return nRet;

				szFind = szEnd+1;
			}
			else
			{
				return exprerrExpectedExprArgument;
			}

			// If no arguments have been set in the expression,
			// make this the left argument.
			
			if(m_pLeft == NULL)
			{
				m_pLeft = pNew;
			}


			// If the left one has been set, but not the right,
			// make this one the right argument.

			else if(m_pRight == NULL)
			{
				m_nOp = nOp;
				m_pRight = pNew;
			}

			// If both are set, collapse the left and right
			// args into a sub expression. Establish this as the
			// left argument and the new one as the right argument.

			else // (m_pLeft && m_pRight - both are filled)
			{
				pExpr = new CExprToken(m_pLeft, m_pRight, m_nOp);
			
				m_nOp    = nOp;
				m_pLeft  = pExpr;
				m_pRight = pNew;
			}

			nState = LOOK_OPERATOR;

			break;
		}
	}

	if(nState == LOOK_ARGUMENT)
		return exprerrExpectedExprArgument;

	szResume = szFind;

	return 0;
}
CATCH(CMemoryException, e)
{
	return errMemory;
}
END_CATCH
}

