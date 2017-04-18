// headstr.h - contains the structures for the header declarations.

typedef struct 
{ char *cIfNotPresent;
  char *cIfPresent;
  int iTag;
} ANYELEMENT, *PANYELEMENT;

typedef struct
{ ANYELEMENT aeItems[];
} ANYLIST, *PANYLIST;

typedef struct
{ char *tlString;
  unsigned int iLength;
} TAGGEDELEMENT, *PTAGGEDELEMENT;


typedef struct 
{ int iNumberofEntries;
  TAGGEDELEMENT teItem[];
} TAGGEDLISTSTRUCT, *PTAGGEDLISTSTRUCT;

typedef struct
{ BYTE bSize;
  char cName[];
} CHARARRAYLEADBYITSBYTELENGTH, *PCHARARRAYLEADBYITSBYTELENGTH;  


typedef union 
{ int iItem;
  char *pszItem;
} UNVAL, *PUNVAL;

typedef struct 
{ int iRowCount;
  int iColumnCount;
  UNVAL items[];
} ITEMLIST, *PITEMLIST;

typedef struct 
{ char *pszHeading;
  char *pszTemplate;
} HEADERTEMPLATE, *PHEADERTEMPLATE;

typedef struct
{
	WORD	flag;
	PSTR	name;
} WORD_FLAG_DESCRIPTIONS;

typedef struct
{
	DWORD	flag;
	PSTR	name;
} DWORD_FLAG_DESCRIPTIONS;

