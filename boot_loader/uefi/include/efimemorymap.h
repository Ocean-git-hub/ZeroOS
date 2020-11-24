#ifndef ZEROOS_EFIMEMORYMAP_H
#define ZEROOS_EFIMEMORYMAP_H

#include <efi/efi.h>
#include <stdint.h>

typedef struct {
    EFI_MEMORY_DESCRIPTOR *descriptorPointerBase;
    uint64_t memoryMapSize, mapKey, descriptorSize;
} EFI_MEMORY_MAP;

void efi_get_memory_map(EFI_MEMORY_MAP *memory_map);

uint64_t efi_get_free_page_address(uint64_t size);

#endif //ZEROOS_EFIMEMORYMAP_H
