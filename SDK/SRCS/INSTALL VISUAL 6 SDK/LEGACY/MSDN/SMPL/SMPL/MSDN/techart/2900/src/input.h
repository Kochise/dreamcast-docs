#define MAXLINEBUFSIZE 1023
#define MAXFMTTOKENS   10

// *********************************************************

//@doc FILE ADINPUT

//@class Autoduck input file. Provides some nice input features on
// top of the MFC <c CStdioFile> class.

class CAdInput : public CStdioFile
{
public:
	long m_lCurLine;            //@cmember Current line number

	char m_szLineBuf[MAXLINEBUFSIZE+1]; //@cmember Input text buffer 
	                                    // for one line of fmt file.

	char *m_szCur;	//@cmember Last character parsed in <md .m_szLineBuf>.

	//@cmember Constructs the input state class.

	CAdInput(void);

	//@cmember Retrieves a line of input from the format file.
	int GetLine(void);

	//@cmember Tells whether we are at end of file or not.
	BOOL EndOfFile(void) { return m_nAdState.EndOfFile; }

    //@cmember Return current position in the input stream.
	long GetCurPos(void) { return Seek(0, current); }

    //@cmember Indicates to reuse the input line on the next call
    // to GetLine rather than actually reading a line from input.

    void SetReuse(BOOL b = TRUE) { m_nAdState.Reuse = b; }

    //@cmember Indicates to append next line.

    void SetAppend(BOOL b = TRUE) { m_nAdState.Append = b; }

    //@cmember Resets the file state variables.

    void ResetState(void);

    //@cmember State variables.
    struct ADSTATE
    {
        unsigned Reuse : 1;
        unsigned Append : 1;
		unsigned EndOfFile : 1;
    } m_nAdState;
};


