#include <efi/efi.h>
#include <efilib.h>

EFI_STATUS efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table) {
    efi_lib_initialize(system_table);
    efi_set_largest_screen_mode();
    efi_clear_screen();
    EFI_TIME time = efi_get_datetime();
    efi_printf(L"ZeroOS Boot Loader [FirmwareVendor: %s(%s)] [%u/%u/%u %02u:%02u]\n\r",
               efi_get_firmware_vendor(), efi_get_uefi_version(),
               time.Year, time.Month, time.Day, time.Hour, time.Minute);
    efi_get_input_key();
    efi_shutdown();
    return EFI_SUCCESS;
}
