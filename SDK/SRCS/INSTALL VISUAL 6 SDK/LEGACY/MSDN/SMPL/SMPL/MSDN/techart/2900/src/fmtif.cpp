#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "input.h"
#include "fmt.h"
#include "topiclog.h"
#include "fmtif.h"
#include "errmsg.h"

/////////////////////////////////////////////////////////////////////

int ParseIfXRef(const char *&sz, PIFCONDITION tail, int nFields);
int ParseIfExpression(const char *&sz, PIFCONDITION tail, int nFields); 

/******************************************************/
// Name Helper functions
/******************************************************/


void InitName(
	PNAMETOKEN pNameTok,
	int nTokens)
{
	for(int i = 0; i < nTokens; i++)
	{
		pNameTok[i].nField = 0;
		pNameTok[i].nType = nameNone;
		pNameTok[i].sTag.Empty();
	}
}	


//@func Parses a single token within a topic name, either $1 for local field
// or $tagname.1 for topic reference.
//
//@comm Caller is responsible for freeing memory allocated in <p pNameTok>.
//
//@rdesc Returns zero if successful or an error code.

int ParseNameToken(
    const char *&sz,		//@parm Name token text.
    						//  $ already parsed, starts with name reference
    PNAMETOKEN pNameTok,	//@parm <t NAMETOKEN> structure to fill out.
    int nFields)            //@parm Number of fields in tag.
{
    int nRet;
    int i;
    const char *szEnd;

    if(isdigit(*sz))
    {
        pNameTok->nType = nameLocal;
        sz = MakeNumber(sz, pNameTok->nField);

        if(pNameTok->nField < 1 || pNameTok->nField > MAXNUMFIELDS)
            return fmterrBadFieldReference;
        
        if(pNameTok->nField > nFields)
            return fmterrFieldReferenceRange;

        pNameTok->nField--;
    }
    else if(*sz == chOpenAngle)
    {
        pNameTok->nType = nameLocalStripTemplate;
        sz = MakeNumber(++sz, pNameTok->nField);

        if(pNameTok->nField < 1 || pNameTok->nField > MAXNUMFIELDS)
            return fmterrBadFieldReference;
        
        if(pNameTok->nField > nFields)
            return fmterrFieldReferenceRange;

        pNameTok->nField--;
    }
    else if(isalpha(*sz))
    {
        pNameTok->nType = nameTopic;

        // Get end of topic name 
        
        for(szEnd = sz, i = 0; istagchar(*szEnd) && i < MAXTAGSIZE; 
                szEnd++, i++);

        if(i == MAXTAGSIZE)
            return fmterrNameBadSpec;
            
        // Make the string

        CString sTag(sz, i);

        pNameTok->sTag = sTag;

        sz = szEnd;
	                        
        if(*sz++ != chPeriod)
        {
            nRet =  fmterrExpectedPeriod;
            goto Err;
        }
	                        
        if(!isdigit(*sz))
        {
            nRet =  fmterrExpectedFieldNum;
            goto Err;
        }

        sz = MakeNumber(sz, pNameTok->nField);

        if(pNameTok->nField < 1 || pNameTok->nField > MAXNUMFIELDS)
            return fmterrBadFieldReference;

        pNameTok->nField--;
    }
    else
    {
        nRet = fmterrNameBadSpec;
        goto Err;
    }

    return 0;

Err:

    return nRet;
}





//@func Parses a topic name mask (such as $1::$2) and fills out an
// array of <t NAMETOKEN> structures with the resulting topic name
// tokens.
//
//@rdesc Returns zero if successful or an error code if failure.
//
//@comm If a parsing error occurs, the caller is responsible for 
// freeing any memory created in the <p pNameTok> array.

