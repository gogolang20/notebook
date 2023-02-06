assume cs:code

code segment

;#---------------------------------------#
            dw 0,1,2,3,4,5,6,7,8
            ;d = define    w = word

start:      mov bx,0
            mov ax,0
            mov cx,8

addNumber:  add ax,cs:[bx]
            add bx,2
            loop addNumber
            
;#---------------------------------------#

            mov ax,4C00H
            int 21H
        
code ends

end start
