#include <windows.h>

/*
#define OLDSIG          0x5a4d
#define NEWSIG          0x454e
#define SINGLEDATA      0x0001
#define MULTIPLEDATA    0x0002
#define PMODEONLY       0x0008
#define LIBRARY         0x8000
#define FASTLOAD        0x0008

*/

typedef struct
{
    BYTE    bFlags;
    WORD    wSegOffset;
} FENTRY, *PFENTRY;

typedef struct
{
    BYTE    bFlags;
    WORD    wINT3F;
    BYTE    bSegNumber;
    WORD    wSegOffset;
} MENTRY, *PMENTRY;

#define EXPORTED    0x01
#define SHAREDDATA  0x02


typedef struct
{
    WORD    wSector;
    WORD    wLength;
    WORD    wFlags;
    WORD    wMinAlloc;
} SEGENTRY, *PSEGENTRY;

#define F_DATASEG       0x0001
#define F_MOVEABLE      0x0010
#define F_SHAREABLE     0x0020
#define F_PRELOAD       0x0040
#define F_DISCARDABLE   0x1000



// The RTYPE and RINFO structures are never actually used
// they are just defined for use in the sizeof() macro when
// reading the info off the disk.  The actual data is read
// into the RESTYPE and RESINFO structures that contain these
// structures with some extra information declared at the end.

typedef struct
{
    WORD    wType;
    WORD    wCount;
    LONG    lReserved;
} RTYPE;

typedef struct
{
    WORD    wOffset;
    WORD    wLength;
    WORD    wFlags;
    WORD    wID;
    LONG    lReserved;
} RINFO;

// RESINFO2 is the same structure as RINFO with one modification.
// RESINFO2 structure uses the lower 16 bits of the lReserved from
// RINFO structure to point to a string that represents
// the resource name.  This can be done since the lReserved piece
// of this structure is used for Run-time data.  This use of the
// lReserved portion is done so that all resources of a certain
// type can be read into one allocated array, thus using 1 ALLOC
// and 1 read.  This saves memory and makes the loading faster
// so it's worth the slight confusion that might be introduced.
/*
typedef struct
{
    WORD     wOffset;
    WORD     wLength;
    WORD     wFlags;
    WORD     wID;
    PSTR     pResourceName;
    WORD     wReserved;
} RESINFO2, *PRESINFO;

extern struct tgRESTYPE;
typedef struct tgRESTYPE *PRESTYPE;

typedef struct tgRESTYPE
{
    WORD        wType;              // Resource type
    WORD        wCount;             // Specifies ResInfoArray size
    LONG        lReserved;          // Reserved for runtime use
    PSTR        pResourceType;      // Points to custom type name
    PRESINFO    pResInfoArray;      // First entry in array
    PRESTYPE    pNext;              // Next Resource type
} RESTYPE;

#define GROUP_CURSOR    12
#define GROUP_ICON      14
#define NAMETABLE       15



typedef struct tgNAME
{
    struct tgNAME  *pNext;
    WORD            wOrdinal;
    char            szName[1];      // Text goes here at allocation time
} NAME, *PNAME;

*/


// the following data is extracted from the samples on the PE format

#define SIZE_OF_NT_SIGNATURE	sizeof (DWORD)

/* global macros to define header offsets into file */
/* offset to PE file signature				       */
#define NTSIGNATURE(a) ((LPVOID)((BYTE *)a		     +	\
			((PIMAGE_DOS_HEADER)a)->e_lfanew))

/* DOS header identifies the NT PEFile signature dword
   the PEFILE header exists just after that dword	       */
#define PEFHDROFFSET(a) ((LPVOID)((BYTE *)a		     +	\
			 ((PIMAGE_DOS_HEADER)a)->e_lfanew    +	\
			 SIZE_OF_NT_SIGNATURE))

/* PE optional header is immediately after PEFile header       */
#define OPTHDROFFSET(a) ((LPVOID)((BYTE *)a		     +	\
			 ((PIMAGE_DOS_HEADER)a)->e_lfanew    +	\
			 SIZE_OF_NT_SIGNATURE		     +	\
			 sizeof (IMAGE_FILE_HEADER)))

/* section headers are immediately after PE optional header    */
#define SECHDROFFSET(a) ((LPVOID)((BYTE *)a		     +	\
			 ((PIMAGE_DOS_HEADER)a)->e_lfanew    +	\
			 SIZE_OF_NT_SIGNATURE		     +	\
			 sizeof (IMAGE_FILE_HEADER)	     +	\
			 sizeof (IMAGE_OPTIONAL_HEADER)))



