#include ../Makefile.am

SOURCES = main.o 
CC = gcc
CFLAGS =  -fno-stack-protector -nostdlib -nostdinc -fno-builtin -nodefaultlibs  
LIB = ../../lib/libc/libc.a

all: 
	gcc $(CFLAGS) main.c -o test $(LIB)
#$(SOURCES) link

clean:
	rm test $(SOURCES)
	
link:
	$(LD) $(LDFLAGS) -o test $(SOURCES) $(LIB)
