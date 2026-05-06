#include "../src/kernel_library.h"

void kernel_main(void) {
    char* vga_video_memory = (char *)0xB8000;
    char kernel_greet_message[] = "The Kernel Greets You! 12347";
    char funfact[] = "This Is A Cool Plot!!!";
    int funfact_length = _str_len(funfact);
    int greet_message_length = _str_len(kernel_greet_message);
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            _draw_character_at_position(j,i, ' ', (-1+i*i-j*j+2*j*i+i*0) % 64);
        }
    }
    _kprint(funfact, funfact_length, 0, 0x1b);
    while (1);
}
