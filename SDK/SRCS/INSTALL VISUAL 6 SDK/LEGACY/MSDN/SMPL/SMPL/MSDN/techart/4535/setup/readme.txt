README.TXT for the 'OLE Control and Control Container Guidelines'
Version 1.1 Verification Software.

- Both VCONTAIN.EXE and VCONTROL.EXE require the following MFC files in
the current directory or in the path to execute:
MFC40.DLL
OLEPRO32.DLL
MSVCRT40.DLL

- The software must run on either Windows 95 or Windows NT.

- To install, copy the contents of the \SETUP directory from the CD to
your hard drive.  Run the REGISTER.BAT file to register the VCONTROL.OCX
with the system. This file calls the REGSVR32.EXE file (also in the 
\SETUP directory) to do this for you.  

- To verify your container, insert the VControl into it by whatever means
is appropriate for your container (usually a menu item like "Insert 
Control") and run your containing application.  Click on the control to 
begin verification

- To verify your registered control, simply run the VCONTAIN.EXE 
program, then instantiate your control in the container to verify it.
Use the VContain's menu items to verify all or a subset of the control's
interfaces.

- During debugging you may want to run the VContainer and the 
VControl against each other.  This is encouraged for tutorial purposes,
and can give you a good idea of how the two modules interact with one
another.

To ensure correct execution, it is best if you delete the instance 
of the control between the two different verification processes. 
Remember that these are test modules and they call certain interfaces
and methods at times that they would not normally be called, which can
result is unexpected results.

For example, suppose that you instantiate the VControl, then run the
VContainer's verification test against it.  If you now want to run 
the VControl's verification test against the VContainer, it is 
recommended that you first delete the VControl instance through the
VContainer's menu or toolbar. Instantiate the VControl again, then 
click on it to verify the VContainer.

- Refer to the whitepaper "Implementation Notes for the OLE Control
and Control Container Guidelines Verification Software" on the MSDN
CD for further information on executing the verifcation process and interpretting 
the results.


"