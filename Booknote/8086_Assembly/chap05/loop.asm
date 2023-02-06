assume cs:code

code segment

            mov ax,2000H
            mov ds,ax
            mov bx,1000H

            mov dl,0

            mov cx,10H       ;保存了跳转次数

 setNumber: mov ds:[bx],dl
            inc dl
            inc bx

            loop setNumber




            mov ax,4C00H
            int 21H
        
code ends

end