int ParseTopicNameMask(
	const char *&sz, 		//@parm Source string with name spec.
	PNAMETOKEN pNameTok,	//@parm <t NAMETOKEN> array to fill.
	int &nTokens,     		//@parm Token count to fill.
    int nFields)
{
    int nRet;
    const char *szEnd;
	
	static char szNameStopChars[] = " \t\r\n);,=";
	static char szTokenStopChars[] = "$)";

    for(nTokens = 0; 
        *sz && !strchr(szNameStopChars, *sz) && nTokens < MAXTOPICNAMETOKENS; 
        nTokens++)
    {
        if(*sz == chDollar)
        {
        	sz++;
			
			// sz is updated to end of token
            nRet = ParseNameToken(sz, &pNameTok[nTokens], nFields);
            if(nRet)
				return nRet;
        }
        else
        {
            // Get the end of the token.

            szEnd = SeekEnd(sz, szTokenStopChars, MAXTAGSIZE);
			if(szEnd == NULL)
				return fmterrNameBadSpec;

            // Make a string.

            pNameTok[nTokens].sTag = CString(sz, szEnd-sz);
            pNameTok[nTokens].nType = nameLiteral;

            sz = szEnd;
        }
    }
    
    if(*sz && !strchr(szNameStopChars, *sz))
		return fmterrNameCount;

    return 0;
}




//@func This function creates a topic name given a format mask and an
// array of fields. 


void PrintName(
    char *szNameBuf,        //@parm Buffer at least MAXTOPICNAMELEN+1 long
	PNAMETOKEN pNameTok,	//@parm Name format specifiers: $1::$2 etc.
	int nTokens,			//@parm Number of name format specifiers.
    CTag *ptagTag,           //@parm TAG struct for tag
    CTag *ptagTopic)			//@parm TAG struct for topi
{
    const char *szToken;
    int i, j;
    int cbToken;
    int nNameLen;

    for(i = 0, nNameLen = 0; i < nTokens; i++)
    {
    	switch(pNameTok[i].nType)
    	{
        case nameLocalStripTemplate:
    	case nameLocal:

            szToken = ptagTag->aszFieldText[pNameTok[i].nField];

            // Empty token - copy nothing
            if(szToken == NULL || *szToken == '\0')
		    {
                cbToken = 0;
    		}
	    	
            // Tag token
	    	else if(pNameTok[i].nType == nameLocal)
            {
                cbToken = strlen(szToken);
            }
            else
            {
                // Find the angle bracket.

                for(j = 0; szToken[j] && szToken[j] != chOpenAngle; j++);
			
    			if(szToken[j] == chOpenAngle && (j > 0 && szToken[j-1] == '\\'))
    				j--;

                cbToken = j;
            }
    		
    		break;
    		
    	case nameTopic:

            szToken = ptagTopic->aszFieldText[pNameTok[i].nField];


            if(szToken == NULL || *szToken == '\0' || 
               _stricmp(pNameTok[i].sTag, ptagTopic->sTag) != 0)
            {
                cbToken = 0;
            }
            else
            {
                cbToken = strlen(szToken);
            }
    		break;

    	case nameLiteral:

            szToken = pNameTok[i].sTag;

            cbToken = strlen(szToken);
    		
    		break;
    		
    	default:
			cbToken = 0;

            ASSERT(0);
    	}


        // if necessary shorten token so it fits in field.

        if(nNameLen + cbToken > MAXTOPICNAMELEN)
			cbToken = MAXTOPICNAMELEN-nNameLen;

        
        // copy token over to recipient field, dealing with
        // escaped characters.

        char *szNameBufCur;     // current recipient position
        int  cbField;           // real count of chars (minus escapes)
        int  k;					// index into token
		extern char szAutoduckEscape[];       // def in OUTPUT.CPP

        szNameBufCur = &szNameBuf[nNameLen];
        for(cbField = 0, k = 0; k < cbToken; k++)
        {
            if(chBackslash == szToken[k] &&
               strchr(szAutoduckEscape, szToken[k+1]))
            {
                // skip backslash and output escaped
                // character

                k++;
            }

            if(szToken[k])
                szNameBufCur[cbField++] = szToken[k];
        }

        nNameLen += cbField;
    }

    szNameBuf[nNameLen] = '\0';
}






/////////////////////////////////////////////////////////////////////

/******************************************************/
// If conditions - will eventually switch these over
// to use the expression classes.
/******************************************************/


