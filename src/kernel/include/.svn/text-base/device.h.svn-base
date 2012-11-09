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
 * \file device
 * \author Davide Gessa
 * \date 01-01-10
 */
#ifndef DEVICE_H
#define DEVICE_H

#include <types.h>
#include <config.h>

#define DEVICE_BUS_TYPE_PCI		0x01
#define DEVICE_BUS_TYPE_ISA		0x02
#define DEVICE_BUS_TYPE_NOT		0x03

/**
 * Device
 */
typedef struct device_p
{
	uint32_t io_base;			///< Porta di io standard
	
	char vendor[32];			///< Nome del costruttore
	char vendor_full[32];		///< Nome intero del costruttore
		
	char device[32];			///< Nome del device
	char device_desc[32];		///< Descrizione del device
		
	char class[32];				///< Nome classe
	char class_desc[32];		///< Descrizione classe
	char class_prog_desc[32];	///< Descrizione avanzata classe

	uint8_t bus_type;			///< Tipo di bus usato
	
	#ifdef DPCI		
		void *pci_dev;
	#endif
	
	uint8_t interrupt;			///< Linea di interrupt del device
	uint32_t base_addresses[6];	///< Indirizzi base del device
	
	char file[32];				///< File assocciato al device
			
	struct device_p *next;
} device_t;



device_t *device_list;				///< Lista dei device

void device_update();
uint32_t device_iget(uint32_t, device_t **);



#endif
