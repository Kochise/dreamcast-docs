#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "topiclog.h"
#include "docexpr.h"
#include "fmtspec.h"
#include "cmdargs.h"
#include "output.h"
#include "errmsg.h"

char szNewline[] = "\r\n";
char szAutoduckEscape[] = "<>/.@\\";

//@doc EXTERNAL

/*
@struct This structure defines an entry in a stack maintained
by the function that outputs a formatted topic. The stack keeps track of
the tag and tag-format information occurring at various output levels
within the topic.
*/

struct FORMATSTACK {
    CFmtPara 	*pfmtPara;		// @field Paragraph formatting information
    CTag 		*ptagPara;		// @field Extracted tag text for paragraph
    FORMATSTACK *next;			// @field Pointer to the next entry in stack
};
typedef struct FORMATSTACK *PFORMATSTACK;



/***************************************************************************************/

PFORMATSTACK Push(PFORMATSTACK pStack, CFmtPara *pfmtPara, CTag *ptag);
PFORMATSTACK Pop(PFORMATSTACK pStack);
PFORMATSTACK OutputParagraph(CTag *ptag, CFmtPara *pfmtPara, CCurTopicInfo &cur, PFORMATSTACK pStack);
void EmptyStack(PFORMATSTACK pStack, CCurTopicInfo &cur);
int ExtractTextTag(const char *&sz, CTag &tagText, int &nSrcLineOffset);

void OutputFormatChar(CCurTopicInfo &cur, const char *&sz, CFmtBase *pfmt);
void OutputField(CCurTopicInfo &cur, CTag *ptag, int  nField, char  cFieldRef);
void OutputFieldChar(CCurTopicInfo &cur, char ch);
void OutputTextTag(CCurTopicInfo &cur, CTag *ptag, const char *&sz, int &nSrcLineOffset);
int OutputBuildInfo(CCurTopicInfo &cur, const char *&sz, CTag *ptag, CFmtBase *pfmt);
void OutputDiagram(CCurTopicInfo &cur, CFmtBase *pfmt, const char *&sz, CTag *ptag);
int OutputIndex(CCurTopicInfo &cur, CFmtBase *pfmt, const char *&sz, CTag *ptag);
int OutputConstant(CCurTopicInfo &cur, const char *&sz);

void MakeContextString(char *szContext, const char *szText);

/***************************************************************************************/

CCurTopicInfo::CCurTopicInfo(
	CTopic *pTopic, 
	CFile &fileOutput, 
	FormatInfo &fmt, 
	RUNOPTIONS &run, 
	CTopicLog &log) : 
		m_pTopic(pTopic), m_fileOutput(fileOutput), m_fmt(fmt), m_run(run), m_log(log)
{
}



/***************************************************************************************/


inline void PrintFmtError(
	CCurTopicInfo &cur, 
	CFmtBase *pfmt, 
	int err)
{
	PrintError(cur.m_fmt.GetSrcFn(pfmt->GetSrcFn()), pfmt->GetSrcLineNum(), err);
}


inline void PrintTagError(
	CCurTopicInfo &cur,
	CTag *ptag,
	int nSrcLineOffset,
	int err)
{
	PrintError(cur.m_log.GetSrcFn(cur.m_pTopic->GetSrcFn()), 
					ptag->lSrcLineNum + nSrcLineOffset, 
					err);
}


/*
@func This function writes an Autoduck topic to the final output file.
*/

void OutputTopic(
	CTopic      *pTopic,
	RUNOPTIONS 	&run,
	FormatInfo 	&fmt,
	CFile      	&fileOutput,
    CFile       &fileTemp,
	CTopicLog  	&log)
{
    int nSrcLineOffset = 0;

    PFORMATSTACK pStack = NULL;
    CCurTopicInfo cur(pTopic, fileOutput, fmt, run, log);
    
    CFmtSrchTopic srchTopic;
	CFmtSrchPara  srchPara;
	CFmtTopic *pfmtTopic;
	CFmtPara  *pfmtPara;

    int nRet = pTopic->Read(fileTemp);
    if(nRet)
    {
        PrintError(run.sTempFile, NO_LINE, nRet);
        return;
    }

    CTagList &listTags = pTopic->GetTags();
    CTag *ptagHead = listTags.GetHead();
	CTag *ptag;

    int nCurLevel;
    
	// Get the topic formatting structure.

	srchTopic.m_sName = ptagHead->sTag;
	srchTopic.m_pLog  = &log;
	srchTopic.m_ptagTag = ptagHead;
	srchTopic.m_plistTags = &listTags;

	pfmtTopic = (CFmtTopic *)fmt.topic.Get(&srchTopic);
	if(NULL == pfmtTopic)
	{
		PrintTagError(cur, ptagHead, 0, warnNoTopicFormat);
		return;
	}
    
    // Output topic pre-text.

    OutputFormatString(cur, pfmtTopic, CFmtListTopic::tagPre, ptagHead);

    // Initialize tag list as "not output yet"

    POSITION posTag = listTags.GetHeadPosition();
    while( posTag )
        listTags.GetNext( posTag )->nState.WasOutput = FALSE;

    // Output topics named in order list.

    CString  *psGroup;
    POSITION posGroup = pfmtTopic->m_listParaTags.GetHeadPosition();
	while( posGroup != NULL )
	{
		psGroup = pfmtTopic->m_listParaTags.GetNext( posGroup );
		ASSERT(psGroup);

    	nCurLevel = MAXLEVEL;
    	
        posTag = listTags.GetHeadPosition();
        ptagHead = listTags.GetNext( posTag );
        while( posTag )
        {
            ptag = listTags.GetNext( posTag );

            // Skip tag if already dealt with.
            
            if(ptag->nState.WasOutput)
            	continue;
            	
		   	// Get the formatting struct for the tag.

			srchPara.m_sName 	= ptag->sTag;
			srchPara.m_pLog  	= &log;
			srchPara.m_ptagTag 	= ptag;
			srchPara.m_plistTags = &listTags;

			pfmtPara = (CFmtPara *)fmt.paragraph.Get(&srchPara);
			if(NULL == pfmtPara)
	    	{
	        	// Error: could not find format string for this tag
			        
	    		ptag->nState.WasOutput = TRUE;
			    				    	
	        	PrintTagError(cur, ptag, 0, warnNoParaFormat);
		    
	        	continue;
		    }
		    
		    // Determine whether to output tag. We output tag if the tag name
		    // matches the one we're looking for, OR if tag is subordinate to
		    // a tag previously output.
		    
		    // Does the tag name match? If so, record the level of the current
		    // tag; we will output this tag plus all following tags that are
		    // subordinate to the current one.
		    
		    if(0 == _stricmp(ptag->sTag, *psGroup))
		    {
			    nCurLevel = pfmtPara->GetLevel();

	           	pStack = OutputParagraph(ptag, pfmtPara, cur, pStack);
			}
			
			// We might still output the tag if the tag is one of a group of
			// subordinate-level tags immediately following a previously
			// matched tag.
			
			else if(pfmtPara->GetLevel() > nCurLevel)
			{
	           	pStack = OutputParagraph(ptag, pfmtPara, cur, pStack);
			}
			
			// Set the level to the max value, to indicate we have found the
			// last of the subordinate tags.
			
			else
			{
				nCurLevel = MAXLEVEL;			
			}
        }
    }

    // Output remaining tags (those not named within ordering list)

    posTag = listTags.GetHeadPosition();
    ptagHead = listTags.GetNext( posTag );
    while( posTag )
    {
        ptag = listTags.GetNext( posTag );

        if(ptag->nState.WasOutput)
            continue;

		srchPara.m_sName 	= ptag->sTag;
		srchPara.m_pLog  	= &log;
		srchPara.m_ptagTag 	= ptag;
		srchPara.m_plistTags = &listTags;

		pfmtPara = (CFmtPara *)fmt.paragraph.Get(&srchPara);
		if(NULL == pfmtPara)
    	{
        	// Error: could not find format string for this tag
		        
        	PrintTagError(cur, ptag, 0, warnNoParaFormat);
	    
        	continue;
	    }
	    
	    pStack = OutputParagraph(ptag, pfmtPara, cur, pStack);
    }
    
    // Output any residual tag post-texts and empty the stack.
    
    EmptyStack(pStack, cur);

    // Output topic post-text.
    
    OutputFormatString(cur, pfmtTopic, CFmtListTopic::tagPost, ptagHead);

	pTopic->FreeTagText();
}


