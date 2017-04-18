#define VALIDHLSTR(x)  if (HIWORD(x) == -1) { MessageBox(NULL,"VBCreateTempHlstr failed -- Contact Support." , "CRITICAL ERROR",MB_ICONSTOP);return NULL;}
