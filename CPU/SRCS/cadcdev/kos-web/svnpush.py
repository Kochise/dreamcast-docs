#!/usr/bin/env python

# This script implements a very simple Subversion repository dump "push",
# which is a cheap (the only?) way to publically host Subversion without
# needing dedicated Apache support.
#
# Copyright (C)2003 Dan Potter
#

# Usage:
# svnpush.py <repo path> <output path> <output scp target>
#
# The repository at <repo path> will be queried for the latest version. If
# it is higher than what is available at <output scp target>, then each
# new version will be dumped as xxx_incr.dump.bz2, where xxx is the revision
# number. These files will be placed in <output path>. Once all new versions
# are dumped, these files will be uploaded to <output scp target> using
# scp, and the administrative files there (highest_full, highest_incr) will
# be updated.
#
# The repository MUST be accessed only by us while we're working on it.
# Subversion may handle this gracefully, and it may not. Your best bet is
# not to bet your data on it. To facilitate this, apache_initrc may be
# set in the config below to stop and start Apache 2 around the operations.
#

import popen2, sys, string, os, smtplib, time

#######################################################################
# Configuration

# Path to the 'svn' binary, or just 'svn' if it's in the PATH
svn_bin = 'svn'

# Path to the 'svnadmin' binary, or just 'svnadmin' if it's in the PATH
svnadmin_bin = 'svnadmin'

# Set to non-none if you want to auto stop and start Apache 2 around the
# operation (it must be stopped while you're running this script). The
# command will be run with a single parameter of 'start' or 'stop'.
apache_initrc = '/etc/init.d/apache2'

# Set this to a string if we should send out a notification email for each
# new revision to the repository. The string will be the email address
# to send messages to. If this feature is enabled, notify_from will
# set the "from" address as well. Note that in these strings the '#'
# character will be changed to '@', so that posting this script on
# a web page won't result in spam. notify_smtp is the server to use
# for sending messages.
notify_to = None
notify_from = None
notify_smtp = None

# Dan's config ;)
#notify_to = 'cadcdev-svn-commits#lists.sourceforge.net'
#notify_from = 'bard-dcdev#allusion.net'
#notify_smtp = 'localhost'

#######################################################################
# Implicit config globals, from cmdline. Set these to something besides
# None if you want to have parameter defaults. If you set one, you must
# set them all.

global path_svnrepo, path_output, path_scp

# path_svnrepo - path to the SVN repo we're working on
path_svnrepo = None

# path_output  - path to write incr files to
path_output = None

# path_scp     - scp target to compare against / update
path_scp = None

# Verify the defaulted parameters
try:
	if (path_svnrepo is not None) or (path_output is not None) \
			or (path_scp is not None):
		assert path_svnrepo is not None
		assert path_output is not None
		assert path_scp is not None
except AssertionError:
	print "Some parameters were defaulted, others were not."
	print "Please correct this in svnpush.py and try again."
	sys.exit(-1)

#######################################################################
# Version

# Modify this line if you fork the program, please.
version = 'SvnPush.py v1.0'

#######################################################################
# SVN Utility funcs

# Run svnadmin with the given parameters, and return the output as a tuple:
# (error code int, stdout string array, stderr string array). We assume
# here that the majority of the output we're concerned about will go onto
# stderr. If this turns out not to be true, a deadlock can happen.
def runSvnAdmin(cmd):
	# Spawn the process and get pipes
	p = popen2.Popen3(svnadmin_bin + ' ' + cmd, 1)

	# Read all of stderr first
	se = p.childerr.readlines()

	# Read all of stdout
	so = p.fromchild.readlines()

	# Get the return code
	rc = p.wait()

	# Return it all
	return (rc, so, se)
	

