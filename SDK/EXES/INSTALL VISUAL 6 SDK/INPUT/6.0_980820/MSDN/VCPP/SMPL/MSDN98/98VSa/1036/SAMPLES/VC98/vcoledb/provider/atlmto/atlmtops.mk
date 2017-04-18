
atlmtops.dll: dlldata.obj atlmto_p.obj atlmto_i.obj
	link /dll /out:atlmtops.dll /def:atlmtops.def /entry:DllMain dlldata.obj atlmto_p.obj atlmto_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del atlmtops.dll
	@del atlmtops.lib
	@del atlmtops.exp
	@del dlldata.obj
	@del atlmto_p.obj
	@del atlmto_i.obj
