global putc

%define COM1 0x3F8

section .text
bits 64

putc:
    mov rax, rdi
    mov dx, COM1
    out dx, al
    ret
