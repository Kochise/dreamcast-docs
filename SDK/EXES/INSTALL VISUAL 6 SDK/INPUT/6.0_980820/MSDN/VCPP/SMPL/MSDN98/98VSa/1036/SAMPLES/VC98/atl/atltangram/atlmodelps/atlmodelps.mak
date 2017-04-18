
ATLModelps.dll: dlldata.obj ATLModel_p.obj ATLModel_i.obj 
	link /dll /out:ATLModelps.dll /def:ATLModelps.def /entry:DllMain dlldata.obj ATLModel_p.obj ATLModel_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib msvcrt.lib

.c.obj:
	cl /I..\ATLModel /I..\ /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del ATLModelps.dll
	@del ATLModelps.lib
	@del ATLModelps.exp
	@del dlldata.obj
	@del ATLModel_p.obj
	@del ATLModel_i.obj
