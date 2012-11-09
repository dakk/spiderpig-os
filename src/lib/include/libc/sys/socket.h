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
 * \file lib/include/libc/sys/socket.h
 * \author Davide Gessa
 * \date 10-12-09
 */
#ifndef LIBC_SYS_SOCKET_H
#define LIBC_SYS_SOCKET_H

#include <ctype.h>
                   
struct sockaddr
{
	char a;
};

typedef size_t ssize_t;
typedef unsigned socklen_t;
                   
int socket(int, int, int);
int connect(int, const struct sockaddr *, socklen_t);
ssize_t send(int, const void *, size_t len, int flags);
ssize_t sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
ssize_t recv(int, void *, size_t, int);
ssize_t recvfrom(int, void *, size_t, int, struct sockaddr *, socklen_t *);                   
int shutdown(int, int);
                                      
#endif
