#include <stdint.h>
#include "printf.h"

#define NUM_EXCEPTIONS 256

struct idt_descr {
    uint16_t off_0_15;
    uint16_t code_segment_selector;
    uint8_t stack_offset;
    uint8_t options;
    uint16_t off_16_31;
    uint32_t off_32_63;
    uint32_t zero;
}  __attribute__((packed)) idt[NUM_EXCEPTIONS] = { 0 };

const struct {
    uint16_t limit;
    void* address;
} __attribute__((packed)) idt_addr = {
    .limit = (uint16_t)(sizeof(idt) - 1),
    .address = idt,
};

static void handle_exception_spin() {
    printf("Got interrupt!\n");
    while(1);
}

static struct idt_descr make_idt_decr(void (*fn)()) {
    return (struct idt_descr){
        .off_0_15 = (uint16_t)((uint64_t)fn & 0xFFFF),
        .off_16_31 = (uint16_t)(((uint64_t)fn >> 16) & 0xFFFF),
        .off_32_63 = (uint32_t)(((uint64_t)fn >> 32) & 0xFFFFFFFF),
        .code_segment_selector = 8,
        .stack_offset = 0,
        .options = 0x8E,
        .zero = 0,
    };
}

void load_idt();

void install_idt() {
    for (int i = 0; i < NUM_EXCEPTIONS; i++) {
        idt[i] = make_idt_decr(handle_exception_spin);
    }
    load_idt();
}
