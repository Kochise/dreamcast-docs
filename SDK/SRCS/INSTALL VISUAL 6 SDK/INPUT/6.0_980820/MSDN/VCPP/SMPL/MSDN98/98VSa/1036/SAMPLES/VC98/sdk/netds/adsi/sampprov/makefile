
Proj = Adssmp

# These are "extra" libs beyond the standard set that inetsdk.mak will
# append to the libs set
LibList=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib \
	 shell32.lib ole32.lib oleaut32.lib uuid.lib activeds.lib adsiid.lib 

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

dll=1

!include <bkoffice.mak>


#All: $(ObjDir)\$(Proj).Dll
# itemize all of the required Object files
ObjList=$(@D)\cclsobj.obj \
	$(@D)\cdispmgr.obj \
	$(@D)\cenumns.obj \
	$(@D)\cenumobj.obj \
	$(@D)\cenumsch.obj \
	$(@D)\cenumvar.obj \
	$(@D)\cgenobj.obj \
	$(@D)\cnamcf.obj \
	$(@D)\cnamesp.obj \
	$(@D)\common.obj \
	$(@D)\core.obj \
	$(@D)\cprops.obj \
	$(@D)\cprov.obj \
	$(@D)\cprovcf.obj \
	$(@D)\cprpobj.obj \
	$(@D)\cschobj.obj \
	$(@D)\getobj.obj \
	$(@D)\globals.obj \
	$(@D)\guid.obj \
	$(@D)\libmain.obj \
	$(@D)\memory.obj \
	$(@D)\object.obj \
	$(@D)\pack.obj \
	$(@D)\parse.obj \
	$(@D)\property.obj \
	$(@D)\regdsapi.obj \
	$(@D)\smpoper.obj \
	$(@D)\stdfact.obj \
        $(@D)\adssmp.obj


LFLAGS= $(LFLAGS)  /def:"adssmp.def"  /implib:"$(@D)\adssmp.lib"




Includes = adssmp.h \
cclsobj.h cdispmgr.h cenumns.h cenumobj.h cenumsch.h \
cenumvar.h cgenobj.h cmacro.h cnamcf.h cnamesp.h common.h \
core.h cprops.h cprov.h cprovcf.h cprpobj.h cschobj.h formtrck.h \
getobj.h globals.h guid.h intf.h libmain.h macro.h memory.h \
object.h pack.h parse.h property.h regdsapi.h smpoper.h smptypes.h \
util.h


#$(@D)\$(Proj).Dll: $(Objs) 
#$(ObjDir)\$(Proj).Dll: $(ObjList) $(@R).Res
All: $(ObjDir)\$(Proj).Dll

$(ObjDir)\$(Proj).Dll: $(ObjList)


$(ObjDir)\$(Proj).exp: $(ObjList) adssmp.def
