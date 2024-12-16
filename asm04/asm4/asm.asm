.586
.MODEL FLAT, stdcall
includelib kernal32.lib
ExitProcess PROTO : DWORD
.STACK 4096
.CONST
.DATA
stdout DWORD ?
INT0	SDWORD	12
UNSIGNEDINT1	DWORD	23

.CODE
main PROC
START:
push 0
call ExitProcess
main ENDP
end main
