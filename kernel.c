#include "printf.h"

void enable_sce();
void enable_star();
void switch_to_user_mode();
void install_gdt();

int foo;
int bar = 5;

void _start() {
    printf("Hello, World! %d %x %s\n");
    printf("Installing GDT\n");
    install_gdt();
    printf("Done!\n");
    printf("Enabling SCE...\n");
    enable_sce();
    printf("Done!\n");
    printf("Enabling STAR...\n");
    enable_star();
    printf("Done!\n");
    printf("Switching to user mode...\n");
    switch_to_user_mode();
    while(1);
}
