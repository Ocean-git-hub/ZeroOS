OUTPUT_FORMAT("binary")
ENTRY(_start)

SECTIONS {
    .bss_start : {QUAD(__bss_start)}
    .bss_end : {QUAD(__bss_end)}
    .text : {
        *(.text)
    }
    __bss_start = .;
    .bss : {
        *(COMMON)
        *(.bss)
    }
    __bss_end = .;
    .data : {
        *(.data)
    }
    .rodata : {
        *(.rodata)
    }
}