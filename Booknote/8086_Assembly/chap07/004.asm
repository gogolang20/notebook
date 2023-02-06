assume cs:code,ds:data

;#---------------------------------------#
data segment
            db      'welcome to nasm!'
            db      '----------------'
data ends

;#---------------------------------------#
code segment

start:      mov ax,data
            mov ds,ax

            mov si,0
            mov di,10H

            mov cx,8

copyString: mov ax,ds:[si]
            mov ds:[di],ax
            add si,2
            add di,2
            loop copyString

;#---------------------------------------#
            mov ax,4C00H
            int 21H
        
code ends
;#---------------------------------------#

end start
