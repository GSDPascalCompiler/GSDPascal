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
swap:
sub esp, 8
mov edi, 4
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
mov edi, -8
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
mov edi, 8
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
mov edi, 4
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
mov edi, 8
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
add esp, 8
ret
main PROC
mov ecx, esp
sub esp, 12
mov eax, 10
push eax
mov edi, -8
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
mov eax, 5
push eax
mov edi, -12
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
mov eax, 3
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
mov eax, 10
push eax
pop ebx
pop eax
add eax, ebx
push eax
mov eax, 7
push eax
pop ebx
pop eax
xor edx, edx
idiv ebx
mov eax,edx
push eax
mov eax, 5
push eax
pop ebx
pop eax
xor edx, edx
cmp ebx, 2
je $MYLABEL11
idiv ebx
jmp $MYLABEL9
$MYLABEL11:
sar eax, 1
$MYLABEL9:
push eax
mov eax, 1
push eax
pop ebx
pop eax
add eax, ebx
push eax
mov edi, -8
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
mov edi, -12
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
mov eax, 5
push eax
pop ebx
pop eax
xor edx, edx
cmp ebx, 2
je $MYLABEL17
idiv ebx
jmp $MYLABEL15
$MYLABEL17:
sar eax, 1
$MYLABEL15:
push eax
mov eax, 4
push eax
mov eax, 3
push eax
mov eax, 2
push eax
pop ebx
pop eax
sub eax, ebx
push eax
pop ebx
pop eax
xor edx, edx
cmp ebx, 2
je $MYLABEL23
cmp eax, 2
je $MYLABEL22
imul ebx
jmp $MYLABEL21
$MYLABEL23:
sal eax, 1
jmp $MYLABEL21
$MYLABEL22:
sal ebx, 1
$MYLABEL21:
push eax
pop ebx
pop eax
add eax, ebx
push eax
mov eax, 5
push eax
pop ebx
pop eax
xor edx, edx
cmp ebx, 2
je $MYLABEL29
idiv ebx
jmp $MYLABEL27
$MYLABEL29:
sar eax, 1
$MYLABEL27:
push eax
mov edi, -12
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
mov edi, -12
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
pop ebx
pop eax
cmp eax, ebx
mov eax, 0
setg al
cmp eax, 0
je $MYLABEL31
mov edi, -12
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
mov edi, -8
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
push ecx
mov ecx, esp
call swap
pop ecx
mov edi, -8
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi],eax
mov edi, -12
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi],eax
$MYLABEL31:
mov edi, -8
mov esi, ecx
add esi, edi
mov eax, [esi]
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
mov edi, -12
mov esi, ecx
add esi, edi
mov eax, [esi]
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
add esp, 12
ret
main ENDP
END main
