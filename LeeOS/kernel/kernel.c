#include "../src/kernel_library.h"

void kernel_main(void) {
    char* vga_video_memory = (char *)0xB8000;
    char kernel_greet_message[] = "The Kernel Greets And Welcomes You!";
    char funfact[] = "This Is A Cool Plot!!!";
    int funfact_length = _str_len(funfact);
    int greet_message_length = _str_len(kernel_greet_message);
    /*
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            timer(1000000);
            _draw_character_at_position(j,i, ' ', (1+i*i-j*j-2*i*j*i) % 64);
        }
    }
    _kprint(funfact, funfact_length, 0, 0x1b);
    */
    _fill_screen_color(0x1b);
    timer(30000000);
    _kprint(kernel_greet_message, greet_message_length, 0, 0x1b);

    int time = 50000000;
    char text[] = "Kernel Loop Begun!";
    int text_length = _str_len(text);
    while (1) {
        timer(5*time);
        _fill_screen_color(0xb0);
        timer(time);
        _fill_screen_color(0x10);
        timer(time);
        _kprint(text, text_length, 360, 0x1b);
        timer(time);
    }
}
