; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CImagePropPage
LastTemplate=CCachedDataPathProperty
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "image.h"
CDK=Y

ClassCount=3
Class1=CImageCtrl
Class2=CImagePropPage

ResourceCount=2
Resource1=IDD_ABOUTBOX_IMAGE
LastPage=0
Class3=CBitmapProperty
Resource2=IDD_PROPPAGE_IMAGE

[CLS:CImageCtrl]
Type=0
HeaderFile=ImageCtl.h
ImplementationFile=ImageCtl.cpp
Filter=W
LastObject=CImageCtrl
BaseClass=COleControl
VirtualFilter=wWC

[CLS:CImagePropPage]
Type=0
HeaderFile=ImagePpg.h
ImplementationFile=ImagePpg.cpp
Filter=D
LastObject=IDC_IMAGEPATH
BaseClass=COlePropertyPage
VirtualFilter=idWC

[DLG:IDD_ABOUTBOX_IMAGE]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROPPAGE_IMAGE]
Type=1
Class=CImagePropPage
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_IMAGEPATH,edit,1350631552
Control3=IDC_AUTOSIZE,button,1342242819

[CLS:CBitmapProperty]
Type=0
HeaderFile=BitmapProperty.h
ImplementationFile=BitmapProperty.cpp
BaseClass=CCachedDataPathProperty
Filter=N
VirtualFilter=1y
LastObject=CBitmapProperty

