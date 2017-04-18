###############################################################################
#   GloblMak.mak
#
#	A file that EVERY build makefile will include...
###############################################################################

#Bloodhound uses -DDEBUG, not DBG=1 to target debug builds...
!IF "$(NTDEBUG)"=="ntsd" || "$(NTDEBUG)"=="cvp" || "$(NTDEBUG)"=="sym" 
C_DEFINES=$(C_DEFINES) -DDEBUG
!ENDIF

