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
 * \file screenpig/window.h
 * \date 01-17-2010
 * \author Davide Gessa
 */
#ifndef SCREENPIG_WINDOW_H
#define SCREENPIG_WINDOW_H

#include <types.h>

#define SP_PATH_WIN_TOP_RIGHT	"/initr/top-right.raw"
#define SP_PATH_WIN_TOP_LEFT	"/initr/top-left.raw"
#define SP_PATH_WIN_TITLE5		"/initr/title-5.raw"
#define SP_PATH_WIN_TITLE4		"/initr/title-4.raw"
#define SP_PATH_WIN_TITLE3		"/initr/title-3.raw"
#define SP_PATH_WIN_TITLE2		"/initr/title-2.raw"
#define SP_PATH_WIN_TITLE1		"/initr/title-1.raw"
#define SP_PATH_WIN_STICK		"/initr/stick.raw"
#define SP_PATH_WIN_STICK_PRESS	"/initr/stick-pressed.raw"
#define SP_PATH_WIN_SHADE		"/initr/shade.raw"
#define SP_PATH_WIN_SHADE_PRESS	"/initr/shade-pressed.raw"
#define SP_PATH_WIN_RIGHT		"/initr/right.raw"
#define SP_PATH_WIN_MENU		"/initr/menu.raw"
#define SP_PATH_WIN_MENU_PRESS	"/initr/menu-pressed.raw"
#define SP_PATH_WIN_MAXIM		"/initr/maximize.raw"
#define SP_PATH_WIN_MAXIM_PRESS	"/initr/maximize-pressed.raw"
#define SP_PATH_WIN_LEFT		"/initr/left.raw"
#define SP_PATH_WIN_HIDE		"/initr/hide.raw"
#define SP_PATH_WIN_HIDE_PRESS	"/initr/hide-pressed.raw"
#define SP_PATH_WIN_CLOSE		"/initr/close.raw"
#define SP_PATH_WIN_CLOSE_PRESS	"/initr/close-pressed.raw"
#define SP_PATH_WIN_BOTTOM		"/initr/bottom.raw"
#define SP_PATH_WIN_BOTTOM_RT	"/initr/bottom-right.raw"
#define SP_PATH_WIN_BOTTOM_LF	"/initr/bottom-left.raw"


/**
 * Struttura di una finestra
 */
typedef struct window_p
{
	uint32_t x;					///< Posizione x
	uint32_t y;					///< Posizione y
	uint32_t size_x;			///< Dimensione x
	uint32_t size_y;			///< Dimensione y
	
	uint32_t level;				///< Livello di rendering
	
	uint8_t if_decorated;		///< Disegnare le decorazioni?
		
	char label[64];				///< Titolo finestra
	uint8_t if_updated;			///< Finestra aggiornata?
		
	struct window_p *next;		///< Prossima finestra
} window_t;


window_t *window_list;		///< Lista finestre


char win_title4[10*25*4];
char win_title3[10*25*4];
char win_title2[10*25*4];
char win_title5[5*25*4];
char win_top_left[5*25*4];
char win_top_right[5*25*4];
char win_close[18*20*4];
char win_hide[18*20*4];
char win_bottom[5*5*4];
char win_right[5*5*4];
char win_left[5*5*4];
char win_bottom_lf[20*20*4];
char win_bottom_rt[20*20*4];


window_t *window_new(char *, uint32_t, uint32_t, uint32_t, uint32_t);
void window_render(window_t *);
void window_delete(window_t *);
void window_load_default_dec();

#endif

