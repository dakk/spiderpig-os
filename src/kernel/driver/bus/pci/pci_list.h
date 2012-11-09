/*
 * SpiderpigOS
 * Copyright (C) 2009 - 2010 Davide Gessa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * \file driver/pci/pci_list.h
 * \date 12-08-2009
 */
#ifndef DRIVER_PCI_PCI_PCI_LIST_H
#define DRIVER_PCI_PCI_PCI_LIST_H



/**
 * Entry per la tabella delle classi hardware
 */
typedef struct
{
	uint8_t class_base;		///< Classe base
	uint8_t class_sub;		///< Sotto classe
	uint8_t prog_if;		///< Info aggiuntive
	char *desc_base;		///< Descrizione base
	char *desc_sub;			///< Descrizione avanzata
	char *desc_prog;		///< Descrizione info aggiuntive
	char file[32];			///< Nome del file device
} pci_classtable_t;


///> Tabella delle classi hardware
pci_classtable_t pci_class_code_table [] =
{
	{ 0x00, 0x00, 0x00, "Pre2.0 PCI Specification Device", "Non-VGA","", "pcisd"  } ,
	{ 0x00, 0x01, 0x00, "Pre2.0 PCI Specification Device", "VGA Compatible", "", "pcisd"  } ,

	{ 0x01, 0x00, 0x00, "Mass Storage Controller", "SCSI", "", "hd"  } ,
	{ 0x01, 0x01, 0x00, "Mass Storage Controller", "IDE", "", "hd"  } ,
	{ 0x01, 0x02, 0x00, "Mass Storage Controller", "Floppy", "", "fd" } ,
	{ 0x01, 0x03, 0x00, "Mass Storage Controller", "IPI", "", "hd"  } ,
	{ 0x01, 0x04, 0x00, "Mass Storage Controller", "RAID", "", "hd" } ,
	{ 0x01, 0x80, 0x00, "Mass Storage Controller", "Other", "", "hd"  } ,

	{ 0x02, 0x00, 0x00, "Network Controller", "Ethernet", "", "eth"  } ,
	{ 0x02, 0x01, 0x00, "Network Controller", "Token Ring", "", "tr"  } ,
	{ 0x02, 0x02, 0x00, "Network Controller", "FDDI", "", "fddi"  } ,
	{ 0x02, 0x03, 0x00, "Network Controller", "ATM", "", "atm"  } ,
	{ 0x02, 0x80, 0x00, "Network Controller", "Other", "", "nc"  } ,

	{ 0x03, 0x00, 0x00, "Display Controller", "PC Compatible", "VGA", "vga"  } ,
	{ 0x03, 0x00, 0x01, "Display Controller", "PC Compatible", "8514", "vga"  } ,
	{ 0x03, 0x01, 0x00, "Display Controller", "XGA", "", "xga"  } ,
	{ 0x03, 0x80, 0x00, "Display Controller", "Other", "", "vga"  } ,

	{ 0x04, 0x00, 0x00, "Multimedia Device", "Video", "", "video"  } ,
	{ 0x04, 0x01, 0x00, "Multimedia Device", "Audio", "", "audio"  } ,
	{ 0x04, 0x80, 0x00, "Multimedia Device", "Other", "", "media"  } ,

	{ 0x05, 0x00, 0x00, "Memory Controller", "RAM", "", "ram"  } ,
	{ 0x05, 0x01, 0x00, "Memory Controller", "Flash", "", "flash"  } ,
	{ 0x05, 0x80, 0x00, "Memory Controller", "Other", "", "mem"  } ,

	{ 0x06, 0x00, 0x00, "Bridge Device", "Host/PCI", "", "pci"  } ,
	{ 0x06, 0x01, 0x00, "Bridge Device", "PCI/ISA", "", "pci"  } ,
	{ 0x06, 0x02, 0x00, "Bridge Device", "PCI/EISA", "", "pci"  } ,
	{ 0x06, 0x03, 0x00, "Bridge Device", "PCI/Micro Channel", "", "pci"  } ,
	{ 0x06, 0x04, 0x00, "Bridge Device", "PCI/PCI", "", "pci"  } ,
	{ 0x06, 0x05, 0x00, "Bridge Device", "PCI/PCMCIA", "", "pci"  } ,
	{ 0x06, 0x06, 0x00, "Bridge Device", "PCI/NuBus", "", "pci"  } ,
	{ 0x06, 0x07, 0x00, "Bridge Device", "PCI/CardBus", "", "pci"  } ,
	{ 0x06, 0x80, 0x00, "Bridge Device", "Other", "", "pci"  } ,

	{ 0x07, 0x00, 0x00, "Simple Communications Controller", "Serial", "Generic XT Compatible", "ser"  } ,
	{ 0x07, 0x00, 0x01, "Simple Communications Controller", "Serial", "16450 Compatible", "ser"  } ,
	{ 0x07, 0x00, 0x02, "Simple Communications Controller", "Serial", "16550 Compatible", "ser"  } ,
	{ 0x07, 0x01, 0x00, "Simple Communications Controller", "Parallel", "Standard", "par"  } ,
	{ 0x07, 0x01, 0x00, "Simple Communications Controller", "Parallel", "Bidirectional", "par"  } ,
	{ 0x07, 0x01, 0x01, "Simple Communications Controller", "Parallel", "ECP 1.X Compliant", "par"  } ,
	{ 0x07, 0x80, 0x02, "Simple Communications Controller", "Other", "", "scc"  } ,

	{ 0x08, 0x00, 0x00, "Base Systems Peripheral", "PIC (Programmable Interrupt Controller)", "Generic 8259", "pic"  } ,
	{ 0x08, 0x00, 0x01, "Base Systems Peripheral", "PIC (Programmable Interrupt Controller)", "ISA", "pic"  } ,
	{ 0x08, 0x00, 0x02, "Base Systems Peripheral", "PIC (Programmable Interrupt Controller)", "PCI", "pic"  } ,
	{ 0x08, 0x01, 0x00, "Base Systems Peripheral", "DMA (Direct Memory Access)", "Generic 8259", "dma"  } ,
	{ 0x08, 0x01, 0x01, "Base Systems Peripheral", "DMA (Direct Memory Access)", "ISA", "dma"  } ,
	{ 0x08, 0x01, 0x02, "Base Systems Peripheral", "DMA (Direct Memory Access)", "EISA", "dma"  } ,
	{ 0x08, 0x02, 0x00, "Base Systems Peripheral", "System Timer", "Generic 8259", "timer"  } ,
	{ 0x08, 0x02, 0x01, "Base Systems Peripheral", "System Timer", "ISA", "timer"  } ,
	{ 0x08, 0x02, 0x02, "Base Systems Peripheral", "System Timer", "EISA", "timer"  } ,
	{ 0x08, 0x03, 0x00, "Base Systems Peripheral", "RTC (Real Time Clock)", "Generic", "rtc"  } ,
	{ 0x08, 0x03, 0x01, "Base Systems Peripheral", "RTC (Real Time Clock)", "ISA", "rtc"  } ,
	{ 0x08, 0x80, 0x00, "Base Systems Peripheral", "Other", "bsp" } ,

	{ 0x09, 0x00, 0x00, "Input Device", "Keyboard", "", "keyb"  } ,
	{ 0x09, 0x01, 0x00, "Input Device", "Digitizer (Pen)", "", "pen"  } ,
	{ 0x09, 0x02, 0x00, "Input Device", "Mouse", "", "mouse"  } ,
	{ 0x09, 0x80, 0x00, "Input Device", "Other", "", "hid"  } ,

	{ 0x0A, 0x00, 0x00, "Docking Station", "Generic", "", "ds"  } ,
	{ 0x0A, 0x80, 0x00, "Docking Station", "Other", "", "ds"  } ,

	{ 0x0B, 0x00, 0x00, "Processor", "i386", "", "proc"  } ,
	{ 0x0B, 0x01, 0x00, "Processor", "i486", "", "proc"  } ,
	{ 0x0B, 0x02, 0x00, "Processor", "Pentium", "", "proc"  } ,
	{ 0x0B, 0x10, 0x00, "Processor", "Alpha", "", "proc"  } ,
	{ 0x0B, 0x20, 0x00, "Processor", "Power PC", "", "proc"  } ,
	{ 0x0B, 0x80, 0x00, "Processor", "Co-processor", "", "proc"  } ,

	{ 0x0C, 0x00, 0x00, "Serial Bus Controller", "Firewire (IEEE 1394)", "", "sbc"  } ,
	{ 0x0C, 0x01, 0x00, "Serial Bus Controller", "ACCESS.bus", "", "sbc"  } ,
	{ 0x0C, 0x02, 0x00, "Serial Bus Controller", "SSA (Serial Storage Archetecture)", "", "ssa"  } ,
	{ 0x0C, 0x03, 0x00, "Serial Bus Controller", "USB (Universal Serial Bus)", "", "usb"  } ,
	{ 0x0C, 0x04, 0x00, "Serial Bus Controller", "Fibre Channel", "", "fib"  } ,

	{ 0xFF, 0x00, 0x00, "Unknown", "Device Does Not Fit In Class Codes", "UDF", "unk" } ,
};

///> Lunghezza della tabella delle classi hardware
#define	PCI_CLASS_CODE_TABLE_LEN (sizeof(pci_class_code_table)/sizeof(pci_classtable_t))


#endif
