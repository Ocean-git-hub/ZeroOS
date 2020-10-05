#ifndef ZEROOS_EFIPROTOCOL_H
#define ZEROOS_EFIPROTOCOL_H

#include <efi/efi.h>

extern EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *simple_file_system_protocol;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL *graphics_output_protocol;

void efi_located_protocol_initilize();

#endif //ZEROOS_EFIPROTOCOL_H
