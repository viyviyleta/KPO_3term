.586
.MODEL FLAT, stdcall

includelib kernel32.lib

ExitProcess PROTO : DWORD
GetStdHandle PROTO : DWORD
WriteConsoleA PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD

.STACK 4096

.CODE

getmin PROC ad : DWORD, len : DWORD
mov esi, ad
mov ecx, len
mov eax, [esi]
add esi, 4

next_element:
dec ecx
jz end_getmin

mov ebx, [esi]
cmp ebx, eax
jl new_min

skip :
add esi, 4
jmp next_element

new_min :
mov eax, ebx
jmp skip

end_getmin :
	ret
getmin ENDP



getmax PROC ad : DWORD, len : DWORD
mov esi, ad
mov ecx, len
mov eax, [esi]
add esi, 4

next_element:
dec ecx
jz end_getmax

mov ebx, [esi]
cmp ebx, eax
jg new_max

skip :
add esi, 4
jmp next_element

new_max :
mov eax, ebx
jmp skip

end_getmax :
	ret
getmax ENDP

int_to_char PROC uses eax ebx ecx edi esi,
pstr : dword,                                            ; ����� ������ ����������
intfield : sdword                                        ; ����� ��� ��������������
mov edi, pstr                                            ; �������� �� pstr � edi
mov esi, 0                                               ; ���������� �������� � ���������� 
mov eax, intfield                                        ; ����� -> � eax
cdq                                                      ; ���� ����� ���������������� � eax �� edx
mov ebx, 10                                              ; ��������� ������� ��������� (10) -> ebx
idiv ebx                                                 ; eax = eax/ebx, ������� � edx (������� ����� �� ������)
test eax, 80000000h                                      ; ��������� �������� ���
jz plus                                                  ; ���� ������������� ����� - �� plus
neg eax                                                  ; ����� ������ ���� eax
neg edx                                                  ; edx = -edx
mov cl, '-'                                              ; ������ ������ ���������� '-'
mov[edi], cl                                             ; ������ ������ ���������� '-'
inc edi                                                  ; ++edi

plus :                                                   ; ���� ���������� �� �������� 10
push dx                                                  ; ������� -> ����
inc esi                                                  ; ++esi
test eax, eax                                            ; eax == ?
jz fin                                                   ; ���� ��, �� �� fin
cdq                                                      ; ���� ���������������� � eax �� edx 
idiv ebx                                                 ; eax = eax/ebx, ������� � edx
jmp plus                                                 ; ����������� ������� �� plus

fin :                                                    ; � ecx ���-�� �� 0-��� �������� = ���-�� �������� ����������
mov ecx, esi
write :                                                  ; ���� ������ ����������
pop bx                                                   ; ������� �� ����� -> bx
add bl, '0'                                              ; ������������ ������ � bl
mov[edi], bl                                             ; bl -> � ���������
inc edi                                                  ; edi++
loop write                                               ; ���� (--ecx)>0 ������� �� write
ret
int_to_char ENDP

printconsole proc uses eax ebx ecx edi esi,
					pstr :dword,
					size :dword
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
		push size
		push pstr
		push eax 
		call WriteConsoleA 
	ret
printconsole ENDP

end
