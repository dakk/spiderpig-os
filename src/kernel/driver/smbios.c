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
 * \file kernel/driver/smbios.c
 * \author Davide Gessa
 * \date 10-12-09
 */
#include "smbios.h"
#include <klibc/stdio.h>
#include <types.h>
#include <arch.h>
#include <video.h>
#include <driver.h>

driver_t driver_smbios = 
{
	.name = "smbios\0",
	.desc = "system mangament bios\0",
	.author = "Davide Gessa\0",
						
	.probe = smbios_probe,
						
	.init = smbios_init
};

char *smbios_mem = NULL;


/**
 * Cerca l'smbios
 */
uint32_t smbios_probe(device_t *dev)
{
	char *mem = (unsigned char *) 0xF0000;
	uint32_t length, i;
	char checksum;
	
	while ((uint32_t) mem < 0x100000)
	{
		if(mem[0] == '_' && mem[1] == 'S' && mem[2] == 'M' && mem[3] == '_')
		{
			length = mem[5];
			checksum = 0;
			for(i = 0; i < length; i++)
				checksum += mem[i];
				
			if(checksum == 0)
			{
				smbios_mem = mem; 
				driver_puts(&driver_smbios, MDRV_OK, "found");

				return 1;
			}
		}
		mem += 16;
	}   
	return 0;
}


/**
 * Inizializza l'smbios
 */
uint32_t smbios_init()
{	
	if(smbios_mem == NULL)
		if(smbios_probe(NULL) == 0)
		{
			driver_puts(&driver_smbios, MDRV_ER, "cannot found a valid smbios table");	
			return DRV_ER;
		}
		
	devfs_reg_device(NULL, NULL, "smbios0");
	
	// Probe cores
	smbios_entry_t *smbios = (smbios_entry_t *) smbios_mem;
	int i;
	
	for(i = 0; i < smbios->number_of_struct; i++)
	{
		smbios_header_t *head = (smbios_header_t *) (smbios->table_address + smbios->table_length * i);
		
		if(head->type == 4)
		{
			smbios_type4_t *t4 = (smbios_type4_t *) head + sizeof(smbios_header_t);
			printf("core_count: %d\n", t4->core_count);
			printf("core_enabled: %d\n", t4->core_enabled);
			printf("voltage: %d\n", t4->voltage);
			printf("max_speed: %d\n", t4->max_speed);
		}
		
	}	
	return DRV_OK;
}
