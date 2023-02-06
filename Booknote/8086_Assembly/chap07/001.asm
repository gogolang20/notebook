assume cs:code,ds:data,ss:stack

;#---------------------------------------#
data segment
            db      '012345abcdefg hijk !!!'
data ends

;#---------------------------------------#
stack segment stack
            dw      0,0,0,0,0,0,0,0
            dw      0,0,0,0,0,0,0,0
stack ends

;#---------------------------------------#
code segment

start:      mov al,00001010B
            and al,00001111B

            mov al,00001111B
            or  al,11110000B

            mov bx,stack
            mov ss,bx
            mov sp,20H

            mov bx,data
            mov ds,bx

            mov al,'a'
            mov al,'b'

;#---------------------------------------#
            mov ax,4C00H
            int 21H
        
code ends
;#---------------------------------------#


end start
