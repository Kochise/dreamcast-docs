//***************************************************************************
//
//  LifeDoc.h
//
//***************************************************************************

class CLifeDoc : public CDocument
{
    DECLARE_DYNCREATE (CLifeDoc)

private:
    int         m_cx;
    int         m_cy;
    BOOL        m_bOpenEdge;
    CByteArray  m_byGrid;
    CByteArray  m_byBuffer;

    void    SetBackgroundCell (int, int, BOOL);

public:
    CLifeDoc ();
    virtual BOOL OnNewDocument ();
    virtual void DeleteContents ();
    virtual void Serialize (CArchive&);

    CSize   GetGridSize ();
    BOOL    GetCell (int, int);
    BOOL    ToggleCell (int, int);
    int     Evolve ();  

protected:
    afx_msg void OnOptionsStep ();
    afx_msg void OnOptionsOpenBoundary ();
    afx_msg void OnOptionsClosedBoundary ();
    afx_msg void OnUpdateOptionsOpenBoundaryUI (CCmdUI*);
    afx_msg void OnUpdateOptionsClosedBoundaryUI (CCmdUI*);

    DECLARE_MESSAGE_MAP ()
};