/*
@func This function pushes a format/tag entry onto the formatting stack.

@parm PFORMATSTACK | pStack | The stack on which to push the entries.

@parm PFORMATENTRY | ptagfmt | The format entry to push.

@parm PTAG | ptag | The tag information to push.

@rdesc Returns the head of the new stack.
*/
PFORMATSTACK Push(
    PFORMATSTACK pStack,    //@parm The stack
    CFmtPara *pfmtPara,     //@parm The paragraph format.
    CTag *ptag)             //@parm The extracted tag.
{
    PFORMATSTACK pNew = new FORMATSTACK;
    
    pNew->next = pStack;
    pNew->pfmtPara = pfmtPara;
    pNew->ptagPara = ptag;
    
    return pNew;
}


/*
@func This function pops a format/tag entry
off the formatting stack and frees associated memory.

@rdesc Returns the head of the new stack.
*/
PFORMATSTACK Pop(
    PFORMATSTACK pStack)    //@parm The stack.
{
    PFORMATSTACK ret = pStack->next;
    
    delete pStack;
    
    return ret;
}


/*
@func void | EmptyStack | This function clears all entries from the
stack, freeing memory in the process. It also outputs post-text for
each stack entry.

@parm PFORMATSTACK | pStack | The stack to empty.

@parm PCURTOPICINFO | pcur | Specifies a pointer to a <t CURTOPICINFO>
structure containing information about the output temp file, 
formatting information, etc.

*/
void EmptyStack(PFORMATSTACK pStack, CCurTopicInfo &cur)
{
    while(pStack)
    {
        OutputFormatString(cur, pStack->pfmtPara, CFmtListPara::tagPost, pStack->ptagPara);
        
        pStack = Pop(pStack);
    }
}

/*

@func This function adjusts the contents of the formatting stack. 
It performs all the work required for handling levels within entry tags.

@parm PFORMATSTACK | pStack | The stack to adjust.

@parm PFORMATENTRY | ptagfmt | Specifies a pointer to a <t FORMATENTRY>
structure containing the formatting information for the currently 
processed tag.

@parm PTAG | ptag | Specifies a pointer to a <t TAG> structure 
containing the field values for the currently processed tag.

@parm PCURTOPICINFO | pcur | Specifies a pointer to a <t CURTOPICINFO>
structure containing information about the output temp file, 
formatting information, etc.

@rdesc Returns a pointer to a <t FORMATSTACK> structure containing
the head of the new stack.

@comm This function performs one of a series of actions depending on how
the current tag (represented by <p ptagfmt> and <p ptag>) compares to the
tag on the head of the stack.

If the stack is empty, we output the pre-text for the current tag and push
the current tag onto the stack.

If the tag names are the same, we don't change configuration of the stack
or output any pre/post text; we just substitute the field information of 
the current tag for the field information stored on the stack (for the 
previous tag).

If the tag names are different, and the current tag has a higher level
value than the stack value, we are descending to a lower tag level. We
output the pre-text for the current tag and push the current tag onto
the stack.

If the tag names are different, and the current tag has the same level
as the stack value, we output the post-text for the stack value; output
the pre-text for the current value; and substitute the current tag
values for the values stored on the head of the stack.

If the tag names are different, and the current tag has a lower level 
value, we need to pop tag values off the stack. We output the post-text
for the stack value, pop the stack, and recurse. The next function
call will need to look at all the preceding situations and proceed
accordingly.
*/
PFORMATSTACK AdjustStack(
    PFORMATSTACK pStack, 
    CFmtPara *pfmtPara, 
    CTag *ptag,
    CCurTopicInfo &cur)
{
    // If stack empty, output pre-text for the current tag & push the current
    // tag onto stack.
                        
    if(NULL == pStack)
    {
        OutputFormatString(cur, pfmtPara, CFmtListPara::tagPre, ptag);
            
        return Push(pStack, pfmtPara, ptag);
    }
    
    // Same tag name? Just substitute current tag information on topmost stack
    // entry, then return. Don't need to output anything because tag isn't changing
            
    if(0 == _stricmp(pStack->ptagPara->sTag, ptag->sTag))
    {
        pStack->ptagPara = ptag;
        return pStack;
    }
        
    // Current level value is higher. Output pre text for current level value
    // and push current level values onto stack.
        
    if(pfmtPara->GetLevel() > pStack->pfmtPara->GetLevel())
    {
        OutputFormatString(cur, pfmtPara, CFmtListPara::tagPre, ptag);
                        
        return Push(pStack, pfmtPara, ptag);
    }
        
    // Current level value is same. Output post text for stack tag; switch stack
    // values to use the current ones; and output pre text for current tag.
        
    if( pfmtPara->GetLevel() == pStack->pfmtPara->GetLevel() )
    {
        OutputFormatString(cur, pStack->pfmtPara, CFmtListPara::tagPost, pStack->ptagPara);
                        
        pStack->pfmtPara = pfmtPara;
        pStack->ptagPara = ptag;
                        
        OutputFormatString(cur, pfmtPara, CFmtListPara::tagPre, ptag);
                    
        return pStack;
    }
        
    // Current level value is lower. Output post text for stack tag; pop stack;
    // and recurse (there may be more values to pop!)
        
    OutputFormatString(cur, pfmtPara, CFmtListPara::tagPost, pStack->ptagPara);
                
    return AdjustStack(Pop(pStack), pfmtPara, ptag, cur);
}



