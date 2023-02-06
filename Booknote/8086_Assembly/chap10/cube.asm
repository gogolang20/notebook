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

            mov bx,data
            mov es,bx

            mov di,0

            mov bx,5            ;参数
            call get_cube       ;对参数的处理
            mov es:[di+0],ax    ;call程序的返回值
            mov es:[di+2],dx

            mov ax,4C00H
            int 21H
   
get_cube:   push bx

            mov ax,bx
            mul bx
            mul bx

            pop bx
            ret

code ends
;#---------------------------------------#


end start
