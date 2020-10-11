#include <efimemory.h>

#include <efisystab.h>

void efi_allocate_pool(UINTN size, EFI_VOID **buffer) {
    get_system_table()->BootServices->EFI_ALLOCATE_POOL(EfiLoaderData, size, buffer);
}

void efi_free_pool(EFI_VOID *buffer) {
    get_system_table()->BootServices->EFI_FREE_POOL(buffer);
}

EFI_STATUS efi_allocate_pages(uint64_t pages, uint64_t *memory) {
    return get_system_table()->BootServices->EFI_ALLOCATE_PAGES(AllocateAddress, EfiLoaderCode, pages, memory);
}

void efi_set_memory(void *buffer, uint64_t size, uint8_t value) {
    get_system_table()->BootServices->EFI_SET_MEM(buffer, size, value);
}
