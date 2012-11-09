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
 * \file kernel/driver/smbios.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef DRIVER_SMBIOS_H
#define DRIVER_SMBIOS_H

#include <types.h>
#include <driver.h>
#include <klibc/ctype.h>


#define SMBIOS_TYPE_BIOS				0
#define SMBIOS_TYPE_SYSTEM				1
#define SMBIOS_TYPE_MAINBOARD			2
#define SMBIOS_TYPE_ENCLOSURE_CHASIS	3
#define SMBIOS_TYPE_PROCESSOR			4
#define SMBIOS_TYPE_CACHE				7
#define SMBIOS_TYPE_SYSTEM_SLOTS		9
#define SMBIOS_TYPE_PHYSICAL_MEMORY		16
#define SMBIOS_TYPE_MEMORY_DEVICE		17
#define SMBIOS_TYPE_MEMORY_MAPPED		19
#define SMBIOS_TYPE_SYSTEM_BOOT			32


extern driver_t driver_smbios;


/**
 * Struttura dell'entry dell'smbios
 */
typedef struct
{
	char entry_string[4];			///< '_SM_'
	uint8_t checksum;              //This value summed with all the values of the table, should be 0 (overflow)
	uint8_t length;                //Length of the Entry Point Table. Since version 2.1 of SMBIOS, this is 0x1F
	uint8_t major_version;          //Major Version of SMBIOS
	uint8_t minor_version;          //Minor Version of SMBIOS
	uint16_t max_structure_size;     //Maximum size of a SMBIOS Structure (we will se later)
	uint8_t entry_revision;
	char formatted_area[5];
	char entry_string2[5];			///< '_DMI_'
	uint8_t checksum2;				// Checksum for values from EntryPointString2 to the end of table
	uint16_t table_length;			//Length of the Table containing all the structures
	uint32_t table_address;			///< Indirizzoo tabella
	uint16_t number_of_struct;		///< Strutture della tabella
	uint8_t bcd_revision;
} smbios_entry_t;


/**
 * Struttura di un header smbios
 */
typedef struct
{
	uint8_t type;
	uint8_t length;
	uint16_t handle;
} smbios_header_t; 


/**
 * Struttura smbios - processore (type 4)
 */
typedef struct
{
	uint8_t socket_designation;
	uint8_t proc_type;
	uint8_t proc_family;
	uint8_t proc_manufacturer;
	uint64_t proc_id;
	uint8_t proc_version;
	uint8_t voltage;
	uint16_t external_clock;
	uint16_t max_speed;
	uint16_t current_speed;
	uint8_t status;
	uint8_t proc_upgrade;
	uint16_t l1_cache_handle;
	uint16_t l2_cache_handle;
	uint16_t l3_cache_handle;
	uint8_t serial_num;
	uint8_t asset_tag;
	uint8_t part_number;
	uint8_t core_count;
	uint8_t core_enabled;
	uint8_t thread_count;
	uint16_t proc_charact;
	uint16_t proc_family_2;
} smbios_type4_t;

uint32_t smbios_init();
uint32_t smbios_shut();
uint32_t smbios_probe(device_t *);
uint32_t smbios_ioctl(device_t *, uint32_t, uint32_t, uint32_t);

#endif
