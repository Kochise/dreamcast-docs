/*
 * extract.cpp
 */

#include <afx.h>
#include <afxtempl.h>
#include <io.h>
#include "parse.h"
#include "topiclog.h"
#include "fmtspec.h"
#include "docexpr.h"
#include "cmdargs.h"
#include "extract.h"
#include "errmsg.h"
#include "parsetag.h"

//char szEmptyField[] = "Empty Field";

void ExtractFile(CFile &out, const char *szFilename, CTopicLog  &log, RUNOPTIONS &run, FormatInfo &fmt);
BOOL ExtractTopic(CSrcInput &in, CTopicLog &log, RUNOPTIONS &run, FormatInfo   &fmt, CFile &out);		

const char *EatNoiseChars(const char * szLine);
int IsBeginTopic(const char *szTag, FormatInfo &fmt);
int IsEndComment(const char *sz, int nCommentType);
void CheckCurTag(CSrcInput &in, CTopicLog &log, CFile &out, FormatInfo &fmt, RUNOPTIONS &run, int fAllowPending);
int AddLineToBuffer(char *szLine, CSrcInput &in);
const char *GetTag(CString &sTagDest, const char *szSrc);
int CheckTagExclusion(const char *&szText, CExprToken &expr, BOOL &bExcludeTag);
void AddTopic(CTopicLog &log, CTagList &listTags, CSrcInput &in, CFile &out, FormatInfo &fmt, RUNOPTIONS &run);


/**********************************************************************/

CSrcInput::CSrcInput()
{
    ZeroMem(m_achCommentStart, MAXLINEBUFSIZE+1);
    ZeroMem(m_achTagBuf, TAGBUFSIZE+1);
    m_szTagCur = m_achTagBuf;
	m_szParseCur = m_szLineBuf;
    m_nSourceType = -1;
    m_nCommentType = -1;
    ResetState();
	m_nFile = 0;
};


CSrcInput::~CSrcInput(void)
{
	ASSERT(m_pendMain.IsEmpty());
	ASSERT(m_pendAux.IsEmpty());
	ASSERT(m_listAuxTags.IsEmpty());
}

void CSrcInput::CueParse(CPendingList &pend, CTag *ptag, int nTargetFields, int nParseType, BOOL bTopic)
{
	CPendingTag *pnew = new CPendingTag;
	pnew->nParseType = nParseType;
	pnew->nPendingFields = nTargetFields;
	pnew->bTopic = bTopic;
	pnew->ptag = ptag;

	pend.AddTail(pnew);	
};

void CSrcInput::CueParse(CPendingList &pend, CTag *ptag, CTag *ptagParent, FormatInfo &fmt)
{
	CPendingTag *pnew = new CPendingTag;
	pnew->ptag = ptag;
	pnew->ptagParent = ptagParent;
	pnew->bTopic = TRUE;

	CFmtSrchTopic srch;
	srch.m_sName = ptag->sTag;
	CFmtTopic *pfmtTopic = (CFmtTopic *)fmt.topic.Get(&srch);
	if(pfmtTopic)
	{
		pnew->nParseType = pfmtTopic->GetParseType();
		pnew->nPendingFields = pfmtTopic->GetNumFields();
	}

	pend.AddTail(pnew);	

}

void CSrcInput::EmptyParse(void)
{
	POSITION pos;
	CPendingTag *p;

	pos = m_pendMain.GetHeadPosition();
	while(pos)
	{
		p = m_pendMain.GetNext(pos);
		delete p;
	}
	pos = m_pendAux.GetHeadPosition();
	while(pos)
	{
		p = m_pendAux.GetNext(pos);
		delete p;
	}
	m_pendMain.RemoveAll();
	m_pendAux.RemoveAll();
}


/*****************************************************************************/

//@func Determines whether the specificed line has only a template
// definition and nothing else. A partial template definition applies.
//
//@rdesc Returns 1 if the line contains only a full or partial template
// definition; 0 if no template definition or if there is other 
// stuff on the line.

int IsTemplateLine(const char *szLine)
{
	szLine = EatWhite(szLine);

	if(strncmp(szLine, "template", 8))
		return 0;

	szLine = EatWhite(szLine+8);
	if(*szLine != chOpenAngle)
		return 1;

	szLine = MatchParen(szLine, chCloseAngle);
	if(*szLine != chCloseAngle)
		return 1;

	szLine = EatWhite(++szLine);

	if(isidchar(*szLine))
		return 0;

	return 1;
}



