#include <afx.h>
#include <afxtempl.h>

#include "parse.h"
#include "input.h"
#include "fmt.h"
#include "errmsg.h"

CString sEmpty;

//@doc 

//@module FMT.CPP | This module contains the format list, format input
// file class, and base class for all format tag objects.
//
// The format list parser, embodied in <mf CFmtList::GetSection>, calls into
// the individual format base classes <mf CFmtBase::ParseEntry> to create
// the appropriate object types and parse the entries.
//
// For searching the format file, each format tag class derived from 
// <c CFmtBase> overrides the <mf CFmtBase::Match> function. These overridden
// functions are called by <mf CFmtList::Get>; the objects are compared
// against the search query objects derived from <c CFmtSrch>.
// 
//@head3 Format Input  |
//@index | FMT & INPUT
//@head3 Format Tag   | 
//@index | FMT & ENTRYBASE
//@head3 Format List   |
//@index | FMT & ENTRYLIST
//@head3 Format Search  |
//@index | FMT & SRCHBASE
//@head3 Generic Stuff   |
//@index | FMT & GENERIC




/**************************************************************************/
//@doc FMT GENERIC

//@func Copies a string from source to destination, stripping
// extra whitespace out of the source string (destination string
// contains each token followed by a single space, including the
// last token). Also normalizes to all uppercase.
//
// @comm Destination string should be same length as source string.

void CopyFlags(
    CString &sDest,			//@parm Destination string
    const char *szSrc)	    //@parm Source string
{
    const char *szEnd;
    static char szFlagStopChar[] = " \t\r\n*";
    static char szFlagEolChar[] = "\r\n*";
    char szToken[MAXTAGSIZE+1];

    ASSERT(szSrc);

    sDest.Empty();

    for(szSrc = EatWhite(szSrc); 
        *szSrc && strchr(szFlagEolChar, *szSrc) == 0; 
        szSrc = EatWhite(szEnd))
	{
        szEnd = strpbrk(szSrc, szFlagStopChar);

        if(NULL == szEnd)
            szEnd = szSrc+strlen(szSrc);

        if(szEnd-szSrc > MAXTAGSIZE)
            szEnd = szSrc+MAXTAGSIZE;

        memcpy(szToken, szSrc, szEnd-szSrc);
        szToken[szEnd-szSrc] = '\0';

		sDest += chSpace;
        sDest += szToken;
	}

	sDest += chSpace;
    sDest.MakeUpper();
}


/**************************************************************************/

//@doc FMT INPUT

//@mfunc Constructor, zeroes the state variables and filename.
CFmtInput::CFmtInput(void)
{
	m_nTokens = 0;
    ZeroMem(&m_nAdState, sizeof(m_nAdState));
    ZeroMem(m_szFilename, _MAX_PATH+1);
}

//@mfunc Breaks the input line into a series of comma-separated
// tokens. Sets fields of <md .m_aszTokens> to the starting points of
// the fields, and updates <md .m_nTokens>. Each field is null-terminated.

void CFmtInput::Tokenize(
	char *szSrc)        //@parm Optional point at which to start tokenizing;
{                       // if omitted, tokenizes <md .m_szLineBuf>.
	char *szToken;

	static char szFieldTerm[] = ";,\r\n";
	static char szLineTerm[]  = ";\r\n";

	if(szSrc == NULL)
		szSrc = m_szLineBuf;

	ASSERT(szSrc);

	ZeroMem(m_aszTokens, sizeof(char *)*MAXFMTTOKENS);
	
	int fContinue = TRUE;

	for(m_nTokens = 0; fContinue && m_nTokens < MAXFMTTOKENS; szSrc++, m_nTokens++)
	{
		for(szToken = szSrc; *szSrc && !strchr(szFieldTerm, *szSrc); szSrc++);

		m_aszTokens[m_nTokens] = szToken;

		if(*szSrc == '\0' || strchr(szLineTerm, *szSrc))
			fContinue = FALSE;
		
		*szSrc = '\0';
	}
}


/**************************************************************************/

