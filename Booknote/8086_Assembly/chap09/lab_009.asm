assume cs:code,ds:data,ss:stack

;#---------------------------------------#
data segment
                   ;'0123456789abcdef'
            db      'welcome to nasm!'
            db      00000010B
            db      00100100B
            db      01110001B
                   ;00000000    颜色控制位
                   ; rgb rgb

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
            mov ds,bx

            mov bx,0B800H
            mov es,bx

            mov si,0
            mov di,160*10 + 30*2
            mov bx,16
            mov dx,0

            mov cx,3

showNasm:   push bx
            push cx
            push si
            push di

            mov cx,16
            mov dh,ds:[bx]      ; 设置高位颜色

showRow:    mov dl,ds:[si]
            mov es:[di],dx
            add di,2
            inc si
            loop showRow

            pop di
            pop si
            pop cx
            pop bx
            add di,160
            inc bx
            loop showNasm

;#---------------------------------------#
            mov ax,4C00H
            int 21H
        
code ends
;#---------------------------------------#

end start
