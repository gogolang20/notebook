;将内存ffff:0 到 ffff:f 内存单元中的数据复制到 0:200 ～ 0:20f 中

assume cs:code

code segment

;#---------------------------------------#
;version 1
            mov ax,0ffffH
            mov ds,ax

            mov bx,0H       ;ds偏移地址

            mov cx,10H      ;循环次数


setNumber1: push ds
            mov dl,ds:[bx]

            mov ax,20H
            mov ds,ax
            mov ds:[bx],dl
            inc bx
            pop ds
            loop setNumber1

;#---------------------------------------#
;version 2
            mov ax,0ffffH
            mov ds,ax

            mov ax,20H
            mov es,ax

            mov cx,10H
            mov bx,0


setNumber2: mov dl,ds:[bx]
            mov es:[bx],dl
            inc bx
            loop setNumber2

;#---------------------------------------#
;version 3
            mov ax,0ffffH
            mov ds,ax

            mov ax,20H
            mov es,ax

            mov bx,0

            mov cx,8H       ;速度快了一倍

setNumber2: push ds:[bx]
            pop es:[bx]
            add bx,2
            loop setNumber3

;#---------------------------------------#

            mov ax,4C00H
            int 21H
        
code ends

end