//@mfunc Opens a format file, using the <mf .GetPath> function to 
// search for the file.
//
//@rdesc Zero or an error code.

int CFmtInput::OpenFmtFile(
	const char *szName,         //@parm Format filename
	const char *szAutoduckPath)  //@parm Autoduck.Exe path name.
{
TRY
{
	int nRet;

	ASSERT(m_szFilename);

	nRet = GetPath(szName, szAutoduckPath);
	if(nRet)
		return nRet;

	Open(m_szFilename, typeBinary | modeRead);

	return 0;
}
CATCH(CFileException, e)
{
	return e->m_cause;
}
END_CATCH
}


//@mfunc Finds the specified file and copies a fully qualified path
// name to the <p szFullPath> buffer.
//
// Searches: current directory; then the directory in which AUTODUCK.EXE
// is located; then the search path. If a drive letter or subdirectory
// path is specified, it just looks there.
//
//@rdesc Zero if the specfied file was found and 1 if no file was found.


int CFmtInput::GetPath(
	const char *szTarget, 			//@parm Name of format file to find.
	const char *szAutoduckPath)        //@parm Location of AUTODUCK.EXE
{		                        
	CFileStatus status;
	char szPath[_MAX_PATH];


    ASSERT(m_szFilename != NULL);

    // First look in the current directory.

    if(GetStatus(szTarget, status))
    {
        strcpy(m_szFilename, szTarget);
        return 0;
    }
	
	// If file not found, and a subdir path or drive letter
	// was specified, exit now.

	if(*szTarget == chBackslash || *(szTarget+1) == chColon ||
	   *szTarget == chPeriod)
	{
		return errFileNotFound;
	}

	// Now look in the same directory as AUTODUCK.EXE
	    
    ASSERT(szAutoduckPath);
    _splitpath(szAutoduckPath, m_szFilename, szPath, NULL, NULL);
    strcat(m_szFilename, szPath);
    strcat(m_szFilename, szTarget);

    if(GetStatus(m_szFilename, status))
    	return 0;

	// Finally, search the path.

    _searchenv(szTarget, "PATH", m_szFilename);
    if(GetStatus(m_szFilename, status))
		return 0;

	return errFileNotFound;
}


/***********************************************************/

//@mfunc Set the output type for the extract operation.

void CFmtInput::SetOutputType(
    const char *szOutputType)   //@parm Output type.
{
	ASSERT(szOutputType);

	m_sOutputType = szOutputType;
}




/**************************************************************************/

//@doc FMT ENTRYBASE

//@mfunc Constructs a format base class.

CFmtBase::CFmtBase(
    int nFmtStrings)    //@parm How many format strings in the class
{
	m_aFmtStrings.SetSize(nFmtStrings);

    m_nInput = 0;
    m_lSrcLine = 0;
}


//@mfunc Destructs a format base class. Deletes all format strings.

CFmtBase::~CFmtBase(void)
{
    for(int i = 0; i < m_aFmtStrings.GetSize(); i++)
        if(m_aFmtStrings[i])
        	delete m_aFmtStrings[i];
}



/***********************************************************/
// Format string access
/***********************************************************/

//@mfunc Retrieves a format string. Always returns a valid
// <c CString> object (empty if format string not specified
// in format file.
//
//@rdesc Reference to the specified format string. If <p nFmt>
// is out of range an empty string is returned.

CString &CFmtBase::GetFmtString(
    int nFmt)                   //@parm Which format string to retrieve
{
    ASSERT(nFmt < m_aFmtStrings.GetSize());

    if(nFmt >= m_aFmtStrings.GetSize())
        return sEmpty;

    if(NULL == m_aFmtStrings[nFmt])
        return sEmpty;
    else
        return *m_aFmtStrings[nFmt];
}



#ifdef _DEBUG

//@func Dumps a format string.

