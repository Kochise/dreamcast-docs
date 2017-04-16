#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "topiclog.h"
#include "fmtspec.h"
#include "docexpr.h"
#include "cmdargs.h"
#include "extract.h"
#include "parsetag.h"
#include "errmsg.h"

const char *ParseTagField(const char *szCur, char *szTempBuf, CTag *ptagNew, int i, int nTagFields);

//@doc


/*
@func Allocates a new CTag object and adds it to the tag list.

@parm List in which to store the tag.
@parm Line number of tag.
@parm Tag name.

@rdesc The new tag.
*/
CTag *AddTag(CTagList &listTags, long lLineTag, const char *szTag)
{
    // Allocate a TAG structure

	CTag *ptagNew = new CTag;
	
	listTags.AddTail(ptagNew);

    // Record filename, starting line number, tag name

    ptagNew->lSrcLineNum  = lLineTag;
    ptagNew->sTag = szTag;

	return ptagNew;
}


/*
@func CTag *| ParseTag | This function converts a text block into a <t TAG>
structure containing a list of fields for the tag. The <t TAG> structure is
added to the linked list of <t TAG> structures passed as a parameter.

@rdesc Returns 0 on success or an error code.
*/

int ParseTag(
	CSrcInput &in,          //@parm Input file
    FormatInfo &fmt,        //@parm Formatting structures
	BOOL bAux,				//@parm Whether this is aux tag
	CTag *ptagAuxParent,	//@parm Paragraph tag, parent of aux tag
	BOOL bTopic)            //@parm Whether this is a topic tag
{
    int nTagFields;
    int nExtrFields = 0;
    int nSrcLineNum = in.m_lCurLine;
    int nParseType;

	CPendingList &listPend = bAux ? in.m_pendAux : in.m_pendMain;
	CTagList &listTags = bAux ? in.m_listAuxTags : in.m_listTags;
	const char *szTag  = in.m_sTag;

    const char *szCur;

    CFmtTopic  *pfmtTopic = NULL;
    CFmtPara  *pfmtPara = NULL;

    char *szTempBuf;
    
    if(bTopic)
    {
        CFmtSrchTopic srch;

        srch.m_sName = szTag;
        pfmtTopic = (CFmtTopic *)fmt.topic.Get(&srch);
        if(pfmtTopic == NULL)
            return warnUnknownTopicTag;
    }
    else
    {
        CFmtSrchPara srch;

        srch.m_sName = szTag;
        pfmtPara = (CFmtPara *)fmt.paragraph.Get(&srch);
        if(pfmtPara == NULL)
            return warnUnknownParaTag;
    }

    // Allocate a temporary buffer for storing field text

    szTempBuf = new char[in.m_szTagCur - in.m_achTagBuf + 1];

	CTag *ptagNew = AddTag(listTags, in.m_nLineTag, szTag);

    // Set up a couple fields for the tag, these are topic/para
    // specific. The rest is generic.

    if(bTopic)
    {
        ASSERT(pfmtTopic);
        nTagFields = pfmtTopic->GetNumFields();
        nParseType = pfmtTopic->GetParseType();
    }
    else
    {
        ASSERT(pfmtPara);
        ptagNew->nState.IsExample = pfmtPara->IsExampleTag();
        nTagFields = pfmtPara->GetNumFields();
        nParseType = pfmtPara->GetParseType();
    }

    szCur = in.m_achTagBuf;

    // Get the text for each field (separated by chTagFieldSep character)

    for(ptagNew->nFields = 0; *szCur && ptagNew->nFields < nTagFields; 
    	ptagNew->nFields++)
    {
        // Process whitespace between fields, unless this is the
        // final field of an example tag.

        if(!(ptagNew->nState.IsExample && (ptagNew->nFields+1 == nTagFields)))
        {
            szCur = EatWhiteNl(szCur, &nSrcLineNum);
        }

        // Grab the field

        szCur = ParseTagField(szCur, szTempBuf, ptagNew, ptagNew->nFields, nTagFields);

        if(*szCur == chTagFieldSep && ptagNew->nFields != nTagFields-1)
            szCur++;
    }

    // Determine whether we have the targeted number of fields. If not, we can
	// try to parse text from the source line preceding the tag.
    
    int nRet = 0;

    if(nTagFields == ptagNew->nFields)
    {
        // Check for field overflow

        if(*szCur == chTagFieldSep)
            nRet = warnTooManyFields;
    }
    else
    {
        ASSERT(ptagNew->nFields < nTagFields);

		// If fields are missing, need to extract the missing fields from the
		// source. If the tag supports source parsing, first see if the source
		// text preceding the comment block (stored in in.m_achCommentStart
		// on a previous loop) has what is needed. If there is no source text
		// stored there, add the tag to the parsing cue, to parse source text
		// from a later line.
			
		if(nParseType == 0)
		{
            nRet = warnWrongNumFields;
		}
		else
		{
			const char *szT;

			szT = EatWhite(in.m_achCommentStart);
			if(*szT && !strchr("/';\r\n", *szT) && in.m_pendMain.IsEmpty())
			{
	            // Try to parse out the source text preceding the tag, which
				// was stored on a previous loop.
				// May need to append the current line's text to the 
				// stored source, but we only do this once.

				CParseText txt(szT);
				BOOL bDone   = FALSE;
				BOOL bAppend = FALSE;
				do
				{
					nRet = ParseSrc(ptagNew, txt, in.m_lCurLine, nParseType, FALSE);
					if(0 == nRet)
					{
						bDone = TRUE;
						in.m_achCommentStart[0] = '\0';
					}
					else if(warnSrcFieldsMultiline == nRet)
					{
						if(bAppend)
						{
							bDone = TRUE;
						}
						else
						{
							bAppend = TRUE;
							strcat(in.m_achCommentStart, in.m_szLineBuf);
						}
					}
				}
				while(!bDone);
			}
			else
			{
				in.CueParse(listPend, ptagNew, nTagFields, nParseType, bTopic);
			}
		}

    }
    
    delete szTempBuf;

    return nRet;
}




