# Microsoft Visual C++ generated build script - Do not modify

PROJ = SQLEYE
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
ORIGIN = MSVCNT
ORIGIN_VER = 1.00
PROJPATH = C:\SQL\OPENDS\SAMPLES\SQLEYE\ 
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = SQLCBS.C
FIRSTCPP = 
RC = rc
CFLAGS_D_WEXE32 = /nologo /W3 /Zi /YX /D "_DEBUG" /D "_X86_" /D "_WINDOWS" /FR /MT /Fd"SQLEYE.PDB"        /Fp"SQLEYE.PCH"
CFLAGS_R_WEXE32 = /nologo /W3 /YX /D "NDEBUG" /D "_X86_" /D "_WINDOWS" /FR /MT /Fp"SQLEYE.PCH"
LFLAGS_D_WEXE32 = /NOLOGO /DEBUG /DEBUGTYPE:cv /SUBSYSTEM:windows user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib olecli32.lib olesvr32.lib shell32.lib
LFLAGS_R_WEXE32 = /NOLOGO /SUBSYSTEM:windows user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib olecli32.lib olesvr32.lib shell32.lib
LFLAGS_D_LIB32 = /NOLOGO
LFLAGS_R_LIB32 = /NOLOGO
LIBS_D_WEXE32 = 
LIBS_R_WEXE32 = 
RCFLAGS32 = 
D_RCDEFINES32 = -d_DEBUG
R_RCDEFINES32 = -dNDEBUG
OBJS_EXT = 
LIBS_EXT = ..\..\..\DBLIB\LIB\NTWDBLIB.LIB ..\..\LIB\OPENDSNT.LIB 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE32)
LFLAGS = $(LFLAGS_D_WEXE32)
LIBS = $(LIBS_D_WEXE32)
LFLAGS_LIB=$(LFLAGS_D_LIB32)
MAPFILE_OPTION = 
RCDEFINES = $(D_RCDEFINES32)
!else
CFLAGS = $(CFLAGS_R_WEXE32)
LFLAGS = $(LFLAGS_R_WEXE32)
LIBS = $(LIBS_R_WEXE32)
MAPFILE_OPTION = 
LFLAGS_LIB=$(LFLAGS_R_LIB32)
RCDEFINES = $(R_RCDEFINES32)
!endif
SBRS = SQLCBS.SBR \
		SQLEYE.SBR \
		INITSERV.SBR \
		INITREMO.SBR \
		LANGEXEC.SBR \
		RPCEXEC.SBR \
		HRESULTS.SBR \
		EXITREMO.SBR \
		ROWSTUFF.SBR \
		MNGESERV.SBR \
		STATS.SBR \
		SENDMSG.SBR


NTWDBLIB_DEP = 

OPENDSNT_DEP = 

SQLCBS_DEP = 

SQLEYE_DEP =  \
	c:\sql\dblib\include\sqlfront.h \
	c:\sql\dblib\include\sqldb.h \
	c:\sql\opends\include\srv.h \
	c:\sql\opends\include\srvmisc.h \
	c:\sql\opends\include\srvdbtyp.h \
	c:\sql\opends\include\srvstruc.h \
	c:\sql\opends\include\srvtok.h \
	c:\sql\opends\include\srvconst.h \
	c:\sql\opends\include\srvtypes.h \
	c:\sql\opends\include\srvapi.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqleye.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\initserv.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqlcbs.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\dialogs.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\mngeserv.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sendmsg.h


SQLEYE_RCDEP =  \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqleye.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\dialogs.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sleep.ico \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqleye.ico \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\in.ico \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\rpc.ico \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\out.ico \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\waiting.ico \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\ghost.ico \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\connect.ico \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\stats.ico


INITSERV_DEP =  \
	c:\sql\dblib\include\sqlfront.h \
	c:\sql\dblib\include\sqldb.h \
	c:\sql\opends\include\srv.h \
	c:\sql\opends\include\srvmisc.h \
	c:\sql\opends\include\srvdbtyp.h \
	c:\sql\opends\include\srvstruc.h \
	c:\sql\opends\include\srvtok.h \
	c:\sql\opends\include\srvconst.h \
	c:\sql\opends\include\srvtypes.h \
	c:\sql\opends\include\srvapi.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqleye.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\initserv.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\rpcexec.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\exitremo.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\langexec.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\rowstuff.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\initremo.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\mngeserv.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\stats.h


