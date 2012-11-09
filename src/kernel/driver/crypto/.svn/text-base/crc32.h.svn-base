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
 * \file crypto/crc32.h
 * \author Davide Gessa
 * \date 11-30-2009
 */
#ifndef CRYPTO_CRC32_H
#define CRYPTO_CRC32_H

#include <types.h>
#include <driver.h>

extern driver_t driver_crc32;

uint32_t crc32_table[256];		///< Tabella dei polinomi generatori

uint32_t crc32_make(uint8_t *, uint32_t);
uint32_t crc32_check(uint32_t, uint8_t *, uint32_t);

#endif
