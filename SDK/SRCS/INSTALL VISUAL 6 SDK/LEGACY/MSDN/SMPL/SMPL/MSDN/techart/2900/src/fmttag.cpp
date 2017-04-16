#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "input.h"
#include "topiclog.h"
#include "fmt.h"
#include "fmtif.h"
#include "fmttag.h"
#include "errmsg.h"

//@doc

//@module FMTTAG.CPP | This module defines a base format tag and format
// search query for Autoduck tags: topic, paragraph, text, diagram, etc.
//
// The base format tag object provides support for format-file IF statements
// and tag field counts. It also provides the <mf CFmtTag::Match> function,
// which matches a tag definition based on tag name and on topic-log
// lookups, tag text comparisons, tag field checks, etc.
//
// The base format list object provides helper functions for parsing
// standard tag entries such as name, field count, parsing type, and
// IF statements.
// 
//@head3 Tag Base Class |
//@index | FMT & TAGBASE
//@head3 Tag List |
//@index | FMT & TAGLIST
//@head3 Tag Search |
//@index | FMT & TAGSEARCH

//@doc FMT TAGSEARCH


/******************************************************/
// Search class
/******************************************************/

//@mfunc Constructs the search tag. Sets the log, tag,
// and topic pointers to NULL.

CFmtSrchTag::CFmtSrchTag(void) 
{
    m_pLog = NULL; 
    m_ptagTag = NULL; 
    m_plistTags = NULL;
}


/******************************************************/
// Format class
/******************************************************/


//@doc FMT TAGBASE

//@mfunc Constructs the tag object. Sets field count and
// IF count to 0.

CFmtTag::CFmtTag(
    int nFmtStrings) : CFmtBase(nFmtStrings) //@parm Format string count
{
	m_nNumFields = 0;
	for(int i = 0; i < MAXNUMIFS; i++)
		m_apIf[i] = NULL;
	m_nNumIf = 0;
}


//@mfunc Destructs the tag object.

CFmtTag::~CFmtTag(void)
{
	PIFCONDITION pIf, pIfNext;
	for(int i = 0; i < m_nNumIf; i++)
    {
        for(pIf = m_apIf[i]; pIf; pIf = pIfNext)
        {
		    pIfNext = pIf->next;
		    delete pIf;
		 }
    }
}


//@mfunc Matches the tag format against a search query specified
// in a <c CFmtSrchTag> object.
//
//@rdesc TRUE if they match, FALSE otherwise.
//
//@comm If the topic log & tag structures are uninitialized in the
// <c CFmtSrchTag> object, the function just does a match on the
// tag name. This means the first tag object with the same tag name
// will be returned if no log or tag structures are provided.

int CFmtTag::Match(
    CFmtSrchBase *psrch)    //@parm Pointer to a <c CFmtSrchTag> object
{
	CFmtSrchTag *psrchTag = (CFmtSrchTag *)psrch;

	ASSERT(psrchTag);

    // See if tag names match

    if(_strcmpi(psrchTag->m_sName, m_sName))
        return FALSE;

    // If no log provided, just return TRUE.

    if(NULL == psrchTag->m_pLog)
        return TRUE;

	// If the log is there the current tag & tag list
	// variables should be there as well.

	ASSERT(psrchTag->m_ptagTag);
	ASSERT(psrchTag->m_plistTags);

    // Otherwise check the if statements.

    if(m_nNumIf == 0)
        return TRUE;

    // Eventually we will do an expression eval with ANDs and ORs
	// but for now it is a straight OR comparison
    
    for(int i = 0; i < m_nNumIf; i++)
    {
    	if(EvalIfCondition(m_apIf[i],
    					   psrchTag->m_pLog, 
    					   psrchTag->m_plistTags,
    					   psrchTag->m_ptagTag))
		{
            return TRUE;
		}
	}
    return FALSE;
}




#ifdef _DEBUG
//@mfunc Dumps the tag structure to a <c CDumpContext>.

