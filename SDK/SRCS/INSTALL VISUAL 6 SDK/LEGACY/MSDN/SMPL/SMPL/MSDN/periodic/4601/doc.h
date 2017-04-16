//////////////////
// Three documents: A base and two derived.

class CBaseDoc : public CDocument {
   DECLARE_DYNAMIC(CBaseDoc)
protected:
   CBaseDoc() { }
public:
   virtual void AddTitleToString(CString& msg) = 0;
};

class CDocA : public CBaseDoc {
   DECLARE_DYNCREATE(CDocA)
protected:
   CDocA() { }
public:
   virtual void AddTitleToString(CString& msg);
};

class CDocB : public CBaseDoc {
   DECLARE_DYNCREATE(CDocB)
protected:
   CDocB() { }
public:
   virtual void AddTitleToString(CString& msg);
};
