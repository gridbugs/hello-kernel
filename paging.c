#include <stdint.h>
#include "printf.h"

// this file assumes that all tables in the paging hierarchy are identity-mapped

#define NUM_ENTRIES 512

#pragma pack (1)
typedef struct table {
    uint64_t entries[NUM_ENTRIES];
} table_t;
#pragma pack ()

static table_t* root_vaddr = (table_t*)0xA000;

static table_t* entry_to_paddr(uint64_t entry) {
    return (table_t*)(entry & ~((uint64_t)0xFFF));
}

void allow_user_access_to_page_containing_address(void* address) {
    printf("Traversing address 0x%p\n", address);
    uint64_t address_int = (uint64_t)address;
    unsigned int pml4_index = (address_int >> 39) & 0x1FF;
    unsigned int pdpt_index = (address_int >> 30) & 0x1FF;
    unsigned int pd_index = (address_int >> 21) & 0x1FF;
    unsigned int pt_index = (address_int >> 12) & 0x1FF;
    printf("pml4_index: %d\n", pml4_index);
    printf("pdpt_index: %d\n", pdpt_index);
    printf("pd_index: %d\n", pd_index);
    printf("pt_index: %d\n", pt_index);
    uint64_t pml4_entry = root_vaddr->entries[pml4_index];
    printf("pml4_entry: 0x%X\n", pml4_entry);
    uint64_t pdpt_entry = entry_to_paddr(pml4_entry)->entries[pdpt_index];
    printf("pdpt_entry: 0x%X\n", pdpt_entry);
    uint64_t pd_entry = entry_to_paddr(pdpt_entry)->entries[pd_index];
    printf("pd_entry: 0x%X\n", pd_entry);
    uint64_t pt_entry = entry_to_paddr(pd_entry)->entries[pt_index];
    printf("pt_entry: 0x%X\n", pt_entry);
    root_vaddr->entries[pml4_index] = pml4_entry | 4;
    entry_to_paddr(pml4_entry)->entries[pdpt_index] = pdpt_entry | 4;
    entry_to_paddr(pdpt_entry)->entries[pd_index] = pd_entry | 4;
    entry_to_paddr(pd_entry)->entries[pt_index] = pt_entry | 4;
}
