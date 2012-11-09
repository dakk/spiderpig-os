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
 * \file driver/net/rs232.h
 * \author Davide Gessa
 * \date 12-05-2009
 */
#ifndef RS232_H
#define RS232_H

#include <types.h>
#include <driver.h>


#define IRQ_COM24		3
#define IRQ_COM13		4

#define COM1 0x3f8
#define COM2 0x2f8
#define COM3 0x3e8
#define COM4 0x2e8

extern device_t rs232_com1;
extern device_t rs232_com2;
extern device_t rs232_com3;
extern device_t rs232_com4;

extern driver_t driver_rs232;

typedef struct
{
	char buf[256];
	uint8_t size;
	uint8_t where;
	uint8_t point;	
} rs232_buf_t;


rs232_buf_t combuf[4];

uint32_t rs232_init();
uint32_t rs232_free();
void rs232_init_port(uint32_t);
void rs232_send(uint32_t, uint8_t);
uint8_t rs232_receive(uint32_t);
uint32_t rs232_probe(device_t *);
static void rs232_callback(regs_t *);

#endif