int TransferAux(
	CPendingTag *ppend,
	CTag *ptagTopic,
	FormatInfo  &fmt)
{
	CFmtSrchTag srch;
	CFmtPara *pfmt;
	NAMETOKEN *pname = NULL;
	char *szField;
	int nLen;

	srch.m_sName = ppend->ptagParent->sTag;

	pfmt = (CFmtPara *)fmt.paragraph.Get(&srch);
	if(pfmt == NULL)
		return 1;

	pname = pfmt->GetMap(ppend->ptag->sTag);
	if(NULL == pname)
		return 1;

	for(int i = 0; i < MAXNUMFIELDS && pname[i].nType != nameNone; i++)
	{
		switch(pname[i].nType)
		{
		case nameLocal:
			szField = ppend->ptagParent->aszFieldText[pname[i].nField];
			nLen = ppend->ptagParent->anFieldLen[pname[i].nField];
			break;

		case nameTopic:
			szField = ptagTopic->aszFieldText[pname[i].nField];
			nLen = ptagTopic->anFieldLen[pname[i].nField];
			break;

		default:
			return 1;
		}

		if(nLen)
		{
			ppend->ptag->aszFieldText[i] = new char[nLen+1];
			strcpy(ppend->ptag->aszFieldText[i], szField);
			ppend->ptag->anFieldLen[i] = nLen;
		}
	}

	ppend->ptag->nFields = i;

	return 0;
}

/*
@func Parses source text for any tags requiring field information
from source statements.

@parm Input state - including parsing wannabe lists, which are emptied
if parsing is successful.

@parm Topic log

@parm Format file

*/

void CheckCurParse(
   CSrcInput &in,
   CTopicLog &log,
   FormatInfo &fmt)
{
	int nRet;
	POSITION pos, posCur;
	CPendingTag *ppend;
	CParseText txt(in.m_szLineBuf, in.m_szParseCur);
	
    // If this line just has "template<...>" on it, then skip it.
	// @todo Parse it!

    if(IsTemplateLine(in.m_szLineBuf))
        return;

	// Decue main topic parse wannabes

	pos = in.m_pendMain.GetHeadPosition();
	while( pos != NULL )
	{
		posCur = pos;

		ppend = in.m_pendMain.GetNext( pos );

		nRet = ParseSrc(ppend->ptag, txt,
        		in.m_lCurLine, ppend->nParseType, TRUE);

		if(warnSrcFieldsMultiline == nRet)
		{
			in.SetAppend();

			return;
		}
		else if(nRet)
		{
			PrintError(log.GetSrcFn(), in.m_lCurLine, nRet);
		}
		else
		{
			in.m_szParseCur = in.m_szLineBuf+(txt.m_szCur-txt.m_szBase);
		}

		delete ppend;
		
		in.m_pendMain.RemoveAt(posCur);
	}

	// Decue aux topic parse wannabes

	pos = in.m_pendAux.GetHeadPosition();
	while( pos != NULL )
	{
		posCur = pos;

		ppend = in.m_pendAux.GetNext( pos );

		if(ppend->bTopic)
		{
			if(TransferAux(ppend, in.m_listTags.GetHead(), fmt))
				PrintError(log.GetSrcFn(), ppend->ptag->lSrcLineNum, warnCantTransferAux);

			if(CFmtTopic::parseMfunc == ppend->nParseType)
				txt.Set(ppend->ptagParent->aszFieldText[2]);
		}
		else
		{
			nRet = ParseSrc(ppend->ptag, txt,
				in.m_lCurLine, ppend->nParseType, TRUE);
			if(nRet)
				PrintError(log.GetSrcFn(), in.m_lCurLine, nRet);
		}

		delete ppend;
		
		in.m_pendAux.RemoveAt(posCur);
	}
	in.m_szParseCur = in.m_szLineBuf;
}



/*
@func This function checks whether there's a tag waiting
to be parsed, and parses the tag if one exists. 

@rdesc Zero if successful, otherwise an error code.
*/

void CheckCurTag(
    CSrcInput &in,          //@parm Input file
	CTopicLog &log,			//@parm Topic log - may need to add aux topics
	CFile &out,				//@parm Output temp file - may need to add aux topics
    FormatInfo &fmt,        //@parm Formatting info
	RUNOPTIONS &run,		//@parm Runtime options structure - for verbosity in adding topics
    int fAllowPending)      //@parm TRUE if source info available for parsing
{
    int nRet = 0;
	BOOL bTopic = FALSE;
    CTagList &listTags = in.m_listTags;

    // If we have an active tag, parse it.

    if(in.m_nState.Tag)
    {
        // If first tag in the topic, it's a topic tag
        if(!in.m_nState.HaveTopicTag)
		{
            in.m_nState.HaveTopicTag = TRUE;
			bTopic = TRUE;
		}

        in.m_nState.Tag = FALSE;

        // An auxiliary paragraph (@@pgraph) gets parsed and added to the
		// auxiliary tag list. Otherwise, parse the tag and add to the
		// main tag list.

		if(in.m_nState.AuxPara)
		{
			nRet = ParseTag(in, fmt, TRUE, NULL, FALSE);
			if(nRet)
			{
				PrintError(log.GetSrcFn(), in.m_nLineTag, nRet);
				return;
			}
			
			in.m_nState.AuxPara = FALSE;
		}
		else
		{
			nRet = ParseTag(in, fmt, FALSE, NULL, bTopic);
			if(nRet)
			{
				PrintError(log.GetSrcFn(), in.m_nLineTag, nRet);
				return;
			}

			// See if an aux topic is available, add it to the log if so.

			if(!in.m_listAuxTags.IsEmpty())
			{
				// Might be an aux topic tag left on the pending cue - this
				// only occurs when aux topic tag fields were complete and
				// did not get filled out from source text later in this function.

				if(!in.m_pendAux.IsEmpty())
				{
					CPendingTag *ppend = in.m_pendAux.GetHead();
					if(TransferAux(ppend, in.m_listTags.GetHead(), fmt))
						PrintError(log.GetSrcFn(), ppend->ptag->lSrcLineNum, warnCantTransferAux);
					in.m_pendAux.RemoveAll();
				}

				AddTopic(log, in.m_listAuxTags, in, out, fmt, run);
			}

			// AuxTopicOpen - last tag extracted (the one we are dealing with now)
			//					has an aux topic attached.
			// AuxTopicTag - this line has an aux topic attached.

			// If there is an auxiliary topic tag attached to the paragraph,
			// allocate a new tag for it and add it to the parsing cue.

			if(in.m_nState.AuxTopicOpen)
			{
				CTag *ptagAux = new CTag;
				ptagAux->sTag = in.m_sTagAux;
				ptagAux->lSrcLineNum = in.m_lCurLine;

				in.m_listAuxTags.AddTail(ptagAux);

				in.CueParse(in.m_pendAux, ptagAux, in.m_listTags.GetTail(), fmt);

				in.m_nState.AuxTopicOpen = FALSE;
			}
		}
    }

    if(in.m_nState.AuxParaTag)
	{
		in.m_nState.AuxParaTag = FALSE;
		in.m_nState.AuxPara = TRUE;
	}

	// If there's a tag that needs fields added, try
    // to parse the fields out of this source line.

    if(fAllowPending)
		CheckCurParse(in, log, fmt);
}





