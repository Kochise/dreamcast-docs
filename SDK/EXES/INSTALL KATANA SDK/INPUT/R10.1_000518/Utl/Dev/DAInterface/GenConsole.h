/*=====================[ SALSA Console API Prototypes ]==================*
 |
 | SALSA Library - Copyright Cross Products Ltd. 1998
 |
 *------------------------------[ VERSION ]------------------------------*
 |
 | $Workfile: GenConsole.h $
 | $Author: Gellison $
 | $Revision: 17 $
 | $Modtime: 17/03/00 8:00a $
 | $Date: 17/03/00 8:52a $
 | $Archive: /library/DALI/SOURCE/USERDIAL/GenConsole.h $
 |
 *-------------------------------[ NOTES ]-------------------------------*
 | 
 |  Description: contains Generic Console API prototypes for the
 |               Sega Advanced Library for SCSI Access (SALSA).
 |
 |  LIB: salsa.lib
 |
 |************************************************************************
 |These enum and structure definitions *MUST* match the firmware *exactly*
 |************************************************************************
 |
 *----------------------------[ DEFINITIONS ]----------------------------*
 |
 *----------------------------[ DECLARATIONS ]---------------------------*
 |
 *=======================================================================*/

#ifndef GenConsole_h
#define GenConsole_h

enum ENDIAN
{
	ENDIAN_LITTLE,
	ENDIAN_BIG
};

class CSalsaConsoleStatus 
{
	BYTE					m_byEndianFlag;
	BOOL					m_fValid;

public:
	CSalsaConsoleStatus()
	{
		InitialiseEndian();
	}

	void InitialiseEndian(void)
	{
		m_byEndianFlag = 0;
		m_fValid = FALSE;
	}

	void SetEndianFlag(BYTE byEndian)
	{
		m_byEndianFlag = byEndian;
		m_fValid = TRUE;
	}

	BOOL IsValid(void) const {return m_fValid ;} 

	ENDIAN GetTargetEndian(void) {return (ENDIAN)(((m_byEndianFlag & 0x40) >> 6) ^ 0x01);};
	ENDIAN GetMemoryProtocolEndian(void) {return (ENDIAN)(((m_byEndianFlag & 0x02) >> 1) ^ 0x01);};
	ENDIAN GetContextProtocolEndian(void) {return (ENDIAN)(((m_byEndianFlag & 0x04) >> 2) ^ 0x01);};
	ENDIAN GetTransportProtocolEndian(void) {return (ENDIAN)(((m_byEndianFlag & 0x08) >> 3) ^ 0x01);};
};

// *********************************************************************
// Define the command protocol structures, ensuring correct byte packing
// *********************************************************************

// *********************************************************************
// Define the command protocol structures, ensuring correct byte packing
// *********************************************************************
#if defined(__MWERKS__)
#pragma pack(push, 1)
#else
#pragma pack(push, console, 1)
#endif

struct CONSOLEINQUIRY
{
	DWORD	dwPCounter;
	BYTE	bySigNum;
	BYTE	bySigCat;
	WORD	wSigID;

	BYTE	tsf0Flag	: 1;
	BYTE	tsf1Flag	: 1;
	BYTE	tsf2Flag	: 1;
	BYTE	tsf3Flag	: 1;
	BYTE	tsf4Flag	: 1;
	BYTE	tsf5Flag	: 1;
	BYTE	tsf6Flag	: 1;
	BYTE	tsf7Flag	: 1;

	BYTE	thf0Flag	: 1;
	BYTE	thf1Flag	: 1;
	BYTE	thf2Flag	: 1;
	BYTE	thf3Flag	: 1;
	BYTE	thf4Flag	: 1;
	BYTE	thf5Flag	: 1;
	BYTE	thf6Flag	: 1;
	BYTE	thf7Flag	: 1;

