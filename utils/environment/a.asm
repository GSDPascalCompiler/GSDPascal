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
l2:
sub esp, 8
mov edi, -8
mov esi, ecx
add esi, edi
mov eax, [esi]
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
mov edi, -8
mov esi, ecx
mov eax, [esi]
mov esi, eax
add esi, edi
mov eax, [esi]
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
add esp, 8
ret
l1:
sub esp, 8
mov eax, 1
push eax
mov edi, -8
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
push eax
mov edi, 4
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
mov eax, 1
push eax
pop ebx
pop eax
add eax, ebx
push eax
push ecx
mov ecx, esp
call l2
pop ecx
pop eax
pop eax
push eax
mov edi, 8
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
mov edi, -8
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
mov eax, 1
push eax
pop ebx
pop eax
add eax, ebx
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
add esp, 8
ret
main PROC
mov ecx, esp
sub esp, 8
push eax
mov eax, 1
push eax
push ecx
mov ecx, esp
call l1
pop ecx
pop eax
pop eax
push eax
mov edi, -8
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
mov edi, -8
mov esi, ecx
add esi, edi
mov eax, [esi]
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
add esp, 8
ret
main ENDP
END main