# Query an SVN repo for the latest available revision. We assume here that
# the root dir '/' is always updated whenever there is any commit. I believe
# this is always true.
#
# Older svnadmin versions had a nice "lscr" command, but that was removed
# for some inexplicable reason by 0.32.1, so we have to use verify (slow).
def getLatestRevision():
	# Do an svnadmin verify command on the repo
	rs = runSvnAdmin("verify " + path_svnrepo)
	if rs[0] != 0:
		print "svnadmin verify command failed with code %d" % rs[0]
		sys.exit(-1)

	# The last line of the stderr should be the version string.
	se = rs[2]
	if len(se) < 1:
		print "svnadmin verify failed:"
		print string.join(se, '\n')
		sys.exit(-1)
	vs = se[-1]

	# Make sure the format is comprehensible
	prefix = '* Verified revision '
	if vs[:len(prefix)] != prefix:
		print "svnadmin returned incomprehensible output:"
		print vs
		sys.exit(-1)

	# Should be in the form '* Verified revision xxx.'
	vs = string.strip(vs)
	vs = vs[len(prefix):-1]
	return int(vs)

# Dump one Subversion revision from the local repository. This uses
# 'svnadmin dump' and 'bzip2' to create the file.
def svnDumpRevision(rev):
	# Gruesome UNIX pipe :)
	cmd = "dump " + path_svnrepo + " -r %d:%d " % (rev,rev) \
		+ "--incremental | bzip2 -c > " \
		+ path_output + "/%d_incr.dump.bz2" % rev
	print "svnadmin " + cmd
	rs = runSvnAdmin(cmd)

	# Make sure it succeeded
	if rs[0] != 0:
		print "svnadmin verify command failed with code %d" % rs[0]
		sys.exit(-1)

#######################################################################
# SCP utility funcs

# Invoke scp to copy some files from src to dst.
def scpCopy(src, dst):
	# Run SCP with src and dst
	rv = os.system("scp '%s' '%s'" % (src, dst))

	# Return the return value
	return rv

# Copy up one revision to the scp target point.
def scpCopyRevision(rev):
	print path_output + "/%d_incr.dump.bz2" % rev,path_output+"/"
	rv = scpCopy(path_output + "/%d_incr.dump.bz2" % rev, path_scp+"/")
	if rv != 0:
		print "Couldn't copy rev %d to scp target (%d)" % (rev, rv)
		sys.exit(-1)


# Go out to the scp target point and grab highest_incr. Returns an integer
# with the highest publically available revision number.
def scpLatestRevision():
	# Pull down our push control file from the scp target loc.
	rv = scpCopy(path_scp + "/highest_incr", path_output + "/")
	if rv != 0:
		print "Couldn't retrieve highest_incr from scp target (%d)" % rv
		sys.exit(-1)

	# Read the data (should be a single number)
	f = open(path_output + "/highest_incr", "rb")
	val = int(string.strip(f.read()))
	f.close()

	return val

# Set a new revision on the scp target.
def scpSetRevision(rev):
	# Make a new revision code file
	f = open(path_output + "/highest_incr", "wb")
	f.write("%d\n" % rev)
	f.close()

	# Copy it up
	rv = scpCopy(path_output+"/highest_incr", path_scp+"/")
	if rv != 0:
		print "Couldn't update highest_incr to scp target (%d)" % rv
		sys.exit(-1)

#######################################################################
# Mail utilities

