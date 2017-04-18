; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=4
Class1=CSmbSmpApp
Class2=CExtObject
Class3=CBasePropertyPage
Class4=CSmbSmpParamsPage
ResourceCount=1
Resource1=IDD_PP_SMBSMP_PARAMETERS
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SmbSmpEx.h"

[CLS:CSmbSmpApp]
Type=0
HeaderFile=SmbSmpEx.h
ImplementationFile=SmbSmpEx.cpp
Filter=N
LastObject=CSmbSmpApp

[CLS:CExtObject]
Type=0
HeaderFile=ExtObj.h
ImplementationFile=ExtObj.cpp
BaseClass=CComObjectRoot
Filter=N
LastObject=CExtObject
VirtualFilter=C

[CLS:CBasePropertyPage]
Type=0
HeaderFile=BasePage.h
ImplementationFile=BasePage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CBasePropertyPage
VirtualFilter=idWC

[CLS:CSmbSmpParamsPage]
Type=0
HeaderFile=ResProp.h
ImplementationFile=ResProp.cpp
BaseClass=CBasePropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CSmbSmpParamsPage

[DLG:IDD_PP_SMBSMP_PARAMETERS]
Type=1
Class=CSmbSmpParamsPage
ControlCount=5
Control1=IDC_PP_ICON,static,1342177283
Control2=IDC_PP_TITLE,static,1342308492
Control3=IDC_PP_RESPARAMS_SHARENAME_LABEL,static,1342308352
Control4=IDC_PP_RESPARAMS_SHARENAME,edit,1350631552
Control5=IDC_PP_RESPARAMS_PATH_LABEL,static,1342308352
Control6=IDC_PP_RESPARAMS_PATH,edit,1350631552
Control7=IDC_PP_RESPARAMS_REMARK_LABEL,static,1342308352
Control8=IDC_PP_RESPARAMS_REMARK,edit,1350631552
