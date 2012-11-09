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
 * \file crypto/crc32.c
 * \author Davide Gessa
 * \date 11-30-2009
 */
#include "crc32.h"
#include <types.h>
#include <klibc/malloc.h>
#include <driver.h>

driver_t driver_crc32 = 
{
	.name = "crc32\0",
	.desc = "32bit crc checksum\0",
	.author = "Davide Gessa\0"
};


/**
 * Crea il crc di un blocco di dati
 * 
 * \param blocks blocchi di cui fare il crc
 * \param size dimensione in byte del blocco
 * \return crc
 */
uint32_t crc32_make(uint8_t *blocks, uint32_t size)
{
	uint32_t crc_code = 0x00000000;
	
	
	return crc_code;
}


/**
 * Fa il check e fixa gli errori dei blocchi con il crc passatogli
 * 
 * \param crc32 codice crc
 * \param blocks blocchi a cui fare il check
 * \param size dimensione in byte del blocco	
 * \return sindrome
 */
uint32_t crc32_check(uint32_t crc32, uint8_t *blocks, uint32_t size)
{
	// Genera il crc del blocco ricevuto
	uint32_t crc_gen = crc32_make(blocks, size);
	
	// Fa lo xor dei due crc
	uint32_t sindrome = crc32 ^ crc_gen;

	// Se la sindrome e' zero, non esiste nessun errore
	if(sindrome == 0) return sindrome;

	// Calcola blocco e bit dell'errore
	uint32_t block = sindrome / 8;
	uint32_t bit = sindrome % 8;
	
	// Corregge l'errore (dubbia funzionalita')
	blocks[block] = blocks[block] + ~(blocks[block] & (1 << bit)) << bit;

	return sindrome;
}


