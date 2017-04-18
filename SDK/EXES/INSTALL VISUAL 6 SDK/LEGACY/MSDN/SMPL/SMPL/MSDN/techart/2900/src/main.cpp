#include <afx.h>
#include <afxtempl.h>
#include <process.h>		// for _getpid()
#include <io.h>				// for findfirst()
#include "parse.h"
#include "topiclog.h"
#include "fmtspec.h"
#include "docexpr.h"
#include "errmsg.h"
#include "cmdargs.h"
#include "extract.h"
#include "output.h"
#include "adoutput.h"
#include "version.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Autoduck names

#if defined(DUCK)
char szName[] = "Autoduck";
char szDefaultFormatFilename[] = "AUTODUCK.FMT";
#else
char szName[] = "Autoduck";
char szDefaultFormatFilename[] = "AUTODUCK.FMT";
#endif

// Global variables

RUNOPTIONS run;
FormatInfo fmt;
CTopicLog  log;

void GenerateTempFilename(CString &sName);
int GenerateOutputFilename(CString &sOutput, const char *szInput1, const char *szExt);
void GenerateOutput(CTopicLog &log, RUNOPTIONS &run, FormatInfo &fmt, CFile &fileTemp, CAdOutput &fileOutput);
int SeekTail(CFile &fileOutput, FormatInfo &fmt);
int PopulateLog(CTopicLog &log, const char *szFilename);


