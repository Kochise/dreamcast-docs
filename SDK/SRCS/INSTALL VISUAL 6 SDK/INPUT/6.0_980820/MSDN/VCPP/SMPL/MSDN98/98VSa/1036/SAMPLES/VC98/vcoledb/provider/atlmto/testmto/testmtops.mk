
TestMTOps.dll: dlldata.obj TestMTO_p.obj TestMTO_i.obj
	link /dll /out:TestMTOps.dll /def:TestMTOps.def /entry:DllMain dlldata.obj TestMTO_p.obj TestMTO_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TestMTOps.dll
	@del TestMTOps.lib
	@del TestMTOps.exp
	@del dlldata.obj
	@del TestMTO_p.obj
	@del TestMTO_i.obj
