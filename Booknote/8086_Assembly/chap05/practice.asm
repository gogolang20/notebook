;用编程进行加法计算 123*236 结果存放在AX中

assume cs:code

code segment

            mov cx,123      ;循环次数
            mov ax,0H

cal:        add ax,236
            loop cal


            mov ax,4C00H
            int 21H
        
code ends

end
