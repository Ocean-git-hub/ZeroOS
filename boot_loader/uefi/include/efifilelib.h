#ifndef ZEROOS_EFIFILELIB_H
#define ZEROOS_EFIFILELIB_H

#include <efi/efi.h>

void get_root_file_protocol(EFI_FILE_PROTOCOL **root);

EFI_FILE_INFO *get_file_info(CHAR16 *file_name);

void read_file_to_address(uint64_t address, CHAR16 *file_name);

#endif //ZEROOS_EFIFILELIB_H
