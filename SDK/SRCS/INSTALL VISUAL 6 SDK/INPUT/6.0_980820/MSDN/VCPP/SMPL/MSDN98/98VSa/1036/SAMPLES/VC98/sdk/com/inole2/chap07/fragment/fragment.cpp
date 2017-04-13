/*
 * FRAGMENT.CPP
 * Fragmented File Generator Chapter 7
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "fragment.h"


/*
 * WinMain
 *
 * Purpose:
 *  Main entry point of application.  This application does nothing
 *  more than pump out garbage into storage as a framented file test.
 *  It has no UI so does not process any messages.
 *
 *  The file created is always called FRAGMENT.BIN.
 */

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hInstPrev
    , LPSTR pszCmdLine, int nCmdShow)
    {
    CFragment  *pFrag;

    pFrag=new CFragment();

    if (NULL==pFrag)
        return -1;

    if (pFrag->Init())
        {
        if (pFrag->AllocCharArrays())
            {
            if (pFrag->CreateFragmentedFile())
                {
                pFrag->FreeSpaceInFile();
                pFrag->DefragmentFile();
                }
            }
        }

    delete pFrag;
    return 0;
    }




/*
 * CFragment::CFragment
 * CFragment::~CFragment
 *
 * Constructor and Destructor for this application.  The
 * constructor does not have any parameters.
 */

CFragment::CFragment(void)
    {
    m_fInitialized=FALSE;
    m_pIMalloc=NULL;
    m_pch=NULL;
    m_pszScratch=NULL;

    m_cch=256;
    m_cStreams=CSTREAMS;

    lstrcpy(m_szFile, TEXT("FRAGMENT.BIN"));
    m_hCur=NULL;

    return;
    }


CFragment::~CFragment(void)
    {
    if (NULL!=m_hCur)
        SetCursor(m_hCur);

    if (NULL!=m_pIMalloc)
        {
        if (NULL!=m_pch)
            m_pIMalloc->Free(m_pch);

        if (NULL!=m_pszScratch)
            m_pIMalloc->Free(m_pszScratch);

        m_pIMalloc->Release();
        }

    if (m_fInitialized)
        CoUninitialize();

    return;
    }




/*
 * CFragment::Init
 *
 * Purpose:
 *  Calls CoInitialize and CoGetMalloc saving the task allocator.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if initialization worked, FALSE otherwise.
 */

BOOL CFragment::Init(void)
    {
    CHECKVER_COM;

    if (FAILED(CoInitialize(NULL)))
        return FALSE;

    m_fInitialized=TRUE;

    if (FAILED(CoGetMalloc(MEMCTX_TASK, &m_pIMalloc)))
        return FALSE;

    m_pszScratch=(TCHAR *)m_pIMalloc->Alloc(1024*sizeof(TCHAR));

    if (NULL==m_pszScratch)
        return FALSE;

    m_hCur=SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_WAIT)));
    return TRUE;
    }



/*
 * CFragmet::AllocCharArrays
 *
 * Purpose:
 *  Allocates CSTREAMS * 256 characters and initializes each 256
 *  charaters with 'A', 'B', etc.  (ANSI characters, not UNICODE).
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the memory was allocated and initialized
 *                  otherwise FALSE.
 */

BOOL CFragment::AllocCharArrays(void)
    {
    char *      pchT;
    UINT        i, j;

    if (NULL==m_pIMalloc)
        return FALSE;

    m_pch=(char *)m_pIMalloc->Alloc(m_cch*m_cStreams);

    if (NULL==m_pch)
        return FALSE;

    pchT=m_pch;

    //Initialize Character Arrays
    for (i=0; i < m_cStreams; i++)
        {
        char    ch=i+'A';

        for (j=0; j < m_cch; j++)
            *pchT++=ch;
        }

    return TRUE;
    }




/*
 * CFragment::CreateFragmentedFile
 *
 * Purpose:
 *  Creates a file with numerous streams that we can fragment.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the file was created, FALSE otherwise.
 */

