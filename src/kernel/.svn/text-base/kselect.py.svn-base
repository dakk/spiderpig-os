# SpiderpigOS
# Copyright (C) 2009 - 2010 Davide Gessa
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import os
import sys


FS = 1
DRIVER = 2
CRYPTO = 3
SYSTEM = 4
NETWORK = 5
OTHER = 6
INPUT = 7
BUS = 8
VIDEO = 9
APP = 10
EXEC = 11
BLOCK = 12
CHAR = 13
	
# Type, Oggetti, nome, descrizione, dipendenze (nome), #define, architetture
content_list = [
				[INPUT, ["driver/input/keyboard.o"], "keyboard", "standard ps2 keyboard", [], ["DKEYBOARD"], ["x86"]],
				[INPUT, ["driver/input/mouse.o"], "mouse", "standard ps2 mouse", [], ["DMOUSE"], ["x86"]],

				[CHAR, ["driver/char/random.o"], "random", "random generator", [], ["DRANDOM"], ["all"]],

				#[DRIVER, ["video.o"], "video", "standard vga text", [], ["DVIDEO"], ["x86"]],
				[DRIVER, ["driver/smbios.o"], "smbios", "system managmet bios", [], ["DSMBIOS"], ["x86"]],
			
				[NETWORK, ["driver/net/ne2k.o"], "ne2k", "ne2k network family chip", [], ["DNE2K"], ["x86"]],
				[NETWORK, ["driver/net/rtl8139.o"], "rtl8139", "rtl8139 network family chip", [], ["DRTL8139"], ["x86"]],	
				[NETWORK, ["driver/net/modem.o"], "modem", "serial modem", ["rs232"], ["DMODEM"], ["x86"]],			
				[NETWORK, ["driver/net/rs232.o"], "rs232", "serial network standard", [], ["DRS232"], ["x86"]],
				
				[NETWORK, ["network/network.o", "network/socket.o", "network/packet.o", "network/net/ip.o", "network/route.o"], "network", "network stack", [], ["NETWORK"], ["all"]],
				[NETWORK, ["network/net/ipv4.o"], "ipv4", "ipv4 network protocol", ["network"], ["NIPV4", "IPV4"], ["all"]],
				[NETWORK, ["network/net/icmp.o"], "icmp", "icmp network protocol", ["network", "ipv4"], ["NICMP"], ["all"]],
				[NETWORK, ["network/link/arp.o"], "arp", "address resolution protocol", ["network", "ipv4"], ["NARP"], ["all"]],
				[NETWORK, ["network/link/eth.o"], "ethernet", "802.3 ethernet support", ["network"], ["NETH"], ["all"]],
				[NETWORK, ["network/link/bt.o"], "bt", "bluetooth", ["network"], ["NBT"], ["all"]],
				[NETWORK, ["network/link/ppp.o"], "ppp", "ppp modems support", ["network"], ["NPPP"], ["all"]],
				[NETWORK, ["network/link/wifi.o"], "wifi", "802.11 wifi support", ["network"], ["NWIFI"], ["all"]],
				[NETWORK, ["network/link/lo.o"], "lo", "loopback interface", ["network"], ["NLO"], ["all"]],
				[NETWORK, ["network/transp/tcp.o"], "tcp", "transport control protocol", ["ipv4", "network"], ["NTCP"], ["all"]],
				[NETWORK, ["network/transp/udp.o"], "udp", "protocol", ["ipv4", "network"], ["NUDP"], ["all"]],
				[NETWORK, ["network/app/dns.o"], "dns", "domain name resolving", ["ipv4"], ["NDNS"], ["all"]],
				
				[VIDEO, ["driver/video/vesa.o"], "vesa", "vesa video driver", [], ["DVESA", "VESA", "VBE"], ["x86"]],
				[VIDEO, ["driver/video/loadsplash/loadsplash.o", "driver/video/loadsplash/render.o"], "loadsplash", "loading splash screen", ["vesa", "initramfs"], ["LOADSPLASH"], ["x86"]],
				
				[BUS, ["driver/bus/pci/pci.o"], "pci", "peripheral component interconnect", [], ["DPCI", "PCI"], ["x86"]],
				[BUS, ["driver/bus/usb/usb.o"], "usb", "universal serial bus", [], ["DUSB", "USB"], ["x86"]],
				[BUS, ["driver/bus/isa/isa.o"], "isa", "isa bus", [], ["DISA", "ISA"], ["x86"]],
									
				[CRYPTO, ["driver/crypto/crc32.o"], "crc32", "crc checksum algorithm", [], ["CRC32"], ["all"]],
				[CRYPTO, ["driver/crypto/md5.o"], "md5", "md5 checksum algorithm", [], ["MD5"], ["all"]],

				[SYSTEM, ["mm/paged.o"], "paging", "paging system", [], ["MPAGING", "PAGING"], ["x86"]],					
				[SYSTEM, ["log.o"], "log", "log system", ["tmpfs"], ["LOG"], ["all"]],
				[SYSTEM, ["bish.o"], "bish", "built in shell", ["keyboard", "pci"], ["SHELL", "BISH"], ["all"]],
				[SYSTEM, ["debug.o"], "debug", "kernel debug", [], ["DEBUG"], ["x86"]],
				[SYSTEM, [], "test", "test functions", [], ["TEST"], ["all"]],
				[SYSTEM, [], "verbose", "verbose output", [], ["VERBOSE"], ["all"]],
				[SYSTEM, [], "smp", "symmetric multiple processor support", [], ["SMP", "MULTIPROC"], ["x86"]],
				
				[EXEC, ["task/elf.o"], "elf", "elf binary support", [], ["EELF"], ["x86"]],

				[BLOCK, ["driver/block/ata_pio.o"], "ata pio", "ata piomode driver", [], ["DATAPIO"], ["x86"]],

				[FS, ["driver/fs/pfs/pfs.o"], "pigfs", "spiderpig file system", [], ["FSPFS"], ["all"]],
				[FS, ["driver/fs/tmpfs/tmpfs.o"], "tmpfs", "ram file system", [], ["FSTMPFS"], ["all"]],
				[FS, ["driver/fs/initramfs/initramfs.o"], "initramfs", "initial ram file system", [], ["FSINITRAMFS"], ["all"]],
			  ]
					
