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
 * \file crypto/md5.h
 * \author Davide Gessa
 * \date 12-2-2009
 */
#ifndef CRYPTO_MD5_H
#define CRYPTO_MD5_H

#include <types.h>
#include <driver.h>

extern driver_t driver_md5;

uint32_t md5_encode(char *, uint32_t, char *);

#endif
