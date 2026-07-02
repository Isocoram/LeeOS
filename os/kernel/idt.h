#ifndef IDT_H
#define IDT_H

void idt_set_gate(u8 number, u32 base, u16 selector, u8 flags);
void idt_install(void);

#endif