#!/usr/bin/env python

# KOS IP Debug Host Tool 1.0
# Copyright (C)2003 Dan Potter
#
# This program is distributed under KOS' BSD-like license. However, you
# should be aware that it can't be distributed as-is in any sort of
# compiled binary-only format (unless source is included) because its
# inclusion of the 'readline' module introduces the restrictions of the
# GPL. If you don't like this, remove the readline stuff.
#

import os, readline, atexit, sys, socket, string, errno, thread, stat

VERSION = 'kos-tool 1.0'
CPORT = 6300
FPORT = 6301

# List of server sockets, so we can close them if the program has an untimely
# demise.
servsocks = [ ]

# Configuration class. This class handles loading the user config file.
class Config:
	def __init__(self):
		self.targetHost = None
		self.targetPort = None
		self.autoConnect = 0

	def load(self, fn):
		try:
			f = open(fn, "rb")
		except IOError:
			print "Can't open config file '%s'... I recommend making one." % fn
			return None

		while 1:
			line = f.readline()
			if line == '': break
			
			line = string.strip(line)
			if len(line) == 0 or line[0] == '#':
				continue

			tokens = string.split(line)
			if tokens[1] != '=':
				print "Malformed line '%s' in config" % line
				continue

			tokens[0] = string.lower(tokens[0])
			if tokens[0] == 'host':
				self.targetHost = tokens[2]
			elif tokens[0] == 'port':
				self.targetPort = tokens[2]
			elif tokens[0] == 'autoconnect':
				if tokens[2] == 'yes':
					self.autoConnect = 1
			else:
				print "Unknown setting '%s' in config" % tokens[0]

		print "Read config from %s" % fn

		return 1

# Handles the fserv file connections
class FServer:
	def __init__(self, conn):
		self.conn = conn

	def normpath(self, p):
		if p[0] == '/':
			p = p[1:]
		if os.sep != '/':
			p = string.replace(p, '/', os.sep)

		return p

	def doOpen(self, s):
		# Split up our args
		p = string.split(s)
		if len(p) != 3:
			self.conn.writeline("Error: %d" % errno.EINVAL)
			return

		# Fix the filename
		p[1] = self.normpath(p[1])

		# Convert file modes. This must be kept in sync with
		# KOS' <kos/fs.h>.
		kmode = int(p[2])
		umode = 0
		if kmode & 7 == 2:
			umode = os.O_RDWR
		elif kmode & 7 == 3:
			umode = os.O_APPEND | os.O_RDWR
		elif kmode & 7 == 4:
			umode = os.O_WRONLY
		if kmode & 0x0100:
			umode = umode | os.O_TRUNC
		umode = umode | os.O_CREAT

		# For Windows/Mac
		if hasattr(os, "O_BINARY"):
			umode = umode | os.O_BINARY

		# Try to open the file
		try:
			f = os.open(p[1], umode)
		except OSError, x:
			self.conn.writeline("Error: %d" % x.errno)
			return

		# Return success
		self.conn.writeline("Ok: %d" % f)

	def doClose(self, s):
		# Split up our args
		p = string.split(s)
		if len(p) != 2:
			self.conn.writeline("Error: %d" % errno.EINVAL)
			return

		# Close the file
		try:
			os.close(int(p[1]))
		except OSError:
			pass

		self.conn.writeline("Ok: no error")

	def doRead(self, s):
		# Split up our args
		p = string.split(s)
		if len(p) != 3:
			self.conn.writeline("Error: %d" % errno.EINVAL)
			return

		fd = int(p[1])
		amt = int(p[2])

		# Attempt the read
		try:
			block = os.read(fd, amt)
		except OSError, x:
			self.conn.writeline("Error: %d" % x.errno)
			return

		# Tell the client it's ok
		self.conn.writeline("Ok: %d" % len(block))

		# Write it out
		self.conn.writechunk(block)

	def doWrite(self, s):
		# Split up our args
		p = string.split(s)
		if len(p) != 3:
			self.conn.writeline("Error: %d" % errno.EINVAL)
			return

		fd = int(p[1])
		amt = int(p[2])

		# Read the data chunk
		block = self.conn.readchunk(amt)

		# Attempt the write
		try:
			amt = os.write(fd, block)
		except OSError, x:
			self.conn.writeline("Error: %d" % x.errno)
			return

		# Tell the client it's ok
		self.conn.writeline("Ok: %d" % amt)

	def doSeek(self, s):
		# Split up our args
		p = string.split(s)
		if len(p) != 4:
			self.conn.writeline("Error: %d" % errno.EINVAL)
			return

		fd = int(p[1])
		loc = int(p[2])
		which = int(p[3])

		# Attempt the seek
		try:
			rv = os.lseek(fd, loc, which)
		except OSError, x:
			self.conn.writeline("Error: %d" % x.errno)
			return

		# Give the client the return value
		self.conn.writeline("Ok: %d" % rv)

	def doTotal(self, s):
		# Split up our args
		p = string.split(s)
		if len(p) != 2:
			self.conn.writeline("Error: %d" % errno.EINVAL)
			return

		fd = int(p[1])

		# Attempt the operation
		try:
			cp = os.lseek(fd, 0, 1)		# SEEK_CUR
			rv = os.lseek(fd, 0, 2)		# SEEK_END
			os.lseek(fd, cp, 0)		# SEEK_SET
		except OSError, x:
			self.conn.writeline("Error: %d" % x.errno)
			return

		# Give the client the return value
		self.conn.writeline("Ok: %d" % rv)

	def doListDir(self, s):
		# Split up our args
		p = string.split(s)
		if len(p) != 2:
			self.conn.writeline("Error: %d" % errno.EINVAL)
			return

		# Normalize the path
		p = self.normpath(p[1])
		if p == "": p = "."

		# Get a list of the contents
		try:
			conts = os.listdir(p)
		except OSError, x:
			self.conn.writeline("Error: %d" % x.errno)
			return

		# Notify the client
		self.conn.writeline("Ok: %d" % len(conts))

		# For each entry...
		for i in conts:
			# Is it a dir or file?
			try:
				st = os.stat(os.path.join(p, i))
				if stat.S_ISDIR(st[stat.ST_MODE]):
					size = -1
				else:
					size = st[stat.ST_SIZE]
			except OSError:
				# Assume file
				size = 0

			self.conn.writeline("%s/%d" % (i, size))

	def loop(self):
		while 1:
			# Read a line of input
			s = self.conn.readline()

			# Parse out the command piece
			cmd = string.split(s)[0]

			if cmd == 'Open:':
				self.doOpen(s)
			elif cmd == 'Close:':
				self.doClose(s)
			elif cmd == 'Read:':
				self.doRead(s)
			elif cmd == 'Write:':
				self.doWrite(s)
			elif cmd == 'Seek:':
				self.doSeek(s)
			elif cmd == 'Total:':
				self.doTotal(s)
			elif cmd == 'ListDir:':
				self.doListDir(s)
			elif cmd == 'Quit':
				break
			else:
				self.conn.writeline("Error: unknown command")


