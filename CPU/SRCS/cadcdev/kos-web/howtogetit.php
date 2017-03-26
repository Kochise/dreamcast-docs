<? $subject = "How to get it"; include("koshdr.php") ?>

<p>There are two options for obtaining a copy of KOS for your use.</p>

<p>Option #1 is to download a release archive. These are snapshots made of
the working tree once in a while and have an associated version number in
the same style as Linux kernel releases (e.g. 1.2.1). An even middle digit
implies a "stable" version, meaning the API will not change significantly
if you upgrade to a new minor release (1.2.2, 1.2.3, etc). An odd middle
digit implies a "development" version, meaning you will get the absolute
latest goodies here, but you may or may not have any real stability. You
may find yourself rewriting chunks of your code to a new API or other
drastic changes.</p>

<p>Release archives can be obtained
<a href="http://sourceforge.net/project/showfiles.php?group_id=23791">here</a>.</p>

<p>Option #2 is to follow the source control. This is bleeding edge stuff,
but it's generally recommended anyway because KOS itself is pretty stable.
If you want to follow the devel version (e.g., 1.3.x) then you need
to be on this version. If you make local modifications to your tree then you
probably also want to be on here so you can merge new updates. Note that it's
also possible to follow a branch, for example the 1.2.x branch. This lets you
track the "stable" versions in a simpler way.</p>

<p>KOS is now developed (as of early October 2003) using
<a href="http://subversion.tigris.org/">Subversion</a>. For more info on
getting setup with that, <a href="svn.php">go here</a>.</p>

<p>Subversion weekly snapshots can be had
<a href="../../svn/snapshots/">here</a>.</p>

<? include("kosftr.php") ?>
