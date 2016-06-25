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
gcd:
sub esp, 4
mov edi, 8
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
mov eax, 0
push eax
pop ebx
pop eax
cmp eax, ebx
mov eax, 0
sete al
cmp eax, 0
je $MYLABEL0
mov edi, 4
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
mov edi, 12
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
jmp $MYLABEL1
$MYLABEL0:
push eax
mov edi, 4
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
mov edi, 8
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
pop ebx
pop eax
xor edx, edx
idiv ebx
mov eax,edx
push eax
mov edi, 8
mov esi, ecx
add esi, edi
mov eax, [esi]
push eax
push ecx
mov ecx, esp
call gcd
pop ecx
pop eax
pop eax
pop eax
push eax
mov edi, 12
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
$MYLABEL1:
add esp, 4
ret
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
$MYLABEL8:
mov eax, 10
push eax
mov edi, -48
mov esi, ecx
add esi, edi
mov eax, [esi]
pop ebx
cmp eax, ebx
ja $MYLABEL9
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
jmp $MYLABEL8
$MYLABEL9:
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
mov eax, 55
push eax
pop ebx
pop eax
cmp eax, ebx
mov eax, 0
sete al
cmp eax, 0
je $MYLABEL20
push eax
mov eax, 45
push eax
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
push ecx
mov ecx, esp
call gcd
pop ecx
pop eax
pop eax
pop eax
push eax
mov edi, -48
mov esi, ecx
add esi, edi
mov eax, [esi]
pop eax
mov [esi-0], eax
mov edi, -48
mov esi, ecx
add esi, edi
mov eax, [esi]
pusha
invoke crt_printf,offset lb_writeln_int, eax
popa
$MYLABEL20:
add esp, 48
ret
main ENDP
END main
