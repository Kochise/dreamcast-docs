class CAmbientProperty :
   public CObject
{
   DECLARE_SERIAL( CAmbientProperty );

public:
   CAmbientProperty();
   CAmbientProperty( DISPID dispid, LPCTSTR pszName, const VARIANT& var,
	  int vti, BOOL tStock = FALSE );

   void Enable( BOOL tEnabled );
   DISPID GetID() const;
   CString GetName() const;
   const COleVariant& GetValue() const;
   int GetVTI() const;
   BOOL IsEnabled() const;
   BOOL IsStock() const;
   void SetValue( const VARIANT& varValue, int vti = -1 );

   void Serialize( CArchive& ar );

protected:
   DISPID m_dispid;
   CString m_strName;
   COleVariant m_varValue;
   int m_vti;
   BOOL m_tEnabled;
   BOOL m_tStock;
};
