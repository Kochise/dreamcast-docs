<? $relpath = "../../"; include("../../header.php") ?>

<?
function heading($t) {
?>

<br>
<p><font size="+1"><b><i><? echo $t ?></i></b></font></p>

<?
}
?>

<center>

<table width="95%" border="0">
<tr>
	<td valign="top">
		<table width="100%" border="0" bgcolor="#6f688c"><tr><td>
<!-- end header -->

<center>
<hr width="70%">
<p><font size="+2">KallistiOS Subversion</font></p>
<p><i>(last updated October 23, 2003)</i></p>
<hr width="70%">
</center>
<br>
<br>

<? heading("Intro"); ?>

<p>Unfortunately two factors have conspired to make it so that we can't
provide a public Subversion server for everyone to access:</p>

<p><ol>
	<li>Subversion is still not in a "stable" state;</li>
	<li>SourceForge does not provide Subversion hosting, and providing
		Subversion hosting requires a custom Apache 2.0 server or
		a cvspserver-like service.</li>
</ol></p>

<p>As I do not have the resources to provide Subversion hosting on my own,
I have opted for a "push" model for Subversion development. What this means
is that each time a developer checks in a new revision into my local
repository, a changeset dump will be generated and posted on this web
site. You can then download these dump files and maintain a private Subversion
repository. In this way, you get the latest updates most accurately, and
you also have access to the full revision history.</p>

<p>I'm aware that there may be some utilities already written to handle and
automate this process, but I have written my own.</p>


<? heading("Initial Stuff"); ?>

<p>A couple of things up front, including system prerequisites.</p>

<p>First of all, you need a Subversion client. You will need both the "svn"
program, and the "svnadmin" program. These programs can be obtained
<a href="http://subversion.tigris.org/project_packages.html">here</a>.
Windows/Cygwin users can get "svn-win32-0.30.0.zip" or
"svn-0.30.0-setup.exe", or whatever the latest versions of those are.
Debian "sid" or "unstable" users can just "apt-get install subversion".
Make sure that after the install, svn and svnadmin are in your path.</p>

<p>Windows users will generally need Cygwin with "bzip2" installed to make
this work. You generally need Cygwin to develop with KOS anyway, so you
probably have this. But make sure you have "bzip2" installed as well.
It's possible to make this work without Cygwin, but you're pretty much on
your own at that point.</p>

<p>Doing this will require about 150MB of disk space initially. After
trimming back the repository this can be lowered to about 110MB if you need
the space back.</p>


<? heading("The Easy Way"); ?>

