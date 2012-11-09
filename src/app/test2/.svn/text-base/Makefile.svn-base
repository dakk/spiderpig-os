include ../../Makefile.am

all:
	$(ASM) -felf main.asm
	$(LD) -T ../link.ld -o test2 main.o

clean:
	rm main.o test2
