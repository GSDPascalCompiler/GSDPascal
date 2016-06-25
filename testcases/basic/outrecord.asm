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
$REALDATA0 dd 99.9
.code
main PROC
mov ecx, esp
sub esp, 12
mov eax, 10
push eax
mov edi, -12
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
mov eax, $REALDATA0
push eax
mov edi, -8
mov esi, ecx
add esi, edi
mov eax, dword ptr [esi]
pop eax
mov [esi-0], eax
mov edi, -12
mov esi, ecx
add esi, edi
mov eax, [esi]
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
mov edi, -8
mov esi, ecx
add esi, edi
mov eax, dword ptr [esi]
pusha
push eax
fld dword ptr [esp]
sub esp, 4
fstp qword ptr [esp]
push offset lb_writeln_real
call crt_printf
add esp, 8
pop eax
popa
add esp, 12
ret
main ENDP
END main
