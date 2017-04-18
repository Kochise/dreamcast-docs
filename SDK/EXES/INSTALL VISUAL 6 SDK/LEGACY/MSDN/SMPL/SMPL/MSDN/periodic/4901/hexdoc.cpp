//***********************************************************************
//
//  HexDoc.cpp
//
//***********************************************************************

#include <afxwin.h>
#include "HexDoc.h"

IMPLEMENT_DYNCREATE (CHexDoc, CDocument)

CHexDoc::CHexDoc ()
{
    m_nDocLength = 0;
    m_pFileData = NULL;
}

void CHexDoc::DeleteContents ()
{
    if (m_pFileData != NULL) {
        delete[] m_pFileData;
        m_pFileData = NULL;
        m_nDocLength = 0;
    }
}

void CHexDoc::Serialize (CArchive& ar)
{
    if (ar.IsLoading ()) {
        CFile* pFile = ar.GetFile ();
        m_nDocLength = (UINT) pFile->GetLength ();

        // Allocate a buffer for the file data
        try {
            m_pFileData = new BYTE[m_nDocLength];
        }
        catch (CMemoryException* e) {
            m_nDocLength = 0;
            throw e;
        }

        // Read the file data into the buffer
        try {
            pFile->Read (m_pFileData, m_nDocLength);
        }
        catch (CFileException* e) {
            delete[] m_pFileData;
            m_pFileData = NULL;
            m_nDocLength = 0;
            throw e;
        }
    }
}

UINT CHexDoc::GetBytes (UINT nIndex, UINT nCount, PVOID pBuffer)
{
    if (nIndex >= m_nDocLength)
        return 0;

    UINT nLength = nCount;
    if ((nIndex + nCount) > m_nDocLength)
        nLength = m_nDocLength - nIndex;

    ::CopyMemory (pBuffer, m_pFileData + nIndex, nLength);
    return nLength;
}

UINT CHexDoc::GetDocumentLength ()
{
    return m_nDocLength;
}
