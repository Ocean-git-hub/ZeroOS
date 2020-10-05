#ifndef ZEROOS_EFIMEMORY_H
#define ZEROOS_EFIMEMORY_H

#include <efi/efi.h>

void efi_allocate_pool(UINTN size, EFI_VOID **buffer);

void efi_free_pool(EFI_VOID *buffer);

#endif //ZEROOS_EFIMEMORY_H
