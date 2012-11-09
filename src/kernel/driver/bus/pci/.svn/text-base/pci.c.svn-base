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
 * \file kernel/driver/pci/pci.c
 * \author Davide Gessa
 * \date 10-25-09
 */
#include "pci.h"
#include "pci_list.h"
#include <arch.h>
#include <klibc/ctype.h>
#include <klibc/string.h>
#include <debug.h>
#include <driver.h>


driver_t driver_pci = 
{
	.name = "pci\0",
	.author = "Davide Gessa\0",
	
	.probe = pci_probe
};




/**
 * Probe pci
 */
uint32_t pci_probe()
{
	return 0;
}



/**
 * Legge un dato dal bus
 */
uint32_t pci_read(uint32_t bus, uint32_t device, uint32_t function, uint32_t offset, uint8_t size)
{
	uint32_t value;
	io_outd(0xCF8,  0x80000000 | (bus << 16) | (device << 11) | (function << 8) | (offset & ~3));

	switch (size)
	{
		case 1: 
			value = io_inb(0xCFC + (offset & 3)); break;
		case 2: 
			value = io_inw(0xCFC + (offset & 2)); break;
		case 4: 
			value = io_ind(0xCFC); break;
		default:
			return 0xFF;
	}
	return value;
}


/**
 * Restituisce il pci_device nella corrispondenza slot bus
 */
uint32_t pci_get(uint32_t bus, uint32_t slot, uint32_t func, device_t *dev)
{
	//*devv = NULL;
	uint32_t tmp = pci_read(bus, slot, func, PCI_VENDOR_ID, 2);
	if ((tmp == 0xFFFF) || (tmp == 0x0000)) return 0;

	pci_device_t *pci_dev = (pci_device_t *) malloc(sizeof(pci_device_t));

	int i;
	pci_dev->bus = bus;
	pci_dev->device = slot;
	pci_dev->function = func;

	pci_dev->vendor_id = pci_read(bus, slot, func, PCI_VENDOR_ID, 2);
	pci_dev->device_id = pci_read(bus, slot, func, PCI_DEVICE_ID, 2);

	//pci_dev->command = pci_read16(bus, device, function, PCI_COMMAND);
	//pci_dev->status = pci_read16(bus, device, function, PCI_STATUS);
	//pci_dev->rev_id = pci_read16(bus, device, function, PCI_REVISION);

	//pci_dev->iface = pci_read8(bus, device, function, PCI_INTERFACE);

	pci_dev->class_id = pci_read(bus, slot, func, PCI_CLASS_BASE, 1);
	pci_dev->subclass_id = pci_read(bus, slot, func, PCI_CLASS_SUB, 1);

	//printf("\n");
	for(i=0;i<6;i++)
	{
		pci_dev->bar[i] = pci_read(bus, slot, func, PCI_BASE_REGISTERS + (i * 4), 4);
		//printf("%x ", pci_dev->bar[i]);
	}
	pci_dev->int_line = pci_read(bus, slot, func, PCI_INTERRUPT_LINE, 1);
	pci_dev->int_pin = pci_read(bus, slot, func, PCI_INTERRUPT_PIN, 1);
	
	//printf("%d %d\n", pci_dev->int_line, pci_dev->int_pin);
	
	#ifdef VERBOSE
		printf("%d:%d:%d - ", bus, slot, func);
	#endif
	
	for(i = 0; i < PCI_CLASS_CODE_TABLE_LEN; i++)
		if(	(pci_class_code_table[i].class_base == pci_dev->class_id) &&
			(pci_class_code_table[i].class_sub == pci_dev->subclass_id))
		{
			#ifdef VERBOSE
				printf("%s (%s)\n", pci_class_code_table[i].desc_base, pci_class_code_table[i].desc_sub);
			#endif
			int j;
			
			strcpy(dev->class, pci_class_code_table[i].desc_base);
			strcpy(dev->class_desc, pci_class_code_table[i].desc_sub);
			
			strcpy(dev->file, pci_class_code_table[i].file);

			break;
		}
		
	dev->pci_dev = (void *) pci_dev;
	return 1;
}



/**
 * Aggiunge i device pci alla lista
 */
void pci_update(device_t **list)
{
	int bus, slot, func;
	
	device_t *dev = NULL;
	device_t *newdev = NULL;
	//*list = NULL;
	
	for(bus = 0; bus < 16; bus++)
		for(slot = 0; slot < 12; slot++)
			for(func = 0; func < 12; func++)
			{
				newdev = (device_t *) malloc(sizeof(device_t));
				
				if(pci_get(bus, slot, func, newdev))
				{
					newdev->bus_type = DEVICE_BUS_TYPE_PCI;
					newdev->next = NULL;

					// Controlla se gia' presente nella lista
					device_t *l = *list;
					while(l != NULL)
					{
						if( (((pci_device_t * )(l->pci_dev))->bus == ((pci_device_t * )(newdev->pci_dev))->bus) &&
							(((pci_device_t * )(l->pci_dev))->device == ((pci_device_t * )(newdev->pci_dev))->device) &&
							(((pci_device_t * )(l->pci_dev))->function == ((pci_device_t * )(newdev->pci_dev))->function))
						{
							goto free_dev;
							
						} 
						l = l->next;
					}
				
					if(*list == NULL)
						*list = newdev;
					else
						dev->next = newdev;	
					
					dev = newdev;
				}
				else
				{
					free_dev:
						free(newdev);
				}
			}
}
