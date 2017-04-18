/************************************************************************/
/*									*/
/*	Header File:	Trnsdt.hÅiDOS LIB + Windows DLL/Win16 & Win32)	*/
/*									*/
/*	(C) Copyright Microsoft Corporation 1993-1996			*/
/*									*/
/************************************************************************/
#if defined(WIN32)
#pragma	pack(4)
#endif
/****************************************************************************
	Definitions for MS-DOS
*****************************************************************************/
#if (!defined(WINDOWS) && !defined(WIN32))
#define	FALSE		0
#define	TRUE		1
#define FAR		_far
#define VOID		void
typedef	unsigned char	BYTE;
typedef BYTE FAR*	LPBYTE;
typedef	unsigned short	WORD;
typedef	unsigned long	DWORD;
#endif

/****************************************************************************
	PASSSTRUCT Structure
*****************************************************************************/
typedef	struct	tagPassParm  {
	WORD	parm_length;		/* Parameter Length(input)	*/
	WORD	exit_code;		/* Exit Code(output)		*/
	WORD	in_length;		/* Input Buffer Length(input)	*/
	LPBYTE	in_addr;		/* Input Buffer Address(input)	*/
	WORD	out_length;		/* Output Buffer Length(in/out)	*/
	LPBYTE	out_addr;		/* Output Buffer Address(input)	*/
	WORD	trns_id;		/* Conversion ID(input)		*/
	WORD	in_page;		/* Input Code Page(input)	*/
	WORD	out_page;		/* Output Code Page	 	*/
	WORD	option;			/* Option(at calling)		*/
}	PASSSTRUCT;

/****************************************************************************
	Function declarations
*****************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif
#if (!defined(WINDOWS) && !defined(WIN32))
WORD TrnsDt(PASSSTRUCT * PassParm);
#else
WORD WINAPI TrnsDt(PASSSTRUCT far* PassParm);
#endif
#if defined(__cplusplus)
}
#endif

/****************************************************************************
	Retuen Codes
*****************************************************************************/
#define	NO_ERR			0
#define	ERR_FILE_NOT_FOUND	2
#define	ERR_INVALID_PARAMETER	87
#define	ERR_BUFFER_OVERFLOW	111
#define	ERR_MEMORY_ALLOCATE	150

#if defined(WIN32)
#pragma	pack()
#endif
