
MyProvps.dll: dlldata.obj MyProv_p.obj MyProv_i.obj
	link /dll /out:MyProvps.dll /def:MyProvps.def /entry:DllMain dlldata.obj MyProv_p.obj MyProv_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del MyProvps.dll
	@del MyProvps.lib
	@del MyProvps.exp
	@del dlldata.obj
	@del MyProv_p.obj
	@del MyProv_i.obj
