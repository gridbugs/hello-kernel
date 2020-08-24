#include "printf.h"

void enable_sce();
void enable_star();
void switch_to_user_mode();
void setup_gdt();
void install_idt();

int foo;
int bar = 5;

void _start() {
    printf("Hello, World!\n");
    printf("Installing GDT\n");
    setup_gdt();
    printf("Done!\n");
    printf("Enabling SCE...\n");
    enable_sce();
    printf("Done!\n");
    printf("Enabling STAR...\n");
    enable_star();
    printf("Done!\n");
    printf("Installing IDT\n");
    install_idt();
    printf("Done!\n");
    printf("Switching to user mode...\n");
    int x = *((int*)0x120000000);
    printf("x = %d\n", x);
    switch_to_user_mode();
    while(1);
}

void _user() {
    while(1);
}
