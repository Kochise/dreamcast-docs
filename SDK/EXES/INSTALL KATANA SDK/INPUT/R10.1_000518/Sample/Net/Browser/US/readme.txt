First build the sample program.  Rename PWBrowser.bin to 1st_read.bin.  Then
build a full GD-ROM project in GD Workshop.

To run you must create a GD Project containing the contents of GD_ROOT
onto the GD-ROM...

i.e. (What GD-ROM should look like)

1st_read.bin		<< sample executable >>
2_dp.bin		<< browser file (GD_ROOT)
MAIGO.BIN		<< application switcher (GD_ROOT)
sg_dpldr.bin		<< loader file (GD_ROOT)
\PWBROWSER		<< browser folder (PWBROWSER)

----------------------------------

When the brower exits it will run 1st_read.bin on the GD-ROM, and restart
the calling application.
