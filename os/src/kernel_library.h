#ifndef KERNEL_LIBRARY_H
#define KERNEL_LIBRARY_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

//extern __volatile__ u8* vga_video_memory;

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((u8*)0xb8000)

void timer(u32 start);
u32 _str_len(const u8* string);
void _draw_character_at_position(u8 x_coordinate, u8 y_coordinate, u8 character, u8 color);
void _kprint(const u8* string, u32 length, u8 color, u8 x_coordinate, u8 y_coordinate);
void _fill_screen_color(u8 color);
void reboot_system(void);
void draw_cool_image(void);
void outb(u16 port, u8 value);
u8 inb(u16 port);

#endif