	BYTE	dasf0Flag	: 1;
	BYTE	dasf1Flag	: 1;
	BYTE	dasf2Flag	: 1;
	BYTE	dasf3Flag	: 1;
	BYTE	dasf4Flag	: 1;
	BYTE	dasf5Flag	: 1;
	BYTE	dasf6Flag	: 1;
	BYTE	dasf7Flag	: 1;

	BYTE	dahf0Flag	: 1;
	BYTE	dahf1Flag	: 1;
	BYTE	dahf2Flag	: 1;
	BYTE	dahf3Flag	: 1;
	BYTE	dahf4Flag	: 1;
	BYTE	dahf5Flag	: 1;
	BYTE	dahf6Flag	: 1;
	BYTE	dahf7Flag	: 1;

	CONSOLEINQUIRY()
	{
		Initialise();
	}

	VOID Initialise()
	{
		memset(this, 0, sizeof(CONSOLEINQUIRY));
	}
};


struct EXECPARAMS
{
	DWORD	dwStartAddr;

	EXECPARAMS(VOID)
	{
		Initialise();
	}

	VOID Initialise(VOID)
	{
		dwStartAddr = 0;
	}
};

struct MEMPARAMS
{
	BYTE	byZPad;
	BYTE	byElementSize;
	DWORD	dwAddress;
	DWORD	dwElementCount;

	MEMPARAMS(VOID)
	{
		Initialise();
	}

	VOID Initialise(VOID)
	{
		memset((VOID*)this, 0, sizeof(MEMPARAMS));
	}

	int Size() { return(10); }

};

struct CONTEXTPARAMS
{
	WORD	wZPad;
	WORD	wMode;
	WORD	wLength;

	CONTEXTPARAMS(VOID)
	{
		Initialise();
	}

	VOID Initialise(VOID)
	{
		memset((VOID*)this, 0, sizeof(CONTEXTPARAMS));	
	}
};

struct STUBCONFIG
{
	BYTE	ss8Flag		: 1;
	BYTE	ss9Flag		: 1;
	BYTE	ss10Flag	: 1;
	BYTE	ss11Flag	: 1;
	BYTE	ss12Flag	: 1;
	BYTE	ss13Flag	: 1;
	BYTE	ss14Flag	: 1;
	BYTE	ss15Flag	: 1;

	BYTE	ss0Flag		: 1;
	BYTE	ss1Flag		: 1;
	BYTE	ss2Flag		: 1;
	BYTE	ss3Flag		: 1;
	BYTE	ss4Flag		: 1;
	BYTE	ss5Flag		: 1;
	BYTE	ss6Flag		: 1;
	BYTE	ss7Flag		: 1;

	STUBCONFIG(VOID)
	{
		Initialise();
	}

	VOID Initialise(VOID)
	{
		memset(this, 0, sizeof(STUBCONFIG));
	}

	int Size() const { return(2); }

};

struct READSTUBCONFIG
{
	enum UPROCFAMILY
	{
		UPROCFAMILY_UNDEF,		// Reserved
		UPROCFAMILY_HI_SH
	};

	enum UPROCTYPE
	{
		UPROCTYPE_UNDEF,		// Reserved
		UPROCTYPE_SH1,
		UPROCTYPE_SH2,
		UPROCTYPE_SH3,
		UPROCTYPE_SH3E,
		UPROCTYPE_SH4,
		UPROCTYPE_SH4EVA_7091,	// Sega variant 	
			UPROCTYPE_SH4EVA = UPROCTYPE_SH4EVA_7091,	// For Backwards Compatibility 
		UPROCTYPE_SH4EVA_7750,	// Standard hitachi eva variant
		UPROCTYPE_SH2E,			// this is out of sequence for backwards compatibility (7055)
		UPROCTYPE_SH7729,		//	SH3 with DSP
		UPROCTYPE_SH7612,		//	SH2 with DSP
		UPROCTYPE_SH7709A,		//	SH7729 with DSP disabled
		UPROCTYPE_SH7410,		//	SH2 with DSP
		UPROCTYPE_SH4EVA_7751,	// Standard hitachi eva variant with PCI
	};

