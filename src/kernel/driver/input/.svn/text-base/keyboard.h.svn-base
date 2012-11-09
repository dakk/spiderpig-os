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
 * \file kernel/driver/hid/keyboard.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef DRIVER_HID_KEYBOARD_H
#define DRIVER_HID_KEYBOARD_H

#include <types.h>
#include <driver.h>
#include <klibc/ctype.h>

#define IRQ_KEYBOARD	1
#define	SHIFT_LEFT		0x2A
#define	SHIFT_RIGHT		0x36
#define PAGE_UP			0x49
#define PAGE_DOWN		0x51
#define LOCK_CAPS		0x3A
#define LOCK_NUM		0x45
#define LED_NUM			2
#define LED_CAPS		4


extern driver_t driver_keyboard;

unsigned shift;
unsigned alt;
unsigned control;
unsigned capslock;
unsigned numlock;

char buf[256];
uint8_t bufsize;
uint8_t bufwhere;
uint8_t bufpoint;

char keyboard_getchar();
static void keyboard_callback(regs_t *);
uint32_t keyboard_init();
void keyboard_update_leds(uint8_t);
uint32_t keyboard_free();
uint32_t keyboard_read(char *, uint32_t, uint64_t);
uint32_t keyboard_probe(device_t *);

#endif