/*
@func char *| ParseTagField | This function creates a memory buffer
containing the text of a tag field. 

@rdesc Returns a pointer to the first character following the field.
This is either the end of the buffer or the pipe character following
the field.
*/

const char *ParseTagField(
    const char *szTagBuf, 	//@parm Pointer to the buffer containing the tag text.
    char *szTempBuf, 	    //@parm Pointer to a temporary buffer for use during parsing.
    CTag *ptagNew, 		    //@parm Pointer to the <t TAG> structure to add the field to.
    int i, 				    //@parm Index of field we're adding.
    int nTagFields)		    //@parm Count of tag fields as defined in format file.
{
    int nFieldLen;

    // If an example field, just copy the whole string into the
    // field.

    if( ptagNew->nState.IsExample && (i+1 == nTagFields) )
    {
        const char *szCont = szTagBuf + strlen(szTagBuf);

        const char *szT = TrimWhite(szCont, szTagBuf);

        nFieldLen = szT-szTagBuf+1;

        ptagNew->aszFieldText[i] = new char[nFieldLen + 1];
        memcpy(ptagNew->aszFieldText[i], szTagBuf, nFieldLen);
        ptagNew->aszFieldText[i][nFieldLen] = '\0';
		ptagNew->anFieldLen[i] = nFieldLen;

        return szCont;
    }

    // Otherwise, copy character by character, dealing with escaped pipes and 
    // newlines...

    for(char *szCur = szTempBuf; *szTagBuf && *szTagBuf != '|'; szCur++, szTagBuf++)
    {
        switch(*szTagBuf)
        {
        case '\\':

            // Ignore an escaped pipe character, just copy as literal

            if(*(szTagBuf+1) == '|')
                szTagBuf++;

            break;

        case '\r':
        case '\n':

            // Delete trailing whitespace at the end of a line

            while((szCur > szTempBuf) && 
            	  (*(szCur-1) == chSpace || *(szCur-1) == chTab) )
			{
                szCur--;
			}

            break;
        }

        *szCur = *szTagBuf;
    }

    // Delete trailing whitespace and newlines from
    // temp buffer containing field

    while((szCur > szTempBuf) && (isspace(*(szCur-1))))
        szCur--;

    *szCur = '\0';

    nFieldLen = strlen(szTempBuf);
    ptagNew->aszFieldText[i] = new char[nFieldLen+1];
    memcpy(ptagNew->aszFieldText[i], szTempBuf, nFieldLen);
    ptagNew->aszFieldText[i][nFieldLen] = '\0';
	ptagNew->anFieldLen[i] = nFieldLen;
    
    return szTagBuf;
}


/**************************************************
 ShiftFields
 
@func This function shifts fields in the TAG structure to make room
for new fields. Fields are NOT reset to NULL!
*/
void ShiftFields(
	CTag *ptag,		//@parm Pointer to the <t TAG> structure.
	int nIndex,		//@parm Where to start shifting.
	int nFields)	//@parm How many fields will be added.
{
	int i;

    ASSERT(ptag->nFields + nFields <= MAXNUMFIELDS);
            
    for(i = ptag->nFields+(nFields-1); i > (nIndex + nFields - 1); i--)
	{
    	ptag->aszFieldText[i] = ptag->aszFieldText[i - nFields];
		ptag->aszFieldText[i - nFields] = NULL;

        ptag->anFieldLen[i] = ptag->anFieldLen[i - nFields];
        ptag->anFieldLen[i - nFields] = 0;
	}
}




//@func This function copies a source string into a tag
// field.

void CopySrcString(
	CTag *ptag, 			    // @parm TAG structure to copy field into
	int iField,         	    // @parm Field to copy into
	const char *szStart = NULL, // @parm Starting position of token (NULL for empty token)
	const char *szEnd = NULL)	// @parm Ending position of token
{
	const char *sz;
	int nLen;
    int i;
    int nEsc = 0;

	// Calculate length of token. If there are Autoduck control characters
    // like backslash or angle brackets, need to allow room for an escape
    // before the character.

	if(szStart && szStart != szEnd)
	{
		if(szEnd)
		{
			sz = TrimWhite(szEnd, szStart);

		    if(!(sz == szStart && isspace(*sz)))
		        sz++;

		    nLen = sz-szStart;
		}
		else
		{
			nLen = strlen(szStart);
		}

	    ASSERT(nLen >= 0);

        // See if any escapable character in the 
        // field.

        for(i = 0; i < nLen; i++)
        {
            if(szStart[i] == chOpenAngle ||
                szStart[i] == chCloseAngle ||
                szStart[i] == chBackslash)
            {
                nEsc++;
            }
        }
	}
	else
	{
		nLen = 0;
	}

	// Copy token into tag structure

    ptag->aszFieldText[iField] = new char[nLen+nEsc+1];
    ZeroMem(ptag->aszFieldText[iField], nLen+nEsc+1);

    // Deal with Autoduck control characters

    if(szStart)
    {
        for(i = 0, nEsc = 0; i < nLen; i++, nEsc++)
        {
            if(szStart[i] == chOpenAngle ||
               szStart[i] == chCloseAngle ||
               szStart[i] == chBackslash)
            {
                ptag->aszFieldText[iField][nEsc++] = chBackslash;
            }
            ptag->aszFieldText[iField][nEsc] = szStart[i];
        }
        ptag->aszFieldText[iField][nEsc] = '\0';
    }

	ptag->anFieldLen[iField] = nEsc;
}


