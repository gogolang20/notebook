#include "multiboot.h"

.section .multiboot
    .long MB_MAGIC      ;long ==> 32bit
    .long MB_ALIGNED_4K_MEM_MAP
    .long CHECKSUM(MB_ALIGNED_4K_MEM_MAP)

.section .bss
    /* System V ABI, the stack must be aligned at 16 bytes boundary */
    .align 16
    stack_bottom:
        .skip 16318, 0
    stack_top:


.section .text
    .global start_
    start_:
        movl $stack_top, %esp
        /*
        kernel init
        1. Load GDT
        2. Load IDT
        3. Enable paging
        */

        call _kernel_init

        pushl %ebx
        call _kernel_main

        cli
    j_:
        hlt
        jmp j_

; i686-elf-gcc -E boot.S
; i686-elf-gcc -c boot.S
; xxd boot.o
; rm boot.o
