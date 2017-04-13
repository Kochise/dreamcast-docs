
providerps.dll: dlldata.obj provider_p.obj provider_i.obj
	link /dll /out:providerps.dll /def:providerps.def /entry:DllMain dlldata.obj provider_p.obj provider_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del providerps.dll
	@del providerps.lib
	@del providerps.exp
	@del dlldata.obj
	@del provider_p.obj
	@del provider_i.obj
