; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
$$IF(HAS_NEW_STEPS)
LastClass=IDD_CUSTOM1
LastTemplate=CDialog
$$ENDIF //HAS_NEW_STEPS
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "$$root$$.h"

$$IF(HAS_NEW_STEPS)
ClassCount=$$NUM_NEW_STEPS$$
$$BEGINLOOP(NUM_NEW_STEPS)
Class$$ITERATOR$$=CCustom$$ITERATOR$$Dlg
$$ENDLOOP //NUM_NEW_STEPS

ResourceCount=$$NUM_NEW_STEPS$$
$$BEGINLOOP(NUM_NEW_STEPS)
Resource$$ITERATOR$$=IDD_CUSTOM$$ITERATOR$$
$$ENDLOOP //NUM_NEW_STEPS

$$BEGINLOOP(NUM_NEW_STEPS)

[CLS:CCustom$$ITERATOR$$Dlg]
Type=0
HeaderFile=cstm$$ITERATOR$$dlg.h
ImplementationFile=cstm$$ITERATOR$$dlg.cpp
Filter=D

[DLG:IDD_CUSTOM$$ITERATOR$$]
Type=1
Class=CCustom$$ITERATOR$$Dlg

$$ENDLOOP //NUM_NEW_STEPS


$$ENDIF //HAS_NEW_STEPS
