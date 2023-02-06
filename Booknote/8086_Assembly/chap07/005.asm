assume cs:code,ds:data

;#---------------------------------------#
data segment
            db      'ibm            ,'
            db      'des            ,'
            db      'dos            ,'
            db      'vax            ,'

data ends

;#---------------------------------------#
code segment

start:      mov ax,data
            mov ds,ax

            mov bx,0
            mov cx,4

upRow:      mov dx,cx
            mov cx,3
            mov si,0

upLetter:   mov al,ds:[bx+si]
            and al,11011111B    ;lower to upper letter
            mov ds:[bx+si],al
            inc si
            loop upLetter

            mov cx,dx
            add bx,10H
            loop upRow

;#---------------------------------------#
            mov ax,4C00H
            int 21H
        
code ends
;#---------------------------------------#


end start
