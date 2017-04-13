MAPI Sample Simple Form


The Simple.Frm sample application illustrates writing a form in C++. The form
can be used by form-aware mail clients for sending/receiving messages of
IPM.Note.Sample.Simple message class instead of standard send/read forms.

Installation
------------

The form has to be properly registered to be used by mail clients. Run
pdkin32 -f smpfrm.cfg to register the form in the local form registry. Then
run regedit smpfrm.reg to register smpfrm.exe as an OLE server for the form in
the registry. The path to the form .EXE file has to be put in smpfrm.reg or
into the PATH.
 
Implementation
--------------

The forms class CBaseForm supports the IMAPIForm, IPersistMessage, and
IMAPIFormAdviseSink interfaces. Class CClassFactory implements IClassFactory.
The form also implements two helper classes: CLastError and CViewNotifier to
handle last error information and event notifications.

If you would like to use the sample as a base for your own form, you'll need
to change:

 - File names.
 - Form message class and class ID (in guid.h, smpfrm.reg, smpfrm.cfg).
 - The Verbs and Extension sections and all the human readable information
   in smpfrm.cfg.
 - The UI and supporting functions.
 - Implementation of all of the IPersistMessage methods, IMAPIForm::Doverb.

Supported Features
------------------

 - Send.
 - Reply, Forward.
 - Next, Previous.
 - Save, Delete.

Unsupported Features
--------------------

 - Attachments.
 - Reply All, Post.
 - Move, Copy.
 - Print.

For unsupported features, you have a choice of either disabling them or
delegating their execution to the form viewer. This is controlled by setting
the appropriate fields of the Value variable in the [Extensions.1] section of
the form .cfg file. Refer to MAPI Form Documentation for details.
