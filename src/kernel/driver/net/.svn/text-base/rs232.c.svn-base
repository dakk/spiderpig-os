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
 * \file driver/net/rs232.c
 * \author Davide Gessa
 * \date 12-05-2009
 * 
 * \note aggiungere anche un buffer per le trasmissioni
 * \note scrivere la read e la write, aggiungere il supporto al vfs
 */
#include "rs232.h"
#include <types.h>
#include <arch.h>
#include <fs/devfs.h>
#include <config.h>
#include <driver/net/modem.h>

driver_t driver_rs232 = 
{
	.name = "rs232\0",
	.desc = "serial network standard\0",
	.author = "Davide Gessa\0",
	
	.probe = rs232_probe,
	.free = rs232_free,
	.init = rs232_init
};



device_t rs232_com1 = { .io_base = COM1, .bus_type = DEVICE_BUS_TYPE_NOT };
device_t rs232_com2 = { .io_base = COM2, .bus_type = DEVICE_BUS_TYPE_NOT };
device_t rs232_com3 = { .io_base = COM3, .bus_type = DEVICE_BUS_TYPE_NOT };
device_t rs232_com4 = { .io_base = COM4, .bus_type = DEVICE_BUS_TYPE_NOT };


/**
 * 
 */
uint32_t rs232_probe(device_t *dev)
{
	
}



/**
 * Deinizializza le porte rs232
 */
uint32_t rs232_free()
{
	handler_unreg(IRQ_COM13);
	handler_unreg(IRQ_COM24);

	devfs_unreg_device("ser0");
	devfs_unreg_device("ser1");
	devfs_unreg_device("ser2");
	devfs_unreg_device("ser3");
	
	return DRV_OK;
}


/**
 * Inizializza le porte rs232
 */
uint32_t rs232_init()
{
	int x;
	
	rs232_init_port(COM1);
	rs232_init_port(COM2);
	rs232_init_port(COM3);
	rs232_init_port(COM4);
	
	for(x = 0; x < 4; x++)
		combuf[x].where = combuf[x].size = combuf[x].point = 0;
		
	handler_reg(IRQ_COM13, &rs232_callback);
	handler_reg(IRQ_COM24, &rs232_callback);
	
	devfs_reg_device(NULL, NULL, "ser0");
	devfs_reg_device(NULL, NULL, "ser1");
	devfs_reg_device(NULL, NULL, "ser2");
	devfs_reg_device(NULL, NULL, "ser3");
	
	return DRV_OK;
}
	




	
/**
 * Inizializza una porta rs232
 */
void rs232_init_port(uint32_t port)
{
	io_outb(port + 1, 0x01);    // Disable all interrupts
	io_outb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	io_outb(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	io_outb(port + 1, 0x00);    //                  (hi byte)
	io_outb(port + 3, 0x03);    // 8 bits, no parity, one stop bit
	io_outb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	io_outb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}


/**
 * Invia un dato ad una porta
 */
void rs232_send(uint32_t port, uint8_t data)
{
	while ((io_inb(port + 5) & 0x20) == 0);
	io_outb(port, data);
}


/**
 * Legge un carattere dal buffer
 */
uint8_t rs232_receive(uint32_t port)
{
	char ch = 0;
	switch(port)
	{
		case COM1:
			if(combuf[0].size > 0)
			{
				ch = combuf[0].buf[combuf[0].where];
				//putchar(ch);
				combuf[0].where++;
				combuf[0].size--;
			}
			return ch;
					
		case COM2:
			if(combuf[1].size > 0)
			{
				ch = combuf[1].buf[combuf[1].where];
				combuf[1].where++;
				combuf[1].size--;
			}
			return ch;
			
		case COM3:
			if(combuf[2].size > 0)
			{
				ch = combuf[2].buf[combuf[2].where];
				combuf[2].where++;
				combuf[2].size--;
			}
			return ch;
			
		case COM4:
			if(combuf[3].size > 0)
			{
				ch = combuf[3].buf[combuf[3].where];
				combuf[3].where++;
				combuf[3].size--;
			}
			return ch;
	}
}



/**
 * Handler delle interruzioni per le porte com
 */
static void rs232_callback(regs_t *reg)
{
	//printf("stdio\n");
	
	if((io_inb(COM1 + 5) & 1) != 0)
	{
		combuf[0].buf[combuf[0].point] = io_inb(COM1);
		combuf[0].size++;
		combuf[0].point++;
	}	
	if((io_inb(COM2 + 5) & 1) != 0)
	{
		combuf[1].buf[combuf[1].point] = io_inb(COM2);
		combuf[1].size++;
		combuf[1].point++;
	}		
	if((io_inb(COM3 + 5) & 1) != 0)
	{
		combuf[2].buf[combuf[2].point] = io_inb(COM3);
		combuf[2].size++;
		combuf[2].point++;
	}		
	if((io_inb(COM4 + 5) & 1) != 0)
	{
		combuf[3].buf[combuf[3].point] = io_inb(COM4);
		combuf[3].size++;
		combuf[3].point++;
	}		

	#ifdef DMODEM
		modem_callback(reg);
	#endif
}
