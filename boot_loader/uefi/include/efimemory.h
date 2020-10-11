#ifndef ZEROOS_EFIMEMORY_H
#define ZEROOS_EFIMEMORY_H

#include <efi/efi.h>

void efi_allocate_pool(UINTN size, EFI_VOID **buffer);

void efi_free_pool(EFI_VOID *buffer);

EFI_STATUS efi_allocate_pages(uint64_t pages, uint64_t *memory);

void efi_set_memory(void *buffer, uint64_t size, uint8_t value);

#endif //ZEROOS_EFIMEMORY_H