	BYTE	byEndian;
	BYTE	uProcFamily;
	BYTE	uProcType;
	
	BYTE	byVersion;
	WORD	wRevision;
	CHAR	cRevision;

	DWORD	dwCheckSum;

	STUBCONFIG
			ConfigFlags;

	READSTUBCONFIG(VOID)
	{
		Initialise();
	}

	VOID Initialise(VOID)
	{
		byEndian = 0;

		uProcFamily	= UPROCFAMILY_UNDEF;
		uProcType	= UPROCTYPE_UNDEF;
		
		byVersion	= 0;
		wRevision	= 0;
		cRevision	= 0;

		ConfigFlags.Initialise();
	}

	int Size() { return(12); }

};

struct CONSOLEIDDATA
{
	CHAR	acVendor[8];
	CHAR	acConsole[16];

	CONSOLEIDDATA(VOID)
	{
		Initialise();
	}

	VOID Initialise(VOID)
	{
		memset(this, 0, sizeof(CONSOLEIDDATA));
	}
};

struct PROFREQPARAMS
{
	BYTE	byRes[2];
	BYTE	byProfileType;
	
	BYTE	pdr0 : 1;
	BYTE	pdr1 : 1;
	BYTE	pdr2 : 1;
	BYTE	pdr3 : 1;
	BYTE	pdr4 : 1;
	BYTE	pdr5 : 1;
	BYTE	pdr6 : 1;
	BYTE	pdr7 : 1;

	PROFREQPARAMS(VOID)
	{
		Initialise();
	}

	VOID Initialise(VOID)
	{
		memset(this, 0, sizeof(PROFREQPARAMS));
	}


	int
	Size()
	{
		return(4);
	}
};

struct PROFREQDATA
{
	BYTE	Counter1[6];
	BYTE	Counter2[6];

	DWORD	dwPC;
	DWORD	dwSP;

	BYTE	Res[2];

	BYTE	NumSets : 4;
	BYTE	ResBits : 3;
	BYTE	Mode	: 1;

	BYTE	byTRMCR;

	DWORD	dwSrce1;
	DWORD	dwDest1;

	DWORD	dwSrce2;
	DWORD	dwDest2;

	DWORD	dwSrce3;
	DWORD	dwDest3;

	DWORD	dwSrce4;
	DWORD	dwDest4;

	DWORD	dwSrce5;
	DWORD	dwDest5;

	DWORD	dwSrce6;
	DWORD	dwDest6;

	DWORD	dwSrce7;
	DWORD	dwDest7;

	DWORD	dwSrce8;
	DWORD	dwDest8;

	enum MODE
	{
		USERMODE,
		PRIVMODE
	};

	PROFREQDATA(VOID)
	{
		Initialise();
	}

	VOID Initialise(VOID)
	{
		memset(this, 0, sizeof(PROFREQDATA));
	}

	int	Size()	{ return(88); }

};

struct SFLASH_RES_CMD
{
	BYTE DataBuffer[4];				// setup the data for the command packet

	SFLASH_RES_CMD()
	{
		Initialise();
	}

	void Initialise(void)
	{
		DataBuffer[0] = 0;
		DataBuffer[1] = 0;
		DataBuffer[2] = 0;
		DataBuffer[3] = 0;
	}
};


struct SSALSARegsSH4EVA
{
   DWORD r0;
   DWORD r1;
   DWORD r2;
   DWORD r3;
   DWORD r4;
   DWORD r5;
   DWORD r6;
   DWORD r7;
   DWORD r8;
   DWORD r9;
   DWORD r10;
   DWORD r11;
   DWORD r12;
   DWORD r13;
   DWORD r14;
   DWORD r15;

