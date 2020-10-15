#include <efiutils.h>
#include <stdbool.h>
#include <stdint.h>

#include <efi/efi.h>
#include <efisystab.h>
#include <efiio.h>
#include <efistring.h>
#include <efiprotocol.h>

CHAR16 uefi_version[15] = {};

void efi_check_error(EFI_STATUS status, CHAR16 *message) {
    if (status != EFI_SUCCESS) {
        efi_puts(L"Error: ");
        efi_puts(message);
        efi_puts(L": ");
        efi_printf(L"0x%016lx", status);
        while (true);
    }
}

uint64_t get_largest_screen_mode() {
    uint64_t columns = 0, rows = 0, mode = 0;
    for (int32_t i = 0; i < get_system_table()->ConOut->Mode->MaxMode; i++) {
        uint64_t c, r;
        EFI_STATUS Status = get_system_table()->ConOut->EFI_TEXT_QUERY_MODE(get_system_table()->ConOut, i, &c, &r);
        if (Status == EFI_SUCCESS) {
            if (c >= columns || r >= rows) {
                columns = c;
                rows = r;
                mode = i;
            }
        }
    }
    return mode;
}

void efi_shutdown() {
    get_system_table()->RuntimeServices->EFI_RESET_SYSTEM(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
}

CHAR16 *efi_get_uefi_version() {
    if (uefi_version[0])
        return uefi_version;
    switch (get_system_table()->Hdr.Revision) {
        case EFI_2_70_SYSTEM_TABLE_REVISION:
            efi_strcpy(uefi_version, L"Ver.2.7.0");
            break;
        case EFI_2_60_SYSTEM_TABLE_REVISION:
            efi_strcpy(uefi_version, L"Ver.2.6.0");
            break;
        case EFI_2_40_SYSTEM_TABLE_REVISION:
            efi_strcpy(uefi_version, L"Ver.2.4.0");
            break;
        case EFI_2_50_SYSTEM_TABLE_REVISION:
            efi_strcpy(uefi_version, L"Ver.2.5.0");
            break;
        case EFI_2_31_SYSTEM_TABLE_REVISION:
            efi_strcpy(uefi_version, L"Ver.2.3.1");
            break;
        case EFI_2_30_SYSTEM_TABLE_REVISION:
            efi_strcpy(uefi_version, L"Ver.2.3.0");
            break;
        case EFI_2_20_SYSTEM_TABLE_REVISION:
            efi_strcpy(uefi_version, L"Ver.2.2.0");
            break;
        case EFI_2_10_SYSTEM_TABLE_REVISION:
            efi_strcpy(uefi_version, L"Ver.2.1.0");
            break;
        case EFI_2_00_SYSTEM_TABLE_REVISION:
            efi_strcpy(uefi_version, L"Ver.2.0.0");
            break;
        case EFI_1_10_SYSTEM_TABLE_REVISION:
            efi_strcpy(uefi_version, L"Ver.1.1.0");
            break;
        case EFI_1_02_SYSTEM_TABLE_REVISION:
            efi_strcpy(uefi_version, L"Ver.1.0.2");
            break;
    }
    return uefi_version;
}

EFI_TIME efi_get_datetime() {
    EFI_TIME current_time;
    get_system_table()->RuntimeServices->EFI_GET_TIME(&current_time, NULL);
    return current_time;
}

CHAR16 *efi_get_firmware_vendor() {
    return get_system_table()->FirmwareVendor;
}

bool efi_is_equal_guid(EFI_GUID *guid1, EFI_GUID *guid2) {
    return ((uint64_t *) guid1)[0] == ((uint64_t *) guid2)[0] && ((uint64_t *) guid1)[1] == ((uint64_t *) guid2)[1];
}

void *efi_get_configuration_table(EFI_GUID *guid) {
    struct EFI_CONFIGURATION_TABLE *configuration_table = get_system_table()->ConfigurationTable;
    for (uint64_t i = 0; i < get_system_table()->NumberOfTableEntries; ++i) {
        if (efi_is_equal_guid(&configuration_table->VendorGuid, guid))
            return configuration_table->VendorTable;
        configuration_table++;
    }
    return NULL;
}

void efi_get_memory_type_name(EFI_MEMORY_TYPE type, CHAR16 *buf) {
    switch (type) {
        case EfiReservedMemoryType:
            efi_strcpy(buf, L"EfiReservedMemoryType");
            break;
        case EfiLoaderCode:
            efi_strcpy(buf, L"EfiLoaderCode");
            break;
        case EfiLoaderData:
            efi_strcpy(buf, L"EfiLoaderData");
            break;
        case EfiBootServicesCode:
            efi_strcpy(buf, L"EfiBootServicesCode");
            break;
        case EfiBootServicesData:
            efi_strcpy(buf, L"EfiBootServicesData");
            break;
        case EfiRuntimeServicesCode:
            efi_strcpy(buf, L"EfiRuntimeServicesCode");
            break;
        case EfiRuntimeServicesData:
            efi_strcpy(buf, L"EfiRuntimeServicesData");
            break;
        case EfiConventionalMemory:
            efi_strcpy(buf, L"EfiConventionalMemory");
            break;
        case EfiUnusableMemory:
            efi_strcpy(buf, L"EfiUnusableMemory");
            break;
        case EfiACPIReclaimMemory:
            efi_strcpy(buf, L"EfiACPIReclaimMemory");
            break;
        case EfiACPIMemoryNVS:
            efi_strcpy(buf, L"EfiACPIMemoryNVS");
            break;
        case EfiMemoryMappedIO:
            efi_strcpy(buf, L"EfiMemoryMappedIO");
            break;
        case EfiMemoryMappedIOPortSpace:
            efi_strcpy(buf, L"EfiMemoryMappedIOPortSpace");
            break;
        case EfiPalCode:
            efi_strcpy(buf, L"EfiPalCode");
            break;
        case EfiPersistentMemory:
            efi_strcpy(buf, L"EfiPersistentMemory");
            break;
        case EfiMaxMemoryType:
            efi_strcpy(buf, L"EfiMaxMemoryType");
            break;
        default:
            break;
    }
}

EFI_FRAME_BUFFER_INFO efi_get_frame_buffer_info() {
    return (EFI_FRAME_BUFFER_INFO) {
            .frameBufferBase=graphics_output_protocol->Mode->FrameBufferBase,
            .frameBufferSize=graphics_output_protocol->Mode->FrameBufferSize,
            .screenHeight=graphics_output_protocol->Mode->Info->VerticalResolution,
            .screenWidth=graphics_output_protocol->Mode->Info->HorizontalResolution};
}

void efi_exit_boot_services(EFI_MEMORY_MAP *memory_map, void *image_handle) {
    EFI_STATUS status;
    do {
        efi_get_memory_map(memory_map);
        status = get_system_table()->BootServices->EFI_EXIT_BOOT_SERVICES(image_handle, memory_map->mapKey);
    } while (status != EFI_SUCCESS);
}
