#include "printf.h"

void enable_sce();
void enable_star();
void switch_to_user_mode();
void setup_gdt();
void install_idt();
void allow_user_access_to_page_containing_address(void* address);

int foo;
int bar = 5;

void push_hi();
void _user();

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
    printf("Giving user access to some memory...\n");
    allow_user_access_to_page_containing_address(_user);
    allow_user_access_to_page_containing_address(push_hi);
    allow_user_access_to_page_containing_address((void*)0xFFFFFFFFFFFFFFFF);
    printf("Done!\n");
    printf("Switching to user mode...\n");
    switch_to_user_mode();
    while(1);
}

void _user() {
    push_hi();
    while(1);
}