BOOL CFragment::CreateFragmentedFile(void)
    {
    HRESULT     hr;
    IStorage   *pIStorage;
    IStream    *rgpIStream[CSTREAMS];
    UINT        i, j;

    //Create the file to build
    hr=StgCreateDocfile(m_szFile, STGM_DIRECT | STGM_READWRITE
        | STGM_SHARE_EXCLUSIVE | STGM_CREATE, 0, &pIStorage);

    if (FAILED(hr))
        return FALSE;

    //Create streams in this file.
    for (i=0; i < m_cStreams; i++)
        StreamCreate(pIStorage, i, &rgpIStream[i]);

    /*
     * Now fill "Stream A" with A's, Stream B with B's, etc.,
     * doing it m_cch characters at a time, a total of 20 times for
     * each stream.  This will allow us to examine the binary
     * format of the file before and after defragmentation.
     *
     * This will create a number of streams that are internally
     * fragmented in the file.
     *
     * Some streams may be invalid, but checks for NULL below
     * avoid problems in such cases.
     */

    for (j=0; j < 20; j++)
        {
        for (i=0; i < m_cStreams; i++)
            {
            if (NULL!=rgpIStream[i])
                rgpIStream[i]->Write((m_pch+(m_cch*i)), m_cch, NULL);
            }
        }

    //Close all the streams
    for (i=0; i < m_cStreams; i++)
        {
        if (NULL!=rgpIStream[i])
            rgpIStream[i]->Release();
        }

    //Close the IStorage to close the file.
    pIStorage->Release();

    Message(TEXT("%s created."));
    return TRUE;
    }







/*
 * CFragment::FreeSpaceInFile
 *
 * Purpose:
 *  Deletes some of the streams in the previously created file.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CFragment::FreeSpaceInFile(void)
    {
    HRESULT     hr;
    IStorage   *pIStorage;

    //Reopen the storage
    hr=StgOpenStorage(m_szFile, NULL, STGM_DIRECT | STGM_READWRITE
        | STGM_SHARE_EXCLUSIVE, NULL, 0, &pIStorage);

    if (SUCCEEDED(hr))
        {
        /*
         * Now create some extra space in the file by destroying
         * streams C E G H J M N T X.
         */
        pIStorage->DestroyElement(OLETEXT("Stream C"));
        pIStorage->DestroyElement(OLETEXT("Stream E"));
        pIStorage->DestroyElement(OLETEXT("Stream G"));
        pIStorage->DestroyElement(OLETEXT("Stream H"));
        pIStorage->DestroyElement(OLETEXT("Stream J"));
        pIStorage->DestroyElement(OLETEXT("Stream M"));
        pIStorage->DestroyElement(OLETEXT("Stream N"));
        pIStorage->DestroyElement(OLETEXT("Stream T"));
        pIStorage->DestroyElement(OLETEXT("Stream X"));

        /*
         * The file size will not have changed here, but there
         * will be unused space.
         */

        pIStorage->Release();
        Message(TEXT("Space has been freed in %s."));
        }
    else
        Message(TEXT("Could not reopen %s."));

    return;
    }





/*
 * CFragment::DefragmentFile
 *
 * Purpose:
 *  Does an IStorage::CopyTo from the existing file to a temp
 *  file then copies that temp file as binary back to the source
 *  file.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CFragment::DefragmentFile(void)
    {
    HRESULT     hr;
    IStorage   *pIStorageOld;
    IStorage   *pIStorageNew;
    STATSTG     st;
   #ifndef WIN32
    OFSTRUCT    of;
   #endif
    TCHAR       szTemp[MAX_PATH];

    /*
     * Create a temporary file.  We don't use DELETEONRELEASE
     * in case we have to save it when copying over the old
     * file fails.
     */
    hr=StgCreateDocfile(NULL, STGM_CREATE | STGM_READWRITE
        | STGM_DIRECT | STGM_SHARE_EXCLUSIVE, 0, &pIStorageNew);

    if (FAILED(hr))
        {
        Message(TEXT("Failed to create temp file to copy %s."));
        return;
        }

    //Open the existing file as read-only
    hr=StgOpenStorage(m_szFile, NULL, STGM_DIRECT | STGM_READ
        | STGM_SHARE_DENY_WRITE, NULL, 0, &pIStorageOld);

    if (FAILED(hr))
        {
        pIStorageNew->Release();
        Message(TEXT("Failed to open %s for CopyTo."));
        return;
        }

    /*
     * Compress with CopyTo.  Since the temp is opened in
     * direct mode, changes are immediate.
     */
    hr=pIStorageOld->CopyTo(NULL, NULL, NULL, pIStorageNew);
    pIStorageOld->Release();

    if (FAILED(hr))
        {
        pIStorageNew->Release();
        Message(TEXT("IStorage::CopyTo from %s failed."));
        return;
        }

    //Get the name of the temp file.
    pIStorageNew->Stat(&st, 0);
    pIStorageNew->Release();

    //Delete the old file before copying back to insure truncation
   #ifdef WIN32
    DeleteFile(m_szFile);

   #ifdef WIN32ANSI
    WideCharToMultiByte(CP_ACP, 0, st.pwcsName, -1, szTemp
        , MAX_PATH, NULL, NULL);
   #else
    lstrcpy(szTemp, st.pwcsName);
   #endif

    MoveFile(szTemp, m_szFile);
   #else
    OpenFile(m_szFile, &of, OF_DELETE);
    MyMoveFile(st.pwcsName, m_szFile);
   #endif

    Message(TEXT("Defragementation complete on %s."));
    return;
    }




