assume cs:code,ds:data,ss:stack


;#---------------------------------------#
data segment
            dw 0,1,2,3,4,5,6,7,8

data ends

;#---------------------------------------#
stack segment stack
            dw      0,0,0,0,0,0,0,0
            dw      0,0,0,0,0,0,0,0

stack ends

;#---------------------------------------#
code segment

start:      mov bx,0
            mov ax,0
            mov cx,8
            
;#---------------------------------------#
            mov ax,4C00H
            int 21H
        
code ends
;#---------------------------------------#


end start