   DWORD pc;
   DWORD pr;
   DWORD gbr;
   DWORD vbr;
   DWORD mach;
   DWORD macl;
   DWORD sr;

   DWORD r0_bank1;
   DWORD r1_bank1;
   DWORD r2_bank1;
   DWORD r3_bank1;
   DWORD r4_bank1;
   DWORD r5_bank1;
   DWORD r6_bank1;
   DWORD r7_bank1;

   DWORD ssr;
   DWORD spc;
   DWORD sgr;
   DWORD dbr;
};

struct SSALSARegsSH4EVA_FPU
{
   DWORD fpr0;
   DWORD fpr1;
   DWORD fpr2;
   DWORD fpr3;
   DWORD fpr4;
   DWORD fpr5;
   DWORD fpr6;
   DWORD fpr7;
   DWORD fpr8;
   DWORD fpr9;
   DWORD fpr10;
   DWORD fpr11;
   DWORD fpr12;
   DWORD fpr13;
   DWORD fpr14;
   DWORD fpr15;

   DWORD fpul;
   DWORD fpscr;

   DWORD fpr0_bank1;
   DWORD fpr1_bank1;
   DWORD fpr2_bank1;
   DWORD fpr3_bank1;
   DWORD fpr4_bank1;
   DWORD fpr5_bank1;
   DWORD fpr6_bank1;
   DWORD fpr7_bank1;
   DWORD fpr8_bank1;
   DWORD fpr9_bank1;
   DWORD fpr10_bank1;
   DWORD fpr11_bank1;
   DWORD fpr12_bank1;
   DWORD fpr13_bank1;
   DWORD fpr14_bank1;
   DWORD fpr15_bank1;
};

struct SSALSARegsSH4EVA_MMU
{
	DWORD PTEH;
	DWORD PTEL;
	DWORD TTB;
	DWORD TEA;
	DWORD MMUCR;
	DWORD QACR0;
	DWORD QACR1;
	DWORD CCR;
	DWORD queue0[8];
	DWORD queue1[8];
};

struct SSALSAUBCRegsSH4EVA
{
	// the member ordering has been modified to provide suitable boundary alignment
	DWORD BARA;
	BYTE  BAMRA;
	BYTE  BASRA;
	WORD  BBRA;
	DWORD BARB;
	BYTE  BAMRB;
	BYTE  BASRB;
	WORD  BBRB;
	DWORD BDRB;
	DWORD BDMRB;
	WORD  BRCR;

	BYTE  Padding[2];
};

struct SSALSAHBCRegsSH4EVA
{
	DWORD BARS;
	BYTE  BAMRS;
	BYTE  BASRS;
	WORD  BBRS;

	DWORD BART;
	BYTE  BAMRT;
	BYTE  BASRT;
	WORD  BBRT;

	DWORD BARU;
	BYTE  BAMRU;
	BYTE  BASRU;
	WORD  BBRU;

	DWORD BARV;
	BYTE  BAMRV;
	BYTE  BASRV;
	WORD  BBRV;
	DWORD BDRV;
	DWORD BDMRV;

	WORD  BRCR;
	WORD  BRCRS;
	DWORD IOBAR;
	BYTE  ASEEVT;

	BYTE  Padding[3];
};

#if defined(__MWERKS__)
#pragma pack(pop)
#else
#pragma pack(pop, console)
#endif

// ********************************************************************************
// Finished defining the command protocol structures, ensuring correct byte packing
// ********************************************************************************


// ********************************************************************************
// Finished defining the command protocol structures, ensuring correct byte packing
// ********************************************************************************

class CGenConsole
{
public:
	typedef CONSOLEINQUIRY	INQUIRY;
	typedef READSTUBCONFIG	READCONFIG;
	typedef STUBCONFIG		WRITECONFIG;
	typedef PROFREQDATA		PROFILEDATA;
	typedef SFLASH_RES_CMD	FLASH_RES_CMD;