void InitIf(
	PIFCONDITION pif)
{
    InitName(pif->apNameTok[0], MAXTOPICNAMETOKENS);
	InitName(pif->apNameTok[1], MAXTOPICNAMETOKENS);

	pif->anTokens[0] = 0;
	pif->anTokens[1] = 0;

	pif->nType = ifNone;
	pif->nParam1 = 0;

	pif->next = NULL;
}

//@func This function parses a type-formatting Xref expression, in the
// form exists($1.$2). The calling function has already found the 
// "exists" keyword.

int ParseIfXRef(
    const char *&sz, 
    PIFCONDITION tail,
    int nFields)
{
    int nRet;

    tail->nType = ifTopicExists;

    // Skip past "exists" keyword and look for opening paren.

	sz = SeekChar(sz+6, chOpenParen);
    if(NULL == sz)
		return fmterrExpectedOpenParen;
	
	// Get topic name mask and construct token list.
	
	sz = EatWhite(++sz);
	
	nRet = ParseTopicNameMask(sz, tail->apNameTok[0], tail->anTokens[0], nFields);
	if(nRet)
		return nRet;
		
    // Find closing paren.

	sz = EatWhite(sz);	

    if(*sz != chCloseParen)
		return fmterrExpectedCloseParen;

    // Advance past closing paren.
	++sz;

	return 0;
}


//@func This function parses a type-formatting .IF expression, in the
// form $1==$func.1

int ParseIfExpression(
    const char *&sz,        // @parm Pointer to format spec buffer
    PIFCONDITION tail,      // @parm End of type if structure list
    int nFields)
{
    int  nRet = 0;
    int  i;

    tail->nType = ifExpression;
    
	// Get the left expression, equal sign, and right expression.

    for(i = 0; i < 2; i++)
    {
        // Get the operand - can be any combination of field references
        // and regular text.
        
		nRet = ParseTopicNameMask(sz, tail->apNameTok[i], tail->anTokens[i], nFields);
		if(nRet)
			return nRet;

        // Only do the next stuff if we're on the left side 
        // of the equal.

        if(i == 1)
            break;
	                    
        // Find the equal sign
	        
        if((sz = SeekChar(sz, '=')) == NULL)
            return fmterrExpectedEqual;

        // Find the start of the next operand.
	                        
        sz = EatWhite(++sz);
    }
    
    return 0;
}


/*
@func This function parses the .IF tag text of a paragraph, text, or
diagram tag. It constructs a linked list of IFCONDITION structures
from the format-file text.

@rdesc Returns 0 if successful or an error code if unsuccessful.
*/

int GetIfCondition(
	const char *sz,			// @parm Start of IF text
	PIFCONDITION &pIf,  	// @parm Where to drop head of linked list
    int nFields)            // @parm How many fields in parent tag
{
TRY
{
    PIFCONDITION tail;
    int nRet;
    static char szNameTerm[] = " \t)";
        
    // Find the end of the tail, if any already exist

    for(tail = pIf; tail && tail->next; tail = tail->next);

    // Cycle through the IF statements, constructing a new IF
    // structure for each.
    
    while(TRUE)
    {
		if(tail == NULL)
		{
        	pIf = tail = new IFCONDITION;
		}
		else
		{
			tail->next = new IFCONDITION;
			tail = tail->next;
		}

		InitIf(tail);

        sz = EatWhite(sz);
        if(*sz == chDollar)
        {
        	nRet = ParseIfExpression(sz, tail, nFields);
    	    if(nRet)
    		    return nRet;
        }
	    else if(_strnicmp(sz, "exists", 6) == 0)
        {
	    	nRet = ParseIfXRef(sz, tail, nFields);
    	    if(nRet)
    		    return nRet;
        }
	    else if(_strnicmp(sz, "tagexists", 9) == 0)
        {
            tail->nType = ifTagExists;

            if((sz = SeekChar(sz+9, chOpenParen)) == NULL)
                return fmterrExpectedOpenParen;

            sz = EatWhite(++sz);
                
            const char *szEnd = SeekEnd(sz, szNameTerm, MAXTAGSIZE);
			if(NULL == szEnd)
				return fmterrBadTagName;

            tail->sParam1 = CString(sz, szEnd-sz);

			sz = szEnd;

            if((sz = SeekChar(sz, chCloseParen)) == NULL)
                return fmterrExpectedCloseParen;

            sz++;
        }
	    else if(_strnicmp(sz, "fieldempty", 10) == 0)
        {
            tail->nType = ifFieldEmpty;

            if((sz = SeekChar(sz+10, chOpenParen)) == NULL)
                return fmterrExpectedOpenParen;

            if((sz = SeekNumber(++sz)) == NULL)
                return fmterrBadFieldReference;

            sz = MakeNumber(sz, tail->nParam1);
            if(tail->nParam1 < 1 || tail->nParam1 > nFields)
                return fmterrBadFieldReference;

            tail->nParam1--;
            
            if((sz = SeekChar(sz, chCloseParen)) == NULL)
                return fmterrExpectedCloseParen;

            sz++;
        }
		else
        {
	    	return fmterrBadIfExpression;
        }
	    	
        // See if we're done.
        
        if(*EatWhite(sz) == '\0')
            break;
            
        // If we're not done, we should now have a comma to separate
        // the IF statements.
                        
        if((sz = SeekChar(sz, chComma)) == NULL)
            return fmterrExpectedComma;
                        
        // Advance past the comma, and allocate a new IF structure.

        sz++;
    }

    return 0;
}
CATCH(CMemoryException, e)
{
    return errMemory;
}
END_CATCH
}



