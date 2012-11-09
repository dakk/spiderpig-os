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
 * \file kernel/driver/block/ata_pio.c
 * \author Davide Gessa
 * \date 03-4-10
 */
#include "ata_pio.h"
#include <klibc/stdio.h>
#include <types.h>
#include <arch.h>
#include <video.h>
#include <driver.h>

driver_t driver_ata_pio = 
{
	.name = "ata_pio\0",
	.desc = "ata pio mode driver\0",
	.author = "Davide Gessa\0",
						
	.probe = ata_pio_probe,
						
	.init = ata_pio_init,
	.free = ata_pio_free,
	.read = ata_pio_read,
	.write = ata_pio_write
};



/**
 * 
 */
uint32_t ata_pio_probe(device_t *dev)
{
	return 1;
}




/**
 * Ata 
 */
uint32_t ata_pio_init()
{	
	devfs_reg_device(NULL, NULL, "ata0");
	
	return DRV_OK;
}


uint32_t ata_pio_free()
{

	return DRV_OK;
}



uint32_t ata_pio_read(device_t *dev, char *data, uint32_t size, uint64_t off)
{

}


uint32_t ata_pio_write(device_t *dev, char *data, uint32_t size, uint64_t off)
{

}
