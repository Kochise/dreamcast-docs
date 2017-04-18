
devcmd.dll: dlldata.obj devcmd_p.obj devcmd_i.obj
	link /dll /out:devcmd.dll /def:devcmd.def /entry:DllMain dlldata.obj devcmd_p.obj devcmd_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Zi /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del devcmd.dll
	@del devcmd.lib
	@del devcmd.exp
	@del dlldata.obj
	@del devcmd_p.obj
	@del devcmd_i.obj
 
