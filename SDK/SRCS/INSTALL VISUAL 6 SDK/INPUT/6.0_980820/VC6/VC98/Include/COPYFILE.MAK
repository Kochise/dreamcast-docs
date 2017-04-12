###############################################################################
#   copyfile.mak
#
#	Move the .ini and recopy the dlls if devcopy is set
###############################################################################


!IF "$(ISPARSER)"=="YES"
CopyPath=$(BH_ROOT)\BUILD\PARSERS
!ELSEIF "$(ISDRIVER)"=="YES"
CopyPath=$(BH_ROOT)\BUILD\DRIVERS
!ELSE
CopyPath=$(BH_ROOT)\BUILD
!ENDIF

all:    CopyFiles

CopyFiles:
!IF "$(COPYINI)"=="YES"
	copy $(MODULE).ini $(CopyPath)\$(CPU)
!ENDIF
!IFDEF EXTRACOPY1
	copy $(EXTRACOPY1) $(CopyPath)\$(CPU)
!ENDIF
!IFDEF EXTRACOPY2
	copy $(EXTRACOPY2) $(CopyPath)\$(CPU)
!ENDIF
!IFDEF EXTRACOPY3
	copy $(EXTRACOPY3) $(CopyPath)\$(CPU)
!ENDIF
!IFDEF EXTRACOPY4
	copy $(EXTRACOPY4) $(CopyPath)\$(CPU)
!ENDIF
!IFDEF DEVCOPY
	COPY $(CopyPath)\$(CPU)\$(MODULE).* $(CopyPath)
!IFDEF EXTRACOPY1
	copy $(EXTRACOPY1) $(CopyPath)
!ENDIF
!IFDEF EXTRACOPY2
	copy $(EXTRACOPY2) $(CopyPath)
!ENDIF
!IFDEF EXTRACOPY3
	copy $(EXTRACOPY3) $(CopyPath)
!ENDIF
!IFDEF EXTRACOPY4
	copy $(EXTRACOPY4) $(CopyPath)
!ENDIF
!ENDIF

