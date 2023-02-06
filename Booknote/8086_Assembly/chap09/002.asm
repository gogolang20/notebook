assume cs:code,ds:data,ss:stack

;#---------------------------------------#
data segment
            db      128 dup (0)
data ends

;#---------------------------------------#
stack segment stack
             db      128 dup (0)
stack ends

;#---------------------------------------#
code segment

start:      mov ax,stack
            and ss,ax
            mov sp,128

            mov ax,data
            mov ds,ax

            mov ax,2233H
            mov ds:[0],ax

            mov word ptr ds:[2],4455H

            jmp dword ptr ds:[0]        ;IP = ds:[0]  CS = ds:[2]
            
;#---------------------------------------#
            mov ax,4C00H
            int 21H
        
code ends
;#---------------------------------------#


end start
