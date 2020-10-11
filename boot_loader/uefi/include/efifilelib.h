#ifndef ZEROOS_EFIFILELIB_H
#define ZEROOS_EFIFILELIB_H

#include <efi/efi.h>

EFI_FILE_INFO *efi_get_file_info(CHAR16 *file_name);

void efi_read_file_to_address(CHAR16 *file_name, uint64_t address);

#endif //ZEROOS_EFIFILELIB_H
