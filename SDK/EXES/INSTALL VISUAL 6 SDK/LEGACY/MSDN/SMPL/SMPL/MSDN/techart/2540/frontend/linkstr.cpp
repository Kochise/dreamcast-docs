//#include <windows.h>
#include "stdafx.h"
#include "linkstr.h"


linkstr::linkstr(LPSTR lpArg)
{ Next = (linkstr *)0;
  csData= new CString(lpArg);
};

linkstr::~linkstr()
{ delete(csData);
};

void linkstr::Append(linkstr *lpNew)
{ if (Next != (linkstr *)0) Next->Append(lpNew); else Next = lpNew;
};