#ifdef DOSHEADERS   // to make sure this code is declared only once


TAGGEDLISTSTRUCT tlDosHeader =
{ 21,
   {{ "DOS Header",0 },
    { "",0},
    { "FileSignature: %#x", sizeof(WORD) },         
    { "Bytes on last page: %#x", sizeof(WORD) },          
    { "Size of file in 512 byte pages (inc header): %#x", sizeof(WORD) },
    { "Relocation Table Items: %#x", sizeof(WORD) },  
    { "Header Size in paragraphs: %#x", sizeof(WORD) },
    { "Paragraphs needed above program: %#x", sizeof(WORD) },              
    { "Paragraphs wanted above program: %#x", sizeof(WORD) },          
    { "Stack displacement: %#x", sizeof(WORD) }, 
    { "Initial SP value: %#x", sizeof(WORD) },                    
    { "CheckSum: %#x", sizeof(WORD) },
    { "Initial IP value: %#x", sizeof(WORD) },
    { "Code displacement: %#x", sizeof(WORD) },      
    { "First relocation item @ offset %#x",sizeof(WORD) },   
    { "Overlay number: %#x", sizeof(WORD) },
	{ "<reserved space>",4*sizeof(WORD) },
	{ "OEM identifier: %#x",sizeof(WORD) },
	{ "OEM information: %#x",sizeof(WORD) },
    { "<reserved space>",10*sizeof(WORD) },
    { "offset of new exe header: %#8lx", sizeof(int)}
   }
};          


#endif

#ifdef NEHEADERS

 
TAGGEDLISTSTRUCT tlNEHeader =
{ 33,
   {{ "New executable header",0 },
    { "",0 },
    { "NewSignature: %#x", sizeof(WORD) },         
    { "Linker version: %#x",sizeof(BYTE) },
    { "Linker Revision: %#x",sizeof(BYTE) },
    { "Entry table offset: %#x",sizeof(WORD) },
    { "Entry table size: %#x",sizeof(WORD) },
    { "check sum: %#8lx",sizeof(int) },
    { "flags: %#x",sizeof(WORD) },
    { "Automatic data in segment %#x",sizeof(WORD) },
    { "Initial heap size: %#x",sizeof(WORD) },
    { "Initial stack size: %#x",sizeof(WORD) },
    { "Initial IP value: %#x",sizeof(WORD) },
    { "Initial CS value: %#x",sizeof(WORD) },
    { "Initial SP value: %#x", sizeof(WORD) },
	{ "Initial SS value: %#x", sizeof(WORD) },
    { "Entries in segment table: %#x",sizeof(WORD) },
    { "Module reference table entries: %#x",sizeof(WORD) },
    { "Non-resident name table size: %#x",sizeof(WORD) },
    { "Segment table offset: %#x",sizeof(WORD) },
    { "Resource table offset: %#x",sizeof(WORD) },
    { "Resident name table offset: %#x",sizeof(WORD) },
    { "Module reference table offset: %#x",sizeof(WORD) },
    { "imort name table offset: %#x",sizeof(WORD) },
    { "Non-resident name table offset: %#8lx",sizeof(int) },
    { "Moveable entries in entry table: %#x",sizeof(WORD) },
    { "Segment alignment shift count: %#x",sizeof(WORD) },
    { "Resource segments: %#x",sizeof(WORD) },
    { "loader flags: %#x",sizeof(WORD) },
    { "Offset of fast load area: %#x",sizeof(WORD) },
    { "Size of fast load area: %#x", sizeof(WORD) },
    { "<reserved>",sizeof(WORD) },
    { "Expected Windows version number: %#x",sizeof(WORD) }
  } 
};


#endif

#ifdef PEHEADERS

TAGGEDLISTSTRUCT tlPEHeader =
{ 8,
   {{ "PE Header",0 },
    { "",0},
    { "Machine: %#x", sizeof(USHORT) },         
    { "Number of sections: %#x", sizeof(USHORT) },          
    { "TimeDateStamp: %#lx", sizeof(ULONG) },
    { "Symbol Table offset: %#lx", sizeof(ULONG) },  
    { "Symbol count: %#x", sizeof(ULONG) },
    { "optional header size: %#x", sizeof(USHORT) },              
   }
};

