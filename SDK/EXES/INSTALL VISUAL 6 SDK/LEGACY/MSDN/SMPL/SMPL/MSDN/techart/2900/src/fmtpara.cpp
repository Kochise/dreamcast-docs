#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "topiclog.h"
#include "input.h"
#include "fmt.h"
#include "fmtif.h"
#include "fmttag.h"
#include "fmtPara.h"
#include "errmsg.h"


/******************************************************/
// Tag list
/******************************************************/

TAGSPEC gtagsParaSection[] =
{
    CFmtListPara::tagTag,	  		"tag",
    CFmtListPara::tagPre,    		"pre",
    CFmtListPara::tagFormat,        "format",
    CFmtListPara::tagPost,   		"post",
    CFmtListPara::tagIf,	  		"if",
	CFmtListPara::tagSrcParse, 	    "parsesource",
	CFmtListPara::tagSrcParse, 	    "parse",
	CFmtListPara::tagMap,			"map",
    -1,        NULL,
};


static TAGSPEC PARSETYPES[] = 
{
	CFmtPara::parseMember,     	"classmember",
    CFmtPara::parseField,		"field",
    CFmtPara::parseParam, 	    "parameter",
    CFmtPara::parseParamOpt,    "parameteropt",
    CFmtPara::parseEmem,	    "emem",
	CFmtPara::parseBparam,		"bparameter",
	CFmtPara::parseBfield,		"bfield",
	CFmtPara::parseMeth,		"method",
	-1, 			NULL,
};


/******************************************************/
// Map class
/******************************************************/

CMapPara::CMapPara(void)
{
	InitName(m_name, MAXNUMFIELDS);
}


/******************************************************/
// Format class
/******************************************************/

CFmtPara::CFmtPara(void) : CFmtTag(3)
{
	m_nLevel = 0;
	m_nParseType = 0;
    m_nFlags.isExample = FALSE;
}

CFmtPara::~CFmtPara(void)
{
	POSITION pos = m_mapPara.GetHeadPosition();
	CMapPara *p;

	while( pos != NULL )
	{
		p = m_mapPara.GetNext(pos);
		delete p;
	}
}

NAMETOKEN *CFmtPara::GetMap(const char *szTag)
{
	CMapPara *pmap;
	POSITION pos = m_mapPara.GetHeadPosition();

	while( pos != NULL )
	{
		pmap = m_mapPara.GetNext(pos);
		if(_stricmp(pmap->m_sName, szTag) == 0)
			return pmap->m_name;
	}

	return NULL;
}




#ifdef _DEBUG
void CFmtPara::Dump(CDumpContext &dc) const
{
	CFmtTag::Dump(dc);

	dc << "\tlevel: "<< m_nLevel << "; example=";
    if(m_nFlags.isExample)
        dc << "yes";
    else
        dc << "no";
    dc << "; parse: ";
	
	for(int i = 0; PARSETYPES[i].iTag != -1 && PARSETYPES[i].iTag != m_nParseType; i++);
	
	dc << PARSETYPES[i].szName << "\r\n";
}
#endif

/******************************************************/
// List class
/******************************************************/


TAGSPEC *CFmtListPara::FmtTagList(void)
{
	return gtagsParaSection;
}
	

int CFmtListPara::ParseEntry(CFmtInput &in)
{
	int nRet;
	const char *sz1;

	CFmtPara *pNew;

	pNew = (CFmtPara *)m_pNew;

	switch(m_nTag)
	{
	// Parent

	case tagTag:
		
		// Expect: .tag = name, output, fields, sortweight, nametemplate

		if(in.m_nTokens != 4 && in.m_nTokens != 5)
			return fmterrBadEntryCount;

		if(!CheckOutputType(in, 1))
			return 0;

		nRet = CheckAddTag();
		if(nRet)
			return nRet;

        // Make a new one

		m_pNew = pNew = new CFmtPara;

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
        
        // Get the required level
        
        sz1 = EatWhite(in.m_aszTokens[3]);
        if(!isdigit(*sz1))
            return fmterrParaExpectedLevel;
            
        MakeNumber(sz1, pNew->m_nLevel);
        
        // Example tag flag 
        
        if(in.m_nTokens == 5)
        {
            sz1 = EatWhite(in.m_aszTokens[4]);
            switch(*sz1)
            {
            case '0':
                pNew->m_nFlags.isExample = FALSE;
                break;

            case '1':
                pNew->m_nFlags.isExample = TRUE;
                break;

            default:
                return fmterrParaExpectedExFlag;
            }
        }

        break;

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

	case tagMap:
	{
		// Validate entry.

		if(m_nState.Skip)
			return 0;

		if(!m_nState.Tag)
			return fmterrOrphanedTag;

		if(in.m_nTokens < 2 || in.m_nTokens > MAXNUMFIELDS+1)
			return fmterrBadEntryCount;

		// Make a map.
		CMapPara *pmap = new CMapPara;

        // Get the required Name field.
        
		nRet = ParseName(pmap->m_sName, in.m_aszTokens[0]);
		if(nRet)
			return nRet;
        
        // Get the name mapping

		int i,j;
		const char *sz;
		for(i = 1, j = 0; i < in.m_nTokens; i++, j++)
		{
			sz = EatWhite(in.m_aszTokens[i]);
			if(chDollar != *sz)
				return fmterrBadMapFieldReference;

			sz++;
			nRet = ParseNameToken(sz, &pmap->m_name[j], pNew->m_nNumFields);
			if(nRet)
				return nRet;
		}

		pNew->m_mapPara.AddTail(pmap);

		break;
	}

    // RTF file header and footer

    case tagPre:
    case tagPost:
    case tagFormat:

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
