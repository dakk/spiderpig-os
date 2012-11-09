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
 * \file kernel/include/video.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef VIDEO_H
#define VIDEO_H

#include <types.h>

#define VIDEO_BLACK_BLACK             0x00
#define VIDEO_BLUE_BLACK              0x01
#define VIDEO_GREEN_BLACK             0x02
#define VIDEO_CYAN_BLACK              0x03
#define VIDEO_RED_BLACK               0x04
#define VIDEO_MAGENTA_BLACK           0x05
#define VIDEO_YELLOW_BLACK            0x06
#define VIDEO_WHITE_BLACK             0x07
#define VIDEO_HI_BLACK_BLACK          0x08
#define VIDEO_HI_BLUE_BLACK           0x09
#define VIDEO_HI_GREEN_BLACK          0x0A
#define VIDEO_HI_CYAN_BLACK           0x0B
#define VIDEO_HI_RED_BLACK            0x0C
#define VIDEO_HI_MAGENTA_BLACK        0x0D
#define VIDEO_HI_YELLOW_BLACK         0x0E
#define VIDEO_HI_WHITE_BLACK          0x0F

#define VIDEO_MEM		0xB8000
#define VIDEO_TAB_DIM	5
#define VIDEO_MAX_X		80
#define VIDEO_MAX_Y		25

typedef uint8_t vcolor_t;

vcolor_t video_std_color;

void video_backspace();
void video_move_cursor(uint8_t, uint8_t);
void video_set_color(vcolor_t);
void video_putchar(uint8_t);
void video_puts_colored(vcolor_t, uint8_t *);
void video_putint(int);
void video_puts(uint8_t *);
void video_gotoxy(uint8_t, uint8_t);
void video_clear();
void video_scroll_dw();
uint8_t video_gety();
uint8_t video_getx();

#endif
