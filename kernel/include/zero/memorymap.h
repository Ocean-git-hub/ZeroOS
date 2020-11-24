#ifndef ZEROOS_MEMORYMAP_H
#define ZEROOS_MEMORYMAP_H

#include <stdint.h>
#include <stddef.h>

typedef enum {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiMaxMemoryType
} EFIMemoryType;

typedef struct {
    uint32_t Type;
    uintptr_t PhysicalStart;
    uintptr_t VirtualStart;
    uint64_t NumberOfPages;
    uint64_t Attribute;
} EFIMemoryDescriptor;

typedef struct {
    EFIMemoryDescriptor *descriptorPointerBase;
    uint64_t memoryMapSize, mapKey, descriptorSize;
} EFIMemoryMap;

#endif //ZEROOS_MEMORYMAP_H