/*
@func Outputs a single autoduck tag to the output file. The output 
generation is controlled by the format information string for the tag.
       
@rdesc Returns a pointer to the new formatting stack.
*/

PFORMATSTACK OutputParagraph(
    CTag 			*ptag,		//@parm Tag to output.
    CFmtPara 		*pfmtPara,	//@parm Formatting information for tag.
	CCurTopicInfo 	&cur,		//@parm Topic log, output file, etc.
    PFORMATSTACK 	pStack)		//@parm Format/tag info stack used to track
								//  the output state, when to print pre/post
{								//  format strings, etc.

    if(pfmtPara->GetNumFields() != ptag->nFields)
    {
        // Error: number of fields did not match
        PrintTagError(cur, ptag, 0, warnWrongNumFields);
        
        // Don't return on this error, go ahead and generate some output
    }
    
    pStack = AdjustStack(pStack, pfmtPara, ptag, cur);

    OutputFormatString(cur, pfmtPara, CFmtListPara::tagFormat, ptag);

    ptag->nState.WasOutput = TRUE;

    return pStack;
}



//@func Outputs a single character from a format string, handling
// escape sequences correctly.
//
//@rdesc Returns a pointer to the next character in the string.

void OutputFormatChar(
    CCurTopicInfo &cur,     //@parm Output state
	const char *&sz,		//@parm Front of string to output - updated with
							// new character position after output
	CFmtBase *pfmt)         //@parm Parent formatting block
{
	CFile &fileOutput = cur.m_fileOutput;    
    
    switch(*sz)
    {
    case chCaret:               // Handle escapes
        switch(sz[1])
        {
        case chCaret:
            fileOutput.Write(&sz[1], 1);
			sz += 2;
			break;
            
        case 'n':
            fileOutput.Write(szNewline, strlen(szNewline));
            sz+2;
			break;
            
        default:
            fileOutput.Write(sz, 1);
            PrintFmtError(cur, pfmt, warnBadFmtEscapeSequence);
            sz++;
			break;
		}
		break;
        
    default:
        fileOutput.Write(sz, 1);
        sz++;
        break;
    }
}


/*****************************************************************************
* Format String Output and Helper Functions
*/

/*
@func This function retrieves the next tag structure with a name
matching the specified name.

@rdesc Returns the tag structure if a match is found; otherwise
returns NULL.
*/
CTag *GetNextTag(
	CTagList &listTags,     //@parm Specifies a pointer to a list of tags.
	const char *szTag,	    //@parm Specifies the name to search for.
    POSITION &posTag)       //@parm List iterator position
{
    CTag *ptag;

    while( posTag )
    {
        ptag = listTags.GetNext( posTag );

        if(_stricmp(szTag, ptag->sTag) == 0)
            return ptag;
    }
    
    return NULL;
}

/*
@func This function outputs a formatting string
(read from the formatting file) to the output temp file. A formatting
string can contain a mixture of straight RTF text and field references.
*/
void OutputFormatString(
    CCurTopicInfo &cur,     //@parm Topic environemnt information
    CFmtBase *pfmt,			//@parm Formatting block to use
	int  nFmt,				//@parm Which format string to output
    CTag *ptag)             //@parm Tag to output
{
    const char *sz = pfmt->GetFmtString(nFmt);

    OutputFormatString(cur, sz, pfmt, ptag);
}

/*
@func This function outputs a formatting string
(read from the formatting file) to the output temp file. A formatting
string can contain a mixture of straight RTF text and field references.
*/
void OutputFormatString(
    CCurTopicInfo &cur,     //@parm Topic environemnt information
    const char *sz,         //@parm Formatting string
    CFmtBase *pfmt,			//@parm Parent formatting block
    CTag *ptag)             //@parm Tag to output
{
    int nFieldIndex;
    int nSrcLineOffset = 0;
	int nRet;
    
    CTag *ptagRef;
    
    // Generate output for tag according to format info string

    while (*sz != '\0')
    {
        if(*sz == chDollar || *sz == chPound)
        {
            // Escape
            
            if(sz[1] == sz[0])
            {
                // Handle escaped field reference character
				sz++;

                OutputFormatChar(cur, sz, pfmt);

                continue;
            }

            // Tag field reference

            if(isdigit(sz[1]))
            {
                if(NULL == ptag)
                {
                    PrintFmtError(cur, pfmt, warnTagFieldUnavailable);
                    sz += 2;
                    continue;
                }

                // Looks like a field reference, check digit
                nFieldIndex = atoi(sz+1) - 1;
                if(nFieldIndex > MAXNUMFIELDS || NULL == ptag->aszFieldText[nFieldIndex])
                {
                    PrintError(cur.m_log.GetSrcFn(cur.m_pTopic->GetSrcFn()), 
								ptag->lSrcLineNum, warnBadFieldReference);
					PrintFmtError(cur, pfmt, warnBadFieldReference);
                }
                else
                {
	                // If field reference is valid, output field
                    OutputField(cur, ptag, nFieldIndex, *sz);
                }

                sz += 2;

                continue;
            }

            // Topic field reference
            
            if( isalpha(sz[1]) )
            {
                if(NULL == cur.m_pTopic)
                {
                    PrintFmtError(cur, pfmt, warnTopicFieldUnavailable);
                    sz += 2;
                    continue;
                }
                
                // Topic field reference. First see if topic tag matches, then check digit.
                
                static char szTopicFieldRefStop[] = ". \n\t0123456789";
                const char *szEnd = SeekEnd(sz+1, szTopicFieldRefStop, MAXTAGSIZE);

                // Check basic syntax first

                if(szEnd == NULL || !(chPeriod == szEnd[0] && isdigit(szEnd[1])) )
                {
					OutputFormatChar(cur, sz, pfmt);

                    PrintFmtError(cur, pfmt, warnBadTopicFieldReference);

                    continue;
                }

                CString sFieldTopicName(sz+1, szEnd-sz-1);
                CTagList &listTags = cur.m_pTopic->GetTags();
                POSITION posTag = listTags.GetHeadPosition();
                if(ptagRef = GetNextTag(listTags, sFieldTopicName, posTag))
                {
	                nFieldIndex = atoi(szEnd+1) - 1;
	                if (nFieldIndex > MAXNUMFIELDS || NULL == ptagRef->aszFieldText[nFieldIndex])
	                {
	                	// Invalid field reference
						PrintError(cur.m_log.GetSrcFn(cur.m_pTopic->GetSrcFn()), 
								ptag->lSrcLineNum, warnBadTopicFieldReference);
                        PrintFmtError(cur, pfmt, warnBadTopicFieldReference);
	                }
	                else
	                {
		                // If field reference is valid, output field
	                    OutputField(cur, ptagRef, nFieldIndex, *sz);
	                }
                }

               	sz = szEnd + 2;

                continue;
            }
            
            // Pound symbol, not followed by a field reference - output as literal.
            
            if(*sz == chPound)
            {
				OutputFormatChar(cur, sz, pfmt);

                continue;
            }


            // Build information

            if (chExclamation == sz[1])
            {
	           	nRet = OutputBuildInfo(cur, sz, ptag, pfmt);
                if(nRet)
					PrintFmtError(cur, pfmt, nRet);

                continue;
	        }
            
            // Index
            
            if( chOpenBracket == sz[1] && (_strnicmp(&sz[2], "index", 5) == 0))
            {
        		nRet = OutputIndex(cur, pfmt, sz, ptag);
                if(nRet)
                    PrintFmtError(cur, pfmt, nRet);

                continue;
            }

            // Diagram
            
            if (chOpenBracket == sz[1])
			{
                OutputDiagram(cur, pfmt, sz, ptag);

                continue;
            }

            // Constant

            if (chOpenParen == *(sz+1))
            {
            	nRet = OutputConstant(cur, sz);
                if(nRet)
                    PrintFmtError(cur, pfmt, nRet);

                continue;
    		}

            // Invalid field reference ($ not followed by digit). Output the
			// char as a literal and print a warning.

            PrintFmtError(cur, pfmt, errBadFieldRef);
			
			OutputFormatChar(cur, sz, pfmt);
        }
        
        else
        {
			OutputFormatChar(cur, sz, pfmt);
        }
    }
}    


