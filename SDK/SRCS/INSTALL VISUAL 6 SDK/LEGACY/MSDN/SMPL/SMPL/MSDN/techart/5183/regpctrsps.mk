
RegPCtrsps.dll: dlldata.obj RegPCtrs_p.obj RegPCtrs_i.obj
	link /dll /out:RegPCtrsps.dll /def:RegPCtrsps.def /entry:DllMain dlldata.obj RegPCtrs_p.obj RegPCtrs_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del RegPCtrsps.dll
	@del RegPCtrsps.lib
	@del RegPCtrsps.exp
	@del dlldata.obj
	@del RegPCtrs_p.obj
	@del RegPCtrs_i.obj