/*
 * CFragment::StreamCreate
 *
 * Purpose:
 *  Creates a stream with a given identifier in a given IStorage.
 *
 * Parameters:
 *  pIStorage       IStorage * in which to create the stream
 *  i               UINT ID of the stream
 *  ppIStream       IStream ** in which to return the stream.
 *
 * Return Value:
 *  None
 */

void CFragment::StreamCreate(IStorage *pIStorage, UINT i
    , IStream ** ppIStream)
    {
    OLECHAR  szName[40];

    //Name is "Stream A", "Stream B", etc.
   #ifdef WIN32ANSI
    char        szTemp[40];

    wsprintf(szTemp, "Stream %c", i+'A');
    MultiByteToWideChar(CP_ACP, 0, szTemp, -1, szName, 40);
   #else
    wsprintf(szName, TEXT("Stream %c"), i+'A');
   #endif

    pIStorage->CreateStream(szName, STGM_DIRECT
        | STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE
        , 0, 0, ppIStream);

    return;
    }



/*
 * CFragment::Message
 *
 * Purpose:
 *  Outputs a message with the filename included.
 *
 * Parameters:
 *  pszFmt          LPTSTR to a wsprintf format string.
 *
 * Return Value:
 *  None
 */

void CFragment::Message(LPTSTR pszFmt)
    {
    wsprintf(m_pszScratch, pszFmt, m_szFile);
    MessageBox(NULL, m_pszScratch, TEXT("Fragmenter"), MB_OK);
    return;
    }





#ifndef WIN32
/*
 * CFragment::MyMoveFile
 *
 * Purpose:
 *  Low-level MoveFile function for 16-bit Windows that lack
 *  the MoveFile[Ex] API.
 *
 * Parameters:
 *  pszSrc          char * of the source filename,
 *  pszDst          char * of the destination filename,
 *
 * Return Value:
 *  None
 */

void CFragment::MyMoveFile(char *pszSrc, char *pszDst)
    {
    HFILE       hFile1, hFile2;
    ULONG       cbCopy;
    const UINT  cbBlock=4096;
    LPBYTE      pb;
    OFSTRUCT    of;

    //Do a binary copy between files.
    hFile1=_lopen(pszSrc, READ | OF_SHARE_EXCLUSIVE);

    if (HFILE_ERROR==hFile1)
        return;

    //Recreate this file before copying.
    hFile2=_lcreat(m_szFile, 0);

    if (HFILE_ERROR==hFile2)
        {
        _lclose(hFile1);
        return;
        }

    //Seek to end of source file to find length
    cbCopy=_llseek(hFile1, 0, 2);
    _llseek(hFile1, 0, 0);

    pb=(LPBYTE)m_pIMalloc->Alloc(cbBlock);

    if (NULL!=pb)
        {
        //Copy in 4K increments
        while (cbCopy >= (ULONG)cbBlock)
            {
            _lread(hFile1,  pb, cbBlock);
            _lwrite(hFile2, pb, cbBlock);
            cbCopy-=4096;
            }

        _lread(hFile1,  pb, (UINT)cbCopy);
        _lwrite(hFile2, pb, (UINT)cbCopy);
        m_pIMalloc->Free(pb);
        }

    _lclose(hFile2);
    _lclose(hFile1);

    //Delete the temp file
    OpenFile(pszSrc, &of, OF_DELETE);
    return;
    }
#endif
