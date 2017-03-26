#!/usr/bin/env python

# A simple little script which takes the output of a "cvs status" command
# and parses it into a more usable format for a large number of files.
#
# (c)2002 Dan Potter
#
# $Id: vcheck.py,v 1.3 2002/10/26 08:03:18 bardtx Exp $
#

import sys, string, os, re

# Exclude any files which match these patterns
exclude_files = [
	".*elf", ".*bz2", ".*run.gdb", ".*romdisk.*img",
	".*environ.*"
]

def main():
	# Run cvs status and get the output
	p = os.popen("cvs status")
	# p = os.popen("cat test.txt")
	cvs_output = p.read()
	p.close()

	# Parse the output into lines
	lines = string.split(cvs_output, "\n")
	line_count = len(lines)

	# Get the unknown file names and remove them from the main list
	unknown_lines = filter(lambda x:len(x)>0 and x[0]=='?', lines)
	unknown_names = map(lambda x:x[2:], unknown_lines)
	lines = filter(lambda x,l=unknown_lines:x not in l, lines)
	assert ( len(lines) + len(unknown_lines) ) == line_count

	# Now seperate everything else into buckets
	buckets = [ ]
	cur_bucket = None
	for i in range(len(lines)):
		line = lines[i]
		if line[:4] == "====":
			if cur_bucket is not None:
				buckets.append(cur_bucket)
			cur_bucket = [ ]
		else:
			if len(line) > 0:
				cur_bucket.append(line)
	if len(cur_bucket) > 0:
		buckets.append(cur_bucket)

	print "Processed %d files" % ( len(buckets) + len(unknown_names) )

	# Now for each bucket, extract the filename and the version
	if len(unknown_names) > 0:
		files = { 'Unknown': unknown_names }
	else:
		files = { }
	for i in buckets:
		j = i[0]
		w = string.find(j, "Status:");
		assert w != -1
		status = j[w+8:]

		j = i[2]
		w = string.split(j, "\t")
		if len(w) == 3:
			file = w[2]
		else:
			file = string.split(i[0])[1]

		if files.has_key(status):
			files[status].append(file)
		else:
			files[status] = [ file ] 

	# Output a list of each file not in the Up-to-date status
	for i in files.keys():
		if i == "Up-to-date": continue
		print "Files with status '%s':" % i
		skipped_cnt = 0
		for j in files[i]:
			pas = 1
			for k in exclude_files:
				if re.compile(k).match(j, 1):
					pas = 0
			if pas:
				print "   %s" % j
			else:
				skipped_cnt = skipped_cnt + 1
		if skipped_cnt > 0:
			print "  (%d files excluded)" % skipped_cnt

main()

