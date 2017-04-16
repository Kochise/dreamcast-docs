#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "topiclog.h"
#include "input.h"
#include "fmt.h"
#include "fmtif.h"
#include "fmttag.h"
#include "fmtDiag.h"
#include "errmsg.h"


/******************************************************/
// Tag list
/******************************************************/

TAGSPEC gtagsDiagramSection[] =
{
	CFmtListDiagram::tagPre,            "pre",
	CFmtListDiagram::tagPost,           "post",
    CFmtListDiagram::tagFormat,         "format",
    CFmtListDiagram::tagFormatFirst,    "formatfirst",
    CFmtListDiagram::tagFormatLast,     "formatlast",
    CFmtListDiagram::tagTag,            "tag",
	CFmtListDiagram::tagNullParas,      "cancelifpresent",
	CFmtListDiagram::tagIf,             "if",
    -1,        NULL,
};



/******************************************************/
// Format class
/******************************************************/

CFmtDiagram::CFmtDiagram(void) : CFmtTag(5)
{
    m_nNumFields = MAXNUMFIELDS;        // bogus value, ok.
}

CFmtDiagram::~CFmtDiagram(void)
{
	int i, n;

	for(i = 0, n = m_asNullParas.GetSize(); i < n; i++)
        delete m_asNullParas[i];
}


#ifdef _DEBUG
void CFmtDiagram::Dump(CDumpContext &dc) const
{
	CFmtTag::Dump(dc);

	dc << "\trepeat item: "<< m_sItem;
    dc << "; cancel if: ";
}
#endif

/******************************************************/
// List class
/******************************************************/

TAGSPEC *CFmtListDiagram::FmtTagList(void)
{
	return gtagsDiagramSection;
}
	

int CFmtListDiagram::ParseEntry(CFmtInput &in)
{
	int nRet;

	CFmtDiagram *pNew;

	pNew = (CFmtDiagram *)m_pNew;

	switch(m_nTag)
	{
	// Parent

	case tagTag:
		
		// Expect: .tag = name, output, paragraph tag, 

		if(in.m_nTokens != 3)
			return fmterrBadEntryCount;

		if(!CheckOutputType(in, 1))
			return 0;

		nRet = CheckAddTag();
		if(nRet)
			return nRet;

        // Make a new one

		m_pNew = pNew = new CFmtDiagram;

		m_nState.Tag = TRUE;

        // Record source file information.

        pNew->SetSource(in.m_nFile, in.m_lCurLine);

        // Get the required tag name field.
        
		nRet = ParseName(pNew->m_sName, in.m_aszTokens[0]);
		if(nRet)
			return nRet;        

        // Get the required Item field.
        
		nRet = ParseName(pNew->m_sItem, in.m_aszTokens[2]);
		if(nRet)
			return nRet;        

        break;

    case tagIf:
        
        nRet = ParseIf(*pNew, in);
        if(nRet)
           return nRet;

        break;

    // RTF file header and footer

    case tagNullParas:
    {
		if(m_nState.Skip)
			return 0;

		if(!m_nState.Tag)
			return fmterrOrphanedTag;

        ASSERT(pNew);
        
        static char szNameTerm[] = "\t ";
        const char *szT;
        const char *szEnd;
        int i, j;
        for(i = 0; i < in.m_nTokens; i++)
        {
            _strlwr(in.m_aszTokens[i]);
            szT = in.m_aszTokens[i];

            j = 0;
            do
            {
                szT = EatWhite(szT);
                if(*szT == '\0')
                    break;

                szEnd = SeekEnd(szT, szNameTerm, MAXTAGSIZE);
                if(szEnd == NULL)
                    return fmterrBadTagName;

                pNew->m_asNullParas.SetSize(++j);
                pNew->m_asNullParas[j-1] = new CString(szT, szEnd-szT);

                if(*szEnd)
                    szEnd++;

				szT = szEnd;

            } while(*szT);

        }
    	break;
    }

    case tagPre:
    case tagPost:
    case tagFormat:
    case tagFormatFirst:
    case tagFormatLast:

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