# This class handles network connections
class NetConnect:
	def __init__(self, host = None, port = CPORT):
		self.ip = None
		self.port = None
		if host:
			connect(host, port)

	##############################################################
	# Client protocol actions

	# Do the target/host handshake protocol and verify that we're compatible.
	# Used during connect().
	def clientHandshake(self):
		# Read the client's version code
		vers = self.readline()

		# Send our version code
		self.writeline("Ok: %d %s" % (FPORT, VERSION))
		
		print "Connected. Client is '%s'." % vers

		return 1

	# Send a file to the target's ramdisk.
	def sendfile(self, src, target):
		# Open the file
		try:
			f = open(src, "rb")
		except IOError:
			print "Can't open source file '%s'" % src
			return None

		# How big is it?
		f.seek(0, 2)
		size = f.tell()
		f.seek(0)
		
		# Tell the target we want to send.
		self.writeline("SendFile: %s %d" % (target, size))

		# Send in chunks
		while size > 0:
			block = f.read(256*1024)
			self.writechunk(block)
			size -= len(block)

		# Close the file
		f.close()

		# Read back the client response
		resp = self.readline()
		print resp

		return 1

	# Execute a file on the taret
	def execute(self, target):
		# Tell the target we want to exec
		self.writeline("Run: %s" % target)

		# Get the response
		resp = self.readline()
		print resp

		return 1

	##############################################################
	# Low level

	# What's our connected peer?
	def getPeer(self):
		return (self.ip, self.port)

	# Bind to a server port and listen for connections
	def serve(self):
		global FPORT

		while 1:
			try:
				s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
				s.setsockopt(0, socket.SO_LINGER, 0)
				s.bind(('', FPORT))
				break
			except socket.error:
				print "Fserv: port %d taken, moving up" % FPORT
				FPORT = FPORT + 1
		print "Fserv thread listening on %d" % FPORT
		while 1:
			s.listen(1)
			conn, addr = s.accept()

			self.sock = conn
			self.ip = addr[0]
			self.port = addr[1]

			# Write out our ID
			self.writeline(VERSION)

			# Wait for the response
			resp = self.readline()

			print "Fserv connection active with %s:%d, id '%s'" % (self.ip,self.port, resp[4:])

			fserv = FServer(self)
			servsocks.append(fserv)
			fserv.loop()
			servsocks.remove(fserv)

			print "Fserv connection terminated."
			self.sock.close()
			self.sock = None


	# Establish a connection with the target
	def connect(self, host, port = CPORT):
		# Look up the name (if any)
		try:
			host = socket.gethostbyname(host)
		except socket.error:
			print "Can't find hostname '%s'" % host
			return None

		try:
			s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		except socket.error:
			print "Warning: Can't make socket"
			
		print "Trying %s:%d..." % (host, port)

		try:
			s.connect((host,port))
		except socket.error:
			print "Can't connect to host"
			return None

		self.sock = s
		self.ip = host
		self.port = port

		return self.clientHandshake()

	# Read a line of input from the client reliably
	def readline(self):
		# There's probably a better way, but I'm lazy...
		buf = ""
		while 1:
			c = self.sock.recv(1)
			if c != '\n':
				buf = buf + c
			else:
				break
		if buf[-1] == '\r':
			buf = buf[:-1]

		return buf

	# Write a line of output to the client reliably
	def writeline(self, line):
		line = line + "\r\n"
		self.writechunk(line)

	# Read a chunk of data from the client reliably
	def readchunk(self, amt):
		buf = ""

		while amt > 0:
			rd = self.sock.recv(amt)
			amt = amt - len(rd)
			buf = buf + rd

		return buf

	# Write a chunk of data to the client reliably
	def writechunk(self, data):
		while len(data) > 0:
			amt = self.sock.send(data)
			data = data[amt:]


