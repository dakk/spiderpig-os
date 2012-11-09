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
#include "modem.h"
#include <types.h>
#include <driver/net/rs232.h>
#include <arch.h>
#include <fs/devfs.h>
#include <network/link/ppp.h>
#include <network/packet.h>


driver_t driver_modem = 
{
	.name = "modem\0",
	.desc = "serial modem\0",
	.author = "Davide Gessa\0",
	
	.read = modem_read,
	.write = modem_write,
	.ioctl = modem_ioctl,
	
	.init = modem_init,
	.free = modem_free
};


uint8_t state = 0;
uint32_t buf_p = 0;
char buff[1024];

/**
 * Inizializza il modem
 */
uint32_t modem_init()
{
	driver_initd("rs232");
	return DRV_OK;
}


/**
 * Deinizializza il modem
 */
uint32_t modem_free()
{
	state = 0;
	
	return DRV_OK;
}

/**
 * Connette il modem ad un dato numero
 */
uint32_t modem_connect(device_t *dev, char *num)
{
	char buf[512];

	driver_initd("rs232");

	driver_puts(&driver_modem, MDRV_OK, "trying connection");	
	modem_write(dev, "\rat\r", sizeof("\rat\r"), 0);
	if(modem_read(dev, buf, 5, 0) == 0)
	{
		driver_puts(&driver_modem, MDRV_WR, "timeout");	
		return DRV_ER;
	}
	
	if(	(strcmp(buf, "ABORT") == 0) || (strcmp(buf, "ERROR") == 0) || 
		(strcmp(buf, "DIAL") == 0))
	{
		driver_puts(&driver_modem, MDRV_ER, "error");
		return DRV_ER;
	}
	
	driver_puts(&driver_modem, MDRV_OK, "sending number");
	strcpy(buf, "atdt");
	strcat(buf, num);
	strcat(buf, "\r");
	
	modem_write(dev, buf, strlen(buf), 0);
	if(modem_read(dev, buf, 8, 0) == 0)
	{
		driver_puts(&driver_modem, MDRV_WR,"timeout");	
		return DRV_ER;
	}	
	
	if(	(strcmp(buf, "ABORT") == 0) || (strcmp(buf, "ERROR") == 0))
	{
		driver_puts(&driver_modem, MDRV_ER, "connect error");
		return DRV_ER;
	}
	else if(strcmp(buf, "DIAL") == 0)
	{
		driver_puts(&driver_modem, MDRV_ER, "dial error");
		return DRV_ER;
	}
	
	else if(strcmp(buf, "CONNECT") == 0)
	{
		driver_puts(&driver_modem, MDRV_OK, "connected");
		devfs_reg_device(NULL, NULL, "modem0");
		state = 1;
		return DRV_OK;
	}
	
	else
	{
		driver_puts(&driver_modem, MDRV_ER, "unknown error");
		return DRV_ER;
	}
}





/**
 * Disconnette da un numero
 */
uint32_t modem_disconnect(device_t *dev)
{
	driver_puts(&driver_modem, MDRV_OK, "disconnected");	
	state = 0;

	return DRV_OK;
}



/**
 * Legge un frame
 */
uint32_t modem_read(device_t *dev, char *frame, uint32_t size, uint64_t of)
{
	uint32_t i;
	uint64_t e;		// Timeout
	uint32_t t;		// Timeout 2
	
	for(i = 0; i < size; i++)
	{
		e = 1000000000;
		aq:
			e--;
			//printf("%d\n", e);
			frame[i] = rs232_receive(dev->io_base);
			
			/*if(e < 1)
				return 0;
			else */
			if(frame[i] == 0) 
				goto aq;
			else if(frame[i] == 13)
				break;
	}
	frame[i] = '\0';
	return i;	
}


/**
 * Scrive un frame
 */
uint32_t modem_write(device_t *dev, char *frame, uint32_t size, uint64_t off)
{
	uint32_t i;
			
	for(i = 0; i < size; i++)
	{
		rs232_send(dev->io_base, frame[i]);
	}

	return i;	
}


/**
 * IoCTL
 */
uint32_t modem_ioctl(device_t *d, uint32_t call, uint32_t a, uint32_t b)
{
	switch(call)
	{
		case MODEM_CONNECT:
			return modem_connect(d, (char *) a);

		case MODEM_DISCONNECT:
			return modem_disconnect(d);

		case MODEM_WRITE:
			return modem_write(d, (char *) a, b, 0);
			
		case MODEM_READ:
			return modem_read(d, (char *) a, b, 0);
			
		default:
			break;
	}	
}


uint32_t modem_callback(regs_t *reg)
{
	#ifdef NPPP
	if(state)
	{
		buff[buf_p] = rs232_receive(COM1);
		buf_p++;

		
		if(buf_p == ppp_linkproto.frame_min_size)
		{
			packet_t *p = packet_create(buff, buf_p);
			
			ppp_handle_frame(0, p);
			buf_p = 0;
		}	
	}	
	#endif
}