int main(int argc, char **argv)
{
TRY
{
    int nRet = 0;
    int n, i;
	const char *sz;
	
	CAdOutput fileOutput;
	CFile fileTemp;
	CFileException e;

    // Announce version info
    fprintf(stderr, "%s - Source Documentation Tool ", szName);
    fprintf(stderr, "Version %s.%s\n", VER_MAJOR, VER_MINOR);

    // If no arguments, print help
    if(argc == 1)
    {
        Usage(szName, szDefaultFormatFilename);
        return 0;
    }
    
    // Parse the command line

    nRet = SetRtOptions(run, fmt, argv, argc, szDefaultFormatFilename);
    if(nRet)
        return nRet;

	// Open format files.

	for(i = 0, n = run.asFmtFiles.GetSize(); i < n; i++)
    {
		sz = *run.asFmtFiles[i];

        nRet = GetFormatFile(sz, argv[0], run.sOutputType, fmt, run.nOptions.Verbose);
        if(nRet)
        {
            PrintError(sz, fmt.lErrLine, nRet);
			goto ExitError;
        }
    }

	// Make sure all's right with the format tags.

	if(!ValidateFormats(fmt))
	    return 1;

    // Open the log file, if specified.

    nRet = PopulateLog(log, run.sLogFileIn);
    if(nRet)
    {
        PrintError(run.sLogFileIn, NO_LINE, nRet);
		goto ExitError;
    }

	// Open the temp output file - stores the extracted comment text.

	GenerateTempFilename(run.sTempFile);
	if(!fileTemp.Open(run.sTempFile, CFile::modeCreate | 
						CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		PrintError(run.sTempFile, NO_LINE, e.m_cause);
		nRet = e.m_cause;
		goto ExitError;
	}

	// Open the final output file - do it now to make sure it isn't
	// already open or something.
	
	if(!run.nOptions.NoOutput)
	{
		// Open the output file, first generating a default name if
        // none provided

		if(run.sOutputFile.IsEmpty())
		{
			CFmtToken *pfmt = (CFmtToken *)fmt.token.Get(NULL);
            
            ASSERT(pfmt);
			ASSERT(run.asInputFiles.GetSize() > 0);

			nRet = GenerateOutputFilename(run.sOutputFile, *run.asInputFiles[0], pfmt->GetExtension());
			if(nRet)
			{
				PrintError(NULL, NO_LINE, nRet);
				goto ExitError;
			}

            fprintf(stdout, "Output file is %s.\n", (const char *)run.sOutputFile);
		}

	    int nOptions;
	    CFileStatus status;
	    if(run.nOptions.Concat && CFile::GetStatus(run.sOutputFile, status))
        {
            nOptions = CFile::modeReadWrite | CFile::typeBinary;
        }
        else
        {
            nOptions = CFile::modeWrite | CFile::modeCreate | CFile::typeBinary;
			run.nOptions.Concat = FALSE;
        }

        if(!fileOutput.Open(run.sOutputFile, nOptions, &e))
        {
            nRet = e.m_cause;
			PrintError(run.sOutputFile, NO_LINE, nRet);
            goto ExitError;
        }

        if(run.nOptions.Concat)
        {
            nRet = SeekTail(fileOutput, fmt);
			if(nRet)
			{
				PrintError(run.sOutputFile, NO_LINE, nRet);
				goto ExitError;
			}
        }
	}

    // Extract comment text

    ExtractTopics(fileTemp, run, log, fmt);

    // Sort da log.

    log.Sort(! run.nOptions.Unsorted);

	// Create the final output file
	
    if(!run.nOptions.NoOutput)
    {
        if(run.nOptions.Verbose)
            fprintf(stdout, "Writing topics...\n");
            
        // Sort log. Needs to be sorted to lookup information.

    	GenerateOutput(log, run, fmt, fileTemp, fileOutput);

	    // Close output file
        fileOutput.Close();
	    
	    // Generate HPJ file for WinHelp output
	    if(_strcmpi(run.sOutputType, "help") == 0)
        {
            if(run.nOptions.Verbose)
                fprintf(stdout, "Writing HPJ file...\n");
        
	        OutputWinHelpHPJFile(run.sOutputFile, szName);
        }
	}

	// Close (and delete) temp file

	fileTemp.Close();
    remove(run.sTempFile);

    // Generate log file - always sort.

    if(!run.sLogFileOut.IsEmpty())
    {
        if (run.nOptions.Verbose)
            fprintf(stdout, "Creating log file...\n");
        
        nRet = log.Print(run.sLogFileOut, run.nOptions.Concat);
		if(nRet)
			PrintError(run.sLogFileOut, NO_LINE, nRet);
    }
    
ExitError:

    // Free input files list.
        
    for(i = 0, n = run.asInputFiles.GetSize(); i < n; i++)
        delete run.asInputFiles[i];
    for(i = 0, n = run.asFmtFiles.GetSize(); i < n; i++)
        delete run.asFmtFiles[i];

    return nRet;
}
CATCH(CFileException, e)
{
    PrintError(NULL, NO_LINE, e->m_cause);
    return e->m_cause;
}
AND_CATCH(CMemoryException, e)
{
    PrintError(NULL, NO_LINE, errMemory);
    return errMemory;
}
END_CATCH
}


/*
@func Populates the topic log with topic names read from
the textual topic log provided on the command line.

@rdesc Zero if success or or an error code.
*/


int PopulateLog(
    CTopicLog &log,             //@parm Log to populate
    const char *szFilename)     //@parm Log filename
{
TRY
{
    if(*szFilename == '\0')
        return 0;

	char szInBuf[1024];
	CTopic *pNew;
	int nLen;

    CStdioFile fileLog(szFilename, CFile::typeText | CFile::modeRead);

	int nRet = 0;
	while(nRet == 0 && fileLog.ReadString(szInBuf, 1024))
	{
		if(*szInBuf && (*szInBuf != '\n'))
		{
			nLen = strlen(szInBuf);
			if(szInBuf[nLen-1] == '\n')
				szInBuf[nLen-1] = '\0';
			
			pNew = new CTopic;
            pNew->SetContext(szInBuf);
			
			log.Add( pNew, CTopicLog::AddOverwrite );
		}
	}
    fileLog.Close();

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
@func This function generates a filename for a temporary file, in the directory pointed
to by the TEMP environment variable. The filename consists of the letters
AD followed by the process Id of Autoduck. The filename, including directory,
is returned in the buffer pointed to by <p szName>.

@parm char *|szName | Buffer in which to print temp filename.
*/

void GenerateTempFilename(
	CString &sName)
{
	char szName[_MAX_PATH];
    char *szTmpDir = getenv("TEMP");
    int  nPid = _getpid();

    if(szTmpDir)
    {
        if(szTmpDir[strlen(szTmpDir)-1] == '\\')
            szTmpDir[strlen(szTmpDir)-1] = '\0';
        sprintf(szName, "%s/~AD%05d.tmp", szTmpDir, nPid);
    }
    else
    {
        sprintf(szName, "~AD%05d.tmp", nPid);
    }

	sName = szName;
}


/*
@func Generates a default output filename using the base filename of the first
input file in the list, and an extension drawn from the [token] section of the
format file.

@rdesc Zero if successful or errCantDeduceOutput.
*/

int GenerateOutputFilename(
	CString &sOutput,               //@parm <c CString> to receive output filename
	const char *szInput1,           //@parm Filename of first input file on list
	const char *szExt)              //@parm Default output extension
{
	char szFileBuf[_MAX_PATH+1];

#if defined(_DOS)
	_find_t fileInfo;
#else
	_finddata_t fileInfo;
	long hFile;
#endif

    strcpy(szFileBuf, szInput1);

#if defined(_DOS)
	if(_dos_findfirst(szFileBuf, _A_NORMAL, &fileInfo))
#else
	if((hFile = _findfirst(szFileBuf, &fileInfo)) == -1L)
#endif
    {
		return errCantDeduceOutput;
    }

    // Use name of first specified file

	_splitpath(fileInfo.name, NULL, NULL, szFileBuf, NULL);

	sOutput =  szFileBuf;
    sOutput += chPeriod;
    sOutput += szExt;

	return 0;
}

/*
@func Generates the output into the specified output file.
*/
void GenerateOutput(
    CTopicLog &log,         //@parm List of topics
    RUNOPTIONS &run,        //@parm Runtime options structure
    FormatInfo &fmt,        //@parm Format informatoin
    CFile &fileTemp,        //@parm Temp fiel containing extracted text
    CAdOutput &fileOutput)  //@parm Output file
{
TRY
{
    int 	 i;
    int 	 nRet;

    CFmtFile *pfmtFile = (CFmtFile *)fmt.file.Get(NULL);

    nRet = fileOutput.SetOutputBuffer(4096);
    if(nRet)
	{
        PrintError(run.sOutputFile, NO_LINE, nRet);
		return;
	}

    CCurTopicInfo cur(NULL, fileOutput, fmt, run, log);

    if(!run.nOptions.Concat)
        OutputFormatString(cur, pfmtFile, CFmtListFile::tagPre, NULL);

    int nTopics = log.GetRealCount();

    for(i = 0; i < nTopics; i++)
        OutputTopic(log.GetTopicOutputOrder(i), run, fmt, fileOutput, fileTemp, log);

    OutputFormatString(cur, pfmtFile, CFmtListFile::tagPost, NULL);

    if(run.nOptions.Verbose)
        fputc(chNewline, stdout);

    fileOutput.FlushOutputBuffer();
}
CATCH(CMemoryException, e)
{
    PrintError(NULL, NO_LINE, errMemory);
}
AND_CATCH(CFileException, e)
{
    PrintError(run.sOutputFile, NO_LINE, e->m_cause);
}
END_CATCH
}



/*
@func This function finds the end of the specified RTF file,
and positions the file pointer at the position of the last
closing brace (the RTF EOF).

@rdesc Returns 1 if successful or 0 if unsuccessful.

@comm This function resets the OPTION_CONCAT flag specified in
<p pnOptions> if the RTF file is zero length.
*/

int SeekTail(
    CFile &fileOut,       //@parm RTF file to append
	FormatInfo &fmt)
{
    UINT   nRead;
	DWORD  dwChars;
	DWORD  dwPos;
	DWORD  dwSeek;

	dwChars = fileOut.GetLength();
	
	if(0 == dwChars)
        return 0;

    dwPos = fileOut.Seek(0, CFile::end);

	// See if file format info in format file - we will get
	// the file footer information and try to find the footer.

	CFmtFile *pfmtFile = (CFmtFile *)fmt.file.Get(NULL);
	if(NULL == pfmtFile)
		return 0;

	CString &sFmt = pfmtFile->GetFmtString(CFmtListFile::tagPost);
	if(sFmt.IsEmpty())
		return 0;

	// Figure out how far back to start.
	
    dwSeek = sFmt.GetLength() + 80;
	
	if(dwSeek > dwChars)
		dwSeek = dwChars;

	fileOut.Seek(dwSeek * -1, CFile::end);

	// Read a chunk of text and find the last occurrence of
	// the closing string in the file.
	
	CString sBuf;
	char *szBuf = sBuf.GetBufferSetLength(dwSeek+1);
	
	nRead = fileOut.Read(szBuf, dwSeek);
	szBuf[nRead] = '\0';

    const char *szNext = szBuf;
	const char *szCur = NULL;

	while(szNext = strstr(szNext, sFmt))
	{
		szCur = szNext;
		szNext++;
	}

	sBuf.ReleaseBuffer();

	// Figure out if we found the end of the file, and
	// seek to that position.
	
	if(NULL == szCur)
        return errCantAppend;

    fileOut.Seek(-1 * (nRead - (szCur - szBuf)), CFile::end);

    fileOut.Flush();

	return 0;
}

