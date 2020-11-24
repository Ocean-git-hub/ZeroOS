#include <zero/physicalmm.h>
#include <zero/tty.h>

#define PMM_PAGE_SIZE (4 * 1024)
#define PMM_PAGE_SHIFT 12u

EFIMemoryMap *memory_map;
PMMInfo physical_memory_info;
PMMPage *pmm_pages_base;

void physical_mm_initialize(EFIMemoryMap *_memory_map, KernelInfo *kernel_info) {
    memory_map = _memory_map;

    physical_memory_info.allocatedPages = physical_memory_info.freePages = 0;
    size_t num_descriptors = memory_map->memoryMapSize / memory_map->descriptorSize;

    size_t tmp = num_descriptors;
    for (EFIMemoryDescriptor *memory_descriptor = memory_map->descriptorPointerBase;
         tmp--;
         memory_descriptor = (EFIMemoryDescriptor *) ((uint64_t) memory_descriptor + memory_map->descriptorSize)) {
        if (memory_descriptor->Type == EfiConventionalMemory)
            physical_memory_info.freePages += memory_descriptor->NumberOfPages;
        else
            physical_memory_info.allocatedPages += memory_descriptor->NumberOfPages;
    }
    physical_memory_info.totalPages = physical_memory_info.freePages + physical_memory_info.allocatedPages;

    size_t num_need_pmm_pages = (sizeof(PMMPage) * physical_memory_info.totalPages + PMM_PAGE_SIZE - 1) / PMM_PAGE_SIZE;
    physical_memory_info.allocatedPages += num_need_pmm_pages;
    physical_memory_info.freePages -= num_need_pmm_pages;
    tmp = num_descriptors;
    for (EFIMemoryDescriptor *memory_descriptor = memory_map->descriptorPointerBase;
         tmp--;
         memory_descriptor = (EFIMemoryDescriptor *) ((uint64_t) memory_descriptor + memory_map->descriptorSize)) {
        if (memory_descriptor->Type == EfiConventionalMemory &&
            memory_descriptor->NumberOfPages >= num_need_pmm_pages) {
            pmm_pages_base = (PMMPage *) memory_descriptor->PhysicalStart;
            break;
        }
    }

    size_t pmm_page_index = 0;
    tmp = num_descriptors;
    for (EFIMemoryDescriptor *memory_descriptor = memory_map->descriptorPointerBase;
         tmp--;
         memory_descriptor = (EFIMemoryDescriptor *) ((uint64_t) memory_descriptor + memory_map->descriptorSize)) {
        if (memory_descriptor->Type == EfiConventionalMemory)
            for (size_t i = 0; i < memory_descriptor->NumberOfPages; ++i)
                physical_mm_set_free_page(physical_mm_get_page(pmm_page_index++));
        else
            for (size_t i = 0; i < memory_descriptor->NumberOfPages; ++i)
                physical_mm_set_allocate_page(physical_mm_get_page(pmm_page_index++), 0, system);
    }

    pmm_page_index = (uint64_t) pmm_pages_base >> PMM_PAGE_SHIFT;
    for (size_t i = 0; i < num_need_pmm_pages; ++i)
        physical_mm_set_allocate_page(physical_mm_get_page(pmm_page_index++), 0, kernel);

    size_t num_kernel_pages = (kernel_info->kernelSize + PMM_PAGE_SIZE - 1) / PMM_PAGE_SIZE;
    pmm_page_index = (uint64_t) kernel_info->kernelStart >> PMM_PAGE_SHIFT;
    for (size_t i = 0; i < num_kernel_pages; ++i)
        physical_mm_set_allocate_page(physical_mm_get_page(pmm_page_index++), 0, kernel);
}

inline __attribute__((always_inline)) PMMPage *physical_mm_get_page(size_t page_no) {
    return (PMMPage *) ((uint64_t) pmm_pages_base + sizeof(PMMPage) * page_no);
}

void physical_mm_set_free_page(PMMPage *page) {
    page->memoryType = none;
    page->virtualMemory = 0;
    page->isFree = 1;
}

void physical_mm_set_allocate_page(PMMPage *page, uintptr_t virtual, PMMMemoryType type) {
    page->memoryType = type;
    page->virtualMemory = virtual;
    page->isFree = 0;
}

PMMPage *physical_mm_allocate_pages(PMMMemoryType type, size_t num_pages) {
    if (num_pages == 0)
        return NULL;
    size_t total_page = physical_memory_info.totalPages;
    bool found = false;
    for (size_t i = 0; i < total_page; ++i) {
        for (size_t j = 0; j < num_pages; ++j) {
            found = true;
            if (physical_mm_get_page(i + j)->isFree == 0) {
                found = false;
                break;
            }
        }
        if (found) {
            PMMPage *page = physical_mm_get_page(i);
            size_t page_no = (uintptr_t) page >> PMM_PAGE_SHIFT;
            for (size_t j = 0; j < num_pages; ++j)
                physical_mm_set_allocate_page(physical_mm_get_page(page_no + j), 0, type);

            physical_memory_info.allocatedPages += num_pages;
            physical_memory_info.freePages -= num_pages;
            return page;
        }
    }
    return NULL;
}

PMMPage *physical_mm_allocate_page(PMMMemoryType type) {
    return physical_mm_allocate_pages(type, 1);
}

void physical_mm_free_pages(PMMPage *page, size_t num_pages) {
    size_t page_no = (uintptr_t) page >> PMM_PAGE_SHIFT;
    for (size_t i = 0; i < num_pages; ++i)
        physical_mm_set_free_page(physical_mm_get_page(page_no + i));

    physical_memory_info.allocatedPages -= num_pages;
    physical_memory_info.freePages += num_pages;
}

void physical_mm_free_page(PMMPage *page) {
    physical_mm_free_pages(page, 1);
}

void *physical_mm_page_to_address(PMMPage *page) {
    if ((uintptr_t) page < (uintptr_t) pmm_pages_base)
        return NULL;
    return (void *) ((((uintptr_t) page - (uintptr_t) pmm_pages_base) / sizeof(struct PMMPage)) << PMM_PAGE_SHIFT);
}
