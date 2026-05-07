#ifndef KERNEL_LIBRARY_H
#define KERNEL_LIBRARY_H

extern void timer(int start);
extern int _str_len(char* string);
extern void _draw_character_at_position(int x_coordinate, int y_coordinate, char character, char color);
extern void _kprint(char* string, int length, int offset, char color);
extern void _fill_screen_color(char color);

#endif