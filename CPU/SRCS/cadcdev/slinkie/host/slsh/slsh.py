#!/usr/bin/env python

# Slinkie Shell Host Tool 1.0
# Copyright (C)2003,2004 Dan Potter
#
# This program is distributed under Slinkie's BSD-like license. However, you
# should be aware that it can't be distributed as-is in any sort of
# compiled binary-only format (unless source is included) because its
# inclusion of the 'readline' module introduces the restrictions of the
# GPL. If you don't like this, remove the readline stuff.
#
# Note: This requires Python 2.2 or higher.
#

import os, readline, atexit, sys, socket, string, errno, thread, stat, time
import random

VERSION = 'slsh 1.0'
PORT = 31313

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


# This class handles network connections
class Net:
	def __init__(self, host = None, port = PORT):
		self.ip = None
		self.port = None
		if host:
			connect(host, port)
		self.serial_hi = -1
		self.slinkie = 0
		self.timeout = 0.5
		self.lastRecvTimeout = 0
		self.inSlaveMode = 0

		self.dirs = { }
		self.dirPos = { }

	##############################################################
	# Console

	# XXX Use termcap/curses
	def msg(self, msg):
		if self.inSlaveMode:
			print "\x1b[1m%s\x1b[0m" % msg
		else:
			print msg

	##############################################################
	# Utils

	# Pack an integer into a DC byte-order dword byte array.
	def htodcl(num):
		return chr((num >> 0) & 0xff) + \
			chr((num >> 8) & 0xff) + \
			chr((num >> 16) & 0xff) + \
			chr((num >> 24) & 0xff)
	htodcl = staticmethod(htodcl)

	# Pack an integer into a network byte-order dword byte array.
	def htonl(num):
		return chr((num >> 24) & 0xff) + \
			chr((num >> 16) & 0xff) + \
			chr((num >> 8) & 0xff) + \
			chr((num >> 0) & 0xff)
	htonl = staticmethod(htonl)

	# Pack a short integer into a network byte-order word byte array.
	def htons(num):
		return chr((num >> 8) & 0xff) + \
			chr((num >> 0) & 0xff)
	htons = staticmethod(htons)

	# Unpack a network word byte array into a short integer.
	def ntohs(arr):
		return long((ord(arr[0]) << 8) | \
			ord(arr[1]))
	ntohs = staticmethod(ntohs)

	# Unpack a network dword byte array into an integer.
	def ntohl(arr):
		return (long(ord(arr[0])) << 24) | \
			(long(ord(arr[1])) << 16) | \
			(long(ord(arr[2])) << 8) | \
			long(ord(arr[3]))
	ntohl = staticmethod(ntohl)

	# Take a received (or about to be sent) packet and do a nice
	# hex/ascii dump on stdout.
	def dumpPacket(self, packet):
		a = list(packet)
		cnt = 0
		hex = ""
		asc = ""
		for i in a:
			hex = hex + "%02x " % ord(i)
			if ord(i) >= 32 and ord(i) <= 127:
				asc = asc + i
			else:
				asc = asc + "."

			cnt = cnt + 1
			if cnt >= 16:
				self.msg("%s %s" % (hex,asc))
				hex = ""
				asc = ""
				cnt = 0
		if cnt > 0:
			self.msg("%s%s %s" % (hex, " "*(3*(16-cnt)), asc))

	# Make a tas packet to send to the target
	def makeTas(type, addr = 0, size = 0, payload = ""):
		return type + \
			Net.htonl(addr) + \
			Net.htonl(size) + \
			payload
	makeTas = staticmethod(makeTas)

	# Split a tas packet from the target into its components
	def parseTas(packet):
		type = packet[:4]
		addr = Net.ntohl(packet[4:8])
		size = Net.ntohl(packet[8:12])
		payload = packet[12:]
		return (type, addr, size, payload)
	parseTas = staticmethod(parseTas)

	# Do a pretty dump of a parsed tas packet.
	def dumpTas(self, tas):
		self.msg("Type:    %s" % tas[0])
		self.msg("Address: %08x" % tas[1])
		self.msg("Size:    %08x" % tas[2])
		if len(tas[3]):
			self.msg("Payload, size %d:" % len(tas[3]))
			self.dumpPacket(tas[3])

	# Takes a C string and truncates at the first null
	def strTrunc(s):
		w = string.find(s, chr(0))
		if w == -1:
			return s
		return s[:w]
	strTrunc = staticmethod(strTrunc)

	# Split a 3i packet from the target into its components
	def parse3i(packet):
		type = packet[:4]
		i0 = Net.ntohl(packet[4:8])
		i1 = Net.ntohl(packet[8:12])
		i2 = Net.ntohl(packet[12:16])
		if len(packet) >= 20:
			i3 = Net.ntohl(packet[16:20])
		else:
			i3 = -1
		return (type, i0, i1, i2, i3)
	parse3i = staticmethod(parse3i)

	# Split a 2is packet
	def parse2is(packet):
		type = packet[:4]
		i0 = Net.ntohl(packet[4:8])
		i1 = Net.ntohl(packet[8:12])
		s = Net.strTrunc(packet[12:])
		return (type, i0, i1, s)
	parse2is = staticmethod(parse2is)

	# Split an i packet
	def parsei(packet):
		type = packet[:4]
		i0 = Net.ntohl(packet[4:8])
		return (type, i0)
	parsei = staticmethod(parsei)

	# Split an s packet
	def parses(packet):
		type = packet[:4]
		s = Net.strTrunc(packet[4:])
		return (type, s)
	parses = staticmethod(parses)

	##############################################################
	# Protocol actions

	# Receive a packet from the socket with the specified timeout.
	# If timeout is None, then there is no timeout. On success the
	# packet will be returned; None will be returned on failure.
	def recv(self, timeout = 1):
		if self.lastRecvTimeout != timeout:
			# Set the timeout
			if timeout:
				self.sock.settimeout(self.timeout)
			else:
				self.sock.settimeout(None)
			self.lastRecvTimeout = timeout

		# Wait for the packet
		try:
			rv = self.sock.recv(1500)
		except socket.timeout:
			rv = None

		return rv

	# Send a packet to the target, expecting a response. If the response
	# is not registered within the timeout, the request is sent again.
	def sendRequest(self, pkt, expecting):
		# Wait for a response, with timeout.
		msg = None
		while msg is None:
			# Send the packet.
			self.sock.send(pkt)

			msg = self.recv()
			if msg is not None:
				if msg[:4] != expecting:
					msg = None

		# Return what we got so we can process it.
		return msg

	# Receive a stream of SBIN/SBIQ/DBIN packets. Pass in the initial
	# received SBIN packet as well as the address and size of the
	# request. This will handle all retry processing.
	def processSbin(self, addr, size, pkt):
		# Figure out the total number of packets.
		pktcnt = size / 1024
		if size % 1024:
			pktcnt = pktcnt + 1

		# This map will store the packets we've actually received,
		# for retries. The results will be concatenated on completion
		# for the final buffer.
		pktmap = { }

		# This internal function will parse and handle one packet.
		def processPkt(pkt, pktmap, addr):
			# Parse one packet.
			pkt = Net.parseTas(pkt)

			# self.msg("Recv %s: %08x %d" % (pkt[0], pkt[1], pkt[2]))

			# Is this a DBIN? If so, drop out.
			if pkt[0] == "DBIN":
				return 1
			if pkt[0] != "SBIN" and pkt[0] != "SBIQ":
				self.msg("Unexpected packet '%s' during SBIN" % pkt[0])
				return 0

			# Figure out the offset of this packet.
			offs = pkt[1] - addr
			pktnum = offs / 1024
			# self.msg("offs %08x = pkt[1] %08x - addr %08x" % (offs, pkt[1], addr))

			# Patch it into the map.
			# self.msg("Saving as pktnum %d" % pktnum)
			pktmap[pktnum] = pkt[3]

			return 0

		# Go until we see a DBIN...
		while 1:
			# Process this packet.
			if processPkt(pkt, pktmap, addr):
				break

			# Receive the next packet. If we time out, assume
			# we missed the final DBIN packet.
			pkt = self.recv(None)
			if pkt is None: break

		# Ok, look and see if we are missing anything.
		while 1:
			missing = 0
			for i in range(pktcnt):
				if not pktmap.has_key(long(i)):
					self.msg("Re-requesting packet %d" % i)

					# Request a re-transmit.
					offs = addr + i*1024
					pktsize = 1024
					if (offs+pktsize) > (addr+size):
						pktsize = size - offs
					resp = self.sendRequest(Net.makeTas("SBIN", offs, pktsize), "SBIN")

					# The DBIN should be next.
					dbin = self.recv(None)

					# Process the SBIN.
					processPkt(resp, pktmap, addr)

					missing = 1
			if not missing: break

		# Finally, patch it all together into a coherent buffer.
		# We can't just concat all the strings here because that is
		# actually over an order of magnitude slower(!). Using this
		# method the receive of large buffers rivals that of the
		# C dc-tool program.
		buffer = [ ]
		for i in range(pktcnt):
			buffer.append(pktmap[i])
		buffer = string.join(buffer, "")

		return buffer

	# Receive a stream of LBIN/PBIN/DBIN packets. Pass in the address
	# and size of the request. This will handle all retry processing.
	def processLbin(self, addr, size, buffer):
		# Break the input data into packet-sized chunks.
		pkts = [ ]
		if len(buffer) % 1024:
			pktcnt = len(buffer) / 1024 + 1
		else:
			pktcnt = len(buffer) / 1024
		for i in range(pktcnt):
			pkts.append(buffer[i*1024:(i+1)*1024])

		ptr = addr
		for i in pkts:
			# Send the packet
			pkt = Net.makeTas("PBIN", ptr, len(i), i)
			self.sock.send(pkt)

			# Move our pointer
			ptr = ptr + len(i)

		# Finish up retries...
		while 1:
			# Send out the final DBIN and wait for a response.
			resp = self.sendRequest(Net.makeTas("DBIN"), "DBIN")
			resp = Net.parseTas(resp)

			# Do we need any re-transmits?
			if resp[1] == 0:
				break
			else:
				# Re-send the requested packet
				offs = (resp[1] - addr) / 1024
				# self.msg("Re-sending packet %d (%08x)" % (offs, resp[1]))
				pkt = pkts[offs]
				pkt = Net.makeTas("PBIN", resp[1], len(pkt), pkt)
				self.sock.send(pkt)
		
	# Ask the target to identify its version
	def getVersion(self):
		# Request the target version.
		resp = self.sendRequest(Net.makeTas("VERS"), "VERS")
		resp = Net.parseTas(resp)

		# If it's slinkie then note that for protocol extensions.
		slst = "Slinkie"
		if resp[3][:len(slst)] == slst:
			self.slinkie = 1

		self.msg("Client is running %s." % resp[3])
		if self.slinkie:
			self.msg("Slinkie extensions ENABLED.")
		else:
			self.msg("Slinkie extensions DISABLED.")

		return resp[3]

	# Ask the target to reboot
	def reboot(self):
		resp = self.sendRequest(Net.makeTas("RBOT"), "RBOT")
		self.dumpPacket(resp)

	# Ask the target to send us binary data
	def sendBin(self, addr, size):
		# Request a transfer.
		resp = self.sendRequest(Net.makeTas("SBIQ", addr, size), "SBIN")
		buffer = self.processSbin(addr, size, resp)
		return buffer

	# Load binary data into the target's RAM.
	def loadBin(self, addr, data):
		# Request a transfer.
		size = len(data)
		resp = self.sendRequest(Net.makeTas("LBIN", addr, size), "LBIN")

		# Complete the transfer.
		self.processLbin(addr, size, data)

	# Begin target execution.
	def execute(self, addr, cons):
		# Request a transfer.
		if cons:
			size = 1
		else:
			size = 0
		resp = self.sendRequest(Net.makeTas("EXEC", addr, size), "EXEC")

		if cons:
			self.slaveMode()

	##############################################################
	# Host slave mode

	def cmdEXIT(self, pkt):
		# Response required only in Slinkie protocol.
		if self.slinkie:
			self.sock.send(Net.makeTas("EXIT"))

		return 1

	def cmdFDWR(self, pkt):
		# Parse the packet
		pkt = Net.parse3i(pkt)

		# Pull out the pieces we care about
		fd = pkt[1]
		addr = pkt[2]
		size = pkt[3]

		# Read the data from the target
		data = self.sendBin(addr, size)

		# Write it out
		try:
			rv = os.write(fd, data)
		except OSError:
			rv = -1

		# ACK the whole operation
		self.sendRequest(Net.makeTas("RETV", rv), "RETV")

	def cmdFDRD(self, pkt):
		# Parse the packet
		pkt = Net.parse3i(pkt)

		# Pull out the pieces we care about
		fd = pkt[1]
		addr = pkt[2]
		size = pkt[3]

		# Read data from the fd
		try:
			data = os.read(fd, size)
			rv = len(data)
		except OSError:
			rv = -1

		# Write it back to the target
		if rv >= 0:
			self.loadBin(addr, data)

		# ACK the whole operation
		self.sendRequest(Net.makeTas("RETV", rv), "RETV")

	def cmdFDOP(self, pkt):
		# Parse the packet
		pkt = Net.parse2is(pkt)

		# Pull the pieces we care about
		fn = pkt[3]
		flags = pkt[1]

		# Try to open it
		try:
			rv = os.open(fn, flags)
		except OSError:
			rv = -1

		# ACK
		self.sendRequest(Net.makeTas("RETV", rv), "RETV")

	def cmdFDCL(self, pkt):
		# Parse the packet
		pkt = Net.parsei(pkt)

		# Pull out the pieces we care about
		fd = pkt[1]

		# Try to close it
		try:
			os.close(fd)
			rv = 0
		except OSError:
			rv = -1

		# ACK
		self.sendRequest(Net.makeTas("RETV", rv), "RETV")

	def cmdFDSE(self, pkt):
		# Parse the packet
		pkt = Net.parse3i(pkt)

		# Pull out the pieces we care about
		fd = pkt[1]
		amt = pkt[2]
		whence = pkt[3]

		# Try to seek it
		try:
			rv = os.lseek(fd, amt, whence)
		except OSError:
			rv = -1

		# ACK
		self.sendRequest(Net.makeTas("RETV", rv), "RETV")

	def cmdSTAT(self, pkt):
		# Parse the packet
		pkt = Net.parse2is(pkt)

		# Pull the pieces we care about
		fn = pkt[3]
		addr = pkt[1]
		size = pkt[2]

		# Do the stat
		try:
			sto = os.stat(fn)
			st = chr(0)*4 + Net.htodcl(sto.st_mode) + \
				chr(0)*8 + Net.htodcl(sto.st_size) + \
				chr(0)*8 + Net.htodcl(sto.st_mtime) + \
				chr(0)*7*4
			rv = 0
		except OSError:
			st = None
			rv = -1

		# Write out the response, if necessary
		if st is not None:
			self.loadBin(addr, st)

		# ACK
		self.sendRequest(Net.makeTas("RETV", rv), "RETV")

	def cmdDROP(self, pkt):
		# Parse the packet
		fn = Net.parses(pkt)[1]

		# Read the directory listing.
		try:
			listing = os.listdir(fn)

			# Store the listing internally for read/close cmds.
			hnd = random.randint(1,10000)
			self.dirs[hnd] = listing
			self.dirPos[hnd] = 0
		except OSError:
			hnd = 0

		# ACK
		self.sendRequest(Net.makeTas("RETV", hnd), "RETV")

	def cmdDRRD(self, pkt):
		# Parse the packet
		pkt = Net.parse3i(pkt)

		# Pull out the pieces we care about
		hnd = pkt[1]
		addr = pkt[2]
		size = pkt[3]

		# Is there anything left?
		listing = self.dirs[hnd]
		if self.dirPos[hnd] >= len(listing):
			de = None
			rv = 0
		else:
			# Build up a "dirent"
			de = chr(0) * 11 + listing[self.dirPos[hnd]] + chr(0)
			self.dirPos[hnd] = self.dirPos[hnd] + 1
			rv = 1

		# Write out the response, if necessary
		if de is not None:
			self.loadBin(addr, de)

		# ACK
		self.sendRequest(Net.makeTas("RETV", rv), "RETV")

	def cmdDRCL(self, pkt):
		# Parse the packet
		pkt = Net.parsei(pkt)

		# Pull out the pieces we care about
		hnd = pkt[1]

		# Remove it from the table
		del self.dirs[hnd]
		del self.dirPos[hnd]

		# ACK
		self.sendRequest(Net.makeTas("RETV"), "RETV")

	# dcload-ip aliases
	def cmdDC00(self, pkt): return self.cmdEXIT(pkt)
	def cmdDD02(self, pkt): return self.cmdFDWR(pkt)
	def cmdDC03(self, pkt): return self.cmdFDRD(pkt)
	def cmdDC04(self, pkt): return self.cmdFDOP(pkt)
	def cmdDC05(self, pkt): return self.cmdFDCL(pkt)
	def cmdDC11(self, pkt): return self.cmdFDSE(pkt)
	def cmdDC13(self, pkt): return self.cmdSTAT(pkt)
	def cmdDC16(self, pkt): return self.cmdDROP(pkt)
	def cmdDC17(self, pkt): return self.cmdDRCL(pkt)
	def cmdDC18(self, pkt): return self.cmdDRRD(pkt)

	# The main host slave mode loop. Called after execute() and
	# will return when we've received a final EXIT command.
	def slaveMode(self):
		self.inSlaveMode = 1
		self.msg("Entering slave mode.")

		# The main loop: receive packets until EXIT...
		while 1:
			# Get a packet (no timeout)
			pkt = self.recv(None)

			# Figure out the packet type
			tag = pkt[:4]

			# Do we have a method for that?
			try:
				func = getattr(self, "cmd" + tag)
			except AttributeError:
				self.msg("Received unknown command '%s'" % tag)
				continue

			# Call it to handle the packet.
			if func(pkt):
				break

		# We're all done.
		self.msg("Exiting slave mode.")
		self.inSlaveMode = 0

	##############################################################
	# Low level

	# What's our connected peer?
	def getPeer(self):
		return (self.ip, self.port)

	# Establish a connection with the target
	def connect(self, host, port = PORT, versionChk = 1):
		# Look up the name (if any)
		try:
			host = socket.gethostbyname(host)
		except socket.error:
			print "Can't find hostname '%s'" % host
			return None

		try:
			s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		except socket.error:
			print "Warning: Can't make socket"
			
		try:
			s.connect((host,port))
		except socket.error:
			print "Can't connect to host"
			return None

		self.sock = s
		self.ip = host
		self.port = port

		if versionChk:
			print "Trying %s:%d..." % (host, port)
			return self.getVersion()
		else:
			return 1


