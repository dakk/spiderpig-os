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
 * \file term.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef TERM_H
#define TERM_H

#include <types.h>

#define TERM_STD_SIZE	1024


/**
 * Struttura di un terminale
 */
typedef struct term_p
{
	char name[32];					///< Titolo del terminale
	char dfile[32];					///< Device file
	char *data;						///< Area dati
	char *input;					///< Stream di input
	unsigned cursor_pos;			///< Posizione del cursore
	char color;						///< Colore corrente
	size_t size;					///< Dimensione area dati

	struct term_p *next;			///< Puntatore al prossimo terminale
} term_t;

term_t *term_new(size_t);
void term_delete(term_t *);
void term_set_title(term_t *, char *);

#endif
