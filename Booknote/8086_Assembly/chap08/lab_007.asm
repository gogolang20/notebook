assume cs:code,ds:data,ss:stack

;#---------------------------------------#
data segment
            db      '1975','1976','1977','1978','1979','1980','1981','1982','1983'
            db      '1984','1985','1986','1987','1988','1989','1990','1991','1992'
            db      '1993','1994','1995'

            dd      16,22,382,1356,2390,8000,16000,24486,50065,97479,140417,197514
            dd      345980,590827,803530,1183000,1843000,2759000,3753000,4649000,5937000

            dw      3,7,9,13,28,38,130,220,476,778,1001,1442,2258,2793,4037,5635,8226
            dw      11542,14430,15257,17800

data ends

;#---------------------------------------#
table segment
             db      21 dup ('year summ ne ?? ')
table ends


stack segment stack
             db      128 dup (0)
stack ends

;#---------------------------------------#
code segment

start:      mov ax,stack
            and ss,ax
            mov sp,128

            mov ax,data
            mov ds,ax

            mov ax,table
            mov es,ax

            mov si,0            ;ds:[si]
            mov di,84           ;ds:[di]
            mov bx,168          ;ds:[bx]
            mov bp,0            ;es:[bp]

            mov cx,21

inputLab:   push ds:[si]
            pop es:[bp]
            push ds:[si+2]
            pop es:[bp+2]

            mov ax,ds:[di]
            mov dx,ds:[di+2]
            mov es:[bp+5],ax
            mov es:[bp+7],dx

            push ds:[bx]
            pop es:[bp+0AH]

            div word ptr ds:[bx]

            mov es:[bp+0DH],ax

            add si,4
            add di,4
            add bx,2
            add bp,16
            loop inputLab

;#---------------------------------------#
            mov ax,4C00H
            int 21H
        
code ends
;#---------------------------------------#


end start
