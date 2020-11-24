#ifndef ZEROOS_PHYSICALMM_H
#define ZEROOS_PHYSICALMM_H

#include <stdbool.h>
#include <zero/memorymap.h>
#include <zero/kernel.h>

typedef enum PMMMemoryType {
    none,
    system,
    kernel,
    usr
} PMMMemoryType;

typedef struct PMMPage {
    uint32_t isFree;
    uint32_t memoryType;
    uintptr_t virtualMemory;
} PMMPage;

typedef struct PMMInfo {
    size_t totalPages;
    size_t freePages;
    size_t allocatedPages;
} PMMInfo;

void physical_mm_initialize(EFIMemoryMap *_memory_map, KernelInfo *kernel_info);

PMMPage *physical_mm_get_page(size_t page_no);

void physical_mm_set_free_page(PMMPage *page);

void physical_mm_set_allocate_page(PMMPage *page, uintptr_t virtual, PMMMemoryType type);

PMMPage *physical_mm_allocate_pages(PMMMemoryType type, size_t num_pages);

PMMPage *physical_mm_allocate_page(PMMMemoryType type);

void physical_mm_free_pages(PMMPage *page, size_t num_pages);

void physical_mm_free_page(PMMPage *page);

void *physical_mm_page_to_address(PMMPage *page);

#endif //ZEROOS_PHYSICALMM_H
