include ../Makefile.am
include configs/current.am


LIBC = 	klibc/typeconv.o klibc/time.o klibc/string.o klibc/stdio.o klibc/math.o \
		klibc/malloc.o klibc/assert.o


GSOURCES = 	task/task.o task/message.o task/term.o \
			mm/mm.o mm/phys.o \
			fs/fs.o fs/devfs.o fs/mount.o fs/fsop.o \
			video.o syscall.o driver.o device.o main.o
		
SOURCES = $(BOOT) $(BUILTIN) $(GSOURCES) $(LIBC)

CFLAGS =  -fno-stack-protector $(EXFLAGS) -nostdlib -nostdinc -fno-builtin -nodefaultlibs  -I"." -I"include" -I"include/klibc" 
LDFLAGS = -Tlink.ld
ASFLAGS = -felf

all: $(SOURCES) link

clean:
	-rm $(SOURCES) kernel

link:
	$(LD) -T link.ld -o kernel $(SOURCES)


