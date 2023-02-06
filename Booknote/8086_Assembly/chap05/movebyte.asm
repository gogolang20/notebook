;求ffff:0 到 ffff:f 字节型数据的和 结果存放在dx中

assume cs:code

code segment

            mov ax,0ffffH
            mov ds,ax

            mov bx,0H       ;ds偏移地址

            mov cx,10H      ;循环次数
            mov dx,0H

            mov ax,0H

moveByte:   mov al,ds:[bx]
            add dx,ax
            inc bx
            loop moveByte


            mov ax,4C00H
            int 21H
        
code ends

end
