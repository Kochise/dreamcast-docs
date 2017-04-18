
atlps.dll: dlldata.obj atl_p.obj atl_i.obj
	link /dll /out:atlps.dll /def:atlps.def /entry:DllMain dlldata.obj atl_p.obj atl_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib uuid.lib

.c.obj:
	cl /c /Ox /DWIN32 /DREGISTER_PROXY_DLL $<

clean:
	@del atlps.dll
	@del atlps.lib
	@del atlps.exp
	@del dlldata.obj
	@del atl_p.obj
	@del atl_i.obj