void DumpFmt(
    CDumpContext &dc,   //@parm Dump context.
    const char *szBuf)  //@parm Format string to dump.
{
    int nLen = strlen(szBuf);
    int nRight, i;
    char szChar[2];
    
    szChar[0] = szChar[1] = '\0';

    for(i = 0; i < 20 && i < nLen; i++)
    {
        switch(szBuf[i])
        {
        case '\r':
            dc << "^r";
            break;
        case '\n':
            dc << "^n";
            break;
        case '\t':
            dc << "^t";
            break;
        default:
            szChar[0] = szBuf[i];
            dc << szChar;
            break;
        }
    }

    
    dc << " ... ";

    if(nLen > 20)
    {
        nRight = max(nLen-20, 20);

        for(i = nRight; i < nLen; i++)
        {
            switch(szBuf[i])
            {
            case '\r':
                dc << "^r";
                break;
            case '\n':
                dc << "^n";
                break;
            case '\t':
                dc << "^t";
                break;
            default:
                szChar[0] = szBuf[i];
                dc << szChar;
                break;
            }
        }
    }
}

//@mfunc Dumps a format object.

void CFmtBase::Dump(
    CDumpContext &dc) const     //@parm Dump context.
{
    int nFmtStrings = m_aFmtStrings.GetSize();

	dc << "CFmtBase: " << nFmtStrings << " strings:\r\n";
    
	for(int n = 0; n < nFmtStrings; n++)
    {
		dc  << "\t[" << n << "]: ";

        if(m_aFmtStrings[n])
	        DumpFmt(dc, *m_aFmtStrings[n]);
		else
			dc << "NULL";

        dc << "\n";
    }
}
#endif

/**************************************************************************/


// ***********************
// Ctor
// ***********************

//@doc FMT ENTRYLIST


//@mfunc Format list class. This object stores a homogenous 
// list of formatting objects.

CFmtList::CFmtList(void)
{
	m_pNew = NULL;

	m_lPosStart = -1;
	m_lPosCur = -1;
	m_lPosNext = -1;

	m_nTag = -1;

	m_nState.Tag   = 0; 
	m_nState.Multi = 0; 
	m_nState.Done  = 0; 
	m_nState.Skip  = 0;
}


//@mfunc Destructs the list.

CFmtList::~CFmtList(void)
{
	POSITION pos;
	CFmtBase *p;

	//Iterate through the list in head-to-tail order.
	for( pos = m_listTags.GetHeadPosition(); pos != NULL; )
	{
		p = m_listTags.GetNext( pos );
	
		delete p;
	}
}


#ifdef _DEBUG

//@mfunc Dumps the format list.

void CFmtList::Dump( 
    CDumpContext &dc ) const        //@parm Where to dump to
{
 	dc << "CFmtList -- Count = " << m_listTags.GetCount() << "\r\n";
	dc << m_listTags << "\r\n";
}
#endif



// ***********************
// Section parsing functions
// ***********************

//@mfunc Parses a format file section. The input file state <p in>
// is left at the next format file section or EOF (or at the position
// of the parsing error).
//
//@rdesc Zero if parsing successful or an error code if a parsing
// error occurred.

