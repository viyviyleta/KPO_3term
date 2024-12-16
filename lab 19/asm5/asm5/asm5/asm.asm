.586
.MODEL FLAT, stdcall
includelib kernel32.lib
includelib user32.lib
includelib libucrt.lib
includelib msvcrt.lib

ExitProcess PROTO :DWORD

.STACK 4096

.DATA
    mas DWORD 10, 2, 3, 4, 5, 6, 7, 8, 1, 9     

.CODE

getmin PROC ad:DWORD, len:DWORD
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

skip:
    add esi, 4           
    jmp next_element     

new_min:
    mov eax, ebx  
    jmp skip            

end_getmin:
    ret                 
getmin ENDP

main PROC
    push LENGTHOF mas          
    push OFFSET mas     
    call getmin   

    push 0              
    call ExitProcess    
main ENDP
end main