/*****************************************************************************
* Field Output and Helper Functions
*/

//@func Outputs a character from an Autoduck source field to the output
// file. Uses the token definition section in the format file to weed
// out special characters such as tabs and high=ascii codes, and outptu
// the appropriate information.

void OutputFieldChar(
    CCurTopicInfo &cur,  //@parm Output file.
    char ch)   			 //@parm Character to output.
{
	static CFmtToken *pfmtToken = NULL;
	
	if(pfmtToken == NULL)
		pfmtToken = (CFmtToken *)cur.m_fmt.token.Get(NULL);

	ASSERT(pfmtToken);

	CFile &fileOutput = cur.m_fileOutput;
	const char *szToken;

	// Characters that must be escaped given this output type
    if( pfmtToken->IsToken(ch) )
    {                                 
        szToken = pfmtToken->GetToken(ch);
    
        fileOutput.Write(szToken, strlen(szToken));
    }
	
    // Output extended ASCII character
    else if( ((unsigned char)ch) > 127)
    {

		szToken = pfmtToken->GetHighCharMask();
		char szHighChar[MAXTAGSIZE];

        sprintf(szHighChar, szToken, (unsigned char)ch);
        fileOutput.Write(szHighChar, strlen(szHighChar));
    }

	else
	{
    	fileOutput.Write(&ch, 1);
	}
}


/*
@func Strips leading whitespace (space 
    and tab characters) from all lines in the given buffer.
*/
void StripLeadingWhiteSpace(
	char *szLine)				//@parm Line to trim leading whitespace from
{
    char *sz;
    
    sz = szLine;

    while (*sz)
    {
        // Find first non-whitespace character in line
        while (((chSpace == *sz) || (chTab == *sz)) && *sz)
        {
            ++sz;
        }

        // Copy remainder of line (overwriting the original string)
        while (*sz)
        {
            *szLine++ = *sz++;
            if (chNewline == *(sz-1))
                break;
        }
    }
    *szLine = '\0';  // add terminating NULL
}






/*
@func void | AdjustExampleWhiteSpace | Adjusts leading whitespace
for example source code lines. Adjusts whitespace by calculating
the amount of leading whitespace on first non-blank line and
subtracting this amount from the leading whitespace on each line.

Specify output tab size in format information file?
*/
void AdjustExampleWhiteSpace(
	char *&szField, 			//@field Field to adjust
	int nTabSize)				//@field Tab size to use
{
    char *szSrc, *szDest;
    int nNumSpacesToRemove = 0;
    int nNumSpacesAdjusted;
    int nNumSpaces;
    int nNewBufSize;
    char *szNewField;
    
    // Set working pointers
    szSrc = szField;
    
    // Locate first non-blank line
    while (*szSrc && ((chSpace == *szSrc) || (chTab == *szSrc) || (chNewline == *szSrc)))
        ++szSrc;
    
    // If whitespace encountered, walk back and determine 
    // amount of whitespace to remove
    if (szSrc > szField)
    {
        --szSrc;
        while(1)
        {
            if (chSpace == *szSrc)
                ++nNumSpacesToRemove;
            else if (chTab == *szSrc)
                nNumSpacesToRemove += nTabSize;
            else if (chNewline == *szSrc)
            {
                // At least one blank line must have preceded, maintain 
                ++szSrc;
                break;
            }
            else
			{
				ASSERT(0);
			}
            
            // Don't walk past beginning of buffer
            if(szSrc == szField)
                break;
            else
                --szSrc;
        }
    }
    else    // No whitespace in first line
    {
        return;
    }
    
    // Allocate a new buffer
    nNewBufSize = 2 * strlen(szField);
    szNewField = new char[nNewBufSize];
	ZeroMem(szNewField, nNewBufSize);

    szDest = szNewField;

    // Walk the buffer, adjusting leading whitespace for each line
    while (*szSrc)
    {
        // Count leading whitespace in line
        nNumSpaces = 0;
        while ((chSpace == *szSrc) || (chTab == *szSrc))
        {
            if (chSpace == *szSrc)
                ++nNumSpaces;
            else if (chTab == *szSrc)
                nNumSpaces += nTabSize;
            
            ++szSrc;
        }

        // Output adjusted whitespace
        // Note: MSGRIDA1 tab=4
        // Maybe output tab size should be specified by format info?
        nNumSpacesAdjusted = nNumSpaces - nNumSpacesToRemove;
        if (nNumSpacesAdjusted > 0)
        {
            while (nNumSpacesAdjusted > 0)
            if (nNumSpacesAdjusted >= nTabSize)
            {
                *szDest++ = chTab;
                nNumSpacesAdjusted -= nTabSize;
            }
            else
            {
                *szDest++ = chSpace;
                --nNumSpacesAdjusted;
            }
            
            // Don't write past end of buffer
            ASSERT(szDest < (szNewField + nNewBufSize));
        }
        
        // Copy remainder of line
        while (*szSrc)
        {
            *szDest++ = *szSrc++;
            if (chNewline == *(szSrc-1))
                break;
            
            // Don't write past end of buffer
            ASSERT(szDest < (szNewField + nNewBufSize));
        }
    }

    *szDest = '\0';  // add terminating NULL

    // Free original buffer
	delete szField;

	szField = szNewField;
}



