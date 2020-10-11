#include <efimemorymap.h>

#include <efisystab.h>
#include <efimemory.h>

void efi_get_memory_map(EFI_MEMORY_MAP *memory_map) {
    memory_map->memoryMapSize = 0;
    EFI_MEMORY_DESCRIPTOR *memoryDescriptor = NULL;
    uint32_t descriptorVersion;
    EFI_STATUS status = get_system_table()->BootServices->EFI_GET_MEMORY_MAP(&memory_map->memoryMapSize,
                                                                             memoryDescriptor,
                                                                             &memory_map->mapKey,
                                                                             &memory_map->descriptorSize,
                                                                             &descriptorVersion);
    while (status == EFI_BUFFER_TOO_SMALL || memoryDescriptor == NULL) {
        if (memoryDescriptor != NULL)
            efi_free_pool(memoryDescriptor);
        efi_allocate_pool(memory_map->memoryMapSize, (void **) &memoryDescriptor);

        status = get_system_table()->BootServices->EFI_GET_MEMORY_MAP(&memory_map->memoryMapSize,
                                                                      memoryDescriptor,
                                                                      &memory_map->mapKey,
                                                                      &memory_map->descriptorSize,
                                                                      &descriptorVersion);
    }
    memory_map->descriptorPointerBase = memoryDescriptor;
}

uint64_t efi_get_free_page_address(uint64_t size) {
    EFI_MEMORY_MAP memory_map;
    efi_get_memory_map(&memory_map);
    EFI_MEMORY_DESCRIPTOR *memory_descriptor = memory_map.descriptorPointerBase;
    for (uint32_t i = 0; i < memory_map.memoryMapSize / memory_map.descriptorSize; ++i) {
        if (memory_descriptor->Type == EfiConventionalMemory && memory_descriptor->NumberOfPages * 4 * 1024 > size) {
            uint64_t start = memory_descriptor->PhysicalStart;
            efi_free_pool(memory_map.descriptorPointerBase);
            return start;
        }
        memory_descriptor = (EFI_MEMORY_DESCRIPTOR *) ((uint64_t) memory_descriptor + memory_map.descriptorSize);
    }
    efi_free_pool(memory_map.descriptorPointerBase);
    return 0;
}
