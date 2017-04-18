OLE Automation Sample


SUMMARY
=======

The TiBrowse sample is an OLE automation browser. When started, it asks the 
user to selected a type library (.tlb) file. The browser then displays the 
contents of the file.

MORE INFORMATION
================

This browser is not suitable for use by end users. It is deficient in many 
ways. Users should never have to know that uuids exist, thus, they should 
not be displayed in a browser. Items that are restricted or that start with 
an underscore should not be displayed in a browser. Duplicates for property 
get/set pairs should be removed, since users think about properties, not 
about get/set pairs.

