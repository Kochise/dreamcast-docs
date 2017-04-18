(Use set Edit.Word Wrap on to view this file.)

All of the differences between the version of StopLite that declares it's safe by marking the registry and the version that declares it's safe using IObjectSafety are in the files StopLiteCtl.CPP and StopLiteCtl.H.

So, I've given you two directories: MarkReg and IObjSafe. Each contains the StopLiteCtl.* files necessary to build the appropriate version.

To build the IObjectSafety version, copy the files in IObjSafe over the source files in the project. If you're not going to mark the registry, you can remove the HELPERS.CPP and HELPERS.H files from your project, since they won't be used.

To build the registry marking version, copy the files in MarkReg over the source files in the project.

If you want to both implement IObjectSafety and mark the registry, you'll need to merge the StopLiteCtl.* files from the two different directories and leave HELPERS.CPP/.H in your project.

The original files in the project are the same as those in MarkReg.
