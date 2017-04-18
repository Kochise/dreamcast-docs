
FinSrvrps.dll: dlldata.obj FinSrvr_p.obj FinSrvr_i.obj
	link /dll /out:FinSrvrps.dll /def:FinSrvrps.def /entry:DllMain dlldata.obj FinSrvr_p.obj FinSrvr_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del FinSrvrps.dll
	@del FinSrvrps.lib
	@del FinSrvrps.exp
	@del dlldata.obj
	@del FinSrvr_p.obj
	@del FinSrvr_i.obj