# This class will handle all command line processing
class CommandProcessor:
	def __init__(self):
		self.net = None

	def doConnect(self, cmd):
		global conf

		args = string.split(cmd)
		if len(args) != 2:
			if not conf.targetHost:
				self.usage("connect")
				return
			else:
				target = conf.targetHost
		else:
			target = args[1]

		print "Attempting to connect to target %s..." % target
		self.net = NetConnect()
		if self.net.connect(target) is None:
			self.net = None

	def doSendfile(self, cmd):
		if not self.net:
			print "Not connected."
			return
	
		args = string.split(cmd)
		if len(args) < 2:
			self.usage("sendfile")
			return
		src = args[1]
		if len(args) > 2:
			target = args[2]
		else:
			target = os.path.basename(src)

		print "Uploading '%s' to '%s'..." % (src, target)
		self.net.sendfile(src, target)

	def doRun(self, cmd):
		if not self.net:
			print "Not connected."
			return
	
		args = string.split(cmd)
		if len(args) != 2:
			self.usage("run")
			return
		target = args[1]

		print "Executing '%s'..." % target
		self.net.execute(target)

	def doLoad(self, cmd):
		if not self.net:
			print "Not connected."
			return
	
		args = string.split(cmd)
		if len(args) != 2:
			self.usage("load")
			return
		target = args[1]

		print "Uploading '%s'..." % target
		self.net.sendfile(target, "run.elf")

		print "Executing..."
		self.net.execute("run.elf")

	def doHelp(self, cmd):
		self.usage(None)

	def usage(self, cmd):
		usages = {
			"connect": \
				"usage: connect <target IP>\n",
			"sendfile": \
				"usage: sendfile <source file> [dest filename]",
			"run": \
				"usage: run <target filename>" +
				"Note: assumes target is already uploaded.",
			"load": \
				"usage: load <source file>" +
				"Note: uploads _and_ runs source binary."
		}

		if cmd is None:
			print "Available commands:"
			print string.join(usages.keys(), ", ")
		else:
			print usages[cmd]


def main():
	print "KOS IP Debug Host Tool 1.0"
	print "Copyright (C)2003 Dan Potter"
	print ""

	# Initialize readline
	histfile = os.path.join(os.environ["HOME"], ".kostoolhist")
	try:
		readline.read_history_file(histfile)
	except IOError:
		pass

	# Read the user's config, if it exists
	global conf
	conffile = os.path.join(os.environ["HOME"], ".kostoolrc")
	conf = Config()
	conf.load(conffile)

	# Spawn off a file server thread
	srv = NetConnect()
	thread.start_new_thread(srv.serve, ())

	# Create a command processor object
	cmdproc = CommandProcessor()

	# Are we auto-connecting?
	if conf.autoConnect:
		cmdproc.doConnect("connect")

	# Our main command loop
	while 1:
		# What's our prompt?
		if cmdproc.net:
			cmdprompt = "kos-tool:%s:%d" % cmdproc.net.getPeer()
		else:
			cmdprompt = "kos-tool"

		# Get a line of input
		try:
			s = raw_input("%s> " % cmdprompt)
		except EOFError:
			print ""
			break

		# Skip blanks
		if len(string.strip(s)) == 0: continue

		# Parse out the command piece
		cmd = string.split(s)[0]
		if cmd == '?': cmd = "help"
		cmdname = "do" + string.capitalize(cmd)

		# Is it a quit request?
		if cmd == 'quit':
			break

		# Try to invoke it
		if not hasattr(cmdproc, cmdname):
			print "Unknown command '%s'" % cmd
			continue
		
		cmdfunc = getattr(cmdproc, cmdname)
		cmdfunc(s)

	# Write out the history file from readline
	try:
		readline.write_history_file(histfile)
	except IOError:
		print "Warning: couldn't write history file '%s'" % histfile

	return 0

if __name__=='__main__':
	try:
		sys.exit(main())
	except:
		for i in servsocks:
			i.conn.sock.close()
