.586
.MODEL FLAT, stdcall
includelib kernel32.lib
includelib user32.lib
includelib libucrt.lib
includelib msvcrt.lib
includelib "..\Debug\StaticLib1.lib"
getmin PROTO : DWORD, : DWORD
getmax PROTO : DWORD, : DWORD
int_to_char PROTO :DWORD, :DWORD
printconsole PROTO : DWORD

ExitProcess PROTO :DWORD
SetConsoleOutputCP PROTO : DWORD 
SetConsoleCP PROTO : DWORD
.STACK 4096

.DATA
    mas DWORD 1, 2, 3, 4, 5, 6, 7, 8, 9, 10     
    sum DWORD 0
    buf BYTE "getmin+getmax=", 0
    outp BYTE 10 dup(0)
.CODE
push 1251d
call SetConsoleOutputCP
push 1251d
call SetConsoleCP


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