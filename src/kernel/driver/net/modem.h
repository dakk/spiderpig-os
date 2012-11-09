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
 * \file driver/net/modem.h
 * \author Davide Gessa
 * \date 02-05-2010
 */
#ifndef MODEM_H
#define MODEM_H

#include <types.h>
#include <driver.h>

#define MODEM_CONNECT		0x01
#define MODEM_DISCONNECT	0x02
#define MODEM_RECEIVE		0x03
#define MODEM_SEND			0x04
#define MODEM_READ			0x03
#define MODEM_WRITE			0x04

extern driver_t driver_modem;

uint32_t modem_init();
uint32_t modem_free();
uint32_t modem_connect(device_t *, char *);
uint32_t modem_disconnect(device_t *);
uint32_t modem_ioctl(device_t *, uint32_t, uint32_t, uint32_t);
uint32_t modem_read(device_t *, char *, uint32_t, uint64_t);
uint32_t modem_write(device_t *, char *, uint32_t, uint64_t);
uint32_t modem_callback(regs_t *);

#endif
