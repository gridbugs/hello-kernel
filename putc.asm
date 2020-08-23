global putc
global _putchar

%define COM1 0x3F8

section .text
bits 64

_putchar:            ; needed to link with printf library
putc:
    mov rax, rdi
    mov dx, COM1
    out dx, al
    ret
