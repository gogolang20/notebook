;向内存 0:200 ～ 0:23F 依次传送数据 0 ～ 63(3FH)
;程序中只能使用9条指令 包括
;mov ax,4C00H
;int 21H

assume cs:code

code segment

;#---------------------------------------#
;version 1
            mov ax,20H
            mov es,ax

            mov cx,3FH
            mov bx,0

            mov dl,0

setNumber1: mov es:[bx],dl
            inc bx
            inc dl
            loop setNumber1

;#---------------------------------------#
;version 2

            mov ax,20H
            mov es,ax

            mov cx,64
            mov bx,0

setNumber:  mov es:[bx],bl
            inc bx
            loop setNumber

;#---------------------------------------#
            mov ax,4C00H
            int 21H
        
code ends

end
