#include "kernel_library.h"

//__volatile__ u8* vga_video_memory = (__volatile__ u8 *)0xB8000;

void timer(u32 start) {
    while (start) {
        start--;
    }
    return;
}

u32 _str_len(const u8* string) {
    u32 length = 0;
    while (string[length] != '\0') {
        length++;
    }
    return length;
}

void _draw_character_at_position(u8 x_coordinate, u8 y_coordinate, u8 character, u8 color) {
    
    __volatile__ u8* vga_video_memory = (__volatile__ u8 *)0xB8000;

    if (x_coordinate > 79 || y_coordinate > 24) {
        return;
    }

    u32 screen_offset = ( x_coordinate + y_coordinate * (u8)80 ) * (u8)2;
    vga_video_memory[screen_offset] = character;
    vga_video_memory[screen_offset + 1] = color;
}

void _kprint(const u8* string, u32 length, u8 color, u8 x_coordinate, u8 y_coordinate) {
    
    __volatile__ u8* vga_video_memory = (__volatile__ u8 *)0xB8000;
    
    for (u32 i = 0; i < length; i++) {
        timer(1000000);
        _draw_character_at_position(x_coordinate + i, y_coordinate, string[i], color);
    }
}

void _fill_screen_color(u8 color) { 
    for (u8 i = 0; i < VGA_WIDTH; i++) {
        for (u8 j = 0; j < VGA_HEIGHT; j++) {
            _draw_character_at_position(i, j, ' ', color);
        }
    }
}

void draw_cool_image(void) {
    for (u8 i = 0; i < VGA_HEIGHT; i++) {
        for (u8 j = 0; j < VGA_WIDTH; j++) {
            _draw_character_at_position(j, i, 'P', 0xec);
        }
    }
}

void inline reboot_system(void) {
       __asm__ __volatile__(
        "pushl $0;"
        "pushw $0;"
        "lidt (%esp);"
        "int $3;"
    );
}

inline void outb(u16 port, u8 value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}
     
inline u8 inb(u16 port) {
    u8 io_port_return_value;
    __asm__ volatile ("inb %1, %0" : "=a"(io_port_return_value) : "Nd"(port));
    return io_port_return_value;
}