/*-----------------------------------------------------------------------
    @doc EXTERNAL EXTRACT
        
    @func char *| GetBeginComment | Looks for the beginning of a comment
        block within the given line. 
            
    @rdesc Returns zero if no comment found, or one of the following
        values to indicate the type of comment found:

    @flag commentSemicolon | Uses semicolons (assembler).
    @flag commentSlashstar | Uses forward slash character followed 
        by asterisk character.
    @flag commentApostrophe | Uses apostrophe (Basic-style).
    @flag commentSlashslash | Uses two forward slash characters.
        
*/

int GetBeginComment(
    const char *sz,         // @parm Line to search for comment block
    int nSourceType,        // @parm Language type:
                            //  @flag sourceC | C or C++ (/* or // comments)
                            //  @flag sourceAsm | Assembly file (; comments)
                            //  @flag sourceBas | Basic file (' comments)
    const char *&szBlock,   // @parm Filled in with a pointer to the first
                            //  character of the comment delimiter.
    const char *&szText)   // @parm Filled with the first text character in
                            //  in the comment.
{
    int bLit;

    ASSERT(sz);
    
    sz = EatWhite(sz);
    
    switch(nSourceType)
    {
    case sourceC:
        
        // Look for a slash-slash or slash-asterisk
        
        for(bLit = FALSE; *sz; sz++)
        {
            if(*sz == chBackslash)
			{
				// keep going past escape character
			}
            else if(*sz == chDoubleQuote || *sz == chSingleQuote)
            {
                // quotation mark - literal string

                bLit = !bLit;
            }
            else if(bLit)
            {
                // keep going past literal string
            }
            else if(*sz == chSlash)
            {
                szBlock = sz;

                if(*(sz+1) == chAsterisk)
                {
                    szText = EatNoiseChars(sz+2);

                    return commentSlashstar;
                }
                else if(*(sz+1) == chSlash)
                {
					while(*sz == chSlash)
						sz++;

                    szText = EatNoiseChars(sz);

                    return commentSlashslash;
                }
            }
        }
        break;
        
    case sourceAsm:

        for(; *sz; sz++)
        {
            if(*sz == chSemicolon)
            {
                szBlock = sz;
                szText = EatNoiseChars(sz+1);

                return commentSemicolon;
            }
        }
        break;
        
    case sourceBas:
        
        for(bLit = FALSE; *sz; sz++)
        {
            if(*sz == chDoubleQuote)
            {
                bLit = !bLit;
            }
            else if(bLit)
            {
                // keep going
            }
            else if(*sz == chSingleQuote)
            {
                szBlock = sz;
                szText = EatNoiseChars(sz+1);

                return commentApostrophe;
            }
        }
        break;
    }
    
    return 0;
}

/*-----------------------------------------------------------------------
    @doc EXTERNAL EXTRACT
        
    @func int | IsEndComment | Determines if the given line ends a
        comment block.
            
    @parm char * | ptr | Specifies a pointer to a null-terminated buffer
        containing the line.
    @parm int | in.m_nCommentType | Specifies a constant identifying the type 
        of comment used in the block:
        @flag commentSemicolon | Uses semicolons (assembler).
        @flag commentSlashstar | Uses forward slash character followed 
            by asterisk character.
        @flag commentApostrophe | Uses apostrophe (Basic-style).
        @flag commentSlashslash | Uses two forward slash characters.
            
    @rdesc The return value is TRUE if the line ends a comment block,
        otherwise it is FALSE.
*/
int IsEndComment(const char *sz, int nCommentType)
{
    switch(nCommentType)
    {
    case commentSemicolon:
    case commentApostrophe:
    case commentSlashslash:
        return TRUE;
        
    default:
        for(sz = EatWhite(sz); *sz; sz++)
        {
            if ((*sz == '*') && (*(sz+1) == '/'))
                return TRUE;
        }
    }
    return FALSE;
}

