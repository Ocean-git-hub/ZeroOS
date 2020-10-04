#include <efi/efi.h>
#include <efilib.h>

EFI_STATUS efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *_system_table) {
    init_systab(_system_table);
    init_located_protocol();
    system_table->ConOut->EFI_TEXT_SET_MODE(system_table->ConOut, get_largest_screen_mode());
    system_table->ConOut->EFI_TEXT_CLEAR_SCREEN(system_table->ConOut);
    print_string(L"Hello, UEFI!");
    while (1);
    return EFI_SUCCESS;
}
