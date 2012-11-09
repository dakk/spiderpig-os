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
 * \file kernel/driver/bus/usb/usb.h
 * \author Davide Gessa
 * \date 10-02-10
 */
#ifndef DRIVER_USB_USB_H
#define DRIVER_USB_USB_H

#include <types.h>
#include <driver.h>
#include <klibc/ctype.h>


#define USB_STATE_ATTACHED			0x1
#define USB_STATE_POWERED			0x2
#define USB_STATE_DEFAULT			0x3
#define USB_STATE_ADDRESS			0x4
#define USB_STATE_CONFIGURED		0x5
#define USB_STATE_SUSPENDED			0x6


#endif