int CFmtList::GetSection(
    CFmtInput &in)          //@parm Input state.
{
TRY
{
    int  nRet;                              // Return values

    const char *szT;                              // Temp
    
	m_nState.Tag   = 0; 
	m_nState.Multi = 0; 
	m_nState.Done  = 0; 
	m_nState.Skip  = 0;

	m_nTag 		= 0;
	m_lPosNext 	= in.GetCurPos();
	m_lPosStart = 0;

    while(!(m_nState.Done))
    {
		// Remember position of next line to read.

       	m_lPosCur = m_lPosNext;
        
        // Get the next input line, storing the current & next line positions
        
        nRet = in.GetLine();
    	if(nRet)
            return nRet;
        
		// If at EOF we will finish on this line.

		if(in.EndOfFile())
			m_nState.Done = TRUE;

		// Get the position of the next line.

		m_lPosNext = in.GetCurPos();

        // If in the process of adding multiline text, see if this line ends
        // the text block. If so, read the text into memory.
        
        if(m_nState.Multi)
        {
            nRet = CheckFmtString(in);
            if(nRet)
                return nRet;
                
            // If we're still in add-mode, skip this line (it's just free-form
            // text belonging to a previous tag).
            
            if(m_nState.Multi)
                continue;
        }
        
        // Now start parsing the entry line.
        
        szT = in.m_szLineBuf; 

        switch(*szT)
        {
        case chFmtSectOpen:			// End of section?
            m_nState.Done = TRUE;
			in.SetReuse();
            break;
        
        case chFmtTagOpen:         // Tag? Get the tag, and process it...
            
            szT = GetFmtTag(in);
            if(szT == NULL)
                return fmterrBadFmtEntry;

			in.Tokenize(in.m_szLineBuf+(szT-in.m_szLineBuf));

			nRet = ParseEntry(in);
			if(nRet)
				return nRet;
		
			break;

        default:                    // Any other line must be empty or a comment
            szT = EatWhite(szT);
            if(*szT == '\0' || *szT == chFmtComment)
                break;
            else
                return fmterrExpectedEol;
        }
    }
    
	nRet = CheckAddTag();
	if(nRet)
		return nRet;

    return Validate();
}
CATCH(CMemoryException, e)
{
    return errMemory;
}
END_CATCH
}



//@mfunc Called when a new tag is encountered in the format section,
// this function adds the current tag to the list.
//
//@rdesc Zero or an error code if the current tag is missing some
// pieces.

int CFmtList::CheckAddTag(void)
{
	int nRet;
		
	if(m_pNew)
	{
		nRet = m_pNew->Validate();
		if(nRet)
			return nRet;
		
		m_listTags.AddTail(m_pNew);
		m_pNew = NULL;
	}

	return 0;
}


//@mfunc Checks the input state to determine whether the current
// format string should be terminated and added to the tag.
//
//@rdesc Zero on success or an error code if a memory or file
// exception occurs.

int CFmtList::CheckFmtString(
	CFmtInput &in)				//@parm Input state structure
{
TRY
{
    DWORD dwCharsRead;
	DWORD dwToRead;

    if(m_nState.Done || 
       in.m_szLineBuf[0] == chFmtSectOpen ||
       in.m_szLineBuf[0] == chFmtTagOpen  ||
       in.m_szLineBuf[0] == chFmtComment  ||
       in.m_szLineBuf[0] == '\0')
    {
        m_nState.Multi = FALSE;

		if(m_nState.Skip)
			return 0;			

        ASSERT(m_pNew);
        ASSERT(m_nTag <= m_pNew->m_aFmtStrings.GetSize());

	    dwToRead = m_lPosCur - m_lPosStart - 2;

        ASSERT(dwToRead >= 0);
		ASSERT(m_pNew->m_aFmtStrings[m_nTag] == NULL);

	    m_pNew->m_aFmtStrings[m_nTag] = new CString;

	    if(dwToRead > 0)
        {
		    in.Seek(m_lPosStart, CFile::begin);

		    LPTSTR sz = m_pNew->m_aFmtStrings[m_nTag]->GetBufferSetLength(dwToRead+1);
    
		    dwCharsRead = in.ReadHuge(sz, dwToRead);
    
		    sz[dwCharsRead] = '\0';

			m_pNew->m_aFmtStrings[m_nTag]->ReleaseBuffer();

		    in.Seek(m_lPosNext, CFile::begin);
        }
    }

    return 0;
}
CATCH(CFileException, e)
{
    return e->m_cause;
}
AND_CATCH(CMemoryException, e)
{
    return errMemory;
}
END_CATCH
}



//@mfunc Gets the index of the current format tag. Calls the <mf .FmtTagList>
// structure to obtain the list of tags for the child format object.
//
//@rdesc Returns a pointer to the first character following the tag name.

