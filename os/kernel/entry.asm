[bits 32]

global _start_kernel
extern kernel_main

section .text

_start_kernel:
    mov esp, 0x90000
    call kernel_main

.hang:
    cli
    hlt
    jmp .hang