void CFmtTag::Dump(
    CDumpContext &dc) const     //@parm Where to dump to
{
	CFmtBase::Dump(dc);

	dc << "\ttag name: " << m_sName
	   << "; " << m_nNumFields << " fields; "
       << m_nNumIf << " if statements: ";
    
    PIFCONDITION pIf;      
    for(int i = 0; i < m_nNumIf; i++)
    {
        dc << "if: ";
        for(pIf = m_apIf[i]; pIf; pIf = pIf->next)
        {
            switch(pIf->nType)
            {
            case ifTopicExists:
                dc << "TopicExists; ";
                break; 
            case ifExpression:
                dc << "Expression; ";
                break; 
            case ifTagExists:
                dc << "TagExists; ";
                break; 
            case ifFieldEmpty:
                dc << "FieldEmpty; ";
                break; 
            }
        }
    }
    dc << "\n";
        
}
#endif


/******************************************************/
// List class
/******************************************************/

//@doc FMT TAGLIST

//@mfunc Helper function for derived classes, parses the .IF format 
// definition.
//
// @rdesc Zero or an error code returned from <f GetIfCondition>.

int CFmtListTag::ParseIf(
    CFmtTag &tag,           //@parm Parent tag format 
    CFmtInput &in)          //@parm Format input file
{
    int nRet;

	if(m_nState.Skip)
		return 0;

	if(!m_nState.Tag)
		return fmterrOrphanedTag;

    if(tag.m_nNumIf == MAXNUMIFS)
        return fmterrTooManyIfs;
         
    for(int i = 0; i < in.m_nTokens; i++)
    {
        nRet = GetIfCondition(in.m_aszTokens[i], tag.m_apIf[tag.m_nNumIf], tag.m_nNumFields);
        if(nRet)
            return nRet;
    }

    tag.m_nNumIf++;

    return 0;
}

//@mfunc Helper function for derived classes, parses a field count
// value.
//
//@rdesc Zero or an error code.

int CFmtListTag::ParseNumFields(
    int &nFields,                   //@parm Returns field count value.
    const char *&sz)                //@parm Pointer to textual field count
{                                   // from format line.
    sz = SeekNumber(sz);
    if(NULL == sz)
        return fmterrExpectedFieldCount;
        
    sz = MakeNumber(sz, nFields);
    if(nFields > MAXNUMFIELDS)
        return fmterrBadFieldCount;
	
	return 0;
}


//@mfunc Helper function for derived classes, parses a tag name
// string.
//
//@rdesc Zero or an error code.

int CFmtListTag::ParseName(
    CString &sName,         //@parm Destination <c CString> for tag name.
    const char *&sz)        //@parm Pointer to name text from fmt entry
{
    char szNameTerm[] = "\t ";

    if((sz = SeekLetter(sz)) == NULL)
        return fmterrExpectedName;
    
    const char *szEnd = SeekEnd(sz, szNameTerm, MAXTAGSIZE);
    if(szEnd == NULL)
        return fmterrBadTagName;

	sName = CString(sz, szEnd-sz);

    sz = szEnd;

    return 0;
}


//@mfunc Helper function for derived classes, parses a source parsing
// specifier.
//
//@rdesc Zero or an error code.

int CFmtListTag::ParseSrcParse(
    int &nParse,                //@parm Returns parsing type
    CFmtInput &in,              //@parm Format input file
    TAGSPEC *pTypes)            //@parm List of parsing types
{
	static char szNameTerm[] = "\t ";
	const char *sz1;
	const char *sz2;

	if(m_nState.Skip)
		return 0;

	if(!m_nState.Tag)
		return fmterrOrphanedTag;

	if(in.m_nTokens != 1)
		return fmterrBadEntryCount;

	sz1 = EatWhite(in.m_aszTokens[0]);
	sz2 = SeekEnd(sz1, szNameTerm, MAXTAGSIZE);
	if(sz2 == NULL)
		return fmterrBadSrcParse;

	CString sName(sz1, sz2-sz1);

    // Get the source parsing type name
    
    ASSERT(pTypes);

    while(pTypes->iTag != -1)
	{
    	if(_stricmp(sName, pTypes->szName) == 0)
    		break;

        pTypes++;
	}
    		
   	if(pTypes->iTag == -1)
   		return fmterrBadSrcParse;

	nParse = pTypes->iTag;

    return 0;
}