arch_list = [["x86", "", ["X86", "BIT32"],
				["arch/x86/boot/boot.o"], ["arch/x86/video.o", "arch/x86/apic.o", "arch/x86/io.o", "arch/x86/dt.o", "arch/x86/arch.o", "arch/x86/timer.o",
				"arch/x86/clock.o", "arch/x86/mm.o", "arch/x86/paging.o", "arch/x86/task.o", "arch/x86/calls.o",
				"arch/x86/cpu.o", "arch/x86/math.o", "arch/x86/syscall.o"]]]


languages = [["italiano", "lang/italian.h"],
	 		 ["english", "lang/english.h"],
	 		 ["sardo", "lang/sardinian.h"]]
#os.system("clear")


def add_content(name, ask, selecteds):
	x = []
	if name in selecteds:
		return selecteds
		
	for a in content_list:
		if a[2] == name:
			x = a
	if x == []: return

	if ask:
		print "          -> insert " + x[2] + " ( " + x[3] + " - ",
		for i in x[1]:
			print i,
		print ")?",
		r = raw_input()
		if r == 'y' or r == 'Y':
			if x[4] != []:
				for a in x[4]:
					selecteds = add_content(a, 0, selecteds);
			selecteds.append(x[2])
	
	else:
		print "          -> inserted " + x[2] + " ( " + x[3] + " - ",
		for i in x[1]:
			print i,
		print " )"
		if x[4] != []:
			for a in x[4]:
				selecteds = add_content(name, 0, selecteds);
		
		selecteds.append(x[2])
				
	return selecteds


print " -> kernel config"
c = raw_input(" -> select a preset (y/n)? ")
if c == 'y':
	preset_list = [	["x86-generic32", "generic x86 32bit set"],
	 						["x86-generic64", "generic x86 64bit set"]]
	
