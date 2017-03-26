#!/usr/bin/env python

# This script implements the client side of the Subversion repository dump
# "push" system, the server side of which is implemented in svnpush.py.
#
# Copyright (C)2003 Dan Potter
#

# Usage:
# svnpull.py <repo path> <svnpush URL>
#
# A Subversion repository should exist at <repo path> and not be in use by
# any other client at the time (e.g., stop your Apache instance if you are
# using one, most people won't; make sure other users aren't using it, etc). 
# The <svnpush URL> should be the URL where updates are being posted on
# the web. This should contain one or more xxx_full.dump.bz2 files and zero
# or more xxx_incr.dump.bz2 files. It can be hand-maintained, but will
# generally be maintined by the svnpush.py script.
#
# When the script is run, it will go out to the URL and check the available
# revisions there. This will be compared against the revisions present in the
# local repository. If there are newer revisions present on the site, they
# will be downloaded and applied locally.
#
# Note that this goes only by version numbers -- you are required by this
# currently to not check in anything to your repository locally! If you do
# then strange things may start to happen. Perhaps this can be fixed later.

import sys, string, svnpush, urllib2, popen2, thread

########################################################################
# Configuration

# All configuration is done in the svnpush.py module. Please look in that
# file for config options.

########################################################################
# Implicit config globals, from cmdline.  Set these to something besides
# None if you want to have parameter defaults. If you set one, you must
# set them all.

global path_svnrepo, path_srcurl

# path_svnrepo - path to the SVN repo we're working on
path_svnrepo = None

# path_srcurl - URL to pull updates from
#path_srcurl = 'http://gamedev.allusion.net/svn/'
path_srcurl = None

# Verify the defaulted parameters
try:
	if (path_svnrepo is not None) or (path_srcurl is not None):
		assert path_svnrepo is not None
		assert path_srcurl is not None
except AssertionError:
	print "Some parameters were defaulted, others were not."
	print "Please correct this in svnpull.py and try again."
	sys.exit(-1)

########################################################################
# SVN Utility funcs
# These supplement what's in svnpush.py. Perhaps not the greatest code
# layout but it works and is simple.

# Merge one Subversion revision from the web server. This uses 'svnadmin
# load' and 'bzip2' to decrunch and load the dump.
def svnLoadRevision(revFn):
	# Grab the revision
	rd = urlGet(path_srcurl + '/' + revFn)

	# Open up a pipe to svnadmin to write it out
	print "Loading '%s' into the repo..." % revFn
	p = popen2.Popen3('bzip2 -cd | ' + svnpush.svnadmin_bin \
		+ ' load %s' % path_svnrepo, 1)

	# Start threads to give the user a running display of stdout/stderr
	def dispthread(fd):
		while 1:
			f = fd.readline()
			if f == '':
				return
	thread.start_new_thread(dispthread, (p.fromchild,))
	thread.start_new_thread(dispthread, (p.childerr,))

	# Write all of our data into the pipe
	p.tochild.write(rd)
	p.tochild.close()

	# Get the return code
	rc = p.wait()

	return rc


########################################################################
# HTTP utility funcs
# These are analogous to the SCP utility funcs in svnpush.py, but they use
# URLs and urllib as a transport.

# Open a URL and return the file contents as a string.
def urlGet(src):
	print "Downloading %s" % src

	# Open a connection
	h = urllib2.urlopen(src)

	# Copy the contents
	cont = h.read()

	# Close out
	h.close()

	return cont

# Copy down one file from the given URL.
def urlCopy(src, dst):
	# Get the file data
	h = urlGet(src)

	# Open the destination file
	f = open(dst, "wb")

	# Copy the contents from h to f
	f.write(h)

	# Close out
	f.close()

# Go out to the URL and find the latest full dump revision.
def urlLatestFullRevision():
	return int(string.strip(urlGet(path_srcurl + "/highest_full")))

# Go out to the URL and find the latest incremental dump revision.
def urlLatestIncrRevision():
	return int(string.strip(urlGet(path_srcurl + "/highest_incr")))

# Go out to the URL and find the latest revision available. Returns both
# the revision and the type string.
def urlLatestRevision():
	# Get the latest full revision
	lf = urlLatestFullRevision()

	# And the latest incremental revision
	li = urlLatestIncrRevision()

	# Make sure it's valid
	if lf < 0:
		print "Latest full revision is -1, which is invalid."
		sys.exit(-1)
	if li > 0 and lf > li:
		print "Full revisions exist without incrementals, which is invalid."
		sys.exit(-1)

	# If there is an incremental revision available, return that.
	if li > 0:
		return li, 'incr'
	else:
		return lf, 'full'

# Grab the specified revision (as 'full' or 'incr') and load it up.
def urlLoadRevision(rev, type):
	# Commit it
	rc = svnLoadRevision("%d_%s.dump.bz2" % (rev, type))
	if rc != 0:
		print "Couldn't load revision %d/%s, exit code %d" \
			% (rev, type, rc)
		sys.exit(-1)

#######################################################################
# Main

def help():
	global path_srcurl

	# Preamble is always the same
	print "usage: svnpull.py ",

	# Do we have defaults?
	if path_svnrepo is not None:
		print "[<local repo path> <src URL>]"
		print "<local repo path> defaults to '%s'" % path_svnrepo
		print "<src URL> defaults to '%s'" % path_srcurl
	else:
		print "<local repo path> <src URL>"

def main(argv):
	global path_svnrepo, path_srcurl

	print """svnpull.py
Subversion push-based repository "client"
Copyright (C)2003 Dan Potter
"""

	# Make sure we're called with enough parameters
	if path_svnrepo is None:
		if len(argv) < 3:
			help()
			sys.exit(-1)
		else:
			# Set our globals
			path_svnrepo = argv[1]
			path_srcurl = argv[2]
	else:
		if len(argv) > 1 and len(argv) < 3:
			help()
			sys.exit(-1)

	# Fill in the defaults in svnpush.py that we use as a module.
	svnpush.path_svnrepo = path_svnrepo

	print "Repo at %s, source at %s" % (path_svnrepo, path_srcurl)

	# Find the latest revision of the local repo (and also verify its
	# integrity)
	print "Finding latest local revision."
	lv = svnpush.getLatestRevision()

	print "Verified repository integrity, latest revision is %d." % lv

	# Get the latest URL target revision
	print "Finding latest public revision."
	pv, ptype = urlLatestRevision()

	print "Latest public revision is %d/%s." % (pv, ptype)

	if lv > pv:
		print "ERROR: Somehow the local repo is past the public one!"
		sys.exit(-1)
	if lv == pv:
		print "Local repo is up to date."
		sys.exit(0)

	# Do we need to do a full import first?
	if lv == 0:
		fpv = urlLatestFullRevision()
		print "Local repo is completely empty, importing full dump %d." % fpv
		urlLoadRevision(fpv, 'full')
		lv = fpv

	print "Full repo is now to %d." % lv

	# Do incrementals if necessary
	if lv < pv:
		print "Applying incrementals..."

	while lv < pv:
		lv = lv + 1
		try:
			urlLoadRevision(lv, 'incr')
		except urllib2.HTTPError:
			print "Couldn't get incremental %d -- perhaps your repo is too old?" % lv
			print "If you have no local data in it, try deleting your repo and"
			print "creating it again with 'svnadmin create'."
			sys.exit(-1)

	print "Repo is now patched to %d." % lv

	print "Done."
	return 0

if __name__=='__main__':
	sys.exit(main(sys.argv))
