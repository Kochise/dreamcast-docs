/////////////////////////////////////////////////////////////////////////////
// cmdproc.h
// Copyright (C) 1996 Microsoft Corp.
//
//  more flexible replacement for mfc CCommandLineInfo

/////////////////////////////////////////////////////////////////////////////
// CCommandLineInfo

#ifndef CMDPROC_H
#define CMDPROC_H


class CCommandLineProc : public CObject 
{
public:
    // process the command line for switch based arguments
    BOOLEAN ProcessCommandLine(int iSC, int &argc, _TCHAR **argv);
protected:
    typedef void (CCommandLineProc::*PMFNCmdProc)(CString &csArg);
    class CArgProcTable {
    public:
        int m_iIDS;  // string resource of command switch
        PMFNCmdProc m_Cmd;    // argument processing function
    };
    friend CArgProcTable;
    static CArgProcTable acapArgs[];
    // remove any desired positional arguments
    virtual BOOLEAN GetPositionalArgs(int &argc, _TCHAR **argv);
    
    // this function deletes the argument at iPos by copy the remaining
    // elements of argv 1 to the left
    inline void CCommandLineProc::DeleteArg(int iPos, int &argc, _TCHAR **argv)
    {
        for (int k = iPos + 1; k < argc; k++) {
	        argv[k - 1] = argv[k];
        }
        argc--;
    }

};


#endif
// end of file - cmdproc.h
