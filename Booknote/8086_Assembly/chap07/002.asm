assume cs:code,ds:data,ss:stack

;#---------------------------------------#
data segment
            db      'BaSic'
            db      'INFOrMaTiOn'
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

upLetter:   mov al,ds:[bx]
            and al,11011111B    ;lower to upper letter
            mov ds:[bx],al
            inc bx
            loop upLetter

            mov bx,5
            mov cx,11

downLetter: mov al,ds:[bx]
            or  al,00100000B   ;upper to lower letter
            mov ds:[bx],al
            inc bx
            loop downLetter


;#---------------------------------------#
            mov ax,4C00H
            int 21H
        
code ends
;#---------------------------------------#


end start
