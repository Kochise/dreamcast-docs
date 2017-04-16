
rdurlps.dll: dlldata.obj rdurl_p.obj rdurl_i.obj
	link /dll /out:rdurlps.dll /def:rdurlps.def /entry:DllMain dlldata.obj rdurl_p.obj rdurl_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del rdurlps.dll
	@del rdurlps.lib
	@del rdurlps.exp
	@del dlldata.obj
	@del rdurl_p.obj
	@del rdurl_i.obj
