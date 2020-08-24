global switch_to_user_mode
extern user_base
extern _user

section .text
bits 64

switch_to_user_mode:
    mov rcx, _user
    o64 mov r11, 0x0202
    o64 sysret
