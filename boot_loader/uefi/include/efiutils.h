#ifndef ZEROOS_UTILS_H
#define ZEROOS_UTILS_H

#include <windef.h>
#include <winnt.h>

#include <efi/efi.h>
#include <stdbool.h>
#include <efimemorymap.h>

typedef struct EFI_FRAME_BUFFER_INFO {
    uint64_t frameBufferBase, frameBufferSize, screenHeight, screenWidth;
} EFI_FRAME_BUFFER_INFO;

void efi_check_error(EFI_STATUS status, CHAR16 *message);

uint64_t get_largest_screen_mode();

CHAR16 *efi_get_uefi_version();

void efi_shutdown();

EFI_TIME efi_get_datetime();

CHAR16 *efi_get_firmware_vendor();

bool efi_is_equal_guid(EFI_GUID *guid1, EFI_GUID *guid2);

void *efi_get_configuration_table(EFI_GUID *guid);

void efi_get_memory_type_name(EFI_MEMORY_TYPE type, CHAR16 *buf);

EFI_FRAME_BUFFER_INFO efi_get_frame_buffer_info();

void efi_exit_boot_services(EFI_MEMORY_MAP *memory_map, void *image_handle);

#endif //ZEROOS_UTILS_H