/*-----------------------------------------------------------------------
    @doc EXTERNAL EXTRACT
        
    @func int | IsBeginTopic | Determines if the given line begins
        an autoduck topic.
            
    @parm char * | szLine | Specifies a pointer to a null-terminated buffer
        containing the line.
    @parm PTOPICTAG | pTopicTags | Specifies a list of valid topic tags 
        such as "func", "api", "asm", and "msg".

    @rdesc The return value is TRUE if the line begins an autoduck topic,
        otherwise it is FALSE.
*/
int IsBeginTopic(
    const char *szTag, 
    FormatInfo &fmt)
{
    // Test for case where no tag found
    if (*szTag == '\0')
        return FALSE;
    
    CFmtSrchTopic srch;
    srch.m_sName = szTag;

    return (fmt.topic.Get(&srch) != NULL);
}



/*-----------------------------------------------------------------------
    @doc EXTERNAL EXTRACT
        
    @func char * | EatNoiseChars | Strips noise characters from the given
        line. The following character combinations are considered to
        be noise characters:
            
        <em-> Semicolon if first character in line
            
        <em-> Apostrophe if first character in line
            
        <em-> Consecutive "border" characters beginning with first 
              character in line ("***************") or second character
              if first character is space (" **************")
            
        <em-> All characters following and including end comment characters
            
        <em-> All text following and including internal designator
              ( ; I n t e r n a l )

        <em-> Whitespace, *, \<, and // characters preceding internal 
              designator
                  
        <em-> // comment characters
            
    @parm char * | szLine | Specifies a pointer to a 
        null-terminated buffer containing the line to process.
            
    @rdesc Returns a pointer to the first non-noise character.
    
    @comm This function is called by <f ExtractTopic> before a source
        line is added to the extract buffer. It assumes that each line 
        ends in newline/null-terminator characters.
        
    @xref <f StripLeadingWhiteSpace>
*/
const char *EatNoiseChars(const char *szLine)
{
    const char *szT;

    ASSERT(szLine);
    
    // Check for empty string
    switch(*szLine)
    {
    case '\0':
    case ';':
    case '\'':
        break;
        
    default:

		szT = EatWhite(szLine);
		if(isnoise(*szT))
			szLine = szT;
           
        while(isnoise(*szLine))
            ++szLine;
            
        if(*szLine == '/' && *(szLine-1) == '*')
            szLine--;

        break;
    }    
    return szLine;
}


/*
@func Adds the current line to the extracted topic buffer.
*/
int AddLineToBuffer(
    const char *szLine,      //@parm Line to add.
    CSrcInput &in)          //@parm Input state structure.
{
    size_t nLen;
    BOOL bStripComment = FALSE;

	// Get the line length.

    nLen = strlen(szLine);

    // Empty, return.
	if(nLen == 0)
        return 0;

    // Back up over any trailing spaces.

    const char *szEnd = TrimWhite(szLine+nLen, szLine);

    nLen = isspace(*szEnd) ? 0 : szEnd-szLine+1;

    // Back up over the comment delimiter, if present.

	if( (in.m_nState.EndComment && in.m_nCommentType == commentSlashstar) &&
	    (nLen >= 2 && szLine[nLen-1] == chSlash && szLine[nLen-2] == chAsterisk) )
    {
        if(nLen == 2)
		{
        	nLen = 0;
		}
        else
		{
        	szEnd = TrimWhite(&szLine[nLen-2], szLine);
		
        	nLen = isspace(*szEnd) ? 0 : szEnd-szLine+1;
		}
    }
   
	// Make sure we don't overwrite the input buffer.

	if((int)((in.m_szTagCur - in.m_achTagBuf) + nLen + 1) >= TAGBUFSIZE)
	    return errTagTooBig;

    if(nLen)
        memcpy(in.m_szTagCur, szLine, nLen);

	in.m_szTagCur[nLen++] = '\n';

	in.m_szTagCur += nLen;

    return 0;
}

/*
@func Gets the Autoduck tag from the given line.
    
@rdesc Returns the index of the next character following the end
    of the tag.
        
@comm The given line can contain leading whitespace and noise
    characters.
*/
const char *GetTag(
    CString &sTagDest,        //@parm Destination buffer for tag name.
    const char *szSrc)        //@parm Line to extract tag from.
{
    int i;

	if(!istagchar(*szSrc))
		return szSrc;

    // Copy tag.

    for(i = 0; szSrc[i] && istagchar(szSrc[i]) && i < MAXTAGSIZE; i++);

    sTagDest = CString(szSrc, i);

    return szSrc + i;
}


/*
@func This function checks extraction flags associated with a paragraph
tag. Tag-level extraction flags allow an Autoduck author to exclude or 
include specific paragraphs within a topic.

@rdesc Returns NULL if the extraction flags were not specified on the
command line, or if there was a syntax error in the extraction specifier.
Otherwise, returns a pointer to the text following the extraction specifier.
*/