/*
@func Converts the specified string to a valid WinHelp context string.
Valid characters include:

- alphanumerics

- underscores

Spaces and colons are converted to underscores.

High-ascii characters are converted to the form ".xx" where
"xx" is the hexadecimal value for the character.

Template specifications are stripped.
*/
void MakeContextString(
    char *szContext,        // @parm Destination buffer of at least 256 bytes
    const char *szText)     // @parm Source string.
{
    char szCode[6];
    int i, j;
    const char *szT;

    ASSERT(szText);

    // @comm Context string is generated using the specified string.
    // Legal context string characters in the string are copied exactly.
    // Spaces and colons are converted to underscores.
    // Other characters are converted to a period, followed by the hex
    // number for the character.

    for(i = 0; i < 255 && *szText; szText++)
    {
        if(chBackslash == *szText)
        {
            // Skip over backslashes
        }
        else if(isalnum(*szText) || chUnderscore == *szText || chPeriod == *szText)
        {
			// Legal characters as is

            szContext[i++] = *szText;
        }
        else if(chSpace == *szText || chColon == *szText)
        {
            szContext[i++] = chUnderscore;
        }
        else
        {
            // If this is a C++ template (matching angle brackets), then
            // we lop off the template arguments

            if(chOpenAngle == *szText)
            {
                szT = MatchParen(szText, chCloseAngle);
                if(*szT)
                    break;
            }

            
			// illegal chars converted to ".xx"
			szCode[0] = chPeriod;
            _itoa((unsigned char)*szText, &szCode[1], 16);

            for(j = 0; szCode[j] && i < 255; j++, i++)
                szContext[i] = szCode[j];
        }
    }
    szContext[i] = 0;
}




/*-----------------------------------------------------------------------
@func Outputs a single autoduck field to a 
given temporary file. Performs some processing of newline
characters (see comments) and calls <f OutputSpecial> to expand
type/special formatting characters.
        
@comm If field is example code, <f OutputField> calls 
<f AdjustExampleWhiteSpace> function to
clean up indentation. This will cause the memory block containing the
field text to be reallocated. <f OutputField> adjusts the
<t TAG> structure by storing the address of the new memory block. 

If a single newline character is followed by additional text, 
<f OutputField> inserts a space character before the 
newline<em->trailing whitespace has already been stripped from 
all lines.
*/
void OutputField(
    CCurTopicInfo &cur,     //@parm Topic state info
    CTag *ptag,             //@parm Parent tag of field
    int  nField,            //@parm Which field to output
    char  cFieldRef)        //@parm Field reference character:
                            //  @flag $ | Output contents of field normally.
                            //  @flag # | Convert to context string.
{
    char *szField;
    char szContext[MAXCONTEXT+1];
	int nSrcLineOffset = 0;

    // Validate that there is a field to output
    if (NULL == ptag->aszFieldText[nField])
        return;

    // Strip/adjust leading whitespace
    if (ptag->nState.IsExample && nField+1 == ptag->nFields)
    {
        AdjustExampleWhiteSpace(ptag->aszFieldText[nField], 
                                    cur.m_run.nExampleTabSize);
    }
    else
    {
        StripLeadingWhiteSpace(ptag->aszFieldText[nField]);
    }

    // Process context strings first - easy.

    if (chPound == cFieldRef)
    {
        MakeContextString(szContext, ptag->aszFieldText[nField]);
        
        szField = szContext;

        cur.m_fileOutput.Write(szContext, strlen(szContext));

        return;
    }

    // Process $ fields now.
    
    szField = ptag->aszFieldText[nField];
        
    // Output contents of field
    while (*szField)
    {
        // Look for newline character
        if(chNewline == *szField)
        {
            // Example field - insert paragraph after each newline.

            if(ptag->nState.IsExample && nField+1 == ptag->nFields)
            {
                // Single newline wraps example source code

				OutputFieldChar(cur, chNewline);
                cur.m_fileOutput.Write(szNewline, strlen(szNewline));
            }
            
            // Two newlines - insert a paragraph for regular fields.

            else if(chNewline == szField[1])
            {
				OutputFieldChar(cur, chNewline);
                cur.m_fileOutput.Write(szNewline, strlen(szNewline));

                szField++;
                nSrcLineOffset++;
            }
            
            // Single newline followed by text - just a space

            else if(szField[1] != '\0')
            {
                cur.m_fileOutput.Write(" ", 1);
                cur.m_fileOutput.Write(szNewline, strlen(szNewline));
            }

            // If field ends here, don't write anything.

            ++szField;
            ++nSrcLineOffset;

            continue;
        }

        // Look for escaped characters
        if (chBackslash == *szField)
        {
            if(ptag->nState.IsExample && nField+1 == ptag->nFields)
            {
                // The only significant escaped characters in example
                // code are forward slash (to allow comments)
                // and '@' to allow autoduck source examples

                switch(szField[1])
                {
                // Escape characters

                case chSlash:
                case chAmpersand:
                    
                    ++szField;
                    OutputFieldChar(cur, *szField++);

                    break;

                default:

				// Output the backslash as is.

                    OutputFieldChar(cur, *szField++);

                    break;
                }

                continue;
            }
            
            // Other field references can contain escaped type 
            // or special formatting characters

            if(strchr(szAutoduckEscape, szField[1]))
            {
                // Output escaped character

                ++szField;
                OutputFieldChar(cur, *szField++);
            }
            else
            {
                // Output backslash as is.

				OutputFieldChar(cur, *szField++);
            }

            continue;

        }

        // Look for type or special formatting
        // (not allowed within example source code and context strings)

        if ((chOpenAngle == *szField) && 
            !(ptag->nState.IsExample && nField+1 == ptag->nFields))
        {
            // Handle special character and type formatting
            OutputTextTag(cur, ptag, szField, nSrcLineOffset);

            continue;
        }

        // Output character

        OutputFieldChar(cur, *szField++);
    }
}

/*****************************************************************************
* Text Tag Output & Helper Functions
*/


/*
@func This function extracts the fields of a text tag.

@rdesc Returns zero if successful or an error code.
*/

