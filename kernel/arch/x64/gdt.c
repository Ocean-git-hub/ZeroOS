#include <stdint.h>

#define SEGMENT_SELECTOR_CODE 0x8
#define SEGMENT_SELECTOR_DATA 0x10

typedef struct __attribute__((packed)) {
    uint16_t size;
    uint64_t offset;
} GDTR;

typedef struct __attribute__((packed)) {
    uint16_t limit;
    uint32_t base: 24;
    uint8_t Ac: 1;
    uint8_t RW: 1;
    uint8_t DC: 1;
    uint8_t Ex: 1;
    uint8_t S: 1;
    uint8_t Privl: 2;
    uint8_t Pr: 1;
    uint8_t limit2: 4;
    uint8_t zero: 1;
    uint8_t L: 1;
    uint8_t Sz: 1;
    uint8_t Gr: 1;
    uint8_t base2;
} GDTEntry;

const GDTEntry gdts[] = {
        {0},
        {
                .limit=0xffff,
                .base=0,
                .Ac=0,
                .RW=1,
                .DC=0,
                .Ex=1,
                .S=1,
                .Privl=0,
                .Pr=1,
                .limit2=0xf,
                .zero=0,
                .L=1,
                .Sz=0,
                .Gr=1,
                .base2=0,
        },
        {
                .limit=0xffff,
                .base=0,
                .Ac=0,
                .RW=1,
                .DC=0,
                .Ex=0,
                .S=1,
                .Privl=0,
                .Pr=1,
                .limit2=0xf,
                .zero=0,
                .L=1,
                .Sz=0,
                .Gr=1,
                .base2=0,
        }
};

void gdt_initialize() {
    GDTR gdtr = {
            .size = sizeof(gdts) - 1,
            .offset = (uint64_t) gdts
    };
    uint16_t data_segment = SEGMENT_SELECTOR_DATA;
    uint16_t code_segment = SEGMENT_SELECTOR_CODE;
    __asm__ volatile ("lgdt %0\n"
                      "mov %1, %%ax\n"
                      "mov %%ax, %%ds\n"
                      "mov %%ax, %%ss\n"
                      "pushq %2\n"
                      "leaq _label(%%rip), %%rax\n"
                      "pushq %%rax\n"
                      "lretq\n"
                      "_label:\n"
    ::"m"(gdtr), "m"(data_segment), "m"(code_segment):"%rax");
}