else:
	flags = "EXFLAGS = "
	builtin = "BUILTIN = "
	boot = "BOOT = "
	config = "#ifndef CONFIG_H\n#define CONFIG_H\n\n"


	print "     -> kernel options selection"

	###############	Language
	print "     -> Language selction: "
	a = 0
	for x in languages:
		print "     	-> "+str(a)+": "+str(x[0])+" ("+x[1]+")"
		a += 1
	a = str(raw_input("     -> 0/"+str(a-1)+": "))
	config += "#include <" + languages[int(a)][1] + ">\n"
	
	
	###############	Arch				
	print "     -> Arch selection: "
	a = 0
	
	if(len(arch_list) == 1):
		a = 0		
		print "     	-> Selected "+str(arch_list[0][0])+" because is the unique arch"
		
	else:
		for x in arch_list:
			print "     	-> "+str(a)+") "+x[0]+" ("+x[1]+")"
			a += 1
		a = str(raw_input("     -> 0/"+str(a-1)+": "))
	
	arch_name = arch_list[int(a)][0]
	
	for x in arch_list[int(a)][3]:
		boot += x + "\\\n"
		
	for x in arch_list[int(a)][4]:
		builtin += x + "\\\n"
		
	for x in arch_list[int(a)][2]:
		config += "#define " + x + "\n"



	print "     -> kernel builtin selection"
	selected = []


	print "       -> generic drivers"
	for x in content_list:
		if x[0] == DRIVER and ((arch_name in x[-1]) or ("all" in x[-1])):
			selected = add_content(x[2], 1, selected)

	
	print "       -> executable format"
	for x in content_list:
		if x[0] == EXEC and ((arch_name in x[-1]) or ("all" in x[-1])):
			selected = add_content(x[2], 1, selected)

	print "       -> input"
	for x in content_list:
		if x[0] == INPUT and ((arch_name in x[-1]) or ("all" in x[-1])):
			selected = add_content(x[2], 1, selected)
			
	print "       -> video"
	for x in content_list:
		if x[0] == VIDEO and ((arch_name in x[-1]) or ("all" in x[-1])):
			selected = add_content(x[2], 1, selected)			
			
	print "       -> bus"
	for x in content_list:
		if x[0] == BUS and ((arch_name in x[-1]) or ("all" in x[-1])):
			selected = add_content(x[2], 1, selected)

	print "       -> block"
	for x in content_list:
		if x[0] == BLOCK and ((arch_name in x[-1]) or ("all" in x[-1])):
			selected = add_content(x[2], 1, selected)

	print "       -> char"
	for x in content_list:
		if x[0] == CHAR and ((arch_name in x[-1]) or ("all" in x[-1])):
			selected = add_content(x[2], 1, selected)			


	print "       -> filesystem"
	for x in content_list:
		if x[0] == FS and ((arch_name in x[-1]) or ("all" in x[-1])):
			selected = add_content(x[2], 1, selected)			

	print "       -> network"
	for x in content_list:
		if x[0] == NETWORK and ((arch_name in x[-1]) or ("all" in x[-1])):
			selected = add_content(x[2], 1, selected)	
			
	print "       -> crypto"
	for x in content_list:
		if x[0] == CRYPTO and ((arch_name in x[-1]) or ("all" in x[-1])):
			selected = add_content(x[2], 1, selected)
			
	print "       -> system"
	for x in content_list:
		if x[0] == SYSTEM and ((arch_name in x[-1]) or ("all" in x[-1])):
			selected = add_content(x[2], 1, selected)
			
			
	print "       -> app"
	for x in content_list:
		if x[0] == APP and ((arch_name in x[-1]) or ("all" in x[-1])):
			selected = add_content(x[2], 1, selected)
			
	print "       -> other"
	for x in content_list:
		if x[0] == OTHER and ((arch_name in x[-1]) or ("all" in x[-1])):
			selected = add_content(x[2], 1, selected)	
			
			

	
	
	for x in selected:
		for a in content_list:
			if a[2] == x:
				for b in a[1]:
					builtin += b + "\\\n"
				for b in a[5]:
					config += "#define " + b + "\n"
				
				try:
					flags += " "+a[6]+" "
				except:
					pass
					
	config += "\n\n#endif\n"
	print "     -> kernel options selection"
	
	
	
	
	# Scrive tutti i dati nei file di configurazione
	a = open("configs/current.am", "w")
	a.write(builtin+"\n\n"+boot+"\n\n"+flags+"\n\n")
	a.close()
	print "     -> configs/current.am wrote"
	
	os.system("rm include/types.h");
	os.system("rm link.ld");
	os.system("link arch/"+arch_name+"/link.ld link.ld");
	os.system("link arch/"+arch_name+"/types.h include/types.h");
		
	a = open("configs/current_config.h", "w")
	a.write(config)
	a.close()
	print "     -> configs/current_config.h wrote"
	
	os.system("cp configs/current_config.h include/config.h")
	print "     -> include/config.h wrote"
	
	os.system("make clean > /dev/null")
	print "     -> .o cleaned"


	# Compile
	print "     -> compile all? ",
	r = raw_input()
	if r == 'y' or r == 'Y':
		os.system("make")
	