# This class will handle all command line processing
class CommandProcessor:
	def __init__(self):
		self.net = None
	usages = { }

	#############################################
	usages["version"] = """
version
Queries the target for its monitor version and prints the results. Also
checks to see if we can use Slinkie protocol extensions.
"""
	def doVersion(self, cmd):
		self.net.getVersion()

	#############################################
	usages["download"] = """
download <filename> <size> [addr]
Downloads data from the target's RAM into a file. Size is in bytes and addr
is an absolute target RAM address (hex numbers like 0x8c010000 are ok).
"""
	def doDownload(self, cmd):
		args = string.split(cmd)

		start = time.time()
		result = self.net.sendBin(long(args[1], 0), long(args[2], 0))
		finish = time.time()
		elapsed = finish - start

		f = open(args[3], "wb")
		f.write(result)
		f.close()
		print "%d bytes downloaded to '%s' in %.2f sec (%.2f bytes/sec)" % (len(result), args[3], elapsed, len(result)/elapsed)

	#############################################
	usages["upload"] = """
upload <filename> [addr]
Uploads data to the target's RAM from a file. Addr is an absolute target RAM
address (hex numbers like 0x8c010000 are ok).
"""
	def doUpload(self, cmd):
		args = string.split(cmd)

		f = open(args[1], "rb")
		data = f.read()
		f.close()

		if len(args) < 3:
			addr = 0x8c010000L
		else:
			addr = long(args[2], 0)

		start = time.time()
		self.net.loadBin(addr, data)
		finish = time.time()
		elapsed = finish - start

		print "%d bytes uploaded from '%s' in %.2f sec (%.2f bytes/sec)" % (len(data), args[1], elapsed, len(data)/elapsed)

	#############################################
	usages["exec"] = """
exec [console [addr]]
Starts the target executing code at the given address. Addr is an absolute
target RAM address, and defaults to 0x8c010000. If a non-zero value is passed
for 'console' then the file / stdin / stdout console will be active.
"""
	def doExec(self, cmd):
		args = string.split(cmd)

		cons = int(args[1])
		if len(args) == 3:
			addr = long(args[2], 0)
		else:
			addr = 0x8c010000L

		print "Execution started at %08x." % addr

		self.net.execute(addr, cons)

	#############################################
	usages["slave"] = """
slave
Places slsh into slave mode immediately. This is useful mainly if slsh has
crashed (or you want to exit it and start it up again later without stopping
the target program).
"""
	def doSlave(self, cmd):
		# This isn't super useful yet...
		self.net.slaveMode()

	#############################################
	usages["reboot"] = """
reboot
Reboots the target. If the monitor is dcload-ip, this will simply reset
dcload-ip, otherwise it will actually reboot the target machine.
"""
	def doReboot(self, cmd):
		self.net.reboot()

	#############################################
	usages["connect"] = """
connect <target IP> [target port]
Connects to a target on the given IP and port. Port defaults to 31313.
"""
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
		self.net = Net()
		if self.net.connect(target) is None:
			self.net = None

	#############################################
	usages["help"] = """
help [command]
Prints out a list of commands and/or help on a specific command. You proably
already know this by now though.
"""
	def doHelp(self, cmd):
		args = string.split(cmd)
		if len(args) != 2:
			self.usage(None)
		else:
			self.usage(args[1])

	#############################################
	usages["quit"] = """
quit
Quit slsh. Command history will be saved in ~/.slshhistory.
"""
	def usage(self, cmd):
		if cmd is None:
			print "Available commands:"
			print string.join(self.usages.keys(), ", ")
		else:
			if self.usages.has_key(cmd):
				print self.usages[cmd]
			else:
				print "Unknown command '%s'" % cmd

	# XXX use termcap/curses
	def getPrompt(self):
		colors = {
			'def': "\x1b[0m",
			'white': "\x1b[1m",
			'cyan': "\x1b[0;36m",
			'green': "\x1b[0;32m",
			'yellow': "\x1b[1;33m"
		}
		if self.net:
			host, port = self.net.getPeer()
			p = "%sslsh%s:%s%s%s:%s%d%s" % \
				(colors['white'],
				colors['green'],
				colors['cyan'],
				host,
				colors['green'],
				colors['cyan'],
				port,
				colors['def'])
		else:
			p = "slsh"

		return p

def main():
	print "Slinkie IP Debug Host Tool 1.0"
	print "Copyright (C)2003,2004 Dan Potter"
	print ""

	# Initialize readline
	histfile = os.path.join(os.environ["HOME"], ".slshhist")
	try:
		readline.read_history_file(histfile)
	except IOError:
		pass

	# Read the user's config, if it exists
	global conf
	conffile = os.path.join(os.environ["HOME"], ".slshrc")
	conf = Config()
	conf.load(conffile)

	# Spawn off a file server thread
	srv = Net()
	#thread.start_new_thread(srv.serve, ())

	# Create a command processor object
	cmdproc = CommandProcessor()

	# Are we auto-connecting?
	if conf.autoConnect:
		cmdproc.doConnect("connect")

	# Our main command loop
	while 1:
		# What's our prompt?
		cmdprompt = cmdproc.getPrompt()

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
	sys.exit(main())
