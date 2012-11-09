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
 * \file kernel/include/klibc/stdarg.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef KLIBC_STDARG_H
#define KLIBC_STDARG_H

/**
 * Lista di argomenti
 */
typedef void * va_list;

#define va_start(list, lastpar) (list = &lastpar)
#define va_arg(list, type) *((type *)(list += sizeof(int)))
#define va_end(list) do {} while(0)

#endif
