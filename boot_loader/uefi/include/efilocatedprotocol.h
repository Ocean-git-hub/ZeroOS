#ifndef ZEROOS_EFILOCATEDPROTOCOL_H
#define ZEROOS_EFILOCATEDPROTOCOL_H

#include <efi/efi.h>

extern EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *simple_file_system_protocol;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL *graphics_output_protocol;

void init_located_protocol();

#endif //ZEROOS_EFILOCATEDPROTOCOL_H
