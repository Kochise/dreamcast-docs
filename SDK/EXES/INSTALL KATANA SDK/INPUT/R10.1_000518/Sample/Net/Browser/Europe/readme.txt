First build the sample program.  Rename DPBrowser.bin to 1st_read.bin.  Then
build a full GD-ROM project in GD Workshop.

i.e.

1st_read.bin		<< sample executable >>
2_dp.bin		<< browser file (GD_ROOT)
MAIGO.BIN		<< application switcher (GD_ROOT)
sg_dpldr.bin		<< loader file (GD_ROOT)
\dpetc			<< browser folder
\dpfont			<< browser folder
\dpmodel		<< browser folder
\dpss			<< browser folder
\dptex			<< browser folder
\dpwww			<< browser folder

----------------------------------

When the brower exits it will run 1st_read.bin on the GD-ROM, and restart
the calling application.
