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

extern void timer(u32 start);
extern u32 _str_len(const u8* string);
extern void _draw_character_at_position(u8 x_coordinate, u8 y_coordinate, u8 character, u8 color);
extern void _kprint(const u8* string, u32 length, u8 color, u8 x_coordinate, u8 y_coordinate);
extern void _fill_screen_color(u8 color);
extern void reboot_system(void);
void draw_cool_image(void);

#endif