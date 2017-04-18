
stockquotesps.dll: dlldata.obj stockquotes_p.obj stockquotes_i.obj
	link /dll /out:stockquotesps.dll /def:stockquotesps.def /entry:DllMain dlldata.obj stockquotes_p.obj stockquotes_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del stockquotesps.dll
	@del stockquotesps.lib
	@del stockquotesps.exp
	@del dlldata.obj
	@del stockquotes_p.obj
	@del stockquotes_i.obj