<p>If you have Python installed (I'm using 2.3.1) then you have a super
easy setup task. Grab <a href="svnpull.py">this script</a> and also
<a href="svnpush.py">this script</a>. Make an initial
repository with svnadmin (see "Create a shell repository" below). Then run
svnpull.py on it, something like this:</p>

<p><pre>
svnadmin create kosrepo
svnpull.py kosrepo http://gamedev.allusion.net/svn/
</pre></p>

<p>Note that the path ("kosrepo") is passed directly to svnadmin. So if you
are using the Win32 Subversion client, this needs to be a Windows-style
path. See below for more info on that confused sillyness... Relative
paths are ok, that is perhaps easiest.</p>

<p>Wait for a few minutes, and you should be all ready to go! You can run this
same script with the same parameters as much as you like, to check for
and apply new updates.</p>

<p>Here are the manual setup directions though, in case that doesn't work
for you...</p>


<? heading("Doing The Initial Import"); ?>

<p>Here are the steps you will take to get your private SVN repository (repo)
going. This generally only needs to be done once.</p>

<p>
<ol>
	<li><i>Create a shell repository</i>.<ul>
		<li>Pick a place for your repository. Under Unix this would be
		a path like /foo/bar/kosrepo. Under Windows you'd use something
		like c:\foo\bar\kosrepo.</li>
		<li>Create a repo with with svnadmin: <pre>svnadmin create /foo/bar/kosrepo</pre></li>
		<li>Or for Windows,<br>
			<pre>svnadmin create c:\foo\bar\kosrepo</pre><br>
			Note that if you are using Cygwin you'll need to
			enclose Windows-style paths in single-quotes, like:<br>
			<pre>svnadmin create 'c:\foo\bar\kosrepo'</pre>
		</li>
	</ul></li>

	<li><i>Download the latest repository base revision and any incremental ones</i>.<ul>
		<li>Browse to <a href="http://gamedev.allusion.net/svn/">http://gamedev.allusion.net/svn/</a>.</li>
		<li>Grab the latest *_full.dump.bz2</li>
		<li>Grab any subsequent *_incr.dump.bz2</li>
	</ul></li>

	<li><i>"Load" your repository with the downloaded goodies</i>.<ul>
		<li><pre>bzip2 -cd 26_full.dump.bz2 | svnadmin load /foo/bar/kosrepo</pre></li>
		<li><pre>bzip2 -cd 27_incr.dump.bz2 | svnadmin load /foo/bar/kosrepo</pre></li>
		<li>...</li>
		<li>Under Windows, use the Windows-style paths to your repo as discussed above.</li>
		<li>The final message should be something like:<br>
			<pre>------- Committed revision 27 &gt;&gt;&gt;</pre>
		</li>
	</ul></li>

	<li><i>Check out a copy of the tree from your local repo into a working dir</i>.<ul>
		<li>Pick a place on your HD. I will use "/foo/bar/kos".</li>
		<li><pre>svn co file:///foo/bar/kosrepo /foo/bar/kos</pre></li>
		<li>Or for Windows,<br>
			<pre>svn co file:///c:/foo/bar/kosrepo c:\foo\bar\kos</pre>
		</li>
		<li>The final message should be something like:<br>
			<pre>Checked out revision 27.</pre>
		</li>
	</ul></li>
</ol></p>

<p>Congrats, you are now setup and should be ready to rock! Note that the
"*" in the "download" step above denotes a version ID (I was at 26 when I
wrote this doc). Any time I post new updates, you can follow a very similar
(but MUCH simpler) process to bring yourself up to date.</p>

	
<? heading("Subsequent Imports"); ?>

<p><ol>
	<li><i>Download the latest incremental versions</i>.<ul>
		<li>Browse to <a href="http://gamedev.allusion.net/svn/">http://gamedev.allusion.net/svn/</a>.</li>
		<li>Grab any subsequent *_incr.dump.bz2 that you don't have.</li>
	</ul></li>

	<li><i>"Load" your repository with the downloaded goodies</i>.<ul>
		<li><pre>bzip2 -cd 28_incr.dump.bz2 | svnadmin load /foo/bar/kosrepo</pre></li>
		<li>...</li>
	</ul></li>

	<li><i>Update your working copy</i>.<ul>
		<li><pre>cd /foo/bar/kos</pre></li>
		<li><pre>svn up</pre></li>
	</ul></li>
</ol></p>

<p>I will periodically upload new full dumps for people just getting
started. I'll keep incrementals back to the last full dump for people who
are behind. If you get more than a full dump behind, you'll have to start
at square one up there with your repo (but I think you can safely keep your
working dirs just fine).</p>

<p>To figure out what version you currently have, make sure you have done a
"svn up" in your working dir (/foo/bar/kos above) and then:</p>

<p><pre>
svn status -uN .
</pre></p>

<p>This will tell you a number like "27":</p>

<p><pre>
Status against revision:     27
</pre></p>

<p>If there are revisions above your number in the web dir I listed above,
you'll need to grab them and patch up your repository. </p>


<? heading("Further..."); ?>

<p>I'd like to get Cygwin binaries for svn and svnadmin. For now it'll have
to be done using the Win32 binaries.</p>


<? heading("Repo Cleanup"); ?>

<p>If you want to reclaim a bit of used space, use the "svnadmin
list-unused-dblogs" command on your repo. This will print a list of files
that can be deleted "safely" (I have had a few issues with this, but your
milage may vary). A Cygwin command that can do this for you:</p>

<p><pre>
for i in `svnadmin list-unused-dblogs /foo/bar/kosrepo`; do \
	echo rm -f `cygpath -u $i`; done
</pre>
</p>

<p>When you think it looks right, remove the "echo" and it'll act. You can
also replace the -f with -i to have it prompt for each file.</p>

	
<? heading("Problems?"); ?>

<p>I know this is a big pain in the rear, but hopefully someone will step up
and provide Subversion hosting for free software projects some time soon. In
the mean time, if you have problems with the above, please join the main
KOS mailing list and post there. You can find info on KOS on
<a href="index.php">the main KOS page</a>.</p>


<!-- begin footer -->
		</td></tr></table>
	</td>
	<td valign="top">
		<? include("../../menu.php") ?>
	</td>
</tr>
</table>

</center>


<? include("../../footer.php") ?>