const char *SkipTemplate(
	const char *szT)
{
	if(strncmp(szT, "template", 8) == 0)
	{
		szT += 8;
		szT = SeekChar(szT, chOpenAngle);
		if(szT == NULL)
			return szT;

		szT = MatchParen(szT, chCloseAngle);
		if(*szT != chCloseAngle)
			return NULL;

		szT = EatWhite(++szT);
	}

	return szT;
}


const char *ParseOperator(
	const char *szName,
    CString &sOp)
{
	const char *szT;
	const char *szAngle;

	ASSERT(szName);

    if(strncmp(szName, "operator", 8) == 0)
    {
        sOp = "operator";
        szT = EatWhite(szName+8);

		// Look at various operator types

		if(*szT == chOpenParen)
		{
			// operator() (we may have already null-terminated the first 
			// open paren)

            sOp += "()";
			szT = EatWhite(++szT);
			if(*szT == chCloseParen)
				szT++;
		}
		else if(strncmp(szT, "delete", 6) == 0)
		{
			// operator delete

            sOp += " delete";

			szT += 6;
		}
		else if(strncmp(szT, "new", 3) == 0)
		{
			// operator new

			sOp += " new";
			szT += 3;
		}
		else if(isalpha(*szT))
		{
			// e.g. operator const BITMAPINFOHEADER *

			szName = szT;
			while(*szT && *szT != chOpenParen && *szT != chOpenAngle)
				szT++;

			sOp += chSpace;
			sOp += CString(szName, szT-szName);
		}
		else
		{
			// other operators e.g. operator+

            szName = szT;

            while(*szT && *szT != ' ' && *szT != chOpenParen)
			{
				// An open angle bracket might indicate a 
				// template argument - see if there is a 
				// matching close angle bracket.

				if(*szT == chOpenAngle)
				{
					szAngle = MatchParen(szT, chCloseAngle, 0);
					if(*szAngle == chCloseAngle)
						break;
				}
                szT++;
			}

			sOp += CString(szName, szT-szName);
        }

        szT = EatWhite(szT);
        if(*szT == chOpenAngle)
        {
            const char *szTempl = szT;
            szT = MatchParen(szT, chCloseAngle);
            if(*szT == chCloseAngle)
            {
                szT++;
                sOp += CString(szTempl, szT-szTempl);
            }
        }

		return EatWhite(szT);
    }
	else
	{
		return NULL;
	}
}


//@func Skips past a set of template args enclosed
// in angle brackets.
//
//@rdesc Pointer to closing template bracket, or
// one character past starting point if no close
// bracket was found.

const char *SkipTemplateArgs(
	const char *szSrc)			//@parm Pos of opening bracket
{
	const char *szT = MatchParen(szSrc, chCloseAngle);
	if(*szT == chCloseAngle)
	{
		return szT+1;
	}
	else
	{
		return szSrc+1;
	}
}


int ParseConstant(
	CTag *ptag,
	const char *szSrc)
{
    static char szStopConst[] = "=;\r\n/";
	const char *szName = NULL;
	const char *szType = NULL;

	// Skip const keyword

	szSrc = EatWhite(szSrc);

	if(strncmp(szSrc, "const", 5) != 0)
		return warnSrcFieldsUnavailable;

	szSrc = szSrc+5;

    // Get type and name
    
    szSrc = SkipTemplate(EatWhite(szSrc));

    // Look for tokens until we hit a separator, paren, newline,
    // or comment

    while(!(*szSrc == '\0' || strchr(szStopConst, *szSrc)))
    {
        if(isidchar(*szSrc))
        {
        	if(szType == NULL)
                szType = szSrc;

            szName = szSrc;

            while(isidchar(*szSrc))
	            szSrc++;
	    }
	    else if(*szSrc == chOpenBracket)
        {
            szSrc = MatchParen(szSrc, chCloseBracket);
            if(*szSrc)
                szSrc++;
        }
		else
        {
        	szName = NULL;
        	szSrc++;
        }

		// Get the next token.
	
        szSrc = EatWhite(szSrc);
    }

    // If we didn't find either of the tokens, parsing failed, exit.

    if(NULL == szName || NULL == szType || szName == szType)
		return warnSrcFieldsIncomplete;

    // Move existing fields over.
    
    ShiftFields(ptag, 0, 2);
    ptag->nFields += 2;

    // Copy constant name

	CopySrcString(ptag, 1, szName, szSrc);

    // Copy type.

    CopySrcString(ptag, 0, szType, szName);

	return 0;
}



//@func Parses a class declaration of the form
//
// class __far MyClass:public YourClass

