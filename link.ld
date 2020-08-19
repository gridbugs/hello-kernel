mmio = 0xfffffffff8000000;
fb = 0xfffffffffc000000;
kernel_base = 0xffffffffffe00000;

SECTIONS {
    . = kernel_base;

    bootboot = .;
    . += 0x1000;

    environment = .;
    . += 0x1000;

    .text : {
        *(.text)
        *(.rodata)
        *(.data)
    }

    .bss (NOLOAD) : ALIGN(0x1000) {
        *(.bss)
    }

    /DISCARD/ : {
        *(.eh_frame)
        *(.comment)
    }
}
