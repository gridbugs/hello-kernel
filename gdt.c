#include <stdint.h>

#pragma pack (1)

struct gdt_entry {
  uint16_t limit15_0;            uint16_t base15_0;
  uint8_t  base23_16;            uint8_t  type;
  uint8_t  limit19_16_and_flags; uint8_t  base31_24;
};

struct tss {
    uint32_t reserved0; uint64_t rsp0;      uint64_t rsp1;
    uint64_t rsp2;      uint64_t reserved1; uint64_t ist1;
    uint64_t ist2;      uint64_t ist3;      uint64_t ist4;
    uint64_t ist5;      uint64_t ist6;      uint64_t ist7;
    uint64_t reserved2; uint16_t reserved3; uint16_t iopb_offset;
} tss;

__attribute__((aligned(4096)))
struct {
  struct gdt_entry null;
  struct gdt_entry kernel_code;
  struct gdt_entry kernel_data;
  struct gdt_entry null2;
  struct gdt_entry user_data;
  struct gdt_entry user_code;
  struct gdt_entry tss_low;
  struct gdt_entry tss_high;
} gdt_table = {
    {0, 0, 0, 0x00, 0x00, 0},  /* 0x00 null  */
    {0, 0, 0, 0x9a, 0xa0, 0},  /* 0x08 kernel code (kernel base selector) */
    {0, 0, 0, 0x92, 0xa0, 0},  /* 0x10 kernel data */
    {0, 0, 0, 0x00, 0x00, 0},  /* 0x18 null (user base selector) */
    {0, 0, 0, 0xF2, 0xa0, 0},  /* 0x20 user data */
    {0, 0, 0, 0xFa, 0xa0, 0},  /* 0x28 user code */
    {0, 0, 0, 0x89, 0xa0, 0},  /* 0x30 tss low */
    {0, 0, 0, 0x00, 0x00, 0},  /* 0x38 tss high */
};

struct table_ptr {
    uint16_t limit;
    uint64_t base;
};

__attribute__((aligned(4096)))
uint8_t interrupt_stack[0x1000];

#pragma pack ()


extern /* defined in assembly */
void install_gdt(struct table_ptr * gdt_ptr);

void memzero(void * s, uint64_t n) {
    for (int i = 0; i < n; i++) ((uint8_t*)s)[i] = 0;
}

void setup_gdt() {
    memzero((void*)&tss, sizeof(tss));
    uint64_t tss_base = ((uint64_t)&tss);
    gdt_table.tss_low.base15_0 = tss_base & 0xffff;
    gdt_table.tss_low.base23_16 = (tss_base >> 16) & 0xff;
    gdt_table.tss_low.base31_24 = (tss_base >> 24) & 0xff;
    gdt_table.tss_low.limit15_0 = sizeof(tss);
    gdt_table.tss_high.limit15_0 = (tss_base >> 32) & 0xffff;

    tss.rsp0 = (uint64_t)(interrupt_stack + 0x1000);
    tss.rsp1 = (uint64_t)(interrupt_stack + 0x1000);
    tss.rsp2 = (uint64_t)(interrupt_stack + 0x1000);
    tss.ist1 = (uint64_t)(interrupt_stack + 0x1000);

    struct table_ptr gdt_ptr = { sizeof(gdt_table)-1, (uint64_t)&gdt_table };
    install_gdt(&gdt_ptr);
}