int ParseClass(
	CTag *ptag,     			//@parm Where to copy name
	const char *szSrc)		    //@parm Start of class declaration
{
	const char *szName = NULL;  				//Class name
	const char *szClose;						//End of class name
	const char *szClassStop = ",{/:";			//Stop chars for class

	// Skip the template, if present

	szSrc = SkipTemplate(EatWhite(szSrc));
	if(szSrc == NULL)
		return warnSrcFieldsIncomplete;

  	// Find "class"

	szSrc = EatWhite(szSrc);
	
	if(_strnicmp(szSrc, "class ", 6) && _strnicmp(szSrc, "class\t", 6))
		return warnSrcFieldsUnavailable;
		
	// Advance past "class" and find class name.
	
	szSrc = EatWhite(szSrc + 6);
	
	while(*szSrc && !strchr(szClassStop, *szSrc))
	{
		szName = szSrc;
		
    	if(!isidchar(*szName))
			return warnSrcFieldsIncomplete;
    	
    	while(isidchar(*szSrc))
    		szSrc++;

		szClose = szSrc;

        szSrc = EatWhite(szSrc);
	}
	
	if(szName == NULL)
		return warnSrcFieldsIncomplete;
    	
	ShiftFields(ptag, 0, 1);

	CopySrcString(ptag, 0, szName, szClose);
	
	ptag->nFields++;    	
	
	return 0;	
}



int ParseParameter(
	CTag *ptag,
	CParseText &txt,
	int nParseType,
	BOOL bReqTerm)
{
    static char szStopParm[] = ",;)\r\n/'";
	static char szEndParm[] = ",;()";
	static char szSkipChars[] = ",({";
	const char *szName = NULL;
//bugfix
	const char *szNameEnd = NULL;
	const char *szType = NULL;
	const char *szT;
    const char *szValue = NULL;
    const char *szValueEnd = NULL;

    if(txt.m_szCur == NULL)
		txt.m_szCur = txt.m_szBase;

	txt.m_szCur = EatWhite(txt.m_szCur);
	if(strchr(szSkipChars, *txt.m_szCur))
		txt.m_szCur = EatWhite(txt.m_szCur+1);

	txt.m_szCur = SkipTemplate(EatWhite(txt.m_szCur));

    // Look for tokens until we hit a separator, paren, newline,
    // or comment

    while(!(*txt.m_szCur == '\0' || strchr(szStopParm, *txt.m_szCur)))
    {
        if(isidchar(*txt.m_szCur))
        {
        	if(szType == NULL)
                szType = txt.m_szCur;

            szName = txt.m_szCur;
			szNameEnd = NULL;

            while(isidchar(*txt.m_szCur))
	            txt.m_szCur++;
	    }
	    else if(*txt.m_szCur == chOpenBracket)
        {
            txt.m_szCur = MatchParen(txt.m_szCur, chCloseBracket);
            if(*txt.m_szCur)
                txt.m_szCur++;
        }
        else if(nParseType == CFmtPara::parseParamOpt && chEqual == *txt.m_szCur)
        {
            // mark end of name
			szNameEnd = txt.m_szCur;

			// advance past equals
            txt.m_szCur = EatWhite(++txt.m_szCur);

            // get the value name
            if(!isidchar(*txt.m_szCur))
                return warnSrcFieldsMultiline;

            szValue = txt.m_szCur;
            while(isidchar(*txt.m_szCur))
                txt.m_szCur++;

            szValueEnd = txt.m_szCur;
        }
	    else if(*txt.m_szCur == chOpenParen)
        {
			// Determine whether this is the opening for the parameter
			// list. If the parent doesn't have a matching close paren
			// on the same line, break out.

            szT = MatchParen(txt.m_szCur, chCloseParen);
			if(*szT != chCloseParen)
				break;

			// Search past the open paren. If there is no token following
			// the paren, break out.
			//
			// @devnote If there is some weird character following the paren,
			// like *&, this will break - but that would be a very strange
			// construct.
			
			szT = EatWhite(++szT);
			if(!(isidchar(*szT) || *szT == chOpenParen))
				break;

			txt.m_szCur = szT;
        }
		else if(*txt.m_szCur == chOpenAngle)
		{
			szT = SkipTemplateArgs(txt.m_szCur);

			szNameEnd = txt.m_szCur;

			txt.m_szCur = szT;
		}
		else
        {
        	szName = NULL;
        	txt.m_szCur++;
        }

		// Get the next token.
	
        txt.m_szCur = EatWhite(txt.m_szCur);
    }

	// See if we found all of it.

	if(bReqTerm && (*txt.m_szCur == '\0' || !strchr(szEndParm, *txt.m_szCur)))
		return warnSrcFieldsMultiline;
    
	// If we didn't find any tokens, parsing failed, exit.

    if(NULL == szName && NULL == szType)
		return warnSrcFieldsIncomplete;

	if(szName == szType)
		szType = NULL;

    // Move existing fields over.
    
    if(CFmtPara::parseParamOpt == nParseType)
    {
        ShiftFields(ptag, 0, 3);
        ptag->nFields += 3;
    }
    else
    {
        ShiftFields(ptag, 0, 2);
        ptag->nFields += 2;
    }

    // COPY FUNCTION NAME

	CopySrcString(ptag, 1, szName, szNameEnd ? szNameEnd : txt.m_szCur);

    // Copy the type.

    if(szType)
    	CopySrcString(ptag, 0, szType, szName);
	else
		CopySrcString(ptag, 0);

    // Copy value.

    if(CFmtPara::parseParamOpt == nParseType)
    {
        if(szValue)
            CopySrcString(ptag, 2, szValue, szValueEnd);
        else
            CopySrcString(ptag, 2);
    }


/*bug
	if(nParseType == CFmtTopic::parseFunc)
		txt.m_szBase = txt.m_szCur;
bug*/
	return 0;	
}


