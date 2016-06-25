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
mov eax, 1
push eax
mov eax, 1
mov ebx, 1
sub eax, ebx
sal eax, 2
mov edi, -44
add edi, eax
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
mov eax, 1
push eax
mov eax, 2
mov ebx, 1
sub eax, ebx
sal eax, 2
mov edi, -44
add edi, eax
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
mov eax, 1
mov ebx, 1
sub eax, ebx
sal eax, 2
mov edi, -44
add edi, eax
mov esi, ecx
add esi, edi
mov eax, [esi]
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
mov eax, 2
mov ebx, 1
sub eax, ebx
sal eax, 2
mov edi, -44
add edi, eax
mov esi, ecx
add esi, edi
mov eax, [esi]
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
mov eax, 3
push eax
mov edi, -48
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
$MYLABEL0:
mov eax, 10
push eax
mov edi, -48
mov esi, ecx
add esi, edi
mov eax, [esi]
pop ebx
cmp eax, ebx
ja $MYLABEL1
mov edi, -48
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
mov eax, 1
push eax
pop ebx
pop eax
sub eax, ebx
mov ebx, 1
sub eax, ebx
sal eax, 2
mov edi, -44
add edi, eax
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
mov edi, -48
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
mov eax, 2
push eax
pop ebx
pop eax
sub eax, ebx
mov ebx, 1
sub eax, ebx
sal eax, 2
mov edi, -44
add edi, eax
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
pop ebx
pop eax
add eax, ebx
push eax
mov edi, -48
mov esi, ecx
add esi, edi
mov eax, [esi]
mov ebx, 1
sub eax, ebx
sal eax, 2
mov edi, -44
add edi, eax
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
mov edi, -48
mov esi, ecx
add esi, edi
mov eax, [esi]
mov ebx, 1
sub eax, ebx
sal eax, 2
mov edi, -44
add edi, eax
mov esi, ecx
add esi, edi
mov eax, [esi]
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
mov edi, -48
mov esi, ecx
add esi, edi
mov eax, [esi]
inc eax
mov [esi-0], eax
jmp $MYLABEL0
$MYLABEL1:
add esp, 48
ret
main ENDP
END main
