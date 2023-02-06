assume cs:code,ds:data,ss:stack

;#---------------------------------------#
data segment
            db      'BaSic'
            db      'MinIX'
data ends

;#---------------------------------------#
stack segment stack
            dw      0,0,0,0
            dw      0,0,0,0
            dw      0,0,0,0
            dw      0,0,0,0
stack ends

;#---------------------------------------#
code segment

start:      mov bx,stack
            mov ss,bx
            mov sp,80H

            mov bx,data
            mov ds,bx

            mov bx,0
            mov cx,5


modLetter:  mov al,ds:[bx]
            and al,11011111B    ;lower to upper letter
            mov ds:[bx],al
            mov al,ds:[bx+5]
            or  al,00100000B    ;upper to lower letter
            mov ds:[bx+5],al
            inc bx
            loop modLetter

;#---------------------------------------#
            mov ax,4C00H
            int 21H
        
code ends
;#---------------------------------------#


end start
