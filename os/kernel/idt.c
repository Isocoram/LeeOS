#include "../src/kernel_library.h"
extern void idt_load();

struct idt_entry {
    u16 isr_low;
    u16 kernel_code_segment;
    u8 alwayszero;
    u8 attributes;
    u16 isr_high;
} __attribute__((packed)) idt_entry_t;

struct idt_ptr {
    u16 limit;
    u32 base;
} __attribute__((packed)) idtr_t;

__attribute__((aligned(0x10)))
struct idt_entry_t idt[256];
struct idtr_t idtr;

__attribute__((noreturn))
void exception_handler(void);
void exception_handler() {
    __asm__ volatile ("cli; hlt");
}

void idt_set_descriptor(u8 vector, void* isr, u8 flags);
void idt_set_descriptor(u8 vector, void* isr, u8 flags) {
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low        = (u32)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
    descriptor->attributes     = flags;
    descriptor->isr_high       = (u32)isr >> 16;
    descriptor->reserved       = 0;
}