assume cs:code

code segment

            mov ax,4C00H
            int 21H

start:      mov ax,0
s:          nop     ; CPU遇到nop指令什么都不做 占用一个字节
            nop

            mov di,OFFSET s
            mov si,OFFSET s2
            mov ax,cs:[si]
            mov cs:[di],ax

s0:         jmp short s

s1:         mov ax,0
            int 21H
            mov ax,0

s2:         jmp short s1
s3:         nop
        
code ends

end start

;为什么可以正常运行
