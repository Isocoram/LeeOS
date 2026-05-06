int _str_len(char* string) {
    int length = 0;
    while (string[length] != '\0') {
        length++;
    }
    return length;
}

void kernel_main(void) {
    char* vga_video_memory = (char *)0xB8000;
    char kernel_greet_message[] = "The Kernel Greets You! And I Hope This Works.";
    int greet_message_length = _str_len(kernel_greet_message);
    for (int i = 0; i < greet_message_length; i++) {
        vga_video_memory[2*i] = kernel_greet_message[i];
        vga_video_memory[2*i+1] = 0xb2;
    }
    while (1);
}
