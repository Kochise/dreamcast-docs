/*
 * FRAGMENT.H
 * Fragmented File Generator Chapter 7
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _FRAGMENT_H_
#define _FRAGMENT_H_


#define INC_OLE2
#define CHAPTER7
#include <inole.h>
#include <string.h>

#define CSTREAMS    26
#define CCHPATHMAX  256


class CFragment
    {
    private:
        BOOL        m_fInitialized;         //CoInitilize?
        IMalloc    *m_pIMalloc;             //Task allocator
        char       *m_pch;                  //Char array (8 bits)
        TCHAR      *m_pszScratch;           //Scratch space

        UINT        m_cch;                  //Stream size
        UINT        m_cStreams;             //Stream count
        TCHAR       m_szFile[CCHPATHMAX];   //File in use

        HCURSOR     m_hCur;                 //Saved cursor


    public:
        CFragment::CFragment(void);
        CFragment::~CFragment(void);

        BOOL        Init(void);
        BOOL        AllocCharArrays(void);
        BOOL        CreateFragmentedFile(void);
        void        FreeSpaceInFile(void);
        void        DefragmentFile(void);

    private:
        void        StreamCreate(IStorage *, UINT, IStream **);
        void        Message(LPTSTR);

       #ifndef WIN32
        //Substitute for Win32 MoveFile under Win16
        void        MyMoveFile(char *, char *);
       #endif
    };

#endif //_FRAGMENT_H_
