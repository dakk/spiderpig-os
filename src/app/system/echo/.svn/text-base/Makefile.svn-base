include ../../../Makefile.am

SOURCES = echo.o ../../../lib/libc/libc.a

all: $(SOURCES) link

clean:
	rm echo $(SOURCES)
	
link:
	$(LD) $(LDFLAGS) -o echo $(SOURCES) $(LIB)