BOOL EvalIfCondition(
    PIFCONDITION pIf,	    //@parm Conditions to evaluate
    CTopicLog *pLog,        //@parm Topic log
    CTagList *plistTags,    //@parm Topic tag list
    CTag *ptagTag)		    //@parm Field info for paragraph or text tag.
{
TRY
{
    char szNameBuf[MAXTOPICNAMELEN+1];
    char szNameBuf2[MAXTOPICNAMELEN+1];
    int nRet;

    CTag *ptagTopic = plistTags->GetHead();
    ASSERT(ptagTopic);
    
    // Cycle through all the IF statements. Give back a FALSE if any
    // of them don't match.
    
    for(; pIf; pIf = pIf->next)
    {
    	switch(pIf->nType)
    	{
    	case ifTopicExists:
        {
            CTopic  *pTopic;

			if(pLog == NULL)
				return FALSE;

            PrintName(szNameBuf, pIf->apNameTok[0], pIf->anTokens[0],
                                ptagTag, ptagTopic);

            nRet = pLog->Search(szNameBuf, pTopic);
			if(nRet == FALSE)
				return FALSE;

			break;
        }
    			
    	case ifExpression: 
        {
            CString sLeft;
            CString sRight;

	        // Try to retrieve expression operands, which can consist of
	        // field references (from entry or topic tag) and text. 

	        PrintName(szNameBuf, pIf->apNameTok[0], pIf->anTokens[0], 
	                            ptagTag, ptagTopic);

            PrintName(szNameBuf2, pIf->apNameTok[1], pIf->anTokens[1],
	        				    ptagTag, ptagTopic);
			// Perform case-insensitive compare.
	        
	        if(_stricmp(szNameBuf, szNameBuf2))
	        	return FALSE;

			break;
        }
            
    	case ifTagExists:
		{
    		CTag *ptag;
			POSITION pos = plistTags->GetHeadPosition();
			BOOL bFound = FALSE;

            while(pos)
            {
                ptag = plistTags->GetNext(pos);

                if(_stricmp(pIf->sParam1, ptag->sTag) == 0)
				{
					bFound = TRUE;
                    break;
				}
            }

			if(FALSE == bFound)
				return FALSE;

			break;
    	}
    			
    	case ifFieldEmpty:
            if(ptagTag->aszFieldText[pIf->nParam1]    != NULL && 
               ptagTag->aszFieldText[pIf->nParam1][0] != '\0')
            {
                return FALSE;
            }
            break;

        default:
            ASSERT(0);

			return FALSE;
	    }
    }
    return TRUE;
}
CATCH(CMemoryException, e)
{
    return errMemory;
}
END_CATCH
}

