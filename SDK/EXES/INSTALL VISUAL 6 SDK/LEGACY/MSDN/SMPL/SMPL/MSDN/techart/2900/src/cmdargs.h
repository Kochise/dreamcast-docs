//@struct RUNOPTIONS | Contains user-specified runtime options.

typedef struct _runoptions {
    struct {
        unsigned Verbose : 1;           //@field Verbose status messages
        unsigned NoEmptyWarnings : 1;   //@field Suppress warnings about empty fields
        unsigned Unsorted : 1;          //@field Generate unsorted output.
        unsigned NoOutput : 1;          //@field Don't generate any output (log file only).
        unsigned Concat : 1;            //@field Concatenate output
    } nOptions;

    int nExampleTabSize;                //@field Tab size (in spaces)

    CString sDocID;						//@field Extraction expression
    CString sOutputType;                //@field Output type (doc, help, etc.)
    CString sOutputFile;                //@field Output file (rtf output)
	CString sTempFile;					//@field Temp filename (extracted text)
    CString sLogFileIn;                 //@field Log file (input)
    CString sLogFileOut;                //@field Log file (output)

	CStrArray asFmtFiles;				//@field List of format files
    CStrArray asInputFiles;				//@field List of input files

    CExprToken exprExtract;             //@field Extraction expression

} RUNOPTIONS;
typedef RUNOPTIONS * PRUNOPTIONS;

int SetRtOptions(RUNOPTIONS &run, FormatInfo &fmt, char **argv, int argc, const char *szDefaultFmtFilename);
void Usage(const char *szExe, const char *szFmt);
#ifdef _DEBUG
void DumpOptions(RUNOPTIONS &run);
#endif
