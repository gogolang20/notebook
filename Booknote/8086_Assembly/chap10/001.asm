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

s:          mov ax,OFFSET start

            mov ax,OFFSET s


;#---------------------------------------#
            mov ax,4C00H
            int 21H
        
code ends
;#---------------------------------------#


end start
