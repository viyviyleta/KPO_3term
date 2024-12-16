.586
.MODEL FLAT, stdcall
includelib kernel32.lib
includelib user32.lib
includelib libucrt.lib
includelib msvcrtd.lib
includelib "..\Debug\StaticLib2.lib"
getmin PROTO : DWORD, : DWORD
getmax PROTO : DWORD, : DWORD

ExitProcess PROTO :DWORD
SetConsoleOutputCP PROTO : DWORD 
SetConsoleCP PROTO : DWORD
GetStdHandle PROTO : DWORD
WriteConsoleA PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD
.STACK 4096

.DATA
    mas DWORD 1, 2, 3, 4, 5, 6, 7, 8, 9, 20     
    sum DWORD 0
    buf BYTE "getmin+getmax=", 0
    outp BYTE 10 dup(0)
.CODE
push 1251d
call SetConsoleOutputCP
push 1251d
call SetConsoleCP


int_to_char PROC uses eax ebx ecx edi esi,
pstr : dword, ; ����� ������ ����������
intfield : sdword ; ����� ��� ��������������
mov edi, pstr ; �������� �� pstr � edi
mov esi, 0 ; ���������� �������� � ���������� 
mov eax, intfield ; ����� -> � eax
cdq ; ���� ����� ���������������� � eax �� edx
mov ebx, 10 ; ��������� ������� ��������� (10) -> ebx
idiv ebx ; eax = eax/ebx, ������� � edx (������� ����� �� ������)
test eax, 80000000h ; ��������� �������� ���
jz plus ; ���� ������������� ����� - �� plus
neg eax ; ����� ������ ���� eax
neg edx ; edx = -edx
mov cl, '-' ; ������ ������ ���������� '-'
mov[edi], cl ; ������ ������ ���������� '-'
inc edi ; ++edi
plus : ; ���� ���������� �� �������� 10
push dx ; ������� -> ����
inc esi ; ++esi
test eax, eax ; eax == ?
jz fin ; ���� ��, �� �� fin
cdq ; ���� ���������������� � eax �� edx 
idiv ebx ; eax = eax/ebx, ������� � edx
jmp plus ; ����������� ������� �� plus
fin : ; � ecx ���-�� �� 0-��� �������� = ���-�� �������� ����������
mov ecx, esi
write : ; ���� ������ ����������
pop bx ; ������� �� ����� -> bx
add bl, '0' ; ������������ ������ � bl
mov[edi], bl ; bl -> � ���������
inc edi ; edi++
loop write ; ���� (--ecx)>0 ������� �� write
ret
int_to_char ENDP

printconsole proc uses eax ebx ecx edi esi,
					pstr :dword,
					siz :dword
	push -11
	call GetStdHandle
	mov esi, pstr
	mov edi, -1
	count:
		inc edi 
		cmp byte ptr [esi + edi], 0
		jne count 
		push 0
		push 0 
		push siz
		push pstr
		push eax 
		call WriteConsoleA 
	ret
printconsole ENDP

main PROC

    push LENGTHOF mas          
    push OFFSET mas     
    call getmin   
    
    mov sum, eax

    push LENGTHOF mas          
    push OFFSET mas     
    call getmax 

    add eax, sum
 
    push eax
    push OFFSET outp
    call int_to_char

    push sizeof buf
    push OFFSET buf
    call printconsole

    push sizeof outp
    push offset outp
    call printconsole
    push 0              
    call ExitProcess    
main ENDP
end main