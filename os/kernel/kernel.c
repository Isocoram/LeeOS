#include "../src/kernel_library.h"
#include "idt.h"
// __volatile__ u8* vga_video_memory = (__volatile__ u8*)0xB8000;
u32 time = 10000000;
void test(void) {
    for (u8 i = 0; i<10; i++) {
    _draw_character_at_position(10+i,21,'s',0xab);
    }
    return;
}
void kernel_main(void) {
    u8 kernel_greet_message[] = "The Kernel Greets And Welcomes You!";
    u8 funfact[] = "This Is A Cool Plot!!!";
    u8 funfact_length = _str_len(funfact);
    u8 greet_message_length = _str_len(kernel_greet_message);
    
    timer(1000000);
    for (u8 i = 0; i < 25; i++) {
        for (u8 j = 0; j < 80; j++) {
            _draw_character_at_position(j,i, ' ', (-2+i*i+j*j-i*j) % 64);
        }
    }
    _kprint(funfact, funfact_length, 0x4e, 27, 11);
    timer(50000000);
    _fill_screen_color(0x1b);
    timer(10000000);
    _kprint(kernel_greet_message, greet_message_length,  0x1b, 10, 10);

    u32 vendor[3];
    u32 maxnum;

   __asm__ __volatile__(
        "cpuid"
        : "=b"(vendor[0]), "=d"(vendor[1]), "=c"(vendor[2]), "=a"(maxnum)
        : "a"(0)
    );

    u8 *vendor_name = (u8 *)&vendor;
    _kprint(vendor_name, 3*4, 0xb1, 0, 24);

    u8 prime_info_text[] = "Each 'P' you see is a prime number on the x axis!";
    _kprint(prime_info_text, sizeof(prime_info_text), 0x30, 2, 15);

    for (u8 i = 0; i < 80; i++) {
        _draw_character_at_position(55+i,i, '\\', 0x1c);
        _draw_character_at_position(55+i,24-i, '/', 0x1c);
        if (i < 10) {
            _draw_character_at_position(i, 18, 48+i, 0x1e);
        }
        u8 is_prime = 1;
        for (u8 j = 2; j < i; j++) {
            if ((i % j) == 0) {
                is_prime = 0;
                break;
            }
        }
       if (is_prime && i >= 2) {
            _draw_character_at_position(i, 17, 'P', 0xdf);
        }
    }

    timer(10000000);
    u8 reboot_warn_message[] = "Rebooting Soon!!!";
    const u8 texto[] = "1234";
    _kprint(reboot_warn_message, sizeof(reboot_warn_message), 0x4f, 13, 13);
    //timer(90000000000);
    test();
    //draw_cool_image();

    outb(0x70, 0x00);
    //u8 secs = inb(0x71);
    //idt_install();
    outb(0x92,0);
    _draw_character_at_position(0,0, 'A', 0xec);

    //outb(0x64, 0xfe);
    //timer(89898989890);
    //reboot_system();

    __asm__ __volatile__(
        "cli; hlt"
        :
    );
}