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
pstr : dword, ; адрес строки результата
intfield : sdword ; число для преобразования
mov edi, pstr ; копирует из pstr в edi
mov esi, 0 ; количество символов в результате 
mov eax, intfield ; число -> в eax
cdq ; знак числа распространяется с eax на edx
mov ebx, 10 ; основание системы счисления (10) -> ebx
idiv ebx ; eax = eax/ebx, остаток в edx (деление целых со знаком)
test eax, 80000000h ; тестируем знаковый бит
jz plus ; если положительное число - на plus
neg eax ; иначе мнеяем знак eax
neg edx ; edx = -edx
mov cl, '-' ; первый символ результата '-'
mov[edi], cl ; первый символ результата '-'
inc edi ; ++edi
plus : ; цикл разложения по степеням 10
push dx ; остаток -> стек
inc esi ; ++esi
test eax, eax ; eax == ?
jz fin ; если да, то на fin
cdq ; знак распространяется с eax на edx 
idiv ebx ; eax = eax/ebx, остаток в edx
jmp plus ; безусловный переход на plus
fin : ; в ecx кол-во не 0-вых остатков = кол-ву символов результата
mov ecx, esi
write : ; цикл записи результата
pop bx ; остаток из стека -> bx
add bl, '0' ; сформировали символ в bl
mov[edi], bl ; bl -> в результат
inc edi ; edi++
loop write ; если (--ecx)>0 переход на write
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