const char *CFmtList::GetFmtTag(
    CFmtInput &in)                 //@parm Format input state.
{
	const char *szEnd = SeekEnd(in.m_szLineBuf+1, " =", MAXTAGSIZE);
	if(szEnd == NULL)
		return NULL;

	CString sTag(in.m_szLineBuf+1, szEnd-(in.m_szLineBuf+1));

    int i;

	TAGSPEC *aTagList = FmtTagList();
    
    szEnd = EatWhite(szEnd);
    if(*szEnd != chFmtDefSep)
        return NULL;
        
    for(i = 0; aTagList[i].iTag != -1; i++)
    {
        if(_stricmp(sTag, aTagList[i].szName) == 0)
        {
            m_nTag = aTagList[i].iTag;
            return ++szEnd;
        }
    }
    return NULL;
}



/**************************************************************************/

//@mfunc Adds the format object to the list.
//
//@rdesc Zero or errMemory if a memory exception occurs.

int CFmtList::Add(
    CFmtBase *p)                //@parm Format object to add
{
TRY
{
    ASSERT(p);

    m_listTags.AddTail(p);

    return 0;
}
CATCH(CMemoryException, e)
{
    return errMemory;
}
END_CATCH
}


/**************************************************************************/

// Tag retrieval

//@mfunc Retrieves a formatting object from the list, given
// a format-file search query. The function calls the <mf CFmtBase::Match>
// function, which is overridden in child classes to perform section-specific
// comparisons. 
//
//@rdesc Pointer to the matching format object, or NULL if no object matches.

CFmtBase *CFmtList::Get(
    CFmtSrchBase *psrch)    //@parm Search object. Child objects cast this 
{                           // to the appropriate search object type.
	POSITION pos;
	CFmtBase *p;

	pos = m_listTags.GetHeadPosition();

	while(pos != NULL)
	{
		p = m_listTags.GetNext(pos);

		if(p->Match(psrch))
			return p;
	}

	return NULL;
}

/**************************************************************************/

// Helper functions for derived classes

//@mfunc Sets the parser up to accept the current line as a format 
// string. Sets state variables and performs standard validations on
// the input state.
//
//@rdesc Zero if successful or an error code if a parsing error occured.

int CFmtList::SetFmtString(
	CFmtInput &in,          //@parm INput state
	int nField)             //@parm Which token has the format string
{
	m_nState.Multi = TRUE;

	if(m_nState.Skip)
		return 0;

	if(!m_nState.Tag)
		return fmterrOrphanedTag;

	ASSERT(m_pNew);
	ASSERT(nField < in.m_nTokens);

	if(m_pNew->m_aFmtStrings[m_nTag])
		return fmterrDuplicateEntry;

	m_lPosStart = m_lPosCur + 
		(in.m_aszTokens[nField] - in.m_szLineBuf);

    ASSERT(m_lPosStart > 0 && m_lPosStart > m_lPosCur);

	return 0;
}


// ***********************
// Output Type functions
// ***********************

//@mfunc Checks an output type string in a tag definition against the
// output type stored in <md CFmtInput.m_sOutputType>. Sets state variables
// in <p in> to read or skip tag definitions depending on whether the output
// types match.
//
//@rdesc TRUE if in tag state or FALSE if output type does not match.

int CFmtList::CheckOutputType(
	CFmtInput &in,              //@parm Input state
	int  nTagField)             //@parm Which tag field token has the output
{                               // type.

	ASSERT(!in.m_sOutputType.IsEmpty());

	const char *szStart = EatWhite(in.m_aszTokens[nTagField]);
	const char *szEnd   = TrimWhite(szStart+strlen(szStart), szStart);

	CString sOutputType(szStart, szEnd-szStart+1);

	// If output type of tag is within set that we are considering,
	// retain it; otherwise, we will discard it and all child
	// elements.

	if((_strcmpi(sOutputType, in.m_sOutputType) == 0) ||
	   (_strcmpi(sOutputType, "both") == 0 && 
	    (_strcmpi(in.m_sOutputType, "doc") == 0 || _strcmpi(in.m_sOutputType, "help") == 0)
	   )
	  )
	{
		m_nState.Tag = TRUE;
		m_nState.Skip = FALSE;
	}
	else
	{
		m_nState.Tag = FALSE;
		m_nState.Skip = TRUE;
	}

	return m_nState.Tag;
}


