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
 * \file kernel/klibc/time.c
 * \author Davide Gessa
 * \note Gestione ora e data
 * \date 10-12-09
 */
#include <klibc/time.h>
#include <types.h>
/*
asctime 	Converte il valore contenuto nella struttura di tipo tm passatale in una stringa simile a "Mon Aug 28 12:38:13 2006\n\0".
clock 	Restituisce il numero di "tick" della CPU utilizzati dal processo sin da quando è partito.
ctime 	Converte il tempo di calendario (tipo time_t *) in una stringa: è equivalente ad asctime(localtime(tp)).
difftime 	Restituisce la differenza in secondi tra due tempi di calendario (tipo time_t).
gmtime 	Converte il tempo di calendario (tipo time_t *) in una struttura tm (intesa come ora UTC).
localtime 	Converte il tempo di calendario (tipo time_t) in una struttura tm (intesa come ora locale).
mktime 	Converte una struttura tm in un valore di tempo di calendario (tipo time_t) (intesa come ora locale).
time 	Restituisce l'attuale tempo di calendario (tipo time_t).
*/


struct tm *localtime(const time_t *timer)
{
	return NULL;
}
