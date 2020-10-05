#include <efimemory.h>

#include <efisystab.h>

void efi_allocate_pool(UINTN size, EFI_VOID **buffer) {
    get_system_table()->BootServices->EFI_ALLOCATE_POOL(EfiLoaderData, size, buffer);
}

void efi_free_pool(EFI_VOID *buffer) {
    get_system_table()->BootServices->EFI_FREE_POOL(buffer);
}
