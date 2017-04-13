/*+==========================================================================
  File:      PAPFILE.H

  Summary:   Include file for the application's paper data file related
             classes. Declares the CPapFile C++ class. A CPapFile is a C++
             object that encapsulates load and save operations on a
             structured storage compound file.  CPapFile knows about an
             underlying server-based COM object, COPaper, that manages the
             actual paper drawing data and uses an IStorage provided
             to store and retrieve that paper drawing data.

             For a comprehensive tutorial code tour of PAPFILE's contents
             and offerings see the tutorial STOCLIEN.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the PAPFILE source code.

  Classes:   CPapFile.

  Origin:    6-13-96: atrent - Created for STOCLIEN Code Sample.

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/

#if !defined(PAPFILE_H)
#define PAPFILE_H

#if defined(__cplusplus)


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CPapFile

  Summary:  Class to encapsulate the paper data compound file.

  Methods:  CPapFile
              Constructor.
            ~CPapFile
              Destructor.
            HRESULT Init(TCHAR* pszFileName, IPaper* pIPaper);
              Initialize CPapFile.
            HRESULT Load(SHORT nLockKey, TCHAR* pszFileName);
              Load default paper data file or a specified paper data file.
            HRESULT Save(SHORT nLockKey, TCHAR* pszFileName);
              Save drawing data to the current paper data file.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CPapFile
{
  public:
    CPapFile(void);
    ~CPapFile(void);
    HRESULT Init(TCHAR* pszFileName, IPaper* pIPaper);
    HRESULT Load(SHORT nLockKey, TCHAR* pszFileName);
    HRESULT Save(SHORT nLockKey, TCHAR* pszFileName);

  private:
    TCHAR          m_szCurFileName[MAX_PATH];
    IPaper*        m_pIPaper;
    IStorage*      m_pIStorage;
};


#endif // __cplusplus

#endif