void AdjustParmWhiteSpace(
	char *szParm)
{
	int i, j;

	CString sParmCopy(szParm);
    char *szParmCopy = sParmCopy.GetBuffer(sParmCopy.GetLength());

	for(i = 0, j = 0; szParmCopy[i]; j++)
	{
		if(iswhite(szParmCopy[i]))
		{
			szParm[j] = chSpace;
			while(iswhite(szParmCopy[i]))
				i++;
		}
		else
		{
			szParm[j] = szParmCopy[i++];
		}
	}
	szParm[j] = '\0';

	sParmCopy.ReleaseBuffer();
}


int ParseMember(
	CTag *ptag,
	CParseText &txt,
	BOOL bCopyParams)
{
    static char szStopMember[] = "\r\n/=;{";
	static char szEndMember[] = ";{=:";
	const char *szT;
	const char *szClose;
	const char *szName = NULL;
	const char *szType = NULL;
    const char *szParams = NULL;
    CString sOp;

    const char *szSrc = EatWhite(txt.m_szBase);
	if(chOpenCurly == *szSrc)
		szSrc = EatWhite(szSrc+1);

    // Look for tokens until we hit a separator, paren, newline,
    // or comment

    while(!(*szSrc == '\0' || strchr(szStopMember, *szSrc)))
    {
        // Name token

        if(isidchar(*szSrc) || *szSrc == chTilde)
        {
        	if(szType == NULL)
                szType = szSrc;

            szName = szSrc;

            // See if we have an operator... function - these
			// need special treatment.

            if(szT = ParseOperator(szSrc, sOp))
			{
				szSrc = szT;
			}
			else
			{
				if(*szSrc == chTilde)
					szSrc++;
				while(isidchar(*szSrc))
	            	szSrc++;
			}
	    }
        // Parameter list or macro return value

		else if(*szSrc == chOpenParen)
		{
			// Find matching paren and determine whether this is the parameter
			// list we're looking at.

			szClose = MatchParen(szSrc, chCloseParen);
			if(*szClose != chCloseParen)
				return warnSrcFieldsMultiline;

            szParams = szSrc;

			// If a paren is found, and the next character after the paren is a
			// stop character, the parens were the last on the line - parameter
			// list.

			szT = EatWhite(++szClose);
			if(*szT == '\0' || strchr(szStopMember, *szT))
			{
                szSrc = szT;
			}
			else if(strncmp(szT, "const", 5) == 0)
			{
				szSrc = szClose = szT+5;
			}
			else
			{
				// Continue past closing paren
				szSrc = szClose+1;
			}
		}
	    
	    // Array specifier

	    else if(*szSrc == chOpenBracket)
        {
            szT = MatchParen(szSrc, chCloseBracket);
            if(*szT == chCloseBracket)
                szSrc = szT+1;
			else
				return warnSrcFieldsMultiline;
        }

		// Template specifier

		else if(*szSrc == chOpenAngle)
		{
			szSrc = SkipTemplateArgs(szSrc);
		}
        
        // Non-name token: must keep looking for the real name
        
        else
        {
        	if(szType && strncmp(szType, "operator", 8) != 0)
				szName = NULL;
        	szSrc++;
        }

		// Get the next token.
	
        szSrc = EatWhite(szSrc);
    }

    if(!strchr(szEndMember, *szSrc))
        return warnSrcFieldsMultiline;

    // If we didn't find any tokens, parsing failed, exit.

    if(NULL == szName && NULL == szType)
		return warnSrcFieldsIncomplete;

	if(szName == szType)
		szType = NULL;

    // Move existing fields over.
    
    if(bCopyParams)
    {
        ShiftFields(ptag, 0, 3);
        ptag->nFields += 3;
    }
    else
    {
        ShiftFields(ptag, 0, 2);
        ptag->nFields += 2;
    }

    // Copy function name. Variations:
	// - with operator
	//		- with or without template args
	// - without operator

	if(szName)
	{
		// See if operator function.
		if(sOp.IsEmpty())
		{
			CopySrcString(ptag, 1, szName, szParams ? szParams : szSrc);
		}
		else
		{
			CopySrcString(ptag, 1, sOp);
		}
	}

	// Copy type

	if(szType)
		CopySrcString(ptag, 0, szType, szName);
	else
		CopySrcString(ptag, 0);

    // IF PARAMETER LIST, COPY IT AS WELL

    if(bCopyParams && szParams)
	{
        CopySrcString(ptag, 2, szParams, szClose);
		AdjustParmWhiteSpace(ptag->aszFieldText[2]);
	}

    // Set parse resume at parameter list, in case there are
    // parameter tags too.

	if(szParams)
	{
		txt.m_szCur = szParams;
	}
	
	return 0;
}