# Given a revision code, look up the dump file we created for that revision
# and ferret out the changelog message. Send this as an email to the
# target address. Assumes SVN dump format version 2.
def sendNotifyEmail(rev):
	# Load up the generated dump file
	fn = "%s/%d_incr.dump.bz2" % (path_output, rev)
	stdo, stdi = popen2.popen2("bzip2 -cd %s" % fn)
	data = stdo.read()
	stdi.close()
	stdo.close()

	# Find the log message. This is really wasteful for large dumps
	# but I don't really care :)
	w = string.find(data, "K 7\nsvn:log\nV ")
	if w == -1:
		print "Can't find log message in '%s'." % fn
		sys.exit(-1)
	w = w + len("K 7\nsvn:log\nV ")
	cnt = string.split(data[w:])
	cnt = int(cnt[0])
	w = w + len(str(cnt))
	while data[w] == '\r' or data[w] == '\n':
		w = w + 1
	logmsg = data[w:w+cnt]

	# Figure out the timezone poo (why is there no func for this...)
	tzoffs = -time.timezone / 3600
	if tzoffs < 0:
		tzstr = "-%04d" % (-tzoffs * 100)
	else:
		tzstr = "+%04d" % (tzoffs * 100)

	# Build up the message
	frommail = string.replace(notify_from, '#', '@')
	tomail = string.replace(notify_to, '#', '@')
	msg = "From: %s\r\n" % frommail
	msg = msg + "To: %s\r\n" % tomail
	msg = msg + "Subject: Repo revision %d\r\n" % rev
	msg = msg + "Date: %s\r\n" % time.strftime("%a, %d %b %Y %H:%M:%S " + tzstr)
	msg = msg + "User-Agent: %s\r\n" % version
	msg = msg + "\r\n"
	msg = msg + "A new revision has been checked into the Subversion repository.\r\n"
	msg = msg + "\r\n"
	msg = msg + "Revision %d:\r\n" % rev
	msg = msg + logmsg + "\r\n"
	msg = msg + "This message was generated by %s.\r\n" % version

	#print "----------------------------"
	#print "Sending SMTP message:"
	#print ""
	#print msg
	#print "----------------------------"

	# Send the message
	smtp = smtplib.SMTP(notify_smtp)
	smtp.sendmail(frommail, tomail, msg)
	smtp.quit()


#######################################################################
# Main

def help():
	global path_svnrepo, path_output, path_scp

	# Preamble is always the same
	print "usage: svnpush.py ",

	# Do we have defaults?
	if path_svnrepo is not None:
		print "[<local repo path> <dump output path> <scp target>]"
		print "<local repo path> defaults to '%s'" % path_svnrepo
		print "<dump output path> defaults to '%s'" % path_output
		print "<scp target> defaults to '%s'" % path_scp
	else:
		print "<local repo path> <dump output path> <scp target>"

def main(argv):
	global path_svnrepo, path_output, path_scp

	print """%s
Subversion push-based repository "server"
Copyright (C)2003 Dan Potter
""" % version

	# Make sure we're called with enough parameters
	if path_svnrepo is None:
		if  len(argv) < 4:
			help()
			sys.exit(-1)
		else:
			# Set our globals
			path_svnrepo = argv[1]
			path_output = argv[2]
			path_scp = argv[3]
	else:
		if len(argv) > 1 and len(argv) < 4:
			help()
			sys.exit(-1)

	print "Repo at %s, output at %s, scp at %s" \
		% (path_svnrepo, path_output, path_scp)

	# Find the latest revision of the local repo (and also verify its
	# integrity)
	print "Finding latest local revision."
	lv = getLatestRevision()

	print "Verified repository integrity, latest revision is %d." % lv

	# Get the latest scp target revision.
	print "Finding latest public revision."
	sv = scpLatestRevision()

	print "Latest public revision is %d." % sv

	if sv > lv:
		print "ERROR: Somehow the public repo is past the local one!"
		sys.exit(-1)
	if sv == lv:
		print "Public repo is up to date."
		sys.exit(0)

	# Ok, looks like we need to do something. For each missing revision,
	# do an svnadmin dump into a file we can upload.
	for i in range(sv+1, lv+1):
		print "Dumping revision %d." % i
		svnDumpRevision(i)
		print "Uploading revision %d." % i
		scpCopyRevision(i)

		if notify_to is not None:
			print "Sending notification email..."
			sendNotifyEmail(i)

	# Finally write out a new control file.
	print "Updating highest revision file."
	scpSetRevision(lv)

	print "Done."

	return 0

if __name__=='__main__':
	sys.exit(main(sys.argv))
