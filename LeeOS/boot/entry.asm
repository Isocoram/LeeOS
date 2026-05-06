[bits 32]

global _start_kernel
extern kernel_main

section .text
_start_kernel:
    ;mov ax, 0xb800
    ;mov ds, ax
    ;mov word [0], 0x0f4b
    ;jmp .hang
    mov esp, 0x90000
    call kernel_main

.hang:
    cli
    hlt
    jmp .hang