int CheckTagExclusion(
    const char *&szText,    //@parm Text to check eg. @tag:(JAPANESE) - updated with
                            // character position following extraction text
    CExprToken &expr,       //@parm Extraction tokens from command line
    BOOL &bExcludeTag)      //@parm Whether to exclude the tag from extraction
{
    bExcludeTag = FALSE;
    
    // Get the colon.

    szText = EatWhite(szText);
    if(*szText != chColon)
        return 0;
    
    // Get the opening paren.

    szText = EatWhite(++szText);
    
    if(*szText != chOpenParen)
        return warnTagExclSyntax;

    // Get the closing paren.

    szText = EatWhite(++szText);

    const char *szFlags = szText;
    static char szTagStopChar[] = ")\n|";

    szText = SeekEnd(szText, szTagStopChar, MAXLINEBUFSIZE);

    if(szText == NULL || *szText != chCloseParen)
        return warnTagExclSyntax;

    // Check the doc IDs.

	CString sTagTokensRaw(szFlags, szText-szFlags);
    CString sTagTokens;

	CopyFlags(sTagTokens, sTagTokensRaw);

    bExcludeTag = !expr.Eval(sTagTokens);

	// Past the closing paren before returning.

	++szText;

    return 0;
}

/****************************************************************************/


//@func Walks the argument list and processes each input
// specified. Expands wilcards into multiple input file
// arguments.

void ExtractTopics(
    CFile &out,
    RUNOPTIONS &run,
    CTopicLog  &log,
    FormatInfo &fmt)
{
   	char szPath[_MAX_PATH];
	char szInFile[_MAX_PATH];

   	char szDrive[_MAX_DRIVE];
   	char szDir[_MAX_DIR];

#if defined(_DOS)
	_find_t fileInfo;
#else
	_finddata_t fileInfo;
	long hFile;
#endif

    int i, nFiles;
    int nInput = 0;

    nFiles = run.asInputFiles.GetSize();
    
    for(i = 0; i < nFiles; i++)
    {
        ASSERT(run.asInputFiles[i]);

        strcpy(szInFile, *run.asInputFiles[i]);

#if defined(_DOS)
		if(_dos_findfirst(szInFile, _A_NORMAL, &fileInfo))
#else
		if((hFile = _findfirst(szInFile, &fileInfo)) == -1L)
#endif
		{
            PrintError(szInFile, NO_LINE, errFileNotFound);
			continue;
		}

		// Build the pathname stub for the input filename.

		_splitpath( szInFile, szDrive, szDir, NULL, NULL);
		*szPath = '\0';
		strcat(szPath, szDrive);
		strcat(szPath, szDir);

		// Process each matching file in wildcard 
		do
		{
			sprintf(szInFile, "%s%s", szPath, fileInfo.name);

#if !defined(_DOS)
			if(fileInfo.attrib & _A_SUBDIR)
				continue;
#endif
	        ExtractFile(out, szInFile, log, run, fmt);

#if defined(_DOS)
		} while(_dos_findnext(&fileInfo) == 0);
#else
		} while(_findnext(hFile, &fileInfo) == 0);
#endif
    }
}


//@func Adds a topic to the log.

//@rdesc Returns zero on success or an error code.
// If an error code, the topic (and tag list) is
// deleted.

void AddTopic(
    CTopicLog &log,         //@parm Topic log.
    CTagList &listTags,     //@parm Linked list of topic tags.
	CSrcInput &in,			//@parm Input file information
    CFile &out,             //@parm Temp file to output topic text.
    FormatInfo &fmt,        //@parm Format information.
    RUNOPTIONS &run)        //@parm Runtime options (verbosity)
{
    CTopic *pTopic;
    CFmtSrchTopic srch;
    CFmtTopic *pfmtTopic;
    char szNameBuf[MAXTOPICNAMELEN+1];
    CTag *ptagHead = listTags.GetHead();

    // Create a topic to hold the tag list.

    pTopic = new CTopic;
    pTopic->SetTags(listTags);

    // See if valid topic tag.

    srch.m_sName = ptagHead->sTag;
    pfmtTopic = (CFmtTopic *)fmt.topic.Get(&srch);
    
    if(NULL == pfmtTopic)
	{
        PrintError(log.GetSrcFn(in.m_nFile), ptagHead->lSrcLineNum, warnUnknownTopicTag);
		return;
	}

    // Check field count.

    if(pfmtTopic->GetNumFields() != ptagHead->nFields)
		PrintError(log.GetSrcFn(in.m_nFile), ptagHead->lSrcLineNum, warnWrongNumFields);
    
    // Print name and context strings into the topic object.

    pfmtTopic->PrintName(szNameBuf, ptagHead);

    if(run.nOptions.Verbose)
        printf("\t%s\n", szNameBuf);

    pTopic->SetName(szNameBuf);

    pfmtTopic->PrintContext(szNameBuf, ptagHead);

    pTopic->SetContext(szNameBuf);

    // Set the other fields.

    pTopic->SetWeight(pfmtTopic->GetSortWeight());
    pTopic->SetSrcFn(in.m_nFile);
	pTopic->SetSrcLine(ptagHead->lSrcLineNum);
	pTopic->SetDocTag(log.GetDocTagIndex());
    pTopic->Write(out);

    log.Add( pTopic, CTopicLog::AddGenerateUnique );

	listTags.RemoveAll();
}

