include ../../../Makefile.am

SOURCES = cat.o ../../../lib/libc/libc.a

all: $(SOURCES) link

clean:
	rm cat $(SOURCES)
	
link:
	$(LD) $(LDFLAGS) -o cat $(SOURCES) $(LIB)
