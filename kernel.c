void putc(char c);
void puts(char* s);

void _start() {
    puts("Hello, World!\n");
    while(1);
}

void puts(char* s) {
    do {
        putc(*(s++));
    } while (*s);
}
