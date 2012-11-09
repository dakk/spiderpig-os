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
 * \file kernel/driver/block/ata_pio.h
 * \author Davide Gessa
 * \date 03-4-10
 */
#ifndef DRIVER_ATA_PIO_H
#define DRIVER_ATA_PIO_H

#include <types.h>
#include <driver.h>
#include <klibc/ctype.h>
#include <device.h>

#define ATA_DATA_PORT						0x1F0			//Data port -- read and write PIO <b>data</b> bytes on this port
#define ATA_FEATURES_ERRINFO				0x1F1			//Features / Error info -- mostly used with ATAPI
#define ATA_SECTOR_COUNT					0x1F2			//Sector Count -- number of sectors to read/write (0 = special value)
#define ATA_PARTIAL_DISK_SECTOR_ADDR1		0x1F3			//Partial Disk Sector address (CHS / LBA28 / LBA48 specific)
#define ATA_PARTIAL_DISK_SECTOR_ADDR2		0x1F4			//Partial Disk Sector address
#define ATA_PARTIAL_DISK_SECTOR_ADDR3		0x1F5			//Partial Disk Sector address
#define ATA_FLAGS							0x1F6			//Drive Select bit, Flag bits, Extra address bits
#define ATA_COMMAND_PORT					0x1F7			//Command port / Regular Status port -- write commands / read status

extern driver_t driver_ata_pio;

uint32_t ata_pio_init();
uint32_t ata_pio_free();
uint32_t ata_pio_read(device_t *, char *, uint32_t, uint64_t);
uint32_t ata_pio_write(device_t *, char *, uint32_t, uint64_t);
uint32_t ata_pio_probe(device_t *);

#endif
