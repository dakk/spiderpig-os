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
 * \file driver/net/ne2k.c
 * \author Davide Gessa
 * \date 12-05-2009
 */
#include "ne2k.h"
#include <types.h>
#include <device.h>
#include <config.h>
#include <network/packet.h>
#include <driver/bus/pci/pci.h>


/**
 * Per fare test con la scheda in qemu
 */
device_t device_ne2k_qemu =
{
	.io_base = 0x380, //0x300, 0x280, 0x320, 0x340, 0x360, 0x380
	.bus_type = DEVICE_BUS_TYPE_NOT
};



/**
 * Lista device ne2k
 */
#ifdef PCI
pci_id_entry_t ne2k_dev_list[] =
{
	{ .vendor_id = 0x10EC, .device_id = 0x8029 }
};
#endif


driver_t driver_ne2k = 
{
	.name = "ne2k",
	.desc = "ne2k network family chip\0",
	.author = "Davide Gessa\0",
	
	.init = ne2k_init,
	.probe = ne2k_probe,
	.ioctl = ne2k_ioctl
};



/**
 * Ricerca un device con cui si puo' usare questo driver
 */
uint32_t ne2k_probe(device_t *d)
{
	uint32_t i, j;
	device_t *dev;
	
	while(device_iget(i, &dev) == 0)
	{
		#ifdef PCI
			if(dev->bus_type == DEVICE_BUS_TYPE_PCI)
			{
				for(j = 0; j < sizeof(sizeof(ne2k_dev_list) / sizeof(pci_id_entry_t)); j++)
				{
					if( (((pci_device_t *) (dev->pci_dev))->device_id == ne2k_dev_list[j].device_id) &&
						(((pci_device_t *) (dev->pci_dev))->vendor_id == ne2k_dev_list[j].vendor_id))
					{
						printf("found ne2k\n");
					}
				}
			}
		#endif
		i++;
	}
}



/**
 * Callback dell'interrupt del ne2k
 */
static void ne2k_callback(regs_t *r)
{
	// Legge registri del nic
	
	ifrec:
		eth_handle_frame(0, 0);
		
	iftrans:
		return;
}


/**
 * Inizializza il driver
 */
uint32_t ne2k_init()
{
	uint8_t a;

	//return DRV_OK;
	
	driver_initd("keyboard");
	uint32_t c;
	uint32_t i;
	for(i = 280; i < 400; i++)
	{
		scanf("%d", c);
		device_ne2k_qemu.io_base = i;
		printf("%d   ", i);
		a = io_inb(device_ne2k_qemu.io_base + 1);
		printf("%x:",a);
		a = io_inb(device_ne2k_qemu.io_base + 2);
		printf("%x:",a);
		a = io_inb(device_ne2k_qemu.io_base + 3);
		printf("%x:",a);
		a = io_inb(device_ne2k_qemu.io_base + 4);
		printf("%x:",a);
		a = io_inb(device_ne2k_qemu.io_base + 5);
		printf("%x:",a);
		a = io_inb(device_ne2k_qemu.io_base + 6);
		printf("%x",a);
		printf("\n");
	}
	
	return DRV_OK;
}





/**
 * Invia un pacchetto
 */
uint32_t ne2k_send_packet(device_t *dev, packet_t *pack)
{
	
}



/**
 * IoCTL
 */
uint32_t ne2k_ioctl(device_t *d, uint32_t call, uint32_t a, uint32_t b)
{
	switch(call)
	{
		default:
			break;
	}	
}