TAGGEDLISTSTRUCT tlPEOptionalHeader =
{ 31,
  {{"",0},
   { "Magic number: %#x", sizeof(WORD) },    
   { "Linker version: %d", sizeof(BYTE) },    
   { "Linker revision: %d", sizeof(BYTE) },    
   { "Size of code: %#lx", sizeof(DWORD) },   
   { "Initialized data: %#lx", sizeof(DWORD) },   
   { "Uninitialized data: %#lx", sizeof(DWORD) },   
   { "Entry point: %#lx", sizeof(DWORD) },   
   { "Code based at: %#lx", sizeof(DWORD) },   
   { "Data based at: %#lx", sizeof(DWORD) },   

    //
    // NT additional fields.
    //

   {"Image based at: %#x", sizeof(DWORD) },   
   { "Section alignment: %#x", sizeof(DWORD) },   
   { "File Alignment: %#x", sizeof(DWORD) },   
   { "OS version: %d", sizeof(WORD) },    
   { "OS revision: %d", sizeof(WORD) },    
   { "Image version: %d", sizeof(WORD) },    
   { "Image revision: %d", sizeof(WORD) },    
   { "Subsystem version: %d", sizeof(WORD) },    
   { "Subsystem revision: %d", sizeof(WORD) },    
   { "<reserved>", sizeof(DWORD) },   
   { "Image size: %#lx", sizeof(DWORD) },   
   { "Size of headers: %#lx", sizeof(DWORD) },   
   { "Checksum: %#lx", sizeof(DWORD) },   
   { "Subsystem: %#x", sizeof(WORD) },    // needs to be laid out here...
   { "DLL characteristics: %#x", sizeof(WORD) },    // same thing
   { "Reserved stack memory: %#lx", sizeof(DWORD) },   
   { "Committed stack memory: %#lx", sizeof(DWORD) },   
   { "Reserved heap memory: %#lx", sizeof(DWORD) },   
   { "Committed heap memory: %#lx", sizeof(DWORD) },   
   { "Loader flags: %#lx", sizeof(DWORD) },   	   // same here
   { "Number of Rva and sizes: %#lx", sizeof(DWORD) }
    }
};   ;
//    IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];


ANYELEMENT alPEChars[] =
       {{"reloctables", "no reloctables",0x0001},  // Relocation info stripped from file.
        {"unresolved externals", "executable file",0x0002},  // File is executable  (i.e. no unresolved externel references).
        {"line numbers","no line numbers",0x0004},  // Line nunbers stripped from file.
        {"local symbols","no local symbols",0x0008},  // Local symbols stripped from file.
        {"low bytes in regular order","low bytes are reversed",0x0080},  // Bytes of machine word are reversed.
        {"no 32-bit words","machine has 32-bit words",0x0100},  // 32 bit word machine.
        {"debug info present","no debug info",0x0200},  
        {"user-mode file","system file",0x1000},  // System File.
        {"EXE (not a DLL)","DLL",0x2000},  // File is a DLL.
        {"high bytes in regular order","high bytes are reversed",0x8000},  // Bytes of machine word are reversed.
       };
       
CHAR *DirectoryString[16] =
       {"Export Directory","Import Directory","Resource Directory","Exception Directory",
        "Security Directory","Base relocation Table","Debug Directory","Copyright String",  
		"Global pointer","TLS directory","Load Configuration Directory","not in use",
		"not in use","not in use","not in use","not in use"};

/*TAGGEDELEMENT csSectionHeaders[9] =
      {{IMAGE_DIRECTORY_ENTRY_EXPORT},            
       {IMAGE_DIRECTORY_ENTRY_IMPORT},         
       {IMAGE_DIRECTORY_ENTRY_RESOURCE},       
       {IMAGE_DIRECTORY_ENTRY_EXCEPTION},      
       {IMAGE_DIRECTORY_ENTRY_SECURITY},       
       {IMAGE_DIRECTORY_ENTRY_BASERELOC},      
       {IMAGE_DIRECTORY_ENTRY_DEBUG},         
       {IMAGE_DIRECTORY_ENTRY_COPYRIGHT},      
       {IMAGE_DIRECTORY_ENTRY_GLOBALPTR},      
       {IMAGE_DIRECTORY_ENTRY_TLS },           
       {IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG}
      };   
*/

CHAR *csSectionHeaders[9] =
       {".text",".bss",".data",".rdata",".rsrc",".edata",".idata",".debug",".pdata"};
#endif
