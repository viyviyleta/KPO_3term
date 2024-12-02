.586
.MODEL FLAT, STDCALL
includelib kernel32.lib

ExitProcess PROTO : DWORD
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD

.stack 4096

.const

.data
myBytes BYTE 10h, 20h, 30h, 40h
myWords WORD 8Ah, 3Bh, 44h, 5Fh, 99h
myDoubles DWORD 1, 2, 3, 4, 5, 6
myPointer DWORD myDoubles
myArr DWORD 1, 2, 3, 0, 5, 6, 7
SUCESS BYTE "Положительный", 0
FAIL BYTE "Отрицательный", 0
STR1 BYTE "Бабич Виолетта, 2 курс, 7 группа", 0
STR2 BYTE " ", 0

.code
main PROC
	mov ESI, OFFSET myWords
	mov AX, [ESI + 4]			; AX = 68 (44)
	mov BX, [ESI + 2]			; BX = 59 (3B)

	xor eax, eax
	mov esi, offset myArr
	mov ecx, lengthof myArr

CYCLE1:
	add eax, [esi]
	add esi, type myArr
	loop CYCLE1

	xor eax, eax
	mov ebx, 1
	mov esi, offset myArr
	mov ecx, lengthof myArr

CYCLE2:
	cmp dword ptr [esi], 0
	je FOUND_ZERO
	add esi, type myArr
	loop CYCLE2

	jmp NOT_FOUND_ZERO

FOUND_ZERO:
	mov ebx, 0
	mov edi, OFFSET SUCESS
	jmp SHOW_MESSAGE

NOT_FOUND_ZERO:
    mov edi, OFFSET FAIL
    jmp SHOW_MESSAGE

SHOW_MESSAGE:
    invoke MessageBoxA, 0, edi, offset STR1, 0

	push 0
	call ExitProcess
main ENDP

end main