/****************************************************************************/

//@func Extracts topics from an input file.

void ExtractFile(
    CFile &out,                 //@parm Temp file to output tag text
    const char *szFilename,     //@parm Input file to process
    CTopicLog  &log,            //@parm Topic log, gets new topics.
    RUNOPTIONS &run,            //@parm Runtime options.
    FormatInfo &fmt)            //@parm Formatting/tag information.
{
    CSrcInput in;
	CFileException except;
    int nTopic = 0;

TRY
{
    if(run.nOptions.Verbose)
        fprintf(stdout, "%s\n", szFilename);

    // Open file, record filename in topic log.

    if(!in.Open(szFilename, CFile::modeRead | CFile::typeBinary, &except))
	{
	    PrintError(szFilename, NO_LINE, except.m_cause);
		return;
	}
    
	in.m_nFile = log.AddSrcFn(szFilename);

    // Determine source type. Default to "C" if unknown.

    CFmtSrchExt srchExt;
    char szExt[_MAX_EXT+1];
    
    _splitpath(szFilename, NULL, NULL, NULL, szExt);
    srchExt.m_sExt = &szExt[1];

    CFmtExt *pExt = (CFmtExt *)fmt.extension.Get(&srchExt);
    if(NULL == pExt)
    {
        PrintError(szFilename, NO_LINE, warnFileTypeUnknown);
        in.m_nSourceType = sourceC;
    }
    else
    {
        in.m_nSourceType = pExt->GetSourceType();
    }

  
    // Set the doc tag number. This might be -1 if no doc tag has been
	// found in the file yet - it will be reset later within this function.

    while (ExtractTopic(in, log, run, fmt, out))
    {
        // Create a topic to hold the tag list.

        AddTopic(log, in.m_listTags, in, out, fmt, run);

		// If an auxiliary topic left over, add it to the list also.

		if(!in.m_listAuxTags.IsEmpty())
			AddTopic(log, in.m_listAuxTags, in, out, fmt, run);
    };

    in.Close();

    return;
}
CATCH(CFileException, e)
{
    PrintError(szFilename, in.m_lCurLine, e->m_cause);
    return;
}
AND_CATCH(CMemoryException, e)
{
    PrintError(szFilename, in.m_lCurLine, errMemory);
    return;
}
END_CATCH
}


/*
@func This function seeks the start of an Autoduck topic in the
input stream, and once it finds one extracts all the topic
text. 

A topic can span multiple comment lines. Topic text can
consist of commented text as well as information read from
source language statements.

The function constructs a linked list of TAG structures
describing each tag within the topic.

@rdesc Pointer to head of linked <t TAG> list or NULL no topic
was extracted.
*/

