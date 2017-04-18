#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "input.h"
#include "fmt.h"
#include "fmtExt.h"
#include "errmsg.h"




/******************************************************/
// Tag list
/******************************************************/

TAGSPEC gtagsExtSection[] =
{
	CFmtListExt::tagExt,           "ext",
    -1,        NULL,
};


TAGSPEC gtagsSrcTypes[] =
{
    sourceC,    "c",
    sourceAsm,  "asm",
    sourceBas,  "bas",
    -1,     NULL,
};


/******************************************************/
// Format class
/******************************************************/

CFmtExt::CFmtExt(void) : CFmtBase(3)
{
}


CFmtExt::Match(CFmtSrchBase *p)
{
    CFmtSrchExt *pExt = (CFmtSrchExt *)p;
    
    return _stricmp(m_sExt, pExt->m_sExt) == 0;
}

#ifdef _DEBUG
void CFmtExt::Dump(CDumpContext &dc) const
{
	CFmtBase::Dump(dc);

	dc << "\tExt: "<< m_sExt;
    for(int i = 0; gtagsSrcTypes[i].iTag != m_nSrcType; i++)
    	ASSERT(gtagsSrcTypes[i].iTag != -1);

	dc << "; Type: " << m_nSrcType << "(" << gtagsSrcTypes[i].szName << ")\r\n";
}
#endif



/******************************************************/
// List class
/******************************************************/

TAGSPEC *CFmtListExt::FmtTagList(void)
{
	return gtagsExtSection;
}
	

int CFmtListExt::ParseEntry(CFmtInput &in)
{
	CFmtExt *pNew;
    const char *sz;
    static char szNameTerm[] = "\t ";
	int nRet;
	    
	switch(m_nTag)
	{
	// Parent

	case tagExt:
	{
        // expect: .define=name , format string

		if(in.m_nTokens != 2)
			return fmterrBadEntryCount;

        // Make a new one

		nRet = CheckAddTag();
		if(nRet)
			return nRet;

		m_pNew = pNew = new CFmtExt;

		m_nState.Tag = TRUE;

        // Get the Extension

        sz = EatWhite(in.m_aszTokens[0]);
        if(!isalnum(*sz))
            return fmterrExpectedExtension;
    
        const char *szEnd = SeekEnd(sz, szNameTerm, MAXTAGSIZE);
        if(szEnd == NULL)
            return fmterrBadTagName;

        pNew->m_sExt = CString(sz, szEnd-sz);

        // Record source file information.

        pNew->SetSource(in.m_nFile, in.m_lCurLine);
		
		// Set the format string.

		sz = EatWhite(in.m_aszTokens[1]);
        szEnd = SeekEnd(sz, szNameTerm, MAXTAGSIZE);
        if(szEnd == NULL)
            return fmterrBadFilenameExtension;

        CString sName(sz, szEnd-sz);

        for(int i = 0; gtagsSrcTypes[i].iTag != -1; i++)
		{
            if(_stricmp(gtagsSrcTypes[i].szName, sName) == 0)
			{
				pNew->m_nSrcType = gtagsSrcTypes[i].iTag;                                
                break;
			}
		}

        if(gtagsSrcTypes[i].iTag == -1)
            return fmterrBadSrcType;

		break;
	}

    default:
        return fmterrBadFmtEntry;
    }

    return 0;
}