int ExtractTextTag(
	const char *&sz,           //@parm Points to start of text tag name.
								// Value updated with ending tag position.
	CTag &tagText,             //@parm TAG structure to fill with text fields
    int &nSrcLineOffset)       //@parm Offset from start of parent
{
	int i, j, k, nFieldLen;
    const char *szField;
	const char *szEnd;

    // Find the end of the text tag.
    
    szEnd = sz;
	do
	{
		if(*szEnd == chCloseAngle)
		{
			if(!(szEnd != sz && *(szEnd-1) == chBackslash))
				break;
		}

	} while(*++szEnd);

	if(*szEnd != chCloseAngle)
		return warnMissingTextTagTerminator;

    // Grab the tag fields.

    szField = sz;

    while(*szField && *szField != chCloseAngle)
    {
        if( MAXNUMFIELDS == tagText.nFields )
            return warnTooManyTextFields;

        // Add the field to the tag. Allocate a block of 
        // memory for the field equal to the remaining
        // text.
        
        k = tagText.nFields;

        szField = EatWhite(szField);
		
		nFieldLen = szEnd - szField;

        tagText.aszFieldText[k] = new char[nFieldLen+1];

        ZeroMem(tagText.aszFieldText[k], nFieldLen+1);
        
    	// Add characters to the field through the end (a field separator
        // or the end of the text tag).
        //
        // K is the field number
        // j is the character number within the field.
        // szField is updated to the next character to be added.
    	
    	j = 0;
        int nContinueField = TRUE;

    	while(nContinueField)
        {
            switch(*szField)
            {
            case chColon:
				if(*(szField+1) == chColon)
					szField++;

            case chPeriod:
                
                // Next character.

                szField++;

                // fall through - for angle bracket we don't want to advance
                // past it, because it terminates the outermost loop.

            case chCloseAngle:

                // next field

                tagText.nFields++;

                // Break out of loop.

                nContinueField = FALSE;

                break;
            
            case chBackslash:

            	switch(*(szField+1))
            	{
                // These are text-tag-specific escapes, and need to be converted
                // before handing the fields over to the format string outputter.

            	case chCloseAngle:
            	case chPeriod:
				case chColon:

                    tagText.aszFieldText[k][j++] = *(szField+1);
                    szField += 2;
                    break;

                // These are not converted, the backslash is passed in to the
                // field and ends up being parsed by <f OutputFormatString>.

    			default:

                    tagText.aszFieldText[j][i++] = *szField++;
                    tagText.aszFieldText[j][i++] = *szField++;
                    break;
                }

            break;

            case chNewline:
                
                nSrcLineOffset++;

                // fall through
           
            default:
                tagText.aszFieldText[k][j++] = *szField++;

                break;
			}
        }
    }
	
    sz = ++szEnd;
    
    return 0;
}


/*-----------------------------------------------------------------------
@func Parses a text tag and outputs the specified format string to the
temporary file.

@parm Current topic state.

@parm Parent paragraph or topic tag for the text tag.

@parm Points to the beginning of the text tag, on the opening angle
bracket. Updated with the ending position of the text tag (one character
beyond the closing angle bracket).

@parm Offset of text tag from start of parent tag.

*/

void OutputTextTag(CCurTopicInfo &cur, CTag *ptag, const char *&szField,
	int &nSrcLineOffset) 
{
    CTag tagText;
    char szTag[MAXTAGSIZE+1];

    int i;
    
    CFmtSrchText srchText;
    CFmtText    *pfmtText;
    
    // parser assumes we have an open angle bracket
    ASSERT(chOpenAngle == *szField);

    // get the tag name.

    szField = EatWhite(++szField);
    for(i = 0; istagchar(szField[i]) && i < MAXTAGSIZE; i++)
        szTag[i] = szField[i];

    if( i == 0 || (i == MAXTAGSIZE && istagchar(szField[i])) )
    {
        PrintTagError(cur, ptag, nSrcLineOffset, fmterrBadTagName);

        return;        
    }
	szTag[i] = '\0';

    // Initialize pseudo-TAG structure
    
    tagText.sTag = szTag;
    tagText.lSrcLineNum = ptag->lSrcLineNum + nSrcLineOffset;
    
    // Try to extract the text fields.
    
    szField += i;
    int nSrcLineSave = nSrcLineOffset;
    int nRet = ExtractTextTag(szField, tagText, nSrcLineOffset);
    if(nRet)
    {
        PrintTagError(cur, ptag, nSrcLineOffset, nRet);

        return;
    }
    
    // get the format string.

    srchText.m_sName = szTag;
    srchText.m_pLog = &cur.m_log;
    srchText.m_ptagTag = &tagText;
    srchText.m_plistTags = &cur.m_pTopic->GetTags();

    pfmtText = (CFmtText *)cur.m_fmt.text.Get(&srchText);
    if(NULL == pfmtText)
    {
        PrintTagError(cur, ptag, nSrcLineSave, warnNoTextFormat);

        return;
    }

    if(pfmtText->GetNumFields() != tagText.nFields)
    {
        PrintTagError(cur, ptag, nSrcLineSave, warnWrongNumTextFields);
        return;
    }

    // Generate output according to format string
    
    OutputFormatString(cur, pfmtText, CFmtListText::tagFormat, &tagText);
}



/*****************************************************************************
* Build Info
*/


/*
@func This function outputs a special build-information field, such as the current filename,
date, or time.

@rdesc Returns a pointer to the character following the build information field.
*/
int OutputBuildInfo(
	CCurTopicInfo &cur,	    		//@parm Output state including topic.
	const char *&szField,   		//@parm Build info specifier.
	CTag *ptag,						//@parm Tag information structure (can be NULL). Used
                                    // for error reporting.
    CFmtBase *pfmt)                 //@parm Format tag structure, used for error reporting.
{
    char szChar[MAXCONTEXT+1];
    char szFname[_MAX_FNAME+1];
    char szExt[_MAX_EXT+1];

	CFile &fileOutput = cur.m_fileOutput;

    int nRet = 0;

    char *sz;

    szField+=2;

    szChar[0] = '\0';
        
    switch(*szField)
    {
    case 'D':
    case 'd':
    	// output the date
    	_strdate(szChar);

        break;
    	
    case 'l':
    case 'L':
        // output the tag line number
        if(ptag)
        	sprintf(szChar, "%l", ptag->lSrcLineNum);
        break;

    case 'f': 
    case 'F':
    	// Output file name
    	if(ptag)
    	{
			_fullpath(szChar, cur.m_log.GetSrcFn(cur.m_pTopic->GetSrcFn()), _MAX_PATH);
			_splitpath(szChar, NULL, NULL, szFname, szExt);

            strcpy(szChar, szFname);
            strcat(szChar, szExt);
		}
		break;
                                                                                                                      
    case 'p':
    case 'P':
    	// Output full path name
    	if(ptag)
    	{
			_fullpath(szChar, cur.m_log.GetSrcFn(cur.m_pTopic->GetSrcFn()), _MAX_PATH);
			
			// Convert forward slashes to back slashes - more
			// universally accepted

			for(int i = 0; szChar[i]; i++)
			{
				if(szChar[i] == chBackslash)
					szChar[i] = chSlash;
			}
		}
        break;
        
    case 'n':
	case 'N':
		if(cur.m_pTopic)
			strcpy(szChar, cur.m_pTopic->GetName());
		break;

	case 'c':
	case 'C':
		if(cur.m_pTopic)
			MakeContextString(szChar, cur.m_pTopic->GetContext());
		break;

	default:

        nRet = warnUnknownBuildConstant;

        break;
	}

	if(isupper(*szField))
		_strupr(szChar);

	if(!nRet)
	{
	    for(sz = szChar; *sz; sz++)
	        OutputFieldChar(cur, *sz);
        szField++;
	}

    return nRet;
}


/*****************************************************************************
* Constants
*/

/*
@func This function parses a constant reference in a formatting
string, and outputs the named constant.

@rdesc Pointer to the first character following the constant
reference in the formatting string.
*/

