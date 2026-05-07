[bits 16]
[org 0x7c00]

%include "boot/macros.inc"

start_boot:
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, BIOS_start_address
    mov [boot_drive], dl

reset_disk_read_system:
    mov ah, BIOS_disk_reset_service
    int BIOS_disk_access_interrupt
    jc reset_disk_read_system

    call time_delay

    mov si, stage1_greeting_message
    call print_16bit_string

    call time_delay

    mov si, disk_reset_success_message
    call print_16bit_string


    call time_delay

    mov si, load_stage2_message
    call print_16bit_string

    call time_delay

load_stage2_from_disk:
    mov ah, BIOS_disk_read_service
    mov al, sector_count
    mov ch, cylinder
    mov dh, head
    mov cl, sector
    mov dl, [boot_drive]
    mov bx, stage2_load_address
    int BIOS_disk_access_interrupt
    jc load_stage2_from_disk

jmp 0x0000:stage2_load_address

print_16bit_string:
.handle_character:
    lodsb
    test al, al
    jz .end_of_string_reached
    mov ah, BIOS_teletype_output_function
    int BIOS_video_service_interrupt
    jmp .handle_character
.end_of_string_reached:
    ret

time_delay:
    mov cx, 0x0fff
.first_loop:
    mov dx, 0x2fff
.second_loop:
    dec dx
    jnz .second_loop
    dec cx
    jnz .first_loop
    ret

stage1_greeting_message db "First Stage Bootloader Started!", 0
disk_reset_success_message db newline, "Disk-Read-System Reset Success!", 0
load_stage2_message db newline, "Loading Second Stage Bootloader...", 0

boot_drive: db 0

times 510 - ($-$$) db 0
dw 0xaa55