int ParseMfunc(
	CTag *ptag,
	CParseText &txt)
{
	CString sOp;

    const char *szT = NULL;

    const char *szClass = NULL;
    const char *szClassEnd = NULL;
	const char *szType;
	const char *szName;
    const char *szNameEnd = NULL;

    //** SET: szType  TO: first char on line

	szType = SkipTemplate(EatWhite(txt.m_szCur));
	if(szType)
	{
        szType = EatWhite(szType);
    }
	else
    {
    	return warnSrcFieldsIncomplete;        
    }

    // Get the member function separator. Note that there might be
    // a :: in the return type (for class enums).

    szName = strstr(szType, "::");
    if(szName == NULL)
		return warnSrcFieldsIncomplete;

    szT = strstr(szName+2, "::");
    if(szT)
        szName = szT;

    // Locate the class name.

    szClass = szName;
	
	// May have to skip over a template specifier.

	if(*(szClass-1) == chCloseAngle)
	{
		while(szClass != szType && *szClass != chOpenAngle)
			szClass--;
		if(*szClass != chOpenAngle)
			return warnSrcFieldsIncomplete;
		
		// Null-terminate at end of template specifier.
		szClassEnd = szClass;
	}

    // Search backward for beginning of class name.

    while(isidchar(*(szClass-1)) && szClass-1 >= szType)
        szClass--;
    if(szT == szClass)
		return warnSrcFieldsIncomplete;

    // Null-terminate class name, advance to function name

    if(szClassEnd == NULL)
        szClassEnd = szName;

    //** SET: szName   TO: first char of function name

    szName += 2;

    // Find end of function name, null-terminate it.

    for(szT = szName; *szT && !strchr("<( \r\n", *szT); szT++);

    // See if this is an overloaded operator - if not, null-terminate
	// the function name.

	const char *sz = ParseOperator(szName, sOp);
	if(sz)
	{
		szNameEnd = sz;
	}
	else
    {
        szNameEnd = szT;
    }

    // Shift tag fields over. First record class name & function
    // name

    ShiftFields(ptag, 0, 3);

	CopySrcString(ptag, 1, szClass, szClassEnd);

    if(sOp.IsEmpty())
    	CopySrcString(ptag, 2, szName, szNameEnd);
    else
    	CopySrcString(ptag, 2, sOp);

    // Store type declaration.

	CopySrcString(ptag, 0, szType, szClass);

    ptag->nFields += 3;

	txt.m_szCur = szNameEnd;

	return 0;
}


//@func Parses the structure tag name from a new-style C++
// enum/structure definition. Places tag name in field 0.

//@rdesc Returns 0 on success or an error code.

int ParseStruct(
	CTag *ptag,			//@parm Tag structure to fill
	const char *szSrc,	//@parm Source string
	int nParseType)		//@parm Either CFmtTopic::parseStruct or parseEnum

{
	const char *szName = NULL;
	static char szRUnion[] = "union";
	static char szREnum[] = "enum";
	static char szRStruct[] = "struct";
	char *szElemName;

	switch(nParseType)
	{
	case CFmtTopic::parseUnion:
		szElemName = szRUnion;
		break;

	case CFmtTopic::parseStruct:
		szElemName = szRStruct;
		break;

	case CFmtTopic::parseEnum:
		szElemName = szREnum;
		break;

	default:
		ASSERT(0);
		szElemName = szRStruct;
		break;
	}

  	// Find "enum"

	szSrc = EatWhite(szSrc);
	
	if(_strnicmp(szSrc, szElemName, strlen(szElemName)))
		return warnSrcFieldsUnavailable;
		
	// Advance past "enum" and enum name
	
	szSrc = EatWhite(szSrc + strlen(szElemName));

	if(!isidchar(*szSrc))
		return warnSrcFieldsIncomplete;

	szName = szSrc;
	
	while(isidchar(*szSrc))
		szSrc++;

	ShiftFields(ptag, 0, 1);

	CopySrcString(ptag, 0, szName, szSrc);
	
	ptag->nFields++;    	
	
	return 0;
}


//@func Parses an enumeration member name.
// Name is placed in field 0 of tag.

//@rdesc Zero on success or error code

int ParseEmem(
	CTag *ptag,				//@parm Tag to fill
	const char *szSrc)		//@parm Source string
{
	const char *szName = NULL;
			
    szSrc = EatWhite(szSrc);
	if(chOpenCurly == *szSrc)
		szSrc = EatWhite(szSrc+1);

	szName = szSrc = EatWhite(szSrc);
	if(!isidchar(*szSrc))
		return warnSrcFieldsIncomplete;
	
	while(isidchar(*szSrc))
		szSrc++;
	
	ShiftFields(ptag, 0, 1);

	CopySrcString(ptag, 0, szName, szSrc);

	ptag->nFields++;    	

	return 0;
}

BOOL MatchAny(char *asz[], const char *sz, int &i)
{
	for(i = 0; asz[i]; i++)
		if(_strnicmp(asz[i], sz, strlen(asz[i])) == 0)
			return TRUE;

	return FALSE;
}



//@func Parses VB type field.
// 0: name modifiers
// 1: name
// 2: type (if present)
// 3: description
//
//[Private | Public] Type varname
//	  elementname [([subscripts])] As type
//	[ elementname [([subscripts])] As type]
//	. . .
//End Type
//

int ParseVbField(
	CTag *ptag,
	CParseText &txt)
{
	static char szNameTerm[] = ",() ";
	static char *aszVarMods[] = { "Optional ", "ByVal ", "ByRef ", "ParamArray ", NULL, };
	static char szAs[] = "As ";

	const char *szName = NULL;
	const char *szNameEnd;
	const char *szType = NULL;
	const char *szTypeEnd;

	if(chOpenParen == *txt.m_szCur || chComma == *txt.m_szCur)
		txt.m_szCur++;

	// Get name.

	txt.m_szCur = EatWhite(txt.m_szCur);

	szName = txt.m_szCur;
	do
	{
		txt.m_szCur++;
	} while(*txt.m_szCur && !strchr(szNameTerm, *txt.m_szCur));

	szNameEnd = txt.m_szCur;

	// Include parens if present.

	txt.m_szCur = EatWhite(txt.m_szCur);

	if(chOpenParen == *txt.m_szCur)
	{
		txt.m_szCur = MatchParen(txt.m_szCur, chCloseParen, FALSE);
		if(chCloseParen != *txt.m_szCur)
			return warnSrcFieldsIncomplete;
		szNameEnd = txt.m_szCur++;

		txt.m_szCur = EatWhite(txt.m_szCur);
	}

	
	// Get the type if present.
	if(_strnicmp(txt.m_szCur, szAs, strlen(szAs)) == 0)
	{
		szType = EatWhite(txt.m_szCur+strlen(szAs));
		for(szTypeEnd = szType; 
			*szTypeEnd && !strchr(szNameTerm, *szTypeEnd); 
			szTypeEnd++);
	}


	// Fill in the tag fields.

	ShiftFields(ptag, 0, 2);
	ptag->nFields += 2;
	
	CopySrcString(ptag, 1, szName, szNameEnd);
	
	if(szType)
		CopySrcString(ptag, 2, szType, szTypeEnd);

	return 0;
}


		


