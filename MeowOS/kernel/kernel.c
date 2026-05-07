// #include "../src/kernel_library.h"
#include "../src/kernel_library.h"

void kernel_main(void) {
    char* vga_video_memory = (char *)0xB8000;
    char kernel_greet_message[] = "The Kernel Greets And Welcomes You!";
    char funfact[] = "This Is A Cool Plot!!!";
    int funfact_length = _str_len(funfact);
    int greet_message_length = _str_len(kernel_greet_message);
    
    timer(5000000);
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            _draw_character_at_position(j,i, ' ', (-2+i*i+j*j-i*j) % 64);
        }
    }
    _kprint(funfact, funfact_length, 0, 0xce);
    timer(50000000);
    _fill_screen_color(0x1b);
    timer(50000000);
    _kprint(kernel_greet_message, greet_message_length, 0, 0x1b);

    int time = 10000000;
    char text[] = "Kernel Loop Begun!";
    int text_length = _str_len(text);
    
    int cpuid_info;
    asm volatile(
        "cpuid"
        : "=b"(cpuid_info)
        : "a"(0)
    );
    char *pText = (char *)&cpuid_info;
    _kprint(pText, 4, 3840, 0xb1);

asm volatile(
    "cli; hlt"
    :
);

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
