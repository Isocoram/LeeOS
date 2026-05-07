[bits 16]
[org 0x8000]

%include "boot/macros.inc"

extern _start_kernel

start_stage2:
    cli 
    xor ax, ax
    mov ds, ax

    call enable_a20_line

    call load_kernel_from_disk

    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp dword code_segment:start_protected_mode
    db "after jump", 0

load_kernel_from_disk:
    mov ax, 0x1000
    mov es, ax
    xor bx, bx              ;   offset
    mov ah, 0x02
    mov al, 3   ;   number sectros
    mov ch, 0   ;   cylinder
    mov cl, 3   ;   sector start read after stage1 + stage 2
    mov dh, 0   ;   head
    ; mov dl, 0x00    ; for qemu only ->> fix in hardware
    int 0x13
    jc disk_read_error
    ret

disk_read_error:
    cli
    hlt
    jmp $

[bits 32]
start_protected_mode:
    mov ax, data_segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000

    cld 

    mov esi, 0x10000
    mov edi, 0x100000
    mov ecx, 5120
    rep movsb

    call clear_screen
    call delay_time_32bit

    mov esi, greeting_message_32bit
    mov ah, 0x0f
    mov edi, 0xb8000
    call print_string_protected_mode

    call delay_time_32bit
    call delay_time_32bit

    mov esi, newline1
    call print_32bit_blank_characters

    mov esi, kernel_overtake_message
    call print_string_protected_mode

    call delay_time_32bit
    call delay_time_32bit

    jmp code_segment:0x100000

.halt_cpu:
    cli
    hlt
    jmp .halt_cpu

enable_a20_line:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

clear_screen:
    mov edi, 0xb8000
    mov ecx, 80*25
    mov ax, 0x0f20       ; space character with white on black attribute
    rep stosw
    ret

delay_time_32bit:
    pushad
    mov ecx, 0x00000fc
    .loop1:
        mov edx, 0x000fffff
    .loop2:
            dec edx
            jnz .loop2
        dec ecx
        jnz .loop1

        popad
    ret

print_string_protected_mode:

    mov ah, 0xec
    mov dx, 0x3D4
    mov al, 0x0F
    out dx, al
    mov dx, 0x3D5
    mov al, 34
    out dx, al
    mov dx, 0x3D4
    mov al, 0x0E
    out dx, al
    mov dx, 0x3D5
    mov al, 0
    out dx, al

    lodsb                   ; [esi] > al
    test al, al
    jz .done
    stosw
    jmp print_string_protected_mode
.done:
    ret

print_32bit_blank_characters:
    mov ah, 0x00
    lodsb
    test al, al
    jz .done
    stosw
    jmp print_32bit_blank_characters
    .done:
        ret

greeting_message_32bit db "CPU Entered 32 Bit Protected Mode!", 0
debug_msg1 db "debugger string", 0
newline1 db "                                              ", 0
kernel_overtake_message db "Handing Control To Kernel!", 0

gdt_start:
    dq 0x0
gdt_code:
    dw 0xffff           ; limit
    dw 0x00             ; base low
    db 0x0              ; base mid
    db 10011010b        ; code acccess byte 
    db 11001111b        ; granularity and flags
    db 0x0              ; base high
gdt_data:
    dw 0xffff           ; limit
    dw 0x00             ; base low
    db 0x0              ; base mid
    db 10010010b        ; code acccess byte 
    db 11001111b        ; granularity and flags
    db 0x0              ; base high
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

code_segment equ gdt_code - gdt_start
data_segment equ gdt_data - gdt_start

times 511 - ($-$$) db 0