
global syscallisr

extern syscall_callback

syscallisr:
       ;push ds
       ;push es
       ;pusha
       ;mov eax,0x10
       ;mov ds,eax
       ;mov es,eax
       ;mov eax,esp                    ;eax = pointer to the structure on the stack
       ;cli
       call syscall_callback
       ;sti
       ;popa
       ;pop es
       ;pop ds
       iret