//@func Parses VB parameter.
// 0: name modifiers
// 1: name
// 2: type (if present)
// 3: description
//
//parm=[Optional][ByVal | ByRef][ParamArray] varname[( )][As type]
//

int ParseVbParm(
	CTag *ptag,
	CParseText &txt,
	int nParseType)
{
	static char szNameTerm[] = ",() ";
	static char *aszVarMods[] = { "Optional ", "ByVal ", "ByRef ", "ParamArray ", NULL, };
	static char szAs[] = "As ";

	const char *szMods = NULL;
	const char *szModsEnd;
	const char *szName = NULL;
	const char *szNameEnd;
	const char *szType = NULL;
	const char *szTypeEnd;
	int i;

    ASSERT(txt.m_szCur);
	if(txt.m_szCur == NULL)
		return warnSrcFieldsIncomplete;

	txt.m_szCur = EatWhite(txt.m_szCur);
	if(chOpenParen == *txt.m_szCur || chComma == *txt.m_szCur)
		txt.m_szCur = EatWhite(txt.m_szCur+1);

	// Get modifiers if present.

	if(MatchAny(aszVarMods, txt.m_szCur, i))
	{
		szMods = txt.m_szCur;
		do
		{
			txt.m_szCur += strlen(aszVarMods[i]);
		} while(MatchAny(aszVarMods, txt.m_szCur, i));
		szModsEnd = txt.m_szCur;
	}

	// Get name.

	txt.m_szCur = EatWhite(txt.m_szCur);

	szName = txt.m_szCur;
	do
	{
		txt.m_szCur++;
	} while(*txt.m_szCur && !strchr(szNameTerm, *txt.m_szCur));

	szNameEnd = txt.m_szCur;

	// Include parens if present.

	txt.m_szCur = EatWhite(txt.m_szCur);

	if(chOpenParen == *txt.m_szCur)
	{
		txt.m_szCur = MatchParen(txt.m_szCur, chCloseParen, FALSE);
		if(chCloseParen != *txt.m_szCur)
			return warnSrcFieldsIncomplete;
		szNameEnd = txt.m_szCur++;

		txt.m_szCur = EatWhite(txt.m_szCur);
	}

	
	// Get the type if present.
	if(_strnicmp(txt.m_szCur, szAs, strlen(szAs)) == 0)
	{
		szType = EatWhite(txt.m_szCur+strlen(szAs));
		for(szTypeEnd = szType; 
			*szTypeEnd && !strchr(szNameTerm, *szTypeEnd); 
			szTypeEnd++);

		txt.m_szCur = szTypeEnd;
	}

	txt.m_szCur = EatWhite(txt.m_szCur);

	// Fill in the tag fields.

	if(nParseType == CFmtPara::parseBparam)
	{
		ShiftFields(ptag, 0, 3);
		ptag->nFields += 3;
		if(szMods)
			CopySrcString(ptag, 0, szMods, szModsEnd);
		
		CopySrcString(ptag, 1, szName, szNameEnd);
		
		if(szType)
			CopySrcString(ptag, 2, szType, szTypeEnd);
	}
	else
	{
		ShiftFields(ptag, 0, 2);
		ptag->nFields += 2;
		
		CopySrcString(ptag, 0, szName, szNameEnd);
	
		if(szType)
			CopySrcString(ptag, 1, szType, szTypeEnd);
	}

	return 0;
}


		




//@func Parses VB function or subroutine.
// 0: name modifiers
// 1: name
// 2: type (if present)
// 2/3: description

/*
[Public | Private][Static] Function name [(arglist)][As type]
	[statements]
	[name = expression]
	[Exit Function] 
	[statements]
	[name = expression]
End Function

[Private | Public][Static] Sub name [(arglist)] 
	[statements]
	[Exit Sub]
	[statements]
End Sub

[Private | Public] Type varname
	  elementname [([subscripts])] As type
	[ elementname [([subscripts])] As type]
	. . .
End Type

arglist=(parm[,parm...])

parm=[Optional][ByVal | ByRef][ParamArray] varname[( )][As type]
*/

