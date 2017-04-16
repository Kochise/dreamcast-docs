#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                   PhoneDir Application                  **#
#**            Copyright(c) Microsoft Corp. 1994            **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>

!ifndef MIDL
MIDL            = midl
!endif

MIDLFLAGS    = /ms_ext /app_config /c_ext 
				  

.cxx.obj:
    $(CC) /D "_UNICODE" /D "UNICODE" $(cdebug) $(CFLAGS) $(cvars) $(cvarsdll) /c $<

.c.obj:
    $(CC) /D "_UNICODE" /D "UNICODE" $(cdebug) $(CFLAGS) $(cvars) $(cvarsdll) /c $<

all:  pd.dll 

# Clean up everything
cleanall: clean
	@-del *.exe 2>nul

# Clean up everything but the .EXEs
clean:  
	@-del *.obj 2>nul
	@-del pd.dll 2>nul
	@-del pd.h 2>nul
	@-del pd_?.* 2>nul


#the files that make up the dll
pd_i.obj : pd_i.c

pd_p.obj : pd_p.c pd.h

dlldata.obj : dlldata.c

# run midl to produce the header files and the proxy file
pd.h pd_p.c pd_i.c dlldata.c: pd.idl
		$(MIDL) $(MIDLFLAGS) pd.idl

pd.dll: pd_p.obj pd_i.obj dlldata.obj pd.def
    $(link) $(linkdebug)              \
    -base:0x1C000000     \
    -dll                 \
    -entry:_DllMainCRTStartup$(DLLENTRY) \
    -DEF:pd.def    \
    -out:pd.dll    \
    pd_p.obj pd_i.obj  dlldata.obj rpcrt4.lib $(ole2libs)

