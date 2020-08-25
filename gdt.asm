global install_gdt
global enable_sce
global enable_star
global load_idt
global push_hi

extern idt_addr

bits 64

section .text

install_gdt:
    ; install new gdt
    lgdt [rdi]

    mov ax, 0x30    ; TSS segment is 0x30
    ltr ax

    ; set segment registers to kernel data segment (all except cs)
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; use far return to load cs with kernel code segment
    o64 pop rdi
    o64 push 0x08
    o64 push rdi
    o64 retf

enable_sce:
    %define .MSR_EFER 0xC0000080
    mov rcx, .MSR_EFER
    rdmsr
    or eax, 1
    wrmsr
    ret

enable_star:
    %define .MSR_STAR 0xC0000081
    mov rcx, .MSR_STAR
    rdmsr
    mov edx, 0x00180008
    mov eax, 0
    wrmsr
    ret

load_idt:
    lidt [idt_addr]
    ret

push_hi:
    o64 pop rdi
    push 0x0123ABCD
    push rdi
    ret
