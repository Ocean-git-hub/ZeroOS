.section .bss
.align 16
.skip 16384

.section .text
.global _start

_start:
    push %rdi
    sub %rsp, 8

    // do something

    add %rsp, 8
    pop %rdi
    call kernel_main

    cli
1:  hlt
    jmp 1
