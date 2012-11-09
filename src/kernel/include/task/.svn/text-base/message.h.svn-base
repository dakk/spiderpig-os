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
 * \file kernel/include/task/message.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef MESSAGE_H
#define MESSAGE_H

#define MESSAGE_BUFFER_MAX	255
#define MESSAGE_MAX		255

#define MESSAGE_STATE_OK		1
#define MESSAGE_STATE_HEAVY	-3
#define MESSAGE_STATE_FULL		-2
#define MESSAGE_STATE_UNKN		-1
	
#include <types.h>
 	
/**
 * Struttura di un messaggio
 */
typedef struct message_p
{
	char 		*data;					///< Dati del messaggio
	uint32_t	size;					///< Dimensione dei dati
	pid_t		pid;					///< Mittente
	struct		message_p *next;		///< Prossimo messaggio
} message_t;


uint32_t message_send(pid_t, char *, uint32_t);
uint32_t message_recv(char *, pid_t *);
void message_clear();

#endif
