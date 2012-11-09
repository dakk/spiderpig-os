ARCH = x86


PROMPT = " -> " 

LD = @echo "   " $(PROMPT) LD "    " $ && ld
CC = @echo "   " $(PROMPT) CC "    " $< && gcc
TCC = @echo "   " $(PROMPT) CC "    " $< && tcc
ASM = @echo "   " $(PROMPT) ASM "   " $< && nasm
AR = @echo "   " $(PROMPT) AR "    " $ && ar
CD = @echo  $(PROMPT) CD "        " && cd


.c.o: 
	$(CC) -c $(CFLAGS) -o "$@" "$<"

.s.o:
	$(ASM) $(ASFLAGS) $<
	