int OutputConstant(
    CCurTopicInfo &cur, 
    const char *&sz)
{
    const char *szEnd;
    static char szConstNameTerm[] = ")\n\r \t";

    CFmtSrchConst srch;
    CFmtConst *pfmt;

    sz += 2;

    szEnd = SeekEnd(sz, szConstNameTerm, MAXTAGSIZE);
    if(szEnd == NULL || *szEnd != chCloseParen)
        return warnBadConstantReference;
    
    CString sConstName(sz, szEnd-sz);
    srch.m_sName = sConstName;

    pfmt = (CFmtConst *)cur.m_fmt.constant.Get(&srch);
    if(NULL == pfmt)
        return warnNoConstFormat;
    
    CString &sFmt = pfmt->GetFmtString(CFmtListConst::tagDefine);

    cur.m_fileOutput.Write(sFmt, sFmt.GetLength());

    sz = szEnd+1;

    return 0;
}


/*****************************************************************************
 * Diagram Output & Helper Functions
 */


/*
@func This function checks to see if a tag with a specified name appears
in the topic.

@rdesc Returns TRUE if the tag is found.
*/

int HasNullParas(
	CTagList  &listTags, 		//@parm Specifies the first tag in the list.
    CStrArray &asParas)         //@parm Specifies a list of names to look for.
{
	CTag *ptagT;
    int  nLen = asParas.GetSize();
    int  i;
    POSITION posTag = listTags.GetHeadPosition();
    while(posTag)
	{
        ptagT = listTags.GetNext(posTag);

        for(i = 0; i < nLen; i++)
        {
            if(_strcmpi(*asParas[i], ptagT->sTag) == 0)
			    return TRUE;
        }
	}
	return FALSE;
}


/*

@func This function outputs a syntax diagram.

*/
void OutputDiagram(
    CCurTopicInfo &cur,     //@parm Topic output state information
    CFmtBase *pfmtParent,   //@parm Parent formatting tag
    const char *&sz,        //@parm Beginning of diagram spec in format string
    CTag *ptagParent)       //@parm Parent tag
{
    CTagList &listTags = cur.m_pTopic->GetTags(); 

    const char *szName;
    static char szDiagramNameTerm[] = "]\n\r \t";

    // Get the diagram name.
    sz = EatWhite(sz+2);

    szName = sz;
    while(istagchar(*sz))
        sz++;

    if(szName == sz || *sz != chCloseBracket)
    {
        PrintFmtError(cur, pfmtParent, warnBadDiagramReference);
        return;
    }


    // Construct the diagram name.

    CString sDiagramName(szName, sz-szName);

    // advance past the close parenthesis.

    sz ++;

    // Find the diagram formatting string.

    CFmtSrchTag srch;
    CFmtDiagram *pfmt;

    srch.m_sName = sDiagramName;
    srch.m_pLog  = &cur.m_log;
    srch.m_ptagTag = ptagParent;
    srch.m_plistTags = &cur.m_pTopic->GetTags();

    pfmt = (CFmtDiagram *)cur.m_fmt.diagram.Get(&srch);
    if(NULL == pfmt)
    {
        PrintFmtError(cur, pfmtParent, warnNoDiagramFormat);
        return;
    }

    // See if there are any "poision paragraphs" in this topic.
    
    if(HasNullParas(listTags, pfmt->GetNullParas()))
        return;

    OutputFormatString(cur, pfmt, CFmtListDiagram::tagPre, ptagParent);
    
    // Output the first tag
    POSITION posTag = listTags.GetHeadPosition();
    CTag *ptag = GetNextTag(listTags, pfmt->GetDiagramItem(), posTag);
    CTag *ptagNext;

    if(ptag)
    {
        CString &sFmtFirst = pfmt->GetFmtString(CFmtListDiagram::tagFormatFirst);
        if(!sFmtFirst.IsEmpty())
            OutputFormatString(cur, pfmt, CFmtListDiagram::tagFormatFirst, ptag);
        else
            OutputFormatString(cur, pfmt, CFmtListDiagram::tagFormat, ptag);

        // Output the middle tags, if any

        ptag = GetNextTag(listTags, pfmt->GetDiagramItem(), posTag);
        while( ptag && (ptagNext = GetNextTag(listTags, pfmt->GetDiagramItem(), posTag))  )
        {
            OutputFormatString(cur, pfmt, CFmtListDiagram::tagFormat, ptag);
            ptag = ptagNext;
        }
        
        // Output the last tag, if one exists
        if(ptag)
        {
            CString &sFmtLast = pfmt->GetFmtString(CFmtListDiagram::tagFormatLast);
            if(!sFmtLast.IsEmpty())
                OutputFormatString(cur, pfmt, CFmtListDiagram::tagFormatLast, ptag);
            else
                OutputFormatString(cur, pfmt, CFmtListDiagram::tagFormat, ptag);
        }
    }
        
    OutputFormatString(cur, pfmt, CFmtListDiagram::tagPost, ptagParent);
}


/*****************************************************************************
 * Index Output & Helper Functions
 */


//@func Evaluate topic to determine whether to include it in the
// index. Can evaluate tag name and extraction flags.

BOOL UseTopicInIndex(
	const char *szTag, 		//@parm Tag name for topic
	const char *szFlags, 	//@parm Flags for topic
	CExprToken &exprTags,	//@parm Topic tag name filter
	CExprToken &exprFlags)	//@parm Topic doc flags filter
{
	CString sTagCopy;

	// Compare tags...

	CopyFlags(sTagCopy, szTag);

	return exprTags.Eval(sTagCopy) && exprFlags.Eval(szFlags);
}


