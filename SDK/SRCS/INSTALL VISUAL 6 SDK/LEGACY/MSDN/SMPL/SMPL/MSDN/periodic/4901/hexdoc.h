//***********************************************************************
//
//  HexDoc.h
//
//***********************************************************************

class CHexDoc : public CDocument
{
    DECLARE_DYNCREATE (CHexDoc)

private:
    UINT m_nDocLength;
    BYTE* m_pFileData;

public:
    CHexDoc ();
    virtual void DeleteContents ();
    virtual void Serialize (CArchive&);
    UINT GetBytes (UINT, UINT, PVOID);
    UINT GetDocumentLength ();
};
