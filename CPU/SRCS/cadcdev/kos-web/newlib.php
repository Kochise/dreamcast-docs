<? $subject = "Newlib info"; include("koshdr.php") ?>

<p>As of August 6, 2004, KOS uses Newlib instead of its own libc/libm. This
means you will need to patch Newlib and build it properly instead of just
haphazardly using the defaults (which are quite broken for KOS).</p>

<p>The patch you need to apply can be found
<a href="newlib/newlib-1.12.0-kos.patch">here</a>. You can do this by grabbing
the Newlib 1.12.0 archives, changing to that dir, and executing
"patch -p1 < newlib-1.12.0-kos.patch" (or whereever you put the file).
Alternatively you can grab a pre-patched Newlib
<a href="newlib/newlib-1.12.0-kos-src.zip">here (zip)</a> or
<a href="newlib/newlib-1.12.0-kos-src.tar.bz2">here (bz2)</a>.</p>

<p>Also if you are not using the standard "-ml -m4-single-only" target on
the DC, or you are using alternate compilation flags from
"-fno-crossjumping" and "-fno-optimize-sibling-calls", you may need to edit
the patch to suit your needs; but I assume that if you are not using those
defaults then you know how to handle that on your own.</p>

<p>Once that's done you can compile Newlib per normal. If you already had 
a tool chain and you're just updating Newlib for all this new crazy stuff,
then here are the directions:</p>

<p>
<pre>
cd ${builddir}
${srcs}/configure --target=sh-elf --prefix=${compilerpath}
make all install CC_FOR_TARGET=sh-elf-gcc AS_FOR_TARGET=sh-elf-as \
	LD_FOR_TARGET=sh-elf-ld AR_FOR_TARGET=sh-elf-ar \
	RANLIB_FOR_TARGET=sh-elf-ranlib
</pre>
</p>

<p>...where ${builddir} is a random dir you made to build Newlib,
${srcs} is the dir containing your Newlib sources, and ${compilerpath}
is where your compiler is installed.</p>

<p>I have put a precompiled copy of Newlib online, built with my GCC 3.3.3
snapshot. It may or may not work for you but it will probably be easier to
try it first if you already have a setup. Grab it
<a href="newlib/newlib-1.12.0-kos-bin.zip">here (zip)</a> or
<a href="newlib/newlib-1.12.0-kos-bin.tar.bz2">here (bz2)</a>.
Both archives have the same contents and are
meant to be extracted inside your compiler target dir (though again if it's
not sh-elf, you'll need to mess with paths).</p>

<? include("kosftr.php") ?>
