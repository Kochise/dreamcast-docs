#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "input.h"
#include "topiclog.h"
#include "fmt.h"
#include "fmtif.h"
#include "fmttag.h"
#include "fmtTopic.h"
#include "errmsg.h"


/******************************************************/
// Tag list
/******************************************************/

TAGSPEC gtagsTopicSection[] =
{
    CFmtListTopic::tagTag,	  		"tag",
    CFmtListTopic::tagPre,    		"pre",
    CFmtListTopic::tagPost,   		"post",
    CFmtListTopic::tagIf,	  		"if",
	CFmtListTopic::tagContext, 		"context",
	CFmtListTopic::tagTopicOrder, 	"order",
	CFmtListTopic::tagSrcParse, 	"parsesource",
	CFmtListTopic::tagSrcParse, 	"parse",
    -1,        NULL,
};


static TAGSPEC PARSETYPES[] = 
{
	CFmtTopic::parseFunc,      	"function",
	CFmtTopic::parseMfunc,     	"memberfunction",
	CFmtTopic::parseClass,     	"class",
    CFmtTopic::parseEnum,		"enum",
	CFmtTopic::parseConstant,	"constant",
	CFmtTopic::parseBsub,		"bsub",
	CFmtTopic::parseBfunc,		"bfunc",
	CFmtTopic::parseStruct,		"struct",
	CFmtTopic::parseBtype,		"btype",
	CFmtTopic::parseUnion,		"union",
	-1, 			NULL,
};



/******************************************************/
// Format class
/******************************************************/

CFmtTopic::CFmtTopic(void) : CFmtTag(2)
{
	m_nSortWeight = 0;

	InitName(m_aNameTok, MAXTOPICNAMETOKENS);
	InitName(m_aCtxTok, MAXTOPICNAMETOKENS);

	m_nNameTokens = 0;
	m_nCtxTokens = 0;
	m_nParseType = 0;
}

CFmtTopic::~CFmtTopic(void)
{
    POSITION pos = m_listParaTags.GetHeadPosition();
    while( pos != NULL)
    {
        delete m_listParaTags.GetNext(pos);
    }
}


void CFmtTopic::PrintName(char *szNameBuf, CTag *ptag)
{
    ::PrintName(szNameBuf, m_aNameTok, m_nNameTokens, ptag, ptag);
}

void CFmtTopic::PrintContext(char *szCtxBuf, CTag *ptag)
{
    if(m_nCtxTokens == 0)
        PrintName(szCtxBuf, ptag);
    else
        ::PrintName(szCtxBuf, m_aCtxTok, m_nCtxTokens, ptag, ptag);
}



#ifdef _DEBUG
void CFmtTopic::Dump(CDumpContext &dc) const
{
	int i;

	CFmtTag::Dump(dc);

	dc << "\tsort weight: "<< m_nSortWeight << "; parse: ";
	
	for(i = 0; PARSETYPES[i].iTag != -1 && PARSETYPES[i].iTag != m_nParseType; i++);
	
	dc << PARSETYPES[i].szName << "\r\n";

    dc << "\ttag order: ";

    POSITION pos = m_listParaTags.GetHeadPosition();
    while( pos != NULL)
        dc << *m_listParaTags.GetNext(pos);

    dc << "\r\n";
}
#endif

/******************************************************/
// List class
/******************************************************/



TAGSPEC *CFmtListTopic::FmtTagList(void)
{
	return gtagsTopicSection;
}
	

int CFmtListTopic::ParseEntry(CFmtInput &in)
{
TRY
{
	int nRet;

	const char *sz1;
	CFmtTopic *pNew;

	pNew = (CFmtTopic *)m_pNew;

	switch(m_nTag)
	{
	// Parent

	case tagTag:
		
		// Expect: .tag = name, output, fields, sortweight, nametemplate

		if(in.m_nTokens != 5)
			return fmterrBadEntryCount;

		if(!CheckOutputType(in, 1))
			return 0;

		nRet = CheckAddTag();
		if(nRet)
			return nRet;

		m_pNew = pNew = new CFmtTopic;

		m_nState.Tag = TRUE;

        // Record source file information.

        pNew->SetSource(in.m_nFile, in.m_lCurLine);

        // Get the required Name field.
        
		nRet = ParseName(pNew->m_sName, in.m_aszTokens[0]);
		if(nRet)
			return nRet;        

        // Get the required number of fields
        
        nRet = ParseNumFields(pNew->m_nNumFields, in.m_aszTokens[2]);
		if(nRet)
			return nRet;
        
        // Get the required sorting weight
        
        sz1 = EatWhite(in.m_aszTokens[3]);
        if(! (isdigit(*sz1) || chHyphen == *sz1) )
            return fmterrTopicExpectedSortWeight;
            
        MakeNumber(sz1, pNew->m_nSortWeight);
        
        // Get the required field name template
        
        sz1 = EatWhite(in.m_aszTokens[4]);
        
        nRet = ParseTopicNameMask(sz1, pNew->m_aNameTok, pNew->m_nNameTokens, 
                                    pNew->m_nNumFields);
       	if(nRet)
       		return nRet;

        break;

    case tagContext:
		if(m_nState.Skip)
			return 0;

		if(!m_nState.Tag)
			return fmterrOrphanedTag;

		if(in.m_nTokens != 1)
			return fmterrBadEntryCount;

		ASSERT(m_pNew);

		sz1 = EatWhite(in.m_aszTokens[0]);

        nRet = ParseTopicNameMask(sz1, pNew->m_aCtxTok, pNew->m_nCtxTokens, 
                                    pNew->m_nNumFields);
       	if(nRet)
       		return nRet;
        
        break;

    case tagTopicOrder:
    {
    	static char szNameTerm[] = "\t ";
        CString *p;
    	const char *sz2;
        int i, j;

		if(m_nState.Skip)
			return 0;

		if(!m_nState.Tag)
			return fmterrOrphanedTag;

		if(in.m_nTokens == 0)
			return fmterrBadEntryCount;

		ASSERT(m_pNew);

        for(j = 0; j < in.m_nTokens; j++)
        {
            for(i = 0, sz1 = EatWhite(in.m_aszTokens[j]);
                *sz1; 
                sz1 = EatWhite(++sz2))
            {
    			if(!isalpha(*sz1))
    				return fmterrExpectedName;

                sz2 = SeekEnd(sz1, szNameTerm, MAXTAGSIZE);
                if(sz2 == NULL)
                    return fmterrBadTagName;

                p = new CString(sz1, sz2-sz1);

    			pNew->m_listParaTags.AddTail(p);
            }
        }

        break;                
    }
            
    case tagSrcParse:					// Get the parsing type

        nRet = ParseSrcParse(pNew->m_nParseType, in, PARSETYPES);
        if(nRet)
            return nRet;

        break;
    
    case tagIf:
        
        nRet = ParseIf(*pNew, in);
        if(nRet)
           return nRet;

        break;

    // RTF file header and footer

    case tagPre:
    case tagPost:

		// expect: .pre= format string

		nRet = SetFmtString(in, 0);

		if(nRet)
			return nRet;
		break;

    default:
        return fmterrBadFmtEntry;
    }

    return 0;
}
CATCH(CMemoryException, e)
{
    return errMemory;
}
END_CATCH
}