INITREMO_DEP =  \
	c:\sql\dblib\include\sqlfront.h \
	c:\sql\dblib\include\sqldb.h \
	c:\sql\opends\include\srv.h \
	c:\sql\opends\include\srvmisc.h \
	c:\sql\opends\include\srvdbtyp.h \
	c:\sql\opends\include\srvstruc.h \
	c:\sql\opends\include\srvtok.h \
	c:\sql\opends\include\srvconst.h \
	c:\sql\opends\include\srvtypes.h \
	c:\sql\opends\include\srvapi.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqleye.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\initremo.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqlcbs.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\rowstuff.h


LANGEXEC_DEP =  \
	c:\sql\dblib\include\sqlfront.h \
	c:\sql\dblib\include\sqldb.h \
	c:\sql\opends\include\srv.h \
	c:\sql\opends\include\srvmisc.h \
	c:\sql\opends\include\srvdbtyp.h \
	c:\sql\opends\include\srvstruc.h \
	c:\sql\opends\include\srvtok.h \
	c:\sql\opends\include\srvconst.h \
	c:\sql\opends\include\srvtypes.h \
	c:\sql\opends\include\srvapi.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqleye.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\langexec.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\hresults.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\rowstuff.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\mngeserv.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqlcbs.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\stats.h


RPCEXEC_DEP =  \
	c:\sql\dblib\include\sqlfront.h \
	c:\sql\dblib\include\sqldb.h \
	c:\sql\opends\include\srv.h \
	c:\sql\opends\include\srvmisc.h \
	c:\sql\opends\include\srvdbtyp.h \
	c:\sql\opends\include\srvstruc.h \
	c:\sql\opends\include\srvtok.h \
	c:\sql\opends\include\srvconst.h \
	c:\sql\opends\include\srvtypes.h \
	c:\sql\opends\include\srvapi.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqleye.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\rpcexec.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\hresults.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\rowstuff.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqlcbs.h


HRESULTS_DEP =  \
	c:\sql\dblib\include\sqlfront.h \
	c:\sql\dblib\include\sqldb.h \
	c:\sql\opends\include\srv.h \
	c:\sql\opends\include\srvmisc.h \
	c:\sql\opends\include\srvdbtyp.h \
	c:\sql\opends\include\srvstruc.h \
	c:\sql\opends\include\srvtok.h \
	c:\sql\opends\include\srvconst.h \
	c:\sql\opends\include\srvtypes.h \
	c:\sql\opends\include\srvapi.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqleye.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\hresults.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\rowstuff.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqlcbs.h


EXITREMO_DEP =  \
	c:\sql\dblib\include\sqlfront.h \
	c:\sql\dblib\include\sqldb.h \
	c:\sql\opends\include\srv.h \
	c:\sql\opends\include\srvmisc.h \
	c:\sql\opends\include\srvdbtyp.h \
	c:\sql\opends\include\srvstruc.h \
	c:\sql\opends\include\srvtok.h \
	c:\sql\opends\include\srvconst.h \
	c:\sql\opends\include\srvtypes.h \
	c:\sql\opends\include\srvapi.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqleye.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\exitremo.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\rowstuff.h


ROWSTUFF_DEP =  \
	c:\sql\dblib\include\sqlfront.h \
	c:\sql\dblib\include\sqldb.h \
	c:\sql\opends\include\srv.h \
	c:\sql\opends\include\srvmisc.h \
	c:\sql\opends\include\srvdbtyp.h \
	c:\sql\opends\include\srvstruc.h \
	c:\sql\opends\include\srvtok.h \
	c:\sql\opends\include\srvconst.h \
	c:\sql\opends\include\srvtypes.h \
	c:\sql\opends\include\srvapi.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqleye.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\rowstuff.h


MNGESERV_DEP =  \
	c:\sql\dblib\include\sqlfront.h \
	c:\sql\opends\include\srv.h \
	c:\sql\opends\include\srvmisc.h \
	c:\sql\opends\include\srvdbtyp.h \
	c:\sql\opends\include\srvstruc.h \
	c:\sql\opends\include\srvtok.h \
	c:\sql\opends\include\srvconst.h \
	c:\sql\opends\include\srvtypes.h \
	c:\sql\opends\include\srvapi.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\mngeserv.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\initremo.h


