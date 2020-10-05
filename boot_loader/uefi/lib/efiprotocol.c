#include <efiprotocol.h>

#include <efi/efi.h>
#include <efisystab.h>

EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *simple_file_system_protocol;
EFI_GRAPHICS_OUTPUT_PROTOCOL *graphics_output_protocol;

void efi_located_protocol_initilize() {
    EFI_GUID simple_file_p = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    get_system_table()->BootServices->EFI_LOCATE_PROTOCOL(&simple_file_p, NULL, (void **) &simple_file_system_protocol);

    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    get_system_table()->BootServices->EFI_LOCATE_PROTOCOL(&gop_guid, NULL, (void **) &graphics_output_protocol);
}
