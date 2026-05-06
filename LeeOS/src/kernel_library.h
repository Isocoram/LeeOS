#ifndef KERNEL_LIBRARY_H
#define KERNEL_LIVRARY_H

extern int _str_len(char* string);
extern void _draw_character_at_position(int x_coordinate, int y_coordinate, char character, char color);
extern void _kprint(char* string, int length, int offset, char color);
extern void _fill_screen_color(char color);

int _str_len(char* string) {
    int length = 0;
    while (string[length] != '\0') {
        length++;
    }
    return length;
}

void _draw_character_at_position(int x_coordinate, int y_coordinate, char character, char color) {
    char* vga_video_memory = (char *)0xB8000;
    int screen_offset = ( (x_coordinate % 80) + (y_coordinate % 25) * 80 ) * 2;
    vga_video_memory[screen_offset] = character;
    vga_video_memory[screen_offset + 1] = color;
}


void _kprint(char* string, int length, int offset, char color) {
    char* vga_video_memory = (char *)0xB8000;
    for (int i = 0; i < length; i++) {
        vga_video_memory[offset+i*2] = string[i];
        vga_video_memory[offset+i*2+1] = color;
    }
}

void _fill_screen_color(char color) { 
    for (int i = 0; i < 80; i++) {
        for (int j = 0; j < 25; j++) {
            _draw_character_at_position(i, j, ' ', color);
        }
    }
}
#endif