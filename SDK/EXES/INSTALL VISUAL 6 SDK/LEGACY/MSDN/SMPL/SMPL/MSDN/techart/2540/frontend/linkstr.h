
class linkstr
{ private:
  CString *csData;
  linkstr *Next;
  public:
  linkstr(LPSTR);
  void Append(linkstr *lpNew);
  ~linkstr();
  linkstr *Succ() { return Next; };
  CString *GetData() { return csData; }; 
};


