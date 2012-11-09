include ../../Makefile.am

SOURCES = assert.o malloc.o math.o stdio.o string.o time.o stdlib.o \
			dirent.o \
			sys/socket.o \
			system/syscall.o system/driver.o system/sysutils.o 
CFLAGS = -I. -I../include/libc -fno-stack-protector -nostdlib -nostdinc -fno-builtin -nodefaultlibs 


all: $(SOURCES)
	$(AR) rcs libc.a $(SOURCES)


clean:
	rm $(SOURCES) libc.a


