#include <afx.h>
#include <afxtempl.h>
#ifdef _DEBUG
#include <ostream.h>
#endif
#include "errmsg.h"
#include "parse.h"
#include "topiclog.h"
#include "fmtspec.h"
#include "docexpr.h"
#include "cmdargs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int GetArgs(CStrArray &asArgs, char **argv, int argc)
{
TRY
{
    CFile file;
	CFileException e;
	char *szBuf;
	const char *szStart;
	const char *sz;
	long lcb;
    BOOL fQuoteBreak;
    int nRet = 0;
    int nArgs = 0;

    // Collect command-line arguments, including response files.

    for(int i = 1; i < argc; i++)
    {
        szBuf = NULL;

        if(argv[i][0] == '@')
        {
			// Open the response file and read contents.

			if(!file.Open(&argv[i][1], CFile::modeRead, &e))
				return e.m_cause;

		    lcb = file.Seek(0, CFile::end);
			szBuf = new char[lcb+1];

		    file.SeekToBegin();
    
		    file.Read(szBuf, (UINT)lcb);
			file.Close();

		    szBuf[lcb] = '\0';

			// Parse contents. 

		    sz = szBuf;
			fQuoteBreak = FALSE;

		  	while(*sz)
		  	{
				// Find end of string and null-terminate.

				szStart = sz = EatWhite(sz);

				// String break on space - or delimited
				// by double quotation marks

				if(fQuoteBreak || *sz == chQuote)
				{
					if(fQuoteBreak)
						fQuoteBreak = FALSE;
					else
						szStart++, sz++;

					while(*sz && *sz != chNewline && *sz != chQuote)
						sz++;

					if(*sz != chQuote)
                    {
                        nRet = errMismatchedResponseQuotes;
                        goto ExitError;
                    }
				}
				else
				{
					while(*sz && !isspace(*sz) && *sz != chQuote)
						sz++;

					fQuoteBreak = (*sz == chQuote);
				}

		        // Add the entry

		        if(*szStart)
				{
			        asArgs.SetSize(++nArgs);
			        asArgs[nArgs-1] = new CString(szStart, sz-szStart);
				}

				// Advance past newline if present.

				if(*sz)
					sz++;
		  	}

            delete szBuf;

            szBuf = NULL;
		}
		else
		{
	        asArgs.SetSize(++nArgs);
	        asArgs[nArgs-1] = new CString(argv[i]);
		}
    }

ExitError:
    if(szBuf)
        delete szBuf;
	return nRet;
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




/*
@func Parses a command-line constant definition, in the form:

/Dname=constant_text
/D name=constant_text

@rdesc Returns 0 if successful or 1 if an error occurs.
*/

int GetCmdLineConstant(
    FormatInfo &fmt, 		                    	//@parm Where to put constant defs
    const char *szArg,                          	//@parm Arg containing /D directive
    CStrArray &asArgs, 	//@parm Rest of the command line arguments
    int &i)                                     	//@parm Array index
{
TRY
{
    const char *szTag;
    const char *szText;
    CFmtConst *pNew;
    int nArgsCount = asArgs.GetSize();

    // Find where the constant def is.

    if(szArg[2])
    {
        szTag = &szArg[2];
    }
    else
    {
        if(i == nArgsCount-1)
            return 1;

        szTag = *asArgs[++i];
    }

    // Find the equal sign.

    for(int i = 0; szTag[i] != chEqual && i < MAXTAGSIZE; i++);
	if(szTag[i] != chEqual)
		return errCmdSyntaxDefine;

    // Seal off the constant name, advance to the constant text,
    // alloc mem for everything.

	szText = szTag+i+1;

	CString sTag;
	char *sz = sTag.GetBufferSetLength(i+1);
	memcpy(sz, szTag, i);
	sz[i] = '\0';
	sTag.ReleaseBuffer;

    pNew = new CFmtConst(sTag, szText);

    // Add constant def to the options.

    fmt.constant.Add(pNew);

    return 0;
}
CATCH(CMemoryException, e)
{
    return errMemory;
}
END_CATCH
}


int Assign(
	CString 	&sTarget,
	const char	*szCurArg,
	CStrArray   &asArgs,
	int     	&i,
	int     	nArgsCount,
	BOOL    	bConcat)
{
    if(*szCurArg)
	{
		if(bConcat)
	        sTarget += szCurArg;
		else
			sTarget = szCurArg;
	}
    else
    {
        if(i == nArgsCount-1)
            return errCmdSyntaxExpectedFlagFollowup;

		if(bConcat)
			sTarget += *asArgs[++i];
		else
			sTarget = *asArgs[++i];
    }

	return 0;
}


/*-----------------------------------------------------------------------
    @doc EXTERNAL AUTODUCK
        
    @func int | ParseArgs | Parses command-line arguments and fills
        <t RUNOPTIONS> structure with runtime options.
            
    @rdesc Returns 0 if successful or 1 if a syntax error in the command
    	line.
*/

int ParseArgs(
	CStrArray &asArgs,          //@parm Array of command line args
    RUNOPTIONS &run,       		//@parm Options structure to fill
    FormatInfo &fmt,			//@parm Format information file
	const char*szDefaultFmtFilename) 	//@parm Default format file
{
    const char *szArg;
    int i, nArgsCount;
	int nRet;
    int nInput = 0;
	int nFmt = 0;

	CString sMainFmtFile(szDefaultFmtFilename);
	CString *psNewFmtFile;

    nArgsCount = asArgs.GetSize();
    ZeroMem(&run.nOptions, sizeof(run.nOptions));

    run.nExampleTabSize = 8;

    for(i = 0; i < nArgsCount; i++)
    {
        szArg = *asArgs[i];

        switch (szArg[0])
        {
        case '/':
        case '-':
            switch( szArg[1] )
            {
            case '?':
            case 'H':
            case 'h':
                return errCmdSyntaxHelp;

            case 'v':
            case 'V':
                run.nOptions.Verbose = TRUE;
                break;

			case 'e':
			case 'E':
				run.nOptions.NoEmptyWarnings = TRUE;
				break;

            case 'u':
            case 'U':
                run.nOptions.Unsorted = TRUE;
                break;

            case 'n':
            case 'N':
                run.nOptions.NoOutput = TRUE;
                break;

            case 'a':
            case 'A':
                run.nOptions.Concat = TRUE;
                break;

            case 'x':
            case 'X':
				nRet = Assign(run.sDocID, &szArg[2], asArgs, i, nArgsCount, TRUE);
				if(nRet)
					return nRet;

                run.sDocID += chSpace;

                break;

            case 'r':
            case 'R':
                if(szArg[2] && (szArg[3] == '\0'))
                {
                    switch(szArg[2])
                    {
                    case 'd':
                    case 'D':
                        run.sOutputType = "doc";
                        continue;

                    case 'h':
                    case 'H':
                        run.sOutputType = "help";
                        continue;
                    }
                }

				nRet = Assign(run.sOutputType, &szArg[2], asArgs, i, nArgsCount, FALSE);
				if(nRet)
					return nRet;

                break;

            case 't':
            case 'T':
                if(!isdigit(szArg[2]))
                    return errCmdSyntaxTab;

                run.nExampleTabSize = atoi(&szArg[2]);

                break;

            case 'o':
            case 'O':
				nRet = Assign(run.sOutputFile, &szArg[2], asArgs, i, nArgsCount, FALSE);
				if(nRet)
					return nRet;

                break;
                
            case 'f':
            case 'F':
				nRet = Assign(sMainFmtFile, &szArg[2], asArgs, i, nArgsCount, FALSE);
				if(nRet)
					return nRet;

                break;
                
            case 's':
            case 'S':
				psNewFmtFile = new CString;
				nRet = Assign(*psNewFmtFile, &szArg[2], asArgs, i, nArgsCount, FALSE);
				if(nRet)
				{
					delete psNewFmtFile;
					return nRet;
				}

				run.asFmtFiles.SetSize(++nFmt);
				run.asFmtFiles[nFmt-1] = psNewFmtFile;

                break;
                
            case 'l':
            case 'L':
				nRet = Assign(run.sLogFileOut, &szArg[2], asArgs, i, nArgsCount, FALSE);
				if(nRet)
					return nRet;

                break;
                
            case 'c':
            case 'C':
				nRet = Assign(run.sLogFileIn, &szArg[2], asArgs, i, nArgsCount, FALSE);
				if(nRet)
					return nRet;

                break;
                
            case 'd':
            case 'D':
                nRet = GetCmdLineConstant(fmt, szArg, asArgs, i);
				if(nRet)
                    return nRet;
                    
                break;

            default:
                return errCmdSyntaxUnknownFlag;
            }

            break;
        
        default:
            run.asInputFiles.SetSize(++nInput);
            run.asInputFiles[nInput-1] = asArgs[i];
            asArgs[i] = NULL;
            break;
        }
    }

	if(run.asInputFiles.GetSize() == 0)
		return errNoFiles;

    if(run.sOutputType.IsEmpty())
        run.sOutputType = "doc";

    char *sz2;
	char *sz = run.sDocID.GetBuffer(run.sDocID.GetLength()+1);
	nRet = run.exprExtract.Set(sz, sz2);
	run.sDocID.ReleaseBuffer();

	run.asFmtFiles.SetSize(++nFmt);
	run.asFmtFiles[nFmt-1] = new CString(sMainFmtFile);

	if(nRet)
		return nRet;

    return 0;
}

/*-----------------------------------------------------------------------
    @doc EXTERNAL AUTODUCK
        
    @func void | Usage | Prints usage statement on <p stderr>.
        
    @parm char * | szName | Specifies a null-terminated string containing
        the name of this program.

    @rdesc Void.
*/
void Usage(const char * szName, const char *szFmtFilename)
{
    fprintf(stderr, "%s [/v] [/e] [/n] [/a] [/u] [/r[dh]] [/t[0-9]]\n\t[/o filename] [/l filename]\n\t[/f filename] [/c filename] \n\t[[/x id]...] [[/d name=text]...] files\n\n", szName);
    fprintf(stderr, "[/v]               Verbose\n");
    fprintf(stderr, "[/e]               Suppress warnings about empty fields.\n");
    fprintf(stderr, "[/n]               No output (extract only - only generate log file)\n");
    fprintf(stderr, "[/a]               Append output to existing file\n");
    fprintf(stderr, "[/u]               Don't sort topics\n");
    fprintf(stderr, "[/rd]              Generate \"doc\" output (default)\n");
    fprintf(stderr, "[/rh]              Generate \"help\" output\n");
    fprintf(stderr, "[/r output]        Generate specified output type\n");
    fprintf(stderr, "[/x expression]    Extract topics matching expression\n");
    fprintf(stderr, "[/t[0-9]]          Set tab size for example tags (default is 8)\n");
    fprintf(stderr, "[/o file]          Create (or append to) RTF file <file>\n");
    fprintf(stderr, "[/l file]          Create (or append to) topic log <file>\n");
    fprintf(stderr, "[/f file]          Use format file <file> (default is %s)\n", szFmtFilename);
    fprintf(stderr, "[/s file]          Use supplemental format file <file>\n");
    fprintf(stderr, "[/c file]          Use topic log <file>\n");
    fprintf(stderr, "[/d name=text]     Define constant <name> as <text>\n");
}


int SetRtOptions(
    RUNOPTIONS &run,
    FormatInfo &fmt,
    char **argv,
    int argc,
    const char *szDefaultFmtFilename)
{
    CStrArray asArgs;
    int nRet;
    int i, nArgs;

    nRet = GetArgs(asArgs, argv, argc);
    if(nRet)
    {
        PrintError(NULL, 0, nRet);
        return nRet;
    }

    nArgs = asArgs.GetSize();
   
    nRet = ParseArgs(asArgs, run, fmt, szDefaultFmtFilename);
    if(errCmdSyntaxHelp == nRet)
    {
        Usage(argv[0], szDefaultFmtFilename);
    }
    else if(nRet)
    {
        PrintError(NULL, NO_LINE, nRet);
    }

    for(i = 0; i < nArgs; i++)
    {
        if(asArgs[i])
            delete asArgs[i];
    }

    return nRet;
}


#ifdef _DEBUG
void DumpOptions(RUNOPTIONS &run)
{
    cout << "RUNOPTIONS dump:\n";

	cout << "\tOptions:\n";
	cout << "\t\tVerbose  " << run.nOptions.Verbose << "\n";         
    cout << "\t\tNoEmptyWarnings  " << run.nOptions.NoEmptyWarnings << "\n";         
    cout << "\t\tUnsorted  " << run.nOptions.Unsorted << "\n";
    cout << "\t\tNoOutput  " << run.nOptions.NoOutput << "\n";
    cout << "\t\tConcat  " << run.nOptions.Concat << "\n";

	cout << "\tnExampleTabSize  " << run.nExampleTabSize << "\n";
 	cout << "\tsDocID  " << run.sDocID << "\n";
    cout << "\tsOutputType  " << run.sOutputType << "\n";              
    cout << "\tsOutputFile  " << run.sOutputFile << "\n";              
    cout << "\tsLogFileIn  " << run.sLogFileIn << "\n";               
    cout << "\tsLogFileOut  " << run.sLogFileOut << "\n";              

    int nFiles = run.asInputFiles.GetSize();
	int i;
    const char *pch;

	cout << "\n\t" << nFiles << " input files, they are:\n";
    for(i = 0; i < nFiles; i++)
	{
		pch = *run.asInputFiles[i];
		cout << "\t\t" << pch << "\n";
	}
	cout << endl;

    nFiles = run.asFmtFiles.GetSize();
	cout << "\n\t" << nFiles << " format files, they are:\n";
    for(i = 0; i < nFiles; i++)
	{
		pch = *run.asFmtFiles[i];
		cout << "\t\t" << pch << "\n";
	}
	cout << endl;
}
#endif
