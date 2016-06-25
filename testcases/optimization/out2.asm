.586
.model flat,stdcall
include msvcrt.inc
includelib msvcrt.lib
.const
lb_write_int db '%d',0
lb_writeln_int db '%d',0ah,0dh,0
lb_write_real db '%lf',0
lb_writeln_real db '%lf',0ah,0dh,0
lb_tmp db 0, 0, 0, 0, 0, 0, 0, 0
lb_read_int db '%d',0
lb_read_real db '%f',0
.data
.code
main PROC
mov ecx, esp
sub esp, 48
mov eax, 10
push eax
mov eax, 2
push eax
pop ebx
pop eax
xor edx, edx
cmp ebx, 2
je $MYLABEL2
cmp eax, 2
je $MYLABEL1
imul ebx
jmp $MYLABEL0
$MYLABEL2:
sal eax, 1
jmp $MYLABEL0
$MYLABEL1:
sal ebx, 1
$MYLABEL0:
push eax
mov edi, -48
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
mov eax, 9998
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
$MYLABEL4:
jmp $MYLABEL6
$MYLABEL5:
mov eax, 9995
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
$MYLABEL6:
mov eax, 9993
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
$MYLABEL7:
mov eax, 9992
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
jmp $MYLABEL7
$MYLABEL8:
$MYLABEL9:
mov eax, 9991
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
jmp$MYLABEL9
add esp, 48
ret
main ENDP
END main
