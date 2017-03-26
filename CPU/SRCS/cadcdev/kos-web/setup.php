<? $subject = "Setup/Compilation"; include("koshdr.php") ?>

<? heading("Intro"); ?>

<p>So you want to get started, but have no idea how. Well, you are not
alone!</p>

<p>The basic steps you will need to perform to get a working KOS dev setup
are the following:</p>

<p><ol>
	<li>Compile GCC</li>
	<li>Compile Newlib</li>
	<li>Compile G++</li>
	<li>Pull KOS from Subversion</li>
	<li>Setup an environ.sh</li>
	<li>Compile KOS</li>
	<li>Compile Ports</li>
</ol></p>

<p>The first three steps are covered adequately by other tutorials, <b>BUT</b>
please read this page before proceeding on one of those.</p>

<? heading("Getting a working GCC/Newlib"); ?>

<p>If you'd like an automated setup script, check out Jim Ursetto's setup
script <a href="dcsetup.php">here</a>. This is now the recommended way
due to the complexity of getting a fully threaded GCC and G++.</p>

<p>Newlib setup is covered <a href="newlib.php">here</a>. If you've previously
built KOS and want to update from a 1.2.x version to a 1.3.x version, or
from a pre-patch-148 1.3.x version, please read it. Otherwise you can
skip that.</p>

<p>Here are some links to standard setup tutorials. Maybe one will
work for you if you want to go this route. It seems like which one works for
people is random. I like the first one best.</p>

<p><a href="http://www.hangar-eleven.de/en/devdc-index.html">Hangar Eleven tutorial</a><br>
<a href="http://www.boob.co.uk/tutorials/guide.html">b00b! Getting started guide</a><br>
</p>

<? heading("Pulling KOS from Subversion"); ?>

<p>This topic is covered <a href="svn.php">here</a>.</p>

<p>You can also grab a
<a href="../../svn/snapshots/">weekly snapshot</a>.</p>

<? heading("Building an environ.sh"); ?>

<p>Once you have a KOS tree extracted, figure out its path. This can be
done by going to a shell (Cygwin or Linux/*NIX), changing to the dir
containing KOS, and using 'pwd' (it'll print something like /home/foo/kos).
This path will become your KOS_BASE.</p>

<p>Make a copy of doc/environ.sh.sample into your KOS_BASE. Edit this file
with a text editor, and set KOS_BASE to the path from above. Also set
KOS_CC_BASE and KOS_CC_PREFIX to match your compiler (generally the defaults
are ok). You may also want to set DC_ARM_BASE and DC_ARM_PREFIX if you
have the ARM compilers.</p>

<p>You should also edit environ_dreamcast.sh if you've upgraded to a newer
compiler version than 3.0.4. Note that versions newer than 3.0.4 are not
fully supported unless you go all the way up to 3.4.1. If you use 3.4.1,
you can remove "-fno-optimize-sibling-calls".</p>

<p>Make sure environ.sh is executed in any shell you'll do KOS work in. This
can be done, for example, by changing to your KOS_BASE dir and using the
command ". environ.sh". You can also add this to your ~/.login or similar,
though I'm not going to cover that here.</p>

<? heading("Building KOS"); ?>

<p>Ok, the big test! Change to your KOS_BASE dir and run make. If all goes
well, you should have a successful compile after a while. You may also want
to go to the kos-ports dir and compile that.</p>

<? heading("Building Ports"); ?>

</p>You should place your ports tree at the same level as your KOS_BASE, to
be standard. So for example, you might have ~/dc with your Dreamcast files
in it, and then ~/dc/kos for KOS_BASE, and ~/dc/kos-ports for Ports.</p>

<p>Change to your kos-ports base dir and use "ln -s ../kos/addons/Makefile .".
This will link the addons Makefile into place, and then "make" should suffice
to build everything.</p>

<? heading("Problems?"); ?>

<p>Join the KOS development list, and ask any questions there.
There are a lot of really helpful people there who are happy to help you
out. Really. :)</p>

<p><a href="list.php">List info can be found here.</a></p>

<? include("kosftr.php") ?>
