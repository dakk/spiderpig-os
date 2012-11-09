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
 * \file kernel/driver/pci/pci.h
 * \author Davide Gessa
 * \date 10-25-09
 */
#ifndef DRIVER_PCI_PCI_H
#define DRIVER_PCI_PCI_H

#include <klibc/ctype.h>
#include <driver.h>


#define PCI_VENDOR_ID      0x00 /* (2 byte) vendor id */
#define PCI_DEVICE_ID      0x02 /* (2 byte) device id */
#define PCI_COMMAND        0x04 /* (2 byte) command */
#define PCI_STATUS         0x06 /* (2 byte) status */
#define PCI_REVISION_ID    0x08 /* (1 byte) revision id */
#define PCI_CLASS_API      0x09 /* (1 byte) specific register interface type */
#define PCI_CLASS_SUB      0x0A /* (1 byte) specific device function */
#define PCI_CLASS_BASE     0x0B /* (1 byte) device type (display vs network, etc) */
#define PCI_LINE_SIZE      0x0C /* (1 byte) cache line size in 32 bit words */
#define PCI_LATENCY        0x0D /* (1 byte) latency timer */
#define PCI_HEADER_TYPE    0x0E /* (1 byte) header type */
#define PCI_BIST           0x0F /* (1 byte) built-in self-test */
#define PCI_BASE_REGISTERS 0x10 /* base registers (size varies) */
#define PCI_SUBSYS_VEND_ID 0x2C /* (2 byte) subsystem vendor id */
#define PCI_SUBSYS_DEV_ID  0x2E /* (2 byte) subsystem id */
#define PCI_INTERRUPT_LINE 0x3C /* (1 byte) interrupt line */
#define PCI_INTERRUPT_PIN  0x3D


/**
 * Dati pci bus
 */
typedef struct
{
	uint32_t bus;					///< Bus del device
	uint32_t function;
	uint32_t device;
	
	uint32_t command;
	uint32_t status;
	uint32_t rev_id;
	uint32_t iface;
	
	uint32_t vendor_id;				///< Id del costruttore
	uint32_t device_id;				///< Id del device
	uint32_t class_id;				///< Classe base id
	uint32_t subclass_id;			///< Sotto classe id	

	uint32_t bar[6];
	uint32_t int_line;
	uint32_t int_pin;
} pci_device_t;



/**
 * Una entry, ogni driver dovra' specificare per quali accopiamenti
 * 	device/vendor e' utile quel driver
 */
typedef struct
{
	uint32_t vendor_id;				///< Id del costruttore
	uint32_t device_id;				///< Id del device	
} pci_id_entry_t;


extern driver_t driver_pci;

uint32_t pci_read(uint32_t, uint32_t, uint32_t, uint32_t, uint8_t);
uint32_t pci_get(uint32_t, uint32_t, uint32_t, device_t *);
uint32_t pci_probe();

#endif