	struct CONSOLEID
	{
		CHAR szVendor[8+1];
		CHAR szConsole[16+1];

		CONSOLEID(VOID)
		{
			Initialise();
		}

		VOID Initialise(VOID)
		{
			memset(szVendor, '\0', sizeof(szVendor));
			memset(szConsole, '\0', sizeof(szConsole));
		}
	};


	enum PROFILE_REQUEST_TYPE
	{
		PROFILE_REQUEST_GENERAL_PACKET			= 0,
		PROFILE_REQUEST_START_PACKET			= 1,
		PROFILE_REQUEST_STOP_PACKET				= 2,
		PROFILE_REQUEST_END_OF_PROFILE_PACKET	= 3
	};

	enum ELEMENTSIZE
	{
		ELEMENTSIZE_BYTE	= 1,
		ELEMENTSIZE_WORD	= 2,
		ELEMENTSIZE_LONG	= 4
	};

	//I believe the stubs rely upon the values of the context enum so
	//DO NOT CHANGE THIS ORDER.  Would be better if we hard coded the enum - gw
	enum CONTEXTMODE
	{
		CONTEXTMODE_GENERAL,
		CONTEXTMODE_FPU,
		CONTEXTMODE_UBC,
		CONTEXTMODE_HBC,
		CONTEXTMODE_MMU,
		CONTEXTMODE_DSP,
		CONTEXTMODE_ALL_NORMAL			// Special optimised case for Read SH4 General + FPU + MMU in one operation
	};
	
	// SigNum informs of the general state of the debug stub
	enum SIGNAL
	{
		SIGNAL_RUNNING,		// not in debug stub therefore executing game code
		SIGNAL_STOPPED,		// in debug stub as result of a Suspend() console command
		SIGNAL_HALTED,		// in debug stub as result of CPU exception *or* console command issued
							// N.B. Need to check SigCat and SigID to differentiate

		SIGNAL_RESET,		// Initial condition after CConsole::ResetAndDebug() or manual reset
							// or power cycle causes stub (re)load when DA in CPU debug mode

		SIGNAL_SAFE,		// indicates a CConsole::MakeSafe() command was issued
							
		SIGNAL_FAIL,		// Failed to load/reset Debug Stub
		SIGNAL_NODEBUG,		// Running without Console debug facilities
		SIGNAL_IN_RESET,	// The target is probably powered down
		SIGNAL_FLASH_PROG	// programming flash
	};

	// the SigID value is CPU specific and matches the 
	// manufacturer's Exception Code for the given category.

	// Hence, 'vector base' & 'offset' are encoded into 'category', 
	// then 'exception code' is the category specific ID

	enum SIGCAT
	{
		SIGCAT_UNDEFINED,
		SIGCAT_ASE,				// Currently defined for use on Hitachi SH4_EVA chip
		SIGCAT_GENERAL,			// General exception	
		SIGCAT_INTERRUPT,		// Interrupt
		SIGCAT_CHNLBLOCK,		// Blocked channel (such as Fserver) operation in progress
		SIGCAT_REPORTEVENT,		// Check SIGID for event being reported
		SIGCAT_PROFILEBUFF,		// Statistical sampling and trace profiling buffer signal (see SIGID)
		SIGCAT_RESET_EXPECTED,
		SIGCAT_RESET_UNEXPECTED,
		SIGCAT_ERASING_FLASH,
		SIGCAT_PROGRAMMING_FLASH,
		SIGCAT_ERROR_FLASH
	};

	enum SIGID_REPORTEVENT
	{
		SIGID_MANUALRESET = 0x01
	};

	enum SIGID_PROFILEBUFF
	{
		SIGID_PROFILEBUFF_FULL  = 0x0F
	};

	enum PROFREQ
	{
		PROFREQ_GENTTP = 0x01,
		PROFREQ_GENSSP = 0x02,
	};
};

#endif
