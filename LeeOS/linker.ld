OUTPUT_FORMAT(elf-i386)
ENTRY(_start_kernel)

SECTIONS
{
    . = 0x100000;
    .text :
    {
        *(.text)
    }
    .data :
    {
        *(.data)
    }
    .rodata : 
    {
        *(.rodata)
    }
    .bss :
    {
        *(.bss)
    }
}
