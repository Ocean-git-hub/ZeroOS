#ifndef ZEROOS_EFIIO_H
#define ZEROOS_EFIIO_H

#include <efi/efi.h>

void print_string(CHAR16 *str);

void print_string_n(CHAR16 *str);

void print_char(CHAR16 c);

EFI_INPUT_KEY get_input_key();

uint64_t gets(CHAR16 *buf, uint64_t buf_size);

#endif //ZEROOS_EFIIO_H
