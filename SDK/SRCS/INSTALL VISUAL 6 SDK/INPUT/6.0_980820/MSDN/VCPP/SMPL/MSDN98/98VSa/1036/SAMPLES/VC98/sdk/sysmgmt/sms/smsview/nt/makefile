USE_SMS=1

Proj=SmsView

libs = ctl3d32s.lib gdi32.lib ntwdblib.lib

!include <BkOffice.Mak>

All: $(ObjDir)\$(Proj).Exe ViewDll\~

$(ObjDir)\$(Proj).Exe: $(@R).Obj $(@R).Res

ViewDll\~:
 cd ViewDll
 nmake /$(MAKEFLAGS)
 copy $(ObjDir)\ViewDll.Dll ..\$(ObjDir)
 cd ..
