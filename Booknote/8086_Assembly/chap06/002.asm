assume cs:code

code segment

;#---------------------------------------#
            dw      0123H,0456H,0789H,0ABCH,0DEFH,0FEDH,0CBAH,0987H     ;16字节
            ;逆序

            dw      0,0,0,0,0,0,0,0     ;32个字节当作我们自己安排的栈空间
            dw      0,0,0,0,0,0,0,0

 start:     mov ax,cs
            mov ss,ax
            mov sp,30H

            mov bx,0
            mov cx,8

pushData:   push cs:[bx]
            add bx,2
            loop pushData


            mov bx,0
            mov cx,8
            
popData:    pop cs:[bx]
            add bx,2
            loop popData

;#---------------------------------------#

            mov ax,4C00H
            int 21H
        
code ends

end start