BOOL ExtractTopic(
    CSrcInput    &in,       //@parm Source file
    CTopicLog    &log,      //@parm Topic log, for updates to list
							// of extract tags and for adding auxiliary
							// topics.
    RUNOPTIONS   &run,      //@parm Runtime options structure
    FormatInfo   &fmt,      //@parm Format entries
	CFile &out)				//@parm Output temp file - for aux topics
{
    CTag *    ptagHead = NULL;
	
    char *szComment;                // Start of comment block (at // etc.)
    const char *szCommentText;      // Start of comment text
    const char *szTag;
    const char *szT;
	int  nRet;
    BOOL bExcludeTag;

    CString sTag;

    int fTopicTag = TRUE;

    in.m_listTags.RemoveAll();

	in.m_pendMain.RemoveAll();
	in.m_pendAux.RemoveAll();
	in.m_listAuxTags.RemoveAll();

    // Initialize input state - leave the state variables as is because they
    // indicate what's up from the last topic extracted. State variables are
    // updated within this function before exit.

    in.m_achTagBuf[0] = '\0';

    in.m_nState.HaveTopicTag = FALSE;
    in.m_nState.Tag = FALSE;
    in.m_nState.GrowingTag = FALSE;
    in.m_nState.Topic = FALSE;
	in.m_nState.SkipTopic = FALSE;
	in.m_nState.AuxTopicTag = FALSE;
	in.m_nState.AuxTopicOpen = FALSE;
	in.m_nState.AuxPara = FALSE;
	in.m_nState.AuxParaTag = FALSE;

    in.m_listAuxTags.RemoveAll();
    in.m_sTagAux.Empty();

    // Set current doc tag - may be -1 if none has been found in
    // topic yet.

    int nDocTag = log.GetDocTagIndex();

    // Loop kicks out at the end of the topic, which can be any of the
    // following situations:
    // * End of file
    // * A new topic is found
    // * A "@doc" tag is found, signifying end of topic
    
    while( ! in.EndOfFile() )       // while not EOF
    {
		// Get next line from source.

		if(nRet = in.GetLine())
		{
			PrintError(log.GetSrcFn(), in.m_lCurLine, nRet);
			return NULL;
		}

        // ********* DETERMINE IF COMMENT LINE **************************

        // If the last line ended a comment, assume this isn't a comment
        // now.
        
        if(in.m_nState.EndComment)
        {
            in.m_nState.Comment = FALSE;
            in.m_nState.EndComment = FALSE;

         	// End of a slash-star block ends the tag.
         	
         	if(in.m_nCommentType == commentSlashstar)
         		in.m_nState.GrowingTag = FALSE;
        }

        if(in.m_nState.Comment)
        {
            in.m_nState.BeginComment = FALSE;

            // Comment starts at beginning of line.
            
            szComment = in.m_szLineBuf;

            // If this is a /* block, and the current line begins with a //
            // comment, ignore the line.
        
            if(in.m_nCommentType == commentSlashstar &&
               strncmp(szComment, "//", 2) == 0)
            {
                continue;
            }

            // Advance past noise characters

            szCommentText = EatNoiseChars(szComment);
        }
        else    // not in comment block
        {
            // Skip blank lines, also end any single-line comment block
            // (blank line following marks the end of the block).

            szT = EatWhite(in.m_szLineBuf);

            if(*szT == '\0' || *szT == '\n')
            {
                in.m_nState.GrowingTag = FALSE;
                continue;
            }

            // See if a comment starts on this line. 

            in.m_nCommentType = GetBeginComment(in.m_szLineBuf, 
                    in.m_nSourceType, szComment, szCommentText);

            if(in.m_nCommentType)
            {
                in.m_nState.Comment = TRUE;
                in.m_nState.BeginComment = TRUE;

				// See if any source text precedes the comment, if so see if 
				// any tags are pending for parsing.

				szT = EatWhite(in.m_szLineBuf);
				if(szT != szComment)
					CheckCurParse(in, log, fmt);
            }
			else
            {
                // If no comment starts on this line, this is a non-blank,
                // non-comment line, a candidate for parsing any pending
                // tag.

                //CheckCurParse(in, log, fmt);//tag
				CheckCurTag(in, log, out, fmt, run, TRUE); 

                continue;
            }
        }


        // See if this line ends the comment. Even if it does, we
        // might still want to store the line with the topic.

        if(IsEndComment(szCommentText, in.m_nCommentType))
        {
            in.m_nState.EndComment = TRUE;
        }

	    // Get the tag starting the line, if present.
	    
		sTag.Empty();
		in.m_nState.AuxParaTag = FALSE;
		szTag = EatWhite(szCommentText);
		
		if(chAtSign == *szTag)
		{
			// Auxiliary paragraph tag

			if(chAtSign == szTag[1])
			{
				szTag++;
				if(in.m_nState.Topic == TRUE)
					in.m_nState.AuxParaTag = TRUE;
			}

			// Get the tag.

			szCommentText = GetTag(sTag, szTag+1);
		}

        // If we're not in an autoduck block, see if the current line
        // starts an autoduck block.

        if(!in.m_nState.Autoduck)
        {
    		if(_stricmp(sTag, "doc") == 0)
            {
                CopyFlags(in.m_sDocFlags, szCommentText);

                if(run.exprExtract.Eval(in.m_sDocFlags))
                {
                    in.m_nState.Autoduck = TRUE;

	                nDocTag = log.AddDocTag(in.m_sDocFlags);
                }
            }
            continue;
        }

        // ******* WITHIN A TOPIC *******************************
        
        if(in.m_nState.Topic)
        {
			// Skip line if topic tag was excluded
			if(in.m_nState.SkipTopic)
				continue;

            // If the line is an @doc tag, end the current topic and tag, and
			// pop out of the Autoduck state. Will reset on next call.

            if(_stricmp(sTag, "doc") == 0)
            {
                // Check the current tag.

                CheckCurTag(in, log, out, fmt, run, TRUE); //FALSE);

			    // Store doc tag line to be used on next call to ExtractTopic

			    in.SetReuse();
                
				in.m_nState.Autoduck = FALSE;

                if(in.m_nState.BeginComment)
                {
                    in.m_nState.BeginComment = FALSE;
                    in.m_nState.Comment = FALSE;
                }

                return TRUE;
            }
            
            // New topic found. End current topic.
            
            if(IsBeginTopic(sTag, fmt))
            {
                // See if there's a field search pending. Since we're
                // still in a comment block, issue a warning message
                // and cancel pending search.

                CheckCurTag(in, log, out, fmt, run, TRUE);//FALSE);

                // Store first line of topic for next call to ExtractTopic

                in.SetReuse();
                
                if(in.m_nState.BeginComment)
                {
                    in.m_nState.BeginComment = FALSE;
                    in.m_nState.Comment = FALSE;
                }

                return TRUE;
            }

            // New tag found. End current tag.

            if( !sTag.IsEmpty() )
            {
                // See if this tag has extraction flags. If it does,
                // make sure the tag is included in the build.

                nRet = CheckTagExclusion(szCommentText, run.exprExtract, bExcludeTag);
                if(nRet)
                    PrintError(log.GetSrcFn(), in.m_lCurLine, nRet);
                
				// New tag. See if there's a new topic defined on this line.
				// If so, set the aux topic open flag variables to notify
				// <f CheckCurTag>. If another aux topic is pending now, need
				// to add it to the log and clear the aux tag list.

                in.m_nState.AuxTopicTag = (chComma == *szCommentText);

				// Now check the current tag state = this means closing out the
				// preceding tag and possibly adding the current aux
				// topic to the log.

                CheckCurTag(in, log, out, fmt, run, FALSE);

				// If tag was excluded just break out here.

				if(bExcludeTag)
                {
                    in.m_nState.Tag = FALSE;
                    in.m_nState.GrowingTag = FALSE;

                    continue;
                }
               
				// If auxiliary tag, get the name of the aux topic tag attached
				// to this paragraph.

				if(in.m_nState.AuxTopicTag)
				{
					in.m_sTagAux.Empty();
					szCommentText = GetTag(in.m_sTagAux, szCommentText+1);
					
					in.m_nState.AuxTopicOpen = (szTag != szCommentText+1);
				}

                // Store the paragraph tag name and any text preceding
				// the tag comment block. May need the text for source
				// parsing.

				in.m_sTag = sTag;

                if(in.m_nState.BeginComment)
                {
                    memcpy(in.m_achCommentStart, in.m_szLineBuf, 
                            szComment - in.m_szLineBuf);
                    in.m_achCommentStart[szComment-in.m_szLineBuf] = '\0';
                }
                else
                {
                    in.m_achCommentStart[0] = '\0';
                }

                // Reset tag pointer and tag buf.

                ZeroMem(in.m_achTagBuf, TAGBUFSIZE+1);
                in.m_szTagCur = in.m_achTagBuf;
	            
                in.m_nLineTag = in.m_lCurLine;
                in.m_nState.Tag = TRUE;
                in.m_nState.GrowingTag = TRUE;
            }

            // Add the line to the tag buffer

            if(in.m_nState.GrowingTag)
            {
                nRet = AddLineToBuffer(szCommentText, in);
                if(nRet)
                    PrintError(log.GetSrcFn(), in.m_lCurLine, nRet);
            }

			// Nothing in comment of interest - so see if 
			// source text preceding the comment is parsable.

			if(in.m_nState.BeginComment && 
			   (!in.m_pendMain.IsEmpty() || !in.m_pendAux.IsEmpty()) )
			{
				*szComment = '\0';
				const char *szSrcText = EatWhite(in.m_szLineBuf);
				if(*szSrcText)
					CheckCurParse(in, log, fmt);
			}
        } // end IN TOPIC
       

        else    // NOT IN TOPIC
        {
            // Does this line begin a topic? If so, we will add the line 
            // to the buffer.
            
            if(IsBeginTopic(sTag, fmt))
            {
                // See if topic has extraction flags. If it does, exclude the
				// whole topic.

                nRet = CheckTagExclusion(szCommentText, run.exprExtract, bExcludeTag);
                if(nRet)
                    PrintError(log.GetSrcFn(), in.m_lCurLine, nRet);
                
                
				if(bExcludeTag)
				{
					in.m_nState.SkipTopic = TRUE;					

                    continue;
                }
				else
				{
					in.m_nState.SkipTopic = FALSE;
				}

                in.m_nState.Topic = TRUE;
                in.m_nState.Tag = TRUE;
                in.m_nState.GrowingTag = TRUE;
				in.m_nState.HaveTopicTag = FALSE;

                in.m_nLineTag = in.m_lCurLine;

                in.m_sTag = sTag;
                
                // Eat white space following tag

                szCommentText = EatWhite(szCommentText);
                
				// Reset pending data
				
	            in.EmptyParse();

                // Reset tag pointer and tag buf.
                ZeroMem(in.m_achTagBuf, TAGBUFSIZE+1);
                in.m_szTagCur = in.m_achTagBuf;
                in.m_nLineTag = in.m_lCurLine;
	            
                nRet = AddLineToBuffer(szCommentText, in);
                if(nRet)
                    PrintError(log.GetSrcFn(), in.m_lCurLine, nRet);

                // If this line starts a new tag, store the text preceding
                // the comment.

                if(in.m_nState.BeginComment)
                {
                    memcpy(in.m_achCommentStart, in.m_szLineBuf, 
                            szComment - in.m_szLineBuf);
                    in.m_achCommentStart[szComment-in.m_szLineBuf] = '\0';
                }
                else
                {
                    in.m_achCommentStart[0] = '\0';
                }
            }
            
            // Check for @doc tag.
            
            else if(_stricmp(sTag, "doc") == 0)
            {
				// Pop out of Autoduck state.

				in.m_nState.Autoduck = FALSE;

                // Store doc tag line to be used on next call to ExtractTopic

                in.SetReuse();
            }
            
            // Continue looking. Print a warning if the line contains
            // a paragraph tag.
            
            else if(!sTag.IsEmpty() && !in.m_nState.SkipTopic)
            {
                PrintError(log.GetSrcFn(), in.m_lCurLine, warnWantTopicTag);
            }

        }   // end NOT IN TOPIC

    }   // while loop
    
    // The only way out of the while loop is EOF. Return FALSE if
    // no topic was extracted.

    CheckCurTag(in, log, out, fmt, run, FALSE);

    return !(in.m_listTags.IsEmpty());
}


