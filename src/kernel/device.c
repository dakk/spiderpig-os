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
 * \file kernel/device.c
 * \author Davide Gessa
 * \date 01-01-10
 */
#include <driver.h>
#include <device.h>
#include <mm/mm.h>
#include <debug.h>
#include <driver/input/keyboard.h>
#include <driver/input/mouse.h>
#include <driver/crypto/crc32.h>
#include <driver/net/rs232.h>
#include <driver/crypto/md5.h>
#include <config.h>
#include <driver/bus/pci/pci.h>
#include <driver/video/vesa.h>
#include <fs/devfs.h>
#include <video.h>


/**
 * Aggiorna la lista dei device
 */
void device_update()
{
	device_t *dev;
	device_t *next;
	
	// Svuota la lista
	dev = device_list;
	
	while(dev != NULL)
	{
		next = dev->next;
		free(dev);
		dev = next;
	}
	
	device_list = NULL;

	#ifdef VERBOSE
	video_puts_colored(VIDEO_HI_BLUE_BLACK, " -> ");
	printf(MSG_DEV_SCAN "\n");
	#endif
	
	// Rileva i dev
	#ifdef PCI
		pci_update(&device_list);
	#endif
		
	dev = device_list;
	while(dev != NULL)
	{
		char tmp[32];
		devfs_find_freen(dev->file, tmp);
		strcpy(dev->file, tmp);
		devfs_reg_device(dev, 0, dev->file);

		switch(dev->bus_type)
		{
			case DEVICE_BUS_TYPE_PCI:
				#ifdef VERBOSE
					video_puts_colored(VIDEO_HI_BLUE_BLACK, "  -> ");
					printf("0%x:0%x:%x - %s (%s)\n", ((pci_device_t *) (dev->pci_dev))->bus, 
										((pci_device_t *) (dev->pci_dev))->device, 
										((pci_device_t *) (dev->pci_dev))->slot,
										dev->class, dev->class_desc);
				#endif
				break;
				
			default:
				break;
		}
		
		dev = dev->next;
	}
}


/**
 * Restituisce il device numero x
 * 
 * \return stato operazione
 */
uint32_t device_iget(uint32_t x, device_t **dev)
{
	device_t *cf = device_list;
	uint32_t i = 0;
	*dev = NULL;
	
	while(cf != NULL)
	{
		if(i == x)
		{
			*dev = cf;
			return 0;
		}
		i++;
		cf = cf->next;
	}
	return 1;	
}