int ParseVbRoutine(
	CTag *ptag,
	CParseText &txt,
	int nParseType)
{
	static char szNameTerm[] = "' \r\n(";
	static char szRFunc[] = "Function ";
	static char szRSub[]  = "Sub ";
	static char szRType[] = "Type ";
	static char szAs[] = "As ";

	const char *szRoutName;

	const char *szMods = NULL;
	const char *szModsEnd;
	const char *szName = NULL;
	const char *szNameEnd;
	const char *szType = NULL;
	const char *szTypeEnd;

	int iName;

	const char *szParamsEnd;

	BOOL bHasType = FALSE;
	int nShift;

	switch(nParseType)
	{
	case CFmtTopic::parseBfunc:
		iName = 1;
		nShift = 3;
		bHasType = TRUE;
		szRoutName = szRFunc;
		break;
		
	case CFmtTopic::parseBsub:
		iName = 1;
		nShift = 2;
		szRoutName = szRSub;
		break;
		
	case CFmtTopic::parseBtype:
		iName = 1;
		nShift = 2;
		szRoutName = szRType;
		break;

	default:
		ASSERT(0);
		nShift = 1;
		szRoutName = szRType;
		break;
	}

	txt.m_szCur = EatWhite(txt.m_szBase);
	
	// Capture modifiers, if present.
	if(_strnicmp(txt.m_szCur, szRoutName, strlen(szRoutName)))
	{
		szMods = txt.m_szCur;
		do
		{
			txt.m_szCur = strchr(txt.m_szCur, chSpace);
			if(txt.m_szCur)
				txt.m_szCur = EatWhite(txt.m_szCur);
		} while(txt.m_szCur && _strnicmp(txt.m_szCur, szRoutName, strlen(szRoutName)));

		if(NULL == txt.m_szCur)
			return warnSrcFieldsIncomplete;

		szModsEnd = txt.m_szCur-1;	
	}

	// Capture routine name.
	txt.m_szCur += strlen(szRoutName);

	txt.m_szCur = EatWhite(txt.m_szCur);

	szName = txt.m_szCur;
	do
	{
		txt.m_szCur++;
	} while(*txt.m_szCur && !strchr(szNameTerm, *txt.m_szCur));

	szNameEnd = txt.m_szCur;

	// Seek end or parameter list.
	txt.m_szCur = EatWhite(txt.m_szCur);

	
	// If a function, seek past the parameter list if present
	// and check for a return type.
	if(bHasType)
	{
		if(chOpenParen == *txt.m_szCur)
		{
			szParamsEnd = MatchParen(txt.m_szCur, chCloseParen, FALSE);
			if(chCloseParen != *szParamsEnd)
				return warnSrcFieldsIncomplete;
			szParamsEnd = EatWhite(szParamsEnd+1);
		}
		else
		{
			szParamsEnd = txt.m_szCur;
		}

		if(_strnicmp(szParamsEnd, szAs, strlen(szAs)) == 0)
		{
			szType = EatWhite(szParamsEnd+strlen(szAs));
			for(szTypeEnd = szType; 
			    *szTypeEnd && !strchr(szNameTerm, *szTypeEnd); 
				szTypeEnd++);
		}
	}

	// Now fill in the tag fields.

	ShiftFields(ptag, 0, nShift);
	ptag->nFields += nShift;
	if(szMods)
		CopySrcString(ptag, 0, szMods, szModsEnd);
	
	CopySrcString(ptag, iName, szName, szNameEnd);
	
	if(szType)
		CopySrcString(ptag, 2, szType, szTypeEnd);

	return 0;
}


/**************************************************
 ParseSrc

@func This function retrieves autoduck tags from C constructs within
the source file.

@rdesc Returns zero if successful or 1 if unsuccessful.
*/
int ParseSrc(
	CTag *ptag, 	    // @parm Specifies a pointer to the <t TAG> structure to add
					    // the field to.
	CParseText &txt, 	// @parm Specifies a pointer to the C source information.
	int nSrcLine, 	    // @parm Specifies the line number of the C source information.
	int nParseType,     // @parm Type of source parsing requested.
	int bReqTerm)       // @parm Whether to require a terminating character
{
    int nRet;

	if(txt.m_szCur == NULL)
		txt.m_szCur = txt.m_szBase;

    switch(nParseType)
    {
    case CFmtTopic::parseFunc:

    	nRet = ParseParameter(ptag, txt, nParseType, bReqTerm);

        break;

    case CFmtTopic::parseConstant:

    	nRet = ParseConstant(ptag, txt.m_szCur);

    	break;

    case CFmtTopic::parseMfunc:

    	nRet = ParseMfunc(ptag, txt);

    	break;

    case CFmtTopic::parseClass:
	
    	nRet = ParseClass(ptag, txt.m_szCur);

    	break;
		
    case CFmtTopic::parseUnion:
    case CFmtTopic::parseEnum:
	case CFmtTopic::parseStruct:
        // Find the enum name.
    
    	nRet = ParseStruct(ptag, txt.m_szCur, nParseType);

    	break;

	case CFmtTopic::parseBtype:
	case CFmtTopic::parseBfunc:
	case CFmtTopic::parseBsub:

		nRet = ParseVbRoutine(ptag, txt, nParseType);
		break;

	case CFmtPara::parseBparam:
	case CFmtPara::parseBfield:
		nRet = ParseVbParm(ptag, txt, nParseType);

		break;

    
	case CFmtPara::parseParam:
	case CFmtPara::parseParamOpt:
    case CFmtPara::parseField:

    	nRet = ParseParameter(ptag, txt, nParseType, bReqTerm);

        break;

    case CFmtPara::parseMember:

    	nRet = ParseMember(ptag, txt, TRUE);

    	break;

    case CFmtPara::parseMeth:

    	nRet = ParseMember(ptag, txt, FALSE);

    	break;

    case CFmtPara::parseEmem:

    	nRet = ParseEmem(ptag, txt.m_szCur);

    	break;

    }

    return nRet;
}



