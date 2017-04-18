#include <afx.h>
#include <afxtempl.h>
#include "parse.h"
#include "topiclog.h"
#include "fmtspec.h"
#include "errmsg.h"

TAGSPEC SECTIONS[] =
{
    sectFILE,       "file",
    sectTOPIC,      "topic",
    sectPARAGRAPH,  "paragraph",
    sectTYPE,       "text",
    sectDIAGRAM,    "diagram",
    sectCONSTANT,   "constant",
    sectINDEX,      "index",
	sectEXTENSION,	"extension",
	sectToken,		"token",
    -1,             NULL,
};


int SeekSection(CFmtInput &in)
{
	int nRet;
	const char *sz;

	do
	{
		nRet = in.GetLine();
		if(nRet)
			return nRet;

		if(in.m_szLineBuf[0] == chFmtSectOpen)
			return 0;

		sz = EatWhite(in.m_szLineBuf);

		switch(*sz)
		{
        	// blank or comment line
			case '\0':
            case '\r': 
            case '\n':
        	case chFmtComment:
				break;
                
            default:
                return fmterrExpectedEol;
        }

	} while( !in.EndOfFile() );

	return 0;
}




int GetSection(char *szSrc, int *piSection)
{
    const char *szCont = SeekEnd(szSrc+1, chCloseBracket, MAXTAGSIZE);
	
	if(szCont == NULL || *szCont != chFmtSectClose)
		return FALSE;

    int i;

	CString sTag(szSrc+1, szCont-(szSrc+1));
    
    for(i = 0; SECTIONS[i].iTag != -1; i++)
    {
        if(_stricmp(sTag, SECTIONS[i].szName) == 0)
        {
            *piSection = SECTIONS[i].iTag;
            return TRUE;
        }
    }
    return FALSE;
}



CFmtList *GetFmtList(
    FormatInfo &fmts,
    int nSection)
{
    switch(nSection)
    {
        case sectFILE:
            return &fmts.file;
                                
        case sectTOPIC:
            return &fmts.topic;
            
        case sectPARAGRAPH:
            return &fmts.paragraph;
            
        case sectTYPE:
            return &fmts.text;
            
        case sectDIAGRAM:
            return &fmts.diagram;
            
        case sectCONSTANT:
            return &fmts.constant;

        case sectEXTENSION:
            return &fmts.extension;

        case sectINDEX:
            return &fmts.index;

		case sectToken:
			return &fmts.token;
    }

    ASSERT(0);

    return NULL;
}


int GetFormatSection(
    CFmtInput &in, 
    FormatInfo &fmts)
{
	int  nRet;
	int  nSection;
	CFmtList    *pfmt;

	// Find the opening of the section.
	
	nRet = SeekSection(in);
	
	// Exit on error or EOF.

	if(nRet)
		return nRet;

    if(in.EndOfFile())
        return 0;

    // Get the section identifier.
    
    if(!GetSection(in.m_szLineBuf, &nSection))
        return fmterrBadSection;
    
    pfmt = GetFmtList(fmts, nSection);
    
    nRet = pfmt->GetSection(in);
    if(nRet)
        return nRet;

	return 0;
}


    

int GetFormatFile(
	const char *szFile,
    const char *szAutoduckPath,
	const char *szOutputType,
	FormatInfo &fmt,
	BOOL bVerbose)
{
	CFmtInput file;
	int nRet;

	int nFile = fmt.asSrcFn.GetSize();
	fmt.asSrcFn.SetSize(nFile+1);
	fmt.asSrcFn[nFile] = new CString(szFile);

	file.SetOutputType(szOutputType);
	file.m_nFile = nFile;

	fmt.lErrLine = NO_LINE;
	
	nRet = file.OpenFmtFile(szFile, szAutoduckPath);
	if(nRet)
		return nRet;
	
	if(bVerbose)
		fprintf(stdout, "Getting tags from %s\n", (const char *)file.m_szFilename);
	
	do {
        
        nRet = GetFormatSection(file, fmt);
		if(nRet)
		{
			fmt.lErrLine = file.m_lCurLine;
			return nRet;
		}

	} while( ! file.EndOfFile() );

	file.Close();

	return 0;
}



BOOL ValidateFormats(
    FormatInfo &fmts)
{
    int nRet;
    BOOL bSuccess = TRUE;

    nRet = fmts.file.Validate();
    if(nRet) 
    {
        PrintError(NULL, NO_LINE, nRet);
        bSuccess = FALSE;
    }

    nRet = fmts.topic.Validate(); 
    if(nRet) 
    {
        PrintError(NULL, NO_LINE, nRet);
        bSuccess = FALSE;
    }

    nRet = fmts.paragraph.Validate(); 
    if(nRet) 
    {
        PrintError(NULL, NO_LINE, nRet);
        bSuccess = FALSE;
    }

    nRet = fmts.text.Validate(); 
    if(nRet) 
    {
        PrintError(NULL, NO_LINE, nRet);
        bSuccess = FALSE;
    }

    nRet = fmts.diagram.Validate(); 
    if(nRet) 
    {
        PrintError(NULL, NO_LINE, nRet);
        bSuccess = FALSE;
    }

    nRet = fmts.constant.Validate(); 
    if(nRet)
    {
        PrintError(NULL, NO_LINE, nRet);
        bSuccess = FALSE;
    }

    nRet = fmts.extension.Validate(); 
    if(nRet) 
    {
        PrintError(NULL, NO_LINE, nRet);
        bSuccess = FALSE;
    }

    nRet = fmts.index.Validate(); 
    if(nRet) 
    {
        PrintError(NULL, NO_LINE, nRet);
        bSuccess = FALSE;
    }

	nRet = fmts.token.Validate(); 
	if(nRet) 
    {
	    PrintError(NULL, NO_LINE, nRet);
        bSuccess = FALSE;
    }

    return bSuccess;
}

