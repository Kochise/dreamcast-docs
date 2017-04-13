Readme.txt for the DSBrowse.exe

DSBrowse.exe is a sample VB application that demonstrates the ease with which VB application developers can quickly put together utilities for viewing/managing Directory Services.

DSBrowse performs the following tasks

1] It can enumerate through multiple namespaces (each corresponding to a Directory Service).  For each object found in a Directory Service hierarchy, it  provides a brief description of the object. Double clicking on a object  (container) will result in enumerating objects within that container.

2] Reading and writing properties on the DS object. Clicking on the properties button allows you to display the properties on an object. You can select a specific property and update it by pressing the "Set" button.

Requirements -
1] You must have Microsoft Visual Basic 4.0a Professional or Enterprise Edition installed on your machine. Microsoft Visual Basic 4.0a Professional or Enterprise Edition is available only on x86 platforms.

List of source  files:

1]dsbrowse.vbp -  Visual Basic Project File
2]Main.Frm- Form for browsing directory service namespaces
3]Property.Frm - Form for getting and setting properties
4]VbADs.Bas-  VisualBasic source code
5]DsVw.Res  - Resource file for the project (x86 only)
6]DsBrowse.Exe - Visual Basic Executable (x86 only)