/*
@func void | OutputWinHelpIndex | Generates a Help index
    from the list of topic logs.

@parm PTOPICLOGHEAD | phead | Specifies a pointer to a
    <t TOPICLOGHEAD> structure containing the list of
    topic log structures.
    
@parm FILE * | fh | Specifies the file handle of the output file.
    
@rdesc Void.
*/
int OutputIndex(
    CCurTopicInfo &cur,     //@parm Topic output state
    CFmtBase *pfmtParent,   //@parm Parent formatting tag
    const char *&sz,        //@parm Index specification
    CTag *ptagParent)       //@parm Parent formatting tag
{
	int nRet;
    CMemFile        memfile;
	CCurTopicInfo   curIndex(cur.m_pTopic, memfile, cur.m_fmt, cur.m_run, cur.m_log);

    // Advance to "index" keyword

    sz += 2;

    // Get the format information.
    CFmtIndex *pfmt = (CFmtIndex *)cur.m_fmt.index.Get(NULL);
    if(NULL == pfmt)
        return warnNoIndexFormat;

	// Look for "index" keyword

    if(_strnicmp(sz, "index", 5))
        return warnBadIndexReference;

	// Mark start of tag specification, if present

	const char *szTags = NULL;
	const char *szTagsEnd = NULL;
    const char *szFlags = NULL;
    const char *szFlagsEnd = NULL;
    static char szTagsTerm[] = ":]";

	sz = EatWhite(sz+5);    // Advance past "index"

	if(chColon == *sz)
	{
		szTags = ++sz;

		// Find the end of the tag field.
	
		szTagsEnd = SeekEnd(szTags, szTagsTerm, strlen(szTags));
        if(NULL == szTagsEnd)
            return warnBadIndexReference;

        sz = szTagsEnd;
    }

    // if both are null this will be an empty string
    CString sTagsExpr(szTags, szTagsEnd-szTags);
    char *szExprBuf;

    // Construct the tags expression. Print the format string to a memory file,
    // then get the information back into sTagsExpr to set into the index
    // expression.

    memfile.SetLength(0);

    OutputFormatString(curIndex, sTagsExpr, pfmtParent, ptagParent);
    
    memfile.Seek(0, CFile::begin);
    DWORD dwLen = memfile.GetLength();
    szExprBuf = sTagsExpr.GetBufferSetLength((int)(dwLen+1));
    memfile.Read(szExprBuf, (UINT)dwLen);
    szExprBuf[dwLen] = '\0';
    sTagsExpr.ReleaseBuffer();

	// Try to mark the flags spec.
	
	if(chColon == *sz)
	{
		sz = szFlags = EatWhite(++sz);

		szFlagsEnd = SeekEnd(szTags, chCloseBracket, strlen(szFlags));
        if(NULL == szFlagsEnd)
            return warnBadIndexReference;

        sz = szFlagsEnd;
	}

   
    // Construct the flags expression. Print the format string to a memory file,
    // then get the information back into sFlagsExpr to set into the index
    // expression.

    CString sFlagsExpr(szFlags, szFlagsEnd-szFlags);

    memfile.SetLength(0);

    OutputFormatString(curIndex, sFlagsExpr, pfmtParent, ptagParent);
    
    memfile.Seek(0, CFile::begin);
    dwLen = memfile.GetLength();
    szExprBuf = sFlagsExpr.GetBufferSetLength((int)(dwLen+1));
    memfile.Read(szExprBuf, (UINT)dwLen);
    szExprBuf[dwLen] = '\0';
    sFlagsExpr.ReleaseBuffer();
    memfile.SetLength(0);
    memfile.Close();

	// Should be at the closing bracket now.

	if(chCloseBracket != *sz)
        return warnBadIndexReference;

    sz++;

	// Set the extract flags.

	CExprToken exprTags;
	CExprToken exprFlags;
    const char *szCont;

	exprTags.UseCommasAsOr();
	exprFlags.UseCommasAsOr();

	if(sTagsExpr.IsEmpty())
    {
        exprTags.Set();
    }
    else
	{
		nRet = exprTags.Set(sTagsExpr, szCont);
		if(nRet)
            return nRet;
	}

	if(sFlagsExpr.IsEmpty())
    {
        exprFlags.Set();
    }
    else
	{
		nRet = exprFlags.Set(sFlagsExpr, szCont);
		if(nRet)
            return nRet;
	}

	// Output the index header.

    OutputFormatString(cur, pfmt, CFmtListIndex::tagPre, ptagParent);
    CTopic *pTopic;
    CTag   *ptagHead;
    
    // Walk the list of logs and output index entry for each file
    int i, nLogs, j;
    const char *szName;
    const char *szContext;
    char szContextString[256];

    for(i = 0, nLogs = cur.m_log.GetRealCount(); i < nLogs; i++)
    {
        pTopic = cur.m_log.GetTopicOutputOrder(i);
        ASSERT(pTopic);

        if(!pTopic->HasTags())
            continue;

        ptagHead = pTopic->GetTopicTag();

        if(UseTopicInIndex(ptagHead->sTag, 
                            cur.m_log.GetDocTag(pTopic->GetDocTag()),
                            exprTags, exprFlags))
        {
            OutputFormatString(cur, pfmt, CFmtListIndex::tagPreName, 
                                cur.m_pTopic ? cur.m_pTopic->GetTopicTag() : NULL);

            szName = pTopic->GetName();
            for(j = 0; szName[j]; j++)
                OutputFieldChar(cur, szName[j]);
                
            OutputFormatString(cur, pfmt, CFmtListIndex::tagPreContext,     
                                    cur.m_pTopic ? cur.m_pTopic->GetTopicTag() : NULL);
            
            szContext = pTopic->GetContext();
            MakeContextString(szContextString, *szContext ? szContext : szName);
            for(j = 0; szContextString[j]; j++)
                OutputFieldChar(cur, szContextString[j]);
            
            OutputFormatString(cur, pfmt, CFmtListIndex::tagPostContext, 
                                cur.m_pTopic ? cur.m_pTopic->GetTopicTag() : NULL);

			cur.m_fileOutput.Write(szNewline, strlen(szNewline));
        }
    }
    
    OutputFormatString(cur, pfmt, CFmtListIndex::tagPost, ptagParent);

    return 0;
}




/*-----------------------------------------------------------------------
@func void | OutputWinHelpHPJFile | Generates a basic Help
project (HPJ) file for the Help Compiler. The name
of the HPJ file is contstructed from the base name of
the output RTF file with an "HPJ" extension. If a file
of this name already exists, the function returns without
creating a file.

@parm char * | szOutputFileName | Specifies a pointer to a
null-terminated string containg the name of the RTF
output file.

@parm PRUNOPTIONS | pOptions | Specifies a pointer to a
<t RUNOPTIONS> structure containing the runtime options.

@rdesc Void.
*/
void OutputWinHelpHPJFile(
    const char * szOutputFileName,
    const char * szAutoduckName)
{
    CStdioFile file;
    CFileStatus status;
    CFileException e;

    char szFileName[_MAX_PATH];
    char szBaseName[_MAX_FNAME];
    char szDirName[_MAX_DIR];
    char szDriveName[_MAX_DRIVE];
    char szExtName[_MAX_EXT];

    _fullpath(szFileName, szOutputFileName, _MAX_PATH);
    _splitpath(szFileName, szDriveName, szDirName, 
        szBaseName, szExtName);

    // Use base name of output file
    sprintf(szFileName, "%s%s%s.HPJ", szDriveName, szDirName, szBaseName);

    // See if file already exists, don't overwrite if present.
    if(file.GetStatus(szFileName, status))
        return;
    
    if(!file.Open(szFileName, CFile::modeWrite | CFile::modeCreate | CFile::typeText, &e))
    {
        PrintError(szFileName, NO_LINE, e.m_cause);
        return;
    }
    
TRY
{
    char szMsgBuf[1024];
    sprintf(szMsgBuf, "; HPJ file generated by %s\n\n", szAutoduckName);
    file.WriteString(szMsgBuf);
    file.WriteString("[options]\n\n");
    file.WriteString("[config]\n");
    file.WriteString(" BrowseButtons()\n\n");
    file.WriteString("[files]\n");
    sprintf(szMsgBuf, " %s%s\n\n", szBaseName, szExtName);
    file.WriteString(szMsgBuf);
    
    file.Close();
}
CATCH(CFileException, e)
{
    PrintError(szFileName, NO_LINE, e->m_cause);
}
END_CATCH
}

 
