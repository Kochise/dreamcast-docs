#define SHORT signed short
#define BITVECTOR sizeof(int)


#ifdef CLASSES

/* This branch is only compiled in the class DLL and is invisible to the application.
   All the data that needs to be seen be the using App must be put into the
   other branch... */

#define DllExport __declspec( dllexport )


HANDLE hMemPool;

class DllExport matrix
{ private:
  LPVOID lpMemory;
  BOOL iStatus;
  int iSquareVal;
  public:
   int iRows,iColumns;
  matrix(int iR, int iC);
  ~matrix();
  void SetElement(int iR, int iC,SHORT iElement);
  SHORT GetElement(int iR, int iC);
  matrix MultiplyRowByInt(int iR, SHORT iMult);
  matrix MultiplyColByInt(int iC, SHORT iMult);
  void ReplaceRowByScalar(int iR, matrix mScalar);
  void ReplaceColByScalar(int iC, matrix mScalar);
  void AddScalarToRow(int iR, matrix mtScalar, SHORT iFactor);
  void AddScalarToColumn(int iC, matrix mtScalar, SHORT iFactor);
  matrix *FindNullSpace();
  matrix *Copy();
};




#else   /* ifdef CLASSES */

#define DllImport __declspec( dllimport )

class DllImport matrix
{ private:
  LPVOID lpMemory;
  BOOL iStatus;
  int iSquareVal;
  public:
   int iRows,iColumns;
  matrix(int iR, int iC);
  ~matrix();
  void SetElement(int iR, int iC,SHORT iElement);
  SHORT GetElement(int iR, int iC);
  matrix MultiplyRowByInt(int iR, SHORT iMult);
  matrix MultiplyColByInt(int iC, SHORT iMult);
  void ReplaceRowByScalar(int iR, matrix mScalar);
  void ReplaceColByScalar(int iC, matrix mScalar);
  void AddScalarToRow(int iR, matrix mtScalar, SHORT iFactor);
  void AddScalarToColumn(int iC, matrix mtScalar, SHORT iFactor);
  matrix *FindNullSpace();
  matrix *Copy();
};

#endif



