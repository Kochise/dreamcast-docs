
stocktickerATLps.dll: dlldata.obj stocktickerATL_p.obj stocktickerATL_i.obj
	link /dll /out:stocktickerATLps.dll /def:stocktickerATLps.def /entry:DllMain dlldata.obj stocktickerATL_p.obj stocktickerATL_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del stocktickerATLps.dll
	@del stocktickerATLps.lib
	@del stocktickerATLps.exp
	@del dlldata.obj
	@del stocktickerATL_p.obj
	@del stocktickerATL_i.obj
