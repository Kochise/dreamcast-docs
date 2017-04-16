
FishTankLevelGetterps.dll: dlldata.obj FishTankLevelGetter_p.obj FishTankLevelGetter_i.obj
	link /dll /out:FishTankLevelGetterps.dll /def:FishTankLevelGetterps.def /entry:DllMain dlldata.obj FishTankLevelGetter_p.obj FishTankLevelGetter_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del FishTankLevelGetterps.dll
	@del FishTankLevelGetterps.lib
	@del FishTankLevelGetterps.exp
	@del dlldata.obj
	@del FishTankLevelGetter_p.obj
	@del FishTankLevelGetter_i.obj
