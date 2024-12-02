.586
.MODEL FLAT, STDCALL
includelib kernel32.lib

ExitProcess PROTO : DWORD
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD

.stack 4096

.const

.data
A DD 2
B DD 7
STR1 DB "Программа сложения", 0
STR2 DB "Результат сложения = ", 0

.code
main PROC
    mov eax, A
    add eax, B
    add eax, 30h
    mov STR2 + sizeof STR2 - 1, al
    invoke MessageBoxA, 0, offset STR2, offset STR1, 0
    push 0
    call ExitProcess
main ENDP


end main
