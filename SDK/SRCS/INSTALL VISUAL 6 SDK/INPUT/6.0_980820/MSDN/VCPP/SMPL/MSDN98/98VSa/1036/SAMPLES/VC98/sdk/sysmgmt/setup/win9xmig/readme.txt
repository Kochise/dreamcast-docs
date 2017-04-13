
THIS IS A VERY EARLY PRE-RELEASE OF WINDOWS NT 5.0, THE MIGRATION SAMPLE CODE AND DOCUMENTATION

Known issues with sample code
*****************************
Migrated screen saver may not work properly if user logs in using a non-administrator account on Windows NT 5.0 after the migration.

Blank screen savers may not work properly until a non-blank screen saver is used. 
VC5 users can open migrate.dsp to build the project.

Other Notes
*****************************
Read sysdiff.doc before running sysdiff.exe or sysdiffa.exe

You may want to change which C runtime is used if you do not want to use the static multithreaded runtime.

A .mak file (migrate.mak) for non-VC5 users is exported

This build joins ProductID to the Object Section to generate incompatibility messages.  This is different that what is described on page 19 of migext.doc.  Migext.doc describes the correct behavior.

 
