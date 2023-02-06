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

            mov ax,0
            mov al,100
            mov bl,10
            mul bl

            mov ax,0
            mov al,100
            mov ds:[0],bl
            mul byte ptr ds:[0]



            mov ax,0
            mov ax,1000
            mov bx,100
            mul bx

            mov ax,0
            mov ax,1000
            mov ds:[0],bx
            mul word ptr ds:[0]

;#---------------------------------------#
            mov ax,4C00H
            int 21H
        
code ends
;#---------------------------------------#


end start