STATS_DEP =  \
	c:\sql\dblib\include\sqlfront.h \
	c:\sql\dblib\include\sqldb.h \
	c:\sql\opends\include\srv.h \
	c:\sql\opends\include\srvmisc.h \
	c:\sql\opends\include\srvdbtyp.h \
	c:\sql\opends\include\srvstruc.h \
	c:\sql\opends\include\srvtok.h \
	c:\sql\opends\include\srvconst.h \
	c:\sql\opends\include\srvtypes.h \
	c:\sql\opends\include\srvapi.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqleye.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\stats.h


SENDMSG_DEP =  \
	c:\sql\dblib\include\sqlfront.h \
	c:\sql\dblib\include\sqldb.h \
	c:\sql\opends\include\srv.h \
	c:\sql\opends\include\srvmisc.h \
	c:\sql\opends\include\srvdbtyp.h \
	c:\sql\opends\include\srvstruc.h \
	c:\sql\opends\include\srvtok.h \
	c:\sql\opends\include\srvconst.h \
	c:\sql\opends\include\srvtypes.h \
	c:\sql\opends\include\srvapi.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\sqleye.h \
	C:\SQL\OPENDS\SAMPLES\SQLEYE\dialogs.h


all:	$(PROJ).EXE $(PROJ).BSC

SQLCBS.OBJ:	SQLCBS.C $(SQLCBS_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c SQLCBS.C

SQLEYE.OBJ:	SQLEYE.C $(SQLEYE_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c SQLEYE.C

SQLEYE.RES:	SQLEYE.RC $(SQLEYE_RCDEP)
	$(RC) $(RCFLAGS32) $(RCDEFINES) -r SQLEYE.RC

INITSERV.OBJ:	INITSERV.C $(INITSERV_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c INITSERV.C

INITREMO.OBJ:	INITREMO.C $(INITREMO_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c INITREMO.C

LANGEXEC.OBJ:	LANGEXEC.C $(LANGEXEC_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c LANGEXEC.C

RPCEXEC.OBJ:	RPCEXEC.C $(RPCEXEC_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c RPCEXEC.C

HRESULTS.OBJ:	HRESULTS.C $(HRESULTS_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c HRESULTS.C

EXITREMO.OBJ:	EXITREMO.C $(EXITREMO_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c EXITREMO.C

ROWSTUFF.OBJ:	ROWSTUFF.C $(ROWSTUFF_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ROWSTUFF.C

MNGESERV.OBJ:	MNGESERV.C $(MNGESERV_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c MNGESERV.C

STATS.OBJ:	STATS.C $(STATS_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c STATS.C

SENDMSG.OBJ:	SENDMSG.C $(SENDMSG_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c SENDMSG.C


$(PROJ).EXE:	SQLEYE.RES

$(PROJ).EXE:	SQLCBS.OBJ SQLEYE.OBJ INITSERV.OBJ INITREMO.OBJ LANGEXEC.OBJ RPCEXEC.OBJ \
	HRESULTS.OBJ EXITREMO.OBJ ROWSTUFF.OBJ MNGESERV.OBJ STATS.OBJ SENDMSG.OBJ $(OBJS_EXT) $(LIBS_EXT)
	echo >NUL @<<$(PROJ).CRF
SQLCBS.OBJ 
SQLEYE.OBJ 
INITSERV.OBJ 
INITREMO.OBJ 
LANGEXEC.OBJ 
RPCEXEC.OBJ 
HRESULTS.OBJ 
EXITREMO.OBJ 
ROWSTUFF.OBJ 
MNGESERV.OBJ 
STATS.OBJ 
SENDMSG.OBJ 
$(OBJS_EXT)
-OUT:$(PROJ).EXE
$(MAPFILE_OPTION)
..\..\..\DBLIB\LIB\NTWDBLIB.LIB
..\..\LIB\OPENDSNT.LIB
SQLEYE.RES

$(LIBS)
$(LIBS_EXT)
$(DEFFILE_OPTION) -implib:$(PROJ).lib
<<
	link $(LFLAGS) @$(PROJ).CRF

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
